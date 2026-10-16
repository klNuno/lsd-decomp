#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/*
 * The application base class (vtable g_appVtbl, 0x20 bytes), the class Scene derives from
 * (vtable 0x8006D3C8, src/game/80025F7C.c). main (src/game/800118DC.c) makes the scene, starts it
 * with a display and a pad (slot 0x44), then runs it (slot 0x4C), which never returns.
 * Slots 0x50 to 0x64 are 0 here; Scene fills them (docs/discoveries.md, the ending video).
 */
typedef struct AppVtbl {
    ObjectVtbl base;
    s32 unk3C;                /* 0x3C 0 */
    void (*setScreenMode)();  /* 0x40 App_SetScreenMode (app, size, vramMode) */
    void (*start)();          /* 0x44 App_Start (app, display, pad) */
    void (*unk48)();          /* 0x48 func_8003B108, empty */
    void (*run)();            /* 0x4C App_Run, the main loop */
    void (*showLogos)();      /* 0x50 Scene: the logos, called with no argument */
    void (*playOpening)();    /* 0x54 Scene: the opening video */
    s32 (*runTitle)();        /* 0x58 Scene: the title, returns 0, 1 or 2 */
    void (*onTitle1)();       /* 0x5C Scene: empty, run when the title returns 1 */
    s32 (*runDream)();        /* 0x60 Scene: the dream, non-zero when the ending must play */
    void (*playEnding)();     /* 0x64 Scene: ETC\ENDING.STR */
} AppVtbl;

typedef struct App {
    AppVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    ScreenSize screenSize;    /* 0x0C g_appScreenSize (320, 240) at init */
    s32 vramMode;             /* 0x14 GsInitGraph's vrammode: 0 at init */
    s32 started;              /* 0x18 1 once start has run */
    ScreenEnv *env;           /* 0x1C display and pad, what every screen runs with */
} App;

/* The display slot start calls, missing from scene.h's DisplayVtbl */
typedef struct AppDisplayVtbl {
    u8 pad_00[0x44];
    void (*initGraph)();      /* 0x44 Display_InitGraph (display, size, vramMode): GsInitGraph */
} AppDisplayVtbl;

ObjectVtbl *Object_GetBaseVtbl(void);
AppVtbl *App_GetVtbl(void);
void File_SetBackend(s32 fileDevice);
s32 CdInit(void);
s32 g_cdInitDone;
extern char g_appScreenSize[];
void Display_SetCurrent(Display *display);
void Spu_ResetCold(void);
void GsInit3D(void);
void *Heap_Alloc(s32 size);
extern u8 g_appVtbl[];

/* fileDevice picks the file back end: 0x13 is the CD (File_SetBackend, src/game/80025F7C.c). */
void App_Init(App *app, s32 fileDevice) {
    Object_GetBaseVtbl()->init(app);
    app->vtbl = App_GetVtbl();
    if (g_cdInitDone == 0) {
        CdInit();
        g_cdInitDone = 1;
    }
    app->started = 0;
    File_SetBackend(fileDevice);
    app->vtbl->setScreenMode(app, g_appScreenSize, 0);
}

void App_Destroy(void) {
}

void App_SetScreenMode(App *app, ScreenSize *size, s32 vramMode) {
    app->screenSize = *size;
    app->vramMode = vramMode;
}

/* Makes display the current one, opens the screen, starts the sound and the 3D library. */
void App_Start(App *app, Display *display, Pad *pad) {
    ScreenEnv *env;

    if (app->started == 0) {
        Display_SetCurrent(display);
        ((AppDisplayVtbl *)display->vtbl)->initGraph(display, &app->screenSize, app->vramMode);
        Spu_ResetCold();
        GsInit3D();
        env = Heap_Alloc(0x14);
        app->env = env;
        env->display = display;
        app->env->pad = pad;
        app->env->clock = 0;
        app->env->root = 0;
        app->env->view = 0;
        app->started = 1;
    }
}

void func_8003B108(void) {
}

/* Logos once, then forever the opening video and the title; title result 2 runs a dream. */
void App_Run(App *app) {
    s32 r;

    if (app->started != 0) {
        app->vtbl->showLogos();
        for (;;) {
            app->vtbl->playOpening(app);
            for (;;) {
                r = app->vtbl->runTitle(app);
                if (r == 1) {
                    app->vtbl->onTitle1(app);
                    continue;
                }
                if (r == 2) {
                    if (app->vtbl->runDream(app) != 0) {
                        app->vtbl->playEnding(app);
                    }
                }
                if (r == 0) {
                    break;
                }
            }
        }
    }
}

AppVtbl *App_GetVtbl(void) {
    return (AppVtbl *)g_appVtbl;
}

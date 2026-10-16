#ifndef GAME_APP_H
#define GAME_APP_H

#include "common.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/screen.h"

/*
 * The application base class (vtable g_appVtbl, 0x20 bytes), the class Scene derives from
 * (vtable 0x8006D3C8, src/game/scene.c). main (src/game/main.c) makes the scene, starts it
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

/* Functions of src/game/app.c that other files call or reference (docs/naming.md, Prototypes) */
void App_Destroy(void);
void func_8003B108(void);
void App_Run(App *app);
AppVtbl *App_GetVtbl(void);

#endif

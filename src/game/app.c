#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

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

/* fileDevice picks the file back end: 0x13 is the CD (File_SetBackend, src/game/file_base.c). */
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
        display->vtbl->initGraph(display, &app->screenSize, app->vramMode);
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

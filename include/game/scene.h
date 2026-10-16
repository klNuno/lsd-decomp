#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "common.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/app.h"
#include "game/screen.h"

/* The scene settings main hands to Scene_New (g_sceneSettings: 0x13, 0, 1, 1, 1, 1). */
typedef struct SceneSettings {
    s32 fileBackend; /* 0x00 FILE_BACKEND_*, given to the base init (File_SetBackend) */
    s32 useCdSearch;        /* 0x04 DreamRunner_New's third argument: DreamRunner_Init calls File_EnableWait(unk4 == 0, 1, 1) */
    s32 videos;      /* 0x08 opening, reel, cinematic and ending videos */
    s32 logos;       /* 0x0C */
    s32 title;       /* 0x10 the graph and the main menu */
    s32 unk14;       /* 0x14 handed to DreamSys slot 0x228, which keeps it at +0x924 */
} SceneSettings;

/*
 * Scene (vtable g_sceneVtbl 0x8006D3C8, src/game/scene.c), the App the game runs: main
 * (src/game/main.c) makes it with g_sceneSettings, then calls setup (0x44) and run (0x4C).
 * Every slot of g_sceneVtbl; 0x00 to 0x3C are Object's, 0x48 and 0x4C the base class's.
 */
typedef struct SceneVtbl {
    s32 classWord;          /* 0x00 0x1F60 */
    void *(*delete_)();    /* 0x04 Object_Delete */
    void (*init)();        /* 0x08 Scene_Init (scene, settings) */
    void (*destroy)();     /* 0x0C App_Destroy, empty */
    u8 pad_10[0x40 - 0x10];
    void (*seedRandom)();  /* 0x40 Scene_SeedRandom */
    void (*setup)();       /* 0x44 Scene_Setup (scene, display, pad) */
    void (*unk48)();       /* 0x48 func_8003B108, empty */
    void (*run)();         /* 0x4C App_Run, the scene loop */
    void (*showLogos)();   /* 0x50 Scene_ShowLogos */
    void (*playOpening)(); /* 0x54 Scene_PlayOpening */
    s32 (*runTitle)();     /* 0x58 Scene_RunTitle */
    void (*unk5C)();       /* 0x5C func_80026690, empty: run when the title returns 1, which it never does */
    s32 (*runDream)();     /* 0x60 Scene_RunDream */
    void (*playEnding)();  /* 0x64 Scene_PlayEnding */
} SceneVtbl;

typedef struct Scene {
    SceneVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    /* App */
    ScreenSize screenSize;   /* 0x0C g_appScreenSize (320, 240), App_SetScreenMode */
    s32 vramMode;            /* 0x14 GsInitGraph's vrammode: 0 */
    s32 started;             /* 0x18 App_Start has built env */
    ScreenEnv *env;          /* 0x1C what every screen of the scene runs with */
    /* Scene */
    SceneSettings *settings; /* 0x20 */
    s32 skipGraph;           /* 0x24 the dream ended in flashback mode, an end or an erase: no graph before the next menu */
    struct DreamSys *dreamSys; /* 0x28 the game state, made with ETC\DREAME5.TMD */
} Scene;

/* Functions of src/game/scene.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Scene_New(SceneSettings *settings);

#endif

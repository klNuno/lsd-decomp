#include "common.h"
#include "game/scene.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/pad.h"
#include "game/file_base.h"
#include "game/app.h"
#include "game/video_screen.h"
#include "game/menu_screen.h"
#include "game/screen.h"
#include "game/tmd.h"
#include "game/path_table.h"
#include "game/dream_runner.h"
#include "game/menu.h"
#include "game/graph.h"
#include "game/dream_sys.h"

/*
 * The scene (vtable g_sceneVtbl, 0x2C bytes, made by Scene_New from main with the settings
 * g_sceneSettings): it derives from the App class of src/game/app.c (vtable 0x8006E4F0), whose run
 * loop App_Run calls slot 0x50 logos, then forever slot 0x54 opening video and slot 0x58
 * title; a title result of 2 runs the dream (slot 0x60), and a non-zero dream result plays the
 * ending (slot 0x64). docs/discoveries.md, "The ending plays when a year closes".
 *
 * File boundaries: likely (docs/layout.md)
 */

/*
 * DreamSys slot 0x1BC as the code calls it: the 4-byte {category, variant} is written through a
 * hidden first argument, which dream_sys.h's CineRef return cannot express.
 */
typedef struct SceneCineVtbl {
    u8 pad_000[0x1BC];
    void (*getCinematic)(u16 *, DreamSys *);
} SceneCineVtbl;

/* Scene_PlayReel's stack area: the frame count sits 8 bytes into 16. */
typedef struct ReelStack {
    s32 pad_00[2];
    s32 frames;
    s32 pad_0C;
} ReelStack;

static AppVtbl *Scene_GetVtbl(void);
/* not from game/path_table.h */
s32 Cine_GetVideoFrames(s32 videoId); /* defined as s16 in src/game/path_table.c; the callers here take the word as is */
static void Scene_ShowLogo(Scene *scene, void *path);
static void Scene_OnLogoClosed(void);
static void Scene_PlayCinematic(Scene *scene);
static s32 Scene_RunScreen(Screen *(*create)(), DreamSys *dreamSys, ScreenEnv *env);
static void Scene_PlayReel(Scene *scene);
extern AppVtbl g_sceneVtbl[];

/* main makes the one scene with g_sceneSettings. */
Scene *Scene_New(SceneSettings *settings) {
    Scene *scene;

    scene = Heap_Alloc(0x2C);
    /* No return on the NULL path: v0 still holds scene (NULL) from the allocator. */
    if (scene != NULL) {
        Scene_GetVtbl()->base.init(scene, settings);
        return scene;
    }
}

void Scene_Init(Scene *scene, SceneSettings *settings) {
    FileSource model;

    App_GetVtbl()->base.init(scene, settings->fileBackend);
    scene->vtbl = Scene_GetVtbl();
    scene->settings = settings;
    File_SetPathPrefix(File_GetRootDir());
    model.data = NULL;
    model.path = "ETC\\DREAME5.TMD";
    scene->dreamSys = DreamSys_New(Tmd_Create(&model), NULL, NULL);
    scene->skipGraph = 0;
    scene->dreamSys->vtbl->unk228(scene->dreamSys, settings->unk14);
    scene->vtbl->setScreenMode(scene); /* Scene_SeedRandom in the Scene vtable */
}

/* Slot 0x40: the only non-zero seed of the game (docs/discoveries.md, random numbers). */
void Scene_SeedRandom(void) {
    Rand_SeedAndNext(*(s32 *)0x1F800000 % 365, 0);
}

/* Slot 0x44, called once by main with the display and a new pad. */
void Scene_Start(Scene *scene, Display *display, Pad *pad) {
    if (scene->started == 0) {
        App_GetVtbl()->start(scene, display, pad, 0);
    }
}

/* Slot 0x50: the ASMIK logo picture, the ETC\ASMK.STR video, the OSD logo picture. */
void Scene_ShowLogos(Scene *scene) {
    s32 videoId;
    VideoScreen *video;
    char *path;

    if (scene->settings->logos != 0) {
        File_EnableWait(0, 0, 0);
        Scene_ShowLogo(scene, "ETC\\ASMKLOGO.TIM");
        video = VideoScreen_New(0, 0, 0, 0);
        path = Cine_GetLogoPath(&videoId);
        video->menuScreen.vtbl->run(video, scene->env, path, Cine_GetVideoFrames(videoId), 1);
        video->menuScreen.vtbl->delete_(video);
        Scene_ShowLogo(scene, "ETC\\OSDLOGO.TIM");
    }
}

/* Shows one logo picture; closing it runs Scene_OnLogoClosed. */
static void Scene_ShowLogo(Scene *scene, void *path) {
    MenuScreen *screen;

    screen = MenuScreen_New(0, 0, 0);
    screen->vtbl->setOnClose(screen, Scene_OnLogoClosed, scene);
    screen->vtbl->setTimeout(screen, 0);
    screen->vtbl->setPicture(screen, path, 0);
    screen->vtbl->run(screen, scene->env, 0);
    screen->vtbl->delete_(screen);
}

/* Each logo's close resolves part of the disc's file table (File_ResolvePathTablePart: half, then the rest). */
static void Scene_OnLogoClosed(void) {
    File_ResolvePathTablePart(0);
}

/* Slot 0x54: one of the 7 opening videos, picked by rand (Cine_PickOpeningPath). */
void Scene_PlayOpening(Scene *scene) {
    s32 videoId;
    s32 path;
    VideoScreen *video;

    if (scene->settings->videos != 0) {
        File_EnableWait(0, 0, 0);
        video = VideoScreen_New(0, 0, 0, 0);
        path = Cine_PickOpeningPath(&videoId, 0);
        video->menuScreen.vtbl->run(video, scene->env, path, Cine_GetVideoFrames(videoId), 1);
        video->menuScreen.vtbl->delete_(video);
    }
}

/*
 * Slot 0x58: the graph (except on day number 1 or right after skipGraph), the secret reel when the
 * graph returns 2, then the main menu; a menu result of 2 shows the graph again.
 * Returns 2 to start the dream, 0 to go back to the opening video.
 */
s32 Scene_RunTitle(Scene *scene) {
    s32 menuResult;

    if (scene->settings->title != 0) {
        File_EnableWait(0, 0, 0);
        if (scene->dreamSys->vtbl->getDayNumber(scene->dreamSys, 0) != 1 && scene->skipGraph == 0 &&
            Scene_RunScreen(Graph_New, scene->dreamSys, scene->env) == 2) {
            Scene_PlayReel(scene);
        }
        for (;;) {
            menuResult = Scene_RunScreen(Menu_New, scene->dreamSys, scene->env);
            if (menuResult != 2) {
                break;
            }
            Scene_RunScreen(Graph_New, scene->dreamSys, scene->env);
        }
        scene->skipGraph = 0;
        return menuResult == 0 ? 2 : 0;
    }
    return 2;
}

/* Makes a screen with create(dreamSys), runs it and deletes it; returns its result. */
static s32 Scene_RunScreen(Screen *(*create)(), DreamSys *dreamSys, ScreenEnv *env) {
    Screen *screen = create(dreamSys);
    s32 result = screen->vtbl->run(screen, env, 0);
    screen->vtbl->delete_(screen);
    return result;
}

/*
 * The secret video reel: FILM\SPDAY01A.STR played on for the length of the 20 videos of
 * categories 0 to 9 (Cine_GetSpecialDayRun), not skippable (docs/discoveries.md, the secret video reel).
 */
static void Scene_PlayReel(Scene *scene) {
    ReelStack reel;
    VideoScreen *video;
    s32 path;

    if (scene->settings->videos != 0) {
        File_EnableWait(0, 0, 0);
        video = VideoScreen_New(0, 0, 0, 0);
        path = Cine_GetSpecialDayRun(&reel.frames, 0, 0xA);
        video->menuScreen.vtbl->setTimeout(video, (u32)reel.frames / 15);
        video->menuScreen.vtbl->setSkippable(video, 0);
        video->menuScreen.vtbl->run(video, scene->env, path, -1, 1);
        video->menuScreen.vtbl->delete_(video);
    }
}

void func_80026690(void) {
}

/*
 * Slot 0x60: runs one dream. Returns 1 when the day number is back to 1 in a year above 0,
 * which makes the scene loop play the ending (slot 0x64).
 */
s32 Scene_RunDream(Scene *scene) {
    DreamRunner *runner;
    s32 runResult;
    DreamSys *dreamSys;
    s32 dayNumber;
    s32 year[2];
    s32 result;

    runner = DreamRunner_New(scene->env, scene->dreamSys, scene->settings->useCdSearch);
    runResult = runner->vtbl->run(runner);
    runner->vtbl->delete_(runner);
    switch (runResult) {
    case 2:
        Scene_PlayCinematic(scene);
        break;
    case 3:
        scene->skipGraph = 1;
        break;
    }
    dreamSys = scene->dreamSys;
    dayNumber = dreamSys->vtbl->getDayNumber(dreamSys, year);
    result = 0;
    if (year[0] != 0) {
        result = dayNumber == 1;
    }
    return result;
}

/*
 * The cinematic of the day: a FILM\ video for variants 0 and 1 (when videos are on), else a
 * still picture shown for 10 seconds (docs/discoveries.md, special days).
 */
static void Scene_PlayCinematic(Scene *scene) {
    u16 cinematic[2];
    s32 videoId[2];
    s32 unused[2];
    s32 path;
    DreamSys *dreamSys;
    Screen *screen;

    dreamSys = scene->dreamSys;
    ((SceneCineVtbl *)dreamSys->vtbl)->getCinematic(cinematic, dreamSys);
    path = Cine_GetPath(&videoId[0], cinematic[0] | (cinematic[1] << 16));
    File_EnableWait(0, 0, 0);
    if (videoId[0] != -1) {
        if (scene->settings->videos == 0) {
            return;
        }
        screen = (Screen *)VideoScreen_New(0, 0, 0, 0);
        screen->vtbl->setSkippable(screen, 0);
        screen->vtbl->run(screen, scene->env, path, Cine_GetVideoFrames(videoId[0]), 1);
    } else {
        screen = (Screen *)MenuScreen_New(0, 0, 0);
        screen->vtbl->setTimeout(screen, 0xA);
        screen->vtbl->setPicture(screen, path, 0);
        screen->vtbl->run(screen, scene->env, 0);
    }
    screen->vtbl->delete_(screen);
}

/* Slot 0x64: ETC\ENDING.STR (Cine_GetEndingPath), not skippable. */
void Scene_PlayEnding(Scene *scene) {
    s32 videoId;
    s32 path;
    VideoScreen *video;

    if (scene->settings->videos != 0) {
        File_EnableWait(0, 0, 0);
        video = VideoScreen_New(0, 0, 0, 0);
        video->menuScreen.vtbl->setSkippable(video, 0);
        path = Cine_GetEndingPath(&videoId, 0);
        video->menuScreen.vtbl->run(video, scene->env, path, Cine_GetVideoFrames(videoId), 1);
        video->menuScreen.vtbl->delete_(video);
    }
}

static AppVtbl *Scene_GetVtbl(void) {
    return g_sceneVtbl;
}

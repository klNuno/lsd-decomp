#include "common.h"
#include "game/heap.h"
#include "game/dreamsys.h"
#include "game/loader.h"
#include "game/scene.h"
#include "game/stage.h"

/*
 * Two classes live in this unit.
 *
 * The scene (vtable g_sceneVtbl, 0x2C bytes, made by Scene_New from main with the settings
 * g_sceneSettings): it derives from the class of src/game/8003AF8C.c (vtable 0x8006E4F0), whose run
 * loop App_Run calls slot 0x50 logos, then forever slot 0x54 opening video and slot 0x58
 * title; a title result of 2 runs the dream (slot 0x60), and a non-zero dream result plays the
 * ending (slot 0x64). docs/discoveries.md, "The ending plays when a year closes".
 *
 * The file base class (vtable g_fileBaseVtbl, returned by File_GetBaseVtbl, include/game/loader.h):
 * delete, init, destroy, load the whole file, free its data. File_SetBackend picks the back end
 * (0x13 the CD, 0x23 an empty one) and copies its I/O slots into every file class; the helpers
 * at the end forward to the CD functions of src/game/800271D8.c only when the CD back end is on.
 */

/* The back end ids: the tag word of the back end's vtable. */
#define FILE_BACKEND_CD 0x13   /* g_fileVtable, src/game/800271D8.c */
#define FILE_BACKEND_NULL 0x23 /* D_8006D9BC: every I/O slot is empty */

/* The scene settings main hands to Scene_New (g_sceneSettings: 0x13, 0, 1, 1, 1, 1). */
typedef struct SceneSettings {
    s32 fileBackend; /* 0x00 FILE_BACKEND_*, given to the base init (File_SetBackend) */
    s32 unk4;        /* 0x04 DreamRunner_New's third argument: DreamRunner_Init calls File_EnableWait(unk4 == 0, 1, 1) */
    s32 videos;      /* 0x08 opening, reel, cinematic and ending videos */
    s32 logos;       /* 0x0C */
    s32 title;       /* 0x10 the graph and the main menu */
    s32 unk14;       /* 0x14 handed to DreamSys slot 0x228, which keeps it at +0x924 */
} SceneSettings;

/* Every slot of g_sceneVtbl; 0x00 to 0x3C are Object's, 0x48 and 0x4C the base class's. */
typedef struct SceneVtbl {
    s32 tag;               /* 0x00 0x1F60 */
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

/* The slots of the base class (vtable 0x8006E4F0, src/game/8003AF8C.c) this unit calls. */
typedef struct SceneBaseVtbl {
    u8 pad_00[0x08];
    void (*init)();        /* 0x08 App_Init (scene, fileBackend): CdInit, File_SetBackend */
    u8 pad_0C[0x44 - 0x0C];
    void (*setup)();       /* 0x44 App_Start (scene, display, pad): builds the ScreenEnv */
} SceneBaseVtbl;

typedef struct Scene {
    SceneVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    ScreenPoint screenSize;  /* 0x0C set by the base slot 0x40 (App_SetScreenMode), (320, 240) from its init */
    s32 unk14;               /* 0x14 the base slot 0x40's third argument */
    s32 started;             /* 0x18 the base setup has built env */
    ScreenEnv *env;          /* 0x1C what every screen of the scene runs with */
    SceneSettings *settings; /* 0x20 */
    s32 skipGraph;           /* 0x24 the dream ended in flashback mode, an end or an erase: no graph before the next menu */
    DreamSys *dreamSys;      /* 0x28 the game state, made with ETC\DREAME5.TMD */
} Scene;

/*
 * DreamSys slot 0x1BC as the code calls it: the 4-byte {category, variant} is written through a
 * hidden first argument, which dreamsys.h's CineRef return cannot express.
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

/*
 * A file object as the base class reads it: Object, then the fields of the CD back end
 * (src/game/800271D8.c) and of the classes of include/game/loader.h.
 */
typedef struct FileObject {
    FileVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;  /* 0x0C set by open (File_LoadByName), cleared by close (File_Unload) */
    s32 data;    /* 0x10 the whole file, or a parent's bytes */
    s32 size;    /* 0x14 0 when the data is borrowed */
    u8 pad_18[0x20 - 0x18];
    u16 unk20;   /* 0x20 when set, freeData keeps the data */
    s16 unk22;
    u32 flags;   /* 0x24 done requests (File_ServiceQueue); bit 0 set by the base onLoaded */
    s16 direct;  /* 0x28 the CD back end runs requests at once instead of queueing them */
    s16 unk2A;
} FileObject;

void func_8004A070(s32);
s32 g_fileBackend;
void File_Lock(void);
void File_Unlock(void);
s32 File_IsBusy(void);
s32 File_IsDone(void);
s32 File_GetOpKind(void);
s32 File_GetState(void);
FileVtbl *File_GetVtable(void);
FileVtbl *func_8002C438(void);
s32 func_8002C448(s32 *optionOut);
s32 File_GetEnabled(s32 *optionOut);
s32 func_8002C478(void);
s32 File_GetVSyncMode(void);
void Rand_SeedAndNext(s32, s32);
ObjectVtbl *Object_GetBaseVtbl(void);
FileVtbl *File_GetBaseVtbl(void);
SceneBaseVtbl *App_GetVtbl(void);
void Heap_Free(void *);
s8 *strcat(s8 *, s8 *);
s32 Heap_Alloc(s32);
SceneVtbl *Scene_GetVtbl(void);
s32 func_8002C468(s32, s32, s32);
s32 File_Enable(s32, s32, s32);
s32 g_fileDirTableSet;
void File_SetDirTable(s32);
void File_SetDirCount(s32);
s32 File_GetDirCount(void);
s32 File_ResolveEntries(s32, s32);
void File_CopyIoSlots(FileVtbl *dst, FileVtbl *src);
extern FileVtbl *(*g_fileClassGetters[])();
void *File_GetRootDir(void);
void File_SetPathPrefix(void *rootDir);
s32 Tmd_Create(s32 source);
DreamSys *DreamSys_New(s32 model, s32 unk58, s32 camera); /* DreamSys_Init stores the second at +0x58 */
void File_EnableWait(s32 enabled, s32 option, s32 vsyncMode);
VideoScreen *VideoScreen_New(s32, s32, s32, s32);
s32 Cine_PickOpeningPath(s32 *videoId, s32 unused); /* the definition takes one argument */
s32 Cine_GetVideoFrames(s32 videoId); /* defined as s16 in src/game/80048894.c; the callers here take the word as is */
MenuScreen *MenuScreen_New(s32, s32, s32);
void Scene_ShowLogo(Scene *scene, void *path);
void Scene_OnLogoClosed(void);
s32 Cine_GetEndingPath(s32 *videoId, s32 unused); /* the definition takes one argument */
char *Cine_GetLogoPath(s32 *videoId);
DreamRunner *DreamRunner_New(ScreenEnv *env, DreamSys *dreamSys, s32 unk4);
void Scene_PlayCinematic(Scene *scene);
s32 Cine_GetSpecialDayRun(s32 *frames, s32 category, s32 count);
s32 Scene_RunScreen(Screen *(*create)(), DreamSys *dreamSys, ScreenEnv *env);
void Scene_PlayReel(Scene *scene);
extern Screen *Graph_New(DreamSys *dreamSys);
extern Screen *func_8004D518(DreamSys *dreamSys);
s32 Cine_GetPath(s32 *videoId, s32 cinematic);
extern SceneVtbl g_sceneVtbl[];
extern FileVtbl g_fileBaseVtbl[];
s8 *g_filePathPrefix;
s8 *File_GetPathPrefix(void);

/* main makes the one scene with g_sceneSettings. */
s32 Scene_New(SceneSettings *settings) {
    s32 scene;

    scene = Heap_Alloc(0x2C);
    /* No return on the NULL path: v0 still holds scene (0) from the allocator. */
    if (scene != 0) {
        Scene_GetVtbl()->init(scene, settings);
        return scene;
    }
}

void Scene_Init(Scene *scene, SceneSettings *settings) {
    FileSource model;

    App_GetVtbl()->init(scene, settings->fileBackend);
    scene->vtbl = Scene_GetVtbl();
    scene->settings = settings;
    File_SetPathPrefix(File_GetRootDir());
    model.data = 0;
    model.path = (s32)"ETC\\DREAME5.TMD";
    scene->dreamSys = DreamSys_New(Tmd_Create((s32)&model), 0, 0);
    scene->skipGraph = 0;
    scene->dreamSys->vtbl->unk228(scene->dreamSys, settings->unk14);
    scene->vtbl->seedRandom(scene);
}

/* Slot 0x40: the only non-zero seed of the game (docs/discoveries.md, random numbers). */
void Scene_SeedRandom(void) {
    Rand_SeedAndNext(*(s32 *)0x1F800000 % 365, 0);
}

/* Slot 0x44, called once by main with the display and a new pad. */
void Scene_Setup(Scene *scene, Display *display, Pad *pad) {
    if (scene->started == 0) {
        App_GetVtbl()->setup(scene, display, pad, 0);
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
        video->vtbl->run(video, scene->env, path, Cine_GetVideoFrames(videoId), 1);
        video->vtbl->delete_(video);
        Scene_ShowLogo(scene, "ETC\\OSDLOGO.TIM");
    }
}

/* Shows one logo picture; closing it runs Scene_OnLogoClosed. */
void Scene_ShowLogo(Scene *scene, void *path) {
    MenuScreen *screen;

    screen = MenuScreen_New(0, 0, 0);
    screen->vtbl->setOnClose(screen, Scene_OnLogoClosed, scene);
    screen->vtbl->setTimeout(screen, 0);
    screen->vtbl->setPicture(screen, path, 0);
    screen->vtbl->run(screen, scene->env, 0);
    screen->vtbl->delete_(screen);
}

/* Each logo's close resolves part of the disc's file table (func_8004A070: half, then the rest). */
void Scene_OnLogoClosed(void) {
    func_8004A070(0);
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
        video->vtbl->run(video, scene->env, path, Cine_GetVideoFrames(videoId), 1);
        video->vtbl->delete_(video);
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
            menuResult = Scene_RunScreen(func_8004D518, scene->dreamSys, scene->env);
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
s32 Scene_RunScreen(Screen *(*create)(), DreamSys *dreamSys, ScreenEnv *env) {
    Screen *screen = create(dreamSys);
    s32 result = screen->vtbl->run(screen, env, 0);
    screen->vtbl->delete_(screen);
    return result;
}

/*
 * The secret video reel: FILM\SPDAY01A.STR played on for the length of the 20 videos of
 * categories 0 to 9 (Cine_GetSpecialDayRun), not skippable (docs/discoveries.md, the secret video reel).
 */
void Scene_PlayReel(Scene *scene) {
    ReelStack reel;
    VideoScreen *video;
    s32 path;

    if (scene->settings->videos != 0) {
        File_EnableWait(0, 0, 0);
        video = VideoScreen_New(0, 0, 0, 0);
        path = Cine_GetSpecialDayRun(&reel.frames, 0, 0xA);
        video->vtbl->setTimeout(video, (u32)reel.frames / 15);
        video->vtbl->setSkippable(video, 0);
        video->vtbl->run(video, scene->env, path, -1, 1);
        video->vtbl->delete_(video);
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

    runner = DreamRunner_New(scene->env, scene->dreamSys, scene->settings->unk4);
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
void Scene_PlayCinematic(Scene *scene) {
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
        video->vtbl->setSkippable(video, 0);
        path = Cine_GetEndingPath(&videoId, 0);
        video->vtbl->run(video, scene->env, path, Cine_GetVideoFrames(videoId), 1);
        video->vtbl->delete_(video);
    }
}

SceneVtbl *Scene_GetVtbl(void) {
    return g_sceneVtbl;
}

/* File base slot 0x04, shared by every file class. */
s32 File_Delete(FileObject *file) {
    file->unk20 = 0;
    file->vtbl->destroy(file);
    Object_GetBaseVtbl()->destroy(file);
    Heap_Free(file);
    return 0;
}

/* File base slot 0x08. */
void File_InitBase(FileObject *file) {
    Object_GetBaseVtbl()->init(file);
    file->vtbl = File_GetBaseVtbl();
    file->isOpen = 0;
    file->data = 0;
    file->size = 0;
    file->unk20 = 0;
    file->unk22 = 0;
    file->flags = 0;
    file->direct = 0;
    file->unk2A = 0;
}

/* File base slot 0x0C: close, then free the data. */
void File_DestroyBase(FileObject *file) {
    file->vtbl->close();
    file->vtbl->freeData(file);
}

/* File base slot 0x58: open path, read the whole file into a new block, close. */
void File_LoadWhole(FileObject *file, char *path) {
    s32 wasOpen;
    s32 size;
    s32 buffer;

    if (file->data == 0) {
        wasOpen = file->isOpen;
        file->isOpen = 0;
        file->vtbl->open(file, path, 1, 0);
        size = file->vtbl->seek(file, 0, 2);
        buffer = Heap_Alloc(size);
        if (buffer != 0) {
            file->vtbl->seek(file, 0, 0);
            file->vtbl->read(file, buffer, size);
            file->vtbl->close(file);
            file->data = buffer;
            file->size = size;
            file->isOpen = wasOpen;
            return;
        }
        Heap_Free(0);
        file->vtbl->close(file);
    }
}

/* File base slot 0x5C: frees owned data (size != 0) unless unk20 is set. */
void File_FreeData(FileObject *file) {
    if (file->data != 0 && file->size != 0 && file->unk20 == 0) {
        Heap_Free(file->data);
        file->data = 0;
    }
}

void func_80026C80(void) {
}

/* File base slot 0x64 (onLoaded). */
void File_MarkLoaded(FileObject *file) {
    file->flags |= 1;
}

FileVtbl *File_GetBaseVtbl(void) {
    return g_fileBaseVtbl;
}

/* The vtable of the back end in use. */
FileVtbl *File_GetBackendVtbl(void) {
    if (g_fileBackend == FILE_BACKEND_NULL) {
        return func_8002C438();
    }
    return File_GetVtable();
}

FileSource *File_MakeSource(FileSource *source, s32 data, s32 path, s32 unk_08) {
    source->data = data;
    source->path = path;
    source->unk_08 = unk_08;
    return source;
}

/* Picks the back end and copies its I/O slots into the base class and every class of g_fileClassGetters. */
void File_SetBackend(s32 backend) {
    FileVtbl *(**getter)();
    FileVtbl *io;
    FileVtbl *vtbl;

    getter = g_fileClassGetters;
    g_fileBackend = backend;
    if (backend == FILE_BACKEND_CD) {
        io = File_GetVtable();
    } else {
        io = func_8002C438();
    }
    vtbl = File_GetBaseVtbl();
    File_CopyIoSlots(vtbl, io);
    while (*getter != NULL) {
        vtbl = (*getter)();
        getter++;
        File_CopyIoSlots(vtbl, io);
    }
}

/* Copies the I/O slots 0x40 to 0x58 and 0x68 to 0x74. */
void File_CopyIoSlots(FileVtbl *dst, FileVtbl *src) {
    dst->unk_40 = src->unk_40;
    dst->open = src->open;
    dst->close = src->close;
    dst->seek = src->seek;
    dst->unk_50 = src->unk_50;
    dst->read = src->read;
    dst->load = src->load;
    dst->runQueue = src->runQueue;
    dst->loadAsync = src->loadAsync;
    dst->unk_70 = src->unk_70;
    dst->cancel = src->cancel;
}

void File_LockBackend(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        File_Lock();
    }
}

void File_UnlockBackend(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        File_Unlock();
    }
}

s32 File_IsBackendBusy(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_IsBusy();
    }
    return 0;
}

s32 File_IsBackendDone(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_IsDone();
    }
    return 1;
}

s32 File_GetBackendOpKind(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetOpKind();
    }
    return 0;
}

s32 File_GetBackendState(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetState();
    }
    return 0;
}

/* File_Enable (or the empty back end's) until it accepts: it refuses while a CD operation runs. */
void File_EnableWait(s32 enabled, s32 option, s32 vsyncMode) {
    s32 (*enable)(s32, s32, s32);

    enable = func_8002C468;
    if (g_fileBackend == FILE_BACKEND_CD) {
        enable = File_Enable;
    }
    while (enable(enabled, option, vsyncMode) == 0) {
    }
}

s32 File_GetBackendEnabled(s32 *optionOut) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetEnabled(optionOut);
    }
    return func_8002C448(optionOut);
}

s32 File_GetBackendVSyncMode(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetVSyncMode();
    }
    return func_8002C478();
}

/* Appends count entries of 0x1C bytes to the CD directory and resolves the new ones. */
s32 File_AddDirEntries(s32 table, s32 count) {
    s32 oldCount;

    if (g_fileBackend == FILE_BACKEND_CD) {
        g_fileDirTableSet = 1;
        File_SetDirTable(table);
        oldCount = File_GetDirCount();
        File_SetDirCount(oldCount + count);
        return File_ResolveEntries(table + (oldCount * 0x1C), count);
    }
    return 1;
}

/* The disc folder every path starts with, "CDI\" (File_BuildPath). */
void File_SetPathPrefix(void *rootDir) {
    g_filePathPrefix = rootDir;
}

s8 *File_GetPathPrefix(void) {
    return g_filePathPrefix;
}

/* dst = prefix (when not NULL) + name + suffix. */
s8 *File_JoinPath(s8 *dst, s8 *name, s8 *prefix, s8 *suffix) {
    *dst = 0;
    if (prefix != NULL) {
        strcat(dst, prefix);
    }
    strcat(dst, name);
    strcat(dst, suffix);
    return dst;
}

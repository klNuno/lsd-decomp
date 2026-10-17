#ifndef GAME_DREAM_RUNNER_H
#define GAME_DREAM_RUNNER_H

#include "common.h"
#include "game/heap.h"
#include "game/sound_bank.h"
#include "game/task.h"
#include "game/dream_sys.h"
#include "game/screen.h"
#include "game/view.h"
#include "game/place.h"

/*
 * DreamRunner (src/game/dream_runner.c): vtable 0x800865C8, class id 0x1F230, 0x50 bytes, a Task
 * (task.h). Scene_RunDream builds one for each dream: it loads the dreamer model and the music bank,
 * creates the dream stage for the stage DreamSys_StartDay returns, rebuilds it on a link and ends
 * the day.
 */

typedef struct DreamRunnerVtbl {
    s32 classWord;          /* 0x1F230 */
    void *(*delete_)();     /* 0x04 Object_Delete */
    void (*init)();         /* 0x08 DreamRunner_Init */
    void (*destroy)();      /* 0x0C DreamRunner_Destroy */
    void (*watch)();        /* 0x10 Object_Watch */
    void (*unwatch)();      /* 0x14 Object_Unwatch */
    u8 pad_18[0x38 - 0x18];
    void (*onNotify)();     /* 0x38 DreamRunner_OnNotify */
    u8 pad_3C[0x40 - 0x3C];
    void (*clearPhase)();   /* 0x40 DreamRunner_ClearPhase */
    s32 (*run)();           /* 0x44 DreamRunner_Run */
    void (*finish)();        /* 0x48 DreamRunner_Finish */
    void (*start)();        /* 0x4C DreamRunner_Start */
    void (*end)();        /* 0x50 DreamRunner_End */
    void (*update)();       /* 0x54 DreamRunner_Update */
    u8 pad_58[0x60 - 0x58];
    void (*setState)();     /* 0x60 Task_SetState */
    u8 pad_64[0x80 - 0x64];
    void (*onDreamSysMessage)(); /* 0x80 DreamRunner_OnDreamSysMessage, empty */
    void (*onPlaceMessage)();    /* 0x84 DreamRunner_OnPlaceMessage */
} DreamRunnerVtbl;

/* Phases of DreamRunner +0x3C. */
#define RUNNER_IDLE 0
#define RUNNER_STARTING 1   /* start the day on the next update */
#define RUNNER_IN_STAGE 2
#define RUNNER_RELINK 3     /* rebuild the stage for DreamSys's new stage on the next update */

typedef struct DreamRunner {
    DreamRunnerVtbl *vtbl;
    u8 pad_04[0x0C - 0x04];
    ScreenEnv *context;     /* 0x0C the scene's (screen.h): root is the StageMap (StageMap_New(0, 1)), view a DreamView */
    Object *clock;
    u8 pad_14[0x18 - 0x14];
    View *view;             /* 0x18 (view.h): slot 0x70 gets DreamSys and two points 1200 units up */
    u32 ticks;              /* 0x1C */
    u8 pad_20[0x28 - 0x20];
    s32 result;             /* 0x28 1 nothing to play, 2 play DreamSys's cinematic (Scene_RunDream), 3 flashback mode, end or erase */
    u8 pad_2C[0x34 - 0x2C];
    SoundBank *sound;       /* 0x34 */
    DreamSys *dreamSys;     /* 0x38 */
    s32 phase;              /* 0x3C RUNNER_* */
    Object *music;          /* 0x40 Bgm_New(Music_PickBank(0), 0, 1) */
    struct Tim *etcTim;     /* 0x44 ETC\ETC.TIM (tim.h) */
    struct Tmd *dreamerModel; /* 0x48 ETC\DREAMER.TMD (tmd.h) */
    Place *place;           /* 0x4C the dream stage, Place_New (place.h) */
} DreamRunner;

/* Functions of src/game/dream_runner.c that other files call or reference (docs/naming.md, Prototypes) */
struct DreamRunner *DreamRunner_New(ScreenEnv *context, DreamSys *dreamSys, s32 useCdSearch);
void File_ResolvePathTablePart(s32 wholeTable);

#endif

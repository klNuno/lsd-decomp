#ifndef GAME_DREAM_RUNNER_H
#define GAME_DREAM_RUNNER_H

#include "common.h"
#include "game/heap.h"
#include "game/sound_bank.h"
#include "game/task.h"
#include "game/dream_sys.h"

/*
 * DreamRunner (src/game/dream_runner.c): vtable 0x800865C8, class id 0x1F230, 0x50 bytes, a Task
 * (task.h). Scene_RunDream builds one for each dream: it loads the dreamer model and the music bank,
 * creates the dream stage for the stage DreamSys_StartDay returns, rebuilds it on a link and ends
 * the day.
 */

/* The camera-like object at +0x18 (base class field): slot 0x70 gets DreamSys and two points 1200 units up. */
typedef struct RunnerViewVtbl {
    u8 pad_00[0x44];
    void (*setScreenSize)();
    u8 pad_48[0x4C - 0x48];
    void (*setPacketCount)();
    u8 pad_50[0x70 - 0x50];
    void (*setCamera)();
    void (*detach)();
    u8 pad_78[0x8C - 0x78];
    void (*allocOt)();
    void (*freeOt)();
    u8 pad_94[0xAC - 0x94];
    struct RunnerViewSub *(*getOverlay)();
} RunnerViewVtbl;

typedef struct RunnerViewSubVtbl {
    u8 pad_00[0x60];
    void (*setVisible)();
} RunnerViewSubVtbl;

typedef struct RunnerViewSub {
    RunnerViewSubVtbl *vtbl;
} RunnerViewSub;

typedef struct RunnerView {
    RunnerViewVtbl *vtbl;
} RunnerView;

/* The object at +0xC (from the scene, +0x1C): its +0 answers slot 0x7C, the runner fills +0x8 to +0x10. */
typedef struct RunnerContextHeadVtbl {
    u8 pad_00[0x7C];
    s32 (*getScreenRect)();
} RunnerContextHeadVtbl;

typedef struct RunnerContextHead {
    RunnerContextHeadVtbl *vtbl;
} RunnerContextHead;

typedef struct RunnerContext {
    RunnerContextHead *display;
    Object *pad;           /* watched by DreamSys while the runner runs */
    Object *clock;           /* Clock_Create() */
    struct StageMap *map;   /* 0x0C StageMap_New(0, 1) */
    struct View *view;     /* DreamView_New(), class 0x800869D8 */
} RunnerContext;

/* The dream stage (place.h, class id 0x2F230) as the runner drives it. */
typedef struct RunnerStageVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();     /* 0x04 */
    u8 pad_08[0x44 - 0x08];
    void (*start)();        /* 0x44 (stage, context, DreamSys) */
    void (*stop)();         /* 0x48 */
} RunnerStageVtbl;

typedef struct RunnerStage {
    RunnerStageVtbl *vtbl;
} RunnerStage;

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
    void (*onStageMessage)();    /* 0x84 DreamRunner_OnStageMessage */
} DreamRunnerVtbl;

/* Phases of DreamRunner +0x3C. */
#define RUNNER_IDLE 0
#define RUNNER_STARTING 1   /* start the day on the next update */
#define RUNNER_IN_STAGE 2
#define RUNNER_RELINK 3     /* rebuild the stage for DreamSys's new stage on the next update */

typedef struct DreamRunner {
    DreamRunnerVtbl *vtbl;
    u8 pad_04[0x0C - 0x04];
    RunnerContext *context; /* 0x0C */
    Object *clock;
    u8 pad_14[0x18 - 0x14];
    RunnerView *view;       /* 0x18 */
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
    RunnerStage *stage;     /* 0x4C the dream stage, Place_New */
} DreamRunner;

/* Functions of src/game/dream_runner.c that other files call or reference (docs/naming.md, Prototypes) */
struct DreamRunner *DreamRunner_New(ScreenEnv *context, DreamSys *dreamSys, s32 useCdSearch);
void File_ResolvePathTablePart(s32 wholeTable);

#endif

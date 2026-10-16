#include "common.h"
#include "game/dream_runner.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/bgm.h"
#include "game/tim.h"
#include "game/clock.h"
#include "game/tmd.h"
#include "game/path_table.h"
#include "game/task.h"
#include "game/stage_map.h"
#include "game/dream_view.h"
#include "game/place.h"
#include "game/dream_sys.h"
#include "game/sym.h"

/*
 * DreamRunner (vtable g_dreamRunnerVtbl 0x800865C8, types in game/dream_runner.h): the object built for
 * each dream. It loads the dreamer model and the music bank, creates the place, rebuilds it after a
 * link.
 *
 * File boundaries: guess (docs/layout.md)
 */

extern u8 g_dreamRunnerVtbl[];
extern s32 g_runnerViewpoint[];        /* {0, -1200, 0} and {0, -1200, 10000}: the points DreamRunner_Start gives the view */
extern s32 g_runnerRefPoint[];

/* The file argument of Tmd_Create (TMD loader). */
typedef struct TmdFileArg {
    s32 data;
    s32 path;
    s32 unk8;
} TmdFileArg;

/* DreamSys slot 0x1BC as called here: the CineRef comes back through a hidden pointer, read as {category, variant}. */
typedef struct RunnerCine {
    s16 category;
    s16 variant;
    s32 unk4;
} RunnerCine;

/*
 * DreamRunner_OnStageMessage calls the dream stage (slots 0x4, 0x48) and DreamSys (0x1B8 endDay, 0x1BC
 * getCinematic) through one pointer variable; typing them apart changes its registers.
 */
typedef struct RunnerPeerVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();
    u8 pad_08[0x48 - 0x08];
    void (*stop)();
    u8 pad_4C[0x1B8 - 0x4C];
    s32 (*endDay)();
    void (*getCinematic)(RunnerCine *out, struct RunnerPeer *dreamSys);
} RunnerPeerVtbl;

typedef struct RunnerPeer {
    RunnerPeerVtbl *vtbl;
} RunnerPeer;

s32 g_pathTablePartCount; /* File_ResolvePathTablePart call count */
s32 g_pathTableFirstHalf;

/* not from game/task.h: other files read this vtable through their own views of the slots */
TaskVtbl *Task_GetVtbl(void);
static DreamRunnerVtbl *DreamRunner_GetVtbl(void);

void DreamRunner_CreateStage(DreamRunner *runner, s32 stage);

/* Called by Scene_RunDream for each dream with the scene's context and its DreamSys. */
s32 DreamRunner_New(s32 context, s32 dreamSys, s32 useCdSearch) {
    s32 runner;

    runner = Heap_Alloc(0x50);
    if (runner != 0) {
        DreamRunner_GetVtbl()->init(runner, context, dreamSys, useCdSearch);
        return runner;
    }
    return 0;
}

/* The world constructor: dreamer model, spawn flags, music bank, the map, and DreamSys watched. */
void DreamRunner_Init(DreamRunner *runner, RunnerContext *context, DreamSys *dreamSys, s32 useCdSearch) {
    TmdFileArg modelFile;
    s32 bankName;
    RunnerRes *tim;
    RunnerRes *res;

    bankName = Music_GetEffectsBank(0);
    Task_GetVtbl()->init(runner, bankName, 0);
    runner->vtbl = DreamRunner_GetVtbl();
    Sym_LoadModels();
    tim = (RunnerRes *)Tim_New((s32)"ETC\\ETC.TIM");
    runner->etcTim = tim;
    tim->vtbl->upload(tim);
    res = runner->etcTim;
    res->vtbl->freeData(res);
    modelFile.data = 0;
    modelFile.path = (s32)"ETC\\DREAMER.TMD";
    runner->dreamerModel = (RunnerRes *)Tmd_Create((s32)&modelFile);
    runner->music = Bgm_New(Music_PickBank(0), 0, 1);
    File_ResolvePathTablePart(1);
    File_EnableWait(useCdSearch == 0, 1, 1);
    runner->context = context;
    context->view = (Object *)DreamView_New();
    context->clock = Clock_Create();
    context->map = (StageMap *)StageMap_New(0, 1);
    runner->dreamSys = dreamSys;
    runner->vtbl->watch(runner, dreamSys);
    dreamSys->vtbl->setSoundBank(dreamSys, runner->sound);
    dreamSys->vtbl->setEtcTim(dreamSys, runner->etcTim);
    runner->vtbl->clearPhase(runner);
}

void DreamRunner_Destroy(DreamRunner *runner) {
    RunnerContext *context;

    context = runner->context;
    runner->vtbl->unwatch(runner, runner->dreamSys);
    context->map = context->map->vtbl->delete_(context->map);
    context->clock = context->clock->vtbl->delete_(context->clock);
    context->view = context->view->vtbl->delete_(context->view);
    runner->music->vtbl->delete_(runner->music);
    runner->dreamerModel->vtbl->delete_(runner->dreamerModel);
    runner->etcTim->vtbl->delete_(runner->etcTim);
    Sym_FreeModels();
    Task_GetVtbl()->destroy(runner);
}

/* Messages from DreamSys (class id 0x1F34) and from the dream stage (0x2F230). */
void DreamRunner_OnNotify(DreamRunner *runner, s32 **sender, s32 message) {
    s32 classId;

    Task_GetVtbl()->onNotify(runner, sender, message);
    classId = **sender;
    if ((classId & 0xFFFF) == 0x1F34) {
        runner->vtbl->onDreamSysMessage(runner, sender, message);
    } else if ((classId & 0xFFFFF) == 0x2F230) {
        runner->vtbl->onStageMessage(runner, sender, message);
    }
}

void DreamRunner_ClearPhase(DreamRunner *runner) {
    runner->phase = RUNNER_IDLE;
}

/* DreamSys watches the context's objects, then the task loop runs; returns the result (Scene_RunDream). */
void DreamRunner_Run(DreamRunner *runner) {
    DreamSys *dreamSys;

    dreamSys = runner->dreamSys;
    dreamSys->vtbl->watch(dreamSys, runner->context->pad);
    dreamSys->vtbl->watch(dreamSys, runner->context->clock);
    dreamSys->vtbl->setCamera(dreamSys, runner->context->view);
    Task_GetVtbl()->run(runner, runner->context, 0);
}

void DreamRunner_Finish(DreamRunner *runner) {
    DreamSys *dreamSys;

    dreamSys = runner->dreamSys;
    Task_GetVtbl()->finish(runner);
    dreamSys->vtbl->setCamera(dreamSys, 0);
    dreamSys->vtbl->unwatch(dreamSys, runner->context->pad);
    dreamSys->vtbl->unwatch(dreamSys, runner->clock);
}

void DreamRunner_Start(DreamRunner *runner) {
    RunnerContextHead *head;
    RunnerView *view;
    RunnerViewSub *sub;

    head = runner->context->display;
    view = runner->view;
    view->vtbl->setScreenSize(view, head->vtbl->getScreenRect(head, 0));
    sub = view->vtbl->getOverlay(view);
    sub->vtbl->setVisible(sub, 1);
    view->vtbl->setPacketCount(view, 0x4B0);
    view->vtbl->setCamera(view, runner->dreamSys, g_runnerViewpoint, g_runnerRefPoint, 0);
    view->vtbl->allocOt(view);
    runner->phase = RUNNER_STARTING;
}

void DreamRunner_End(DreamRunner *runner) {
    RunnerView *view;

    view = runner->view;
    view->vtbl->freeOt(view);
    view->vtbl->detach(view);
}

/* On update (message 2): start the day, or rebuild the stage after a link. A special day (stage -1) ends at once with result 2. */
void DreamRunner_Update(DreamRunner *runner, s32 **sender, s32 message) {
    s32 stage;

    Task_GetVtbl()->update(runner, sender, message);
    if (message != 2) {
        return;
    }
    if (runner->phase == message) {
        return;
    }
    switch (runner->phase) {
    case RUNNER_IN_STAGE:
        return;
    case RUNNER_STARTING:
        stage = runner->dreamSys->vtbl->startDay(runner->dreamSys);
        if (stage < 0) {
            runner->dreamSys->vtbl->endDay(runner->dreamSys, 0);
            runner->result = message;
            runner->vtbl->setState(runner, 3);
            return;
        }
        break;
    case RUNNER_RELINK:
        runner->stage->vtbl->stop(runner->stage);
        runner->stage->vtbl->delete_(runner->stage);
        stage = runner->dreamSys->vtbl->getStage(runner->dreamSys);
        break;
    default:
        return;
    }
    DreamRunner_CreateStage(runner, stage);
}

void DreamRunner_CreateStage(DreamRunner *runner, s32 stage) {
    void *dreamStage;

    dreamStage = Place_New(runner->sound, runner->music, runner->etcTim, runner->dreamerModel, stage);
    runner->stage = dreamStage;
    runner->vtbl->watch(runner, dreamStage);
    runner->stage->vtbl->start(runner->stage, runner->context, runner->dreamSys);
    runner->phase = RUNNER_IN_STAGE;
}

void DreamRunner_OnTimeout(void) {
}

void DreamRunner_OnDreamSysMessage(void) {
}

/*
 * Messages of the dream stage: 4 the day ran out (normal end, result 2 when a cinematic is due),
 * 5 to 8 and 10 a link (rebuild on the next update), 12 an end, 13 the SELECT + TRIANGLE erase.
 */
void DreamRunner_OnStageMessage(DreamRunner *runner, s32 sender, s32 message) {
    RunnerPeer *peer;
    RunnerPeer *dreamSys;
    RunnerPeerVtbl *vt;
    RunnerCine cine;
    s32 reason;
    s32 result;

    switch (message) {
    case 4:
        peer = (RunnerPeer *)runner->stage;
        peer->vtbl->stop(peer);
        peer = (RunnerPeer *)runner->stage;
        peer->vtbl->delete_(peer);
        peer = (RunnerPeer *)runner->dreamSys;
        if (peer->vtbl->endDay(peer, 0) == 0) {
            dreamSys = (RunnerPeer *)runner->dreamSys;
            dreamSys->vtbl->getCinematic(&cine, dreamSys);
            result = 2;
            if (cine.variant < 0) {
                result = 1;
            }
            runner->result = result;
        } else {
            runner->result = 3;
        }
        runner->vtbl->setState(runner, 3);
        return;
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        runner->phase = RUNNER_RELINK;
        return;
    case 12:
    case 13:
        peer = (RunnerPeer *)runner->stage;
        peer->vtbl->stop(peer);
        peer = (RunnerPeer *)runner->stage;
        peer->vtbl->delete_(peer);
        peer = (RunnerPeer *)runner->dreamSys;
        vt = peer->vtbl;
        reason = 1;
        if (message != 12) {
            reason = 2;
        }
        vt->endDay(peer, reason);
        runner->result = 3;
        runner->vtbl->setState(runner, 3);
        return;
    default:
        return;
    }
}

static DreamRunnerVtbl *DreamRunner_GetVtbl(void) {
    return (DreamRunnerVtbl *)g_dreamRunnerVtbl;
}

void File_ResolvePathTablePart(s32 wholeTable) {
    s32 count;
    s32 files;

    files = (s32)File_GetPathTable(&count);
    switch (++g_pathTablePartCount) {
    case 1:
        if (wholeTable != 0) {
            g_pathTablePartCount++;
        } else {
            g_pathTableFirstHalf = count /= 2;
        }
        break;
    case 2:
        count -= g_pathTableFirstHalf;
        break;
    default:
        count = 0;
        break;
    }
    do {
    } while (File_AddDirEntries(files, count) == 0);
}

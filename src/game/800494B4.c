#include "common.h"
#include "game/stage.h"

/*
 * Stage tables, the dream runner, the Task base class and the stage map (types in game/stage.h).
 * Vtables: DreamRunner g_dreamRunnerVtbl, Task g_taskVtbl, StageMap g_stageMapVtbl, the 0xDC render object
 * D_800869D8, MapTile g_mapTileVtbl.
 */

extern StageGrid g_stageGrids[];  /* g_stageGrids, 14 entries (Stage_GetGrids) */
extern StageGrid D_800861D6[];  /* g_stageGrids + 2 */
extern s16 *g_stageChunkMoods[];       /* per stage: the s16 mood of each chunk, row-major */
extern u8 g_dreamRunnerVtbl[];
extern s32 D_80086650[];        /* {0, -1200, 0} and {0, -1200, 10000}: the points DreamRunner_Start gives the view */
extern s32 D_8008665C[];
extern u8 g_taskVtbl[];
extern u8 g_stageMapVtbl[];
extern Vec3 D_8008682C;         /* default map origin (0, 0, 0) */
extern Vec3 g_chunkNeighborOffsets[];       /* per neighbour: offset of its chunk corner from the centre chunk's centre */
extern s32 D_8008688C[];        /* per neighbour: 1 << neighbour */
extern HexNeighbor g_chunkNeighborSteps[];
extern s8 D_800868FC[];         /* per chunk id: which D_80086974 list to load around it */
extern NeighborUse D_80086904[];
extern NeighborUse *D_80086974[];
extern MapView D_80086990;      /* {slot -1, 0, 0, 20, 20}: a whole chunk */
extern MapTileStep D_8008699C, D_800869A8, D_800869B4, D_800869C0;
extern s32 D_800869CC;
extern u8 D_800869D8[];
extern char g_mapTileVtbl[];

/* The PSY-Q MATRIX of RotMatrix and ApplyMatrixLV. */
typedef struct GteMatrix {
    s16 m[3][3];
    s32 t[3];
} GteMatrix;
extern GteMatrix D_8008E98C;    /* in .bss; StageMap_ComputeFlatView copies it, RotMatrix fills the rotation */

/* The actor base class (SceneNode_GetVtbl, vtable 0x8006B5CC) and the map's base (RootNode_GetVtbl): slots chained to here. */
typedef struct ActorVtbl {
    u8 pad_00[0x08];
    void (*init)();             /* 0x08 */
    void (*destroy)();          /* 0x0C */
    u8 pad_10[0x38 - 0x10];
    void (*onNotify)();         /* 0x38 */
    u8 pad_3C[0x88 - 0x3C];
    void (*onSlotMessage)();    /* 0x88 */
    u8 pad_8C[0x9C - 0x8C];
    void (*unk9C)();            /* 0x9C */
} ActorVtbl;

/* What StageMap slot 0xB8 (RootNode_GetLight) returns. */
typedef struct MapChildVtbl {
    u8 pad_00[0x44];
    void (*unk44)();
    void (*unk48)();
} MapChildVtbl;

typedef struct MapChild {
    MapChildVtbl *vtbl;
} MapChild;

/* The record MapModels slot 0x78 fills for each model, 0x40 bytes. */
typedef struct MapModelRecord {
    u8 pad_00[0x0C];
    Vec3 pos;                   /* 0x0C position in the chunk */
    u8 pad_18[0x1A - 0x18];
    u16 rotY;                   /* 0x1A yaw, into the tile's rotate[1] */
    u8 pad_1C[0x2E - 0x1C];
    u16 flags;                  /* 0x2E into MapTile.flags */
    s32 extra;                  /* 0x30 placed from tile 400 on instead of on its square */
    s32 chained;                /* 0x34 the next model stacks on the same square */
    u8 pad_38[0x40 - 0x38];
} MapModelRecord;

/* The box +0x1DC points to (func_8004CD38): tiles x0..x1, y0..y1. */
typedef struct MapBox {
    s16 x0;
    s16 y0;
    s32 x1;
    s32 y1;
} MapBox;

/* The 0xDC object of class 0x800869D8 (func_8004D254); slot 0xA0 is Scene_DrawNode, which draws scene nodes. */
typedef struct RenderObjVtbl {
    u8 pad_00[0x08];
    void (*init)();             /* 0x08 */
    u8 pad_0C[0x40 - 0x0C];
    void (*unk40)();            /* 0x40 */
    u8 pad_44[0x9C - 0x44];
    void (*unk9C)();            /* 0x9C */
} RenderObjVtbl;

typedef struct RenderObj {
    RenderObjVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    s32 unk10;
    u8 pad_14[0x70 - 0x14];
    s32 unk70;
} RenderObj;

/* The class of src/game/8004D578.c (Menu_GetVtbl), 0xC4 bytes. */
typedef struct MenuNewVtbl {
    u8 pad_00[0x08];
    void (*init)(s32, s32);
} MenuNewVtbl;

/* The file argument of Tmd_Create (TMD loader). */
typedef struct TmdFileArg {
    s32 unk0;
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

s32 D_8008A980; /* view distance StageMap_Reset sets */

s32 D_8008A978; /* func_8004A070 call count */
s32 D_8008A97C;

s32 Heap_Alloc(s32 size);
void Heap_Free(void *);
TaskBaseVtbl *Screen_GetVtbl(void);
TaskVtbl *Task_GetVtbl(void);
DreamRunnerVtbl *DreamRunner_GetVtbl(void);
StageMapVtbl *StageMap_GetVtbl(void);
ActorVtbl *SceneNode_GetVtbl(void);
ActorVtbl *RootNode_GetVtbl(void);
RenderObjVtbl *View_GetVtbl(void);
RenderObjVtbl *func_8004D37C(void);
MapTileVtbl *MapTile_GetVtbl(void);
extern MenuNewVtbl *Menu_GetVtbl(void);
extern void *Place_New(void *sound, void *music, void *etcTim, void *dreamerModel, s32 stage);
void *Sound_CreateBank(s32 bankName);
void *File_GetPathTable(s32 *count);
s32 File_AddDirEntries(s32, s32);
s32 Music_GetEffectsBank(s32);
void Sym_LoadModels(void);
void Sym_FreeModels(void);
s32 Tim_New(s32 path);
s32 Tmd_Create(s32 file);
s32 Music_PickBank(s32);
void *Bgm_New(s32, s32, s32);
void File_EnableWait(s32, s32, s32);
void *Clock_Create(void);
extern void *Display_GetCurrent(void);
extern void *MapChunk_New(void);
extern void *func_8002C12C(s32);
void GsLinkObject4(s32 objp, void *packet, s32 id);
void RotMatrix(void *, void *);
void ApplyMatrixLV(s32 *, void *, void *);

void func_8004A070(s32);
s32 StageMap_New(s32 origin, s32);
s32 func_8004D254(void);
void DreamRunner_CreateStage(DreamRunner *runner, s32 stage);
s32 Stage_PlaceToWorld(Vec3 *pos, Vec3 *chunkCenter, StageGrid *grid, Vec3 *origin, StagePlace *place);
s32 StageMap_CountLoading(StageMap *map);
void MapTile_Tell(MapTile *tile, MapActor *sender, s32 message);
void func_8004AFE0();
void func_8004B030();
void StageMap_TellViewTiles(StageMap *map, MapActor *sender, s32 message);
s32 StageMap_GetNeighborMask(StageMap *map, s32 chunkIndex, s32 oddRow);
s32 StageMap_RequestNeighbor(StageMap *map, ChunkRequest *request, s32 cols, s32 oddRow, s32 chunkIndex, s32 mask, s32 neighbor);
void StageMap_ChunkColRow(StageMap *map, StagePlace *place, s32 chunkIndex);
void StageMap_ComputeFlatView(StageMap *map, s32 width, s32 depth);
void StageMap_SplitView();
s32 StageMap_SplitViewRows(StageMap *map, MapView *view, s32 index, s32 neighbor, s32 x, s32 y, s32 cols, s32 rows);
void StageMap_ComputeStackedView(StageMap *map);
s32 func_8004CD38(void *box, void *tile);
s32 StageMap_AddChunkView(StageMap *map, s32 unused, s32 index, s32 chunkIndex);
void StageMap_ShowView(StageMap *map, s32 show);
void func_8004D0D0();
void func_8004D108(s32 map, MapTile *tile);
void StageMap_ForEachTile(StageMap *map, void (*perTile)(), void (*perSlot)(void *, void *));
void StageMap_ForEachSlotTile(StageMap *map, void (*perTile)(), MapSlot *slot);
s32 MapTile_New(void);

/* The number of stages (STG00 to STG13). */
s32 Stage_GetCount(void) {
    return 0xE;
}

StageGrid *Stage_GetGrids(s32 *count) {
    if (count != NULL) {
        *count = 14;
    }
    return g_stageGrids;
}

StageGrid *Stage_GetGrid(s32 stage) {
    return &Stage_GetGrids(NULL)[stage];
}

/* First stage, scanning stages then rows, with a chunk whose mood equals *mood; writes its (col, row), -1 when none. */
u32 Stage_FindChunkByMood(StagePlace *place, s16 *mood) {
    u32 stage;
    s32 col;
    s32 row;
    s32 rows;
    s32 cols;
    s16 *chunkMood;

    for (stage = 0; stage < 0xE; stage++) {
        chunkMood = g_stageChunkMoods[stage];
        rows = D_800861D6[stage].cols; /* D_800861D6 is g_stageGrids + 2: this reads the rows */
        cols = g_stageGrids[stage].cols;
        for (row = 0; row < rows; row++) {
            for (col = 0; col < cols; col++) {
                if (*mood == *chunkMood) {
                    place->col = col;
                    place->row = row;
                    return stage;
                }
                chunkMood++;
            }
        }
    }
    return -1;
}

s16 *Stage_GetChunkMood(s32 stage, StagePlace *place) {
    return g_stageChunkMoods[stage] + place->row * g_stageGrids[stage].cols + place->col;
}

/* Called by Scene_RunDream for each dream with the scene's context and its DreamSys. */
s32 DreamRunner_New(s32 context, s32 dreamSys, s32 arg2) {
    s32 runner;

    runner = Heap_Alloc(0x50);
    if (runner != 0) {
        DreamRunner_GetVtbl()->init(runner, context, dreamSys, arg2);
        return runner;
    }
    return 0;
}

/* The world constructor: dreamer model, spawn flags, music bank, the map, and DreamSys watched. */
void DreamRunner_Init(DreamRunner *runner, RunnerContext *context, DreamSys *dreamSys, s32 arg3) {
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
    tim->vtbl->unk78(tim);
    res = runner->etcTim;
    res->vtbl->unk5C(res);
    modelFile.unk0 = 0;
    modelFile.path = (s32)"ETC\\DREAMER.TMD";
    runner->dreamerModel = (RunnerRes *)Tmd_Create((s32)&modelFile);
    runner->music = Bgm_New(Music_PickBank(0), 0, 1);
    func_8004A070(1);
    File_EnableWait(arg3 == 0, 1, 1);
    runner->context = context;
    context->unk10 = (Object *)func_8004D254();
    context->unk8 = Clock_Create();
    context->map = (StageMap *)StageMap_New(0, 1);
    runner->dreamSys = dreamSys;
    runner->vtbl->watch(runner, dreamSys);
    dreamSys->vtbl->unk10C(dreamSys, runner->sound);
    dreamSys->vtbl->unk114(dreamSys, runner->etcTim);
    runner->vtbl->clearPhase(runner);
}

void DreamRunner_Destroy(DreamRunner *runner) {
    RunnerContext *context;

    context = runner->context;
    runner->vtbl->unwatch(runner, runner->dreamSys);
    context->map = context->map->vtbl->delete_(context->map);
    context->unk8 = context->unk8->vtbl->delete_(context->unk8);
    context->unk10 = context->unk10->vtbl->delete_(context->unk10);
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
    dreamSys->vtbl->unk10(dreamSys, runner->context->unk4);
    dreamSys->vtbl->unk10(dreamSys, runner->context->unk8);
    dreamSys->vtbl->unk110(dreamSys, runner->context->unk10);
    Task_GetVtbl()->run(runner, runner->context, 0);
}

void func_80049AC0(DreamRunner *runner) {
    DreamSys *dreamSys;

    dreamSys = runner->dreamSys;
    Task_GetVtbl()->unk48(runner);
    dreamSys->vtbl->unk110(dreamSys, 0);
    dreamSys->vtbl->unk14(dreamSys, runner->context->unk4);
    dreamSys->vtbl->unk14(dreamSys, runner->unk10);
}

void DreamRunner_Start(DreamRunner *runner) {
    RunnerContextHead *head;
    RunnerView *view;
    RunnerViewSub *sub;

    head = runner->context->unk0;
    view = runner->view;
    view->vtbl->unk44(view, head->vtbl->unk7C(head, 0));
    sub = view->vtbl->unkAC(view);
    sub->vtbl->unk60(sub, 1);
    view->vtbl->unk4C(view, 0x4B0);
    view->vtbl->unk70(view, runner->dreamSys, D_80086650, D_8008665C, 0);
    view->vtbl->unk8C(view);
    runner->phase = RUNNER_STARTING;
}

void func_80049C50(DreamRunner *runner) {
    RunnerView *view;

    view = runner->view;
    view->vtbl->unk90(view);
    view->vtbl->unk74(view);
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

void func_80049EA4(void) {
}

void func_80049EAC(void) {
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

DreamRunnerVtbl *DreamRunner_GetVtbl(void) {
    return (DreamRunnerVtbl *)g_dreamRunnerVtbl;
}

void func_8004A070(s32 arg0) {
    s32 count;
    s32 files;

    files = (s32)File_GetPathTable(&count);
    switch (++D_8008A978) {
    case 1:
        if (arg0 != 0) {
            D_8008A978++;
        } else {
            D_8008A97C = count /= 2;
        }
        break;
    case 2:
        count -= D_8008A97C;
        break;
    default:
        count = 0;
        break;
    }
    do {
    } while (File_AddDirEntries(files, count) == 0);
}

s32 Task_New(s32 bankName, s32 sound) {
    s32 task;

    task = Heap_Alloc(0x38);
    if (task != 0) {
        Task_GetVtbl()->init(task, bankName, sound);
        return task;
    }
    return 0;
}

/* With a bank name the task makes and owns its sound bank, else it uses the one given. */
void Task_Init(Task *task, s32 bankName, void *sound) {
    Screen_GetVtbl()->init(task);
    task->vtbl = Task_GetVtbl();
    if (bankName != 0) {
        task->sound = Sound_CreateBank(bankName);
    } else {
        task->sound = sound;
    }
    task->bankName = bankName;
    task->vtbl->reset(task);
}

void Task_Destroy(Task *task) {
    if (task->bankName != 0) {
        SoundBank *sound = task->sound;
        sound->vtbl->delete_(sound);
    }
    Screen_GetVtbl()->destroy(task);
}

void Task_ClearTimeout(Task *task) {
    task->vtbl->setTimeout(task, -1);
}

s32 Task_Run(Task *task, s32 context, s32 arg2) {
    task->result = 0;
    Screen_GetVtbl()->run(task, context, arg2);
    return task->result;
}

void func_8004A324(s32 task) {
    Screen_GetVtbl()->unk48(task);
}

void func_8004A35C(void) {
}

void Task_OnTick(Task *task, s32 sender, s32 message) {
    Screen_GetVtbl()->onTick(task, sender, message);
    if (task->ticks > task->timeout) {
        task->vtbl->setState(task, TASK_STATE_TIMEOUT);
    }
}

void Task_SetState(Task *task, s32 state) {
    Screen_GetVtbl()->setState(task, state);
    if (state == TASK_STATE_TIMEOUT) {
        task->result = 1;
        task->vtbl->onTimeout(task);
    }
}

/* Timeout x 20 ticks; negative never times out. */
void Task_SetTimeout(Task *task, s32 timeout) {
    task->timeout = timeout;
    if (timeout >= 0) {
        task->timeout = timeout * 20;
    }
}

void Task_PlayTone(Task *task, s32 tone) {
    SoundBank *sound = task->sound;
    if (sound != NULL) {
        sound->vtbl->playTone(sound, tone, 0x7F, 0x7F);
    }
}

TaskVtbl *Task_GetVtbl(void) {
    return (TaskVtbl *)g_taskVtbl;
}

s32 StageMap_New(s32 origin, s32 arg1) {
    s32 map;

    map = Heap_Alloc(0x1E8);
    if (map != 0) {
        StageMap_GetVtbl()->init(map, origin, arg1);
        return map;
    }
    return 0;
}

/* Constructor: 7 slots, each with its chunk object, model set, origin node and 410 tiles laid 0x800 apart. */
void StageMap_Init(StageMap *map, Vec3 *origin, s32 arg2) {
    Vec3 pos;
    MapSlot *slot;
    MapChunk *chunk;
    MapTile *tile;
    MapTile **p;
    MapTile **end;
    s32 i;

    RootNode_GetVtbl()->init(map);
    map->vtbl = StageMap_GetVtbl();
    if (origin != NULL) {
        map->origin = *origin;
    } else {
        map->origin = D_8008682C;
    }
    map->swapping = 0;
    map->pendingSlots = 0;
    map->ready = 0;
    map->active = 0;
    map->target = NULL;
    map->messageFilter = NULL;
    map->unk1E0 = 0;
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        slot->chunk = MapChunk_New();
        slot->chunk->unk20 = (slot->chunk->data != 0);
        slot->chunk->id = i;
        chunk = slot->chunk;
        chunk->vtbl->unk88(chunk, arg2);
        slot->unk14 = 0;
        slot->unk18 = 0;
        slot->index = i;
        slot->loading = 0;
        slot->models = func_8002C12C(0);
        tile = (MapTile *)MapTile_New();
        slot->root = tile;
        tile->vtbl->unk4C(tile, map, &map->origin);
        slot->tiles = (MapTile **)Heap_Alloc(0x668);
        if (slot->tiles == NULL) {
            return;
        }
        pos.x = 0x400;
        pos.y = 0;
        pos.z = 0x400;
        end = (MapTile **)((u8 *)slot->tiles + 0x668);
        for (p = slot->tiles; p < end; p++) {
            tile = (MapTile *)MapTile_New();
            *p = tile;
            tile->vtbl->unk4C(tile, slot->root, &pos);
            pos.x += 0x800;
            if (pos.x > 0xA400) {
                pos.x = 0x400;
                pos.z += 0x800;
            }
            tile = *p;
            tile->vtbl->unk70(tile, 1);
            tile = *p;
            tile->attribute = (s32)(tile->attribute | MAP_TILE_HIDDEN);
        }
    }
    map->vtbl->watch(map, Display_GetCurrent());
    map->vtbl->reset(map);
}

void StageMap_Destroy(StageMap *map) {
    MapSlot *slot;
    MapTile *tile;
    MapTile **p;
    MapTile **end;
    s32 i;

    map->vtbl->unwatch(map, Display_GetCurrent());
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        map->vtbl->onSlotMessage(map, 6, slot, i);
        if (slot->chunk != NULL) {
            slot->chunk->vtbl->delete_(slot->chunk);
        }
        if (slot->models != NULL) {
            if (slot->models->tmd != NULL) {
                slot->models->tmd->vtbl->delete_(slot->models->tmd);
            }
            slot->models = slot->models->vtbl->delete_(slot->models);
        }
        if (slot->root != NULL) {
            slot->root->vtbl->delete_(slot->root);
        }
        end = slot->tiles + MAP_SLOT_TILES;
        for (p = slot->tiles; p < end; p++) {
            tile = *p;
            if (tile != NULL) {
                tile->vtbl->delete_(tile);
            }
        }
        Heap_Free(slot->tiles);
    }
    RootNode_GetVtbl()->destroy(map);
}

void StageMap_OnNotify(StageMap *map, s32 **sender, s32 message) {
    SceneNode_GetVtbl()->onNotify(map, sender, message);
    if ((**sender & 0xF) == 1) {
        map->vtbl->unk100(map, sender, message);
    }
}

void StageMap_Reset(StageMap *map) {
    map->grid = NULL;
    map->messageFilter = NULL;
    map->viewCount = 0;
    map->vtbl->setViewDistance(map, D_8008A980);
    map->unk1CC[0] = -1;
    map->unk1CC[1] = -1;
    map->unk1CC[2] = -1;
    map->unk1CC[3] = -1;
}

/* Message 6 (slot emptied) deletes the slot's +0x14 object; 6 and 7 make it the current slot and notify the watchers. */
void StageMap_OnSlotMessage(StageMap *map, s32 message, MapSlot *slot) {
    Object *obj;

    SceneNode_GetVtbl()->onSlotMessage(map, message);
    switch (message) {
    case 6:
        obj = slot->unk14;
        if (obj != NULL) {
            slot->unk14 = obj->vtbl->delete_(obj);
        }
        /* fallthrough */
    case 7:
        map->currentSlot = slot;
        map->vtbl->notify(map, message);
        return;
    }
}

void StageMap_Tick(StageMap *map) {
    if (map->active != 0) {
        map->vtbl->follow(map);
        map->vtbl->unk13C(map);
    }
}

/* Message 0x34 goes to slot 0xD0 with the same arguments still in a1 and a2. */
void func_8004AB88(StageMap *map, u8 **message) {
    if (**message == 0x34) {
        map->vtbl->filterMessage(map);
    }
}

void StageMap_ClearSlots(StageMap *map) {
    MapSlot *slot;
    MapModels *models;
    s32 i;

    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        slot->chunk->vtbl->unload(slot->chunk);
        slot->loading = 0;
        map->vtbl->hideSlot(map, slot);
        models = slot->models;
        if (models->tmd != NULL) {
            models->tmd = models->tmd->vtbl->delete_(models->tmd);
        }
        map->vtbl->onSlotMessage(map, 6, slot, i);
        slot->chunk->vtbl->unk84(slot->chunk);
    }
    map->ready = 0;
    map->pendingSlots = 0;
    map->vtbl->unk140(map);
}

void func_8004ACF8(StageMap *map, s32 count, s32 arg2, s32 arg3) {
    s32 i;
    MapChild *child;

    for (i = 0; i < count; i++) {
        child = map->vtbl->unkB8(map, i);
        child->vtbl->unk44(child, 1, arg3);
        arg3 += 3;
        child->vtbl->unk48(child, 1, arg2);
        arg2 += 6;
    }
}

void StageMap_SetChunkLoader(StageMap *map, void *loader, void *context) {
    map->loadChunk = loader;
    map->loadContext = context;
}

void StageMap_SetMessageFilter(StageMap *map, s32 *filter) {
    map->messageFilter = filter;
}

/* Passes messages 2, 3 and 5 to 8 whose sender's class id is in the filter list to slot 0x12C. */
void StageMap_FilterMessage(StageMap *map, s32 **sender, s32 message) {
    s32 *code;
    s32 unused[6];

    switch (message) {
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
        code = map->messageFilter;
        if ((code != NULL) && (*code != 0)) {
            do {
                if (*code == **sender) {
                    map->vtbl->tellView(map, sender, message);
                }
                code++;
            } while (*code != 0);
        }
        break;
    }
}

/* Tells the tiles around the sender (3 x 3 tiles, or its whole floor on a stacked stage), keeping the view. */
s32 StageMap_TellNearTiles(StageMap *map, MapActor *sender, s32 message) {
    MapViewSave saved[3];
    MapViewSave location[3]; /* a MapLocation, in a 48-byte buffer */
    MapViewSave *src;
    MapViewSave *dst;
    s32 savedCount;
    s32 ret;
    Vec3 *pos;

    if (sender->attached != 0) {
        pos = &sender->coord->workT;
    } else {
        pos = NULL;
    }
    ret = map->vtbl->locate(map, location, pos);
    if (ret != 0) {
        return ret;
    }
    savedCount = map->viewCount;
    dst = saved;
    src = map->v.save;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != &map->v.save[3]);
    if (map->grid->stacked == 0) {
        func_8004AFE0(map, location, 3);
    } else {
        func_8004B030(map, location, 3);
    }
    StageMap_TellViewTiles(map, sender, message);
    map->viewCount = savedCount;
    dst = map->v.save;
    src = saved;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != &saved[3]);
}

/* A size x size view starting one tile before the location's tile; StageMap_SplitView (map still in a0) splits it. */
void func_8004AFE0(StageMap *map, MapLocation *location, s32 size) {
    map->viewX = location->at.place.tileX - 1;
    map->viewY = location->at.place.tileY - 1;
    map->viewCols = size;
    map->viewRows = size;
    StageMap_SplitView();
}

/* The same on a stacked stage: one rectangle, clipped at the chunk edges (tiles 0 and 19). */
void func_8004B030(StageMap *map, MapLocation *location, s32 size) {
    s32 firstX = location->at.place.tileX;
    s32 firstY = location->at.place.tileY;
    s32 rows = size;
    s32 cols = rows;
    s32 x = firstX;
    s32 y = firstY;

    if (x == 0) {
        cols--;
    } else {
        firstX--;
    }
    if (x == 0x13) {
        cols--;
    }
    if (y == 0) {
        rows--;
    } else {
        firstY--;
    }
    if (y == 0x13) {
        rows--;
    }
    map->viewCount = 1;
    map->v.views[0].slot = map->vtbl->slotIndexByChunk(map, location->chunkIndex);
    map->v.views[0].tileX = firstX;
    map->v.views[0].tileY = firstY;
    map->v.views[0].cols = cols;
    map->v.views[0].rows = rows;
}

void StageMap_TellViewTiles(StageMap *map, MapActor *sender, s32 message) {
    MapView *view;
    MapSlot *slot;
    MapTile **row;
    MapTile *tile;
    s32 i;
    s32 j;
    s32 k;

    view = map->v.views;
    for (i = 0; i < map->viewCount; i++) {
        slot = &map->slots[view->slot];
        if (slot->chunk->loaded != 0) {
            row = slot->tiles + view->tileX + view->tileY * 20;
            for (j = 0; j < view->rows; j++) {
                for (k = 0; k < view->cols; k++) {
                    map->tellKey = map->location.at.chunkKeyU;
                    map->tellX = view->tileX + k;
                    map->tellY = view->tileY + j;
                    MapTile_Tell(*row, sender, message);
                    tile = (*row)->next;
                    while (tile != NULL) {
                        MapTile_Tell(tile, sender, message);
                        tile = tile->next;
                    }
                    row++;
                }
                row += 20 - view->cols;
            }
        }
        view++;
    }
}

void MapTile_Tell(MapTile *tile, MapActor *sender, s32 message) {
    if ((tile != NULL) && (tile->flags & 0x80)) {
        tile->vtbl->unk38(tile);
    }
}

/* &map->tellKey */
s32 func_8004B31C(s32 map) {
    return map + 0x1C0;
}

void func_8004B324(void) {
}

void StageMap_SetViewDistance(StageMap *map, s32 distance) {
    map->viewDistance = distance;
    map->viewTiles = distance >> 11;
    map->viewHalf = distance >> 12;
}

void StageMap_SetGrid(StageMap *map, StageGrid *grid) {
    map->vtbl->reset(map);
    map->grid = grid;
}

/* Puts the target at a place: its world position into pos, then loads the chunk there and its 6 neighbours. */
void StageMap_SetTarget(StageMap *map, Vec3 *pos, MapActor *target, StagePlace *place) {
    Vec3 chunkCenter;

    map->target = target;
    map->location.at.place = *place;
    map->vtbl->loadAround(map, Stage_PlaceToWorld(pos, &chunkCenter, map->grid, &map->origin, place), &chunkCenter, D_80086904);
}

void StageMap_PlaceToWorld(StageMap *map, Vec3 *pos, StagePlace *place) {
    Vec3 chunkCenter;
    Stage_PlaceToWorld(pos, &chunkCenter, map->grid, &map->origin, place);
}

/*
 * World position of a place: chunk (col, row) from the grid origin, 0xA000 per chunk with odd rows
 * half a chunk to the left, then the tile (0x800) and the offset from the tile centre. Writes the
 * chunk centre and returns the chunk index (0 on a stacked stage).
 */
s32 Stage_PlaceToWorld(Vec3 *pos, Vec3 *chunkCenter, StageGrid *grid, Vec3 *origin, StagePlace *place) {
    s32 row;
    s32 rows;
    s32 index;
    s32 x;
    s32 z;
    s32 tileX;
    s32 tileZ;
    s32 offsetX;
    s32 offsetZ;

    if (grid->stacked == 0) {
        row = place->row;
        rows = grid->rows;
        index = place->col + grid->cols * row;
    } else {
        rows = 1;
        row = 0;
        index = 0;
    }
    x = (origin->x - grid->cols * 0x5000) + place->col * 0xA000;
    z = origin->z - rows * 0x5000;
    chunkCenter->x = x;
    if (row & 1) {
        chunkCenter->x = x - 0x5000;
    }
    chunkCenter->y = origin->y;
    chunkCenter->z = z + row * 0xA000;
    tileX = (place->tileX << 11) + chunkCenter->x;
    offsetX = place->x + 0x400;
    pos->x = tileX + offsetX;
    pos->y = place->y + chunkCenter->y;
    tileZ = (place->tileY << 11) + chunkCenter->z;
    offsetZ = place->z + 0x400;
    pos->z = tileZ + offsetZ;
    chunkCenter->x += 0x5000;
    chunkCenter->z += 0x5000;
    return index;
}

void StageMap_Activate(StageMap *map) {
    map->active = 1;
}

void StageMap_Deactivate(StageMap *map) {
    map->vtbl->clearSlots(map);
    map->active = 0;
}

/*
 * Each tick while active: locate the target; on a flat stage reload the neighbours of its chunk,
 * redraw the view, keep the location and notify 5 when the chunk changed.
 */
s32 StageMap_Follow(StageMap *map) {
    MapLocation location;
    s16 prevKey;
    s32 layout;

    if (map->vtbl->getLocation(map, &location, 0) == 0) {
        return 0;
    }
    layout = D_800868FC[location.slot->chunk->id];
    if (map->grid->stacked == 0) {
        map->vtbl->loadAround(map, location.chunkIndex, &location.chunkCenter, D_80086974[layout]);
    }
    map->vtbl->updateView(map);
    prevKey = map->location.at.chunkKey;
    map->location = location;
    if (prevKey != location.at.chunkKey) {
        map->vtbl->notify(map, 5);
    }
    return layout;
}

/* Places the 7 slots around a chunk (or the floors of a stacked stage) and asks the loader for their data. */
void StageMap_LoadAround(StageMap *map, s32 chunkIndex, Vec3 *center, NeighborUse *use) {
    ChunkRequest requests[7];
    s32 mask;
    s32 cols;
    s32 oddRow;
    s32 i;
    s32 count;
    MapSlot *slot;
    Coord2 *coord;
    Vec3 *offset;

    if (use != NULL) {
        cols = map->grid->cols;
        count = 0;
        oddRow = (chunkIndex / cols) & 1;
        mask = StageMap_GetNeighborMask(map, chunkIndex, oddRow);
        for (i = 0; i < 7; i++, use++) {
            slot = map->vtbl->slotById(map, i);
            slot->index = use->neighbor;
            if (use->enabled != 0) {
                offset = &g_chunkNeighborOffsets[use->neighbor];
                coord = slot->root->coord;
                if (map->grid->stacked == 0) {
                    coord->t.x = center->x + offset->x;
                    coord->t.y = center->y;
                    coord->t.z = center->z + offset->z;
                } else {
                    coord->t.x = center->x - 0x5000;
                    coord->t.y = center->y + offset->y;
                    coord->t.z = center->z - 0x5000;
                }
                slot->root->coord->flg = 0;
                StageMap_RequestNeighbor(map, &requests[count], cols, oddRow, chunkIndex, mask, use->neighbor);
                count++;
            }
        }
        for (i = 0; i < 7; i++) {
            slot = &map->slots[i];
            slot->chunk->id = slot->index;
        }
        map->vtbl->assignChunks(map, requests, count);
    }
}

/* Bit i set when neighbour i of the chunk lies inside the grid; a stacked stage sets one bit per floor. */
s32 StageMap_GetNeighborMask(StageMap *map, s32 chunkIndex, s32 oddRow) {
    StageGrid *grid;
    s32 cols;
    s32 rows;
    s32 outside;
    s32 i;

    grid = map->grid;
    cols = grid->cols;
    rows = grid->rows;
    if (grid->stacked == 0) {
        outside = -(chunkIndex < cols) & 3;
        if (chunkIndex >= cols * (rows - 1)) {
            outside |= 0x60;
        }
        if (chunkIndex % cols == 0) {
            if (oddRow != 0) {
                outside |= 0x25;
            } else {
                outside |= 4;
            }
        }
        if ((chunkIndex + 1) % cols == 0) {
            if (oddRow != 0) {
                outside |= 0x10;
            } else {
                outside |= 0x52;
            }
        }
    } else {
        outside = -1;
        for (i = 0; i < rows; i++) {
            outside *= 2;
        }
    }
    return ~outside;
}

s32 StageMap_RequestNeighbor(StageMap *map, ChunkRequest *request, s32 cols, s32 oddRow, s32 chunkIndex, s32 mask, s32 neighbor) {
    HexNeighbor *step;
    s32 delta;

    if (mask & D_8008688C[neighbor]) {
        if (map->grid->stacked != 0) {
            request->chunkIndex = chunkIndex + neighbor;
        } else {
            step = &g_chunkNeighborSteps[neighbor];
            if (step->rowStep == 0) {
                delta = step->colStepOdd;
                request->chunkIndex = chunkIndex + delta;
            } else {
                delta = cols * step->rowStep;
                if (oddRow != 0) {
                    delta += step->colStepOdd;
                } else {
                    delta += step->colStepEven;
                }
                request->chunkIndex = chunkIndex + delta;
            }
        }
        request->data = map->loadChunk(map->loadContext, request->chunkIndex, 0, 0);
        request->neighbor = neighbor;
        return 1;
    }
    request->data = 0;
    request->neighbor = neighbor;
    return 0;
}

void StageMap_AssignChunks(StageMap *map, ChunkRequest *request, s32 count) {
    s32 i;
    MapSlot *slot;

    for (i = 0; i < count; request++, i++) {
        slot = map->vtbl->slotById(map, request->neighbor);
        map->vtbl->onSlotMessage(map, 6, slot, i);
        if (request->data != 0) {
            if (slot->chunk->loaded != 0) {
                map->vtbl->hideSlot(map, slot);
            }
            slot->chunk->index = request->chunkIndex;
            slot->chunk->vtbl->load(slot->chunk, request->data);
            slot->loading = 1;
            map->swapping = 1;
        } else {
            if (slot->chunk->loaded != 0) {
                map->vtbl->hideSlot(map, slot);
            }
            if (slot->chunk->unk2A != 0) {
                slot->chunk->vtbl->unload(slot->chunk);
                slot->loading = 0;
            }
        }
    }
    map->pendingSlots = StageMap_CountLoading(map);
}

s32 StageMap_CountLoading(StageMap *map) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (map->slots[i].loading != 0) {
            count++;
        }
    }
    return count;
}

/* On update (message 2): a slot whose chunk data arrived gets its tiles; when none is left the map is ready. */
void StageMap_PollLoads(StageMap *map, s32 sender, s32 message) {
    MapSlot *slot;
    MapChunk *chunk;
    s32 i;
    s32 swapping;
    u16 pending;

    if (message == 2) {
        for (i = 0; i < 7; i++) {
            slot = &map->slots[i];
            chunk = slot->chunk;
            if (chunk->unk2E != 0) {
                chunk->unk2E = 0;
                map->vtbl->onSlotMessage(map, 7, slot, i);
            }
            swapping = map->swapping;
            if (swapping == 1 && slot->loading != 0) {
                chunk = slot->chunk;
                if (chunk->loaded != 0) {
                    map->vtbl->buildTiles(map, slot);
                    slot->chunk->loaded = 2;
                    slot->loading = 0;
                    pending = map->pendingSlots - 1;
                    map->pendingSlots = pending;
                    if (pending == 0) {
                        map->pendingSlots = 0;
                        map->swapping = 0;
                        map->ready = swapping;
                    }
                } else if (chunk->unk2A == 0) {
                    slot->loading = 0;
                }
            }
        }
    }
}

/*
 * Builds a slot's tiles from its chunk data: the TMD after the model list, then one model per
 * square from the model set, linked into the square's GsDOBJ2 (GsLinkObject4); extra models go
 * from index 400 on and chain behind the square's tile.
 */
void StageMap_BuildTiles(StageMap *map, MapSlot *slot) {
    MapModelRecord record;
    void *tmdFile[4];
    MapChunk *chunk;
    MapChunkData *data;
    MapModels *models;
    MapTile **tile;
    Coord2Param *param;
    void *model;
    s32 i;
    s32 j;
    s32 modelsSize;
    MapTile **tiles;

    chunk = slot->chunk;
    models = slot->models;
    models->data = (u8 *)chunk->data + chunk->data->modelsOffset;
    models->unk14 = 0;
    if (models->tmd != NULL) {
        models->tmd->vtbl->delete_(models->tmd);
    }
    data = chunk->data;
    modelsSize = data->modelsSize;
    tmdFile[0] = (u8 *)data + data->modelsOffset + modelsSize;
    models->tmd = (Object *)Tmd_Create((s32)tmdFile);
    record.chained = 0;
    i = 0;
    j = 400;
    for (;;) {
        model = models->vtbl->nextModel(models, &record, i);
        if (model == NULL) {
            break;
        }
        if (model == (void *)-1) {
            tile = &slot->tiles[i];
            (*tile)->attribute |= MAP_TILE_HIDDEN;
            (*tile)->model = NULL;
            (*tile)->tmd = 0;
        } else {
            tiles = slot->tiles;
            if (record.extra != 0) {
                tile = &tiles[j++];
            } else {
                tile = &tiles[i];
            }
            (*tile)->model = model;
            (*tile)->tmd = (*tile)->model->tmd;
            GsLinkObject4((*tile)->model->tmd, &(*tile)->attribute, 0);
            (*tile)->coord->t = record.pos;
            param = (*tile)->coord->param;
            param->rotate[0] = 0;
            param->rotate[1] = record.rotY;
            param->rotate[2] = 0;
            (*tile)->flags = record.flags;
            (*tile)->coord->flg = 0;
            (*tile)->attribute |= MAP_TILE_HIDDEN;
        }
        if (record.chained != 0) {
            (*tile)->next = slot->tiles[j];
        } else {
            i++;
            (*tile)->next = NULL;
        }
    }
}

void StageMap_HideSlot(StageMap *map, MapSlot *slot) {
    MapTile **p;
    MapTile **end;

    if (slot->chunk->index >= 0) {
        slot->chunk->vtbl->unk7C(slot->chunk);
        end = slot->tiles + MAP_SLOT_TILES;
        for (p = slot->tiles; p < end; p++) {
            (*p)->attribute = (*p)->attribute | MAP_TILE_HIDDEN;
            (*p)->model = 0;
            (*p)->tmd = 0;
        }
    }
}

/* The kept location; with out, first locates the target into out and returns NULL when that fails. */
void *StageMap_GetLocation(StageMap *map, MapLocation *out, s32 **outPos) {
    s32 *pos = &map->target->coord->t.x;

    if (outPos != NULL) {
        *outPos = pos;
    }
    if (out == NULL || map->vtbl->locate(map, out, pos) == 0) {
        return &map->location;
    }
    return NULL;
}

/* Where a world position falls: slot, chunk, tile and offsets. Returns 1 when no slot holds it. */
s32 StageMap_Locate(StageMap *map, MapLocation *out, s32 *pos) {
    MapSlot *slot;
    MapSlot *idSlot;
    Coord2 *coord;
    Coord2 *slotCoord;
    s16 chunkIndex;
    s32 x;
    s32 z;
    slot = map->vtbl->slotAt(map, pos);
    if (slot != NULL) {
        chunkIndex = slot->chunk->index;
        out->chunkIndex = chunkIndex;
        StageMap_ChunkColRow(map, &out->at.place, chunkIndex);
        idSlot = map->vtbl->slotById(map, slot->chunk->id);
        coord = idSlot->root->coord;
        out->chunkCenter.x = coord->t.x + 0x5000;
        out->chunkCenter.y = coord->t.y;
        out->chunkCenter.z = coord->t.z + 0x5000;
        slotCoord = slot->root->coord;
        out->offset.x = pos[0] - out->chunkCenter.x;
        out->offset.y = pos[1];
        out->offset.z = pos[2] - out->chunkCenter.z;
        out->at.place.tileX = (pos[0] - slotCoord->t.x) / 2048;
        out->at.place.tileY = (pos[2] - slotCoord->t.z) / 2048;
        x = (u16)pos[0] - 0x400;
        out->at.place.x = x - ((u16)slotCoord->t.x + out->at.place.tileX * 2048);
        out->at.place.y = (u16)pos[1];
        z = (u16)pos[2] - 0x400;
        out->at.place.z = z - ((u16)slotCoord->t.z + out->at.place.tileY * 2048);
        out->slot = slot;
        return 0;
    }
    return 1;
}

void StageMap_ChunkColRow(StageMap *map, StagePlace *place, s32 chunkIndex) {
    place->col = chunkIndex % map->grid->cols;
    place->row = chunkIndex / map->grid->cols;
}

MapSlot *StageMap_GetCurrentSlot(StageMap *map, StagePlace *place) {
    StageMap_ChunkColRow(map, place, map->currentSlot->chunk->index);
    return map->currentSlot;
}

MapSlot *StageMap_SlotById(StageMap *map, s32 id) {
    s32 i;
    MapSlot *slot;
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        if (slot->chunk->id == id) {
            return slot;
        }
    }
}

/* The slot whose chunk square holds the position; on a stacked stage slot i is the floor from -0x800 * i up. */
MapSlot *StageMap_SlotAt(StageMap *map, s32 *pos) {
    s32 i;

    for (i = 0; i < 7; i++) {
        MapSlot *slot = map->vtbl->slotById(map, i);
        Coord2 *coord = slot->root->coord;
        if (pos[0] >= coord->t.x && pos[0] < coord->t.x + 0xA000 && pos[2] >= coord->t.z && pos[2] < coord->t.z + 0xA000) {
            if (map->grid->stacked == 0) {
                return slot;
            }
            if (i * -0x800 < pos[1]) {
                continue;
            }
            if (i * -0x800 - 0x800 < pos[1]) {
                return slot;
            }
        }
    }
    return NULL;
}

s32 StageMap_SlotIndexById(StageMap *map, s32 id) {
    s32 found = 0;
    s32 i;
    MapSlot *slot;
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        if (slot->chunk->id == id) {
            found = i;
            break;
        }
    }
    return found;
}

s32 StageMap_SlotIndexByChunk(StageMap *map, s32 chunkIndex) {
    s32 i;
    MapSlot *slot;

    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        if (slot->chunk->index == chunkIndex && slot->chunk->loaded != 0) {
            return i;
        }
    }
    return -1;
}

/* Hides the old view's tiles, computes the new view and shows its tiles, once the chunks are loaded. */
void StageMap_UpdateView(StageMap *map) {
    s32 width;

    if (map->ready != 0) {
        width = map->viewHalf * 2;
        StageMap_ShowView(map, 0);
        if (map->grid->stacked == 0) {
            StageMap_ComputeFlatView(map, width, map->viewTiles);
        } else {
            StageMap_ComputeStackedView(map);
        }
        StageMap_ShowView(map, 1);
    }
}

/*
 * The view of a flat stage: a rectangle of width x depth tiles in front of the target, oriented by
 * its yaw (param rotate[1]) to the nearest axis, shifted toward the point viewDistance ahead.
 */
void StageMap_ComputeFlatView(StageMap *map, s32 width, s32 depth) {
    s8 location[0x30];
    GteMatrix mat;
    Coord2Param *param;
    s16 *rot;
    u16 angle;
    s32 x;
    s32 y;
    s32 d;
    s32 alongX;

    param = map->target->coord->param;
    rot = param->rotate;
    map->vtbl->getLocation(map, location, 0);
    x = location[2];
    y = location[3];
    angle = param->rotate[1];
    if (param->rotate[1] < 0) {
        angle += 0x1000;
    }
    mat = D_8008E98C;
    mat.t[0] = 0;
    mat.t[1] = 0;
    mat.t[2] = map->viewDistance;
    RotMatrix(rot, &mat);
    ApplyMatrixLV((s32 *)&mat, mat.t, mat.t);

    if ((angle >= 0x200 && angle < 0x600) || (angle >= 0xA00 && angle < 0xE00)) {
        d = mat.t[2];
        map->viewCols = depth;
        map->viewRows = width;
        map->viewX = (mat.t[0] > 0) ? x : x - width + 1;
        map->viewY = (mat.t[2] > 0) ? y - (u16)map->viewHalf - 1 : y - (u16)map->viewHalf + 1;
        alongX = 0;
    } else if ((angle >= 0x600 && angle < 0xA00) || (angle < 0x200 || angle >= 0xE00)) {
        d = mat.t[0];
        map->viewCols = width;
        map->viewRows = depth;
        map->viewX = (mat.t[0] > 0) ? x - (u16)map->viewHalf - 1 : x - (u16)map->viewHalf + 1;
        map->viewY = (mat.t[2] > 0) ? y : y - depth + 1;
        alongX = 1;
    }
    d = d >> 11;
    if (d >= map->viewHalf) {
        d = map->viewHalf - 1;
    }
    if (-map->viewHalf >= d) {
        d = -map->viewHalf + 1;
    }
    if (alongX != 0) {
        map->viewX += d;
    } else {
        map->viewY += d;
    }
    StageMap_SplitView(map);
}

/*
 * Splits the view rectangle over the chunks it covers: a negative first tile starts in a neighbour
 * (10 tiles across on the half-shifted rows), a rectangle past tile 20 continues in the next one.
 * x is reused for the rectangle count.
 */
void StageMap_SplitView(StageMap *map) {
    s32 endX;
    s32 x;
    s32 neighbor;
    s32 y;
    s32 cols;
    s32 rows;
    s32 wrapped;
    s32 slot;
    s32 over;
    MapView *view;

    wrapped = 0;
    x = map->viewX;
    cols = map->viewCols;
    rows = map->viewRows;
    neighbor = 3;
    if (x < 0) {
        x += 20;
        wrapped = 1;
        neighbor = 2;
    }
    y = map->viewY;
    view = map->v.views;
    if (y < 0) {
        y += 20;
        if (wrapped != 0) {
            x -= 10;
            neighbor = 0;
        } else {
            neighbor = 0;
            if (x < 10) {
                x += 10;
            } else {
                x -= 10;
                neighbor = 1;
            }
            view = map->v.views;
        }
    }

    slot = map->vtbl->slotIndexById(map, neighbor);
    map->v.views[0].slot = slot;
    map->v.views[0].tileX = x < 0 ? 0 : x;
    map->v.views[0].tileY = y;
    endX = x + cols;
    if (endX >= 21) {
        over = endX - 20;
        map->v.views[0].cols = cols - over;
        endX = over;
        x = StageMap_SplitViewRows(map, view, 0, neighbor, x, y, cols, rows) + 1;
        view = &map->v.views[x];
        view->slot = map->vtbl->slotIndexById(map, neighbor + 1);
        view->tileX = 0;
        view->tileY = (u16)map->v.views[0].tileY;
        view->cols = endX;
        view->rows = (u16)map->v.views[0].rows;
    } else {
        map->v.views[0].cols = cols;
        x = StageMap_SplitViewRows(map, view, 0, neighbor, x, y, cols, rows);
    }
    x += 1;
    map->viewCount = x;
}

/* Splits rectangle index of the view at the bottom edge of its chunk; returns the last index written. */
s32 StageMap_SplitViewRows(StageMap *map, MapView *view, s32 index, s32 neighbor, s32 x, s32 y, s32 cols, s32 rows) {
    s32 over;
    s32 id;
    s32 endX;

    if (y + rows > 20) {
        over = y + rows - 20;
        view->rows = rows - over;
        index++;
        view = &map->v.views[index];
        if (x < 10) {
            id = neighbor + 2;
            view->slot = map->vtbl->slotIndexById(map, id);
            view->tileX = x + 10;
            view->rows = over;
        } else {
            id = neighbor + 3;
            view->slot = map->vtbl->slotIndexById(map, id);
            view->tileX = x - 10;
            view->rows = over;
        }
        endX = view->tileX + cols;
        view->tileY = 0;
        if (endX > 20) {
            view->cols = cols - (endX - 20);
            index++;
            view = &map->v.views[index];
            view->slot = map->vtbl->slotIndexById(map, id + 1);
            view->tileX = 0;
            view->tileY = 0;
            view->cols = endX - 20;
            view->rows = over;
        } else {
            view->cols = cols;
        }
    } else {
        view->rows = rows;
    }
    return index;
}

/* The view of a stacked stage: the target's whole floor, the one above when inside the bounds box, and the one below. */
void StageMap_ComputeStackedView(StageMap *map) {
    MapLocation location;
    s32 unset;

    map->vtbl->getLocation(map, &location, 0);
    map->viewCount = 0;
    map->viewCount = StageMap_AddChunkView(map, unset, 0, location.chunkIndex);
    if (func_8004CD38(map->bounds, &location.at.place.tileX) != 0) {
        if (location.chunkIndex + 1 < map->grid->rows) {
            map->viewCount = StageMap_AddChunkView(map, unset, map->viewCount, location.chunkIndex + 1);
        }
    }
    if (location.chunkIndex - 1 >= 0) {
        map->viewCount = StageMap_AddChunkView(map, unset, map->viewCount, location.chunkIndex - 1);
    }
}

/* Returns 0 when the tile (tile[0], tile[1]) lies inside the box, 1 otherwise or without a box. */
s32 func_8004CD38(void *box, void *tile) {
    MapBox *b = box;
    u8 *pt = tile;

    if (b != NULL && (s8)pt[0] >= b->x0 && (s8)pt[0] <= b->x1
        && (s8)pt[1] >= b->y0 && (s8)pt[1] <= b->y1) {
        return 0;
    }
    return 1;
}

/* Adds a whole-chunk rectangle (D_80086990: 20 x 20 tiles) for a chunk index; returns the next index. */
s32 StageMap_AddChunkView(StageMap *map, s32 unused, s32 index, s32 chunkIndex) {
    MapView *view = &map->v.views[index];

    *view = D_80086990;
    view->slot = map->vtbl->slotIndexByChunk(map, chunkIndex);
    return index + 1;
}

/* Shows (show != 0) or hides the tiles of the view rectangles; rows[-3] is tileX, rows[-2] tileY, rows[-1] cols. */
void StageMap_ShowView(StageMap *map, s32 show) {
    MapView *view;
    s16 *rows;
    MapSlot *slot;
    s32 i;
    s32 row;
    s32 col;
    MapTile **p;
    MapTile *tile;
    MapTile *next;
    s32 attribute;

    view = (MapView *)((u8 *)map + 0x8C);
    for (i = 0; i < map->viewCount; i++) {
        slot = &map->slots[view->slot];
        rows = &view->rows;
        if (slot->chunk->loaded != 0) {
            p = slot->tiles + rows[-3] + rows[-2] * 20;
            for (row = 0; row < rows[0]; row++) {
                for (col = 0; col < rows[-1]; col++) {
                    if (show != 0) {
                        tile = *p;
                        attribute = tile->attribute & 0x7FFFFFFF;
                    } else {
                        tile = *p;
                        attribute = tile->attribute | MAP_TILE_HIDDEN;
                    }
                    tile->attribute = attribute;
                    next = (*p)->next;
                    while (next != NULL) {
                        if (show != 0) {
                            attribute = next->attribute & 0x7FFFFFFF;
                        } else {
                            attribute = next->attribute | MAP_TILE_HIDDEN;
                        }
                        next->attribute = attribute;
                        next = next->next;
                    }
                    p++;
                }
                p += 20 - rows[-1];
            }
        }
        view++;
    }
}

/* &map->unk1CC */
s32 func_8004CFA8(s32 map) {
    return map + 0x1CC;
}

void func_8004CFB0(StageMap *map, void *bounds) {
    map->bounds = bounds;
}

/* Picks the tile step record by sign and arg2; +0x1E0 = its ticks x |count|. */
void func_8004CFB8(StageMap *map, s32 count, s32 arg2) {
    MapTileStep *step;
    if (count > 0) {
        step = &D_8008699C;
        if (arg2 != 0) {
            map->unk1E4 = &D_800869A8;
        } else {
            map->unk1E4 = step;
        }
    } else {
        step = &D_800869B4;
        if (arg2 != 0) {
            step = &D_800869C0;
        }
        map->unk1E4 = step;
    }
    map->unk1E0 = map->unk1E4->ticks * (count < 0 ? ~count + 1 : count);
}

void func_8004D028(StageMap *map) {
    if (map->unk1E0 > 0) {
        StageMap_ForEachTile(map, func_8004D0D0, 0);
        if (--map->unk1E0 == 0) {
            map->unk1E0 = -1;
        }
    }
}

void func_8004D088(StageMap *map) {
    if (map->unk1E0 != 0) {
        StageMap_ForEachTile(map, func_8004D108, 0);
        map->unk1E0 = 0;
    }
}

void func_8004D0D0(StageMap *map, MapTile *tile) {
    tile->vtbl->unk48(tile, 0, map->unk1E4);
}

void func_8004D108(s32 map, MapTile *tile) {
    tile->vtbl->unk48(tile, 1, &D_800869CC);
}

/* Calls perTile(map, tile) on the tiles of the 7 slots, after perSlot(map, slot) when given. */
void StageMap_ForEachTile(StageMap *map, void (*perTile)(), void (*perSlot)(void *, void *)) {
    s32 i;
    u8 *slot;

    for (i = 0; i < 7; i++) {
        slot = (u8 *)map + 0xEC + i * 0x1C;
        if (perSlot != NULL) {
            perSlot(map, slot);
        }
        StageMap_ForEachSlotTile(map, perTile, slot);
    }
}

void StageMap_ForEachSlotTile(StageMap *map, void (*perTile)(), MapSlot *slot) {
    MapTile **p;
    MapTile **end;

    end = slot->tiles + 0x19A;
    for (p = slot->tiles; p < end; p++) {
        perTile(map, *p);
    }
}

StageMapVtbl *StageMap_GetVtbl(void) {
    return (StageMapVtbl *)g_stageMapVtbl;
}

s32 func_8004D254(void) {
    s32 obj;

    obj = Heap_Alloc(0xDC);
    if (obj != 0) {
        func_8004D37C()->init(obj);
        return obj;
    }
    return 0;
}

void func_8004D2A4(void **obj) {
    RenderObjVtbl *vtbl;

    View_GetVtbl()->init(obj);
    vtbl = func_8004D37C();
    *obj = vtbl;
    vtbl->unk40(obj);
}

void func_8004D2F8(void) {
}

void func_8004D300(RenderObj *obj) {
    if ((obj->unk10 != 0) && (obj->unk70 != 0)) {
        View_GetVtbl()->unk9C(obj);
    }
}

void func_8004D35C(void) {
}

void func_8004D364(void) {
}

void func_8004D36C(void) {
}

void func_8004D374(void) {
}

RenderObjVtbl *func_8004D37C(void) {
    return (RenderObjVtbl *)D_800869D8;
}

s32 MapTile_New(void) {
    s32 tile;

    tile = Heap_Alloc(0x3C);
    if (tile != 0) {
        MapTile_GetVtbl()->init(tile);
        return tile;
    }
    return 0;
}

void MapTile_Init(MapTile *tile) {
    SceneNode_GetVtbl()->init(tile);
    tile->vtbl = MapTile_GetVtbl();
    tile->unk34 = 0;
    tile->flags = 0;
    tile->next = 0;
}

void func_8004D42C(void) {
}

void func_8004D434(MapTile *tile, u8 **message) {
    if (**message == 0x34) {
        tile->vtbl->unkB8(tile);
    }
}

void func_8004D47C(MapTile *tile, void *sender, s32 message) {
    SceneNode_GetVtbl()->unk9C(tile, sender, message);
    if (message < 9) {
        if (message >= 5) {
            tile->vtbl->unkA0(tile, sender, message);
        }
    }
}

s32 func_8004D500(s32 arg0) {
    return arg0;
}

MapTileVtbl *MapTile_GetVtbl(void) {
    return (MapTileVtbl *)g_mapTileVtbl;
}

/* Allocates 0xC4 bytes and runs slot 0x8 of the class of src/game/8004D578.c. */
s32 func_8004D518(s32 arg0) {
    s32 obj;

    obj = Heap_Alloc(0xC4);
    if (obj != 0) {
        Menu_GetVtbl()->init(obj, arg0);
        return obj;
    }
    return 0;
}

#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include "common.h"
#include "game/heap.h"
#include "game/dreamsys.h"
#include "game/entity.h"
#include "game/sound.h"

/*
 * Stages and the world the dream is built from (src/game/stage.c to src/game/map_tile.c):
 * - the per-stage chunk grids (StageGrid, g_stageChunkMoods at g_stageChunkMoods),
 * - Task, the class with a timeout and a result (vtable 0x80086668, class id 0x230) that the
 *   dream runner and the dream stage (include/game/place.h) derive from,
 * - DreamRunner (vtable 0x800865C8, class id 0x1F230, 0x50 bytes): built by Scene_RunDream for
 *   each dream, it loads the dreamer model and the music bank, creates the dream stage for the
 *   stage DreamSys_StartDay returns, rebuilds it on a link and ends the day,
 * - StageMap (vtable 0x800866E8, 0x1E8 bytes): the 7 chunks loaded around the dreamer, each a
 *   20 x 20 grid of 0x800-unit tiles, and the view rectangle of tiles drawn around the camera.
 * Vtable contents come from the executable (work/readable/W3/vt.py); slots are named after the
 * function stored there. Slots are left unprototyped where callers pass different types.
 */

/*
 * The chunk grid of a stage, 8 bytes, 14 entries at g_stageGrids (Stage_GetGrids). A chunk is
 * 0xA000 units (20 tiles of 0x800) square; odd rows are shifted by half a chunk (Stage_PlaceToWorld),
 * so a chunk has 6 neighbours.
 */
typedef struct StageGrid {
    s16 cols;     /* 0x00 chunks per row */
    s16 rows;     /* 0x02 */
    s32 stacked;  /* 0x04 1 for stages 0 and 6: one column of chunks stacked in height, 0x800 apart (StageMap_SlotAt) */
} StageGrid;

/* ------------------------------------------------------------------------------------------ */
/* Task: vtable 0x80086668, 0x38 bytes. Its base (vtable 0x8006E878) runs the loop.           */

/* The base class of Task (vtable 0x8006E878, src/game/screen.c): the slots Task chains to. */
typedef struct TaskBaseVtbl {
    u8 pad_00[0x08];
    void (*init)();         /* 0x08 Screen_Init */
    void (*destroy)();      /* 0x0C Object_Destroy */
    u8 pad_10[0x44 - 0x10];
    void (*run)();          /* 0x44 Screen_Run */
    void (*unk48)();        /* 0x48 Screen_Finish */
    u8 pad_4C[0x5C - 0x4C];
    void (*onTick)();       /* 0x5C Screen_OnClock: ticks++ */
    void (*setState)();     /* 0x60 Screen_SetState: state = arg, notify the watchers */
} TaskBaseVtbl;

typedef struct TaskVtbl {
    s32 classWord;          /* 0x230 */
    void *(*delete_)();     /* 0x04 Object_Delete */
    void (*init)();         /* 0x08 Task_Init */
    void (*destroy)();      /* 0x0C Task_Destroy */
    void (*watch)();        /* 0x10 Object_Watch */
    void (*unwatch)();      /* 0x14 Object_Unwatch */
    u8 pad_18[0x30 - 0x18];
    void (*notify)();       /* 0x30 Object_Notify */
    u8 pad_34[0x38 - 0x34];
    void (*onNotify)();     /* 0x38 */
    u8 pad_3C[0x40 - 0x3C];
    void (*reset)();        /* 0x40 Task_ClearTimeout: no timeout */
    s32 (*run)();           /* 0x44 Task_Run: run the loop, return the result */
    void (*unk48)();        /* 0x48 Task_Finish */
    u8 pad_4C[0x54 - 0x4C];
    void (*update)();       /* 0x54 Screen_OnDisplay (base), message type 1 */
    u8 pad_58[0x5C - 0x58];
    void (*onTick)();       /* 0x5C Task_OnTick */
    void (*setState)();     /* 0x60 Task_SetState: state 4 means timed out */
    u8 pad_64[0x6C - 0x64];
    void (*setTimeout)();   /* 0x6C Task_SetTimeout */
    void (*playTone)();     /* 0x70 Task_PlayTone */
    u8 pad_74[0x7C - 0x74];
    void (*onTimeout)();    /* 0x7C 0 in this vtable, set by derived classes */
} TaskVtbl;

typedef struct Task {
    TaskVtbl *vtbl;
    u8 pad_04[0x1C - 0x04];
    u32 ticks;              /* 0x1C counted by the base's slot 0x5C */
    s32 state;              /* 0x20 set by slot 0x60 */
    u8 pad_24[0x28 - 0x24];
    s32 result;             /* 0x28 returned by run */
    u32 timeout;            /* 0x2C ticks; -1 never (slot 0x6C) */
    s32 bankName;           /* 0x30 when not 0, the task made its own sound bank from this name */
    SoundBank *sound;       /* 0x34 */
} Task;

#define TASK_STATE_TIMEOUT 4

/* ------------------------------------------------------------------------------------------ */
/* DreamRunner: vtable 0x800865C8, 0x50 bytes, a Task.                                         */

/* The camera-like object at +0x18 (base class field): slot 0x70 gets DreamSys and two points 1200 units up. */
typedef struct RunnerViewVtbl {
    u8 pad_00[0x44];
    void (*unk44)();
    u8 pad_48[0x4C - 0x48];
    void (*unk4C)();
    u8 pad_50[0x70 - 0x50];
    void (*unk70)();
    void (*unk74)();
    u8 pad_78[0x8C - 0x78];
    void (*unk8C)();
    void (*unk90)();
    u8 pad_94[0xAC - 0x94];
    struct RunnerViewSub *(*unkAC)();
} RunnerViewVtbl;

typedef struct RunnerViewSubVtbl {
    u8 pad_00[0x60];
    void (*unk60)();
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
    s32 (*unk7C)();
} RunnerContextHeadVtbl;

typedef struct RunnerContextHead {
    RunnerContextHeadVtbl *vtbl;
} RunnerContextHead;

typedef struct RunnerContext {
    RunnerContextHead *unk0;
    s32 unk4;               /* watched by DreamSys while the runner runs */
    Object *unk8;           /* Clock_Create() */
    struct StageMap *map;   /* 0x0C StageMap_New(0, 1) */
    Object *unk10;          /* DreamView_New(), class 0x800869D8 */
} RunnerContext;

/* What the vtable slots of the loaded TIM and model objects do here. */
typedef struct RunnerResVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();     /* 0x04 */
    u8 pad_08[0x5C - 0x08];
    void (*unk5C)();
    u8 pad_60[0x78 - 0x60];
    void (*unk78)();
} RunnerResVtbl;

typedef struct RunnerRes {
    RunnerResVtbl *vtbl;
} RunnerRes;

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
    void (*unk48)();        /* 0x48 DreamRunner_Finish */
    void (*start)();        /* 0x4C DreamRunner_Start */
    void (*unk50)();        /* 0x50 DreamRunner_End */
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
    s32 unk10;
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
    RunnerRes *etcTim;      /* 0x44 ETC\ETC.TIM */
    RunnerRes *dreamerModel; /* 0x48 ETC\DREAMER.TMD */
    RunnerStage *stage;     /* 0x4C the dream stage, Place_New */
} DreamRunner;

/* ------------------------------------------------------------------------------------------ */
/* StageMap: vtable 0x800866E8, 0x1E8 bytes.                                                  */

/* A tile (class 0x80086AA0, 0x3C bytes): a GsDOBJ2 at +0x10 (GsLinkObject4 in StageMap_BuildTiles). */
typedef struct MapTileVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();     /* 0x04 */
    void (*init)();         /* 0x08 MapTile_Init */
    u8 pad_0C[0x38 - 0x0C];
    void (*unk38)();        /* 0x38 run on the tiles of the view by MapTile_Tell */
    u8 pad_3C[0x48 - 0x3C];
    void (*unk48)();        /* 0x48 (tile, 0 or 1, 12-byte record) from StageMap_AddTileStretchStep and StageMap_ResetOneTileScale */
    void (*unk4C)();        /* 0x4C (tile, parent, position) */
    u8 pad_50[0x70 - 0x50];
    void (*unk70)();
    u8 pad_74[0xA0 - 0x74];
    void (*unkA0)();        /* 0xA0 SceneNode_CheckContact */
    u8 pad_A4[0xB8 - 0xA4];
    void (*unkB8)();        /* 0xB8 MapTile_OnActorMessage */
} MapTileVtbl;

typedef struct MapTileModel {
    u8 pad_00[0x10];
    s32 tmd;                /* 0x10 handed to GsLinkObject4 */
} MapTileModel;

typedef struct MapTile {
    MapTileVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    s32 attribute;          /* 0x10 GsDOBJ2.attribute; bit 31 (GsDOFF) hides the tile */
    Coord2 *coord;          /* 0x14 GsDOBJ2.coord2 */
    s32 tmd;                /* 0x18 GsDOBJ2.tmd */
    u8 pad_1C[0x20 - 0x1C];
    MapTileModel *model;    /* 0x20 */
    u8 pad_24[0x34 - 0x24];
    s16 unk34;
    u16 flags;              /* 0x36 bit 0x80: told through slot 0x38 by MapTile_Tell */
    struct MapTile *next;   /* 0x38 more tiles on the same square (from index 400 of the slot's array) */
} MapTile;

#define MAP_TILE_HIDDEN 0x80000000
#define MAP_SLOT_TILES 410      /* 20 x 20 squares and 10 extra tiles */

/* The chunk object of a slot (MapChunk_New, 0x3C bytes, src/game/map_chunk.c): a file object (loader.h
   File) that reads one STGxx\Mxxx.LBD chunk file, then its entity part. Vtable g_mapChunkVtbl: the file
   class slots, then the chunk's own. */
typedef struct MapChunkVtbl {
    s32 classWord;           /* 0x903 */
    void *(*delete_)();      /* 0x04 File_Delete */
    void (*init)();          /* 0x08 MapChunk_Init */
    void (*destroy)();       /* 0x0C MapChunk_Destroy */
    u8 pad_10[0x44 - 0x10];  /* Object methods, then 0 */
    void (*open)();          /* 0x44 (self, path, 1, 0) */
    void (*close)();         /* 0x48 */
    void (*seek)();          /* 0x4C (self, offset, whence) */
    u8 pad_50[0x54 - 0x50];
    void (*read)();          /* 0x54 (self, buffer, size) */
    u8 pad_58[0x5C - 0x58];
    void (*freeData)();      /* 0x5C File_FreeData */
    void (*unk_60)();        /* 0x60 func_80026C80, empty */
    void (*onLoaded)();      /* 0x64 MapChunk_OnLoaded */
    u8 pad_68[0x74 - 0x68];
    void (*unload)();        /* 0x74 MapChunk_Unload, replaces the file class cancel slot */
    void (*load)();          /* 0x78 MapChunk_Load (chunk, data from the stage's chunk loader) */
    void (*clear)();         /* 0x7C MapChunk_Clear */
    void (*loadEntities)();  /* 0x80 MapChunk_LoadEntities */
    void (*freeEntities)();  /* 0x84 MapChunk_FreeEntities */
    void (*setLoadEntities)(); /* 0x88 MapChunk_SetLoadEntities (chunk, flag given to StageMap_Init) */
} MapChunkVtbl;

/* The header of a chunk file: the model list, then the TMD, then the entity part. */
typedef struct MapChunkData {
    u8 pad_00[2];
    u16 hasEntities;         /* 0x02 non-zero: the file has an entity part (slot 0x80) */
    s32 modelsOffset;        /* 0x04 the model list, handed to the slot's model set */
    s32 modelsSize;          /* 0x08 the TMD follows the list */
    u8 pad_0C[0x10 - 0x0C];
    s32 entitiesOffset;      /* 0x10 file offset of the entity part */
    s32 entitiesSize;        /* 0x14 */
} MapChunkData;

typedef struct MapChunk {
    MapChunkVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    MapChunkData *data;      /* 0x10 the 0xB358-byte chunk buffer */
    s32 size;                /* 0x14 0xB358 once the buffer exists */
    u8 pad_18[0x20 - 0x18];
    u16 keepData;            /* 0x20 File.keepData: set to data != NULL at creation */
    u8 pad_22[0x24 - 0x22];
    s32 flags;               /* 0x24 done file requests: 0x80 read */
    u8 pad_28[0x2A - 0x28];
    u16 state;               /* 0x2A 9 reading the chunk, 10 reading its entity part, 0 idle */
    s16 loaded;              /* 0x2C 0 empty; non-zero once its data is in, 2 after StageMap_BuildTiles built its tiles */
    s16 entitiesLoaded;      /* 0x2E StageMap_PollLoads clears it and sends slot message 7 */
    s16 index;               /* 0x30 chunk index in the stage grid (row * cols + col), -1 when empty */
    s16 id;                  /* 0x32 neighbour position 0 to 6 (StageMap_LoadAround) */
    s32 entities;            /* 0x34 the entity part (heap), first argument of Sym_SpawnOrSpy (Place_SpawnCell) */
    s32 loadEntities;        /* 0x38 read the entity part as soon as the chunk is in */
} MapChunk;

/* The model set of a slot (MapModels_New(0)): slot 0x78 hands out the chunk's models one by one. */
typedef struct MapModelsVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();     /* 0x04 */
    u8 pad_08[0x78 - 0x08];
    void *(*nextModel)();   /* 0x78 (models, out record, index): NULL at the end, -1 for an empty square */
} MapModelsVtbl;

typedef struct MapModels {
    MapModelsVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    void *data;             /* 0x10 */
    s32 unk14;
    u8 pad_18[0x2C - 0x18];
    Object *tmd;            /* 0x2C the chunk's TMD, Tmd_Create */
} MapModels;

/* One loaded chunk, 0x1C bytes, 7 at StageMap +0xEC. */
typedef struct MapSlot {
    u16 loading;            /* 0x00 set while its chunk data loads (StageMap_AssignChunks, StageMap_PollLoads) */
    s16 index;              /* 0x02 position 0 to 6 */
    MapChunk *chunk;        /* 0x04 */
    MapModels *models;      /* 0x08 */
    MapTile *root;          /* 0x0C the chunk's origin node; its coord is the chunk position */
    MapTile **tiles;        /* 0x10 MAP_SLOT_TILES tiles, row-major 20 per row */
    Object *spawned;        /* 0x14 Sym_SpawnOrSpy's result (Place_SpawnCell), deleted on slot message 6 */
    s32 unk18;
} MapSlot;

/* What StageMap slot 0x110 (StageMap_Locate) computes for a world position, 0x2C bytes. */
typedef struct MapLocation {
    union {
        StagePlace place;
        s16 chunkKey;       /* col | row << 8 */
        u16 chunkKeyU;
    } at;
    u8 pad_0A[0x0C - 0x0A];
    Vec3 chunkCenter;       /* 0x0C */
    Vec3 offset;            /* 0x18 position minus chunkCenter */
    MapSlot *slot;          /* 0x24 */
    s32 chunkIndex;         /* 0x28 */
} MapLocation;

/* A rectangle of tiles in one slot, 12 bytes: what the view draws. */
typedef struct MapView {
    s32 slot;               /* 0x00 slot index */
    s16 tileX;
    s16 tileY;
    s16 cols;
    s16 rows;
} MapView;

/* StageMap_TellNearTiles saves and restores the 48 bytes of views as these. */
typedef struct MapViewSave {
    s32 w[4];
} MapViewSave;

/* One request of StageMap_LoadAround, 12 bytes: what the chunk loader returned for a neighbour. */
typedef struct ChunkRequest {
    s32 data;               /* 0x00 the loader's result, 0 when the neighbour is outside the grid */
    s32 chunkIndex;         /* 0x04 */
    s32 neighbor;           /* 0x08 0 to 6 */
} ChunkRequest;

/* Neighbour step: chunk index delta = rowStep * cols + (odd row ? colStepOdd : colStepEven), g_chunkNeighborSteps. */
typedef struct HexNeighbor {
    s32 rowStep;
    s32 colStepOdd;
    s32 colStepEven;
} HexNeighbor;

/* Which neighbours StageMap_LoadAround loads, 7 pairs (g_allNeighbors, g_neighborLoadLists[]). */
typedef struct NeighborUse {
    u8 neighbor;            /* 0 to 6 */
    u8 enabled;
} NeighborUse;

/* What the map follows (+0x6C) and the senders of its messages: objects with a GsCOORDINATE2 at +0x14. */
typedef struct MapActor {
    u8 pad_00[0x0C];
    s32 attached;           /* 0x0C */
    u8 pad_10[0x14 - 0x10];
    Coord2 *coord;          /* 0x14 */
} MapActor;

/* The 12-byte records +0x1E4 points to (g_tileStretchSlowUp to g_tileStretchFastDown), handed to every tile's slot 0x48. */
typedef struct MapTileStep {
    s16 unk0[3];
    s16 ticks;              /* 0x06 64 or 4: +0x1E0 = ticks x count (StageMap_StartTileStretch) */
} MapTileStep;

typedef struct StageMapVtbl {
    s32 classWord;          /* 0x114 */
    void *(*delete_)();     /* 0x04 Object_Delete */
    void (*init)();         /* 0x08 StageMap_Init */
    void (*destroy)();      /* 0x0C StageMap_Destroy */
    void (*watch)();        /* 0x10 */
    void (*unwatch)();      /* 0x14 */
    u8 pad_18[0x30 - 0x18];
    void (*notify)();       /* 0x30 Object_Notify */
    u8 pad_34[0x40 - 0x34];
    void (*reset)();        /* 0x40 StageMap_Reset */
    u8 pad_44[0x88 - 0x44];
    void (*onSlotMessage)(); /* 0x88 StageMap_OnSlotMessage (map, 6 or 7, slot, index) */
    u8 pad_8C[0xB8 - 0x8C];
    void *(*unkB8)();       /* 0xB8 RootNode_GetLight */
    void (*setAmbient)();   /* 0xBC RootNode_SetAmbient */
    void (*clearSlots)();   /* 0xC0 StageMap_ClearSlots */
    void (*unkC4)();        /* 0xC4 StageMap_SetLights */
    void (*setChunkLoader)(); /* 0xC8 StageMap_SetChunkLoader */
    void (*setMessageFilter)(); /* 0xCC StageMap_SetMessageFilter */
    void (*filterMessage)(); /* 0xD0 StageMap_FilterMessage */
    u8 pad_D4[0xDC - 0xD4];
    void (*setViewDistance)(); /* 0xDC StageMap_SetViewDistance */
    void (*setGrid)();      /* 0xE0 StageMap_SetGrid */
    void (*setTarget)();    /* 0xE4 StageMap_SetTarget */
    void (*placeToWorld)(); /* 0xE8 StageMap_PlaceToWorld */
    void (*activate)();     /* 0xEC StageMap_Activate */
    void (*deactivate)();   /* 0xF0 StageMap_Deactivate */
    s32 (*follow)();        /* 0xF4 StageMap_Follow */
    void (*loadAround)();   /* 0xF8 StageMap_LoadAround (map, chunk index, origin, neighbours) */
    void (*assignChunks)(); /* 0xFC StageMap_AssignChunks */
    void (*unk100)();       /* 0x100 StageMap_PollLoads */
    void (*buildTiles)();   /* 0x104 StageMap_BuildTiles */
    void (*hideSlot)();     /* 0x108 StageMap_HideSlot */
    void *(*getLocation)(); /* 0x10C StageMap_GetLocation */
    s32 (*locate)();        /* 0x110 StageMap_Locate */
    MapSlot *(*currentSlot)(); /* 0x114 StageMap_GetCurrentSlot (map, &place): the current slot, its chunk (col, row) into place */
    MapSlot *(*slotById)(); /* 0x118 StageMap_SlotById */
    MapSlot *(*slotAt)();   /* 0x11C StageMap_SlotAt */
    s32 (*slotIndexById)(); /* 0x120 StageMap_SlotIndexById */
    s32 (*slotIndexByChunk)(); /* 0x124 StageMap_SlotIndexByChunk */
    void (*updateView)();   /* 0x128 StageMap_UpdateView */
    s32 (*tellView)();      /* 0x12C StageMap_TellNearTiles */
    void (*unk130)();       /* 0x130 func_8004CFA8 */
    void (*setBounds)();       /* 0x134 StageMap_SetBounds */
    void (*unk138)();       /* 0x138 StageMap_StartTileStretch */
    void (*unk13C)();       /* 0x13C StageMap_StepTileStretch */
    void (*unk140)();       /* 0x140 StageMap_ResetTileScale */
} StageMapVtbl;

typedef struct StageMap {
    StageMapVtbl *vtbl;
    u8 pad_04[0x54 - 0x04];
    Vec3 origin;            /* 0x54 world position of the grid, g_mapDefaultOrigin (0, 0, 0) when none is given */
    s32 (*loadChunk)();     /* 0x60 (loadContext, chunk index, 0, 0), set by slot 0xC8 */
    void *loadContext;      /* 0x64 */
    StageGrid *grid;        /* 0x68 */
    MapActor *target;       /* 0x6C what the view follows, set by slot 0xE4 */
    s32 active;             /* 0x70 slots 0xEC and 0xF0 */
    s32 viewDistance;       /* 0x74 slot 0xDC */
    s16 viewHalf;           /* 0x78 viewDistance >> 12 */
    s16 viewTiles;          /* 0x7A viewDistance >> 11 */
    s16 viewX;              /* 0x7C first tile of the view */
    s16 viewY;              /* 0x7E */
    s32 viewCols;           /* 0x80 */
    s32 viewRows;           /* 0x84 */
    s32 viewCount;          /* 0x88 rectangles in views */
    union {
        MapView views[4];   /* 0x8C */
        MapViewSave save[3];
    } v;
    MapLocation location;   /* 0xBC where the target stands */
    s32 *messageFilter;     /* 0xE8 message codes slot 0xD0 passes on, 0-terminated */
    MapSlot slots[7];       /* 0xEC */
    s32 swapping;           /* 0x1B0 set while chunks load */
    u16 pendingSlots;       /* 0x1B4 slots still loading */
    u8 pad_1B6[0x1B8 - 0x1B6];
    s32 ready;              /* 0x1B8 set once they all loaded; the view is drawn only then */
    MapSlot *currentSlot;   /* 0x1BC */
    s16 tellKey;            /* 0x1C0 chunk key of the tile being told (StageMap_TellViewTiles) */
    u8 tellX;               /* 0x1C2 */
    u8 tellY;               /* 0x1C3 */
    u8 pad_1C4[0x1CC - 0x1C4];
    s32 unk1CC[4];          /* 0x1CC address returned by slot 0x130 */
    void *bounds;           /* 0x1DC box of chunks tested by StageMap_IsOutsideBounds */
    s32 unk1E0;             /* 0x1E0 */
    MapTileStep *unk1E4;    /* 0x1E4 */
} StageMap;

/* Functions of src/game/stage.c that other files call or reference (docs/naming.md, Prototypes) */
StageGrid *Stage_GetGrid(s32 stage);
u32 Stage_FindChunkByMood(StagePlace *place, s16 *mood);
s16 *Stage_GetChunkMood(s32 stage, StagePlace *place);

#endif

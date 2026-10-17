#ifndef GAME_STAGE_MAP_H
#define GAME_STAGE_MAP_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/map_models.h"
#include "game/map_chunk.h"
#include "game/stage.h"
#include "game/map_tile.h"

/*
 * StageMap (src/game/stage_map.c): vtable 0x800866E8, 0x1E8 bytes: the 7 chunks loaded around the
 * dreamer, each a 20 x 20 grid of 0x800-unit tiles, and the view rectangle of tiles drawn around
 * the camera. A chunk is a MapChunk (map_chunk.h) with its MapModels (map_models.h) and MapTile
 * nodes (map_tile.h).
 */

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
    void *(*getLight)();       /* 0xB8 RootNode_GetLight */
    void (*setAmbient)();   /* 0xBC RootNode_SetAmbient */
    void (*clearSlots)();   /* 0xC0 StageMap_ClearSlots */
    void (*setLights)();        /* 0xC4 StageMap_SetLights */
    void (*setChunkLoader)(); /* 0xC8 StageMap_SetChunkLoader */
    void (*setMessageFilter)(); /* 0xCC StageMap_SetMessageFilter */
    void (*filterMessage)(); /* 0xD0 StageMap_FilterMessage */
    StagePlace *(*getTellKey)(); /* 0xD4 StageMap_GetTellKey (map, sender): the place of the tile told */
    u8 pad_D8[0xDC - 0xD8];
    void (*setViewDistance)(); /* 0xDC StageMap_SetViewDistance */
    void (*setGrid)();      /* 0xE0 StageMap_SetGrid */
    void (*setTarget)();    /* 0xE4 StageMap_SetTarget */
    void (*placeToWorld)(); /* 0xE8 StageMap_PlaceToWorld */
    void (*activate)();     /* 0xEC StageMap_Activate */
    void (*deactivate)();   /* 0xF0 StageMap_Deactivate */
    s32 (*follow)();        /* 0xF4 StageMap_Follow */
    void (*loadAround)();   /* 0xF8 StageMap_LoadAround (map, chunk index, origin, neighbours) */
    void (*assignChunks)(); /* 0xFC StageMap_AssignChunks */
    void (*pollLoads)();       /* 0x100 StageMap_PollLoads */
    void (*buildTiles)();   /* 0x104 StageMap_BuildTiles */
    void (*hideSlot)();     /* 0x108 StageMap_HideSlot */
    void *(*getLocation)(); /* 0x10C StageMap_GetLocation */
    s32 (*locate)();        /* 0x110 StageMap_Locate */
    MapSlot *(*notifiedSlot)(); /* 0x114 StageMap_GetNotifiedSlot (map, &place): the notified slot, its chunk (col, row) into place */
    MapSlot *(*slotById)(); /* 0x118 StageMap_SlotById */
    MapSlot *(*slotAt)();   /* 0x11C StageMap_SlotAt */
    s32 (*slotIndexById)(); /* 0x120 StageMap_SlotIndexById */
    s32 (*slotIndexByChunk)(); /* 0x124 StageMap_SlotIndexByChunk */
    void (*updateView)();   /* 0x128 StageMap_UpdateView */
    s32 (*tellNearTiles)();      /* 0x12C StageMap_TellNearTiles */
    void (*unk130)();       /* 0x130 func_8004CFA8 */
    void (*setBounds)();       /* 0x134 StageMap_SetBounds */
    void (*startTileStretch)();       /* 0x138 StageMap_StartTileStretch */
    void (*stepTileStretch)();       /* 0x13C StageMap_StepTileStretch */
    void (*resetTileScale)();       /* 0x140 StageMap_ResetTileScale */
} StageMapVtbl;

typedef struct StageMap {
    StageMapVtbl *vtbl;
    u8 pad_04[0x54 - 0x04];
    Vec3 origin;            /* 0x54 world position of the grid, g_mapDefaultOrigin (0, 0, 0) when none is given */
    s32 (*loadChunk)();     /* 0x60 (loadContext, chunk index, 0, 0), set by slot 0xC8 */
    void *loadContext;      /* 0x64 */
    StageGrid *grid;        /* 0x68 */
    SceneNode *target;      /* 0x6C what the view follows (the DreamSys), set by slot 0xE4 */
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
    s32 *messageFilter;     /* 0xE8 sender class words slot 0xD0 passes on, 0-terminated (g_placeMapMessageFilter: 0x1F34, 0x1F234) */
    MapSlot slots[7];       /* 0xEC */
    s32 swapping;           /* 0x1B0 set while chunks load */
    u16 pendingSlots;       /* 0x1B4 slots still loading */
    u8 pad_1B6[0x1B8 - 0x1B6];
    s32 ready;              /* 0x1B8 set once they all loaded; the view is drawn only then */
    MapSlot *notifiedSlot;   /* 0x1BC */
    s16 tellKey;            /* 0x1C0 chunk key of the tile being told (StageMap_TellViewTiles) */
    u8 tellX;               /* 0x1C2 */
    u8 tellY;               /* 0x1C3 */
    u8 pad_1C4[0x1CC - 0x1C4];
    s32 unk1CC[4];          /* 0x1CC address returned by slot 0x130 */
    void *bounds;           /* 0x1DC box of chunks tested by StageMap_IsOutsideBounds */
    s32 stretchTicks;             /* 0x1E0 */
    Fraction *stretchStep;  /* 0x1E4 a Fraction[3] scale step handed to every tile's slot 0x48 (g_tileStretchSlowUp to g_tileStretchFastDown); its y denominator is the ticks per step */
} StageMap;

/* Functions of src/game/stage_map.c that other files call or reference (docs/naming.md, Prototypes) */
StageMap *StageMap_New(Vec3 *origin, s32 loadEntities);

#endif

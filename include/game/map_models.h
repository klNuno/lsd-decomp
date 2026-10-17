#ifndef GAME_MAP_MODELS_H
#define GAME_MAP_MODELS_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/gs.h"

/*
 * MapModels (vtable g_mapModelsVtbl 0x8006D940, 0x34 bytes, MapModels_New): a file class
 * (file_base.h) holding the model list of one map chunk, a 20 by 20 grid of chained records.
 * Slot 0x78 hands out the chunk's models one by one.
 */
typedef struct MapModelsVtbl {
    s32 classWord;
    void *(*delete_)();     /* 0x04 */
    void (*init)(void *modelSet, s32 path); /* 0x08 MapModels_Init */
    u8 pad_0C[0x6C - 0x0C]; /* the other FileVtbl slots (file_base.h) */
    void (*loadAsync)(void *modelSet, s32 path); /* 0x6C */
    u8 pad_70[0x78 - 0x70];
    void *(*nextModel)();   /* 0x78 MapModels_NextModel (models, out record, index): NULL at the end, -1 for an empty square */
} MapModelsVtbl;

/* The record slot 0x78 fills for one model (0x40 bytes); the caller keeps chained between calls. */
typedef struct MapModelRecord {
    u8 pad_00[0x0C];
    Vec3 pos;                   /* 0x0C position in the chunk: square centre, height * 0x800 */
    u8 pad_18[0x1A - 0x18];
    u16 rotY;                   /* 0x1A yaw, quarter turns << 10, into the tile's rotate[1] */
    u8 pad_1C[0x2C - 0x1C];
    s16 unk_2C;                 /* 0x2C byte 1 of the grid record */
    u16 flags;                  /* 0x2E into MapTile.flags */
    s32 extra;                  /* 0x30 placed from tile 400 on instead of on its square */
    s32 chained;                /* 0x34 offset of the next record of the square, 0 at the end */
    s32 objectIndex;            /* 0x38 the TMD object, also given to the TMD's slot 0x80 */
    u8 pad_3C[0x40 - 0x3C];
} MapModelRecord;

typedef struct MapModels {
    MapModelsVtbl *vtbl;    /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    u8 *data;               /* 0x10 a 8-byte header, then 400 records of 0xC bytes, then the chained ones */
    s32 size;
    CdlLocDir cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
    struct Tmd *tmd;        /* 0x2C the chunk's TMD, Tmd_Create (tmd.h) */
    s32 loaded;             /* 0x30 set by MapModels_OnLoaded */
} MapModels;

/* Functions of src/game/map_models.c that other files call or reference (docs/naming.md, Prototypes) */
MapModels *MapModels_New(s32 path);
MapModelsVtbl *MapModels_GetVtbl(void);

#endif

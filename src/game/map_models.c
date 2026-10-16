#include "common.h"
#include "game/map_models.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * MapModels: the model list of one map chunk (vtable 0x8006D940, made by MapModels_New).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The object that MapModels_OnLoaded marks: only 0x30 is used here. */
typedef struct RootObject {
    u8 pad_00[0x30];
    s32 loaded;
} RootObject;

/* Vtable of the root object class returned by File_GetBackendVtbl (heap.h ObjectVtbl: init 0x08, destroy 0x0C). */
typedef struct ObjectRootVtbl {
    u8 pad_00[0x8];
    void (*init)(void *object);     /* 0x08 */
    void (*destroy)(s32 object);    /* 0x0C, the caller passes the pointer as s32 */
    u8 pad_10[0x54];
    void (*onLoaded)(void *object);   /* 0x64, not named in heap.h */
} ObjectRootVtbl;

/* Vtable of the 0x34-byte object class at g_mapModelsVtbl (MapModels_New; map_models.h calls it a model set). */
typedef struct ModelSetVtbl {
    u8 pad_00[0x8];
    void (*init)(void *modelSet, s32 param);   /* 0x08 */
    u8 pad_0C[0x60];
    void (*loadAsync)(void *modelSet, s32 param); /* 0x6C */
} ModelSetVtbl;

typedef struct ModelSet {
    ModelSetVtbl *vt;     /* 0x00 */
    u8 pad_04[0x28];
    s32 tmd;
    s32 loaded;
} ModelSet;

extern ModelSetVtbl g_mapModelsVtbl;

/* One cell of the 20 by 20 grid: 0xC bytes, 400 cells, a chain of records through unk_08. */
typedef struct GridRecord {
    u8 present;
    u8 unk_01;
    u16 objectIndex;
    u8 flags;
    u8 quarterTurns;
    s16 height;
    s32 nextOffset;   /* offset of the next record, 0 at the end of the chain */
} GridRecord;

/* The grid item that MapModels_NextModel fills for one cell (0x3C bytes). */
typedef struct GridItem {
    u8 pad_00[0xC];
    s32 posX;
    s32 posY;
    s32 posZ;
    u8 pad_18[0x2];
    s16 rotY;
    u8 pad_1C[0x10];
    s16 unk_2C;
    s16 flags;
    s32 extra;
    s32 nextOffset;   /* offset of the next record in the chain */
    s32 objectIndex;
} GridItem;

typedef struct GridObjectVtbl {
    u8 pad_00[0x80];
    s32 (*getModel)(void *object, u16 id, s32 cell, void *item);
} GridObjectVtbl;

typedef struct GridObject {
    GridObjectVtbl *vt;
} GridObject;

/* The grid context: the record table at unk_10 and the object at unk_2C that places the item. */
typedef struct GridContext {
    u8 pad_00[0x10];
    u8 *data;
    u8 pad_14[0x18];
    GridObject *tmd;
} GridContext;
s32 MapModels_New(s32 path) {
    s32 modelSet;

    modelSet = (s32)Heap_Alloc(0x34);
    if (modelSet != 0) {
        MapModels_GetVtbl()->init((void *)modelSet, path);
        return modelSet;
    }
    return 0;
}

void MapModels_Init(ModelSet *modelSet, s32 path) {
    ((ObjectRootVtbl *)File_GetBackendVtbl())->init(modelSet);
    modelSet->vt = MapModels_GetVtbl();
    modelSet->tmd = 0;
    modelSet->loaded = 0;
    if (path != 0) {
        modelSet->vt->loadAsync(modelSet, path);
    }
}

void MapModels_Destroy(s32 object) {
    ((ObjectRootVtbl *)File_GetBackendVtbl())->destroy(object);
}

void MapModels_OnLoaded(RootObject *object) {
    object->loaded = 1;
    ((ObjectRootVtbl *)File_GetBackendVtbl())->onLoaded(object);
}

s32 MapModels_NextModel(GridContext *context, GridItem *item, s32 cellIndex) {
    GridRecord *record;
    s32 nextOffset;
    u16 itemId;
    s32 val6;
    u8 *base;

    if (cellIndex < 0x190) {
        nextOffset = item->nextOffset;
        if (nextOffset != 0) {
            base = context->data;
            record = (GridRecord *)(base + nextOffset);
            item->extra = 1;
        } else {
            record = (GridRecord *)(cellIndex * 0xC + 8 + context->data);
            item->extra = 0;
        }
        item->nextOffset = record->nextOffset;
        if (record->present != 0) {
            item->posX = ((cellIndex % 20) << 0xB) + 0x400;
            val6 = record->height;
            item->posZ = ((cellIndex / 20) << 0xB) + 0x400;
            item->posY = val6 << 0xB;
            item->rotY = record->quarterTurns << 0xA;
            item->unk_2C = record->unk_01;
            item->flags = record->flags;
            itemId = record->objectIndex;
            item->objectIndex = itemId;
            return context->tmd->vt->getModel(context->tmd, itemId, cellIndex, item);
        }
        return -1;
    }
    return 0;
}

ModelSetVtbl *MapModels_GetVtbl(void) {
    return &g_mapModelsVtbl;
}

static s32 func_8002C3B8(void) {
    return 0;
}

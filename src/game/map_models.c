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
    s32 unk_30;
} RootObject;

/* Vtable of the root object class returned by File_GetBackendVtbl (heap.h ObjectVtbl: init 0x08, destroy 0x0C). */
typedef struct ObjectRootVtbl {
    u8 pad_00[0x8];
    void (*init)(void *object);     /* 0x08 */
    void (*destroy)(s32 object);    /* 0x0C, the caller passes the pointer as s32 */
    u8 pad_10[0x54];
    void (*unk_64)(void *object);   /* 0x64, not named in heap.h */
} ObjectRootVtbl;

/* Vtable of the 0x34-byte object class at g_mapModelsVtbl (MapModels_New; stage.h calls it a model set). */
typedef struct ModelSetVtbl {
    u8 pad_00[0x8];
    void (*init)(void *modelSet, s32 param);   /* 0x08 */
    u8 pad_0C[0x60];
    void (*unk_6C)(void *modelSet, s32 param); /* 0x6C */
} ModelSetVtbl;

typedef struct ModelSet {
    ModelSetVtbl *vt;     /* 0x00 */
    u8 pad_04[0x28];
    s32 unk_2C;
    s32 unk_30;
} ModelSet;

extern ModelSetVtbl g_mapModelsVtbl;

/* One cell of the 20 by 20 grid: 0xC bytes, 400 cells, a chain of records through unk_08. */
typedef struct GridRecord {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    s16 unk_06;
    s32 unk_08;   /* offset of the next record, 0 at the end of the chain */
} GridRecord;

/* The grid item that MapModels_NextModel fills for one cell (0x3C bytes). */
typedef struct GridItem {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
    u8 pad_1C[0x10];
    s16 unk_2C;
    s16 unk_2E;
    s32 unk_30;
    s32 unk_34;   /* offset of the next record in the chain */
    s32 unk_38;
} GridItem;

typedef struct GridObjectVtbl {
    u8 pad_00[0x80];
    s32 (*unk_80)(void *object, u16 id, s32 cell, void *item);
} GridObjectVtbl;

typedef struct GridObject {
    GridObjectVtbl *vt;
} GridObject;

/* The grid context: the record table at unk_10 and the object at unk_2C that places the item. */
typedef struct GridContext {
    u8 pad_00[0x10];
    u8 *unk_10;
    u8 pad_14[0x18];
    GridObject *unk_2C;
} GridContext;
s32 MapModels_New(s32 initParam) {
    s32 modelSet;

    modelSet = (s32)Heap_Alloc(0x34);
    if (modelSet != 0) {
        MapModels_GetVtbl()->init((void *)modelSet, initParam);
        return modelSet;
    }
    return 0;
}

void MapModels_Init(ModelSet *modelSet, s32 initParam) {
    ((ObjectRootVtbl *)File_GetBackendVtbl())->init(modelSet);
    modelSet->vt = MapModels_GetVtbl();
    modelSet->unk_2C = 0;
    modelSet->unk_30 = 0;
    if (initParam != 0) {
        modelSet->vt->unk_6C(modelSet, initParam);
    }
}

void MapModels_Destroy(s32 object) {
    ((ObjectRootVtbl *)File_GetBackendVtbl())->destroy(object);
}

void MapModels_OnLoaded(RootObject *object) {
    object->unk_30 = 1;
    ((ObjectRootVtbl *)File_GetBackendVtbl())->unk_64(object);
}

s32 MapModels_NextModel(GridContext *context, GridItem *item, s32 cellIndex) {
    GridRecord *record;
    s32 nextOffset;
    u16 itemId;
    s32 val6;
    u8 *base;

    if (cellIndex < 0x190) {
        nextOffset = item->unk_34;
        if (nextOffset != 0) {
            base = context->unk_10;
            record = (GridRecord *)(base + nextOffset);
            item->unk_30 = 1;
        } else {
            record = (GridRecord *)(cellIndex * 0xC + 8 + context->unk_10);
            item->unk_30 = 0;
        }
        item->unk_34 = record->unk_08;
        if (record->unk_00 != 0) {
            item->unk_0C = ((cellIndex % 20) << 0xB) + 0x400;
            val6 = record->unk_06;
            item->unk_14 = ((cellIndex / 20) << 0xB) + 0x400;
            item->unk_10 = val6 << 0xB;
            item->unk_1A = record->unk_05 << 0xA;
            item->unk_2C = record->unk_01;
            item->unk_2E = record->unk_04;
            itemId = record->unk_02;
            item->unk_38 = itemId;
            return context->unk_2C->vt->unk_80(context->unk_2C, itemId, cellIndex, item);
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

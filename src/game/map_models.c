#include "common.h"
#include "game/map_models.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/tmd.h"

/*
 * MapModels: the model list of one map chunk (vtable 0x8006D940, made by MapModels_New).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern MapModelsVtbl g_mapModelsVtbl;

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

MapModels *MapModels_New(s32 path) {
    MapModels *modelSet;

    modelSet = Heap_Alloc(0x34);
    if (modelSet != NULL) {
        MapModels_GetVtbl()->base.init(modelSet, path);
        return modelSet;
    }
    return NULL;
}

void MapModels_Init(MapModels *modelSet, s32 path) {
    File_GetBackendVtbl()->init(modelSet);
    modelSet->vtbl = MapModels_GetVtbl();
    modelSet->tmd = 0;
    modelSet->loaded = 0;
    if (path != 0) {
        modelSet->vtbl->base.loadAsync(modelSet, path);
    }
}

void MapModels_Destroy(MapModels *object) {
    File_GetBackendVtbl()->destroy(object);
}

void MapModels_OnLoaded(MapModels *object) {
    object->loaded = 1;
    File_GetBackendVtbl()->onLoaded(object);
}

ModelObject *MapModels_NextModel(MapModels *context, MapModelRecord *item, s32 cellIndex) {
    GridRecord *record;
    s32 nextOffset;
    u16 itemId;
    s32 val6;
    u8 *base;

    if (cellIndex < 0x190) {
        nextOffset = item->chained;
        if (nextOffset != 0) {
            base = context->data;
            record = (GridRecord *)(base + nextOffset);
            item->extra = 1;
        } else {
            record = (GridRecord *)(cellIndex * 0xC + 8 + context->data);
            item->extra = 0;
        }
        item->chained = record->nextOffset;
        if (record->present != 0) {
            item->pos.x = ((cellIndex % 20) << 0xB) + 0x400;
            val6 = record->height;
            item->pos.z = ((cellIndex / 20) << 0xB) + 0x400;
            item->pos.y = val6 << 0xB;
            item->rotY = record->quarterTurns << 0xA;
            item->unk_2C = record->unk_01;
            item->flags = record->flags;
            itemId = record->objectIndex;
            item->objectIndex = itemId;
            return context->tmd->vtbl->getModel(context->tmd, itemId, cellIndex, item);
        }
        return (ModelObject *)-1;
    }
    return 0;
}

MapModelsVtbl *MapModels_GetVtbl(void) {
    return &g_mapModelsVtbl;
}

static s32 func_8002C3B8(void) {
    return 0;
}

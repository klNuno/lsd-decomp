#include "common.h"
#include "game/loader.h"
#include "game/tmd.h"
#include "game/heap.h"
#include "game/model_object.h"
#include "game/file_base.h"

/*
 * Tmd: a TMD model file and its model objects (include/game/loader.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern void GsMapModelingData(u32 *p);
extern TmdVtbl g_tmdVtbl;

/* ---- TMD model ---- */

s32 Tmd_Create(s32 source) {
    s32 tmd;

    tmd = Heap_Alloc(0x30);
    if (tmd != 0) {
        if (Tmd_GetVtbl()->base.init(tmd, source) != 0) {
            return tmd;
        }
        Heap_Free(tmd);
    }
    return 0;
}

/* Slot 0x08: borrows source->data and parses it at once, or queues source->path; NULL on failure */
Tmd *Tmd_Init(Tmd *tmd, FileSource *source) {
    s32 data;
    TmdVtbl *vtbl;

    File_GetBackendVtbl()->init(tmd);
    vtbl = Tmd_GetVtbl();
    tmd->vtbl = vtbl;
    if (source != NULL) {
        data = source->data;
        if (data != 0) {
            tmd->data.addr = data;
            tmd->size = 0;
            if (tmd->vtbl->base.onLoaded(tmd) != 0) {
                goto fail;
            }
        } else {
            vtbl->base.loadAsync(tmd, source->path);
        }
    }
    return tmd;
fail:
    return NULL;
}

void Tmd_Destroy(Tmd *tmd) {
    Object **p;
    Object *model;

    for (p = tmd->models; *p != NULL; p++) {
        model = *p;
        model->vtbl->delete_(model);
    }
    Heap_Free((s32)tmd->models);
    File_GetBackendVtbl()->destroy(tmd);
}

/* Slot 0x64: maps the TMD and makes one model per TMD object; 1 on failure */
s32 Tmd_OnLoaded(Tmd *tmd) {
    Object **model;
    u32 i;

    model = (Object **)Heap_Alloc((tmd->data.header->objectCount + 1) * 4);
    if (model == NULL) {
        return 1;
    }
    tmd->models = model;
    tmd->vtbl->mapModelingData(tmd);
    for (i = 0; i < tmd->data.header->objectCount; i++) {
        *model = ModelObject_Create((s32)&tmd->data.header->objects[i]);
        if (*model == NULL) {
            while (i != 0) {
                model--;
                (*model)->vtbl->delete_(*model);
                i--;
            }
            Heap_Free((s32)model);
            return 1;
        }
        model++;
    }
    *model = NULL;
    File_GetBackendVtbl()->onLoaded(tmd);
    return 0;
}

void Tmd_MapModelingData(Tmd *tmd) {
    GsMapModelingData(tmd->data.words + 1);
}

/* Address of TMD object index (entries of 0x1C bytes from +0xC) */
s32 Tmd_GetObject(Tmd *tmd, s32 index) {
    s32 offset = index * 0x1C + 0xC;
    return offset + tmd->data.addr;
}

s32 Tmd_GetModel(Tmd *tmd, s32 index) {
    return (s32)tmd->models[index];
}

void Tmd_EmptySlot84(void) {
}

TmdVtbl *Tmd_GetVtbl(void) {
    return &g_tmdVtbl;
}

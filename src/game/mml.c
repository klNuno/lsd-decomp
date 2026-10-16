#include "common.h"
#include "game/mml.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/mom.h"

/*
 * Mml: the list of MOM models of a map square (include/game/mml.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern MomVtbl g_mmlVtbl;

Mml *Mml_Create(FileSource *source) {
    Mml *mml;

    mml = Heap_Alloc(0x3C);
    if (mml != NULL) {
        if (Mml_GetVtbl()->base.init(mml, source) == 0) {
            Heap_Free(mml);
            return NULL;
        }
        return mml;
    }
    return NULL;
}

Mml *Mml_Init(Mml *mml, FileSource *source) {
    MomVtbl *vtbl;

    Mom_GetVtbl()->base.init(mml, source, 0);
    vtbl = Mml_GetVtbl();
    mml->vtbl = vtbl;
    if (source->data != NULL) {
        if (vtbl->base.onLoaded(mml) != 0) {
            return NULL;
        }
    }
    return mml;
}

void Mml_Destroy(Mml *mml) {
    mml->vtbl->freeParts(mml);
    Mom_GetVtbl()->base.destroy(mml);
}

/* Slot 0x78 is called without arguments: a0 still holds mml */
void Mml_OnLoaded(Mml *mml) {
    mml->vtbl->loadParts();
}

/* Slot 0x78: one Mom per offset, written over the offset; 1 (Moms freed) on failure */
s32 Mml_LoadParts(Mml *mml) {
    FileSource source;
    Mom **entry;
    s32 count;
    s32 i;
    Mom *mom;

    File_MakeSource(&source, NULL, NULL, 1);
    entry = mml->data.header->table.moms;
    count = mml->data.header->count;
    mml->momCount = 0;
    for (i = 0; i < count; i++) {
        source.data = mml->data.bytes + mml->data.header->table.offsets[i];
        mom = Mom_Create(&source);
        *entry = mom;
        if (mom == NULL) {
            goto fail;
        }
        mml->momCount++;
        entry++;
    }
    return 0;
fail:
    mml->vtbl->freeParts(mml);
    return 1;
}

void Mml_FreeParts(Mml *mml) {
    Object_DeleteArray(mml->data.header->table.objects, mml->momCount);
    mml->momCount = 0;
}

/* Slot 0x88: Mom number index, 0 past the count */
Mom *Mml_GetMom(Mml *mml, u32 index) {
    MmlHeader *header = mml->data.header;

    if (index < header->count) {
        return header->table.moms[index];
    }
    return NULL;
}

MomVtbl *Mml_GetVtbl(void) {
    return &g_mmlVtbl;
}

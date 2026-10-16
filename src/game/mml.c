#include "common.h"
#include "game/loader.h"

/*
 * Mml: the list of MOM models of a map square (include/game/loader.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern void Object_DeleteArray(void *, s32);
extern void Heap_Free(s32);
extern s32 Heap_Alloc(s32 size);
FileSource *File_MakeSource(FileSource *source, s32 data, s32 path, s32 unk08);
MomVtbl *Mom_GetVtbl(void);
MomVtbl *Mml_GetVtbl(void);
s32 Mom_Create(s32 source);
extern MomVtbl g_mmlVtbl;

/* ---- MML: the MOM list of a map square ---- */

s32 Mml_Create(s32 source) {
    s32 mml;

    mml = Heap_Alloc(0x3C);
    if (mml != 0) {
        if (Mml_GetVtbl()->base.init(mml, source) == 0) {
            Heap_Free(mml);
            return 0;
        }
        return mml;
    }
    return 0;
}

Mml *Mml_Init(Mml *mml, FileSource *source) {
    MomVtbl *vtbl;

    Mom_GetVtbl()->base.init(mml, source, 0);
    vtbl = Mml_GetVtbl();
    mml->vtbl = vtbl;
    if (source->data != 0) {
        if (vtbl->base.onLoaded(mml) != 0) {
            return 0;
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
    s32 *entry;
    s32 count;
    s32 i;
    s32 mom;

    File_MakeSource(&source, 0, 0, 1);
    entry = &mml->data[2];
    count = mml->data[1];
    mml->momCount = 0;
    for (i = 0; i < count; i++) {
        source.data = (s32)((u8 *)mml->data + mml->data[i + 2]);
        mom = Mom_Create((s32)&source);
        *entry = mom;
        if (mom == 0) {
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
    Object_DeleteArray(mml->data + 2, mml->momCount);
    mml->momCount = 0;
}

/* Slot 0x88: Mom number index, 0 past the count */
u32 Mml_GetMom(Mml *mml, u32 index) {
    u32 *words = (u32 *)mml->data;

    if (index < words[1]) {
        return words[index + 2];
    }
    return 0;
}

MomVtbl *Mml_GetVtbl(void) {
    return &g_mmlVtbl;
}

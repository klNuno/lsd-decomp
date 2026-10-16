#include "common.h"
#include "game/tod_pack.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/tod.h"

/*
 * TodPack: a list of TOD files, the motions of a MOM (include/game/tod_pack.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern TodVtbl g_todPackVtbl;

s32 TodPack_Create(s32 source) {
    s32 todPack;

    todPack = Heap_Alloc(0x2C);
    if (todPack == 0) {
        return 0;
    }
    if (TodPack_GetVtbl()->base.init(todPack, source) != 0) {
        return todPack;
    }
    Heap_Free(todPack);
    return 0;
}

TodPack *TodPack_Init(TodPack *todPack, FileSource *source) {
    TodVtbl *vtbl;

    Tod_GetVtbl()->base.init(todPack, source);
    vtbl = TodPack_GetVtbl();
    todPack->vtbl = vtbl;
    if (source->data != 0) {
        if (vtbl->base.onLoaded(todPack) != 0) {
            return NULL;
        }
    }
    return todPack;
}

/* The offsets hold Tod objects once loaded */
void TodPack_Destroy(TodPack *todPack) {
    u32 *words = todPack->data.words;

    Object_DeleteArray(words + 2, words[1]);
    Tod_GetVtbl()->base.destroy(todPack);
}

/* Slot 0x64: one Tod per offset, written over the offset; 1 (Tods freed) on failure */
s32 TodPack_OnLoaded(TodPack *todPack) {
    FileSource source;
    TodPackHeader *header;
    Tod *tod;
    s32 i;
    s32 *out;
    s32 n;
    s32 made;

    File_MakeSource(&source, 0, 0, 1);
    out = todPack->data.header->offsets;
    n = todPack->data.header->count;
    for (i = 0; i < n; i++, out++) {
        header = todPack->data.header;
        source.data = (s32)header + header->offsets[i];
        made = Tod_Create((s32)&source);
        *out = made;
        if (made == 0) {
            while (i != 0) {
                out--;
                tod = (Tod *)*out;
                i--;
                tod->vtbl->base.delete_(tod);
            }
            return 1;
        }
    }
    return 0;
}

/* Slot 0x78: slot 0x7C on the first frame of the first TOD (past the offsets and its 8-byte header) */
s32 TodPack_ScanFirstFrame(TodPack *todPack, s32 ids, s32 tmdId) {
    return todPack->vtbl->scanFrame(todPack, ids, tmdId, &todPack->data.words[todPack->data.words[1]] + 4) & 0xFF;
}

TodVtbl *TodPack_GetVtbl(void) {
    return &g_todPackVtbl;
}

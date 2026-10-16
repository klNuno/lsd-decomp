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

TodPack *TodPack_Create(FileSource *source) {
    TodPack *todPack;

    todPack = Heap_Alloc(0x2C);
    if (todPack == NULL) {
        return NULL;
    }
    if (TodPack_GetVtbl()->base.init(todPack, source) != 0) {
        return todPack;
    }
    Heap_Free(todPack);
    return NULL;
}

TodPack *TodPack_Init(TodPack *todPack, FileSource *source) {
    TodVtbl *vtbl;

    Tod_GetVtbl()->base.init(todPack, source);
    vtbl = TodPack_GetVtbl();
    todPack->vtbl = vtbl;
    if (source->data != NULL) {
        if (vtbl->base.onLoaded(todPack) != 0) {
            return NULL;
        }
    }
    return todPack;
}

/* The offsets hold Tod objects once loaded */
void TodPack_Destroy(TodPack *todPack) {
    TodPackHeader *header = todPack->data.header;

    Object_DeleteArray(header->table.objects, header->count);
    Tod_GetVtbl()->base.destroy(todPack);
}

/* Slot 0x64: one Tod per offset, written over the offset; 1 (Tods freed) on failure */
s32 TodPack_OnLoaded(TodPack *todPack) {
    FileSource source;
    TodPackHeader *header;
    Tod *tod;
    s32 i;
    Tod **out;
    s32 n;
    Tod *made;

    File_MakeSource(&source, NULL, NULL, 1);
    out = todPack->data.header->table.tods;
    n = todPack->data.header->count;
    for (i = 0; i < n; i++, out++) {
        header = todPack->data.header;
        source.data = (u8 *)header + header->table.offsets[i];
        made = Tod_Create(&source);
        *out = made;
        if (made == NULL) {
            while (i != 0) {
                out--;
                tod = *out;
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

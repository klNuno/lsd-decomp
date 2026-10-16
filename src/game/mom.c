#include "common.h"
#include "game/mom.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/tmd.h"
#include "game/tod_pack.h"

/*
 * Mom: a MOM model file, a TMD and a TodPack (include/game/mom.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern MomVtbl g_momVtbl;

Mom *Mom_Create(FileSource *source) {
    Mom *mom;

    mom = Heap_Alloc(0x38);
    if (mom != NULL) {
        if (Mom_GetVtbl()->base.init(mom, source, 1) != 0) {
            return mom;
        }
        Heap_Free(mom);
    }
    return NULL;
}

Mom *Mom_Init(Mom *mom, FileSource *source, s32 hasParts) {
    MomVtbl *vtbl;
    u8 *data;

    File_GetBackendVtbl()->init(mom);
    mom->vtbl = Mom_GetVtbl();
    mom->hasParts = hasParts;
    data = source->data;
    if (data != NULL) {
        vtbl = mom->vtbl;
        mom->data.bytes = data;
        mom->size = 0;
        if (vtbl->base.onLoaded(mom) == 0) {
            return mom;
        }
    } else {
        mom->vtbl->base.loadAsync(mom, source->path);
        return mom;
    }
    return NULL;
}

/* Slot 0x7C is called without arguments: a0 still holds mom */
void Mom_Destroy(Mom *mom) {
    mom->vtbl->freeParts();
    File_GetBackendVtbl()->destroy(mom);
}

void Mom_OnLoaded(Mom *mom) {
    File_GetBackendVtbl()->onLoaded(mom);
    mom->vtbl->loadParts(mom);
}

/* Slot 0x78: the TMD at data + data[2] and the TodPack at data + 0xC; 1 (parts freed) on failure */
s32 Mom_LoadParts(Mom *mom) {
    FileSource source;
    Tmd *tmd;
    TodPack *motions;

    if (mom->hasParts != 0) {
        File_MakeSource(&source, mom->data.bytes + mom->data.header->tmdOffset, NULL, 1);
        tmd = Tmd_Create(&source);
        mom->tmd = tmd;
        if (tmd != NULL) {
            source.data = mom->data.bytes + sizeof(MomHeader);
            motions = TodPack_Create(&source);
            mom->motions = motions;
            if (motions != NULL) {
                return 0;
            }
            mom->motions = NULL;
        }
        mom->vtbl->freeParts(mom);
        return 1;
    }
    return 0;
}

void Mom_FreeParts(Mom *mom) {
    TodPack *motions;
    Tmd *tmd;

    if (mom->hasParts != 0) {
        motions = mom->motions;
        if (motions != NULL) {
            motions->vtbl->base.delete_(motions);
        }
        tmd = mom->tmd;
        if (tmd != NULL) {
            tmd->vtbl->base.delete_(tmd);
        }
    }
}

s32 Mom_ScanFirstFrame(Mom *mom) {
    TodPack *motions = mom->motions;

    return motions->vtbl->scanFirstFrame(motions);
}

void Mom_ReadPacket(Mom *mom, s32 packet, s32 id, s32 type, s32 flag, s32 length) {
    mom->motions->vtbl->readPacket(mom->motions, packet, id, type, flag, length);
}

MomVtbl *Mom_GetVtbl(void) {
    return &g_momVtbl;
}

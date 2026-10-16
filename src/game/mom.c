#include "common.h"
#include "game/loader.h"

/*
 * Mom: a MOM model file, a TMD and a TodPack (include/game/loader.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern void Heap_Free(s32);
extern s32 Heap_Alloc(s32 size);
FileVtbl *File_GetBackendVtbl(void);
FileSource *File_MakeSource(FileSource *source, s32 data, s32 path, s32 unk08);
MomVtbl *Mom_GetVtbl(void);
s32 Tmd_Create(s32 source);
s32 Mom_Create(s32 source);
s32 TodPack_Create(s32 source);
extern MomVtbl g_momVtbl;

/* ---- MOM model: a TMD and a TodPack ---- */

s32 Mom_Create(s32 source) {
    s32 mom;

    mom = Heap_Alloc(0x38);
    if (mom != 0) {
        if (Mom_GetVtbl()->base.init(mom, source, 1) != 0) {
            return mom;
        }
        Heap_Free(mom);
    }
    return 0;
}

Mom *Mom_Init(Mom *mom, FileSource *source, s32 hasParts) {
    MomVtbl *vtbl;
    s32 data;

    File_GetBackendVtbl()->init(mom);
    mom->vtbl = Mom_GetVtbl();
    mom->hasParts = hasParts;
    data = source->data;
    if (data != 0) {
        vtbl = mom->vtbl;
        mom->data = (u8 *)data;
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
    s32 tmd;
    s32 motions;

    if (mom->hasParts != 0) {
        File_MakeSource(&source, (s32)(mom->data + *(s32 *)(mom->data + 8)), 0, 1);
        tmd = Tmd_Create((s32)&source);
        mom->tmd = (Tmd *)tmd;
        if (tmd != 0) {
            source.data = (s32)(mom->data + 0xC);
            motions = TodPack_Create((s32)&source);
            mom->motions = (TodPack *)motions;
            if (motions != 0) {
                return 0;
            }
            mom->motions = 0;
        }
        mom->vtbl->freeParts(mom);
        return 1;
    }
    return 0;
}

void Mom_FreeParts(Mom *mom) {
    Object *part;

    if (mom->hasParts != 0) {
        part = (Object *)mom->motions;
        if (part != NULL) {
            part->vtbl->delete_(part);
        }
        part = (Object *)mom->tmd;
        if (part != NULL) {
            part->vtbl->delete_(part);
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

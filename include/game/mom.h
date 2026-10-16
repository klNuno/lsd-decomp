#ifndef GAME_MOM_H
#define GAME_MOM_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/tmd.h"
#include "game/tod_pack.h"

/*
 * MOM model (vtable g_momVtbl, 0x38 bytes, Mom_Create): ETC\SYMSPY.MOM and the models of
 * a map square. +0x8 is the offset of its TMD, its TodPack starts at +0xC.
 * MML (vtable g_mmlVtbl, 0x3C bytes, Mml_Create) derives from it: the model list of a map
 * square (LBD +0x10), {unk, count, offsets[count]} of MOM files, each replaced by a Mom object
 * at load; slot 0x88 returns one (Sym_SpawnGroup).
 */
typedef struct MomVtbl {
    FileVtbl base;
    s32 (*loadParts)();       /* 0x78 Mom Mom_LoadParts, Mml Mml_LoadParts */
    void (*freeParts)();      /* 0x7C Mom Mom_FreeParts, Mml Mml_FreeParts */
    s32 (*scanFirstFrame)();  /* 0x80 Mom_ScanFirstFrame: the TodPack's slot 0x78 */
    void (*readPacket)();     /* 0x84 Mom_ReadPacket: the TodPack's slot 0x80 */
    s32 (*getMom)();          /* 0x88 MML only: Mml_GetMom (self, index) */
} MomVtbl;

typedef struct Mom {
    MomVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    u8 *data;                 /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
    Tmd *tmd;                 /* 0x2C */
    TodPack *motions;         /* 0x30 */
    s32 hasParts;             /* 0x34 1 from Mom_Create, 0 for an MML */
} Mom;

/* Functions of src/game/mom.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Mom_Create(s32 source);
s32 Mom_ScanFirstFrame(Mom *mom);
void Mom_ReadPacket(Mom *mom, s32 packet, s32 id, s32 type, s32 flag, s32 length);
MomVtbl *Mom_GetVtbl(void);

#endif

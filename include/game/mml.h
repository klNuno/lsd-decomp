#ifndef GAME_MML_H
#define GAME_MML_H

#include "common.h"
#include "game/heap.h"
#include "game/mom.h"

typedef struct Mml {
    MomVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    s32 *data;                /* 0x10 {unk, count, offsets[count]}, then Mom objects */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x38 - 0x18];   /* Mom's tmd and motions stay NULL, hasParts 0 */
    s32 momCount;             /* 0x38 Mom objects made */
} Mml;

/* Functions of src/game/mml.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Mml_Create(s32 source);
MomVtbl *Mml_GetVtbl(void);

#endif

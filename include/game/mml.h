#ifndef GAME_MML_H
#define GAME_MML_H

#include "common.h"
#include "game/heap.h"
#include "game/mom.h"

typedef struct MmlHeader {
    s32 unk_00;
    u32 count;
    union {
        s32 offsets[1];       /* each MOM's offset from the start of the list */
        Mom *moms[1];         /* once loaded, written over the offsets */
        Object *objects[1];
    } table;
} MmlHeader;

typedef struct Mml {
    MomVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    union {
        MmlHeader *header;
        u8 *bytes;
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x38 - 0x18];   /* Mom's tmd and motions stay NULL, hasParts 0 */
    s32 momCount;             /* 0x38 Mom objects made */
} Mml;

/* Functions of src/game/mml.c that other files call or reference (docs/naming.md, Prototypes) */
Mml *Mml_Create(FileSource *source);
MomVtbl *Mml_GetVtbl(void);

#endif

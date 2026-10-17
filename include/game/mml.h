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
    MomVtbl *vtbl;            /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    union {
        MmlHeader *header;
        u8 *bytes;
    } data;                   /* 0x10 */
    s32 size;
    CdlLocDir cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
    Tmd *tmd;                 /* 0x2C to 0x37: Mom's fields (mom.h), NULL and 0 in an MML */
    TodPack *motions;
    s32 hasParts;
    s32 momCount;             /* 0x38 Mom objects made */
} Mml;

/* Functions of src/game/mml.c that other files call or reference (docs/naming.md, Prototypes) */
Mml *Mml_Create(FileSource *source);
MomVtbl *Mml_GetVtbl(void);

#endif

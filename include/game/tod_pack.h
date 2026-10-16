#ifndef GAME_TOD_PACK_H
#define GAME_TOD_PACK_H

#include "common.h"
#include "game/heap.h"
#include "game/tod.h"

typedef struct TodPackHeader {
    s32 unk_00;
    s32 count;
    union {
        s32 offsets[1];       /* each TOD's offset from the start of the pack */
        Tod *tods[1];         /* once loaded, written over the offsets */
        Object *objects[1];
    } table;
} TodPackHeader;

typedef struct TodPack {
    TodVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    union {
        TodPackHeader *header;
        u32 *words;
        u8 *bytes;
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
} TodPack;

/* Functions of src/game/tod_pack.c that other files call or reference (docs/naming.md, Prototypes) */
TodPack *TodPack_Create(FileSource *source);
TodVtbl *TodPack_GetVtbl(void);

#endif

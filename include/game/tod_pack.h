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
    TodVtbl *vtbl;            /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    union {
        TodPackHeader *header;
        u32 *words;
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
} TodPack;

/* Functions of src/game/tod_pack.c that other files call or reference (docs/naming.md, Prototypes) */
TodPack *TodPack_Create(FileSource *source);
TodVtbl *TodPack_GetVtbl(void);

#endif

#ifndef GAME_TOD_H
#define GAME_TOD_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * TOD animation file (vtable g_todVtbl, 0x2C bytes, Tod_Create): Sony TOD, an 8-byte file
 * header then frames {u16 size, u16 packetCount, u32 frame} of packets. A packet header word
 * holds the object id (bits 0 to 15), the type (16 to 19), the flag (20 to 23) and the length
 * in words (24 to 31): Tod_ReadPacket splits it. Type 8 flag 0 creates an object, type 2 gives
 * an object its TMD (u16 at +4).
 * TodPack (vtable g_todPackVtbl, 0x2C bytes, TodPack_Create) derives from it: {unk, count,
 * offsets[count]} of TOD files; onLoaded replaces each offset with a Tod object.
 */
typedef struct TodVtbl {
    FileVtbl base;
    u8 (*scanFirstFrame)();   /* 0x78 Tod Tod_ScanFirstFrame, TodPack TodPack_ScanFirstFrame (self, ids, tmdIndex) */
    s32 (*scanFrame)();       /* 0x7C Tod_ScanFrame (self, ids, tmdIndex, frame) */
    void (*readPacket)();     /* 0x80 Tod_ReadPacket (self, packet, &id, &type, &flag, &length) */
} TodVtbl;

typedef struct TodFrame {
    u16 size;
    u16 packetCount;
    u32 frame;
} TodFrame;

typedef struct TodPacket {
    u32 header;
    u16 tmdId;                /* type 2 packets */
} TodPacket;

typedef struct Tod {
    TodVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    s32 data;                 /* 0x10 the TOD file */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
} Tod;

/* Functions of src/game/tod.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Tod_Create(s32 source);
s32 Tod_ScanFrame(Tod *tod, u8 *ids, s32 *tmdId, void *packet);
u32 *Tod_ReadPacket(void *tod, u32 *packet, s8 *id, s8 *type, s8 *flag, s8 *length);
TodVtbl *Tod_GetVtbl(void);

#endif

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

/* A walk through the packets of a frame */
typedef union TodCursor {
    TodFrame *frame;
    TodPacket *packet;
    u32 *words;
} TodCursor;

/* The 8-byte header of a TOD file; the frames follow it */
typedef struct TodFileHeader {
    u32 id;                   /* 0x50, version, resolution */
    s32 frameCount;           /* 0x04 */
} TodFileHeader;

typedef struct Tod {
    TodVtbl *vtbl;            /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    union {
        u8 *bytes;
        TodFileHeader *header;
    } data;                   /* 0x10 the TOD file */
    s32 size;
    CdlLocDir cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
} Tod;

/* Functions of src/game/tod.c that other files call or reference (docs/naming.md, Prototypes) */
Tod *Tod_Create(FileSource *source);
s32 Tod_ScanFrame(Tod *tod, u8 *ids, s32 *tmdId, TodCursor packet);
u32 *Tod_ReadPacket(void *tod, u32 *packet, u8 *id, u8 *type, u8 *flag, u8 *length);
TodVtbl *Tod_GetVtbl(void);

#endif

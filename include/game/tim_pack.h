#ifndef GAME_TIM_PACK_H
#define GAME_TIM_PACK_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * TimPack (vtable g_timPackVtbl, 0x3C bytes, TimPack_Create): one part of a TIX, {count,
 * offsets[count]} then the TIM images. onLoaded makes a TIM object (Tim_New) per image,
 * borrowing its data, and points its +0x4C at the fade of its palette row.
 */
typedef struct TimPackVtbl {
    FileVtbl base;
    void (*uploadAll)();      /* 0x78 TimPack_UploadAll: slot 0x78 (upload to VRAM) of every TIM */
} TimPackVtbl;

typedef struct TimPack {
    TimPackVtbl *vtbl;        /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    union {
        u8 *bytes;
        s32 *words;           /* count, then count offsets from the start */
    } data;                   /* 0x10 */
    s32 size;
    CdlLOC cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;                /* 0x24 0x200: a load request (slot 0x58) is done (File_ServiceQueue) */
    u16 direct;
    u16 state;
    s32 count;                /* 0x2C TIM objects made */
    struct Tim **tims;     /* 0x30 */
    struct TixFade *fades;    /* 0x34 the owner's TixFade[4] (tix.h) */
    s32 loaded;               /* 0x38 */
} TimPack;

/* Functions of src/game/tim_pack.c that other files call or reference (docs/naming.md, Prototypes) */
TimPack *TimPack_Create(char *path);
TimPackVtbl *TimPack_GetVtbl(void);

#endif

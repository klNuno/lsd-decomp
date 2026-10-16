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
    TimPackVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    union {
        s32 addr;
        s32 *words;           /* count, then count offsets from the start */
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x24 - 0x18];
    s32 flags;                /* 0x24 0x200: a load request (slot 0x58) is done (File_ServiceQueue) */
    u8 pad_28[0x2C - 0x28];
    s32 count;                /* 0x2C TIM objects made */
    struct Tim **tims;     /* 0x30 */
    s32 fades;                /* 0x34 address of the owner's TixFade[4] */
    s32 loaded;               /* 0x38 */
} TimPack;

/* Functions of src/game/tim_pack.c that other files call or reference (docs/naming.md, Prototypes) */
s32 TimPack_Create(s32 path);
TimPackVtbl *TimPack_GetVtbl(void);

#endif

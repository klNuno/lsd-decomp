#ifndef GAME_TIM_H
#define GAME_TIM_H

#include "common.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/file_base.h"

/*
 * The TIM image class (vtable g_timVtbl, 0x50 bytes, Tim_New): a file object
 * (include/game/file_base.h) holding one TIM. Slot 0x78 uploads its pixels and its CLUT to VRAM
 * through the current display; slots 0x7C to 0x94 are empty. A TimPack makes one per image of
 * a TIX and points +0x4C at the fade of its palette row (src/game/tix.c).
 */
typedef struct TimVtbl {
    FileVtbl base;
    void (*upload)();         /* 0x78 Tim_Upload */
    void (*unk7C)();          /* 0x7C to 0x94: empty */
    void (*unk80)();
    void (*unk84)();
    void (*unk88)();
    void (*unk8C)();
    void (*unk90)();
    void (*unk94)();
    void (*setUnk48)();       /* 0x98 func_8003B5E4: +0x48 = 1 */
    void (*getInfo)(void *, void *); /* 0x9C Tim_GetInfo: GsGetTimInfo into a GsIMAGE */
} TimVtbl;

/* PSY-Q GsIMAGE, filled by GsGetTimInfo (slot 0x9C); the one GsIMAGE type of the game C */
typedef struct TimImage {
    u32 pmode;                /* 0x00 bit 3: the TIM has a CLUT */
    s16 px;                   /* 0x04 VRAM position of the pixels */
    s16 py;
    u16 pw;
    u16 ph;
    u32 *pixel;               /* 0x0C */
    s16 cx;                   /* 0x10 VRAM position of the CLUT; cy is its row */
    s16 cy;
    u16 cw;
    u16 ch;
    u32 *clut;                /* 0x18 */
} TimImage;

typedef struct Tim {
    TimVtbl *vtbl;            /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    union {
        u8 *bytes;
        u32 *words;           /* the TIM file: id word, then the TIM */
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 0 when the TIM is borrowed from a TimPack */
    CdlLOC cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
    TimImage image;           /* 0x2C filled by getInfo before each upload */
    s32 unk48;                /* 0x48 0 at init, 1 after slot 0x98; not read in this unit */
    struct TixFade *fade;     /* 0x4C the TixFade of its palette row (tix.h), NULL at init */
} Tim;

/* Functions of src/game/tim.c that other files call or reference (docs/naming.md, Prototypes) */
Tim *Tim_New(char *path);
TimVtbl *Tim_GetVtbl(void);
void Display_RotateRect(ScreenRect *rect, s32 count, ScreenRect *spare);

#endif

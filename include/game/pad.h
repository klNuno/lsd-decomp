#ifndef GAME_PAD_H
#define GAME_PAD_H

#include "common.h"
#include "game/heap.h"

/* The pad (vtable 0x8006D370, class word 2, src/game/pad.c, sender type 2): docs/discoveries.md, pad codes. */
typedef struct PadVtbl {
    s32 classWord;          /* 0x00 2 */
    void *(*delete_)();    /* 0x04 Object_Delete */
    void (*init)();        /* 0x08 Pad_Init (pad, padInitMode, padId) */
    void (*destroy)();     /* 0x0C Pad_Destroy */
    u8 pad_10[0x30 - 0x10];
    void (*notify)();      /* 0x30 Object_Notify: sends one code */
    u8 pad_34[0x40 - 0x34];
    void (*reset)();       /* 0x40 Pad_Reset (pad, padId) */
    void (*read)();        /* 0x44 Pad_Read */
    void (*send)();        /* 0x48 Pad_SendEvents */
    void (*unk4C)();       /* 0x4C Pad_EmptySlot4C, empty */
    void (*initButtons)(); /* 0x50 Pad_InitButtons */
    void (*unk54)();       /* 0x54 Pad_EmptySlot54, empty */
} PadVtbl;

typedef struct Pad {
    PadVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s16 padId;   /* 0x0C PadRead's argument, 0 or 1 */
    u8 pad_0E[0x10 - 0x0E];
    s32 held;    /* 0x10 the last PadRead */
    s32 released; /* 0x14 bits that went up this frame */
    s32 pressed; /* 0x18 bits that went down this frame */
} Pad;

/* The states of an event code (code = state + button index, 0 UP to 15 START, g_padButtonMasks). */
#define PAD_HELD 2
#define PAD_PRESSED 0x12  /* down this frame */
#define PAD_RELEASED 0x22 /* up this frame */

/* Functions of src/game/pad.c that other files call or reference (docs/naming.md, Prototypes) */
Pad *Pad_New(s32 padInitMode, s32 padId);

#endif

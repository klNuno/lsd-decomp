#ifndef GAME_BOX_H
#define GAME_BOX_H

#include "common.h"
#include "game/display.h"
#include "game/gs.h"

/* A box size as Box_Reset and Box_SetSize read it: two words, of which only the low halves count */
typedef struct BoxSize {
    u16 width;
    u16 pad_02;
    u16 height;
    u16 pad_06;
} BoxSize;

/*
 * Box (vtable g_boxVtbl at 0x8006EAC0, class word 0x64, 0x6C bytes): a scene node holding a PSY-Q
 * GsBOXF at +0x58. The scene draw (View_DrawNode, kind 0x64) places it at +0x50, in percent of the
 * half screen when +0x48 is set, and sorts it with GsSortBoxFill at the priority +0x44.
 */
typedef struct BoxVtbl {
    u8 pad_00[0x8];
    void (*init)(void *box, BoxSize *size, u8 *color, s32 priority); /* 0x08 Box_Init */
    u8 pad_0C[0x40 - 0xC];
    void (*reset)(void *box, BoxSize *size, u8 *color, s32 priority); /* 0x40 Box_Reset */
    u8 pad_44[0x4C - 0x44];
    void (*show)();                           /* 0x4C Box_Show (box, root, position) */
    u8 pad_50[0xB8 - 0x50];
    void (*setColor)(void *box, s32 copy, u8 *color); /* 0xB8 */
    void (*setPosition)(void *box, s32 position);    /* 0xBC */
    u8 pad_C0[0xCC - 0xC0];
    void (*setMask)(void *box, s32 bits);     /* 0xCC */
} BoxVtbl;

typedef struct Box {
    BoxVtbl *vtbl;
    u8 pad_04[0xC - 0x4];
    s32 parent;             /* 0x0C SceneNode *, set while the box is shown */
    u8 pad_10[0x44 - 0x10];
    s32 priority;           /* 0x44 ordering table priority given to GsSortBoxFill */
    s32 relative;           /* 0x48 position in percent of the half screen */
    s32 unk_4C;
    ScreenPoint position;       /* 0x50 */
    s32 attribute;          /* 0x58 GsBOXF: bit 31 hidden, bit 30 semi-transparent, bits 28-29 blend mode */
    u16 x;                  /* 0x5C GsBOXF, written by the draw from position */
    u16 y;                  /* 0x5E */
    u16 width;              /* 0x60 */
    u16 height;             /* 0x62 */
    Color3 color;              /* 0x64 */
    u8 pad_67;
    s32 mask;               /* 0x68 (1 << bits) - 1, 13 bits by default */
} Box;

/* Functions of src/game/box.c that other files call or reference (docs/naming.md, Prototypes) */
Box *Box_Create(BoxSize *size, u8 *color, s32 priority);
void Box_Show(Box *box, s32 root, s32 position);
s32 Box_SetVisible(Box *box, s32 visible);
void Box_SetSemiTrans(Box *box, s32 on);
void Box_SetBlendMode(Box *box, s32 mode);
void Box_SetColor(Box *box, s32 copy, Color3 *color);
void Box_SetPosition(Box *box, ScreenPoint *position);
void Box_SetSize(Box *box, BoxSize *size);
void Box_ShowAbsolute(Box *box, s32 root, s32 position, s32 value);
void Box_SetPriority(Box *box, s32 priority);
void Box_SetMask(Box *box, s32 bits);
BoxVtbl *Box_GetVtbl(void);

#endif

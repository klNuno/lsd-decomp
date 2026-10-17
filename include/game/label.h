#ifndef GAME_LABEL_H
#define GAME_LABEL_H

#include "common.h"
#include "game/tim.h"
#include "game/glyph.h"

/*
 * Label (vtable g_labelVtbl, class word 0x11144, 0xB8 bytes, src/game/label.c): a glyph that owns
 * a row of glyphs (src/game/glyph.c), one per character, laid out from its position with spacing
 * pixels between them. Label_Create makes the menu texts and the save title (menu.h Menu +0xB0).
 */
typedef struct LabelVtbl {
    u8 pad_00[0x4];
    void *(*delete_)();                       /* 0x04 Object_Delete */
    void (*init)(void *label, Tim *font, s32 count, char *text); /* 0x08 Label_Construct */
    u8 pad_0C[0x40 - 0xC];
    void (*reset)(void *label, char *text);   /* 0x40 Label_Init */
    u8 pad_44[0x4C - 0x44];
    void (*show)();                           /* 0x4C Label_Show (label, root, 2D position) */
    u8 pad_50[0xB8 - 0x50];
    void (*setColor)();                       /* 0xB8 Label_SetColor (label, color) */
    u8 pad_BC[0xC4 - 0xBC];
    void (*setChar)(void *label, s32 c, s32 index); /* 0xC4 Label_SetChar */
    u8 pad_C8[0xCC - 0xC8];
    void (*setText)(void *label, char *text); /* 0xCC Label_SetText */
    s32 unk_D0;
    void (*setSpacing)(void *label, s32 spacing); /* 0xD4 */
} LabelVtbl;

/* The first 0xA9 bytes are the glyph's (glyph.h Glyph); its own code at 0xA8 is the space under the row. */
typedef struct Label {
    LabelVtbl *vtbl;
    u8 pad_04[0xC - 0x4];
    s32 parent;             /* 0x0C */
    u8 pad_10[0xA9 - 0x10];
    u8 count;               /* 0xA9 glyphs, the longest text setText takes */
    u8 gapAt;               /* 0xAA when nonzero, 16 more pixels before this glyph */
    u8 shownCount;          /* 0xAB */
    u8 firstShown;          /* 0xAC */
    u8 pad_AD[0xB0 - 0xAD];
    s32 spacing;            /* 0xB0 */
    Glyph **glyphs;         /* 0xB4 */
} Label;

/* Functions of src/game/label.c that other files call or reference (docs/naming.md, Prototypes) */
Label *Label_Create(Tim *font, s32 count, char *text);

#endif

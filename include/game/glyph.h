#ifndef GAME_GLYPH_H
#define GAME_GLYPH_H

#include "common.h"
#include "game/screen_sprite.h"

/*
 * Glyph (vtable g_glyphVtbl 0x8006EC74, tag 0x1144, 0xAC bytes, src/game/glyph.c): a ScreenSprite
 * showing one 8x8 character of a font image laid out 32 characters per row; the base of Label.
 * Slots other files call with their own argument shapes are left unprototyped.
 */
struct Glyph;

typedef struct GlyphVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();                               /* 0x04 Object_Delete */
    void (*init)(void *glyph, Tim *font, s32 code);   /* 0x08 Glyph_Init */
    void (*destroy)();                                /* 0x0C SceneNode_Destroy */
    u8 pad_10[0x40 - 0x10];
    void (*setup)();                                  /* 0x40 Glyph_Setup (glyph, code) */
    u8 pad_44[0x4C - 0x44];
    void (*attach)();                                 /* 0x4C ScreenSprite_Attach (glyph, parent, 2D position) */
    void (*detach)();                                 /* 0x50 SceneNode_Detach */
    u8 pad_54[0x60 - 0x54];
    s32 (*setVisible)();                              /* 0x60 SpriteNode_SetVisible (glyph, visible) */
    u8 pad_64[0x78 - 0x64];
    void (*setZSort)();                               /* 0x78 SceneNode_SetZSort */
    u8 pad_7C[0xB8 - 0x7C];
    void (*setColor)();                               /* 0xB8 SpriteNode_SetColor (glyph, Color3) */
    void (*setPosition)();                            /* 0xBC ScreenSprite_SetPosition (glyph, 2D position) */
    u8 pad_C0[0xC4 - 0xC0];
    void (*setCode)(struct Glyph *glyph, u8 code);    /* 0xC4 Glyph_SetCode */
} GlyphVtbl;

/* The first 0xA8 bytes are the screen sprite's (screen_sprite.h ScreenSprite). */
typedef struct Glyph {
    GlyphVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C SceneNode *, 0 until attached */
    u8 pad_10[0x48 - 0x10]; /* the other SceneNode fields */
    TimImage *tim;          /* 0x48 */
    SpriteRect rect;        /* 0x4C */
    s32 unk58;              /* 0x58 */
    u8 pad_5C[0x64 - 0x5C];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0xA0 - 0x88];
    ScreenPoint position;   /* 0xA0 */
    u8 code;                /* 0xA8 the character shown */
} Glyph;

/* Functions of src/game/glyph.c that other files call or reference (docs/naming.md, Prototypes) */
Glyph *Glyph_Create(Tim *font, u8 code);
GlyphVtbl *Glyph_GetVtbl(void);

#endif

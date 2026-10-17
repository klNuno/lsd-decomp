#ifndef GAME_SCREEN_SPRITE_H
#define GAME_SCREEN_SPRITE_H

#include "common.h"
#include "game/display.h"
#include "game/sprite_node.h"

/*
 * ScreenSprite (vtable g_screenSpriteVtbl 0x8006ED4C, tag 0x144, 0xA8 bytes, src/game/screen_sprite.c):
 * a SpriteNode attached with a 2D position (slot 0x4C) and a pivot (slot 0xC0). The comment keyboard's
 * input box, the card menu's message and the list backgrounds; the base of Glyph. Slots other files
 * call with their own argument shapes are left unprototyped.
 */
typedef struct ScreenSpriteVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();                                    /* 0x04 Object_Delete */
    void (*init)(void *sprite, Tim *image, SpriteRect *rect, s32 unused); /* 0x08 ScreenSprite_Init */
    u8 pad_0C[0x40 - 0x0C];
    void (*setup)();                                       /* 0x40 ScreenSprite_Setup, empty */
    u8 pad_44[0x4C - 0x44];
    void (*attach)();                                      /* 0x4C ScreenSprite_Attach (sprite, parent, 2D position) */
    u8 pad_50[0x78 - 0x50];
    void (*setZSort)();                                    /* 0x78 SceneNode_SetZSort */
    u8 pad_7C[0xBC - 0x7C];
    void (*setPosition)();                                 /* 0xBC ScreenSprite_SetPosition (sprite, 2D position) */
    void (*setPivot)();                                    /* 0xC0 ScreenSprite_SetPivot */
} ScreenSpriteVtbl;

/* The first 0xA0 bytes are the sprite node's (sprite_node.h SpriteNode). */
typedef struct ScreenSprite {
    ScreenSpriteVtbl *vtbl;
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
    ScreenPoint position;   /* 0xA0 set once attached */
} ScreenSprite;

/* Functions of src/game/screen_sprite.c that other files call or reference (docs/naming.md, Prototypes) */
ScreenSprite *ScreenSprite_Create(Tim *image, SpriteRect *rect, s32 unused);
void ScreenSprite_Attach(ScreenSprite *sprite, s32 parent, ScreenPoint *position);
void ScreenSprite_SetPosition(ScreenSprite *sprite, ScreenPoint *position);
void ScreenSprite_SetPivot(ScreenSprite *sprite, s32 pivot);
ScreenSpriteVtbl *ScreenSprite_GetVtbl(void);

#endif

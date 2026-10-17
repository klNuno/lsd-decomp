#ifndef GAME_SPRITE_NODE_H
#define GAME_SPRITE_NODE_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/tim.h"
#include "game/scene_node.h"

/* The part of a TIM image cut into a sprite: copied whole. */
typedef struct SpriteRect {
    u16 u;
    u16 v;
    s32 w;
    s32 h;
} SpriteRect;

/*
 * SpriteNode (vtable g_spriteNodeVtbl 0x8006EE1C, tag 0x44, 0xA0 bytes, src/game/sprite_node.c): a
 * scene node (scene_node.h, base SceneNode_GetVtbl) that draws a libgs GsSPRITE cut from a TIM image;
 * its slots 0x60 to 0x68 work on the sprite's attribute word instead of the node's. The base of
 * ScreenSprite, Glyph and Label. The slots other files call, with the arguments they pass.
 */
typedef struct SpriteNodeVtbl {
    u8 pad_00[0x08];
    void (*init)(void *node, Tim *image, s32 blendRate, SpriteRect *rect, s32 unused4, s32 unused5); /* 0x08 SpriteNode_Init */
    u8 pad_0C[0x40 - 0x0C];
    void (*setImage)(void *node, Tim *image, s32 blendRate, SpriteRect *rect, s32 unused4, s32 unused5); /* 0x40 SpriteNode_SetImage */
    u8 pad_44[0x4C - 0x44];
    void (*attach)(void *node, s32 parent, void *position); /* 0x4C SceneNode_Attach (node, parent, Vec3 position) */
} SpriteNodeVtbl;

/* The first 0x44 bytes are the scene node's (scene_node.h SceneNode). */
typedef struct SpriteNode {
    SpriteNodeVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C SceneNode *, 0 until attached */
    u8 pad_10[0x48 - 0x10]; /* the other SceneNode fields */
    TimImage *tim;          /* 0x48 the GsIMAGE inside the image object (Tim.image) */
    SpriteRect rect;        /* 0x4C */
    s32 unk58;              /* 0x58 0 */
    u8 pad_5C[0x64 - 0x5C];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0xA0 - 0x88];
} SpriteNode;

/* Functions of src/game/sprite_node.c that other files call or reference (docs/naming.md, Prototypes) */
void SpriteNode_SetRotation(SpriteNode *node, s32 assign, Fraction *degrees);
s32 SpriteNode_SetVisible(SpriteNode *node, s32 visible);
void SpriteNode_SetSemiTrans(SpriteNode *node, s32 semiTrans);
void SpriteNode_SetBlendRate(SpriteNode *node, s32 blendRate);
void SpriteNode_OnClock(void);
void SpriteNode_SetColor(SpriteNode *node, Color3 *color);

#endif

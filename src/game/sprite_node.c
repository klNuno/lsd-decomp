#include "common.h"
#include "game/heap.h"
#include "game/scene.h"
#include "game/sprite_node.h"
#include "game/scene_node.h"

/*
 * SpriteNode: vtable g_spriteNodeVtbl 0x8006EE1C (tag 0x44), 0xA0 bytes, SpriteNode_Create. A scene
 * node (base SceneNode_GetVtbl, vtable 0x8006B5CC, tag 4) that draws a libgs GsSPRITE cut from a TIM
 * image; its slots 0x60 to 0x68 work on the sprite's attribute word instead of the node's.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* libgs GsSPRITE */
typedef struct Sprite {
    s32 attribute;  /* 0x00 bit 31 hidden, bit 30 semi-transparent, bits 28-29 blend rate, 24-25 color mode */
    u16 x;          /* 0x04 */
    u16 y;          /* 0x06 */
    u16 w;          /* 0x08 */
    u16 h;          /* 0x0A */
    u16 tpage;      /* 0x0C */
    u8 u;           /* 0x0E */
    u8 v;           /* 0x0F */
    u16 cx;         /* 0x10 CLUT */
    u16 cy;         /* 0x12 */
    Color3 color;   /* 0x14 0x80 neutral */
    u8 pad_17;
    s16 mx;         /* 0x18 rotation and scaling center */
    s16 my;         /* 0x1A */
    u16 scaleX;     /* 0x1C 0x1000 = 1 */
    u16 scaleY;     /* 0x1E */
    s32 rotate;     /* 0x20 degrees, 20.12 */
} Sprite;

/* The part of a TIM image cut into a sprite: copied whole. */
typedef struct SpriteRect {
    u16 u;
    u16 v;
    s32 w;
    s32 h;
} SpriteRect;

/* SpriteRect as SpriteNode_FillSprite reads it: bytes for u and v, halves for w and h. */
typedef struct SpriteRectBytes {
    u8 u;
    u8 pad_01;
    u8 v;
    u8 pad_03;
    u16 w;
    u16 pad_06;
    u16 h;
} SpriteRectBytes;

/* The start of the GsIMAGE of a TIM image object (at +0x2C), as SpriteNode_FillSprite reads it. */
typedef struct SpriteTim {
    s32 pmode;      /* 0x00 the low 2 bits are the color mode */
    s16 px;         /* 0x04 VRAM position of the pixels */
    s16 py;
    u8 pad_08[0x10 - 0x08];
    u16 cx;         /* 0x10 VRAM position of the CLUT */
    u16 cy;
} SpriteTim;

/* The rotation a scene node takes (base slot 0x44): 3 angles in degrees, each a fraction. */
typedef struct NodeAngles {
    Fraction x;
    Fraction y;
    Fraction z;
} NodeAngles;

struct SpriteNode;

/* Slots of g_spriteNodeVtbl this unit calls, with the arguments it passes. */
typedef struct SpriteNodeVtbl {
    u8 pad_00[0x08];
    void (*init)(void *, s32, s32, s32, s32, s32);     /* 0x08 SpriteNode_Init */
    u8 pad_0C[0x40 - 0x0C];
    void (*setImage)(void *, s32, s32, s32, s32, s32); /* 0x40 SpriteNode_SetImage */
    u8 pad_44[0x4C - 0x44];
    void (*attach)(void *, s32, void *);               /* 0x4C SceneNode_Attach (node, parent, Vec3 position) */
} SpriteNodeVtbl;

/* The first 0x18 bytes are the scene node's (scene.h SceneNode). */
typedef struct SpriteNode {
    SpriteNodeVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C SceneNode *, 0 until attached */
    u8 pad_10[0x48 - 0x10];
    s32 tim;                /* 0x48 SpriteTim *, the GsIMAGE inside the image object */
    SpriteRect rect;        /* 0x4C */
    s32 unk58;              /* 0x58 0 */
    u8 pad_5C[0x64 - 0x5C];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0xA0 - 0x88];
} SpriteNode;

/* the vtable of scene_node.c through this file's view of its slots, so not from game/scene_node.h */
ObjectVtbl *SceneNode_GetVtbl(void);
u16 GetTPage(s32 tp, s32 abr, s16 x, s16 y);
static void SpriteNode_FillSprite();
/* not in game/sprite_node.h: each file that calls it reads the vtable through its own view of the slots */
SpriteNodeVtbl *SpriteNode_GetVtbl(void);
extern SpriteNodeVtbl g_spriteNodeVtbl;

/* SpriteNode */

static void *SpriteNode_Create(s32 image, s32 blendRate, s32 rect, s32 arg3, s32 arg4) {
    void *node;

    node = Heap_Alloc(0xA0);
    if (node != 0) {
        SpriteNode_GetVtbl()->init(node, image, blendRate, rect, arg3, arg4);
        return node;
    }
    return 0;
}

/* Slot 0x08 */
void SpriteNode_Init(SpriteNode *node, s32 image, s32 blendRate, s32 rect, s32 arg4, s32 arg5) {
    SpriteNodeVtbl *vtbl;

    SceneNode_GetVtbl()->init(node);
    vtbl = SpriteNode_GetVtbl();
    node->vtbl = vtbl;
    vtbl->setImage(node, image, blendRate, rect, arg4, arg5);
}

/* Slot 0x40 (node, image object, blend rate, rect) */
void SpriteNode_SetImage(SpriteNode *node, s32 image, s32 blendRate, SpriteRect *rect) {
    node->tim = image + 0x2C;
    node->rect = *rect;
    SpriteNode_FillSprite(&node->sprite, blendRate, rect, node->tim);
    node->unk58 = 0;
}

/* Fills the sprite for the rect of the TIM: centered pivot, white, scale 1, no rotation. */
static void SpriteNode_FillSprite(Sprite *sprite, s32 blendRate, SpriteRectBytes *rect, SpriteTim *tim) {
    s32 colorMode;

    colorMode = tim->pmode;
    sprite->x = 0;
    sprite->y = 0;
    colorMode &= 3;
    sprite->attribute = colorMode << 0x18;
    sprite->w = rect->w;
    sprite->h = rect->h;
    sprite->mx = sprite->w >> 1;
    sprite->my = sprite->h >> 1;
    sprite->tpage = GetTPage(colorMode, blendRate, tim->px, tim->py);
    sprite->u = rect->u;
    sprite->v = rect->v;
    sprite->cx = tim->cx;
    sprite->cy = tim->cy;
    sprite->color.b = 0x80;
    sprite->color.g = 0x80;
    sprite->color.r = 0x80;
    sprite->rotate = 0;
    sprite->scaleX = 0x1000;
    sprite->scaleY = 0x1000;
}

/* Slot 0x44: a sprite only turns around z; assign 0 adds to the current angle. */
void SpriteNode_SetRotation(SpriteNode *node, s32 assign, NodeAngles *angles) {
    s32 rotate;

    rotate = ((angles->z.num / angles->z.den) << 12) + (((angles->z.num % angles->z.den) << 12) / angles->z.den);
    if (assign != 0) {
        node->sprite.rotate = rotate;
        return;
    }
    node->sprite.rotate = rotate + node->sprite.rotate;
}

/* Slot 0x60: returns whether it was visible. */
s32 SpriteNode_SetVisible(SpriteNode *node, s32 visible) {
    return Bits_SetField(&node->sprite.attribute, 0x1F, 1, visible == 0) == 0;
}

/* Slot 0x64 */
void SpriteNode_SetSemiTrans(SpriteNode *node, s32 semiTrans) {
    Bits_SetField(&node->sprite.attribute, 0x1E, 1, semiTrans != 0);
}

/* Slot 0x68 */
void SpriteNode_SetBlendRate(SpriteNode *node, s32 blendRate) {
    Bits_SetField(&node->sprite.attribute, 0x1C, 2, blendRate);
}

/* Slot 0x98, empty as in the base */
void SpriteNode_OnClock(void) {
}

/* Slot 0xB8 */
void SpriteNode_SetColor(SpriteNode *node, Color3 *color) {
    node->sprite.color = *color;
}

SpriteNodeVtbl *SpriteNode_GetVtbl(void) {
    return &g_spriteNodeVtbl;
}

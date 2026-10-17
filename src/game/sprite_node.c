#include "common.h"
#include "game/sprite_node.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/tim.h"
#include "psyq/libgpu.h"

/*
 * SpriteNode: vtable g_spriteNodeVtbl 0x8006EE1C (tag 0x44), 0xA0 bytes, SpriteNode_Create. A scene
 * node (base SceneNode_GetVtbl, vtable 0x8006B5CC, tag 4) that draws a libgs GsSPRITE cut from a TIM
 * image; its slots 0x60 to 0x68 work on the sprite's attribute word instead of the node's.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* SpriteRect as SpriteNode_FillSprite reads it: bytes for u and v, halves for w and h. Kept as a view:
   reading u and v as u16 would load them with lhu instead of lbu. */
typedef struct SpriteRectBytes {
    u8 u;
    u8 pad_01;
    u8 v;
    u8 pad_03;
    u16 w;
    u16 pad_06;
    u16 h;
} SpriteRectBytes;

/* not in game/scene_node.h: actor.c still reads this vtable through its own view of the slots */
SceneNodeVtbl *SceneNode_GetVtbl(void);
static void SpriteNode_FillSprite();
/* not in game/sprite_node.h: scenery_part.c still reads this vtable through its own view of the slots */
SpriteNodeVtbl *SpriteNode_GetVtbl(void);
extern SpriteNodeVtbl g_spriteNodeVtbl;

static SpriteNode *SpriteNode_Create(Tim *image, s32 blendRate, SpriteRect *rect, s32 unused4, s32 unused5) {
    SpriteNode *node;

    node = Heap_Alloc(0xA0);
    if (node != NULL) {
        SpriteNode_GetVtbl()->init(node, image, blendRate, rect, unused4, unused5);
        return node;
    }
    return NULL;
}

/* Slot 0x08 */
void SpriteNode_Init(SpriteNode *node, Tim *image, s32 blendRate, SpriteRect *rect, s32 unused4, s32 unused5) {
    SpriteNodeVtbl *vtbl;

    SceneNode_GetVtbl()->init(node);
    vtbl = SpriteNode_GetVtbl();
    node->vtbl = vtbl;
    vtbl->setImage(node, image, blendRate, rect, unused4, unused5);
}

/* Slot 0x40 (node, image object, blend rate, rect) */
void SpriteNode_SetImage(SpriteNode *node, Tim *image, s32 blendRate, SpriteRect *rect) {
    node->tim = &image->image;
    node->rect = *rect;
    SpriteNode_FillSprite(&node->sprite, blendRate, rect, node->tim);
    node->unk58 = 0;
}

/* Fills the sprite for the rect of the TIM: centered pivot, white, scale 1, no rotation. */
static void SpriteNode_FillSprite(Sprite *sprite, s32 blendRate, SpriteRectBytes *rect, TimImage *tim) {
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
void SpriteNode_SetRotation(SpriteNode *node, s32 assign, Fraction *degrees) {
    s32 rotate;

    rotate = ((degrees[2].num / degrees[2].den) << 12) + (((degrees[2].num % degrees[2].den) << 12) / degrees[2].den);
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

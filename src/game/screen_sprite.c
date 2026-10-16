#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/*
 * ScreenSprite: vtable g_screenSpriteVtbl 0x8006ED4C (tag 0x144), 0xA8 bytes, ScreenSprite_Create:
 * a SpriteNode (src/game/sprite_node.c) attached with a 2D position (slot 0x4C) and a pivot (slot
 * 0xC0). The comment keyboard's input box, the card menu's message and the list backgrounds.
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

/* Slots of g_spriteNodeVtbl this unit calls, with the arguments it passes. */
typedef struct SpriteNodeVtbl {
    u8 pad_00[0x08];
    void (*init)(void *, s32, s32, s32, s32, s32);     /* 0x08 SpriteNode_Init */
    u8 pad_0C[0x40 - 0x0C];
    void (*setImage)(void *, s32, s32, s32, s32, s32); /* 0x40 SpriteNode_SetImage */
    u8 pad_44[0x4C - 0x44];
    void (*attach)(void *, s32, void *);               /* 0x4C SceneNode_Attach (node, parent, Vec3 position) */
} SpriteNodeVtbl;

struct ScreenSprite;

typedef struct ScreenSpriteVtbl {
    u8 pad_00[0x08];
    void (*init)(void *, s32, SpriteRect *, s32);         /* 0x08 ScreenSprite_Init */
    u8 pad_0C[0x40 - 0x0C];
    void (*setup)(void *);                                /* 0x40 ScreenSprite_Setup, empty */
    u8 pad_44[0xBC - 0x44];
    void (*setPosition)(struct ScreenSprite *, ScreenPoint *); /* 0xBC ScreenSprite_SetPosition */
} ScreenSpriteVtbl;

typedef struct ScreenSprite {
    ScreenSpriteVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C */
    u8 pad_10[0x64 - 0x10];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0xA0 - 0x88];
    ScreenPoint position;   /* 0xA0 set once attached */
} ScreenSprite;

void *Heap_Alloc(s32 size);
ScreenSpriteVtbl *ScreenSprite_GetVtbl(void);
SpriteNodeVtbl *SpriteNode_GetVtbl(void);
extern ScreenSpriteVtbl g_screenSpriteVtbl;
extern s32 g_screenSpriteOrigin[3];          /* {0, 0, 0}: the Vec3 a screen sprite is attached at */

/* ScreenSprite */

void *ScreenSprite_Create(s32 image, SpriteRect *rect, s32 arg2) {
    void *sprite;

    sprite = Heap_Alloc(0xA8);
    if (sprite != 0) {
        ScreenSprite_GetVtbl()->init(sprite, image, rect, arg2);
        return sprite;
    }
    return 0;
}

/* Slot 0x08 */
void ScreenSprite_Init(ScreenSprite *sprite, s32 image, s32 rect, s32 arg3) {
    SpriteNode_GetVtbl()->init(sprite, image, 0, rect, 0, arg3);
    sprite->vtbl = ScreenSprite_GetVtbl();
    sprite->vtbl->setup(sprite);
}

/* Slot 0x40 */
void ScreenSprite_Setup(void) {
}

/* Slot 0x4C: attach to the parent node at the origin, then set the 2D position. */
void ScreenSprite_Attach(ScreenSprite *sprite, s32 parent, ScreenPoint *position) {
    if (sprite->parent == 0) {
        SpriteNode_GetVtbl()->attach(sprite, parent, g_screenSpriteOrigin);
        sprite->vtbl->setPosition(sprite, position);
    }
}

/* Slot 0xBC */
void ScreenSprite_SetPosition(ScreenSprite *sprite, ScreenPoint *position) {
    if (sprite->parent != 0) {
        sprite->position = *position;
    }
}

/* Slot 0xC0: the rotation and scaling center, 0 middle, 1 left, 2 right, 3 top, 4 bottom. */
void ScreenSprite_SetPivot(ScreenSprite *sprite, s32 pivot) {
    if (sprite->parent != 0) {
        switch (pivot) {
        case 0:
            sprite->sprite.mx = sprite->sprite.w >> 1;
            sprite->sprite.my = sprite->sprite.h >> 1;
            break;
        case 1:
            sprite->sprite.mx = 0;
            break;
        case 2:
            sprite->sprite.mx = sprite->sprite.w;
            break;
        case 3:
            sprite->sprite.my = 0;
            break;
        case 4:
            sprite->sprite.my = sprite->sprite.h;
            break;
        }
    }
}

ScreenSpriteVtbl *ScreenSprite_GetVtbl(void) {
    return &g_screenSpriteVtbl;
}

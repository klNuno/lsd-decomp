#include "common.h"
#include "game/screen_sprite.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/sprite_node.h"
#include "game/tim.h"

/*
 * ScreenSprite: vtable g_screenSpriteVtbl 0x8006ED4C (tag 0x144), 0xA8 bytes, ScreenSprite_Create:
 * a SpriteNode (src/game/sprite_node.c) attached with a 2D position (slot 0x4C) and a pivot (slot
 * 0xC0). The comment keyboard's input box, the card menu's message and the list backgrounds.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* not in game/sprite_node.h: scenery_part.c still reads this vtable through its own view of the slots */
SpriteNodeVtbl *SpriteNode_GetVtbl(void);
extern ScreenSpriteVtbl g_screenSpriteVtbl;
extern s32 g_screenSpriteOrigin[3];          /* {0, 0, 0}: the Vec3 a screen sprite is attached at */

ScreenSprite *ScreenSprite_Create(Tim *image, SpriteRect *rect, s32 unused) {
    ScreenSprite *sprite;

    sprite = Heap_Alloc(0xA8);
    if (sprite != NULL) {
        ScreenSprite_GetVtbl()->init(sprite, image, rect, unused);
        return sprite;
    }
    return NULL;
}

/* Slot 0x08 */
void ScreenSprite_Init(ScreenSprite *sprite, Tim *image, SpriteRect *rect, s32 unused) {
    SpriteNode_GetVtbl()->init(sprite, image, 0, rect, 0, unused);
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

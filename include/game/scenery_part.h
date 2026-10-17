#ifndef GAME_SCENERY_PART_H
#define GAME_SCENERY_PART_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"

/*
 * The scenery part class g_sceneryPartVtbl (0xC8 bytes of slots, checked against the .data dump),
 * built on SpriteNode's (sprite_node.h): the parts of kinds 2 and 3 of a scenery object (scenery_obj.h).
 * Slots 0x00 to 0xB4 carry SceneNodeVtbl's names (scene_node.h); 0xB8 is SpriteNode's, the rest
 * this class's empty slots. Kind 0 parts are Actors (actor.h), whose 0xB8 and 0xBC are setPos and movePos.
 */
typedef struct SceneryPartVtbl {
    u8 pad_00[0x08];
    void (*init)();           /* 0x08 SceneryPart_Construct (part, index, blendRate, font) */
    u8 pad_0C[0x40 - 0x0C];
    void (*reset)();          /* 0x40 SceneryPart_Init (part, index) */
    void (*setRotation)();    /* 0x44 SpriteNode_SetRotation */
    void (*setScale)();       /* 0x48 SceneryPart_SetScale */
    void (*attach)();         /* 0x4C SceneNode_Attach */
    u8 pad_50[0x60 - 0x50];
    void (*setVisible)();     /* 0x60 SpriteNode_SetVisible */
    void (*setSemiTrans)();   /* 0x64 SpriteNode_SetSemiTrans */
    void (*setBlendRate)();   /* 0x68 SpriteNode_SetBlendRate */
    u8 pad_6C[0xB8 - 0x6C];   /* 0x98 SceneryPart_EmptySlot98 */
    void (*setColor)();       /* 0xB8 SpriteNode_SetColor */
    void (*unkBC)();          /* 0xBC SceneryPart_EmptySlotBC */
    void (*unkC0)();          /* 0xC0 SceneryPart_EmptySlotC0 */
    void (*unkC4)();          /* 0xC4 SceneryPart_EmptySlotC4 */
} SceneryPartVtbl;

/*
 * A scenery part (0xA8 bytes, SceneryPart_New): a SpriteNode (0xA0 bytes, sprite_node.h) with an
 * index. Its sprite is SpriteNode.sprite at +0x64 (a GsSPRITE, gs.h Sprite).
 */
typedef struct SceneryPart {
    SceneryPartVtbl *vtbl;
    u8 pad_04[0x58 - 0x04];
    void *unk58;          /* 0x58 SpriteNode.unk58: slot 0x48 scales +0x5C and +0x60 while set, else the sprite's scale */
    s32 unk5C;
    s32 unk60;
    Sprite sprite;        /* 0x64 SpriteNode.sprite: cx, cy from g_sceneryPartCluts; rotate a random angle for kind 3 */
    u8 pad_88[0xA0 - 0x88];
    s32 index;            /* 0xA0 */
    s32 unkA4;
} SceneryPart;

/* Functions of src/game/scenery_part.c that other files call or reference (docs/naming.md, Prototypes) */
void *SceneryPart_New(s32 index, s32 blendRate, void *font);

#endif

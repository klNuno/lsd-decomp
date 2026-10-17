#include "common.h"
#include "game/scenery_part.h"
#include "game/heap.h"
#include "game/sprite_node.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/* CLUT position of each part in VRAM (SceneryPart_Reset). */
typedef struct SceneryPartClut { u16 x; u16 y; } SceneryPartClut;
extern SceneryPartClut g_sceneryPartCluts[];
static SceneryPartVtbl *SceneryPart_GetVtbl(void);
extern u8 g_sceneryPartRects[];
extern SceneryPartVtbl g_sceneryPartVtbl;

/* Allocate a scenery part of class g_sceneryPartVtbl (0xA8 bytes) for kinds 2 and 3. */
void *SceneryPart_New(s32 index, s32 blendRate, void *font) {
    void *part;

    part = Heap_Alloc(0xA8);
    if (part != NULL) {
        SceneryPart_GetVtbl()->init(part, index, blendRate, font);
        return part;
    }
    return NULL;
}

/* Slot 0x08 of g_sceneryPartVtbl: base construct with the font and the 12-byte entry g_sceneryPartRects[index]. */
void SceneryPart_Init(SceneryPart *part, s32 index, s32 blendRate, void *font) {
    SpriteNode_GetVtbl()->init(part, font, 0, (SpriteRect *)(g_sceneryPartRects + index * 0xC), blendRate, 0);
    part->vtbl = SceneryPart_GetVtbl();
    part->unkA4 = 0;
    part->vtbl->reset(part, index);
}

/* Slot 0x40 */
void SceneryPart_Reset(SceneryPart *part, s32 index) {
    part->index = index;
    part->sprite.cx = g_sceneryPartCluts[index].x;
    part->sprite.cy = g_sceneryPartCluts[index].y;
}

/* Slot 0x48: two 4.12 ratios from ratio[0] / ratio[1] and ratio[2] / ratio[3]. */
void SceneryPart_SetScale(SceneryPart *part, s32 assign, s16 *ratio) {
    s16 x;
    s16 y;

    x = ((ratio[0] / ratio[1]) << 12) + (((ratio[0] % ratio[1]) << 12) / ratio[1]);
    y = ((ratio[2] / ratio[3]) << 12) + (((ratio[2] % ratio[3]) << 12) / ratio[3]);
    if (part->unk58 != 0) {
        part->unk5C = (x * part->unk5C) >> 12;
        part->unk60 = (y * part->unk60) >> 12;
    } else {
        part->sprite.scaleX = x;
        part->sprite.scaleY = y;
    }
}

void SceneryPart_EmptySlot98(void) {
}

void SceneryPart_EmptySlotBC(void) {
}

void SceneryPart_EmptySlotC0(void) {
}

void SceneryPart_EmptySlotC4(void) {
}

static SceneryPartVtbl *SceneryPart_GetVtbl(void) {
    return &g_sceneryPartVtbl;
}

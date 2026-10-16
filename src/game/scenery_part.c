#include "common.h"
#include "game/scenery_part.h"
#include "game/heap.h"
#include "game/sprite_node.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/* The scenery part class g_sceneryPartVtbl (0xA8 bytes, SceneryPart_New), built on the class of SpriteNode_GetVtbl. */
typedef struct TextPartVtbl {
    u8 pad_00[0x08];
    void (*construct)();  /* 0x08 SceneryPart_Construct */
    u8 pad_0C[0x40 - 0x0C];
    void (*init)();       /* 0x40 SceneryPart_Init */
} TextPartVtbl;

typedef struct TextPart {
    TextPartVtbl *vt;
    u8 pad_04[0x58 - 0x04];
    void *unk58;          /* 0x58 slot 0x48 scales +0x5C and +0x60 while set, else stores the ratios at +0x80 */
    s32 unk5C;
    s32 unk60;
    u8 pad_64[0x74 - 0x64];
    u16 clutX;            /* 0x74 g_sceneryPartCluts[index].x */
    u16 clutY;            /* 0x76 g_sceneryPartCluts[index].y */
    u8 pad_78[0x80 - 0x78];
    s16 scaleX;
    s16 scaleY;
    u8 pad_84[0xA0 - 0x84];
    s32 index;            /* 0xA0 */
    s32 unkA4;
} TextPart;

/* The class SpriteNode_GetVtbl returns, base of TextPart. */
typedef struct TextPartBaseVtbl { u8 pad_00[0x8]; void (*construct)(void *, void *, s32, void *, s32, s32); } TextPartBaseVtbl;
/* CLUT position of each part in VRAM (SceneryPart_Init). */
typedef struct SceneryPartClut { u16 x; u16 y; } SceneryPartClut;
extern SceneryPartClut g_sceneryPartCluts[];
static TextPartVtbl *SceneryPart_GetVtbl(void);
extern u8 g_sceneryPartRects[];
/* the vtable of sprite_node.c through this file's view of its slots, so not from game/sprite_node.h */
TextPartBaseVtbl *SpriteNode_GetVtbl(void);
extern TextPartVtbl g_sceneryPartVtbl;

/* Allocate a scenery part of class g_sceneryPartVtbl (0xA8 bytes) for kinds 2 and 3. */
void *SceneryPart_New(s32 index, s32 blendRate, void *font) {
    void *part;

    part = Heap_Alloc(0xA8);
    if (part != NULL) {
        SceneryPart_GetVtbl()->construct(part, index, blendRate, font);
        return part;
    }
    return NULL;
}

/* Slot 0x08 of g_sceneryPartVtbl: base construct with the font and the 12-byte entry g_sceneryPartRects[index]. */
void SceneryPart_Construct(TextPart *part, s32 index, s32 blendRate, void *font) {
    SpriteNode_GetVtbl()->construct(part, font, 0, g_sceneryPartRects + index * 0xC, blendRate, 0);
    part->vt = SceneryPart_GetVtbl();
    part->unkA4 = 0;
    part->vt->init(part, index);
}

/* Slot 0x40 */
void SceneryPart_Init(TextPart *part, s32 index) {
    part->index = index;
    part->clutX = g_sceneryPartCluts[index].x;
    part->clutY = g_sceneryPartCluts[index].y;
}

/* Slot 0x48: two 4.12 ratios from ratio[0] / ratio[1] and ratio[2] / ratio[3]. */
void SceneryPart_SetScale(TextPart *part, s32 assign, s16 *ratio) {
    s16 x;
    s16 y;

    x = ((ratio[0] / ratio[1]) << 12) + (((ratio[0] % ratio[1]) << 12) / ratio[1]);
    y = ((ratio[2] / ratio[3]) << 12) + (((ratio[2] % ratio[3]) << 12) / ratio[3]);
    if (part->unk58 != 0) {
        part->unk5C = (x * part->unk5C) >> 12;
        part->unk60 = (y * part->unk60) >> 12;
    } else {
        part->scaleX = x;
        part->scaleY = y;
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

static TextPartVtbl *SceneryPart_GetVtbl(void) {
    return &g_sceneryPartVtbl;
}

#include "common.h"
#include "game/box.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"

/*
 * Box: a filled rectangle, a 2D widget drawn by the scene tree (src/game/scene_draw.c).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* not in game/scene_node.h: actor.c still reads this vtable through its own view of the slots */
SceneNodeVtbl *SceneNode_GetVtbl(void);

extern u8 g_boxDefaultColor[];     /* the default box color, (128, 128, 128) */
static void Rgb_CopyOrAdd(void *box, Color3 *dst, Color3 *src, s32 copy);
extern BoxVtbl g_boxVtbl;

/* new Box(size, color, priority) */
Box *Box_Create(BoxSize *size, u8 *color, s32 priority) {
    Box *box;

    box = Heap_Alloc(0x6C);
    if (box != NULL) {
        Box_GetVtbl()->init(box, size, color, priority);
        return box;
    }
    return NULL;
}

/* Slot 0x08: base scene node init, then the Box vtable and slot 0x40 */
void Box_Construct(void **box, BoxSize *size, u8 *color, s32 priority) {
    BoxVtbl *vtbl;

    SceneNode_GetVtbl()->init(box);
    vtbl = Box_GetVtbl();
    *box = vtbl;
    vtbl->reset(box, size, color, priority);
}

/* Slot 0x40: relative position (0, 0), the size, the color or the default gray, mask of 13 bits */
void Box_Init(Box *box, BoxSize *size, u8 *color, s32 priority) {
    BoxVtbl *vtbl;

    box->priority = priority;
    box->relative = 1;
    box->unk_4C = 0;
    box->attribute = 0;
    box->x = 0;
    box->y = 0;
    box->width = size->width;
    box->height = size->height;
    vtbl = box->vtbl;
    if (color == NULL) {
        color = g_boxDefaultColor;
    }
    vtbl->setColor(box, 1, color);
    box->vtbl->setMask(box, 0xD);
}

/* Slot 0x4C: attaches the box under root once, then places it */
void Box_Show(Box *box, s32 root, s32 position) {
    if (box->parent == 0) {
        SceneNode_GetVtbl()->attach(box, root, 0);
        box->vtbl->setPosition(box, position);
    }
}

/* Slot 0x60: shows or hides the box (GsBOXF bit 31), returns whether it was shown */
s32 Box_SetVisible(Box *box, s32 visible) {
    return Bits_SetField(&box->attribute, 0x1F, 1, visible == 0) == 0;
}

/* Slot 0x64: semi-transparency on or off (GsBOXF bit 30) */
void Box_SetSemiTrans(Box *box, s32 on) {
    Bits_SetField(&box->attribute, 0x1E, 1, on != 0);
}

/* Slot 0x68: the semi-transparency mode (GsBOXF bits 28-29: 1 adds, 2 subtracts) */
void Box_SetBlendMode(Box *box, s32 mode) {
    Bits_SetField(&box->attribute, 0x1C, 2, mode);
}

/* Slot 0xB8: copies the color, or adds it when copy is 0 */
void Box_SetColor(Box *box, s32 copy, Color3 *color) {
    Rgb_CopyOrAdd(box, &box->color, color, copy);
}

static void Rgb_CopyOrAdd(void *box, Color3 *dst, Color3 *src, s32 copy) {
    if (copy != 0) {
        *dst = *src;
        return;
    }
    dst->r += src->r;
    dst->g += src->g;
    dst->b += src->b;
}

/* Slot 0xBC: moves a shown box */
void Box_SetPosition(Box *box, ScreenPoint *position) {
    if (box->parent != 0) {
        box->position = *position;
    }
}

/* Slot 0xC0: resizes a shown box (size read as u16 halves) */
void Box_SetSize(Box *box, BoxSize *size) {
    if (box->parent != 0) {
        box->width = size->width;
        box->height = size->height;
    }
}

/* Slot 0xC4: shows the box (root and position passed through), then clears the percent flag */
void Box_ShowAbsolute(Box *box, s32 root, s32 position, s32 value) {
    box->vtbl->show();
    box->relative = 0;
    box->unk_4C = value;
}

/* Slot 0xC8 */
void Box_SetPriority(Box *box, s32 priority) {
    box->priority = priority;
}

/* Slot 0xCC */
void Box_SetMask(Box *box, s32 bits) {
    box->mask = (1 << bits) - 1;
}

BoxVtbl *Box_GetVtbl(void) {
    return &g_boxVtbl;
}

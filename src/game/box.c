#include "common.h"
#include "game/scene.h"

/*
 * Box: a filled rectangle, a 2D widget drawn by the scene tree (src/game/scene_draw.c).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* An (x, y) pair of s32 */
/* A bit field setter of src/game/scene_node.c: sets width bits at shift in *word, returns the old value */
s32 Bits_SetField(s32 *word, s32 shift, s32 width, s32 value);
void *Heap_Alloc(s32 size);

/* The base scene node class (SceneNode_GetVtbl, src/game/scene_node.c), as Box calls it */
typedef struct BaseNodeVtbl {
    u8 pad_00[0x8];
    void (*init)(void *box);                  /* 0x08 */
    u8 pad_0C[0x4C - 0xC];
    void (*show)(void *box, s32 root, s32 position); /* 0x4C */
} BaseNodeVtbl;
BaseNodeVtbl *SceneNode_GetVtbl(void);

/*
 * Box (vtable g_boxVtbl at 0x8006EAC0, class word 0x64, 0x6C bytes): a scene node holding a PSY-Q
 * GsBOXF at +0x58. The scene draw (Scene_DrawNode, kind 0x64) places it at +0x50, in percent of the
 * half screen when +0x48 is set, and sorts it with GsSortBoxFill at the priority +0x44.
 */
typedef struct BoxVtbl {
    u8 pad_00[0x8];
    void (*init)(void *box, s32 size, u8 *color, s32 priority); /* 0x08 Box_Construct */
    u8 pad_0C[0x40 - 0xC];
    void (*reset)(void *box, s32 size, s32 color, s32 priority); /* 0x40 Box_Init */
    u8 pad_44[0x4C - 0x44];
    void (*show)();                           /* 0x4C Box_Show (box, root, position) */
    u8 pad_50[0xB8 - 0x50];
    void (*setColor)(void *box, s32 copy, u8 *color); /* 0xB8 */
    void (*setPosition)(void *box, s32 position);    /* 0xBC */
    u8 pad_C0[0xCC - 0xC0];
    void (*setMask)(void *box, s32 bits);     /* 0xCC */
} BoxVtbl;

typedef struct Box {
    BoxVtbl *vtbl;
    u8 pad_04[0xC - 0x4];
    s32 parent;             /* 0x0C SceneNode *, set while the box is shown */
    u8 pad_10[0x44 - 0x10];
    s32 priority;           /* 0x44 ordering table priority given to GsSortBoxFill */
    s32 relative;           /* 0x48 position in percent of the half screen */
    s32 unk_4C;
    ScreenPoint position;       /* 0x50 */
    s32 attribute;          /* 0x58 GsBOXF: bit 31 hidden, bit 30 semi-transparent, bits 28-29 blend mode */
    u16 x;                  /* 0x5C GsBOXF, written by the draw from position */
    u16 y;                  /* 0x5E */
    u16 width;              /* 0x60 */
    u16 height;             /* 0x62 */
    Color3 color;              /* 0x64 */
    u8 pad_67;
    s32 mask;               /* 0x68 (1 << bits) - 1, 13 bits by default */
} Box;

extern u8 g_boxDefaultColor[];     /* the default box color, (128, 128, 128) */
BoxVtbl *Box_GetVtbl(void);
void Rgb_CopyOrAdd(void *box, Color3 *dst, Color3 *src, s32 copy);
extern u8 g_boxVtbl[];

/* new Box(size, color, priority) */
void *Box_Create(s32 size, s32 color, s32 priority) {
    void *box;

    box = Heap_Alloc(0x6C);
    if (box != NULL) {
        Box_GetVtbl()->init(box, size, color, priority);
        return box;
    }
    return NULL;
}

/* Slot 0x08: base scene node init, then the Box vtable and slot 0x40 */
void Box_Construct(void **box, s32 size, s32 color, s32 priority) {
    BoxVtbl *vtbl;

    SceneNode_GetVtbl()->init(box);
    vtbl = Box_GetVtbl();
    *box = vtbl;
    vtbl->reset(box, size, color, priority);
}

/* Slot 0x40: relative position (0, 0), the size, the color or the default gray, mask of 13 bits */
void Box_Init(Box *box, u16 *size, u8 *color, s32 priority) {
    BoxVtbl *vtbl;

    box->priority = priority;
    box->relative = 1;
    box->unk_4C = 0;
    box->attribute = 0;
    box->x = 0;
    box->y = 0;
    box->width = size[0];
    box->height = size[2];
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
        SceneNode_GetVtbl()->show(box, root, 0);
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
void Box_SetColor(Box *box, s32 copy, u8 *color) {
    Rgb_CopyOrAdd(box, &box->color, color, copy);
}

void Rgb_CopyOrAdd(void *box, Color3 *dst, Color3 *src, s32 copy) {
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
void Box_SetSize(Box *box, u16 *size) {
    if (box->parent != 0) {
        box->width = size[0];
        box->height = size[2];
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
    return (BoxVtbl *)g_boxVtbl;
}

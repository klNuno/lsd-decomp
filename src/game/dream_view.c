#include "common.h"

/*
 * DreamView (vtable g_dreamViewVtbl 0x800869D8): the dream camera, a View subclass of 0xDC bytes.
 *
 * File boundaries: likely (docs/layout.md)
 */

extern u8 g_dreamViewVtbl[];

/* The 0xDC object of class 0x800869D8 (DreamView_New); slot 0xA0 is Scene_DrawNode, which draws scene nodes. */
typedef struct RenderObjVtbl {
    u8 pad_00[0x08];
    void (*init)();             /* 0x08 */
    u8 pad_0C[0x40 - 0x0C];
    void (*unk40)();            /* 0x40 */
    u8 pad_44[0x9C - 0x44];
    void (*unk9C)();            /* 0x9C */
} RenderObjVtbl;

typedef struct RenderObj {
    RenderObjVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    s32 unk10;
    u8 pad_14[0x70 - 0x14];
    s32 unk70;
} RenderObj;

s32 Heap_Alloc(s32 size);
RenderObjVtbl *View_GetVtbl(void);
RenderObjVtbl *DreamView_GetVtbl(void);
s32 DreamView_New(void);

s32 DreamView_New(void) {
    s32 obj;

    obj = Heap_Alloc(0xDC);
    if (obj != 0) {
        DreamView_GetVtbl()->init(obj);
        return obj;
    }
    return 0;
}

void DreamView_Init(void **obj) {
    RenderObjVtbl *vtbl;

    View_GetVtbl()->init(obj);
    vtbl = DreamView_GetVtbl();
    *obj = vtbl;
    vtbl->unk40(obj);
}

void DreamView_Reset(void) {
}

void DreamView_Render(RenderObj *obj) {
    if ((obj->unk10 != 0) && (obj->unk70 != 0)) {
        View_GetVtbl()->unk9C(obj);
    }
}

void DreamView_EmptySlotB8(void) {
}

void DreamView_EmptySlotBC(void) {
}

void DreamView_EmptySlotC0(void) {
}

void DreamView_EmptySlotC4(void) {
}

RenderObjVtbl *DreamView_GetVtbl(void) {
    return (RenderObjVtbl *)g_dreamViewVtbl;
}

#include "common.h"
#include "game/dream_view.h"
#include "game/heap.h"
#include "game/view.h"

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
    void (*reset)();            /* 0x40 */
    u8 pad_44[0x9C - 0x44];
    void (*render)();            /* 0x9C */
} RenderObjVtbl;

typedef struct RenderObj {
    RenderObjVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    s32 node;
    u8 pad_14[0x70 - 0x14];
    s32 otReady;
} RenderObj;

/* the vtable of view.c through this file's view of its slots, so not from game/view.h */
RenderObjVtbl *View_GetVtbl(void);
static RenderObjVtbl *DreamView_GetVtbl(void);

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
    vtbl->reset(obj);
}

void DreamView_Reset(void) {
}

void DreamView_Render(RenderObj *obj) {
    if ((obj->node != 0) && (obj->otReady != 0)) {
        View_GetVtbl()->render(obj);
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

static RenderObjVtbl *DreamView_GetVtbl(void) {
    return (RenderObjVtbl *)g_dreamViewVtbl;
}

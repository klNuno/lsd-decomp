#include "common.h"
#include "game/dream_view.h"
#include "game/heap.h"
#include "game/view.h"

/*
 * DreamView (vtable g_dreamViewVtbl 0x800869D8): the dream camera, a View subclass of 0xDC bytes.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The 0xDC object of class 0x800869D8 (DreamView_New): a View whose slots 0xB8 to 0xC4 are empty. */
extern ViewVtbl g_dreamViewVtbl;

/* the vtable of view.c, not in game/view.h */
ViewVtbl *View_GetVtbl(void);
static ViewVtbl *DreamView_GetVtbl(void);

View *DreamView_New(void) {
    View *obj;

    obj = Heap_Alloc(0xDC);
    if (obj != NULL) {
        DreamView_GetVtbl()->init(obj);
        return obj;
    }
    return NULL;
}

void DreamView_Init(void **obj) {
    ViewVtbl *vtbl;

    View_GetVtbl()->init(obj);
    vtbl = DreamView_GetVtbl();
    *obj = vtbl;
    vtbl->reset(obj);
}

void DreamView_Reset(void) {
}

void DreamView_Render(View *obj) {
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

static ViewVtbl *DreamView_GetVtbl(void) {
    return &g_dreamViewVtbl;
}

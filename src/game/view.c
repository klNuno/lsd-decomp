#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/*
 * View (include/game/scene.h): the 3D view (vtable 0x8006E8E4): GsRVIEW2, double ordering tables,
 * fog and light mode.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* View_SetTwist's argument: rz = num / den in 4.12 fixed point. */
typedef struct ViewRatio {
    s16 num;
    s16 den;
} ViewRatio;

ObjectVtbl *Object_GetBaseVtbl(void);
void *Heap_Alloc(s32 size);
void Heap_Free(void *);
extern s32 DrawSync(s32);
extern void SetGeomScreen(s32);
void GsSetRefView2(void *);
void ResetGraph(s32 mode);
void GsSortClear(u8 r, u8 g, u8 b, GsOT *ot);
void GsDrawOt(GsOT *ot);
void GsClearOt(s32, s32, GsOT *);
void GsSetLightMode(s32);
void SetFarColor(u8, u8, u8);
void SetFogNear(s32, s32);
void func_8003FB0C(s32);
void func_8003FBE4(void *packets);
SceneNode *SceneNode_New(void);
void *Fade_Create(s32, s32, s32);
View *View_New(void);
ViewVtbl *View_GetVtbl(void);
SceneNode *SceneNode_GetRoot(SceneNode *node);
void View_SetGeomScreen(s32 projection);
extern ViewVtbl g_viewVtbl[];   /* View */
extern s32 g_viewNoTwist;          /* ViewRatio (0, 1): no twist */
extern Color3 g_viewDefaultColor;       /* black */
/* .sdata owned by this unit (config/splat.yaml), defined at the end of the file: read whole by View_Reset */
extern ScreenPoint g_viewDefaultScreenSize;
extern s32 g_overlayPos;          /* ScreenPoint (-100, -100): where the overlay hangs */
extern s32 g_overlaySize;          /* the overlay: 320, 240, 10, 10 */

/* View */

View *View_New(void) {
    View *view;

    view = Heap_Alloc(0xBC);
    if (view != NULL) {
        View_GetVtbl()->init(view);
        return view;
    }
    return NULL;
}

void View_Init(View *view) {
    Fade *overlay;

    Object_GetBaseVtbl()->init(view);
    view->vtbl = View_GetVtbl();
    view->display = 0;
    view->node = 0;
    view->root = SceneNode_New();
    overlay = Fade_Create((s32)&g_overlaySize, 0, 0);
    view->overlay = overlay;
    overlay->vtbl->show(overlay, view->root, &g_overlayPos);
    view->vtbl->reset(view);
}

void View_Destroy(View *view) {
    SceneNode *root;

    view->vtbl->freeOt();
    view->vtbl->detach(view);
    root = view->root;
    root->vtbl->delete_(root);
    view->vtbl->setOverlay(view, 0);
    Object_GetBaseVtbl()->destroy(view);
}

/* Watching a display draws for it; watching a scene node takes its coordinate as the view's super. */
void View_Watch(View *view, Object *other) {
    s32 type;

    Object_GetBaseVtbl()->watch(view, other);
    type = other->vtbl->classWord & 0xF;
    if (type == 4) {
        view->node = (SceneNode *)other;
        view->super = ((SceneNode *)other)->coord;
    } else if (type == 1) {
        view->display = (Display *)other;
    }
}

void View_Unwatch(View *view, Object *other) {
    s32 type;

    type = other->vtbl->classWord & 0xF;
    if (type == 4) {
        view->super = 0;
        view->node = 0;
    } else if (type == 1) {
        view->display = 0;
    }
    Object_GetBaseVtbl()->unwatch(view, other);
}

void View_UnwatchAll(View *view) {
    view->super = 0;
    view->node = 0;
    view->display = 0;
    Object_GetBaseVtbl()->unwatchAll(view);
}

void View_OnNotify(View *view, Object *sender, s32 message) {
    s32 type;

    Object_GetBaseVtbl()->onNotify(view, sender, message);
    type = sender->vtbl->classWord & 0xF;
    if (type == 5) {
        view->vtbl->onClock(view, sender, message);
    } else if (type == 1) {
        view->vtbl->onDisplay(view, sender, message);
    }
}

void View_Reset(View *view) {
    view->clockCount = 0;
    view->otReady = 0;
    view->screenSize = g_viewDefaultScreenSize;
    view->otBits = 0xD;
    view->packetCount = 0x7D0;
    view->packetSize = 0x40;
    view->projection = 0x100;
    view->nearZ = 0xA;
    view->farZ = 0x10000;
    view->lightMode = 0;
    view->fogNear = 0x4E20;
    view->fogColor = g_viewDefaultColor;
    view->clearColor = g_viewDefaultColor;
    view->unkB4 = 0;
    view->unkB8 = 1;
}

void View_SetScreenSize(View *view, ScreenPoint *value) {
    view->screenSize = *value;
}

void View_SetOtBits(View *view, s32 otBits) {
    view->otBits = otBits;
}

/* The packet sizes only change while the ordering tables are not allocated. */
void View_SetPacketCount(View *view, s32 packetCount) {
    if (view->otReady == 0) {
        view->packetCount = packetCount;
    }
}

void View_SetPacketSize(View *view, s32 packetSize) {
    if (view->otReady == 0) {
        view->packetSize = packetSize;
    }
}

void View_SetProjection(View *view, s32 projection) {
    view->projection = projection;
}

void View_EmptySlot58(void) {
}

void View_EmptySlot5C(void) {
}

void View_SetLightMode(View *view, s32 lightMode) {
    view->lightMode = lightMode;
}

void View_SetClearColor(View *view, Color3 *color) {
    view->clearColor = *color;
}

void View_SetFogColor(View *view, Color3 *color) {
    view->fogColor = *color;
}

void View_SetFogNear(View *view, s32 fogNear) {
    view->fogNear = fogNear;
}

/* Only when no node is watched yet: watches node, sets viewpoint, reference point and twist. */
void View_SetCamera(View *view, SceneNode *node, ScreenVec *viewpoint, ScreenVec *refPoint, ViewRatio *twist) {
    ViewVtbl *vtbl;
    ViewRatio *ratio;

    vtbl = view->vtbl;
    if (view->node == 0) {
        vtbl->watch(); /* (view, node): both are still in the argument registers */
        vtbl->setViewpoint(view, viewpoint);
        vtbl->setRefPoint(view, refPoint);
        ratio = twist;
        if (ratio == NULL) {
            ratio = (ViewRatio *)&g_viewNoTwist;
        }
        vtbl->setTwist(view, ratio);
        GsSetRefView2(&view->viewpoint);
    }
}

void View_Detach(View *view) {
    SceneNode *node = view->node;
    if (node != 0) {
        view->vtbl->unwatch(view, node);
    }
}

void View_SetViewpoint(View *view, ScreenVec *viewpoint) {
    if (view->node != 0) {
        view->viewpoint = *viewpoint;
    }
}

void View_SetRefPoint(View *view, ScreenVec *refPoint) {
    if (view->node != 0) {
        view->refPoint = *refPoint;
    }
}

void View_SetTwist(View *view, ViewRatio *ratio) {
    s16 num;
    s16 den;

    if (view->node != 0) {
        num = ratio->num;
        den = ratio->den;
        view->twist = ((num / den) << 12) + (((num % den) << 12) / den);
    }
}

void View_EmptySlot84(void) {
}

void View_EmptySlot88(void) {
}

/*
 * One heap block for both buffers, each: a GsOT header (0x14 bytes), 2^otBits entries, then
 * packetCount x packetSize bytes of GPU packets.
 */
void View_AllocOt(View *view) {
    s32 size;
    u8 *block;

    if (view->otReady == 0) {
        size = 0x14 + (4 << view->otBits) + view->packetSize * view->packetCount;
        block = (u8 *) Heap_Alloc(size * 2);
        if (block != NULL) {
            view->ot[0] = (GsOT *) block;
            block = block + 0x14;
            view->otEntries[0] = block;
            view->packets[0] = (void *) ((4 << view->otBits) + (s32)block);
            view->ot[1] = (GsOT *) (size + (u8 *) view->ot[0]);
            view->otEntries[1] = (void *) (size + (u8 *) view->otEntries[0]);
            view->packets[1] = (void *) (size + (u8 *) view->packets[0]);
            view->ot[0]->length = view->otBits;
            view->ot[0]->org = view->otEntries[0];
            view->ot[1]->length = view->otBits;
            view->ot[1]->org = view->otEntries[1];
            GsClearOt(0, 0, view->ot[0]);
            GsClearOt(0, 0, view->ot[1]);
            view->otReady = 1;
            view->buffer = 0;
        }
    }
}

void View_FreeOt(View *view) {
    if (view->otReady != 0) {
        DrawSync(0);
        Heap_Free(view->ot[0]);
        view->otReady = 0;
    }
}

/* Clock messages 2 (tick) and 3 (paused) render a frame. */
void View_OnClock(View *view, Clock *clock, s32 message) {
    s32 render;

    render = (message == 2 || message == 3);
    view->clockCount++;
    if (render) {
        view->vtbl->render(view, clock, render);
    }
}

void View_OnDisplay(View *view, Display *display, s32 message) {
    if (message == 2) {
        view->vtbl->present(view);
    }
}

/* Sorts the root and the watched node's tree into the ordering table of this buffer. */
void View_Render(View *view) {
    if (view->otReady != 0) {
        if (view->node->parent != NULL) {
            view->vtbl->drawNode(view, view->node);
        }
        View_SetGeomScreen(view->projection);
        func_8003FB0C(view->nearZ);
        GsSetLightMode(view->lightMode);
        if (view->lightMode == 1 || view->lightMode == 3) {
            SetFarColor(view->fogColor.r, view->fogColor.g, view->fogColor.b);
            SetFogNear(view->fogNear, view->projection);
        }
        GsSetRefView2(&view->viewpoint);
        view->super->flg = 0;
        view->unk98 = ((u32)(view->farZ - view->nearZ) / (u32)(1 << view->otBits)) + 1;
        func_8003FBE4(view->packets[view->buffer]);
        GsClearOt(0, 0, view->ot[view->buffer]);
        view->vtbl->drawNode(view, view->root);
        if (view->node != NULL) {
            view->vtbl->drawNode(view, SceneNode_GetRoot(view->node));
        }
    }
}

/* Each display frame: clears with clearColor and draws the ordering table, then flips the buffer. */
void View_Present(View *view) {
    if (view->otReady != 0) {
        view->buffer = view->display->vtbl->getActiveBuffer(view->display);
        if (view->unkB8 != 0) {
            ResetGraph(1);
            view->display->vtbl->swapBuffers(view->display);
            if (view->unkB4 != 0 && view->buffer == 0) {
                view->display->vtbl->swapBuffers(view->display);
            }
            GsSortClear(view->clearColor.r, view->clearColor.g, view->clearColor.b, view->ot[view->buffer]);
            GsDrawOt(view->ot[view->buffer]);
            if (view->unkB4 != 0 && view->buffer == 0) {
                view->display->vtbl->swapBuffers(view->display);
            }
        }
        view->buffer = view->buffer == 0;
    }
}

void View_SetOverlay(View *view, Fade *overlay) {
    Fade *previous;

    if (view->node == 0) {
        previous = view->overlay;
        if (previous != NULL) {
            previous->vtbl->delete_(previous);
        }
        view->overlay = overlay;
        if (overlay != NULL) {
            overlay->vtbl->show(overlay, view->root, &g_overlayPos);
        }
    }
}

Fade *View_GetOverlay(View *view) {
    return view->overlay;
}

void View_SetExtraSwap(View *view, s32 value) {
    view->unkB4 = value;
}

void View_SetPresentEnabled(View *view, s32 value) {
    view->unkB8 = value;
}

ViewVtbl *View_GetVtbl(void) {
    return g_viewVtbl;
}

SceneNode *SceneNode_GetRoot(SceneNode *node) {
    while (node->parent != NULL) {
        node = node->parent;
    }
    return node;
}

void View_SetGeomScreen(s32 projection) {
    SetGeomScreen(projection);
}

ScreenPoint g_viewDefaultScreenSize = { 0x100, 0xF0 };

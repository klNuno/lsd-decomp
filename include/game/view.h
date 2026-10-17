#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"
#include "game/fade.h"
#include "game/clock.h"

/*
 * View (src/game/view.c): vtable g_viewVtbl (tag 7), 0xBC bytes, made by View_New, derived from
 * Object: the GsRVIEW2, two ordering tables with their packet areas, fog, light mode and clear color.
 */

/* The view's slots past Object (vtable g_viewVtbl). */
typedef struct ViewVtbl {
    s32 classWord;               /* 0x00 7 */
    void *(*delete_)();
    void (*init)();
    void (*destroy)();
    void (*watch)();            /* 0x10 View_Watch */
    void (*unwatch)();          /* 0x14 View_Unwatch */
    void (*unwatchAll)();
    void (*nextWatched)();
    void (*addWatcher)();
    void (*removeWatcher)();
    void (*freeWatchers)();
    void (*nextWatcher)();
    void (*notify)();
    void (*unk34)();
    void (*onNotify)();         /* 0x38 */
    void (*unk3C)();
    void (*reset)();            /* 0x40 */
    void (*setScreenSize)();    /* 0x44 */
    void (*setOtBits)();        /* 0x48 */
    void (*setPacketCount)();   /* 0x4C */
    void (*setPacketSize)();    /* 0x50 */
    void (*setProjection)();    /* 0x54 */
    void (*unk58)();            /* 0x58 empty */
    void (*unk5C)();            /* 0x5C empty */
    void (*setLightMode)();     /* 0x60 */
    void (*setClearColor)();    /* 0x64 */
    void (*setFogColor)();      /* 0x68 */
    void (*setFogNear)();       /* 0x6C */
    void (*setCamera)();        /* 0x70 (view, node, viewpoint, refPoint, twist) */
    void (*detach)();           /* 0x74 */
    void (*setViewpoint)();     /* 0x78 */
    void (*setRefPoint)();      /* 0x7C */
    void (*setTwist)();         /* 0x80 */
    void (*unk84)();            /* 0x84 empty */
    void (*unk88)();            /* 0x88 empty */
    void (*allocOt)();          /* 0x8C */
    void (*freeOt)();           /* 0x90 */
    void (*onClock)();          /* 0x94 sender type 5 */
    void (*onDisplay)();        /* 0x98 sender type 1 */
    void (*render)();           /* 0x9C */
    void (*drawNode)();         /* 0xA0 View_DrawNode */
    void (*present)();          /* 0xA4 */
    void (*setOverlay)();       /* 0xA8 */
    struct Fade *(*getOverlay)(); /* 0xAC View_GetOverlay */
    void (*setExtraSwap)();         /* 0xB0 */
    void (*setPresentEnabled)();         /* 0xB4 */
} ViewVtbl;

typedef struct View {
    ViewVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    Display *display;       /* 0x0C the watched type 1 object */
    SceneNode *node;        /* 0x10 the watched type 4 object; rendered with its root */
    /* 0x14 GsRVIEW2, given to GsSetRefView2 */
    Vec3 viewpoint;         /* 0x14 world position, copied whole */
    Vec3 refPoint;          /* 0x20 */
    s32 twist;              /* 0x2C rz, 4.12 */
    Coord2 *super;          /* 0x30 node's coordinate; render clears its flg */
    ScreenPoint screenSize; /* 0x34 (0x100, 0xF0): View_DrawNode (src/game/scene_draw.c) sizes boxes and sprites by its half */
    s32 otBits;             /* 0x3C 13 */
    s32 projection;         /* 0x40 h of SetGeomScreen, 0x100 */
    s32 packetCount;        /* 0x44 2000 */
    s32 packetSize;         /* 0x48 0x40 */
    s32 nearZ;              /* 0x4C 10, GsSetNearClip */
    s32 farZ;              /* 0x50 0x10000; (unk50 - unk4C) / OT length + 1 is unk98 */
    s32 lightMode;          /* 0x54 GsSetLightMode; 1 and 3 turn the fog on */
    Color3 clearColor;      /* 0x58 GsSortClear */
    Color3 fogColor;        /* 0x5B SetFarColor */
    u8 pad_5E[0x60 - 0x5E];
    s32 fogNear;            /* 0x60 SetFogNear, 20000 */
    u8 pad_64[0x70 - 0x64];
    s32 otReady;            /* 0x70 */
    s32 buffer;             /* 0x74 the display's active buffer */
    GsOT *ot[2];            /* 0x78 */
    void *otEntries[2];     /* 0x80 */
    void *packets[2];       /* 0x88 GPU packet areas, packetCount x packetSize each */
    s32 clockCount;         /* 0x90 clock messages received */
    u8 pad_94[0x98 - 0x94];
    s32 otZStep;              /* 0x98 */
    u8 pad_9C[0xAC - 0x9C];
    SceneNode *root;        /* 0xAC SceneNode_New, drawn every frame; the overlay hangs from it */
    Fade *overlay;          /* 0xB0 a 320 x 240 Fade at (-100, -100); Place uses it as its fader (place.h) */
    s32 extraSwap;              /* 0xB4 when set, present swaps buffers once more on buffer 0 */
    s32 presentEnabled;              /* 0xB8 present draws only when set, 1 */
} View;

/* Functions of src/game/view.c that other files call or reference (docs/naming.md, Prototypes) */
View *View_New(void);
void View_Destroy(View *view);
void View_Watch(View *view, Object *other);
void View_Unwatch(View *view, Object *other);
void View_UnwatchAll(View *view);
void View_OnNotify(View *view, Object *sender, s32 message);
void View_SetScreenSize(View *view, ScreenPoint *value);
void View_SetOtBits(View *view, s32 otBits);
void View_SetPacketCount(View *view, s32 packetCount);
void View_SetPacketSize(View *view, s32 packetSize);
void View_SetProjection(View *view, s32 projection);
void View_EmptySlot58(void);
void View_EmptySlot5C(void);
void View_SetLightMode(View *view, s32 lightMode);
void View_SetClearColor(View *view, Color3 *color);
void View_SetFogColor(View *view, Color3 *color);
void View_SetFogNear(View *view, s32 fogNear);
void View_SetCamera(View *view, SceneNode *node, Vec3 *viewpoint, Vec3 *refPoint, Fraction *twist);
void View_Detach(View *view);
void View_SetViewpoint(View *view, Vec3 *viewpoint);
void View_SetRefPoint(View *view, Vec3 *refPoint);
void View_SetTwist(View *view, Fraction *twist);
void View_EmptySlot84(void);
void View_EmptySlot88(void);
void View_AllocOt(View *view);
void View_FreeOt(View *view);
void View_OnClock(View *view, Clock *clock, s32 message);
void View_OnDisplay(View *view, Display *display, s32 message);
void View_Present(View *view);
void View_SetOverlay(View *view, Fade *overlay);
Fade *View_GetOverlay(View *view);
void View_SetExtraSwap(View *view, s32 value);
void View_SetPresentEnabled(View *view, s32 value);

#endif

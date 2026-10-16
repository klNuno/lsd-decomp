#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene.h"

/* Functions of src/game/view.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/view.c */
struct ViewRatio;
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
void View_SetCamera(View *view, SceneNode *node, ScreenVec *viewpoint, ScreenVec *refPoint, struct ViewRatio *twist);
void View_Detach(View *view);
void View_SetViewpoint(View *view, ScreenVec *viewpoint);
void View_SetRefPoint(View *view, ScreenVec *refPoint);
void View_SetTwist(View *view, struct ViewRatio *ratio);
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

#ifndef GAME_SCENERY_OBJ_H
#define GAME_SCENERY_OBJ_H

#include "common.h"
#include "game/view.h"
#include "game/place.h"

/* Functions of src/game/scenery_obj.c that other files call or reference (docs/naming.md, Prototypes) */
void *Scenery_New(s32 kind, s32 params, s32 map, s32 origin);
void Scenery_SetPlaceRefs(s32 family, PlaceObj *models, void *font, View *view);

#endif

#ifndef GAME_SCENERY_H
#define GAME_SCENERY_H

#include "common.h"
#include "game/place.h"

/* Functions of src/game/scenery.c that other files call or reference (docs/naming.md, Prototypes) */
Ambience *Scenery_Begin(s32 map, s32 stage, PlaceRefs *refs, s32 dayNumber, s32 unused);
void Scenery_Teardown(void);
s32 Scenery_Tick(s32 mapPos, s32 ignored, s32 found);
s32 Ambience_IsEvenFamily(void);

#endif

#ifndef GAME_DREAM_LINK_H
#define GAME_DREAM_LINK_H

#include "common.h"

/* A rotation in degrees (Fraction[3], scene_node.h, as SceneNode_GetRotation fills it) read for the
   y numerator, unsigned (Link_IsFacing subtracts u16 yaws). */
typedef struct RotationYaw {
    u8 pad_00[4];
    u16 yaw;
} RotationYaw;

/* Functions of src/game/dream_link.c that other files call or reference (docs/naming.md, Prototypes) */
void Nav_InitFlags(u8 *flags, s32 *linkCount);
s32 Nav_CalcScore(void);
s32 Spawn_PickRandom(void *place, s32 stage, s32 unused);
s32 Link_FindStatic(void *out, void *location, s32 stage);
s32 Link_FindFacing(void *out, void *location, s32 stage);
s32 Link_CheckFacing(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation);
s32 Link_PickFallStage(void *place, s32 stage, void *location, s32 timer);
s32 *Link_GetFallTurn(void);
void Link_SetExtraListOn(s32 on);
s32 Link_FindExtra(void *out, void *location, s32 stage);
s32 Link_GetExtraSeconds(void);
s32 Link_FindScripted(void *out, void *location, s32 stage);
s32 Link_CheckScripted(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation);
s32 Link_GetStepScript(void);
s32 Spawn_PickFromMood(void *place, s32 *secondsOut, void *point, s32 day);
struct MoodPoint *Day_FindSpecial(void *cinematic, s32 dayNumber);

#endif

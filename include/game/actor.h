#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include "common.h"
#include "game/gs.h"

/* Functions of src/game/actor.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/actor.c */
struct Actor;
struct ModelVec;
void *Actor_New(void);
void Actor_Watch(struct Actor *actor, s32 **other);
void Actor_Unwatch(struct Actor *actor, s32 **other);
void Actor_UnwatchAll(struct Actor *actor);
void Actor_SendBoxes(struct Actor *actor, s32 message);
void Actor_OnNode(struct Actor *actor, u8 **message);
void Actor_SetPos(void *actor, Vec3 *pos);
void Actor_MovePos(void *actor, Vec3 *delta);
void Actor_MoveLocal(struct Actor *actor, struct ModelVec *local);
void Actor_MoveZ(void *actor, s32 value, s32 notify);
void Actor_MoveX(void *actor, s32 value, s32 notify);
void Actor_MoveY(void *actor, s32 value, s32 notify);
void Actor_MoveZOnGround(struct Actor *actor, s32 value, s32 notify);
void Actor_MoveXOnGround(struct Actor *actor, s32 value, s32 notify);
void Actor_EmptySlotD8(void);
void Actor_OnNode34(struct Actor *actor, void *sender, s32 message);
void Actor_OnNode24(struct Actor *actor, void *sender, s32 message);
void Actor_SetSpeed(struct Actor *actor, s16 value);
void Actor_EmptySlotE8(void);
void Actor_SetBoxMargin(struct Actor *actor, s32 value);

#endif

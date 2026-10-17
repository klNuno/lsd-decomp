#ifndef GAME_SPRITE_NODE_H
#define GAME_SPRITE_NODE_H

#include "common.h"
#include "game/gs.h"

/* The part of a TIM image cut into a sprite: copied whole. */
typedef struct SpriteRect {
    u16 u;
    u16 v;
    s32 w;
    s32 h;
} SpriteRect;

/* Functions of src/game/sprite_node.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/sprite_node.c */
struct NodeAngles;
struct SpriteNode;
void SpriteNode_SetRotation(struct SpriteNode *node, s32 assign, struct NodeAngles *angles);
s32 SpriteNode_SetVisible(struct SpriteNode *node, s32 visible);
void SpriteNode_SetSemiTrans(struct SpriteNode *node, s32 semiTrans);
void SpriteNode_SetBlendRate(struct SpriteNode *node, s32 blendRate);
void SpriteNode_OnClock(void);
void SpriteNode_SetColor(struct SpriteNode *node, Color3 *color);

#endif

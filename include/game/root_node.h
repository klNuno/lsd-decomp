#ifndef GAME_ROOT_NODE_H
#define GAME_ROOT_NODE_H

#include "common.h"
#include "game/gs.h"
#include "game/flat_light.h"

/* Functions of src/game/root_node.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/root_node.c */
struct RootNode;
struct RootNode *RootNode_Create(void);
FlatLight *RootNode_GetLight(struct RootNode *root, s32 index);
void RootNode_SetAmbient(struct RootNode *root, Color3 *color, s32 swap);

#endif

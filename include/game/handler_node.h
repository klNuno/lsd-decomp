#ifndef GAME_HANDLER_NODE_H
#define GAME_HANDLER_NODE_H

#include "common.h"
#include "game/sound.h"

/* Functions of src/game/handler_node.c that other files call or reference (docs/naming.md, Prototypes) */
s32 HandlerNode_Start(s32 bank, HandlerNode *node, s32 nodeId, s32 owner, s32 handler);
void HandlerNode_Stop(SoundBank *bank, HandlerNode *node);
void HandlerNode_Run(SoundBank *bank, HandlerNode *node);

#endif

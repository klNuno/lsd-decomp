#ifndef GAME_SCENE_DRAW_H
#define GAME_SCENE_DRAW_H

#include "common.h"
#include "game/scene.h"

/* Functions of src/game/scene_draw.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/scene_draw.c */
struct DrawNode;
void Scene_DrawNode(View *view, struct DrawNode *node);

#endif

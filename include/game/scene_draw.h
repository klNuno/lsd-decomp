#ifndef GAME_SCENE_DRAW_H
#define GAME_SCENE_DRAW_H

#include "common.h"
#include "game/view.h"

/* Functions of src/game/scene_draw.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/scene_draw.c */
struct DrawNode;
void View_DrawNode(View *view, struct DrawNode *node);

#endif

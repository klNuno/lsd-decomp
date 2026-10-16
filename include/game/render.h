#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "common.h"

/* Functions of src/game/render.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/render.c */
struct TmdCtx;
struct TmdObject;
struct TmdOt;
void Render_SortModel(struct TmdObject *object, struct TmdOt *ot, s32 shift, struct TmdCtx *scratch);

#endif

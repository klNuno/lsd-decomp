#ifndef GAME_MAP_MODELS_H
#define GAME_MAP_MODELS_H

#include "common.h"

/* Functions of src/game/map_models.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/map_models.c */
struct ModelSetVtbl;
s32 MapModels_New(s32 initParam);
struct ModelSetVtbl *MapModels_GetVtbl(void);

#endif

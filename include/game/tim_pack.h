#ifndef GAME_TIM_PACK_H
#define GAME_TIM_PACK_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/tim_pack.c that other files call or reference (docs/naming.md, Prototypes) */
s32 TimPack_Create(s32 path);
TimPackVtbl *TimPack_GetVtbl(void);

#endif

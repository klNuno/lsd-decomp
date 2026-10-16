#ifndef GAME_TOD_PACK_H
#define GAME_TOD_PACK_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/tod_pack.c that other files call or reference (docs/naming.md, Prototypes) */
s32 TodPack_Create(s32 source);
TodVtbl *TodPack_GetVtbl(void);

#endif

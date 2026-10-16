#ifndef GAME_TIX_H
#define GAME_TIX_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/tix.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Tix_Create(s32 path);
TixVtbl *Tix_GetVtbl(void);

#endif

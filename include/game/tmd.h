#ifndef GAME_TMD_H
#define GAME_TMD_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/tmd.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Tmd_Create(s32 source);
TmdVtbl *Tmd_GetVtbl(void);

#endif

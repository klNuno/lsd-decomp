#ifndef GAME_MML_H
#define GAME_MML_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/mml.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Mml_Create(s32 source);
MomVtbl *Mml_GetVtbl(void);

#endif

#ifndef GAME_BG_MAP_H
#define GAME_BG_MAP_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/bg_map.c that other files call or reference (docs/naming.md, Prototypes) */
s32 BgMap_Create(s32 skipBuild, s32 cells);
BgMapVtbl *BgMap_GetVtbl(void);

#endif

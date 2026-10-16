#ifndef GAME_BG_CELLS_H
#define GAME_BG_CELLS_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/bg_cells.c that other files call or reference (docs/naming.md, Prototypes) */
s32 BgCells_Create(s32 skipBuild);
BgCellsVtbl *BgCells_GetVtbl(void);

#endif

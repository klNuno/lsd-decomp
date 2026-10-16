#ifndef GAME_SYM_H
#define GAME_SYM_H

#include "common.h"
#include "game/dreamsys.h"

/* Functions of src/game/sym.c that other files call or reference (docs/naming.md, Prototypes) */
void Sym_LoadModels(void);
void Sym_FreeModels(void);
void Sym_InitStage(s32 stage, s32 map, DreamSys *dreamSys, s32 soundBank, s32 watched);
void Sym_FreeSpy(void);
s32 Sym_SpawnOrSpy(s32 square, void *chunkKey, s32 dayNumber);

#endif

#ifndef GAME_SYM_H
#define GAME_SYM_H

#include "common.h"
#include "game/dream_sys.h"

struct StageMap;
struct Mml;

/* Functions of src/game/sym.c that other files call or reference (docs/naming.md, Prototypes) */
void Sym_ResetGroupsAndLoadSpy(void);
void Sym_FreeModels(void);
void Sym_InitStage(s32 stage, struct StageMap *map, DreamSys *dreamSys, void *soundBank, void *clock);
void Sym_FreeSpy(void);
struct Mml *Sym_SpawnOrSpy(u8 *square, void *chunkKey, s32 dayNumber);

#endif

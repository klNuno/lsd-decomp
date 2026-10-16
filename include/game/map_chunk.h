#ifndef GAME_MAP_CHUNK_H
#define GAME_MAP_CHUNK_H

#include "common.h"
#include "game/stage.h"

/* Functions of src/game/map_chunk.c that other files call or reference (docs/naming.md, Prototypes) */
s32 MapChunk_New(void);
MapChunkVtbl *MapChunk_GetVtbl(void);

#endif

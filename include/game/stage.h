#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include "common.h"

/*
 * Stage tables of src/game/stage.c: the per-stage chunk grids (StageGrid, g_stageChunkMoods) and a
 * position on a stage (StagePlace). The classes the dream's world is built from have their own
 * headers: Task (task.h), DreamRunner (dream_runner.h), StageMap (stage_map.h), MapChunk
 * (map_chunk.h), MapModels (map_models.h) and MapTile (map_tile.h).
 */

/*
 * The chunk grid of a stage, 8 bytes, 14 entries at g_stageGrids (Stage_GetGrids). A chunk is
 * 0xA000 units (20 tiles of 0x800) square; odd rows are shifted by half a chunk (Stage_PlaceToWorld),
 * so a chunk has 6 neighbours.
 */
typedef struct StageGrid {
    s16 cols;     /* 0x00 chunks per row */
    s16 rows;     /* 0x02 */
    s32 stacked;  /* 0x04 1 for stages 0 and 6: one column of chunks stacked in height, 0x800 apart (StageMap_SlotAt) */
} StageGrid;

/*
 * A position on a stage, 10 bytes: chunk (col, row), tile in the chunk, and the offset in the
 * tile from its centre (Stage_PlaceToWorld turns it into world coordinates). DreamSys keeps two: where the dreamer stands and the link target.
 */
typedef struct StagePlace {
    s8 col;       /* 0x00 chunk column */
    s8 row;       /* 0x01 chunk row */
    s8 tileX;     /* 0x02 tile in the chunk, 0 to 19 */
    s8 tileY;     /* 0x03 */
    s16 x;        /* 0x04 offset in the tile, from its centre (0x400) */
    s16 y;        /* 0x06 height */
    s16 z;        /* 0x08 */
} StagePlace;

/* A chunk of a stage, (col, row) as in StagePlace: Stage_FindChunkByMood writes one. */
typedef struct StageChunkPos {
    s8 col;
    s8 row;
} StageChunkPos;

/* A graph point: two mood axes in -9..9 (a day of the graph, a chunk, an entity record). */
typedef struct MoodPoint {
    s8 x;
    s8 y;
} MoodPoint;

/* A MoodPoint copied or compared as one halfword (the chunk mood tables, DreamSys_ComputeDayPoint). */
typedef union MoodWord {
    MoodPoint point;
    s16 word;
} MoodWord;

/* Functions of src/game/stage.c that other files call or reference (docs/naming.md, Prototypes) */
StageGrid *Stage_GetGrid(s32 stage);
u32 Stage_FindChunkByMood(StageChunkPos *chunk, MoodWord *mood);
MoodPoint *Stage_GetChunkMood(s32 stage, StagePlace *place);

#endif

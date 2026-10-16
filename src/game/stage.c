#include "common.h"
#include "game/stage.h"

/*
 * Stage tables (types in game/stage.h): one entry per STGxx folder, 0 to 13 (time limits, chunk
 * moods, spawn points, paths).
 *
 * File boundaries: guess (docs/layout.md)
 */

extern StageGrid g_stageGrids[];  /* g_stageGrids, 14 entries (Stage_GetGrids) */
extern StageGrid g_stageGridRows[];  /* g_stageGrids + 2 */
extern s16 *g_stageChunkMoods[];       /* per stage: the s16 mood of each chunk, row-major */

/* The number of stages (STG00 to STG13). */
s32 Stage_GetCount(void) {
    return 0xE;
}

StageGrid *Stage_GetGrids(s32 *count) {
    if (count != NULL) {
        *count = 14;
    }
    return g_stageGrids;
}

StageGrid *Stage_GetGrid(s32 stage) {
    return &Stage_GetGrids(NULL)[stage];
}

/* First stage, scanning stages then rows, with a chunk whose mood equals *mood; writes its (col, row), -1 when none. */
u32 Stage_FindChunkByMood(StagePlace *place, s16 *mood) {
    u32 stage;
    s32 col;
    s32 row;
    s32 rows;
    s32 cols;
    s16 *chunkMood;

    for (stage = 0; stage < 0xE; stage++) {
        chunkMood = g_stageChunkMoods[stage];
        rows = g_stageGridRows[stage].cols; /* g_stageGridRows is g_stageGrids + 2: this reads the rows */
        cols = g_stageGrids[stage].cols;
        for (row = 0; row < rows; row++) {
            for (col = 0; col < cols; col++) {
                if (*mood == *chunkMood) {
                    place->col = col;
                    place->row = row;
                    return stage;
                }
                chunkMood++;
            }
        }
    }
    return -1;
}

s16 *Stage_GetChunkMood(s32 stage, StagePlace *place) {
    return g_stageChunkMoods[stage] + place->row * g_stageGrids[stage].cols + place->col;
}

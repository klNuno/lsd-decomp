#ifndef GAME_PATH_TABLE_H
#define GAME_PATH_TABLE_H

#include "common.h"

/* Functions of src/game/path_table.c that other files call or reference (docs/naming.md, Prototypes) */
void *File_GetRootDir(void);
s32 Rand_SeedAndNext(); /* K&R definition: two callers pass an extra argument it ignores */
void *File_GetPathTable(s32 *count);
s32 Music_PickBank(s32 unused);
s32 Music_GetEffectsBank(); /* unprototyped: dream_runner.c passes an argument */
u8 *Stage_PickTexturePath(s32 stage, s32 unused, s32 dayNumber);
u8 *Music_PickTrack(); /* unprototyped: place.c passes a second argument */
u8 *Stage_GetChunkPath(); /* unprototyped: place.c passes only the stage */
void Stage_GetChunkPathAt(s32 stage, s32 col, s32 row);
char *Cine_GetLogoPath(s32 *videoId);
s32 Cine_PickOpeningPath(); /* unprototyped: scene.c passes a second argument */
s32 Cine_GetEndingPath(); /* unprototyped: scene.c passes a second argument */
s32 Cine_GetPath(); /* unprototyped: scene.c passes the {category, variant} pair as one s32 */
s32 Cine_GetSpecialDayRun(s32 *frames, s32 category, s32 count);

#endif

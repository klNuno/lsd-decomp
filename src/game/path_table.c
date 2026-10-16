#include "common.h"
#include "game/path_table.h"
#include "game/stage.h"
#include "psyq/libc.h"

/*
 * The path table g_pathTable: 0x1C-byte path entries, 560 counted by File_GetPathTable (sound banks, then per stage
 * TEXA to TEXD.TIX, BGA to BGE.SEQ and the Mxxx.LBD chunks from g_stageFirstPath[stage]), then the
 * opening, ending, event and special-day videos. The getters below hand out pieces of it, with
 * the video id (index into g_videoTable) through their out parameter.
 *
 * File boundaries: likely (docs/layout.md)
 */

extern u8 g_pathTable[];      /* the path table, 0x1C bytes per path */
extern s16 g_videoTable[];   /* frame count of each video, by video id */
s32 g_musicBankOverride;              /* forced music bank + 1, 0 = random (Music_SetOverride) */
s32 g_musicTrackOverride;              /* forced track + 1, 0 = random (Music_SetOverride) */
static u8 *Stage_GetPathBase(s32 stage);
static s8 **Music_GetEffectsBankPtr(void);
extern s16 g_stageFirstPath[];     /* first path of each stage in the path table */
static u8 *Stage_GetChunkPaths(s32 stage);
static u8 *Cine_GetEventPaths(s32 *videoId);
static s32 Cine_GetOpeningPaths(s32 *videoId);
static s32 Cine_GetEndingPathEntry(s32 *videoId);
static u8 *Cine_GetEventPath(s32 *videoId, s32 event);
static s32 Cine_GetSpecialDayPaths(s32 *videoId, s32 category);

/* {category, variant} of DreamSys +0x168; a negative category means an event video */
typedef struct CineChoice {
    s16 category;
    s16 variant;
} CineChoice;

static u8 *Stage_GetTrackPaths(s32 stage);
static u8 *Stage_GetTexturePaths(s32 stage);
static u8 *Music_GetBanks(void);
void *g_rootDir;            /* "CDI\\", the root directory of every path */
extern u8 g_musicBanks[];      /* the 7 sound bank paths, SND\AMBIENT to SND\STANDERD */
extern s8 *g_effectsBank[];     /* points to "SND\\SE" */

void *File_GetRootDir(void) {
    return g_rootDir;
}

s32 Rand_SeedAndNext(seed)
    s32 seed;
{
    if (seed != 0) {
        srand(seed);
    }
    return rand();
}

/* No caller: pins the bank and the track (1-based), a negative value keeps the current one */
static void Music_SetOverride(s32 bank, s32 track) {
    if (bank >= 0) {
        g_musicBankOverride = bank;
    }
    if (track >= 0) {
        g_musicTrackOverride = track;
    }
}

u8 *File_GetPathTable(s32 *count) {
    if (count != NULL) {
        *count = 0x230;
    }
    return g_pathTable;
}

static u8 *Music_GetBanks(void) {
    return g_musicBanks;
}

/* unused goes to Rand_SeedAndNext as an extra argument it ignores */
s8 *Music_PickBank(s32 unused) {
    s32 r;
    u8 *banks;
    s32 ofs;

    r = (u32)Rand_SeedAndNext(0, unused) % 7;
    banks = Music_GetBanks();
    if (g_musicBankOverride != 0) {
        ofs = (g_musicBankOverride - 1) * 4;
    } else {
        ofs = r * 4;
    }
    return *(s8 **)(banks + ofs);
}

static s8 **Music_GetEffectsBankPtr(void) {
    return g_effectsBank;
}

s8 *Music_GetEffectsBank(void) {
    return *Music_GetEffectsBankPtr();
}

static u8 *Stage_GetPathBase(s32 stage) {
    return File_GetPathTable(NULL) + g_stageFirstPath[stage] * 0x1C;
}

static u8 *Stage_GetTexturePaths(s32 stage) {
    return Stage_GetPathBase(stage);
}

/* TEXA to TEXD.TIX: rand() % (((dayNumber - 1) % 40) / 10 + 1) */
u8 *Stage_PickTexturePath(s32 stage, s32 unused, s32 dayNumber) {
    s32 row;
    s32 r;

    row = ((dayNumber - 1) % 40) / 10 + 1;
    r = Rand_SeedAndNext(0, unused) % row;
    return Stage_GetTexturePaths(stage) + r * 0x1C;
}

static u8 *Stage_GetTrackPaths(s32 stage) {
    return Stage_GetPathBase(stage) + 0x70;
}

/* BGA to BGE.SEQ at random; stage 9 never gets BGC */
u8 *Music_PickTrack(s32 stage) {
    u32 track;
    u8 *tracks;
    s32 ofs;

    track = (u32)Rand_SeedAndNext(0) % 5;
    if (stage == 9) {
        if (track == 2) {
            track = 3;
        }
        if (g_musicTrackOverride == 3) {
            g_musicTrackOverride = 4;
        }
    }
    tracks = Stage_GetTrackPaths(stage);
    if (g_musicTrackOverride != 0) {
        ofs = (g_musicTrackOverride - 1) * 7;
    } else {
        ofs = track * 7;
    }
    return tracks + (ofs * 4);
}

static u8 *Stage_GetChunkPaths(s32 stage) {
    return Stage_GetPathBase(stage) + 0xFC;
}

u8 *Stage_GetChunkPath(s32 stage, s32 chunk) {
    return Stage_GetChunkPaths(stage) + chunk * 0x1C;
}

void Stage_GetChunkPathAt(s32 stage, s32 col, s32 row) {
    Stage_GetChunkPath(stage, col + (Stage_GetGrid(stage)->cols * row));
}

INCLUDE_RODATA("asm/nonmatchings/game/path_table", D_80011384);
INCLUDE_RODATA("asm/nonmatchings/game/path_table", g_musicBankLovely);
INCLUDE_RODATA("asm/nonmatchings/game/path_table", g_musicBankHuman);
INCLUDE_RODATA("asm/nonmatchings/game/path_table", g_musicBankEthnova);
INCLUDE_RODATA("asm/nonmatchings/game/path_table", g_musicBankElectro);
INCLUDE_RODATA("asm/nonmatchings/game/path_table", g_musicBankCartoon);
INCLUDE_RODATA("asm/nonmatchings/game/path_table", g_musicBankAmbient);

/* The ASMIK logo video, video id 0x31 */
char *Cine_GetLogoPath(s32 *videoId) {
    if (videoId != NULL) {
        *videoId = 0x31;
    }
    return "ETC\\ASMK.STR";
}

/* ETC\OPENINGA.STR to OPENINGG.STR, video ids 0 to 6 */
static s32 Cine_GetOpeningPaths(s32 *videoId) {
    if (videoId != NULL) {
        *videoId = 0;
    }
    return (s32)File_GetPathTable(NULL) + 0x3D40;
}

s32 Cine_PickOpeningPath(s32 *videoId) {
    s32 firstId;
    s32 r;
    s32 path;

    r = (u32)Rand_SeedAndNext(0) % 7;
    path = Cine_GetOpeningPaths(&firstId);
    if (videoId != NULL) {
        *videoId = r + firstId;
    }
    return path + r * 0x1C;
}

/* ETC\ENDING.STR, video id 7 */
static s32 Cine_GetEndingPathEntry(s32 *videoId) {
    if (videoId != NULL) {
        *videoId = 7;
    }
    return (s32)File_GetPathTable(NULL) + 0x3E04;
}

s32 Cine_GetEndingPath(s32 *videoId) {
    s32 id;
    s32 path;

    path = Cine_GetEndingPathEntry(&id);
    if (videoId != NULL) {
        *videoId = id;
    }
    return path;
}

/* FILM\EVENT1.STR to EVENT6.STR, video ids from 8 */
static u8 *Cine_GetEventPaths(s32 *videoId) {
    if (videoId != NULL) {
        *videoId = 8;
    }
    return File_GetPathTable(NULL) + 0x3E20;
}

static u8 *Cine_GetEventPath(s32 *videoId, s32 event) {
    s32 firstId;
    u8 *paths;

    paths = Cine_GetEventPaths(&firstId);
    if (videoId != NULL) {
        *videoId = event + firstId;
    }
    return paths + event * 0x1C;
}

/* The 6 paths of a special-day category (0xA8 bytes): videos A and B have ids category * 2 + 14 */
static s32 Cine_GetSpecialDayPaths(s32 *videoId, s32 category) {
    s32 paths;

    paths = (s32)File_GetPathTable(NULL) + 0x3EC8;
    if (videoId != NULL) {
        *videoId = (category * 2) + 0xE;
    }
    return paths + (category * 0xA8);
}

/* Variants 0 and 1 are videos; 2 to 5 are pictures and get video id -1 */
s32 Cine_GetPath(s32 *videoId, CineChoice choice) {
    s32 firstId;
    s32 paths;
    s32 id;

    if (choice.category >= 0) {
        paths = Cine_GetSpecialDayPaths(&firstId, choice.category);
        if (videoId != NULL) {
            if ((u16)choice.variant < 2U) {
                id = choice.variant + firstId;
            } else {
                id = -1;
            }
            *videoId = id;
        }
        return paths + (choice.variant * 0x1C);
    }
    return (s32)Cine_GetEventPath(videoId, choice.variant);
}

s16 Cine_GetVideoFrames(s32 videoId) {
    return g_videoTable[videoId];
}

/*
 * The first path of special-day category `category` and, in *frames, the length of its videos
 * and those of the next count - 1 categories played as one stream (A and B each, 10 frames per join).
 */
s32 Cine_GetSpecialDayRun(s32 *frames, s32 category, s32 count) {
    s32 start;
    s32 ret;
    s32 i;

    ret = Cine_GetSpecialDayPaths(&start, category);
    *frames = 0;
    count *= 2;
    count += start;
    for (i = start; i < count; i++) {
        *frames += 10 + g_videoTable[i];
    }
    *frames -= 10;
    return ret;
}

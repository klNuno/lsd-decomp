#include "common.h"
#include "game/loader.h"
#include "game/stage.h"

/*
 * Two things live in this unit.
 *
 * The map chunk file class (vtable g_mapChunkVtbl, 0x3C bytes, created by MapChunk_New for each
 * StageMap slot): a file object of src/game/80025F7C.c with a 0xB358-byte buffer that receives a
 * stage's STGxx\Mxxx.LBD chunk file (slot 0x78), then, when the header says so, a second read of
 * the chunk's entity part into its own heap block (slot 0x80). include/game/stage.h holds the
 * part of it StageMap reads (MapChunk); MapChunk below is the whole object.
 *
 * The path table g_pathTable: 0x1C-byte path entries, 560 counted by File_GetPathTable (sound banks, then per stage
 * TEXA to TEXD.TIX, BGA to BGE.SEQ and the Mxxx.LBD chunks from g_stageFirstPath[stage]), then the
 * opening, ending, event and special-day videos. The getters below hand out pieces of it, with
 * the video id (index into g_videoTable) through their out parameter.
 */

extern u8 g_pathTable[];      /* the path table, 0x1C bytes per path */
extern s16 g_videoTable[];   /* frame count of each video, by video id */
s32 g_musicBankOverride;              /* forced music bank + 1, 0 = random (Music_SetOverride) */
s32 g_musicTrackOverride;              /* forced track + 1, 0 = random (Music_SetOverride) */
u8 *Stage_GetPathBase(s32 stage);
s32 *Music_GetEffectsBankPtr(void);
extern void srand(u32 seed);
extern s32 rand(void);
void *File_GetPathTable(s32 *count);
s32 Heap_Free(s32);

MapChunkVtbl *MapChunk_GetVtbl(void);
FileVtbl *File_GetBackendVtbl(void);
s32 Heap_Alloc(s32 size);
extern s16 g_stageFirstPath[];     /* first path of each stage in the path table */
StageGrid *Stage_GetGrid(s32 stage);
u8 *Stage_GetChunkPaths(s32 stage);
u8 *Stage_GetChunkPath(s32 stage, s32 chunk);
u8 *Cine_GetEventPaths(s32 *videoId);
s32 Cine_GetOpeningPaths(s32 *videoId);
s32 Cine_GetEndingPathEntry(s32 *videoId);
u8 *Cine_GetEventPath(s32 *videoId, s32 event);
s32 Cine_GetSpecialDayPaths(s32 *videoId, s32 category);

/* {category, variant} of DreamSys +0x168; a negative category means an event video */
typedef struct CineChoice {
    s16 category;
    s16 variant;
} CineChoice;

s32 Rand_SeedAndNext();
u8 *Stage_GetTrackPaths(s32 stage);
u8 *Stage_GetTexturePaths(s32 stage);
u8 *Music_GetBanks(void);
extern u8 g_mapChunkVtbl[];      /* MapChunkVtbl */
void *g_rootDir;            /* "CDI\\", the root directory of every path */
extern u8 g_musicBanks[];      /* the 7 sound bank paths, SND\AMBIENT to SND\STANDERD */
extern s32 g_effectsBank[];     /* points to "SND\\SE" */

s32 MapChunk_New(void) {
    s32 chunk;

    chunk = Heap_Alloc(0x3C);
    if (chunk != 0) {
        MapChunk_GetVtbl()->init(chunk);
        return chunk;
    }
    return 0;
}

/* Slot 0x08 */
void MapChunk_Init(MapChunk *chunk) {
    File_GetBackendVtbl()->init(chunk);
    chunk->vtbl = MapChunk_GetVtbl();
    chunk->index = -1;
    chunk->loaded = 0;
    chunk->entitiesLoaded = 0;
    chunk->id = 0;
    chunk->entities = 0;
    chunk->loadEntities = 1;
    chunk->data = ((void *)Heap_Alloc(0xB358));
    if (chunk->data != NULL) {
        chunk->size = 0xB358;
    }
}

/* Slot 0x0C */
void MapChunk_Destroy(MapChunk *chunk) {
    chunk->vtbl->freeEntities(chunk);
    File_GetBackendVtbl()->destroy(chunk);
}

/* Slot 0x64, after each finished file request */
void MapChunk_OnLoaded(MapChunk *chunk) {
    u16 state;

    state = chunk->state;
    if (state == 9) {
        if (chunk->flags & 0x80) {
            s32 loadEntities = chunk->loadEntities;

            chunk->state = 0;
            chunk->loaded = 1;
            if (loadEntities != 0) {
                chunk->vtbl->loadEntities();
            }
        }
    } else if (state == 0xA) {
        if (chunk->flags & 0x80) {
            chunk->entitiesLoaded = 1;
            chunk->state = 0;
        }
    }
    File_GetBackendVtbl()->onLoaded(chunk);
}

/* Slot 0x74: drops the pending requests */
void MapChunk_Unload(MapChunk *chunk) {
    File_GetBackendVtbl()->cancel(chunk);
    chunk->loaded = 0;
    chunk->entitiesLoaded = 0;
    chunk->state = 0;
}

/* Slot 0x78: reads the chunk file at path into the buffer */
void MapChunk_Load(MapChunk *chunk, s32 path) {
    if ((chunk->data != NULL) && (path != 0)) {
        if (chunk->state == 0) {
            chunk->loaded = 0;
        } else {
            chunk->vtbl->unload(chunk);
        }
        chunk->state = 9;
        chunk->vtbl->close(chunk);
        chunk->vtbl->open(chunk, path, 1, 0);
        chunk->vtbl->read(chunk, chunk->data, 0xB358);
    }
}

/* Slot 0x7C */
void MapChunk_Clear(MapChunk *chunk) {
    chunk->vtbl->freeData();
    chunk->loaded = 0;
    chunk->index = -1;
}

/* Slot 0x80: reads the entity part of the chunk file into a new heap block; 1 when started */
s32 MapChunk_LoadEntities(MapChunk *chunk) {
    s32 size;
    s32 entities;

    if ((chunk->data->hasEntities != 0) && (chunk->state == 0)) {
        chunk->vtbl->freeEntities(chunk);
        size = chunk->data->entitiesSize;
        entities = Heap_Alloc(size);
        chunk->entities = entities;
        if (entities != 0) {
            chunk->state = 10;
            chunk->vtbl->seek(chunk, chunk->data->entitiesOffset, 0);
            chunk->vtbl->read(chunk, chunk->entities, size);
            return 1;
        }
    }
    return 0;
}

/* Slot 0x84 */
void MapChunk_FreeEntities(MapChunk *chunk) {
    s32 entities;

    entities = chunk->entities;
    chunk->entitiesLoaded = 0;
    if (entities != 0) {
        chunk->entities = Heap_Free(entities);
    }
}

/* Slot 0x88 */
void MapChunk_SetLoadEntities(MapChunk *chunk, s32 loadEntities) {
    chunk->loadEntities = loadEntities;
}

MapChunkVtbl *MapChunk_GetVtbl(void) {
    return (MapChunkVtbl *)g_mapChunkVtbl;
}

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
void Music_SetOverride(s32 bank, s32 track) {
    if (bank >= 0) {
        g_musicBankOverride = bank;
    }
    if (track >= 0) {
        g_musicTrackOverride = track;
    }
}

void *File_GetPathTable(s32 *count) {
    if (count != NULL) {
        *count = 0x230;
    }
    return g_pathTable;
}

u8 *Music_GetBanks(void) {
    return g_musicBanks;
}

/* unused goes to Rand_SeedAndNext as an extra argument it ignores */
s32 Music_PickBank(s32 unused) {
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
    return *(s32 *)(banks + ofs);
}

s32 *Music_GetEffectsBankPtr(void) {
    return g_effectsBank;
}

s32 Music_GetEffectsBank(void) {
    return *Music_GetEffectsBankPtr();
}

u8 *Stage_GetPathBase(s32 stage) {
    return (u8 *)File_GetPathTable(NULL) + g_stageFirstPath[stage] * 0x1C;
}

u8 *Stage_GetTexturePaths(s32 stage) {
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

u8 *Stage_GetTrackPaths(s32 stage) {
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

u8 *Stage_GetChunkPaths(s32 stage) {
    return Stage_GetPathBase(stage) + 0xFC;
}

u8 *Stage_GetChunkPath(s32 stage, s32 chunk) {
    return Stage_GetChunkPaths(stage) + chunk * 0x1C;
}

void Stage_GetChunkPathAt(s32 stage, s32 col, s32 row) {
    Stage_GetChunkPath(stage, col + (Stage_GetGrid(stage)->cols * row));
}

INCLUDE_RODATA("asm/nonmatchings/game/80048894", D_80011384);

/* The ASMIK logo video, video id 0x31 */
char *Cine_GetLogoPath(s32 *videoId) {
    if (videoId != NULL) {
        *videoId = 0x31;
    }
    return "ETC\\ASMK.STR";
}

/* ETC\OPENINGA.STR to OPENINGG.STR, video ids 0 to 6 */
s32 Cine_GetOpeningPaths(s32 *videoId) {
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
s32 Cine_GetEndingPathEntry(s32 *videoId) {
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
u8 *Cine_GetEventPaths(s32 *videoId) {
    if (videoId != NULL) {
        *videoId = 8;
    }
    return (u8 *)File_GetPathTable(NULL) + 0x3E20;
}

u8 *Cine_GetEventPath(s32 *videoId, s32 event) {
    s32 firstId;
    u8 *paths;

    paths = Cine_GetEventPaths(&firstId);
    if (videoId != NULL) {
        *videoId = event + firstId;
    }
    return paths + event * 0x1C;
}

/* The 6 paths of a special-day category (0xA8 bytes): videos A and B have ids category * 2 + 14 */
s32 Cine_GetSpecialDayPaths(s32 *videoId, s32 category) {
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

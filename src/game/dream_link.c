#include "common.h"
#include "game/dream_link.h"
#include "game/stage.h"
#include "game/dream_sys.h"
#include "psyq/libc.h"

/*
 * File boundaries: guess (docs/layout.md)
 */

/* The first 4 bytes of a StagePlace, copied as one: chunk column and row, tile x and y. */
typedef struct { u8 col, row, tileX, tileY; } PlaceTile;
/* One g_tileOffsets entry, 6 bytes copied into StagePlace +4: the x, y (as one word) and z offsets in the tile. */
typedef struct { PlaceTile xy; s16 z; } TileOffset;
/* A spawn point or link target, 6 bytes: the tile, an index into g_tileOffsets and the navigation flag a link sets. */
typedef struct { PlaceTile tile; u8 offsetIndex; s8 navFlag; } SpawnPoint;
/* One entry of a stage link list: chunk key (col | row << 8), tile key (x | y << 8, negative for any tile), target stage and index. */
typedef struct { s16 chunkKey; s16 tileKey; s8 toStage; u8 toIndex; } LinkEntry;

u8 *g_navFlags;
s32 *g_dynamicLinkCount;
extern s32 g_fallTurn[];
s32 g_linkToStage;
s32 g_linkFromStage;
/* A scripted link target as Link_GetStepScript reads it: byte 5 is the index into g_linkSteps. */
typedef struct { u8 pad[5]; s8 stepScript; } ScriptedTarget;
extern ScriptedTarget *g_scriptedLinkTargets[];
s32 g_linkToIndex;
extern s16 g_stageTimeLimits[];
extern u8 g_staticLinkCounts[];
extern LinkEntry *g_staticLinkLists[];
extern SpawnPoint *g_staticLinkTargets[];
static s32 Link_Find(void *place, void *location, s32 stage, u8 *counts, LinkEntry **lists, SpawnPoint **targets, s32 setNavFlag);
extern u8 g_facingLinkCounts[];
extern LinkEntry *g_facingLinkLists[];
extern SpawnPoint *g_facingLinkTargets[];
extern u8 g_extraLinkCounts;
extern LinkEntry *g_extraLinkLists;
extern SpawnPoint *g_extraLinkTargets;
s32 g_extraListOn;
extern u8 g_scriptedLinkCounts[];
extern LinkEntry *g_scriptedLinkLists[];
extern u16 g_linkHeadingYaws[];
extern s16 g_specialDays[42];
extern MoodPoint g_specialDayPoint;
extern u8 g_linkHeadings[];
extern u8 *g_facingArrivalHeadings[];
extern u8 *g_facingLinkHeadings[];
s32 g_linkFromIndex;
static s32 Link_IsFacing(RotationYaw *rotation, u8 heading);
extern u8 *g_scriptedLinkHeadings[];
extern u8 *g_scriptedArrivalHeadings[];
s32 g_fallPlace5;
/* The map location (StageMap_GetLocation) as Link_PickFallStage reads it: the tile word, then the x and y (height) offsets. */
typedef struct FallLocation {
    s32 tile;
    s16 x;
    s16 y;
} FallLocation;
/* A StagePlace as the link and spawn pickers write it. */
typedef struct { PlaceTile tile; TileOffset offset; } PlaceOut;
extern TileOffset g_tileOffsets[];
extern SpawnPoint *g_spawnPoints[];
extern u8 g_spawnCounts[];

void Nav_InitFlags(u8 *flags, s32 *linkCount) {
    s32 i;
    for (i = 29; i >= 0; i--) {
        flags[i] = 0;
    }
    g_navFlags = flags;
    *linkCount = 0;
    g_dynamicLinkCount = linkCount;
}

s32 Nav_CalcScore(void) {
    s32 i;
    s32 sum = 0;

    for (i = 0; i < 30; i++) {
        if (((s8 *)g_navFlags)[i] != 0) {
            sum += 1000000;
        }
    }
    if (sum > 29999999) {
        sum = 50000000;
    }
    sum -= *g_dynamicLinkCount * 11024;
    if (sum < 0) {
        sum = 0;
    }
    return sum;
}

static s16 Stage_GetTimeLimit(s32 stage) {
    return g_stageTimeLimits[stage];
}

s32 Spawn_PickRandom(void *place, s32 stage, s32 unused) {
    s32 newStage;
    s32 n;
    PlaceOut *out;
    SpawnPoint *target;

    n = 6;
    if (stage >= 0) {
        newStage = rand() % n;
        if (newStage == stage) {
            newStage += 1;
            if (newStage >= 6) {
                newStage = 0;
            }
        }
    } else {
        newStage = -stage;
    }
    target = g_spawnPoints[newStage] + rand() % g_spawnCounts[newStage];
    out = place;
    out->tile = target->tile;
    out->offset = g_tileOffsets[target->offsetIndex];
    *g_dynamicLinkCount += 1;
    return newStage;
}

s32 Link_FindStatic(void *out, void *location, s32 stage) {
    return Link_Find(out, location, stage, g_staticLinkCounts, g_staticLinkLists, g_staticLinkTargets, 1);
}

s32 Link_FindFacing(void *out, void *location, s32 stage) {
    return Link_Find(out, location, stage, g_facingLinkCounts, g_facingLinkLists, g_facingLinkTargets, 1);
}

s32 Link_CheckFacing(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation) {
    u8 heading;

    heading = g_facingLinkHeadings[g_linkFromStage][g_linkFromIndex];
    if (Link_IsFacing(rotation, heading) != 0) {
        if (headingOut != NULL) {
            *headingOut = g_linkHeadings + heading * 12;
        }
        if (arrivalOut != NULL) {
            *arrivalOut = g_linkHeadings + g_facingArrivalHeadings[g_linkToStage][g_linkToIndex] * 12;
        }
        return 1;
    }
    return 0;
}

static s32 Link_IsFacing(RotationYaw *rotation, u8 heading) {
    s32 diff = rotation->yaw - g_linkHeadingYaws[heading * 6];
    s16 diff16 = diff;
    s16 wrapped;

    wrapped = diff;
    if (diff16 > 0xB4) {
        wrapped -= 0x168;
    } else if (diff16 < -0xB4) {
        wrapped += 0x168;
    }
    return (u16)(wrapped + 0x2C) < 0x59U;
}

s32 Link_PickFallStage(void *place, s32 stage, void *where, s32 timer) {
    FallLocation *location = where;
    s32 ret;

    if (stage != 3 && stage != 1 && stage != 5 && stage != 9 && stage != 12) {
        return -1;
    }
    if (stage == 5) {
        if (location->y >= -0xFFF && location->tile != g_fallPlace5) {
            return -1;
        }
    } else if (stage == 9) {
        if (location->y < 0x800) {
            return -1;
        }
    }
    if (timer & 1) {
        stage = -12;
    }
    ret = Spawn_PickRandom(place, stage, timer);
    g_linkToStage = ret;
    return ret;
}

s32 *Link_GetFallTurn(void) {
    s32 *r = NULL;
    if (g_linkToStage != 12) {
        r = g_fallTurn;
    }
    return r;
}

void Link_SetExtraListOn(s32 on) {
    g_extraListOn = on;
}

s32 Link_FindExtra(void *out, void *location, s32 stage) {
    if (g_extraListOn != 0) {
        return Link_Find(out, location, stage, &g_extraLinkCounts, &g_extraLinkLists, &g_extraLinkTargets, 0);
    }
    return -1;
}

s32 Link_GetExtraSeconds(void) {
    return g_linkFromStage == 0 ? 10 : 0;
}

s32 Link_FindScripted(void *out, void *location, s32 stage) {
    if (stage == 0) {
        return Link_Find(out, location, 0, g_scriptedLinkCounts, g_scriptedLinkLists, (SpawnPoint **)g_scriptedLinkTargets, 0);
    }
    return -1;
}

s32 Link_CheckScripted(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation) {
    u8 heading;

    heading = g_scriptedLinkHeadings[g_linkFromStage][g_linkFromIndex];
    if (Link_IsFacing(rotation, heading) != 0) {
        if (headingOut != 0) {
            *headingOut = g_linkHeadings + heading * 12;
        }
        if (arrivalOut != 0) {
            *arrivalOut = g_linkHeadings + g_scriptedArrivalHeadings[g_linkToStage][g_linkToIndex] * 12;
        }
        return 1;
    }
    return 0;
}

s32 Link_GetStepScript(void) {
    return g_scriptedLinkTargets[g_linkToStage][g_linkToIndex].stepScript;
}

static s32 Link_Find(void *place, void *location, s32 stage, u8 *counts, LinkEntry **lists, SpawnPoint **targets, s32 setNavFlag) {
    LinkEntry *entry;
    SpawnPoint *target;
    PlaceOut *out;
    s16 *key;
    s32 n;
    s32 i;
    s32 toStage;
    s32 toIndex;

    out = place;
    key = location;
    n = counts[stage];
    if (n != 0) {
        entry = lists[stage];
        for (i = 0; i < n; i++, entry++) {
            if (key[0] == entry->chunkKey && (key[1] == entry->tileKey || entry->tileKey < 0)) {
                g_linkFromStage = stage;
                g_linkFromIndex = i;
                toStage = entry->toStage;
                g_linkToStage = toStage;
                toIndex = entry->toIndex;
                target = targets[toStage] + toIndex;
                g_linkToIndex = toIndex;
                out->tile = target->tile;
                out->offset = g_tileOffsets[target->offsetIndex];
                if (setNavFlag != 0) {
                    g_navFlags[target->navFlag] = 1;
                }
                return g_linkToStage;
            }
        }
    }
    return -1;
}

s32 Spawn_PickFromMood(void *place, s32 *secondsOut, void *point, s32 day) {
    union {
        StageChunkPos chunk;
        s16 chunkKey; /* col | row << 8, as LinkEntry.chunkKey */
    } key;
    s32 idx;
    s32 cnt;
    s32 i;
    SpawnPoint *rec;
    PlaceOut *out;

    idx = Stage_FindChunkByMood(&key.chunk, point);
    if (idx >= 0) {
        *secondsOut = g_stageTimeLimits[idx];
        cnt = g_spawnCounts[idx];
        rec = g_spawnPoints[idx];
        for (i = 0; i < cnt; i++, rec++) {
            if (key.chunkKey == *(s16 *)rec) {
                goto found;
            }
        }
        rec = g_spawnPoints[idx] + key.chunkKey % cnt;
found:
        out = place;
        out->tile = rec->tile;
        out->offset = g_tileOffsets[rec->offsetIndex];
        return idx;
    }
    idx = Spawn_PickRandom(place, idx, day);
    *secondsOut = g_stageTimeLimits[idx];
    return idx;
}

MoodPoint *Day_FindSpecial(void *cinematic, s32 dayNumber) {
    CineId *o = cinematic;
    s32 i;

    for (i = 0; i < sizeof(g_specialDays) / sizeof(g_specialDays[0]); i++) {
        if (dayNumber == g_specialDays[i]) {
            o->variant = rand() % 6;
            o->category = i % 12;
            return &g_specialDayPoint;
        }
    }
    return NULL;
}

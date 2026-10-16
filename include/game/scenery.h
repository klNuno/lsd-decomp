#ifndef GAME_SCENERY_H
#define GAME_SCENERY_H

#include "common.h"

/*
 * The ambience record a place gets from Scenery_Begin (g_ambience, or a fixed one given to
 * load): Ambience_Fill fills +0xC to +0x1C from a 4-byte family record {unk0, unk1, unk2, unk3}
 * (work/hunt6/C-notes-note.md). +0x0 to +0x8 are static data handed to the map.
 */
/* A 4-byte ambience record: per stage (g_stageAmbience) or from a family table (g_ambienceFamilies, Ambience_PickFamily). */
typedef struct AmbienceRecord {
    s8 mode;      /* 0x0 Ambience.mode */
    s8 depth;     /* 0x1 index of g_ambienceDepths; 4 and up also make the extra object of Ambience_CreateTint */
    s8 colorB;    /* 0x2 RGB triple index (0x12 picks the second band palette) */
    s8 colorA;    /* 0x3 RGB triple index */
} AmbienceRecord;

typedef struct Ambience {
    s32 lightVectors;     /* 0x00 map slot 0xC4, second argument */
    s32 lightColors;     /* 0x04 map slot 0xC4, third argument */
    s32 ambient;     /* 0x08 map slot 0xBC */
    u8 *colorA;   /* 0x0C RGB triple of g_ambienceColors, record byte 3 */
    s32 unk10;
    s32 mode;     /* 0x14 record byte 0; picks colorA or colorB for the view (1 and 2 tested) */
    u8 *colorB;   /* 0x18 RGB triple of g_ambienceColors, record byte 2 */
    s32 depth;    /* 0x1C g_ambienceDepths[record byte 1]: 0x6800, 0x5000, 0x3800, 0x2000, 0x1000 or 0x800 */
} Ambience;

/* Functions of src/game/scenery.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in include/game/place.h, which includes this header */
struct PlaceRefs;
struct StageMap;
Ambience *Scenery_Begin(struct StageMap *map, s32 stage, struct PlaceRefs *refs, s32 dayNumber, s32 unused);
void Scenery_Teardown(void);
s32 Scenery_Tick(void *mapPos, s32 ignored, s32 found);
s32 Ambience_IsEvenFamily(void);

#endif

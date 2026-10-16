#include "common.h"
#include "game/scenery.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/handler_node.h"
#include "game/tim.h"
#include "game/view.h"
#include "game/box.h"
#include "game/place.h"
#include "game/scenery_obj.h"
#include "psyq/libc.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/* One word of g_sceneryParams, as Scenery_CreateKind2 writes unk1C and unk20. */
typedef struct ParamWord {
    s32 v;
} ParamWord;

/* A screen position, {x, y} (the band layout g_bandPos, g_bandSize). */
typedef struct Point {
    s32 x;
    s32 y;
} Point;

/* The ambience band objects (Box_Create): 18 in g_ambienceBands for family 0, one at g_ambienceTint. */
typedef struct AmbienceBandVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();   /* 0x04 Object_Delete */
    u8 pad_08[0x4C - 0x08];
    void (*attach)();     /* 0x4C (band, parent, position) */
    u8 pad_50[0x64 - 0x50];
    void (*setSemiTrans)();
    void (*setBlendMode)();
    u8 pad_6C[0xB8 - 0x6C];
    void (*setColor)();   /* 0xB8 (band, 1, RGB) */
    void (*setPos)();     /* 0xBC */
} AmbienceBandVtbl;

typedef struct AmbienceBand {
    AmbienceBandVtbl *vt;
} AmbienceBand;


/*
 * A spot: an 8-byte record of g_stageSoundSpots[stage] (count g_stageSoundSpotCounts[stage]) with a map tile
 * record, a handler index idx and a range class. While the dreamer is within g_soundSpotRanges[range]
 * (ground distance |dx| + |dz|), one of the two slots g_soundSpotSlots holds it and its handler
 * g_soundSpotHandlers[range] runs (SoundSpot_Acquire); the range is negated while it is held.
 */
typedef struct SpotTile {
    u8 b0, b1, b2, b3;    /* handed to map slot 0xE8 with the g_soundSpotTileExtras entry */
} SpotTile;

typedef struct SpotTileExtra {
    SpotTile tile;
    s16 v;
} SpotTileExtra;

typedef struct SpotRecord {
    SpotTile tile;        /* 0x0 */
    u8 idx;               /* 0x4 index of g_soundSpotTileExtras */
    u8 unk5;
    s8 range;             /* 0x6 > 0 free, < 0 held by a slot */
    u8 unk7;
} SpotRecord;

typedef struct SpotQuery {
    SpotTile a;
    SpotTileExtra b;
} SpotQuery;

/* The two slots (g_soundSpotSlots points into g_soundSpotSlotData, 0x68 bytes each). */
typedef struct SpotSlot {
    SpotRecord *record;   /* 0x00 */
    s32 pos[3];           /* 0x04 the spot's position (map slot 0xE8) */
    s32 distance;         /* 0x10 ground distance to the dreamer */
    HandlerNode node;     /* 0x14 registered with HandlerNode_Start; SoundSpot_CalcFade divides the range by its fadeSteps */
} SpotSlot;

/* .sdata owned by this unit (config/splat.yaml), defined at the end of the file: pairs read whole by Ambience_UpdateBands, Ambience_CreateBands */
extern Point g_bandPos;
extern Point g_bandSize;
s32 g_ambienceFamily;
extern s32 g_soundSpotRanges[];
s32 g_bandLayout;
s32 g_sceneryCount;
extern Scenery *g_scenery[];
u8 *g_ambienceTintColor;
AmbienceBand *g_ambienceTint;
static s32 SoundSpot_CalcFade(SpotSlot *slot);
static s32 SoundSpot_IsInRange(SpotSlot *slot, s32 *origin);
static SpotSlot *SoundSpot_Release(SpotSlot *slot);
PlaceRefs *g_placeRefs;
extern u8 g_ambienceColors[];
extern s32 g_ambienceDepths[];
extern ScreenRect g_clutCycleRectA[];
extern ScreenRect g_clutCycleSpareA[];
extern ScreenRect g_clutCycleRectB[];
extern ScreenRect g_clutCycleSpareB[];
s32 g_placeStage;
StageMap *g_sceneryMap;
s32 g_placeTicks;
s32 g_placeDayNumber;
s32 D_8008AC78;
extern s32 g_soundSpotSlot1;
static Ambience *Ambience_Get(void);
extern SpotSlot *g_soundSpotSlots[];
extern AmbienceRecord *g_stageAmbience[];
extern Ambience g_ambience;
static AmbienceRecord *Ambience_PickFamily(void);
static void Ambience_Fill(Ambience *ambience, AmbienceRecord *record);
void Scenery_RandomizeParams(void *origin, s32 height);
extern s32 g_sceneryHeights2;
extern u8 g_sceneryKind1Scale[];
extern SceneryParams g_sceneryParams;
void SoundSpot_Type11(SpotSlot *slot, HandlerNode *node);
extern AmbienceBand *g_ambienceBands[];
extern s32 g_ambienceTintPos[];
extern BoxSize g_ambienceTintSize[];
static SpotRecord *SoundSpot_FindInRange(s32 *pos, s32 *distance, s32 *origin);
extern void (*g_soundSpotHandlers[])();
extern s8 g_sceneryKind0Counts[];
static Scenery **Scenery_CreateKind0(Scenery **out, s32 count, void *origin);
static Scenery **Scenery_CreateKind1(Scenery **out, s32 count, void *origin);
static Scenery **Scenery_CreateKind3(Scenery **out, void *origin);
static Scenery **Scenery_CreateKind2(Scenery **out, void *origin);
s32 g_ambienceIndex;
u8 *g_bandPalette;
u8 *g_bandClearColor;
extern s8 g_ambienceFamilyCycle[];
extern s8 g_ambienceFamilyCounts[];
extern u8 g_bandPaletteA[];
extern u8 g_bandPaletteB[];
extern AmbienceRecord *g_ambienceFamilies[];
extern s32 g_sceneryHeights1;
extern u8 g_sceneryRotations[];
static void Scenery_RandomizeParamsDay7(void *origin, s32 height);
extern s32 g_sceneryHeights[];
extern u8 g_sceneryScales[];
s32 g_soundSpotNext;
extern SpotSlot g_soundSpotSlotData[];
static void Ambience_CreateBands(void);
static void Ambience_UpdateBands(void);
void Stage_CyclePalettes(void);
extern SpotTileExtra g_soundSpotTileExtras[];
extern SpotRecord *g_stageSoundSpots[];
extern u8 g_stageSoundSpotCounts[];
extern u8 g_sceneryKind3Colors[];
static void Ambience_ShiftRgb(u8 *out, u8 *rgb, s32 shift);
extern s32 g_sceneryDayMark;
extern u8 g_sceneryKind2Colors[];

/*
 * When a place loads (Place slot 0x4C): keep its map, stage, refs and day number, reset the
 * tick counter g_placeTicks and the two spot slots (g_soundSpotSlots[0..1], g_soundSpotSlot1 is [1]), and
 * return the ambience. Runs only while no place is up (g_sceneryMap is 0 again after Scenery_Teardown).
 */
Ambience *Scenery_Begin(StageMap *map, s32 stage, PlaceRefs *refs, s32 dayNumber, s32 unused) {
    s32 *slot;
    s32 n;

    if (g_sceneryMap == 0) {
        n = 1;
        slot = &g_soundSpotSlot1;
        g_sceneryMap = map;
        g_placeStage = stage;
        g_placeRefs = refs;
        g_ambienceFamily = -1;
        g_placeDayNumber = dayNumber;
        D_8008AC78 = unused;
        g_placeTicks = 0;
        do {
            *slot = 0;
            n -= 1;
            slot -= 1;
        } while (n >= 0);
        return Ambience_Get();
    }
    return 0;
}

/* The stage's fixed ambience record, else one of the day's family (Ambience_PickFamily), into g_ambience. */
static Ambience *Ambience_Get(void) {
    AmbienceRecord *record;

    record = g_stageAmbience[g_placeStage];
    if (record == NULL) {
        record = Ambience_PickFamily();
    }
    Ambience_Fill(&g_ambience, record);
    if (record->depth >= 4) {
        g_ambienceTintColor = g_ambienceColors + record->colorB * 3;
    }
    return &g_ambience;
}

static void Ambience_Fill(Ambience *ambience, AmbienceRecord *record) {
    ambience->colorA = g_ambienceColors + record->colorA * 3;
    ambience->colorB = g_ambienceColors + record->colorB * 3;
    ambience->depth = g_ambienceDepths[record->depth];
    ambience->mode = record->mode;
}

/* The extra ambience object, when the record's depth is 4 or more. */
static void Ambience_CreateTint(void) {
    AmbienceBand *band;
    View *view;

    if (g_ambienceTintColor != 0) {
        band = (AmbienceBand *)Box_Create(g_ambienceTintSize, g_ambienceTintColor, 0);
        g_ambienceTint = band;
        band->vt->setSemiTrans(band, 1);
        g_ambienceTint->vt->setBlendMode(g_ambienceTint, 0);
        view = g_placeRefs->view;
        g_ambienceTint->vt->attach(g_ambienceTint, view->vtbl->getOverlay(view), g_ambienceTintPos);
    }
}

static void Ambience_DeleteTint(void) {
    if (g_ambienceTintColor != 0) {
        g_ambienceTint->vt->delete_(g_ambienceTint);
        g_ambienceTintColor = 0;
    }
}

/*
 * The ambience family of the dream: g_ambienceFamilyCycle[(day number + stage) & 15], a 16-entry cycle over
 * 4 families, then record (day number + stage) % count (work/hunt6/C-notes-note.md). Family 0
 * also picks the band palette and, for records 0 to 5, the band layout (1 or 2).
 */
static AmbienceRecord *Ambience_PickFamily(void) {
    s32 sum;
    s32 family;
    s32 index;
    AmbienceRecord *record;
    u8 *palette;

    sum = g_placeDayNumber + g_placeStage;
    family = g_ambienceFamilyCycle[sum & 0xF];
    g_ambienceFamily = family;
    index = sum % g_ambienceFamilyCounts[family];
    g_ambienceIndex = index;
    record = g_ambienceFamilies[family] + index;
    if (family == 0) {
        g_bandClearColor = g_ambienceColors + record->colorA * 3;
        palette = g_bandPaletteB;
        if (record->colorB != 0x12) {
            palette = g_bandPaletteA;
        }
        g_bandPalette = palette;
        if (index < 4) {
            g_bandLayout = 1;
        } else if (index < 6) {
            g_bandLayout = 2;
        }
    }
    return record;
}

/* Make the 18 bands (run again by every first tick: the old ones are not freed, work/hunt6/F-findings.md). */
static void Ambience_CreateBands(void) {
    Point layout[2];
    s32 i;
    AmbienceBand *band;
    View *view;

    if (g_bandLayout != 0) {
        layout[0] = g_bandPos;
        if (g_bandLayout == 2) {
            layout[0].y += 0x1E;
        }
        layout[1] = g_bandSize;
        g_ambienceBands[0] = (AmbienceBand *)Box_Create((BoxSize *)&layout[1], g_bandPalette, 0x1FFF);
        for (i = 1; i < 0x12; i++) {
            band = (AmbienceBand *)Box_Create((BoxSize *)&layout[1], g_bandPalette + i * 3, 0x1FFF);
            g_ambienceBands[i] = band;
            band->vt->attach(band, g_ambienceBands[0], layout);
            layout[0].y += 3;
            layout[1].y -= 7;
        }
        view = g_placeRefs->view;
        g_ambienceBands[0]->vt->attach(g_ambienceBands[0], view->vtbl->getOverlay(view), layout);
    }
}

/* Every tick: shift the band colours and positions with the view's height. */
static void Ambience_UpdateBands(void) {
    u8 rgb[8];
    Point pos;
    View *view;
    AmbienceBand **band;
    s32 shift;
    s32 off;
    s32 i;

    if (g_bandLayout == 0) {
        return;
    }
    view = g_placeRefs->view;
    shift = ((view->viewpoint.y - view->refPoint.y) / 600) * 3;
    if (shift > 0) {
        pos = g_bandPos;
        i = 0;
        if (g_bandLayout == 2) {
            pos.y += 0x1E;
        }
        band = g_ambienceBands;
        off = 0;
        pos.y += shift * 3;
        for (; i < 18; i++) {
            Ambience_ShiftRgb(rgb, g_bandPalette + off, shift);
            (*band)->vt->setColor(*band, 1, rgb);
            (*band)->vt->setPos(*band, &pos);
            off += 3;
            pos.y += 3;
            band++;
        }
        Ambience_ShiftRgb(rgb, g_bandClearColor, shift);
        view->vtbl->setClearColor(view, rgb);
    }
}

/* out = rgb with red and green lowered and blue raised by shift. */
static void Ambience_ShiftRgb(u8 *out, u8 *rgb, s32 shift) {
    out[0] = rgb[0] - shift;
    out[1] = rgb[1] - shift;
    out[2] = rgb[2] + shift;
}

static void Ambience_DeleteBands(void) {
    if (g_bandLayout != 0) {
        Object_DeleteArray(g_ambienceBands, 0x12);
        g_bandLayout = 0;
    }
}

/*
 * First tick: the scenery objects into g_scenery around origin, g_sceneryCount of them
 * (work/hunt6/F-findings.md): count of kind 0 from g_sceneryKind0Counts, kind 1 up to 16 for family 2,
 * plus one of kind 3 for family 0 or of kind 2 for family 2.
 */
void Scenery_CreateAll(void *origin) {
    Scenery **end;
    s32 extra;
    s32 count;

    if (g_ambienceFamily >= 0) {
        Scenery_SetPlaceRefs(g_ambienceFamily, g_placeRefs->models, g_placeRefs->font, g_placeRefs->view);
        count = g_sceneryKind0Counts[rand() & 3];
        extra = (g_ambienceFamily == 2) ? (0x10 - count) : 0;
        g_sceneryCount = count + extra;
        end = Scenery_CreateKind1(Scenery_CreateKind0(g_scenery, count, origin), extra, origin);
        if (g_ambienceFamily == 0) {
            Scenery_CreateKind3(end, origin);
            g_sceneryCount += 1;
        } else if (g_ambienceFamily == 2) {
            Scenery_CreateKind2(end, origin);
            g_sceneryCount += 1;
        }
    }
}

/* Every tick: slot 0xEC (Scenery_Update) of every scenery object. */
static void Scenery_UpdateAll(void *origin) {
    s32 i;
    Scenery **objs;

    if (g_ambienceFamily >= 0) {
        objs = g_scenery;
        for (i = 0; i < g_sceneryCount; i++) {
            Scenery *obj = objs[i];
            obj->vt->update(obj, origin);
        }
    }
}

static void Scenery_DeleteAll(void) {
    if (g_ambienceFamily >= 0) {
        Object_DeleteArray(g_scenery, g_sceneryCount);
    }
}

/* When the place goes (Place slot 0x50): free the extra object, the bands, the scenery and the spots. */
void Scenery_Teardown(void) {
    s32 i;

    Ambience_DeleteTint();
    Ambience_DeleteBands();
    Scenery_DeleteAll();
    for (i = 0; i < 2; i++) {
        g_soundSpotSlots[i] = SoundSpot_Release(g_soundSpotSlots[i]);
    }
    if (g_sceneryMap != 0) {
        g_sceneryMap = 0;
    }
}

/* Kind 0: count objects at random offsets (Scenery_RandomizeParamsDay7 on day numbers divisible by 7, else Scenery_RandomizeParams). */
static Scenery **Scenery_CreateKind0(Scenery **out, s32 count, void *origin) {
    void (*randomize)(void *, s32);
    s32 i;
    s32 height;

    g_sceneryParams.variant = rand() % 7;
    g_sceneryParams.scale = &g_sceneryScales[((u32)rand() % 5) * 12];
    height = (u32)rand() % 5;
    if (height != 0) {
        height = g_sceneryHeights[height];
    }

    randomize = Scenery_RandomizeParamsDay7;
    if (g_placeDayNumber % 7 != 0) {
        randomize = Scenery_RandomizeParams;
    }

    for (i = 0; i < count; i++) {
        randomize(origin, height);
        *out = Scenery_New(0, &g_sceneryParams, g_sceneryMap, origin);
        out++;
    }
    return out;
}

/* Kind 1 */
static Scenery **Scenery_CreateKind1(Scenery **out, s32 count, void *origin) {
    s32 i;
    s32 height = g_sceneryHeights2;

    g_sceneryParams.scale = g_sceneryKind1Scale;
    for (i = 0; i < count; i++) {
        Scenery_RandomizeParams(origin, height);
        *out = Scenery_New(1, &g_sceneryParams, g_sceneryMap, origin);
        out++;
    }
    return out;
}

/* Kind 3, one object: a fixed offset with the second band palette, else a random one behind the origin. */
static Scenery **Scenery_CreateKind3(Scenery **out, void *origin) {
    Scenery_RandomizeParams(origin, g_sceneryHeights2);
    if (g_bandLayout != 0 && g_bandPalette == g_bandPaletteB) {
        g_sceneryParams.x = 0xFFFF5000;
        g_sceneryParams.y = -0x2000;
        g_sceneryParams.z = 0;
        g_sceneryParams.color = g_sceneryKind3Colors + 3;
    } else {
        if (g_sceneryParams.z > 0) {
            g_sceneryParams.z = -g_sceneryParams.z;
        }
        if (g_sceneryParams.z < -0x7800) {
            g_sceneryParams.z = -0x7800;
        }
        g_sceneryParams.color = g_sceneryKind3Colors + ((u32)rand() % 3) * 3;
    }
    g_sceneryParams.rotation = g_sceneryRotations;
    *out++ = Scenery_New(3, &g_sceneryParams, g_sceneryMap, origin);
    return out;
}

/* Kind 2, one object: a colour of g_sceneryKind2Colors, and dayMark g_sceneryDayMark (0 on day numbers divisible by 20). */
static Scenery **Scenery_CreateKind2(Scenery **out, void *origin) {
    ParamWord *p;
    u8 **q;
    s32 x;
    s32 v;

    v = (s32)(g_sceneryKind2Colors + ((u32)rand() % 3) * 3);
    p = (ParamWord *)&g_sceneryParams.color;
    p->v = v;
    p++;
    if (g_placeDayNumber % 20) {
        x = g_sceneryDayMark;
    } else {
        x = g_placeDayNumber % 20;
    }
    p->v = x;
    Scenery_RandomizeParams(origin, g_sceneryHeights2);
    q = &g_sceneryParams.rotation;
    *q = g_sceneryRotations;
    g_sceneryParams.variant = rand() % 6;
    *out++ = Scenery_New(2, &g_sceneryParams, g_sceneryMap, origin);
    return out;
}

/* Random offset: x and z in -22..22 tiles (<< 11), y = height (or one of g_sceneryHeights when 0). */
void Scenery_RandomizeParams(void *origin, s32 height) {
    if (height == 0) {
        height = g_sceneryHeights[rand() & 3];
    }
    g_sceneryParams.y = height;
    g_sceneryParams.x = (rand() % 23) << 11;
    if (rand() & 1) {
        g_sceneryParams.x = -g_sceneryParams.x;
    }
    g_sceneryParams.z = (rand() % 23) << 11;
    if (rand() & 1) {
        g_sceneryParams.z = -g_sceneryParams.z;
    }
    g_sceneryParams.rotation = g_sceneryRotations + ((u32)rand() % 7) * 12;
    g_sceneryParams.direction = rand() % 5;
}

/* Day numbers divisible by 7: x in 0..19 tiles, z 0xA000, -0x6000 or 0x800 by day number % 3. */
static void Scenery_RandomizeParamsDay7(void *origin, s32 height) {
    s32 v;
    s32 m;

    rand();
    g_sceneryParams.y = g_sceneryHeights1;
    v = rand();
    g_sceneryParams.z = 0xA000;
    g_sceneryParams.x = (v % 20) << 11;
    m = g_placeDayNumber % 3;
    if (m == 1) {
        g_sceneryParams.z = 0xFFFF6000;
    } else if (m == 2) {
        g_sceneryParams.z = 0x800;
    }
    g_sceneryParams.rotation = g_sceneryRotations + ((u32)rand() % 7) * 12;
    g_sceneryParams.direction = rand() % 5;
}

/* Hold the next free spot in range of origin in slot and register its handler. */
static SpotSlot *SoundSpot_Acquire(SpotSlot *slot, s32 *found, void *origin, s32 unused) {
    SpotRecord *record;

    record = SoundSpot_FindInRange(slot->pos, &slot->distance, origin);
    if (record != NULL) {
        slot->record = record;
        HandlerNode_Start(g_placeRefs->handlerList, &slot->node, record->range, slot, g_soundSpotHandlers[record->range]);
        if (record->range == *found) {
            *found = -record->range;
        }
        record->range = -record->range;
        return slot;
    }
    return NULL;
}

/* Walk the stage's spots from g_soundSpotNext and return the first free one within its range of origin. */
static SpotRecord *SoundSpot_FindInRange(s32 *pos, s32 *distance, s32 *origin) {
    SpotQuery query;
    SpotRecord *record;
    s32 *from;
    s32 i;
    s32 n;
    s32 dx;
    s32 dz;
    s32 dist;

    from = origin;
    if (from != NULL) {
        n = g_stageSoundSpotCounts[g_placeStage] - g_soundSpotNext;
        record = g_stageSoundSpots[g_placeStage] + g_soundSpotNext;
        for (i = 0; i < n; i++, record++) {
            g_soundSpotNext++;
            if (record->range > 0) {
                query.a = record->tile;
                query.b = g_soundSpotTileExtras[record->idx];
                g_sceneryMap->vtbl->placeToWorld(g_sceneryMap, pos, &query);
                dx = pos[0] - from[0];
                if (dx < 0) {
                    dx = ~dx + 1;
                }
                dz = pos[2] - from[2];
                dist = dx + (dz < 0 ? ~dz + 1 : dz);
                *distance = dist;
                if (dist < g_soundSpotRanges[record->range]) {
                    return record;
                }
            }
        }
    }
    return NULL;
}

/* Release a slot: unregister its handler and free its spot. */
static SpotSlot *SoundSpot_Release(SpotSlot *slot) {
    HandlerNode_Stop(g_placeRefs->handlerList, &slot->node);
    slot->record->range = -slot->record->range;
    return NULL;
}

static s32 SoundSpot_Update(SpotSlot *slot, void *origin, s32 unused) {
    if (SoundSpot_IsInRange(slot, origin) != 0) {
        HandlerNode_Run(g_placeRefs->handlerList, &slot->node);
        return 1;
    }
    return 0;
}

/* Is the held spot still within its range of origin (the range is negative while held)? */
static s32 SoundSpot_IsInRange(SpotSlot *slot, s32 *origin) { s32 dx,dz,d; if (origin != NULL) {
    dx = slot->pos[0] - origin[0];
    if (dx < 0) dx = ~dx + 1;
    dz = slot->pos[2] - origin[2];
    d = dx + (dz < 0 ? ~dz + 1 : dz);
    slot->distance = d;
    if (d < g_soundSpotRanges[-slot->record->range]) return 1; } return 0; }

/*
 * The scenery tick (Place slot 0x8C), with the map position of the dreamer. On the first tick
 * after a place starts (g_placeTicks reads 0) it makes the extra object, the bands and the
 * scenery; zeroing g_placeTicks makes them again without freeing the old ones (the "location_time"
 * leak, work/hunt6/F-findings.md). Then it updates them and the two spot slots, and returns the
 * range of a spot just taken when it equals found.
 */
s32 Scenery_Tick(void *mapPos, s32 ignored, s32 found) {
    s32 posBuf[4];
    void *origin;
    s32 i;
    s32 unused;
    SpotSlot **slot;

    origin = 0;
    if (mapPos != 0) {
        origin = posBuf;
        g_sceneryMap->vtbl->placeToWorld(g_sceneryMap, origin, mapPos);
    }
    if (g_placeTicks++ == 0) {
        Ambience_CreateTint();
        Ambience_CreateBands();
        Scenery_CreateAll(origin);
    }
    Ambience_UpdateBands();
    Scenery_UpdateAll(origin);
    Stage_CyclePalettes();
    g_soundSpotNext = 0;
    slot = g_soundSpotSlots;
    for (i = 0; i < 2; i++, slot++) {
        if (*slot != NULL) {
            if (SoundSpot_Update(*slot, origin, ignored) == 0) {
                *slot = SoundSpot_Release(*slot);
            }
        } else {
            *slot = SoundSpot_Acquire(&g_soundSpotSlotData[i], &found, origin, ignored);
        }
    }
    return found;
}

void Stage_CyclePalettes(void) {
    if (g_placeStage == 2) {
        Display_RotateRect(g_clutCycleRectA, 1, g_clutCycleSpareA);
    } else if (g_placeStage >= 3 && g_placeStage < 6) {
        Display_RotateRect(g_clutCycleRectB, 1, g_clutCycleSpareB);
    }
}

/* Spot handlers (table g_soundSpotHandlers, by range): slot is the SpotSlot, node its handler node (voices 0 to 2, fade from SoundSpot_CalcFade). */
void SoundSpot_Type1(SpotSlot *slot, HandlerNode *node) {
    s32 tick;

    node->fade = SoundSpot_CalcFade(slot);
    tick = node->tick;
    if (tick == 0) {
        node->voices[0].sound = 7;
        node->voices[0].octave = 0;
    } else if (tick == 2) {
        node->voices[1].sound = 7;
        node->voices[1].octave = 0;
    } else if (tick == 5) {
        node->voices[2].sound = 7;
        node->voices[2].octave = 0;
    } else if (tick >= 8) {
        node->tick = -1;
    }
}

void SoundSpot_Type2(SpotSlot *slot, HandlerNode *node) {
    node->fade = SoundSpot_CalcFade(slot);
    if (node->tick == 0) {
        node->voices[0].sound = 0x18;
        node->voices[0].octave = -2;
        return;
    }
    if (node->tick >= 0x401) {
        node->tick = -1;
    }
}

void SoundSpot_Type3(SpotSlot *slot, HandlerNode *node) {
    s32 tick;

    node->fade = SoundSpot_CalcFade(slot);
    tick = node->tick;
    if (tick == 0) {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = 2;
        return;
    }
    if (tick >= 5) {
        node->tick = -1;
    }
}

void SoundSpot_Type4(SpotSlot *slot, HandlerNode *node) {
    node->fade = SoundSpot_CalcFade(slot);
    if (node->tick % 20 == 0) {
        node->voices[0].sound = 0x1E;
        node->voices[0].volume = 0x20;
        node->voices[0].octave = 0;
        node->voices[0].endVolume = 0xA;
    }
    if (node->tick % 400 == 0) {
        node->voices[1].sound = 0x1E;
        node->voices[1].octave = 0;
    }
    node->voices[2].sound = 6;
    node->voices[2].volume = 0x20;
    node->voices[2].octave = 0;
    node->voices[2].endVolume = 0xA;
}

void SoundSpot_Type5(SpotSlot *slot, HandlerNode *node) {
    node->fade = SoundSpot_CalcFade(slot);
    if (node->tick % 3 == 0) {
        node->voices[0].sound = 0x1E;
        node->voices[0].octave = 0;
    }
    if (node->tick % 5 == 0) {
        node->voices[1].sound = 0x1E;
        node->voices[1].octave = 0;
        node->voices[1].volume = 0x18;
        node->voices[1].endVolume = 0x18;
    }
    if (node->tick % 7 == 0) {
        node->voices[0].sound = 0x1E;
        node->voices[0].octave = 0;
    }
    node->voices[2].sound = 6;
    node->voices[2].octave = 1;
    node->voices[2].volume = 0x2A;
    node->voices[2].endVolume = 0xA;
}

void SoundSpot_Type6(SpotSlot *slot, HandlerNode *node) {
    node->fade = SoundSpot_CalcFade(slot);
    if (node->tick == 0) {
        node->voices[0].sound = 0x1E;
        node->voices[0].octave = -1;
        return;
    }
    if (node->tick < 50 && node->tick % 5 == 4) {
        node->voices[1].sound = 0x1E;
        node->voices[1].octave = 0;
        node->voices[1].endVolume = node->voices[1].volume -= node->tick * 2;
        return;
    }
    if (node->tick >= 0x65 && node->tick < 0x6E) {
        node->voices[2].sound = 0xD;
        node->voices[2].octave = 1;
        return;
    }
    if (node->tick >= 0xC9) {
        node->tick = -1;
    }
}

void SoundSpot_Type7(SpotSlot *slot, HandlerNode *node) {
    s32 tick;

    node->fade = SoundSpot_CalcFade(slot);
    tick = node->tick;
    if (tick == 0) {
        node->voices[0].sound = 7;
        node->voices[0].octave = 2;
        return;
    }
    if (tick >= 0x1B) {
        node->tick = -1;
    }
}

void SoundSpot_Type8(SpotSlot *slot, HandlerNode *node) {
    s32 tick;

    node->fade = SoundSpot_CalcFade(slot);
    tick = node->tick;
    if (tick == 0) {
        node->voices[0].sound = 0x14;
        node->voices[0].octave = 1;
        return;
    }
    if (tick == 3) {
        node->voices[0].octave = 2;
        node->voices[0].volume = 0x18;
        node->voices[0].sound = 3;
        node->voices[0].endVolume = 0x14;
        return;
    }
    if (tick >= 0x33) {
        node->tick = -1;
    }
}

void SoundSpot_Type9(SpotSlot *slot, HandlerNode *node) {
    node->fade = SoundSpot_CalcFade(slot);
    if (node->tick % 20 == 0) {
        node->voices[0].sound = 9;
        node->voices[0].octave = 0;
        node->voices[0].volume = 0x40;
        node->voices[0].endVolume = 0x40;
    }
}

void SoundSpot_Type10(SpotSlot *slot, HandlerNode *node) {
    node->fade = SoundSpot_CalcFade(slot);
    if (node->tick == ((node->tick / 20) * 20)) {
        node->voices[0].sound = 9;
        node->voices[0].octave = -2;
    }
}

void SoundSpot_Type11(SpotSlot *slot, HandlerNode *node) {
    s32 phase;

    node->fade = SoundSpot_CalcFade(slot);
    phase = node->tick % 20;
    if (phase == 1) {
        node->voices[0].sound = 9;
        node->voices[0].octave = -2;
    } else if (phase == 16) {
        node->voices[1].sound = 9;
        node->voices[1].octave = -2;
    }
}

void SoundSpot_Type12(SpotSlot *slot, HandlerNode *node) {
    s32 phase;

    SoundSpot_Type11(slot, node);
    phase = node->tick % 70;
    if (phase == 50) {
        node->voices[2].sound = 20;
        node->voices[2].octave = 1;
    } else if (phase >= 54 && phase < 59) {
        node->voices[2].sound = 13;
        node->voices[2].octave = 1;
    } else if (phase == 61) {
        node->voices[2].sound = 9;
        node->voices[2].octave = -1;
    }
}

void SoundSpot_Type13(SpotSlot *slot, HandlerNode *node) {
    s32 tick;

    node->fade = SoundSpot_CalcFade(slot);
    tick = node->tick;
    if (tick == 0) {
        node->voices[0].sound = 0x14;
        node->voices[0].octave = -2;
        node->voices[1].sound = 0x14;
        node->voices[1].octave = -2;
        return;
    }
    if (tick == 4) {
        node->voices[1].sound = 0x14;
        node->voices[1].octave = -2;
        return;
    }
    if (tick == 20) {
        node->voices[0].sound = 0x10;
        node->voices[0].octave = -2;
        node->voices[1].sound = 0x12;
        node->voices[1].octave = -2;
        return;
    }
    if (tick >= 0xC9) {
        node->tick = -1;
    }
}

void SoundSpot_Type14(SpotSlot *slot, HandlerNode *node) {
    node->fade = SoundSpot_CalcFade(slot);
    if (node->tick == 0) {
        node->voices[0].sound = 0x18;
        node->voices[0].octave = 0;
    }
}

/* distance / (range / node.fadeSteps): grows with the distance to the spot. */
static s32 SoundSpot_CalcFade(SpotSlot *slot) {
    return slot->distance / (g_soundSpotRanges[-slot->record->range] / slot->node.fadeSteps);
}

/* Spawn rule 7 (Sym_CheckRule): 1 when the ambience family is even, 0 for odd ones and none (-1). */
s32 Ambience_IsEvenFamily(void) {
    return (g_ambienceFamily & 1) ^ 1;
}

Point g_bandPos = { -100, -60 };
Point g_bandSize = { 0x140, 0x90 };

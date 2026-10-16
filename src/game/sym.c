#include "common.h"
#include "game/sym.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/file_base.h"
#include "game/mom.h"
#include "game/mml.h"
#include "game/stage_map.h"
#include "game/scenery.h"
#include "game/dream_sys.h"
#include "game/dream_link.h"
#include "game/entity.h"
#include "psyq/libc.h"

/*
 * Sym: entities loaded from ETC\SYM*.MOM; only SYMSPY.MOM is loaded.
 *
 * File boundaries: likely (docs/layout.md)
 */

DreamSys *g_symDreamSys;
/* The source record a spawned model is built from: a FileSource (file_base.h) for Mml_Create, the model at +0xC for Entity_Create. */
typedef struct SpawnSource {
    FileSource file;
    Mom *model;
} SpawnSource;
extern s8 g_ruleColors[];
/* g_spyModel: the model loaded from ETC\SYMSPY.MOM and the Grey Man entity built on it */
typedef struct SpyModel {
    Mom *model;
    Entity *spy;
    s32 spawnOffset;
    u8 pad_0C[0x8];
} SpyModel;
extern SpyModel g_spyModel[];
typedef struct SpyEntityRef {
    Entity *obj;
    u8 pad[0x14 - 4];
} SpyEntityRef;
extern SpyEntityRef g_spyEntity[];
s32 g_currentStage;
extern s8 g_spawnSlotCounts[];
extern SpawnSlot *g_spawnSlots[];
static SpawnSlot *Sym_PickSlotVariant(SpawnSlot *slot, s32 index);
static void Sym_InitExtraList(s32);
StageMap *g_symMap;
SoundBank *g_symSoundBank;
void *g_symClock;
static SpawnSlot *Sym_FindSlot(s16 *chunkKey);
static s32 Sym_CheckDayParity(s32 dayNumber, SpawnSlot *slot);
static Mml *Sym_SpawnSlot(s32 dayNumber, SpawnSlot *slot, u8 *square);
static void Sym_SpawnSpy(SpyModel *spyModel);
static s32 Sym_SpawnGroup();
extern SpawnGroup *g_spawnGroups[];
extern s8 g_spawnGroupCounts[];

static void Sym_CheckExtraListType(s32 type);
s32 Sym_CheckRule(s32 dayNumber, SpawnGroup *group);
static s32 Sym_SpawnAtPlace(s32 type, SpawnSource *source, SpawnSlot *slot, s32 place);
static s32 Sym_CheckColorRule(s32 rule);
static s32 Sym_CheckMonthRule(s32 dayNumber, s32 month);
/* The 6-byte records of g_spawnPlaceOffsets: four bytes copied whole, then the height. */
typedef struct SpawnPlaceOffset {
    u8 bytes[4];
    s16 height;
} SpawnPlaceOffset;
/* The query StageMap_PlaceToWorld reads: the slot's chunk key, the place's first word, then the offset record. */
typedef struct SpawnQuery {
    u16 chunkKey;
    u16 placeWord;
    SpawnPlaceOffset offset;
} SpawnQuery;

extern SpawnPlace g_spawnPlaces[];
extern SpawnPlaceOffset g_spawnPlaceOffsets[];
extern u8 g_spawnPlaceRotations[];

void Sym_LoadModels(void) {
    FileSource file;
    u32 i;
    s32 j;

    /* clear the done flag of every spawn group of every stage */
    for (i = 0; i < 14; i++) {
        for (j = 0; j < g_spawnGroupCounts[i]; j++) {
            g_spawnGroups[i][j].done = 0;
        }
    }
    File_MakeSource(&file, 0, "ETC\\SYMSPY.MOM", 1);
    /* one pass: SYMDOG.MOM would be the second model, the loop never reaches it */
    for (i = 0; i < 1; i++) {
        g_spyModel[i].model = Mom_Create(&file);
        file.path = "ETC\\SYMDOG.MOM";
    }
}

void Sym_FreeModels(void) {
    SpyModel *entry;
    u32 i;

    entry = g_spyModel;
    for (i = 0; i < 1; i++) {
        if (entry->model != NULL) {
            entry->model = entry->model->vtbl->base.delete_(entry->model);
        }
        entry++;
    }
}

void Sym_InitStage(s32 stage, StageMap *map, DreamSys *dreamSys, void *soundBank, void *watched) {
    SpawnSource source;
    SpyModel *entry;
    u32 i;

    entry = g_spyModel;
    g_currentStage = stage;
    g_symMap = map;
    g_symDreamSys = dreamSys;
    g_symSoundBank = soundBank;
    g_symClock = watched;
    /* entity type 0x62 = 98, the Grey Man */
    for (i = 0; i < 1; i++) {
        source.model = entry->model;
        entry->spy = Entity_Create(i + 0x62, &source, g_symSoundBank);
        entry++;
    }
    Sym_InitExtraList(stage);
}

static void Sym_InitExtraList(s32 stage) {
    s32 extraList;

    extraList = 0;
    if ((stage == 0xB) || (stage == 3)) {
        extraList = 1;
    }
    Link_SetExtraListOn(extraList);
}

static void Sym_CheckExtraListType(s32 type) {
    switch (type) {
        case 0xB:
        case 0x38:
        case 0x4E:
        case 0x5D:
            Link_SetExtraListOn(1);
            break;
    }
}

void Sym_FreeSpy(void) {
    SpyEntityRef *entry;
    u32 i;

    for (i = 0, entry = g_spyEntity; i < 1; i++) {
        if (entry->obj != NULL) {
            entry->obj = entry->obj->vt->delete_(entry->obj);
        }
        entry++;
    }
}

Mml *Sym_SpawnOrSpy(u8 *square, void *chunkKey, s32 dayNumber) {
    SpawnSlot *slot;

    slot = Sym_FindSlot(chunkKey);
    if (slot != NULL) {
        if (Sym_CheckDayParity(dayNumber, slot) != 0) {
            return Sym_SpawnSlot(dayNumber, slot, square);
        }
        if (g_currentStage != 0) {
            if (rand() % 12 == 0 && !(dayNumber & 1)) {
                Sym_SpawnSpy(g_spyModel);
            }
        }
    }
    return NULL;
}

static SpawnSlot *Sym_FindSlot(s16 *chunkKey) {
    SpawnSlot *slot;
    s32 i;
    s32 count;
    s32 pad[2];

    count = g_spawnSlotCounts[g_currentStage];
    slot = g_spawnSlots[g_currentStage];
    i = 0;
    if (count > 0) {
        do {
            if (*chunkKey == slot->chunkKey) {
                return Sym_PickSlotVariant(slot, i);
            }
            i++;
            slot++;
        } while (i < count);
    }
    return NULL;
}

/* Stage 4, slot 16: on a red day (colour 4) use slot 21, 30 bytes further. */
static SpawnSlot *Sym_PickSlotVariant(SpawnSlot *slot, s32 index) {
    s32 stage = g_currentStage;

    if (stage == 4 && index == 0x10) {
        if (g_symDreamSys->vtbl->getDreamColor(g_symDreamSys) == stage) {
            slot += 5;
        }
    }
    return slot;
}

static s32 Sym_CheckDayParity(s32 dayNumber, SpawnSlot *slot) {
    s32 pass;
    s8 parity;

    parity = slot->dayParity;
    pass = 1;
    if (parity != 0) {
        dayNumber = (dayNumber % 2) + 1;
        pass = parity != dayNumber;
    }
    return pass;
}

static Mml *Sym_SpawnSlot(s32 dayNumber, SpawnSlot *slot, u8 *square) {
    SpawnSource source;
    Mml *squareObj;
    s8 *group;
    s8 *end;
    SpawnGroup *groups;

    source.file.data = square;
    squareObj = Mml_Create(&source.file);
    if (squareObj != NULL) {
        group = slot->groups;
        end = slot->groups + 3;
        groups = g_spawnGroups[g_currentStage];
        while (group < end && *group != -1) {
            Sym_SpawnGroup(dayNumber, slot, groups + *group, squareObj);
            group++;
        }
        return squareObj;
    }
    return NULL;
}

static s32 Sym_SpawnGroup(s32 dayNumber, SpawnSlot *slot, SpawnGroup *group, Mml *squareObj) {
    SpawnSource source;
    s8 *place;
    s8 *placesEnd;
    Mom *model;

    if (Sym_CheckRule(dayNumber, group) != 0) {
        place = group->places;
        Sym_CheckExtraListType(group->type);
        model = squareObj->vtbl->getMom(squareObj, group->model);
        source.model = model;
        placesEnd = group->places + 4;
        if (model != NULL) {
            for (; place < placesEnd && *place != -1; place++) {
                if (Sym_SpawnAtPlace(group->type, &source, slot, (u8)*place) != 0) {
                    return 1;
                }
            }
        }
        /* a type 2 group also tries the group seven entries further (0x38 bytes) */
        if (group->type == 2) {
            return Sym_SpawnGroup(dayNumber, slot, group + 7, squareObj);
        }
    }
    return 0;
}

s32 Sym_CheckRule(s32 dayNumber, SpawnGroup *group) {
    SpawnGroup *p;
    s8 rule;
    s32 n;
    s32 pass;

    p = group;
    rule = p->rule;
    if (rule == 1) {
        p->done = 1;
        return 1;
    }
    /* a negative rule passes once, until Sym_LoadModels clears the flag */
    if (rule < 0 && p->done != 0) {
        return 0;
    }
    n = rule < 0 ? ~rule + 1 : rule;
    switch (n) {
        case 2:
        case 3:
        case 4:
            pass = Sym_CheckMonthRule(dayNumber, n - 1);
            break;
        case 5:
            if (dayNumber == (dayNumber / 3) * 3) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 6:
            if (dayNumber != (dayNumber / 3) * 3) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 7:
            pass = Ambience_IsEvenFamily();
            break;
        case 8:
        case 9:
            if (dayNumber % 3 == n - 7) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 20:
            if ((dayNumber & 1) == 0) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 21:
            pass = dayNumber & 1;
            break;
        default:
            if (n < 10) {
                p->done = 1;
                return 1;
            }
            pass = Sym_CheckColorRule(n);
            break;
    }
    if (pass != 0) {
        p->done = 1;
        return 1;
    }
    return 0;
}

/* Rules 10 to 17: g_ruleColors[rule - 10] is the mood colour the day must have (DreamSys vtable 0x200). */
static s32 Sym_CheckColorRule(s32 rule) {
    s32 colour;

    colour = g_ruleColors[rule - 10];
    return colour == g_symDreamSys->vtbl->getDreamColor(g_symDreamSys);
}

/* Rules 2 to 4: the 30-day month (day - 1) / 30 + 1 equals month, month + 3, + 6 or + 9. */
static s32 Sym_CheckMonthRule(s32 dayNumber, s32 month) {
    s32 i;
    s32 n;

    n = ((dayNumber - 1) / 30) + 1;
    for (i = 0; i < 4; i++) {
        if (n == month) {
            return 1;
        }
        month += 3;
    }
    return 0;
}

static s32 Sym_SpawnAtPlace(s32 type, SpawnSource *source, SpawnSlot *slot, s32 place) {
    SpawnQuery query;
    s32 placement[4];
    Entity *entity;
    SpawnPlace *placeInfo;
    s32 recIndex;

    entity = Entity_Create(type, source, g_symSoundBank);
    if (entity != NULL) {
        query.chunkKey = slot->chunkKey;
        placeInfo = &g_spawnPlaces[place];
        query.placeWord = placeInfo->tile;
        recIndex = placeInfo->offsetIndex;
        query.offset = g_spawnPlaceOffsets[recIndex];
        g_symMap->vtbl->placeToWorld(g_symMap, placement, &query);
        entity->vt->rotate(entity, 1, &g_spawnPlaceRotations[placeInfo->rotationIndex * 12]);
        entity->vt->attach(entity, g_symDreamSys, g_symClock, g_symMap, placement);
        return 0;
    }
    return 1;
}

static void Sym_SpawnSpy(SpyModel *spyModel) {
    s32 placement[4];
    Entity *spy;

    spy = spyModel->spy;
    if (spy != NULL) {
        spy->vt->detach(spy);
        SceneNode_LocalToWorld(g_symDreamSys, placement, &spyModel->spawnOffset, 0);
        spyModel->spy->vt->attach(spyModel->spy, g_symDreamSys, g_symClock, g_symMap, placement);
        Entity_FaceDreamer(spyModel->spy, g_symDreamSys, 1, 0, 0);
    }
}

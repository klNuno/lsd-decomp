#include "common.h"
#include "game/place.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/view.h"
#include "game/fade.h"
#include "game/label.h"
#include "game/tix.h"
#include "game/map_chunk.h"
#include "game/path_table.h"
#include "game/stage.h"
#include "game/task.h"
#include "game/stage_map.h"
#include "game/scenery.h"
#include "game/dream_sys.h"
#include "game/sym.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/* The dream runner's object at +0xC (src/game/dream_runner.c): slot 0xC8 registers a callback with an argument. */
typedef struct PlaceOwnerObjVtbl {
    u8 pad_00[0xC8];
    void (*setCallback)(void *, void (*)(Place *, s32, s32, s32), void *);
} PlaceOwnerObjVtbl;
typedef struct PlaceOwnerObj {
    PlaceOwnerObjVtbl *vt;
} PlaceOwnerObj;
typedef struct PlaceOwner {
    u8 pad_00[0xC];
    PlaceOwnerObj *callbackObj;
} PlaceOwner;
static void Place_CheckTextureLoad(Place *place, PlaceTexLoader *loader);
/* the vtable of task.c through this file's view of its slots, so not from game/task.h */
PlaceBaseVtbl *Task_GetVtbl();
void Place_StartFade(Place *place, s32 color, s32 holdMode, s32 duration, s32 watch);
static void Place_GetChunkPath(Place *place, s32 result, s32 col, s32 row);
static PlaceVtbl *Place_GetVtbl(void);
extern u8 g_pauseText[];
extern s32 g_pauseTextPos[];
extern s32 g_pauseTextColor[];
extern PlaceVtbl g_placeVtbl;
extern s32 g_placeViewpoint[];
extern s32 g_placeRefPoint[];
extern s32 g_placeMapMessageFilter[];
s32 g_placeProjectionOffset;
extern s32 g_stageBoxMargins[];
extern s32 g_stage0Bounds[];

/* Allocate a place (0x88 bytes) and construct it (slot 0x08); called by the dream runner DreamRunner_CreateStage. */
void *Place_New(SoundBank *handlerList, void *music, void *font, void *models, s32 stage) {
    void *place;

    place = Heap_Alloc(0x88);
    if (place != NULL) {
        Place_GetVtbl()->construct(place, handlerList, music, font, models, stage);
        return place;
    }
    return NULL;
}

/* Slot 0x08 */
void Place_Construct(Place *place, SoundBank *handlerList, PlaceObj *music, void *font, PlaceObj *models, s32 stage) {
    Task_GetVtbl()->construct(place, 0, handlerList);
    place->vt = Place_GetVtbl();
    place->ready = 0;
    place->started = 0;
    place->texLoading = 1;
    place->music = music;
    place->stage = stage;
    place->refs.handlerList = handlerList;
    place->refs.font = font;
    place->refs.models = models;
    place->pauseOpen = 0;
    place->exitArmed = 0;
    place->vt->reset(place);
}

/* Slot 0x0C */
void Place_Destruct(s32 place) {
    Task_GetVtbl(place)->destruct(place);
}

/*
 * Slot 0x38: a watched object sent a message. The first word of the sender's vtable is its
 * class id: DreamSys (0x1F34) goes to slot 0x90, ids ending in 0x164 (the fader) to 0xB0,
 * ids ending in 0x114 (the map) to 0xB4.
 */
void Place_OnNotify(Place *place, s32 **sender, s32 message) {
    s32 classId;

    Task_GetVtbl()->onNotify(place, sender, message);
    classId = **sender;
    if ((classId & 0xFFF) == 0x114) {
        place->vt->onMapNotify(place, sender, message);
    } else if ((classId & 0xFFF) == 0x164) {
        place->vt->onFaderNotify(place, sender, message);
    } else if ((classId & 0xFFFF) == 0x1F34) {
        place->vt->onDreamSysNotify(place, sender, message);
    }
}

void Place_EmptySlot40(void) {
}

/* Slot 0x44: keep the DreamSys and register Place_GetChunkPath with the runner's object. */
void Place_Attach(Place *place, PlaceOwner *owner, DreamSys *dreamSys) {
    PlaceOwnerObj *obj;

    obj = owner->callbackObj;
    obj->vt->setCallback(obj, &Place_GetChunkPath, place);
    place->dreamSys = dreamSys;
    Task_GetVtbl()->attach(place, owner, 1);
    place->vt->watch(place, dreamSys);
}

static void Place_GetChunkPath(Place *place, s32 result, s32 col, s32 row) {
    if (result >= 0) {
        Stage_GetChunkPath(place->stage);
    } else {
        Stage_GetChunkPathAt(place->stage, col, row);
    }
}

/* Slot 0x48 */
void Place_Detach(Place *place) {
    place->vt->unwatch(place, place->dreamSys);
    Task_GetVtbl()->detach(place);
}

/*
 * Slot 0x4C, when a stage loads: picks the music track (Music_PickTrack) and starts the
 * texture-set loader (Stage_PickTexturePath, Tix_Create), starts the scenery
 * (Scenery_Begin, which gives the ambience) and sets the state to 5.
 */
void Place_Load(Place *place, s32 viewDistance, Ambience *ambience, s32 ambienceGiven) {
    View *view;
    s32 mode;

    view = place->view;
    view->vtbl->detach(view);
    place->texLoading = 1;
    place->music->vt->setSeq(place->music, Music_PickTrack(place->stage, 0));
    place->texLoader = Tix_Create(Stage_PickTexturePath(place->stage, 0, place->dreamSys->vtbl->getDayNumber(place->dreamSys, 0)));
    view->vtbl->setCamera(view, place->dreamSys, g_placeViewpoint, g_placeRefPoint, 0);
    place->refs.view = view;
    place->ambience = Scenery_Begin(place->map, place->stage, &place->refs, place->dreamSys->vtbl->getDayNumber(place->dreamSys, 0), 0);
    if (ambience != 0) {
        place->ambience = ambience;
    }
    place->unk4C = ambienceGiven;
    if (place->stage != 0) {
        place->linkPeriod = 0x10;
        place->moveSpeed = 3;
        mode = place->stage == 5;
        if (place->stage == 6) {
            mode = 1;
        }
        if (place->stage == 3) {
            mode = 1;
        }
        place->map->vtbl->setBounds(place->map, NULL);
    } else {
        place->linkPeriod = 0x10;
        place->moveSpeed = 2;
        mode = 1;
        place->map->vtbl->setBounds(place->map, g_stage0Bounds);
    }
    place->viewDistance = viewDistance;
    if (viewDistance == 0) {
        place->viewDistance = 0xA000;
    }
    SceneNode_SetRayHeightCheck(mode);
    place->dreamSys->vtbl->setBoxMargin(place->dreamSys, g_stageBoxMargins[place->stage]);
    place->state = 5;
}

/* Slot 0x50: teardown (called without the place), free the scenery, stop the music object. */
void Place_Unload(Place *place) {
    PlaceObj *music;

    place->vt->teardown();
    Sym_FreeSpy();
    Scenery_Teardown();
    music = place->music;
    music->vt->stop(music);
}

/* Slot 0x54 */
void Place_OnDisplay(Place *place, s32 sender, s32 event) {
    if (event == 2) {
        Place_CheckTextureLoad(place, place->texLoader);
    }
}

/*
 * Check the texture-set loader. When it failed (+0x80, a heap allocation returned 0) the set
 * is dropped and the time limit becomes elapsed + 30 s (discoveries "the 30-second dreams");
 * when it is done the ambience colour goes to it. Then, once the map is ready, start the place.
 */
static void Place_CheckTextureLoad(Place *place, PlaceTexLoader *loader) {
    PlaceTexLoaderVtbl *vt;
    Ambience *ambience;
    u8 *color;

    if (place->texLoading != 0) {
        if (loader->failed != 0) {
            loader->vt->delete_(loader);
            place->texLoading = 0;
            place->vt->setup(place);
            place->dreamSys->vtbl->swapTimeLimit(place->dreamSys, place->dreamSys->vtbl->getElapsedSeconds(place->dreamSys) + 0x1E);
        } else if (loader->done != 0) {
            ambience = place->ambience;
            vt = loader->vt;
            if (ambience->mode != 2) {
                color = ambience->colorB;
            } else {
                color = ambience->colorA;
            }
            vt->apply(loader, color);
            loader->vt->delete_(loader);
            place->texLoading = 0;
            place->vt->setup(place);
        }
        if (place->texLoading != 0) {
            return;
        }
    }
    if (place->map->pendingSlots == 0 && place->started == 0) {
        place->ready = 1;
        place->vt->start(place);
    }
}

/* Slot 0x58, the pad handler: 33 START, 12 SELECT held, 22 TRIANGLE, 44 SELECT released (discoveries "the hidden exit"). */
void Place_OnPad(Place *place, s32 sender, s32 code) {
    PlaceVtbl *vt;
    void (*fn)();

    vt = place->vt;
    if (place->started != 0) {
        switch (code) {
        case 33:
            fn = vt->togglePause;
            break;
        case 12:
            fn = vt->armExit;
            break;
        case 22:
            fn = vt->confirmExit;
            break;
        case 44:
            fn = vt->disarmExit;
            break;
        default:
            return;
        }
        fn(place);
    }
}

/* Slot 0x5C, every tick once started: the pause window while it is open, else the update. */
void Place_Tick(Place *place) {
    if (place->started != 0) {
        place->ticks = place->ticks + 1;
        if (place->pauseOpen != 0) {
            place->vt->updatePause(place);
        } else {
            place->vt->update(place);
        }
    }
}

/* Slot 0x74, START */
void Place_TogglePause(Place *place) {
    PlaceVtbl *vt;

    vt = place->vt;
    if (place->pauseOpen != 0) {
        vt->disarmExit(place);
        vt->closePause(place);
    } else {
        vt->updatePause(place);
    }
}

void Place_EmptySlot7C(void) {
}

/* Slot 0x80, after the texture set: hands the stage to the spawn code (Sym_InitStage) and sets up the map. */
void Place_Setup(Place *place) {
    View *view;
    StageMap *map;
    Ambience *ambience;
    PlaceObj *first;
    DreamSys *dreamSys;

    view = place->view;
    ambience = place->ambience;
    view->vtbl->detach(view);
    first = *place->env;
    view->vtbl->setProjection(view, (((*first->vt->getScreenRect(first, 0) / 2) * 5) / 3) + g_placeProjectionOffset);
    view->vtbl->setCamera(view, place->dreamSys, g_placeViewpoint, g_placeRefPoint, 0);
    Sym_InitStage(place->stage, place->map, place->dreamSys, place->sound, place->clock);
    map = place->map;
    place->vt->watch(place, map);
    map->vtbl->setAmbient(map, ambience->ambient, 0);
    map->vtbl->setLights(map, 3, ambience->lightVectors, ambience->lightColors);
    map->vtbl->setGrid(map, Stage_GetGrid(place->stage));
    dreamSys = place->dreamSys;
    dreamSys->vtbl->enterMap(dreamSys, map);
    map->vtbl->setViewDistance(map, place->viewDistance);
    map->vtbl->setMessageFilter(map, g_placeMapMessageFilter);
}

/* Slot 0x84 */
void Place_Teardown(Place *place) {
    place->vt->closePause(place);
    place->dreamSys->vtbl->lockControls(place->dreamSys);
    place->dreamSys->vtbl->leaveMap(place->dreamSys);
    place->view->vtbl->detach(place->view);
    place->vt->unwatch(place, place->map);
}

/* Slot 0x88: the place starts; the view takes the ambience colours and the fader the day's colour. */
void Place_Start(Place *place) {
    s32 color;
    DreamSys *dreamSys;
    StageMap *map;
    View *view;
    Ambience *ambience;
    Fade *fader;
    s32 flashbackMode;

    place->started = 1;
    place->dreamSys->vtbl->startPlace(place->dreamSys, place->moveSpeed, place->linkPeriod);
    map = place->map;
    map->vtbl->activate(map);
    view = place->view;
    ambience = place->ambience;
    view->vtbl->setLightMode(view, 1);
    view->vtbl->setClearColor(view, ambience->colorA);
    view->vtbl->setFogNear(view, ambience->depth);
    view->vtbl->setFogColor(view, ambience->mode != 1 ? ambience->colorB : ambience->colorA);
    view->vtbl->setExtraSwap(view, 0);
    view->vtbl->setPresentEnabled(view, 1);
    fader = view->vtbl->getOverlay(view);
    place->vt->watch(place, fader);
    dreamSys = place->dreamSys;
    flashbackMode = dreamSys->vtbl->setFlashbackMode(dreamSys, &color, -1);
    fader->vtbl->setTint(fader, flashbackMode, flashbackMode != 0 ? 3 : 0);
    fader->vtbl->startIn(fader, place->clock, flashbackMode != 0 ? color : -1, 0);
}

/* Slot 0x8C, every tick while not paused: the scenery tick at the map's position. */
void Place_Update(Place *place) {
    StageMap *map = place->map;
    Scenery_Tick(map->vtbl->getLocation(map, 0, 0), 0, 0);
}

/* Slot 0x90: DreamSys messages 10 to 17 go to slots 0x94 to 0xAC while the state is 0. */
void Place_OnDreamSysNotify(Place *place, s32 sender, s32 message) {
    s32 event;

    if (place->state == 0) {
        event = message - 10;
        switch (event) {
            case 0:
                place->vt->onEvent10(place, sender, event);
                break;
            case 1:
                break;
            case 2:
                place->vt->onEvent12(place, sender, event);
                break;
            case 3:
                place->vt->onEvent13(place, sender, event);
                break;
            case 4:
                place->vt->onEvent14(place, sender, event);
                break;
            case 5:
                place->vt->onEvent15(place, sender, event);
                break;
            case 6:
                place->vt->onEvent16(place, sender, event);
                break;
            case 7:
                place->vt->onEvent17(place, sender, event);
                break;
        }
    } else if (message >= 9) {
        place->dreamSys->transition = 0;
    }
}

/* Slot 0x94: state 4; out of a flashback, (ticks + stage) & 3 picks no fade (notify 4) or colour 0, 4 or 7. */
void Place_OnTimeUp(Place *place) {
    s32 color;
    s32 phase;
    s32 pick;
    s32 flashbackMode;
    s32 duration;
    DreamSys *dreamSys;

    dreamSys = place->dreamSys;
    place->state = 4;
    flashbackMode = dreamSys->vtbl->setFlashbackMode(dreamSys, &color, -1);
    if (flashbackMode == 0) {
        phase = (place->ticks + place->stage) & 3;
        pick = phase;
        if (phase == 0) {
            place->vt->notify(place, 4);
            return;
        }
        duration = 0xA;
        switch (pick) {
        case 1:
            color = 0;
            break;
        case 2:
            color = 4;
            break;
        case 3:
            color = 7;
            duration = 5;
            break;
        }
        Place_StartFade(place, color, 0, duration, 1);
    } else {
        Place_StartFade(place, 0, 0, 5, 1);
    }
}

/* Slot 0x98: state 5, fade to the dream colour (slot 0x200), or go to slot 0x9C when DreamSys +0x164 is negative. */
void Place_OnLinkDynamic(Place *place) {
    DreamSys *dreamSys;

    if (place->dreamSys->stage < 0) {
        place->vt->onEvent13(place);
    } else {
        place->state = 5;
        dreamSys = place->dreamSys;
        Place_StartFade(place, dreamSys->vtbl->getDreamColor(dreamSys), 0, 0xA, 1);
        dreamSys = place->dreamSys;
        dreamSys->vtbl->lockControls(dreamSys);
    }
}

/* Slot 0x9C: state 6, a 30-tick fade to the dream colour. */
void Place_OnLinkStatic(Place *place) {
    DreamSys *dreamSys;

    dreamSys = place->dreamSys;
    place->state = 6;
    Place_StartFade(place, dreamSys->vtbl->getDreamColor(dreamSys), 0, 0x1E, 1);
    dreamSys = place->dreamSys;
    dreamSys->vtbl->lockControls(dreamSys);
}

/* Slot 0xA0: state 7, fade to the day's colour. */
void Place_OnNextFlashback(Place *place) {
    s32 color;
    DreamSys *dreamSys;

    dreamSys = place->dreamSys;
    place->state = 7;
    dreamSys->vtbl->setFlashbackMode(dreamSys, &color, -1);
    Place_StartFade(place, color, 0, 5, 1);
    dreamSys = place->dreamSys;
    dreamSys->vtbl->lockControls(dreamSys);
}

/* Slot 0xA4 */
void Place_OnLink15(Place *place) {
    place->state = 8;
    Place_StartFade(place, 0, 0, 6, 1);
    place->dreamSys->vtbl->setAutoWalk(place->dreamSys, 1);
}

/* Slot 0xA8 */
void Place_OnLink16(Place *place) {
    place->state = 10;
    Place_StartFade(place, 0, 0, 6, 1);
    place->dreamSys->vtbl->setMoveMode(place->dreamSys, 2);
    place->dreamSys->vtbl->setAutoWalk(place->dreamSys, 2);
}

/* Slot 0xAC */
void Place_OnLink17(Place *place) {
    place->vt->notify(place, 0xB);
}

/* Start the view's fader towards a colour index (0 to 7), watched when asked. */
void Place_StartFade(Place *place, s32 color, s32 holdMode, s32 duration, s32 watch) {
    View *view;
    Fade *fader;

    view = place->view;
    fader = view->vtbl->getOverlay(view);
    if (duration != 0) {
        fader->vtbl->setStep(fader, duration);
    }
    if (watch != 0) {
        place->vt->watch(place, fader);
    }
    fader->vtbl->startOut(fader, place->clock, color, holdMode);
}

/* Slot 0xB0: the fader is done (5: back to state 0; 6: its colour goes to the view, state 10 becomes 4). */
void Place_OnFaderNotify(Place *place, Fade *fader, s32 message) {
    void *color;

    switch (message) {
    case 5:
        place->vt->unwatch(place, fader);
        place->dreamSys->vtbl->setAutoWalk(place->dreamSys, 0);
        place->state = 0;
        break;
    case 6:
        place->vt->unwatch(place, fader);
        color = fader->vtbl->getColor(fader);
        place->view->vtbl->setClearColor(place->view, color);
        if (place->state == 5 || place->state == 8) {
        } else if (place->state == 10) {
            place->dreamSys->vtbl->endFall(place->dreamSys, 1);
            place->dreamSys->vtbl->setAutoWalk(place->dreamSys, 0);
            place->state = 4;
        }
        place->vt->notify(place, place->state);
        break;
    }
}

/* Slot 0xB4: map message 7 runs slot 0xB8 (called without arguments; a0 still holds the place). */
void Place_OnMapNotify(Place *place, s32 sender, s32 message) {
    if (message == 7) {
        place->vt->spawnCell();
    }
}

/* Slot 0xB8: spawn the characters of the map cell under the dreamer (Sym_SpawnOrSpy, discoveries "Grey Man spawn"). */
s32 Place_SpawnCell(Place *place) {
    s32 chunkKey;
    StageMap *map;
    DreamSys *dreamSys;
    MapChunk *chunk;
    MapSlot *slot;
    s32 dayNumber;
    struct Mml *spawned;

    map = place->map;
    slot = map->vtbl->currentSlot(map, &chunkKey);
    dreamSys = place->dreamSys;
    dayNumber = dreamSys->vtbl->getDayNumber(dreamSys, 0);
    spawned = Sym_SpawnOrSpy(slot->chunk->entities, &chunkKey, dayNumber);
    slot->spawned = (Object *)spawned;
    if (spawned != 0) {
        return 0;
    }
    chunk = slot->chunk;
    chunk->vtbl->freeEntities(chunk);
    return 1;
}

void Place_EmptySlotBC(void) {
}

/* Slot 0xC0, SELECT held: arms the exit while the pause is open and the state is 0. */
void Place_ArmExit(Place *place) {
    if (place->pauseOpen != 0 && place->state == 0) {
        place->exitArmed = 1;
    }
}

/* Slot 0xC4, SELECT released */
void Place_DisarmExit(Place *place) {
    place->exitArmed = 0;
}

/* Slot 0xC8, TRIANGLE: when armed, close the pause and send 0xD (DreamSys_EndDay(2), a new game). */
void Place_ConfirmExit(Place *place) {
    if (place->exitArmed != 0) {
        place->vt->closePause(place);
        place->vt->notify(place, 0xD);
    }
}

/* Slot 0xCC, never called: send 0xC (DreamSys_EndDay(1), the day is restored). */
void Place_ExitNoRecord(Place *place) {
    if (place->exitArmed != 0) {
        place->vt->closePause(place);
        place->vt->notify(place, 0xC);
    }
}

/* Slot 0xD0: open the pause window ("Pause"), and suspend the place's objects on its fourth tick. */
void Place_UpdatePause(Place *place) {
    s32 ticks = place->pauseOpen;

    if (ticks == 0) {
        place->pauseText = (Widget *)Label_Create(place->refs.font, 5, g_pauseText);
        place->pauseText->vtbl->show(place->pauseText, place->map, g_pauseTextPos);
        place->pauseText->vtbl->setColor(place->pauseText, g_pauseTextColor);
        place->pauseOpen = 1;
        return;
    }
    place->pauseOpen = ticks + 1;
    if (ticks == 4) {
        place->view->vtbl->setPresentEnabled(place->view, 0);
        place->clock->vt->pause(place->clock);
        place->music->vt->pause(place->music);
        place->sound->vt->muteBank(place->sound);
    }
}

/* Slot 0xD4: close the pause window and resume the objects. */
void Place_ClosePause(Place *place) {
    if (place->pauseOpen != 0) {
        place->pauseText->vtbl->delete_(place->pauseText);
    }
    place->sound->vt->unmuteBank(place->sound);
    place->music->vt->resume(place->music);
    place->clock->vt->resume(place->clock);
    place->view->vtbl->setPresentEnabled(place->view, 1);
    place->pauseOpen = 0;
}

static PlaceVtbl *Place_GetVtbl(void) {
    return &g_placeVtbl;
}

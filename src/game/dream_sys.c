#include "common.h"
#include "game/dream_sys.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/sound_bank.h"
#include "game/handler_node.h"
#include "game/view.h"
#include "game/stage.h"
#include "game/actor.h"
#include "game/dream_link.h"
#include "psyq/libc.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

static s32 Mood_GetColor(s16 *point);
static s32 DreamSys_ExecuteLink();
extern u8 g_turnRotations[];
/* The StageMap (stage_map.h) as DreamSys_OnMapMessage calls it: slot 0x10C StageMap_GetLocation. */
typedef struct MapLocateVtbl {
    u8 pad_00[0x10C];
    s32 (*getLocation)(void *, s32, s32);
} MapLocateVtbl;
typedef struct MapLocateView {
    MapLocateVtbl *vt;
} MapLocateView;
/* g_actorVtbl (0x800878D4), the Actor base class (src/game/actor.c), as the DreamSys methods call it. */
typedef struct ActorVtblView {
    u8 pad_00[0x8];
    void (*init)(void *);                       /* 0x08 Actor_Construct */
    u8 pad_0C[0x50 - 0x0C];
    void (*detach)(void *);                     /* 0x50 SceneNode_Detach */
    u8 pad_54[0x9C - 0x54];
    void (*onNode)(void *, s32 **, s32);        /* 0x9C Actor_OnNode */
    u8 pad_A0[0xDC - 0xA0];
    void (*onNode34)(void *, s32 **, s32);      /* 0xDC Actor_OnNode34 */
    void (*onNode24)(void *, s32 **, s32);      /* 0xE0 Actor_OnNode24 */
} ActorVtblView;
/* the vtable of actor.c through this file's view of its slots, so not from game/actor.h */
ActorVtblView *Actor_GetVtbl(void);
/* A rotation in degrees (three Fractions, SceneNode_GetRotation) read for its yaw numerator. */
typedef struct RotationYaw {
    u8 pad_00[4];
    u16 yaw;
} RotationYaw;
s32 g_saveMagic;
static DreamSysVtbl *DreamSys_GetVtable(void);
extern s32 g_dreamerStartRotation[];
static s32 Mood_CalcAxis(s32, s32, s32);
extern s32 g_fallStep[];
extern s8 g_moodColors[][3];
extern s16 g_linkStep2Start[];
extern u8 g_yawPlus45[];
static void DreamSys_MoveToTileOffset(DreamSys *, s16 *, s16 *);
extern s32 g_pointAheadZ[];
static s32 DreamSys_GetSightHeight(ScreenVec *start, ScreenVec *end, s32 pos);
extern s16 g_linkStep0Start[];
extern s32 g_pitchSteps[];
extern s32 g_pitchLimits[];
/* The Tmd (tmd.h) slot 0x80 Tmd_GetModel (tmd, index). */
typedef struct TmdModelVtbl {
    u8 pad_00[0x80];
    s32 (*getModel)(void *, s32);
} TmdModelVtbl;
extern s8 g_stepSoundTones[];
extern s8 g_stepSoundOctaves[];
/* The StageMap slot 0xE4 StageMap_SetTarget (map, out position, target, place). */
typedef struct MapTargetVtbl {
    u8 pad_00[0xE4];
    void (*setTarget)(void *, void *, void *, void *);
} MapTargetVtbl;
/* g_actorVtbl slot 0x4C SceneNode_Attach, called with the map and the start position. */
typedef struct ActorAttachVtbl {
    u8 pad_00[0x4C];
    void (*attach)(void *, void *, void *);
} ActorAttachVtbl;
extern s16 g_linkStep1Start[];
extern u8 g_yawMinus45[];
/* g_actorVtbl slot 0x88 Actor_SendBoxes. */
typedef struct ActorBoxesVtbl {
    u8 pad_00[0x88];
    void (*sendBoxes)(void *, s32);
} ActorBoxesVtbl;
extern s16 g_linkStep3Start[];
/* What SceneNode_GetRotation writes: three Fractions of degrees (x, y, z). */
typedef struct RotationDegrees {
    s16 xNum;
    s16 xDen;
    s16 yNum;
    s16 yDen;
    s16 zNum;
    s16 zDen;
} RotationDegrees;
extern s32 g_lookBackSteps[];
extern s32 g_lookBackLimits[];
extern s16 g_turnRotationYaw[];
static void DreamSys_ReverseDirection(DreamSys *dreamSys);
extern u8 g_dreamSysVtbl[];
extern s32 g_walkSpeeds[];
extern s8 g_walkSigns[];
extern void (*g_walkMoves[])(void *, s32, s32);
/* The entity vtable (0x80089AD4, entity.h) as DreamSys_OnEntityEvent calls it. */
typedef struct EventEntityVtbl {
    u8 pad_00[0x38];
    void (*onNotify)(void *, void *, s32);      /* 0x38 Model_OnNotify */
    u8 pad_3C[0x14C - 0x3C];
    s32 (*getRecord)(void *);                   /* 0x14C Entity_GetRecord: the record starts with its mood point */
    s32 (*getPoints)(void *);                   /* 0x150 Entity_GetPoints */
    s32 (*getLinkStage)(void *);                /* 0x154 Entity_GetLinkStage */
    s32 (*getVideo)(void *);                    /* 0x158 Entity_GetVideo */
} EventEntityVtbl;
extern s32 (*g_linkSteps[])(void *);

void *DreamSys_New(s32 tmd, s32 soundBank, s32 camera) {
    void *dreamSys;

    dreamSys = Heap_Alloc(0x928);
    if (dreamSys != 0) {
        DreamSys_GetVtable()->init(dreamSys, tmd, soundBank, camera);
        return dreamSys;
    }
    return 0;
}

void DreamSys_Init(DreamSys *dreamSys, void **tmd, s32 soundBank, s32 camera) {
    Actor_GetVtbl()->init(dreamSys);
    dreamSys->vtbl = (DreamSysVtbl *)DreamSys_GetVtable();
    dreamSys->soundBank = soundBank;
    dreamSys->camera.obj = camera;
    dreamSys->etcTim = 0;
    dreamSys->tmd = tmd;
    dreamSys->vtbl->watch(dreamSys, ((TmdModelVtbl *)*tmd)->getModel(tmd, 0));
    dreamSys->vtbl->swapTimeLimit(dreamSys, -1);
    dreamSys->controlsLocked = 1;
    dreamSys->autoWalk = 0;
    dreamSys->neverSaved = 1;
    dreamSys->vtbl->initNewGame(dreamSys);
    dreamSys->vtbl->reset(dreamSys);
}

void DreamSys_Reset(DreamSys *dreamSys) {
    dreamSys->vtbl->setVisible(dreamSys, 0);
    dreamSys->vtbl->setRotation(dreamSys, 1, g_dreamerStartRotation);
    dreamSys->lookHandler = 0;
    dreamSys->moveHandler = 0;
    dreamSys->fallSound.word = 0;
    dreamSys->ignorePad = 0;
    dreamSys->skipMoveBoxes = 0;
    dreamSys->linkStep = 0;
    dreamSys->unk78 = 0;
    dreamSys->unk924 = 0;
}

void DreamSys_EnterMap(DreamSys *dreamSys, void **map) {
    s32 startPos[4];
    Flashback *elem;
    void *arrivalHeading;

    ((MapTargetVtbl *)*map)->setTarget(map, startPos, dreamSys, (u8 *)dreamSys + 0x16C);
    ((ActorAttachVtbl *)Actor_GetVtbl())->attach(dreamSys, map, startPos);
    dreamSys->vtbl->watch(dreamSys, map);
    if (dreamSys->transition == 0xE) {
        elem = &dreamSys->save.flashbacks[dreamSys->nextFlashback];
        dreamSys->vtbl->setRotation(dreamSys, 1, elem->rotation.bytes);
        dreamSys->vtbl->swapTimeLimit(dreamSys, elem->length + 4);
        dreamSys->nextFlashback++;
    }
    if (dreamSys->autoWalk != 0) {
        arrivalHeading = dreamSys->arrivalHeading;
        if (arrivalHeading != 0) {
            dreamSys->vtbl->setRotation(dreamSys, 1, arrivalHeading);
        }
    }
}

void DreamSys_LeaveMap(DreamSys *dreamSys) {
    DreamPlayer *map;

    map = dreamSys->map;
    map->vt->deactivate(map);
    dreamSys->vtbl->unwatch(dreamSys, dreamSys->map);
    Actor_GetVtbl()->detach(dreamSys);
}

void DreamSys_OnGroundProbe(DreamSys *dreamSys, s32 message) {
    s32 groundSound;
    DreamPlayer *map;
    DreamPlayer *map2;

    ((ActorBoxesVtbl *)Actor_GetVtbl())->sendBoxes(dreamSys, message);
    switch (message) {
    case -1:
        groundSound = dreamSys->contact->flags & 0x7F;
        dreamSys->stepSound = groundSound;
        if (groundSound >= 0x18) {
            dreamSys->stepSound = 0;
        }
        if (dreamSys->transition == 0xF && dreamSys->stepSound == 0) {
            dreamSys->stepSound = 2;
        }
        if (dreamSys->stage == 9) {
            map = dreamSys->map;
            dreamSys->vtbl->linkFall(dreamSys, map->vt->getLocation(map, 0, 0));
        }
        return;
    case -2:
        map2 = dreamSys->map;
        if (map2->vt->slotAt(map2, dreamSys->pos.bytes + 0x18)->chunk->loaded == 2) {
            map = dreamSys->map;
            dreamSys->vtbl->linkFall(dreamSys, map->vt->getLocation(map, 0, 0));
        } else {
            dreamSys->vtbl->restorePosition(dreamSys);
        }
        return;
    }
}

void DreamSys_OnPad(DreamSys *dreamSys, s32 sender, s32 code) {
    if (dreamSys->autoWalk == 0 && dreamSys->controlsLocked == 0) {
        code -= 2;
        if (dreamSys->ignorePad == 0) {
            switch (code) {
                case 0:
                    dreamSys->walkDirection = 1;
                    break;
                case 1:
                    dreamSys->walkDirection = 2;
                    break;
                case 2:
                    dreamSys->turnInput = 1;
                    break;
                case 3:
                    dreamSys->turnInput = 2;
                    break;
                case 4:
                    dreamSys->pitchInput = 1;
                    break;
                case 5:
                    if (dreamSys->walkDirection == 1) {
                        dreamSys->vtbl->pushSpeed(dreamSys, 4);
                    }
                    break;
                case 6:
                    dreamSys->pitchInput = 2;
                    break;
                case 11:
                    dreamSys->lookBackInput = 2;
                    break;
                case 12:
                    dreamSys->walkDirection = 4;
                    break;
                case 13:
                    dreamSys->lookBackInput = 1;
                    break;
                case 14:
                    dreamSys->walkDirection = 3;
                    break;
                case 23:
                    dreamSys->circlePressed = 1;
                    break;
                case 32:
                    dreamSys->vtbl->popSpeed(dreamSys, sender, code);
                    break;
                case 47:
                    break;
            }
        }
    }
}

void DreamSys_TickTimer(DreamSys *dreamSys, s32 sender, s32 message) {
    u32 ticks;

    if (message == 2) {
        ticks = dreamSys->timer;
        dreamSys->timer = ticks + 1;
        if (ticks >= (u32) dreamSys->timeLimit) {
            if (dreamSys->flashbackMode != 0) {
                if (dreamSys->transition != 0 || dreamSys->vtbl->loadNextFlashback(dreamSys, 0) != 0) {
                reset:
                    dreamSys->timer = 0;
                    return;
                }
            } else {
                dreamSys->vtbl->maybeSaveFlashback(dreamSys, 0, 0x10);
            }
            dreamSys->vtbl->notify(dreamSys, 0xA);
            goto reset;
        }
        dreamSys->vtbl->tickBegin(dreamSys);
        dreamSys->vtbl->tickHandlers(dreamSys);
    }
}

void DreamSys_RouteMapMessage(DreamSys *dreamSys, s32 **sender, s32 message) {
    Actor_GetVtbl()->onNode(dreamSys, sender, message);
    if ((**sender & 0xFFF) == 0x114) {
        dreamSys->vtbl->onMapMessage(dreamSys, sender, message);
    }
}

void DreamSys_RouteEntityMessage(DreamSys *dreamSys, s32 **sender, s32 message) {
    Actor_GetVtbl()->onNode34(dreamSys, sender, message);
    if ((**sender & 0xFFFFF) == 0x1F234) {
        dreamSys->vtbl->onEntityEvent(dreamSys, sender, message);
    }
}

void DreamSys_OnWallTouch(DreamSys *dreamSys, s32 **sender, s32 message) {
    DreamPlayer *map;
    StagePlace *touched;

    Actor_GetVtbl()->onNode24(dreamSys, sender, message);
    if (message == 4 && dreamSys->transition == 0) {
        map = dreamSys->map;
        touched = map->vt->getTellKey(map, sender);
        dreamSys->place = *touched;
        if (dreamSys->vtbl->linkStatic(dreamSys, &dreamSys->place) == 0 && dreamSys->dynamicLinkOn != 0) {
            dreamSys->vtbl->linkDynamic(dreamSys);
        }
        dreamSys->vtbl->restorePosition(dreamSys);
        dreamSys->vtbl->afterWallTouch(dreamSys);
    }
}

void DreamSys_EmptySlotE8(void) {
}

s32 DreamSys_SetFlashbackMode(DreamSys *dreamSys, s32 *colorOut, s32 mode) {
    s32 oldMode;

    oldMode = dreamSys->flashbackMode;
    if (mode < 0) {
        *colorOut = Mood_GetColor((s16 *)((u8 *)dreamSys + (dreamSys->save.day * 2 + 0x190)));
    } else {
        dreamSys->flashbackMode = mode;
    }
    return oldMode;
}

void DreamSys_SetAutoWalk(DreamSys *dreamSys, s32 mode) {
    s32 heading;

    dreamSys->autoWalk = mode;
    if (mode != 0) {
        dreamSys->vtbl->swapSpeed(dreamSys, 1);
        heading = dreamSys->linkHeading;
        if (heading != 0) {
            dreamSys->vtbl->setRotation(dreamSys, 1, heading);
        }
    }
}

void DreamSys_StartPlace(DreamSys *dreamSys, s32 speed, s32 linkPeriod) {
    RotationDegrees rotation;

    dreamSys->vtbl->logChunkMood(dreamSys, &dreamSys->place);
    dreamSys->vtbl->setLookMode(dreamSys, 1);
    dreamSys->vtbl->setMoveMode(dreamSys, 1);
    dreamSys->vtbl->swapSpeed(dreamSys, speed);
    dreamSys->stepVoice = -1;
    dreamSys->stepTick = 0;
    dreamSys->stepSound = 0;
    dreamSys->walkDirection = 0;
    dreamSys->turnInput = 0;
    dreamSys->pitchInput = 0;
    dreamSys->lookBackInput = 0;
    dreamSys->pitch = 0;
    dreamSys->lookBackYaw = 0;
    dreamSys->vtbl->setLinkFlags(dreamSys, 0, 1, 1, 1);
    dreamSys->vtbl->setLinkPeriod(dreamSys, linkPeriod);
    dreamSys->cinematic.id.variant = -1;
    dreamSys->controlsLocked = 0;
    dreamSys->transition = 0;
    dreamSys->circlePressed = 0;
    dreamSys->ignorePad = 0;
    dreamSys->skipMoveBoxes = 0;
    dreamSys->linkStep = 0;
    dreamSys->unk78 = 0;
    SceneNode_GetRotation(dreamSys, (s32 *)&rotation);
    rotation.zNum = 0;
    rotation.zDen = 1;
    dreamSys->vtbl->setRotation(dreamSys, 1, &rotation);
}

void DreamSys_LockControls(DreamSys *dreamSys) {
    dreamSys->controlsLocked = 1;
}

s32 DreamSys_WasCirclePressed(DreamSys *dreamSys) {
    return dreamSys->circlePressed;
}

s32 DreamSys_SwapTimeLimit(DreamSys *dreamSys, s32 seconds) {
    s32 old;

    if (seconds >= 0) {
        seconds *= 15;
    }
    old = dreamSys->timeLimit;
    dreamSys->timeLimit = seconds;
    if (old >= 0) {
        old = (u32)old / 15;
    }
    return old;
}

u32 DreamSys_GetElapsedSeconds(DreamSys *dreamSys) {
    return dreamSys->timer / 15;
}

void DreamSys_SetSoundBank(DreamSys *dreamSys, s32 value) {
    dreamSys->soundBank = value;
}

void DreamSys_SetCamera(DreamSys *dreamSys, s32 value) {
    dreamSys->camera.obj = value;
}

void DreamSys_SetEtcTim(DreamSys *dreamSys, s32 value) {
    dreamSys->etcTim = value;
}

void DreamSys_TickBegin(DreamSys *dreamSys) {
    if (dreamSys->controlsLocked == 0) {
        dreamSys->circlePressed = 0;
        dreamSys->dynamicLinkOn = dreamSys->timer % dreamSys->linkPeriod == 0;
    }
}

void DreamSys_TickHandlers(DreamSys *dreamSys) {
    if (dreamSys->lookHandler != NULL) {
        dreamSys->lookHandler();
    }
    if (dreamSys->moveHandler != NULL) {
        dreamSys->moveHandler(dreamSys);
    }
}

s32 DreamSys_TestPointAhead(DreamSys *dreamSys, Vec3 *pointOut, s32 distance, s32 *pos, s32 range) {
    Vec3 point;
    s32 height;
    s32 *worldPos;

    g_pointAheadZ[0] = distance;
    SceneNode_LocalToWorld(dreamSys, &point, &g_pointAheadZ[-2], 0);
    height = DreamSys_GetSightHeight((ScreenVec *)(dreamSys->camera.bytes + 0x14), (ScreenVec *)(dreamSys->camera.bytes + 0x20), distance);
    if (dreamSys->parent != 0) {
        worldPos = (s32 *)(dreamSys->pos.bytes + 0x38);
    } else {
        worldPos = NULL;
    }
    point.y = height + worldPos[1];
    if (pointOut != NULL) {
        *pointOut = point;
    }
    if (pos != NULL) {
        return Entity_IsWithinBox((s32 *)&point, range, pos);
    }
    return 0;
}

static s32 DreamSys_GetSightHeight(ScreenVec *start, ScreenVec *end, s32 pos) {
    s32 span;

    pos /= 1024;
    span = (end->z - start->z) / 1024;
    if (span == 0) {
        span = 1;
    }
    return ((end->y - start->y) * pos) / span + start->y;
}

void func_80059590(DreamSys *dreamSys) {
    dreamSys->unk7C = 0;
}

void func_80059598(DreamSys *dreamSys) {
    dreamSys->unk78 = 0;
}

s32 DreamSys_EmptySlot12C(void) {
    return 0;
}

void DreamSys_StopControls(DreamSys *dreamSys, s32 stopLook) {
    dreamSys->vtbl->setMoveMode(dreamSys, 0);
    if (stopLook != 0) {
        dreamSys->vtbl->setLookMode(dreamSys, 0);
    }
}

void DreamSys_SetControls(DreamSys *dreamSys, s32 moveMode, s32 lookMode) {
    dreamSys->vtbl->setMoveMode(dreamSys);
    dreamSys->vtbl->setLookMode(dreamSys, lookMode);
}

void DreamSys_SetLookMode(DreamSys *dreamSys, s32 mode) {
    DreamSysVtbl *vtbl = dreamSys->vtbl;

    dreamSys->lookMode = mode;
    switch (mode) {
    case 0:
        dreamSys->lookHandler = 0;
        return;
    case 1:
        dreamSys->lookHandler = vtbl->tickLook;
        return;
    case 2:
        dreamSys->lookHandler = vtbl->tickLookMode2;
        return;
    case 3:
        dreamSys->lookHandler = vtbl->tickLookMode3;
        return;
    }
}

void DreamSys_SetMoveMode(DreamSys *dreamSys, s32 mode) {
    DreamSysVtbl *vt;

    vt = dreamSys->vtbl;
    if (dreamSys->moveMode == 2) {
        vt->endFall(dreamSys, 0);
    }
    dreamSys->moveMode = mode;
    switch (mode) {
    case 0:
        dreamSys->moveHandler = 0;
        return;
    case 1:
        dreamSys->moveHandler = vt->tickMove;
        return;
    case 2: {
        s32 handler;
        DreamSysVtbl *vtblAgain;

        handler = vt->tickFall;
        vtblAgain = dreamSys->vtbl;
        dreamSys->falling = 1;
        dreamSys->fallSoundOn = 1;
        dreamSys->moveHandler = handler;
        HandlerNode_Start(dreamSys->soundBank, dreamSys->fallSound.bytes, 1, dreamSys, vtblAgain->fallSoundHandler);
        return;
    }
    }
}

void DreamSys_TickLook(DreamSys *dreamSys) {
    dreamSys->vtbl->tickPitch(dreamSys);
    dreamSys->vtbl->tickLookBack(dreamSys);
}

void DreamSys_TickPitch(DreamSys *dreamSys) {
    s32 newPitch;
    s32 step;
    s32 pitch;
    s32 limit;
    DreamCamera *camera2;
    DreamCamera *camera;
    s32 input;

    input = dreamSys->pitchInput;
    if (input != 0) {
        step = g_pitchSteps[input];
        limit = g_pitchLimits[input];
        newPitch = step + dreamSys->pitch;
        if ((newPitch < 0 ? ~newPitch + 1 : newPitch) < limit) {
            camera = dreamSys->camera.obj;
            camera->refPointY = (u32) (step + camera->refPointY);
            dreamSys->pitch = newPitch;
        }
        dreamSys->pitchInput = 0;
        return;
    }
    pitch = dreamSys->pitch;
    if (pitch != 0) {
        step = -0x258;
        if (pitch < 0) {
            step = 0x258;
        }
        camera2 = dreamSys->camera.obj;
        camera2->refPointY = (u32) (step + camera2->refPointY);
        dreamSys->pitch = (s32) (step + dreamSys->pitch);
    }
}

void DreamSys_TickLookBack(DreamSys *dreamSys) {
    s32 step;
    s32 sum;
    s32 lim;

    dreamSys->walkingForward = dreamSys->walkDirection == 1;
    if (dreamSys->lookBackInput != 0) {
        step = g_lookBackSteps[dreamSys->lookBackInput];
        sum = step + dreamSys->lookBackYaw;
        lim = g_lookBackLimits[dreamSys->lookBackInput];
        if ((sum < 0 ? ~sum + 1 : sum) < lim) {
            g_turnRotationYaw[0] = step;
            dreamSys->vtbl->setRotation(dreamSys, 0, &g_turnRotationYaw[-2]);
            dreamSys->lookBackYaw = sum;
        }
        dreamSys->lookBackInput = 0;
        DreamSys_ReverseDirection(dreamSys);
    } else if (dreamSys->lookBackYaw != 0) {
        step = dreamSys->lookBackYaw < 0 ? 0x2D : -0x2D;
        g_turnRotationYaw[0] = step;
        dreamSys->vtbl->setRotation(dreamSys, 0, &g_turnRotationYaw[-2]);
        dreamSys->lookBackYaw += step;
        DreamSys_ReverseDirection(dreamSys);
    }
}

static void DreamSys_ReverseDirection(DreamSys *dreamSys) {
    s32 direction;
    s32 reversed;

    direction = dreamSys->walkDirection;
    dreamSys->walkingForward = 0;
    if (direction != 0) {
        if (direction & 1) {
            reversed = direction + 1;
        } else {
            reversed = direction - 1;
        }
        dreamSys->walkDirection = reversed;
    }
}

void DreamSys_EmptySlot14C(void) {
}

void DreamSys_EmptySlot150(void) {
}

void DreamSys_TickMove(DreamSys *dreamSys) {
    if (dreamSys->autoWalk == 0) {
        dreamSys->vtbl->tickTurn(dreamSys);
        dreamSys->vtbl->tickWalk(dreamSys);
    } else if (dreamSys->autoWalk == 2) {
        dreamSys->vtbl->setForward(dreamSys);
    } else {
        dreamSys->vtbl->tickAutoWalk(dreamSys);
    }
}

void DreamSys_TickWalk(DreamSys *dreamSys) {
    if (dreamSys->controlsLocked == 0) {
        dreamSys->vtbl->walk(dreamSys, dreamSys->vtbl->tickStep(dreamSys, 1));
    }
}

void DreamSys_TickAutoWalk(DreamSys *dreamSys) {
    dreamSys->walkDirection = 1;
    if (dreamSys->controlsLocked == 0) {
        dreamSys->vtbl->walk(dreamSys, dreamSys->vtbl->tickStep(dreamSys, 1));
    } else {
        dreamSys->vtbl->tickStep(dreamSys, 0);
    }
}

void DreamSys_SetForward(DreamSys *dreamSys) {
    dreamSys->walkDirection = 1;
}

s32 DreamSys_TickStep(DreamSys *dreamSys, void *allowShake) {
    s32 playSound = 0;
    s32 direction;
    s32 tick;
    s32 bit;
    s32 step;
    DreamCamera *camera = allowShake;

    direction = 0;
    if (dreamSys->walkDirection != 0) {
        direction = dreamSys->walkDirection;
        tick = dreamSys->stepTick + 1;
        dreamSys->stepTick = tick;
        if (tick < 4) {
            if (dreamSys->speed == 4) {
                bit = tick & 1;
                playSound = bit == 0;
            }
        } else {
            dreamSys->walkDirection = 0;
            playSound = 1;
        }
        if (playSound != 0) {
            dreamSys->vtbl->playStepSound(dreamSys);
        }
        camera = dreamSys->camera.obj;
        if (camera != 0 && dreamSys->save.shake != 0 && allowShake != 0) {
            step = -0x32;
            if (dreamSys->stepTick >= 3) {
                step = 0x32;
            }
            camera->viewpointY += step;
            camera->refPointY += step;
        }
        if (dreamSys->walkDirection == 0) {
            dreamSys->stepTick = 0;
        }
    }
    if (playSound == 0) {
        dreamSys->vtbl->stopStepSound(dreamSys, camera);
    }
    return direction;
}

void DreamSys_PlayStepSound(DreamSys *dreamSys) {
    SoundBank *bank = dreamSys->soundBank;
    s32 groundSound = dreamSys->stepSound;
    SoundBankVtbl *bankVtbl = bank->vtbl;
    s32 tone;

    if (groundSound != 0) {
        tone = g_stepSoundTones[groundSound] * 0x10;
        bankVtbl->setOctave(bank, g_stepSoundOctaves[groundSound]);
        dreamSys->stepVoice = bankVtbl->playTone(bank, tone, 0x6E, 0x6E);
        if (dreamSys->stepSound != 0x16) {
            dreamSys->stepVoice = -1;
        }
        if (dreamSys->stepSound == 0xB) {
            bankVtbl->setOctave(bank, 1);
            bankVtbl->playTone(bank, tone, 0x6E, 0x6E);
            bankVtbl->setOctave(bank, 2);
            bankVtbl->playTone(bank, 0x90, 0x6E, 0x6E);
        }
    }
}

void DreamSys_StopStepSound(DreamSys *dreamSys) {
    s32 voice;
    SoundBank *bank;

    voice = dreamSys->stepVoice;
    if (voice >= 0) {
        bank = dreamSys->soundBank;
        bank->vtbl->stopVoice(bank, voice);
        dreamSys->stepVoice = -1;
    }
}

void DreamSys_Walk(DreamSys *dreamSys, s32 direction) {
    s32 distance;
    s32 location;
    DreamPlayer *map;
    Coord2 *coord;

    if (direction != 0) {
        distance = g_walkSigns[direction] * g_walkSpeeds[dreamSys->speed];
        dreamSys->vtbl->beforeWalk(dreamSys);
        map = dreamSys->map;
        location = map->vt->getLocation(map, 0, 0);
        if (dreamSys->vtbl->startLinkStep(dreamSys, location) == 0 && dreamSys->vtbl->linkExtra(dreamSys, location) == 0 && dreamSys->vtbl->linkFacing(dreamSys, location) == 0) {
            dreamSys->vtbl->savePosition(dreamSys);
            g_walkMoves[direction](dreamSys, distance, dreamSys->skipMoveBoxes == 0);
            if (dreamSys->stage == 0) {
                coord = dreamSys->pos.coord;
                if (coord->coord.t.y < -0x7D0 && coord->coord.t.x >= -0x1F3) {
                    dreamSys->vtbl->onWallTouch(dreamSys, dreamSys, 4);
                }
            }
        }
        dreamSys->pos.coord->flg = 0;
    }
}

void DreamSys_TickTurn(DreamSys *dreamSys) {
    s32 turn;

    turn = dreamSys->turnInput;
    if (turn != 0) {
        dreamSys->vtbl->setRotation(dreamSys, 0, g_turnRotations + turn * 12);
        dreamSys->turnInput = 0;
    }
}

void DreamSys_TickFall(DreamSys *dreamSys) {
    DreamCamera *camera;

    if (dreamSys->falling != 0) {
        dreamSys->vtbl->move(dreamSys, g_fallStep);
        camera = dreamSys->camera.obj;
        camera->refPointY = camera->refPointY - 0x258;
    }
    if (dreamSys->fallSoundOn != 0) {
        HandlerNode_Run((s32) dreamSys->soundBank, dreamSys->fallSound.bytes);
    }
}

void DreamSys_EndFall(DreamSys *dreamSys, s32 stopSound) {
    dreamSys->falling = 0;
    dreamSys->fallSoundOn = stopSound;
    if (stopSound != 0) {
        HandlerNode_Stop(dreamSys->soundBank, dreamSys->fallSound.bytes);
    }
}

s32 DreamSys_SwapSpeed(DreamSys *dreamSys, s32 speed) {
    s32 old;

    old = dreamSys->speed;
    if (speed >= 0) {
        dreamSys->speed = speed;
        dreamSys->savedSpeed = speed;
    }
    return old;
}

void DreamSys_PushSpeed(DreamSys *dreamSys, s32 speed) {
    s32 current;

    current = dreamSys->speed;
    if (current != speed) {
        dreamSys->savedSpeed = current;
        dreamSys->speed = speed;
    }
}

void DreamSys_PopSpeed(DreamSys *dreamSys) {
    dreamSys->speed = dreamSys->savedSpeed;
}

void DreamSys_SetLinkFlags(DreamSys *dreamSys, s32 dynamicLinkOn, s32 arg2, s32 arg3, s32 arg4) {
    if (dynamicLinkOn >= 0) {
        dreamSys->dynamicLinkOn = dynamicLinkOn;
    }
    if (arg2 >= 0) {
        dreamSys->unk128 = arg2;
    }
    if (arg3 >= 0) {
        dreamSys->unk12C = arg3;
    }
    if (arg4 >= 0) {
        dreamSys->unk130 = arg4;
    }
}

void DreamSys_SetLinkPeriod(DreamSys *dreamSys, s32 period) {
    dreamSys->linkPeriod = period;
}

void DreamSys_FallSoundHandler(s32 owner, HandlerNode *node) {
    s32 r;
    if (node->id == 1) {
        r = node->tick % 20; if (r == 0) {
            node->voices[0].sound = 9;
            node->voices[0].octave = -1;
        } else {
            node->voices[1].sound = 9;
            node->voices[1].octave = -1;
        }
    }
}

void DreamSys_InitNewGame(DreamSys *dreamSys) {
    dreamSys->save.magic = g_saveMagic;
    dreamSys->save.year = 0;
    dreamSys->save.day = 0;
    dreamSys->save.unlockScore = 0;
    dreamSys->save.navScore = 0;
    dreamSys->save.instanceScore = 0;
    dreamSys->save.flashbackCount = 0;
    dreamSys->save.reelSeen = 0;
    dreamSys->save.unk460 = 0;
    dreamSys->save.shake = 1;
    dreamSys->save.unk504 = 0;
    dreamSys->save.unk508 = 0;
    Nav_InitFlags(dreamSys->save.navFlags, &dreamSys->save.dynamicLinkCount);
    memset(dreamSys->save.unk50C, 0, 0x1F4);
}

void DreamSys_SwapShake(DreamSys *dreamSys, s32 *shake) {
    s32 old;

    old = dreamSys->save.shake;
    dreamSys->save.shake = *shake;
    *shake = old;
}

s32 DreamSys_GetDayNumber(DreamSys *dreamSys, s32 *yearOut) {
    if (yearOut != NULL) {
        *yearOut = dreamSys->save.year;
    }
    return dreamSys->save.day + 1;
}

s32 DreamSys_AdvanceDay(DreamSys *dreamSys) {
    if (++dreamSys->save.day >= 365) {
        dreamSys->save.day = 0;
        dreamSys->save.year++;
    }
    return dreamSys->save.day;
}

void DreamSys_ClearNeverSaved(DreamSys *dreamSys) {
    dreamSys->neverSaved = 0;
}

s32 DreamSys_IsNeverSaved(DreamSys *dreamSys) {
    return dreamSys->neverSaved;
}

s32 DreamSys_GetSaveBlock(s32 dreamSys, s32 *sizeOut) {
    if (sizeOut != NULL) {
        *sizeOut = 0x700;
    }
    return dreamSys + 0x178;
}

s32 DreamSys_StartDay(DreamSys *dreamSys) {
    s32 specialPoint;

    dreamSys->nextFlashback = 0;
    dreamSys->timer = 0;
    dreamSys->savedDay = dreamSys->save.day;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->vtbl->loadNextFlashback(dreamSys, 1);
        return dreamSys->stage;
    }
    specialPoint = Day_FindSpecial(dreamSys->cinematic.bytes, dreamSys->save.day + 1);
    dreamSys->vtbl->resetMoodAccumulators(dreamSys, specialPoint);
    if (specialPoint == 0) {
        dreamSys->vtbl->chooseStart(dreamSys);
        return dreamSys->stage;
    }
    return -1;
}

s32 DreamSys_EndDay(DreamSys *dreamSys, s32 reason) {
    dreamSys->save.day = dreamSys->savedDay;
    if (dreamSys->flashbackMode == 0 && reason == 0) {
        dreamSys->vtbl->calcUnlockScore(dreamSys);
        dreamSys->vtbl->computeDayPoint(dreamSys, &dreamSys->save.graph[dreamSys->save.day]);
        dreamSys->vtbl->advanceDay(dreamSys);
    } else if (reason == 2) {
        dreamSys->vtbl->initNewGame(dreamSys);
        dreamSys->neverSaved = 1;
    }
    return dreamSys->flashbackMode;
}

CineRef DreamSys_GetCinematic(DreamSys *dreamSys) {
    return dreamSys->cinematic.ref;
}

void DreamSys_ChooseStart(DreamSys *dreamSys) {
    s32 prevPoint;
    s32 seconds;

    dreamSys->vtbl->getPreviousPoint(dreamSys, &prevPoint, 1);
    dreamSys->stage = Spawn_PickFromMood(&dreamSys->place, &seconds, &prevPoint, dreamSys->save.day);
    seconds = dreamSys->vtbl->swapTimeLimit(dreamSys, seconds);
    dreamSys->transition = 0xB;
}

void DreamSys_LinkDynamic(DreamSys *dreamSys) {
    if (dreamSys->transition == 0) {
        DreamSys_ExecuteLink(dreamSys, Spawn_PickRandom(&dreamSys->place, dreamSys->stage, dreamSys->timer), 0xC, 1);
    }
}

s32 DreamSys_LinkStatic(DreamSys *dreamSys, void *target) {
    s32 newStage;

    if (dreamSys->transition == 0) {
        newStage = Link_FindStatic(&dreamSys->place, target, dreamSys->stage);
        if (newStage >= 0) {
            DreamSys_ExecuteLink(dreamSys, newStage, 0xD, 1);
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 DreamSys_LoadNextFlashback(DreamSys *dreamSys, s32 quiet) {
    Flashback *elem;
    s32 idx;

    idx = dreamSys->nextFlashback;
    if (idx < dreamSys->save.flashbackCount) {
        dreamSys->transition = 0xE;
        elem = &dreamSys->save.flashbacks[idx];
        if (quiet == 0) {
            dreamSys->vtbl->notify(dreamSys, 0xE);
        }
        dreamSys->save.day = elem->day;
        dreamSys->stage = elem->stage;
        dreamSys->place = elem->place;
        return 1;
    }
    return 0;
}

s32 DreamSys_LinkFacing(DreamSys *dreamSys, s16 *location) {
    s32 rotation[4];
    s32 newStage;

    if (dreamSys->transition != 0) {
        return 0;
    }
    newStage = Link_FindFacing(&dreamSys->place, location, dreamSys->stage);
    if (newStage < 0) {
        return 0;
    }
    SceneNode_GetRotation(dreamSys, rotation);
    if (Link_CheckFacing(&dreamSys->arrivalHeading, &dreamSys->linkHeading, rotation) == 0) {
        return 0;
    }
    if (dreamSys->walkingForward == 0) {
        return 0;
    }
    DreamSys_ExecuteLink(dreamSys, newStage, 0xF, 0);
    return 1;
}

s32 DreamSys_LinkFall(DreamSys *dreamSys, s32 location) {
    s32 newStage;

    if (dreamSys->transition == 0) {
        newStage = Link_PickFallStage(&dreamSys->place, dreamSys->stage, location, dreamSys->timer);
        if (newStage >= 0) {
            dreamSys->fallTurn = Link_GetFallTurn();
            dreamSys->linkHeading = 0;
            dreamSys->arrivalHeading = 0;
            DreamSys_ExecuteLink(dreamSys, newStage, 0x10, 0);
            return 1;
        }
    }
    return 0;
}

s32 DreamSys_LinkExtra(DreamSys *dreamSys, void *location) {
    s32 worldPos[4];
    s32 bonusSeconds;
    s32 newStage;

    newStage = Link_FindExtra(&dreamSys->place, location, dreamSys->stage);
    if (newStage >= 0) {
        bonusSeconds = Link_GetExtraSeconds();
        if (DreamSys_ExecuteLink(dreamSys, newStage, 0x11, 0) != 0) {
            dreamSys->transition = 0;
            dreamSys->map->vt->placeToWorld(dreamSys->map, worldPos, &dreamSys->place);
            dreamSys->vtbl->setPosition(dreamSys, worldPos);
            if (bonusSeconds != 0 && dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->swapTimeLimit(dreamSys, dreamSys->vtbl->getElapsedSeconds(dreamSys) + bonusSeconds);
            }
        }
        return 1;
    }
    return 0;
}

static s32 DreamSys_ExecuteLink(DreamSys *dreamSys, s32 newStage, s32 transition, s32 playSound) {
    dreamSys->transition = transition;
    dreamSys->vtbl->notify(dreamSys, transition);
    if (dreamSys->transition == 0) {
        return 0;
    }
    dreamSys->stage = newStage;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->timer = 0;
    }
    if (playSound != 0) {
        SoundBank *bank = dreamSys->soundBank;
        bank->vtbl->playTone(bank, 0x90, 0x6E, 0x6E);
    }
    return 1;
}

s32 DreamSys_StartLinkStep(DreamSys *dreamSys, StagePlace *target) {
    s32 rotation[4];

    if (dreamSys->transition == 0) {
        if (dreamSys->linkStep != 0) {
            if (dreamSys->linkStep(dreamSys) != 0) {
                dreamSys->ignorePad = 0;
                dreamSys->linkStep = 0;
                dreamSys->skipMoveBoxes = 0;
                if (dreamSys->speed == 4) {
                    dreamSys->vtbl->popSpeed(dreamSys);
                    return 0;
                }
            }
            return 0;
        }
        if (Link_FindScripted(&dreamSys->place, target, dreamSys->stage) >= 0) {
            SceneNode_GetRotation(dreamSys, rotation);
            if (Link_CheckScripted((u8 **)&dreamSys->arrivalHeading, (u8 **)&dreamSys->linkHeading, (RotationYaw *)rotation) != 0 && dreamSys->walkingForward != 0) {
                dreamSys->linkTarget = *target;
                dreamSys->ignorePad = 1;
                dreamSys->skipMoveBoxes = 1;
                dreamSys->linkStepTick = 0;
                dreamSys->linkStep = g_linkSteps[Link_GetStepScript()];
                dreamSys->vtbl->setRotation(dreamSys, 1, dreamSys->linkHeading);
                dreamSys->linkStep(dreamSys);
            }
        }
    }
    return 0;
}

s32 DreamSys_LinkStep0(DreamSys *dreamSys) {
    s32 tick;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep0Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->speed != 4) {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x85) {
            return 1;
        }
        if ((tick >= 0x2B && tick < 0x3A) || (tick >= 0x4B && tick < 0x5A)) {
            dreamSys->turnInput = 2;
        }
    } else {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x13) {
            return 1;
        }
        if ((tick >= 8 && tick < 0xA) || (tick >= 0xD && tick < 0xF)) {
            dreamSys->vtbl->setRotation(dreamSys, 0, g_yawPlus45);
        }
    }
    dreamSys->walkDirection = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 DreamSys_LinkStep1(DreamSys *dreamSys) {
    s32 lookDown;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep1Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->speed != 4) {
        if (dreamSys->linkStepTick >= 0x95) {
            return 1;
        }
        if ((u32)(dreamSys->linkStepTick - 0x16) < 0xF || (u32)(dreamSys->linkStepTick - 0x39) < 0x10 || (u32)(dreamSys->linkStepTick - 0x6E) < 0xF) {
            dreamSys->turnInput = 1;
        }
        lookDown = (u32)(dreamSys->linkStepTick - 0x39) < 0x35;
    } else {
        if (dreamSys->linkStepTick >= 0x19) {
            return 1;
        }
        if ((u32)(dreamSys->linkStepTick - 6) < 2 || (u32)(dreamSys->linkStepTick - 0xB) < 2 || (u32)(dreamSys->linkStepTick - 0x14) < 2) {
            dreamSys->vtbl->setRotation(dreamSys, 0, g_yawMinus45);
        }
        lookDown = (u32)(dreamSys->linkStepTick - 3) < 0xE;
    }
    if (lookDown) {
        dreamSys->pitchInput = 2;
    }
    dreamSys->walkDirection = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 DreamSys_LinkStep2(DreamSys *dreamSys) {
    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep2Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->speed != 4) {
        if (dreamSys->linkStepTick > 100) {
            return 1;
        }
        if (dreamSys->linkStepTick >= 43 && dreamSys->linkStepTick < 58) {
            dreamSys->turnInput = 2;
        }
    } else {
        if (dreamSys->linkStepTick > 14) {
            return 1;
        }
        if (dreamSys->linkStepTick >= 8 && dreamSys->linkStepTick < 10) {
            dreamSys->vtbl->setRotation(dreamSys, 0, g_yawPlus45);
        }
    }
    dreamSys->walkDirection = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 DreamSys_LinkStep3(DreamSys *dreamSys) {
    s32 tick;
    s32 lookDown;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep3Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->speed != 4) {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x71) {
            return 1;
        }
        if ((u32)(tick - 0x1E) < 0xF || (u32)(tick - 0x52) < 0xF) {
            dreamSys->turnInput = 1;
        }
        lookDown = (u32)(dreamSys->linkStepTick - 0x1E) < 0x34;
    } else {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x13) {
            return 1;
        }
        if ((u32)(tick - 6) < 2 || (u32)(tick - 0xF) < 2) {
            dreamSys->vtbl->setRotation(dreamSys, 0, g_yawMinus45);
        }
        lookDown = (u32)dreamSys->linkStepTick < 9;
    }
    if (lookDown) {
        dreamSys->pitchInput = 2;
    }
    dreamSys->walkDirection = 1;
    dreamSys->linkStepTick++;
    return 0;
}

static void DreamSys_MoveToTileOffset(DreamSys *dreamSys, s16 *from, s16 *to) {
    s32 delta[3];

    delta[0] = from[0] - to[0];
    delta[1] = from[1] - to[1];
    delta[2] = from[2] - to[2];
    delta[1] = 0;
    dreamSys->vtbl->move(dreamSys, delta);
}

s32 DreamSys_GetStage(DreamSys *dreamSys) {
    return dreamSys->stage;
}

void DreamSys_OnMapMessage(DreamSys *dreamSys, MapLocateView *sender, s32 message) {
    if (message == 5) {
        dreamSys->vtbl->logChunkMood(dreamSys, sender->vt->getLocation(sender, 0, 0));
    }
}

void DreamSys_OnEntityEvent(DreamSys *dreamSys, EventEntityVtbl **entity, s32 message) {
    s32 oldStage;

    if (dreamSys->transition == 0) {
        switch (message) {
        case 4:
            (*entity)->onNotify(entity, dreamSys, message);
            return;
        case 9:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->logEntityMood(dreamSys, (*entity)->getRecord(entity));
                dreamSys->save.instanceScore = (*entity)->getPoints(entity) + dreamSys->save.instanceScore;
                dreamSys->vtbl->maybeSaveFlashback(dreamSys, 0, 0x10);
                return;
            }
            break;
        case 10:
            oldStage = dreamSys->stage;
            dreamSys->stage = -(*entity)->getLinkStage(entity);
            dreamSys->vtbl->linkDynamic(dreamSys);
            if (dreamSys->stage < 0) {
                dreamSys->stage = oldStage;
                return;
            }
            break;
        case 11:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->cinematic.id.category = -1;
                dreamSys->timer = dreamSys->timeLimit;
                dreamSys->cinematic.id.variant = (*entity)->getVideo(entity);
                return;
            }
            break;
        case 12:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->timer = dreamSys->timeLimit;
            }
            break;
        }
    }
}

void DreamSys_GetPreviousPoint(DreamSys *dreamSys, MoodPoint *out, s32 yesterday) {
    s32 sum1 = 0;
    s32 sum0 = 0;
    s32 count;
    s32 i;
    MoodPoint *p;

    if (yesterday != 0) {
        if (dreamSys->save.year != 0 || dreamSys->save.day != 0) {
            sum0 = dreamSys->save.graph[dreamSys->save.day - 1].x;
            sum1 = dreamSys->save.graph[dreamSys->save.day - 1].y;
        }
    } else {
        count = 365;
        if (dreamSys->save.year == 0) {
            count = dreamSys->save.day;
        }
        if (count != 0) {
            p = dreamSys->save.graph;
            for (i = 0; i < count; i++, p++) {
                sum0 += p->x;
                sum1 += p->y;
            }
            sum0 = sum0 / count;
            sum1 = sum1 / count;
        }
    }
    out->x = sum0;
    out->y = sum1;
}

void DreamSys_ResetMoodAccumulators(DreamSys *dreamSys, s32 point) {
    MoodAccum *chunk = &dreamSys->chunkMood;
    MoodAccum *entity = &dreamSys->entityMood;

    dreamSys->vtbl->moodReset(dreamSys, chunk);
    dreamSys->vtbl->moodReset(dreamSys, entity);
    if (point != 0) {
        dreamSys->vtbl->moodLog(dreamSys, chunk, point);
        dreamSys->vtbl->moodLog(dreamSys, entity, point);
    }
}

void DreamSys_LogChunkMood(DreamSys *dreamSys, s8 *place) {
    dreamSys->vtbl->moodLog(dreamSys, &dreamSys->chunkMood, Stage_GetChunkMood(dreamSys->stage, place));
}

void DreamSys_LogEntityMood(DreamSys *dreamSys, s32 point) {
    dreamSys->vtbl->moodLog(dreamSys, &dreamSys->entityMood, point);
}

void DreamSys_ComputeDayPoint(DreamSys *dreamSys, MoodPoint *out) {
    s16 chunkPoint;
    s16 entityPoint;

    dreamSys->vtbl->moodResolve(dreamSys, &dreamSys->chunkMood, &chunkPoint);
    dreamSys->vtbl->moodResolve(dreamSys, &dreamSys->entityMood, &entityPoint);
    if (dreamSys->entityMood.count == 0) {
        entityPoint = chunkPoint;
    }
    out->x = ((s8)chunkPoint + (s8)entityPoint) / 2;
    out->y = (((s8 *)&chunkPoint)[1] + ((s8 *)&entityPoint)[1]) / 2;
}

void DreamSys_GetDreamColor(DreamSys *dreamSys) {
    s16 point;

    dreamSys->vtbl->computeDayPoint(dreamSys, &point);
    Mood_GetColor(&point);
}

static s32 Mood_GetColor(s16 *point) {
    s8 buf[2];
    s8 *p;
    s32 i;
    s8 v;

    *(u16 *)buf = *(u16 *)point;
    p = buf;
    i = 0;
    do {
        v = *p;
        if (v >= 4) {
            *p = 2;
        } else if (v < -3) {
            *p = 0;
        } else {
            *p = 1;
        }
        i++;
        p++;
    } while (i < 2);
    return g_moodColors[buf[0]][buf[1]];
}

void Mood_Reset(DreamSys *dreamSys, MoodAccum *accum) {
    accum->last = 0;
    accum->sumY = 0;
    accum->sumX = 0;
    accum->count = 0;
}

void Mood_Log(DreamSys *dreamSys, MoodAccum *accum, MoodPoint *point) {
    s32 sumX;

    sumX = accum->sumX;
    accum->last = *(u16 *)point;
    accum->sumX = point->x + sumX;
    accum->sumY = point->y + accum->sumY;
    accum->count = accum->count + 1;
}

void Mood_Resolve(DreamSys *dreamSys, MoodAccum *accum, MoodPoint *point) {
    if (accum->count != 0) {
        point->x = Mood_CalcAxis(((MoodPoint *)accum)->x, accum->sumX, accum->count);
        point->y = Mood_CalcAxis(((MoodPoint *)accum)->y, accum->sumY, accum->count);
        return;
    }
    *(u16 *)point = *(u16 *)accum;
}

static s32 Mood_CalcAxis(s32 last, s32 sum, s32 count) {
    s32 r = sum / count + last / 3;
    if (r > 9) {
        r = -9;
    } else if (r < -9) {
        r = 9;
    }
    return r;
}

void DreamSys_CalcUnlockScore(DreamSys *dreamSys) {
    s32 score;

    dreamSys->save.navScore = Nav_CalcScore();
    score = dreamSys->save.instanceScore;
    if (score < 0) {
        dreamSys->save.instanceScore = 0;
    } else if (score > 0x02FAF080) {
        dreamSys->save.instanceScore = 0x02FAF080;
    }
    dreamSys->save.unlockScore = dreamSys->save.navScore + dreamSys->save.instanceScore;
}

void DreamSys_AddFlashback(DreamSys *dreamSys, s32 stage, StagePlace *place, DreamRotation *rotation, s32 arg4, s32 length, s32 day) {
    Flashback *ent;
    s32 n;

    ent = dreamSys->save.flashbacks;
    n = dreamSys->save.flashbackCount;
    if (n < 10) {
        dreamSys->save.flashbackCount = n + 1;
        ent += n;
    } else {
        ent += dreamSys->timer % 9;
    }
    ent->stage = stage;
    ent->place = *place;
    ent->rotation.rot = *rotation;
    ent->unk1C = arg4;
    ent->length = length;
    ent->day = day;
}

void DreamSys_MaybeSaveFlashback(DreamSys *dreamSys, s32 arg1, s32 length) {
    s32 rotation[4];
    s32 location;
    DreamPlayer *map;

    if (dreamSys->map != NULL) {
        if (rand() % 3 == 0) {
            map = dreamSys->map;
            location = map->vt->getLocation(map, 0, 0);
            SceneNode_GetRotation(dreamSys, rotation);
            dreamSys->vtbl->addFlashback(dreamSys, dreamSys->stage, location, rotation, arg1, length, dreamSys->save.day);
        }
    }
}

void DreamSys_ClearFlashbacks(DreamSys *dreamSys) {
    dreamSys->save.flashbackCount = 0;
}

void DreamSys_SavePosition(DreamSys *dreamSys) {
    Coord2 *src = dreamSys->pos.coord;

    dreamSys->coordCopy = *src;
    dreamSys->paramCopy = *src->param;
}

void DreamSys_RestorePosition(DreamSys *dreamSys) {
    Coord2 *dst = dreamSys->pos.coord;

    *dst = dreamSys->coordCopy;
    *dst->param = dreamSys->paramCopy;
    dst->flg = 0;
}

s32 func_8005BA20(DreamSys *dreamSys, s32 value) {
    s32 old;

    if (value < 0) {
        return dreamSys->unk924;
    }
    old = dreamSys->unk924;
    dreamSys->unk924 = value;
    return old;
}

static DreamSysVtbl *DreamSys_GetVtable(void) {
    return (DreamSysVtbl *)g_dreamSysVtbl;
}

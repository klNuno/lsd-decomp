#include "common.h"
#include "game/entity.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/handler_node.h"
#include "game/fade.h"
#include "game/model.h"
#include "game/view.h"
#include "game/dream_sys.h"
#include "game/stage_map.h"
#include "psyq/libc.h"

/*
 * Entities and their behaviour handlers (record +0xC). A handler runs once per tick as
 * handler(entity, node): Entity_StartHandler registers it in the node at Entity +0x9C
 * (HandlerNode_Start) and slot 0x11C (Entity_RunHandler) runs HandlerNode_Run, which calls the
 * handler, then plays the sounds the handler asked for on the entity's sound bank (+0x58).
 *
 * File boundaries: likely (docs/layout.md)
 */


extern EntityRecord g_entityRecords[];
extern void Behavior_MazePenguin();
extern s32 g_scaleHalf;
extern s32 g_scaleSix;
extern s32 g_scaleQuarter;
extern void Behavior_Type71();
extern s32 g_scaleDouble[];
extern s32 g_moveYNeg64[];
extern s32 g_scaleTiny;
static s32 Entity_IsDreamerNear();
static EntityVtbl *Entity_GetVtbl(void);
static s32 Entity_IsAtPointAhead(Entity *entity, Vec3 *pos, s32 range, s32 param);
extern s16 g_rotY9[];
extern s16 g_rotYNeg9[];
extern s32 g_moveYNeg512[];
extern s32 g_rotY180[];
static Fade *Entity_StartEffect();
static void Behavior_QueueSound18And3(HandlerNode *node);
extern s32 g_rotY90;
extern s16 g_scaleShrinkStep[];

extern s32 g_scaleTallTwo;
extern s16 g_scaleWideThree[];
extern s32 g_moveZNeg256[];
extern s32 g_rotY2[];
extern s32 g_rotY4[];
extern s32 g_scaleTwoFifths[];
extern s8 g_rotXEighth[];
static void Behavior_RollWideOrSlide(Entity *entity);

extern s32 g_rotY1;
extern s32 g_scaleTriple;
extern s32 g_effectDefaultPos[];
extern s32 g_effectDefaultSize[];
extern s32 g_rotYNeg90;
extern s32 g_scaleThinTall[];
extern s16 g_scaleNarrowTall[];
extern s32 g_moveYNeg1500Z1024[];
extern s16 g_rotYNegHalf[];
static void Behavior_TrainRun(Entity *entity, HandlerNode *node, s32 turnTick, s32 leaveTick, s32 speed);
extern s32 g_moveYNeg4096[];
extern s32 g_moveY64[];
extern s32 g_moveXNeg64[];
static void Entity_CheckLinkRadius();
static s32 Entity_IsAtPointAhead(Entity *entity, Vec3 *pos, s32 range, s32 param);
extern EntityVtbl g_entityVtbl;
extern s8 g_type74ClearColor[];
extern s32 g_moveYNeg256[];
extern s32 g_scaleTallFour[];
extern s32 g_moveY256[];
extern s32 g_rotZ9[];
extern s32 g_moveY8[];
extern s32 g_rotYNegThird;
extern s32 g_scaleOne;
extern s32 g_scaleEighth;
extern s32 g_rotYNeg120[];
extern s32 g_astronautBarPose[];
extern s32 g_moveY64ZNeg64[];
extern s16 g_type41Scale[];
static s32 Entity_IsDreamerNear(Entity *entity, s32 radius);
extern s16 g_rotZ1[];
extern s16 g_rotZNeg9[];
static Fade *Entity_StartEffect(Entity *entity, void *size, void *pos, s32 step, s32 priority);
static void Behavior_QueueLowSound7(HandlerNode *node);
extern s32 g_rotZNeg90[];
extern s32 g_rotX90;
s32 g_type78Stopped;
extern s32 g_scaleGrowStep[];

Entity *Entity_Create(s32 type, void *source, SoundBank *soundBank) {
    Entity *mem;

    mem = Heap_Alloc(0x108);
    if (mem == NULL) {
        return NULL;
    }
    if (Entity_GetVtbl()->construct(mem, type, source, soundBank) != 0) {
        return mem;
    }
    Heap_Free(mem);
    return NULL;
}

void *Entity_Construct(Entity *entity, s32 type, void *source, SoundBank *soundBank) {
    if (Model_GetVtbl()->init(entity, source, soundBank) != 0) {
        entity->vtbl = Entity_GetVtbl();
        entity->type = type;
        entity->handlerNode.id = 0;
        entity->effect = 0;
        entity->secondEffect = 0;
        entity->vtbl->init(entity);
        return entity;
    }
    return NULL;
}

static Fade *Entity_StartEffect(Entity *entity, void *size, void *pos, s32 step, s32 priority) {
    Fade *effect;

    if (entity->effect == NULL) {
        if (size == NULL) {
            size = g_effectDefaultSize;
        }
        effect = Fade_Create(size, 0, priority);
        if (effect == NULL) {
            return NULL;
        }
        entity->effect = effect;
    } else {
        effect = entity->effect;
    }
    effect->vtbl->hide(effect);
    effect->vtbl->show(effect, entity, pos ? pos : g_effectDefaultPos);
    effect->vtbl->setStep(effect, step);
    return effect;
}

void Entity_Destruct(Entity *entity) {
    Fade *effect;

    effect = entity->effect;
    if (effect != NULL) {
        effect->vtbl->delete_(effect);
    }
    effect = entity->secondEffect;
    if (effect != NULL) {
        effect->vtbl->delete_(effect);
    }
    Model_GetVtbl()->destroy(entity);
}

void Entity_Init(Entity *entity) {
    /* record points byte (+2) of 1 to 9 */
    if ((u8)g_entityRecords[entity->type].points - 1U < 9) {
        entity->vtbl->setLightFlags(entity, 1);
    }
    entity->vtbl->setTickMode(entity, 0x42);
    entity->vtbl->sleep(entity);
}

void Entity_Attach(Entity *entity, DreamSys *dreamSys, void *watched, StageMap *map, void *placement) {
    if (entity->parent == 0) {
        Model_GetVtbl()->attach(entity, dreamSys, watched, map, placement);
        entity->map = map;
        /* record +3 wake mode 0: awake at spawn; +0xB handler range 0: handler from the start */
        if (g_entityRecords[entity->type].wakeMode == 0) {
            entity->vtbl->wake(entity);
            if (g_entityRecords[entity->type].handlerRange == 0) {
                entity->vtbl->startHandler(entity);
            }
        }
    }
}

void Entity_Detach(Entity *entity) {
    if (entity->parent != 0) {
        entity->vtbl->sleep(entity);
        Model_GetVtbl()->detach(entity);
        entity->map = 0;
    }
}

void Entity_Update(Entity *entity, void *sender, s32 phase) {
    if (entity->vtbl->checkWake(entity) != 0) {
        entity->vtbl->checkSleep(entity);
    }
    if (entity->vtbl->checkHandlerStart(entity) != 0) {
        entity->vtbl->checkHandlerStop(entity);
    }
    entity->vtbl->checkTouch(entity);
    Model_GetVtbl()->onClock(entity, sender, phase);
}

void Entity_OnActorTouch(Entity *entity, void *sender, s32 message) {
    s32 link;

    /* record +7 link */
    link = g_entityRecords[entity->type].link;
    if (message < 2 || message >= 9 || link > 0) {
        Model_GetVtbl()->onTouch34(entity, sender, message);
        /* entity events: 10 link, 11 end with the record's video (+8), 12 end; link 0x7F ends the dream */
        if (message == 4 && link > 0) {
            if (link != 0x7F) {
                message = 0xA;
            } else {
                message = 0xC;
                if (g_entityRecords[entity->type].video != 0) {
                    message = 0xB;
                }
            }
            entity->vtbl->notify(entity, message);
        }
    }
}

void Entity_OnWallTouch(Entity *entity, void *sender, s32 message) {
    Model_GetVtbl()->onTouch24(entity, sender, message);
    if (message == 4) {
        entity->vtbl->sleep(entity);
    }
}

void Entity_RunHandler(Entity *entity) {
    HandlerNode_Run(entity->soundBank, &entity->handlerNode);
    entity->handlerTicks++;
}

/* Is pos within range << 11 of the dreamer; the record's points byte (+2), when -9 to -1, raises the tested height by points * 1024. */
static s32 Entity_IsAtPointAhead(Entity *entity, Vec3 *pos, s32 range, s32 param) {
    Vec3 point;
    u8 points;

    point = *pos;
    points = *(u8 *)&g_entityRecords[entity->type].points;
    if ((u32)((points + 9) & 0xFF) < 9U) {
        point.y += (s32)(points << 0x18) >> 0xE;
    }
    if (param < 0) {
        param = 0x800 / (s32)(~param + 1);
    } else {
        param = param << 0xB;
    }
    return entity->dreamSys->vtbl->testPointAhead(entity->dreamSys, 0, range << 0xB, &point, param);
}

/* Ground distance |dx| + |dz| from this entity to the position copy of other. */
s32 Entity_GroundDistance(Entity *entity, Entity *other) {
    Vec3 *otherPos;
    Coord2 *block;
    s32 dz;
    s32 dx;
    s32 dist;

    otherPos = NULL;
    if (other->parent != 0) {
        otherPos = &other->object.coord->workm.t;
    }
    block = entity->object.coord;
    dx = block->coord.t.x - otherPos->x;
    if (dx < 0) {
        dx = ~dx + 1;
    }
    dz = block->coord.t.z - otherPos->z;
    if (dz >= 0) {
        dist = dx + dz;
    } else {
        dist = dx - dz;
    }
    return dist;
}

s32 Entity_GetSoundFade(Entity *entity) {
    s32 dist;
    s32 range;

    if (entity->dreamSys != NULL) {
        dist = entity->vtbl->distanceTo(entity, entity->dreamSys);
        range = g_entityRecords[entity->type].soundRange << 11;
        if (range >= dist) {
            return dist / (range / entity->handlerNode.fadeSteps);
        }
    }
    return -1;
}

EntityRecord *Entity_GetRecord(Entity *entity) {
    return &g_entityRecords[entity->type];
}

s32 Entity_GetPoints(Entity *entity) {
    return g_entityRecords[entity->type].points * 1000;
}

s32 Entity_GetLinkStage(Entity *entity) {
    s8 link;

    link = g_entityRecords[entity->type].link;
    if (link < 0) {
        return ~link;
    }
    return link - 1;
}

s32 Entity_GetVideo(Entity *entity) {
    return g_entityRecords[entity->type].video - 1;
}

void Entity_Wake(Entity *entity) {
    entity->vtbl->setVisible(entity, 1);
    entity->awake = 1;
    entity->ticks = 0;
}

void Entity_Sleep(Entity *entity) {
    entity->vtbl->setVisible(entity, 0);
    entity->vtbl->stopHandler(entity);
    entity->vtbl->setTouched(entity, 0);
    entity->awake = 0;
}

void Entity_SetTouched(Entity *entity, s32 touched) {
    if (touched != 0) {
        entity->vtbl->notify(entity, 9);
    }
    entity->touched = touched;
}

void Entity_StartHandler(Entity *entity) {
    /* register the record's handler (+0xC) */
    HandlerNode_Start(entity->soundBank, &entity->handlerNode, entity->type + 1, entity, g_entityRecords[entity->type].handler);
    entity->vtbl->playAnimation(entity);
    entity->vtbl->startTick(entity);
    entity->handlerTicks = 0;
    entity->handlerActive = 1;
}

void Entity_StopHandler(Entity *entity) {
    HandlerNode_Stop(entity->soundBank, &entity->handlerNode);
    entity->vtbl->stopAnimation(entity);
    entity->vtbl->stopTick(entity);
    entity->handlerActive = 0;
}

s32 Entity_CheckWake(Entity *entity) {
    EntityRecord *record;
    s32 wake;

    if (entity->awake == 0 && entity->state != 1) {
        wake = 0;
        record = &g_entityRecords[entity->type];
        if (record->wakeMode == 0) {
            goto done;
        }
        if (record->wakeMode == 4) {
            goto rnd;
        }
        if (record->wakeRange == 0) {
            goto done;
        }
        if (Entity_IsAtPointAhead(entity, &entity->object.coord->coord.t, record->wakeRange, record->boxSize) != 0) {
            if (record->wakeMode == 1) {
                goto set1;
            }
            if (record->wakeMode == 3) {
                goto rnd;
            }
            goto done;
        }
        if (record->wakeMode == 2) {
            wake = 1;
        }
        goto done;
rnd:
        if ((rand() & 0x7F) != 0) {
            goto done;
        }
set1:
        wake = 1;
done:
        if (wake != 0) {
            entity->vtbl->wake(entity);
        }
    }
    return entity->awake;
}

s32 Entity_CheckSleep(Entity *entity) {
    EntityRecord *record;
    s32 sleep;
    s32 inRange;
    u8 mode;

    if (entity->awake != 0) {
        record = &g_entityRecords[entity->type];
        Entity_CheckLinkRadius(entity, 0);
        mode = record->sleepMode;
        sleep = 0;
        if (mode != 0 && mode != 3) {
            if (mode >= 10) {
                sleep = entity->ticks == (u32)(mode * 15);
            } else if (record->wakeRange != 0) {
                inRange = Entity_IsAtPointAhead(entity, &entity->object.coord->coord.t, record->wakeRange, record->boxSize);
                if (inRange != 0) {
                    if (record->sleepMode == 1) {
                        sleep = 1;
                    }
                } else if (record->sleepMode == 2) {
                    sleep = 1;
                }
            }
        }
        if (sleep != 0) {
            entity->vtbl->sleep(entity);
        }
    }
    return entity->awake;
}

s32 Entity_CheckTouch(Entity *entity) {
    s32 range;
    Vec3 *pos;
    EntityRecord *record;

    record = &g_entityRecords[entity->type];
    if (entity->awake != 0) {
        if (entity->touched == 0) {
            pos = &entity->object.coord->coord.t;
            range = record->touchRange;
            if (range < 0) {
                range = ~range + 1;
            }
            if (Entity_IsAtPointAhead(entity, pos, range, record->boxSize) != 0) {
                entity->vtbl->setTouched(entity, 1);
            }
        }
        if (record->touchRange < 0) {
            SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        }
    }
    return entity->touched;
}

s32 Entity_CheckHandlerStart(Entity *entity) {
    EntityRecord *record;
    s32 range;
    Vec3 *pos;

    if (entity->awake != 0) {
        if (entity->handlerActive == 0) {
            if (entity->state != 1) {
                record = &g_entityRecords[entity->type];
                range = record->handlerRange;
                if (range != 0) {
                    pos = &entity->object.coord->coord.t;
                    if (range < 0) {
                        range = ~range + 1;
                    }
                    if (Entity_IsAtPointAhead(entity, pos, range, record->boxSize) != 0) {
                        entity->vtbl->startHandler(entity);
                    }
                }
            }
        }
    }
    return entity->handlerActive;
}

/* With a negative link (+7), link as soon as the dreamer is within the record's +8 << 9. */
static void Entity_CheckLinkRadius(Entity *entity, s32 arg1) {
    s8 radius;

    if (g_entityRecords[entity->type].link < 0) {
        radius = g_entityRecords[entity->type].video;
        if ((radius != 0) && (Entity_IsDreamerNear(entity, radius << 9) != 0)) {
            entity->vtbl->notify(entity, 0xA);
        }
    }
}

/* The dreamer is within 0x200 in height and closer than radius on the ground. */
static s32 Entity_IsDreamerNear(Entity *entity, s32 radius) {
    DreamSys *other;
    s32 y;
    s32 my;

    other = entity->dreamSys;
    y = other->object.coord->coord.t.y;
    my = entity->object.coord->coord.t.y;
    if (y + 0x200 >= my && my >= y - 0x200 && entity->vtbl->distanceTo(entity, other, y) < radius) {
        return 1;
    }
    return 0;
}

s32 Entity_CheckHandlerStop(Entity *entity) {
    EntityRecord *record;
    s8 range;

    if (entity->awake != 0) {
        if (entity->handlerActive != 0) {
            record = &g_entityRecords[entity->type];
            range = record->handlerRange;
            if ((range < 0) && (Entity_IsAtPointAhead(entity, &entity->object.coord->coord.t, ~range + 1, record->boxSize) == 0)) {
                entity->vtbl->stopHandler(entity);
            }
        }
    }
    return entity->handlerActive;
}

static EntityVtbl *Entity_GetVtbl(void) {
    return &g_entityVtbl;
}

void Behavior_Astronaut(Entity *entity, HandlerNode *node) {
    DreamSys *dreamSys;

    if (node->tick == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vtbl->getDreamColor(dreamSys) == 5) {
            entity->state = 0x64;
        }
    }
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->state == 0) {
        if (node->tick % 10 == 0) {
            node->voices[0].sound = 5;
            node->voices[0].octave = -2;
        }
        if (entity->handlerTicks == 0x960) {
            entity->handlerTicks = -1;
            return;
        }
        if (entity->handlerTicks < 0x4B0) {
            entity->vtbl->moveZ(entity, 0x32, 0);
        } else {
            entity->vtbl->moveZ(entity, -0x32, 0);
        }
        return;
    }
    if (entity->handlerTicks < 0xFA) {
        if (node->tick % 10 == 0) {
            node->voices[0].sound = 5;
            node->voices[0].octave = -2;
        }
        if (entity->handlerTicks < 0x64) {
            entity->vtbl->moveZ(entity, 0x32, 0);
        } else if (entity->handlerTicks < 0xFA) {
            entity->vtbl->move(entity, g_moveY64ZNeg64);
        }
    } else {
        if (entity->handlerTicks == 0xFA) {
            entity->vtbl->stopAnimation(entity);
            node->voices[0].sound = -2;
            return;
        }
        if (entity->handlerTicks >= 0x105 && entity->handlerTicks < 0x238) {
            entity->vtbl->moveZ(entity, -0x32, 0);
            entity->vtbl->rotate(entity, 1, g_rotYNeg120);
            return;
        }
        if (entity->handlerTicks >= 0x239) {
            entity->vtbl->rotate(entity, 1, g_astronautBarPose);
        }
    }
}

void Behavior_Type1(Entity *entity, HandlerNode *node) {
    node->fade = 0;
    if (node->tick == 0) {
        node->voices[0].sound = 0x14;
        node->voices[1].sound = 0x14;
        node->voices[2].sound = 0x14;
        entity->dreamSys->vtbl->stopControls(entity->dreamSys, 1);
    }
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    entity->vtbl->moveZ(entity, -0x5A, 0);
    if (entity->handlerTicks == 0x1E) {
        entity->vtbl->notify(entity, 0xA);
    }
}

void Behavior_Type5(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0x17;
    }
}

void Behavior_Type7(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->animFrame == entity->animLength / 2) {
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
        node->voices[1].sound = 3;
        node->voices[1].octave = -2;
    }
    if (node->tick % 90 < 3) {
        node->voices[2].sound = 6;
        node->voices[2].octave = -1;
    }
    if (entity->handlerTicks >= 0x79) {
        entity->vtbl->rotate(entity, 0, g_rotY2);
        entity->vtbl->moveZ(entity, -0x140, 0);
        return;
    }
    if (entity->handlerTicks >= 0x38 || Entity_IsAtPointAhead(entity, &entity->object.coord->coord.t, 1, 1) != 0) {
        entity->vtbl->move(entity, g_moveYNeg64);
        return;
    }
    if (entity->handlerTicks >= 0xA) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        entity->vtbl->moveZ(entity, -0x100, 0);
        return;
    }
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_PurpleBeast(Entity *entity) {
    entity->vtbl->scale(entity, 1, g_scaleDouble);
    entity->vtbl->move(entity, g_moveYNeg64);
}

void Behavior_Type9(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
    }
    entity->vtbl->moveZ(entity, -0x1E, 0);
}

void Behavior_Type10(Entity *entity, HandlerNode *node) {
    node->fade = 0;
    if (node->tick == 0) {
        node->voices[0].sound = 0xB;
        node->voices[1].sound = 0xB;
        node->voices[2].sound = 0xB;
    }
    entity->vtbl->moveZ(entity, -0x1E, 0);
}

void Behavior_WalkingGeisha(Entity *entity, HandlerNode *node) {
    void *turn;
    DreamSys *dreamSys;

    entity->speed = -0x14;
    node->fade = entity->vtbl->getSoundFade(entity);
    turn = NULL;
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
        node->voices[0].octave = 1;
    }
    if (entity->state == 11) {
        if (entity->handlerTicks == 0xA8C) {
            turn = &g_rotYNeg90;
        }
        if (entity->handlerTicks == 0xC6C) {
            turn = &g_rotY90;
        }
        if (entity->handlerTicks == 0xE10) {
            turn = &g_rotYNeg90;
        }
        if (entity->handlerTicks >= 0xD5D && entity->handlerTicks < 0xDD5) {
            dreamSys = entity->dreamSys;
            if (dreamSys->vtbl->wasCirclePressed(dreamSys) != 0) {
                entity->handlerTicks = 0;
                entity->state = 0xD;
            }
        }
    } else if (entity->state == 12) {
        if (entity->handlerTicks == 0x7BC) {
            turn = &g_rotYNeg90;
        }
    } else if (entity->state == 13) {
        entity->speed = -0x78;
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        entity->vtbl->scale(entity, 1, &g_scaleHalf);
        if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->vtbl->notify(entity, 0xB);
        }
    }
    if (entity->handlerTicks == 0x618) {
        if (rand() & 1) {
            turn = &g_rotY90;
            entity->state = 0xB;
        } else {
            turn = &g_rotYNeg90;
            entity->state = 0xC;
        }
    }
    if (turn != NULL) {
        entity->vtbl->rotate(entity, 0, turn);
    }
    entity->vtbl->moveZOnGround(entity, entity->speed, 0);
    if (entity->state != 0xC && entity->contact != 0) {
        entity->vtbl->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type12(Entity *entity) {

    if (entity->handlerTicks == 0 && !(rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->object.coord->coord.t.y < 0x7D0) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    }
    if (entity->state == 11) {
        if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0xA00) {
            entity->map->vtbl->startTileStretch(entity->map, 1, 1);
            entity->handlerTicks = 1;
            entity->state = 0xC;
        }
    } else if (entity->state == 12) {
        if (entity->handlerTicks++ == 300) {
            entity->vtbl->notify(entity, 0xC);
        }
    }
}

void Behavior_Type13(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0xC;
        entity->state = entity->state + 1;
    } else if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
    if (entity->state == 0x24) {
        if (rand() % 3 == 0) {
            entity->vtbl->notify(entity, 0xB);
        }
    }
}

void Behavior_Type14(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->animFrame == 0xA) {
        node->voices[0].sound = 0xD;
    }
    entity->vtbl->moveZ(entity, -0xA, 0);
}

void Behavior_Type15(Entity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        node->fade = 0;
        node->voices[0].sound = 0xF;
    }
}

void Behavior_Type16(Entity *entity) {
    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->state == 0) {
        if (entity->handlerTicks < 0x40) {
            entity->vtbl->moveZ(entity, -0x5A, 0);
            return;
        }
        if (entity->handlerTicks == 0x40) {
            entity->vtbl->rotate(entity, 0, (rand() & 1) ? &g_rotY90 : &g_rotYNeg90);
            entity->vtbl->move(entity, g_moveY256);
            return;
        }
        entity->vtbl->moveZOnGround(entity, -0x176, rand() % 2);
        return;
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks % 5 == 0) {
            entity->vtbl->rotate(entity, 0, &g_rotY90);
        }
        entity->vtbl->moveZ(entity, -0x800, 0);
        entity->vtbl->setVisible(entity, (rand() % 7) == 0);
    }
}

void Behavior_Type17(Entity *entity) {
    entity->vtbl->scale(entity, 1, &g_scaleHalf);
}

void Behavior_Type19(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == (node->tick / 10) * 10) {
        node->voices[0].sound = 0x11;
    }
    entity->vtbl->moveZ(entity, -0x100, 0);
}

void Behavior_Type20(Entity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        if (rand() % 7 == 0) {
            entity->vtbl->scale(entity, 1, &g_scaleTallTwo);
        }
    }
    if (!(node->tick & 3)) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 0x1C;
    }
    entity->vtbl->moveZ(entity, -0x64, 0);
}

void Behavior_MinotaurRickshaw(Entity *entity, HandlerNode *node) {
    s32 phase;

    node->fade = entity->vtbl->getSoundFade(entity);
    phase = node->tick % (entity->animLength / 2);
    if (phase == 0) {
        node->voices[0].sound = 0xA;
    } else if (phase == 3) {
        node->voices[1].sound = 0xD;
    }
    entity->vtbl->moveZ(entity, -0x1E, 1);
}

void Behavior_Type22(Entity *entity) {
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type23(Entity *entity) {
    EntityVtbl *vt;
    s32 ticks;
    s32 speed;

    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    if (entity->touched != 0) {
        if (entity->handlerTicks >= 0x41) {
            entity->handlerTicks = 0;
        }
        if (entity->handlerTicks >= 7) {
            entity->vtbl->move(entity, g_moveYNeg64);
            entity->vtbl->moveZ(entity, 0xA, 0);
        } else {
            entity->vtbl->move(entity, g_moveXNeg64);
        }
        return;
    }
    ticks = entity->handlerTicks;
    if (ticks == 0) {
        entity->vtbl->move(entity, g_moveYNeg4096);
    } else if (ticks < 0x41) {
        entity->vtbl->move(entity, g_moveY64);
    } else if (ticks < 0x47) {
        entity->vtbl->move(entity, g_moveYNeg64);
        entity->vtbl->moveZ(entity, -0x1E, 0);
    } else {
        vt = entity->vtbl;
        if (ticks < 0x100) {
            speed = -ticks - 0x41;
        } else {
            speed = 0xFF;
        }
        vt->moveZ(entity, speed, 0);
    }
}

void Behavior_Type24(Entity *entity, HandlerNode *node) {
    if (node->tick % 15 == 0) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
    }
    entity->vtbl->scale(entity, 1, g_scaleDouble);
    entity->vtbl->rotate(entity, 0, g_rotY2);
    entity->vtbl->moveZ(entity, -0x200, 0);
}

void Behavior_Type25(Entity *entity, HandlerNode *node) {
    s32 ticks;

    node->fade = 0;
    ticks = entity->handlerTicks;
    if (ticks < 0x64) {
        if (node->tick % 3 == 0) {
            node->voices[0].sound = 0x16;
            node->voices[0].octave = 1;
        }
        entity->vtbl->moveY(entity, -0x40, 0);
    } else if (ticks < 0x12C) {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
        node->voices[1].sound = 0xC;
        node->voices[1].octave = -1;
        node->voices[2].sound = 0xC;
        node->voices[2].octave = -1;
        entity->vtbl->moveY(entity, -0x100, 0);
    } else {
        entity->vtbl->rotate(entity, 0, g_rotXEighth);
        entity->vtbl->moveY(entity, -0x200, 0);
    }
}

void Behavior_Type26(Entity *entity, HandlerNode *node) {
    if (node->tick % entity->animLength == 0) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 0x1A;
    }
    entity->vtbl->moveZOnGround(entity, (entity->handlerTicks == 0x6E) ? -0x2D00 : -0x180, 0);
}

void Behavior_Type27(Entity *entity, HandlerNode *node) {
    if (node->tick % 70 == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x1B;
    }
    entity->vtbl->moveZ(entity, -0x80, 0);
    if (entity->handlerTicks < 0x64) {
        entity->vtbl->moveY(entity, 0x20, 0);
    } else if (entity->handlerTicks > 300) {
        entity->vtbl->moveY(entity, -0x20, 0);
    }
}

void Behavior_Type119(Entity *entity) {
    entity->vtbl->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type29(Entity *entity) {
    DreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vtbl->getDreamColor(dreamSys) == 7) {
            entity->vtbl->scale(entity, 1, &g_scaleTriple);
            entity->vtbl->moveY(entity, -0x7800, 0);
        }
        entity->state = rand() % 5;
    }
    if (entity->state == 0) {
        entity->vtbl->rotate(entity, 0, &g_rotY1);
    }
}

void Behavior_Type30(Entity *entity) {
    DreamSys *dreamSys;
    s32 state;

    if (entity->state == 0) {
        dreamSys = entity->dreamSys;
        state = dreamSys->vtbl->getDreamColor(dreamSys);
        if (state == 1) {
            state = 0xB;
        } else {
            state = 0xC;
        }
        entity->state = state;
    }
    if (entity->state == 0xC) {
        entity->vtbl->scale(entity, 1, g_scaleDouble);
        entity->vtbl->moveY(entity, -0x1E, 0);
        return;
    }
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    if (entity->state == 0xB) {
        entity->vtbl->moveZ(entity, -0x64, 0);
        if ((u32)(entity->handlerTicks - 0x55) < 0x1E) {
            entity->vtbl->moveY(entity, 0x50, 0);
            return;
        }
        if (entity->handlerTicks == 0x78) {
            entity->state = 0xD;
        }
        return;
    }
    if (entity->state == 0xD) {
        entity->vtbl->setPosition(entity, &entity->dreamSys->object.coord->coord.t);
        entity->vtbl->move(entity, g_moveYNeg1500Z1024);
    }
}

void Behavior_Type31(Entity *entity, HandlerNode *node) {
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    entity->dreamSys->vtbl->stopControls(entity->dreamSys, 1);
    if ((node->tick % 10) < 3) {
        node->fade = 0;
        node->voices[0].sound = 0xD;
        node->voices[1].sound = 0xD;
        node->voices[2].sound = 0xD;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vtbl->stopAnimation(entity);
        entity->vtbl->notify(entity, 0xA);
    }
}

void Behavior_Type32(Entity *entity) {
    entity->vtbl->moveZ(entity, -0x1E, 0);
}

void Behavior_Type33(Entity *entity, HandlerNode *node) {
    if (entity->touched != 0) {
        entity->vtbl->scale(entity, 1, &g_scaleQuarter);
    } else if (node->tick % 30 == 0) {
        node->fade = 0;
        node->voices[0].sound = 3;
    }
    entity->vtbl->moveZOnGround(entity, -0x1E, 0);
    if (entity->contact != 0) {
        entity->vtbl->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type34(Entity *entity) {
    s32 ticks;

    ticks = entity->handlerTicks;
    if (ticks >= 0x190 && ticks < 0x19A) {
        entity->vtbl->rotate(entity, 0, g_rotY9);
    } else if ((ticks >= 0x2BC && ticks < 0x2C6) || (ticks >= 0x33E && ticks < 0x342)) {
        entity->vtbl->rotate(entity, 0, g_rotYNeg9);
    } else if (ticks >= 0x353) {
        entity->vtbl->sleep(entity);
    }
    entity->vtbl->moveZ(entity, (entity->handlerTicks < 0x320) ? -0x3C : -0x200, 1);
}

void Behavior_Type35(Entity *entity) {
    s32 phase;

    phase = entity->handlerTicks % 500;
    entity->vtbl->moveY(entity, (entity->handlerTicks % 6 < 3) ? -0x40 : 0x40, 0);
    entity->vtbl->moveX(entity, (entity->handlerTicks % 12 < 6) ? -0x40 : 0x40, 0);
    entity->vtbl->moveZ(entity, (entity->handlerTicks % 64 < 0x20) ? -0x80 : 0x80, 0);
    if (phase < 0x20) {
        entity->vtbl->move(entity, g_moveYNeg64);
    } else if (phase < 0x40) {
        entity->vtbl->move(entity, g_moveY64);
    }
}

void Behavior_Type36(Entity *entity) {
    if (entity->state == 0) {
        entity->vtbl->scale(entity, 1, (rand() & 1) ? g_scaleDouble : &g_scaleSix);
        entity->state = 0xB;
    }
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x7000) {
        entity->vtbl->moveZ(entity, 0x100, 0);
    }
}

void Behavior_Type37(Entity *entity) {
    entity->vtbl->moveY(entity, -0x5A, 0);
}

void Behavior_OperaSinger(Entity *entity, HandlerNode *node) {
    if (node->tick % 120 == 0) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 1;
    }
}

void Behavior_Mushroom(Entity *entity, HandlerNode *node) {
    s32 dayRest;
    void (*animFn)(void *);

    if (entity->handlerTicks == 0) {
        dayRest = entity->dreamSys->vtbl->getDayNumber(entity->dreamSys, 0) % 3;
        if (dayRest == 0) {
            if (rand() % 3 == 0) {
                entity->vtbl->scale(entity, 1, g_scaleTallFour);
            }
        } else if (dayRest == 2) {
            entity->vtbl->scale(entity, 1, g_scaleTallFour);
        }
    }
    if (node->tick == (node->tick / 22) * 22) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 2;
    }
    if (rand() % 12 == 0) {
        animFn = entity->vtbl->stopAnimation;
    } else if (rand() % 6 == 0) {
        animFn = entity->vtbl->playAnimation;
    } else {
        return;
    }
    animFn(entity);
}

void Behavior_Type40(Entity *entity, HandlerNode *node) {
    void *turn = 0;

    if (node->tick % 7 == 0) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 3;
        node->voices[0].volume = 0x40;
        node->voices[0].endVolume = 0x40;
    }

    if (entity->handlerTicks == 0xC8) {
        turn = &g_rotYNeg90;
    } else if (entity->handlerTicks == 0x190) {
        turn = g_rotY180;
    } else if (entity->handlerTicks == 0x258) {
        turn = &g_rotY90;
    } else if (entity->handlerTicks == 0x320) {
        turn = g_rotY180;
        entity->handlerTicks = -1;
    }

    if (turn != 0) {
        entity->vtbl->rotate(entity, 0, turn);
    }
    entity->vtbl->moveZOnGround(entity, -0x1E, 0);
    if (entity->contact != 0) {
        entity->vtbl->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type41(Entity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        entity->state = rand() % 5 + 0xA;
    }
    if (entity->state < 0xE || entity->handlerTicks < 0x140) {
        Behavior_TrainRun(entity, node, 0xBB8, 0x1F4, -0x100);
        return;
    }
    if (entity->state == 0xE && !(entity->handlerTicks & 3)) {
        g_type41Scale[5] = rand() % 32 + 1;
        entity->vtbl->scale(entity, 1, g_type41Scale);
    }
}

void Behavior_Type42(Entity *entity, HandlerNode *node) {
    s32 sound;

    if (entity->handlerTicks < 0x14) {
        entity->vtbl->stopAnimation(entity);
        entity->vtbl->moveZ(entity, -0x1E, 0);
        return;
    }
    if (entity->handlerTicks == 0x14) {
        entity->vtbl->playAnimation(entity);
        sound = 5;
        node->fade = 0;
    } else {
        if (entity->handlerTicks % (entity->animLength * 3 + 0x14) != 0) {
            return;
        }
        entity->vtbl->stopAnimation(entity);
        sound = -2;
    }
    node->voices[0].sound = sound;
}

void Behavior_Type43(Entity *entity, HandlerNode *node) {
    s16 *angles;
    s32 amount;

    Behavior_RollWideOrSlide(entity);
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->animFrame == 0 || entity->animFrame == 0xF) {
        node->voices[0].sound = 0x12;
        node->voices[1].sound = 0x12;
    }
    if (entity->handlerTicks >= 0x141) {
        if (rand() & 1) {
            amount = -0x3C;
        } else {
            amount = 0x3C;
        }
        entity->vtbl->moveX(entity, amount, 0);
        if (rand() & 3) {
            angles = g_rotYNeg9;
        } else {
            angles = g_rotY9;
        }
        entity->vtbl->rotate(entity, 0, angles);
    }
}

void Behavior_Type44(Entity *entity, HandlerNode *node) {
    s16 *angles;
    s32 amount;

    Behavior_RollWideOrSlide(entity);
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->animFrame == 7 || entity->animFrame == 0x16) {
        node->voices[0].sound = 3;
    }
    if ((u32)(entity->handlerTicks - 0x12C) < 0x14) {
        entity->vtbl->moveZ(entity, -0x3C, 0);
    } else if ((u32)(entity->handlerTicks - 0x141) < 0x13) {
        entity->vtbl->rotate(entity, 0, g_rotYNeg9);
    } else if (entity->handlerTicks >= 0x141) {
        if (rand() & 1) {
            amount = 0x80;
        } else {
            amount = -0x80;
        }
        entity->vtbl->moveX(entity, amount, 1);
        if (rand() & 3) {
            angles = g_rotYNeg9;
        } else {
            angles = g_rotY9;
        }
        entity->vtbl->rotate(entity, 0, angles);
    }
}

static void Behavior_RollWideOrSlide(Entity *entity) {
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand() % 10;
        if (roll >= 8) {
            entity->vtbl->scale(entity, 1, g_scaleWideThree);
        } else if (roll >= 5) {
            entity->state = 0xA;
        }
    }
    if (entity->state == 0xA && entity->handlerTicks >= 0xC9) {
        entity->vtbl->move(entity, g_moveZNeg256);
    }
}

void Behavior_Type45(void) {
}

void Behavior_Flower(Entity *entity, HandlerNode *node) {
    s32 dayRest;
    s32 roll;

    if (entity->handlerTicks == 0) {
        dayRest = entity->dreamSys->vtbl->getDayNumber(entity->dreamSys, 0) % 3;
        if (dayRest == 0) {
            roll = rand();
            if (roll % 3 == 0) {
                entity->vtbl->scale(entity, 1, &g_scaleSix);
            }
        } else if (dayRest == 1) {
            entity->vtbl->scale(entity, 1, &g_scaleSix);
        }
    }
    if (node->tick == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x12;
    }
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type47(Entity *entity) {
    if (entity->touched != 0) {
        if (entity->state == 0) {
            entity->state = 0xC;
            entity->handlerTicks = 0;
            return;
        } else if (entity->state == 0xC) {
            if (entity->handlerTicks < 0x1E) {
                if (entity->dreamSys->vtbl->wasCirclePressed(entity->dreamSys) != 0) {
                    entity->dreamSys->vtbl->stopControls(entity->dreamSys, 0);
                    entity->handlerTicks = 0;
                    entity->state = 0xB;
                    return;
                }
            } else {
                entity->vtbl->notify(entity, 0xB);
                entity->state = 0xA;
                return;
            }
        } else if (entity->state == 0xB) {
            if (entity->handlerTicks == 0x64) {
                entity->vtbl->notify(entity, 0xC);
                return;
            }
            entity->dreamSys->vtbl->moveY(entity->dreamSys, -0x64, 0);
        }
    }
}

void Behavior_FloatingLips(Entity *entity, HandlerNode *node) {
    s32 amount;
    EntityVtbl *vt;

    if (entity->animFrame == 0x26) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 6;
    }
    amount = 0x1E;
    vt = entity->vtbl;
    if ((entity->handlerTicks % 10) < 5) {
        amount = -0x1E;
    }
    vt->moveY(entity, amount, 0);
    entity->vtbl->moveZ(entity, -0x1E, 1);
}

void Behavior_Type49(Entity *entity, HandlerNode *node) {
    DreamSysVtbl *dreamSysVtbl;
    s32 state;
    Vec3 *standPos;

    if (node->tick == 6) {
        node->fade = 0;
        node->voices[0].sound = 4;
        node->voices[1].sound = 4;
        node->voices[2].sound = 4;
    }
    if (entity->touched != 0) {
        state = entity->state;
        if (state == 0) {
            entity->state = 0xA;
            entity->handlerTicks = 0;
        } else if (state == 0xA) {
            if (entity->handlerTicks == 0xA) {
                entity->vtbl->notify(entity, 0xA);
            } else if (entity->dreamSys->vtbl->wasCirclePressed(entity->dreamSys) != 0) {
                dreamSysVtbl = entity->dreamSys->vtbl;
                if (entity->parent != 0) {
                    standPos = &entity->object.coord->workm.t;
                } else {
                    standPos = 0;
                }
                dreamSysVtbl->setPosition(entity->dreamSys, standPos);
                entity->dreamSys->vtbl->setRotation(entity->dreamSys, 1, &g_rotYNeg90);
                entity->dreamSys->vtbl->stopControls(entity->dreamSys, 0);
                entity->handlerTicks = 0;
                entity->state = 0xB;
            }
        } else if (state == 0xB) {
            dreamSysVtbl = entity->dreamSys->vtbl;
            dreamSysVtbl->setPosition(entity->dreamSys, entity->parent ? &entity->object.coord->workm.t : 0);
            if (entity->handlerTicks == 0x64) {
                entity->vtbl->notify(entity, 0xA);
            }
        }
    }
    entity->vtbl->moveZ(entity, -0x100, 0);
}

void Behavior_Type50(Entity *entity, HandlerNode *node) {
    s32 frame;

    if (entity->handlerTicks < (entity->animLength * 5)) {
        frame = entity->animFrame;
        if ((frame == 0xF) || (frame == 0x46)) {
            node->fade = 0;
            node->voices[0].sound = 7;
            node->voices[1].sound = 7;
            node->voices[2].sound = 7;
        }
    } else {
        entity->vtbl->sleep(entity);
        entity->state = 1;
    }
}

void Behavior_MazePenguin(Entity *entity, HandlerNode *node) {
    void *turn;
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if ((roll == ((roll / 5) * 5)) && (entity->state == 0)) {
            entity->vtbl->scale(entity, 1, &g_scaleSix);
            entity->vtbl->moveY(entity, 0x320, 0);
            entity->state = 0xB;
        }
    }
    turn = NULL;
    if (node->tick == ((node->tick / 5) * 5)) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 8;
    }
    if (entity->handlerTicks == 0x5A) {
        turn = &g_rotYNeg90;
    } else if (entity->handlerTicks == 0xA0) {
        turn = &g_rotY90;
    } else if (entity->handlerTicks == 0xDC) {
        if (rand() & 1) {
            turn = g_rotY180;
        }
    }
    if (turn != NULL) {
        entity->vtbl->rotate(entity, 0, turn);
    }
    entity->vtbl->moveZ(entity, -0x50, 1);
}

void Behavior_Type52(Entity *entity, HandlerNode *node) {
    s32 ticks;

    node->fade = entity->vtbl->getSoundFade(entity);
    ticks = entity->handlerTicks;
    if (ticks < 0xBC) {
        if (ticks == 0x54) {
            entity->vtbl->rotate(entity, 0, g_rotY180);
        }
        if (node->tick % 20 == 0) {
            node->voices[0].sound = 9;
        }
    } else if (ticks < 0xC8) {
        entity->vtbl->rotate(entity, 0, g_rotY9);
    } else {
        entity->vtbl->sleep(entity);
        node->voices[1].sound = 0x1E;
        entity->state = 1;
    }
    entity->vtbl->moveZOnGround(entity, -0x200, 0);
}

void Behavior_Type55(Entity *entity, HandlerNode *node) {
    s32 frame;

    frame = entity->animFrame;
    if (entity->handlerTicks == 0) {
        if (rand() % 3 == 0) {
            entity->vtbl->scale(entity, 1, &g_scaleTallTwo);
        }
    }
    node->fade = entity->vtbl->getSoundFade(entity);
    if (frame >= 0x20) {
        frame -= 0x20;
    }
    if ((frame == 9) || (frame == 0x11) || (frame == 0x17)) {
        node->voices[0].sound = 0x13;
        if (frame == 0x17) {
            node->voices[1].sound = 0x13;
        }
    }
}

void Behavior_Type56(Entity *entity) {
    if (entity->handlerTicks == 0) {
        entity->vtbl->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type57(Entity *entity, HandlerNode *node) {
    Fade *effect;
    s32 frame;

    if (entity->handlerTicks == 0) {
        entity->state = rand() % 3;
        if (entity->state == 0) {
            entity->vtbl->stopAnimation(entity);
            entity->vtbl->moveY(entity, 0x1800, 0);
        }
    }
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->state != 0) {
        frame = entity->animFrame;
        if (frame < 0x1E) {
            node->voices[0].sound = 0xC;
            node->voices[0].octave = -1;
            return;
        }
        if (frame == 0x1E) {
            node->voices[0].sound = -2;
            return;
        }
        if (frame == 0x23) {
            node->voices[2].sound = 0x16;
            node->voices[2].octave = -2;
            return;
        }
        if (frame == 0x30) {
            if (Entity_IsAtPointAhead(entity, &entity->object.coord->coord.t, 0xF, 0xA) != 0) {
                if (Entity_StartEffect(entity, 0, 0, 0xA, 0) != 0) {
                    effect = entity->effect;
                    effect->vtbl->startIn(effect, entity->clock, 4, 0);
                }
                if (rand() & 1) {
                    entity->vtbl->notify(entity, 0xB);
                    return;
                }
            }
        } else if (frame == 0x3B) {
            entity->vtbl->sleep(entity);
            entity->state = 1;
        }
    } else {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
        entity->vtbl->moveZ(entity, -0x200, 0);
        if (entity->handlerTicks >= 0x80 && entity->handlerTicks < 0x142) {
            entity->vtbl->moveY(entity, -0x80, 0);
            return;
        }
        if (entity->handlerTicks == 0x142) {
            entity->vtbl->playAnimation(entity);
            entity->state = 1;
        }
    }
}

void Behavior_Type58(Entity *entity, HandlerNode *node) {
    s32 liftedTicks;
    s32 fallenTicks;
    DreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        node->fade = 0;
        node->voices[0].sound = 0xC;
        if (entity->dreamSys->vtbl->getDreamColor(entity->dreamSys) == 6) {
            entity->state = 0xB;
        } else if (rand() % 3 == 0) {
            entity->state = 0xC;
        }
    }
    if (node->tick % 100 == 0) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
    }
    if (entity->state == 0xB) {
        if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->dreamSys->vtbl->stopControls(entity->dreamSys, 0);
            entity->state = 0xD;
            entity->handlerTicks = 0;
        }
    } else if (entity->state == 0xC) {
        if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->vtbl->stopAnimation(entity);
            entity->state = 0xE;
            entity->handlerTicks = 0;
        }
    }
    if (entity->state == 0xD) {
        liftedTicks = entity->handlerTicks;
        if (liftedTicks < 0x32) {
            entity->dreamSys->vtbl->moveY(entity->dreamSys, -0x14, 0);
        } else if (liftedTicks < 0x1F4) {
            dreamSys = entity->dreamSys;
            dreamSys->vtbl->moveX(dreamSys, liftedTicks % 40 < 0x14 ? -5 : 5, 0);
        } else if (liftedTicks == 0x1F4) {
            entity->vtbl->notify(entity, 0xC);
        }
    }
    if (entity->state == 0xE) {
        fallenTicks = entity->handlerTicks;
        if (fallenTicks < 0xA) {
            entity->vtbl->moveY(entity, 0xC8, 0);
            return;
        }
        if (fallenTicks == 0xA) {
            node->voices[0].sound = 0x12;
            node->fade = 0;
            node->voices[1].sound = 3;
            entity->vtbl->rotate(entity, 1, g_rotZNeg90);
            entity->vtbl->moveX(entity, 0x960, 0);
            entity->vtbl->moveY(entity, 0x5DC, 0);
            entity->parts[1]->vtbl->setVisible(entity->parts[1], 0);
            entity->state = 1;
        }
    }
}

void Behavior_Type115(Entity *entity, HandlerNode *node) {
    DreamSys *dreamSys;
    s32 ticks;

    if (entity->state == 0 && Entity_IsDreamerNear(entity, 0x800) != 0) {
        entity->state = 0xB;
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        SceneNode_TurnToward((Entity *)entity->dreamSys, (DreamSys *)entity, 1, 1, 0);
        entity->vtbl->wake(entity);
        entity->vtbl->startHandler(entity);
        dreamSys = entity->dreamSys;
        dreamSys->vtbl->stopControls(dreamSys, 1);
        node->fade = 0;
        node->voices[0].sound = 0xC;
        entity->handlerTicks = 0;
    }
    if (entity->state == 0) {
        entity->vtbl->sleep(entity);
        entity->vtbl->stopHandler(entity);
    } else {
        if (node->tick % 100 == 0) {
            node->fade = entity->vtbl->getSoundFade(entity);
            node->voices[0].sound = 0xC;
            node->voices[0].octave = -1;
        }
        ticks = entity->handlerTicks;
        if (ticks < 3) {
            entity->vtbl->moveY(entity, 0x96, 0);
        } else if (ticks < 7) {
            entity->vtbl->moveY(entity, (ticks & 1) ? -0x32 : 0x32, 0);
        } else if (ticks == 0x64) {
            if (rand() & 1) {
                entity->state = 0xC;
                entity->vtbl->stopAnimation(entity);
            }
        } else if (ticks == 0xF0) {
            dreamSys = entity->dreamSys;
            dreamSys->vtbl->setControls(dreamSys, 1, 1);
        }
        if (entity->state == 0xC) {
            ticks = entity->handlerTicks;
            if (ticks < 0x82) {
                entity->vtbl->moveY(entity, 0xA, 0);
            } else if (ticks < 0xA0) {
                entity->vtbl->moveZ(entity, -0x1E, 0);
            } else if (ticks >= 0x12D) {
                SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
                entity->vtbl->moveZ(entity, -0x1E, 0);
            }
        }
    }
    if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x200) {
        entity->vtbl->sleep(entity);
        entity->vtbl->notify(entity, 0xA);
    }
}

void Behavior_Type59(Entity *entity, HandlerNode *node) {
    s32 roll;
    StageMap *map;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if (roll == ((roll / 10) * 10)) {
            entity->state = 0xC;
        }
    }
    if (node->tick == ((node->tick / 10) * 10)) {
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
    }
    if (entity->handlerTicks == 0) {
        if (rand() & 1) {
            entity->vtbl->moveY(entity, 0x800, 0);
        }
    }
    entity->vtbl->moveZ(entity, -0x80, 0);
    if ((entity->state == 0xC) && (entity->handlerTicks == 0x12C)) {
        map = entity->map;
        map->vtbl->startTileStretch(map, 1, 1);
    }
}

void Behavior_Type61(Entity *entity, HandlerNode *node) {
    if (entity->animFrame == 0x1E) {
        node->voices[0].sound = 0x12;
        node->fade = 0;
        node->voices[0].octave = -1;
    }
}

void Behavior_Type62(Entity *entity, HandlerNode *node) {
    DreamSys *dreamSys;
    StageMap *map;
    s32 state;

    if (entity->animFrame % 30 == 0) {
        node->voices[0].sound = 3;
        node->fade = 0;
        node->voices[0].octave = -2;
    }
    if (entity->handlerTicks >= 0x65) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    }
    entity->vtbl->moveZ(entity, -5, 0);
    if (entity->handlerTicks == 0x12C && entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x1000) {
        dreamSys = entity->dreamSys;
        dreamSys->vtbl->stopControls(dreamSys, 0);
    } else if (entity->handlerTicks == 0x1F4) {
        dreamSys = entity->dreamSys;
        dreamSys->vtbl->setControls(dreamSys, 1, 1);
    }
    if (entity->state == 0 && entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x400) {
        if (rand() & 1) {
            node->voices[1].sound = 6;
            node->fade = 0;
            node->voices[1].octave = -1;
            if (rand() & 1) {
                map = entity->map;
                map->vtbl->startTileStretch(map, -1, 0);
            }
            state = 0xA;
            entity->handlerTicks = 0;
        } else {
            state = 0xB;
        }
        entity->state = state;
    }
    if (entity->state == 0xA && entity->handlerTicks == 0x46) {
        entity->vtbl->notify(entity, (rand() & 1) ? 0xC : 0xB);
    }
}

void Behavior_Type64(Entity *entity, HandlerNode *node) {
    s32 phase;

    phase = node->tick % 300;
    node->fade = entity->vtbl->getSoundFade(entity);
    if (phase < 0x14) {
        node->voices[0].sound = 5;
        node->voices[0].octave = -2;
    } else if (phase == 0x16) {
        node->voices[0].sound = -2;
    }
    entity->vtbl->moveZ(entity, -0xA, 0);
}

void Behavior_Type65(Entity *entity) {
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if (roll % 3 == 0) {
            entity->vtbl->scale(entity, 1, &g_scaleHalf);
            entity->vtbl->moveY(entity, -0x12C, 0);
            entity->vtbl->rotate(entity, 1, &g_rotY90);
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0x7D0) {
            entity->vtbl->rotate(entity, 0, &g_rotYNeg90);
        }
        entity->vtbl->moveZ(entity, -0x14, 0);
    }
}

void Behavior_Type66(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == ((node->tick / 30) * 30)) {
        node->voices[0].sound = 0xD;
    }
}

void Behavior_Type67(Entity *entity) {
    if (entity->handlerTicks == 0) {
        if (rand() % 3 == 0) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0x1F6) {
            entity->vtbl->moveY(entity, 0x800, 0);
            SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        }
        if (entity->handlerTicks >= 0x1F5) {
            entity->vtbl->moveZ(entity, -0x200, 0);
        }
    }
}

void Behavior_Type68(Entity *entity, HandlerNode *node) {
    s16 speed;
    s32 coin;

    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == 0) {
        speed = (rand() & 1) ? -0x176 : -0xC0;
        entity->speed = speed;
    }
    if (entity->state == 0) {
        if (node->tick % 10 == 0) {
            node->voices[0].sound = 0x1C;
        }
        if (node->tick % 20 == 0) {
            node->voices[1].sound = 0x17;
            node->voices[1].octave = -1;
            node->voices[2].sound = 0x17;
            node->voices[2].octave = -1;
        } else if (node->tick % 20 == 0xE) {
            node->voices[1].sound = -2;
            node->voices[2].sound = -2;
        }
        if (!(entity->handlerTicks & 1)) {
            if (entity->dreamSys->vtbl->wasCirclePressed(entity->dreamSys) != 0) {
                entity->handlerTicks = -1;
                entity->state = 10;
                node->voices[0].sound = 0x12;
            }
        }
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        entity->vtbl->moveZ(entity, entity->speed, 1);
        return;
    } else if (entity->state == 10) {
        if (entity->handlerTicks < 8) {
            entity->vtbl->rotate(entity, 0, g_rotZ9);
            entity->vtbl->move(entity, g_moveY8);
            return;
        }
        node->voices[0].sound = 0x12;
        node->voices[1].sound = 3;
        entity->vtbl->stopHandler(entity);
        coin = rand() & 1;
        entity->state = coin == 0;
        return;
    }
}

void Behavior_Type69(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->animFrame == entity->animLength - 1) {
        node->voices[0].sound = 0x19;
        node->voices[0].octave = -2;
    }
    if ((node->tick & 3) == 0) {
        node->voices[1].sound = 0x15;
        node->voices[1].octave = -1;
    }
    if (node->tick % 200 == 0) {
        node->voices[2].sound = 0xD;
        node->voices[2].octave = 1;
    }
}

void Behavior_Type70(Entity *entity) {
    s32 speed;

    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->handlerTicks == 0x12C) {
        entity->vtbl->rotate(entity, 0, g_rotY180);
    }
    if (entity->handlerTicks < 0x258) {
        EntityVtbl *vt = entity->vtbl;

        speed = 0x100;
        if (entity->state == 0) {
            speed = -0x100;
        }
        vt->moveZ(entity, speed, 0);
    }
}

void Behavior_Type71(Entity *entity, HandlerNode *node) {
    s32 roll;

    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0;
        roll = rand() % 3;
        entity->vtbl->moveX(entity, roll * 0xC800, 0, roll);
    }
    if (entity->handlerTicks >= 0x961) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    }
    entity->vtbl->moveZ(entity, -0x1E, 0);
}

void Behavior_Type73(Entity *entity, HandlerNode *node) {
    s32 tick;

    tick = node->tick;
    node->fade = 0;
    if (tick == 0) {
        entity->dreamSys->vtbl->setRotation(entity->dreamSys, 1, &g_rotY90);
        entity->dreamSys->vtbl->stopControls(entity->dreamSys, 1);
        node->voices[0].sound = 0x19;
        node->voices[1].sound = 0x19;
        node->voices[2].sound = 0x19;
    } else if (tick == 0x14) {
        node->voices[1].sound = 0xD;
    }
    if (entity->handlerTicks == (entity->animLength - 1)) {
        entity->vtbl->sleep(entity);
    }
}

void Behavior_Type74(Entity *entity) {
    s32 ticks;

    if (entity->handlerTicks == 0) {
        entity->dreamSys->camera->vtbl->setClearColor(entity->dreamSys->camera, g_type74ClearColor);
        entity->state = rand() % 3;
        if (entity->dreamSys->object.coord->coord.t.z < 0x262) {
            entity->state = 0;
        }
    }
    if (entity->state != 0) {
        if (entity->animLength / 2 < entity->handlerTicks) {
            entity->dreamSys->vtbl->moveZ(entity->dreamSys, 0x80, 0);
        }
        if (entity->handlerTicks == entity->animLength - 0x1E) {
            entity->vtbl->notify(entity, 0xA);
        }
    } else {
        ticks = entity->handlerTicks;
        if (ticks >= 0x14 && ticks < 0x78) {
            entity->dreamSys->vtbl->moveZ(entity->dreamSys, -((ticks - 0x13) << 5), 1);
            if (entity->handlerTicks == 0x55) {
                entity->dreamSys->vtbl->setControls(entity->dreamSys, 1, 1);
            }
        }
    }
}

void Behavior_Type75(Entity *entity, HandlerNode *node) {
    if (node->tick == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x19;
        node->voices[1].sound = 0x19;
        node->voices[2].sound = 0x19;
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vtbl->stopAnimation(entity);
        entity->vtbl->notify(entity, 0xA);
    }
}

void Behavior_Type76(Entity *entity) {
    if (entity->touched != 0) {
        entity->vtbl->playAnimation(entity);
        if (entity->animFrame == entity->animLength - 1) {
            entity->vtbl->stopAnimation(entity);
            entity->vtbl->scale(entity, 0, g_scaleShrinkStep);
        }
    } else {
        entity->vtbl->stopAnimation(entity);
        entity->vtbl->rotate(entity, 0, g_rotY9);
    }
}

void Behavior_Type77(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick % 5 == 0) {
        node->voices[0].sound = 0x11;
        node->voices[0].octave = -2;
    }
    if (entity->animation == 0) {
        if (entity->handlerTicks == entity->animLength) {
            entity->vtbl->setAnimation(entity, 1);
            if (rand() & 1) {
                entity->state = 0xB;
            }
        }
    } else {
        if (entity->state == 0) {
            if (entity->handlerTicks == 0x3C || entity->handlerTicks == 0xD4 || entity->handlerTicks == 0x122 || entity->handlerTicks == 0x140) {
                entity->vtbl->rotate(entity, 0, &g_rotY90);
            }
            if (entity->handlerTicks == 0x18E) {
                entity->vtbl->rotate(entity, 0, &g_rotYNeg90);
            }
            entity->vtbl->moveZOnGround(entity, -0x32, 0);
        } else {
            if (entity->handlerTicks == 0x3C || entity->handlerTicks == 0x8C) {
                entity->vtbl->rotate(entity, 0, &g_rotY90);
            }
            if (entity->handlerTicks < 0xAE) {
                entity->vtbl->moveZOnGround(entity, -0x32, 0);
            }
            if (entity->handlerTicks == 0xAE) {
                entity->vtbl->stopHandler(entity);
                entity->state = 1;
            }
        }
    }
}

void Behavior_Type78(Entity *entity, HandlerNode *node) {
    s32 roll;
    s32 ticks;
    s32 length;
    void *factors;

    if (node->tick == 0) {
        g_type78Stopped = 0;
        roll = rand() % 3;
        if (roll == 1) {
            entity->state = 0xB;
        }
        if (roll == 2) {
            entity->state = 0xC;
        }
    }
    node->fade = entity->vtbl->getSoundFade(entity);
    if (entity->animPlaying != 0 && !(node->tick & 3)) {
        node->voices[0].sound = 0x1C;
    }
    length = entity->animLength;
    ticks = entity->handlerTicks;
    if (ticks == length - 1) {
        entity->handlerTicks = -1;
    } else if (ticks >= length / 2 + length / 4) {
        entity->vtbl->playAnimation(entity);
    } else if (ticks >= length / 2) {
        if (ticks == length / 2) {
            node->voices[0].sound = 0x10;
        }
        entity->vtbl->moveZ(entity, 0x6E, 0);
    } else if (ticks >= length / 4) {
        entity->vtbl->stopAnimation(entity);
        entity->vtbl->moveZ(entity, -0x6E, 0);
    }
    if (entity->state == 0xB && node->tick == 0x1FE) {
        entity->vtbl->moveY(entity, -0x17C, 0);
        entity->vtbl->rotate(entity, 0, &g_rotX90);
        entity->vtbl->stopHandler(entity);
        entity->state = 1;
        g_type78Stopped = 1;
    } else if (entity->state >= 0xC) {
        if (node->tick >= 0x14A && node->tick % 60 == 30) {
            roll = 0;
            if (rand() & 1) {
                factors = &g_scaleTallTwo;
                if (entity->state == 0xC) {
                    roll = 0x190;
                }
                entity->state = 0xD;
            } else {
                factors = &g_scaleOne;
                if (entity->state == 0xD) {
                    roll = -0x190;
                }
                entity->state = 0xC;
            }
            entity->vtbl->scale(entity, 1, factors);
            entity->vtbl->moveY(entity, roll, 0);
        }
    }
    if (node->tick == 0x208 && g_type78Stopped != 0) {
        entity->vtbl->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type79(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick % 10 == 0) {
        node->voices[0].sound = 0x19;
        node->voices[0].octave = 2;
    }
    entity->vtbl->rotate(entity, 0, g_rotY2);
    if ((entity->state == 0) && (entity->touched != 0)) {
        entity->vtbl->notify(entity, 0xB);
        entity->state = 0xB;
    }
}

void Behavior_Type80(Entity *entity, HandlerNode *node) {
    if (entity->handlerTicks < entity->animLength) {
        switch (entity->animFrame) {
        case 0:
            break;
        case 0x14:
            node->fade = 0;
            node->voices[0].sound = 0x10;
            break;
        }
    } else {
        entity->vtbl->stopAnimation(entity);
        entity->vtbl->move(entity, g_moveYNeg512);
    }
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type81(Entity *entity, HandlerNode *node) {
    s32 speed;
    s32 mode;

    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = rand() % 3;
    }
    if (entity->state != 0 && entity->touched != 0) {
        if (node->tick >= 0x3D) {
            node->tick = 0;
        }
        if (node->tick % 20 == 0) {
            node->fade = 0;
            node->voices[0].sound = 0x17;
            node->voices[0].octave = -1;
            node->voices[1].sound = 0x17;
            node->voices[1].octave = -1;
            node->voices[2].sound = 0x17;
            node->voices[2].octave = -2;
        } else if (node->tick % 20 == 14) {
            node->voices[0].sound = -2;
            node->voices[1].sound = -2;
            node->voices[2].sound = -2;
        }
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        mode = entity->state;
        if (mode == 1) {
            entity->vtbl->scale(entity, 0, g_scaleGrowStep);
            speed = -0x176;
            if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x200) {
                entity->vtbl->sleep(entity);
                entity->state = mode;
            }
        } else {
            entity->dreamSys->vtbl->stopControls(entity->dreamSys, 1);
            SceneNode_TurnToward((Entity *)entity->dreamSys, (DreamSys *)entity, 1, 1, 0);
            if (entity->state == 2) {
                if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x960) {
                    entity->state = 0xB;
                    entity->vtbl->notify(entity, 0xC);
                }
                speed = -0x60;
            } else {
                speed = 0;
            }
        }
    } else {
        node->fade = entity->vtbl->getSoundFade(entity);
        if (node->tick % 22 == 0) {
            node->voices[0].sound = 0x1C;
        }
        if (entity->handlerTicks >= 0x1F5) {
            SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        }
        if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x800) {
            entity->dreamSys->vtbl->moveZ(entity->dreamSys, -0x800, 0);
        }
        speed = -0x14;
    }
    entity->vtbl->moveZOnGround(entity, speed, 1);
    if (entity->contact != 0) {
        entity->vtbl->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type82(Entity *entity, HandlerNode *node) {
    s32 state;
    DreamSys *dreamSys;

    if (entity->state == 0 && entity->handlerTicks == 0) {
        if (rand() % 3) {
            state = (rand() & 1) ? 0xB : 0xC;
            entity->state = state;
        } else {
            entity->vtbl->stopHandler(entity);
            entity->vtbl->moveZ(entity, -0x5000, 0);
            rand();
        }
    }
    if (entity->state == 0xC) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        if (entity->handlerTicks == 0x14) {
            node->voices[0].sound = 0x12;
            node->fade = 0;
            node->voices[1].sound = 3;
            dreamSys = entity->dreamSys;
            dreamSys->vtbl->stopControls(dreamSys, 1);
        }
        if (entity->handlerTicks >= 0x15) {
            entity->vtbl->moveZ(entity, -0x28, 0);
        }
        if (entity->handlerTicks == 0x28) {
            entity->vtbl->notify(entity, 0xA);
        }
    } else if (entity->state == 0xB) {
        entity->vtbl->stopAnimation(entity);
        if (entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x200) {
            if (rand() % 3) {
                entity->vtbl->sleep(entity);
            } else {
                entity->vtbl->stopHandler(entity);
            }
        }
    }
}

void Behavior_Type83(Entity *entity, HandlerNode *node) {
    if (entity->animFrame == ((entity->animFrame / 15) * 15)) {
        node->voices[0].sound = 12;
        node->fade = 0;
        node->voices[0].octave = 2;
    }
    if (entity->handlerTicks == entity->animLength) {
        node->voices[0].sound = -2;
        entity->vtbl->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type84(Entity *entity, HandlerNode *node) {
    s32 frame;

    node->fade = entity->vtbl->getSoundFade(entity);
    frame = entity->animFrame;
    if (frame < 0x28) {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -2;
        node->voices[2].sound = 5;
        node->voices[2].octave = -1;
    } else if (frame == 0x28) {
        node->voices[0].sound = -2;
        node->voices[2].sound = -2;
    } else if (frame == 0x2D) {
        node->voices[1].sound = 0x12;
        node->voices[1].octave = 1;
    } else if (frame == 0x40) {
        node->voices[0].sound = 7;
    } else if (frame == 0x59) {
        entity->vtbl->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type85(Entity *entity, HandlerNode *node) {
    if (entity->state == 0) {
        if (entity->animFrame == 5) {
            Behavior_QueueLowSound7(node);
        }
        if (entity->handlerTicks == entity->animLength) {
            entity->vtbl->stopAnimation(entity);
            entity->state = 0xA;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xA) {
        if (entity->handlerTicks < 0xA) {
            entity->vtbl->rotate(entity, 0, g_rotY9);
            if (entity->dreamSys->vtbl->wasCirclePressed(entity->dreamSys) != 0) {
                Behavior_QueueLowSound7(node);
                entity->state = 0xC;
                entity->handlerTicks = -1;
            }
        } else {
            entity->dreamSys->vtbl->stopControls(entity->dreamSys, 1);
            entity->state = 0xB;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xB) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        if (entity->handlerTicks < 0x1E) {
            entity->vtbl->moveZ(entity, -10, 0);
        } else {
            Behavior_QueueLowSound7(node);
            if (Entity_StartEffect(entity, 0, 0, 0x1E, 0) != 0) {
                entity->effect->vtbl->startIn(entity->effect, entity->clock, 7, 0);
            }
            entity->state = 0xD;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xD) {
        if (entity->handlerTicks < 0x5A) {
            if (entity->handlerTicks == 0x1E) {
                if (Entity_StartEffect(entity, 0, 0, 0xA, 0) != 0) {
                    entity->effect->vtbl->startOut(entity->effect, entity->clock, 0, 0);
                }
            }
            entity->dreamSys->vtbl->setRotation(entity->dreamSys, 0, g_rotZ1);
        } else {
            Behavior_QueueSound18And3(node);
            entity->dreamSys->vtbl->setRotation(entity->dreamSys, 1, g_rotY180);
            entity->vtbl->notify(entity, rand() % 5 ? 0xA : 0xC);
            entity->state = 0xE;
        }
    } else if (entity->state == 0xC) {
        if (entity->handlerTicks < 0xA) {
            entity->vtbl->rotate(entity, 0, g_rotZNeg9);
        } else {
            Behavior_QueueSound18And3(node);
            entity->vtbl->stopHandler(entity);
            entity->state = 1;
        }
    }
}

void Behavior_Type86(Entity *entity, HandlerNode *node) {
    if (entity->handlerTicks < 0xA) {
        entity->vtbl->stopAnimation(entity);
    } else if (entity->handlerTicks == 0xA) {
        entity->vtbl->playAnimation(entity);
    }
    if (entity->animFrame == 0xA) {
        Behavior_QueueSound18And3(node);
    }
    if (entity->handlerTicks == entity->animLength + 0xA) {
        entity->vtbl->stopHandler(entity);
        entity->state = 1;
    }
}

static void Behavior_QueueLowSound7(HandlerNode *node) {
    node->fade = 0;
    node->voices[0].sound = 7;
    node->voices[0].octave = -2;
    node->voices[1].sound = 7;
    node->voices[1].octave = -2;
    node->voices[2].sound = 7;
    node->voices[2].octave = -2;
}

static void Behavior_QueueSound18And3(HandlerNode *node) {
    node->voices[0].sound = 0x12;
    node->fade = 0;
    node->voices[1].sound = 3;
    node->voices[2].sound = 3;
}

void Behavior_Type87(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0x12;
    }
    if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
}

void Behavior_Type88(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == entity->animLength / 2) {
        node->voices[0].sound = 0x12;
    }
    if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
}

void Behavior_Type89(Entity *entity, HandlerNode *node) {
    s32 ticks;

    ticks = entity->handlerTicks;
    if (ticks == 0x14) {
        node->voices[0].sound = 0x12;
        node->fade = 0;
        node->voices[1].sound = 3;
        return;
    }
    if (ticks == entity->animLength) {
        entity->vtbl->stopHandler(entity);
        entity->state = 1;
        if (rand() & 1) {
            entity->vtbl->notify(entity, 0xB);
        }
    }
}

void Behavior_Type90(Entity *entity, HandlerNode *node) {
    s32 sound;

    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == 0) {
        if (rand() & 1) {
            sound = 2;
        } else {
            sound = 1;
        }
        node->voices[0].sound = sound;
        node->voices[0].octave = 2;
    }
}

void Behavior_Type91(Entity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        if (Entity_StartEffect(entity, 0, 0, 5, 0)) {
            if (rand() & 1) {
                entity->vtbl->move(entity, g_moveYNeg256);
            }
            entity->effect->vtbl->startIn(entity->effect, entity->clock, 0, 0);
        }
    } else if (entity->animFrame == 0) {
        do {
            entity->animData = entity->vtbl->applyFrame(entity, entity->animData, 0);
            entity->animFrame++;
        } while (entity->animFrame < 0x18);
    }
    if (entity->animFrame >= 0x19) {
        entity->vtbl->moveZ(entity, -0x14, 0);
        entity->dreamSys->vtbl->stopControls(entity->dreamSys, 1);
    }
    if (entity->handlerTicks == 0x32) {
        entity->vtbl->notify(entity, 0xA);
    } else if (entity->handlerTicks == 0xC) {
        node->fade = 0;
        node->voices[0].sound = 0x15;
    }
    entity->vtbl->scale(entity, 1, g_scaleNarrowTall);
}

void Behavior_Type92(Entity *entity, HandlerNode *node) {
    s32 frame;

    if (entity->animation == 0) {
        if (entity->touched != 0) {
            SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
            entity->vtbl->setAnimation(entity, 1);
            entity->dreamSys->vtbl->stopControls(entity->dreamSys, 1);
        } else if (entity->animFrame == 0) {
            do {
                entity->animData = entity->vtbl->applyFrame(entity, entity->animData, 0);
                frame = entity->animFrame + 1;
                entity->animFrame = frame;
            } while (frame < 0x18);
        }
    } else {
        if (entity->animFrame == 0) {
            node->fade = 0;
            node->voices[0].sound = 0x16;
        } else if (entity->animFrame == entity->animLength - 1) {
            node->fade = 0;
            node->voices[1].sound = 0x12;
            entity->vtbl->notify(entity, 0xA);
        }
    }
    entity->vtbl->scale(entity, 1, g_scaleNarrowTall);
}

void Behavior_Type93(Entity *entity, HandlerNode *node) {
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick % 10 == 0) {
        node->voices[0].sound = 3;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vtbl->setAnimation(entity, 1);
    }
    if (entity->animation == 1) {
        entity->vtbl->moveZ(entity, -0x80, 1);
    }
}

void Behavior_Type94(Entity *entity, HandlerNode *node) {
    s32 roll;
    DreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vtbl->getDreamColor(dreamSys) != 7) {
            entity->state = 0xB;
        }
    }
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick == (node->tick / 10) * 10) {
        node->voices[0].sound = 0xE;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vtbl->setAnimation(entity, 1);
        if (entity->state != 0 && !(rand() & 1)) {
            entity->vtbl->scale(entity, 1, &g_scaleSix);
            entity->vtbl->moveY(entity, 0x800, 0);
        }
        roll = rand();
        if (roll == (roll / 3) * 3) {
            entity->vtbl->rotate(entity, 0, &g_rotY180);
        }
    }
    if (entity->animation != 0) {
        entity->vtbl->moveZ(entity, -0x80, 1);
    }
}

void Behavior_Type95(Entity *entity) {
    if (entity->handlerTicks == 0) {
        entity->vtbl->setAnimation(entity, 3);
    } else if (entity->handlerTicks == entity->animLength) {
        entity->vtbl->setAnimation(entity, 1);
    }
    if (entity->animation == 1) {
        entity->vtbl->moveZ(entity, -0x80, 0);
    }
}

void Behavior_Type96(Entity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        entity->vtbl->setAnimation(entity, rand() % 4);
        return;
    }
    if (entity->handlerTicks % entity->animLength == 0) {
        entity->vtbl->setAnimation(entity, rand() % 4);
        node->fade = entity->vtbl->getSoundFade(entity);
        node->voices[0].sound = 0x16;
        node->voices[0].octave = 2;
        node->voices[0].volume = 0x40;
        node->voices[0].endVolume = 0x20;
    }
}

void Behavior_EraseFlashbacks(Entity *entity) {
    if (entity->touched != 0 && Entity_StartEffect(entity, 0, 0, 0xA, 0)) {
        entity->effect->vtbl->startIn(entity->effect, entity->clock, 7, 0);
        entity->vtbl->sleep(entity);
        entity->dreamSys->vtbl->clearFlashbacks(entity->dreamSys);
    }
    entity->vtbl->moveZ(entity, -0x1E, 1);
}

void Behavior_Type102(Entity *entity, HandlerNode *node) {
    DreamSys *dreamSys;
    void *factors;
    s32 length;
    s32 ticks;

    if (entity->handlerTicks == 0) {
        entity->vtbl->moveY(entity, -0x200, 0);
    }
    node->fade = entity->vtbl->getSoundFade(entity);
    length = entity->animLength;
    if (entity->animFrame == length / 2) {
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
        node->voices[1].sound = 3;
        node->voices[1].octave = -2;
    }
    if (entity->handlerTicks >= 0x33) {
        entity->vtbl->rotate(entity, 0, &g_rotYNegThird);
    }
    if (entity->handlerTicks >= 0x30D) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        ticks = entity->handlerTicks;
        if (ticks >= 0x790) {
            factors = &g_scaleOne;
        } else if (ticks >= 0x78B) {
            factors = g_scaleNarrowTall;
        } else if (ticks >= 0x786) {
            factors = &g_scaleHalf;
        } else {
            factors = &g_scaleEighth;
            if (ticks >= 0x781) {
                factors = &g_scaleQuarter;
            }
        }
        entity->vtbl->scale(entity, 1, factors);
        if (entity->handlerTicks < 0x7D0) {
            entity->vtbl->moveZ(entity, -0x40, 0);
        } else {
            entity->state = 1;
        }
    } else {
        entity->vtbl->moveZ(entity, -0x100, 0);
    }
    if ((entity->touched != 0) && (entity->state == 0)) {
        dreamSys = entity->dreamSys;
        entity->state = 0xC;
        dreamSys->vtbl->stopControls(dreamSys, 1);
        entity->vtbl->notify(entity, 0xA);
    }
    if (entity->state == 0xC) {
        dreamSys = entity->dreamSys;
        dreamSys->vtbl->moveZ(dreamSys, 0x100, 0);
    }
}

void Behavior_Type103(Entity *entity) {
    s32 roll;
    StageMap *map;

    if (entity->handlerTicks == 0x2BC) {
        roll = rand();
        if (roll == (roll / 3) * 3) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks < 0x3FC) {
            entity->vtbl->rotate(entity, 0, g_rotYNegHalf);
            entity->vtbl->moveY(entity, 0x1E, 0);
        }
        if (entity->handlerTicks == 0x3A2) {
            entity->vtbl->notify(entity, 0xA);
        }
    } else if (entity->handlerTicks == 0x64 || entity->handlerTicks == 0x320) {
        if (rand() % 5 == 0) {
            map = entity->map;
            map->vtbl->startTileStretch(map, 4, 0);
        }
    }
    entity->vtbl->moveZ(entity, -0x1E, 0);
}

void Behavior_Type104(Entity *entity) {
    entity->vtbl->scale(entity, 1, &g_scaleQuarter);
    if (entity->handlerTicks >= 201 && entity->handlerTicks < 300) {
        entity->vtbl->moveY(entity, -0x20, 0);
    }
}

void Behavior_Type105(Entity *entity) {
    entity->vtbl->setVisible(entity, (rand() % 20) == 0);
}

void Behavior_Type106(Entity *entity) {
    if (entity->handlerTicks == 0) {
        if ((rand() & 1) == 0) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0) {
            entity->vtbl->stopAnimation(entity);
        }
        entity->vtbl->scale(entity, 1, g_scaleThinTall);
    } else {
        if (entity->handlerTicks == 0) {
            entity->vtbl->setAnimation(entity, 1);
        }
        entity->vtbl->moveX(entity, (entity->handlerTicks % 20) < 10 ? 0x20 : -0x20, 0);
    }
}

void Behavior_Type108(Entity *entity, HandlerNode *node) {
    Behavior_Type71(entity, node);
    entity->vtbl->scale(entity, 1, &g_scaleSix);
}

void Behavior_YellowDayBeast(Entity *entity) {
    entity->vtbl->scale(entity, 1, &g_scaleHalf);
    entity->vtbl->moveZ(entity, -10, 0);
}

void Behavior_BridgeGeisha(Entity *entity) {
    entity->vtbl->scale(entity, 1, g_scaleTwoFifths);
    entity->vtbl->stopAnimation(entity);
    if (entity->state == 0 && entity->vtbl->distanceTo(entity, entity->dreamSys) < 0x800) {
        entity->state = 0xA;
        entity->handlerTicks = 0;
    }
    if (entity->state == 0xA) {
        if (entity->handlerTicks < 0x2D) {
            entity->vtbl->rotate(entity, 0, g_rotY4);
        }
        if (entity->handlerTicks >= 0x1F5) {
            entity->state = 0;
        }
    }
}

void Behavior_FlyingTrain(Entity *entity, HandlerNode *node) {
    DreamSys *dreamSys;
    s32 ticks;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vtbl->getDreamColor(dreamSys) == 5) {
            entity->state = 0xB;
        }
    }
    if (entity->state != 0 && entity->handlerTicks >= 0x870) {
        ticks = entity->handlerTicks;
        if ((u32)(ticks - 0x870) < 0x191U) {
            if (ticks == 0x870) {
                entity->vtbl->stopAnimation(entity);
                node->voices[0].sound = -2;
                node->voices[1].sound = -2;
                node->voices[2].sound = -2;
                return;
            }
            if ((u32)(ticks - 0x9F6) < 0xAU) {
                node->voices[0].sound = 5;
                node->voices[0].octave = -2;
                return;
            }
            if (ticks == 0xA00) {
                entity->vtbl->playAnimation(entity);
                node->tick = 1;
            }
        } else if (ticks >= 0xA03) {
            if (ticks >= 0xAF1) {
                entity->vtbl->moveY(entity, -0x20, 0);
            }
            Behavior_TrainRun(entity, node, 0x1E1, 0xFA0, -0x3C);
        }
    } else {
        Behavior_TrainRun(entity, node, 0x1E1, 0x884, -0x3C);
    }
}

static void Behavior_TrainRun(Entity *entity, HandlerNode *node, s32 turnTick, s32 leaveTick, s32 speed) {
    node->fade = 0;
    if (node->tick == 6) {
        node->voices[0].sound = 4;
        node->voices[1].sound = 4;
        node->voices[2].sound = 4;
    }
    if ((entity->handlerTicks >= turnTick && entity->handlerTicks <= turnTick + 0x5B) ||
        (entity->handlerTicks >= turnTick + 0x155 && entity->handlerTicks <= turnTick + 0x1B1) ||
        (entity->handlerTicks >= turnTick + 0x2BA && entity->handlerTicks <= turnTick + 0x317)) {
        entity->vtbl->rotate(entity, 0, &g_rotY1);
    }
    entity->vtbl->moveZ(entity, speed, 0);
    if (entity->handlerTicks == leaveTick) {
        entity->vtbl->sleep(entity);
        entity->state = 1;
    }
}

void Behavior_Type113(Entity *entity, HandlerNode *node) {
    Behavior_MazePenguin(entity, node);
}

void Behavior_RedDayPenguin(Entity *entity) {
    s16 *angles;

    if (rand() % 3 == 0) {
        return;
    }
    if (rand() % 3 != 0) {
        angles = g_rotY9;
    } else {
        angles = g_rotYNeg9;
    }
    entity->vtbl->rotate(entity, 0, angles);
}

void Behavior_Type117(Entity *entity) {
    entity->vtbl->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type118(Entity *entity) {
    entity->vtbl->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type121(Entity *entity) {
    entity->vtbl->scale(entity, 1, &g_scaleQuarter);
}

void Behavior_Type123(Entity *entity) {

    if (entity->handlerTicks == 0) {
        if (rand() % 5 == 0) {
            entity->state = 0xB;
        }
    }
    entity->vtbl->stopAnimation(entity);
    entity->vtbl->moveZ(entity, 0x64, 0);
    if (entity->handlerTicks == 0x3E8) {
        entity->vtbl->stopHandler(entity);
        entity->state = 1;
    }
    if ((entity->state == 0xB) && (entity->handlerTicks >= 0x12D)) {
        entity->dreamSys->vtbl->onPad(entity->dreamSys, 0, 2);
        entity->dreamSys->vtbl->onPad(entity->dreamSys, 0, 7);
    }
}

void Behavior_OddDayGeisha(Entity *entity, HandlerNode *node) {
    if (((entity->handlerTicks == 0) && !(rand() & 3)) || (entity->handlerTicks == 0xE10)) {
        entity->vtbl->sleep(entity);
        entity->state = 1;
    }
    entity->vtbl->scale(entity, 1, g_scaleTwoFifths);
    node->fade = entity->vtbl->getSoundFade(entity);
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
        node->voices[0].octave = 1;
    }
    entity->vtbl->moveZ(entity, -0xA, 0);
}

void Behavior_TinyLips(Entity *entity) {
    SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
    entity->vtbl->scale(entity, 1, &g_scaleTiny);
    entity->vtbl->moveZ(entity, -0x1E, 1);
}

void Behavior_Type129(Entity *entity) {
    if (entity->handlerTicks == 0) {
        entity->state = (rand() % 2) + 0xA;
    }
    entity->vtbl->stopAnimation(entity);
    if (entity->handlerTicks >= 0xC9) {
        SceneNode_TurnToward(entity, entity->dreamSys, 1, 0, 0);
        if (entity->state == 0xA) {
            entity->vtbl->moveZOnGround(entity, -0x200, 0);
        }
    }
}

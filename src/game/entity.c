#include "common.h"
#include "game/entity.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/handler_node.h"
#include "game/fade.h"
#include "game/model.h"
#include "game/view.h"
#include "psyq/libc.h"

/*
 * Entities and their behaviour handlers (record +0xC). A handler runs once per tick as
 * handler(entity, node): Entity_StartHandler registers it in the node at Entity +0x9C
 * (HandlerNode_Start) and slot 0x11C (Entity_RunHandler) runs HandlerNode_Run, which calls the
 * handler, then plays the sounds the handler asked for on the entity's sound bank (+0x58).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The animations of a model file (+0x30): animation i is anims->list->entries[i]->data. */
typedef struct ModelAnimData {
    u8 pad_00[0x4];
    s32 frameCount; /* 0x04 */
    /* 0x08 the first frame: u16 command count at +2, commands from +8 (Model_ApplyFrame) */
} ModelAnimData;

typedef struct ModelAnimEntry {
    u8 pad_00[0x10];
    ModelAnimData *data; /* 0x10 */
} ModelAnimEntry;

typedef struct ModelAnimList {
    u8 pad_00[0x8];
    ModelAnimEntry *entries[1]; /* 0x08 */
} ModelAnimList;

typedef struct ModelAnimSet {
    u8 pad_00[0x10];
    ModelAnimList *list; /* 0x10 */
} ModelAnimSet;

/* The object at +0x2C of a model file: frame command 2 asks its slot 0x80 for a texture. */
typedef struct ModelTexturesVtbl {
    u8 pad_00[0x80];
    s32 (*getModel)(void *self, s32 index); /* 0x80 Tmd_GetModel (tmd.h TmdVtbl) */
} ModelTexturesVtbl;

typedef struct ModelTextures {
    ModelTexturesVtbl *vt;
} ModelTextures;

/* A model's file object at +0x5C: part ids, frame commands, animations. */
typedef struct ModelFileVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(void *self);            /* 0x04 */
    u8 pad_08[0x64 - 0x08];
    void (*onLoaded)(void *self, void *arg);  /* 0x64 Mom_OnLoaded (file_base.h FileVtbl); Behavior_Type74 passes a 4-byte word */
    u8 pad_68[0x80 - 0x68];
    s32 (*getPartIds)();                     /* 0x80 (self, ids, &current): fills the part ids, returns their count */
    s32 *(*readCommand)();                   /* 0x84 (self, command, &part, &type, &flags, &size): a frame command's data */
} ModelFileVtbl;

typedef struct ModelFile {
    ModelFileVtbl *vt;
    u8 pad_04[0x2C - 0x04];
    ModelTextures *textures; /* 0x2C */
    ModelAnimSet *anims;     /* 0x30 */
} ModelFile;

/* An entity's position block (+0x14), as the handlers read it (entity.h Coord2). */
typedef union BehaviorPos {
    u8 *bytes;
    Coord2 *coord;
} BehaviorPos;

/*
 * The DreamSys (g_symDreamSys) as the handlers see it through Entity +0x94: the dreamer they face,
 * push and test. Slots 0x44 to 0xCC are the model base class's (ModelVtbl).
 */
typedef struct BehaviorDreamSysVtbl {
    u8 pad_00[0x44];
    void (*rotate)(void *self, s32 absolute, void *angles); /* 0x44 SceneNode_SetRotation */
    u8 pad_48[0x94 - 0x48];
    void (*onPad)(void *self, s32 pad, s32 button);        /* 0x94 DreamSys_OnPad */
    u8 pad_98[0xB8 - 0x98];
    void (*setPosition)(void *self, void *pos);             /* 0xB8 Actor_SetPos */
    u8 pad_BC[0xC4 - 0xBC];
    void (*moveZ)(void *self, s32 amount, s32 animate);     /* 0xC4 Actor_MoveZ */
    void (*moveX)(void *self, s32 amount, s32 animate);     /* 0xC8 Actor_MoveX */
    void (*moveY)(void *self, s32 amount, s32 animate);     /* 0xCC Actor_MoveY */
    u8 pad_D0[0x100 - 0xD0];
    s32 (*wasCirclePressed)(void *self);                    /* 0x100 DreamSys_WasCirclePressed, returns DreamSys +0x74 */
    u8 pad_104[0x130 - 0x104];
    void (*stopControls)(void *self, s32 stopLook);         /* 0x130 DreamSys_StopControls */
    void (*setControls)(void *self, s32 unused, s32 lookMode); /* 0x134 DreamSys_SetControls */
    u8 pad_138[0x1A0 - 0x138];
    s32 (*getDayNumber)(void *self, s32 *out);              /* 0x1A0 DreamSys_GetDayNumber */
    u8 pad_1A4[0x200 - 0x1A4];
    s32 (*getDreamColor)(void *self);                       /* 0x200 DreamSys_GetDreamColor */
    u8 pad_204[0x21C - 0x204];
    void (*clearFlashbacks)(void *self);                    /* 0x21C DreamSys_ClearFlashbacks */
} BehaviorDreamSysVtbl;

typedef struct BehaviorDreamSys {
    BehaviorDreamSysVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    BehaviorPos pos;         /* 0x14 */
    u8 pad_18[0x5C - 0x18];
    View *camera;             /* 0x5C the DreamView (g_viewVtbl): Behavior_Type74 sets its clear color */
} BehaviorDreamSys;

/*
 * Entity class vtable 0x80089AD4 as the handlers call it. Slots up to 0x140 belong to the model
 * base class (vtable 0x8008A6C4, ModelVtbl); 0x144 on are entity.h's EntityVtbl.
 */
typedef struct BehaviorEntityVtbl {
    u8 pad_00[0x30];
    void (*postEvent)(void *self, s32 event);                /* 0x30 entity event: 10 link, 11 video end, 12 end */
    u8 pad_34[0x44 - 0x34];
    void (*rotate)(void *self, s32 absolute, void *angles);  /* 0x44 SceneNode_SetRotation: degrees as {num, den} s16 pairs */
    void (*scale)(void *self, s32 absolute, void *factors);  /* 0x48 SceneNode_SetScale: {num, den} s16 pairs */
    u8 pad_4C[0x60 - 0x4C];
    void (*setVisible)(void *self, s32 visible);             /* 0x60 Model_SetVisible, 1 on wake, 0 on sleep */
    u8 pad_64[0xB8 - 0x64];
    void (*setPosition)(void *self, void *pos);              /* 0xB8 Actor_SetPos */
    void (*move)(void *self, void *delta);                   /* 0xBC Actor_MovePos: adds a world vector to the position */
    u8 pad_C0[0xC4 - 0xC0];
    void (*moveZ)(void *self, s32 amount, s32 animate);      /* 0xC4 Actor_MoveZ: along the model's own z axis */
    void (*moveX)();                                         /* 0xC8 Actor_MoveX (self, amount, animate): own x axis */
    void (*moveY)(void *self, s32 amount, s32 animate);      /* 0xCC Actor_MoveY: own y axis, negative is up */
    void (*moveZOnGround)(void *self, s32 amount, s32 animate); /* 0xD0 Actor_MoveZOnGround: moveZ, then the ground test Actor_SnapToGround */
    u8 pad_D4[0xDC - 0xD4];
    void (*onActorTouch)(void *self, void *sender, s32 message); /* 0xDC Entity_OnActorTouch (Actor_OnNode34 in the model class) */
    void (*onWallTouch)(void *self, void *sender, s32 message);  /* 0xE0 Entity_OnWallTouch (Actor_OnNode24 in the model class) */
    u8 pad_E4[0x128 - 0xE4];
    void (*setAnimation)(void *self, s32 animation);         /* 0x128 Model_SetAnimation */
    void (*playAnimation)(void *self);                       /* 0x12C Model_PlayAnimation */
    void (*stopAnimation)(void *self);                       /* 0x130 Model_StopAnimation */
    u8 *(*applyFrame)(void *self, u8 *frame, void *context); /* 0x134 Model_ApplyFrame: runs one frame's commands, returns the next frame */
    u8 pad_138[0x144 - 0x138];
    s32 (*distanceTo)();                                     /* 0x144 Entity_GroundDistance */
    s32 (*getSoundFade)(void *self);                         /* 0x148 Entity_GetSoundFade */
    u8 pad_14C[0x15C - 0x14C];
    void (*wake)(void *self);                                /* 0x15C Entity_Wake */
    void (*sleep)(void *self);                               /* 0x160 Entity_Sleep */
    u8 pad_164[0x168 - 0x164];
    void (*startHandler)(void *self);                        /* 0x168 Entity_StartHandler */
    void (*stopHandler)(void *self);                         /* 0x16C Entity_StopHandler */
} BehaviorEntityVtbl;

/* The object at Entity +0x4C (the map the entity stands on: Actor_SnapToGround asks its slot 0x110 for the ground). */
typedef struct BehaviorMapVtbl {
    u8 pad_00[0x138];
    void (*startTileStretch)(void *self, s32 count, s32 fast); /* 0x138 StageMap_StartTileStretch (stage_map.h) */
} BehaviorMapVtbl;

typedef struct BehaviorMap {
    BehaviorMapVtbl *vt;
} BehaviorMap;

/* A part of a model (one per object of its TMD, made by Actor_New). */
typedef struct ModelPartVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(void *self);                         /* 0x04 */
    u8 pad_08[0x4C - 0x08];
    void (*attach)(void *self, void *parent, s32 child); /* 0x4C SceneNode_Attach */
    u8 pad_50[0x60 - 0x50];
    void (*setVisible)(void *self, s32 visible);         /* 0x60 SceneNode_SetVisible (SpriteNode_SetVisible in the part class) */
    u8 pad_64[0x70 - 0x64];
    void (*setLightFlags)(void *self, s32 flags);        /* 0x70 SceneNode_SetLightFlags */
    u8 pad_74[0x88 - 0x74];
    void (*sendBoxes)(void *self, s32 message);          /* 0x88 Actor_SendBoxes: messages 6, 7, 8 after a move */
} ModelPartVtbl;

typedef struct ModelPart {
    ModelPartVtbl *vt;
    u8 pad_04[0x10 - 0x04];
    s32 flags;              /* 0x10 frame command 0 masks and sets it */
    Coord2 *coord;      /* 0x14 */
    u8 pad_18[0x20 - 0x18];
    s32 texture;            /* 0x20 frame command 2 gives it a texture only while it is 0 */
} ModelPart;

/*
 * The model class, vtable 0x8008A6C4 (Model_GetVtbl), 0x98 bytes (Model_New): a model file
 * split into parts, one animation played frame by frame, a per-tick function, a sound bank and a
 * target it watches. Entity (vtable 0x80089AD4) derives from it. Slots named from the functions
 * stored in the vtable read from the executable.
 */
typedef struct ModelVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(void *self);                          /* 0x04 Object_Delete */
    s32 (*construct)(void *self, s32 source, s32 soundBank); /* 0x08 Model_Construct */
    u8 pad_0C[0x10 - 0x0C];
    void (*watch)(void *self, void *other);                /* 0x10 */
    void (*unwatch)(void *self, void *other);              /* 0x14 */
    u8 pad_18[0x40 - 0x18];
    void (*init)(void *self);                              /* 0x40 Model_Init */
    u8 pad_44[0x98 - 0x44];
    void (*update)(void *self, void *sender, s32 phase);   /* 0x98 Model_Update */
    u8 pad_9C[0xC4 - 0x9C];
    void (*moveZ)(void *self, s32 amount, s32 animate);    /* 0xC4 Actor_MoveZ */
    u8 pad_C8[0xDC - 0xC8];
    void (*onActorTouch)(void *self, void *sender, s32 message); /* 0xDC Actor_OnNode34, Entity_OnActorTouch in the entity class */
    void (*onWallTouch)(void *self, void *sender, s32 message);  /* 0xE0 Actor_OnNode24, Entity_OnWallTouch in the entity class */
    void (*setSpeed)(void *self, s32 speed);               /* 0xE4 Actor_SetSpeed */
    u8 pad_E8[0xF0 - 0xE8];
    void (*setAnim6Flag)(void *self, s32 value);           /* 0xF0 Model_SetAnim6Flag */
    s32 (*load)(void *self, s32 source);                   /* 0xF4 Model_Load */
    void (*unload)(void *self);                            /* 0xF8 Model_Unload */
    u8 pad_FC[0x100 - 0xFC];
    s32 (*createParts)(void *self);                        /* 0x100 Model_CreateParts */
    void (*freeParts)(void *self);                         /* 0x104 Model_FreeParts */
    void (*tickAnimation)(void *self);                     /* 0x108 Model_TickAnimation */
    void (*setTickMode)(void *self, s32 mode);             /* 0x10C Model_SetTickMode: 0x41, 0x42 or 0x43 */
    void (*startTick)(void *self);                         /* 0x110 Model_StartTick */
    void (*stopTick)(void *self);                          /* 0x114 Model_StopTick */
    void (*tickA)(void *self);                             /* 0x118 Model_TickForward */
    void (*tickB)(void *self);                             /* 0x11C empty here, the entity's handler run (Entity_RunHandler) */
    void (*tickC)(void *self);                             /* 0x120 empty */
    u8 pad_124[0x128 - 0x124];
    void (*setAnimation)(void *self, s32 animation);       /* 0x128 Model_SetAnimation */
    u8 pad_12C[0x130 - 0x12C];
    void (*stopAnimation)(void *self);                     /* 0x130 Model_StopAnimation */
    u8 *(*applyFrame)(void *self, u8 *frame, void *context);  /* 0x134 Model_ApplyFrame */
    u8 *(*applyCommand)(void *self, u8 *command, void *context); /* 0x138 Model_ApplyCommand */
    void (*setTarget)(void *self, void *target);           /* 0x13C Model_SetTarget */
    void (*clearTarget)(void *self);                       /* 0x140 Model_ClearTarget */
} ModelVtbl;

/*
 * The entity (entity.h Entity, 0x108 bytes) with the model base class fields the handlers use.
 * Model fields (+0x00 to +0x94): see Model below.
 */
typedef struct BehaviorEntity {
    BehaviorEntityVtbl *vt;
    u8 pad_04[0xC - 0x4];
    s32 attached;              /* 0x0C */
    u8 pad_10[0x14 - 0x10];
    BehaviorPos pos;           /* 0x14 */
    u8 pad_18[0x24 - 0x18];
    u32 timer;                 /* 0x24 */
    s32 contact;                /* 0x28 result of the ground test after moveZOnGround */
    u8 pad_2C[0x44 - 0x2C];
    s32 state;                 /* 0x44 handler state; 1 stops Entity_CheckWake for good */
    s16 speed;                 /* 0x48 last amount given to moveX, moveY or moveZ (Actor_MoveAxis) */
    u8 pad_4A[0x4C - 0x4A];
    BehaviorMap *map;          /* 0x4C */
    void *clock;             /* 0x50 Model.watched, the ticker Fade_StartIn and Fade_StartOut take */
    u8 pad_54[0x6C - 0x54];
    s32 partCount;             /* 0x6C */
    ModelPart **parts;         /* 0x70 */
    u8 pad_74[0x7C - 0x74];
    s32 animation;             /* 0x7C current animation (setAnimation) */
    s32 animLength;            /* 0x80 frames of the current animation */
    s32 animFrame;             /* 0x84 current frame, 0 to animLength - 1 */
    u8 *animData;              /* 0x88 the next frame's commands (applyFrame) */
    s32 tickEnabled;           /* 0x8C */
    s32 animPlaying;           /* 0x90 playAnimation sets it, stopAnimation clears it */
    BehaviorDreamSys *dreamSys; /* 0x94 */
    s32 type;                  /* 0x98 */
    HandlerNode node;          /* 0x9C */
    s32 awake;                 /* 0xF0 */
    s32 touched;               /* 0xF4 */
    s32 handlerActive;         /* 0xF8 */
    s32 handlerTicks;          /* 0xFC */
    Fade *effect;    /* 0x100 */
} BehaviorEntity;
extern EntityRecord g_entityRecords[];
extern void Behavior_MazePenguin();
extern s32 g_scaleHalf;
extern s32 g_scaleSix;
extern s32 g_scaleQuarter;
extern void Behavior_Type71();
extern s32 g_scaleDouble[];
extern s32 g_moveYNeg64[];
typedef struct ModelBaseVtbl {
    u8 pad[0x8];
    s32 (*construct)(void *, s32, s32);                 /* 0x08 Model_Construct */
    void (*destruct)(void *);                           /* 0x0C Model_Destruct */
    u8 pad1[0x4C - 0x10];
    void (*attach)(void *, void *, void *, s32, s32);   /* 0x4C Model_Attach */
    void (*detach)(void *);                             /* 0x50 Model_Detach */
    u8 pad2[0x98 - 0x54];
    void (*update)(void *, void *, s32);                /* 0x98 Model_Update */
    u8 pad3[0xDC - 0x9C];
    void (*onActorTouch)(void *, void *, s32);          /* 0xDC Entity_OnActorTouch */
    void (*onWallTouch)(void *, void *, s32);           /* 0xE0 Entity_OnWallTouch */
} ModelBaseVtbl;
extern s32 g_scaleTiny;
static s32 Entity_IsDreamerNear();
static EntityVtbl *Entity_GetVtbl(void);
static s32 Entity_IsInRange(Entity *entity, u8 *pos, s32 range, s32 param);
extern s16 g_rotY9[];
extern s16 g_rotYNeg9[];
extern s32 g_moveYNeg512[];
extern s32 g_rotY180[];
static s32 Entity_StartEffect();
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
static void Behavior_RollWideOrSlide(BehaviorEntity *entity);

extern s32 g_rotY1;
extern s32 g_scaleTriple;
extern s32 g_effectDefaultPos[];
extern s32 g_effectDefaultSize[];
extern s32 g_rotYNeg90;
extern s32 g_scaleThinTall[];
extern s16 g_scaleSquash[];
extern s32 g_moveYNeg1500Z1024[];
extern s16 g_rotYNegHalf[];
static void Behavior_TrainRun(BehaviorEntity *entity, HandlerNode *node, s32 turnTick, s32 leaveTick, s32 speed);
extern s32 g_moveYNeg4096[];
extern s32 g_moveY64[];
extern s32 g_moveXNeg64[];
static void Entity_CheckLinkRadius();
static s32 Entity_IsInRange(Entity *entity, u8 *pos, s32 range, s32 param);
extern u8 g_entityVtbl[];
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
static s32 Entity_StartEffect(Entity *entity, void *size, void *pos, s32 step, s32 priority);
static void Behavior_QueueLowSound7(HandlerNode *node);
extern s32 g_rotZNeg90[];
extern s32 g_rotX90;
s32 g_type78Stopped;
extern s32 g_scaleGrowStep[];

s32 Entity_Create(s32 type, s32 params, s32 soundBank) {
    s32 mem;

    mem = Heap_Alloc(0x108);
    if (mem == 0) {
        return 0;
    }
    if (Entity_GetVtbl()->construct(mem, type, params, soundBank) != 0) {
        return mem;
    }
    Heap_Free(mem);
    return 0;
}

void *Entity_Construct(Entity *entity, s32 type, s32 source, s32 soundBank) {
    if (Model_GetVtbl()->construct(entity, source, soundBank) != 0) {
        entity->vt = Entity_GetVtbl();
        entity->type = type;
        entity->handlerNode.id = 0;
        entity->effect = 0;
        entity->secondEffect = 0;
        ((EntityVtbl *)entity->vt)->init(entity);
        return entity;
    }
    return NULL;
}

static s32 Entity_StartEffect(Entity *entity, void *size, void *pos, s32 step, s32 priority) {
    Fade *effect;

    if (entity->effect == NULL) {
        if (size == NULL) {
            size = g_effectDefaultSize;
        }
        effect = Fade_Create(size, 0, priority);
        if (effect == NULL) {
            return 0;
        }
        entity->effect = effect;
    } else {
        effect = entity->effect;
    }
    effect->vtbl->hide(effect);
    effect->vtbl->show(effect, entity, pos ? pos : g_effectDefaultPos);
    effect->vtbl->setStep(effect, step);
    return (s32)effect;
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
    Model_GetVtbl()->destruct(entity);
}

void Entity_Init(Entity *entity) {
    /* record points byte (+2) of 1 to 9 */
    if ((u8)g_entityRecords[entity->type].points - 1U < 9) {
        entity->vt->setLightFlags(entity, 1);
    }
    entity->vt->setTickMode(entity, 0x42);
    entity->vt->sleep(entity);
}

void Entity_Attach(Entity *entity, void *dreamSys, void *watched, s32 map, s32 placement) {
    if (entity->attached == 0) {
        Model_GetVtbl()->attach(entity, dreamSys, watched, map, placement);
        entity->map = map;
        /* record +3 wake mode 0: awake at spawn; +0xB handler range 0: handler from the start */
        if (g_entityRecords[entity->type].wakeMode == 0) {
            entity->vt->wake(entity);
            if (g_entityRecords[entity->type].handlerRange == 0) {
                entity->vt->startHandler(entity);
            }
        }
    }
}

void Entity_Detach(Entity *entity) {
    if (entity->attached != 0) {
        entity->vt->sleep(entity);
        Model_GetVtbl()->detach(entity);
        entity->map = 0;
    }
}

void Entity_Update(Entity *entity, void *sender, s32 phase) {
    if (entity->vt->checkWake(entity) != 0) {
        entity->vt->checkSleep(entity);
    }
    if (entity->vt->checkHandlerStart(entity) != 0) {
        entity->vt->checkHandlerStop(entity);
    }
    entity->vt->checkTouch(entity);
    ((ModelVtbl *)Model_GetVtbl())->update(entity, sender, phase);
}

void Entity_OnActorTouch(Entity *entity, void *sender, s32 message) {
    s32 link;

    /* record +7 link */
    link = g_entityRecords[entity->type].link;
    if (message < 2 || message >= 9 || link > 0) {
        ((ModelVtbl *)Model_GetVtbl())->onActorTouch(entity, sender, message);
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
            entity->vt->postEvent(entity, message);
        }
    }
}

void Entity_OnWallTouch(Entity *entity, void *sender, s32 message) {
    Model_GetVtbl()->onWallTouch(entity, sender, message);
    if (message == 4) {
        entity->vt->sleep(entity);
    }
}

void Entity_RunHandler(Entity *entity) {
    HandlerNode_Run(entity->soundBank, &entity->handlerNode);
    entity->handlerTicks++;
}

/* Is pos within range << 11 of the dreamer; the record's points byte (+2), when -9 to -1, raises the tested height by points * 1024. */
static s32 Entity_IsInRange(Entity *entity, u8 *pos, s32 range, s32 param) {
    Vec3 point;
    u8 points;

    point = *(Vec3 *)pos;
    points = *(u8 *)&g_entityRecords[entity->type].points;
    if ((u32)((points + 9) & 0xFF) < 9U) {
        point.y += (s32)(points << 0x18) >> 0xE;
    }
    if (param < 0) {
        param = 0x800 / (s32)(~param + 1);
    } else {
        param = param << 0xB;
    }
    return entity->dreamSys->vt->testPointAhead(entity->dreamSys, 0, range << 0xB, &point, param);
}

/* Ground distance |dx| + |dz| from this entity to the position copy of other. */
s32 Entity_GroundDistance(Entity *entity, Entity *other) {
    Vec3 *otherPos;
    Coord2 *block;
    s32 dz;
    s32 dx;
    s32 dist;

    otherPos = NULL;
    if (other->attached != 0) {
        otherPos = (Vec3 *)(other->pos.bytes + 0x38);
    }
    block = entity->pos.coord;
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
        dist = entity->vt->distanceTo(entity, entity->dreamSys);
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
    entity->vt->setVisible(entity, 1);
    entity->awake = 1;
    entity->timer = 0;
}

void Entity_Sleep(Entity *entity) {
    entity->vt->setVisible(entity, 0);
    entity->vt->stopHandler(entity);
    entity->vt->setTouched(entity, 0);
    entity->awake = 0;
}

void Entity_SetTouched(Entity *entity, s32 touched) {
    if (touched != 0) {
        entity->vt->postEvent(entity, 9);
    }
    entity->touched = touched;
}

void Entity_StartHandler(Entity *entity) {
    /* register the record's handler (+0xC) */
    HandlerNode_Start(entity->soundBank, &entity->handlerNode, entity->type + 1, entity, g_entityRecords[entity->type].handler);
    entity->vt->playAnimation(entity);
    entity->vt->startTick(entity);
    entity->handlerTicks = 0;
    entity->handlerActive = 1;
}

void Entity_StopHandler(Entity *entity) {
    HandlerNode_Stop(entity->soundBank, &entity->handlerNode);
    entity->vt->stopAnimation(entity);
    entity->vt->stopTick(entity);
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
        if (Entity_IsInRange(entity, entity->pos.bytes + 0x18, record->wakeRange, record->boxSize) != 0) {
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
            entity->vt->wake(entity);
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
                sleep = entity->timer == (u32)(mode * 15);
            } else if (record->wakeRange != 0) {
                inRange = Entity_IsInRange(entity, entity->pos.bytes + 0x18, record->wakeRange, record->boxSize);
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
            entity->vt->sleep(entity);
        }
    }
    return entity->awake;
}

s32 Entity_CheckTouch(Entity *entity) {
    s32 range;
    u8 *pos;
    EntityRecord *record;

    record = &g_entityRecords[entity->type];
    if (entity->awake != 0) {
        if (entity->touched == 0) {
            pos = entity->pos.bytes + 0x18;
            range = record->touchRange;
            if (range < 0) {
                range = ~range + 1;
            }
            if (Entity_IsInRange(entity, pos, range, record->boxSize) != 0) {
                entity->vt->setTouched(entity, 1);
            }
        }
        if (record->touchRange < 0) {
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        }
    }
    return entity->touched;
}

s32 Entity_CheckHandlerStart(Entity *entity) {
    EntityRecord *record;
    s32 range;
    u8 *pos;

    if (entity->awake != 0) {
        if (entity->handlerActive == 0) {
            if (entity->state != 1) {
                record = &g_entityRecords[entity->type];
                range = record->handlerRange;
                if (range != 0) {
                    pos = entity->pos.bytes + 0x18;
                    if (range < 0) {
                        range = ~range + 1;
                    }
                    if (Entity_IsInRange(entity, pos, range, record->boxSize) != 0) {
                        entity->vt->startHandler(entity);
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
            entity->vt->postEvent(entity, 0xA);
        }
    }
}

/* The dreamer is within 0x200 in height and closer than radius on the ground. */
static s32 Entity_IsDreamerNear(Entity *entity, s32 radius) {
    Entity *other;
    s32 y;
    s32 my;

    other = entity->dreamSys;
    y = other->pos.coord->coord.t.y;
    my = entity->pos.coord->coord.t.y;
    if (y + 0x200 >= my && my >= y - 0x200 && entity->vt->distanceTo(entity, other, y) < radius) {
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
            if ((range < 0) && (Entity_IsInRange(entity, entity->pos.bytes + 0x18, ~range + 1, record->boxSize) == 0)) {
                entity->vt->stopHandler(entity);
            }
        }
    }
    return entity->handlerActive;
}

static EntityVtbl *Entity_GetVtbl(void) {
    return (EntityVtbl *)g_entityVtbl;
}

void Behavior_Astronaut(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;

    if (node->tick == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) == 5) {
            entity->state = 0x64;
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
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
            entity->vt->moveZ(entity, 0x32, 0);
        } else {
            entity->vt->moveZ(entity, -0x32, 0);
        }
        return;
    }
    if (entity->handlerTicks < 0xFA) {
        if (node->tick % 10 == 0) {
            node->voices[0].sound = 5;
            node->voices[0].octave = -2;
        }
        if (entity->handlerTicks < 0x64) {
            entity->vt->moveZ(entity, 0x32, 0);
        } else if (entity->handlerTicks < 0xFA) {
            entity->vt->move(entity, g_moveY64ZNeg64);
        }
    } else {
        if (entity->handlerTicks == 0xFA) {
            entity->vt->stopAnimation(entity);
            node->voices[0].sound = -2;
            return;
        }
        if (entity->handlerTicks >= 0x105 && entity->handlerTicks < 0x238) {
            entity->vt->moveZ(entity, -0x32, 0);
            entity->vt->rotate(entity, 1, g_rotYNeg120);
            return;
        }
        if (entity->handlerTicks >= 0x239) {
            entity->vt->rotate(entity, 1, g_astronautBarPose);
        }
    }
}

void Behavior_Type1(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = 0;
    if (node->tick == 0) {
        node->voices[0].sound = 0x14;
        node->voices[1].sound = 0x14;
        node->voices[2].sound = 0x14;
        entity->dreamSys->vt->stopControls(entity->dreamSys, 1);
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    entity->vt->moveZ(entity, -0x5A, 0);
    if (entity->handlerTicks == 0x1E) {
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type5(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0x17;
    }
}

void Behavior_Type7(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
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
        entity->vt->rotate(entity, 0, g_rotY2);
        entity->vt->moveZ(entity, -0x140, 0);
        return;
    }
    if (entity->handlerTicks >= 0x38 || Entity_IsInRange(entity, entity->pos.bytes + 0x18, 1, 1) != 0) {
        entity->vt->move(entity, g_moveYNeg64);
        return;
    }
    if (entity->handlerTicks >= 0xA) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        entity->vt->moveZ(entity, -0x100, 0);
        return;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_PurpleBeast(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, g_scaleDouble);
    entity->vt->move(entity, g_moveYNeg64);
}

void Behavior_Type9(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type10(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = 0;
    if (node->tick == 0) {
        node->voices[0].sound = 0xB;
        node->voices[1].sound = 0xB;
        node->voices[2].sound = 0xB;
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_WalkingGeisha(BehaviorEntity *entity, HandlerNode *node) {
    void *turn;
    BehaviorDreamSys *dreamSys;

    entity->speed = -0x14;
    node->fade = entity->vt->getSoundFade(entity);
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
            if (dreamSys->vt->wasCirclePressed(dreamSys) != 0) {
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
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        entity->vt->scale(entity, 1, &g_scaleHalf);
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->vt->postEvent(entity, 0xB);
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
        entity->vt->rotate(entity, 0, turn);
    }
    entity->vt->moveZOnGround(entity, entity->speed, 0);
    if (entity->state != 0xC && entity->contact != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type12(BehaviorEntity *entity) {

    if (entity->handlerTicks == 0 && !(rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->pos.coord->coord.t.y < 0x7D0) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    }
    if (entity->state == 11) {
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0xA00) {
            entity->map->vt->startTileStretch(entity->map, 1, 1);
            entity->handlerTicks = 1;
            entity->state = 0xC;
        }
    } else if (entity->state == 12) {
        if (entity->handlerTicks++ == 300) {
            entity->vt->postEvent(entity, 0xC);
        }
    }
}

void Behavior_Type13(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0xC;
        entity->state = entity->state + 1;
    } else if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
    if (entity->state == 0x24) {
        if (rand() % 3 == 0) {
            entity->vt->postEvent(entity, 0xB);
        }
    }
}

void Behavior_Type14(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animFrame == 0xA) {
        node->voices[0].sound = 0xD;
    }
    entity->vt->moveZ(entity, -0xA, 0);
}

void Behavior_Type15(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        node->fade = 0;
        node->voices[0].sound = 0xF;
    }
}

void Behavior_Type16(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->state == 0) {
        if (entity->handlerTicks < 0x40) {
            entity->vt->moveZ(entity, -0x5A, 0);
            return;
        }
        if (entity->handlerTicks == 0x40) {
            entity->vt->rotate(entity, 0, (rand() & 1) ? &g_rotY90 : &g_rotYNeg90);
            entity->vt->move(entity, g_moveY256);
            return;
        }
        entity->vt->moveZOnGround(entity, -0x176, rand() % 2);
        return;
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks % 5 == 0) {
            entity->vt->rotate(entity, 0, &g_rotY90);
        }
        entity->vt->moveZ(entity, -0x800, 0);
        entity->vt->setVisible(entity, (rand() % 7) == 0);
    }
}

void Behavior_Type17(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleHalf);
}

void Behavior_Type19(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == (node->tick / 10) * 10) {
        node->voices[0].sound = 0x11;
    }
    entity->vt->moveZ(entity, -0x100, 0);
}

void Behavior_Type20(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        if (rand() % 7 == 0) {
            entity->vt->scale(entity, 1, &g_scaleTallTwo);
        }
    }
    if (!(node->tick & 3)) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0x1C;
    }
    entity->vt->moveZ(entity, -0x64, 0);
}

void Behavior_MinotaurRickshaw(BehaviorEntity *entity, HandlerNode *node) {
    s32 phase;

    node->fade = entity->vt->getSoundFade(entity);
    phase = node->tick % (entity->animLength / 2);
    if (phase == 0) {
        node->voices[0].sound = 0xA;
    } else if (phase == 3) {
        node->voices[1].sound = 0xD;
    }
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type22(BehaviorEntity *entity) {
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type23(BehaviorEntity *entity) {
    BehaviorEntityVtbl *vt;
    s32 ticks;
    s32 speed;

    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    if (entity->touched != 0) {
        if (entity->handlerTicks >= 0x41) {
            entity->handlerTicks = 0;
        }
        if (entity->handlerTicks >= 7) {
            entity->vt->move(entity, g_moveYNeg64);
            entity->vt->moveZ(entity, 0xA, 0);
        } else {
            entity->vt->move(entity, g_moveXNeg64);
        }
        return;
    }
    ticks = entity->handlerTicks;
    if (ticks == 0) {
        entity->vt->move(entity, g_moveYNeg4096);
    } else if (ticks < 0x41) {
        entity->vt->move(entity, g_moveY64);
    } else if (ticks < 0x47) {
        entity->vt->move(entity, g_moveYNeg64);
        entity->vt->moveZ(entity, -0x1E, 0);
    } else {
        vt = entity->vt;
        if (ticks < 0x100) {
            speed = -ticks - 0x41;
        } else {
            speed = 0xFF;
        }
        vt->moveZ(entity, speed, 0);
    }
}

void Behavior_Type24(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % 15 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
    }
    entity->vt->scale(entity, 1, g_scaleDouble);
    entity->vt->rotate(entity, 0, g_rotY2);
    entity->vt->moveZ(entity, -0x200, 0);
}

void Behavior_Type25(BehaviorEntity *entity, HandlerNode *node) {
    s32 ticks;

    node->fade = 0;
    ticks = entity->handlerTicks;
    if (ticks < 0x64) {
        if (node->tick % 3 == 0) {
            node->voices[0].sound = 0x16;
            node->voices[0].octave = 1;
        }
        entity->vt->moveY(entity, -0x40, 0);
    } else if (ticks < 0x12C) {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
        node->voices[1].sound = 0xC;
        node->voices[1].octave = -1;
        node->voices[2].sound = 0xC;
        node->voices[2].octave = -1;
        entity->vt->moveY(entity, -0x100, 0);
    } else {
        entity->vt->rotate(entity, 0, g_rotXEighth);
        entity->vt->moveY(entity, -0x200, 0);
    }
}

void Behavior_Type26(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % entity->animLength == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0x1A;
    }
    entity->vt->moveZOnGround(entity, (entity->handlerTicks == 0x6E) ? -0x2D00 : -0x180, 0);
}

void Behavior_Type27(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % 70 == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x1B;
    }
    entity->vt->moveZ(entity, -0x80, 0);
    if (entity->handlerTicks < 0x64) {
        entity->vt->moveY(entity, 0x20, 0);
    } else if (entity->handlerTicks > 300) {
        entity->vt->moveY(entity, -0x20, 0);
    }
}

void Behavior_Type119(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type29(BehaviorEntity *entity) {
    BehaviorDreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) == 7) {
            entity->vt->scale(entity, 1, &g_scaleTriple);
            entity->vt->moveY(entity, -0x7800, 0);
        }
        entity->state = rand() % 5;
    }
    if (entity->state == 0) {
        entity->vt->rotate(entity, 0, &g_rotY1);
    }
}

void Behavior_Type30(BehaviorEntity *entity) {
    BehaviorDreamSys *dreamSys;
    s32 state;

    if (entity->state == 0) {
        dreamSys = entity->dreamSys;
        state = dreamSys->vt->getDreamColor(dreamSys);
        if (state == 1) {
            state = 0xB;
        } else {
            state = 0xC;
        }
        entity->state = state;
    }
    if (entity->state == 0xC) {
        entity->vt->scale(entity, 1, g_scaleDouble);
        entity->vt->moveY(entity, -0x1E, 0);
        return;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    if (entity->state == 0xB) {
        entity->vt->moveZ(entity, -0x64, 0);
        if ((u32)(entity->handlerTicks - 0x55) < 0x1E) {
            entity->vt->moveY(entity, 0x50, 0);
            return;
        }
        if (entity->handlerTicks == 0x78) {
            entity->state = 0xD;
        }
        return;
    }
    if (entity->state == 0xD) {
        entity->vt->setPosition(entity, entity->dreamSys->pos.bytes + 0x18);
        entity->vt->move(entity, g_moveYNeg1500Z1024);
    }
}

void Behavior_Type31(BehaviorEntity *entity, HandlerNode *node) {
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    entity->dreamSys->vt->stopControls(entity->dreamSys, 1);
    if ((node->tick % 10) < 3) {
        node->fade = 0;
        node->voices[0].sound = 0xD;
        node->voices[1].sound = 0xD;
        node->voices[2].sound = 0xD;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->stopAnimation(entity);
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type32(BehaviorEntity *entity) {
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type33(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->touched != 0) {
        entity->vt->scale(entity, 1, &g_scaleQuarter);
    } else if (node->tick % 30 == 0) {
        node->fade = 0;
        node->voices[0].sound = 3;
    }
    entity->vt->moveZOnGround(entity, -0x1E, 0);
    if (entity->contact != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type34(BehaviorEntity *entity) {
    s32 ticks;

    ticks = entity->handlerTicks;
    if (ticks >= 0x190 && ticks < 0x19A) {
        entity->vt->rotate(entity, 0, g_rotY9);
    } else if ((ticks >= 0x2BC && ticks < 0x2C6) || (ticks >= 0x33E && ticks < 0x342)) {
        entity->vt->rotate(entity, 0, g_rotYNeg9);
    } else if (ticks >= 0x353) {
        entity->vt->sleep(entity);
    }
    entity->vt->moveZ(entity, (entity->handlerTicks < 0x320) ? -0x3C : -0x200, 1);
}

void Behavior_Type35(BehaviorEntity *entity) {
    s32 phase;

    phase = entity->handlerTicks % 500;
    entity->vt->moveY(entity, (entity->handlerTicks % 6 < 3) ? -0x40 : 0x40, 0);
    entity->vt->moveX(entity, (entity->handlerTicks % 12 < 6) ? -0x40 : 0x40, 0);
    entity->vt->moveZ(entity, (entity->handlerTicks % 64 < 0x20) ? -0x80 : 0x80, 0);
    if (phase < 0x20) {
        entity->vt->move(entity, g_moveYNeg64);
    } else if (phase < 0x40) {
        entity->vt->move(entity, g_moveY64);
    }
}

void Behavior_Type36(BehaviorEntity *entity) {
    if (entity->state == 0) {
        entity->vt->scale(entity, 1, (rand() & 1) ? g_scaleDouble : &g_scaleSix);
        entity->state = 0xB;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x7000) {
        entity->vt->moveZ(entity, 0x100, 0);
    }
}

void Behavior_Type37(BehaviorEntity *entity) {
    entity->vt->moveY(entity, -0x5A, 0);
}

void Behavior_OperaSinger(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % 120 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 1;
    }
}

void Behavior_Mushroom(BehaviorEntity *entity, HandlerNode *node) {
    s32 dayRest;
    void (*animFn)(void *);

    if (entity->handlerTicks == 0) {
        dayRest = entity->dreamSys->vt->getDayNumber(entity->dreamSys, 0) % 3;
        if (dayRest == 0) {
            if (rand() % 3 == 0) {
                entity->vt->scale(entity, 1, g_scaleTallFour);
            }
        } else if (dayRest == 2) {
            entity->vt->scale(entity, 1, g_scaleTallFour);
        }
    }
    if (node->tick == (node->tick / 22) * 22) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 2;
    }
    if (rand() % 12 == 0) {
        animFn = entity->vt->stopAnimation;
    } else if (rand() % 6 == 0) {
        animFn = entity->vt->playAnimation;
    } else {
        return;
    }
    animFn(entity);
}

void Behavior_Type40(BehaviorEntity *entity, HandlerNode *node) {
    void *turn = 0;

    if (node->tick % 7 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
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
        entity->vt->rotate(entity, 0, turn);
    }
    entity->vt->moveZOnGround(entity, -0x1E, 0);
    if (entity->contact != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type41(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        entity->state = rand() % 5 + 0xA;
    }
    if (entity->state < 0xE || entity->handlerTicks < 0x140) {
        Behavior_TrainRun(entity, node, 0xBB8, 0x1F4, -0x100);
        return;
    }
    if (entity->state == 0xE && !(entity->handlerTicks & 3)) {
        g_type41Scale[5] = rand() % 32 + 1;
        entity->vt->scale(entity, 1, g_type41Scale);
    }
}

void Behavior_Type42(BehaviorEntity *entity, HandlerNode *node) {
    s32 sound;

    if (entity->handlerTicks < 0x14) {
        entity->vt->stopAnimation(entity);
        entity->vt->moveZ(entity, -0x1E, 0);
        return;
    }
    if (entity->handlerTicks == 0x14) {
        entity->vt->playAnimation(entity);
        sound = 5;
        node->fade = 0;
    } else {
        if (entity->handlerTicks % (entity->animLength * 3 + 0x14) != 0) {
            return;
        }
        entity->vt->stopAnimation(entity);
        sound = -2;
    }
    node->voices[0].sound = sound;
}

void Behavior_Type43(BehaviorEntity *entity, HandlerNode *node) {
    s16 *angles;
    s32 amount;

    Behavior_RollWideOrSlide(entity);
    node->fade = entity->vt->getSoundFade(entity);
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
        entity->vt->moveX(entity, amount, 0);
        if (rand() & 3) {
            angles = g_rotYNeg9;
        } else {
            angles = g_rotY9;
        }
        entity->vt->rotate(entity, 0, angles);
    }
}

void Behavior_Type44(BehaviorEntity *entity, HandlerNode *node) {
    s16 *angles;
    s32 amount;

    Behavior_RollWideOrSlide(entity);
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animFrame == 7 || entity->animFrame == 0x16) {
        node->voices[0].sound = 3;
    }
    if ((u32)(entity->handlerTicks - 0x12C) < 0x14) {
        entity->vt->moveZ(entity, -0x3C, 0);
    } else if ((u32)(entity->handlerTicks - 0x141) < 0x13) {
        entity->vt->rotate(entity, 0, g_rotYNeg9);
    } else if (entity->handlerTicks >= 0x141) {
        if (rand() & 1) {
            amount = 0x80;
        } else {
            amount = -0x80;
        }
        entity->vt->moveX(entity, amount, 1);
        if (rand() & 3) {
            angles = g_rotYNeg9;
        } else {
            angles = g_rotY9;
        }
        entity->vt->rotate(entity, 0, angles);
    }
}

static void Behavior_RollWideOrSlide(BehaviorEntity *entity) {
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand() % 10;
        if (roll >= 8) {
            entity->vt->scale(entity, 1, g_scaleWideThree);
        } else if (roll >= 5) {
            entity->state = 0xA;
        }
    }
    if (entity->state == 0xA && entity->handlerTicks >= 0xC9) {
        entity->vt->move(entity, g_moveZNeg256);
    }
}

void Behavior_Type45(void) {
}

void Behavior_Flower(BehaviorEntity *entity, HandlerNode *node) {
    s32 dayRest;
    s32 roll;

    if (entity->handlerTicks == 0) {
        dayRest = entity->dreamSys->vt->getDayNumber(entity->dreamSys, 0) % 3;
        if (dayRest == 0) {
            roll = rand();
            if (roll % 3 == 0) {
                entity->vt->scale(entity, 1, &g_scaleSix);
            }
        } else if (dayRest == 1) {
            entity->vt->scale(entity, 1, &g_scaleSix);
        }
    }
    if (node->tick == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x12;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type47(BehaviorEntity *entity) {
    if (entity->touched != 0) {
        if (entity->state == 0) {
            entity->state = 0xC;
            entity->handlerTicks = 0;
            return;
        } else if (entity->state == 0xC) {
            if (entity->handlerTicks < 0x1E) {
                if (entity->dreamSys->vt->wasCirclePressed(entity->dreamSys) != 0) {
                    entity->dreamSys->vt->stopControls(entity->dreamSys, 0);
                    entity->handlerTicks = 0;
                    entity->state = 0xB;
                    return;
                }
            } else {
                entity->vt->postEvent(entity, 0xB);
                entity->state = 0xA;
                return;
            }
        } else if (entity->state == 0xB) {
            if (entity->handlerTicks == 0x64) {
                entity->vt->postEvent(entity, 0xC);
                return;
            }
            entity->dreamSys->vt->moveY(entity->dreamSys, -0x64, 0);
        }
    }
}

void Behavior_FloatingLips(BehaviorEntity *entity, HandlerNode *node) {
    s32 amount;
    BehaviorEntityVtbl *vt;

    if (entity->animFrame == 0x26) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 6;
    }
    amount = 0x1E;
    vt = entity->vt;
    if ((entity->handlerTicks % 10) < 5) {
        amount = -0x1E;
    }
    vt->moveY(entity, amount, 0);
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type49(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSysVtbl *dreamSysVtbl;
    s32 state;
    s32 standPos;

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
                entity->vt->postEvent(entity, 0xA);
            } else if (entity->dreamSys->vt->wasCirclePressed(entity->dreamSys) != 0) {
                dreamSysVtbl = entity->dreamSys->vt;
                if (entity->attached != 0) {
                    standPos = entity->pos.bytes + 0x38;
                } else {
                    standPos = 0;
                }
                dreamSysVtbl->setPosition(entity->dreamSys, standPos);
                entity->dreamSys->vt->rotate(entity->dreamSys, 1, &g_rotYNeg90);
                entity->dreamSys->vt->stopControls(entity->dreamSys, 0);
                entity->handlerTicks = 0;
                entity->state = 0xB;
            }
        } else if (state == 0xB) {
            dreamSysVtbl = entity->dreamSys->vt;
            dreamSysVtbl->setPosition(entity->dreamSys, entity->attached ? entity->pos.bytes + 0x38 : 0);
            if (entity->handlerTicks == 0x64) {
                entity->vt->postEvent(entity, 0xA);
            }
        }
    }
    entity->vt->moveZ(entity, -0x100, 0);
}

void Behavior_Type50(BehaviorEntity *entity, HandlerNode *node) {
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
        entity->vt->sleep(entity);
        entity->state = 1;
    }
}

void Behavior_MazePenguin(BehaviorEntity *entity, HandlerNode *node) {
    void *turn;
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if ((roll == ((roll / 5) * 5)) && (entity->state == 0)) {
            entity->vt->scale(entity, 1, &g_scaleSix);
            entity->vt->moveY(entity, 0x320, 0);
            entity->state = 0xB;
        }
    }
    turn = NULL;
    if (node->tick == ((node->tick / 5) * 5)) {
        node->fade = entity->vt->getSoundFade(entity);
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
        entity->vt->rotate(entity, 0, turn);
    }
    entity->vt->moveZ(entity, -0x50, 1);
}

void Behavior_Type52(BehaviorEntity *entity, HandlerNode *node) {
    s32 ticks;

    node->fade = entity->vt->getSoundFade(entity);
    ticks = entity->handlerTicks;
    if (ticks < 0xBC) {
        if (ticks == 0x54) {
            entity->vt->rotate(entity, 0, g_rotY180);
        }
        if (node->tick % 20 == 0) {
            node->voices[0].sound = 9;
        }
    } else if (ticks < 0xC8) {
        entity->vt->rotate(entity, 0, g_rotY9);
    } else {
        entity->vt->sleep(entity);
        node->voices[1].sound = 0x1E;
        entity->state = 1;
    }
    entity->vt->moveZOnGround(entity, -0x200, 0);
}

void Behavior_Type55(BehaviorEntity *entity, HandlerNode *node) {
    s32 frame;

    frame = entity->animFrame;
    if (entity->handlerTicks == 0) {
        if (rand() % 3 == 0) {
            entity->vt->scale(entity, 1, &g_scaleTallTwo);
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
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

void Behavior_Type56(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type57(BehaviorEntity *entity, HandlerNode *node) {
    Fade *effect;
    s32 frame;

    if (entity->handlerTicks == 0) {
        entity->state = rand() % 3;
        if (entity->state == 0) {
            entity->vt->stopAnimation(entity);
            entity->vt->moveY(entity, 0x1800, 0);
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
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
            if (Entity_IsInRange(entity, entity->pos.bytes + 0x18, 0xF, 0xA) != 0) {
                if (Entity_StartEffect((Entity *)entity, 0, 0, 0xA, 0) != 0) {
                    effect = entity->effect;
                    effect->vtbl->startIn(effect, entity->clock, 4, 0);
                }
                if (rand() & 1) {
                    entity->vt->postEvent(entity, 0xB);
                    return;
                }
            }
        } else if (frame == 0x3B) {
            entity->vt->sleep(entity);
            entity->state = 1;
        }
    } else {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
        entity->vt->moveZ(entity, -0x200, 0);
        if (entity->handlerTicks >= 0x80 && entity->handlerTicks < 0x142) {
            entity->vt->moveY(entity, -0x80, 0);
            return;
        }
        if (entity->handlerTicks == 0x142) {
            entity->vt->playAnimation(entity);
            entity->state = 1;
        }
    }
}

void Behavior_Type58(BehaviorEntity *entity, HandlerNode *node) {
    s32 liftedTicks;
    s32 fallenTicks;
    BehaviorDreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        node->fade = 0;
        node->voices[0].sound = 0xC;
        if (entity->dreamSys->vt->getDreamColor(entity->dreamSys) == 6) {
            entity->state = 0xB;
        } else if (rand() % 3 == 0) {
            entity->state = 0xC;
        }
    }
    if (node->tick % 100 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
    }
    if (entity->state == 0xB) {
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->dreamSys->vt->stopControls(entity->dreamSys, 0);
            entity->state = 0xD;
            entity->handlerTicks = 0;
        }
    } else if (entity->state == 0xC) {
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->vt->stopAnimation(entity);
            entity->state = 0xE;
            entity->handlerTicks = 0;
        }
    }
    if (entity->state == 0xD) {
        liftedTicks = entity->handlerTicks;
        if (liftedTicks < 0x32) {
            entity->dreamSys->vt->moveY(entity->dreamSys, -0x14, 0);
        } else if (liftedTicks < 0x1F4) {
            dreamSys = entity->dreamSys;
            dreamSys->vt->moveX(dreamSys, liftedTicks % 40 < 0x14 ? -5 : 5, 0);
        } else if (liftedTicks == 0x1F4) {
            entity->vt->postEvent(entity, 0xC);
        }
    }
    if (entity->state == 0xE) {
        fallenTicks = entity->handlerTicks;
        if (fallenTicks < 0xA) {
            entity->vt->moveY(entity, 0xC8, 0);
            return;
        }
        if (fallenTicks == 0xA) {
            node->voices[0].sound = 0x12;
            node->fade = 0;
            node->voices[1].sound = 3;
            entity->vt->rotate(entity, 1, g_rotZNeg90);
            entity->vt->moveX(entity, 0x960, 0);
            entity->vt->moveY(entity, 0x5DC, 0);
            entity->parts[1]->vt->setVisible(entity->parts[1], 0);
            entity->state = 1;
        }
    }
}

void Behavior_Type115(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    s32 ticks;

    if (entity->state == 0 && Entity_IsDreamerNear((Entity *)entity, 0x800) != 0) {
        entity->state = 0xB;
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        Entity_FaceDreamer(entity->dreamSys, entity, 1, 1, 0);
        entity->vt->wake(entity);
        entity->vt->startHandler(entity);
        dreamSys = entity->dreamSys;
        dreamSys->vt->stopControls(dreamSys, 1);
        node->fade = 0;
        node->voices[0].sound = 0xC;
        entity->handlerTicks = 0;
    }
    if (entity->state == 0) {
        entity->vt->sleep(entity);
        entity->vt->stopHandler(entity);
    } else {
        if (node->tick % 100 == 0) {
            node->fade = entity->vt->getSoundFade(entity);
            node->voices[0].sound = 0xC;
            node->voices[0].octave = -1;
        }
        ticks = entity->handlerTicks;
        if (ticks < 3) {
            entity->vt->moveY(entity, 0x96, 0);
        } else if (ticks < 7) {
            entity->vt->moveY(entity, (ticks & 1) ? -0x32 : 0x32, 0);
        } else if (ticks == 0x64) {
            if (rand() & 1) {
                entity->state = 0xC;
                entity->vt->stopAnimation(entity);
            }
        } else if (ticks == 0xF0) {
            dreamSys = entity->dreamSys;
            dreamSys->vt->setControls(dreamSys, 1, 1);
        }
        if (entity->state == 0xC) {
            ticks = entity->handlerTicks;
            if (ticks < 0x82) {
                entity->vt->moveY(entity, 0xA, 0);
            } else if (ticks < 0xA0) {
                entity->vt->moveZ(entity, -0x1E, 0);
            } else if (ticks >= 0x12D) {
                Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
                entity->vt->moveZ(entity, -0x1E, 0);
            }
        }
    }
    if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x200) {
        entity->vt->sleep(entity);
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type59(BehaviorEntity *entity, HandlerNode *node) {
    s32 roll;
    BehaviorMap *map;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if (roll == ((roll / 10) * 10)) {
            entity->state = 0xC;
        }
    }
    if (node->tick == ((node->tick / 10) * 10)) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
    }
    if (entity->handlerTicks == 0) {
        if (rand() & 1) {
            entity->vt->moveY(entity, 0x800, 0);
        }
    }
    entity->vt->moveZ(entity, -0x80, 0);
    if ((entity->state == 0xC) && (entity->handlerTicks == 0x12C)) {
        map = entity->map;
        map->vt->startTileStretch(map, 1, 1);
    }
}

void Behavior_Type61(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->animFrame == 0x1E) {
        node->voices[0].sound = 0x12;
        node->fade = 0;
        node->voices[0].octave = -1;
    }
}

void Behavior_Type62(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    BehaviorMap *map;
    s32 state;

    if (entity->animFrame % 30 == 0) {
        node->voices[0].sound = 3;
        node->fade = 0;
        node->voices[0].octave = -2;
    }
    if (entity->handlerTicks >= 0x65) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    }
    entity->vt->moveZ(entity, -5, 0);
    if (entity->handlerTicks == 0x12C && entity->vt->distanceTo(entity, entity->dreamSys) < 0x1000) {
        dreamSys = entity->dreamSys;
        dreamSys->vt->stopControls(dreamSys, 0);
    } else if (entity->handlerTicks == 0x1F4) {
        dreamSys = entity->dreamSys;
        dreamSys->vt->setControls(dreamSys, 1, 1);
    }
    if (entity->state == 0 && entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
        if (rand() & 1) {
            node->voices[1].sound = 6;
            node->fade = 0;
            node->voices[1].octave = -1;
            if (rand() & 1) {
                map = entity->map;
                map->vt->startTileStretch(map, -1, 0);
            }
            state = 0xA;
            entity->handlerTicks = 0;
        } else {
            state = 0xB;
        }
        entity->state = state;
    }
    if (entity->state == 0xA && entity->handlerTicks == 0x46) {
        entity->vt->postEvent(entity, (rand() & 1) ? 0xC : 0xB);
    }
}

void Behavior_Type64(BehaviorEntity *entity, HandlerNode *node) {
    s32 phase;

    phase = node->tick % 300;
    node->fade = entity->vt->getSoundFade(entity);
    if (phase < 0x14) {
        node->voices[0].sound = 5;
        node->voices[0].octave = -2;
    } else if (phase == 0x16) {
        node->voices[0].sound = -2;
    }
    entity->vt->moveZ(entity, -0xA, 0);
}

void Behavior_Type65(BehaviorEntity *entity) {
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if (roll % 3 == 0) {
            entity->vt->scale(entity, 1, &g_scaleHalf);
            entity->vt->moveY(entity, -0x12C, 0);
            entity->vt->rotate(entity, 1, &g_rotY90);
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0x7D0) {
            entity->vt->rotate(entity, 0, &g_rotYNeg90);
        }
        entity->vt->moveZ(entity, -0x14, 0);
    }
}

void Behavior_Type66(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == ((node->tick / 30) * 30)) {
        node->voices[0].sound = 0xD;
    }
}

void Behavior_Type67(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        if (rand() % 3 == 0) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0x1F6) {
            entity->vt->moveY(entity, 0x800, 0);
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        }
        if (entity->handlerTicks >= 0x1F5) {
            entity->vt->moveZ(entity, -0x200, 0);
        }
    }
}

void Behavior_Type68(BehaviorEntity *entity, HandlerNode *node) {
    s16 speed;
    s32 coin;

    node->fade = entity->vt->getSoundFade(entity);
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
            if (entity->dreamSys->vt->wasCirclePressed(entity->dreamSys) != 0) {
                entity->handlerTicks = -1;
                entity->state = 10;
                node->voices[0].sound = 0x12;
            }
        }
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        entity->vt->moveZ(entity, entity->speed, 1);
        return;
    } else if (entity->state == 10) {
        if (entity->handlerTicks < 8) {
            entity->vt->rotate(entity, 0, g_rotZ9);
            entity->vt->move(entity, g_moveY8);
            return;
        }
        node->voices[0].sound = 0x12;
        node->voices[1].sound = 3;
        entity->vt->stopHandler(entity);
        coin = rand() & 1;
        entity->state = coin == 0;
        return;
    }
}

void Behavior_Type69(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
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

void Behavior_Type70(BehaviorEntity *entity) {
    s32 speed;

    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->handlerTicks == 0x12C) {
        entity->vt->rotate(entity, 0, g_rotY180);
    }
    if (entity->handlerTicks < 0x258) {
        BehaviorEntityVtbl *vt = entity->vt;

        speed = 0x100;
        if (entity->state == 0) {
            speed = -0x100;
        }
        vt->moveZ(entity, speed, 0);
    }
}

void Behavior_Type71(BehaviorEntity *entity, HandlerNode *node) {
    s32 roll;

    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0;
        roll = rand() % 3;
        entity->vt->moveX(entity, roll * 0xC800, 0, roll);
    }
    if (entity->handlerTicks >= 0x961) {
        Entity_FaceDreamer(entity, (void *)entity->dreamSys, 1, 0, 0);
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type73(BehaviorEntity *entity, HandlerNode *node) {
    s32 tick;

    tick = node->tick;
    node->fade = 0;
    if (tick == 0) {
        entity->dreamSys->vt->rotate(entity->dreamSys, 1, &g_rotY90);
        entity->dreamSys->vt->stopControls(entity->dreamSys, 1);
        node->voices[0].sound = 0x19;
        node->voices[1].sound = 0x19;
        node->voices[2].sound = 0x19;
    } else if (tick == 0x14) {
        node->voices[1].sound = 0xD;
    }
    if (entity->handlerTicks == (entity->animLength - 1)) {
        entity->vt->sleep(entity);
    }
}

void Behavior_Type74(BehaviorEntity *entity) {
    s32 ticks;

    if (entity->handlerTicks == 0) {
        entity->dreamSys->camera->vtbl->setClearColor(entity->dreamSys->camera, g_type74ClearColor);
        entity->state = rand() % 3;
        if (entity->dreamSys->pos.coord->coord.t.z < 0x262) {
            entity->state = 0;
        }
    }
    if (entity->state != 0) {
        if (entity->animLength / 2 < entity->handlerTicks) {
            entity->dreamSys->vt->moveZ(entity->dreamSys, 0x80, 0);
        }
        if (entity->handlerTicks == entity->animLength - 0x1E) {
            entity->vt->postEvent(entity, 0xA);
        }
    } else {
        ticks = entity->handlerTicks;
        if (ticks >= 0x14 && ticks < 0x78) {
            entity->dreamSys->vt->moveZ(entity->dreamSys, -((ticks - 0x13) << 5), 1);
            if (entity->handlerTicks == 0x55) {
                entity->dreamSys->vt->setControls(entity->dreamSys, 1, 1);
            }
        }
    }
}

void Behavior_Type75(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x19;
        node->voices[1].sound = 0x19;
        node->voices[2].sound = 0x19;
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->stopAnimation(entity);
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type76(BehaviorEntity *entity) {
    if (entity->touched != 0) {
        entity->vt->playAnimation(entity);
        if (entity->animFrame == entity->animLength - 1) {
            entity->vt->stopAnimation(entity);
            entity->vt->scale(entity, 0, g_scaleShrinkStep);
        }
    } else {
        entity->vt->stopAnimation(entity);
        entity->vt->rotate(entity, 0, g_rotY9);
    }
}

void Behavior_Type77(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % 5 == 0) {
        node->voices[0].sound = 0x11;
        node->voices[0].octave = -2;
    }
    if (entity->animation == 0) {
        if (entity->handlerTicks == entity->animLength) {
            entity->vt->setAnimation(entity, 1);
            if (rand() & 1) {
                entity->state = 0xB;
            }
        }
    } else {
        if (entity->state == 0) {
            if (entity->handlerTicks == 0x3C || entity->handlerTicks == 0xD4 || entity->handlerTicks == 0x122 || entity->handlerTicks == 0x140) {
                entity->vt->rotate(entity, 0, &g_rotY90);
            }
            if (entity->handlerTicks == 0x18E) {
                entity->vt->rotate(entity, 0, &g_rotYNeg90);
            }
            entity->vt->moveZOnGround(entity, -0x32, 0);
        } else {
            if (entity->handlerTicks == 0x3C || entity->handlerTicks == 0x8C) {
                entity->vt->rotate(entity, 0, &g_rotY90);
            }
            if (entity->handlerTicks < 0xAE) {
                entity->vt->moveZOnGround(entity, -0x32, 0);
            }
            if (entity->handlerTicks == 0xAE) {
                entity->vt->stopHandler(entity);
                entity->state = 1;
            }
        }
    }
}

void Behavior_Type78(BehaviorEntity *entity, HandlerNode *node) {
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
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animPlaying != 0 && !(node->tick & 3)) {
        node->voices[0].sound = 0x1C;
    }
    length = entity->animLength;
    ticks = entity->handlerTicks;
    if (ticks == length - 1) {
        entity->handlerTicks = -1;
    } else if (ticks >= length / 2 + length / 4) {
        entity->vt->playAnimation(entity);
    } else if (ticks >= length / 2) {
        if (ticks == length / 2) {
            node->voices[0].sound = 0x10;
        }
        entity->vt->moveZ(entity, 0x6E, 0);
    } else if (ticks >= length / 4) {
        entity->vt->stopAnimation(entity);
        entity->vt->moveZ(entity, -0x6E, 0);
    }
    if (entity->state == 0xB && node->tick == 0x1FE) {
        entity->vt->moveY(entity, -0x17C, 0);
        entity->vt->rotate(entity, 0, &g_rotX90);
        entity->vt->stopHandler(entity);
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
            entity->vt->scale(entity, 1, factors);
            entity->vt->moveY(entity, roll, 0);
        }
    }
    if (node->tick == 0x208 && g_type78Stopped != 0) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type79(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % 10 == 0) {
        node->voices[0].sound = 0x19;
        node->voices[0].octave = 2;
    }
    entity->vt->rotate(entity, 0, g_rotY2);
    if ((entity->state == 0) && (entity->touched != 0)) {
        entity->vt->postEvent(entity, 0xB);
        entity->state = 0xB;
    }
}

void Behavior_Type80(BehaviorEntity *entity, HandlerNode *node) {
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
        entity->vt->stopAnimation(entity);
        entity->vt->move(entity, g_moveYNeg512);
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type81(BehaviorEntity *entity, HandlerNode *node) {
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
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        mode = entity->state;
        if (mode == 1) {
            entity->vt->scale(entity, 0, g_scaleGrowStep);
            speed = -0x176;
            if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x200) {
                entity->vt->sleep(entity);
                entity->state = mode;
            }
        } else {
            entity->dreamSys->vt->stopControls(entity->dreamSys, 1);
            Entity_FaceDreamer(entity->dreamSys, entity, 1, 1, 0);
            if (entity->state == 2) {
                if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x960) {
                    entity->state = 0xB;
                    entity->vt->postEvent(entity, 0xC);
                }
                speed = -0x60;
            } else {
                speed = 0;
            }
        }
    } else {
        node->fade = entity->vt->getSoundFade(entity);
        if (node->tick % 22 == 0) {
            node->voices[0].sound = 0x1C;
        }
        if (entity->handlerTicks >= 0x1F5) {
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        }
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x800) {
            entity->dreamSys->vt->moveZ(entity->dreamSys, -0x800, 0);
        }
        speed = -0x14;
    }
    entity->vt->moveZOnGround(entity, speed, 1);
    if (entity->contact != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type82(BehaviorEntity *entity, HandlerNode *node) {
    s32 state;
    BehaviorDreamSys *dreamSys;

    if (entity->state == 0 && entity->handlerTicks == 0) {
        if (rand() % 3) {
            state = (rand() & 1) ? 0xB : 0xC;
            entity->state = state;
        } else {
            entity->vt->stopHandler(entity);
            entity->vt->moveZ(entity, -0x5000, 0);
            rand();
        }
    }
    if (entity->state == 0xC) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        if (entity->handlerTicks == 0x14) {
            node->voices[0].sound = 0x12;
            node->fade = 0;
            node->voices[1].sound = 3;
            dreamSys = entity->dreamSys;
            dreamSys->vt->stopControls(dreamSys, 1);
        }
        if (entity->handlerTicks >= 0x15) {
            entity->vt->moveZ(entity, -0x28, 0);
        }
        if (entity->handlerTicks == 0x28) {
            entity->vt->postEvent(entity, 0xA);
        }
    } else if (entity->state == 0xB) {
        entity->vt->stopAnimation(entity);
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x200) {
            if (rand() % 3) {
                entity->vt->sleep(entity);
            } else {
                entity->vt->stopHandler(entity);
            }
        }
    }
}

void Behavior_Type83(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->animFrame == ((entity->animFrame / 15) * 15)) {
        node->voices[0].sound = 12;
        node->fade = 0;
        node->voices[0].octave = 2;
    }
    if (entity->handlerTicks == entity->animLength) {
        node->voices[0].sound = -2;
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type84(BehaviorEntity *entity, HandlerNode *node) {
    s32 frame;

    node->fade = entity->vt->getSoundFade(entity);
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
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type85(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->state == 0) {
        if (entity->animFrame == 5) {
            Behavior_QueueLowSound7(node);
        }
        if (entity->handlerTicks == entity->animLength) {
            entity->vt->stopAnimation(entity);
            entity->state = 0xA;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xA) {
        if (entity->handlerTicks < 0xA) {
            entity->vt->rotate(entity, 0, g_rotY9);
            if (entity->dreamSys->vt->wasCirclePressed(entity->dreamSys) != 0) {
                Behavior_QueueLowSound7(node);
                entity->state = 0xC;
                entity->handlerTicks = -1;
            }
        } else {
            entity->dreamSys->vt->stopControls(entity->dreamSys, 1);
            entity->state = 0xB;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xB) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        if (entity->handlerTicks < 0x1E) {
            entity->vt->moveZ(entity, -10, 0);
        } else {
            Behavior_QueueLowSound7(node);
            if (Entity_StartEffect((Entity *)entity, 0, 0, 0x1E, 0) != 0) {
                entity->effect->vtbl->startIn(entity->effect, entity->clock, 7, 0);
            }
            entity->state = 0xD;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xD) {
        if (entity->handlerTicks < 0x5A) {
            if (entity->handlerTicks == 0x1E) {
                if (Entity_StartEffect((Entity *)entity, 0, 0, 0xA, 0) != 0) {
                    entity->effect->vtbl->startOut(entity->effect, entity->clock, 0, 0);
                }
            }
            entity->dreamSys->vt->rotate(entity->dreamSys, 0, g_rotZ1);
        } else {
            Behavior_QueueSound18And3(node);
            entity->dreamSys->vt->rotate(entity->dreamSys, 1, g_rotY180);
            entity->vt->postEvent(entity, rand() % 5 ? 0xA : 0xC);
            entity->state = 0xE;
        }
    } else if (entity->state == 0xC) {
        if (entity->handlerTicks < 0xA) {
            entity->vt->rotate(entity, 0, g_rotZNeg9);
        } else {
            Behavior_QueueSound18And3(node);
            entity->vt->stopHandler(entity);
            entity->state = 1;
        }
    }
}

void Behavior_Type86(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks < 0xA) {
        entity->vt->stopAnimation(entity);
    } else if (entity->handlerTicks == 0xA) {
        entity->vt->playAnimation(entity);
    }
    if (entity->animFrame == 0xA) {
        Behavior_QueueSound18And3(node);
    }
    if (entity->handlerTicks == entity->animLength + 0xA) {
        entity->vt->stopHandler(entity);
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

void Behavior_Type87(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0x12;
    }
    if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
}

void Behavior_Type88(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == entity->animLength / 2) {
        node->voices[0].sound = 0x12;
    }
    if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
}

void Behavior_Type89(BehaviorEntity *entity, HandlerNode *node) {
    s32 ticks;

    ticks = entity->handlerTicks;
    if (ticks == 0x14) {
        node->voices[0].sound = 0x12;
        node->fade = 0;
        node->voices[1].sound = 3;
        return;
    }
    if (ticks == entity->animLength) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
        if (rand() & 1) {
            entity->vt->postEvent(entity, 0xB);
        }
    }
}

void Behavior_Type90(BehaviorEntity *entity, HandlerNode *node) {
    s32 sound;

    node->fade = entity->vt->getSoundFade(entity);
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

void Behavior_Type91(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        if (Entity_StartEffect(entity, 0, 0, 5, 0)) {
            if (rand() & 1) {
                entity->vt->move(entity, g_moveYNeg256);
            }
            entity->effect->vtbl->startIn(entity->effect, entity->clock, 0, 0);
        }
    } else if (entity->animFrame == 0) {
        do {
            entity->animData = entity->vt->applyFrame(entity, entity->animData, 0);
            entity->animFrame++;
        } while (entity->animFrame < 0x18);
    }
    if (entity->animFrame >= 0x19) {
        entity->vt->moveZ(entity, -0x14, 0);
        entity->dreamSys->vt->stopControls(entity->dreamSys, 1);
    }
    if (entity->handlerTicks == 0x32) {
        entity->vt->postEvent(entity, 0xA);
    } else if (entity->handlerTicks == 0xC) {
        node->fade = 0;
        node->voices[0].sound = 0x15;
    }
    entity->vt->scale(entity, 1, g_scaleSquash);
}

void Behavior_Type92(BehaviorEntity *entity, HandlerNode *node) {
    s32 frame;

    if (entity->animation == 0) {
        if (entity->touched != 0) {
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
            entity->vt->setAnimation(entity, 1);
            entity->dreamSys->vt->stopControls(entity->dreamSys, 1);
        } else if (entity->animFrame == 0) {
            do {
                entity->animData = entity->vt->applyFrame(entity, entity->animData, 0);
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
            entity->vt->postEvent(entity, 0xA);
        }
    }
    entity->vt->scale(entity, 1, g_scaleSquash);
}

void Behavior_Type93(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % 10 == 0) {
        node->voices[0].sound = 3;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->setAnimation(entity, 1);
    }
    if (entity->animation == 1) {
        entity->vt->moveZ(entity, -0x80, 1);
    }
}

void Behavior_Type94(BehaviorEntity *entity, HandlerNode *node) {
    s32 roll;
    BehaviorDreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) != 7) {
            entity->state = 0xB;
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == (node->tick / 10) * 10) {
        node->voices[0].sound = 0xE;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->setAnimation(entity, 1);
        if (entity->state != 0 && !(rand() & 1)) {
            entity->vt->scale(entity, 1, &g_scaleSix);
            entity->vt->moveY(entity, 0x800, 0);
        }
        roll = rand();
        if (roll == (roll / 3) * 3) {
            entity->vt->rotate(entity, 0, &g_rotY180);
        }
    }
    if (entity->animation != 0) {
        entity->vt->moveZ(entity, -0x80, 1);
    }
}

void Behavior_Type95(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        entity->vt->setAnimation(entity, 3);
    } else if (entity->handlerTicks == entity->animLength) {
        entity->vt->setAnimation(entity, 1);
    }
    if (entity->animation == 1) {
        entity->vt->moveZ(entity, -0x80, 0);
    }
}

void Behavior_Type96(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        entity->vt->setAnimation(entity, rand() % 4);
        return;
    }
    if (entity->handlerTicks % entity->animLength == 0) {
        entity->vt->setAnimation(entity, rand() % 4);
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0x16;
        node->voices[0].octave = 2;
        node->voices[0].volume = 0x40;
        node->voices[0].endVolume = 0x20;
    }
}

void Behavior_EraseFlashbacks(BehaviorEntity *entity) {
    if (entity->touched != 0 && Entity_StartEffect(entity, 0, 0, 0xA, 0)) {
        entity->effect->vtbl->startIn(entity->effect, entity->clock, 7, 0);
        entity->vt->sleep(entity);
        entity->dreamSys->vt->clearFlashbacks(entity->dreamSys);
    }
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type102(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    void *factors;
    s32 length;
    s32 ticks;

    if (entity->handlerTicks == 0) {
        entity->vt->moveY(entity, -0x200, 0);
    }
    node->fade = entity->vt->getSoundFade(entity);
    length = entity->animLength;
    if (entity->animFrame == length / 2) {
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
        node->voices[1].sound = 3;
        node->voices[1].octave = -2;
    }
    if (entity->handlerTicks >= 0x33) {
        entity->vt->rotate(entity, 0, &g_rotYNegThird);
    }
    if (entity->handlerTicks >= 0x30D) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        ticks = entity->handlerTicks;
        if (ticks >= 0x790) {
            factors = &g_scaleOne;
        } else if (ticks >= 0x78B) {
            factors = g_scaleSquash;
        } else if (ticks >= 0x786) {
            factors = &g_scaleHalf;
        } else {
            factors = &g_scaleEighth;
            if (ticks >= 0x781) {
                factors = &g_scaleQuarter;
            }
        }
        entity->vt->scale(entity, 1, factors);
        if (entity->handlerTicks < 0x7D0) {
            entity->vt->moveZ(entity, -0x40, 0);
        } else {
            entity->state = 1;
        }
    } else {
        entity->vt->moveZ(entity, -0x100, 0);
    }
    if ((entity->touched != 0) && (entity->state == 0)) {
        dreamSys = entity->dreamSys;
        entity->state = 0xC;
        dreamSys->vt->stopControls(dreamSys, 1);
        entity->vt->postEvent(entity, 0xA);
    }
    if (entity->state == 0xC) {
        dreamSys = entity->dreamSys;
        dreamSys->vt->moveZ(dreamSys, 0x100, 0);
    }
}

void Behavior_Type103(BehaviorEntity *entity) {
    s32 roll;
    BehaviorMap *map;

    if (entity->handlerTicks == 0x2BC) {
        roll = rand();
        if (roll == (roll / 3) * 3) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks < 0x3FC) {
            entity->vt->rotate(entity, 0, g_rotYNegHalf);
            entity->vt->moveY(entity, 0x1E, 0);
        }
        if (entity->handlerTicks == 0x3A2) {
            entity->vt->postEvent(entity, 0xA);
        }
    } else if (entity->handlerTicks == 0x64 || entity->handlerTicks == 0x320) {
        if (rand() % 5 == 0) {
            map = entity->map;
            map->vt->startTileStretch(map, 4, 0);
        }
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type104(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleQuarter);
    if (entity->handlerTicks >= 201 && entity->handlerTicks < 300) {
        entity->vt->moveY(entity, -0x20, 0);
    }
}

void Behavior_Type105(BehaviorEntity *entity) {
    entity->vt->setVisible(entity, (rand() % 20) == 0);
}

void Behavior_Type106(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        if ((rand() & 1) == 0) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0) {
            entity->vt->stopAnimation(entity);
        }
        entity->vt->scale(entity, 1, g_scaleThinTall);
    } else {
        if (entity->handlerTicks == 0) {
            entity->vt->setAnimation(entity, 1);
        }
        entity->vt->moveX(entity, (entity->handlerTicks % 20) < 10 ? 0x20 : -0x20, 0);
    }
}

void Behavior_Type108(BehaviorEntity *entity, HandlerNode *node) {
    Behavior_Type71(entity, node);
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_YellowDayBeast(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleHalf);
    entity->vt->moveZ(entity, -10, 0);
}

void Behavior_BridgeGeisha(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, g_scaleTwoFifths);
    entity->vt->stopAnimation(entity);
    if (entity->state == 0 && entity->vt->distanceTo(entity, entity->dreamSys) < 0x800) {
        entity->state = 0xA;
        entity->handlerTicks = 0;
    }
    if (entity->state == 0xA) {
        if (entity->handlerTicks < 0x2D) {
            entity->vt->rotate(entity, 0, g_rotY4);
        }
        if (entity->handlerTicks >= 0x1F5) {
            entity->state = 0;
        }
    }
}

void Behavior_FlyingTrain(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    s32 ticks;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) == 5) {
            entity->state = 0xB;
        }
    }
    if (entity->state != 0 && entity->handlerTicks >= 0x870) {
        ticks = entity->handlerTicks;
        if ((u32)(ticks - 0x870) < 0x191U) {
            if (ticks == 0x870) {
                entity->vt->stopAnimation(entity);
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
                entity->vt->playAnimation(entity);
                node->tick = 1;
            }
        } else if (ticks >= 0xA03) {
            if (ticks >= 0xAF1) {
                entity->vt->moveY(entity, -0x20, 0);
            }
            Behavior_TrainRun(entity, node, 0x1E1, 0xFA0, -0x3C);
        }
    } else {
        Behavior_TrainRun(entity, node, 0x1E1, 0x884, -0x3C);
    }
}

static void Behavior_TrainRun(BehaviorEntity *entity, HandlerNode *node, s32 turnTick, s32 leaveTick, s32 speed) {
    node->fade = 0;
    if (node->tick == 6) {
        node->voices[0].sound = 4;
        node->voices[1].sound = 4;
        node->voices[2].sound = 4;
    }
    if ((entity->handlerTicks >= turnTick && entity->handlerTicks <= turnTick + 0x5B) ||
        (entity->handlerTicks >= turnTick + 0x155 && entity->handlerTicks <= turnTick + 0x1B1) ||
        (entity->handlerTicks >= turnTick + 0x2BA && entity->handlerTicks <= turnTick + 0x317)) {
        entity->vt->rotate(entity, 0, &g_rotY1);
    }
    entity->vt->moveZ(entity, speed, 0);
    if (entity->handlerTicks == leaveTick) {
        entity->vt->sleep(entity);
        entity->state = 1;
    }
}

void Behavior_Type113(BehaviorEntity *entity, HandlerNode *node) {
    Behavior_MazePenguin(entity, node);
}

void Behavior_RedDayPenguin(BehaviorEntity *entity) {
    s16 *angles;

    if (rand() % 3 == 0) {
        return;
    }
    if (rand() % 3 != 0) {
        angles = g_rotY9;
    } else {
        angles = g_rotYNeg9;
    }
    entity->vt->rotate(entity, 0, angles);
}

void Behavior_Type117(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type118(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type121(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleQuarter);
}

void Behavior_Type123(BehaviorEntity *entity) {

    if (entity->handlerTicks == 0) {
        if (rand() % 5 == 0) {
            entity->state = 0xB;
        }
    }
    entity->vt->stopAnimation(entity);
    entity->vt->moveZ(entity, 0x64, 0);
    if (entity->handlerTicks == 0x3E8) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
    if ((entity->state == 0xB) && (entity->handlerTicks >= 0x12D)) {
        entity->dreamSys->vt->onPad(entity->dreamSys, 0, 2);
        entity->dreamSys->vt->onPad(entity->dreamSys, 0, 7);
    }
}

void Behavior_OddDayGeisha(BehaviorEntity *entity, HandlerNode *node) {
    if (((entity->handlerTicks == 0) && !(rand() & 3)) || (entity->handlerTicks == 0xE10)) {
        entity->vt->sleep(entity);
        entity->state = 1;
    }
    entity->vt->scale(entity, 1, g_scaleTwoFifths);
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
        node->voices[0].octave = 1;
    }
    entity->vt->moveZ(entity, -0xA, 0);
}

void Behavior_TinyLips(BehaviorEntity *entity) {
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    entity->vt->scale(entity, 1, &g_scaleTiny);
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type129(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        entity->state = (rand() % 2) + 0xA;
    }
    entity->vt->stopAnimation(entity);
    if (entity->handlerTicks >= 0xC9) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        if (entity->state == 0xA) {
            entity->vt->moveZOnGround(entity, -0x200, 0);
        }
    }
}

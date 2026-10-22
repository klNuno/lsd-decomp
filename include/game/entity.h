#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "common.h"
#include "game/gs.h"
#include "game/handler_node.h"
#include "game/stage.h"
#include "game/heap.h"
#include "game/mom.h"
#include "game/model_object.h"
#include "game/render.h"

/*
 * Characters ("entities"): the per-type record table, the spawn tables that place them,
 * and the character object of class vtable 0x80089AD4 (constructor Entity_Init, 0x108 bytes).
 * Meanings and addresses: docs/discoveries.md, "The hidden rules that decide which characters
 * appear" and "The character record: mood, points, waking up and leaving".
 */

/* One record per entity type, 16 bytes, table g_entityRecords indexed by Entity.type (dump: tools/research/recs.py). */
typedef struct EntityRecord {
    MoodPoint mood;  /* 0x00 graph point logged when touched (slot 0x14C returns the record) */
    s8 points;       /* 0x02 points / 1000 (slot 0x150) */
    s8 wakeMode;     /* 0x03 0 at spawn, 1 in the box ahead of the dreamer, 2 outside it, 3 in it and 1/128, 4 1/128 anywhere */
    u8 sleepMode;    /* 0x04 1 in the box ahead of the dreamer, 2 outside it, >= 10 after sleepMode * 15 ticks */
    s8 wakeRange;    /* 0x05 range of the wake and sleep tests, << 11 */
    s8 touchRange;   /* 0x06 negative: same range, and the entity also faces or follows the dreamer (SceneNode_TurnToward) */
    s8 link;         /* 0x07 > 0 stage link - 1, < 0 stage ~link (slot 0x154) */
    s8 video;        /* 0x08 event video + 1 (slot 0x158); with link < 0, link radius << 9 */
    s8 boxSize;         /* 0x09 last parameter of every range test (Entity_IsAtPointAhead) */
    s8 soundRange;   /* 0x0A range Entity_GetSoundFade (slot 0x148) fades the handler sounds over, << 11 */
    s8 handlerRange; /* 0x0B range that starts the handler (slot 0x17C); negative also stops it out of range */
    void *handler;   /* 0x0C per-tick handler, registered by slot 0x168 */
} EntityRecord;

/* A character group of a stage, 8 bytes, tables g_spawnGroups[stage] (count g_spawnGroupCounts[stage]). */
typedef struct SpawnGroup {
    s8 done;      /* 0x00 set when the rule passed; a negative rule then fails until Sym_ResetGroupsAndLoadSpy clears it */
    s8 rule;      /* 0x01 day, month or mood-colour rule, Sym_CheckRule */
    s8 model;     /* 0x02 model index in the map square's file */
    u8 type;      /* 0x03 entity type, index of EntityRecord */
    s8 places[4]; /* 0x04 place indexes, -1 ends the list */
} SpawnGroup;

/* A spawn slot of a stage, 6 bytes, tables g_spawnSlots[stage] (count g_spawnSlotCounts[stage]). */
typedef struct SpawnSlot {
    s16 chunkKey;  /* 0x00 map square the slot belongs to */
    s8 dayParity;  /* 0x02 0 every day, else the slot is skipped when (day % 2) + 1 equals it */
    s8 groups[3];  /* 0x03 SpawnGroup indexes, -1 ends the list */
} SpawnSlot;

/* A place a group can stand on, 4 bytes, table g_spawnPlaces indexed by SpawnGroup.places (Sym_SpawnAtPlace). */
typedef struct SpawnPlace {
    u16 tile; /* 0x00 copied into the placement query */
    s8 rotationIndex;  /* 0x02 index of a 12-byte record at g_spawnPlaceRotations, given to the new entity's slot 0x44 */
    s8 offsetIndex;  /* 0x03 index of a 6-byte record at g_spawnPlaceOffsets, copied into the placement query */
} SpawnPlace;

struct DreamSys;
struct StageMap;
struct Fade;

/*
 * Class vtable 0x80089AD4 (returned by Entity_GetVtbl). Slots up to 0x140 belong to the model base
 * class (vtable 0x8008A6C4, src/game/model.c), 0x144 on are the entity's own; slots named from the
 * functions stored there. distanceTo is called with two and with three arguments and moveX with
 * three and two, so they have no prototype.
 */
typedef struct EntityVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(void *self);                             /* 0x04 Object_Delete */
    s32 (*init)(void *self, s32 type, void *source, SoundBank *soundBank); /* 0x08 Entity_Init */
    void (*destroy)(void *self);                             /* 0x0C Entity_Destruct */
    u8 pad_10[0x30 - 0x10];
    void (*notify)(void *self, s32 event);                 /* 0x30 entity event: 9 touch (the box ahead), 10 link, 11 end with the record's video, 12 end */
    u8 pad_34[0x38 - 0x34];
    void (*onNotify)(void *self, void *sender, s32 message);  /* 0x38 Model_OnNotify */
    u8 pad_3C[0x40 - 0x3C];
    void (*reset)(void *self);                                 /* 0x40 Entity_Reset, last step of init */
    void (*rotate)(void *self, s32 absolute, void *angles);   /* 0x44 SceneNode_SetRotation: degrees as {num, den} s16 pairs */
    void (*scale)(void *self, s32 absolute, void *factors);   /* 0x48 SceneNode_SetScale: {num, den} s16 pairs */
    void (*attach)(void *self, struct DreamSys *dreamSys, void *watched, struct StageMap *map, void *placement); /* 0x4C Entity_Attach */
    void (*detach)(void *self);                               /* 0x50 Entity_Detach */
    u8 pad_54[0x60 - 0x54];
    void (*setVisible)(void *self, s32 visible);              /* 0x60 Model_SetVisible, 1 on wake, 0 on sleep */
    u8 pad_64[0x70 - 0x64];
    void (*setLightFlags)(void *self, s32 flags);             /* 0x70 Model_SetLightFlags */
    u8 pad_74[0x98 - 0x74];
    void (*onClock)(void *self, void *sender, s32 phase);      /* 0x98 Entity_Update */
    u8 pad_9C[0xB8 - 0x9C];
    void (*setPos)(void *self, void *pos);               /* 0xB8 Actor_SetPos */
    void (*movePos)(void *self, void *delta);                    /* 0xBC Actor_MovePos: adds a world vector to the position */
    u8 pad_C0[0xC4 - 0xC0];
    void (*moveZ)(void *self, s32 amount, s32 notify);        /* 0xC4 Actor_MoveZ: along the model's own z axis; notify sends box message 6 after the move */
    void (*moveX)();                                          /* 0xC8 Actor_MoveX (self, amount, notify): own x axis, box message 7 */
    void (*moveY)(void *self, s32 amount, s32 notify);        /* 0xCC Actor_MoveY: own y axis, negative is up, box message 8 */
    void (*moveZOnGround)(void *self, s32 amount, s32 notify); /* 0xD0 Actor_MoveZOnGround: moveZ, then the ground test Actor_SnapToGround */
    u8 pad_D4[0xDC - 0xD4];
    void (*onActorContact)(void *self, void *sender, s32 message); /* 0xDC Entity_OnActorContact */
    void (*onTileContact)(void *self, void *sender, s32 message);  /* 0xE0 Entity_OnTileContact */
    u8 pad_E4[0x10C - 0xE4];
    void (*setTickMode)(void *self, s32 mode);                /* 0x10C Model_SetTickMode */
    void (*startTick)(void *self);                            /* 0x110 Model_StartTick */
    void (*stopTick)(void *self);                             /* 0x114 Model_StopTick */
    u8 pad_118[0x128 - 0x118];
    void (*setAnimation)(void *self, s32 animation);          /* 0x128 Model_SetAnimation */
    void (*playAnimation)(void *self);                        /* 0x12C Model_PlayAnimation */
    void (*stopAnimation)(void *self);                        /* 0x130 Model_StopAnimation */
    u8 *(*applyFrame)(void *self, u8 *frame, void *context);  /* 0x134 Model_ApplyFrame: runs one frame's commands, returns the next frame */
    u8 pad_138[0x144 - 0x138];
    s32 (*distanceTo)();                                      /* 0x144 Entity_GroundDistance */
    s32 (*getSoundFade)(void *self);                          /* 0x148 Entity_GetSoundFade */
    EntityRecord *(*getRecord)(void *self);                   /* 0x14C Entity_GetRecord */
    s32 (*getPoints)(void *self);                             /* 0x150 Entity_GetPoints */
    s32 (*getLinkStage)(void *self);                          /* 0x154 Entity_GetLinkStage */
    s32 (*getVideo)(void *self);                              /* 0x158 Entity_GetVideo */
    void (*wake)(void *self);                                 /* 0x15C Entity_Wake */
    void (*sleep)(void *self);                                /* 0x160 Entity_Sleep */
    void (*setTouched)(void *self, s32 touched);              /* 0x164 Entity_SetTouched */
    void (*startHandler)(void *self);                         /* 0x168 Entity_StartHandler */
    void (*stopHandler)(void *self);                          /* 0x16C Entity_StopHandler */
    s32 (*checkWake)(void *self);                             /* 0x170 Entity_CheckWake */
    void (*checkSleep)(void *self);                           /* 0x174 Entity_CheckSleep */
    void (*checkTouch)(void *self);                           /* 0x178 Entity_CheckTouch */
    s32 (*checkHandlerStart)(void *self);                     /* 0x17C Entity_CheckHandlerStart */
    void (*checkHandlerStop)(void *self);                     /* 0x180 Entity_CheckHandlerStop */
} EntityVtbl;

/*
 * The entity, 0x108 bytes (Entity_Create). Fields up to +0x94 are Model's (model.h) under the same
 * names and types, with the vtable typed as EntityVtbl; Model.target is named dreamSys here, the
 * object passed to attach (an entity's target is always the dreamer).
 */
typedef struct Entity {
    EntityVtbl *vtbl;        /* 0x00 */
    ListNode *watched;       /* 0x04 */
    ListNode *watchers;      /* 0x08 */
    struct SceneNode *parent; /* 0x0C attach runs only while it is 0, detach only while it is set */
    DObj2 object;            /* 0x10 coord is its GsCOORDINATE2 (gs.h): position t, world position workT */
    s32 id;                  /* 0x1C */
    ModelObject *model;      /* 0x20 */
    u32 ticks;               /* 0x24 cleared on waking; sleep mode >= 10 compares it with mode * 15 */
    void *contact;           /* 0x28 result of the ground test after moveZOnGround */
    s32 hitMask;             /* 0x2C */
    NodeBoxList *boxList;    /* 0x30 */
    u8 pad_34[0x44 - 0x34];
    s32 state;               /* 0x44 handler state; 1 stops Entity_CheckWake for good */
    s16 speed;               /* 0x48 last amount given to moveX, moveY or moveZ (Actor_MoveAxis) */
    u8 pad_4A[0x4C - 0x4A];
    struct StageMap *map;    /* 0x4C the map it stands on (stage_map.h): third argument of attach, cleared by detach; slot 0x110 ground query */
    void *clock;             /* 0x50 Model.clock, the ticker Fade_StartIn and Fade_StartOut take */
    s32 boxMargin;           /* 0x54 */
    SoundBank *soundBank;    /* 0x58 the handler node's voices play on it (HandlerNode_Start, HandlerNode_Run) */
    Mom *file;               /* 0x5C */
    s32 ownsFile;            /* 0x60 */
    s32 forwardContact;      /* 0x64 */
    struct SceneNode *part;  /* 0x68 */
    s32 partCount;           /* 0x6C model parts (Model in model.h) */
    struct SceneNode **parts; /* 0x70 */
    u8 *partIds;             /* 0x74 */
    void (*tickFn)(void *self); /* 0x78 */
    s32 animation;           /* 0x7C current animation (setAnimation) */
    s32 animLength;          /* 0x80 frames of the current animation */
    s32 animFrame;           /* 0x84 current frame, 0 to animLength - 1 */
    u8 *animData;            /* 0x88 the next frame's commands (applyFrame) */
    s32 tickEnabled;         /* 0x8C */
    s32 animPlaying;         /* 0x90 playAnimation sets it, stopAnimation clears it */
    struct DreamSys *dreamSys; /* 0x94 Model.target: the object passed to attach (g_symDreamSys); range tests measure from it */
    s32 type;                /* 0x98 entity type, index of EntityRecord */
    HandlerNode handlerNode; /* 0x9C the record's handler (handler_node.h); its fadeSteps divides slot 0x148's range */
    s32 awake;               /* 0xF0 set by wake, cleared by sleep */
    s32 touched;             /* 0xF4 set by setTouched */
    s32 handlerActive;       /* 0xF8 set by startHandler, cleared by stopHandler */
    s32 handlerTicks;        /* 0xFC cleared by startHandler, counted by slot 0x11C */
    struct Fade *effect;     /* 0x100 a Fade (fade.h) made by Fade_Create: the Grey Man white flash */
    struct Fade *secondEffect;
} Entity;

/* Functions of src/game/entity.c that other files call or reference (docs/naming.md, Prototypes) */
Entity *Entity_Create(s32 type, void *source, SoundBank *soundBank);

#endif

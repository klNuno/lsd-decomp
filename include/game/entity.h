#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "types.h"
#include "game/sound.h"
#include "game/gs.h"

/*
 * Characters ("entities"): the per-type record table, the spawn tables that place them,
 * and the character object of class vtable 0x80089AD4 (constructor Entity_Construct, 0x108 bytes).
 * Meanings and addresses: docs/discoveries.md, "The hidden rules that decide which characters
 * appear" and "The character record: mood, points, waking up and leaving".
 */

/* One record per entity type, 16 bytes, table g_entityRecords indexed by Entity.type (dump: work/hunt3/recs.txt). */
typedef struct EntityRecord {
    s8 mood[2];      /* 0x00 graph point logged when touched (slot 0x14C returns the record) */
    s8 points;       /* 0x02 points / 1000 (slot 0x150) */
    s8 wakeMode;     /* 0x03 0 at spawn, 1 in range, 2 out of range, 3 in range and 1/128, 4 1/128 anywhere */
    u8 sleepMode;    /* 0x04 1 in range, 2 out of range, >= 10 after sleepMode * 15 ticks */
    s8 wakeRange;    /* 0x05 range of the wake and sleep tests, << 11 */
    s8 touchRange;   /* 0x06 negative: same range, and the entity also faces or follows the dreamer (Entity_FaceDreamer) */
    s8 link;         /* 0x07 > 0 stage link - 1, < 0 stage ~link (slot 0x154) */
    s8 video;        /* 0x08 event video + 1 (slot 0x158); with link < 0, link radius << 9 */
    s8 boxSize;         /* 0x09 last parameter of every range test (Entity_IsInRange) */
    s8 soundRange;   /* 0x0A range Entity_GetSoundFade (slot 0x148) fades the handler sounds over, << 11 */
    s8 handlerRange; /* 0x0B range that starts the handler (slot 0x17C); negative also stops it out of range */
    void *handler;   /* 0x0C per-tick handler, registered by slot 0x168 */
} EntityRecord;

/* A character group of a stage, 8 bytes, tables g_spawnGroups[stage] (count g_spawnGroupCounts[stage]). */
typedef struct SpawnGroup {
    s8 done;      /* 0x00 set when the rule passed; a negative rule then fails until Sym_LoadModels clears it */
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
    u16 unk0; /* 0x00 copied into the placement query */
    s8 unk2;  /* 0x02 index of a 12-byte record at g_spawnPlaceRotations, given to the new entity's slot 0x44 */
    s8 unk3;  /* 0x03 index of a 6-byte record at g_spawnPlaceOffsets, copied into the placement query */
} SpawnPlace;

/*
 * Class vtable 0x80089AD4 (returned by Entity_GetVtbl). Slots 0x8 to 0x180 named from the functions
 * stored there; the slots the class inherits from its base (vtable 0x8008A6C4) keep unk names.
 * distanceTo is called with two and with three arguments, so it has no prototype.
 */
typedef struct EntityVtbl {
    u8 pad_00[0x8];
    s32 (*construct)(s32 self, s32 type, s32 arg2, s32 arg3); /* 0x08 Entity_Construct */
    void (*destruct)(void *self);                             /* 0x0C Entity_Destruct */
    u8 pad_10[0x30 - 0x10];
    void (*postEvent)(void *self, s32 event);                 /* 0x30 entity event: 9 touch, 10 link, 11 video end, 12 end */
    u8 pad_34[0x40 - 0x34];
    void (*init)(void *self);                                 /* 0x40 Entity_Init, last step of construct */
    void (*rotate)(void *self, s32 arg1, void *arg2);        /* 0x44 SceneNode_SetRotation (self, assign, degrees) */
    u8 pad_48[0x4C - 0x48];
    void (*attach)(void *self, void *dreamSys, s32 arg2, s32 arg3, void *place); /* 0x4C Entity_Attach */
    void (*detach)(void *self);                               /* 0x50 Entity_Detach */
    u8 pad_54[0x60 - 0x54];
    void (*setVisible)(void *self, s32 arg1);
    u8 pad_64[0x70 - 0x64];
    void (*setLightFlags)(void *self, s32 arg1);
    u8 pad_74[0x98 - 0x74];
    void (*update)(void *self, void *arg1, s32 arg2);         /* 0x98 Entity_Update */
    u8 pad_9C[0x10C - 0x9C];
    void (*setTickMode)(void *self, s32 arg1);                /* 0x10C */
    void (*startTick)(void *self);                            /* 0x110 */
    void (*stopTick)(void *self);                             /* 0x114 */
    u8 pad_118[0x120 - 0x118];
    s32 (*testPointAhead)(void *self, s32 arg1, s32 range, void *pos, s32 arg4); /* the range test Entity_IsInRange runs on the dreamer */
    u8 pad_124[0x12C - 0x124];
    void (*playAnimation)(void *self);                        /* 0x12C */
    void (*stopAnimation)(void *self);                        /* 0x130 */
    u8 pad_134[0x144 - 0x134];
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


typedef struct Entity {
    EntityVtbl *vt;
    u8 pad_04[0xC - 0x4];
    s32 attached;            /* 0x0C attach runs only while it is 0, detach only while it is set */
    u8 pad_10[0x14 - 0x10];
    union {
        u8 *bytes;
        Coord2 *coord;
    } pos;                   /* 0x14 its GsCOORDINATE2 (gs.h): position t, world position workT */
    u8 pad_18[0x24 - 0x18];
    u32 timer;               /* 0x24 cleared on waking; sleep mode >= 10 compares it with mode * 15 */
    s32 contact;               /* 0x28 result of the ground test after moveZOnGround */
    u8 pad_2C[0x44 - 0x2C];
    s32 state;               /* 0x44 handler state; 1 stops Entity_CheckWake for good */
    s16 speed;               /* 0x48 last amount given to moveX, moveY or moveZ (Actor_MoveAxis) */
    u8 pad_4A[0x4C - 0x4A];
    s32 map;                 /* 0x4C StageMap * (stage.h): third argument of attach, cleared by detach; slot 0x110 ground query */
    void *clock;             /* 0x50 */
    u8 pad_54[0x58 - 0x54];
    s32 soundBank;           /* 0x58 SoundBank *: the handler node's voices play on it (HandlerNode_Start, HandlerNode_Run) */
    u8 pad_5C[0x6C - 0x5C];
    s32 partCount;           /* 0x6C model parts (Model in src/game/model.c) */
    struct ModelPart **parts; /* 0x70 */
    u8 pad_74[0x7C - 0x74];
    s32 animation;           /* 0x7C current animation (setAnimation) */
    s32 animLength;          /* 0x80 frames of the current animation */
    s32 animFrame;           /* 0x84 current frame, 0 to animLength - 1 */
    u8 *animData;            /* 0x88 the next frame's commands (applyFrame) */
    s32 tickEnabled;         /* 0x8C */
    s32 animPlaying;         /* 0x90 playAnimation sets it, stopAnimation clears it */
    struct Entity *dreamSys; /* 0x94 the object passed to attach (g_symDreamSys, the DreamSys); range tests measure from it */
    s32 type;                /* 0x98 entity type, index of EntityRecord */
    HandlerNode handlerNode; /* 0x9C the record's handler (sound.h); its fadeSteps divides slot 0x148's range */
    s32 awake;               /* 0xF0 set by wake, cleared by sleep */
    s32 touched;             /* 0xF4 set by setTouched */
    s32 handlerActive;       /* 0xF8 set by startHandler, cleared by stopHandler */
    s32 handlerTicks;        /* 0xFC cleared by startHandler, counted by slot 0x11C */
    struct Fade *effect;     /* 0x100 a Fade (scene.h) made by Fade_Create: the Grey Man white flash */
    struct Fade *unk104;
} Entity;

/* Functions of src/game/entity.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Entity_Create(s32 type, s32 params, s32 soundBank);

#endif

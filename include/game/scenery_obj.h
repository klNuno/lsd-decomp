#ifndef GAME_SCENERY_OBJ_H
#define GAME_SCENERY_OBJ_H

#include "common.h"
#include "game/view.h"
#include "game/place.h"
#include "game/stage_map.h"
#include "game/actor.h"
#include "game/scenery_part.h"

/* The parameters g_sceneryParams holds for the next scenery object (copied whole by its init, Scenery_Reset). */
typedef struct SceneryParams {
    s32 x;        /* 0x00 offset from the origin: random +-22 tiles (<< 11) in Scenery_RandomizeParams */
    s32 y;        /* 0x04 */
    s32 z;        /* 0x08 */
    u8 *rotation;     /* 0x0C 12-byte entry of g_sceneryRotations */
    u8 *scale;    /* 0x10 12-byte entry of g_sceneryScales, or g_sceneryKind1Scale */
    s32 direction;    /* 0x14 rand() % 5 */
    s32 variant;    /* 0x18 */
    u8 *color;    /* 0x1C 3-byte entry of g_sceneryKind3Colors or g_sceneryKind2Colors */
    s32 altColor;    /* 0x20 kind 2 only: g_sceneryKind2AltColor or day number % 20 when that is 0, so always 0; a colour override part 1 would take instead of color */
} SceneryParams;

/*
 * A scenery object (class g_sceneryVtbl returned by Scenery_GetVtbl, 0x98 bytes, made by Scenery_New):
 * one of 4 kinds made around the dreamer at a place's first tick (Scenery_CreateAll, work/hunt6/F-findings.md).
 * Its base class is g_actorVtbl (constructor Actor_Init, 0x58 bytes).
 */
typedef struct SceneryVtbl {
    u8 pad_00[0x08];
    s32 (*init)();   /* 0x08 Scenery_Init */
    void (*destroy)();   /* 0x0C Scenery_Destruct */
    u8 pad_10[0x40 - 0x10];
    void (*reset)();       /* 0x40 Scenery_Reset */
    void (*setRotation)();
    void (*setScale)();
    void (*attach)();
    u8 pad_50[0xB8 - 0x50];
    void (*setPos)();     /* 0xB8 Actor_SetPos */
    void (*movePos)();    /* 0xBC Actor_MovePos */
    u8 pad_C0[0xEC - 0xC0];
    void (*update)();     /* 0xEC Scenery_Update */
} SceneryVtbl;

typedef struct Scenery {
    SceneryVtbl *vtbl;
    ListNode *watched;    /* 0x04 Actor's fields up to +0x54 (actor.h), under Actor's names */
    ListNode *watchers;   /* 0x08 */
    struct SceneNode *parent; /* 0x0C */
    DObj2 object;         /* 0x10 object.coord flg is cleared once moved */
    s32 id;               /* 0x1C */
    void *model;          /* 0x20 */
    u32 ticks;            /* 0x24 counted by update (Scenery_Update) */
    u8 pad_28[0x44 - 0x28];
    s32 state;            /* 0x44 cleared by the constructor */
    u8 pad_48[0x54 - 0x48];
    s32 kind;             /* 0x54 0 to 3 */
    Vec3 offset;          /* 0x58 params x, y, z: offset from the origin */
    u8 *rotation;         /* 0x64 params rotation */
    s16 *scale;           /* 0x68 params unk10 */
    s32 direction;            /* 0x6C params unk14, kind 0: direction 1 to 4 of its two parts */
    s32 variant;            /* 0x70 params unk18 */
    s32 color;            /* 0x74 params color (an RGB entry); kind 2 hands it to the same slot as dayMark */
    s32 altColor;
    union {
        Actor *pair[2];                                       /* 0x7C kind 0: Actors (Actor_New) */
        struct { u8 pad_7C[0x84 - 0x7C]; SceneryPart *parts[5]; } many; /* 0x84 kinds 2 and 3 */
    } u;
} Scenery;

/* Functions of src/game/scenery_obj.c that other files call or reference (docs/naming.md, Prototypes) */
Scenery *Scenery_New(s32 kind, SceneryParams *params, StageMap *map, Vec3 *origin);
void Scenery_SetPlaceRefs(s32 unused, Tmd *models, void *font, View *view);

#endif

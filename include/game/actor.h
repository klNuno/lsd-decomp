#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/model_object.h"
#include "game/render.h"

struct Actor;
struct StageMap;

/*
 * The Actor vtable g_actorVtbl (Actor_GetVtbl, 0xF0 bytes, in .data at 0x800878D4). Slots 0x00 to
 * 0xB4 are SceneNodeVtbl's (scene_node.h) under the same names, Actor's overrides noted;
 * 0xB8 on are Actor's own. Subclasses (Scenery, Model, DreamSys) chain to these slots.
 * Slots are left unprototyped like SceneNodeVtbl's.
 */
typedef struct ActorVtbl {
    u8 classByte;             /* 0x00 low byte of SceneNodeVtbl.classWord: 0x34 runs afterTouch on contact */
    u8 pad_01[0x04 - 0x01];
    void *(*delete_)();       /* 0x04 Object_Delete */
    void *(*init)();          /* 0x08 Actor_Init, returns the actor or NULL */
    void (*destroy)();        /* 0x0C SceneNode_Destroy */
    void (*watch)();          /* 0x10 Actor_Watch */
    void (*unwatch)();        /* 0x14 Actor_Unwatch */
    void (*unwatchAll)();     /* 0x18 Actor_UnwatchAll */
    void (*nextWatched)();    /* 0x1C Object_NextWatched */
    void (*addWatcher)();     /* 0x20 Object_AddWatcher */
    void (*removeWatcher)();  /* 0x24 Object_RemoveWatcher */
    void (*freeWatchers)();   /* 0x28 Object_FreeWatchers */
    void (*nextWatcher)();    /* 0x2C Object_NextWatcher */
    void (*notify)();         /* 0x30 Object_Notify */
    void (*unk34)();          /* 0x34 Object_EmptySlot34, empty */
    void (*onNotify)();       /* 0x38 SceneNode_OnNotify */
    void (*unk3C)();          /* 0x3C 0 */
    void (*reset)();          /* 0x40 Actor_Reset: speed 0x12C, boxMargin 0 */
    void (*setRotation)();    /* 0x44 SceneNode_SetRotation */
    void (*setScale)();       /* 0x48 SceneNode_SetScale */
    void (*attach)();         /* 0x4C SceneNode_Attach */
    void (*detach)();         /* 0x50 SceneNode_Detach */
    void (*detachChildren)(); /* 0x54 SceneNode_DetachChildren */
    void (*nextChild)();      /* 0x58 SceneNode_NextChild */
    void (*unk5C)();          /* 0x5C SceneNode_EmptySlot5C, empty */
    s32 (*setVisible)();      /* 0x60 SceneNode_SetVisible */
    void (*setSemiTrans)();   /* 0x64 SceneNode_SetSemiTrans */
    void (*setBlendRate)();   /* 0x68 SceneNode_SetBlendRate */
    void (*setLit)();         /* 0x6C SceneNode_SetLit */
    void (*setLightFlags)();  /* 0x70 SceneNode_SetLightFlags */
    void (*setDim)();         /* 0x74 SceneNode_SetDim */
    s32 (*setZSort)();        /* 0x78 SceneNode_SetZSort */
    void (*setDivision)();    /* 0x7C SceneNode_SetDivision */
    s32 (*setBackfaceClip)(); /* 0x80 SceneNode_SetBackfaceClip */
    void (*getRotMatrix)();   /* 0x84 SceneNode_GetRotMatrix */
    void (*sendBoxes)();      /* 0x88 Actor_SendBoxes (actor, message): -1 contact found, -2 none */
    void (*getBoxList)();     /* 0x8C SceneNode_GetBoxList */
    void (*sendShape)();      /* 0x90 SceneNode_SendShape */
    void (*onPad)();          /* 0x94 SceneNode_OnPad, empty */
    void (*onClock)();        /* 0x98 SceneNode_OnClock, empty */
    void (*onNode)();         /* 0x9C Actor_OnNode */
    void (*checkContact)();   /* 0xA0 SceneNode_CheckContact */
    void (*worldToLocal)();   /* 0xA4 SceneNode_WorldToLocal */
    s32 (*boxesOverlap)();    /* 0xA8 SceneNode_BoxesOverlap */
    s32 (*rayTestBoxes)();    /* 0xAC SceneNode_RayTestBoxes */
    void (*unkB0)();          /* 0xB0 0 */
    void (*unkB4)();          /* 0xB4 SceneNode_AddActorWatchers */
    void (*setPos)();         /* 0xB8 Actor_SetPos */
    void (*movePos)();        /* 0xBC Actor_MovePos */
    void (*moveLocal)();      /* 0xC0 Actor_MoveLocal */
    void (*moveZ)();          /* 0xC4 Actor_MoveZ */
    void (*moveX)();          /* 0xC8 Actor_MoveX */
    void (*moveY)();          /* 0xCC Actor_MoveY */
    void (*moveZOnGround)();  /* 0xD0 Actor_MoveZOnGround */
    void (*moveXOnGround)();  /* 0xD4 Actor_MoveXOnGround */
    void (*unkD8)();          /* 0xD8 Actor_EmptySlotD8, empty */
    void (*onActorContact)(); /* 0xDC Actor_OnActorContact: Actor_OnNode for a sender of class byte 0x34 */
    void (*onTileContact)();  /* 0xE0 Actor_OnTileContact: for a sender of class byte 0x24 (MapTile) */
    void (*setSpeed)();       /* 0xE4 Actor_SetSpeed */
    void (*afterTouch)();     /* 0xE8 Actor_EmptySlotE8; the contact's override runs after a 0x34 touch */
    void (*setBoxMargin)();   /* 0xEC Actor_SetBoxMargin */
} ActorVtbl;

/*
 * The base class of the scenery objects, their kind 0 parts, Model (so every Entity) and DreamSys:
 * vtable g_actorVtbl, constructor Actor_Init, 0x58 bytes (Actor_New). Fields up to +0x44 are
 * SceneNode's (scene_node.h) under the same names, with the vtable typed as ActorVtbl and contact
 * left untyped (an Actor or a MapTile).
 */
typedef struct Actor {
    ActorVtbl *vtbl;             /* 0x00 g_actorVtbl or a subclass's */
    ListNode *watched;           /* 0x04 SceneNode.watched */
    ListNode *watchers;          /* 0x08 */
    struct SceneNode *parent;    /* 0x0C */
    DObj2 object;                /* 0x10 SceneNode.object: coord flg is cleared after each move */
    s32 id;                      /* 0x1C */
    ModelObject *model;          /* 0x20 tested by ModelObject_GetBoxCount */
    s32 ticks;                   /* 0x24 */
    void *contact;               /* 0x28 the Actor or MapTile found by Actor_SnapToGround, 0 when none */
    s32 hitMask;                 /* 0x2C */
    NodeBoxList *boxList;        /* 0x30 */
    u8 pad_34[0x44 - 0x34];
    s32 state;                   /* 0x44 cleared by the constructor */
    s16 speed;                   /* 0x48 0x12C at init, last amount given to a move */
    u8 pad_4A[0x4C - 0x4A];
    struct StageMap *map;        /* 0x4C the watched object whose class id ends in 0x114 (the stage map) */
    void *clock;                 /* 0x50 the watched object whose class id ends in 5 (a clock) */
    s32 boxMargin;               /* 0x54 slot 0xEC */
} Actor;

ActorVtbl *Actor_GetVtbl(void);

/* Functions of src/game/actor.c that other files call or reference (docs/naming.md, Prototypes) */
void *Actor_New(void);
void Actor_Watch(Actor *actor, s32 **other);
void Actor_Unwatch(Actor *actor, s32 **other);
void Actor_UnwatchAll(Actor *actor);
void Actor_SendBoxes(Actor *actor, s32 message);
void Actor_OnNode(Actor *actor, u8 **sender);
void Actor_SetPos(void *actor, Vec3 *pos);
void Actor_MovePos(void *actor, Vec3 *delta);
void Actor_MoveLocal(Actor *actor, ModelVec *local);
void Actor_MoveZ(void *actor, s32 value, s32 notify);
void Actor_MoveX(void *actor, s32 value, s32 notify);
void Actor_MoveY(void *actor, s32 value, s32 notify);
void Actor_MoveZOnGround(Actor *actor, s32 value, s32 notify);
void Actor_MoveXOnGround(Actor *actor, s32 value, s32 notify);
void Actor_EmptySlotD8(void);
void Actor_OnActorContact(Actor *actor, void *sender, s32 message);
void Actor_OnTileContact(Actor *actor, void *sender, s32 message);
void Actor_SetSpeed(Actor *actor, s16 value);
void Actor_EmptySlotE8(void);
void Actor_SetBoxMargin(Actor *actor, s32 value);

#endif

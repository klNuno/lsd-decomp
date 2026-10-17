#ifndef GAME_SCENE_NODE_H
#define GAME_SCENE_NODE_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/model_object.h"
#include "game/entity.h"

struct DreamSys;

/* A {numerator, denominator} pair: scene node rotations in degrees and scales (Fraction_ToFixed). */
typedef struct Fraction {
    s16 num;
    s16 den;
} Fraction;

/* A scene node (vtable g_sceneNodeVtbl, class word 4, 0x44 bytes, src/game/scene_node.c; sender type 4):
   a GsDOBJ2 with a parent; View_DrawNode draws a tree of them. Slots are left unprototyped. */
typedef struct SceneNodeVtbl {
    s32 classWord;             /* 0x00 4: sender type scene node */
    void *(*delete_)();       /* 0x04 Object_Delete */
    void *(*init)();          /* 0x08 SceneNode_Init, returns the node or NULL */
    void (*destroy)();        /* 0x0C SceneNode_Destroy */
    void (*watch)();          /* 0x10 SceneNode_Watch */
    void (*unwatch)();        /* 0x14 SceneNode_Unwatch */
    void (*unwatchAll)();     /* 0x18 SceneNode_UnwatchAll */
    void (*nextWatched)();    /* 0x1C Object_NextWatched */
    void (*addWatcher)();     /* 0x20 Object_AddWatcher */
    void (*removeWatcher)();  /* 0x24 Object_RemoveWatcher */
    void (*freeWatchers)();   /* 0x28 Object_FreeWatchers */
    void (*nextWatcher)();    /* 0x2C Object_NextWatcher */
    void (*notify)();         /* 0x30 Object_Notify */
    void (*unk34)();          /* 0x34 Object_EmptySlot34, empty */
    void (*onNotify)();       /* 0x38 SceneNode_OnNotify */
    void (*unk3C)();          /* 0x3C 0 */
    void (*reset)();          /* 0x40 SceneNode_Reset */
    void (*setRotation)();    /* 0x44 SceneNode_SetRotation (node, assign, Fraction[3] degrees) */
    void (*setScale)();       /* 0x48 SceneNode_SetScale (node, assign, Fraction[3]) */
    void (*attach)();         /* 0x4C SceneNode_Attach (node, parent, position) */
    void (*detach)();         /* 0x50 SceneNode_Detach */
    void (*detachChildren)(); /* 0x54 SceneNode_DetachChildren */
    void (*nextChild)();      /* 0x58 SceneNode_NextChild (node, &child, &iter) */
    void (*unk5C)();          /* 0x5C SceneNode_EmptySlot5C, empty */
    s32 (*setVisible)();      /* 0x60 SceneNode_SetVisible, GsDOFF */
    void (*setSemiTrans)();   /* 0x64 SceneNode_SetSemiTrans, GsALON */
    void (*setBlendRate)();   /* 0x68 SceneNode_SetBlendRate, GsAZERO to GsATHREE */
    void (*setLit)();         /* 0x6C SceneNode_SetLit, GsLOFF */
    void (*setLightFlags)();  /* 0x70 SceneNode_SetLightFlags, GsFOG, GsMATE, GsLLMOD */
    void (*setDim)();         /* 0x74 SceneNode_SetDim, GsLDIM0 to GsLDIM7 */
    s32 (*setZSort)();        /* 0x78 SceneNode_SetZSort, GsZIGNR */
    void (*setDivision)();    /* 0x7C SceneNode_SetDivision, GsDIV1 to GsDIV5 */
    s32 (*setBackfaceClip)(); /* 0x80 SceneNode_SetBackfaceClip, GsNBACKC */
    void (*getRotMatrix)();   /* 0x84 SceneNode_GetRotMatrix (node, matrix, invert) */
    void (*sendBoxes)();      /* 0x88 SceneNode_SendBoxes (node, message) */
    void (*getBoxList)();     /* 0x8C SceneNode_GetBoxList (node, box list) */
    void (*sendShape)();      /* 0x90 SceneNode_SendShape (node, box list, message) */
    void (*onPad)();          /* 0x94 SceneNode_OnPad, empty: messages of a pad (sender type 2) */
    void (*onClock)();        /* 0x98 SceneNode_OnClock, empty: messages of a clock (sender type 5) */
    void (*onNode)();         /* 0x9C SceneNode_OnNode: messages of another node (sender type 4) */
    void (*checkContact)();   /* 0xA0 SceneNode_CheckContact (node, sender) */
    void (*worldToLocal)();   /* 0xA4 SceneNode_WorldToLocal (node, offset, dst, src, count) */
    s32 (*boxesOverlap)();    /* 0xA8 SceneNode_BoxesOverlap (node, box list, offset) */
    s32 (*rayTestBoxes)();    /* 0xAC SceneNode_RayTestBoxes (node, &sender hit mask, hit position, box list) */
    void (*unkB0)();          /* 0xB0 SceneNode_EmptySlotB0, empty */
    void (*unkB4)();          /* 0xB4 SceneNode_AddActorWatchers */
} SceneNodeVtbl;

typedef struct SceneNode {
    SceneNodeVtbl *vtbl;
    ListNode *watched;           /* 0x04 objects this one watches: its children among them */
    ListNode *watchers;          /* 0x08 */
    struct SceneNode *parent; /* 0x0C */
    s32 attribute;               /* 0x10 GsDOBJ2.attribute: bit 31 GsDOFF hides the node */
    Coord2 *coord;               /* 0x14 GsDOBJ2.coord2: a view watching the node takes it as super */
    ModelEntry *tmd;             /* 0x18 GsDOBJ2.tmd: the model object's TMD object */
    s32 id;                      /* 0x1C GsDOBJ2.id */
    ModelObject *model;          /* 0x20 the watched model object (sender type 9) */
    s32 ticks;                   /* 0x24 cleared by reset */
    struct SceneNode *contact; /* 0x28 the last node that hit this one (message 4) */
    s32 hitMask;                 /* 0x2C boxes hit by the last test, one bit per box */
    NodeBoxList *boxList;        /* 0x30 the box list being sent, NULL otherwise */
    u8 pad_34[0x44 - 0x34];
} SceneNode;

/* Functions of src/game/scene_node.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/scene_node.c */
SceneNode *SceneNode_New(void);
void SceneNode_Destroy(SceneNode *node);
void SceneNode_Watch(SceneNode *node, Object *other);
void SceneNode_Unwatch(SceneNode *node, Object *other);
void SceneNode_UnwatchAll(SceneNode *node);
void SceneNode_OnNotify(SceneNode *node, Object *sender, s32 message);
void SceneNode_SetRotation(SceneNode *node, s32 assign, Fraction *degrees);
void SceneNode_SetScale(SceneNode *node, s32 assign, Fraction *factors);
SceneNode *SceneNode_Attach(SceneNode *node, SceneNode *parent, Vec3 *pos);
SceneNode *SceneNode_Detach(SceneNode *node);
void SceneNode_DetachChildren(SceneNode *node);
void SceneNode_NextChild(SceneNode *node, SceneNode **child, ListNode **iter);
void SceneNode_EmptySlot5C(void);
s32 SceneNode_SetVisible(SceneNode *node, s32 visible);
void SceneNode_SetSemiTrans(SceneNode *node, s32 semiTrans);
void SceneNode_SetBlendRate(SceneNode *node, s32 rate);
void SceneNode_SetLit(SceneNode *node, s32 lit);
void SceneNode_SetLightFlags(SceneNode *node, s32 flags);
void SceneNode_SetDim(SceneNode *node, s32 dim);
s32 SceneNode_SetZSort(SceneNode *node, s32 zSort);
void SceneNode_SetDivision(SceneNode *node, s32 division);
s32 SceneNode_SetBackfaceClip(SceneNode *node, s32 backfaceClip);
void SceneNode_GetRotMatrix(SceneNode *node, void *matrix, s32 invert);
void SceneNode_SendBoxes(SceneNode *node, s32 message);
void SceneNode_GetBoxList(SceneNode *node, NodeBoxList *boxList);
void SceneNode_SendShape(SceneNode *node, NodeBoxList *boxList, s32 message);
void SceneNode_OnPad(void);
void SceneNode_OnClock(void);
void SceneNode_OnNode(SceneNode *node, SceneNode *sender, s32 message);
void SceneNode_CheckContact(SceneNode *node, SceneNode *sender);
void SceneNode_WorldToLocal(SceneNode *node, ModelVec *offset, ModelVec *dst, ModelVec *src, s32 count);
s32 SceneNode_BoxesOverlap(SceneNode *node, NodeBoxList *boxList, ModelVec *offset);
s32 SceneNode_RayTestBoxes(SceneNode *node, s32 *senderHits, ModelVec *hitPos, NodeBoxList *boxList);
void SceneNode_EmptySlotB0(void);
void SceneNode_AddActorWatchers(s32 node, Object *object);
void SceneNode_RotateVector(SceneNode *node, Vec3 *dst, ModelVec *src);
void SceneNode_LocalToWorld(); /* unprototyped: dream_sys.c and sym.c pass a fourth argument */
void SceneNode_GetRotation(SceneNode *node, Fraction *degrees);
void SceneNode_LinkModel(SceneNode *node, ModelObject *model);
s32 SceneNode_ProbeHeight(); /* unprototyped: actor.c calls it with no arguments */
void SceneNode_TurnToward(Entity *entity, struct DreamSys *target, s32 noPitch, s32 facing, Fraction *extra);
s32 Bits_SetField(s32 *word, s32 shift, s32 width, s32 value);
void Render_TransformLongVectors(Vec3 *dstVecs, Vec3 *srcVecs, s32 count, Matrix *matrix);
s32 Entity_IsWithinBox(s32 *center, s32 range, s32 *pos);
s32 SceneNode_SetRayHeightCheck(s32 enable);

#endif

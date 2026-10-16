#include "common.h"
#include "game/heap.h"
#include "game/entity.h"

/*
 * Scene nodes: the class of vtable g_sceneNodeVtbl (SceneNode_GetVtbl, tag 4, 0x44 bytes, made by
 * SceneNode_New). DreamSys, Model (so every Entity), map tiles, the Bg, effects and the
 * actors of a place derive from it: their vtables reuse its slots.
 * A node is an Object that carries a PSY-Q GsDOBJ2 at +0x10 (attribute, coordinate, TMD)
 * and hangs from a parent node: the parent watches its children, and the node's
 * GsCOORDINATE2 takes the parent's as super.
 * Collisions: a node sends its box list to its watchers (message 2 or 3); each watcher
 * brings the boxes into its own frame, tests them against its model's box, then casts
 * rays along their edges, and tells the sender message 4 on a hit.
 */

/* A PSY-Q SVECTOR: three shorts and a pad. */
typedef struct SVector {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVector;

/* Three shorts: a box corner, a point of a ray. */
typedef struct SVec3 {
    s16 x;
    s16 y;
    s16 z;
} SVec3;

/* An axis-aligned box: min and max corners (ModelObject_GetBox, the ray tests). */
typedef struct NodeBox {
    SVec3 min;
    SVec3 max;
} NodeBox;

/* A box list (ModelObject_GetBoxList): a count of boxes, then 8 corners per box (0x30 bytes). */
typedef struct NodeBoxList {
    s32 count;
    SVec3 corners[8];
    s32 pad_34;
} NodeBoxList;

/* PSY-Q GsCOORD2PARAM, 0x28 bytes, allocated by SceneNode_Init. */
typedef struct NodeCoordParam {
    s32 scale[4];   /* 0x00 VECTOR, 4096 = 1.0 (SceneNode_SetScale) */
    SVector rotate; /* 0x10 SVECTOR, 4096 = 360 degrees (SceneNode_SetRotation) */
    s32 trans[4];   /* 0x18 VECTOR */
} NodeCoordParam;

/* PSY-Q GsCOORDINATE2, 0x50 bytes, allocated by SceneNode_Init. */
typedef struct NodeCoord {
    s32 flg;                 /* 0x00 cleared after each change, 1 after reset */
    s16 m[3][3];             /* 0x04 coord: local matrix */
    u8 pad_16[0x18 - 0x16];
    Vec3 t;                  /* 0x18 position relative to the parent */
    s16 workm[3][3];         /* 0x24 workm: world matrix */
    u8 pad_36[0x38 - 0x36];
    Vec3 workT;              /* 0x38 world position */
    NodeCoordParam *param;   /* 0x44 */
    struct NodeCoord *super; /* 0x48 the parent's coordinate */
    struct NodeCoord *sub;   /* 0x4C */
} NodeCoord;

/* A one-entry fraction, num / den; three of them give a rotation in degrees or a scale. */
typedef struct Fraction {
    s16 num;
    s16 den;
} Fraction;

/* The view of a model object (src/game/8001F250.c) this unit needs: its TMD object. */
typedef struct ModelObject {
    u8 pad_00[0xC];
    s32 tmdObjectBase; /* 0x0C tmdObject - 0xC */
    s32 tmdObject;     /* 0x10 address of the TMD object entry */
} ModelObject;

/* Vtable g_sceneNodeVtbl; the Object slots 0x04 to 0x38 as in heap.h. Slots are left unprototyped. */
typedef struct SceneNodeVtbl {
    s32 tag;                  /* 0x00 4: sender type scene node */
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
    void (*unk34)();          /* 0x34 func_80018350, empty */
    void (*onNotify)();       /* 0x38 SceneNode_OnNotify */
    void (*unk3C)();          /* 0x3C 0 */
    void (*reset)();          /* 0x40 SceneNode_Reset */
    void (*setRotation)();    /* 0x44 SceneNode_SetRotation (node, assign, Fraction[3] degrees) */
    void (*setScale)();       /* 0x48 SceneNode_SetScale (node, assign, Fraction[3]) */
    void (*attach)();         /* 0x4C SceneNode_Attach (node, parent, position) */
    void (*detach)();         /* 0x50 SceneNode_Detach */
    void (*detachChildren)(); /* 0x54 SceneNode_DetachChildren */
    void (*nextChild)();      /* 0x58 SceneNode_NextChild (node, &child, &iter) */
    void (*unk5C)();          /* 0x5C func_8001D33C, empty */
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
    void (*unkB0)();          /* 0xB0 func_8001E49C, empty */
    void (*unkB4)();          /* 0xB4 func_8001E4A4 */
} SceneNodeVtbl;

typedef struct SceneNodeObj {
    SceneNodeVtbl *vtbl;
    ListNode *watched;           /* 0x04 objects this one watches: its children among them */
    ListNode *watchers;          /* 0x08 */
    struct SceneNodeObj *parent; /* 0x0C */
    s32 attribute;               /* 0x10 GsDOBJ2.attribute: bit 31 GsDOFF hides the node */
    NodeCoord *coord;            /* 0x14 GsDOBJ2.coord2 */
    s32 tmd;                     /* 0x18 GsDOBJ2.tmd */
    s32 id;                      /* 0x1C GsDOBJ2.id */
    ModelObject *model;          /* 0x20 the watched model object (sender type 9) */
    s32 unk24;                   /* 0x24 cleared by reset */
    struct SceneNodeObj *contact; /* 0x28 the last node that hit this one (message 4) */
    s32 hitMask;                 /* 0x2C boxes hit by the last test, one bit per box */
    s32 *boxList;                /* 0x30 the box list being sent, NULL otherwise */
    u8 pad_34[0x44 - 0x34];
} SceneNodeObj;

/* Message a node sends to the node it hit, and that the hit node keeps as contact. */
#define NODE_MSG_CONTACT 4

void *Heap_Alloc(s32 size);
void Heap_Free(void *block);
ObjectVtbl *Object_GetBaseVtbl(void);
void Object_NextWatcher(Object *self, s32 *value, s32 *more);
void List_Next(s32 *value, ListNode **iter);
SceneNodeVtbl *SceneNode_GetVtbl(void);
void SceneNode_LinkModel(SceneNodeObj *node, ModelObject *model);
void SceneNode_UnlinkModel(SceneNodeObj *node);
s32 Fraction_ToFixed(Fraction *fraction);
s32 ModelBox_OutCode(NodeBox *box, SVec3 *point);
s32 Bits_SetField(s32 *word, s32 shift, s32 width, s32 value);
s32 ModelBox_ClipSegment(SVec3 *out, NodeBox *box, SVec3 *start, SVec3 *end);
void ModelBox_FindExit(SVec3 *out, NodeBox *box, SVec3 *inside, SVec3 *outside);
void func_8001EA8C(Vec3 *out, SVec3 *from, SVec3 *to);
void Render_TransformLongVectors(void *dstVecs, void *srcVecs, s32 count, s32 *matrix);
void Render_TransformVectors(SVec3 *dst, SVec3 *src, s32 count, void *matrix);
s32 ModelObject_IsReady(ModelObject *model);
void ModelObject_UpdateBox(ModelObject *model);
NodeBox *ModelObject_GetBox(ModelObject *model, s32 index);
void ModelObject_GetBoxList(ModelObject *model, s32 *boxList);
s32 ModelObject_RayTest(ModelObject *model, s32 *hitDist, SVec3 *hitPos, s32 *hitHeight, SVec3 *start, SVec3 *end);
void GsInitCoordinate2(NodeCoord *super, NodeCoord *coord);
extern void GsLinkObject4(u32 *src, void *dst, s32 id);
void RotMatrix(SVector *r, void *m);
void MulMatrix2(s32 *m0, s32 *m1);
void ApplyMatrixSV(void *, SVec3 *, SVec3 *);
void ApplyMatrixLV(s32 *, void *, void *);
s32 ratan2(s32, s32);

extern s32 g_sceneNodeVtbl[];
extern s32 g_nodeZeroRotation[];
extern s32 g_nodeUnitScale[];
s32 g_rayHeightCheck;

/* The class head of func_8001E4A4's watchers: a tag byte and the watch slot. */
typedef struct WatcherVtbl {
    u8 tag;
    u8 pad_01[0xF];
    void (*watch)(Object *, s32);
} WatcherVtbl;

/* New scene node: 0x44 bytes from the heap, initialized through slot 0x08. */
SceneNodeObj *SceneNode_New(void) {
    SceneNodeObj *node;

    node = Heap_Alloc(0x44);
    if (node == NULL) {
        return NULL;
    }
    if (SceneNode_GetVtbl()->init(node) != NULL) {
        return node;
    }
    Heap_Free(node);
    return NULL;
}

/* Slot 0x08: allocates the GsCOORDINATE2 and its GsCOORD2PARAM, then resets the node. */
SceneNodeObj *SceneNode_Init(SceneNodeObj *node) {
    NodeCoord *coord;
    NodeCoordParam *param;

    coord = Heap_Alloc(0x50);
    node->coord = coord;
    if (coord != NULL) {
        param = Heap_Alloc(0x28);
        node->coord->param = param;
        if (param != NULL) {
            Object_GetBaseVtbl()->init(node);
            node->vtbl = SceneNode_GetVtbl();
            node->model = NULL;
            node->tmd = 0;
            node->parent = NULL;
            node->coord->super = NULL;
            node->vtbl->reset(node);
            return node;
        }
        Heap_Free(node->coord);
    }
    return NULL;
}

/* Slot 0x0C: leaves the parent, drops the children, frees the coordinate. */
void SceneNode_Destroy(SceneNodeObj *node) {
    node->vtbl->detach(node);
    node->vtbl->detachChildren(node);
    node->vtbl->unk5C(node, 0);
    Heap_Free(node->coord->param);
    Heap_Free(node->coord);
    Object_GetBaseVtbl()->destroy(node);
}

/* Slot 0x10: watching a model object (sender type 9) links its TMD object to the GsDOBJ2. */
void SceneNode_Watch(SceneNodeObj *node, Object *other) {
    Object_GetBaseVtbl()->watch(node, other);
    if ((other->vtbl->unk_00 & 0xF) == 9) {
        SceneNode_LinkModel(node, (ModelObject *)other);
    }
}

/* Slot 0x14 */
void SceneNode_Unwatch(SceneNodeObj *node, Object *other) {
    if ((other->vtbl->unk_00 & 0xF) == 9) {
        SceneNode_UnlinkModel(node);
    }
    Object_GetBaseVtbl()->unwatch(node, other);
}

/* Slot 0x18 */
void SceneNode_UnwatchAll(SceneNodeObj *node) {
    SceneNode_UnlinkModel(node);
    Object_GetBaseVtbl()->unwatchAll(node);
}

/* Slot 0x38: dispatches on the sender type: 2 pad, 5 clock, 4 scene node. */
void SceneNode_OnNotify(SceneNodeObj *node, Object *sender, s32 message) {
    s32 senderType;

    Object_GetBaseVtbl()->onNotify(node, sender, message);
    senderType = sender->vtbl->unk_00 & 0xF;
    if (senderType == 2) {
        node->vtbl->onPad(node, sender, message);
    } else if (senderType == 5) {
        node->vtbl->onClock(node, sender, message);
    } else if (senderType == 4) {
        node->vtbl->onNode(node, sender, message);
    }
}

/* Slot 0x40: no parent coordinate, rotation 0, scale 1 (g_nodeZeroRotation and g_nodeUnitScale are Fraction[3]). */
void SceneNode_Reset(SceneNodeObj *node) {
    node->unk24 = 0;
    node->attribute = 0;
    GsInitCoordinate2(0, node->coord);
    node->vtbl->setRotation(node, 1, g_nodeZeroRotation);
    node->vtbl->setScale(node, 1, g_nodeUnitScale);
    node->coord->flg = 1;
}

/* Slot 0x44: sets (assign != 0) or adds the rotation, three fractions of degrees. */
void SceneNode_SetRotation(SceneNodeObj *node, s32 assign, Fraction *degrees) {
    s32 angles[3];
    s32 i;
    NodeCoordParam *param;
    s16 *p;
    s16 *cur;

    angles[0] = Fraction_ToFixed(degrees);
    angles[1] = Fraction_ToFixed(degrees + 1);
    angles[2] = Fraction_ToFixed(degrees + 2);
    angles[0] /= 0x168;
    angles[1] /= 0x168;
    angles[2] /= 0x168;
    param = node->coord->param;
    p = &param->rotate.vx;
    if (assign != 0) {
        param->rotate.vx = angles[0];
        param->rotate.vy = angles[1];
        param->rotate.vz = angles[2];
    } else {
        for (i = 0; i < 3; i++) {
            cur = p;
            p = cur + 1;
            *cur = (*cur + angles[i]) % 0x1000;
        }
    }
    node->coord->flg = 0;
}

/* Slot 0x48: sets (assign != 0) or adds the scale, three fractions. */
void SceneNode_SetScale(SceneNodeObj *node, s32 assign, Fraction *factors) {
    s32 x;
    s32 y;
    s32 z;
    s32 *scale;

    x = Fraction_ToFixed(factors);
    y = Fraction_ToFixed(factors + 1);
    z = Fraction_ToFixed(factors + 2);
    scale = node->coord->param->scale;
    if (assign != 0) {
        scale[0] = (s16)x;
        scale[1] = (s16)y;
        scale[2] = (s16)z;
    } else {
        scale[0] = (s16)x + scale[0];
        scale[1] = (s16)y + scale[1];
        scale[2] = (s16)z + scale[2];
    }
    node->coord->flg = 0;
}

/* Slot 0x4C: hangs the node from parent at pos (or at the parent's origin); the parent watches it. */
SceneNodeObj *SceneNode_Attach(SceneNodeObj *node, SceneNodeObj *parent, Vec3 *pos) {
    NodeCoord *coord;

    if (node->parent == NULL) {
        node->parent = parent;
        node->coord->super = parent->coord;
        parent->vtbl->watch(parent, node);
        coord = node->coord;
        if (pos != NULL) {
            coord->t.x = pos->x;
            coord->t.y = pos->y;
            coord->t.z = pos->z;
        } else {
            coord->t.x = 0;
            coord->t.y = 0;
            coord->t.z = 0;
        }
        node->coord->flg = 0;
    }
    return node;
}

/* Slot 0x50 */
SceneNodeObj *SceneNode_Detach(SceneNodeObj *node) {
    SceneNodeObj *parent;

    parent = node->parent;
    if (parent != NULL) {
        parent->vtbl->unwatch(parent, node);
        node->coord->super = NULL;
        node->parent = NULL;
    }
    return node;
}

/* Slot 0x54 */
void SceneNode_DetachChildren(SceneNodeObj *node) {
    SceneNodeObj *child;
    s32 more;

    child = NULL;
    do {
        node->vtbl->nextChild(node, &child, &more);
        if (child != NULL) {
            child->vtbl->detach(child);
        }
    } while (more != 0);
}

/* Slot 0x58: the next watched scene node whose parent is this node, NULL at the end. */
void SceneNode_NextChild(SceneNodeObj *node, SceneNodeObj **child, ListNode **iter) {
    SceneNodeObj *obj;

    do {
        if (*child == NULL) {
            *iter = node->watched;
        }
        List_Next((s32 *)child, iter);
        obj = *child;
        if (obj != NULL && (obj->vtbl->tag & 0xF) == 4 && obj->parent == node) {
            return;
        }
    } while (*iter != NULL);
    *child = NULL;
}

void func_8001D33C(void) {
}

/* Slots 0x60 to 0x80 set the GsDOBJ2 attribute bits (PSY-Q libgs.h names). */

/* Slot 0x60: GsDOFF = !visible, returns whether the node was visible. */
s32 SceneNode_SetVisible(SceneNodeObj *node, s32 visible) {
    return Bits_SetField(&node->attribute, 0x1F, 1, visible == 0) == 0;
}

/* Slot 0x64: GsALON */
void SceneNode_SetSemiTrans(SceneNodeObj *node, s32 semiTrans) {
    Bits_SetField(&node->attribute, 0x1E, 1, semiTrans != 0);
}

/* Slot 0x68: semi-transparency rate, GsAZERO to GsATHREE */
void SceneNode_SetBlendRate(SceneNodeObj *node, s32 rate) {
    Bits_SetField(&node->attribute, 0x1C, 2, rate);
}

/* Slot 0x6C: GsLOFF = !lit */
void SceneNode_SetLit(SceneNodeObj *node, s32 lit) {
    Bits_SetField(&node->attribute, 6, 1, lit == 0);
}

/* Slot 0x70: GsFOG, GsMATE and GsLLMOD as one 3-bit value */
void SceneNode_SetLightFlags(SceneNodeObj *node, s32 flags) {
    Bits_SetField(&node->attribute, 3, 3, flags);
}

/* Slot 0x74: GsLDIM0 to GsLDIM7 */
void SceneNode_SetDim(SceneNodeObj *node, s32 dim) {
    Bits_SetField(&node->attribute, 0, 3, dim);
}

/* Slot 0x78: GsZIGNR = !value, returns the previous value */
s32 SceneNode_SetZSort(SceneNodeObj *node, s32 zSort) {
    return Bits_SetField(&node->attribute, 7, 1, zSort == 0) == 0;
}

/* Slot 0x7C: polygon division, GsDIV1 to GsDIV5 */
void SceneNode_SetDivision(SceneNodeObj *node, s32 division) {
    Bits_SetField(&node->attribute, 9, 3, division);
}

/* Slot 0x80: GsNBACKC = !value, returns the previous value */
s32 SceneNode_SetBackfaceClip(SceneNodeObj *node, s32 backfaceClip) {
    return Bits_SetField(&node->attribute, 8, 1, backfaceClip == 0) == 0;
}

/* Slot 0x84: the rotation matrix of the node's own rotation, or of its inverse angles. */
void SceneNode_GetRotMatrix(SceneNodeObj *node, void *matrix, s32 invert) {
    SVector rot;
    NodeCoordParam *param;

    param = node->coord->param;
    if (invert != 0) {
        rot.vx = -param->rotate.vx;
        rot.vy = -param->rotate.vy;
        rot.vz = -param->rotate.vz;
    } else {
        rot = param->rotate;
    }
    RotMatrix(&rot, matrix);
}

/* Slot 0x88: for messages 2 and 3, sends the model's box list to the watchers. */
void SceneNode_SendBoxes(SceneNodeObj *node, s32 message) {
    s32 boxList[14];
    ModelObject *model;

    if (message < 4) {
        if (message >= 2) {
            model = node->model;
            if ((model != NULL) && (ModelObject_IsReady(model) != 0)) {
                node->vtbl->getBoxList(node, boxList);
                node->vtbl->sendShape(node, boxList, message);
            }
        }
    }
}

/* Slot 0x8C: the model's box list: one box, 8 corners. */
void SceneNode_GetBoxList(SceneNodeObj *node, s32 *boxList) {
    ModelObject_GetBoxList(node->model, boxList);
}

/* Slot 0x90: moves the box list into world space and notifies the watchers with it. */
void SceneNode_SendShape(SceneNodeObj *node, s32 *boxList, s32 message) {
    Render_TransformVectors((SVec3 *)(boxList + 1), (SVec3 *)(boxList + 1), boxList[0] * 8, &node->coord->workm);
    node->contact = NULL;
    node->hitMask = 0;
    node->boxList = boxList;
    node->vtbl->notify(node, message);
    node->boxList = NULL;
}

void SceneNode_OnPad(void) {
}

void SceneNode_OnClock(void) {
}

/* Slot 0x9C: messages 2 and 3 run the contact test against the sender, 4 records a hit. */
void SceneNode_OnNode(SceneNodeObj *node, SceneNodeObj *sender, s32 message) {
    switch (message) {
        case 2:
        case 3:
            node->vtbl->checkContact(node, sender, message);
            break;
        case NODE_MSG_CONTACT:
            node->contact = sender;
            break;
    }
}

/*
 * Slot 0xA0: tests the box list the sender is sending against this node's model. Within
 * 0x4000 on each axis, the sender's boxes are brought into this node's frame, then a box
 * overlap and the ray tests must both pass: the sender becomes the contact and gets message 4.
 */
void SceneNode_CheckContact(SceneNodeObj *node, SceneNodeObj *sender) {
    Vec3 offset;
    u16 localOffset[3];
    u8 unused[0x20];
    NodeBoxList boxes;
    Vec3 *senderPos;
    Vec3 *pos;
    s32 *corners;

    if (node->model != NULL && ModelObject_IsReady(node->model) != 0) {
        senderPos = NULL;
        if (sender->parent != NULL) {
            senderPos = &sender->coord->workT;
        }
        offset = *senderPos;
        pos = NULL;
        if (node->parent != NULL) {
            pos = &node->coord->workT;
        }
        offset.x -= pos->x;
        offset.y -= pos->y;
        offset.z -= pos->z;
        if ((offset.x >= 0 ? offset.x < 0x4001 : ~offset.x + 1 < 0x4001)
         && (offset.y >= 0 ? offset.y < 0x4001 : ~offset.y + 1 < 0x4001)
         && (offset.z >= 0 ? offset.z < 0x4001 : ~offset.z + 1 < 0x4001)) {
            localOffset[0] = offset.x;
            localOffset[1] = offset.y;
            localOffset[2] = offset.z;
            boxes.count = *sender->boxList;
            corners = sender->boxList + 1;
            node->vtbl->worldToLocal(node, localOffset, boxes.corners, corners, boxes.count * 8);
            if (node->vtbl->boxesOverlap(node, &boxes, localOffset) != 0
             && node->vtbl->rayTestBoxes(node, &sender->hitMask, localOffset, &boxes) != 0) {
                node->contact = sender;
                sender->vtbl->onNotify(sender, node, NODE_MSG_CONTACT);
            }
        }
    }
}

/*
 * Slot 0xA4: rotates count short vectors from world axes into the node's axes (the inverse
 * rotations of the node and of every parent), and the offset with them when there is one.
 */
void SceneNode_WorldToLocal(SceneNodeObj *node, SVec3 *offset, SVec3 *dst, SVec3 *src, s32 count) {
    s32 parentMtx[8];
    s32 worldMtx[8];
    SceneNodeObj *parent;

    node->vtbl->getRotMatrix(node, worldMtx, 1);
    for (parent = node->parent; parent != NULL; parent = parent->parent) {
        parent->vtbl->getRotMatrix(parent, parentMtx, 1);
        MulMatrix2(parentMtx, worldMtx);
    }
    Render_TransformVectors(dst, src, count, worldMtx);
    if (offset != NULL) {
        Render_TransformVectors(offset, offset, 1, worldMtx);
    }
}

/*
 * Slot 0xA8: moves the box list by offset and tests the bounding box of all its corners
 * against the bounding box of the node model's boxes.
 */
s32 SceneNode_BoxesOverlap(SceneNodeObj *node, NodeBoxList *boxList, SVec3 *offset) {
    NodeBox own;
    NodeBox other;
    u8 *end;
    SVec3 *p;
    NodeBox *box;
    NodeBox *b;
    NodeBox *bend;
    s32 n;

    p = &boxList->corners[0];
    end = (u8 *)p + boxList->count * 0x30;
    boxList->corners[0].x += offset->x;
    boxList->corners[0].y += offset->y;
    boxList->corners[0].z += offset->z;
    own.min = boxList->corners[0];
    own.max = boxList->corners[0];
    box = &own;
    for (p = &boxList->corners[1]; (u8 *)p < end; p++) {
        p->x += offset->x;
        p->y += offset->y;
        p->z += offset->z;
        box->min.x = (box->min.x < p->x) ? box->min.x : p->x;
        box->min.y = (box->min.y < p->y) ? box->min.y : p->y;
        box->min.z = (box->min.z < p->z) ? box->min.z : p->z;
        box->max.x = (box->max.x > p->x) ? box->max.x : p->x;
        box->max.y = (box->max.y > p->y) ? box->max.y : p->y;
        box->max.z = (box->max.z > p->z) ? box->max.z : p->z;
    }

    ModelObject_UpdateBox(node->model);
    b = ModelObject_GetBox(node->model, 0);
    n = ModelObject_IsReady(node->model);
    other = *b;
    bend = b + n;
    for (b++; b < bend; b++) {
        other.min.x = (other.min.x < b->min.x) ? other.min.x : b->min.x;
        other.min.y = (other.min.y < b->min.y) ? other.min.y : b->min.y;
        other.min.z = (other.min.z < b->min.z) ? other.min.z : b->min.z;
        other.max.x = (other.max.x > b->max.x) ? other.max.x : b->max.x;
        other.max.y = (other.max.y > b->max.y) ? other.max.y : b->max.y;
        other.max.z = (other.max.z > b->max.z) ? other.max.z : b->max.z;
    }

    return (own.min.z <= other.max.z) && (own.max.z >= other.min.z) &&
           (own.min.x <= other.max.x) && (own.max.x >= other.min.x) &&
           (own.min.y <= other.max.y) && (own.max.y >= other.min.y);
}

/*
 * Slot 0xAC: ray tests of the sender's boxes against the node model's boxes. First the
 * segment between the centres of the first box's two z faces; on a miss, the edges of
 * corners 1 and 2 to corners 5 and 6 of every box. A box of the model hit sets its bit in
 * node->hitMask, a sender box that hit sets its bit in *senderHits. With g_rayHeightCheck set,
 * a hit counts only when the ray test's height output is 0x201 or more (always for edges).
 */
s32 SceneNode_RayTestBoxes(SceneNodeObj *node, s32 *senderHits, SVec3 *hitPos, NodeBoxList *boxList) {
    SVec3 axis[2];
    NodeBox unused[2];
    s32 hitDist;
    s32 hitHeight;
    SVec3 *p;
    SVec3 *q;
    SVec3 *dst;
    s32 count;
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    NodeBox *box;

    hitDist = 0x7FFFFFFF;
    p = &boxList->corners[0];
    q = &boxList->corners[2];
    for (dst = axis; dst < axis + 2; dst++) {
        dst->x = (p->x + q->x) >> 1;
        dst->y = (p->y + q->y) >> 1;
        dst->z = (p->z + q->z) >> 1;
        p += 4;
        q += 4;
    }

    node->hitMask = 0;
    count = ModelObject_IsReady(node->model);
    ret = 0;
    for (i = 0; i < count; i++) {
        box = ModelObject_GetBox(node->model, i);
        if (ModelBox_ClipSegment(0, box, axis, axis + 1) != 0 &&
            ModelObject_RayTest(node->model, &hitDist, hitPos, &hitHeight, axis, axis + 1) != 0) {
            if (g_rayHeightCheck == 0) {
                node->hitMask |= 1 << i;
            } else if (hitHeight >= 0x201) {
                node->hitMask |= 1 << i;
            }
        }
    }

    if (node->hitMask != 0) {
        *senderHits = 1;
        if (ret != 0) {
            return 2;
        }
        return 1;
    }

    *senderHits = 0;
    n = boxList->count;
    for (i = 0; i < count; i++) {
        k = 0;
        box = ModelObject_GetBox(node->model, i);
        p = &boxList->corners[0];
        for (; k < n; k++) {
            for (j = 0; j < 4; j++) {
                if (j > 0 && j < 3) {
                    if (ModelBox_ClipSegment(0, box, p, p + 4) != 0 &&
                        ModelObject_RayTest(node->model, &hitDist, hitPos, &hitHeight, p, p + 4) != 0 &&
                        hitHeight >= 0x201) {
                        node->hitMask |= 1 << i;
                        *senderHits |= 1 << k;
                    }
                }
                p++;
            }
            p += 4;
        }
    }
    return *senderHits != 0;
}

/*
 * Segment against box by bisection with outcodes: 0 no part inside, 1 both ends inside,
 * 2 start inside, 3 end inside; for 2 and 3, *out gets the point where it leaves the box.
 */
s32 ModelBox_ClipSegment(SVec3 *out, NodeBox *box, SVec3 *start, SVec3 *end) {
    SVec3 mid;
    u8 startCode;
    u8 endCode;
    s32 result;

    startCode = ModelBox_OutCode(box, start);
    endCode = ModelBox_OutCode(box, end);
    if (!startCode) {
        if (!endCode) {
            return 1;
        }
    } else if (!endCode) {
        if (out != 0) {
            ModelBox_FindExit(out, box, end, start);
        }
        return 3;
    }
    if (!startCode) {
        if (out != 0) {
            ModelBox_FindExit(out, box, start, end);
        }
        return 2;
    }
    if (startCode & endCode) {
        return 0;
    }
    mid.x = (start->x + end->x) >> 1;
    mid.y = (start->y + end->y) >> 1;
    mid.z = (start->z + end->z) >> 1;
    if (start->x == mid.x && start->y == mid.y && start->z == mid.z) {
        return 0;
    }
    if (end->x == mid.x && end->y == mid.y && end->z == mid.z) {
        return 0;
    }
    if ((result = ModelBox_ClipSegment(out, box, start, &mid)) != 0
     || (result = ModelBox_ClipSegment(out, box, &mid, end)) != 0) {
        return result;
    }
    return 0;
}

/* Bisects from a point inside the box to a point outside until the midpoint stops moving. */
void ModelBox_FindExit(SVec3 *out, NodeBox *box, SVec3 *inside, SVec3 *outside)
{
    s16 tmp[2][4];
    u8 bits;
    s16 *t;

    for (;;) {
        out->x = (inside->x + outside->x) >> 1;
        out->y = (inside->y + outside->y) >> 1;
        out->z = (inside->z + outside->z) >> 1;
        if ((out->x == inside->x && out->y == inside->y && out->z == inside->z) ||
            (out->x == outside->x && out->y == outside->y && out->z == outside->z)) {
            return;
        }
        bits = 0;
        if (box->max.x < out->x) {
            bits = 8;
        } else if (out->x < box->min.x) {
            bits = 4;
        }
        if (box->max.y < out->y) {
            bits |= 2;
        } else if (out->y < box->min.y) {
            bits |= 1;
        }
        if (box->max.z < out->z) {
            bits |= 0x20;
        } else if (out->z < box->min.z) {
            bits |= 0x10;
        }
        if (bits != 0) {
            t = tmp[1];
            outside = (SVec3 *)t;
        } else {
            t = tmp[0];
            inside = (SVec3 *)t;
        }
        *(SVec3 *)t = *out;
    }
}

void func_8001E49C(void) {
}

/*
 * Slot 0xB4: every watcher of object that is a scene node (sender type 4) and whose
 * class tag byte is 0x34 is made to watch arg0.
 */
void func_8001E4A4(s32 arg0, Object *object) {
    WatcherVtbl *vtbl;
    Object *watcher;
    s32 more;

    watcher = NULL;
    do {
        for (;;) {
            Object_NextWatcher(object, (s32 *)&watcher, &more);
            if (watcher != NULL && (watcher->vtbl->unk_00 & 0xF) == 4) {
                break;
            }
            if (more == 0) {
                watcher = NULL;
                break;
            }
        }
        if (watcher != NULL) {
            vtbl = (WatcherVtbl *)watcher->vtbl;
            if (vtbl->tag == 0x34) {
                vtbl->watch(watcher, arg0);
            }
        }
    } while (more != 0);
}

SceneNodeVtbl *SceneNode_GetVtbl(void) {
    return (SceneNodeVtbl *)g_sceneNodeVtbl;
}

/* Rotates a short vector by the node's own rotation into dst (no translation, no parents). */
void SceneNode_RotateVector(SceneNodeObj *node, Vec3 *dst, SVec3 *src) {
    s32 rotMtx[8];

    node->vtbl->getRotMatrix(node, rotMtx, 0);
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    Render_TransformLongVectors(dst, dst, 1, rotMtx);
}

/* Rotates src by the node's own rotation and adds the node's world position. */
void SceneNode_LocalToWorld(SceneNodeObj *node, Vec3 *dst, Vec3 *src) {
    s32 rotMtx[8];
    Vec3 *worldPos;

    node->vtbl->getRotMatrix(node, rotMtx, 0);
    Render_TransformLongVectors(dst, src, 1, rotMtx);
    worldPos = NULL;
    if (node->parent != NULL) {
        worldPos = &node->coord->workT;
    }
    dst->x += worldPos->x;
    worldPos = NULL;
    if (node->parent != NULL) {
        worldPos = &node->coord->workT;
    }
    dst->y += worldPos->y;
    worldPos = NULL;
    if (node->parent != NULL) {
        worldPos = &node->coord->workT;
    }
    dst->z += worldPos->z;
}

/* The rotation as three fractions of degrees, each over 1 (the inverse of slot 0x44). */
void SceneNode_GetRotation(SceneNodeObj *node, Fraction *degrees) {
    NodeCoordParam *param;

    param = node->coord->param;
    degrees[0].num = (param->rotate.vx * 45) >> 9;
    degrees[0].den = 1;
    degrees[1].num = (param->rotate.vy * 45) >> 9;
    degrees[1].den = 1;
    degrees[2].num = (param->rotate.vz * 45) >> 9;
    degrees[2].den = 1;
}

/* Links the model object's TMD object to the node's GsDOBJ2 (GsLinkObject4). */
void SceneNode_LinkModel(SceneNodeObj *node, ModelObject *model) {
    node->model = model;
    node->tmd = model->tmdObject;
    GsLinkObject4((u32 *)(node->model->tmdObjectBase + 0xC), &node->attribute, 0);
}

void SceneNode_UnlinkModel(SceneNodeObj *node) {
    node->tmd = 0;
    node->model = NULL;
}

/*
 * Casts a ray 0x400 up from point (in the node's frame), then 0x400 down, against the node's
 * model; on a hit, *offset = hit position - point and returns 1. A hidden node (GsDOFF) is not
 * drawn, so its world position is first rebuilt from its parents' positions.
 */
s32 SceneNode_ProbeHeight(SceneNodeObj *node, Vec3 *offset, Vec3 *point) {
    SVec3 from;
    SVec3 to;
    SVec3 hit;
    s32 dist;
    Vec3 *base;
    SceneNodeObj *n;

    if (node->model == NULL) {
        return 0;
    }
    if (node->attribute < 0 && node->parent != NULL) {
        if (&node->coord->workT != NULL) {
            node->coord->workT = node->coord->t;
            for (n = node->parent; n != NULL; n = n->parent) {
                (node->parent != NULL ? &node->coord->workT : NULL)->x =
                    (node->parent != NULL ? &node->coord->workT : NULL)->x + n->coord->t.x;
                (node->parent != NULL ? &node->coord->workT : NULL)->y =
                    (node->parent != NULL ? &node->coord->workT : NULL)->y + n->coord->t.y;
                (node->parent != NULL ? &node->coord->workT : NULL)->z =
                    (node->parent != NULL ? &node->coord->workT : NULL)->z + n->coord->t.z;
            }
        }
    }
    base = node->parent != NULL ? &node->coord->workT : NULL;
    to.x = point->x - base->x;
    to.y = point->y - base->y;
    to.z = point->z - base->z;
    node->vtbl->worldToLocal(node, 0, &from, &to, 1);
    to.x = from.x;
    to.y = from.y - 0x400;
    to.z = from.z;
    if (ModelObject_RayTest(node->model, &dist, &hit, NULL, &from, &to) != 0) {
        func_8001EA8C(offset, &from, &hit);
        return 1;
    }
    to.y = from.y + 0x400;
    if (ModelObject_RayTest(node->model, &dist, &hit, NULL, &from, &to) == 0) {
        return 0;
    }
    func_8001EA8C(offset, &from, &hit);
    return 1;
}

void func_8001EA8C(Vec3 *out, SVec3 *from, SVec3 *to) {
    out->x = to->x - from->x;
    out->y = to->y - from->y;
    out->z = to->z - from->z;
}

/*
 * Turns entity toward target (docs/discoveries.md, touch range): yaw and pitch from ratan2 in
 * degrees; noPitch keeps it level, facing == 0 turns it away (yaw + 180), extra is added after.
 */
void Entity_FaceDreamer(Entity *entity, SceneNodeObj *target, s32 noPitch, s32 facing, Fraction *extra) {
    Fraction rot[3];
    Vec3 *targetPos;
    Vec3 *pos;
    s32 yaw;

    pos = &entity->pos.block->pos;
    if (target->parent != NULL) {
        targetPos = &target->coord->workT;
    } else {
        targetPos = NULL;
    }
    if (targetPos->x != pos->x) {
        rot[1].num = ratan2(targetPos->x - pos->x, targetPos->z - pos->z);
    } else {
        rot[1].num = ratan2(1, targetPos->z - pos->z);
    }
    if (targetPos->z != pos->z) {
        rot[0].num = ratan2(targetPos->z - pos->z, targetPos->y - pos->y);
    } else {
        rot[0].num = ratan2(1, targetPos->y - pos->y);
    }
    rot[0].num = ((rot[0].num + 0x400) * 0x168) / 0x1000;
    yaw = (rot[1].num * 0x168) / 0x1000;
    rot[1].num = yaw;
    rot[2].num = 0;
    rot[2].den = 1;
    rot[1].den = 1;
    rot[0].den = 1;
    if (noPitch != 0) {
        rot[0].num = 0;
    }
    if (facing == 0) {
        rot[1].num = yaw + 0xB4;
    }
    entity->vt->unk44(entity, 1, rot);
    if (extra != 0) {
        entity->vt->unk44(entity, 0, extra);
    }
}

/* num / den in 20.12 fixed point. */
s32 Fraction_ToFixed(Fraction *fraction) {
    s32 num;
    s32 den;

    num = fraction->num;
    den = fraction->den;
    return ((num / den) << 12) + (((num % den) << 12) / den);
}

/* Outcode of a point against a box: 8 or 4 past max or min x, 2 or 1 for y, 0x20 or 0x10 for z. */
s32 ModelBox_OutCode(NodeBox *box, SVec3 *point) {
    s32 code;

    code = 0;
    if (box->max.x < point->x) {
        code = 8;
    } else if (point->x < box->min.x) {
        code = 4;
    }
    if (box->max.y < point->y) {
        code |= 2;
    } else if (point->y < box->min.y) {
        code |= 1;
    }
    if (box->max.z < point->z) {
        code |= 0x20;
    } else if (point->z < box->min.z) {
        code |= 0x10;
    }
    return code;
}

/* Writes value into the width-bit field at bit shift of *word, returns the old field value. */
s32 Bits_SetField(s32 *word, s32 shift, s32 width, s32 value) {
    s32 i;
    s32 mask;
    s32 old;

    mask = 1;
    for (i = 0; i < width; i++) {
        mask <<= 1;
    }
    mask = mask - 1;
    mask = mask << shift;
    old = *word;
    *word &= ~mask;
    *word |= value << shift;
    return (u32)(mask & old) >> shift;
}

void Render_TransformVectors(SVec3 *dst, SVec3 *src, s32 count, void *matrix) {
    SVec3 tmp;
    SVec3 *end;

    end = dst + count;
    while (dst < end) {
        tmp = *src;
        ApplyMatrixSV(matrix, &tmp, dst);
        dst++;
        src++;
    }
}

/* ApplyMatrixLV on count long vectors (12 bytes each). */
void Render_TransformLongVectors(void *dstVecs, void *srcVecs, s32 count, s32 *matrix) {
    u8 *dst;
    u8 *src;
    u8 *end;
    s32 *mtx;
    s32 pad[2];

    dst = dstVecs;
    src = srcVecs;
    mtx = matrix;
    end = (u8 *)dstVecs + count * 12;
    while (dst < end) {
        ApplyMatrixLV(mtx, src, dst);
        dst += 12;
        src += 12;
    }
}

/* Whether pos is within range of center on each of the three axes. */
s32 Entity_IsWithinBox(s32 *center, s32 range, s32 *pos) {
    s32 i;

    for (i = 0; i < 3; i++, center++, pos++) {
        if (*pos < *center - range) {
            return 0;
        }
        if (*center + range < *pos) {
            return 0;
        }
    }
    return 1;
}

/* Sets g_rayHeightCheck (ray hits need a height of 0x201 or more), returns the old value. */
s32 SceneNode_SetRayHeightCheck(s32 enable) {
    s32 old;

    old = g_rayHeightCheck;
    g_rayHeightCheck = enable;
    return old;
}

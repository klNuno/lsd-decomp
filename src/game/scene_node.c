#include "common.h"
#include "game/scene_node.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/model_object.h"
#include "game/entity.h"
#include "game/dream_sys.h"
#include "psyq/libgte.h"
#include "psyq/libgs.h"

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
 *
 * File boundaries: proven (docs/layout.md)
 */

/* Message a node sends to the node it hit, and that the hit node keeps as contact. */
#define NODE_MSG_CONTACT 4

/* not in game/scene_node.h: each file that calls it reads the vtable through its own view of the slots */
SceneNodeVtbl *SceneNode_GetVtbl(void);
static void SceneNode_UnlinkModel(SceneNode *node);
static s32 Fraction_ToFixed(Fraction *fraction);
static s32 ModelBox_OutCode(ModelBox *box, ModelVec *point);
static s32 ModelBox_ClipSegment(ModelVec *out, ModelBox *box, ModelVec *start, ModelVec *end);
static void ModelBox_FindExit(ModelVec *out, ModelBox *box, ModelVec *inside, ModelVec *outside);
static void SceneNode_SubtractVec(Vec3 *out, ModelVec *from, ModelVec *to);
static void Render_TransformVectors(ModelVec *dst, ModelVec *src, s32 count, void *matrix);

extern SceneNodeVtbl g_sceneNodeVtbl;
extern s32 g_nodeZeroRotation[];
extern s32 g_nodeUnitScale[];
s32 g_rayHeightCheck;

/* The class head of SceneNode_AddActorWatchers's watchers: a tag byte and the watch slot. */
typedef struct WatcherVtbl {
    u8 tag;
    u8 pad_01[0xF];
    void (*watch)(Object *, s32);
} WatcherVtbl;

/* New scene node: 0x44 bytes from the heap, initialized through slot 0x08. */
SceneNode *SceneNode_New(void) {
    SceneNode *node;

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
SceneNode *SceneNode_Init(SceneNode *node) {
    Coord2 *coord;
    Coord2Param *param;

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
void SceneNode_Destroy(SceneNode *node) {
    node->vtbl->detach(node);
    node->vtbl->detachChildren(node);
    node->vtbl->unk5C(node, 0);
    Heap_Free(node->coord->param);
    Heap_Free(node->coord);
    Object_GetBaseVtbl()->destroy(node);
}

/* Slot 0x10: watching a model object (sender type 9) links its TMD object to the GsDOBJ2. */
void SceneNode_Watch(SceneNode *node, Object *other) {
    Object_GetBaseVtbl()->watch(node, other);
    if ((other->vtbl->classWord & 0xF) == 9) {
        SceneNode_LinkModel(node, (ModelObject *)other);
    }
}

/* Slot 0x14 */
void SceneNode_Unwatch(SceneNode *node, Object *other) {
    if ((other->vtbl->classWord & 0xF) == 9) {
        SceneNode_UnlinkModel(node);
    }
    Object_GetBaseVtbl()->unwatch(node, other);
}

/* Slot 0x18 */
void SceneNode_UnwatchAll(SceneNode *node) {
    SceneNode_UnlinkModel(node);
    Object_GetBaseVtbl()->unwatchAll(node);
}

/* Slot 0x38: dispatches on the sender type: 2 pad, 5 clock, 4 scene node. */
void SceneNode_OnNotify(SceneNode *node, Object *sender, s32 message) {
    s32 senderType;

    Object_GetBaseVtbl()->onNotify(node, sender, message);
    senderType = sender->vtbl->classWord & 0xF;
    if (senderType == 2) {
        node->vtbl->onPad(node, sender, message);
    } else if (senderType == 5) {
        node->vtbl->onClock(node, sender, message);
    } else if (senderType == 4) {
        node->vtbl->onNode(node, sender, message);
    }
}

/* Slot 0x40: no parent coordinate, rotation 0, scale 1 (g_nodeZeroRotation and g_nodeUnitScale are Fraction[3]). */
void SceneNode_Reset(SceneNode *node) {
    node->ticks = 0;
    node->attribute = 0;
    GsInitCoordinate2(0, node->coord);
    node->vtbl->setRotation(node, 1, g_nodeZeroRotation);
    node->vtbl->setScale(node, 1, g_nodeUnitScale);
    node->coord->flg = 1;
}

/* Slot 0x44: sets (assign != 0) or adds the rotation, three fractions of degrees. */
void SceneNode_SetRotation(SceneNode *node, s32 assign, Fraction *degrees) {
    s32 angles[3];
    s32 i;
    Coord2Param *param;
    s16 *p;
    s16 *cur;

    angles[0] = Fraction_ToFixed(degrees);
    angles[1] = Fraction_ToFixed(degrees + 1);
    angles[2] = Fraction_ToFixed(degrees + 2);
    angles[0] /= 0x168;
    angles[1] /= 0x168;
    angles[2] /= 0x168;
    param = node->coord->param;
    p = &param->rotate.vec.vx;
    if (assign != 0) {
        param->rotate.vec.vx = angles[0];
        param->rotate.vec.vy = angles[1];
        param->rotate.vec.vz = angles[2];
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
void SceneNode_SetScale(SceneNode *node, s32 assign, Fraction *factors) {
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
SceneNode *SceneNode_Attach(SceneNode *node, SceneNode *parent, Vec3 *pos) {
    Coord2 *coord;

    if (node->parent == NULL) {
        node->parent = parent;
        node->coord->super = parent->coord;
        parent->vtbl->watch(parent, node);
        coord = node->coord;
        if (pos != NULL) {
            coord->coord.t.x = pos->x;
            coord->coord.t.y = pos->y;
            coord->coord.t.z = pos->z;
        } else {
            coord->coord.t.x = 0;
            coord->coord.t.y = 0;
            coord->coord.t.z = 0;
        }
        node->coord->flg = 0;
    }
    return node;
}

/* Slot 0x50 */
SceneNode *SceneNode_Detach(SceneNode *node) {
    SceneNode *parent;

    parent = node->parent;
    if (parent != NULL) {
        parent->vtbl->unwatch(parent, node);
        node->coord->super = NULL;
        node->parent = NULL;
    }
    return node;
}

/* Slot 0x54 */
void SceneNode_DetachChildren(SceneNode *node) {
    SceneNode *child;
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
void SceneNode_NextChild(SceneNode *node, SceneNode **child, ListNode **iter) {
    SceneNode *obj;

    do {
        if (*child == NULL) {
            *iter = node->watched;
        }
        List_Next((Object **)child, iter);
        obj = *child;
        if (obj != NULL && (obj->vtbl->classWord & 0xF) == 4 && obj->parent == node) {
            return;
        }
    } while (*iter != NULL);
    *child = NULL;
}

void SceneNode_EmptySlot5C(void) {
}

/* Slots 0x60 to 0x80 set the GsDOBJ2 attribute bits (PSY-Q libgs.h names). */

/* Slot 0x60: GsDOFF = !visible, returns whether the node was visible. */
s32 SceneNode_SetVisible(SceneNode *node, s32 visible) {
    return Bits_SetField(&node->attribute, 0x1F, 1, visible == 0) == 0;
}

/* Slot 0x64: GsALON */
void SceneNode_SetSemiTrans(SceneNode *node, s32 semiTrans) {
    Bits_SetField(&node->attribute, 0x1E, 1, semiTrans != 0);
}

/* Slot 0x68: semi-transparency rate, GsAZERO to GsATHREE */
void SceneNode_SetBlendRate(SceneNode *node, s32 rate) {
    Bits_SetField(&node->attribute, 0x1C, 2, rate);
}

/* Slot 0x6C: GsLOFF = !lit */
void SceneNode_SetLit(SceneNode *node, s32 lit) {
    Bits_SetField(&node->attribute, 6, 1, lit == 0);
}

/* Slot 0x70: GsFOG, GsMATE and GsLLMOD as one 3-bit value */
void SceneNode_SetLightFlags(SceneNode *node, s32 flags) {
    Bits_SetField(&node->attribute, 3, 3, flags);
}

/* Slot 0x74: GsLDIM0 to GsLDIM7 */
void SceneNode_SetDim(SceneNode *node, s32 dim) {
    Bits_SetField(&node->attribute, 0, 3, dim);
}

/* Slot 0x78: GsZIGNR = !value, returns the previous value */
s32 SceneNode_SetZSort(SceneNode *node, s32 zSort) {
    return Bits_SetField(&node->attribute, 7, 1, zSort == 0) == 0;
}

/* Slot 0x7C: polygon division, GsDIV1 to GsDIV5 */
void SceneNode_SetDivision(SceneNode *node, s32 division) {
    Bits_SetField(&node->attribute, 9, 3, division);
}

/* Slot 0x80: GsNBACKC = !value, returns the previous value */
s32 SceneNode_SetBackfaceClip(SceneNode *node, s32 backfaceClip) {
    return Bits_SetField(&node->attribute, 8, 1, backfaceClip == 0) == 0;
}

/* Slot 0x84: the rotation matrix of the node's own rotation, or of its inverse angles. */
void SceneNode_GetRotMatrix(SceneNode *node, void *matrix, s32 invert) {
    SVector rot;
    Coord2Param *param;

    param = node->coord->param;
    if (invert != 0) {
        rot.vx = -param->rotate.vec.vx;
        rot.vy = -param->rotate.vec.vy;
        rot.vz = -param->rotate.vec.vz;
    } else {
        rot = param->rotate.vec;
    }
    RotMatrix(&rot, matrix);
}

/* Slot 0x88: for messages 2 and 3, sends the model's box list to the watchers. */
void SceneNode_SendBoxes(SceneNode *node, s32 message) {
    NodeBoxList boxList;
    ModelObject *model;

    if (message < 4) {
        if (message >= 2) {
            model = node->model;
            if ((model != NULL) && (ModelObject_IsReady(model) != 0)) {
                node->vtbl->getBoxList(node, &boxList);
                node->vtbl->sendShape(node, &boxList, message);
            }
        }
    }
}

/* Slot 0x8C: the model's box list: one box, 8 corners. */
void SceneNode_GetBoxList(SceneNode *node, NodeBoxList *boxList) {
    ModelObject_GetBoxList(node->model, boxList);
}

/* Slot 0x90: moves the box list into world space and notifies the watchers with it. */
void SceneNode_SendShape(SceneNode *node, NodeBoxList *boxList, s32 message) {
    Render_TransformVectors(boxList->corners, boxList->corners, boxList->count * 8, &node->coord->workm);
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
void SceneNode_OnNode(SceneNode *node, SceneNode *sender, s32 message) {
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
void SceneNode_CheckContact(SceneNode *node, SceneNode *sender) {
    Vec3 offset;
    u16 localOffset[3];
    u8 unused[0x20];
    NodeBoxList boxes;
    Vec3 *senderPos;
    Vec3 *pos;
    ModelVec *corners;

    if (node->model != NULL && ModelObject_IsReady(node->model) != 0) {
        senderPos = NULL;
        if (sender->parent != NULL) {
            senderPos = &sender->coord->workm.t;
        }
        offset = *senderPos;
        pos = NULL;
        if (node->parent != NULL) {
            pos = &node->coord->workm.t;
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
            boxes.count = sender->boxList->count;
            corners = sender->boxList->corners;
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
void SceneNode_WorldToLocal(SceneNode *node, ModelVec *offset, ModelVec *dst, ModelVec *src, s32 count) {
    s32 parentMtx[8];
    s32 worldMtx[8];
    SceneNode *parent;

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
s32 SceneNode_BoxesOverlap(SceneNode *node, NodeBoxList *boxList, ModelVec *offset) {
    ModelBox own;
    ModelBox other;
    u8 *end;
    ModelVec *p;
    ModelBox *box;
    ModelBox *b;
    ModelBox *bend;
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
s32 SceneNode_RayTestBoxes(SceneNode *node, s32 *senderHits, ModelVec *hitPos, NodeBoxList *boxList) {
    ModelVec axis[2];
    ModelBox unused[2];
    s32 hitDist;
    s32 hitHeight;
    ModelVec *p;
    ModelVec *q;
    ModelVec *dst;
    s32 count;
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    ModelBox *box;

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
static s32 ModelBox_ClipSegment(ModelVec *out, ModelBox *box, ModelVec *start, ModelVec *end) {
    ModelVec mid;
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
static void ModelBox_FindExit(ModelVec *out, ModelBox *box, ModelVec *inside, ModelVec *outside)
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
            outside = (ModelVec *)t;
        } else {
            t = tmp[0];
            inside = (ModelVec *)t;
        }
        *(ModelVec *)t = *out;
    }
}

void SceneNode_EmptySlotB0(void) {
}

/*
 * Slot 0xB4: every watcher of object that is a scene node (sender type 4) and whose
 * class tag byte is 0x34 is made to watch arg0.
 */
void SceneNode_AddActorWatchers(s32 node, Object *object) {
    WatcherVtbl *vtbl;
    Object *watcher;
    ListNode *more;

    watcher = NULL;
    do {
        for (;;) {
            Object_NextWatcher(object, &watcher, &more);
            if (watcher != NULL && (watcher->vtbl->classWord & 0xF) == 4) {
                break;
            }
            if (more == NULL) {
                watcher = NULL;
                break;
            }
        }
        if (watcher != NULL) {
            vtbl = (WatcherVtbl *)watcher->vtbl;
            if (vtbl->tag == 0x34) {
                vtbl->watch(watcher, node);
            }
        }
    } while (more != 0);
}

SceneNodeVtbl *SceneNode_GetVtbl(void) {
    return &g_sceneNodeVtbl;
}

/* Rotates a short vector by the node's own rotation into dst (no translation, no parents). */
void SceneNode_RotateVector(SceneNode *node, Vec3 *dst, ModelVec *src) {
    Matrix rotMtx;

    node->vtbl->getRotMatrix(node, &rotMtx, 0);
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    Render_TransformLongVectors(dst, dst, 1, &rotMtx);
}

/* Rotates src by the node's own rotation and adds the node's world position. */
void SceneNode_LocalToWorld(SceneNode *node, Vec3 *dst, Vec3 *src) {
    Matrix rotMtx;
    Vec3 *worldPos;

    node->vtbl->getRotMatrix(node, &rotMtx, 0);
    Render_TransformLongVectors(dst, src, 1, &rotMtx);
    worldPos = NULL;
    if (node->parent != NULL) {
        worldPos = &node->coord->workm.t;
    }
    dst->x += worldPos->x;
    worldPos = NULL;
    if (node->parent != NULL) {
        worldPos = &node->coord->workm.t;
    }
    dst->y += worldPos->y;
    worldPos = NULL;
    if (node->parent != NULL) {
        worldPos = &node->coord->workm.t;
    }
    dst->z += worldPos->z;
}

/* The rotation as three fractions of degrees, each over 1 (the inverse of slot 0x44). */
void SceneNode_GetRotation(SceneNode *node, Fraction *degrees) {
    Coord2Param *param;

    param = node->coord->param;
    degrees[0].num = (param->rotate.vec.vx * 45) >> 9;
    degrees[0].den = 1;
    degrees[1].num = (param->rotate.vec.vy * 45) >> 9;
    degrees[1].den = 1;
    degrees[2].num = (param->rotate.vec.vz * 45) >> 9;
    degrees[2].den = 1;
}

/* Links the model object's TMD object to the node's GsDOBJ2 (GsLinkObject4). */
void SceneNode_LinkModel(SceneNode *node, ModelObject *model) {
    node->model = model;
    node->tmd = model->entry;
    GsLinkObject4((u32 *)(node->model->tmdObjectBase + 0xC), &node->attribute, 0);
}

static void SceneNode_UnlinkModel(SceneNode *node) {
    node->tmd = 0;
    node->model = NULL;
}

/*
 * Casts a ray 0x400 up from point (in the node's frame), then 0x400 down, against the node's
 * model; on a hit, *offset = hit position - point and returns 1. A hidden node (GsDOFF) is not
 * drawn, so its world position is first rebuilt from its parents' positions.
 */
s32 SceneNode_ProbeHeight(SceneNode *node, Vec3 *offset, Vec3 *point) {
    ModelVec from;
    ModelVec to;
    ModelVec hit;
    s32 dist;
    Vec3 *base;
    SceneNode *n;

    if (node->model == NULL) {
        return 0;
    }
    if (node->attribute < 0 && node->parent != NULL) {
        if (&node->coord->workm.t != NULL) {
            node->coord->workm.t = node->coord->coord.t;
            for (n = node->parent; n != NULL; n = n->parent) {
                (node->parent != NULL ? &node->coord->workm.t : NULL)->x =
                    (node->parent != NULL ? &node->coord->workm.t : NULL)->x + n->coord->coord.t.x;
                (node->parent != NULL ? &node->coord->workm.t : NULL)->y =
                    (node->parent != NULL ? &node->coord->workm.t : NULL)->y + n->coord->coord.t.y;
                (node->parent != NULL ? &node->coord->workm.t : NULL)->z =
                    (node->parent != NULL ? &node->coord->workm.t : NULL)->z + n->coord->coord.t.z;
            }
        }
    }
    base = node->parent != NULL ? &node->coord->workm.t : NULL;
    to.x = point->x - base->x;
    to.y = point->y - base->y;
    to.z = point->z - base->z;
    node->vtbl->worldToLocal(node, 0, &from, &to, 1);
    to.x = from.x;
    to.y = from.y - 0x400;
    to.z = from.z;
    if (ModelObject_RayTest(node->model, &dist, &hit, NULL, &from, &to) != 0) {
        SceneNode_SubtractVec(offset, &from, &hit);
        return 1;
    }
    to.y = from.y + 0x400;
    if (ModelObject_RayTest(node->model, &dist, &hit, NULL, &from, &to) == 0) {
        return 0;
    }
    SceneNode_SubtractVec(offset, &from, &hit);
    return 1;
}

static void SceneNode_SubtractVec(Vec3 *out, ModelVec *from, ModelVec *to) {
    out->x = to->x - from->x;
    out->y = to->y - from->y;
    out->z = to->z - from->z;
}

/*
 * Turns entity toward target (docs/discoveries.md, touch range): yaw and pitch from ratan2 in
 * degrees; noPitch keeps it level, facing == 0 turns it away (yaw + 180), extra is added after.
 * Behavior_Type115 and Behavior_Type81 swap the two (the dreamer turns to the entity) through casts:
 * both classes are scene nodes, with the parent at 0x0C, the coordinate at 0x14 and slot 0x44.
 */
void Entity_FaceDreamer(Entity *entity, struct DreamSys *target, s32 noPitch, s32 facing, Fraction *extra) {
    Fraction rot[3];
    Vec3 *targetPos;
    Vec3 *pos;
    s32 yaw;

    pos = &entity->pos.coord->coord.t;
    if (target->parent != NULL) {
        targetPos = &target->pos.coord->workm.t;
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
    entity->vt->rotate(entity, 1, rot);
    if (extra != 0) {
        entity->vt->rotate(entity, 0, extra);
    }
}

/* num / den in 20.12 fixed point. */
static s32 Fraction_ToFixed(Fraction *fraction) {
    s32 num;
    s32 den;

    num = fraction->num;
    den = fraction->den;
    return ((num / den) << 12) + (((num % den) << 12) / den);
}

/* Outcode of a point against a box: 8 or 4 past max or min x, 2 or 1 for y, 0x20 or 0x10 for z. */
static s32 ModelBox_OutCode(ModelBox *box, ModelVec *point) {
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

static void Render_TransformVectors(ModelVec *dst, ModelVec *src, s32 count, void *matrix) {
    ModelVec tmp;
    ModelVec *end;

    end = dst + count;
    while (dst < end) {
        tmp = *src;
        ApplyMatrixSV(matrix, &tmp, dst);
        dst++;
        src++;
    }
}

/* ApplyMatrixLV on count long vectors (12 bytes each). */
void Render_TransformLongVectors(Vec3 *dstVecs, Vec3 *srcVecs, s32 count, Matrix *matrix) {
    Vec3 *dst;
    Vec3 *src;
    Vec3 *end;
    Matrix *mtx;
    s32 pad[2];

    dst = dstVecs;
    src = srcVecs;
    mtx = matrix;
    end = dstVecs + count;
    while (dst < end) {
        ApplyMatrixLV(mtx, src, dst);
        dst++;
        src++;
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

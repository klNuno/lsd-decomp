#ifndef GAME_MODEL_OBJECT_H
#define GAME_MODEL_OBJECT_H

#include "common.h"
#include "game/heap.h"

/* 16-byte value at +0x14 of a ModelObject, copied in by ModelObject_SetValue */
typedef struct ModelObjectValue {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} ModelObjectValue;

/*
 * One model object (src/game/model_object.c, sender type 9): the 0x24-byte Object subclass made by
 * ModelObject_Create, one per TMD object; a scene node links one at +0x20.
 * Its vtable is g_modelObjectVtbl (g_modelObjectVtbl). The first three fields are the Object root
 * of heap.h, kept as s32 because the constructor stores an s32 in them (see the report).
 */
typedef struct ModelObject {
    s32 vtbl;               /* +0x00 ObjectVtbl * in heap.h */
    ListNode *watched;      /* +0x04 */
    ListNode *watchers;     /* +0x08 */
    s32 tmdObjectBase;      /* +0x0C tmdObject - 0xC, see ModelObject_GetObjectAt */
    s32 tmdObject;          /* +0x10 address of the TMD object entry */
    ModelObjectValue value; /* +0x14 */
} ModelObject;

/* Functions of src/game/model_object.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/model_object.c */
struct ClutPos;
struct ModelBoxList;
struct ModelBoxOut;
struct ModelObjectView;
struct ModelVec;
void *ModelObject_Create(s32 tmdObject);
s32 ModelObject_IsReady(s32 modelObject);
void ModelObject_UpdateBox(void *modelObject);
void *ModelObject_GetBox(); /* unprototyped: scene_node.c passes the model and a box index */
void ModelObject_GetBoxList(void *modelObject, struct ModelBoxOut *out);
void ModelBox_ShiftList(struct ModelBoxList *list, s32 alongX, s32 side, s32 delta);
s32 ModelObject_RayTest(struct ModelObjectView *modelObject, s32 *hitDist, struct ModelVec *hitPos, s32 *hitHeight, struct ModelVec *from, struct ModelVec *to);
void ModelObject_SetClut(struct ModelObjectView *modelObject, struct ClutPos *pos);

#endif

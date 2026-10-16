#ifndef GAME_MODEL_OBJECT_H
#define GAME_MODEL_OBJECT_H

#include "common.h"

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

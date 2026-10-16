#ifndef GAME_SCENE_NODE_H
#define GAME_SCENE_NODE_H

#include "common.h"
#include "game/entity.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene.h"

/* Functions of src/game/scene_node.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/scene_node.c */
struct NodeBoxList;
struct SVec3;
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
void SceneNode_GetBoxList(SceneNode *node, s32 *boxList);
void SceneNode_SendShape(SceneNode *node, s32 *boxList, s32 message);
void SceneNode_OnPad(void);
void SceneNode_OnClock(void);
void SceneNode_OnNode(SceneNode *node, SceneNode *sender, s32 message);
void SceneNode_CheckContact(SceneNode *node, SceneNode *sender);
void SceneNode_WorldToLocal(SceneNode *node, struct SVec3 *offset, struct SVec3 *dst, struct SVec3 *src, s32 count);
s32 SceneNode_BoxesOverlap(SceneNode *node, struct NodeBoxList *boxList, struct SVec3 *offset);
s32 SceneNode_RayTestBoxes(SceneNode *node, s32 *senderHits, struct SVec3 *hitPos, struct NodeBoxList *boxList);
void SceneNode_EmptySlotB0(void);
void SceneNode_AddActorWatchers(s32 arg0, Object *object);
void SceneNode_RotateVector(SceneNode *node, Vec3 *dst, struct SVec3 *src);
void SceneNode_LocalToWorld(); /* unprototyped: dream_sys.c and sym.c pass a fourth argument */
void SceneNode_GetRotation(SceneNode *node, Fraction *degrees);
void SceneNode_LinkModel(SceneNode *node, ModelObject *model);
s32 SceneNode_ProbeHeight(); /* unprototyped: actor.c calls it with no arguments */
void Entity_FaceDreamer(Entity *entity, SceneNode *target, s32 noPitch, s32 facing, Fraction *extra);
s32 Bits_SetField(s32 *word, s32 shift, s32 width, s32 value);
void Render_TransformLongVectors(void *dstVecs, void *srcVecs, s32 count, s32 *matrix);
s32 Entity_IsWithinBox(s32 *center, s32 range, s32 *pos);
s32 SceneNode_SetRayHeightCheck(s32 enable);

#endif

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

/* Three shorts: a vertex, a box corner, a point of a ray */
typedef struct ModelVec {
    s16 x;
    s16 y;
    s16 z;
} ModelVec;

/*
 * One primitive of a TMD object, the Sony packet (psx-spx "TMD - Modeling Data for OS Library").
 * The GPU polygon code is in mode (0x20 to 0x3F). flag bit 2 selects the gouraud layout, which
 * pushes the vertex index words 8 bytes down, so one offset holds a different word per code.
 * ModelObject_NextPrim reads only the vertex index words. The names below are those indexes for
 * the flat layout. In the gouraud layout the same field is read as the next vertex's index.
 */
typedef struct ModelPrim {
    u8 olen;     /* +0x00 output packet size in words */
    u8 ilen;     /* +0x01 input packet size in words */
    u8 flag;     /* +0x02 bit 2: gouraud, the vertex indexes move */
    u8 mode;     /* +0x03 GPU command 0x20 to 0x3F */
    u16 i04;
    u16 clut;    /* +0x06 CBA of a textured primitive: clut x / 16 + clut y * 64 */
    u16 v0;      /* +0x08 flat untextured (0x21, 0x23, 0x29, 0x2B); gouraud puts a normal here */
    u16 v1;      /* +0x0A */
    u16 v2;      /* +0x0C */
    u16 v3;      /* +0x0E quad only; a triangle ends here */
    u16 i10;     /* +0x10 flat textured quad's fourth vertex (0x28) */
    u16 i12;
    u16 i14;     /* +0x14 flat textured unlit quad's first vertex (0x39) */
    u16 i16;
    u16 i18;
    u16 i1A;
    u16 i1C;     /* +0x1C gouraud textured unlit triangle's first vertex (0x35) */
    u16 i1E;
    u16 i20;
    u16 i22;
    u16 i24;     /* +0x24 gouraud textured unlit quad's first vertex (0x3D) */
    u16 i26;
    u16 i28;
    u16 i2A;
} ModelPrim;

typedef struct ModelVertex {
    ModelVec pos;
    s16 pad;
} ModelVertex;

/* One TMD object table entry, 0x1C bytes (TmdHeader.objects in tmd.h) */
typedef struct ModelEntry {
    ModelVertex *vertices;  /* +0x00 */
    s32 vertexCount;        /* +0x04, read by ModelObject_ComputeBox */
    void *normals;          /* +0x08 */
    s32 normalCount;        /* +0x0C */
    ModelPrim *primitives;  /* +0x10, read by ModelObject_NextPrim */
    u32 primitiveCount;     /* +0x14, read by ModelObject_NextPrim */
    s32 scale;              /* +0x18 */
} ModelEntry;

/* An axis-aligned box: min and max corners (ModelObject_GetBox, the ray tests of scene nodes) */
typedef struct ModelBox {
    ModelVec min;
    ModelVec max;
} ModelBox;

/*
 * A box list: a count of boxes, then 8 corners per box (0x30 bytes). ModelObject_GetBoxList fills
 * one box: c0 (min, min, min), c1 (min, max y, min), c2 (max, max y, min), c3 (max, min y, min),
 * and c4 to c7 the same with max z. A scene node sends it to its watchers (SceneNode_SendShape).
 */
typedef struct NodeBoxList {
    s32 count;
    ModelVec corners[8];
    s32 pad_34;
} NodeBoxList;

/* The same box list as ModelBox_ShiftList reads it: u16 corners, one 0x30-byte record per box */
typedef struct ModelBoxCorner {
    u16 x;
    u16 y;
    u16 z;
} ModelBoxCorner;

typedef struct ModelBoxRecord {
    ModelBoxCorner v[8];
} ModelBoxRecord;

typedef struct ModelBoxList {
    s32 count;
    ModelBoxRecord recs[1];
} ModelBoxList;

/*
 * One model object (src/game/model_object.c, sender type 9): the 0x24-byte Object subclass made by
 * ModelObject_Create, one per TMD object; a scene node links one at +0x20.
 * Its vtable is g_modelObjectVtbl. The first three fields are the Object root of heap.h.
 */
typedef struct ModelObject {
    ObjectVtbl *vtbl;       /* +0x00 g_modelObjectVtbl */
    ListNode *watched;      /* +0x04 */
    ListNode *watchers;     /* +0x08 */
    s32 tmdObjectBase;      /* +0x0C entry - 0xC: the TMD header when entry is its first object, see ModelObject_GetObjectAt */
    ModelEntry *entry;      /* +0x10 the TMD object entry */
    ModelObjectValue value; /* +0x14 */
} ModelObject;

/* Functions of src/game/model_object.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/model_object.c */
struct ClutPos;
ModelObject *ModelObject_Create(ModelEntry *tmdObject);
s32 ModelObject_GetBoxCount(ModelObject *modelObject);
void ModelObject_UpdateBox(ModelObject *modelObject);
void *ModelObject_GetBox(); /* unprototyped: scene_node.c passes the model and a box index */
void ModelObject_GetBoxList(ModelObject *modelObject, NodeBoxList *out);
void ModelBox_ShiftList(ModelBoxList *list, s32 alongX, s32 side, s32 delta);
s32 ModelObject_RayTest(ModelObject *modelObject, s32 *hitDist, ModelVec *hitPos, s32 *hitHeight, ModelVec *from, ModelVec *to);
void ModelObject_SetClut(ModelObject *modelObject, struct ClutPos *pos);

#endif

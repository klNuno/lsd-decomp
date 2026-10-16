#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

/* ModelObject_MapModelingData reads +0x0C as a u32 pointer for GsMapModelingData, see the report */
typedef struct ModelObjectMapView {
    u8 pad_00[0xC];
    u32 *tmdObjectBase;
} ModelObjectMapView;

extern void GsMapModelingData(u32 *p);
extern u8 g_modelBox[];
void ModelObject_ComputeBox(void *modelObject, u8 *out);
/* A CLUT offset in VRAM pixels, added to a primitive's CLUT by ModelObject_OffsetClut */
typedef struct ClutOffset {
    s32 x;
    s32 y;
} ClutOffset;

/* A CLUT position in VRAM pixels, written into a primitive's CLUT by ModelObject_SetClut */
typedef struct ClutPos {
    s16 x;
    s16 y;
} ClutPos;

void *Object_GetBaseVtbl(void);
s32 ModelObject_GetVtbl(void);
void ModelObject_SetReady(void *modelObject);
void *Heap_Alloc(s32 size);

/*
 * Output of ModelObject_GetBoxList: count 1, then the eight corners of the box, three u16 each.
 * c0 is (min, min, min), c1 (min, max y, min), c2 (max, max y, min), c3 (max, min y, min),
 * and c4 to c7 repeat them with max z. Same layout as ModelBoxRecord.
 */
typedef struct ModelBoxOut {
    s32 count;
    u16 c0x, c0y, c0z;
    u16 c1x, c1y, c1z;
    u16 c2x, c2y, c2z;
    u16 c3x, c3y, c3z;
    u16 c4x, c4y, c4z;
    u16 c5x, c5y, c5z;
    u16 c6x, c6y, c6z;
    u16 c7x, c7y, c7z;
} ModelBoxOut;

/* Scratch buffer of ModelObject_GetBoxList: min x, y, z then max x, y, z */
typedef struct ModelBoxBuf {
    s32 one;
    u16 buf[6];
} ModelBoxBuf;

extern u8 g_modelObjectVtbl[];
s32 g_modelObjectReady;

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

typedef struct ModelVec {
    s16 x;
    s16 y;
    s16 z;
} ModelVec;

typedef struct ModelVertex {
    ModelVec pos;
    s16 pad;
} ModelVertex;

/* One TMD object table entry, 0x1C bytes (the same layout as TmdObjectEntry in loader.h) */
typedef struct ModelEntry {
    ModelVertex *vertices;  /* +0x00 */
    s32 vertexCount;        /* +0x04, read by ModelObject_ComputeBox */
    void *normals;          /* +0x08 */
    s32 normalCount;        /* +0x0C */
    ModelPrim *primitives;  /* +0x10, read by ModelObject_NextPrim */
    u32 primitiveCount;     /* +0x14, read by ModelObject_NextPrim */
    s32 scale;              /* +0x18 */
} ModelEntry;

/* A model object as the mesh and draw functions read it: its TMD entry is at +0x10 */
typedef struct ModelObjectView {
    u8 pad_00[0x10];
    ModelEntry *entry;
} ModelObjectView;

/* One box corner, u16 coordinates */
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

typedef struct ModelBox {
    ModelVec min;
    ModelVec max;
} ModelBox;

void *ModelObject_NextPrim(ModelObjectView *modelObject, ModelPrim *prim, s32 *count, ModelVec *out, u32 *primIndex);

typedef struct HitLongVec { s32 x; s32 y; s32 z; s32 pad; } HitLongVec;
typedef struct HitShortVec { s16 x; s16 y; s16 z; s16 pad; } HitShortVec;
typedef struct HitFraction { s32 num; s32 den; } HitFraction;
void OuterProduct0(HitLongVec *a, HitLongVec *b, HitLongVec *out);
void Square0(HitLongVec *in, HitLongVec *out);
s32 SquareRoot0(s32 a);
#define ABS(x) ((x) < 0 ? ~(x) + 1 : (x))
#define FIX_DIV(n, d) ((((n) / (d)) != 0 ? ((n) / (d)) << 16 : ((n) * (d)) & 0x80000000) | (ABS((n) % (d)) << 16) / ABS(d))


void *ModelObject_Create(s32 tmdObject) {
    void *modelObject;

    modelObject = Heap_Alloc(0x24);
    if (modelObject != 0) {
        ((ObjectVtbl *)ModelObject_GetVtbl())->init(modelObject, tmdObject);
        return modelObject;
    }
    return 0;
}

void ModelObject_Init(ModelObject *modelObject, s32 tmdObject) {
    s32 vtbl;

    ((ObjectVtbl *)Object_GetBaseVtbl())->init(modelObject);
    vtbl = ModelObject_GetVtbl();
    modelObject->tmdObject = tmdObject;
    modelObject->vtbl = vtbl;
    modelObject->tmdObjectBase = tmdObject - 0xC;
    ModelObject_SetReady(modelObject);
}

void ModelObject_SetValue(ModelObject *modelObject, ModelObjectValue *value) {
    modelObject->value = *value;
}

void ModelObject_MapModelingData(ModelObjectMapView *modelObject) {
    GsMapModelingData(modelObject->tmdObjectBase + 1);
}

s32 ModelObject_GetObjectAt(ModelObject *modelObject, s32 index) {
    s32 offset = index * 0x1C + 0xC;
    return offset + modelObject->tmdObjectBase;
}

void ModelObject_EmptySlot4C(void) {
}

s32 ModelObject_GetVtbl(void) {
    return (s32)g_modelObjectVtbl;
}

void ModelObject_SetReady(void *modelObject) {
    g_modelObjectReady = 1;
}

s32 ModelObject_IsReady(s32 modelObject) {
    return g_modelObjectReady;
}

void ModelObject_ComputeBox(void *modelObject, u8 *out) {
    ModelBox *box;
    ModelVertex *v;
    s16 *miny;
    s16 *minz;
    s16 *maxx;
    s16 *maxy;
    s16 *maxz;
    s32 remaining;
    s32 i;

    box = (ModelBox *)out;
    miny = &box->min.y;
    minz = &box->min.z;
    maxx = &box->max.x;
    maxy = &box->max.y;
    maxz = &box->max.z;
    v = ((ModelObjectView *)modelObject)->entry->vertices;
    remaining = ((ModelObjectView *)modelObject)->entry->vertexCount - 1;
    box->min.x = v->pos.x;
    box->min.y = v->pos.y;
    box->min.z = v->pos.z;
    box->max = box->min;
    for (i = 0; i < remaining; i++) {
        v++;
        if (v->pos.x < box->min.x) {
            box->min.x = v->pos.x;
        }
        if (v->pos.y < *miny) {
            *miny = v->pos.y;
        }
        if (v->pos.z < *minz) {
            *minz = v->pos.z;
        }
        if (*maxx < v->pos.x) {
            *maxx = v->pos.x;
        }
        if (*maxy < v->pos.y) {
            *maxy = v->pos.y;
        }
        if (*maxz < v->pos.z) {
            *maxz = v->pos.z;
        }
    }
}

void ModelObject_UpdateBox(void *modelObject) {
    ModelObject_ComputeBox(modelObject, g_modelBox);
}

void *ModelObject_GetBox(void) {
    return g_modelBox;
}

void ModelObject_GetBoxList(void *modelObject, ModelBoxOut *out) {
    ModelBoxBuf box;

    ModelObject_ComputeBox(modelObject, (u8 *)box.buf);
    box.one = 1;
    out->c0x = box.buf[0];
    out->c0y = box.buf[1];
    out->c0z = box.buf[2];
    out->c1x = box.buf[0];
    out->c1y = box.buf[4];
    out->c1z = box.buf[2];
    out->c2x = box.buf[3];
    out->c2y = box.buf[4];
    out->c2z = box.buf[2];
    out->c3x = box.buf[3];
    out->c3y = box.buf[1];
    out->c3z = box.buf[2];
    out->c4x = box.buf[0];
    out->c4y = box.buf[1];
    out->c4z = box.buf[5];
    out->c5x = box.buf[0];
    out->c5y = box.buf[4];
    out->c5z = box.buf[5];
    out->c6x = box.buf[3];
    out->c6y = box.buf[4];
    out->c6z = box.buf[5];
    out->c7x = box.buf[3];
    out->c7y = box.buf[1];
    out->c7z = box.buf[5];
    out->count = 1;
}

void ModelBox_ShiftList(ModelBoxList *list, s32 alongX, s32 side, s32 delta) {
    ModelBoxRecord copy;
    ModelBoxRecord *rec;
    s32 i;

    for (i = 0; i < list->count; i++) {
        rec = &list->recs[i];
        if (alongX != 0) {
            copy = *rec;
            rec->v[3] = copy.v[0];
            rec->v[2] = copy.v[1];
            rec->v[6] = copy.v[2];
            rec->v[7] = copy.v[3];
            rec->v[0] = copy.v[4];
            rec->v[1] = copy.v[5];
            rec->v[5] = copy.v[6];
            rec->v[4] = copy.v[7];
            if (side == 0) {
                s32 j;

                for (j = 0; j < 4; j++) {
                    rec->v[j].x += delta;
                }
            } else {
                ModelBoxCorner *p = rec->v;
                s32 j;

                for (j = 0; j < 4; j++) {
                    p[j + 4].x += delta;
                }
            }
        } else {
            if (side == 0) {
                s32 j;

                for (j = 0; j < 4; j++) {
                    rec->v[j].z += delta;
                }
            } else {
                ModelBoxCorner *p = rec->v;
                s32 j;

                for (j = 0; j < 4; j++) {
                    p[j + 4].z += delta;
                }
            }
        }
    }
}

/* Ray against the triangles and quads of one model object: keeps the nearest hit */
s32 ModelObject_RayTest(ModelObjectView *modelObject, s32 *hitDist, ModelVec *hitPos, s32 *hitHeight,
                  ModelVec *from, ModelVec *to) {
    ModelVec corners[4];
    HitLongVec normal;
    ModelVec ray[2];
    ModelVec hit;
    s32 vertCount;
    u32 primIndex;
    ModelPrim *prim;
    s32 found;
    s32 tFix, i;

    primIndex = 0;
    *hitDist = 0x7FFFFFFF;
    ray[0].x = from->x;
    ray[0].y = from->y;
    ray[0].z = from->z;
    ray[1].x = to->x - from->x;
    ray[1].y = to->y - from->y;
    ray[1].z = to->z - from->z;
    found = 0;
    while ((prim = ModelObject_NextPrim(modelObject, prim, &vertCount, corners, &primIndex)) != NULL) {
        HitLongVec spare;
        HitShortVec e1;
        HitShortVec e2;
        HitLongVec c;
        HitLongVec a;
        HitLongVec b;
        HitFraction fa;
        HitFraction ft;
        s32 w[3];
        HitLongVec d;
        HitLongVec sq;
        union {
            HitLongVec sq;
            ModelVec box[2];
        } u;
        s32 len[2];

        e1.x = corners[1].x - corners[0].x;
        e1.y = corners[1].y - corners[0].y;
        e1.z = corners[1].z - corners[0].z;
        e2.x = corners[2].x - corners[0].x;
        e2.y = corners[2].y - corners[0].y;
        e2.z = corners[2].z - corners[0].z;
        a.x = e1.x; a.y = e1.y; a.z = e1.z;
        b.x = e2.x; b.y = e2.y; b.z = e2.z;
        OuterProduct0(&a, &b, &c);
        normal.x = c.x; normal.y = c.y; normal.z = c.z;
        normal.x /= 4096;
        normal.y /= 4096;
        normal.z /= 4096;
        normal.pad = -(corners[0].x * normal.x + corners[0].y * normal.y + corners[0].z * normal.z);
        w[0] = ray[1].x * normal.x + ray[1].y * normal.y + ray[1].z * normal.z;
        if (ABS(w[0]) <= 0) {
            w[1] = 2;
        } else {
            c.x = w[0];
            c.y = 1;
            w[2] = ray[0].x * normal.x + ray[0].y * normal.y + ray[0].z * normal.z;
            w[2] += normal.pad;
            fa.num = -w[2];
            fa.den = 1;
            ft.num = fa.num * c.y;
            ft.den = fa.den * c.x;
            if (ABS(ft.den) >= 0x1000) {
                ft.num /= 4096;
                ft.den /= 4096;
            }
            tFix = FIX_DIV(ft.num, ft.den);
            if (tFix < 0) {
                w[1] = 0;
            } else {
                d.x = ray[1].x; d.y = ray[1].y; d.z = ray[1].z;
                b.x = (ray[1].x * tFix) >> 16;
                a.x = ray[0].x + b.x;
                b.x = a.x - ray[0].x;
                b.y = (ray[1].y * tFix) >> 16;
                a.y = ray[0].y + b.y;
                b.y = a.y - ray[0].y;
                b.z = (ray[1].z * tFix) >> 16;
                a.z = ray[0].z + b.z;
                b.z = a.z - ray[0].z;
                Square0(&d, &sq);
                w[0] = sq.x + sq.y + sq.z;
                w[0] = SquareRoot0(w[0]);
                Square0(&b, &u.sq);
                w[2] = u.sq.x + u.sq.y + u.sq.z;
                w[2] = SquareRoot0(w[2]);
                if (w[0] >= w[2]) {
                    len[0] = w[2];
                    w[1] = 1;
                    hit.x = a.x;
                    hit.y = a.y;
                    hit.z = a.z;
                } else {
                    w[1] = 0;
                }
            }
        }
        if (w[1] == 1) {
            ModelVec *p;
            s16 *x0 = &u.box[0].x;
            s16 *y0 = &u.box[0].y;
            s16 *z0 = &u.box[0].z;
            s16 *x1 = &u.box[1].x;
            s16 *y1 = &u.box[1].y;
            s16 *z1 = &u.box[1].z;

            p = corners;
            u.box[0] = *p;
            u.box[1] = u.box[0];
            for (i = 0; i < vertCount - 1; i++) {
                p++;
                if (p->x < *x0) *x0 = p->x;
                if (p->y < *y0) *y0 = p->y;
                if (p->z < *z0) *z0 = p->z;
                if (*x1 < p->x) *x1 = p->x;
                if (*y1 < p->y) *y1 = p->y;
                if (*z1 < p->z) *z1 = p->z;
            }
            if (hit.x >= u.box[0].x - 24 && hit.y >= u.box[0].y - 24 && hit.z >= u.box[0].z - 24 &&
                u.box[1].x + 24 >= hit.x && u.box[1].y + 24 >= hit.y && u.box[1].z + 24 >= hit.z) {
                found = 1;
                if (len[0] < *hitDist) {
                    *hitDist = len[0];
                    *hitPos = hit;
                    if (hitHeight != NULL) {
                        *hitHeight = hit.y - u.box[0].y;
                    }
                }
            }
        }
    }
    return found;
}

/* Walks the primitives of a model object, one per call, and copies up to four corners to out */
void *ModelObject_NextPrim(ModelObjectView *modelObject, ModelPrim *prim, s32 *count, ModelVec *out, u32 *primIndex) {
    s32 idx[4];
    s32 size;
    s32 i;
    ModelEntry *model;
    ModelVertex *verts;
    ModelVertex *v;

    model = modelObject->entry;
    if (model->primitiveCount == 0 || *primIndex >= model->primitiveCount) {
        return NULL;
    }
    if (*primIndex == 0) {
        prim = model->primitives;
    }
    *count = 4;
    switch (prim->mode) {
    case 0x20:
    case 0x22:
        if (prim->flag & 4) {
            idx[0] = prim->i12;
            idx[1] = prim->i14;
            idx[2] = prim->i16;
            size = 0x18;
        } else {
            idx[0] = prim->v1;
            idx[1] = prim->v2;
            idx[2] = prim->v3;
            size = 0x10;
        }
        *count = 3;
        break;
    case 0x21:
    case 0x23:
        idx[0] = prim->v0;
        idx[1] = prim->v1;
        idx[2] = prim->v2;
        size = 0x10;
        *count = 3;
        break;
    case 0x24:
    case 0x26:
        idx[0] = prim->i12;
        idx[1] = prim->i14;
        idx[2] = prim->i16;
        size = 0x18;
        *count = 3;
        break;
    case 0x25:
    case 0x27:
        idx[0] = prim->i14;
        idx[1] = prim->i16;
        idx[2] = prim->i18;
        size = 0x1C;
        *count = 3;
        break;
    case 0x28:
    case 0x2A:
        if (prim->flag & 4) {
            idx[0] = prim->i16;
            idx[1] = prim->i18;
            idx[2] = prim->i1A;
            idx[3] = prim->i1C;
            size = 0x20;
        } else {
            idx[0] = prim->v1;
            idx[1] = prim->v2;
            idx[2] = prim->v3;
            idx[3] = prim->i10;
            size = 0x14;
        }
        break;
    case 0x29:
    case 0x2B:
        idx[0] = prim->v0;
        idx[1] = prim->v1;
        idx[2] = prim->v2;
        idx[3] = prim->v3;
        size = 0x10;
        break;
    case 0x2C:
    case 0x2E:
        idx[0] = prim->i16;
        idx[1] = prim->i18;
        idx[2] = prim->i1A;
        idx[3] = prim->i1C;
        size = 0x20;
        break;
    case 0x2D:
    case 0x2F:
        idx[0] = prim->i18;
        idx[1] = prim->i1A;
        idx[2] = prim->i1C;
        idx[3] = prim->i1E;
        size = 0x20;
        break;
    case 0x30:
    case 0x32:
        if (prim->flag & 4) {
            idx[0] = prim->i12;
            idx[1] = prim->i16;
            idx[2] = prim->i1A;
            size = 0x1C;
        } else {
            idx[0] = prim->v1;
            idx[1] = prim->v3;
            idx[2] = prim->i12;
            size = 0x14;
        }
        *count = 3;
        break;
    case 0x31:
    case 0x33:
        idx[0] = prim->i10;
        idx[1] = prim->i12;
        idx[2] = prim->i14;
        size = 0x18;
        *count = 3;
        break;
    case 0x34:
    case 0x36:
        idx[0] = prim->i12;
        idx[1] = prim->i16;
        idx[2] = prim->i1A;
        size = 0x1C;
        *count = 3;
        break;
    case 0x35:
    case 0x37:
        idx[0] = prim->i1C;
        idx[1] = prim->i1E;
        idx[2] = prim->i20;
        size = 0x24;
        *count = 3;
        break;
    case 0x38:
    case 0x3A:
        if (prim->flag & 4) {
            idx[0] = prim->i16;
            idx[1] = prim->i1A;
            idx[2] = prim->i1E;
            idx[3] = prim->i22;
            size = 0x24;
        } else {
            idx[0] = prim->v1;
            idx[1] = prim->v3;
            idx[2] = prim->i12;
            idx[3] = prim->i16;
            size = 0x18;
        }
        break;
    case 0x39:
    case 0x3B:
        idx[0] = prim->i14;
        idx[1] = prim->i16;
        idx[2] = prim->i18;
        idx[3] = prim->i1A;
        size = 0x1C;
        break;
    case 0x3C:
    case 0x3E:
        idx[0] = prim->i16;
        idx[1] = prim->i1A;
        idx[2] = prim->i1E;
        idx[3] = prim->i22;
        size = 0x24;
        break;
    case 0x3D:
    case 0x3F:
        idx[0] = prim->i24;
        idx[1] = prim->i26;
        idx[2] = prim->i28;
        idx[3] = prim->i2A;
        size = 0x2C;
        break;
    default:
        *count = 0;
        break;
    }
    verts = modelObject->entry->vertices;
    for (i = 0; i < *count; i++) {
        v = &verts[idx[i]];
        *out = v->pos;
        out++;
    }
    (*primIndex)++;
    return (u8 *)prim + size;
}

/* Moves the CLUT of the model's first primitive: CBA = clut x / 16 + clut y * 64 */
void ModelObject_OffsetClut(ModelObjectView *modelObject, ClutOffset *offset) {
    ModelPrim *prim = modelObject->entry->primitives;
    prim->clut += offset->x / 16;
    prim->clut += offset->y * 64;
}

/* Sets the CLUT of the model's first primitive to the VRAM position pos */
void ModelObject_SetClut(ModelObjectView *modelObject, ClutPos *pos) {
    ModelPrim *prim = modelObject->entry->primitives;

    prim->clut = pos->x / 16;
    prim->clut += pos->y * 64;
}

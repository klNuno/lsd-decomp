#include "common.h"

/* A vector of three s32: the translation of a Matrix, and the points that Render_TransformLongVectors writes. */
typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

/* PSY-Q MATRIX: the rotation m, then the translation t at 0x14. */
typedef struct Matrix {
    s16 m[3][3];        /* 0x00 rotation */
    Vec3 t;             /* 0x14 translation */
} Matrix;

/* PSY-Q VECTOR for the scale: 4.12 fixed point, the code shifts each product right by 12. */
typedef struct Vec4 {
    s32 x;
    s32 y;
    s32 z;
    s32 pad_0C;
} Vec4;

/* PSY-Q GsCOORD2PARAM as this unit reads it: the scale, then the rotation. */
typedef struct Coord2Param {
    Vec4 scale;         /* 0x00 */
    s16 rotate[4];      /* 0x10 SVECTOR, the fourth entry is padding */
} Coord2Param;

/* PSY-Q GsCOORDINATE2 as this unit reads it: flg (0 means the matrix is scaled by param), the local matrix,
 * the world matrix and the param. stage.h's Coord2 has the same offsets but splits each matrix into m and t,
 * so it is not reused here. */
typedef struct Coord2 {
    s32 flg;            /* 0x00 */
    Matrix coord;       /* 0x04 local matrix */
    Matrix workm;       /* 0x24 world matrix */
    Coord2Param *param; /* 0x44 */
} Coord2;

/* A parent node as a child sees it: only its own parent link (at 0x0C) is read. */
typedef struct ParentNode {
    u8 pad_00[0xC];
    s32 unk_0C;         /* 0x0C the parent's own parent link, tested against 0 */
} ParentNode;

/* A box fill as GsSortBoxFill takes it. */
typedef struct BoxFill {
    u32 attribute;      /* 0x00 */
    s16 x;              /* 0x04 */
    s16 y;              /* 0x06 */
} BoxFill;

/* A sprite as GsSortSprite takes it: the attribute word, x and y, then the offsets mx and my. */
typedef struct Sprite {
    u32 attribute;      /* 0x00 */
    s16 x;              /* 0x04 */
    s16 y;              /* 0x06 */
    u8 pad_08[0x10];
    s16 mx;             /* 0x18 added to x */
    s16 my;             /* 0x1A added to y */
    u8 pad_1C[0x8];
} Sprite;

/* A scene node (sender type 4, see scene.h): Scene_DrawNode draws a tree of them. */
typedef struct SceneNode {
    u32 *vtbl;              /* 0x00 vtable; its first word is the tag: low 4 bits the sender type, low byte the kind */
    s32 unk_04;             /* 0x04 first child for List_Next; the walk ends when it reaches 0 */
    u8 pad_08[0x4];
    ParentNode *parent;     /* 0x0C */
    s32 unk_10;             /* 0x10 embedded model object, given to Render_SortModel */
    Coord2 *coord;          /* 0x14 */
    s32 unk_18;             /* 0x18 when set, the model is sorted */
    u8 pad_1C[0x28];
    u16 unk_44;             /* 0x44 box priority; for kind 0x54 its address is the bg data */
    u8 pad_46[0x2];
    s32 unk_48;             /* 0x48 when set, the box size is a percent of half the screen */
    u8 pad_4C[0x4];
    s32 unk_50;             /* 0x50 box width, or its percent */
    s32 unk_54;             /* 0x54 box height, or its percent */
    BoxFill boxFill;        /* 0x58 */
    u8 pad_60[0x4];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0x18];
    s32 unk_A0;             /* 0xA0 sprite x scale, used with half the screen width */
    s32 unk_A4;             /* 0xA4 sprite y scale, used with half the screen height */
} SceneNode;

/* The view that draws the scene nodes. scene.h's View shares the offsets 0x3C, 0x40, 0x4C, 0x74 and 0x78,
 * but has a ScreenPoint at 0x34 and ot[2] at 0x78. */
typedef struct View {
    u8 pad_00[0x34];
    s32 screenWidth;        /* 0x34 (0x100 in scene.h); box and sprite sizes use half of it */
    s32 screenHeight;       /* 0x38 (0xF0 in scene.h) */
    s32 otBits;             /* 0x3C ordering table depth in bits; priorities are below 1 << otBits */
    s32 projection;         /* 0x40 x and y are scaled by projection / z */
    u8 pad_44[0x8];
    s32 unk_4C;             /* 0x4C near distance: nodes with z at or below it are skipped */
    u8 pad_50[0x24];
    s32 buffer;             /* 0x74 the active buffer */
    void *ot[8];            /* 0x78 ordering table of each buffer */
    s32 unk_98;             /* 0x98 divisor: depth index = (z - unk_4C) / unk_98 */
} View;

void RotMatrix(s16 *r, Matrix *m);
void GsGetLs(Coord2 *coord, Matrix *ls);
void GsGetLws(Coord2 *coord, Matrix *lw, Matrix *ls);
void GsSetLightMatrix(Matrix *m);
void GsSetLsMatrix(Matrix *m);
void GsSortBg(void *bg, void *ot, u16 pri);
void GsSortBoxFill(BoxFill *box, void *ot, u16 pri);
void GsSortSprite(Sprite *sp, void *ot, u16 pri);
void List_Next(SceneNode **node, s32 *iter);
void Render_SortModel(void *obj, void *ot, s32 shift, u32 *scratch);
void Render_TransformLongVectors(Vec3 *out, Vec3 *in, s32 n, Matrix *m);

void Scene_DrawNode(View *view, SceneNode *node) {
    Matrix lsbuf;
    Matrix lwbuf;
    SceneNode *child;
    s32 iter;
    Matrix *ls = &lsbuf;
    Matrix *lw = &lwbuf;
    Coord2 *coord;
    Sprite *sp;
    SceneNode *boxNode;
    SceneNode *spriteNode;
    s16 *p;
    s16 *end;
    u32 *s;
    s32 scaled;
    u32 type;
    u32 kind;

    scaled = 0;
    if ((*node->vtbl & 0xFF) == 0x24 && node->unk_10 < 0) {
        return;
    }
    coord = node->coord;
    if (coord->flg == 0) {
        s = (u32 *)&coord->param->scale.x;
        scaled = 1;
        end = &coord->coord.m[2][2] + 1;
        RotMatrix(coord->param->rotate, &coord->coord);
        for (p = coord->coord.m[0]; p < end;) {
            *p = *p * *s >> 12;
            p++;
            s++;
            *p = *p * *s >> 12;
            p++;
            s++;
            *p = *p * *s >> 12;
            p++;
            s -= 2;
        }
    }
    child = NULL;
    do {
        for (;;) {
            if (child == NULL) {
                iter = node->unk_04;
            }
            List_Next(&child, &iter);
            if (child != NULL && (*child->vtbl & 0xF) == 4 && child->parent == (ParentNode *)node) {
                break;
            }
            if (iter == 0) {
                child = NULL;
                break;
            }
        }
        if (child != NULL) {
            if (scaled) {
                child->coord->flg = 0;
            }
            Scene_DrawNode(view, child);
        }
    } while (iter != 0);

    type = *node->vtbl;
    kind = type & 0xFF;
    if (kind == 0x54) {
        GsSortBg(&node->unk_44, view->ot[view->buffer], (1 << view->otBits) - 1);
    } else if (kind == 0x64) {
        boxNode = node;
        if (boxNode->unk_48 != 0) {
            boxNode->boxFill.x = (view->screenWidth >> 1) * boxNode->unk_50 / 100;
            boxNode->boxFill.y = (view->screenHeight >> 1) * boxNode->unk_54 / 100;
        } else {
            boxNode->boxFill.x = boxNode->unk_50;
            boxNode->boxFill.y = boxNode->unk_54;
        }
        GsSortBoxFill(&boxNode->boxFill, view->ot[view->buffer], boxNode->unk_44);
    } else if (kind != 0x44) {
        GsGetLws(node->coord, lw, ls);
        GsSetLightMatrix(lw);
        GsSetLsMatrix(ls);
        if (node->unk_18 != 0) {
            Render_SortModel(&node->unk_10, view->ot[view->buffer], 14 - view->otBits, (u32 *)0x1F800000);
        }
    } else {
        Vec3 pos[2];

        if ((type & 0xFFF) == 0x144) {
            SceneNode *spr = node;
            s32 *dim;

            sp = &spr->sprite;
            dim = &view->screenWidth;
            sp->x = spr->unk_A0 != 0 ? (dim[0] >> 1) * 100 / (10000 / spr->unk_A0) : 0;
            sp->y = spr->unk_A4 != 0 ? (dim[1] >> 1) * 100 / (10000 / spr->unk_A4) : 0;
            sp->x += sp->mx;
            sp->y += sp->my;
            GsSortSprite(sp, view->ot[view->buffer], 0);
            return;
        }
        GsGetLs(node->coord, ls);
        if (ls->t.z - 1 > 0xFFFEU) {
            return;
        }
        if (node->parent->unk_0C != 0) {
            Render_TransformLongVectors(pos, &node->coord->coord.t, 1, ls);
            pos->x += lsbuf.t.x;
            pos->y += lsbuf.t.y;
            pos->z += lsbuf.t.z;
        } else {
            *pos = lsbuf.t;
        }
        if (pos->z > view->unk_4C) {
            pos->x = pos->x * view->projection / pos->z;
            pos->y = pos->y * view->projection / pos->z;
            pos->z = (pos->z - view->unk_4C) / view->unk_98;
            spriteNode = node;
            if ((pos->x < 0 ? ~pos->x + 1 : pos->x) <= 0x200) {
                spriteNode->sprite.x = pos->x;
            } else {
                spriteNode->sprite.x = 0x200;
            }
            if ((pos->y < 0 ? ~pos->y + 1 : pos->y) <= 0x200) {
                spriteNode->sprite.y = pos->y;
            } else {
                spriteNode->sprite.y = 0x200;
            }
            GsSortSprite(&spriteNode->sprite, view->ot[view->buffer], pos->z);
        }
    }
}

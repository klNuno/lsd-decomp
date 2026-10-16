#include "common.h"
#include "game/gs.h"
#include "game/scene.h"
#include "game/scene_draw.h"
#include "game/heap.h"
#include "game/render.h"
#include "game/scene_node.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

/* A parent node as a child sees it: only its own parent link (at 0x0C) is read. */
typedef struct ParentNode {
    u8 pad_00[0xC];
    s32 parent;         /* 0x0C the parent's own parent link, tested against 0 */
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

/* Any scene node as Scene_DrawNode reads it (scene.h SceneNode, then the fields of the kind it draws:
   Box at +0x44 to +0x58 with a u16 priority, Sprite at +0x64, ScreenSprite's scale at +0xA0). */
typedef struct DrawNode {
    u32 *vtbl;              /* 0x00 vtable; its first word is the tag: low 4 bits the sender type, low byte the kind */
    s32 firstChild;         /* 0x04 first child for List_Next; the walk ends when it reaches 0 */
    u8 pad_08[0x4];
    ParentNode *parent;     /* 0x0C */
    s32 model;              /* 0x10 embedded model object, given to Render_SortModel; negative skips kind 0x24 */
    Coord2 *coord;          /* 0x14 */
    s32 modelShown;         /* 0x18 when set, the model is sorted */
    u8 pad_1C[0x28];
    u16 priority;           /* 0x44 box priority; for kind 0x54 its address is the bg data */
    u8 pad_46[0x2];
    s32 percent;            /* 0x48 when set, the box size is a percent of half the screen */
    u8 pad_4C[0x4];
    s32 boxW;               /* 0x50 box width, or its percent */
    s32 boxH;               /* 0x54 box height, or its percent */
    BoxFill boxFill;        /* 0x58 */
    u8 pad_60[0x4];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0x18];
    s32 scaleX;             /* 0xA0 sprite x scale, used with half the screen width */
    s32 scaleY;             /* 0xA4 sprite y scale, used with half the screen height */
} DrawNode;

void RotMatrix(s16 *r, Matrix *m);
void GsGetLs(Coord2 *coord, Matrix *ls);
void GsGetLws(Coord2 *coord, Matrix *lw, Matrix *ls);
void GsSetLightMatrix(Matrix *m);
void GsSetLsMatrix(Matrix *m);
void GsSortBg(void *bg, void *ot, u16 pri);
void GsSortBoxFill(BoxFill *box, void *ot, u16 pri);
void GsSortSprite(Sprite *sp, void *ot, u16 pri);

void Scene_DrawNode(View *view, DrawNode *node) {
    Matrix lsbuf;
    Matrix lwbuf;
    DrawNode *child;
    s32 iter;
    Matrix *ls = &lsbuf;
    Matrix *lw = &lwbuf;
    Coord2 *coord;
    Sprite *sp;
    DrawNode *boxNode;
    DrawNode *spriteNode;
    s16 *p;
    s16 *end;
    u32 *s;
    s32 scaled;
    u32 type;
    u32 kind;

    scaled = 0;
    if ((*node->vtbl & 0xFF) == 0x24 && node->model < 0) {
        return;
    }
    coord = node->coord;
    if (coord->flg == 0) {
        s = (u32 *)&coord->param->scale[0];
        scaled = 1;
        end = &coord->coord.m[2][2] + 1;
        RotMatrix(coord->param->rotate.axis, &coord->coord);
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
                iter = node->firstChild;
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
        GsSortBg(&node->priority, view->ot[view->buffer], (1 << view->otBits) - 1);
    } else if (kind == 0x64) {
        boxNode = node;
        if (boxNode->percent != 0) {
            boxNode->boxFill.x = (view->screenSize.x >> 1) * boxNode->boxW / 100;
            boxNode->boxFill.y = (view->screenSize.y >> 1) * boxNode->boxH / 100;
        } else {
            boxNode->boxFill.x = boxNode->boxW;
            boxNode->boxFill.y = boxNode->boxH;
        }
        GsSortBoxFill(&boxNode->boxFill, view->ot[view->buffer], boxNode->priority);
    } else if (kind != 0x44) {
        GsGetLws(node->coord, lw, ls);
        GsSetLightMatrix(lw);
        GsSetLsMatrix(ls);
        if (node->modelShown != 0) {
            Render_SortModel(&node->model, view->ot[view->buffer], 14 - view->otBits, (u32 *)0x1F800000);
        }
    } else {
        Vec3 pos[2];

        if ((type & 0xFFF) == 0x144) {
            DrawNode *spr = node;
            s32 *dim;

            sp = &spr->sprite;
            dim = &view->screenSize.x;
            sp->x = spr->scaleX != 0 ? (dim[0] >> 1) * 100 / (10000 / spr->scaleX) : 0;
            sp->y = spr->scaleY != 0 ? (dim[1] >> 1) * 100 / (10000 / spr->scaleY) : 0;
            sp->x += sp->mx;
            sp->y += sp->my;
            GsSortSprite(sp, view->ot[view->buffer], 0);
            return;
        }
        GsGetLs(node->coord, ls);
        if (ls->t.z - 1 > 0xFFFEU) {
            return;
        }
        if (node->parent->parent != 0) {
            Render_TransformLongVectors(pos, &node->coord->coord.t, 1, ls);
            pos->x += lsbuf.t.x;
            pos->y += lsbuf.t.y;
            pos->z += lsbuf.t.z;
        } else {
            *pos = lsbuf.t;
        }
        /* unk4C is the near plane (View_Reset stores 10): a sprite behind it is dropped.
           unk98 is the OT z step, (far - near) / OT length + 1, computed by the view's frame setup. */
        if (pos->z > view->nearZ) {
            pos->x = pos->x * view->projection / pos->z;
            pos->y = pos->y * view->projection / pos->z;
            pos->z = (pos->z - view->nearZ) / view->unk98;
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

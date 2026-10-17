#include "common.h"
#include "game/scene_draw.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/render.h"
#include "game/scene_node.h"
#include "game/view.h"
#include "psyq/libgte.h"
#include "psyq/libgs.h"

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

/* Any scene node as View_DrawNode reads it (scene_node.h SceneNode, then the fields of the kind it draws:
   Box at +0x44 to +0x58 with a u16 priority, Sprite at +0x64, ScreenSprite's position at +0xA0). */
typedef struct DrawNode {
    u32 *vtbl;              /* 0x00 vtable; its first word is the tag: low 4 bits the sender type, low byte the kind */
    ListNode *watched;      /* 0x04 the watched objects, its children among them (List_Next) */
    u8 pad_08[0x4];
    ParentNode *parent;     /* 0x0C */
    DObj2 object;       /* 0x10 the GsDOBJ2 given to Render_SortModel: attribute bit 31 skips kind 0x24,
                               the model is sorted only when set */
    u8 pad_1C[0x28];
    u16 priority;           /* 0x44 box priority; for kind 0x54 its address is the bg data */
    u8 pad_46[0x2];
    s32 percent;            /* 0x48 when set, the box size is a percent of half the screen */
    u8 pad_4C[0x4];
    s32 boxX;               /* 0x50 box width, or its percent */
    s32 boxY;               /* 0x54 box height, or its percent */
    BoxFill boxFill;        /* 0x58 */
    u8 pad_60[0x4];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0x18];
    s32 spriteX;             /* 0xA0 ScreenSprite.position x, in percent of half the screen width */
    s32 spriteY;             /* 0xA4 ScreenSprite.position y, in percent of half the screen height */
} DrawNode;


void View_DrawNode(View *view, DrawNode *node) {
    Matrix lsbuf;
    Matrix lwbuf;
    DrawNode *child;
    ListNode *iter;
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
    if ((*node->vtbl & 0xFF) == 0x24 && (s32)node->object.attribute < 0) {
        return;
    }
    coord = node->object.coord;
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
                iter = node->watched;
            }
            List_Next((Object **)&child, &iter);
            if (child != NULL && (*child->vtbl & 0xF) == 4 && child->parent == (ParentNode *)node) {
                break;
            }
            if (iter == NULL) {
                child = NULL;
                break;
            }
        }
        if (child != NULL) {
            if (scaled) {
                child->object.coord->flg = 0;
            }
            View_DrawNode(view, child);
        }
    } while (iter != NULL);

    type = *node->vtbl;
    kind = type & 0xFF;
    if (kind == 0x54) {
        GsSortBg(&node->priority, view->ot[view->buffer], (1 << view->otBits) - 1);
    } else if (kind == 0x64) {
        boxNode = node;
        if (boxNode->percent != 0) {
            boxNode->boxFill.x = (view->screenSize.x >> 1) * boxNode->boxX / 100;
            boxNode->boxFill.y = (view->screenSize.y >> 1) * boxNode->boxY / 100;
        } else {
            boxNode->boxFill.x = boxNode->boxX;
            boxNode->boxFill.y = boxNode->boxY;
        }
        GsSortBoxFill(&boxNode->boxFill, view->ot[view->buffer], boxNode->priority);
    } else if (kind != 0x44) {
        GsGetLws(node->object.coord, lw, ls);
        GsSetLightMatrix(lw);
        GsSetLsMatrix(ls);
        if (node->object.tmd != NULL) {
            Render_SortModel(&node->object, view->ot[view->buffer], 14 - view->otBits, (struct TmdCtx *)0x1F800000);
        }
    } else {
        Vec3 pos[2];

        if ((type & 0xFFF) == 0x144) {
            DrawNode *spr = node;
            s32 *dim;

            sp = &spr->sprite;
            dim = &view->screenSize.x;
            sp->x = spr->spriteX != 0 ? (dim[0] >> 1) * 100 / (10000 / spr->spriteX) : 0;
            sp->y = spr->spriteY != 0 ? (dim[1] >> 1) * 100 / (10000 / spr->spriteY) : 0;
            sp->x += sp->mx;
            sp->y += sp->my;
            GsSortSprite(sp, view->ot[view->buffer], 0);
            return;
        }
        GsGetLs(node->object.coord, ls);
        if (ls->t.z - 1 > 0xFFFEU) {
            return;
        }
        if (node->parent->parent != 0) {
            Vec_TransformLong(pos, &node->object.coord->coord.t, 1, ls);
            pos->x += lsbuf.t.x;
            pos->y += lsbuf.t.y;
            pos->z += lsbuf.t.z;
        } else {
            *pos = lsbuf.t;
        }
        /* nearZ is the near plane (View_Reset stores 10): a sprite behind it is dropped.
           otZStep is the OT z step, (far - near) / OT length + 1, computed by the view's frame setup. */
        if (pos->z > view->nearZ) {
            pos->x = pos->x * view->projection / pos->z;
            pos->y = pos->y * view->projection / pos->z;
            pos->z = (pos->z - view->nearZ) / view->otZStep;
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

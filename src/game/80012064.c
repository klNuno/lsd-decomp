#include "common.h"

typedef struct Unk_80012064_Vec3 {
    s32 vx;
    s32 vy;
    s32 vz;
} Unk_80012064_Vec3;
typedef struct Unk_80012064_Mat {
    s16 m[3][3];
    Unk_80012064_Vec3 t;
} Unk_80012064_Mat;
typedef struct Unk_80012064_Vec {
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} Unk_80012064_Vec;
typedef struct Unk_80012064_Param {
    Unk_80012064_Vec scale;
    s16 rotate[4];
} Unk_80012064_Param;
typedef struct Unk_80012064_Coord {
    s32 flg;
    Unk_80012064_Mat coord;
    Unk_80012064_Mat workm;
    Unk_80012064_Param *param;
} Unk_80012064_Coord;
typedef struct Unk_80012064_Parent {
    u8 pad_00[0xC];
    s32 unkC;
} Unk_80012064_Parent;
typedef struct Unk_80012064_Box {
    u32 attribute;
    s16 x;
    s16 y;
} Unk_80012064_Box;
typedef struct Unk_80012064_Sprite {
    u32 attribute;
    s16 x;
    s16 y;
    u8 pad_08[0x10];
    s16 mx;
    s16 my;
    u8 pad_1C[0x8];
} Unk_80012064_Sprite;
typedef struct Unk_80012064_Node {
    u32 *unk0;
    s32 unk4;
    u8 pad_08[0x4];
    Unk_80012064_Parent *unkC;
    s32 unk10;
    Unk_80012064_Coord *unk14;
    s32 unk18;
    u8 pad_1C[0x28];
    u16 unk44;
    u8 pad_46[0x2];
    s32 unk48;
    u8 pad_4C[0x4];
    s32 unk50;
    s32 unk54;
    Unk_80012064_Box unk58;
    u8 pad_60[0x4];
    Unk_80012064_Sprite unk64;
    u8 pad_88[0x18];
    s32 unkA0;
    s32 unkA4;
} Unk_80012064_Node;
typedef struct Unk_80012064_Scene {
    u8 pad_00[0x34];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    u8 pad_44[0x8];
    s32 unk4C;
    u8 pad_50[0x24];
    s32 unk74;
    void *unk78[8];
    s32 unk98;
} Unk_80012064_Scene;
void RotMatrix(s16 *r, Unk_80012064_Mat *m);
void GsGetLs(Unk_80012064_Coord *coord, Unk_80012064_Mat *ls);
void GsGetLws(Unk_80012064_Coord *coord, Unk_80012064_Mat *lw, Unk_80012064_Mat *ls);
void GsSetLightMatrix(Unk_80012064_Mat *m);
void GsSetLsMatrix(Unk_80012064_Mat *m);
void GsSortBg(void *bg, void *ot, u16 pri);
void GsSortBoxFill(Unk_80012064_Box *box, void *ot, u16 pri);
void GsSortSprite(Unk_80012064_Sprite *sp, void *ot, u16 pri);
void func_800183A0(Unk_80012064_Node **node, s32 *iter);
void func_80018464(void *obj, void *ot, s32 shift, u32 *scratch);
void func_8001EE98(Unk_80012064_Vec3 *out, Unk_80012064_Vec3 *in, s32 n, Unk_80012064_Mat *m);

void func_80012064(Unk_80012064_Scene *scene, Unk_80012064_Node *node) {
    Unk_80012064_Mat lsbuf;
    Unk_80012064_Mat lwbuf;
    Unk_80012064_Node *child;
    s32 iter;
    Unk_80012064_Mat *ls = &lsbuf;
    Unk_80012064_Mat *lw = &lwbuf;
    Unk_80012064_Coord *coord;
    Unk_80012064_Sprite *sp;
    Unk_80012064_Node *box;
    Unk_80012064_Node *sn;
    s16 *p;
    s16 *end;
    u32 *s;
    s32 scaled;
    u32 type;
    u32 kind;

    scaled = 0;
    if ((*node->unk0 & 0xFF) == 0x24 && node->unk10 < 0) {
        return;
    }
    coord = node->unk14;
    if (coord->flg == 0) {
        s = (u32 *)&coord->param->scale.vx;
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
                iter = node->unk4;
            }
            func_800183A0(&child, &iter);
            if (child != NULL && (*child->unk0 & 0xF) == 4 && child->unkC == (Unk_80012064_Parent *)node) {
                break;
            }
            if (iter == 0) {
                child = NULL;
                break;
            }
        }
        if (child != NULL) {
            if (scaled) {
                child->unk14->flg = 0;
            }
            func_80012064(scene, child);
        }
    } while (iter != 0);

    type = *node->unk0;
    kind = type & 0xFF;
    if (kind == 0x54) {
        GsSortBg(&node->unk44, scene->unk78[scene->unk74], (1 << scene->unk3C) - 1);
    } else if (kind == 0x64) {
        box = node;
        if (box->unk48 != 0) {
            box->unk58.x = (scene->unk34 >> 1) * box->unk50 / 100;
            box->unk58.y = (scene->unk38 >> 1) * box->unk54 / 100;
        } else {
            box->unk58.x = box->unk50;
            box->unk58.y = box->unk54;
        }
        GsSortBoxFill(&box->unk58, scene->unk78[scene->unk74], box->unk44);
    } else if (kind != 0x44) {
        GsGetLws(node->unk14, lw, ls);
        GsSetLightMatrix(lw);
        GsSetLsMatrix(ls);
        if (node->unk18 != 0) {
            func_80018464(&node->unk10, scene->unk78[scene->unk74], 14 - scene->unk3C, (u32 *)0x1F800000);
        }
    } else {
        Unk_80012064_Vec3 pos[2];

        if ((type & 0xFFF) == 0x144) {
            Unk_80012064_Node *spr = node;
            s32 *dim;

            sp = &spr->unk64;
            dim = &scene->unk34;
            sp->x = spr->unkA0 != 0 ? (dim[0] >> 1) * 100 / (10000 / spr->unkA0) : 0;
            sp->y = spr->unkA4 != 0 ? (dim[1] >> 1) * 100 / (10000 / spr->unkA4) : 0;
            sp->x += sp->mx;
            sp->y += sp->my;
            GsSortSprite(sp, scene->unk78[scene->unk74], 0);
            return;
        }
        GsGetLs(node->unk14, ls);
        if (ls->t.vz - 1 > 0xFFFEU) {
            return;
        }
        if (node->unkC->unkC != 0) {
            func_8001EE98(pos, &node->unk14->coord.t, 1, ls);
            pos->vx += lsbuf.t.vx;
            pos->vy += lsbuf.t.vy;
            pos->vz += lsbuf.t.vz;
        } else {
            *pos = lsbuf.t;
        }
        if (pos->vz > scene->unk4C) {
            pos->vx = pos->vx * scene->unk40 / pos->vz;
            pos->vy = pos->vy * scene->unk40 / pos->vz;
            pos->vz = (pos->vz - scene->unk4C) / scene->unk98;
            sn = node;
            if ((pos->vx < 0 ? ~pos->vx + 1 : pos->vx) <= 0x200) {
                sn->unk64.x = pos->vx;
            } else {
                sn->unk64.x = 0x200;
            }
            if ((pos->vy < 0 ? ~pos->vy + 1 : pos->vy) <= 0x200) {
                sn->unk64.y = pos->vy;
            } else {
                sn->unk64.y = 0x200;
            }
            GsSortSprite(&sn->unk64, scene->unk78[scene->unk74], pos->vz);
        }
    }
}

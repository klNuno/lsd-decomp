#include "common.h"

struct Unk_8001F360 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
};
struct Unk_8001F33C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u32 *unkC;
};
extern void GsMapModelingData(u32 *p);
struct Unk_8001F314_Data {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
};
struct Unk_8001F314 {
    u8 pad_00[0x14];
    struct Unk_8001F314_Data unk14;
};
extern u8 D_8008B21C[];
void func_8001F3B0(void *arg0, u8 *arg1);
struct Unk_800204D0_Q {
    u8 pad_00[0x6];
    u16 unk6;
};
struct Unk_800204D0_P {
    u8 pad_00[0x10];
    struct Unk_800204D0_Q *unk10;
};
struct Unk_800204D0 {
    u8 pad_00[0x10];
    struct Unk_800204D0_P *unk10;
};
struct Unk_800204D0_Arg1 {
    s32 unk0;
    s32 unk4;
};
struct Unk_80020510_Sub {
    u8 pad_00[0x6];
    s16 unk6;
};
struct Unk_80020510_Mid {
    u8 pad_00[0x10];
    struct Unk_80020510_Sub *unk10;
};
struct Unk_80020510 {
    u8 pad_00[0x10];
    struct Unk_80020510_Mid *unk10;
};
struct Unk_80020510_Arg {
    s16 unk0;
    s16 unk2;
};
typedef struct Unk_8001F2B0_Ret {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8001F2B0_Ret;
typedef struct Unk_8001F2B0 {
    s32 unk0;
    u8 pad_04[0x8];
    s32 unkC;
    s32 unk10;
} Unk_8001F2B0;
void *Object_GetBaseVtbl(void);
s32 func_8001F384(void);
void func_8001F394(void *arg0);
struct Unk_8001F250 {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32);
};
void *Heap_Alloc(s32 size);
struct Unk_8001F51C {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 unk2A;
    u16 unk2C;
    u16 unk2E;
    u16 unk30;
    u16 unk32;
};
struct Unk_8001F51C_tmp {
    s32 one;
    u16 buf[6];
};
extern u8 D_8006BEA0[];
s32 D_8008AC4C;
typedef struct Unk_80020050_Prim {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 unk2A;
} Unk_80020050_Prim;
typedef struct Unk_80020050_Vec {
    s16 x;
    s16 y;
    s16 z;
} Unk_80020050_Vec;
typedef struct Unk_80020050_Vert {
    Unk_80020050_Vec v;
    s16 pad;
} Unk_80020050_Vert;
typedef struct Unk_80020050_Model {
    Unk_80020050_Vert *unk0;
    u8 pad_04[0xC];
    Unk_80020050_Prim *unk10;
    u32 unk14;
} Unk_80020050_Model;
typedef struct Unk_80020050 {
    u8 pad_00[0x10];
    Unk_80020050_Model *unk10;
} Unk_80020050;
typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Unk_8001F66C_V;
typedef struct {
    Unk_8001F66C_V v[8];
} Unk_8001F66C_Rec;
struct Unk_8001F66C {
    s32 count;
    Unk_8001F66C_Rec recs[1];
};
typedef struct Unk_8001F3B0_Vec {
    s16 x, y, z;
} Unk_8001F3B0_Vec;
typedef struct Unk_8001F3B0_Box {
    Unk_8001F3B0_Vec min;
    Unk_8001F3B0_Vec max;
} Unk_8001F3B0_Box;
typedef struct Unk_8001F3B0_Vert {
    s16 x, y, z, pad;
} Unk_8001F3B0_Vert;
typedef struct Unk_8001F3B0_Mesh {
    Unk_8001F3B0_Vert *verts;
    s32 count;
} Unk_8001F3B0_Mesh;
typedef struct Unk_8001F3B0 {
    u8 pad_00[0x10];
    Unk_8001F3B0_Mesh *unk10;
} Unk_8001F3B0;
void *func_80020050(Unk_80020050 *arg0, Unk_80020050_Prim *prim, s32 *count, Unk_80020050_Vec *out, u32 *index);
typedef struct Unk_8001F8B8_LVec { s32 x; s32 y; s32 z; s32 pad; } Unk_8001F8B8_LVec;
typedef struct Unk_8001F8B8_SVec { s16 x; s16 y; s16 z; s16 pad; } Unk_8001F8B8_SVec;
typedef struct Unk_8001F8B8_Frac { s32 num; s32 den; } Unk_8001F8B8_Frac;
void OuterProduct0(Unk_8001F8B8_LVec *a, Unk_8001F8B8_LVec *b, Unk_8001F8B8_LVec *out);
void Square0(Unk_8001F8B8_LVec *in, Unk_8001F8B8_LVec *out);
s32 SquareRoot0(s32 a);
#define ABS(x) ((x) < 0 ? ~(x) + 1 : (x))
#define FIX_DIV(n, d) ((((n) / (d)) != 0 ? ((n) / (d)) << 16 : ((n) * (d)) & 0x80000000) | (ABS((n) % (d)) << 16) / ABS(d))


void *func_8001F250(s32 arg0) {
    void *temp;

    temp = Heap_Alloc(0x24);
    if (temp != 0) {
        ((struct Unk_8001F250 *)func_8001F384())->unk8(temp, arg0);
        return temp;
    }
    return 0;
}

void func_8001F2B0(Unk_8001F2B0 *arg0, s32 arg1) {
    s32 temp;

    ((Unk_8001F2B0_Ret *)Object_GetBaseVtbl())->unk8(arg0);
    temp = func_8001F384();
    arg0->unk10 = arg1;
    arg0->unk0 = temp;
    arg0->unkC = arg1 - 0xC;
    func_8001F394(arg0);
}

void func_8001F314(struct Unk_8001F314 *arg0, struct Unk_8001F314_Data *arg1) {
    arg0->unk14 = *arg1;
}

void func_8001F33C(struct Unk_8001F33C *arg0) {
    GsMapModelingData(arg0->unkC + 1);
}

s32 func_8001F360(struct Unk_8001F360 *arg0, s32 arg1) {
    s32 offset = arg1 * 0x1C + 0xC;
    return offset + arg0->unkC;
}

void func_8001F37C(void) {
}

s32 func_8001F384(void) {
    return (s32)D_8006BEA0;
}

void func_8001F394(void *arg0) {
    D_8008AC4C = 1;
}

s32 func_8001F3A4(s32 arg0) {
    return D_8008AC4C;
}

void func_8001F3B0(void *arg0, u8 *arg1) {
    Unk_8001F3B0_Box *box;
    Unk_8001F3B0_Vert *v;
    s16 *miny;
    s16 *minz;
    s16 *maxx;
    s16 *maxy;
    s16 *maxz;
    s32 n;
    s32 i;

    box = (Unk_8001F3B0_Box *)arg1;
    miny = &box->min.y;
    minz = &box->min.z;
    maxx = &box->max.x;
    maxy = &box->max.y;
    maxz = &box->max.z;
    v = ((Unk_8001F3B0 *)arg0)->unk10->verts;
    n = ((Unk_8001F3B0 *)arg0)->unk10->count - 1;
    box->min.x = v->x;
    box->min.y = v->y;
    box->min.z = v->z;
    box->max = box->min;
    for (i = 0; i < n; i++) {
        v++;
        if (v->x < box->min.x) {
            box->min.x = v->x;
        }
        if (v->y < *miny) {
            *miny = v->y;
        }
        if (v->z < *minz) {
            *minz = v->z;
        }
        if (*maxx < v->x) {
            *maxx = v->x;
        }
        if (*maxy < v->y) {
            *maxy = v->y;
        }
        if (*maxz < v->z) {
            *maxz = v->z;
        }
    }
}

void func_8001F4E4(void *arg0) {
    func_8001F3B0(arg0, D_8008B21C);
}

void *func_8001F50C(void) {
    return D_8008B21C;
}

void func_8001F51C(void *arg0, struct Unk_8001F51C *arg1) {
    struct Unk_8001F51C_tmp t;

    func_8001F3B0(arg0, (u8 *)t.buf);
    t.one = 1;
    arg1->unk4 = t.buf[0];
    arg1->unk6 = t.buf[1];
    arg1->unk8 = t.buf[2];
    arg1->unkA = t.buf[0];
    arg1->unkC = t.buf[4];
    arg1->unkE = t.buf[2];
    arg1->unk10 = t.buf[3];
    arg1->unk12 = t.buf[4];
    arg1->unk14 = t.buf[2];
    arg1->unk16 = t.buf[3];
    arg1->unk18 = t.buf[1];
    arg1->unk1A = t.buf[2];
    arg1->unk1C = t.buf[0];
    arg1->unk1E = t.buf[1];
    arg1->unk20 = t.buf[5];
    arg1->unk22 = t.buf[0];
    arg1->unk24 = t.buf[4];
    arg1->unk26 = t.buf[5];
    arg1->unk28 = t.buf[3];
    arg1->unk2A = t.buf[4];
    arg1->unk2C = t.buf[5];
    arg1->unk2E = t.buf[3];
    arg1->unk30 = t.buf[1];
    arg1->unk32 = t.buf[5];
    arg1->unk0 = 1;
}

void func_8001F66C(struct Unk_8001F66C *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_8001F66C_Rec t;
    Unk_8001F66C_Rec *rec;
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        rec = &arg0->recs[i];
        if (arg1 != 0) {
            t = *rec;
            rec->v[3] = t.v[0];
            rec->v[2] = t.v[1];
            rec->v[6] = t.v[2];
            rec->v[7] = t.v[3];
            rec->v[0] = t.v[4];
            rec->v[1] = t.v[5];
            rec->v[5] = t.v[6];
            rec->v[4] = t.v[7];
            if (arg2 == 0) {
                s32 j;

                for (j = 0; j < 4; j++) {
                    rec->v[j].x += arg3;
                }
            } else {
                Unk_8001F66C_V *p = rec->v;
                s32 j;

                for (j = 0; j < 4; j++) {
                    p[j + 4].x += arg3;
                }
            }
        } else {
            if (arg2 == 0) {
                s32 j;

                for (j = 0; j < 4; j++) {
                    rec->v[j].z += arg3;
                }
            } else {
                Unk_8001F66C_V *p = rec->v;
                s32 j;

                for (j = 0; j < 4; j++) {
                    p[j + 4].z += arg3;
                }
            }
        }
    }
}

s32 func_8001F8B8(Unk_80020050 *arg0, s32 *dist, Unk_80020050_Vec *hitOut, s32 *heightOut,
                  Unk_80020050_Vec *from, Unk_80020050_Vec *to) {
    Unk_80020050_Vec v[4];
    Unk_8001F8B8_LVec n;
    Unk_80020050_Vec ray[2];
    Unk_80020050_Vec hit;
    s32 count;
    u32 index;
    Unk_80020050_Prim *prim;
    s32 ret;
    s32 fx, i;

    index = 0;
    *dist = 0x7FFFFFFF;
    ray[0].x = from->x;
    ray[0].y = from->y;
    ray[0].z = from->z;
    ray[1].x = to->x - from->x;
    ray[1].y = to->y - from->y;
    ray[1].z = to->z - from->z;
    ret = 0;
    while ((prim = func_80020050(arg0, prim, &count, v, &index)) != NULL) {
        Unk_8001F8B8_LVec spare;
        Unk_8001F8B8_SVec e1;
        Unk_8001F8B8_SVec e2;
        Unk_8001F8B8_LVec c;
        Unk_8001F8B8_LVec a;
        Unk_8001F8B8_LVec b;
        Unk_8001F8B8_Frac fa;
        Unk_8001F8B8_Frac ft;
        s32 w[3];
        Unk_8001F8B8_LVec d;
        Unk_8001F8B8_LVec sq;
        union {
            Unk_8001F8B8_LVec sq;
            Unk_80020050_Vec box[2];
        } u;
        s32 len[2];

        e1.x = v[1].x - v[0].x;
        e1.y = v[1].y - v[0].y;
        e1.z = v[1].z - v[0].z;
        e2.x = v[2].x - v[0].x;
        e2.y = v[2].y - v[0].y;
        e2.z = v[2].z - v[0].z;
        a.x = e1.x; a.y = e1.y; a.z = e1.z;
        b.x = e2.x; b.y = e2.y; b.z = e2.z;
        OuterProduct0(&a, &b, &c);
        n.x = c.x; n.y = c.y; n.z = c.z;
        n.x /= 4096;
        n.y /= 4096;
        n.z /= 4096;
        n.pad = -(v[0].x * n.x + v[0].y * n.y + v[0].z * n.z);
        w[0] = ray[1].x * n.x + ray[1].y * n.y + ray[1].z * n.z;
        if (ABS(w[0]) <= 0) {
            w[1] = 2;
        } else {
            c.x = w[0];
            c.y = 1;
            w[2] = ray[0].x * n.x + ray[0].y * n.y + ray[0].z * n.z;
            w[2] += n.pad;
            fa.num = -w[2];
            fa.den = 1;
            ft.num = fa.num * c.y;
            ft.den = fa.den * c.x;
            if (ABS(ft.den) >= 0x1000) {
                ft.num /= 4096;
                ft.den /= 4096;
            }
            fx = FIX_DIV(ft.num, ft.den);
            if (fx < 0) {
                w[1] = 0;
            } else {
                d.x = ray[1].x; d.y = ray[1].y; d.z = ray[1].z;
                b.x = (ray[1].x * fx) >> 16;
                a.x = ray[0].x + b.x;
                b.x = a.x - ray[0].x;
                b.y = (ray[1].y * fx) >> 16;
                a.y = ray[0].y + b.y;
                b.y = a.y - ray[0].y;
                b.z = (ray[1].z * fx) >> 16;
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
            Unk_80020050_Vec *p;
            s16 *x0 = &u.box[0].x;
            s16 *y0 = &u.box[0].y;
            s16 *z0 = &u.box[0].z;
            s16 *x1 = &u.box[1].x;
            s16 *y1 = &u.box[1].y;
            s16 *z1 = &u.box[1].z;

            p = v;
            u.box[0] = *p;
            u.box[1] = u.box[0];
            for (i = 0; i < count - 1; i++) {
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
                ret = 1;
                if (len[0] < *dist) {
                    *dist = len[0];
                    *hitOut = hit;
                    if (heightOut != NULL) {
                        *heightOut = hit.y - u.box[0].y;
                    }
                }
            }
        }
    }
    return ret;
}

void *func_80020050(Unk_80020050 *arg0, Unk_80020050_Prim *prim, s32 *count, Unk_80020050_Vec *out, u32 *index) {
    s32 idx[4];
    s32 size;
    s32 i;
    Unk_80020050_Model *model;
    Unk_80020050_Vert *verts;
    Unk_80020050_Vert *v;

    model = arg0->unk10;
    if (model->unk14 == 0 || *index >= model->unk14) {
        return NULL;
    }
    if (*index == 0) {
        prim = model->unk10;
    }
    *count = 4;
    switch (prim->unk3) {
    case 0x20:
    case 0x22:
        if (prim->unk2 & 4) {
            idx[0] = prim->unk12;
            idx[1] = prim->unk14;
            idx[2] = prim->unk16;
            size = 0x18;
        } else {
            idx[0] = prim->unkA;
            idx[1] = prim->unkC;
            idx[2] = prim->unkE;
            size = 0x10;
        }
        *count = 3;
        break;
    case 0x21:
    case 0x23:
        idx[0] = prim->unk8;
        idx[1] = prim->unkA;
        idx[2] = prim->unkC;
        size = 0x10;
        *count = 3;
        break;
    case 0x24:
    case 0x26:
        idx[0] = prim->unk12;
        idx[1] = prim->unk14;
        idx[2] = prim->unk16;
        size = 0x18;
        *count = 3;
        break;
    case 0x25:
    case 0x27:
        idx[0] = prim->unk14;
        idx[1] = prim->unk16;
        idx[2] = prim->unk18;
        size = 0x1C;
        *count = 3;
        break;
    case 0x28:
    case 0x2A:
        if (prim->unk2 & 4) {
            idx[0] = prim->unk16;
            idx[1] = prim->unk18;
            idx[2] = prim->unk1A;
            idx[3] = prim->unk1C;
            size = 0x20;
        } else {
            idx[0] = prim->unkA;
            idx[1] = prim->unkC;
            idx[2] = prim->unkE;
            idx[3] = prim->unk10;
            size = 0x14;
        }
        break;
    case 0x29:
    case 0x2B:
        idx[0] = prim->unk8;
        idx[1] = prim->unkA;
        idx[2] = prim->unkC;
        idx[3] = prim->unkE;
        size = 0x10;
        break;
    case 0x2C:
    case 0x2E:
        idx[0] = prim->unk16;
        idx[1] = prim->unk18;
        idx[2] = prim->unk1A;
        idx[3] = prim->unk1C;
        size = 0x20;
        break;
    case 0x2D:
    case 0x2F:
        idx[0] = prim->unk18;
        idx[1] = prim->unk1A;
        idx[2] = prim->unk1C;
        idx[3] = prim->unk1E;
        size = 0x20;
        break;
    case 0x30:
    case 0x32:
        if (prim->unk2 & 4) {
            idx[0] = prim->unk12;
            idx[1] = prim->unk16;
            idx[2] = prim->unk1A;
            size = 0x1C;
        } else {
            idx[0] = prim->unkA;
            idx[1] = prim->unkE;
            idx[2] = prim->unk12;
            size = 0x14;
        }
        *count = 3;
        break;
    case 0x31:
    case 0x33:
        idx[0] = prim->unk10;
        idx[1] = prim->unk12;
        idx[2] = prim->unk14;
        size = 0x18;
        *count = 3;
        break;
    case 0x34:
    case 0x36:
        idx[0] = prim->unk12;
        idx[1] = prim->unk16;
        idx[2] = prim->unk1A;
        size = 0x1C;
        *count = 3;
        break;
    case 0x35:
    case 0x37:
        idx[0] = prim->unk1C;
        idx[1] = prim->unk1E;
        idx[2] = prim->unk20;
        size = 0x24;
        *count = 3;
        break;
    case 0x38:
    case 0x3A:
        if (prim->unk2 & 4) {
            idx[0] = prim->unk16;
            idx[1] = prim->unk1A;
            idx[2] = prim->unk1E;
            idx[3] = prim->unk22;
            size = 0x24;
        } else {
            idx[0] = prim->unkA;
            idx[1] = prim->unkE;
            idx[2] = prim->unk12;
            idx[3] = prim->unk16;
            size = 0x18;
        }
        break;
    case 0x39:
    case 0x3B:
        idx[0] = prim->unk14;
        idx[1] = prim->unk16;
        idx[2] = prim->unk18;
        idx[3] = prim->unk1A;
        size = 0x1C;
        break;
    case 0x3C:
    case 0x3E:
        idx[0] = prim->unk16;
        idx[1] = prim->unk1A;
        idx[2] = prim->unk1E;
        idx[3] = prim->unk22;
        size = 0x24;
        break;
    case 0x3D:
    case 0x3F:
        idx[0] = prim->unk24;
        idx[1] = prim->unk26;
        idx[2] = prim->unk28;
        idx[3] = prim->unk2A;
        size = 0x2C;
        break;
    default:
        *count = 0;
        break;
    }
    verts = arg0->unk10->unk0;
    for (i = 0; i < *count; i++) {
        v = &verts[idx[i]];
        *out = v->v;
        out++;
    }
    (*index)++;
    return (u8 *)prim + size;
}

void func_800204D0(struct Unk_800204D0 *arg0, struct Unk_800204D0_Arg1 *arg1) {
    struct Unk_800204D0_Q *q = arg0->unk10->unk10;
    q->unk6 += arg1->unk0 / 16;
    q->unk6 += arg1->unk4 * 64;
}

void func_80020510(struct Unk_80020510 *arg0, struct Unk_80020510_Arg *arg1) {
    struct Unk_80020510_Sub *sub = arg0->unk10->unk10;

    sub->unk6 = arg1->unk0 / 16;
    sub->unk6 += arg1->unk2 * 64;
}

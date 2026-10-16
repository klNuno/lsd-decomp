#include "common.h"
#include "game/heap.h"
#include "game/entity.h"

struct Unk_8001D600 {
    u8 pad_00[0x20];
    s32 unk20;
};
void ModelObject_GetBoxList(s32);
s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8001E770();
void func_8001E7B0(s32 arg0);
ObjectVtbl *Object_GetBaseVtbl(void);
extern void GsLinkObject4(u32 *src, void *dst, s32 id);
struct Unk_8001E770_Data {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
};
struct Unk_8001E770 {
    u8 pad_00[0x10];
    u8 unk10[8];
    s32 unk18;
    u8 pad_1C[4];
    struct Unk_8001E770_Data *unk20;
};
typedef struct Unk_8001CA94_vt {
    u8 pad_00[0x8];
    s32 (*unk8)(s32);
} Unk_8001CA94_vt;
Unk_8001CA94_vt *func_8001E57C(void);
s32 Heap_Alloc(s32);
void Heap_Free(s32);
typedef struct Unk_8001D1A4_Sub {
    s32 unk0;
    u8 pad_04[0x14];
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8 pad_24[0x24];
    s32 unk48;
} Unk_8001D1A4_Sub;
typedef struct Unk_8001D1A4_Vt {
    u8 pad_00[0x14];
    void (*unk14)(void *, void *);
} Unk_8001D1A4_Vt;
typedef struct Unk_8001D1A4_Obj {
    Unk_8001D1A4_Vt *vt;
} Unk_8001D1A4_Obj;
struct Unk_8001D1A4 {
    u8 pad_00[0xC];
    Unk_8001D1A4_Obj *unkC;
    u8 pad_10[4];
    Unk_8001D1A4_Sub *unk14;
};
typedef struct Unk_8001D6B4_Vtbl {
    u8 pad[0xA0];
    void (*unkA0)(void *, s32, s32);
} Unk_8001D6B4_Vtbl;
typedef struct Unk_8001D6B4 {
    Unk_8001D6B4_Vtbl *unk0;
    u8 pad4[0x24];
    s32 unk28;
} Unk_8001D6B4;
typedef struct Unk_8001E58C_Vt {
    u8 pad_00[0x84];
    void (*unk84)(void *, s32 *, s32);
} Unk_8001E58C_Vt;
typedef struct Unk_8001E58C_Obj {
    Unk_8001E58C_Vt *vt;
} Unk_8001E58C_Obj;
typedef struct Unk_8001E58C_Src {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Unk_8001E58C_Src;
void func_8001EE98(void *, void *, s32, s32 *);
typedef struct Unk_8001E6F8_Src {
    u8 pad_00[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
} Unk_8001E6F8_Src;
typedef struct Unk_8001E6F8_Mid {
    s32 unk0;
    u8 pad_04[0x44 - 0x04];
    Unk_8001E6F8_Src *unk44;
} Unk_8001E6F8_Mid;
struct Unk_8001E6F8 {
    u8 pad_00[0x14];
    Unk_8001E6F8_Mid *unk14;
};
typedef struct Unk_8001E6F8_Out {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Unk_8001E6F8_Out;
typedef struct Unk_8001EC84 {
    s16 unk0;
    s16 unk2;
} Unk_8001EC84;
/* Writes arg3 into the arg2-bit field at bit arg1 of *arg0, returns the old field value. */
typedef struct Unk_8001D204_Obj Unk_8001D204_Obj;
typedef struct Unk_8001D204_Vt {
    u8 pad_00[0x50];
    void (*unk50)(Unk_8001D204_Obj *);
    u8 pad_54[0x4];
    void (*unk58)(Unk_8001D204_Obj *, Unk_8001D204_Obj **, s32 *);
} Unk_8001D204_Vt;
struct Unk_8001D204_Obj {
    Unk_8001D204_Vt *vt;
};
void ApplyMatrixLV(s32 *, void *, void *);
typedef struct Unk_8001D624_Vt {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
} Unk_8001D624_Vt;
struct Unk_8001D624 {
    Unk_8001D624_Vt *unk0;
    u8 pad_04[0x10];
    s32 unk14;
    u8 pad_18[0x10];
    s32 unk28;
    s32 unk2C;
    s32 *unk30;
};
typedef struct Unk_8001EE04 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Unk_8001EE04;
void Render_TransformVectors(Unk_8001EE04 *dst, Unk_8001EE04 *src, s32 count, void *matrix);
extern s32 D_8006B684[];
extern s32 D_8006B690[];
void GsInitCoordinate2(s32 *arg0, s32 *arg1);
typedef struct Unk_8001CE30_Vt {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, s32 *);
    void (*unk48)(void *, s32, s32 *);
} Unk_8001CE30_Vt;
typedef struct Unk_8001CE30 {
    Unk_8001CE30_Vt *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    s32 *unk14;
    u8 pad_18[0xC];
    s32 unk24;
} Unk_8001CE30;
s32 ModelObject_IsReady(s32);
typedef struct Unk_8001D568_Vt {
    u8 pad_00[0x8C];
    void (*unk8C)(void *, s32 *);
    void (*unk90)(void *, s32 *, s32);
} Unk_8001D568_Vt;
typedef struct Unk_8001D568 {
    Unk_8001D568_Vt *vt;
    u8 pad_04[0x1C];
    s32 unk20;
} Unk_8001D568;
typedef struct Unk_8001CBA4_Vt {
    u8 pad_00[0x50];
    void (*unk50)(void *);
    void (*unk54)(void *);
    u8 pad_58[0x4];
    void (*unk5C)(void *, s32);
} Unk_8001CBA4_Vt;
typedef struct Unk_8001CBA4_Sub {
    u8 pad_00[0x44];
    s32 unk44;
} Unk_8001CBA4_Sub;
typedef struct Unk_8001CBA4 {
    Unk_8001CBA4_Vt *unk0;
    u8 pad_04[0x10];
    Unk_8001CBA4_Sub *unk14;
} Unk_8001CBA4;
typedef struct Unk_8001ECFC {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Unk_8001ECFC;
typedef struct Unk_8001ECFC_Pt {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Unk_8001ECFC_Pt;
typedef struct Unk_8001D0EC_Vt {
    u8 pad_00[0x10];
    void (*unk10)(void *, void *);
} Unk_8001D0EC_Vt;
typedef struct Unk_8001D0EC_Obj {
    Unk_8001D0EC_Vt *unk0;
    u8 pad_04[0x10];
    s32 unk14;
} Unk_8001D0EC_Obj;
struct Unk_8001D280 {
    u8 pad_00[0x4];
    ListNode *unk4;
};
struct Unk_8001D280_Obj {
    s32 *unk0;
    u8 pad_04[0x8];
    struct Unk_8001D280 *unkC;
};
void List_Next(s32 *value, ListNode **iter);
typedef struct Unk_8001CD60_Vt {
    u8 pad_00[0x94];
    void (*unk94)(void *, s32 **, s32);
    void (*unk98)(void *, s32 **, s32);
    void (*unk9C)(void *, s32 **, s32);
} Unk_8001CD60_Vt;
typedef struct Unk_8001CD60 {
    Unk_8001CD60_Vt *vt;
} Unk_8001CD60;
typedef struct Unk_8001D950 {
    Unk_8001E58C_Vt *vt;
    u8 pad_04[0x8];
    struct Unk_8001D950 *unkC;
} Unk_8001D950;
void MulMatrix2(s32 *arg0, s32 *arg1);
s32 func_8001EC84(Unk_8001EC84 *arg0);
typedef struct Unk_8001D008_Mid {
    s32 unk0;
    u8 pad_04[0x40];
    s32 *unk44;
} Unk_8001D008_Mid;
typedef struct Unk_8001D008 {
    u8 pad_00[0x14];
    Unk_8001D008_Mid *unk14;
} Unk_8001D008;
struct Unk_8001E600 {
    Unk_8001E58C_Vt *vt;
    u8 pad_04[0x8];
    void *unkC;
    u8 pad_10[0x4];
    u8 *unk14;
};
typedef struct Unk_8001CAF4_Vt {
    u8 pad_00[0x40];
    void (*unk40)(void *);
} Unk_8001CAF4_Vt;
typedef struct Unk_8001CAF4_Obj {
    u8 pad_00[0x44];
    void *unk44;
    s32 unk48;
} Unk_8001CAF4_Obj;
typedef struct Unk_8001CAF4 {
    Unk_8001CAF4_Vt *unk0;
    u8 pad_04[0x8];
    s32 unkC;
    u8 pad_10[4];
    Unk_8001CAF4_Obj *unk14;
    s32 unk18;
    u8 pad_1C[4];
    s32 unk20;
} Unk_8001CAF4;
extern s32 D_8006B5CC[];
s32 D_8008A838;
typedef struct Unk_8001EACC_Arg {
    u8 pad_00[0xC];
    s32 unkC;
    u8 pad_10[4];
    EntityPos *unk14;
} Unk_8001EACC_Arg;
s32 ratan2(s32, s32);
typedef struct Unk_8001D4DC {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} Unk_8001D4DC;
void RotMatrix(Unk_8001D4DC *r, void *m);
typedef struct Unk_8001E2E8 {
    s16 v[3];
} Unk_8001E2E8;
void ApplyMatrixSV(void *, Unk_8001EE04 *, Unk_8001EE04 *);
s32 func_8001ECFC(Unk_8001ECFC *arg0, Unk_8001ECFC_Pt *arg1);
typedef struct Unk_8001D714_Vt {
    u8 pad_00[0xA4];
    s32 (*unkA4)(void *, void *, void *, void *, s32);
    s32 (*unkA8)(void *, void *, void *);
    s32 (*unkAC)(void *, void *, void *, void *);
} Unk_8001D714_Vt;
typedef struct Unk_8001D714_Obj {
    Unk_8001D714_Vt *unk0;
    u8 pad_04[0x8];
    s32 unkC;
    u8 pad_10[0x4];
    u8 *unk14;
    u8 pad_18[0x8];
    s32 unk20;
    u8 pad_24[0x4];
    void *unk28;
} Unk_8001D714_Obj;
typedef struct Unk_8001D714_Arg_Vt {
    u8 pad_00[0x38];
    void (*unk38)(void *, void *, s32);
} Unk_8001D714_Arg_Vt;
typedef struct Unk_8001D714_Arg {
    Unk_8001D714_Arg_Vt *unk0;
    u8 pad_04[0x8];
    s32 unkC;
    u8 pad_10[0x4];
    u8 *unk14;
    u8 pad_18[0x14];
    s32 unk2C;
    s32 *unk30;
} Unk_8001D714_Arg;
typedef struct Unk_8001D714_Loc {
    s32 unk0;
    s32 unk4;
    u8 pad_08[0x30];
} Unk_8001D714_Loc;
void Object_NextWatcher(Object *self, s32 *value, s32 *more);
typedef struct Unk_8001E4A4 {
    u8 unk0;
    u8 pad_01[0xF];
    void (*unk10)(s32 **, s32);
} Unk_8001E4A4;
typedef struct Unk_8001DA28_Pt {
    s16 x;
    s16 y;
    s16 z;
} Unk_8001DA28_Pt;
typedef struct Unk_8001DA28_Box {
    Unk_8001DA28_Pt min;
    Unk_8001DA28_Pt max;
} Unk_8001DA28_Box;
typedef struct Unk_8001DA28_Arg1 {
    s32 count;
    Unk_8001DA28_Pt bbox;
    Unk_8001DA28_Pt verts;
} Unk_8001DA28_Arg1;
typedef struct Unk_8001DA28 {
    u8 pad_00[0x20];
    s32 unk20;
} Unk_8001DA28;
void ModelObject_UpdateBox(s32);
Unk_8001DA28_Box *ModelObject_GetBox(s32, s32);
typedef struct Unk_8001DDF4 {
    u8 pad_00[0x20];
    s32 unk20;
    u8 pad_24[0x8];
    s32 unk2C;
} Unk_8001DDF4;
s32 func_8001E110(Unk_8001ECFC_Pt *out, Unk_8001ECFC *bounds, Unk_8001ECFC_Pt *start, Unk_8001ECFC_Pt *end);
s32 ModelObject_RayTest(s32, s32 *, void *, s32 *, Unk_8001ECFC_Pt *, Unk_8001ECFC_Pt *);
typedef struct Unk_8001E7BC_Vt {
    u8 pad_00[0xA4];
    void (*unkA4)(void *, s32, Unk_8001ECFC_Pt *, Unk_8001ECFC_Pt *, s32);
} Unk_8001E7BC_Vt;
typedef struct Unk_8001E7BC {
    Unk_8001E7BC_Vt *unk0;
    u8 pad_04[0x8];
    struct Unk_8001E7BC *unkC;
    s32 unk10;
    EntityPos *unk14;
    u8 pad_18[0x8];
    s32 unk20;
} Unk_8001E7BC;
void func_8001EA8C(s32 *arg0, s16 *arg1, s16 *arg2);

s32 func_8001CA94(void) {
    s32 block;

    block = Heap_Alloc(0x44);
    if (block == 0) {
        return 0;
    }
    if (func_8001E57C()->unk8(block) != 0) {
        return block;
    }
    Heap_Free(block);
    return 0;
}

Unk_8001CAF4 *func_8001CAF4(Unk_8001CAF4 *arg0) {
    Unk_8001CAF4_Obj *obj;
    void *buf;

    obj = ((void *)Heap_Alloc(0x50));
    arg0->unk14 = obj;
    if (obj != NULL) {
        buf = ((void *)Heap_Alloc(0x28));
        arg0->unk14->unk44 = buf;
        if (buf != NULL) {
            Object_GetBaseVtbl()->init(arg0);
            arg0->unk0 = ((Unk_8001CAF4_Vt *)func_8001E57C());
            arg0->unk20 = 0;
            arg0->unk18 = 0;
            arg0->unkC = 0;
            arg0->unk14->unk48 = 0;
            arg0->unk0->unk40(arg0);
            return arg0;
        }
        Heap_Free((s32)arg0->unk14);
    }
    return NULL;
}

void func_8001CBA4(Unk_8001CBA4 *arg0) {
    arg0->unk0->unk50(arg0);
    arg0->unk0->unk54(arg0);
    arg0->unk0->unk5C(arg0, 0);
    Heap_Free(arg0->unk14->unk44);
    Heap_Free((s32)arg0->unk14);
    Object_GetBaseVtbl()->destroy(arg0);
}

void func_8001CC48(s32 object, s32 **other) {
    Object_GetBaseVtbl()->watch(object, other);
    if ((**other & 0xF) == 9) {
        func_8001E770(object, other);
    }
}

void func_8001CCB4(s32 object, s32 **other) {
    if ((**other & 0xF) == 9) {
        func_8001E7B0(object);
    }
    Object_GetBaseVtbl()->unwatch(object, other);
}

void func_8001CD20(s32 object) {
    func_8001E7B0(object);
    Object_GetBaseVtbl()->unwatchAll(object);
}

void func_8001CD60(Unk_8001CD60 *object, s32 **sender, s32 message) {
    s32 v;

    Object_GetBaseVtbl()->onNotify(object, sender, message);
    v = **sender & 0xF;
    if (v == 2) {
        object->vt->unk94(object, sender, message);
    } else if (v == 5) {
        object->vt->unk98(object, sender, message);
    } else if (v == 4) {
        object->vt->unk9C(object, sender, message);
    }
}

void func_8001CE30(Unk_8001CE30 *arg0) {
    arg0->unk24 = 0;
    arg0->unk10 = 0;
    GsInitCoordinate2(0, arg0->unk14);
    arg0->unk0->unk44(arg0, 1, D_8006B684);
    arg0->unk0->unk48(arg0, 1, D_8006B690);
    *arg0->unk14 = 1;
}

void func_8001CEB4(struct Unk_8001E6F8 *arg0, s32 assign, Unk_8001EC84 *fractions) {
    s32 angles[3];
    s32 i;
    Unk_8001E6F8_Src *src;
    s16 *p;
    s16 *cur;

    angles[0] = func_8001EC84(fractions);
    angles[1] = func_8001EC84(fractions + 1);
    angles[2] = func_8001EC84(fractions + 2);
    angles[0] /= 0x168;
    angles[1] /= 0x168;
    angles[2] /= 0x168;
    src = arg0->unk14->unk44;
    p = &src->unk10;
    if (assign != 0) {
        src->unk10 = angles[0];
        src->unk12 = angles[1];
        src->unk14 = angles[2];
    } else {
        for (i = 0; i < 3; i++) {
            cur = p;
            p = cur + 1;
            *cur = (*cur + angles[i]) % 0x1000;
        }
    }
    arg0->unk14->unk0 = 0;
}

void func_8001D008(Unk_8001D008 *arg0, s32 assign, Unk_8001EC84 *fractions) {
    s32 x;
    s32 y;
    s32 z;
    s32 *dst;

    x = func_8001EC84(fractions);
    y = func_8001EC84(fractions + 1);
    z = func_8001EC84(fractions + 2);
    dst = arg0->unk14->unk44;
    if (assign != 0) {
        dst[0] = (s16)x;
        dst[1] = (s16)y;
        dst[2] = (s16)z;
    } else {
        dst[0] = (s16)x + dst[0];
        dst[1] = (s16)y + dst[1];
        dst[2] = (s16)z + dst[2];
    }
    arg0->unk14->unk0 = 0;
}

void *func_8001D0EC(struct Unk_8001D1A4 *arg0, Unk_8001D0EC_Obj *obj, Vec3 *pos) {
    Unk_8001D1A4_Sub *sub;

    if (arg0->unkC == NULL) {
        arg0->unkC = (Unk_8001D1A4_Obj *) obj;
        arg0->unk14->unk48 = obj->unk14;
        obj->unk0->unk10(obj, arg0);
        sub = arg0->unk14;
        if (pos != NULL) {
            sub->unk18 = pos->x;
            sub->unk1C = pos->y;
            sub->unk20 = pos->z;
        } else {
            sub->unk18 = 0;
            sub->unk1C = 0;
            sub->unk20 = 0;
        }
        arg0->unk14->unk0 = 0;
    }
    return arg0;
}

void *func_8001D1A4(struct Unk_8001D1A4 *arg0) {
    Unk_8001D1A4_Obj *attached;

    attached = arg0->unkC;
    if (attached != NULL) {
        attached->vt->unk14(attached, arg0);
        arg0->unk14->unk48 = 0;
        arg0->unkC = NULL;
    }
    return arg0;
}

void func_8001D204(Unk_8001D204_Obj *arg0) {
    Unk_8001D204_Obj *value;
    s32 more;

    value = NULL;
    do {
        arg0->vt->unk58(arg0, &value, &more);
        if (value != NULL) {
            value->vt->unk50(value);
        }
    } while (more != 0);
}

void func_8001D280(struct Unk_8001D280 *arg0, struct Unk_8001D280_Obj **value, ListNode **iter) {
    struct Unk_8001D280_Obj *obj;

    do {
        if (*value == NULL) {
            *iter = arg0->unk4;
        }
        List_Next((s32 *)value, iter);
        obj = *value;
        if (obj != NULL && (*obj->unk0 & 0xF) == 4 && obj->unkC == arg0) {
            return;
        }
    } while (*iter != NULL);
    *value = NULL;
}

void func_8001D33C(void) {
}

s32 func_8001D344(u8 *arg0, s32 value) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 0x1F, 1, value == 0) == 0;
}

void func_8001D374(u8 *arg0, s32 value) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0x1E, 1, value != 0);
}

void func_8001D3A0(u8 *arg0, s32 value) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0x1C, 2, value);
}

void func_8001D3CC(u8 *arg0, s32 value) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 6, 1, value == 0);
}

void func_8001D3F8(u8 *arg0, s32 value) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 3, 3, value);
}

void func_8001D424(u8 *arg0, s32 value) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0, 3, value);
}

s32 func_8001D450(u8 *arg0, s32 value) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 7, 1, value == 0) == 0;
}

void func_8001D480(u8 *arg0, s32 value) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 9, 3, value);
}

s32 func_8001D4AC(u8 *arg0, s32 value) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 8, 1, value == 0) == 0;
}

void func_8001D4DC(struct Unk_8001E6F8 *arg0, void *matrix, s32 invert) {
    Unk_8001D4DC rot;
    Unk_8001E6F8_Src *src;

    src = arg0->unk14->unk44;
    if (invert != 0) {
        rot.vx = -src->unk10;
        rot.vy = -src->unk12;
        rot.vz = -src->unk14;
    } else {
        rot = *(Unk_8001D4DC *)&src->unk10;
    }
    RotMatrix(&rot, matrix);
}

void func_8001D568(Unk_8001D568 *arg0, s32 mode) {
    s32 sp10[14];
    s32 temp_a0;

    if (mode < 4) {
        if (mode >= 2) {
            temp_a0 = arg0->unk20;
            if ((temp_a0 != 0) && (ModelObject_IsReady(temp_a0) != 0)) {
                arg0->vt->unk8C(arg0, sp10);
                arg0->vt->unk90(arg0, sp10, mode);
            }
        }
    }
}

void func_8001D600(struct Unk_8001D600 *arg0) {
    ModelObject_GetBoxList(arg0->unk20);
}

void func_8001D624(struct Unk_8001D624 *arg0, s32 *arg1, s32 arg2) {
    Render_TransformVectors(arg1 + 1, arg1 + 1, arg1[0] * 8, arg0->unk14 + 0x24);
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk30 = arg1;
    arg0->unk0->unk30(arg0, arg2);
    arg0->unk30 = NULL;
}

void func_8001D6A4(void) {
}

void func_8001D6AC(void) {
}

void func_8001D6B4(Unk_8001D6B4 *arg0, s32 value, s32 kind) {
    switch (kind) {
        case 2:
        case 3:
            arg0->unk0->unkA0(arg0, value, kind);
            break;
        case 4:
            arg0->unk28 = value;
            break;
    }
}

void func_8001D714(Unk_8001D714_Obj *arg0, Unk_8001D714_Arg *arg1) {
    Vec3 sp18;
    u16 sp28[3];
    u8 sp30[0x20];
    Unk_8001D714_Loc loc;
    Vec3 *src;
    Vec3 *dst;
    s32 *p;

    if (arg0->unk20 != 0 && ModelObject_IsReady(arg0->unk20) != 0) {
        src = NULL;
        if (arg1->unkC != 0) {
            src = (Vec3 *)(arg1->unk14 + 0x38);
        }
        sp18 = *src;
        dst = NULL;
        if (arg0->unkC != 0) {
            dst = (Vec3 *)(arg0->unk14 + 0x38);
        }
        sp18.x -= dst->x;
        sp18.y -= dst->y;
        sp18.z -= dst->z;
        if ((sp18.x >= 0 ? sp18.x < 0x4001 : ~sp18.x + 1 < 0x4001)
         && (sp18.y >= 0 ? sp18.y < 0x4001 : ~sp18.y + 1 < 0x4001)
         && (sp18.z >= 0 ? sp18.z < 0x4001 : ~sp18.z + 1 < 0x4001)) {
            sp28[0] = sp18.x;
            sp28[1] = sp18.y;
            sp28[2] = sp18.z;
            loc.unk0 = *arg1->unk30;
            p = arg1->unk30 + 1;
            arg0->unk0->unkA4(arg0, sp28, &loc.unk4, p, loc.unk0 * 8);
            if (arg0->unk0->unkA8(arg0, &loc.unk0, sp28) != 0
             && arg0->unk0->unkAC(arg0, &arg1->unk2C, sp28, &loc.unk0) != 0) {
                arg0->unk28 = arg1;
                arg1->unk0->unk38(arg1, arg0, 4);
            }
        }
    }
}

void func_8001D950(Unk_8001D950 *arg0, s32 *arg1, s32 *dst, s32 *src, s32 count) {
    s32 nodeMtx[8];
    s32 worldMtx[8];
    Unk_8001D950 *node;

    arg0->vt->unk84(arg0, worldMtx, 1);
    for (node = arg0->unkC; node != NULL; node = node->unkC) {
        node->vt->unk84(node, nodeMtx, 1);
        MulMatrix2(nodeMtx, worldMtx);
    }
    Render_TransformVectors(dst, src, count, (s32)worldMtx);
    if (arg1 != NULL) {
        Render_TransformVectors(arg1, arg1, 1, (s32)worldMtx);
    }
}

s32 func_8001DA28(Unk_8001DA28 *arg0, Unk_8001DA28_Arg1 *arg1, Unk_8001DA28_Pt *offset) {
    Unk_8001DA28_Box own;
    Unk_8001DA28_Box other;
    u8 *end;
    Unk_8001DA28_Pt *p;
    Unk_8001DA28_Box *box;
    Unk_8001DA28_Box *b;
    Unk_8001DA28_Box *bend;
    s32 n;

    p = &arg1->bbox;
    end = (u8 *)p + arg1->count * 0x30;
    arg1->bbox.x += offset->x;
    arg1->bbox.y += offset->y;
    arg1->bbox.z += offset->z;
    own.min = arg1->bbox;
    own.max = arg1->bbox;
    box = &own;
    for (p = &arg1->verts; (u8 *)p < end; p++) {
        p->x += offset->x;
        p->y += offset->y;
        p->z += offset->z;
        box->min.x = (box->min.x < p->x) ? box->min.x : p->x;
        box->min.y = (box->min.y < p->y) ? box->min.y : p->y;
        box->min.z = (box->min.z < p->z) ? box->min.z : p->z;
        box->max.x = (box->max.x > p->x) ? box->max.x : p->x;
        box->max.y = (box->max.y > p->y) ? box->max.y : p->y;
        box->max.z = (box->max.z > p->z) ? box->max.z : p->z;
    }

    ModelObject_UpdateBox(arg0->unk20);
    b = ModelObject_GetBox(arg0->unk20, 0);
    n = ModelObject_IsReady(arg0->unk20);
    other = *b;
    bend = b + n;
    for (b++; b < bend; b++) {
        other.min.x = (other.min.x < b->min.x) ? other.min.x : b->min.x;
        other.min.y = (other.min.y < b->min.y) ? other.min.y : b->min.y;
        other.min.z = (other.min.z < b->min.z) ? other.min.z : b->min.z;
        other.max.x = (other.max.x > b->max.x) ? other.max.x : b->max.x;
        other.max.y = (other.max.y > b->max.y) ? other.max.y : b->max.y;
        other.max.z = (other.max.z > b->max.z) ? other.max.z : b->max.z;
    }

    return (own.min.z <= other.max.z) && (own.max.z >= other.min.z) &&
           (own.min.x <= other.max.x) && (own.max.x >= other.min.x) &&
           (own.min.y <= other.max.y) && (own.max.y >= other.min.y);
}

s32 func_8001DDF4(Unk_8001DDF4 *arg0, s32 *arg1, void *arg2, s32 *arg3) {
    Unk_8001ECFC_Pt sp18[2];
    Unk_8001ECFC sp28[2];
    s32 sp40;
    s32 sp44;
    Unk_8001ECFC_Pt *p;
    Unk_8001ECFC_Pt *q;
    Unk_8001ECFC_Pt *dst;
    s32 count;
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    Unk_8001DA28_Box *box;

    sp40 = 0x7FFFFFFF;
    p = (Unk_8001ECFC_Pt *) (arg3 + 1);
    q = (Unk_8001ECFC_Pt *) (arg3 + 4);
    for (dst = sp18; dst < sp18 + 2; dst++) {
        dst->unk0 = (p->unk0 + q->unk0) >> 1;
        dst->unk2 = (p->unk2 + q->unk2) >> 1;
        dst->unk4 = (p->unk4 + q->unk4) >> 1;
        p += 4;
        q += 4;
    }

    arg0->unk2C = 0;
    count = ModelObject_IsReady(arg0->unk20);
    ret = 0;
    for (i = 0; i < count; i++) {
        box = ModelObject_GetBox(arg0->unk20, i);
        if (func_8001E110(0, (Unk_8001ECFC *) box, sp18, sp18 + 1) != 0 &&
            ModelObject_RayTest(arg0->unk20, &sp40, arg2, &sp44, sp18, sp18 + 1) != 0) {
            if (D_8008A838 == 0) {
                arg0->unk2C |= 1 << i;
            } else if (sp44 >= 0x201) {
                arg0->unk2C |= 1 << i;
            }
        }
    }

    if (arg0->unk2C != 0) {
        *arg1 = 1;
        if (ret != 0) {
            return 2;
        }
        return 1;
    }

    *arg1 = 0;
    n = *arg3;
    for (i = 0; i < count; i++) {
        k = 0;
        box = ModelObject_GetBox(arg0->unk20, i);
        p = (Unk_8001ECFC_Pt *) (arg3 + 1);
        for (; k < n; k++) {
            for (j = 0; j < 4; j++) {
                if (j > 0 && j < 3) {
                    if (func_8001E110(0, (Unk_8001ECFC *) box, p, p + 4) != 0 &&
                        ModelObject_RayTest(arg0->unk20, &sp40, arg2, &sp44, p, p + 4) != 0 &&
                        sp44 >= 0x201) {
                        arg0->unk2C |= 1 << i;
                        *arg1 |= 1 << k;
                    }
                }
                p++;
            }
            p += 4;
        }
    }
    return *arg1 != 0;
}

s32 func_8001E110(Unk_8001ECFC_Pt *out, Unk_8001ECFC *bounds, Unk_8001ECFC_Pt *start, Unk_8001ECFC_Pt *end) {
    Unk_8001ECFC_Pt mid;
    u8 startCode;
    u8 endCode;
    s32 result;

    startCode = func_8001ECFC(bounds, start);
    endCode = func_8001ECFC(bounds, end);
    if (!startCode) {
        if (!endCode) {
            return 1;
        }
    } else if (!endCode) {
        if (out != 0) {
            func_8001E2E8(out, bounds, end, start);
        }
        return 3;
    }
    if (!startCode) {
        if (out != 0) {
            func_8001E2E8(out, bounds, start, end);
        }
        return 2;
    }
    if (startCode & endCode) {
        return 0;
    }
    mid.unk0 = (start->unk0 + end->unk0) >> 1;
    mid.unk2 = (start->unk2 + end->unk2) >> 1;
    mid.unk4 = (start->unk4 + end->unk4) >> 1;
    if (start->unk0 == mid.unk0 && start->unk2 == mid.unk2 && start->unk4 == mid.unk4) {
        return 0;
    }
    if (end->unk0 == mid.unk0 && end->unk2 == mid.unk2 && end->unk4 == mid.unk4) {
        return 0;
    }
    if ((result = func_8001E110(out, bounds, start, &mid)) != 0
     || (result = func_8001E110(out, bounds, &mid, end)) != 0) {
        return result;
    }
    return 0;
}

void func_8001E2E8(s16 *out, s16 *bounds, s16 *a, s16 *b)
{
    s16 tmp[2][4];
    u8 bits;
    s16 *t;

    for (;;) {
        out[0] = (a[0] + b[0]) >> 1;
        out[1] = (a[1] + b[1]) >> 1;
        out[2] = (a[2] + b[2]) >> 1;
        if ((out[0] == a[0] && out[1] == a[1] && out[2] == a[2]) ||
            (out[0] == b[0] && out[1] == b[1] && out[2] == b[2])) {
            return;
        }
        bits = 0;
        if (bounds[3] < out[0]) {
            bits = 8;
        } else if (out[0] < bounds[0]) {
            bits = 4;
        }
        if (bounds[4] < out[1]) {
            bits |= 2;
        } else if (out[1] < bounds[1]) {
            bits |= 1;
        }
        if (bounds[5] < out[2]) {
            bits |= 0x20;
        } else if (out[2] < bounds[2]) {
            bits |= 0x10;
        }
        if (bits != 0) {
            t = tmp[1];
            b = t;
        } else {
            t = tmp[0];
            a = t;
        }
        *(Unk_8001E2E8 *)t = *(Unk_8001E2E8 *)out;
    }
}

void func_8001E49C(void) {
}

void func_8001E4A4(s32 arg0, Object *object) {
    Unk_8001E4A4 *obj;
    s32 **p;
    s32 more;

    p = NULL;
    do {
        for (;;) {
            Object_NextWatcher(object, (s32 *)&p, &more);
            if (p != NULL && (**p & 0xF) == 4) {
                break;
            }
            if (more == 0) {
                p = NULL;
                break;
            }
        }
        if (p != NULL) {
            obj = (Unk_8001E4A4 *)*p;
            if (obj->unk0 == 0x34) {
                obj->unk10(p, arg0);
            }
        }
    } while (more != 0);
}

Unk_8001CA94_vt *func_8001E57C(void) {
    return (Unk_8001CA94_vt *)D_8006B5CC;
}

void func_8001E58C(Unk_8001E58C_Obj *arg0, Vec3 *dst, Unk_8001E58C_Src *src) {
    s32 sp10[8];

    arg0->vt->unk84(arg0, sp10, 0);
    dst->x = src->unk0;
    dst->y = src->unk2;
    dst->z = src->unk4;
    func_8001EE98(dst, dst, 1, sp10);
}

void func_8001E600(struct Unk_8001E600 *dreamSys, Vec3 *dst, Unk_8001E58C_Src *src) {
    s32 sp10[8];
    s32 *var_v1;

    dreamSys->vt->unk84(dreamSys, sp10, 0);
    func_8001EE98(dst, src, 1, sp10);
    var_v1 = NULL;
    if (dreamSys->unkC != NULL) {
        var_v1 = (s32 *)(dreamSys->unk14 + 0x38);
    }
    dst->x += *var_v1;
    var_v1 = NULL;
    if (dreamSys->unkC != NULL) {
        var_v1 = (s32 *)(dreamSys->unk14 + 0x38);
    }
    dst->y += var_v1[1];
    var_v1 = NULL;
    if (dreamSys->unkC != NULL) {
        var_v1 = (s32 *)(dreamSys->unk14 + 0x38);
    }
    dst->z += var_v1[2];
}

void func_8001E6F8(struct Unk_8001E6F8 *arg0, Unk_8001E6F8_Out *arg1) {
    Unk_8001E6F8_Src *src;

    src = arg0->unk14->unk44;
    arg1->unk0 = (src->unk10 * 45) >> 9;
    arg1->unk2 = 1;
    arg1->unk4 = (src->unk12 * 45) >> 9;
    arg1->unk6 = 1;
    arg1->unk8 = (src->unk14 * 45) >> 9;
    arg1->unkA = 1;
}

void func_8001E770(struct Unk_8001E770 *arg0, struct Unk_8001E770_Data *arg1) {
    arg0->unk20 = arg1;
    arg0->unk18 = arg1->unk10;
    GsLinkObject4((u32 *)(arg0->unk20->unkC + 0xC), &arg0->unk10, 0);
}

void func_8001E7B0(s32 arg0) {
    *(s32 *)(arg0 + 0x18) = 0;
    *(s32 *)(arg0 + 0x20) = 0;
}

s32 func_8001E7BC(Unk_8001E7BC *arg0, s32 *arg1, Vec3 *arg2) {
    Unk_8001ECFC_Pt from;
    Unk_8001ECFC_Pt to;
    Unk_8001ECFC_Pt hit;
    s32 dist;
    Vec3 *base;
    Unk_8001E7BC *n;

    if (arg0->unk20 == 0) {
        return 0;
    }
    if (arg0->unk10 < 0 && arg0->unkC != NULL) {
        if (&arg0->unk14->posCopy != NULL) {
            arg0->unk14->posCopy = arg0->unk14->pos;
            for (n = arg0->unkC; n != NULL; n = n->unkC) {
                (arg0->unkC != NULL ? &arg0->unk14->posCopy : NULL)->x =
                    (arg0->unkC != NULL ? &arg0->unk14->posCopy : NULL)->x + n->unk14->pos.x;
                (arg0->unkC != NULL ? &arg0->unk14->posCopy : NULL)->y =
                    (arg0->unkC != NULL ? &arg0->unk14->posCopy : NULL)->y + n->unk14->pos.y;
                (arg0->unkC != NULL ? &arg0->unk14->posCopy : NULL)->z =
                    (arg0->unkC != NULL ? &arg0->unk14->posCopy : NULL)->z + n->unk14->pos.z;
            }
        }
    }
    base = arg0->unkC != NULL ? &arg0->unk14->posCopy : NULL;
    to.unk0 = arg2->x - base->x;
    to.unk2 = arg2->y - base->y;
    to.unk4 = arg2->z - base->z;
    arg0->unk0->unkA4(arg0, 0, &from, &to, 1);
    to.unk0 = from.unk0;
    to.unk2 = from.unk2 - 0x400;
    to.unk4 = from.unk4;
    if (ModelObject_RayTest(arg0->unk20, &dist, &hit, NULL, &from, &to) != 0) {
        func_8001EA8C(arg1, &from.unk0, &hit.unk0);
        return 1;
    }
    to.unk2 = from.unk2 + 0x400;
    if (ModelObject_RayTest(arg0->unk20, &dist, &hit, NULL, &from, &to) == 0) {
        return 0;
    }
    func_8001EA8C(arg1, &from.unk0, &hit.unk0);
    return 1;
}

void func_8001EA8C(s32 *arg0, s16 *arg1, s16 *arg2) {
    arg0[0] = arg2[0] - arg1[0];
    arg0[1] = arg2[1] - arg1[1];
    arg0[2] = arg2[2] - arg1[2];
}

void Entity_FaceDreamer(Entity *arg0, Unk_8001EACC_Arg *arg1, s32 arg2, s32 arg3, s32 *arg4) {
    s16 buf[6];
    Vec3 *s0;
    Vec3 *s1;
    s32 v1;

    s1 = &arg0->pos.block->pos;
    if (arg1->unkC != 0) {
        s0 = &arg1->unk14->posCopy;
    } else {
        s0 = NULL;
    }
    if (s0->x != s1->x) {
        buf[2] = ratan2(s0->x - s1->x, s0->z - s1->z);
    } else {
        buf[2] = ratan2(1, s0->z - s1->z);
    }
    if (s0->z != s1->z) {
        buf[0] = ratan2(s0->z - s1->z, s0->y - s1->y);
    } else {
        buf[0] = ratan2(1, s0->y - s1->y);
    }
    buf[0] = ((buf[0] + 0x400) * 0x168) / 0x1000;
    v1 = (buf[2] * 0x168) / 0x1000;
    buf[2] = v1;
    buf[4] = 0;
    buf[5] = 1;
    buf[3] = 1;
    buf[1] = 1;
    if (arg2 != 0) {
        buf[0] = 0;
    }
    if (arg3 == 0) {
        buf[2] = v1 + 0xB4;
    }
    arg0->vt->unk44(arg0, 1, buf);
    if (arg4 != 0) {
        arg0->vt->unk44(arg0, 0, arg4);
    }
}

s32 func_8001EC84(Unk_8001EC84 *arg0) {
    s32 a;
    s32 b;

    a = arg0->unk0;
    b = arg0->unk2;
    return ((a / b) << 12) + (((a % b) << 12) / b);
}

s32 func_8001ECFC(Unk_8001ECFC *arg0, Unk_8001ECFC_Pt *arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg0->unk6 < arg1->unk0) {
        var_v1 = 8;
    } else if (arg1->unk0 < arg0->unk0) {
        var_v1 = 4;
    }
    if (arg0->unk8 < arg1->unk2) {
        var_v1 |= 2;
    } else if (arg1->unk2 < arg0->unk2) {
        var_v1 |= 1;
    }
    if (arg0->unkA < arg1->unk4) {
        var_v1 |= 0x20;
    } else if (arg1->unk4 < arg0->unk4) {
        var_v1 |= 0x10;
    }
    return var_v1;
}

s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 mask;
    s32 old;

    mask = 1;
    for (i = 0; i < arg2; i++) {
        mask <<= 1;
    }
    mask = mask - 1;
    mask = mask << arg1;
    old = *arg0;
    *arg0 &= ~mask;
    *arg0 |= arg3 << arg1;
    return (u32)(mask & old) >> arg1;
}

void Render_TransformVectors(Unk_8001EE04 *dst, Unk_8001EE04 *src, s32 count, void *matrix) {
    Unk_8001EE04 tmp;
    Unk_8001EE04 *end;

    end = dst + count;
    while (dst < end) {
        tmp = *src;
        ApplyMatrixSV(matrix, &tmp, dst);
        dst++;
        src++;
    }
}

void func_8001EE98(void *arg0, void *arg1, s32 arg2, s32 *arg3) {
    u8 *dst;
    u8 *src;
    u8 *end;
    s32 *mtx;
    s32 pad[2];

    dst = arg0;
    src = arg1;
    mtx = arg3;
    end = (u8 *)arg0 + arg2 * 12;
    while (dst < end) {
        ApplyMatrixLV(mtx, src, dst);
        dst += 12;
        src += 12;
    }
}

s32 Entity_IsWithinBox(s32 *arg0, s32 arg1, s32 *arg2) {
    s32 i;

    for (i = 0; i < 3; i++, arg0++, arg2++) {
        if (*arg2 < *arg0 - arg1) {
            return 0;
        }
        if (*arg0 + arg1 < *arg2) {
            return 0;
        }
    }
    return 1;
}

s32 func_8001EF60(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_8008A838;
    D_8008A838 = arg0;
    return temp_v0;
}

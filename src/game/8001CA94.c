#include "common.h"

struct Unk_8001D600 {
    u8 pad_00[0x20];
    s32 unk20;
};
void func_8001F51C(s32);
s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct Unk_8001CD20 {
    u8 pad_00[0x10];
    void (*unk10)(s32, s32 **);
    void (*unk14)(s32, s32 **);
    void (*unk18)(s32);
    u8 pad_1C[0x1C];
    void (*unk38)(void *, s32 **, s32);
} Unk_8001CD20;
void func_8001E770();
void func_8001E7B0(s32 arg0);
Unk_8001CD20 *func_80018390(void);
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
s32 func_80017B34(s32);
void func_80017CFC(s32);
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
typedef struct Unk_8001E58C_Dst {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8001E58C_Dst;
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
void func_8001EE04(Unk_8001EE04 *arg0, Unk_8001EE04 *arg1, s32 arg2, void *arg3);
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
s32 func_8001F3A4(s32);
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
typedef struct Unk_8001CBA4_Ret {
    u8 pad_00[0xC];
    void (*unkC)(void *);
} Unk_8001CBA4_Ret;
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
typedef struct Unk_8001D0EC_Vec {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8001D0EC_Vec;
struct Unk_800183A0;
struct Unk_8001D280 {
    u8 pad_00[0x4];
    struct Unk_800183A0 *unk4;
};
struct Unk_8001D280_Obj {
    s32 *unk0;
    u8 pad_04[0x8];
    struct Unk_8001D280 *unkC;
};
void func_800183A0(s32 *arg0, struct Unk_800183A0 **arg1);
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
typedef struct Unk_8001CA94_vt_8001CAF4 {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8001CA94_vt_8001CAF4;
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
typedef struct Unk_8001EACC_Vec {
    s32 x;
    s32 y;
    s32 z;
} Unk_8001EACC_Vec;
typedef struct Unk_8001EACC_Vt {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, void *);
} Unk_8001EACC_Vt;
typedef struct Unk_8001EACC_Sub {
    u8 pad_00[0x18];
    Unk_8001EACC_Vec vec18;
} Unk_8001EACC_Sub;
typedef struct Unk_8001EACC_Src {
    u8 pad_00[0x38];
    Unk_8001EACC_Vec vec38;
} Unk_8001EACC_Src;
typedef struct Unk_8001EACC_Obj {
    Unk_8001EACC_Vt *unk0;
    u8 pad_04[0x10];
    Unk_8001EACC_Sub *unk14;
} Unk_8001EACC_Obj;
typedef struct Unk_8001EACC_Arg {
    u8 pad_00[0xC];
    s32 unkC;
    u8 pad_10[4];
    Unk_8001EACC_Src *unk14;
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
typedef struct Unk_8001816C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8001816C;
void func_8001816C(Unk_8001816C *arg1, s32 *arg2, s32 *arg3);
typedef struct Unk_8001E4A4 {
    u8 unk0;
    u8 pad_01[0xF];
    void (*unk10)(s32 **, s32);
} Unk_8001E4A4;

s32 func_8001CA94(void) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x44);
    if (temp_s0 == 0) {
        return 0;
    }
    if (func_8001E57C()->unk8(temp_s0) != 0) {
        return temp_s0;
    }
    func_80017CFC(temp_s0);
    return 0;
}

Unk_8001CAF4 *func_8001CAF4(Unk_8001CAF4 *arg0) {
    Unk_8001CAF4_Obj *obj;
    void *buf;

    obj = ((void *)func_80017B34(0x50));
    arg0->unk14 = obj;
    if (obj != NULL) {
        buf = ((void *)func_80017B34(0x28));
        arg0->unk14->unk44 = buf;
        if (buf != NULL) {
            ((Unk_8001CA94_vt_8001CAF4 *)func_80018390())->unk8(arg0);
            arg0->unk0 = ((Unk_8001CAF4_Vt *)func_8001E57C());
            arg0->unk20 = 0;
            arg0->unk18 = 0;
            arg0->unkC = 0;
            arg0->unk14->unk48 = 0;
            arg0->unk0->unk40(arg0);
            return arg0;
        }
        func_80017CFC((s32)arg0->unk14);
    }
    return NULL;
}

void func_8001CBA4(Unk_8001CBA4 *arg0) {
    arg0->unk0->unk50(arg0);
    arg0->unk0->unk54(arg0);
    arg0->unk0->unk5C(arg0, 0);
    func_80017CFC(arg0->unk14->unk44);
    func_80017CFC((s32)arg0->unk14);
    ((Unk_8001CBA4_Ret *)func_80018390())->unkC(arg0);
}

void func_8001CC48(s32 arg0, s32 **arg1) {
    func_80018390()->unk10(arg0, arg1);
    if ((**arg1 & 0xF) == 9) {
        func_8001E770(arg0, arg1);
    }
}

void func_8001CCB4(s32 arg0, s32 **arg1) {
    if ((**arg1 & 0xF) == 9) {
        func_8001E7B0(arg0);
    }
    func_80018390()->unk14(arg0, arg1);
}

void func_8001CD20(s32 arg0) {
    func_8001E7B0(arg0);
    func_80018390()->unk18(arg0);
}

void func_8001CD60(Unk_8001CD60 *arg0, s32 **arg1, s32 arg2) {
    s32 v;

    func_80018390()->unk38(arg0, arg1, arg2);
    v = **arg1 & 0xF;
    if (v == 2) {
        arg0->vt->unk94(arg0, arg1, arg2);
    } else if (v == 5) {
        arg0->vt->unk98(arg0, arg1, arg2);
    } else if (v == 4) {
        arg0->vt->unk9C(arg0, arg1, arg2);
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

void func_8001CEB4(struct Unk_8001E6F8 *arg0, s32 arg1, Unk_8001EC84 *arg2) {
    s32 sp10[3];
    s32 i;
    Unk_8001E6F8_Src *src;
    s16 *p;
    s16 *cur;

    sp10[0] = func_8001EC84(arg2);
    sp10[1] = func_8001EC84(arg2 + 1);
    sp10[2] = func_8001EC84(arg2 + 2);
    sp10[0] /= 0x168;
    sp10[1] /= 0x168;
    sp10[2] /= 0x168;
    src = arg0->unk14->unk44;
    p = &src->unk10;
    if (arg1 != 0) {
        src->unk10 = sp10[0];
        src->unk12 = sp10[1];
        src->unk14 = sp10[2];
    } else {
        for (i = 0; i < 3; i++) {
            cur = p;
            p = cur + 1;
            *cur = (*cur + sp10[i]) % 0x1000;
        }
    }
    arg0->unk14->unk0 = 0;
}

void func_8001D008(Unk_8001D008 *arg0, s32 arg1, Unk_8001EC84 *arg2) {
    s32 x;
    s32 y;
    s32 z;
    s32 *dst;

    x = func_8001EC84(arg2);
    y = func_8001EC84(arg2 + 1);
    z = func_8001EC84(arg2 + 2);
    dst = arg0->unk14->unk44;
    if (arg1 != 0) {
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

void *func_8001D0EC(struct Unk_8001D1A4 *arg0, Unk_8001D0EC_Obj *arg1, Unk_8001D0EC_Vec *arg2) {
    Unk_8001D1A4_Sub *temp_v1;

    if (arg0->unkC == NULL) {
        arg0->unkC = (Unk_8001D1A4_Obj *) arg1;
        arg0->unk14->unk48 = arg1->unk14;
        arg1->unk0->unk10(arg1, arg0);
        temp_v1 = arg0->unk14;
        if (arg2 != NULL) {
            temp_v1->unk18 = arg2->unk0;
            temp_v1->unk1C = arg2->unk4;
            temp_v1->unk20 = arg2->unk8;
        } else {
            temp_v1->unk18 = 0;
            temp_v1->unk1C = 0;
            temp_v1->unk20 = 0;
        }
        arg0->unk14->unk0 = 0;
    }
    return arg0;
}

void *func_8001D1A4(struct Unk_8001D1A4 *arg0) {
    Unk_8001D1A4_Obj *temp;

    temp = arg0->unkC;
    if (temp != NULL) {
        temp->vt->unk14(temp, arg0);
        arg0->unk14->unk48 = 0;
        arg0->unkC = NULL;
    }
    return arg0;
}

void func_8001D204(Unk_8001D204_Obj *arg0) {
    Unk_8001D204_Obj *sp10;
    s32 sp14;

    sp10 = NULL;
    do {
        arg0->vt->unk58(arg0, &sp10, &sp14);
        if (sp10 != NULL) {
            sp10->vt->unk50(sp10);
        }
    } while (sp14 != 0);
}

void func_8001D280(struct Unk_8001D280 *arg0, struct Unk_8001D280_Obj **arg1, struct Unk_800183A0 **arg2) {
    struct Unk_8001D280_Obj *obj;

    do {
        if (*arg1 == NULL) {
            *arg2 = arg0->unk4;
        }
        func_800183A0((s32 *)arg1, arg2);
        obj = *arg1;
        if (obj != NULL && (*obj->unk0 & 0xF) == 4 && obj->unkC == arg0) {
            return;
        }
    } while (*arg2 != NULL);
    *arg1 = NULL;
}

void func_8001D33C(void) {
}

s32 func_8001D344(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 0x1F, 1, arg1 == 0) == 0;
}

void func_8001D374(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0x1E, 1, arg1 != 0);
}

void func_8001D3A0(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0x1C, 2, arg1);
}

void func_8001D3CC(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 6, 1, arg1 == 0);
}

void func_8001D3F8(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 3, 3, arg1);
}

void func_8001D424(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0, 3, arg1);
}

s32 func_8001D450(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 7, 1, arg1 == 0) == 0;
}

void func_8001D480(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 9, 3, arg1);
}

s32 func_8001D4AC(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 8, 1, arg1 == 0) == 0;
}

void func_8001D4DC(struct Unk_8001E6F8 *arg0, void *arg1, s32 arg2) {
    Unk_8001D4DC rot;
    Unk_8001E6F8_Src *src;

    src = arg0->unk14->unk44;
    if (arg2 != 0) {
        rot.vx = -src->unk10;
        rot.vy = -src->unk12;
        rot.vz = -src->unk14;
    } else {
        rot = *(Unk_8001D4DC *)&src->unk10;
    }
    RotMatrix(&rot, arg1);
}

void func_8001D568(Unk_8001D568 *arg0, s32 arg1) {
    s32 sp10[14];
    s32 temp_a0;

    if (arg1 < 4) {
        if (arg1 >= 2) {
            temp_a0 = arg0->unk20;
            if ((temp_a0 != 0) && (func_8001F3A4(temp_a0) != 0)) {
                arg0->vt->unk8C(arg0, sp10);
                arg0->vt->unk90(arg0, sp10, arg1);
            }
        }
    }
}

void func_8001D600(struct Unk_8001D600 *arg0) {
    func_8001F51C(arg0->unk20);
}

void func_8001D624(struct Unk_8001D624 *arg0, s32 *arg1, s32 arg2) {
    func_8001EE04(arg1 + 1, arg1 + 1, arg1[0] * 8, arg0->unk14 + 0x24);
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

void func_8001D6B4(Unk_8001D6B4 *arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
        case 2:
        case 3:
            arg0->unk0->unkA0(arg0, arg1, arg2);
            break;
        case 4:
            arg0->unk28 = arg1;
            break;
    }
}

void func_8001D714(Unk_8001D714_Obj *arg0, Unk_8001D714_Arg *arg1) {
    Unk_8001D0EC_Vec sp18;
    u16 sp28[3];
    u8 sp30[0x20];
    Unk_8001D714_Loc loc;
    Unk_8001D0EC_Vec *src;
    Unk_8001D0EC_Vec *dst;
    s32 *p;

    if (arg0->unk20 != 0 && func_8001F3A4(arg0->unk20) != 0) {
        src = NULL;
        if (arg1->unkC != 0) {
            src = (Unk_8001D0EC_Vec *)(arg1->unk14 + 0x38);
        }
        sp18 = *src;
        dst = NULL;
        if (arg0->unkC != 0) {
            dst = (Unk_8001D0EC_Vec *)(arg0->unk14 + 0x38);
        }
        sp18.unk0 -= dst->unk0;
        sp18.unk4 -= dst->unk4;
        sp18.unk8 -= dst->unk8;
        if ((sp18.unk0 >= 0 ? sp18.unk0 < 0x4001 : ~sp18.unk0 + 1 < 0x4001)
         && (sp18.unk4 >= 0 ? sp18.unk4 < 0x4001 : ~sp18.unk4 + 1 < 0x4001)
         && (sp18.unk8 >= 0 ? sp18.unk8 < 0x4001 : ~sp18.unk8 + 1 < 0x4001)) {
            sp28[0] = sp18.unk0;
            sp28[1] = sp18.unk4;
            sp28[2] = sp18.unk8;
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

void func_8001D950(Unk_8001D950 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 arg4) {
    s32 sp10[8];
    s32 sp30[8];
    Unk_8001D950 *node;

    arg0->vt->unk84(arg0, sp30, 1);
    for (node = arg0->unkC; node != NULL; node = node->unkC) {
        node->vt->unk84(node, sp10, 1);
        MulMatrix2(sp10, sp30);
    }
    func_8001EE04(arg2, arg3, arg4, (s32)sp30);
    if (arg1 != NULL) {
        func_8001EE04(arg1, arg1, 1, (s32)sp30);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001DA28);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001DDF4);

s32 func_8001E110(Unk_8001ECFC_Pt *arg0, Unk_8001ECFC *arg1, Unk_8001ECFC_Pt *arg2, Unk_8001ECFC_Pt *arg3) {
    Unk_8001ECFC_Pt mid;
    u8 temp_s0;
    u8 temp_v0;
    s32 var_v0;

    temp_s0 = func_8001ECFC(arg1, arg2);
    temp_v0 = func_8001ECFC(arg1, arg3);
    if (!temp_s0) {
        if (!temp_v0) {
            return 1;
        }
    } else if (!temp_v0) {
        if (arg0 != 0) {
            func_8001E2E8(arg0, arg1, arg3, arg2);
        }
        return 3;
    }
    if (!temp_s0) {
        if (arg0 != 0) {
            func_8001E2E8(arg0, arg1, arg2, arg3);
        }
        return 2;
    }
    if (temp_s0 & temp_v0) {
        return 0;
    }
    mid.unk0 = (arg2->unk0 + arg3->unk0) >> 1;
    mid.unk2 = (arg2->unk2 + arg3->unk2) >> 1;
    mid.unk4 = (arg2->unk4 + arg3->unk4) >> 1;
    if (arg2->unk0 == mid.unk0 && arg2->unk2 == mid.unk2 && arg2->unk4 == mid.unk4) {
        return 0;
    }
    if (arg3->unk0 == mid.unk0 && arg3->unk2 == mid.unk2 && arg3->unk4 == mid.unk4) {
        return 0;
    }
    if ((var_v0 = func_8001E110(arg0, arg1, arg2, &mid)) != 0
     || (var_v0 = func_8001E110(arg0, arg1, &mid, arg3)) != 0) {
        return var_v0;
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

void func_8001E4A4(s32 arg0, Unk_8001816C *arg1) {
    Unk_8001E4A4 *obj;
    s32 **p;
    s32 more;

    p = NULL;
    do {
        for (;;) {
            func_8001816C(arg1, (s32 *)&p, &more);
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

void func_8001E58C(Unk_8001E58C_Obj *arg0, Unk_8001E58C_Dst *arg1, Unk_8001E58C_Src *arg2) {
    s32 sp10[8];

    arg0->vt->unk84(arg0, sp10, 0);
    arg1->unk0 = arg2->unk0;
    arg1->unk4 = arg2->unk2;
    arg1->unk8 = arg2->unk4;
    func_8001EE98(arg1, arg1, 1, sp10);
}

void func_8001E600(struct Unk_8001E600 *arg0, Unk_8001E58C_Dst *arg1, Unk_8001E58C_Src *arg2) {
    s32 sp10[8];
    s32 *var_v1;

    arg0->vt->unk84(arg0, sp10, 0);
    func_8001EE98(arg1, arg2, 1, sp10);
    var_v1 = NULL;
    if (arg0->unkC != NULL) {
        var_v1 = (s32 *)(arg0->unk14 + 0x38);
    }
    arg1->unk0 += *var_v1;
    var_v1 = NULL;
    if (arg0->unkC != NULL) {
        var_v1 = (s32 *)(arg0->unk14 + 0x38);
    }
    arg1->unk4 += var_v1[1];
    var_v1 = NULL;
    if (arg0->unkC != NULL) {
        var_v1 = (s32 *)(arg0->unk14 + 0x38);
    }
    arg1->unk8 += var_v1[2];
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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E7BC);

void func_8001EA8C(s32 *arg0, s16 *arg1, s16 *arg2) {
    arg0[0] = arg2[0] - arg1[0];
    arg0[1] = arg2[1] - arg1[1];
    arg0[2] = arg2[2] - arg1[2];
}

void func_8001EACC(Unk_8001EACC_Obj *arg0, Unk_8001EACC_Arg *arg1, s32 arg2, s32 arg3, s32 *arg4) {
    s16 buf[6];
    Unk_8001EACC_Vec *s0;
    Unk_8001EACC_Vec *s1;
    s32 v1;

    s1 = &arg0->unk14->vec18;
    if (arg1->unkC != 0) {
        s0 = &arg1->unk14->vec38;
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
    arg0->unk0->unk44(arg0, 1, buf);
    if (arg4 != 0) {
        arg0->unk0->unk44(arg0, 0, arg4);
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

void func_8001EE04(Unk_8001EE04 *arg0, Unk_8001EE04 *arg1, s32 arg2, void *arg3) {
    Unk_8001EE04 tmp;
    Unk_8001EE04 *end;

    end = arg0 + arg2;
    while (arg0 < end) {
        tmp = *arg1;
        ApplyMatrixSV(arg3, &tmp, arg0);
        arg0++;
        arg1++;
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

s32 func_8001EF14(s32 *arg0, s32 arg1, s32 *arg2) {
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

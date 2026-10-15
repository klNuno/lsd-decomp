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
    u8 pad_00[0x48];
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
    u8 pad_00[0x44];
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
void func_8001EE04(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CAF4);

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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CD60);

void func_8001CE30(Unk_8001CE30 *arg0) {
    arg0->unk24 = 0;
    arg0->unk10 = 0;
    GsInitCoordinate2(0, arg0->unk14);
    arg0->unk0->unk44(arg0, 1, D_8006B684);
    arg0->unk0->unk48(arg0, 1, D_8006B690);
    *arg0->unk14 = 1;
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CEB4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D008);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D0EC);

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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D280);

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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D4DC);

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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D714);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D950);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001DA28);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001DDF4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E110);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E2E8);

void func_8001E49C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E4A4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E57C);

void func_8001E58C(Unk_8001E58C_Obj *arg0, Unk_8001E58C_Dst *arg1, Unk_8001E58C_Src *arg2) {
    s32 sp10[8];

    arg0->vt->unk84(arg0, sp10, 0);
    arg1->unk0 = arg2->unk0;
    arg1->unk4 = arg2->unk2;
    arg1->unk8 = arg2->unk4;
    func_8001EE98(arg1, arg1, 1, sp10);
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E600);

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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E7B0);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E7BC);

void func_8001EA8C(s32 *arg0, s16 *arg1, s16 *arg2) {
    arg0[0] = arg2[0] - arg1[0];
    arg0[1] = arg2[1] - arg1[1];
    arg0[2] = arg2[2] - arg1[2];
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EACC);

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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EE04);

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

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EF60);

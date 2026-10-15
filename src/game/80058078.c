#include "common.h"

extern void func_800183DC(void *, s32);
typedef struct { u8 p0[0x24]; u32 u24; u8 p1[0x70 - 0x28]; s32 u70; s32 u74; u8 p2[0x120 - 0x78]; u32 u120; s32 u124; } Unk_80059394;
u8 *D_8008ACB4;
s32 *D_8008ACB8;
extern s32 D_8008ABF0[];
s32 D_8008ACC4;
s32 D_8008ACBC;
typedef struct { u8 pad[5]; s8 u5; } S6;
extern S6 *D_80088BA4[];
s32 D_8008ACC8;
typedef struct Unk_8005A2D0 {
    u8 pad[0x678];
    s32 unk678;
} Unk_8005A2D0;
typedef struct Unk_8005B5A4 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Unk_8005B5A4;
typedef struct Unk_80059360 {
    u8 pad[0x24];
    u32 unk24;
} Unk_80059360;
typedef struct Unk_8005A168 {
    u8 pad[0xAC];
    s32 unkAC;
    s32 unkB0;
} Unk_8005A168;
extern s16 D_80087F14[];
typedef struct Unk_8005A184 {
    u8 pad[0xAC];
    s32 unkAC;
    s32 unkB0;
} Unk_8005A184;
typedef struct Unk_8005A2E4 {
    u8 pad[0x17C];
    s32 unk17C;
    s32 unk180;
} Unk_8005A2E4;
typedef struct { u8 pad[0x924]; s32 u924; } Unk_8005BA20;
void func_800573CC(void *arg0, s32 arg1, s32 *arg2);
extern void func_80056D18(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_800531CC(void *, void *);
typedef struct { s32 u0; s32 u4; u8 pad[0x14]; s32 u1C; s32 u20; u8 pad2[0xC]; s32 u30; s32 u34; } S;
typedef struct Unk_8005A134 {
    u8 pad[0x58];
    void *u58;
    u8 pad2[0xC4 - 0x5C];
    s32 uC4;
    s32 uC8;
    u8 uCC[1];
} Unk_8005A134;
void func_8002CC84(void *, void *);
typedef struct Unk_8005A1B0 {
    u8 pad[0x124];
    s32 unk124;
    s32 unk128;
    s32 unk12C;
    s32 unk130;
} Unk_8005A1B0;
typedef struct Unk_80059328 {
    u8 pad_00[0x134];
    s32 unk134;
} Unk_80059328;
typedef struct Unk_8005A304 {
    u8 pad_00[0x17C];
    s32 unk17C;
    s32 unk180;
} Unk_8005A304;
typedef struct Unk_8005B4E0_Vtbl {
    u8 pad_00[0x1FC];
    void (*unk1FC)(void *, s16 *);
} Unk_8005B4E0_Vtbl;
typedef struct Unk_8005B4E0 {
    Unk_8005B4E0_Vtbl *unk0;
} Unk_8005B4E0;
void func_8005B518(s16 *arg0);
typedef struct Unk_8005B5B8 {
    s8 unk0;
    s8 unk1;
} Unk_8005B5B8;
extern u8 D_80088748[];
extern s32 D_80088710[];
extern s32 D_80088664[];
s32 func_8005C150(void *arg0, void *arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 arg6);
extern u8 D_800889F0[];
extern void *D_80088980[];
extern void *D_80088820[];
typedef struct Unk_8005B3A4_Vtbl {
    u8 pad_00[0x208];
    void (*unk208)(void *, void *, s16 *);
} Unk_8005B3A4_Vtbl;
typedef struct Unk_8005B3A4 {
    Unk_8005B3A4_Vtbl *unk0;
    u8 pad_04[0x144 - 0x4];
    u8 unk144[0x164 - 0x144];
    s32 unk164;
} Unk_8005B3A4;
s16 *func_800495B8(s32 arg0, s8 *arg1);
extern u8 D_80088B5C;
extern s32 D_80088B24;
extern s32 D_80088A80;
s32 D_8008ABE4;
extern u8 D_80088CBC[];
extern s32 D_80088C4C[];
typedef struct Unk_800593D8 {
    u8 pad_00[0x80];
    void (*unk80)(void);
    u8 pad_84[0x98 - 0x84];
    void (*unk98)(struct Unk_800593D8 *);
} Unk_800593D8;
typedef struct Unk_800597C0_Vtbl {
    u8 pad_00[0x144];
    void (*unk144)(void *);
    void (*unk148)(void *);
} Unk_800597C0_Vtbl;
typedef struct Unk_800597C0 {
    Unk_800597C0_Vtbl *unk0;
} Unk_800597C0;
s32 func_8005BB30(void *, s32, s32);
void func_8005A928(void *, s32, s32, s32);
typedef struct Unk_8005A580 {
    u8 pad_00[0x24];
    s32 unk24;
    u8 pad_28[0x44 - 0x28];
    s32 unk44;
    u8 pad_48[0x164 - 0x48];
    s32 unk164;
    u8 pad_168[0x16C - 0x168];
    u8 unk16C[1];
} Unk_8005A580;
typedef struct Unk_80059610_Vtbl {
    u8 pad[0x138];
    void (*unk138)(void *, s32);
    void (*unk13C)();
} Unk_80059610_Vtbl;
typedef struct Unk_80059610 {
    Unk_80059610_Vtbl *unk0;
} Unk_80059610;
typedef struct Unk_80059E3C_Vtbl {
    u8 pad_00[0x84];
    void (*unk84)(void *, s32);
} Unk_80059E3C_Vtbl;
typedef struct Unk_80059E3C_Obj {
    Unk_80059E3C_Vtbl *vt;
} Unk_80059E3C_Obj;
typedef struct Unk_80059E3C {
    u8 pad_00[0x58];
    Unk_80059E3C_Obj *u58;
    u8 pad_5C[0xBC - 0x5C];
    s32 uBC;
} Unk_80059E3C;
typedef struct Unk_800590E8 {
    u8 pad[0x68];
    s32 unk68;
    u8 pad2[0x180 - 0x6C];
    s32 unk180;
} Unk_800590E8;
typedef struct Unk_8005A050 Unk_8005A050;
typedef struct Unk_8005A050_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(Unk_8005A050 *, s32, void *);
} Unk_8005A050_Vtbl;
struct Unk_8005A050 {
    Unk_8005A050_Vtbl *unk0;
    u8 pad_04[0xA4 - 0x04];
    s32 unkA4;
};
extern u8 D_80087E80[];
typedef struct Unk_8005AFDC_VtblA {
    u8 pad_00[0x1F4];
    void (*unk1F4)(void *, s32);
} Unk_8005AFDC_VtblA;
typedef struct Unk_8005AFDC_A {
    Unk_8005AFDC_VtblA *vt;
} Unk_8005AFDC_A;
typedef struct Unk_8005AFDC_VtblB {
    u8 pad_00[0x10C];
    s32 (*unk10C)(void *, s32, s32);
} Unk_8005AFDC_VtblB;
typedef struct Unk_8005AFDC_B {
    Unk_8005AFDC_VtblB *vt;
} Unk_8005AFDC_B;
typedef struct Unk_800581C4_Obj {
    u8 pad_00[0x70];
    void (*unk70)(void *, s32);
    u8 pad_74[0x94 - 0x74];
    void (*unk94)(void *);
} Unk_800581C4_Obj;
typedef struct Unk_800581C4 {
    Unk_800581C4_Obj *unk0;
    u8 pad_04[0x238 - 0x04];
    s32 unk238;
} Unk_800581C4;
typedef struct Unk_80059AEC_Vtbl {
    u8 pad_00[0x164];
    s32 (*unk164)(void *, s32);
    u8 pad_168[0x170 - 0x168];
    void (*unk170)(void *, s32);
} Unk_80059AEC_Vtbl;
typedef struct Unk_80059AEC {
    Unk_80059AEC_Vtbl *unk0;
    u8 pad_04[0x70 - 0x04];
    s32 unk70;
} Unk_80059AEC;
void func_8005BCB4(void *, void *, s32);
typedef struct Unk_80058078_Vtbl {
    u8 pad_00[0x6C];
    void (*unk6C)(void *, s32);
    u8 pad_70[0xD4 - 0x70];
    void (*unkD4)(void *, void *, s32);
} Unk_80058078_Vtbl;
typedef struct Unk_80058078 {
    Unk_80058078_Vtbl *vt;
    u8 pad_04[0x2C - 0x04];
    s32 unk2C;
    u8 pad_30[0x84 - 0x30];
    s32 unk84;
} Unk_80058078;
typedef struct Unk_80059148_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, s32);
    u8 pad_48[0x180 - 0x48];
    void (*unk180)(void *, s32);
} Unk_80059148_Vtbl;
typedef struct Unk_80059148 {
    Unk_80059148_Vtbl *unk0;
    u8 pad_04[0x6C - 0x04];
    s32 unk6C;
    u8 pad_70[0x884 - 0x70];
    s32 unk884;
} Unk_80059148;
typedef struct Unk_8005AF64_Vtbl {
    u8 pad_00[0xBC];
    void (*unkBC)(void *, s32 *);
} Unk_8005AF64_Vtbl;
typedef struct Unk_8005AF64 {
    Unk_8005AF64_Vtbl *unk0;
} Unk_8005AF64;
s32 func_8005BA7C(void);
typedef struct Unk_8005B6E0 {
    u8 pad[0x184];
    s32 unk184;
    s32 unk188;
    s32 unk18C;
} Unk_8005B6E0;
typedef struct Unk_80058390_Vt {
    u8 pad_00[0x44];
    void (*unk44)(void *, void *, s32);
} Unk_80058390_Vt;
typedef struct Unk_80058390 {
    u8 pad_00[0x38];
    s32 unk38;
    u8 pad_3C[0x238 - 0x3C];
    s32 unk238;
} Unk_80058390;
extern Unk_80058390_Vt *func_8003DFBC(void);
typedef struct Unk_80058A94_Vt {
    u8 pad_00[0x14];
    void (*unk14)(void *, void *);
} Unk_80058A94_Vt;
typedef struct Unk_80058A94_ObjVt {
    u8 pad_00[0xF0];
    void (*unkF0)(void *);
} Unk_80058A94_ObjVt;
typedef struct Unk_80058A94_Obj {
    Unk_80058A94_ObjVt *vt;
} Unk_80058A94_Obj;
typedef struct Unk_80058A94 {
    Unk_80058A94_Vt *unk0;
    u8 pad_04[0x4C - 0x4];
    Unk_80058A94_Obj *unk4C;
} Unk_80058A94;
typedef struct Unk_80058A94_RetVt {
    u8 pad_00[0x50];
    void (*unk50)(void *);
} Unk_80058A94_RetVt;
Unk_80058A94_RetVt *func_80057C84(void);
extern u16 D_8008875C[];
typedef struct Unk_8005BE28 {
    u8 pad_00[4];
    u16 u4;
} Unk_8005BE28;
s32 D_8008ABE0;
extern void func_8005BA50(u8 *arg0, s32 *arg1);
extern void *memset(void *arg0, s32 arg1, s32 arg2);
typedef struct Unk_8005A258 {
    u8 pad_00[0x178];
    s32 unk178;
    s32 unk17C;
    s32 unk180;
    s32 unk184;
    s32 unk188;
    s32 unk18C;
    u8 pad_190[0x46C - 0x190];
    s32 unk46C;
    u8 pad_470[0x5D8 - 0x470];
    u8 unk5D8;
    u8 pad_5D9[0x5DF - 0x5D9];
    u8 unk5DF;
    u8 unk5E0[0x600 - 0x5E0];
    s32 unk600[(0x678 - 0x600) / 4];
    s32 unk678;
    s32 unk67C;
    s32 unk680;
    u8 unk684[0x1F4];
} Unk_8005A258;
s32 func_8005C28C(void *arg0, s32 *arg1, void *arg2, s32 arg3);
typedef struct Unk_8005A508_Vtbl {
    u8 pad_00[0x104];
    s32 (*unk104)(void *, s32);
    u8 pad_108[0x1EC - 0x108];
    void (*unk1EC)(void *, void *, s32);
} Unk_8005A508_Vtbl;
typedef struct Unk_8005A508 {
    Unk_8005A508_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    u8 pad_48[0x164 - 0x48];
    s32 unk164;
    u8 pad_168[0x16C - 0x168];
    u8 unk16C[1];
    u8 pad_16D[0x180 - 0x16D];
    s32 unk180;
} Unk_8005A508;

void func_80058078(Unk_80058078 *arg0) {
    arg0->unk84 = 5;
    arg0->unk2C = 0x190;
    arg0->vt->unkD4(arg0, "ETC\\HGRAPH.TIM", 0);
    arg0->vt->unk6C(arg0, 10);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800580E0);

void func_800581C4(Unk_800581C4 *arg0) {
    if (arg0->unk238 == 0) {
        arg0->unk0->unk70(arg0, 0x10);
        arg0->unk0->unk94(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058228);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058308);

s32 func_80058390(Unk_80058390 *arg0, void *arg1, s32 arg2) {
    s32 ret;

    func_8003DFBC()->unk44(arg0, arg1, arg2);
    ret = 2;
    if (arg0->unk238 == 0) {
        ret = arg0->unk38;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058404);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800585B4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058694);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058764);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058774);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800587F0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800588EC);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058968);

void func_80058A94(Unk_80058A94 *arg0) {
    Unk_80058A94_Obj *temp_a0;

    temp_a0 = arg0->unk4C;
    temp_a0->vt->unkF0(temp_a0);
    arg0->unk0->unk14(arg0, arg0->unk4C);
    func_80057C84()->unk50(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058B08);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058C58);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058D94);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058E8C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058F18);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058FAC);

void func_800590E0(void) {
}

s32 func_800590E8(Unk_800590E8 *arg0, s32 *arg1, s32 arg2) {
    s32 temp_s1;

    temp_s1 = arg0->unk68;
    if (arg2 < 0) {
        *arg1 = ((s32 (*)(void *))func_8005B518)((u8 *)arg0 + (arg0->unk180 * 2 + 0x190));
    } else {
        arg0->unk68 = arg2;
    }
    return temp_s1;
}

void func_80059148(Unk_80059148 *arg0, s32 arg1) {
    s32 temp_a2;

    arg0->unk6C = arg1;
    if (arg1 != 0) {
        arg0->unk0->unk180(arg0, 1);
        temp_a2 = arg0->unk884;
        if (temp_a2 != 0) {
            arg0->unk0->unk44(arg0, 1, temp_a2);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800591B4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059310);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005931C);

s32 func_80059328(Unk_80059328 *arg0, s32 arg1) {
    s32 old;

    if (arg1 >= 0) {
        arg1 *= 15;
    }
    old = arg0->unk134;
    arg0->unk134 = arg1;
    if (old >= 0) {
        old = (u32)old / 15;
    }
    return old;
}

u32 func_80059360(Unk_80059360 *arg0) {
    return arg0->unk24 / 15;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005937C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059384);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005938C);

void func_80059394(Unk_80059394 *arg0) {
    if (arg0->u70 == 0) {
        arg0->u74 = 0;
        arg0->u124 = arg0->u24 % arg0->u120 == 0;
    }
}

void func_800593D8(Unk_800593D8 *arg0) {
    if (arg0->unk80 != NULL) {
        arg0->unk80();
    }
    if (arg0->unk98 != NULL) {
        arg0->unk98(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005942C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005950C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059590);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059598);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800595A0);

void func_800595A8(Unk_80059610 *arg0, s32 arg1) {
    arg0->unk0->unk13C(arg0, 0);
    if (arg1 != 0) {
        arg0->unk0->unk138(arg0, 0);
    }
}

void func_80059610(Unk_80059610 *arg0, s32 arg1, s32 arg2) {
    arg0->unk0->unk13C(arg0);
    arg0->unk0->unk138(arg0, arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005966C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800596E8);

void func_800597C0(Unk_800597C0 *arg0) {
    arg0->unk0->unk144(arg0);
    arg0->unk0->unk148(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059814);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800598E8);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059A1C);

void func_80059A48(void) {
}

void func_80059A50(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059A58);

void func_80059AEC(Unk_80059AEC *arg0) {
    if (arg0->unk70 == 0) {
        arg0->unk0->unk170(arg0, arg0->unk0->unk164(arg0, 1));
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059B50);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059BD4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059BE0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059D1C);

void func_80059E3C(Unk_80059E3C *arg0) {
    s32 temp_a1;
    Unk_80059E3C_Obj *temp_a0;

    temp_a1 = arg0->uBC;
    if (temp_a1 >= 0) {
        temp_a0 = arg0->u58;
        temp_a0->vt->unk84(temp_a0, temp_a1);
        arg0->uBC = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059E98);

void func_8005A050(Unk_8005A050 *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unkA4;
    if (temp_v0 != 0) {
        arg0->unk0->unk44(arg0, 0, D_80087E80 + temp_v0 * 12);
        arg0->unkA4 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A0B0);

void func_8005A134(Unk_8005A134 *arg0, s32 arg1) {
    arg0->uC4 = 0;
    arg0->uC8 = arg1;
    if (arg1 != 0) {
        func_8002CC84(arg0->u58, arg0->uCC);
    }
}

s32 func_8005A168(Unk_8005A168 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0->unkAC;
    if (arg1 >= 0) {
        arg0->unkAC = arg1;
        arg0->unkB0 = arg1;
    }
    return temp_v0;
}

void func_8005A184(Unk_8005A184 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0->unkAC;
    if (temp_v0 != arg1) {
        arg0->unkB0 = temp_v0;
        arg0->unkAC = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A1A4);

void func_8005A1B0(Unk_8005A1B0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg1 >= 0) {
        arg0->unk124 = arg1;
    }
    if (arg2 >= 0) {
        arg0->unk128 = arg2;
    }
    if (arg3 >= 0) {
        arg0->unk12C = arg3;
    }
    if (arg4 >= 0) {
        arg0->unk130 = arg4;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A1EC);

void func_8005A1F4(s32 arg0, S *arg1) {
    s32 r;
    if (arg1->u0 == 1) {
        r = arg1->u4 % 20; if (r == 0) {
            arg1->u1C = 9;
            arg1->u20 = -1;
        } else {
            arg1->u30 = 9;
            arg1->u34 = -1;
        }
    }
}

void func_8005A258(Unk_8005A258 *arg0) {
    arg0->unk178 = D_8008ABE0;
    arg0->unk17C = 0;
    arg0->unk180 = 0;
    arg0->unk184 = 0;
    arg0->unk188 = 0;
    arg0->unk18C = 0;
    arg0->unk46C = 0;
    arg0->unk5DF = 0;
    arg0->unk5D8 = 0;
    arg0->unk678 = 1;
    arg0->unk67C = 0;
    arg0->unk680 = 0;
    func_8005BA50(arg0->unk5E0, arg0->unk600);
    memset(arg0->unk684, 0, 0x1F4);
}

void func_8005A2D0(Unk_8005A2D0 *arg0, s32 *arg1) {
    s32 temp_v1;

    temp_v1 = arg0->unk678;
    arg0->unk678 = *arg1;
    *arg1 = temp_v1;
}

s32 func_8005A2E4(Unk_8005A2E4 *arg0, s32 *arg1) {
    if (arg1 != NULL) {
        *arg1 = arg0->unk17C;
    }
    return arg0->unk180 + 1;
}

s32 func_8005A304(Unk_8005A304 *arg0) {
    if (++arg0->unk180 >= 365) {
        arg0->unk180 = 0;
        arg0->unk17C++;
    }
    return arg0->unk180;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A33C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A344);

s32 func_8005A350(s32 arg0, s32 *arg1) {
    if (arg1 != NULL) {
        *arg1 = 0x700;
    }
    return arg0 + 0x178;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A368);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A41C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A4E8);

void func_8005A508(Unk_8005A508 *arg0) {
    s32 sp10;
    s32 sp14;

    arg0->unk0->unk1EC(arg0, &sp10, 1);
    arg0->unk164 = func_8005C28C(arg0->unk16C, &sp14, &sp10, arg0->unk180);
    sp14 = arg0->unk0->unk104(arg0, sp14);
    arg0->unk44 = 0xB;
}

void func_8005A580(Unk_8005A580 *arg0) {
    if (arg0->unk44 == 0) {
        func_8005A928(arg0, func_8005BB30(arg0->unk16C, arg0->unk164, arg0->unk24), 0xC, 1);
    }
}

s32 func_8005A5D8(Unk_8005A580 *arg0, void *arg1) {
    s32 temp_v0;

    if (arg0->unk44 == 0) {
        temp_v0 = ((s32 (*)(void *, void *, s32))func_8005BCB4)(arg0->unk16C, arg1, arg0->unk164);
        if (temp_v0 >= 0) {
            func_8005A928(arg0, temp_v0, 0xD, 1);
            return 1;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A63C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A700);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A7A0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A82C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A928);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A9CC);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AB2C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AC24);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AD68);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AE40);

void func_8005AF64(Unk_8005AF64 *arg0, s16 *arg1, s16 *arg2) {
    s32 sp10[3];

    sp10[0] = arg1[0] - arg2[0];
    sp10[1] = arg1[1] - arg2[1];
    sp10[2] = arg1[2] - arg2[2];
    sp10[1] = 0;
    arg0->unk0->unkBC(arg0, sp10);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AFD0);

void func_8005AFDC(Unk_8005AFDC_A *arg0, Unk_8005AFDC_B *arg1, s32 arg2) {
    if (arg2 == 5) {
        arg0->vt->unk1F4(arg0, arg1->vt->unk10C(arg1, 0, 0));
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B03C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B1F4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B2F4);

void func_8005B3A4(Unk_8005B3A4 *arg0, s8 *arg1) {
    arg0->unk0->unk208(arg0, arg0->unk144, func_800495B8(arg0->unk164, arg1));
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B3F0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B420);

void func_8005B4E0(Unk_8005B4E0 *arg0) {
    s16 sp10;

    arg0->unk0->unk1FC(arg0, &sp10);
    func_8005B518(&sp10);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B518);

void func_8005B5A4(s32 arg0, Unk_8005B5A4 *arg1) {
    arg1->unk0 = 0;
    arg1->unk8 = 0;
    arg1->unk4 = 0;
    arg1->unkC = 0;
}

void func_8005B5B8(s32 arg0, Unk_8005B5A4 *arg1, Unk_8005B5B8 *arg2) {
    s32 temp_v1;

    temp_v1 = arg1->unk4;
    arg1->unk0 = *(u16 *)arg2;
    arg1->unk4 = arg2->unk0 + temp_v1;
    arg1->unk8 = arg2->unk1 + arg1->unk8;
    arg1->unkC = arg1->unkC + 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B5F0);

s32 func_8005B66C(s32 arg0, s32 arg1, s32 arg2) {
    s32 r = arg1 / arg2 + arg0 / 3;
    if (r > 9) {
        r = -9;
    } else if (r < -9) {
        r = 9;
    }
    return r;
}

void func_8005B6E0(Unk_8005B6E0 *arg0) {
    s32 temp;

    arg0->unk188 = func_8005BA7C();
    temp = arg0->unk18C;
    if (temp < 0) {
        arg0->unk18C = 0;
    } else if (temp > 0x02FAF080) {
        arg0->unk18C = 0x02FAF080;
    }
    arg0->unk184 = arg0->unk188 + arg0->unk18C;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B74C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B81C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B8FC);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B904);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B990);

s32 func_8005BA20(Unk_8005BA20 *arg0, s32 arg1) {
    s32 temp;

    if (arg1 < 0) {
        return arg0->u924;
    }
    temp = arg0->u924;
    arg0->u924 = arg1;
    return temp;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BA40);

void func_8005BA50(u8 *arg0, s32 *arg1) {
    s32 i;
    for (i = 29; i >= 0; i--) {
        arg0[i] = 0;
    }
    D_8008ACB4 = arg0;
    *arg1 = 0;
    D_8008ACB8 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BA7C);

s16 func_8005BB14(s32 arg0) {
    return D_80087F14[arg0];
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BB30);

void func_8005BCB4(void *arg0, void *arg1, s32 arg2) {
    func_8005C150(arg0, arg1, arg2, D_80088748, D_80088710, D_80088664, 1);
}

s32 func_8005BCF8(void *arg0, s16 *arg1, s32 arg2) {
    return func_8005C150(arg0, arg1, arg2, D_800889F0, D_80088980, D_80088820, 1);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BD3C);

s32 func_8005BE28(Unk_8005BE28 *arg0, u8 arg1) {
    s32 diff = arg0->u4 - D_8008875C[arg1 * 6];
    s16 temp = diff;
    s16 var_a1;

    var_a1 = diff;
    if (temp > 0xB4) {
        var_a1 -= 0x168;
    } else if (temp < -0xB4) {
        var_a1 += 0x168;
    }
    return (u16)(var_a1 + 0x2C) < 0x59U;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BE90);

s32 *func_8005BF48(void) {
    s32 *r = NULL;
    if (D_8008ACC4 != 12) {
        r = D_8008ABF0;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BF68);

s32 func_8005BF74(void *arg0, void *arg1, s32 arg2) {
    if (D_8008ABE4 != 0) {
        return func_8005C150(arg0, arg1, arg2, &D_80088B5C, &D_80088B24, &D_80088A80, 0);
    }
    return -1;
}

s32 func_8005BFC4(void) {
    return D_8008ACBC == 0 ? 10 : 0;
}

s32 func_8005BFDC(void *arg0, void *arg1, s32 arg2) {
    if (arg2 == 0) {
        return func_8005C150(arg0, arg1, 0, D_80088CBC, D_80088C4C, (s32 *)D_80088BA4, 0);
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005C02C);

s32 func_8005C118(void) {
    return D_80088BA4[D_8008ACC4][D_8008ACC8].u5;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005C150);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005C28C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005C438);

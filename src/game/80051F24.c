#include "common.h"

s32 D_8008AC80;
extern void func_800183DC(void *, s32);
typedef struct { u8 p0[0x24]; u32 u24; u8 p1[0x70 - 0x28]; s32 u70; s32 u74; u8 p2[0x120 - 0x78]; u32 u120; s32 u124; } Unk_80059394;
void func_800573CC(void *arg0, s32 arg1, s32 *arg2);
extern void func_80056D18(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct { u8 pad[0x58]; void *u58; } Unk_800531A0;
extern void func_800531CC(void *, void *);
typedef struct Unk_800541D4 {
    u8 p0[0x20];
    s32 u20;
    u8 p1[0x80 - 0x24];
    s32 u80;
    s32 u84;
} Unk_800541D4;
extern void func_80056640(void);
typedef struct { s8 pad[6]; s8 u6; } K;
typedef struct { K *u0; s32 u4; s32 u8; s32 uC; s32 u10; } A;
typedef struct { s32 u0; s32 u4; s32 u8; } B;
extern s32 D_80087474[];
s32 D_8008AB50;
extern u8 D_8008E10C[];
s32 D_8008AC88;
extern u8 D_8008E0C8[];
void func_8002CC84(void *, void *);
extern s32 func_8001E7BC(void);
typedef struct Unk_80052CD8 {
    u8 pad_00[0xC];
    void (*unkC)(s32);
} Unk_80052CD8;
Unk_80052CD8 *func_8004A4B8(s32);
typedef struct Unk_800540E8 {
    u8 pad_00[0xB8];
    void (*unkB8)(void);
} Unk_800540E8;
extern s16 D_8008ABA8[];
void func_80057534(void *arg0, s16 *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s16 D_8008ABA4[];
typedef struct Unk_80057DBC {
    u8 pad_00[0x74];
    u16 unk74;
    u16 unk76;
    u8 pad_78[0xA0 - 0x78];
    s32 unkA0;
} Unk_80057DBC;
extern u16 D_80087AA4[];
extern u16 D_80087AA6[];
typedef struct Unk_800523F0_Obj Unk_800523F0_Obj;
typedef struct { u8 pad[0x80]; void (*f80)(Unk_800523F0_Obj *, s32, s32, s32); } Unk_800523F0_Vt;
struct Unk_800523F0_Obj { Unk_800523F0_Vt *vt; };
typedef struct Unk_800523F0 { u8 pad[0x3C]; Unk_800523F0_Obj *u3C; } Unk_800523F0;
typedef struct Unk_80052E7C { u8 pad_00[0x38]; s32 u38; } Unk_80052E7C;
void func_80049060(s32);
void func_80049098(s32, s32, s32);
typedef struct Unk_80056464_Vtbl {
    u8 pad_00[0xC];
    void (*unkC)(s32);
} Unk_80056464_Vtbl;
extern void func_80056718(void);
extern Unk_80056464_Vtbl *func_80057C84(void);
typedef struct Unk_80056794 { s32 u0; s32 u4; s32 u8; } Unk_80056794;
typedef struct Unk_800571A8_vt { u8 pad_00[0x18]; void (*unk18)(void *); } Unk_800571A8_vt;
typedef struct Unk_800571A8 { u8 pad_00[0x4C]; s32 unk4C; s32 unk50; } Unk_800571A8;
Unk_800571A8_vt *func_8001E57C(void);
typedef struct Unk_80054714Vt { u8 pad_00[4]; void (*unk4)(void *); } Unk_80054714Vt;
typedef struct Unk_80054714 { Unk_80054714Vt *vt; } Unk_80054714;
s32 D_8008AB54;
Unk_80054714 *D_8008AC94;
typedef struct Unk_80056238 {
    u8 p0[0x4];
    s32 u4;
    u8 p1[0x10 - 0x8];
    s32 u10;
    u8 p2[0x1C - 0x14];
    s32 u1C;
    s32 u20;
} Unk_80056238;
s32 func_8005627C(void *arg0);
extern void func_800558F0(s32, s32, s32);
typedef struct Unk_8005393C_Vtbl {
    u8 pad_00[0x10C];
    s32 (*unk10C)(void *, s32, s32);
} Unk_8005393C_Vtbl;
typedef struct Unk_8005393C_Obj {
    Unk_8005393C_Vtbl *unk0;
} Unk_8005393C_Obj;
typedef struct Unk_8005393C {
    u8 pad_00[0x14];
    Unk_8005393C_Obj *unk14;
} Unk_8005393C;
void func_8002CD08(s32, s32);
s32 *D_8008AC7C;
typedef struct Unk_80057444 {
    u8 pad_00[0xBC];
    void (*unkBC)(void *, void *);
} Unk_80057444;
extern void func_8001E58C(void *, void *, void *);
typedef struct { u8 pad[6]; u8 u6; } Unk_800557DC_Sub;
typedef struct { Unk_800557DC_Sub *u0; s32 u4; s32 u8; s32 uC; s32 u10; s32 u14; } Unk_800557DC;
typedef struct Unk_800564A4 { s32 u[9]; } Unk_800564A4;
typedef struct Unk_80057618 { u8 pad_00[0x28]; s32 u28; } Unk_80057618;
void func_80057668(void *arg0);
typedef struct Unk_8005217C_Vt {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32);
} Unk_8005217C_Vt;
typedef struct Unk_8005217C {
    Unk_8005217C_Vt *vt;
    u8 pad_04[0x34 - 0x4];
    s32 u34;
    s32 u38;
    s32 u3C;
} Unk_8005217C;
typedef struct Unk_80057C14_Vt { u8 pad_00[0x9C]; void (*unk9C)(s32, s32, s32); } Unk_80057C14_Vt;
extern u8 D_8008AB10[];
typedef struct Unk_800529FC_Vt { u8 pad_00[0xB8]; void (*fB8)(void *, void *, s32, s32); } Unk_800529FC_Vt;
typedef struct Unk_800529FC_Obj { Unk_800529FC_Vt *vt; } Unk_800529FC_Obj;
typedef struct Unk_800529FC { u8 pad_00[0x20]; s32 u20; s32 u24; s32 u28; u8 pad_2C[0x40 - 0x2C]; Unk_800529FC_Obj *u40[1]; } Unk_800529FC;
typedef struct Unk_80057F68 {
    u8 pad[8];
    void (*unk8)(void *, s32);
} Unk_80057F68;
void *func_80017B34(s32 size);
Unk_80057F68 *func_80058764(void);
extern void func_80053EB4(void *, s32, s32, s32, s32);
typedef struct Unk_80053D9C_Obj Unk_80053D9C_Obj;
typedef struct Unk_80053D9C_Vtbl {
    u8 pad_00[0xF4];
    void (*unkF4)(Unk_80053D9C_Obj *, s32);
} Unk_80053D9C_Vtbl;
struct Unk_80053D9C_Obj {
    Unk_80053D9C_Vtbl *unk0;
};
typedef struct Unk_80053D9C {
    u8 pad_00[0x20];
    s32 unk20;
    u8 pad_24[0x3C - 0x24];
    Unk_80053D9C_Obj *unk3C;
} Unk_80053D9C;
typedef struct Unk_80054208 Unk_80054208;
typedef struct Unk_80054208_Vtbl {
    u8 pad_00[0x30];
    void (*unk30)(Unk_80054208 *, s32);
    u8 pad_34[0xD4 - 0x34];
    void (*unkD4)(Unk_80054208 *);
} Unk_80054208_Vtbl;
struct Unk_80054208 {
    Unk_80054208_Vtbl *unk0;
    u8 pad_04[0x84 - 0x04];
    s32 unk84;
};
typedef struct Unk_8005426C Unk_8005426C;
typedef struct Unk_8005426C_Vtbl {
    u8 pad_00[0x30];
    void (*unk30)(Unk_8005426C *, s32);
    u8 pad_34[0xD4 - 0x34];
    void (*unkD4)(Unk_8005426C *);
} Unk_8005426C_Vtbl;
struct Unk_8005426C {
    Unk_8005426C_Vtbl *unk0;
    u8 pad_04[0x84 - 0x04];
    s32 unk84;
};
extern u8 D_800872C4[];
extern s32 D_8008730C[];
typedef struct Unk_800545FC_Src {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
} Unk_800545FC_Src;
typedef struct Unk_800545FC {
    u8 pad_00[0xC];
    u8 *unkC;
    u8 pad_10[4];
    s32 unk14;
    u8 *unk18;
    s32 unk1C;
} Unk_800545FC;
extern void func_8003B624(s32 *arg0, s32 arg1, s32 *arg2);
extern s32 D_80087444[];
extern s32 D_80087450[];
extern s32 D_8008745C[];
extern s32 D_80087468[];
s32 D_8008AC6C;
typedef struct Unk_80057320 { u8 pad_00[0xDC]; void (*unkDC)(void); void (*unkE0)(void); } Unk_80057320;
typedef struct Unk_8005227C_Vt { u8 pad_00[0x54]; void (*f54)(void *, s32); } Unk_8005227C_Vt;
typedef struct Unk_8005227C {
    Unk_8005227C_Vt *vt;
    u8 pad_04[0x2C - 0x4];
    s32 u2C;
    s32 u30;
} Unk_8005227C;
typedef struct Unk_80052498_Vt {
    u8 pad_00[0x94];
    void (*f94)(void *, s32, s32, s32, s32);
} Unk_80052498_Vt;
typedef struct Unk_80052498 {
    Unk_80052498_Vt *vt;
    u8 pad_04[0x20 - 0x4];
    s32 u20;
    s32 u24;
    s32 u28;
    u8 pad_2C[0x50 - 0x2C];
    s32 u50;
} Unk_80052498;
typedef struct Unk_800533F0 Unk_800533F0;
typedef struct Unk_800533F0_Vt {
    u8 pad_00[0x8C];
    void (*f8C)(Unk_800533F0 *);
    u8 pad_90[0xD0 - 0x90];
    void (*fD0)(Unk_800533F0 *);
} Unk_800533F0_Vt;
struct Unk_800533F0 {
    Unk_800533F0_Vt *vt;
    u8 pad_04[0x1C - 0x4];
    s32 u1C;
    u8 pad_20[0x68 - 0x20];
    s32 u68;
    u8 pad_6C[0x80 - 0x6C];
    s32 u80;
};
typedef struct Unk_80052110_Vt {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
} Unk_80052110_Vt;
typedef struct Unk_80052110 {
    Unk_80052110_Vt *unk0;
    u8 pad_04[0x2C - 0x04];
    s32 unk2C;
    u8 pad_30[0x3C - 0x30];
    s32 unk3C;
} Unk_80052110;
extern void func_8005C76C(void);
extern void func_80054D30(void);
typedef struct Unk_80053134_Vt {
    u8 pad_00[0x48];
    void (*unk48)(void *);
    u8 pad_4C[0x84 - 0x4C];
    void (*unk84)(void);
} Unk_80053134_Vt;
typedef struct Unk_80053134_Obj {
    Unk_80053134_Vt *unk0;
} Unk_80053134_Obj;
typedef struct Unk_80053134 {
    Unk_80053134_Vt *unk0;
    u8 pad_04[0x54 - 0x04];
    Unk_80053134_Obj *unk54;
} Unk_80053134;
typedef struct Unk_800520A0_Vt {
    u8 pad_00[0x4];
    void *(*unk4)(void *);
    u8 pad_08[0x90 - 0x08];
    void (*unk90)(void *);
} Unk_800520A0_Vt;
typedef struct Unk_800520A0 {
    Unk_800520A0_Vt *vt;
    u8 pad_04[0x50 - 0x04];
    void *unk50;
} Unk_800520A0;
s32 D_8008AB4C;
s32 D_8008AC70;
s32 D_8008AC74;
s32 D_8008AC78;
extern s32 D_8008ACA0;
s32 func_80054558(void);
typedef struct Unk_80055F74 {
    u8 pad_00[0x4];
    s32 unk4;
    u8 pad_08[0x10 - 0x8];
    s32 unk10;
    u8 pad_14[0x1C - 0x14];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
} Unk_80055F74;

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116A4);

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116E4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80051F24);

void func_800520A0(Unk_800520A0 *arg0) {
    Unk_800520A0 *temp;

    if (arg0->unk50 != NULL) {
        arg0->vt->unk90(arg0);
        temp = arg0->unk50;
        arg0->unk50 = temp->vt->unk4(temp);
    }
}

void func_80052110(Unk_80052110 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0->unk10(arg0, arg1);
    arg0->unk0->unk10(arg0, arg2);
    arg0->unk3C = arg3;
    arg0->unk2C = 0;
}

void func_8005217C(Unk_8005217C *arg0) {
    arg0->vt->unk14(arg0, arg0->u34);
    arg0->vt->unk14(arg0, arg0->u38);
    arg0->u3C = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800521D4);

void func_8005227C(Unk_8005227C *arg0) {
    s32 temp_v1;
    s32 temp_v1_2;

    temp_v1 = arg0->u2C;
    if (temp_v1 >= 4) {
        return;
    }
    if (temp_v1 < 2) {
        return;
    }
    temp_v1_2 = arg0->u30;
    arg0->u30 = temp_v1_2 + 1;
    if (temp_v1_2 != 0) {
        arg0->vt->f54(arg0, 4);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800522DC);

void func_800523F0(Unk_800523F0 *arg0, s32 arg1) {
    Unk_800523F0_Obj *temp_a0 = arg0->u3C;
    if (temp_a0 != NULL) {
        temp_a0->vt->f80(temp_a0, arg1, 0x60, 0x60);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052430);

void func_80052498(Unk_80052498 *arg0) {
    s32 temp;

    if (arg0->u50 != 0) {
        temp = arg0->u24 - 1;
        if (temp >= 0) {
            arg0->u24 = temp;
            arg0->vt->f94(arg0, arg0->u20, temp, arg0->u28, 1);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800524F8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052598);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052644);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005278C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005281C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005292C);

void func_800529FC(Unk_800529FC *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp;
    Unk_800529FC_Obj *obj;

    arg0->u20 = arg1;
    arg0->u24 = arg2;
    arg0->u28 = arg3;
    if (arg4 != 0) {
        temp = arg3 - arg1;
        obj = arg0->u40[temp];
        obj->vt->fB8(obj, D_8008AB10, arg2, temp);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052A58);

s32 func_80052B54(u8 *arg0) {
    return *(s32 *)(arg0 + 0x28);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052B60);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052B70);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052C10);

void func_80052CD8(s32 arg0) {
    func_8004A4B8(arg0)->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052D10);

void func_80052DE0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052DE8);

void func_80052E7C(Unk_80052E7C *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 >= 0) {
        func_80049060(arg0->u38);
    } else {
        func_80049098(arg0->u38, arg2, arg3);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052EBC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052F10);

void func_80053134(Unk_80053134 *arg0) {
    Unk_80053134_Obj *temp_a0;

    arg0->unk0->unk84();
    func_8005C76C();
    func_80054D30();
    temp_a0 = arg0->unk54;
    temp_a0->unk0->unk48(temp_a0);
}

void func_800531A0(Unk_800531A0 *arg0, s32 arg1, s32 arg2) {
    if (arg2 == 2) {
        func_800531CC(arg0, arg0->u58);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800531CC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053358);

void func_800533F0(Unk_800533F0 *arg0) {
    if (arg0->u68 != 0) {
        arg0->u1C = arg0->u1C + 1;
        if (arg0->u80 != 0) {
            arg0->vt->fD0(arg0);
        } else {
            arg0->vt->f8C(arg0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053458);

void func_800534C0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800534C8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800536B0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053764);

void func_8005393C(Unk_8005393C *arg0) {
    Unk_8005393C_Obj *temp = arg0->unk14;
    func_800558F0(temp->unk0->unk10C(temp, 0, 0), 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053984);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053ACC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053BE8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053C94);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053D18);

void func_80053D9C(Unk_80053D9C *arg0) {
    arg0->unk20 = 8;
    func_80053EB4(arg0, 0, 0, 6, 1);
    arg0->unk3C->unk0->unkF4(arg0->unk3C, 1);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053E00);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053E84);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053EB4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053F84);

void func_800540E8(Unk_800540E8 **arg0, s32 arg1, s32 arg2) {
    if (arg2 == 7) {
        (*arg0)->unkB8();
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054120);

void func_800541CC(void) {
}

void func_800541D4(Unk_800541D4 *arg0) {
    if (arg0->u80 != 0 && arg0->u20 == 0) {
        arg0->u84 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054200);

void func_80054208(Unk_80054208 *arg0) {
    if (arg0->unk84 != 0) {
        arg0->unk0->unkD4(arg0);
        arg0->unk0->unk30(arg0, 0xD);
    }
}

void func_8005426C(Unk_8005426C *arg0) {
    if (arg0->unk84 != 0) {
        arg0->unk0->unkD4(arg0);
        arg0->unk0->unk30(arg0, 0xC);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800542D0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800543FC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800544D4);

s32 func_800544E4(s32 arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    s32 *var_v1;
    s32 var_t0;

    if (D_8008AB4C == 0) {
        var_t0 = 1;
        var_v1 = &D_8008ACA0;
        D_8008AB4C = arg0;
        D_8008AC6C = arg1;
        D_8008AC7C = arg2;
        D_8008AC80 = -1;
        D_8008AC74 = arg3;
        D_8008AC78 = arg4;
        D_8008AC70 = 0;
        do {
            *var_v1 = 0;
            var_t0 -= 1;
            var_v1 -= 1;
        } while (var_t0 >= 0);
        return func_80054558();
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054558);

void func_800545FC(Unk_800545FC *arg0, Unk_800545FC_Src *arg1) {
    arg0->unkC = D_800872C4 + arg1->unk3 * 3;
    arg0->unk18 = D_800872C4 + arg1->unk2 * 3;
    arg0->unk1C = D_8008730C[arg1->unk1];
    arg0->unk14 = arg1->unk0;
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054660);

void func_80054714(void) {
    if (D_8008AB54 != 0) {
        D_8008AC94->vt->unk4(D_8008AC94);
        D_8008AB54 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054758);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054850);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800549A8);

void func_80054B1C(u8 *arg0, u8 *arg1, s32 arg2) {
    arg0[0] = arg1[0] - arg2;
    arg0[1] = arg1[1] - arg2;
    arg0[2] = arg1[2] + arg2;
}

void func_80054B50(void) {
    if (D_8008AB50 != 0) {
        func_800183DC(D_8008E10C, 0x12);
        D_8008AB50 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054B84);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054C74);

void func_80054CFC(void) {
    if (D_8008AC80 >= 0) {
        func_800183DC(D_8008E0C8, D_8008AC88);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054D30);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054DA4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054F30);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054FD8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005511C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055258);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055410);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005556C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055620);

s32 func_800557DC(Unk_800557DC *arg0) {
    func_8002CC84((void *)*D_8008AC7C, &arg0->u14);
    arg0->u0->u6 = -arg0->u0->u6;
    return 0;
}

s32 func_8005582C(s32 arg0) {
    if (func_80055874(arg0) != 0) {
        func_8002CD08(*D_8008AC7C, arg0 + 0x14);
        return 1;
    }
    return 0;
}

s32 func_80055874(A *arg0, B *arg1) { s32 dx,dz,d; if (arg1 != NULL) {
    dx = arg0->u4 - arg1->u0;
    if (dx < 0) dx = ~dx + 1;
    dz = arg0->uC - arg1->u8;
    d = dx + (dz < 0 ? ~dz + 1 : dz);
    arg0->u10 = d;
    if (d < D_80087474[-arg0->u0->u6]) return 1; } return 0; }

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800558F0);

void func_80055A24(void) {
    if (D_8008AC6C == 2) {
        func_8003B624(D_80087444, 1, D_80087450);
    } else if (D_8008AC6C >= 3 && D_8008AC6C < 6) {
        func_8003B624(D_8008745C, 1, D_80087468);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055A88);

void func_80055B10(void *arg0, Unk_80056238 *arg1) {
    arg1->u10 = func_8005627C(arg0);
    if (arg1->u4 == 0) {
        arg1->u1C = 0x18;
        arg1->u20 = -2;
        return;
    }
    if (arg1->u4 >= 0x401) {
        arg1->u4 = -1;
    }
}

void func_80055B6C(void *arg0, Unk_80056238 *arg1) {
    s32 temp_v1;

    arg1->u10 = func_8005627C(arg0);
    temp_v1 = arg1->u4;
    if (temp_v1 == 0) {
        arg1->u1C = 0xC;
        arg1->u20 = 2;
        return;
    }
    if (temp_v1 >= 5) {
        arg1->u4 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055BC8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055CA8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055DB4);

void func_80055E94(void *arg0, Unk_80056238 *arg1) {
    s32 temp_v1;

    arg1->u10 = func_8005627C(arg0);
    temp_v1 = arg1->u4;
    if (temp_v1 == 0) {
        arg1->u1C = 7;
        arg1->u20 = 2;
        return;
    }
    if (temp_v1 >= 0x1B) {
        arg1->u4 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055EF0);

void func_80055F74(void *arg0, Unk_80055F74 *arg1) {
    arg1->unk10 = func_8005627C(arg0);
    if (arg1->unk4 % 20 == 0) {
        arg1->unk1C = 9;
        arg1->unk20 = 0;
        arg1->unk24 = 0x40;
        arg1->unk28 = 0x40;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055FE8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056054);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800560E4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056194);

void func_80056238(void *arg0, Unk_80056238 *arg1) {
    arg1->u10 = func_8005627C(arg0);
    if (arg1->u4 == 0) {
        arg1->u1C = 0x18;
        arg1->u20 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005627C);

s32 func_8005630C(void) {
    return (D_8008AC80 & 1) ^ 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056320);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800563C0);

void func_80056464(s32 arg0) {
    func_80056718();
    func_80057C84()->unkC(arg0);
}

void func_800564A4(Unk_80059394 *arg0, Unk_800564A4 *arg1) {
    *(Unk_800564A4 *)((u8 *)arg0 + 0x58) = *arg1;
    arg0->u24 = 0;
}

void func_800564F4(Unk_80059394 *arg0) {
    arg0->u24++;
    func_80056640();
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056520);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056640);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056718);

void func_80056794(Unk_80056794 *arg0, Unk_80056794 *arg1, Unk_80056794 *arg2) {
    arg0->u0 = arg1->u0 + arg2->u0;
    arg0->u4 = arg1->u4 + arg2->u4;
    arg0->u8 = arg1->u8 + arg2->u8;
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800567D4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056858);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800569A8);

void func_80056B8C(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x6C) != 0) {
        func_800183DC(arg0 + 0x7C, 2);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056BBC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056D18);

void func_80056DF0(void) {
}

void func_80056DF8(u8 *arg0) {
    func_800183DC(arg0 + 0x84, 5);
}

void func_80056E1C(u8 *arg0) {
    func_80056D18(arg0, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056E44);

void func_80056F28(u8 *arg0) {
    func_800183DC(arg0 + 0x84, 5);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056F4C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056F5C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056FE4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057044);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800570B4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057130);

void func_800571A8(Unk_800571A8 *arg0) {
    arg0->unk4C = 0;
    arg0->unk50 = 0;
    func_8001E57C()->unk18(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800571E8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800571F8);

void func_80057320(Unk_80057320 **arg0, u8 **arg1) {
    u8 c = **arg1;

    if (c == 0x34) {
        (*arg0)->unkDC();
    } else if (c == 0x24) {
        (*arg0)->unkE0();
    }
}

void func_80057384(void *arg0, s32 *arg1) {
    func_800573CC(arg0, 1, arg1);
}

void func_800573A8(void *arg0, s32 *arg1) {
    func_800573CC(arg0, 0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800573CC);

void func_80057444(Unk_80057444 **arg0, void *arg1) {
    s32 sp10[3];

    func_8001E58C(arg0, sp10, arg1);
    (*arg0)->unkBC(arg0, sp10);
}

void func_8005748C(void *arg0, s32 arg1, s32 arg2) {
    func_80057534(arg0, D_8008ABA8, arg1, arg2, 6);
}

void func_800574C4(void *arg0, s32 arg1, s32 arg2) {
    func_80057534(arg0, D_8008ABA4, arg1, arg2, 7);
}

void func_800574FC(void *arg0, s32 arg1, s32 arg2) {
    func_80057534(arg0, D_8008ABA4 + 1, arg1, arg2, 8);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057534);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800575B0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800575E0);

void func_80057610(void) {
}

void func_80057618(Unk_80057618 *arg0, void (*arg1)(void *, s32, s32), s32 arg2, s32 arg3) {
    arg0->u28 = 0;
    arg1(arg0, arg2, arg3);
    if (arg0->u28 == 0) {
        func_80057668(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057668);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057784);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057954);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057A18);

s32 func_80057B54(s32 arg0) {
    if (arg0 != 0 && func_8001E7BC() != 0) {
        return arg0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057B90);

void func_80057C14(s32 arg0, s32 arg1, s32 arg2) {
    ((Unk_80057C14_Vt *)func_8001E57C())->unk9C(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C6C);

void func_80057C74(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C7C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C84);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C94);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057D10);

void func_80057DBC(Unk_80057DBC *arg0, s32 arg1) {
    arg0->unkA0 = arg1;
    arg0->unk74 = D_80087AA4[arg1 * 2];
    arg0->unk76 = D_80087AA6[arg1 * 2];
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057DF4);

void func_80057F38(void) {
}

void func_80057F40(void) {
}

void func_80057F48(void) {
}

void func_80057F50(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057F58);

void *func_80057F68(s32 arg0) {
    void *temp;

    temp = func_80017B34(0x244);
    if (temp != 0) {
        func_80058764()->unk8(temp, arg0);
        return temp;
    }
    return 0;
}

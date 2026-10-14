#include "common.h"

typedef struct VTable { s32 unk0, unk4, unk8; void (*fnC)(); } VTable;
extern void func_80017CFC(s32);
extern VTable *func_80018390(void);
typedef struct { u8 pad[0x20]; s32 u20; u8 pad2[0x24]; s32 u48; } Unk_800517EC;
s32 D_8008AC80;
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
typedef struct Unk_80089EA4 {
    u8 pad[0x8];
    s8 unk8;
    u8 pad9[0x7];
} Unk_80089EA4;
extern Unk_80089EA4 D_80089EA4[];
typedef struct Unk_8005D944 { u8 pad[0x98]; s32 unk98; } Unk_8005D944;
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
typedef struct Unk_80063CAC {
    u8 pad[0x10];
    s32 unk10;
    u8 pad2[0x08];
    s32 unk1C;
    u8 pad3[0x10];
    s32 unk30;
    u8 pad4[0x10];
    s32 unk44;
} Unk_80063CAC;
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
typedef struct Unk_8005ED10_0 {
    u8 pad[0xFC];
    s32 uFC;
} Unk_8005ED10_0;
typedef struct Unk_8005ED10 {
    u8 pad0[0x10];
    s32 u10;
    u8 pad1[0x1C - 0x14];
    s32 u1C;
} Unk_8005ED10;
extern void func_80060D80(void);
void func_800573CC(void *arg0, s32 arg1, s32 *arg2);
extern s8 D_80089EAC[];
typedef struct Unk_8005D9D0 { u8 pad[0x98]; s32 unk98; } Unk_8005D9D0;
extern void func_80056D18(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct { u8 pad[0x84]; s32 unk84; } Unk_80061C04_0;
typedef struct { u8 p0[0x10]; s32 u10; u8 p1[0x08]; s32 u1C; s32 u20; } Unk_80061C04;
typedef struct Unk_80063C84 {
    u8 p0[0x10];
    s32 u10;
    u8 p1[0x8];
    s32 u1C;
    s32 u20;
    u8 p2[0xC];
    s32 u30;
    s32 u34;
    u8 p3[0xC];
    s32 u44;
    s32 u48;
} Unk_80063C84;
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
typedef struct { s32 u0; s32 u4; u8 pad[0x14]; s32 u1C; s32 u20; u8 pad2[0xC]; s32 u30; s32 u34; } S;
typedef struct Unk_80065BFC {
    u8 pad[0x5C];
    s32 u5C;
} Unk_80065BFC;
s32 func_80065C5C(void);
typedef struct Unk_80065C2C {
    u8 pad[0x5C];
    s32 u5C;
} Unk_80065C2C;
extern void func_80065CEC(void);
extern s32 func_80065E1C(Unk_80059394 *arg0);
extern void func_80065F2C(Unk_80059394 *arg0);
s32 D_8008AB50;
extern u8 D_8008E10C[];
s32 D_8008AC88;
extern u8 D_8008E0C8[];
typedef struct Unk_8005A134 {
    u8 pad[0x58];
    void *u58;
    u8 pad2[0xC4 - 0x5C];
    s32 uC4;
    s32 uC8;
    u8 uCC[1];
} Unk_8005A134;
void func_8002CC84(void *, void *);
typedef struct Unk_8005EF20_vt { u8 pad[0x48]; void (*fn48)(void *, s32, void *); } Unk_8005EF20_vt;
typedef struct Unk_8005EF20 { Unk_8005EF20_vt *vt; } Unk_8005EF20;
extern s32 D_80089DD8;
extern s32 D_80089E38;
typedef struct Unk_8005F6D4_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_8005F6D4_Vtbl;
typedef struct Unk_8005F6D4 {
    Unk_8005F6D4_Vtbl *vtbl;
} Unk_8005F6D4;
typedef struct Unk_8006519CVtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_8006519CVtbl;
typedef struct Unk_8006519C {
    Unk_8006519CVtbl *vtbl;
} Unk_8006519C;
typedef struct Unk_800651D0_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_800651D0_Vtbl;
typedef struct Unk_800651D0 {
    Unk_800651D0_Vtbl *vtbl;
} Unk_800651D0;
extern s32 D_80089DCC;
typedef struct Unk_80065204_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_80065204_Vtbl;
typedef struct Unk_80065204 {
    Unk_80065204_Vtbl *vtbl;
} Unk_80065204;

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050BA8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050C14);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050CD8);

void func_80050CE8(u8 *arg0) {
    func_80017CFC(*(s32 *)(arg0 + 0x28));
    func_80018390()->fnC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050D30);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050DB4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050E34);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050E78);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050F28);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050F98);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051174);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051200);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051270);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800512C8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051370);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800513D0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005161C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005165C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800516C0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051720);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051784);

void func_800517EC(Unk_800517EC *arg0) {
    if (arg0->u48 != 0) {
        arg0->u20 ^= 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051814);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051858);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800518F4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051998);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051A4C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051A5C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051AC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051C74);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051C84);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051D1C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051DA0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051E20);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051E64);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051F14);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051F24);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800520A0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052110);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005217C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800521D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005227C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800522DC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800523F0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052430);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052498);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800524F8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052598);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052644);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005278C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005281C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005292C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800529FC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052A58);

s32 func_80052B54(u8 *arg0) {
    return *(s32 *)(arg0 + 0x28);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052B60);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052B70);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052C10);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052CD8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052D10);

void func_80052DE0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052DE8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052E7C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052EBC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80052F10);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053134);

void func_800531A0(Unk_800531A0 *arg0, s32 arg1, s32 arg2) {
    if (arg2 == 2) {
        func_800531CC(arg0, arg0->u58);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800531CC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053358);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800533F0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053458);

void func_800534C0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800534C8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800536B0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053764);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005393C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053984);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053ACC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053BE8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053C94);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053D18);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053D9C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053E00);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053E84);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053EB4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80053F84);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800540E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054120);

void func_800541CC(void) {
}

void func_800541D4(Unk_800541D4 *arg0) {
    if (arg0->u80 != 0 && arg0->u20 == 0) {
        arg0->u84 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054200);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054208);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005426C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800542D0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800543FC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800544D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800544E4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054558);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800545FC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054660);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054714);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054758);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054850);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800549A8);

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

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054B84);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054C74);

void func_80054CFC(void) {
    if (D_8008AC80 >= 0) {
        func_800183DC(D_8008E0C8, D_8008AC88);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054D30);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054DA4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054F30);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80054FD8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005511C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055258);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055410);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005556C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055620);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800557DC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005582C);

s32 func_80055874(A *arg0, B *arg1) { s32 dx,dz,d; if (arg1 != NULL) {
    dx = arg0->u4 - arg1->u0;
    if (dx < 0) dx = ~dx + 1;
    dz = arg0->uC - arg1->u8;
    d = dx + (dz < 0 ? ~dz + 1 : dz);
    arg0->u10 = d;
    if (d < D_80087474[-arg0->u0->u6]) return 1; } return 0; }

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800558F0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055A24);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055A88);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055B10);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055B6C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055BC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055CA8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055DB4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055E94);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055EF0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055F74);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80055FE8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056054);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800560E4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056194);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056238);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005627C);

s32 func_8005630C(void) {
    return (D_8008AC80 & 1) ^ 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056320);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800563C0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056464);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800564A4);

void func_800564F4(Unk_80059394 *arg0) {
    arg0->u24++;
    func_80056640();
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056520);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056640);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056718);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056794);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800567D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056858);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800569A8);

void func_80056B8C(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x6C) != 0) {
        func_800183DC(arg0 + 0x7C, 2);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056BBC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056D18);

void func_80056DF0(void) {
}

void func_80056DF8(u8 *arg0) {
    func_800183DC(arg0 + 0x84, 5);
}

void func_80056E1C(u8 *arg0) {
    func_80056D18(arg0, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056E44);

void func_80056F28(u8 *arg0) {
    func_800183DC(arg0 + 0x84, 5);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056F4C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056F5C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80056FE4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057044);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800570B4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057130);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800571A8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800571E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800571F8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057320);

void func_80057384(void *arg0, s32 *arg1) {
    func_800573CC(arg0, 1, arg1);
}

void func_800573A8(void *arg0, s32 *arg1) {
    func_800573CC(arg0, 0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800573CC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057444);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005748C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800574C4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800574FC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057534);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800575B0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800575E0);

void func_80057610(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057618);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057668);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057784);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057954);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057A18);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057B54);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057B90);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057C14);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057C6C);

void func_80057C74(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057C7C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057C84);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057C94);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057D10);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057DBC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057DF4);

void func_80057F38(void) {
}

void func_80057F40(void) {
}

void func_80057F48(void) {
}

void func_80057F50(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057F58);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057F68);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80057FC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058078);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800580E0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800581C4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058228);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058308);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058390);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058404);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800585B4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058694);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058764);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058774);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800587F0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800588EC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058968);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058A94);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058B08);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058C58);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058D94);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058E8C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058F18);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80058FAC);

void func_800590E0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800590E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059148);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800591B4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059310);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005931C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059328);

u32 func_80059360(Unk_80059360 *arg0) {
    return arg0->unk24 / 15;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005937C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059384);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005938C);

void func_80059394(Unk_80059394 *arg0) {
    if (arg0->u70 == 0) {
        arg0->u74 = 0;
        arg0->u124 = arg0->u24 % arg0->u120 == 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800593D8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005942C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005950C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059590);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059598);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800595A0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800595A8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059610);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005966C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800596E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800597C0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059814);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800598E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059A1C);

void func_80059A48(void) {
}

void func_80059A50(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059A58);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059AEC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059B50);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059BD4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059BE0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059D1C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059E3C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80059E98);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A050);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A0B0);

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

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A1A4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A1B0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A1EC);

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

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A258);

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

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A304);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A33C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A344);

s32 func_8005A350(s32 arg0, s32 *arg1) {
    if (arg1 != NULL) {
        *arg1 = 0x700;
    }
    return arg0 + 0x178;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A368);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A41C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A4E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A508);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A580);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A5D8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A63C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A700);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A7A0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A82C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A928);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005A9CC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005AB2C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005AC24);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005AD68);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005AE40);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005AF64);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005AFD0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005AFDC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B03C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B1F4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B2F4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B3A4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B3F0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B420);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B4E0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B518);

void func_8005B5A4(s32 arg0, Unk_8005B5A4 *arg1) {
    arg1->unk0 = 0;
    arg1->unk8 = 0;
    arg1->unk4 = 0;
    arg1->unkC = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B5B8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B5F0);

s32 func_8005B66C(s32 arg0, s32 arg1, s32 arg2) {
    s32 r = arg1 / arg2 + arg0 / 3;
    if (r > 9) {
        r = -9;
    } else if (r < -9) {
        r = 9;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B6E0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B74C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B81C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B8FC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B904);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005B990);

s32 func_8005BA20(Unk_8005BA20 *arg0, s32 arg1) {
    s32 temp;

    if (arg1 < 0) {
        return arg0->u924;
    }
    temp = arg0->u924;
    arg0->u924 = arg1;
    return temp;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BA40);

void func_8005BA50(u8 *arg0, s32 *arg1) {
    s32 i;
    for (i = 29; i >= 0; i--) {
        arg0[i] = 0;
    }
    D_8008ACB4 = arg0;
    *arg1 = 0;
    D_8008ACB8 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BA7C);

s16 func_8005BB14(s32 arg0) {
    return D_80087F14[arg0];
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BB30);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BCB4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BCF8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BD3C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BE28);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BE90);

s32 *func_8005BF48(void) {
    s32 *r = NULL;
    if (D_8008ACC4 != 12) {
        r = D_8008ABF0;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BF68);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BF74);

s32 func_8005BFC4(void) {
    return D_8008ACBC == 0 ? 10 : 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005BFDC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C02C);

s32 func_8005C118(void) {
    return D_80088BA4[D_8008ACC4][D_8008ACC8].u5;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C150);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C28C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C438);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C508);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C5E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C650);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C6D8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C714);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C76C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C7D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C8AC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C930);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C9A4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005C9DC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005CAB4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005CBC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005CD58);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005CDA8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005CDF8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005CF34);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005CFDC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D068);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D108);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D1EC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D278);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D314);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D418);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D480);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D560);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D658);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D6D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D714);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D7FC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D864);

Unk_80089EA4 *func_8005D944(Unk_8005D944 *arg0) {
    return &D_80089EA4[arg0->unk98];
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D95C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D994);

s32 func_8005D9D0(Unk_8005D9D0 *arg0) {
    return D_80089EAC[arg0->unk98 * 16] - 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005D9F4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DA3C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DAAC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DAFC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DB8C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DBF0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DD18);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DE18);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DEE0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005DF9C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E02C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E0B0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E150);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E160);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E3C4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E480);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E4D0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E694);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E6F0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E7A8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005E7F8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005EA94);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005EBB4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005EC98);

void func_8005ED10(Unk_8005ED10_0 *arg0, Unk_8005ED10 *arg1) {
    if (arg0->uFC == 0) {
        arg1->u10 = 0;
        arg1->u1C = 0xF;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005ED30);

void func_8005EF20(Unk_8005EF20 *arg0) {
    arg0->vt->fn48(arg0, 1, &D_80089DD8);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005EF54);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005EFF4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F0D8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F1A8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F1D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F368);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F454);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F544);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F608);

void func_8005F6D4(Unk_8005F6D4 *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089E38);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F708);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F800);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005F970);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FA64);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FA94);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FB6C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FC58);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FDFC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FEC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FEF8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005FF7C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060148);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800602AC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800603C4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800604DC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800605D0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060710);

void func_800607F8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060800);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8006090C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060A4C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060B34);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060CF0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060D80);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80060F38);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061070);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061158);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061198);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061400);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061778);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061A90);

void func_80061C04(Unk_80061C04_0 *arg0, Unk_80061C04 *arg1) {
    if (arg0->unk84 == 0x1E) {
        arg1->u1C = 0x12;
        arg1->u10 = 0;
        arg1->u20 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061C2C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061E60);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80061F30);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8006204C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800620C4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800621A8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800623E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800624BC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80062570);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80062660);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80062730);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800628D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80062970);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80062A40);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80062C58);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80062FAC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063094);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063144);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800634A8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800636E4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063784);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063874);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063BC0);

void func_80063C84(Unk_80063C84 *arg0) {
    arg0->u10 = 0;
    arg0->u1C = 7;
    arg0->u20 = -2;
    arg0->u30 = 7;
    arg0->u34 = -2;
    arg0->u44 = 7;
    arg0->u48 = -2;
}

void func_80063CAC(Unk_80063CAC *arg0) {
    arg0->unk1C = 0x12;
    arg0->unk10 = 0;
    arg0->unk30 = 3;
    arg0->unk44 = 3;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063CC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063D40);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063DC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063E68);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80063ED4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064078);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800641C0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064294);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064450);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800644E8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064618);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800646D8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064928);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064AA4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064B14);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064B80);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064CA4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064CEC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064D48);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064E34);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80064FBC);

void func_800650D4(void) {
    func_80060D80();
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800650F4);

void func_8006519C(Unk_8006519C *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089E38);
}

void func_800651D0(Unk_800651D0 *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089E38);
}

void func_80065204(Unk_80065204 *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089DCC);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065238);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8006536C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800654A0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065514);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800655D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065650);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8006573C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065790);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065830);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065918);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800659D0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065A5C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065AE0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065B80);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065BF4);

s32 func_80065BFC(Unk_80065BFC *arg0) {
    if (arg0->u5C == 0) {
        return func_80065C5C();
    }
    return 0;
}

void func_80065C2C(Unk_80065C2C *arg0) {
    if (arg0->u5C != 0) {
        func_80065CEC();
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065C5C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065CEC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065D64);

s32 func_80065DBC(Unk_80059394 *arg0) {
    if (arg0->u70 == 0) {
        return func_80065E1C(arg0);
    }
    return 0;
}

void func_80065DEC(Unk_80059394 *arg0) {
    if (arg0->u70 != 0) {
        func_80065F2C(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065E1C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065F2C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80065FD8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800660BC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8006613C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80066148);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80066150);

void func_800661C4(void) {
}

void func_800661CC(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800661D4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80066214);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800662A8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800662B4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800662BC);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80066340);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80066748);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800667B0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80066818);

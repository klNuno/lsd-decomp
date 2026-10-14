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

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116A4);

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116E4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80051F24);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800520A0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052110);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005217C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800521D4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005227C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800522DC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800523F0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052430);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052498);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800524F8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052598);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052644);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005278C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005281C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005292C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800529FC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052A58);

s32 func_80052B54(u8 *arg0) {
    return *(s32 *)(arg0 + 0x28);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052B60);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052B70);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052C10);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052CD8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052D10);

void func_80052DE0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052DE8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052E7C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052EBC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052F10);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053134);

void func_800531A0(Unk_800531A0 *arg0, s32 arg1, s32 arg2) {
    if (arg2 == 2) {
        func_800531CC(arg0, arg0->u58);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800531CC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053358);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800533F0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053458);

void func_800534C0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800534C8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800536B0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053764);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005393C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053984);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053ACC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053BE8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053C94);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053D18);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053D9C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053E00);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053E84);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053EB4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80053F84);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800540E8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054120);

void func_800541CC(void) {
}

void func_800541D4(Unk_800541D4 *arg0) {
    if (arg0->u80 != 0 && arg0->u20 == 0) {
        arg0->u84 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054200);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054208);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005426C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800542D0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800543FC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800544D4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800544E4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054558);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800545FC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054660);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054714);

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

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800557DC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005582C);

s32 func_80055874(A *arg0, B *arg1) { s32 dx,dz,d; if (arg1 != NULL) {
    dx = arg0->u4 - arg1->u0;
    if (dx < 0) dx = ~dx + 1;
    dz = arg0->uC - arg1->u8;
    d = dx + (dz < 0 ? ~dz + 1 : dz);
    arg0->u10 = d;
    if (d < D_80087474[-arg0->u0->u6]) return 1; } return 0; }

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800558F0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055A24);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055A88);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055B10);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055B6C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055BC8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055CA8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055DB4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055E94);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055EF0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055F74);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80055FE8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056054);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800560E4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056194);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056238);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005627C);

s32 func_8005630C(void) {
    return (D_8008AC80 & 1) ^ 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056320);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800563C0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056464);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800564A4);

void func_800564F4(Unk_80059394 *arg0) {
    arg0->u24++;
    func_80056640();
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056520);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056640);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056718);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80056794);

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

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800571A8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800571E8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800571F8);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057320);

void func_80057384(void *arg0, s32 *arg1) {
    func_800573CC(arg0, 1, arg1);
}

void func_800573A8(void *arg0, s32 *arg1) {
    func_800573CC(arg0, 0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800573CC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057444);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005748C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800574C4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800574FC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057534);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800575B0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800575E0);

void func_80057610(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057618);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057668);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057784);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057954);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057A18);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057B54);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057B90);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C14);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C6C);

void func_80057C74(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C7C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C84);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C94);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057D10);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057DBC);

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

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057F68);

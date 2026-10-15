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

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116A4);

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116E4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80051F24);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800520A0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80052110);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005217C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800521D4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005227C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800522DC);

void func_800523F0(Unk_800523F0 *arg0, s32 arg1) {
    Unk_800523F0_Obj *temp_a0 = arg0->u3C;
    if (temp_a0 != NULL) {
        temp_a0->vt->f80(temp_a0, arg1, 0x60, 0x60);
    }
}

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

void func_8005393C(Unk_8005393C *arg0) {
    Unk_8005393C_Obj *temp = arg0->unk14;
    func_800558F0(temp->unk0->unk10C(temp, 0, 0), 0, 0);
}

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

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054208);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_8005426C);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800542D0);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800543FC);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800544D4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800544E4);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80054558);

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_800545FC);

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

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057320);

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

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057C14);

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

INCLUDE_ASM("asm/nonmatchings/game/80051F24", func_80057F68);

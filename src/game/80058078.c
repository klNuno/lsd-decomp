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

INCLUDE_RODATA("asm/nonmatchings/game/80058078", D_80011778);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058078);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800580E0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800581C4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058228);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058308);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058390);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058404);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800585B4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058694);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058764);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058774);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800587F0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800588EC);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058968);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058A94);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058B08);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058C58);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058D94);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058E8C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058F18);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058FAC);

void func_800590E0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800590E8);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059148);

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

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800593D8);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005942C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005950C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059590);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059598);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800595A0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800595A8);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059610);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005966C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800596E8);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800597C0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059814);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800598E8);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059A1C);

void func_80059A48(void) {
}

void func_80059A50(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059A58);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059AEC);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059B50);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059BD4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059BE0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059D1C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059E3C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059E98);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A050);

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

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A258);

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

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A508);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A580);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A5D8);

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

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AF64);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AFD0);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AFDC);

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

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B6E0);

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

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BE28);

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

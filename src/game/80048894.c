#include "common.h"

extern u8 D_80081A04[];
extern s16 D_80086170[];
s32 D_8008A964;
s32 D_8008A968;
u8 *func_80048E2C(s32 arg0);
s32 *func_80048DF8(void);
extern void srand(u32 seed);
extern s32 rand(void);
void *func_80048D48(s32 *arg0);
s32 func_80017CFC(s32);
typedef struct Unk_80048C98 {
    u8 pad_00[0x2E];
    s16 unk2E;
    u8 pad_30[4];
    s32 unk34;
} Unk_80048C98;
u8 *func_8004903C(s32 arg0);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048894);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800488E4);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048960);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800489B4);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048A68);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048AAC);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048B78);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048BC0);

void func_80048C98(Unk_80048C98 *arg0) {
    s32 temp_a0;

    temp_a0 = arg0->unk34;
    arg0->unk2E = 0;
    if (temp_a0 != 0) {
        arg0->unk34 = func_80017CFC(temp_a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048CD8);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048CE0);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048CF0);

void func_80048CFC(s32 arg0) {
    if (arg0 != 0) {
        srand(arg0);
    }
    rand();
}

void func_80048D28(s32 arg0, s32 arg1) {
    if (arg0 >= 0) {
        D_8008A964 = arg0;
    }
    if (arg1 >= 0) {
        D_8008A968 = arg1;
    }
}

void *func_80048D48(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0x230;
    }
    return D_80081A04;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048D64);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048D74);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048DF8);

s32 func_80048E08(void) {
    return *func_80048DF8();
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048E2C);

u8 *func_80048E80(s32 arg0) {
    return func_80048E2C(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048EA0);

u8 *func_80048F60(s32 arg0) {
    return func_80048E2C(arg0) + 0x70;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048F84);

u8 *func_8004903C(s32 arg0) {
    return func_80048E2C(arg0) + 0xFC;
}

u8 *func_80049060(s32 arg0, s32 arg1) {
    return func_8004903C(arg0) + arg1 * 0x1C;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80049098);

INCLUDE_RODATA("asm/nonmatchings/game/80048894", D_80011384);

char *func_800490F4(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0x31;
    }
    return "ETC\\ASMK.STR";
}

s32 func_80049110(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0;
    }
    return (s32)func_80048D48(NULL) + 0x3D40;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_8004913C);

s32 func_800491CC(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 7;
    }
    return (s32)func_80048D48(NULL) + 0x3E04;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800491FC);

u8 *func_80049240(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 8;
    }
    return (u8 *)func_80048D48(NULL) + 0x3E20;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80049270);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800492D0);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80049334);

s16 func_800493C8(s32 arg0) {
    return D_80086170[arg0];
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800493E4);

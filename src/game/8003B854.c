#include "common.h"

struct Unk_8003E4A4 {
    u8 pad_00[0x1C];
    s32 unk1C;
};
typedef struct Unk_8003EA0C_Pair {
    s32 unk0;
    s32 unk4;
} Unk_8003EA0C_Pair;
struct Unk_8003EA0C {
    u8 pad_00[0x34];
    Unk_8003EA0C_Pair unk34;
};
struct Unk_8003BCF4 {
    u8 pad_00[0x40];
    s32 unk40;
};
typedef struct Unk_8003DFA0 {
    u8 pad_00[0x58];
    s32 unk58;
    s32 pad_5C;
    s32 *unk60;
} Unk_8003DFA0;
struct Unk_8003EA2C {
    u8 pad_00[0x44];
    s32 unk44;
    u8 pad_48[0x70 - 0x48];
    s32 unk70;
};
typedef struct Unk_8003EA48 {
    u8 pad[0x48];
    s32 unk48;
    u8 pad4C[0x70 - 0x4C];
    s32 unk70;
} Unk_8003EA48;
struct Unk_8003BA38 {
    u8 pad_00[0xC4];
    s32 unkC4;
    s32 unkC8;
    s32 unkCC;
    s32 unkD0;
    s32 unkD4;
};
struct Unk_8003C794 {
    u8 pad_00[0x40];
    s32 unk40;
};
extern void SetGeomScreen(s32);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003B854);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003B8E4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003B9DC);

void func_8003BA38(struct Unk_8003BA38 *arg0) {
    arg0->unkC8 = -1;
    arg0->unkC4 = 0;
    arg0->unkCC = 1;
    arg0->unkD0 = 0;
    arg0->unkD4 = 1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BA58);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BAB4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BB5C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BC14);

void func_8003BCF4(struct Unk_8003BCF4 *arg0, s32 arg1) {
    arg0->unk40 = arg1;
    if (arg1 >= 0) {
        arg0->unk40 = arg1 * 15;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BD10);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BD74);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BDAC);

void func_8003BDE4(void) {
}

void func_8003BDEC(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BDF4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE5C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE64);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE6C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE74);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE7C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE84);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE94);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BF10);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C008);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C11C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C1DC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C238);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C3D0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C48C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C51C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C63C);

void func_8003C794(struct Unk_8003C794 *arg0, s32 arg1) {
    arg0->unk40 = arg1;
    if (arg1 >= 0) {
        arg0->unk40 = arg1 * 20;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C7B4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C7F4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C858);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C8D0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C944);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C9B0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CA1C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CA94);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CAEC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CAF8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CB30);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CB68);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CBB8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CBC0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CC2C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CCDC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CD48);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CDE0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CE98);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D050);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D194);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D2CC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D3B0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D444);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D4DC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D5C0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D5CC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D6D4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D73C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D980);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DA10);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DAD4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DCAC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DDC8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DE30);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DE9C);

s32 func_8003DFA0(Unk_8003DFA0 *arg0) {
    return arg0->unk60[arg0->unk58];
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DFBC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DFCC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DFDC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E030);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E100);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E10C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E280);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E418);

void func_8003E4A4(struct Unk_8003E4A4 *arg0) {
    arg0->unk1C++;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E4B8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E538);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E578);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E5C8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E5D8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E628);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E6CC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E770);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E7F4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E874);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E8B8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E968);

void func_8003EA0C(struct Unk_8003EA0C *arg0, Unk_8003EA0C_Pair *arg1) {
    arg0->unk34 = *arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EA24);

void func_8003EA2C(struct Unk_8003EA2C *arg0, s32 arg1) {
    if (arg0->unk70 == 0) {
        arg0->unk44 = arg1;
    }
}

void func_8003EA48(Unk_8003EA48 *arg0, s32 arg1) {
    if (arg0->unk70 == 0) {
        arg0->unk48 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EA64);

void func_8003EA6C(void) {
}

void func_8003EA74(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EA7C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EA84);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EAA4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EAC4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EACC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EB84);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EBC4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EBF8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EC2C);

void func_8003ECC0(void) {
}

void func_8003ECC8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003ECD0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EDF4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EE40);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EE88);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EEC0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F04C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F1A8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F230);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F23C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F244);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F24C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F25C);

void func_8003F28C(s32 arg0) {
    SetGeomScreen(arg0);
}

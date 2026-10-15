#include "common.h"

typedef struct Unk_800408A8 {
    u8 pad[0x68];
    s32 unk68;
} Unk_800408A8;
void func_80040790(void *arg0, u8 *arg1, u8 *arg2, s32 arg3);
s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct Unk_800407F8Pair {
    s32 unk0;
    s32 unk4;
} Unk_800407F8Pair;
typedef struct Unk_800407F8 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x50 - 0x10];
    Unk_800407F8Pair unk50;
} Unk_800407F8;
typedef struct Unk_80040824 {
    u8 pad[0xC];
    s32 unkC;
    u8 pad2[0x60 - 0x10];
    u16 unk60;
    u16 unk62;
} Unk_80040824;
typedef struct Unk_800403F8 {
    u8 pad0[0x78];
    s32 unk78;
} Unk_800403F8;
extern u8 D_8006EA90[][3];
extern u8 D_8006EAA8[3];
typedef struct Unk_80040490 {
    u8 pad0[0x50];
    Unk_800407F8Pair unk50;
    u8 pad58[0x60 - 0x58];
    u16 unk60;
    u16 unk62;
    u8 pad64[0x88 - 0x64];
    u16 unk88;
    u8 pad8A[0x8C - 0x8A];
    u16 unk8C;
    u8 pad8E[0x90 - 0x8E];
    Unk_800407F8Pair unk90;
} Unk_80040490;
typedef struct Unk_80040EDC_obj Unk_80040EDC_obj;
typedef struct Unk_80040EDC_vt {
    u8 pad[0xC4];
    void (*unkC4)(Unk_80040EDC_obj *, u8, Unk_80040EDC_obj **);
} Unk_80040EDC_vt;
struct Unk_80040EDC_obj {
    Unk_80040EDC_vt *unk0;
};
typedef struct Unk_80040EDC {
    u8 pad[0xB4];
    Unk_80040EDC_obj **unkB4;
} Unk_80040EDC;
typedef struct Unk_80040854_Vtbl {
    u8 pad[0x4C];
    void (*unk4C)(void);
} Unk_80040854_Vtbl;
typedef struct Unk_80040854 {
    Unk_80040854_Vtbl *unk0;
    u8 pad4[0x44];
    s32 unk48;
    s32 unk4C;
} Unk_80040854;
typedef struct Unk_80040A30_obj {
    u8 pad[0xC];
    void (*unkC)(void *);
} Unk_80040A30_obj;
typedef struct Unk_80040A30 {
    u8 pad[0xA9];
    u8 unkA9;
    u8 padAA[0xB4 - 0xAA];
    Unk_80040EDC_obj **unkB4;
} Unk_80040A30;
void func_800183DC(void *, s32);
void *func_80017CFC(void *);
Unk_80040A30_obj *func_80041C3C(void);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8003FDB0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8003FE2C);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8003FED8);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8003FF44);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8004001C);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040024);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800400B0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040154);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800402F0);

u8 *func_800403F8(Unk_800403F8 *arg0) {
    s32 index = arg0->unk78;

    if (index == 0xF) {
        return D_8006EAA8;
    }
    return D_8006EA90[index];
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8004042C);

void func_80040490(Unk_80040490 *arg0) {
    arg0->unk50 = arg0->unk90;
    arg0->unk60 = arg0->unk88;
    arg0->unk62 = arg0->unk8C;
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800404B4);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800404C0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800404D0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8004054C);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800405D0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040664);

s32 func_800406E4(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x58), 0x1F, 1, arg1 == 0) == 0;
}

void func_80040714(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x58), 0x1E, 1, arg1 != 0);
}

void func_80040740(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x58), 0x1C, 2, arg1);
}

void func_8004076C(u8 *arg0, s32 arg1, u8 *arg2) {
    func_80040790(arg0, arg0 + 0x64, arg2, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040790);

void func_800407F8(Unk_800407F8 *arg0, Unk_800407F8Pair *arg1) {
    if (arg0->unkC != 0) {
        arg0->unk50 = *arg1;
    }
}

void func_80040824(Unk_80040824 *arg0, u16 *arg1) {
    if (arg0->unkC != 0) {
        arg0->unk60 = arg1[0];
        arg0->unk62 = arg1[2];
    }
}

void func_80040854(Unk_80040854 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0->unk4C();
    arg0->unk48 = 0;
    arg0->unk4C = arg3;
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800408A0);

void func_800408A8(Unk_800408A8 *arg0, s32 arg1) {
    arg0->unk68 = (1 << arg1) - 1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800408BC);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800408CC);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040948);

void func_80040A30(Unk_80040A30 *arg0) {
    func_800183DC(arg0->unkB4, arg0->unkA9);
    arg0->unkB4 = func_80017CFC(arg0->unkB4);
    func_80041C3C()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040A88);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040AE8);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040C00);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040CD0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040D74);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040E14);

void func_80040EDC(Unk_80040EDC *arg0, s32 arg1, s32 arg2) {
    Unk_80040EDC_obj **temp_a2 = &arg0->unkB4[arg2];
    Unk_80040EDC_obj *temp_a0 = *temp_a2;

    temp_a0->unk0->unkC4(temp_a0, arg1, temp_a2);
}

void func_80040F20(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040F28);

void func_80040FA0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040FA8);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040FB0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040FC0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80041020);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8004109C);

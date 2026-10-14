#include "common.h"

typedef struct { u8 pad[0xA8]; u8 unkA8; } Unk_80041C28;
struct Unk_800425D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
};
struct Unk_80042828 {
    u8 pad_00[0x44];
    s32 unk44[1];
};
struct Unk_80041E2C {
    s32 unk0;
    s32 unk4;
};
struct Unk_80041E2C_obj {
    u8 pad_00[0xC];
    s32 unkC;
    u8 pad_10[0x90];
    struct Unk_80041E2C unkA0;
};
s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
struct Unk_80041BAC;
struct Unk_80041BAC_vtbl {
    u8 pad_00[0xC4];
    void (*unkC4)(struct Unk_80041BAC *, u8);
};
struct Unk_80041BAC {
    struct Unk_80041BAC_vtbl *unk0;
};
typedef struct {
    u8 pad[0xC];
    s32 uC;
    u8 pad2[0x6C - 0x10];
    u16 u6C;
    u16 u6E;
    u8 pad3[0x7C - 0x70];
    u16 u7C;
    u16 u7E;
} Unk_80041E58;

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041AB4);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041B20);

void func_80041BAC(struct Unk_80041BAC *arg0, u8 arg1) {
    arg0->unk0->unkC4(arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041BDC);

u8 func_80041C28(Unk_80041C28 *arg0) {
    s32 buf[4];
    return arg0->unkA8;
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041C3C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041C4C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041C9C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041D18);

void func_80041DA4(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041DAC);

void func_80041E2C(struct Unk_80041E2C_obj *arg0, struct Unk_80041E2C *arg1) {
    if (arg0->unkC != 0) {
        arg0->unkA0 = *arg1;
    }
}

void func_80041E58(Unk_80041E58 *arg0, s32 arg1) {
    if (arg0->uC != 0) {
        switch (arg1) {
        case 0:
            arg0->u7C = arg0->u6C >> 1;
            arg0->u7E = arg0->u6E >> 1;
            break;
        case 1:
            arg0->u7C = 0;
            break;
        case 2:
            arg0->u7C = arg0->u6C;
            break;
        case 3:
            arg0->u7E = 0;
            break;
        case 4:
            arg0->u7E = arg0->u6E;
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041ED8);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041EE8);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041F88);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004202C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004208C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042170);

s32 func_8004220C(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x64), 0x1F, 1, arg1 == 0) == 0;
}

void func_8004223C(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x64), 0x1E, 1, arg1 != 0);
}

void func_80042268(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x64), 0x1C, 2, arg1);
}

void func_80042294(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004229C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800422BC);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800422CC);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004232C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800423A8);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800423E4);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800423F0);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042400);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042450);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800424A8);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800424E0);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042550);

void func_800425D8(struct Unk_800425D8 *arg0, s32 arg1) {
    arg0->unkC = arg1;
    arg0->unk14 = 0;
    arg0->unk10 = 0;
    arg0->unk18 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800425EC);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004264C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042658);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042664);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004266C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042678);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042684);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042694);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800426E4);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042790);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042814);

void func_80042820(void) {
}

s32 func_80042828(struct Unk_80042828 *arg0, s32 arg1) {
    return arg0->unk44[arg1];
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004283C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800428E4);

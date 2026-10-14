#include "common.h"

typedef struct Unk_80026C88 {
    u8 pad[0x24];
    u32 unk24;
} Unk_80026C88;
void func_8004A070(s32);
struct Unk_80026CE8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
s32 D_8008A84C;
void func_800280D0(void);
void func_800280E0(void);
s32 func_80027EC8(void);
s32 func_80027ED4(void);
s32 func_80027EE0(void);
s32 func_80027EEC(void);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80025F7C);

INCLUDE_RODATA("asm/nonmatchings/game/80025F7C", D_800107A4);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80025FDC);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800260A4);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026108);

INCLUDE_RODATA("asm/nonmatchings/game/80025F7C", D_800107B4);

INCLUDE_RODATA("asm/nonmatchings/game/80025F7C", D_800107C8);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026170);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026254);

void func_80026328(void) {
    func_8004A070(0);
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026348);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026410);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026518);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_8002658C);

void func_80026690(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026698);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_8002677C);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026900);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800269E0);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800269F0);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026A50);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026AB4);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026B08);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026C20);

void func_80026C80(void) {
}

void func_80026C88(Unk_80026C88 *arg0) {
    arg0->unk24 |= 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026C9C);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026CAC);

struct Unk_80026CE8 *func_80026CE8(struct Unk_80026CE8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = arg3;
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026CFC);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026D88);

void func_80026E0C(void) {
    if (D_8008A84C == 0x13) {
        func_800280D0();
    }
}

void func_80026E38(void) {
    if (D_8008A84C == 0x13) {
        func_800280E0();
    }
}

s32 func_80026E64(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EC8();
    }
    return 0;
}

s32 func_80026E98(void) {
    if (D_8008A84C == 0x13) {
        return func_80027ED4();
    }
    return 1;
}

s32 func_80026ECC(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EE0();
    }
    return 0;
}

s32 func_80026F00(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EEC();
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026F34);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026FAC);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026FE8);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80027024);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270AC);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270B8);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270C4);


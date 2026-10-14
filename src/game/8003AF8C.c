#include "common.h"

typedef struct Unk_8003B02C_Pair {
    s32 unk0;
    s32 unk4;
} Unk_8003B02C_Pair;
struct Unk_8003B02C {
    u8 pad_00[0xC];
    Unk_8003B02C_Pair unkC;
    s32 unk14;
};

INCLUDE_ASM("asm/nonmatchings/game/8003AF8C", func_8003AF8C);

void func_8003B024(void) {
}

void func_8003B02C(struct Unk_8003B02C *arg0, Unk_8003B02C_Pair *arg1, s32 arg2) {
    arg0->unkC = *arg1;
    arg0->unk14 = arg2;
}

INCLUDE_ASM("asm/nonmatchings/game/8003AF8C", func_8003B044);

void func_8003B108(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003AF8C", func_8003B110);

INCLUDE_ASM("asm/nonmatchings/game/8003AF8C", func_8003B20C);

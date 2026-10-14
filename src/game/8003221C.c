#include "common.h"

extern void func_8003221C(s32);

INCLUDE_ASM("asm/nonmatchings/game/8003221C", func_8003221C);

void func_80032368(void) {
    func_8003221C(0);
}

void func_80032388(void) {
    func_8003221C(1);
}

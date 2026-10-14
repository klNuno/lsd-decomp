#include "common.h"

extern void GsGetTimInfo(u32 *im, void *tim);
typedef struct Unk_8003B5F0 {
    u8 pad_00[0x10];
    u32 *unk10;
} Unk_8003B5F0;

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B39C);

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B3FC);

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B470);

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B4A8);

void func_8003B5AC(void) {
}

void func_8003B5B4(void) {
}

void func_8003B5BC(void) {
}

void func_8003B5C4(void) {
}

void func_8003B5CC(void) {
}

void func_8003B5D4(void) {
}

void func_8003B5DC(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B5E4);

void func_8003B5F0(Unk_8003B5F0 *arg0, void *arg1) {
    GsGetTimInfo(arg0->unk10 + 1, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B614);

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B624);

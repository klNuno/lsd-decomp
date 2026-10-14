#include "common.h"

struct Unk_8001F360 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
};

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F250);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F2B0);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F314);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F33C);

s32 func_8001F360(struct Unk_8001F360 *arg0, s32 arg1) {
    s32 offset = arg1 * 0x1C + 0xC;
    return offset + arg0->unkC;
}

void func_8001F37C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F384);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F394);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F3A4);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F3B0);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F4E4);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F50C);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F51C);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F66C);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F8B8);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_80020050);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_800204D0);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_80020510);

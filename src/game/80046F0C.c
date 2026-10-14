#include "common.h"

void StFreeRing(void *ring);
void StUnSetRing(void);
extern void StClearRing(void);
extern s32 CdSync(s32, u8 *);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80046F0C);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80046F88);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047074);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800470C8);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047114);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047240);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_8004728C);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800472EC);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047388);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800473E4);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800474C8);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047574);

void func_800475C8(void) {
}

void func_800475D0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800475D8);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047638);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047694);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800477B0);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047810);

void func_80047870(s32 arg0, void *arg1) {
    StFreeRing(arg1);
}

void func_80047890(void) {
    StUnSetRing();
}

void func_800478B0(void) {
    StClearRing();
}

void func_800478D0(u8 *arg0, s32 arg1) {
    CdSync(arg1, arg0 + 0x24);
}

void func_800478F8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047900);

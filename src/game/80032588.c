#include "common.h"

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032588);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032708);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032998);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_800329B8);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_800329D8);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032A7C);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032A9C);

extern s32 D_8006DCA0;
extern void SsSeqCalledTbyT(void);

void func_80032AD0(void) {
    if (D_8006DCA0 == 0) {
        D_8006DCA0 = 1;
    } else {
        D_8006DCA0 = 0;
        SsSeqCalledTbyT();
    }
}

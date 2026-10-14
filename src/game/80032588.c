#include "common.h"

extern s32 D_8006DCA0;
extern void SsSeqCalledTbyT(void);
void func_80032708(s32 arg0);
extern void SpuQuit(void);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032588);

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032708);

void func_80032998(void) {
    func_80032708(1);
}

void func_800329B8(void) {
    func_80032708(0);
}

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_800329D8);

void func_80032A7C(void) {
    SpuQuit();
}

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032A9C);

void func_80032AD0(void) {
    if (D_8006DCA0 == 0) {
        D_8006DCA0 = 1;
    } else {
        D_8006DCA0 = 0;
        SsSeqCalledTbyT();
    }
}

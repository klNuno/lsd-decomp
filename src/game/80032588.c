#include "common.h"

extern s32 D_8006DCA0;
extern void SsSeqCalledTbyT(void);
void func_80032708(s32 arg0);
extern void SpuQuit(void);
extern void (*D_8006DC9C)(void);
extern s32 D_8006DC8C;
extern s32 D_8006DC90;
extern s32 D_8006DC94;
extern s32 D_8006DCA8;
extern s32 EnterCriticalSection();
extern s32 ExitCriticalSection();
void VSyncCallback(void (*func)(void));
void InterruptCallback(s32 irq, void (*func)(void));
extern s32 D_8006DC98;
extern s32 D_8006DCA4;
extern s32 D_8009024C;

void func_80032588(s32 arg0) {
    if (arg0 & 0x1000) {
        D_8006DCA8 = 1;
        D_8006DCA4 = arg0 & 0xFFF;
    } else {
        D_8006DCA8 = 0;
        D_8006DCA4 = arg0;
    }
    if (D_8006DCA4 < 6) {
        switch (D_8006DCA4) {
        case 4:
            D_8009024C = 0x32;
            if (D_8006DC98 == 1) {
                D_8006DCA4 = 5;
            } else {
                D_8006DCA4 = 0x32;
            }
            return;
        case 1:
            D_8009024C = 0x3C;
            if (D_8006DC98 == 0) {
                D_8006DCA4 = 5;
            } else {
                D_8006DCA4 = 0x3C;
            }
            return;
        case 3:
            D_8009024C = 0x78;
            return;
        case 2:
            D_8009024C = 0xF0;
            return;
        case 5:
            switch (D_8006DC98) {
            case 1:
                D_8009024C = 0x32;
                return;
            default:
            case 0:
                D_8009024C = 0x3C;
                return;
            }
            break;
        case 0:
            if (D_8006DC98 != 0) {
                if (D_8006DC98 == 1) {
                    D_8009024C = 0x32;
                    return;
                }
                D_8009024C = 0x3C;
                return;
            }
            D_8009024C = 0x3C;
            return;
        default:
            D_8009024C = 0x3C;
            return;
        }
    } else {
        D_8009024C = D_8006DCA4;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80032588", func_80032708);

void func_80032998(void) {
    func_80032708(1);
}

void func_800329B8(void) {
    func_80032708(0);
}

void func_800329D8(void) {
    if (D_8006DCA8 == 0) {
        D_8006DC94 = 0;
        EnterCriticalSection();
        if (D_8006DC8C != 0) {
            VSyncCallback(0);
            D_8006DC8C = 0;
        } else if (D_8006DC90 != -1) {
            if (D_8006DC90 == 0) {
                InterruptCallback(0, D_8006DC9C);
            } else {
                InterruptCallback(D_8006DC90, 0);
            }
            D_8006DC90 = -1;
        }
        ExitCriticalSection();
    }
}

void func_80032A7C(void) {
    SpuQuit();
}

void func_80032A9C(void) {
    if (D_8006DC9C != NULL) {
        D_8006DC9C();
    }
    SsSeqCalledTbyT();
}

void func_80032AD0(void) {
    if (D_8006DCA0 == 0) {
        D_8006DCA0 = 1;
    } else {
        D_8006DCA0 = 0;
        SsSeqCalledTbyT();
    }
}

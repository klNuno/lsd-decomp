#include "common.h"

typedef struct Unk_80028A34 {
    u8 pad[0xC];
    s32 unkC;
} Unk_80028A34;
s32 D_8008A85C;
s32 D_8008A860;
s32 D_8008A864;
s32 D_8008A870;
s32 D_8008A874;
s32 D_8008A878;
s32 *D_8008A894;
s32 D_8008A898;
s32 D_8008A8A0;
void func_800280D0(void);
void func_800280E0(void);
s32 D_8008A890;
typedef struct Unk_80028A50 {
    u8 pad[0xC];
    s32 unkC;
    u8 pad2[0xC];
    u32 unk1C;
} Unk_80028A50;

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800271D8);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027228);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027274);

void func_800272C8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800272D0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027480);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027528);

void func_800276C8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800276D0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027800);

INCLUDE_RODATA("asm/nonmatchings/game/800271D8", D_800107D8);

INCLUDE_RODATA("asm/nonmatchings/game/800271D8", D_800107F4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027A24);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027C80);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027D40);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027D70);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027E68);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027E78);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027EC8);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027ED4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027EE0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027EEC);

s32 func_80027EF8(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = D_8008A860;
    }
    return D_8008A85C;
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027F18);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FD8);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FE4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FF0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FFC);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800280D0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800280E0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800280EC);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800281B0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028218);

void func_80028280(void) {
    func_800280D0();
    D_8008A890 = 0;
    func_800280E0();
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800282AC);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_8002832C);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800283C4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028448);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800284C4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028540);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_8002858C);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800286E4);

void func_80028844(s32 arg0, s32 arg1) {
    D_8008A864 = 1;
    D_8008A874 = arg0;
    D_8008A878 = arg1;
    D_8008A870 = 0;
    *D_8008A894 = 1;
}

void func_80028864(void) {
    D_8008A874 = 0;
    D_8008A878 = 0;
    D_8008A898 = 0;
    D_8008A870 = 1;
    D_8008A8A0 = 0;
    D_8008A864 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028888);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028898);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800288E0);

void func_80028918(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028920);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800289CC);

void func_80028A34(Unk_80028A34 *arg0) {
    if (arg0->unkC != 0) {
        arg0->unkC = 0;
    }
}

s32 func_80028A50(Unk_80028A50 *arg0) {
    if (arg0->unkC != 0) {
        return ((arg0->unk1C >> 0xB) + 1) << 0xB;
    }
    return 0;
}

void func_80028A7C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028A84);

void func_80028B64(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028B6C);

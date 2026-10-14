#include "common.h"

void GsSetFlatLight(s32 id, void *light, void *arg2);
typedef struct Unk_800429E8 {
    u8 pad0[0xC];
    s32 unkC;
    u8 unk10[0xC];
    s8 unk1C;
    s8 unk1D;
    s8 unk1E;
} Unk_800429E8;

INCLUDE_ASM("asm/nonmatchings/game/8004291C", func_8004291C);

INCLUDE_ASM("asm/nonmatchings/game/8004291C", func_8004297C);

INCLUDE_ASM("asm/nonmatchings/game/8004291C", func_800429E0);

void func_800429E8(Unk_800429E8 *arg0, s32 arg1, s8 *arg2) {
    s32 r;
    s32 g;
    s32 b;

    if (arg1 != 0) {
        r = arg2[0];
        g = arg2[1];
        b = arg2[2];
        arg0->unk1C = r;
        arg0->unk1D = g;
        arg0->unk1E = b;
    }
    GsSetFlatLight(arg0->unkC, arg0->unk10, arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/8004291C", func_80042A2C);

INCLUDE_ASM("asm/nonmatchings/game/8004291C", func_80042A7C);

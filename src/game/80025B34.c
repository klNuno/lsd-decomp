#include "common.h"

typedef struct Unk_80025C84_Vtbl {
    u8 pad[0x50];
    void (*unk50)(void *, s32);
} Unk_80025C84_Vtbl;
typedef struct Unk_80025C84 {
    Unk_80025C84_Vtbl *unk0;
    u8 pad4[0x8];
    s16 unkC;
    u8 padE[0x2];
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Unk_80025C84;
extern s32 PadRead(u16);

INCLUDE_ASM("asm/nonmatchings/game/80025B34", func_80025B34);

INCLUDE_ASM("asm/nonmatchings/game/80025B34", func_80025BA0);

INCLUDE_ASM("asm/nonmatchings/game/80025B34", func_80025C30);

void func_80025C84(Unk_80025C84 *arg0, s32 arg1) {
    s32 temp = arg1 != 0;
    arg0->unkC = temp;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk18 = 0;
    arg0->unk0->unk50(arg0, temp);
}

void func_80025CC4(Unk_80025C84 *arg0) {
    s32 cur;
    s32 prev;
    s32 changed;

    cur = PadRead(arg0->unkC);
    prev = arg0->unk10;
    arg0->unk10 = cur;
    changed = cur ^ prev;
    arg0->unk14 = changed & prev;
    arg0->unk18 = changed & cur;
}

INCLUDE_ASM("asm/nonmatchings/game/80025B34", func_80025D10);

void func_80025E14(void) {
}

INCLUDE_RODATA("asm/nonmatchings/game/80025B34", D_80010764);

INCLUDE_ASM("asm/nonmatchings/game/80025B34", func_80025E1C);

void func_80025E94(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80025B34", func_80025E9C);

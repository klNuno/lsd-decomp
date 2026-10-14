#include "common.h"

typedef struct Unk_8002089C {
    u8 pad[0x10];
    s32 unk10;
} Unk_8002089C;
typedef struct Unk_80020B4C {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad_14[0xC];
    /* 0x20 */ s32 unk20;
} Unk_80020B4C;
void GsSwapDispBuff(void);
extern int GsGetActiveBuff(void);
typedef struct Unk_80020970 {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
} Unk_80020970;

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_800206E0);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020730);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020784);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_800207DC);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_8002085C);

void func_8002089C(Unk_8002089C *arg0) {
    if (arg0->unk10 != 0) {
        arg0->unk10 = 0;
    }
}

void func_800208B8(void) {
    GsSwapDispBuff();
}

void func_800208D8(void) {
    GsGetActiveBuff();
}

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_800208F8);

void func_80020970(Unk_80020970 *arg0, Unk_80020970 *arg1) {
    arg0->unk0 = arg1->unk0;
    arg0->unk2 = arg1->unk2;
    arg0->unk4 = arg1->unk4;
    arg0->unk6 = arg1->unk8;
}

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_800209A0);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020A1C);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020A24);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020A74);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020AF4);

void func_80020B4C(Unk_80020B4C *arg0, s32 arg1) {
    if (arg0->unk10 == 0) {
        arg0->unk20 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020B68);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020B74);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C08);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C3C);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C44);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C4C);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C5C);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C68);

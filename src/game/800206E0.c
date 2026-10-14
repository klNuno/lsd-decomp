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
typedef struct Unk_80020C08 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad_0C[0x8];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} Unk_80020C08;
typedef struct Unk_8002085C_Obj {
    u8 pad_00[0x68];
    void (*unk68)(void);
} Unk_8002085C_Obj;
typedef struct Unk_8002085C {
    /* 0x00 */ Unk_8002085C_Obj *unk0;
    /* 0x04 */ u8 pad_04[0xC];
    /* 0x10 */ s32 unk10;
} Unk_8002085C;

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_800206E0);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020730);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020784);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_800207DC);

void func_8002085C(Unk_8002085C *arg0) {
    if (arg0->unk10 == 0) {
        arg0->unk10 = 1;
        arg0->unk0->unk68();
    }
}

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

s32 *func_80020C08(Unk_80020C08 *arg0, Unk_80020C08 *arg1) {
    if (arg1 != NULL) {
        arg1->unk0 = 0;
        arg1->unk2 = 0;
        arg1->unk4 = arg0->unk14;
        arg1->unk8 = arg0->unk18 * 2;
    }
    return &arg0->unk14;
}

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C3C);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C44);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C4C);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C5C);

INCLUDE_ASM("asm/nonmatchings/game/800206E0", func_80020C68);

#include "common.h"

struct Unk_80043B58 {
    u8 pad_00[0x2C];
    s32 *unk2C;
};
struct Unk_80043B3C {
    u8 pad_00[0x10];
    s32 unk10;
};
struct Unk_80043538_Entry {
    u16 unk0;
    s16 unk2;
    u8 pad_04[0xC];
};
struct Unk_80043538 {
    u8 pad_00[0x40];
    struct Unk_80043538_Entry unk40[1];
};
struct Unk_80043B18 {
    u8 pad_00[0x10];
    u32 *unk10;
};
extern void GsMapModelingData(u32 *p);
struct Unk_80045E18 {
    u8 pad_00[0x4C];
    s32 unk4C;
};
typedef struct Unk_8004464C_Color {
    s8 unk0;
    s8 unk1;
    s8 unk2;
} Unk_8004464C_Color;
struct Unk_8004464C {
    u8 pad_00[0x54];
    Unk_8004464C_Color unk54;
};
struct Unk_80044B58 {
    u8 pad_00[0x78];
    void (*unk78)(void);
};

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043008);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043068);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800431A8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043200);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800434DC);

void func_80043538(struct Unk_80043538 *arg0, s32 arg1, u16 arg2) {
    struct Unk_80043538_Entry *entry = &arg0->unk40[arg1];

    entry->unk0 = arg2;
    entry->unk2 = 1 << entry->unk0;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004355C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800435D0);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043648);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043830);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043840);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800438B0);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043954);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800439EC);

void func_80043B18(struct Unk_80043B18 *arg0) {
    GsMapModelingData(arg0->unk10 + 1);
}

s32 func_80043B3C(struct Unk_80043B3C *arg0, s32 arg1) {
    s32 t = arg1 * 0x1C + 0xC;
    return t + arg0->unk10;
}

s32 func_80043B58(struct Unk_80043B58 *arg0, s32 arg1) {
    return arg0->unk2C[arg1];
}

void func_80043B70(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043B78);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043B88);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043BE8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043C60);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043CB8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043DFC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043E74);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043E84);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043EE4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043F78);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043FB0);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043FE4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004416C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800441A4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800441B4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044220);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044294);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044380);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004441C);

void func_8004464C(struct Unk_8004464C *arg0, s32 arg1, Unk_8004464C_Color *arg2) {
    if (arg1 != 0) {
        arg0->unk54 = *arg2;
    }
}

void func_80044674(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004467C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004468C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800446FC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800447B4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044808);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044858);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800448F8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004497C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800449B8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800449FC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044A0C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044A7C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044B04);

void func_80044B58(struct Unk_80044B58 **arg0) {
    (*arg0)->unk78();
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044B88);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044C58);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044C90);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044CC4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044CD4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044D40);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044DC8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044E10);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044E64);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044F20);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044F30);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044F90);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004500C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045060);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800450B4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800451A8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800451B8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045228);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800452AC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800452FC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800453DC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045428);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045438);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800454C4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800455D4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004564C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004575C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800457C0);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800458AC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800458B8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004593C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045948);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045A38);

void func_80045AC8(void) {
}

void func_80045AD0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045AD8);

void func_80045BC0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045BC8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045C94);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045CFC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045DE0);

void func_80045E18(struct Unk_80045E18 *arg0) {
    while (arg0->unk4C == 0) {
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045E3C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045E44);

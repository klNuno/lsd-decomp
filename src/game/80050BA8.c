#include "common.h"

typedef struct Unk_80018390 { s32 unk0, unk4, unk8; void (*unkC)(); u8 pad_10[0x8]; void (*unk18)(void *); } Unk_80018390;
extern void func_80017CFC(s32);
extern Unk_80018390 *func_80018390(void);
typedef struct { u8 pad[0x20]; s32 u20; u8 pad2[0x24]; s32 u48; } Unk_800517EC;
extern void func_800183DC(void *, s32);
extern void func_800531CC(void *, void *);
void func_8002CC84(void *, void *);
typedef struct Unk_8005161C_Vtbl {
    u8 pad[0x80];
    void (*unk80)(void *, s32, s32, s32);
} Unk_8005161C_Vtbl;
typedef struct Unk_8005161C_Obj {
    Unk_8005161C_Vtbl *vtbl;
} Unk_8005161C_Obj;
typedef struct Unk_8005161C {
    u8 pad[0x3C];
    Unk_8005161C_Obj *u3C;
} Unk_8005161C;
struct Unk_80051814;
struct Unk_80051814_vtbl {
    u8 pad_00[0xA8];
    void (*unkA8)(struct Unk_80051814 *, s32, s32, s32);
};
struct Unk_80051814 {
    struct Unk_80051814_vtbl *unk0;
    u8 pad_04[0x10];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x28];
    s32 unk48;
};
typedef struct Unk_80050E34 {
    u8 pad_00[0x34];
    s32 unk34;
    s32 unk38;
    u8 pad_3C[0x48 - 0x3C];
    s32 unk48;
} Unk_80050E34;
typedef struct Unk_80051E20 {
    u8 pad_00[0x34];
    s32 unk34;
    s32 unk38;
    u8 pad_3C[0x50 - 0x3C];
    s32 unk50;
} Unk_80051E20;
typedef struct Unk_80051270_Vtbl {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32);
} Unk_80051270_Vtbl;
typedef struct Unk_80051270 {
    Unk_80051270_Vtbl *unk0;
    u8 pad_04[0x30];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} Unk_80051270;
struct Unk_8005165C;
typedef struct Unk_8005165C_vtbl {
    u8 pad_00[0xA4];
    void (*unkA4)(struct Unk_8005165C *, s32, s32);
} Unk_8005165C_vtbl;
typedef struct Unk_8005165C {
    Unk_8005165C_vtbl *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    u8 pad_14[0x4];
    s32 unk18;
    u8 pad_1C[0x48 - 0x1C];
    s32 unk48;
} Unk_8005165C;
typedef struct Unk_80051720_vtbl {
    u8 pad_00[0xA8];
    void (*unkA8)(void *, s32, s32, s32);
} Unk_80051720_vtbl;
typedef struct Unk_80051720 {
    Unk_80051720_vtbl *unk0;
    u8 pad_04[0x10];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x28];
    s32 unk48;
} Unk_80051720;
typedef struct Unk_80051370_Vtbl {
    u8 pad_00[0x54];
    void (*unk54)(void *, s32);
} Unk_80051370_Vtbl;
typedef struct Unk_80051370 {
    Unk_80051370_Vtbl *unk0;
    u8 pad_04[0x28];
    s32 unk2C;
    s32 unk30;
} Unk_80051370;
typedef struct Unk_800516C0_Vtbl {
    u8 pad_00[0xA4];
    void (*unkA4)(void *, s32, s32);
} Unk_800516C0_Vtbl;
typedef struct Unk_800516C0 {
    Unk_800516C0_Vtbl *unk0;
    u8 pad_04[0x14];
    s32 unk18;
    u8 pad_1C[0x2C];
    s32 unk48;
} Unk_800516C0;

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050BA8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050C14);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050CD8);

void func_80050CE8(u8 *arg0) {
    func_80017CFC(*(s32 *)(arg0 + 0x28));
    func_80018390()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050D30);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050DB4);

void func_80050E34(Unk_80050E34 *arg0) {
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk48 = 0;
    func_80018390()->unk18(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050E78);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050F28);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_800115D0);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_80011610);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_8001161C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050F98);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051174);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051200);

void func_80051270(Unk_80051270 *arg0) {
    arg0->unk0->unk14(arg0, arg0->unk34);
    arg0->unk0->unk14(arg0, arg0->unk38);
    arg0->unk3C = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800512C8);

void func_80051370(Unk_80051370 *arg0) {
    s32 temp_v1;
    s32 temp_v1_2;

    temp_v1 = arg0->unk2C;
    if (temp_v1 < 4) {
        if (temp_v1 >= 2) {
            temp_v1_2 = arg0->unk30;
            arg0->unk30 = temp_v1_2 + 1;
            if (temp_v1_2 != 0) {
                arg0->unk0->unk54(arg0, 4);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800513D0);

void func_8005161C(Unk_8005161C *arg0, s32 arg1) {
    Unk_8005161C_Obj *temp_a0;

    temp_a0 = arg0->u3C;
    if (temp_a0 != NULL) {
        temp_a0->vtbl->unk80(temp_a0, arg1, 0x60, 0x60);
    }
}

void func_8005165C(Unk_8005165C *arg0) {
    s32 temp_a1;
    s32 temp_v1;

    if (arg0->unk48 != 0) {
        temp_v1 = arg0->unk18;
        temp_a1 = temp_v1 + 1;
        arg0->unk18 = temp_a1;
        if (temp_a1 < arg0->unk10) {
            arg0->unk0->unkA4(arg0, temp_a1, 1);
            return;
        }
        arg0->unk18 = temp_v1;
    }
}

void func_800516C0(Unk_800516C0 *arg0) {
    s32 temp_v0;
    s32 temp_a1;

    if (arg0->unk48 != 0) {
        temp_v0 = arg0->unk18;
        temp_a1 = temp_v0 - 1;
        arg0->unk18 = temp_a1;
        if (temp_a1 >= 0) {
            arg0->unk0->unkA4(arg0, temp_a1, 1);
            return;
        }
        arg0->unk18 = temp_v0;
    }
}

void func_80051720(Unk_80051720 *arg0) {
    s32 temp_a2;

    if (arg0->unk48 != 0) {
        temp_a2 = arg0->unk1C + 1;
        arg0->unk1C = temp_a2;
        if (temp_a2 < arg0->unk14) {
            arg0->unk0->unkA8(arg0, arg0->unk18, temp_a2, 1);
            return;
        }
        arg0->unk1C = 0;
    }
}

void func_80051784(struct Unk_80051814 *arg0) {
    s32 temp_a2;

    if (arg0->unk48 != 0) {
        temp_a2 = arg0->unk1C - 1;
        arg0->unk1C = temp_a2;
        if (temp_a2 > 0) {
            arg0->unk0->unkA8(arg0, arg0->unk18, temp_a2, 1);
            return;
        }
        arg0->unk1C = arg0->unk14;
    }
}

void func_800517EC(Unk_800517EC *arg0) {
    if (arg0->u48 != 0) {
        arg0->u20 ^= 1;
    }
}

void func_80051814(struct Unk_80051814 *arg0) {
    if (arg0->unk48 != 0) {
        arg0->unk1C = 0;
        arg0->unk0->unkA8(arg0, arg0->unk18, 0, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051858);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800518F4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051998);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051A4C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051A5C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051AC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051C74);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051C84);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051D1C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051DA0);

void func_80051E20(Unk_80051E20 *arg0) {
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk50 = 0;
    func_80018390()->unk18(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051E64);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051F14);

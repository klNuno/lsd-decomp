#include "common.h"

extern u8 D_80081A04[];
extern s16 D_80086170[];
s32 D_8008A964;
s32 D_8008A968;
u8 *func_80048E2C(s32 arg0);
s32 *func_80048DF8(void);
extern void srand(u32 seed);
extern s32 rand(void);
void *func_80048D48(s32 *arg0);
s32 func_80017CFC(s32);
typedef struct Unk_80048C98 {
    u8 pad_00[0x2E];
    s16 unk2E;
    u8 pad_30[4];
    s32 unk34;
} Unk_80048C98;
u8 *func_8004903C(s32 arg0);
typedef struct Unk_80048A68 {
    u8 pad_00[0x2A];
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
} Unk_80048A68;
typedef struct Unk_80048A68_Vtbl {
    u8 pad_00[0x74];
    void (*unk74)(Unk_80048A68 *);
} Unk_80048A68_Vtbl;
Unk_80048A68_Vtbl *func_80026CAC(void);
s32 func_800491CC(s32 *arg0);
struct Unk_80048B78_Vtbl {
    u8 pad_00[0x5C];
    void (*unk5C)(void);
};
struct Unk_80048B78 {
    struct Unk_80048B78_Vtbl *unk0;
    u8 pad_04[0x28];
    s16 unk2C;
    u8 pad_2E[2];
    s16 unk30;
};
typedef struct Unk_80048894 {
    u8 pad_00[8];
    void (*unk8)(s32);
} Unk_80048894;
Unk_80048894 *func_80048CE0(void);
s32 func_80017B34(s32 arg0);
extern s16 D_800819E8[];
typedef struct { s16 unk_0; s16 unk_2; s32 unk_4; } Unk_800861D4;
Unk_800861D4 *func_800494D8(s32 arg0);
u8 *func_80049060(s32 arg0, s32 arg1);
u8 *func_80049240(s32 *arg0);

s32 func_80048894(void) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x3C);
    if (temp_v0 != 0) {
        func_80048CE0()->unk8(temp_v0);
        return temp_v0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800488E4);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048960);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800489B4);

void func_80048A68(Unk_80048A68 *arg0) {
    func_80026CAC()->unk74(arg0);
    arg0->unk2C = 0;
    arg0->unk2E = 0;
    arg0->unk2A = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048AAC);

void func_80048B78(struct Unk_80048B78 *arg0) {
    arg0->unk0->unk5C();
    arg0->unk2C = 0;
    arg0->unk30 = -1;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048BC0);

void func_80048C98(Unk_80048C98 *arg0) {
    s32 temp_a0;

    temp_a0 = arg0->unk34;
    arg0->unk2E = 0;
    if (temp_a0 != 0) {
        arg0->unk34 = func_80017CFC(temp_a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048CD8);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048CE0);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048CF0);

void func_80048CFC(s32 arg0) {
    if (arg0 != 0) {
        srand(arg0);
    }
    rand();
}

void func_80048D28(s32 arg0, s32 arg1) {
    if (arg0 >= 0) {
        D_8008A964 = arg0;
    }
    if (arg1 >= 0) {
        D_8008A968 = arg1;
    }
}

void *func_80048D48(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0x230;
    }
    return D_80081A04;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048D64);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048D74);

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048DF8);

s32 func_80048E08(void) {
    return *func_80048DF8();
}

u8 *func_80048E2C(s32 arg0) {
    return (u8 *)func_80048D48(NULL) + D_800819E8[arg0] * 0x1C;
}

u8 *func_80048E80(s32 arg0) {
    return func_80048E2C(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048EA0);

u8 *func_80048F60(s32 arg0) {
    return func_80048E2C(arg0) + 0x70;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80048F84);

u8 *func_8004903C(s32 arg0) {
    return func_80048E2C(arg0) + 0xFC;
}

u8 *func_80049060(s32 arg0, s32 arg1) {
    return func_8004903C(arg0) + arg1 * 0x1C;
}

void func_80049098(s32 arg0, s32 arg1, s32 arg2) {
    func_80049060(arg0, arg1 + (func_800494D8(arg0)->unk_0 * arg2));
}

INCLUDE_RODATA("asm/nonmatchings/game/80048894", D_80011384);

char *func_800490F4(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0x31;
    }
    return "ETC\\ASMK.STR";
}

s32 func_80049110(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0;
    }
    return (s32)func_80048D48(NULL) + 0x3D40;
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_8004913C);

s32 func_800491CC(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 7;
    }
    return (s32)func_80048D48(NULL) + 0x3E04;
}

s32 func_800491FC(s32 *arg0) {
    s32 sp10;
    s32 temp_v1;

    temp_v1 = func_800491CC(&sp10);
    if (arg0 != NULL) {
        *arg0 = sp10;
    }
    return temp_v1;
}

u8 *func_80049240(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 8;
    }
    return (u8 *)func_80048D48(NULL) + 0x3E20;
}

u8 *func_80049270(s32 *arg0, s32 arg1) {
    s32 sp10;
    u8 *temp_v1;

    temp_v1 = func_80049240(&sp10);
    if (arg0 != NULL) {
        *arg0 = arg1 + sp10;
    }
    return temp_v1 + arg1 * 0x1C;
}

s32 func_800492D0(s32 *arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = (s32)func_80048D48(NULL) + 0x3EC8;
    if (arg0 != NULL) {
        *arg0 = (arg1 * 2) + 0xE;
    }
    return temp_v1 + (arg1 * 0xA8);
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_80049334);

s16 func_800493C8(s32 arg0) {
    return D_80086170[arg0];
}

INCLUDE_ASM("asm/nonmatchings/game/80048894", func_800493E4);

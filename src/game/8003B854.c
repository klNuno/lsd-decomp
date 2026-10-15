#include "common.h"

struct Unk_8003E4A4 {
    u8 pad_00[0x1C];
    s32 unk1C;
};
typedef struct Unk_8003EA0C_Pair {
    s32 unk0;
    s32 unk4;
} Unk_8003EA0C_Pair;
struct Unk_8003EA0C {
    u8 pad_00[0x34];
    Unk_8003EA0C_Pair unk34;
};
struct Unk_8003BCF4 {
    u8 pad_00[0x40];
    s32 unk40;
};
typedef struct Unk_8003DFA0 {
    u8 pad_00[0x58];
    s32 unk58;
    s32 pad_5C;
    s32 *unk60;
} Unk_8003DFA0;
struct Unk_8003EA2C {
    u8 pad_00[0x44];
    s32 unk44;
    u8 pad_48[0x70 - 0x48];
    s32 unk70;
};
typedef struct Unk_8003EA48 {
    u8 pad[0x48];
    s32 unk48;
    u8 pad4C[0x70 - 0x4C];
    s32 unk70;
} Unk_8003EA48;
struct Unk_8003BA38 {
    u8 pad_00[0xC4];
    s32 unkC4;
    s32 unkC8;
    s32 unkCC;
    s32 unkD0;
    s32 unkD4;
};
struct Unk_8003C794 {
    u8 pad_00[0x40];
    s32 unk40;
};
extern void SetGeomScreen(s32);
struct Unk_8003F25C {
    u8 pad_00[0xC];
    struct Unk_8003F25C *unkC;
};
typedef struct Unk_8003EBC4_Vec {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8003EBC4_Vec;
struct Unk_8003EBC4 {
    u8 pad_00[0x10];
    s32 unk10;
    Unk_8003EBC4_Vec unk14;
};
typedef struct Unk_8003EBF8_Vec {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8003EBF8_Vec;
struct Unk_8003EBF8 {
    u8 pad_00[0x10];
    s32 unk10;
    u8 pad_14[0x20 - 0x14];
    Unk_8003EBF8_Vec unk20;
};
typedef struct Unk_8003EA84_Rgb {
    s8 r;
    s8 g;
    s8 b;
} Unk_8003EA84_Rgb;
struct Unk_8003EA84 {
    u8 pad_00[0x58];
    Unk_8003EA84_Rgb unk58;
};
typedef struct Unk_8003EAA4_Rgb {
    s8 r;
    s8 g;
    s8 b;
} Unk_8003EAA4_Rgb;
struct Unk_8003EAA4 {
    u8 pad_00[0x5B];
    Unk_8003EAA4_Rgb unk5B;
};
struct Unk_8003C7B4_Obj;
typedef struct Unk_8003C7B4_Vtbl {
    u8 pad_00[0x80];
    void (*unk80)(struct Unk_8003C7B4_Obj *, s32, s32, s32);
} Unk_8003C7B4_Vtbl;
struct Unk_8003C7B4_Obj {
    Unk_8003C7B4_Vtbl *unk0;
};
struct Unk_8003C7B4 {
    u8 pad_00[0x48];
    struct Unk_8003C7B4_Obj *unk48;
};
typedef struct Unk_8003E538_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *);
} Unk_8003E538_Vtbl;
typedef struct Unk_8003E538_Obj {
    Unk_8003E538_Vtbl *unk0;
} Unk_8003E538_Obj;
typedef struct Unk_8003E538_Link {
    Unk_8003E538_Obj *unk0;
} Unk_8003E538_Link;
struct Unk_8003E538 {
    u8 pad_00[0xC];
    Unk_8003E538_Link *unkC;
    u8 pad_10[0x1C - 0x10];
    s32 unk1C;
};
typedef struct Unk_8003EB84_Vt {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32);
} Unk_8003EB84_Vt;
struct Unk_8003EB84 {
    Unk_8003EB84_Vt *unk0;
    u8 pad_04[0x10 - 0x4];
    s32 unk10;
};
struct Unk_8003BD74 {
    u8 pad_00[0x80];
    void (*unk80)(s32);
};
extern void *func_8003DFBC(void);
struct Unk_8003BDAC {
    u8 pad_00[0x84];
    void (*unk84)(s32);
};
struct Unk_8003CAF8_Inner {
    u8 pad_00[0xB0];
    s32 unkB0;
};
struct Unk_8003CAF8 {
    struct Unk_8003CAF8_Inner *unk0;
    u8 pad_04[0x88 - 0x04];
    s32 unk88;
};
struct Unk_8003CB30_Sub {
    u8 pad_00[0xC4];
    s32 unkC4;
};
struct Unk_8003CB30 {
    struct Unk_8003CB30_Sub *unk0;
    u8 pad_04[0x8C - 0x4];
    s32 unk8C;
};
typedef struct Unk_8003EE88_Vtbl {
    u8 pad[0xA4];
    void (*unkA4)(void *);
} Unk_8003EE88_Vtbl;
typedef struct Unk_8003EE88 {
    Unk_8003EE88_Vtbl *unk0;
} Unk_8003EE88;
struct Unk_8003E874 {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
    u8 pad_14[0x30 - 0x14];
    s32 unk30;
};
typedef struct Unk_8003E874_Vtbl {
    u8 pad_00[0x18];
    void (*unk18)(void *);
} Unk_8003E874_Vtbl;
Unk_8003E874_Vtbl *func_80018390(void);
struct Unk_8003EE40;
typedef struct Unk_8003EE40_Vtbl {
    u8 pad_00[0x9C];
    void (*unk9C)(struct Unk_8003EE40 *, s32, s32);
} Unk_8003EE40_Vtbl;
struct Unk_8003EE40 {
    Unk_8003EE40_Vtbl *unk0;
    u8 pad_04[0x90 - 0x04];
    s32 unk90;
};
extern s32 DrawSync(s32);
extern void func_80017CFC(s32);
struct Unk_8003EDF4 {
    u8 pad_00[0x70];
    s32 unk70;
    u8 pad_74[0x78 - 0x74];
    s32 unk78;
};
struct Unk_8003CB68 {
    u8 pad_00[0x90];
    Unk_8003EA84_Rgb unk90;
    Unk_8003EA84_Rgb unk93;
    Unk_8003EA84_Rgb unk96;
};
typedef struct Unk_8003E578_Vtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *);
} Unk_8003E578_Vtbl;
struct Unk_8003E5D8 {
    u8 pad_00[0x8];
    void (*unk8)(s32);
};
s32 func_80017B34(s32);
struct Unk_8003E5D8 *func_8003F24C(void);
typedef struct Unk_8003CA94_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_8003CA94_Vtbl;
typedef struct Unk_8003CA94 {
    Unk_8003CA94_Vtbl *unk0;
    u8 pad_04[0x9C - 0x04];
    void (*unk9C)(s32);
    s32 unkA0;
} Unk_8003CA94;
typedef struct Unk_8003B9DC_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
} Unk_8003B9DC_Vtbl;
typedef struct Unk_8003B9DC_Obj {
    Unk_8003B9DC_Vtbl *unk0;
} Unk_8003B9DC_Obj;
struct Unk_8003B9DC {
    u8 pad_00[0xB4];
    Unk_8003B9DC_Obj *unkB4;
};
struct Unk_8003B9DC_Callee {
    u8 pad_00[0xC];
    void (*unkC)(void *);
};
struct Unk_8003BA58 {
    u8 pad_00[0xB8];
    s32 unkB8;
    s32 unkBC;
    s32 unkC0;
};
typedef struct Unk_8003BA58_Vt {
    u8 pad_00[0x44];
    void (*unk44)(void *, void *, s32);
} Unk_8003BA58_Vt;
typedef struct Unk_8003C1DC {
    u8 pad_00[0x38];
    s32 unk38;
} Unk_8003C1DC;
typedef struct Unk_8003C1DC_Obj {
    u8 pad_00[0x44];
    void (*unk44)(Unk_8003C1DC *, s32, s32);
} Unk_8003C1DC_Obj;
extern void *func_8003E5C8(void);
typedef struct Unk_8003BD10_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_8003BD10_Vtbl;
struct Unk_8003BD10 {
    Unk_8003BD10_Vtbl *unk0;
    u8 pad_04[0x38 - 0x04];
    s32 unk38;
    u8 pad_3C[0xCC - 0x3C];
    s32 unkCC;
};
struct Unk_8003BD10_Ret {
    u8 pad_00[0x78];
    void (*unk78)(void *);
};
struct Unk_8003C7F4;
typedef struct Unk_8003C7F4_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(struct Unk_8003C7F4 *, s32);
    u8 pad_64[0x70 - 0x64];
    void (*unk70)(struct Unk_8003C7F4 *, s32);
} Unk_8003C7F4_Vtbl;
struct Unk_8003C7F4 {
    Unk_8003C7F4_Vtbl *unk0;
    u8 pad_04[0x4C - 0x04];
    s32 unk4C;
};
typedef struct Unk_8003E578_Obj {
    Unk_8003E578_Vtbl *unk0;
} Unk_8003E578_Obj;
typedef struct Unk_8003BDF4 {
    Unk_8003CA94_Vtbl *unk0;
    u8 pad_04[0xB4 - 0x04];
    Unk_8003E578_Obj *unkB4;
    u8 pad_B8[0xD4 - 0xB8];
    s32 unkD4;
} Unk_8003BDF4;
struct Unk_8003D6D4 {
    u8 pad_00[0x58];
    s32 unk58;
    s32 *unk5C;
    s32 pad_60;
    void **unk64;
};
extern void func_800183DC(void *, s32);
typedef struct Unk_8003DDC8_Vtbl {
    u8 pad_00[0x11C];
    void (*unk11C)(void *, s32, s32);
} Unk_8003DDC8_Vtbl;
struct Unk_8003DDC8 {
    Unk_8003DDC8_Vtbl *unk0;
    u8 pad_04[0x58 - 0x04];
    s32 unk58;
    s32 *unk5C;
    s32 *unk60;
};
struct Unk_8003C944;
typedef struct Unk_8003C944_Vtbl {
    u8 pad_00[0xEC];
    void (*unkEC)(struct Unk_8003C944 *);
    u8 pad_F0[0x118 - 0xF0];
    void (*unk118)(struct Unk_8003C944 *);
} Unk_8003C944_Vtbl;
struct Unk_8003C944 {
    Unk_8003C944_Vtbl *unk0;
    u8 pad_04[0x3C - 0x04];
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    s32 unk4C;
};
struct Unk_8003C9B0;
typedef struct Unk_8003C9B0_Vtbl {
    u8 pad_00[0xE8];
    void (*unkE8)(struct Unk_8003C9B0 *);
    u8 pad_EC[0x114 - 0xEC];
    void (*unk114)(struct Unk_8003C9B0 *);
} Unk_8003C9B0_Vtbl;
struct Unk_8003C9B0 {
    Unk_8003C9B0_Vtbl *unk0;
    u8 pad_04[0x3C - 0x04];
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    s32 unk4C;
};
typedef struct Unk_8003CBC0_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_8003CBC0_Vtbl;
struct Unk_8003CBC0 {
    Unk_8003CBC0_Vtbl *unk0;
    u8 pad_04[0x88 - 0x04];
    s32 (*unk88)(void);
};
typedef struct Unk_8003CCDC_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_8003CCDC_Vtbl;
struct Unk_8003CCDC {
    Unk_8003CCDC_Vtbl *unk0;
    u8 pad_04[0x8C - 0x04];
    s32 (*unk8C)();
};
typedef struct Unk_8003C8D0_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0x70 - 0x64];
    void (*unk70)(void *, s32);
} Unk_8003C8D0_Vtbl;
typedef struct Unk_8003C8D0 {
    Unk_8003C8D0_Vtbl *unk0;
    u8 pad_04[0x3C - 0x04];
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    s32 unk4C;
} Unk_8003C8D0;

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003B854);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003B8E4);

void func_8003B9DC(struct Unk_8003B9DC *arg0) {
    Unk_8003B9DC_Obj *temp = arg0->unkB4;
    temp->unk0->unk4(temp);
    ((struct Unk_8003B9DC_Callee *)func_8003DFBC())->unkC(arg0);
}

void func_8003BA38(struct Unk_8003BA38 *arg0) {
    arg0->unkC8 = -1;
    arg0->unkC4 = 0;
    arg0->unkCC = 1;
    arg0->unkD0 = 0;
    arg0->unkD4 = 1;
}

void func_8003BA58(struct Unk_8003BA58 *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->unkB8 = arg2;
    arg0->unkBC = arg3;
    arg0->unkC0 = arg4;
    ((Unk_8003BA58_Vt *)func_8003DFBC())->unk44(arg0, arg1, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BAB4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BB5C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BC14);

void func_8003BCF4(struct Unk_8003BCF4 *arg0, s32 arg1) {
    arg0->unk40 = arg1;
    if (arg1 >= 0) {
        arg0->unk40 = arg1 * 15;
    }
}

void func_8003BD10(struct Unk_8003BD10 *arg0) {
    ((struct Unk_8003BD10_Ret *)func_8003DFBC())->unk78(arg0);
    if (arg0->unkCC != 0) {
        arg0->unk38 = 2;
        arg0->unk0->unk60(arg0, 0x12);
    }
}

void func_8003BD74(s32 arg0) {
    ((struct Unk_8003BD74 *)func_8003DFBC())->unk80(arg0);
}

void func_8003BDAC(s32 arg0) {
    ((struct Unk_8003BDAC *)func_8003DFBC())->unk84(arg0);
}

void func_8003BDE4(void) {
}

void func_8003BDEC(void) {
}

void func_8003BDF4(Unk_8003BDF4 *arg0) {
    if (arg0->unkD4 != 0) {
        arg0->unkB4->unk0->unk4C(arg0->unkB4);
        return;
    }
    arg0->unk0->unk60(arg0, 7);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE5C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE64);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE6C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE74);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE7C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE84);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BE94);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003BF10);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C008);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C11C);

s32 func_8003C1DC(Unk_8003C1DC *arg0, s32 arg1, s32 arg2) {
    ((Unk_8003C1DC_Obj *)func_8003E5C8())->unk44(arg0, arg1, arg2);
    return arg0->unk38;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C238);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C3D0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C48C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C51C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C63C);

void func_8003C794(struct Unk_8003C794 *arg0, s32 arg1) {
    arg0->unk40 = arg1;
    if (arg1 >= 0) {
        arg0->unk40 = arg1 * 20;
    }
}

void func_8003C7B4(struct Unk_8003C7B4 *arg0, s32 arg1) {
    struct Unk_8003C7B4_Obj *temp_a0;

    temp_a0 = arg0->unk48;
    if (temp_a0 != NULL) {
        temp_a0->unk0->unk80(temp_a0, arg1, 0x60, 0x60);
    }
}

void func_8003C7F4(struct Unk_8003C7F4 *arg0) {
    if (arg0->unk4C != 0) {
        arg0->unk0->unk70(arg0, 0x10);
        arg0->unk0->unk60(arg0, 0xA);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003C858);

void func_8003C8D0(Unk_8003C8D0 *arg0) {
    if (arg0->unk4C != 0 && arg0->unk3C != 1) {
        arg0->unk0->unk70(arg0, 0x10);
        arg0->unk0->unk60(arg0, 0x11);
    }
}

void func_8003C944(struct Unk_8003C944 *arg0) {
    if (arg0->unk4C != 0) {
        if (arg0->unk3C == 1) {
            arg0->unk0->unkEC(arg0);
        } else if (arg0->unk3C == 2) {
            arg0->unk0->unk118(arg0);
        }
    }
}

void func_8003C9B0(struct Unk_8003C9B0 *arg0) {
    if (arg0->unk4C != 0) {
        if (arg0->unk3C == 1) {
            arg0->unk0->unkE8(arg0);
        } else if (arg0->unk3C == 2) {
            arg0->unk0->unk114(arg0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CA1C);

void func_8003CA94(Unk_8003CA94 *arg0) {
    if (arg0->unk9C != NULL) {
        arg0->unk9C(arg0->unkA0);
    }
    arg0->unk0->unk60(arg0, 7);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CAEC);

void func_8003CAF8(struct Unk_8003CAF8 *arg0, s32 arg1) {
    struct Unk_8003CAF8_Inner *temp_v1 = arg0->unk0;

    switch (arg1) {
    case 0:
        arg0->unk88 = 0;
        break;
    case 1:
        arg0->unk88 = temp_v1->unkB0;
        break;
    }
}

void func_8003CB30(struct Unk_8003CB30 *arg0, s32 arg1) {
    struct Unk_8003CB30_Sub *v1 = arg0->unk0;

    switch (arg1) {
    case 0:
        arg0->unk8C = 0;
        return;
    case 1:
        arg0->unk8C = v1->unkC4;
        return;
    }
}

void func_8003CB68(struct Unk_8003CB68 *arg0, Unk_8003EA84_Rgb *arg1, Unk_8003EA84_Rgb *arg2, Unk_8003EA84_Rgb *arg3) {
    arg0->unk90 = *arg1;
    arg0->unk93 = *arg2;
    arg0->unk96 = *arg3;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CBB8);

s32 func_8003CBC0(struct Unk_8003CBC0 *arg0) {
    s32 (*temp_v0)(void);
    s32 var_s1;

    temp_v0 = arg0->unk88;
    var_s1 = 1;
    if (temp_v0 != NULL) {
        var_s1 = temp_v0();
    }
    if (var_s1 != 0) {
        arg0->unk0->unk60(arg0, 5);
    }
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CC2C);

s32 func_8003CCDC(struct Unk_8003CCDC *arg0) {
    s32 var_s1 = 1;

    if (arg0->unk8C == NULL || (var_s1 = arg0->unk8C()) != 0) {
        arg0->unk0->unk60(arg0, 8);
    }
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CD48);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CDE0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CE98);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D050);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D194);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D2CC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D3B0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D444);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D4DC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D5C0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D5CC);

void func_8003D6D4(struct Unk_8003D6D4 *arg0) {
    func_800183DC(arg0->unk64[arg0->unk58], arg0->unk5C[arg0->unk58]);
    func_80017CFC(arg0->unk64[arg0->unk58]);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D73C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D980);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DA10);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DAD4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DCAC);

void func_8003DDC8(struct Unk_8003DDC8 *arg0) {
    s32 var_a1;

    var_a1 = arg0->unk60[arg0->unk58];
    var_a1 = var_a1 + 1;
    if (var_a1 >= arg0->unk5C[arg0->unk58]) {
        var_a1 = 0;
    }
    arg0->unk0->unk11C(arg0, var_a1, 1);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DE30);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DE9C);

s32 func_8003DFA0(Unk_8003DFA0 *arg0) {
    return arg0->unk60[arg0->unk58];
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DFBC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DFCC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DFDC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E030);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E100);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E10C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E280);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E418);

void func_8003E4A4(struct Unk_8003E4A4 *arg0) {
    arg0->unk1C++;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E4B8);

void func_8003E538(struct Unk_8003E538 *arg0) {
    arg0->unk1C = 0;
    arg0->unkC->unk0->unk0->unk48(arg0->unkC->unk0);
}

void func_8003E578(struct Unk_8003E538 *arg0) {
    Unk_8003E538_Obj *temp_a0;

    temp_a0 = arg0->unkC->unk0;
    ((Unk_8003E578_Vtbl *)temp_a0->unk0)->unk4C(temp_a0);
    arg0->unk1C = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E5C8);

s32 func_8003E5D8(void) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0xBC);
    if (temp_v0 != 0) {
        func_8003F24C()->unk8(temp_v0);
        return temp_v0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E628);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E6CC);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E770);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E7F4);

void func_8003E874(struct Unk_8003E874 *arg0) {
    arg0->unk30 = 0;
    arg0->unk10 = 0;
    arg0->unkC = 0;
    func_80018390()->unk18(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E8B8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E968);

void func_8003EA0C(struct Unk_8003EA0C *arg0, Unk_8003EA0C_Pair *arg1) {
    arg0->unk34 = *arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EA24);

void func_8003EA2C(struct Unk_8003EA2C *arg0, s32 arg1) {
    if (arg0->unk70 == 0) {
        arg0->unk44 = arg1;
    }
}

void func_8003EA48(Unk_8003EA48 *arg0, s32 arg1) {
    if (arg0->unk70 == 0) {
        arg0->unk48 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EA64);

void func_8003EA6C(void) {
}

void func_8003EA74(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EA7C);

void func_8003EA84(struct Unk_8003EA84 *arg0, Unk_8003EA84_Rgb *arg1) {
    arg0->unk58 = *arg1;
}

void func_8003EAA4(struct Unk_8003EAA4 *arg0, Unk_8003EAA4_Rgb *arg1) {
    arg0->unk5B = *arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EAC4);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EACC);

void func_8003EB84(struct Unk_8003EB84 *arg0) {
    s32 temp = arg0->unk10;
    if (temp != 0) {
        arg0->unk0->unk14(arg0, temp);
    }
}

void func_8003EBC4(struct Unk_8003EBC4 *arg0, Unk_8003EBC4_Vec *arg1) {
    if (arg0->unk10 != 0) {
        arg0->unk14 = *arg1;
    }
}

void func_8003EBF8(struct Unk_8003EBF8 *arg0, Unk_8003EBF8_Vec *arg1) {
    if (arg0->unk10 != 0) {
        arg0->unk20 = *arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EC2C);

void func_8003ECC0(void) {
}

void func_8003ECC8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003ECD0);

void func_8003EDF4(struct Unk_8003EDF4 *arg0) {
    if (arg0->unk70 != 0) {
        DrawSync(0);
        func_80017CFC(arg0->unk78);
        arg0->unk70 = 0;
    }
}

void func_8003EE40(struct Unk_8003EE40 *arg0, s32 arg1, s32 arg2) {
    s32 flag;

    flag = (arg2 == 2 || arg2 == 3);
    arg0->unk90++;
    if (flag) {
        arg0->unk0->unk9C(arg0, arg1, flag);
    }
}

void func_8003EE88(Unk_8003EE88 *arg0, s32 arg1, s32 arg2) {
    if (arg2 == 2) {
        arg0->unk0->unkA4(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003EEC0);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F04C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F1A8);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F230);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F23C);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F244);

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003F24C);

struct Unk_8003F25C *func_8003F25C(struct Unk_8003F25C *arg0) {
    while (arg0->unkC != NULL) {
        arg0 = arg0->unkC;
    }
    return arg0;
}

void func_8003F28C(s32 arg0) {
    SetGeomScreen(arg0);
}

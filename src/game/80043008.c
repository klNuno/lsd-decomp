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
typedef s32 (*Unk_80043FB0_Fn)(void *arg0, s32 arg1, s32 arg2, s32 arg3);
struct Unk_80043FB0_Vtbl {
    u8 pad_00[0x7C];
    Unk_80043FB0_Fn unk7C;
};
struct Unk_80043FB0 {
    struct Unk_80043FB0_Vtbl *unk0;
    u8 pad_04[0xC];
    s32 unk10;
};
struct Unk_8004497C_Vtbl {
    u8 pad_00[0x78];
    u8 (*unk78)(void *arg0);
};
struct Unk_8004497C_Obj {
    struct Unk_8004497C_Vtbl *unk0;
};
struct Unk_8004497C {
    u8 pad_00[0x30];
    struct Unk_8004497C_Obj *unk30;
};
struct Unk_80043F78 {
    u8 pad_00[0xC];
    void (*unkC)(void *);
};
struct Unk_80043F78 *func_80026CAC(void);
struct Unk_80044C58 {
    u8 pad_00[0x10];
    u8 *unk10;
    u8 pad_14[0x24];
    s32 unk38;
};
extern void func_800183DC(void *, s32);
typedef void (*Unk_80045DE0_Fn)(void *self);
struct Unk_80045DE0_Vtbl {
    u8 pad_00[0x60];
    Unk_80045DE0_Fn unk60;
};
struct Unk_80045DE0 {
    struct Unk_80045DE0_Vtbl *unk0;
};
struct Unk_80045DE0 *D_8008A940;
struct Unk_800449B8_Vtbl {
    u8 pad_00[0x80];
    void (*unk80)(void *self, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
};
struct Unk_800449B8_Obj {
    struct Unk_800449B8_Vtbl *unk0;
};
struct Unk_800449B8 {
    u8 pad_00[0x30];
    struct Unk_800449B8_Obj *unk30;
};
extern void func_80017CFC(s32);
struct Unk_80044DC8 {
    u8 pad_00[0x38];
    s32 unk38;
};
typedef s32 (*Unk_800453DC_Fn)(void *arg0, s32 arg1, s32 arg2, u32 *arg3);
struct Unk_800453DC_Vtbl {
    u8 pad_00[0x7C];
    Unk_800453DC_Fn unk7C;
};
struct Unk_800453DC {
    struct Unk_800453DC_Vtbl *unk0;
    u8 pad_04[0xC];
    u32 *unk10;
};
struct Unk_80044808_Vtbl {
    u8 pad_00[0x78];
    void (*unk78)(void *arg0);
};
struct Unk_80044808_Obj {
    struct Unk_80044808_Vtbl *unk0;
};
struct Unk_80044808_Mgr {
    u8 pad_00[0x64];
    void (*unk64)(void *arg0);
};
struct Unk_800452AC_Obj {
    u8 pad_00[0xC];
    void (*unkC)(void *arg0);
};
struct Unk_800452AC_Obj *func_800441A4(void);
struct Unk_80044B04 {
    u8 pad_00[0x7C];
    void (*unk7C)(struct Unk_80044B04 **arg0);
};
struct Unk_800449FC {
    u8 pad_00[0xC];
    void (*unkC)(struct Unk_80044B04 **arg0);
};
struct Unk_800449FC *func_800449FC(void);
struct Unk_80044E10 {
    struct Unk_80044B58 *unk0;
    u8 pad_04[0x26];
    u16 unk2A;
    u8 pad_2C[0x16];
    u16 unk42;
};
typedef void (*Unk_80045060_Fn)(void *self);
struct Unk_80045060_Vtbl {
    u8 pad_00[0x78];
    Unk_80045060_Fn unk78;
};
struct Unk_80045060 {
    struct Unk_80045060_Vtbl *unk0;
    u8 pad_04[0x26];
    u16 unk2A;
    u8 pad_2C[6];
    u16 unk32;
};
struct Unk_800447B4 {
    u8 pad_00[0x7C];
    void (*unk7C)(void);
};
struct Unk_8004500C {
    u8 pad_00[0x2C];
    s32 unk2C;
    u8 pad_30[0x4];
    s32 unk34;
};
struct Unk_800431A8 {
    u8 pad_00[0x2C];
    s32 unk2C;
    void *unk30;
};
struct Unk_80043C60 {
    u8 pad_00[0x2C];
    s32 unk2C;
    void *unk30;
};
struct Unk_8004575C {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};
struct Unk_80043008_Obj {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32);
};
struct Unk_80043008_Obj *func_80043830(void);
s32 func_80017B34(s32 arg0);
typedef struct Unk_80043B88 {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32);
} Unk_80043B88;
extern s32 func_80017B34(s32 size);
extern Unk_80043B88 *func_80043E74(void);
struct Unk_80044F30 {
    u8 pad_00[0x8];
    void (*unk8)(void *arg0, s32 arg1);
};
struct Unk_80044F30 *func_800451A8(void);
s32 D_8008A948;
struct Unk_80045C94_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *self);
};
struct Unk_80045C94 {
    struct Unk_80045C94_Vtbl *unk0;
    u8 pad_04[0x50];
    s32 unk54;
};
struct Unk_800441B4_Mgr {
    u8 pad_00[0x8];
    void (*unk8)(void *arg0, s32 arg1, s32 arg2);
};
struct Unk_800441B4_Mgr *func_8004467C(void);
struct Unk_80043840_Obj {
    u8 pad_00[0x8];
    s32 (*unk8)(s32, s32);
};
struct Unk_80043840_Obj *func_80043B78(void);
struct Unk_80044A0C_Obj {
    u8 pad_00[0x8];
    s32 (*unk8)(s32, s32);
};
struct Unk_80044A0C_Obj *func_80044CC4(void);
struct Unk_800451B8_Obj {
    u8 pad_00[0x8];
    s32 (*unk8)(s32 arg0, s32 arg1);
};
struct Unk_800451B8_Obj *func_80045428(void);

s32 func_80043008(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x84);
    if (temp_v0 != 0) {
        func_80043830()->unk8(temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043068);

void func_800431A8(struct Unk_800431A8 *arg0) {
    func_800183DC(arg0->unk30, arg0->unk2C);
    func_80017CFC(arg0->unk30);
    func_80026CAC()->unkC(arg0);
}

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

s32 func_80043840(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x30);
    if (temp_v0 != 0) {
        if (func_80043B78()->unk8(temp_v0, arg0) != 0) {
            return temp_v0;
        }
        func_80017CFC(temp_v0);
    }
    return 0;
}

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

s32 func_80043B88(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x3C);
    if (temp_v0 != 0) {
        func_80043E74()->unk8(temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043BE8);

void func_80043C60(struct Unk_80043C60 *arg0) {
    func_800183DC(arg0->unk30, arg0->unk2C);
    func_80017CFC(arg0->unk30);
    func_80026CAC()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043CB8);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043DFC);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043E74);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043E84);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043EE4);

void func_80043F78(s32 arg0) {
    func_80026CAC()->unkC(arg0);
}

s32 func_80043FB0(struct Unk_80043FB0 *arg0, s32 arg1, s32 arg2) {
    return arg0->unk0->unk7C(arg0, arg1, arg2, arg0->unk10 + 8) & 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80043FE4);

u32 *func_8004416C(void *arg0, u32 *arg1, s8 *arg2, s8 *arg3, s8 *arg4, s8 *arg5) {
    u32 temp_v1 = *arg1;

    *arg2 = temp_v1;
    *arg3 = (temp_v1 >> 16) & 0xF;
    *arg4 = (temp_v1 >> 20) & 0xF;
    *arg5 = temp_v1 >> 24;
    return arg1 + 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800441A4);

s32 func_800441B4(s32 arg0, s32 arg1) {
    void *temp_s0 = (void *)func_80017B34(0x68);

    if (temp_s0 != NULL) {
        func_8004467C()->unk8(temp_s0, arg0, arg1);
        return (s32)temp_s0;
    }
    return 0;
}

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

void func_800447B4(struct Unk_800447B4 **arg0) {
    (*arg0)->unk7C();
    func_80026CAC()->unkC(arg0);
}

void func_80044808(struct Unk_80044808_Obj *arg0) {
    ((struct Unk_80044808_Mgr *)func_80026CAC())->unk64(arg0);
    arg0->unk0->unk78(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044858);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800448F8);

s32 func_8004497C(struct Unk_8004497C *arg0) {
    struct Unk_8004497C_Obj *temp_a0 = arg0->unk30;

    return temp_a0->unk0->unk78(temp_a0);
}

void func_800449B8(struct Unk_800449B8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unk30->unk0->unk80(arg0->unk30, arg1, arg2, arg3, arg4, arg5);
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800449FC);

s32 func_80044A0C(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x3C);
    if (temp_s0 != 0) {
        if (func_80044CC4()->unk8(temp_s0, arg0) == 0) {
            func_80017CFC(temp_s0);
            return 0;
        }
        return temp_s0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044A7C);

void func_80044B04(struct Unk_80044B04 **arg0) {
    (*arg0)->unk7C(arg0);
    func_800449FC()->unkC(arg0);
}

void func_80044B58(struct Unk_80044B58 **arg0) {
    (*arg0)->unk78();
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044B88);

void func_80044C58(struct Unk_80044C58 *arg0) {
    func_800183DC(arg0->unk10 + 8, arg0->unk38);
    arg0->unk38 = 0;
}

u32 func_80044C90(struct Unk_80043B18 *arg0, u32 arg1) {
    u32 *temp_v1 = arg0->unk10;

    if (arg1 < temp_v1[1]) {
        return temp_v1[arg1 + 2];
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044CC4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044CD4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044D40);

void func_80044DC8(struct Unk_80044DC8 *arg0) {
    func_80017CFC(arg0->unk38);
    func_80026CAC()->unkC((s32)arg0);
}

void func_80044E10(struct Unk_80044E10 *arg0) {
    if (arg0->unk2A == 0) {
        arg0->unk0->unk78();
        arg0->unk42 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044E64);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044F20);

s32 func_80044F30(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x38);
    if (temp_v0 != 0) {
        func_800451A8()->unk8((void *)temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80044F90);

void func_8004500C(struct Unk_8004500C *arg0) {
    func_80017CFC(arg0->unk34);
    func_80017CFC(arg0->unk2C);
    func_80026CAC()->unkC(arg0);
}

void func_80045060(struct Unk_80045060 *arg0) {
    s32 buf[8];

    if (arg0->unk2A == 0) {
        arg0->unk0->unk78(arg0);
        arg0->unk32 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800450B4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800451A8);

s32 func_800451B8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x2C);
    if (temp_v0 == 0) {
        return 0;
    }
    if (func_80045428()->unk8(temp_v0, arg0) != 0) {
        return temp_v0;
    }
    func_80017CFC(temp_v0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045228);

void func_800452AC(struct Unk_80043B18 *arg0) {
    u32 *temp = arg0->unk10;

    func_800183DC(temp + 2, temp[1]);
    func_800441A4()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800452FC);

s32 func_800453DC(struct Unk_800453DC *arg0, s32 arg1, s32 arg2) {
    return arg0->unk0->unk7C(arg0, arg1, arg2, &arg0->unk10[arg0->unk10[1]] + 4) & 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045428);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045438);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800454C4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_800455D4);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_8004564C);

void func_8004575C(struct Unk_8004575C *arg0) {
    if (arg0->unkC == 0) {
        func_80017CFC(arg0->unk14);
        func_80017CFC(arg0->unk18);
        func_80017CFC(arg0->unk10);
        func_80017CFC(arg0->unk1C);
    }
}

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

s32 func_80045C94(struct Unk_80045C94 *arg0) {
    if (arg0->unk54 != 0) {
        if (D_8008A948++ > 100) {
            D_8008A948 = 1;
            arg0->unk0->unk44(arg0);
        }
        return 0;
    }
    D_8008A940 = NULL;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045CFC);

void func_80045DE0(void) {
    struct Unk_80045DE0 *obj = D_8008A940;

    if (obj != NULL) {
        obj->unk0->unk60(obj);
    }
}

void func_80045E18(struct Unk_80045E18 *arg0) {
    while (arg0->unk4C == 0) {
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045E3C);

INCLUDE_ASM("asm/nonmatchings/game/80043008", func_80045E44);

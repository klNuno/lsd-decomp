#include "common.h"

typedef struct { s16 unk_0; s16 unk_2; s32 unk_4; } Unk_800861D4;
extern Unk_800861D4 D_800861D4[];
extern s16 *D_80086590[];
typedef struct { u8 pad[0x74]; s32 u74; s16 u78; s16 u7A; } Unk_8004B32C;
typedef struct { u8 pad[0x32]; s16 id; } Obj;
typedef struct { s32 unk0; Obj *obj; u8 pad[0x14]; } Slot;
typedef struct { u8 pad[0xEC]; Slot slots[7]; } Owner;
extern void func_8004F40C(s32, s32 (*)(), s32);
typedef struct { u8 pad[0x2C]; s32 u2C; } Unk_8004A458;
void func_8004F4C8(s32, s32);
typedef struct { s16 pad[3]; s16 u6; } T;
typedef struct { u8 pad[0x1E0]; s32 u1E0; T *u1E4; } S;
extern T D_8008699C, D_800869A8, D_800869B4, D_800869C0;
typedef struct { u8 pad[0x54]; s32 u54[3]; u8 pad2[0x68 - 0x60]; Unk_800861D4 *u68; } Unk_8004B418;
void func_8004B44C(s32 *arg0, s32 *arg1, Unk_800861D4 *arg2, s32 *arg3, void *arg4);
typedef struct Unk_8004BCE0_Slot {
    u16 unk0;
    u8 pad_02[0x1C - 0x2];
} Unk_8004BCE0_Slot;
typedef struct Unk_8004BCE0 {
    u8 pad_00[0xEC];
    Unk_8004BCE0_Slot unkEC[7];
} Unk_8004BCE0;
typedef struct Unk_8004A478_vt { u8 pad[0x80]; void (*unk80)(void *, s32, s32, s32); } Unk_8004A478_vt;
typedef struct Unk_8004A478_obj { Unk_8004A478_vt *unk0; } Unk_8004A478_obj;
typedef struct Unk_8004A478 { u8 pad[0x34]; Unk_8004A478_obj *unk34; } Unk_8004A478;
struct Unk_8004B57C;
typedef struct Unk_8004B57C_Vtbl {
    u8 pad_00[0xC0];
    void (*unkC0)(struct Unk_8004B57C *);
    u8 pad_C4[0xF4 - 0xC4];
    void (*unkF4)(struct Unk_8004B57C *);
    u8 pad_F8[0x13C - 0xF8];
    void (*unk13C)(struct Unk_8004B57C *);
} Unk_8004B57C_Vtbl;
typedef struct Unk_8004B57C {
    Unk_8004B57C_Vtbl *unk0;
    u8 pad_04[0x70 - 0x4];
    s32 unk70;
} Unk_8004B57C;
typedef struct Unk_8004A324 {
    u8 pad[0xC];
    void (*unkC)(void *);
    u8 pad_10[0x38];
    void (*unk48)(s32);
    u8 pad_4C[0x10];
    void (*unk5C)(void *, s32, s32);
    void (*unk60)(void *, s32);
} Unk_8004A324;
Unk_8004A324 *func_8003E5C8(void);
typedef struct Unk_8004D0D0_Arg0 {
    u8 pad_00[0x1E4];
    void *unk1E4;
} Unk_8004D0D0_Arg0;
typedef struct Unk_8004D0D0_Vtbl {
    u8 pad_00[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_8004D0D0_Vtbl;
typedef struct Unk_8004D0D0 {
    Unk_8004D0D0_Vtbl *unk0;
} Unk_8004D0D0;
typedef struct Unk_8004D108_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_8004D108_Vtbl;
typedef struct Unk_8004D108 {
    Unk_8004D108_Vtbl *unk0;
} Unk_8004D108;
extern s32 D_800869CC;
typedef struct Unk_8004C3F0_B { u8 pad_00[0x30]; s16 u30; } Unk_8004C3F0_B;
typedef struct Unk_8004C3F0_A { u8 pad_00[0x4]; Unk_8004C3F0_B *u4; } Unk_8004C3F0_A;
typedef struct Unk_8004C3F0 { u8 pad_00[0x68]; Unk_800861D4 *u68; u8 pad_6C[0x1BC - 0x6C]; Unk_8004C3F0_A *u1BC; } Unk_8004C3F0;
void func_8004C368(Unk_8004C3F0 *arg0, u8 *arg1, s32 arg2);
struct Unk_8004AB88;
typedef struct Unk_8004AB88_Vtbl {
    u8 pad_00[0xD0];
    void (*unkD0)(struct Unk_8004AB88 *);
} Unk_8004AB88_Vtbl;
typedef struct Unk_8004AB88 {
    Unk_8004AB88_Vtbl *unk0;
} Unk_8004AB88;
typedef struct Unk_8004B2D4_Vtbl {
    u8 pad_00[0x38];
    void (*unk38)(void *);
} Unk_8004B2D4_Vtbl;
typedef struct Unk_8004B2D4 {
    Unk_8004B2D4_Vtbl *unk0;
    u8 pad_04[0x36 - 0x4];
    u16 unk36;
} Unk_8004B2D4;
struct Unk_8004B344;
typedef struct Unk_8004B344_Vtbl {
    u8 pad_00[0x40];
    void (*unk40)(struct Unk_8004B344 *);
} Unk_8004B344_Vtbl;
typedef struct Unk_8004B344 {
    Unk_8004B344_Vtbl *unk0;
    u8 pad_04[0x68 - 0x4];
    s32 unk68;
} Unk_8004B344;
typedef struct Unk_8004D088 {
    u8 pad_00[0x1E0];
    s32 unk1E0;
} Unk_8004D088;
void func_8004D108(s32 arg0, Unk_8004D108 *arg1);
void func_8004D140(void *arg0, void (*arg1)(), void (*arg2)(void *, void *));
typedef struct Unk_8004D434_Vtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *);
} Unk_8004D434_Vtbl;
typedef struct Unk_8004D434 {
    Unk_8004D434_Vtbl *unk0;
} Unk_8004D434;
typedef struct { u8 pad[0x7C]; s16 u7C; s16 u7E; s32 u80; s32 u84; } Unk_8004AFE0;
void func_8004C93C(void);
typedef struct { u8 pad_00[0x2C]; s16 u2C; s16 pad_2E; s16 u30; } Unk_8004C5D0_Obj;
typedef struct { s32 unk0; Unk_8004C5D0_Obj *obj; u8 pad_08[0x14]; } Unk_8004C5D0_Slot;
typedef struct { u8 pad_00[0xEC]; Unk_8004C5D0_Slot slots[7]; } Unk_8004C5D0;
typedef struct Unk_8004D254 {
    u8 pad_00[0x8];
    void (*unk8)(s32);
} Unk_8004D254;
s32 func_80017B34(s32);
Unk_8004D254 *func_8004D37C(void);
typedef struct Unk_8004D38C {
    u8 pad_00[0x8];
    void (*unk8)(s32);
} Unk_8004D38C;
s32 func_80017B34(s32 size);
void *func_8004D508(void);
typedef struct Unk_8004D3DC_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8004D3DC_vt;
Unk_8004D3DC_vt *func_8001E57C(void);
typedef struct Unk_8004D3DC {
    void *unk0;
    u8 pad_04[0x34 - 0x4];
    s16 unk34;
    s16 unk36;
    s32 unk38;
} Unk_8004D3DC;
typedef struct Unk_8004D2A4 {
    u8 pad_00[0x8];
    void (*unk8)(void **);
    u8 pad_0C[0x40 - 0xC];
    void (*unk40)(void **);
    u8 pad_44[0x9C - 0x44];
    void (*unk9C)(void *);
} Unk_8004D2A4;
Unk_8004D2A4 *func_8003F24C(void);
typedef struct Unk_80049C50_Vtbl {
    u8 pad_00[0x74];
    void (*unk74)(void *);
    u8 pad_78[0x90 - 0x78];
    void (*unk90)(void *);
} Unk_80049C50_Vtbl;
typedef struct Unk_80049C50_Obj {
    Unk_80049C50_Vtbl *unk0;
} Unk_80049C50_Obj;
typedef struct Unk_80049C50 {
    u8 pad_00[0x18];
    Unk_80049C50_Obj *unk18;
} Unk_80049C50;
s32 D_8008A980;
typedef struct Unk_8004AA10_Vtbl {
    u8 pad_00[0xDC];
    void (*unkDC)(void *, s32);
} Unk_8004AA10_Vtbl;
typedef struct Unk_8004AA10 {
    Unk_8004AA10_Vtbl *unk0;
    u8 pad_04[0x68 - 0x4];
    s32 unk68;
    u8 pad_6C[0x88 - 0x6C];
    s32 unk88;
    u8 pad_8C[0xE8 - 0x8C];
    s32 unkE8;
    u8 pad_EC[0x1CC - 0xEC];
    s32 unk1CC;
    s32 unk1D0;
    s32 unk1D4;
    s32 unk1D8;
} Unk_8004AA10;
typedef struct Unk_8004A2C4 {
    u8 pad_00[0x28];
    s32 u28;
} Unk_8004A2C4;
typedef struct Unk_8004A2C4_Obj {
    u8 pad_00[0x44];
    void (*unk44)(Unk_8004A2C4 *, s32, s32);
} Unk_8004A2C4_Obj;
void func_8004D0D0();
typedef struct Unk_8004D518 { u8 pad_00[0x8]; void (*unk8)(s32, s32); } Unk_8004D518;
extern Unk_8004D518 *func_8004E2D0(void);
struct Unk_8004C158;
typedef struct Unk_8004C158_Vtbl {
    u8 pad_00[0x110];
    s32 (*unk110)(struct Unk_8004C158 *, s32, s32);
} Unk_8004C158_Vtbl;
typedef struct Unk_8004C158_A {
    u8 pad_00[0x14];
    s32 unk14;
} Unk_8004C158_A;
typedef struct Unk_8004C158 {
    Unk_8004C158_Vtbl *unk0;
    u8 pad_04[0x6C - 0x4];
    Unk_8004C158_A *unk6C;
    u8 pad_70[0xBC - 0x70];
    u8 unkBC[1];
} Unk_8004C158;
typedef struct Unk_8004A130 {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32, s32);
} Unk_8004A130;
Unk_8004A130 *func_8004A4B8(void);
typedef struct Unk_8004A4C8 { u8 pad_00[0x8]; void (*unk8)(s32, s32, s32); } Unk_8004A4C8;
Unk_8004A4C8 *func_8004D244(void);
typedef struct Unk_8004A228_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
} Unk_8004A228_Vtbl;
typedef struct Unk_8004A228_Obj {
    Unk_8004A228_Vtbl *unk0;
} Unk_8004A228_Obj;
typedef struct Unk_8004A228 {
    u8 pad_00[0x30];
    s32 unk30;
    Unk_8004A228_Obj *unk34;
} Unk_8004A228;
typedef struct Unk_8004A3EC Unk_8004A3EC;
typedef struct Unk_8004A3EC_Vtbl {
    u8 pad_00[0x7C];
    void (*unk7C)(Unk_8004A3EC *);
} Unk_8004A3EC_Vtbl;
struct Unk_8004A3EC {
    Unk_8004A3EC_Vtbl *unk0;
    u8 pad_04[0x28 - 0x4];
    s32 unk28;
};
typedef struct Unk_8004D300 {
    u8 pad_00[0x10];
    s32 unk10;
    u8 pad_14[0x70 - 0x14];
    s32 unk70;
} Unk_8004D300;
typedef struct Unk_80049608 {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32, s32, s32);
} Unk_80049608;
Unk_80049608 *func_8004A060(void);
extern void *func_80052B70(s32, s32, s32, s32, s32);
typedef struct Unk_80049E20 Unk_80049E20;
typedef struct Unk_80049E20_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void *, void *);
    u8 pad_14[0x44 - 0x14];
    void (*unk44)(void *, s32, s32);
} Unk_80049E20_Vtbl;
typedef struct Unk_80049E20_Obj {
    Unk_80049E20_Vtbl *unk0;
} Unk_80049E20_Obj;
struct Unk_80049E20 {
    Unk_80049E20_Vtbl *unk0;
    u8 pad_04[0x0C - 0x04];
    s32 unkC;
    u8 pad_10[0x34 - 0x10];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    Unk_80049E20_Obj *unk4C;
};
typedef struct Unk_8004D47C_Mgr {
    u8 pad_00[0x9C];
    void (*unk9C)(void **, void *, s32);
} Unk_8004D47C_Mgr;
typedef struct Unk_8004D47C_Obj {
    u8 pad_00[0xA0];
    void (*unkA0)(void **, void *, s32);
} Unk_8004D47C_Obj;
typedef struct Unk_8004A364_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_8004A364_Vtbl;
typedef struct Unk_8004A364 {
    Unk_8004A364_Vtbl *unk0;
    u8 pad_04[0x1C - 0x4];
    s32 unk1C;
    u8 pad_20[0x2C - 0x20];
    s32 unk2C;
} Unk_8004A364;
typedef struct Unk_8004C620 {
    u8 pad_00[0x68];
    Unk_800861D4 *unk68;
    u8 pad_6C[0x78 - 0x6C];
    s16 unk78;
    s16 unk7A;
    u8 pad_7C[0x1B8 - 0x7C];
    s32 unk1B8;
} Unk_8004C620;
void func_8004CE24(void *arg0, s32 arg1);
void func_8004C6A8(void *arg0, s32 arg1, s16 arg2);
void func_8004CC74(void *arg0);
typedef struct Unk_8004A984_Mgr {
    u8 pad_00[0x38];
    void (*unk38)(void **, s32 **, s32);
} Unk_8004A984_Mgr;
typedef struct Unk_8004A984_Obj {
    u8 pad_00[0x100];
    void (*unk100)(void **, s32 **, s32);
} Unk_8004A984_Obj;
typedef struct Unk_80049AC0_Mgr {
    u8 pad_00[0x48];
    void (*unk48)(void *);
} Unk_80049AC0_Mgr;
typedef struct Unk_80049AC0_Vtbl {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32);
    u8 pad_18[0x110 - 0x18];
    void (*unk110)(void *, s32);
} Unk_80049AC0_Vtbl;
typedef struct Unk_80049AC0_Obj {
    Unk_80049AC0_Vtbl *unk0;
} Unk_80049AC0_Obj;
typedef struct Unk_80049AC0_Sub {
    u8 pad_00[0x4];
    s32 unk4;
} Unk_80049AC0_Sub;
typedef struct Unk_80049AC0 {
    u8 pad_00[0xC];
    Unk_80049AC0_Sub *unkC;
    s32 unk10;
    u8 pad_14[0x38 - 0x14];
    Unk_80049AC0_Obj *unk38;
} Unk_80049AC0;
void func_8004D1D0(void *arg0, void (*arg1)(), void *arg2);
typedef struct Unk_8004A19C_Obj { u8 pad_00[0x8]; void (*unk8)(void *); u8 pad_0C[0x40 - 0xC]; void (*unk40)(void *); } Unk_8004A19C_Obj;
typedef struct Unk_8004A19C { Unk_8004A19C_Obj *unk0; u8 pad_04[0x30 - 0x4]; s32 unk30; void *unk34; } Unk_8004A19C;
typedef struct Unk_8004A324_8004A19C {
    u8 pad[0xC];
    void (*unkC)(void *);
    u8 pad_10[0x38];
    void (*unk48)(s32);
    u8 pad_4C[0x14];
    void (*unk60)(void *, s32);
} Unk_8004A324_8004A19C;
void *func_8002C480(s32 arg0);
typedef struct Unk_8004D1D0 {
    u8 pad_00[0x10];
    s32 *u10;
} Unk_8004D1D0;

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_800494B4);

Unk_800861D4 *func_800494BC(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 14;
    }
    return D_800861D4;
}

Unk_800861D4 *func_800494D8(s32 arg0) {
    return &func_800494BC(NULL)[arg0];
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004950C);

s16 *func_800495B8(s32 arg0, s8 *arg1) {
    return D_80086590[arg0] + arg1[1] * D_800861D4[arg0].unk_0 + arg1[0];
}

s32 func_80049608(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x50);
    if (temp_v0 != 0) {
        func_8004A060()->unk8(temp_v0, arg0, arg1, arg2);
        return temp_v0;
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/game/800494B4", D_800113EC);

INCLUDE_RODATA("asm/nonmatchings/game/800494B4", D_800113F8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049684);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049830);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049958);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049A14);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049A1C);

void func_80049AC0(Unk_80049AC0 *arg0) {
    Unk_80049AC0_Obj *temp_s0;

    temp_s0 = arg0->unk38;
    ((Unk_80049AC0_Mgr *)func_8004A4B8())->unk48(arg0);
    temp_s0->unk0->unk110(temp_s0, 0);
    temp_s0->unk0->unk14(temp_s0, arg0->unkC->unk4);
    temp_s0->unk0->unk14(temp_s0, arg0->unk10);
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049B54);

void func_80049C50(Unk_80049C50 *arg0) {
    Unk_80049C50_Obj *temp_s0;

    temp_s0 = arg0->unk18;
    temp_s0->unk0->unk90(temp_s0);
    temp_s0->unk0->unk74(temp_s0);
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049CA8);

void func_80049E20(Unk_80049E20 *arg0, s32 arg1) {
    void *temp;

    temp = func_80052B70(arg0->unk34, arg0->unk40, arg0->unk44, arg0->unk48, arg1);
    arg0->unk4C = temp;
    arg0->unk0->unk10(arg0, temp);
    arg0->unk4C->unk0->unk44(arg0->unk4C, arg0->unkC, arg0->unk38);
    arg0->unk3C = 2;
}

void func_80049EA4(void) {
}

void func_80049EAC(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049EB4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A060);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A070);

s32 func_8004A130(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x38);
    if (temp_v0 != 0) {
        func_8004A4B8()->unk8(temp_v0, arg0, arg1);
        return temp_v0;
    }
    return 0;
}

void func_8004A19C(Unk_8004A19C *arg0, s32 arg1, void *arg2) {
    ((Unk_8004A19C_Obj *)((Unk_8004A324_8004A19C *)func_8003E5C8()))->unk8(arg0);
    arg0->unk0 = (Unk_8004A19C_Obj *)((Unk_8004A130 *)func_8004A4B8());
    if (arg1 != 0) {
        arg0->unk34 = func_8002C480(arg1);
    } else {
        arg0->unk34 = arg2;
    }
    arg0->unk30 = arg1;
    arg0->unk0->unk40(arg0);
}

void func_8004A228(Unk_8004A228 *arg0) {
    if (arg0->unk30 != 0) {
        Unk_8004A228_Obj *obj = arg0->unk34;
        obj->unk0->unk4(obj);
    }
    func_8003E5C8()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A294);

s32 func_8004A2C4(Unk_8004A2C4 *arg0, s32 arg1, s32 arg2) {
    arg0->u28 = 0;
    ((Unk_8004A2C4_Obj *)func_8003E5C8())->unk44(arg0, arg1, arg2);
    return arg0->u28;
}

void func_8004A324(s32 arg0) {
    func_8003E5C8()->unk48(arg0);
}

void func_8004A35C(void) {
}

void func_8004A364(Unk_8004A364 *arg0, s32 arg1, s32 arg2) {
    func_8003E5C8()->unk5C(arg0, arg1, arg2);
    if ((u32) arg0->unk1C > (u32) arg0->unk2C) {
        arg0->unk0->unk60(arg0, 4);
    }
}

void func_8004A3EC(Unk_8004A3EC *arg0, s32 arg1) {
    func_8003E5C8()->unk60(arg0, arg1);
    if (arg1 == 4) {
        arg0->unk28 = 1;
        arg0->unk0->unk7C(arg0);
    }
}

void func_8004A458(Unk_8004A458 *arg0, s32 arg1) {
    arg0->u2C = arg1;
    if (arg1 >= 0) {
        arg0->u2C = arg1 * 20;
    }
}

void func_8004A478(Unk_8004A478 *arg0, s32 arg1) {
    Unk_8004A478_obj *obj = arg0->unk34;
    if (obj != NULL) {
        obj->unk0->unk80(obj, arg1, 0x7F, 0x7F);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A4B8);

s32 func_8004A4C8(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x1E8);
    if (temp_s0 != 0) {
        func_8004D244()->unk8(temp_s0, arg0, arg1);
        return temp_s0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A534);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A7C0);

void func_8004A984(void **arg0, s32 **arg1, s32 arg2) {
    ((Unk_8004A984_Mgr *)func_8001E57C())->unk38(arg0, arg1, arg2);
    if ((**arg1 & 0xF) == 1) {
        ((Unk_8004A984_Obj *)*arg0)->unk100(arg0, arg1, arg2);
    }
}

void func_8004AA10(Unk_8004AA10 *arg0) {
    arg0->unk68 = 0;
    arg0->unkE8 = 0;
    arg0->unk88 = 0;
    arg0->unk0->unkDC(arg0, D_8008A980);
    arg0->unk1CC = -1;
    arg0->unk1D0 = -1;
    arg0->unk1D4 = -1;
    arg0->unk1D8 = -1;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AA6C);

void func_8004AB24(Unk_8004B57C *arg0) {
    if (arg0->unk70 != 0) {
        arg0->unk0->unkF4(arg0);
        arg0->unk0->unk13C(arg0);
    }
}

void func_8004AB88(Unk_8004AB88 *arg0, u8 **arg1) {
    if (**arg1 == 0x34) {
        arg0->unk0->unkD0(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ABD0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ACF8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ADC4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ADD0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ADD8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AEA4);

void func_8004AFE0(Unk_8004AFE0 *arg0, s8 *arg1, s32 arg2) {
    arg0->u7C = arg1[2] - 1;
    arg0->u7E = arg1[3] - 1;
    arg0->u80 = arg2;
    arg0->u84 = arg2;
    func_8004C93C();
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B030);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B100);

void func_8004B2D4(Unk_8004B2D4 *arg0) {
    if ((arg0 != NULL) && (arg0->unk36 & 0x80)) {
        arg0->unk0->unk38(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B31C);

void func_8004B324(void) {
}

void func_8004B32C(Unk_8004B32C *arg0, s32 arg1) {
    arg0->u74 = arg1;
    arg0->u7A = arg1 >> 11;
    arg0->u78 = arg1 >> 12;
}

void func_8004B344(Unk_8004B344 *arg0, s32 arg1) {
    arg0->unk0->unk40(arg0);
    arg0->unk68 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B38C);

void func_8004B418(Unk_8004B418 *arg0, s32 *arg1, void *arg2) {
    s32 sp18[3];
    func_8004B44C(arg1, sp18, arg0->u68, arg0->u54, arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B44C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B570);

void func_8004B57C(Unk_8004B57C *arg0) {
    arg0->unk0->unkC0(arg0);
    arg0->unk70 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B5BC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B700);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B930);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BA40);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BB3C);

s32 func_8004BCE0(Unk_8004BCE0 *arg0) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (arg0->unkEC[i].unk0 != 0) {
            count++;
        }
    }
    return count;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BD14);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BE54);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C0AC);

void *func_8004C158(Unk_8004C158 *arg0, s32 arg1, s32 *arg2) {
    s32 temp_v1 = arg0->unk6C->unk14 + 0x18;

    if (arg2 != NULL) {
        *arg2 = temp_v1;
    }
    if (arg1 == 0 || arg0->unk0->unk110(arg0, arg1, temp_v1) == 0) {
        return arg0->unkBC;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C1C0);

void func_8004C368(Unk_8004C3F0 *arg0, u8 *arg1, s32 arg2) {
    arg1[0] = arg2 % arg0->u68->unk_0;
    arg1[1] = arg2 / arg0->u68->unk_0;
}

Unk_8004C3F0_A *func_8004C3F0(Unk_8004C3F0 *arg0, u8 *arg1) {
    func_8004C368(arg0, arg1, arg0->u1BC->u4->u30);
    return arg0->u1BC;
}

Slot *func_8004C434(Owner *arg0, s32 arg1) {
    s32 i;
    Slot *s;
    for (i = 0; i < 7; i++) {
        s = &arg0->slots[i];
        if (s->obj->id == arg1) {
            return s;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C470);

s32 func_8004C588(Owner *arg0, s32 arg1) {
    s32 found = 0;
    s32 i;
    Slot *s;
    for (i = 0; i < 7; i++) {
        s = &arg0->slots[i];
        if (s->obj->id == arg1) {
            found = i;
            break;
        }
    }
    return found;
}

s32 func_8004C5D0(Unk_8004C5D0 *arg0, s32 arg1) {
    s32 i;
    Unk_8004C5D0_Slot *slot;

    for (i = 0; i < 7; i++) {
        slot = &arg0->slots[i];
        if (slot->obj->u30 == arg1 && slot->obj->u2C != 0) {
            return i;
        }
    }
    return -1;
}

void func_8004C620(Unk_8004C620 *arg0) {
    s32 temp_s1;

    if (arg0->unk1B8 != 0) {
        temp_s1 = arg0->unk78 * 2;
        func_8004CE24(arg0, 0);
        if (arg0->unk68->unk_4 == 0) {
            func_8004C6A8(arg0, temp_s1, arg0->unk7A);
        } else {
            func_8004CC74(arg0);
        }
        func_8004CE24(arg0, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C6A8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C93C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CAF0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CC74);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CD38);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CDA4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CE24);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CFA8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CFB0);

void func_8004CFB8(S *arg0, s32 arg1, s32 arg2) {
    T *p;
    if (arg1 > 0) {
        p = &D_8008699C;
        if (arg2 != 0) {
            arg0->u1E4 = &D_800869A8;
        } else {
            arg0->u1E4 = p;
        }
    } else {
        p = &D_800869B4;
        if (arg2 != 0) {
            p = &D_800869C0;
        }
        arg0->u1E4 = p;
    }
    arg0->u1E0 = arg0->u1E4->u6 * (arg1 < 0 ? ~arg1 + 1 : arg1);
}

void func_8004D028(Unk_8004D088 *arg0) {
    if (arg0->unk1E0 > 0) {
        func_8004D140(arg0, func_8004D0D0, 0);
        if (--arg0->unk1E0 == 0) {
            arg0->unk1E0 = -1;
        }
    }
}

void func_8004D088(Unk_8004D088 *arg0) {
    if (arg0->unk1E0 != 0) {
        func_8004D140(arg0, func_8004D108, 0);
        arg0->unk1E0 = 0;
    }
}

void func_8004D0D0(Unk_8004D0D0_Arg0 *arg0, Unk_8004D0D0 *arg1) {
    arg1->unk0->unk48(arg1, 0, arg0->unk1E4);
}

void func_8004D108(s32 arg0, Unk_8004D108 *arg1) {
    arg1->unk0->unk48(arg1, 1, &D_800869CC);
}

void func_8004D140(void *arg0, void (*arg1)(), void (*arg2)(void *, void *)) {
    s32 i;
    u8 *entry;

    for (i = 0; i < 7; i++) {
        entry = (u8 *)arg0 + 0xEC + i * 0x1C;
        if (arg2 != NULL) {
            arg2(arg0, entry);
        }
        func_8004D1D0(arg0, arg1, entry);
    }
}

void func_8004D1D0(void *arg0, void (*arg1)(), void *arg2) {
    s32 *p;
    s32 *end;

    end = ((Unk_8004D1D0 *)arg2)->u10 + 0x19A;
    for (p = ((Unk_8004D1D0 *)arg2)->u10; p < end; p++) {
        arg1(arg0, *p);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D244);

s32 func_8004D254(void) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0xDC);
    if (temp_v0 != 0) {
        func_8004D37C()->unk8(temp_v0);
        return temp_v0;
    }
    return 0;
}

void func_8004D2A4(void **arg0) {
    Unk_8004D2A4 *temp_v0;

    func_8003F24C()->unk8(arg0);
    temp_v0 = func_8004D37C();
    *arg0 = temp_v0;
    temp_v0->unk40(arg0);
}

void func_8004D2F8(void) {
}

void func_8004D300(Unk_8004D300 *arg0) {
    if ((arg0->unk10 != 0) && (arg0->unk70 != 0)) {
        func_8003F24C()->unk9C(arg0);
    }
}

void func_8004D35C(void) {
}

void func_8004D364(void) {
}

void func_8004D36C(void) {
}

void func_8004D374(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D37C);

s32 func_8004D38C(void) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x3C);
    if (temp_v0 != 0) {
        ((Unk_8004D38C *)func_8004D508())->unk8(temp_v0);
        return temp_v0;
    }
    return 0;
}

void func_8004D3DC(Unk_8004D3DC *arg0) {
    func_8001E57C()->unk8(arg0);
    arg0->unk0 = func_8004D508();
    arg0->unk34 = 0;
    arg0->unk36 = 0;
    arg0->unk38 = 0;
}

void func_8004D42C(void) {
}

void func_8004D434(Unk_8004D434 *arg0, u8 **arg1) {
    if (**arg1 == 0x34) {
        arg0->unk0->unkB8(arg0);
    }
}

void func_8004D47C(void **arg0, void *arg1, s32 arg2) {
    ((Unk_8004D47C_Mgr *)func_8001E57C())->unk9C(arg0, arg1, arg2);
    if (arg2 < 9) {
        if (arg2 >= 5) {
            ((Unk_8004D47C_Obj *)*arg0)->unkA0(arg0, arg1, arg2);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D500);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D508);

s32 func_8004D518(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0xC4);
    if (temp_v0 != 0) {
        func_8004E2D0()->unk8(temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

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
void *func_8003DFBC(void);
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
    struct Unk_8003E770 *unkC;
    struct Unk_8003E770 *unk10;
    u8 pad_14[0x30 - 0x14];
    s32 unk30;
};
typedef struct Unk_8003E874_Vtbl {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    void (*unkC)(void *);
    void (*unk10)(void *, void *);
    u8 pad_14[0x4];
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
void *func_8003E5C8(void);
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
    s32 *unk60;
    void ***unk64;
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
typedef struct Unk_8003DE30_Vtbl {
    u8 pad_00[0x11C];
    void (*unk11C)(void *, s32, s32);
} Unk_8003DE30_Vtbl;
typedef struct Unk_8003DE30 {
    Unk_8003DE30_Vtbl *unk0;
    u8 pad_04[0x58 - 0x04];
    s32 unk58;
    s32 *unk5C;
    s32 *unk60;
} Unk_8003DE30;
struct Unk_8003C858;
typedef struct Unk_8003C858_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(struct Unk_8003C858 *, s32);
    u8 pad_64[0x70 - 0x64];
    void (*unk70)(struct Unk_8003C858 *, s32);
} Unk_8003C858_Vtbl;
struct Unk_8003C858 {
    Unk_8003C858_Vtbl *unk0;
    u8 pad_04[0x3C - 0x04];
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    s32 unk4C;
};
typedef struct Unk_8003CA1C_Vtbl {
    u8 pad_00[0x94];
    void (*unk94)(void *, void *, s32);
    u8 pad_98[0x108 - 0x98];
    void (*unk108)(void *, void *, s32);
} Unk_8003CA1C_Vtbl;
typedef struct Unk_8003CA1C_Sub {
    u8 pad_00[0xC];
    s32 unkC;
    u8 pad_10[0x24 - 0x10];
    s32 *unk24;
} Unk_8003CA1C_Sub;
typedef struct Unk_8003CA1C {
    Unk_8003CA1C_Vtbl *unk0;
    u8 pad_04[0x4C - 0x04];
    Unk_8003CA1C_Sub *unk4C;
    u8 pad_50[0x58 - 0x50];
    s32 unk58;
} Unk_8003CA1C;
struct Unk_8003BE94 {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32, s32, s32);
};
typedef struct Unk_8003DFDC_Obj {
    u8 pad_00[0x40];
    void (*unk40)(void *);
} Unk_8003DFDC_Obj;
struct Unk_8003E770;
struct Unk_8003E770 {
    s32 *unk0;
    u8 pad_04[0x14 - 0x04];
    s32 unk14;
};
typedef struct Unk_8003F1A8_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x4C - 0x8];
    void (*unk4C)(void *, s32, s32 *);
} Unk_8003F1A8_Vtbl;
typedef struct Unk_8003F1A8_Obj {
    Unk_8003F1A8_Vtbl *unk0;
} Unk_8003F1A8_Obj;
struct Unk_8003F1A8 {
    u8 pad_00[0x10];
    s32 unk10;
    u8 pad_14[0xAC - 0x14];
    s32 unkAC;
    Unk_8003F1A8_Obj *unkB0;
};
extern s32 D_8008A904;
typedef struct Unk_8003E418_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *);
    void (*unk48)(void *);
} Unk_8003E418_Vtbl;
typedef struct Unk_8003E418_Obj {
    Unk_8003E418_Vtbl *unk0;
} Unk_8003E418_Obj;
typedef struct Unk_8003E418_Link {
    u8 pad_00[0x4];
    Unk_8003E418_Obj *unk4;
} Unk_8003E418_Link;
struct Unk_8003E418 {
    u8 pad_00[0xC];
    Unk_8003E418_Link *unkC;
    Unk_8003E418_Obj *unk10;
};
typedef struct Unk_8003B854_Obj {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32, s32, s32, s32);
} Unk_8003B854_Obj;
Unk_8003B854_Obj *func_8003BE84(void);
typedef struct Unk_8003C48C_Vtbl {
    u8 pad_00[0x74];
    void (*unk74)(void *, s32);
    void (*unk78)(void *, s32);
    void (*unk7C)(void *, s32);
    void (*unk80)(void *, s32);
    void (*unk84)(void *, s32);
} Unk_8003C48C_Vtbl;
struct Unk_8003C48C {
    Unk_8003C48C_Vtbl *unk0;
    u8 pad_04[0x3C - 0x04];
    s32 unk3C;
};
typedef struct Unk_8003D980_Vtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *, s32);
} Unk_8003D980_Vtbl;
typedef struct Unk_8003D980_Obj {
    Unk_8003D980_Vtbl *unk0;
} Unk_8003D980_Obj;
typedef struct Unk_8003D3B0_Vtbl {
    u8 pad_00[0xF0];
    void (*unkF0)(void *, s32, s32);
} Unk_8003D3B0_Vtbl;
typedef struct Unk_8003D3B0_Sub {
    u8 pad_00[0x18];
    s32 *unk18;
} Unk_8003D3B0_Sub;
struct Unk_8003D3B0 {
    Unk_8003D3B0_Vtbl *unk0;
    u8 pad_04[0x4C - 0x04];
    Unk_8003D3B0_Sub *unk4C;
    s32 unk50;
    u8 pad_54[0x58 - 0x54];
    s32 unk58;
};
typedef struct Unk_8003EC2C_Pair {
    s16 unk0;
    s16 unk2;
} Unk_8003EC2C_Pair;
struct Unk_8003EC2C {
    u8 pad_00[0x10];
    s32 unk10;
    u8 pad_14[0x2C - 0x14];
    s32 unk2C;
};
typedef struct Unk_8003CD48_Vtbl {
    u8 pad_00[0xE4];
    void (*unkE4)(void *, void *);
} Unk_8003CD48_Vtbl;
typedef struct Unk_8003CD48_ObjVtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *, s32, void *);
} Unk_8003CD48_ObjVtbl;
typedef struct Unk_8003CD48_Obj {
    Unk_8003CD48_ObjVtbl *unk0;
} Unk_8003CD48_Obj;
struct Unk_8003CD48 {
    Unk_8003CD48_Vtbl *unk0;
    u8 pad_04[0x1C - 0x04];
    s32 unk1C;
    u8 pad_20[0x78 - 0x20];
    Unk_8003CD48_Obj *unk78;
    u8 pad_7C[0x84 - 0x7C];
    s32 unk84;
};
struct Unk_8003E7F4 {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
    u8 pad_14[0x30 - 0x14];
    s32 unk30;
};
typedef struct Unk_8003E7F4_vt {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32 **);
} Unk_8003E7F4_vt;
s32 func_8001CA94(void);
void *func_8003FDB0(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_8008A90C;
typedef struct Unk_8003E628_Vtbl {
    u8 pad_00[0x40];
    void (*unk40)(void *);
} Unk_8003E628_Vtbl;
typedef struct Unk_8003E628_ObjVtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *, s32, s32 *);
} Unk_8003E628_ObjVtbl;
typedef struct Unk_8003E628_Obj {
    Unk_8003E628_ObjVtbl *unk0;
} Unk_8003E628_Obj;
struct Unk_8003E628 {
    Unk_8003E628_Vtbl *unk0;
    u8 pad_04[0xC - 0x4];
    s32 unkC;
    s32 unk10;
    u8 pad_14[0xAC - 0x14];
    s32 unkAC;
    Unk_8003E628_Obj *unkB0;
};
typedef struct Unk_8003E6CC_ObjVtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
} Unk_8003E6CC_ObjVtbl;
typedef struct Unk_8003E6CC_Obj {
    Unk_8003E6CC_ObjVtbl *unk0;
} Unk_8003E6CC_Obj;
typedef struct Unk_8003E6CC_Vtbl {
    u8 pad_00[0x74];
    void (*unk74)(void *);
    u8 pad_78[0x90 - 0x78];
    void (*unk90)(void);
    u8 pad_94[0xA8 - 0x94];
    void (*unkA8)(void *, s32);
} Unk_8003E6CC_Vtbl;
struct Unk_8003E6CC {
    Unk_8003E6CC_Vtbl *unk0;
    u8 pad_04[0xAC - 0x04];
    Unk_8003E6CC_Obj *unkAC;
};
typedef struct Unk_8003CC2C_Vtbl {
    u8 pad_00[0xE4];
    void (*unkE4)(void *, void *);
} Unk_8003CC2C_Vtbl;
typedef struct Unk_8003CC2C_ObjVtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *, s32, void *);
} Unk_8003CC2C_ObjVtbl;
typedef struct Unk_8003CC2C_Obj {
    Unk_8003CC2C_ObjVtbl *unk0;
} Unk_8003CC2C_Obj;
struct Unk_8003CC2C {
    Unk_8003CC2C_Vtbl *unk0;
    u8 pad_04[0x1C - 0x04];
    s32 unk1C;
    u8 pad_20[0x78 - 0x20];
    Unk_8003CC2C_Obj *unk78;
    u8 pad_7C[0x84 - 0x7C];
    s32 unk84;
    u8 pad_88[0x90 - 0x88];
    u8 unk90;
    u8 unk91;
    u8 unk92;
};
struct Unk_8003BB5C_Ret {
    u8 pad_00[0x5C];
    void (*unk5C)(void *, s32, s32);
};
typedef struct Unk_8003BB5C_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_8003BB5C_Vtbl;
typedef struct Unk_8003BB5C_Sub_Vtbl {
    u8 pad_00[0x48];
    s32 (*unk48)(void *);
} Unk_8003BB5C_Sub_Vtbl;
typedef struct Unk_8003BB5C_Obj {
    Unk_8003BB5C_Sub_Vtbl *unk0;
} Unk_8003BB5C_Obj;
struct Unk_8003BB5C {
    Unk_8003BB5C_Vtbl *unk0;
    u8 pad_04[0xA4 - 0x04];
    s32 unkA4;
    u8 pad_A8[0xB4 - 0xA8];
    Unk_8003BB5C_Obj *unkB4;
    u8 pad_B8[0xD8 - 0xB8];
    s32 unkD8;
};
typedef struct Unk_8003EACC_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void);
    u8 pad_14[0x78 - 0x14];
    void (*unk78)(void *, s32);
    void (*unk7C)(void *, s32);
    void (*unk80)(void *, void *);
} Unk_8003EACC_Vtbl;
struct Unk_8003EACC {
    Unk_8003EACC_Vtbl *unk0;
    u8 pad_04[0x10 - 0x04];
    s32 unk10;
};
extern s32 D_8008A8F4;
void GsSetRefView2(void *);
typedef struct Unk_8003C3D0_Vtbl {
    u8 pad_00[0x50];
    void (*unk50)(void *);
    u8 pad_54[0x20];
    void (*unk74)(void *);
    void (*unk78)(void *, void *, s32);
    u8 pad_7C[0x14];
    void (*unk90)(void *);
} Unk_8003C3D0_Vtbl;
typedef struct Unk_8003C3D0_Obj {
    Unk_8003C3D0_Vtbl *unk0;
} Unk_8003C3D0_Obj;
struct Unk_8003C3D0 {
    u8 pad_00[0xC];
    Unk_8003C3D0_Obj **unkC;
    u8 pad_10[0x8];
    Unk_8003C3D0_Obj *unk18;
    u8 pad_1C[0x18];
    s32 unk34;
    u8 pad_38[0x40];
    Unk_8003C3D0_Obj *unk78;
};
typedef struct Unk_8003C11C_Vtbl {
    u8 pad_00[0x6C];
    void (*unk6C)(void *, s32);
    u8 pad_70[0x9C - 0x70];
    void (*unk9C)(void *, s32);
    void (*unkA0)(void *, s32);
    void (*unkA4)(void *, void *, void *, void *);
} Unk_8003C11C_Vtbl;
typedef struct Unk_8003C11C {
    Unk_8003C11C_Vtbl *unk0;
    u8 pad_04[0x28 - 0x04];
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    u8 pad_38[0x3C - 0x38];
    s32 unk3C;
    u8 pad_40[0x84 - 0x40];
    s32 unk84;
    u8 pad_88[0x9C - 0x88];
    s32 unk9C;
    s32 unkA0;
} Unk_8003C11C;
extern u8 D_8006E860[];
typedef struct Unk_8003DA10_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0x70 - 0x64];
    void (*unk70)(void *, s32);
    u8 pad_74[0x100 - 0x74];
    void (*unk100)(void *, s32, s32);
} Unk_8003DA10_Vtbl;
typedef struct Unk_8003DA10_Sub {
    u8 pad_00[0x24];
    s32 *unk24;
} Unk_8003DA10_Sub;
typedef struct Unk_8003DA10_ElemVtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0xB8 - 0x64];
    void (*unkB8)(void *, s32);
} Unk_8003DA10_ElemVtbl;
typedef struct Unk_8003DA10_Elem {
    Unk_8003DA10_ElemVtbl *unk0;
} Unk_8003DA10_Elem;
typedef struct Unk_8003DA10 {
    Unk_8003DA10_Vtbl *unk0;
    u8 pad_04[0x14 - 0x04];
    s32 unk14;
    u8 pad_18[0x3C - 0x18];
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    Unk_8003DA10_Sub *unk4C;
    u8 pad_50[0x58 - 0x50];
    s32 unk58;
    u8 pad_5C[0x60 - 0x5C];
    s32 *unk60;
    Unk_8003DA10_Elem ***unk64;
} Unk_8003DA10;
typedef struct Unk_8003E030_Ret {
    u8 pad_00[0x38];
    void (*unk38)(void *, s32 **, s32);
} Unk_8003E030_Ret;
typedef struct Unk_8003E030_Vt {
    u8 pad_00[0x54];
    void (*unk54)(void *, s32 **, s32);
    void (*unk58)(void *, s32 **, s32);
    void (*unk5C)(void *, s32 **, s32);
} Unk_8003E030_Vt;
typedef struct Unk_8003E030 {
    Unk_8003E030_Vt *vt;
} Unk_8003E030;
typedef struct Unk_8003BC14_Sub_Vtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *);
} Unk_8003BC14_Sub_Vtbl;
typedef struct Unk_8003BC14_Sub {
    Unk_8003BC14_Sub_Vtbl *unk0;
} Unk_8003BC14_Sub;
typedef struct Unk_8003BC14_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0x94 - 0x64];
    void (*unk94)(void *);
} Unk_8003BC14_Vtbl;
typedef struct Unk_8003BC14 {
    Unk_8003BC14_Vtbl *unk0;
    u8 pad_04[0xB4 - 0x04];
    Unk_8003BC14_Sub *unkB4;
    u8 pad_B8[0xD4 - 0xB8];
    s32 unkD4;
    s32 unkD8;
} Unk_8003BC14;
typedef struct Unk_8003D4DC_ElemVtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *, s32);
} Unk_8003D4DC_ElemVtbl;
typedef struct Unk_8003D4DC_Elem {
    Unk_8003D4DC_ElemVtbl *unk0;
} Unk_8003D4DC_Elem;
typedef struct Unk_8003D4DC_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0x70 - 0x64];
    void (*unk70)(void *, s32);
} Unk_8003D4DC_Vtbl;
struct Unk_8003D4DC {
    Unk_8003D4DC_Vtbl *unk0;
    u8 pad_04[0x4C - 0x04];
    s32 unk4C;
    u8 pad_50[0x54 - 0x50];
    Unk_8003D4DC_Elem **unk54;
    s32 unk58;
};
void *func_8003DFCC(void);
s32 func_80045438(s32, s32, s32);
typedef struct Unk_8003B8E4_Vt {
    u8 pad_00[0x40];
    void (*unk40)(void *);
} Unk_8003B8E4_Vt;
typedef struct Unk_8003B8E4_Src {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8003B8E4_Src;
typedef struct Unk_8003B8E4 {
    Unk_8003B8E4_Vt *unk0;
    u8 pad_04[0xA8 - 0x04];
    Unk_8003B8E4_Src unkA8;
    s32 unkB4;
    s32 unkB8;
} Unk_8003B8E4;
struct Unk_8003B8E4_Ret {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32, s32);
};
typedef struct Unk_8003BF10_Vtbl {
    u8 pad_00[0x40];
    void (*unk40)(void *);
    u8 pad_44[0xD4 - 0x44];
    void (*unkD4)(void *, s32, s32);
    void (*unkD8)(void *, void *);
} Unk_8003BF10_Vtbl;
struct Unk_8003BF10 {
    Unk_8003BF10_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    s32 unk48;
    u8 pad_4C[0x78 - 0x4C];
    s32 unk78;
    s32 unk7C;
    s32 unk80;
};
struct Unk_8003BF10_Ret {
    u8 pad_00[0x8];
    void (*unk8)(void *);
};
void *func_8002C480(s32 arg0);
s32 func_80044F30(s32 arg0);
s32 func_80044CD4(s32 arg0, s32 arg1);
s32 func_800441B4(s32 arg0, s32 arg1);
typedef struct Unk_8003BAB4_Vtbl {
    u8 pad_00[0x40];
    s32 (*unk40)(void *, s32, s32, s32, s32);
    u8 pad_44[0x6C - 0x44];
    void (*unk6C)(void *, s32);
} Unk_8003BAB4_Vtbl;
typedef struct Unk_8003BAB4_Obj {
    Unk_8003BAB4_Vtbl *unk0;
} Unk_8003BAB4_Obj;
struct Unk_8003BAB4 {
    Unk_8003BAB4_Vtbl *unk0;
    u8 pad_04[0xA4 - 0x04];
    s32 unkA4;
    u8 pad_A8[0xB4 - 0xA8];
    Unk_8003BAB4_Obj *unkB4;
    s32 unkB8;
    s32 unkBC;
    s32 unkC0;
    s32 unkC4;
    s32 unkC8;
};
struct Unk_8003BAB4_Callee {
    u8 pad_00[0x4C];
    void (*unk4C)(void *);
};
typedef struct Unk_8003E8B8_Ret {
    u8 pad_00[0x38];
    void (*unk38)(void *, void *, s32);
} Unk_8003E8B8_Ret;
typedef struct Unk_8003E8B8_Vtbl {
    u8 pad_00[0x94];
    void (*unk94)(void *, void *, s32);
    void (*unk98)(void *, void *, s32);
} Unk_8003E8B8_Vtbl;
typedef struct Unk_8003E8B8 {
    Unk_8003E8B8_Vtbl *unk0;
} Unk_8003E8B8;
typedef struct Unk_8003CDE0_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x5C - 0x08];
    void (*unk5C)(void *);
    u8 pad_60[0x78 - 0x60];
    void (*unk78)(void *);
} Unk_8003CDE0_Vtbl;
struct Unk_8003CDE0_Obj {
    Unk_8003CDE0_Vtbl *unk0;
};
struct Unk_8003CDE0 {
    u8 pad_00[0x70];
    s32 unk70;
    struct Unk_8003CDE0_Obj *unk74;
};
extern s32 func_8003B39C(s32);
typedef struct Unk_8003D2CC_ObjVtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *, s32);
} Unk_8003D2CC_ObjVtbl;
typedef struct Unk_8003D2CC_Obj {
    Unk_8003D2CC_ObjVtbl *unk0;
} Unk_8003D2CC_Obj;
typedef struct Unk_8003D2CC_Sub {
    u8 pad_00[0x24];
    s32 *unk24;
} Unk_8003D2CC_Sub;
typedef struct Unk_8003D2CC_Vtbl {
    u8 pad_00[0x104];
    void (*unk104)(void *, s32);
} Unk_8003D2CC_Vtbl;
typedef struct Unk_8003D2CC {
    Unk_8003D2CC_Vtbl *unk0;
    u8 pad_04[0x4C - 0x04];
    Unk_8003D2CC_Sub *unk4C;
    s32 unk50;
    Unk_8003D2CC_Obj **unk54;
    s32 unk58;
} Unk_8003D2CC;
extern s32 strlen(u8 *);
extern s32 func_800408CC(s32, s32, s32);
struct Unk_8003D5CC {
    u8 pad_00[0x4];
    s32 unk4;
    u8 pad_08[0x18 - 0x08];
    s32 *unk18;
};
typedef struct Unk_8003C51C_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0xAC - 0x64];
    void (*unkAC)(void *);
    u8 pad_B0[0xC0 - 0xB0];
    void (*unkC0)(void *);
} Unk_8003C51C_Vtbl;
typedef struct Unk_8003C51C_Obj {
    Unk_8003C51C_Vtbl *unk0;
    u8 pad_04[0x1C - 0x04];
    s32 unk1C;
    s32 unk20;
    u8 pad_24[0x3C - 0x24];
    s32 unk3C;
    s32 unk40;
} Unk_8003C51C_Obj;
typedef struct Unk_8003C51C_Ret {
    u8 pad_00[0x5C];
    void (*unk5C)(void *, s32, s32);
} Unk_8003C51C_Ret;
typedef struct Unk_8003D050_Vtbl {
    u8 pad_00[0xFC];
    void (*unkFC)(void *);
} Unk_8003D050_Vtbl;
typedef struct Unk_8003D050_ObjVtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
} Unk_8003D050_ObjVtbl;
typedef struct Unk_8003D050_Obj {
    Unk_8003D050_ObjVtbl *unk0;
} Unk_8003D050_Obj;
typedef struct Unk_8003D050_Sub {
    s32 unk0;
    Unk_8003D050_Obj *unk4;
    u8 pad_08[0x24 - 0x08];
    s32 *unk24;
} Unk_8003D050_Sub;
struct Unk_8003D050 {
    Unk_8003D050_Vtbl *unk0;
    u8 pad_04[0x4C - 0x04];
    Unk_8003D050_Sub *unk4C;
    s32 unk50;
    Unk_8003D050_Obj **unk54;
    s32 unk58;
    s32 *unk5C;
    s32 *unk60;
    s32 *unk64;
    Unk_8003D050_Obj *unk68;
};
typedef struct Unk_8003C63C_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0x90 - 0x64];
    void (*unk90)(void *);
    void (*unk94)(void *);
    u8 pad_98[0xE4 - 0x98];
    void (*unkE4)(void *, void *);
    u8 pad_E8[0xF0 - 0xE8];
    void (*unkF0)(void *, s32, s32);
    u8 pad_F4[0x10C - 0xF4];
    void (*unk10C)(void *);
    void (*unk110)(void *);
} Unk_8003C63C_Vtbl;
typedef struct Unk_8003C63C_Sub {
    u8 pad_00[0x8];
    s32 unk8;
} Unk_8003C63C_Sub;
typedef struct Unk_8003C63C_Obj {
    Unk_8003C63C_Vtbl *unk0;
    u8 pad_04[0x1C - 0x04];
    s32 unk1C;
    s32 unk20;
    u8 pad_24[0x38 - 0x24];
    s32 unk38;
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    Unk_8003C63C_Sub *unk4C;
} Unk_8003C63C_Obj;
void ResetGraph(s32 mode);
void GsSortClear(u8 r, u8 g, u8 b, s32 ot);
void GsDrawOt(s32 ot);
typedef struct Unk_8003F04C_Vtbl {
    u8 pad_00[0x50];
    void (*unk50)(void *);
    s32 (*unk54)(void *);
} Unk_8003F04C_Vtbl;
typedef struct Unk_8003F04C_Obj {
    Unk_8003F04C_Vtbl *unk0;
} Unk_8003F04C_Obj;
struct Unk_8003F04C {
    u8 pad_00[0xC];
    Unk_8003F04C_Obj *unkC;
    u8 pad_10[0x58 - 0x10];
    u8 unk58;
    u8 unk59;
    u8 unk5A;
    u8 pad_5B[0x70 - 0x5B];
    s32 unk70;
    s32 unk74;
    s32 unk78[2];
    u8 pad_80[0xB4 - 0x80];
    void *unkB4;
    s32 unkB8;
};
typedef struct Unk_8003C008_Vtbl {
    u8 pad_00[0xDC];
    void (*unkDC)(void *);
} Unk_8003C008_Vtbl;
struct Unk_8003C008 {
    Unk_8003C008_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    Unk_8003B9DC_Obj *unk48;
    u8 pad_4C[0x70 - 0x4C];
    s32 unk70;
    Unk_8003B9DC_Obj *unk74;
    Unk_8003B9DC_Obj *unk78;
    Unk_8003B9DC_Obj *unk7C;
    Unk_8003B9DC_Obj *unk80;
};
void GsClearOt(s32, s32, void *);
typedef struct Unk_8003ECD0_Ot {
    s32 unk0;
    void *unk4;
} Unk_8003ECD0_Ot;
struct Unk_8003ECD0 {
    u8 pad_00[0x3C];
    s32 unk3C;
    u8 pad_40[0x44 - 0x40];
    s32 unk44;
    s32 unk48;
    u8 pad_4C[0x70 - 0x4C];
    s32 unk70;
    s32 unk74;
    Unk_8003ECD0_Ot *unk78;
    Unk_8003ECD0_Ot *unk7C;
    void *unk80;
    void *unk84;
    void *unk88;
    void *unk8C;
};
void *func_80042400(void);
void *func_80042694(void);
s32 func_8003E5D8(void);
typedef struct Unk_8003E10C_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
    u8 pad_14[0x48 - 0x14];
    void (*unk48)(void *);
    void (*unk4C)(void *, s32, s32, s32);
    u8 pad_50[0x60 - 0x50];
    void (*unk60)(void *, s32);
} Unk_8003E10C_Vtbl;
typedef struct Unk_8003E10C_Obj {
    Unk_8003E10C_Vtbl *unk0;
} Unk_8003E10C_Obj;
typedef struct Unk_8003E10C_Arg {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Unk_8003E10C_Arg;
typedef struct Unk_8003E10C {
    Unk_8003E10C_Vtbl *unk0;
    u8 pad_04[0x8];
    Unk_8003E10C_Arg *unkC;
    s32 unk10;
    Unk_8003E10C_Obj *unk14;
    Unk_8003E10C_Obj *unk18;
    u8 pad_1C[0x8];
    s32 unk24;
} Unk_8003E10C;
typedef struct Unk_8003EEC0_Vtbl {
    u8 pad_00[0xA0];
    void (*unkA0)(void *, void *);
} Unk_8003EEC0_Vtbl;
struct Unk_8003EEC0 {
    Unk_8003EEC0_Vtbl *unk0;
    u8 pad_04[0x10 - 0x04];
    struct Unk_8003F25C *unk10;
    u8 pad_14[0x30 - 0x14];
    s32 *unk30;
    u8 pad_34[0x3C - 0x34];
    s32 unk3C;
    s32 unk40;
    u8 pad_44[0x4C - 0x44];
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    u8 pad_58[0x5B - 0x58];
    u8 unk5B;
    u8 unk5C;
    u8 unk5D;
    u8 pad_5E[0x60 - 0x5E];
    s32 unk60;
    u8 pad_64[0x70 - 0x64];
    s32 unk70;
    s32 unk74;
    s32 unk78[4];
    s32 unk88[1];
    u8 pad_8C[0x98 - 0x8C];
    s32 unk98;
    u8 pad_9C[0xAC - 0x9C];
    void *unkAC;
};
struct Unk_8003F25C *func_8003F25C(struct Unk_8003F25C *);
void func_8003F28C(s32);
void func_8003FB0C(s32);
void func_8003FBE4(s32);
void GsSetLightMode(s32);
void SetFarColor(u8, u8, u8);
void SetFogNear(s32, s32);
typedef struct Unk_8003C238_Vtbl {
    u8 pad_00[0xE0];
    void (*unkE0)(void *, s32);
    void (*unkE4)(void *, void *);
} Unk_8003C238_Vtbl;
typedef struct Unk_8003C238_Vt18 {
    u8 pad_00[0x48];
    void (*unk48)(void *, s32);
    void (*unk4C)(void *, s32);
    void (*unk50)(void *, s32);
    u8 pad_54[0x70 - 0x54];
    void (*unk70)(void *, s32, void *, void *, s32);
    u8 pad_74[0x8C - 0x74];
    void (*unk8C)(void *);
} Unk_8003C238_Vt18;
typedef struct Unk_8003C238_Obj18 {
    Unk_8003C238_Vt18 *unk0;
} Unk_8003C238_Obj18;
typedef struct Unk_8003C238_Vt78 {
    u8 pad_00[0x4C];
    void (*unk4C)(void *, s32, s32);
    u8 pad_50[0xB8 - 0x50];
    void (*unkB8)(void *, s32, void *);
} Unk_8003C238_Vt78;
typedef struct Unk_8003C238_Obj78 {
    Unk_8003C238_Vt78 *unk0;
} Unk_8003C238_Obj78;
typedef struct Unk_8003C238_VtC {
    u8 pad_00[0x78];
    void (*unk78)(void *, void *, void *);
} Unk_8003C238_VtC;
typedef struct Unk_8003C238_ObjC {
    Unk_8003C238_VtC *unk0;
} Unk_8003C238_ObjC;
struct Unk_8003C238 {
    Unk_8003C238_Vtbl *unk0;
    u8 pad_04[0x0C - 0x04];
    Unk_8003C238_ObjC **unkC;
    u8 pad_10[0x14 - 0x10];
    s32 unk14;
    Unk_8003C238_Obj18 *unk18;
    u8 pad_1C[0x28 - 0x1C];
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad_34[0x38 - 0x34];
    s32 unk38;
    u8 pad_3C[0x74 - 0x3C];
    s32 unk74;
    Unk_8003C238_Obj78 *unk78;
    u8 pad_7C[0x88 - 0x7C];
    s32 unk88;
};
extern s32 D_8006E854[];
extern s32 D_8006E86C[];
typedef struct Unk_8003E280_Vtbl {
    u8 pad_00[0x4];
    void *(*unk4)(void *);
    u8 pad_08[0x14 - 0x08];
    void (*unk14)(void *, s32);
    u8 pad_18[0x50 - 0x18];
    void (*unk50)(void *);
} Unk_8003E280_Vtbl;
typedef struct Unk_8003E280_Obj {
    Unk_8003E280_Vtbl *unk0;
} Unk_8003E280_Obj;
typedef struct Unk_8003E280_Link {
    s32 unk0;
    s32 unk4;
    void *unk8;
    void *unkC;
    void *unk10;
} Unk_8003E280_Link;
struct Unk_8003E280 {
    Unk_8003E280_Vtbl *unk0;
    u8 pad_04[0xC - 0x4];
    Unk_8003E280_Link *unkC;
    Unk_8003E280_Obj *unk10;
    Unk_8003E280_Obj *unk14;
    Unk_8003E280_Obj *unk18;
    u8 pad_1C[0x24 - 0x1C];
    s32 unk24;
};
typedef struct Unk_8003E4B8_Vtbl {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
    u8 pad_34[0x64 - 0x34];
    void (*unk64)(void *);
    void (*unk68)(void *);
} Unk_8003E4B8_Vtbl;
struct Unk_8003E4B8 {
    Unk_8003E4B8_Vtbl *unk0;
    u8 pad_04[0x20 - 0x04];
    s32 unk20;
};
extern s32 D_8006E5F8[];
struct Unk_8003CAEC {
    u8 pad_00[0x9C];
    s32 unk9C;
    s32 unkA0;
};
struct Unk_8003CBB8 {
    u8 pad_00[0x84];
    s32 unk84;
};
struct Unk_8003D5C0 {
    u8 pad_00[0x58];
    s32 unk58;
};
extern s32 D_8006E730[];
struct Unk_8003E100 {
    u8 pad_00[0x1C];
    s32 unk1C;
    s32 unk20;
};
extern u8 D_8006E878[];
struct Unk_8003EA24 {
    u8 pad_00[0x3C];
    s32 unk3C;
};
struct Unk_8003EA64 {
    u8 pad_00[0x40];
    s32 unk40;
};
struct Unk_8003EA7C {
    u8 pad_00[0x54];
    s32 unk54;
};
struct Unk_8003EAC4 {
    u8 pad_00[0x60];
    s32 unk60;
};
struct Unk_8003F230 {
    u8 pad_00[0xB0];
    s32 unkB0;
};
struct Unk_8003F23C {
    u8 pad_00[0xB4];
    s32 unkB4;
};
struct Unk_8003F244 {
    u8 pad_00[0xB8];
    s32 unkB8;
};
extern struct Unk_8003E5D8 D_8006E8E4[];

s32 func_8003B854(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0xDC);
    if (temp_s0 != 0) {
        func_8003BE84()->unk8(temp_s0, arg0, arg1, arg2, arg3);
        return temp_s0;
    }
    return 0;
}

void func_8003B8E4(Unk_8003B8E4 *arg0, s32 arg1, s32 arg2, s32 arg3, Unk_8003B8E4_Src *arg4) {
    ((struct Unk_8003B8E4_Ret *)func_8003DFBC())->unk8(arg0, arg1, arg2, arg3);
    arg0->unk0 = (Unk_8003B8E4_Vt *)func_8003BE84();
    if (arg4 != NULL) {
        arg0->unkA8 = *arg4;
    } else {
        arg0->unkA8 = *(Unk_8003B8E4_Src *)func_8003DFCC();
    }
    arg0->unkB4 = func_80045438((s32)func_8003DFCC(), 0, 0);
    arg0->unkB8 = 0;
    arg0->unk0->unk40(arg0);
}

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

void func_8003BAB4(struct Unk_8003BAB4 *arg0) {
    Unk_8003BAB4_Obj *temp_a0;

    ((struct Unk_8003BAB4_Callee *)func_8003DFBC())->unk4C(arg0);
    temp_a0 = arg0->unkB4;
    arg0->unkA4 = 0;
    temp_a0->unk0->unk6C(temp_a0, arg0->unkC0);
    if (arg0->unkB4->unk0->unk40(arg0->unkB4, arg0->unkB8, arg0->unkBC, arg0->unkC4, arg0->unkC8) != 0) {
        arg0->unk0->unk6C(arg0, 0);
    }
}

void func_8003BB5C(struct Unk_8003BB5C *arg0, s32 arg1, s32 arg2) {
    Unk_8003BB5C_Obj *temp;
    s32 temp_v0;

    ((struct Unk_8003BB5C_Ret *)func_8003DFBC())->unk5C(arg0, arg1, arg2);
    if (arg0->unkA4 == 0) {
        temp = arg0->unkB4;
        temp_v0 = temp->unk0->unk48(temp);
        arg0->unkA4 = temp_v0;
        if ((temp_v0 != 0) && (arg0->unkD8 == 0)) {
            arg0->unk0->unk60(arg0, 7);
        }
    }
}

void func_8003BC14(Unk_8003BC14 *arg0, s32 arg1) {
    ((Unk_8003BC14_Vtbl *)func_8003DFBC())->unk60(arg0, arg1);
    switch (arg1) {
    case 5:
        arg0->unkD8 = 0;
        break;
    case 7:
        arg0->unkD8 = 1;
        break;
    case 8:
        if (arg0->unkD4 == 0) {
            arg0->unkB4->unk0->unk4C(arg0->unkB4);
        }
        break;
    case 0x12:
        arg0->unk0->unk94(arg0);
        break;
    }
}

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

void func_8003BE5C(struct Unk_8003BA38 *arg0, s32 arg1) {
    arg0->unkC4 = arg1;
}

void func_8003BE64(struct Unk_8003BA38 *arg0, s32 arg1) {
    arg0->unkC8 = arg1;
}

void func_8003BE6C(struct Unk_8003BA38 *arg0, s32 arg1) {
    arg0->unkCC = arg1;
}

void func_8003BE74(struct Unk_8003BA38 *arg0, s32 arg1) {
    arg0->unkD0 = arg1;
}

void func_8003BE7C(struct Unk_8003BA38 *arg0, s32 arg1) {
    arg0->unkD4 = arg1;
}

Unk_8003B854_Obj *func_8003BE84(void) {
    return (Unk_8003B854_Obj *) D_8006E5F8;
}

s32 func_8003BE94(s32 arg0, s32 arg1, s32 arg2) {
    s32 obj;

    obj = func_80017B34(0xA4);
    if (obj != 0) {
        ((struct Unk_8003BE94 *)func_8003DFBC())->unk8(obj, arg0, arg1, arg2);
        return obj;
    }
    return 0;
}

void func_8003BF10(struct Unk_8003BF10 *arg0, void *arg1, s32 arg2, s32 arg3) {
    void *temp;
    s32 v;
    s32 w;

    ((struct Unk_8003BF10_Ret *)func_8003E5C8())->unk8(arg0);
    temp = func_8003DFBC();
    arg0->unk0 = temp;
    ((Unk_8003BF10_Vtbl *)temp)->unkD8(arg0, arg1);
    if (arg2 != 0) {
        arg0->unk48 = (s32)func_8002C480(arg2);
    } else {
        arg0->unk48 = arg3;
    }
    arg0->unk44 = arg2;
    arg0->unk0->unkD4(arg0, 0, 0);
    v = func_80044F30(0);
    arg0->unk80 = v;
    w = func_80044CD4(0, v);
    arg0->unk7C = w;
    arg0->unk78 = func_800441B4(w, 1);
    arg0->unk0->unk40(arg0);
}

void func_8003C008(struct Unk_8003C008 *arg0) {
    arg0->unk78->unk0->unk4(arg0->unk78);
    arg0->unk7C->unk0->unk4(arg0->unk7C);
    arg0->unk80->unk0->unk4(arg0->unk80);
    if (arg0->unk44 != 0) {
        arg0->unk48->unk0->unk4(arg0->unk48);
    }
    if (arg0->unk70 != 0) {
        arg0->unk74->unk0->unk4(arg0->unk74);
    }
    arg0->unk0->unkDC(arg0);
    ((struct Unk_8003B9DC_Callee *)func_8003E5C8())->unkC(arg0);
}

void func_8003C11C(Unk_8003C11C *arg0) {
    Unk_8003C11C_Vtbl *temp_s1;

    temp_s1 = arg0->unk0;
    temp_s1->unk6C(arg0, -1);
    temp_s1->unkA4(arg0, D_8006E860, D_8006E860 + 3, D_8006E860 + 6);
    temp_s1->unk9C(arg0, 1);
    temp_s1->unkA0(arg0, 1);
    arg0->unk84 = 9;
    arg0->unk28 = 3;
    arg0->unk2C = 0x12C;
    arg0->unk30 = 0x40;
    arg0->unk9C = 0;
    arg0->unkA0 = 0;
    arg0->unk34 = 1;
    arg0->unk3C = 0;
}

s32 func_8003C1DC(Unk_8003C1DC *arg0, s32 arg1, s32 arg2) {
    ((Unk_8003C1DC_Obj *)func_8003E5C8())->unk44(arg0, arg1, arg2);
    return arg0->unk38;
}

void func_8003C238(struct Unk_8003C238 *arg0) {
    Unk_8003C238_Obj18 *temp_s2;
    Unk_8003C238_Vt18 *temp_s3;

    temp_s2 = arg0->unk18;
    temp_s3 = temp_s2->unk0;
    arg0->unk0->unkE0(arg0, arg0->unk14);
    arg0->unk78->unk0->unk4C(arg0->unk78, arg0->unk14, 0);
    if (arg0->unk88 != 0) {
        arg0->unk0->unkE4(arg0, (u8 *)arg0 + 0x90);
        arg0->unk78->unk0->unkB8(arg0->unk78, 1, (u8 *)arg0 + 0x90);
    }
    if (arg0->unk74 == 0) {
        (*arg0->unkC)->unk0->unk78(*arg0->unkC, (u8 *)arg0 + 0x90, D_8006E854);
    }
    (*arg0->unkC)->unk0->unk78(*arg0->unkC, (u8 *)arg0 + 0x90, 0);
    temp_s3->unk48(temp_s2, arg0->unk28);
    temp_s3->unk4C(temp_s2, arg0->unk2C);
    temp_s3->unk50(temp_s2, arg0->unk30);
    temp_s3->unk70(temp_s2, arg0->unk14, D_8006E86C, D_8006E86C, 0);
    temp_s3->unk8C(temp_s2);
    arg0->unk38 = 0;
}

void func_8003C3D0(struct Unk_8003C3D0 *arg0) {
    Unk_8003C3D0_Obj *temp_s0;
    Unk_8003C3D0_Obj *temp_a0;
    Unk_8003C3D0_Obj *temp_a0_2;

    temp_s0 = arg0->unk18;
    temp_s0->unk0->unk90(temp_s0);
    temp_s0->unk0->unk74(temp_s0);
    temp_a0 = arg0->unk78;
    temp_a0->unk0->unk50(temp_a0);
    if (arg0->unk34 != 0) {
        temp_a0_2 = *arg0->unkC;
        temp_a0_2->unk0->unk78(temp_a0_2, (u8 *)arg0 + 0x93, 0);
    }
}

void func_8003C48C(struct Unk_8003C48C *arg0, s32 arg1, s32 arg2) {
    Unk_8003C48C_Vtbl *vt = arg0->unk0;
    void (*fn)(void *, s32);

    if (arg0->unk3C != 0) {
        switch (arg2) {
        case 0x12:
            fn = vt->unk80;
            break;
        case 0x13:
            fn = vt->unk84;
            break;
        case 0x21:
            fn = vt->unk74;
            break;
        case 0x17:
            fn = vt->unk7C;
            break;
        case 0x19:
            fn = vt->unk78;
            break;
        default:
            return;
        }
        fn(arg0, arg1);
    }
}

void func_8003C51C(Unk_8003C51C_Obj *arg0, s32 arg1, s32 arg2) {
    Unk_8003C51C_Vtbl *vt = arg0->unk0;

    ((Unk_8003C51C_Ret *) func_8003E5C8())->unk5C(arg0, arg1, arg2);
    if (arg0->unk3C != 0 && (u32) arg0->unk1C > (u32) arg0->unk40) {
        vt->unk60(arg0, 6);
    }
    switch (arg0->unk20) {
    case 2:
        vt->unk60(arg0, 4);
        break;
    case 4:
        vt->unkAC(arg0);
        break;
    case 7:
        vt->unkC0(arg0);
        break;
    case 8:
        vt->unk60(arg0, 3);
        break;
    }
}

void func_8003C63C(Unk_8003C63C_Obj *arg0, s32 arg1) {
    Unk_8003C63C_Vtbl *vt;
    void (*fn)(void *);

    vt = arg0->unk0;
    ((Unk_8003C63C_Vtbl *) func_8003E5C8())->unk60(arg0, arg1);
    switch (arg1) {
    case 5:
        vt->unkE4(arg0, (u8 *) arg0->unk4C + 0x10);
        vt->unkF0(arg0, arg0->unk4C->unk8, 0);
        arg0->unk1C = 0;
        arg0->unk3C = 1;
        return;
    case 6:
        arg0->unk38 = 1;
        fn = vt->unk94;
        break;
    case 4:
    case 7:
        arg0->unk1C = 0;
        arg0->unk3C = 0;
        return;
    case 8:
        arg0->unk1C = 0;
        return;
    case 9:
    case 10:
    case 11:
    case 14:
    case 15:
    case 16:
    case 17:
        arg0->unk20 = 5;
        arg0->unk1C = 0;
        switch (arg1) {
        case 11:
            fn = vt->unk90;
            break;
        case 15:
            fn = vt->unk10C;
            break;
        case 17:
            fn = vt->unk110;
            break;
        default:
            return;
        }
        break;
    default:
        return;
    }
    fn(arg0);
}

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

void func_8003C858(struct Unk_8003C858 *arg0) {
    s32 var_a1;

    if (arg0->unk4C != 0) {
        arg0->unk0->unk70(arg0, 0x10);
        var_a1 = 0xF;
        if (arg0->unk3C == 1) {
            var_a1 = 0xB;
        }
        arg0->unk0->unk60(arg0, var_a1);
    }
}

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

void func_8003CA1C(Unk_8003CA1C *arg0) {
    Unk_8003CA1C_Sub *temp_a1 = arg0->unk4C;
    s32 temp_a2 = arg0->unk58;
    void (*fn)(void *, void *, s32);

    if (temp_a1->unk24[temp_a2] != 0) {
        fn = arg0->unk0->unk108;
    } else if (temp_a2 == temp_a1->unkC) {
        fn = arg0->unk0->unk94;
    } else {
        return;
    }
    fn(arg0, temp_a1, temp_a2);
}

void func_8003CA94(Unk_8003CA94 *arg0) {
    if (arg0->unk9C != NULL) {
        arg0->unk9C(arg0->unkA0);
    }
    arg0->unk0->unk60(arg0, 7);
}

void func_8003CAEC(struct Unk_8003CAEC *arg0, s32 arg1, s32 arg2) {
    arg0->unk9C = arg1;
    arg0->unkA0 = arg2;
}

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

void func_8003CBB8(struct Unk_8003CBB8 *arg0, s32 arg1) {
    arg0->unk84 = arg1;
}

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

s32 func_8003CC2C(struct Unk_8003CC2C *arg0) {
    s8 buf[3];
    s32 temp;
    Unk_8003CC2C_Obj *temp_a0;

    temp = arg0->unk1C * arg0->unk84;
    buf[0] = temp + arg0->unk90;
    buf[1] = temp + arg0->unk91;
    buf[2] = temp + arg0->unk92;
    arg0->unk0->unkE4(arg0, buf);
    temp_a0 = arg0->unk78;
    temp_a0->unk0->unkB8(temp_a0, 1, buf);
    return (u8)temp >= 0x81;
}

s32 func_8003CCDC(struct Unk_8003CCDC *arg0) {
    s32 var_s1 = 1;

    if (arg0->unk8C == NULL || (var_s1 = arg0->unk8C()) != 0) {
        arg0->unk0->unk60(arg0, 8);
    }
    return var_s1;
}

s32 func_8003CD48(struct Unk_8003CD48 *arg0) {
    s8 buf[3];
    s32 temp;
    Unk_8003CD48_Obj *temp_a0;

    temp = 0x80 - (arg0->unk1C * arg0->unk84);
    buf[0] = temp;
    buf[1] = temp;
    buf[2] = temp;
    arg0->unk0->unkE4(arg0, buf);
    temp_a0 = arg0->unk78;
    temp_a0->unk0->unkB8(temp_a0, 1, buf);
    return (u8)temp > 0x80;
}

void func_8003CDE0(struct Unk_8003CDE0 *arg0, s32 arg1, struct Unk_8003CDE0_Obj *arg2) {
    struct Unk_8003CDE0_Obj *temp_a0;
    struct Unk_8003CDE0_Obj *temp_v0;

    if (arg1 != 0) {
        if (arg0->unk70 != 0) {
            temp_a0 = arg0->unk74;
            temp_a0->unk0->unk4(temp_a0);
        }
        temp_v0 = (struct Unk_8003CDE0_Obj *)func_8003B39C(arg1);
        arg0->unk74 = temp_v0;
        temp_v0->unk0->unk78(temp_v0);
        temp_a0 = arg0->unk74;
        temp_a0->unk0->unk5C(temp_a0);
    } else {
        arg0->unk74 = arg2;
    }
    arg0->unk70 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003CE98);

void func_8003D050(struct Unk_8003D050 *arg0) {
    s32 i;
    s32 sp_pad[2];
    Unk_8003D050_Sub *temp_v1;
    Unk_8003D050_Obj **p;
    Unk_8003D050_Obj *obj;
    Unk_8003D050_Obj *temp_a0;

    temp_v1 = arg0->unk4C;
    if (temp_v1 != NULL) {
        if (temp_v1->unk0 != 0) {
            temp_a0 = temp_v1->unk4;
            temp_a0->unk0->unk4(temp_a0);
        }
        obj = arg0->unk68;
        i = 0;
        obj->unk0->unk4(obj);
        p = arg0->unk54;
        if (arg0->unk50 > 0) {
            do {
                if (arg0->unk4C->unk24[i] != 0) {
                    arg0->unk58 = i;
                    arg0->unk0->unkFC(arg0);
                }
                obj = *p;
                obj->unk0->unk4(obj);
                i++;
                p++;
            } while (i < arg0->unk50);
        }
        func_80017CFC(arg0->unk64);
        func_80017CFC(arg0->unk60);
        func_80017CFC(arg0->unk5C);
        func_80017CFC(arg0->unk54);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D194);

void func_8003D2CC(Unk_8003D2CC *arg0, s32 arg1) {
    s32 i;
    s32 saved;
    Unk_8003D2CC_Obj **p;
    Unk_8003D2CC_Obj *obj;

    if (arg0->unk4C != NULL) {
        p = arg0->unk54;
        saved = arg0->unk58;
        for (i = 0; i < arg0->unk50; i++, p++) {
            obj = *p;
            obj->unk0->unkB8(obj, arg1);
            if (arg0->unk4C->unk24[i] != 0) {
                arg0->unk58 = i;
                arg0->unk0->unk104(arg0, arg1);
            }
        }
        arg0->unk58 = saved;
    }
}

void func_8003D3B0(struct Unk_8003D3B0 *arg0) {
    s32 i;

    if (arg0->unk4C != NULL) {
        i = arg0->unk58;
        do {
            i++;
            if (i >= arg0->unk50) {
                i = 0;
            }
        } while (i != arg0->unk58 && arg0->unk4C->unk18[i] != 0);
        arg0->unk0->unkF0(arg0, i, 1);
    }
}

void func_8003D444(struct Unk_8003D3B0 *arg0) {
    s32 i;

    if (arg0->unk4C != NULL) {
        i = arg0->unk58;
        do {
            i--;
            if (i < 0) {
                i = arg0->unk50 - 1;
            }
        } while (i != arg0->unk58 && arg0->unk4C->unk18[i] != 0);
        arg0->unk0->unkF0(arg0, i, 1);
    }
}

void func_8003D4DC(struct Unk_8003D4DC *arg0, s32 arg1, s32 arg2) {
    Unk_8003D4DC_Elem *temp_a0;
    Unk_8003D4DC_Elem *temp_s1;

    if (arg0->unk4C != 0) {
        temp_a0 = arg0->unk54[arg0->unk58];
        temp_s1 = arg0->unk54[arg1];
        if (arg0->unk58 >= 0) {
            temp_a0->unk0->unkB8(temp_a0, arg0->unk4C + 0x10);
        }
        temp_s1->unk0->unkB8(temp_s1, arg0->unk4C + 0x13);
        arg0->unk58 = arg1;
        if (arg2 != 0) {
            arg0->unk0->unk70(arg0, 0);
        }
        arg0->unk0->unk60(arg0, 9);
    }
}

s32 func_8003D5C0(struct Unk_8003D5C0 *arg0) {
    return arg0->unk58;
}

void func_8003D5CC(struct Unk_8003D6D4 *arg0, struct Unk_8003D5CC *arg1, s32 arg2) {
    s32 *p;
    s32 cnt;
    s32 idx;
    s32 *buf;
    s32 len;

    p = arg1->unk18;
    idx = arg0->unk58;
    cnt = 0;
    while (*p++ != 0) {
        cnt++;
    }
    buf = (s32 *)func_80017B34(cnt * 4);
    arg0->unk64[idx] = (void **)buf;
    arg0->unk60[idx] = arg1->unk4;
    arg0->unk5C[idx] = cnt;
    p = arg1->unk18;
    while (*p != 0) {
        len = strlen((u8 *)*p);
        *buf++ = func_800408CC(arg2, len, *p);
        p++;
    }
}

void func_8003D6D4(struct Unk_8003D6D4 *arg0) {
    func_800183DC(arg0->unk64[arg0->unk58], arg0->unk5C[arg0->unk58]);
    func_80017CFC(arg0->unk64[arg0->unk58]);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003D73C);

void func_8003D980(struct Unk_8003D6D4 *arg0, s32 arg1) {
    void **p;
    s32 count;
    s32 i;

    p = arg0->unk64[arg0->unk58];
    count = arg0->unk5C[arg0->unk58];
    for (i = 0; i < count; i++) {
        void *obj = *p;
        p++;
        ((Unk_8003D980_Obj *)obj)->unk0->unkB8(obj, arg1);
    }
}

void func_8003DA10(Unk_8003DA10 *arg0) {
    s32 i;
    Unk_8003DA10_Elem *elem;

    if (arg0->unk3C == 1) {
        i = arg0->unk58;
        arg0->unk0->unk100(arg0, arg0->unk14, 1);
        elem = arg0->unk64[i][arg0->unk60[i]];
        elem->unk0->unkB8(elem, arg0->unk4C->unk24[i] + 8);
        arg0->unk3C = 2;
        arg0->unk0->unk60(arg0, 0xE);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003DAD4);

void func_8003DCAC(Unk_8003DA10 *arg0) {
    s32 i;
    s32 idx;
    s32 v;
    Unk_8003DA10_Elem **arr;
    Unk_8003DA10_Elem *e;

    if (arg0->unk3C == 2) {
        i = arg0->unk58;
        idx = arg0->unk60[i];
        arg0->unk0->unk100(arg0, arg0->unk14, 0);
        arr = arg0->unk64[i];
        e = arr[idx];
        e->unk0->unkB8(e, (s32)arg0->unk4C + 0x10);
        v = ((s32 *)arg0->unk4C->unk24[i])[1];
        arg0->unk60[i] = v;
        e = arr[v];
        e->unk0->unk60(e, 1);
        arg0->unk3C = 1;
        arg0->unk0->unk60(arg0, 0x11);
    }
}

void func_8003DDC8(struct Unk_8003DDC8 *arg0) {
    s32 var_a1;

    var_a1 = arg0->unk60[arg0->unk58];
    var_a1 = var_a1 + 1;
    if (var_a1 >= arg0->unk5C[arg0->unk58]) {
        var_a1 = 0;
    }
    arg0->unk0->unk11C(arg0, var_a1, 1);
}

void func_8003DE30(Unk_8003DE30 *arg0) {
    s32 n;

    n = arg0->unk60[arg0->unk58];
    n--;
    if (n < 0) {
        n = arg0->unk5C[arg0->unk58] - 1;
    }
    arg0->unk0->unk11C(arg0, n, 1);
}

void func_8003DE9C(Unk_8003DA10 *arg0, s32 arg1, s32 arg2) {
    s32 i = arg0->unk58;
    s32 *p60 = &arg0->unk60[i];
    Unk_8003DA10_Elem ***p64 = &arg0->unk64[i];
    Unk_8003DA10_Elem **temp_a2 = *p64;
    Unk_8003DA10_Elem *temp_a0 = temp_a2[*p60];
    Unk_8003DA10_Elem *temp_s1 = temp_a2[arg1];

    temp_a0->unk0->unkB8(temp_a0, (s32)arg0->unk4C + 0x10);
    temp_s1->unk0->unkB8(temp_s1, arg0->unk4C->unk24[i] + 8);
    arg0->unk60[i] = arg1;
    if (arg2 != 0) {
        arg0->unk0->unk70(arg0, 0);
    }
    arg0->unk0->unk60(arg0, 9);
}

s32 func_8003DFA0(Unk_8003DFA0 *arg0) {
    return arg0->unk60[arg0->unk58];
}

void *func_8003DFBC(void) {
    return D_8006E730;
}

void *func_8003DFCC(void) {
    return D_8006E854;
}

void func_8003DFDC(void **arg0) {
    Unk_8003DFDC_Obj *temp_v0;

    func_80018390()->unk8(arg0);
    temp_v0 = func_8003E5C8();
    *arg0 = temp_v0;
    temp_v0->unk40(arg0);
}

void func_8003E030(Unk_8003E030 *arg0, s32 **arg1, s32 arg2) {
    s32 temp_v1;

    ((Unk_8003E030_Ret *)func_80018390())->unk38(arg0, arg1, arg2);
    temp_v1 = **arg1 & 0xF;
    if (temp_v1 == 1) {
        arg0->vt->unk54(arg0, arg1, arg2);
    } else if (temp_v1 == 2) {
        arg0->vt->unk58(arg0, arg1, arg2);
    } else if (temp_v1 == 5) {
        arg0->vt->unk5C(arg0, arg1, arg2);
    }
}

void func_8003E100(struct Unk_8003E100 *arg0) {
    arg0->unk1C = 0;
    arg0->unk20 = 0;
}

void func_8003E10C(Unk_8003E10C *arg0, Unk_8003E10C_Arg *arg1, s32 arg2) {
    Unk_8003E10C_Vtbl *temp_s3;
    Unk_8003E10C_Obj *temp_s2;
    Unk_8003E10C_Obj *temp_a0;
    s32 temp_v0;

    temp_s3 = arg0->unk0;
    temp_v0 = arg1->unk8;
    if (temp_v0 == 0) {
        temp_v0 = (s32)func_80042400();
    }
    arg0->unk10 = temp_v0;
    temp_v0 = arg1->unkC;
    if (temp_v0 == 0) {
        temp_v0 = (s32)func_80042694();
    }
    arg0->unk14 = (Unk_8003E10C_Obj *)temp_v0;
    temp_v0 = arg1->unk10;
    if (temp_v0 == 0) {
        temp_v0 = func_8003E5D8();
    }
    arg0->unk18 = (Unk_8003E10C_Obj *)temp_v0;
    arg0->unkC = arg1;
    temp_s2 = arg0->unk18;
    temp_s3->unk10(arg0, arg1->unk0);
    temp_s3->unk10(arg0, arg1->unk4);
    temp_s3->unk10(arg0, arg0->unk10);
    temp_s3->unk4C(arg0, 0, 0, 0);
    arg0->unk24 = arg2;
    if (arg2 == 0) {
        temp_s2->unk0->unk10(temp_s2, arg1->unk0);
        temp_s2->unk0->unk10(temp_s2, arg0->unk10);
        temp_a0 = arg0->unk14;
        temp_a0->unk0->unk10(temp_a0, arg0->unk10);
        temp_s3->unk60(arg0, 2);
        temp_s3->unk48(arg0);
    }
}

void func_8003E280(struct Unk_8003E280 *arg0) {
    Unk_8003E280_Vtbl *temp_s2;
    Unk_8003E280_Obj *temp_s1;
    Unk_8003E280_Obj *temp_a0;
    Unk_8003E280_Obj *temp_a0_2;
    Unk_8003E280_Obj *temp_a0_3;

    temp_s2 = arg0->unk0;
    temp_s2->unk50(arg0);
    temp_s1 = arg0->unk18;
    if (arg0->unk24 == 0) {
        temp_a0 = arg0->unk14;
        temp_a0->unk0->unk14(temp_a0, (s32)arg0->unk10);
        temp_s1->unk0->unk14(temp_s1, (s32)arg0->unk10);
        temp_s1->unk0->unk14(temp_s1, arg0->unkC->unk0);
    }
    temp_s2->unk14(arg0, (s32)arg0->unk10);
    temp_s2->unk14(arg0, arg0->unkC->unk4);
    temp_s2->unk14(arg0, arg0->unkC->unk0);
    if (arg0->unkC->unk10 != temp_s1) {
        arg0->unk18 = (Unk_8003E280_Obj *)temp_s1->unk0->unk4(temp_s1);
    }
    temp_a0_2 = arg0->unk14;
    if (arg0->unkC->unkC != temp_a0_2) {
        arg0->unk14 = (Unk_8003E280_Obj *)temp_a0_2->unk0->unk4(temp_a0_2);
    }
    temp_a0_3 = arg0->unk10;
    if (arg0->unkC->unk8 != temp_a0_3) {
        arg0->unk10 = (Unk_8003E280_Obj *)temp_a0_3->unk0->unk4(temp_a0_3);
    }
}

void func_8003E418(struct Unk_8003E418 *arg0, s32 arg1, s32 arg2) {
    Unk_8003E418_Obj *temp_a0;
    Unk_8003E418_Obj *temp_s0;

    if (arg2 == 2) {
        temp_a0 = arg0->unk10;
        temp_a0->unk0->unk44(temp_a0);
        temp_s0 = arg0->unkC->unk4;
        temp_s0->unk0->unk44(temp_s0);
        temp_s0->unk0->unk48(temp_s0);
    }
}

void func_8003E4A4(struct Unk_8003E4A4 *arg0) {
    arg0->unk1C++;
}

void func_8003E4B8(struct Unk_8003E4B8 *arg0, s32 arg1) {
    Unk_8003E4B8_Vtbl *vt = arg0->unk0;

    arg0->unk20 = arg1;
    vt->unk30(arg0, arg1);
    if (arg1 == 2) {
        vt->unk64(arg0);
    } else if (arg1 == 3) {
        vt->unk68(arg0);
    }
}

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

void *func_8003E5C8(void) {
    return D_8006E878;
}

s32 func_8003E5D8(void) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0xBC);
    if (temp_v0 != 0) {
        func_8003F24C()->unk8(temp_v0);
        return temp_v0;
    }
    return 0;
}

void func_8003E628(struct Unk_8003E628 *arg0) {
    Unk_8003E628_Obj *temp;

    func_80018390()->unk8(arg0);
    arg0->unk0 = (Unk_8003E628_Vtbl *)func_8003F24C();
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unkAC = func_8001CA94();
    temp = func_8003FDB0((s32)&D_8008A90C, 0, 0);
    arg0->unkB0 = temp;
    temp->unk0->unk4C(temp, arg0->unkAC, &D_8008A904);
    arg0->unk0->unk40(arg0);
}

void func_8003E6CC(struct Unk_8003E6CC *arg0) {
    Unk_8003E6CC_Obj *temp_a0;

    arg0->unk0->unk90();
    arg0->unk0->unk74(arg0);
    temp_a0 = arg0->unkAC;
    temp_a0->unk0->unk4(temp_a0);
    arg0->unk0->unkA8(arg0, 0);
    func_80018390()->unkC(arg0);
}

void func_8003E770(struct Unk_8003E874 *arg0, struct Unk_8003E770 *arg1) {
    s32 temp;

    func_80018390()->unk10(arg0, arg1);
    temp = *arg1->unk0 & 0xF;
    if (temp == 4) {
        arg0->unk10 = arg1;
        arg0->unk30 = arg1->unk14;
    } else if (temp == 1) {
        arg0->unkC = arg1;
    }
}

void func_8003E7F4(struct Unk_8003E7F4 *arg0, s32 **arg1) {
    s32 temp_v1;

    temp_v1 = **arg1 & 0xF;
    if (temp_v1 == 4) {
        arg0->unk30 = 0;
        arg0->unk10 = 0;
    } else if (temp_v1 == 1) {
        arg0->unkC = 0;
    }
    ((Unk_8003E7F4_vt *)func_80018390())->unk14(arg0, arg1);
}

void func_8003E874(struct Unk_8003E874 *arg0) {
    arg0->unk30 = 0;
    arg0->unk10 = 0;
    arg0->unkC = 0;
    func_80018390()->unk18(arg0);
}

void func_8003E8B8(Unk_8003E8B8 *arg0, s32 **arg1, s32 arg2) {
    s32 type;

    ((Unk_8003E8B8_Ret *)func_80018390())->unk38(arg0, arg1, arg2);
    type = **arg1 & 0xF;
    if (type == 5) {
        arg0->unk0->unk94(arg0, arg1, arg2);
    } else if (type == 1) {
        arg0->unk0->unk98(arg0, arg1, arg2);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003B854", func_8003E968);

void func_8003EA0C(struct Unk_8003EA0C *arg0, Unk_8003EA0C_Pair *arg1) {
    arg0->unk34 = *arg1;
}

void func_8003EA24(struct Unk_8003EA24 *arg0, s32 arg1) {
    arg0->unk3C = arg1;
}

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

void func_8003EA64(struct Unk_8003EA64 *arg0, s32 arg1) {
    arg0->unk40 = arg1;
}

void func_8003EA6C(void) {
}

void func_8003EA74(void) {
}

void func_8003EA7C(struct Unk_8003EA7C *arg0, s32 arg1) {
    arg0->unk54 = arg1;
}

void func_8003EA84(struct Unk_8003EA84 *arg0, Unk_8003EA84_Rgb *arg1) {
    arg0->unk58 = *arg1;
}

void func_8003EAA4(struct Unk_8003EAA4 *arg0, Unk_8003EAA4_Rgb *arg1) {
    arg0->unk5B = *arg1;
}

void func_8003EAC4(struct Unk_8003EAC4 *arg0, s32 arg1) {
    arg0->unk60 = arg1;
}

void func_8003EACC(struct Unk_8003EACC *arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    Unk_8003EACC_Vtbl *vt;
    void *var_a1;

    vt = arg0->unk0;
    if (arg0->unk10 == 0) {
        vt->unk10();
        vt->unk78(arg0, arg2);
        vt->unk7C(arg0, arg3);
        var_a1 = arg4;
        if (var_a1 == NULL) {
            var_a1 = &D_8008A8F4;
        }
        vt->unk80(arg0, var_a1);
        GsSetRefView2((u8 *)arg0 + 0x14);
    }
}

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

void func_8003EC2C(struct Unk_8003EC2C *arg0, Unk_8003EC2C_Pair *arg1) {
    s16 temp_v0;
    s16 temp_a0;

    if (arg0->unk10 != 0) {
        temp_v0 = arg1->unk0;
        temp_a0 = arg1->unk2;
        arg0->unk2C = ((temp_v0 / temp_a0) << 12) + (((temp_v0 % temp_a0) << 12) / temp_a0);
    }
}

void func_8003ECC0(void) {
}

void func_8003ECC8(void) {
}

void func_8003ECD0(struct Unk_8003ECD0 *arg0) {
    s32 temp_s1;
    u8 *temp_v1;

    if (arg0->unk70 == 0) {
        temp_s1 = 0x14 + (4 << arg0->unk3C) + arg0->unk48 * arg0->unk44;
        temp_v1 = (u8 *) func_80017B34(temp_s1 * 2);
        if (temp_v1 != NULL) {
            arg0->unk78 = (Unk_8003ECD0_Ot *) temp_v1;
            temp_v1 = temp_v1 + 0x14;
            arg0->unk80 = temp_v1;
            arg0->unk88 = (void *) ((4 << arg0->unk3C) + (s32)temp_v1);
            arg0->unk7C = (Unk_8003ECD0_Ot *) (temp_s1 + (u8 *) arg0->unk78);
            arg0->unk84 = (void *) (temp_s1 + (u8 *) arg0->unk80);
            arg0->unk8C = (void *) (temp_s1 + (u8 *) arg0->unk88);
            arg0->unk78->unk0 = arg0->unk3C;
            arg0->unk78->unk4 = arg0->unk80;
            arg0->unk7C->unk0 = arg0->unk3C;
            arg0->unk7C->unk4 = arg0->unk84;
            GsClearOt(0, 0, arg0->unk78);
            GsClearOt(0, 0, arg0->unk7C);
            arg0->unk70 = 1;
            arg0->unk74 = 0;
        }
    }
}

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

void func_8003EEC0(struct Unk_8003EEC0 *arg0) {
    if (arg0->unk70 != 0) {
        if (arg0->unk10->unkC != NULL) {
            arg0->unk0->unkA0(arg0, arg0->unk10);
        }
        func_8003F28C(arg0->unk40);
        func_8003FB0C(arg0->unk4C);
        GsSetLightMode(arg0->unk54);
        if (arg0->unk54 == 1 || arg0->unk54 == 3) {
            SetFarColor(arg0->unk5B, arg0->unk5C, arg0->unk5D);
            SetFogNear(arg0->unk60, arg0->unk40);
        }
        GsSetRefView2((u8 *)arg0 + 0x14);
        *arg0->unk30 = 0;
        arg0->unk98 = ((u32)(arg0->unk50 - arg0->unk4C) / (u32)(1 << arg0->unk3C)) + 1;
        func_8003FBE4(arg0->unk88[arg0->unk74]);
        GsClearOt(0, 0, arg0->unk78[arg0->unk74]);
        arg0->unk0->unkA0(arg0, arg0->unkAC);
        if (arg0->unk10 != NULL) {
            arg0->unk0->unkA0(arg0, func_8003F25C(arg0->unk10));
        }
    }
}

void func_8003F04C(struct Unk_8003F04C *arg0) {
    if (arg0->unk70 != 0) {
        arg0->unk74 = arg0->unkC->unk0->unk54(arg0->unkC);
        if (arg0->unkB8 != 0) {
            ResetGraph(1);
            arg0->unkC->unk0->unk50(arg0->unkC);
            if (arg0->unkB4 != 0 && arg0->unk74 == 0) {
                arg0->unkC->unk0->unk50(arg0->unkC);
            }
            GsSortClear(arg0->unk58, arg0->unk59, arg0->unk5A, arg0->unk78[arg0->unk74]);
            GsDrawOt(arg0->unk78[arg0->unk74]);
            if (arg0->unkB4 != 0 && arg0->unk74 == 0) {
                arg0->unkC->unk0->unk50(arg0->unkC);
            }
        }
        arg0->unk74 = arg0->unk74 == 0;
    }
}

void func_8003F1A8(struct Unk_8003F1A8 *arg0, Unk_8003F1A8_Obj *arg1) {
    Unk_8003F1A8_Obj *temp;

    if (arg0->unk10 == 0) {
        temp = arg0->unkB0;
        if (temp != NULL) {
            temp->unk0->unk4(temp);
        }
        arg0->unkB0 = arg1;
        if (arg1 != NULL) {
            arg1->unk0->unk4C(arg1, arg0->unkAC, &D_8008A904);
        }
    }
}

s32 func_8003F230(struct Unk_8003F230 *arg0) {
    return arg0->unkB0;
}

void func_8003F23C(struct Unk_8003F23C *arg0, s32 arg1) {
    arg0->unkB4 = arg1;
}

void func_8003F244(struct Unk_8003F244 *arg0, s32 arg1) {
    arg0->unkB8 = arg1;
}

struct Unk_8003E5D8 *func_8003F24C(void) {
    return D_8006E8E4;
}

struct Unk_8003F25C *func_8003F25C(struct Unk_8003F25C *arg0) {
    while (arg0->unkC != NULL) {
        arg0 = arg0->unkC;
    }
    return arg0;
}

void func_8003F28C(s32 arg0) {
    SetGeomScreen(arg0);
}

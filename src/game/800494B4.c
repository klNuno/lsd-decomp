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
typedef struct Unk_8004B44C { s8 a; s8 b; s8 c; s8 d; s16 e; s16 f; s16 g; } Unk_8004B44C;
s32 func_8004B44C(s32 *arg0, s32 *arg1, Unk_800861D4 *arg2, s32 *arg3, Unk_8004B44C *arg4);
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
    struct Unk_8004B2D4 *unk38;
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
void func_8004C93C();
typedef struct { u8 pad_00[0x2C]; s16 u2C; s16 pad_2E; s16 u30; } Unk_8004C5D0_Obj;
typedef struct { s32 unk0; Unk_8004C5D0_Obj *obj; u8 pad_08[0x14]; } Unk_8004C5D0_Slot;
typedef struct { u8 pad_00[0xEC]; Unk_8004C5D0_Slot slots[7]; } Unk_8004C5D0;
typedef struct Unk_8004D254 {
    u8 pad_00[0x8];
    void (*unk8)(s32);
} Unk_8004D254;
s32 Heap_Alloc(s32);
Unk_8004D254 *func_8004D37C(void);
typedef struct Unk_8004D38C {
    u8 pad_00[0x8];
    void (*unk8)(s32);
} Unk_8004D38C;
s32 Heap_Alloc(s32 size);
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
    u8 pad_0C[0x38 - 0xC];
    void (*unk38)(void *, s32 **, s32);
} Unk_8004A130;
Unk_8004A130 *func_8004A4B8(void);
typedef struct Unk_8004A4C8 { u8 pad_00[0x8]; void (*unk8)(s32, s32, s32); u8 pad_0C[0x10 - 0xC]; void (*unk10)(void *, void *); u8 pad_14[0x40 - 0x14]; void (*unk40)(void *); } Unk_8004A4C8;
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
typedef struct Unk_8004C6A8_M { s16 m[3][3]; s32 t[3]; } Unk_8004C6A8_M;
typedef struct Unk_8004C6A8_C { u8 pad[0x10]; s16 rot[3]; } Unk_8004C6A8_C;
typedef struct Unk_8004C6A8_B { u8 pad[0x44]; Unk_8004C6A8_C *u44; } Unk_8004C6A8_B;
typedef struct Unk_8004C6A8_A { u8 pad[0x14]; Unk_8004C6A8_B *u14; } Unk_8004C6A8_A;
typedef struct Unk_8004C6A8_vt { u8 pad[0x10C]; void (*f10C)(void *, void *, s32); } Unk_8004C6A8_vt;
typedef struct Unk_8004C6A8 {
    Unk_8004C6A8_vt *unk0;
    u8 pad4[0x68];
    Unk_8004C6A8_A *u6C;
    u8 pad70[0x4];
    s32 u74;
    s16 u78;
    u8 pad7A[0x2];
    u16 u7C;
    u16 u7E;
    s32 u80;
    s32 u84;
} Unk_8004C6A8;
void func_8004C6A8(Unk_8004C6A8 *self, s32 arg1, s32 arg2);
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
typedef struct Unk_80049A1C_Mgr {
    u8 pad_00[0x44];
    void (*unk44)(void *, void *, s32);
} Unk_80049A1C_Mgr;
typedef struct Unk_80049A1C_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
    u8 pad_14[0x110 - 0x14];
    void (*unk110)(void *, s32);
} Unk_80049A1C_Vtbl;
typedef struct Unk_80049A1C_Obj {
    Unk_80049A1C_Vtbl *unk0;
} Unk_80049A1C_Obj;
typedef struct Unk_80049A1C_Sub {
    u8 pad_00[0x4];
    s32 unk4;
    s32 unk8;
    u8 pad_0C[0x10 - 0xC];
    s32 unk10;
} Unk_80049A1C_Sub;
typedef struct Unk_80049A1C {
    u8 pad_00[0xC];
    Unk_80049A1C_Sub *unkC;
    u8 pad_10[0x38 - 0x10];
    Unk_80049A1C_Obj *unk38;
} Unk_80049A1C;
extern Unk_800861D4 D_800861D6[];
typedef struct Unk_8004950C { u8 unk0; u8 unk1; } Unk_8004950C;
typedef struct Unk_8004C0AC_Elem {
    u8 pad_00[0x10];
    u32 unk10;
    u8 pad_14[0x18 - 0x14];
    u32 unk18;
    u8 pad_1C[0x20 - 0x1C];
    u32 unk20;
} Unk_8004C0AC_Elem;
typedef struct Unk_8004C0AC_Obj Unk_8004C0AC_Obj;
typedef struct Unk_8004C0AC_Vtbl {
    u8 pad_00[0x7C];
    void (*unk7C)(Unk_8004C0AC_Obj *);
} Unk_8004C0AC_Vtbl;
struct Unk_8004C0AC_Obj {
    Unk_8004C0AC_Vtbl *unk0;
    u8 pad_04[0x30 - 0x4];
    s16 unk30;
};
typedef struct Unk_8004C0AC {
    u8 pad_00[0x4];
    Unk_8004C0AC_Obj *unk4;
    u8 pad_08[0x10 - 0x8];
    Unk_8004C0AC_Elem **unk10;
} Unk_8004C0AC;
typedef struct Unk_8004AA6C_Ret {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32);
} Unk_8004AA6C_Ret;
typedef struct Unk_8004AA6C_Vt {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
} Unk_8004AA6C_Vt;
typedef struct Unk_8004AA6C_Obj {
    Unk_8004AA6C_Vt *unk0;
    u8 pad_04[0x1BC - 0x4];
    void *unk1BC;
} Unk_8004AA6C_Obj;
typedef struct Unk_8004AA6C_SubVt {
    u8 pad_00[0x4];
    void *(*unk4)(void *);
} Unk_8004AA6C_SubVt;
typedef struct Unk_8004AA6C_Sub {
    Unk_8004AA6C_SubVt *unk0;
} Unk_8004AA6C_Sub;
typedef struct Unk_8004AA6C_Arg {
    u8 pad_00[0x14];
    Unk_8004AA6C_Sub *unk14;
} Unk_8004AA6C_Arg;
typedef struct Unk_80049958_Vtbl {
    u8 pad_00[0x80];
    void (*unk80)(void *, s32 **, s32);
    void (*unk84)(void *, s32 **, s32);
} Unk_80049958_Vtbl;
typedef struct Unk_80049958 {
    Unk_80049958_Vtbl *unk0;
} Unk_80049958;
void *func_80048D48(s32 *arg0);
s32 func_80027024(s32 arg0, s32 arg1);
s32 D_8008A978;
s32 D_8008A97C;
typedef struct Unk_8004CC74_Vtbl {
    u8 pad_00[0x10C];
    void (*unk10C)(void *, void *, s32);
} Unk_8004CC74_Vtbl;
typedef struct Unk_8004CC74_Sp10 {
    s16 unk_0;
    s16 unk_2;
    u8 pad_04[0x28 - 0x4];
    s32 unk_28;
} Unk_8004CC74_Sp10;
typedef struct Unk_8004CC74 {
    Unk_8004CC74_Vtbl *unk0;
    u8 pad_04[0x68 - 0x4];
    Unk_800861D4 *unk68;
    u8 pad_6C[0x88 - 0x6C];
    s32 unk88;
    u8 pad_8C[0x1DC - 0x8C];
    void *unk1DC;
} Unk_8004CC74;
s32 func_8004CD38(void *arg0, void *arg1);
s32 func_8004CDA4(void *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct Unk_8004ACF8_Vtbl {
    u8 pad_00[0xB8];
    void *(*unkB8)(void *, s32);
} Unk_8004ACF8_Vtbl;
typedef struct Unk_8004ACF8 {
    Unk_8004ACF8_Vtbl *unk0;
} Unk_8004ACF8;
typedef struct Unk_8004ACF8_Child_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, s32);
    void (*unk48)(void *, s32, s32);
} Unk_8004ACF8_Child_Vtbl;
typedef struct Unk_8004ACF8_Child {
    Unk_8004ACF8_Child_Vtbl *unk0;
} Unk_8004ACF8_Child;
typedef struct Unk_8004ADD8_Vtbl {
    u8 pad_00[0x12C];
    void (*unk12C)(void *, s32 **, s32);
} Unk_8004ADD8_Vtbl;
typedef struct Unk_8004ADD8 {
    Unk_8004ADD8_Vtbl *unk0;
    u8 pad_04[0xE8 - 0x4];
    s32 *unkE8;
} Unk_8004ADD8;
typedef struct Unk_8004B030_Vt {
    u8 pad_00[0x124];
    s32 (*unk124)(void *, void *);
} Unk_8004B030_Vt;
typedef struct Unk_8004B030_Obj {
    Unk_8004B030_Vt *unk0;
    u8 pad_04[0x88 - 0x4];
    s32 unk88;
    s32 unk8C;
    s16 unk90;
    s16 unk92;
    s16 unk94;
    s16 unk96;
} Unk_8004B030_Obj;
typedef struct Unk_8004B030_Arg {
    u8 pad_00[0x2];
    s8 unk2;
    s8 unk3;
    u8 pad_04[0x28 - 0x4];
    void *unk28;
} Unk_8004B030_Arg;
extern s32 D_80086650[];
extern s32 D_8008665C[];
typedef struct Unk_80049B54_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, void *);
    u8 pad_48[0x4C - 0x48];
    void (*unk4C)(void *, s32);
    u8 pad_50[0x60 - 0x50];
    void (*unk60)(void *, s32);
    u8 pad_64[0x70 - 0x64];
    void (*unk70)(void *, void *, void *, void *, s32);
    u8 pad_74[0x7C - 0x74];
    s32 (*unk7C)(void *, s32);
    u8 pad_80[0x8C - 0x80];
    void (*unk8C)(void *);
    u8 pad_90[0xAC - 0x90];
    void *(*unkAC)(void *);
} Unk_80049B54_Vtbl;
typedef struct Unk_80049B54_Obj {
    Unk_80049B54_Vtbl *unk0;
} Unk_80049B54_Obj;
typedef struct Unk_80049B54 {
    u8 pad_00[0xC];
    Unk_80049B54_Obj **unkC;
    u8 pad_10[0x18 - 0x10];
    Unk_80049B54_Obj *unk18;
    u8 pad_1C[0x38 - 0x1C];
    void *unk38;
    s32 unk3C;
} Unk_80049B54;
struct Unk_8004ABD0;
typedef struct Unk_8004ABD0_ObjVtbl {
    u8 pad_00[0x74];
    void (*unk74)(void *);
    u8 pad_78[0x84 - 0x78];
    void (*unk84)(void *);
} Unk_8004ABD0_ObjVtbl;
typedef struct Unk_8004ABD0_Obj {
    Unk_8004ABD0_ObjVtbl *unk0;
} Unk_8004ABD0_Obj;
typedef struct Unk_8004ABD0_InnerVtbl {
    u8 pad_00[0x4];
    void *(*unk4)(void *);
} Unk_8004ABD0_InnerVtbl;
typedef struct Unk_8004ABD0_Inner {
    Unk_8004ABD0_InnerVtbl *unk0;
} Unk_8004ABD0_Inner;
typedef struct Unk_8004ABD0_Sub {
    u8 pad_00[0x2C];
    Unk_8004ABD0_Inner *unk2C;
} Unk_8004ABD0_Sub;
typedef struct Unk_8004ABD0_Slot {
    s16 unk0;
    u8 pad_02[0x4 - 0x2];
    Unk_8004ABD0_Obj *unk4;
    Unk_8004ABD0_Sub *unk8;
    u8 pad_0C[0x1C - 0x0C];
} Unk_8004ABD0_Slot;
typedef struct Unk_8004ABD0_Vtbl {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32, void *, s32);
    u8 pad_8C[0x108 - 0x8C];
    void (*unk108)(void *, void *);
    u8 pad_10C[0x140 - 0x10C];
    void (*unk140)(void *);
} Unk_8004ABD0_Vtbl;
typedef struct Unk_8004ABD0 {
    Unk_8004ABD0_Vtbl *unk0;
    u8 pad_04[0xEC - 0x04];
    Unk_8004ABD0_Slot unkEC[7];
    u8 pad_1B0[0x1B4 - 0x1B0];
    s16 unk1B4;
    u8 pad_1B6[0x1B8 - 0x1B6];
    s32 unk1B8;
} Unk_8004ABD0;
typedef struct Unk_8004AEA4_Vtbl {
    u8 pad_00[0x110];
    s32 (*unk110)(void *, void *, s32);
} Unk_8004AEA4_Vtbl;
typedef struct Unk_8004AEA4_Elem {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Unk_8004AEA4_Elem;
typedef struct Unk_8004B100_Obj {
    u8 pad_00[0x2C];
    s16 unk2C;
} Unk_8004B100_Obj;
typedef struct Unk_8004B100_Slot {
    u8 pad_00[0x4];
    Unk_8004B100_Obj *unk4;
    u8 pad_08[0x10 - 0x8];
    Unk_8004B2D4 **unk10;
    u8 pad_14[0x1C - 0x14];
} Unk_8004B100_Slot;
typedef struct Unk_8004AEA4 {
    Unk_8004AEA4_Vtbl *unk0;
    u8 pad_04[0x68 - 0x04];
    Unk_800861D4 *unk68;
    u8 pad_6C[0x88 - 0x6C];
    s32 unk88;
    Unk_8004AEA4_Elem unk8C[3];
    u16 unkBC;
    u8 pad_BE[0xEC - 0xBE];
    Unk_8004B100_Slot slots[7];
    u8 pad_1B0[0x1C0 - 0x1B0];
    s16 unk1C0;
    u8 unk1C2;
    u8 unk1C3;
} Unk_8004AEA4;
typedef struct Unk_8004AEA4_Arg {
    u8 pad_00[0xC];
    s32 unkC;
    u8 pad_10[0x14 - 0x10];
    s32 unk14;
} Unk_8004AEA4_Arg;
void func_8004B2D4(Unk_8004B2D4 *arg0, Unk_8004AEA4_Arg *arg1, s32 arg2);
void func_8004AFE0();
void func_8004B030();
typedef struct Unk_8004B100_Elem {
    s32 idx;
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} Unk_8004B100_Elem;
void func_8004B100(Unk_8004AEA4 *arg0, Unk_8004AEA4_Arg *arg1, s32 arg2);
typedef struct Unk_8004BD14_Obj {
    u8 pad_00[0x2A];
    u16 u2A;
    s16 u2C;
    s16 u2E;
} Unk_8004BD14_Obj;
typedef struct Unk_8004BD14_Slot {
    u16 u0;
    u8 pad_02[0x2];
    Unk_8004BD14_Obj *obj;
    u8 pad_08[0x1C - 0x8];
} Unk_8004BD14_Slot;
typedef struct Unk_8004BD14_Vtbl {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32, Unk_8004BD14_Slot *, s32);
    u8 pad_8C[0x104 - 0x8C];
    void (*unk104)(void *, Unk_8004BD14_Slot *);
} Unk_8004BD14_Vtbl;
typedef struct Unk_8004BD14 {
    Unk_8004BD14_Vtbl *unk0;
    u8 pad_04[0xEC - 0x4];
    Unk_8004BD14_Slot slots[7];
    s32 u1B0;
    u16 u1B4;
    u8 pad_1B6[0x1B8 - 0x1B6];
    s32 u1B8;
} Unk_8004BD14;
typedef struct Unk_8004A130_80049830 {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32, s32);
} Unk_8004A130_80049830;
void Sym_FreeModels(void);
typedef struct Unk_80049830_Mgr {
    u8 pad_00[0xC];
    void (*unkC)(void *);
} Unk_80049830_Mgr;
typedef struct Unk_80049830_Vtbl {
    u8 pad_00[0x4];
    void *(*unk4)(void *);
    u8 pad_08[0x14 - 0x8];
    void (*unk14)(void *, s32);
} Unk_80049830_Vtbl;
typedef struct Unk_80049830_Obj {
    Unk_80049830_Vtbl *unk0;
} Unk_80049830_Obj;
typedef struct Unk_80049830_Sub {
    u8 pad_00[0x8];
    Unk_80049830_Obj *unk8;
    Unk_80049830_Obj *unkC;
    Unk_80049830_Obj *unk10;
} Unk_80049830_Sub;
typedef struct Unk_80049830 {
    Unk_80049830_Vtbl *unk0;
    u8 pad_04[0xC - 0x4];
    Unk_80049830_Sub *unkC;
    u8 pad_10[0x38 - 0x10];
    s32 unk38;
    u8 pad_3C[0x40 - 0x3C];
    Unk_80049830_Obj *unk40;
    Unk_80049830_Obj *unk44;
    Unk_80049830_Obj *unk48;
} Unk_80049830;
typedef struct Unk_8004C470 Unk_8004C470;
typedef struct Unk_8004C470_Range { s32 unk0; u8 pad_04[0x18 - 0x4]; s32 unk18; s32 unk1C; s32 unk20; } Unk_8004C470_Range;
typedef struct Unk_8004C470_Pair { u8 pad_00[0x14]; Unk_8004C470_Range *unk14; } Unk_8004C470_Pair;
typedef struct Unk_8004B700_Prim { u8 pad_00[0x32]; u16 unk32; } Unk_8004B700_Prim;
typedef struct Unk_8004C470_Obj {
    u8 pad_00[0x2];
    s16 unk2;
    Unk_8004B700_Prim *unk4;
    u8 pad_08[0xC - 0x8];
    Unk_8004C470_Pair *unkC;
    u8 pad_10[0x1C - 0x10];
} Unk_8004C470_Obj;
typedef struct Unk_8004C470_Vtbl {
    u8 pad_00[0xFC];
    void (*unkFC)(Unk_8004C470 *, void *, s32);
    u8 pad_100[0x118 - 0x100];
    void *(*unk118)(Unk_8004C470 *, s32);
} Unk_8004C470_Vtbl;
struct Unk_8004C470 {
    Unk_8004C470_Vtbl *unk0;
    u8 pad_04[0x68 - 0x4];
    Unk_800861D4 *u68;
    u8 pad_6C[0xEC - 0x6C];
    Unk_8004C470_Obj parts[7];
};
typedef struct Unk_8004CE24_Node Unk_8004CE24_Node;
struct Unk_8004CE24_Node {
    u8 pad_00[0x10];
    s32 unk10;
    u8 pad_14[0x24];
    Unk_8004CE24_Node *unk38;
};
typedef struct {
    s32 unk0;
    Unk_8004C5D0_Obj *obj;
    u8 pad_08[0x8];
    Unk_8004CE24_Node **base;
    u8 pad_14[0x8];
} Unk_8004CE24_Slot;
typedef struct Unk_8004CE24 {
    u8 pad_00[0x88];
    s32 unk88;
    u8 pad_8C[0xEC - 0x8C];
    Unk_8004CE24_Slot slots[7];
} Unk_8004CE24;
typedef struct {
    s32 slot;
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} Unk_8004CE24_Entry;
void func_80049E20(Unk_80049E20 *arg0, s32 arg1);
typedef struct Unk_80049CA8_Mgr {
    u8 pad_00[0x54];
    void (*unk54)(void *, s32 **, s32);
} Unk_80049CA8_Mgr;
typedef struct Unk_80049CA8_Ctl_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x48 - 0x8];
    void (*unk48)(void *);
} Unk_80049CA8_Ctl_Vtbl;
typedef struct Unk_80049CA8_Ctl {
    Unk_80049CA8_Ctl_Vtbl *unk0;
} Unk_80049CA8_Ctl;
typedef struct Unk_80049CA8_Sub_Vtbl {
    u8 pad_00[0x1B4];
    s32 (*unk1B4)(void *);
    void (*unk1B8)(void *, s32);
    u8 pad_1BC[0x1E0 - 0x1BC];
    s32 (*unk1E0)(void *);
} Unk_80049CA8_Sub_Vtbl;
typedef struct Unk_80049CA8_Sub {
    Unk_80049CA8_Sub_Vtbl *unk0;
} Unk_80049CA8_Sub;
typedef struct Unk_80049CA8 Unk_80049CA8;
typedef struct Unk_80049CA8_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_80049CA8_Vtbl;
struct Unk_80049CA8 {
    Unk_80049CA8_Vtbl *unk0;
    u8 pad_04[0x28 - 0x4];
    s32 unk28;
    u8 pad_2C[0x38 - 0x2C];
    Unk_80049CA8_Sub *unk38;
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    Unk_80049CA8_Ctl *unk4C;
};
extern s8 D_800868FC[];
extern s32 D_80086974[];
typedef struct Unk_8004B5BC_Ref { u8 pad_00[0x4]; Obj *u4; } Unk_8004B5BC_Ref;
typedef struct Unk_8004B5BC {
    s16 u00;
    u8 pad_02[0x0C - 0x02];
    s32 u0C[5];
    s32 u20;
    Unk_8004B5BC_Ref *u24;
    s32 u28;
} Unk_8004B5BC;
typedef struct Unk_8004B5BC_Vtbl {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
    u8 pad_34[0xF8 - 0x34];
    void (*unkF8)(void *, s32, s32 *, s32);
    u8 pad_FC[0x10C - 0xFC];
    s32 (*unk10C)(void *, Unk_8004B5BC *, s32);
    u8 pad_110[0x128 - 0x110];
    void (*unk128)(void *);
} Unk_8004B5BC_Vtbl;
typedef struct Unk_8004B5BC_Obj {
    Unk_8004B5BC_Vtbl *unk0;
    u8 pad_04[0x68 - 0x4];
    Unk_800861D4 *u68;
    u8 pad_6C[0xBC - 0x6C];
    Unk_8004B5BC u0BC;
} Unk_8004B5BC_Obj;
typedef struct Unk_8004CAF0_Entry {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Unk_8004CAF0_Entry;
typedef struct Unk_8004CAF0_Vtbl {
    u8 pad_00[0x120];
    s32 (*unk120)(void *, s32);
} Unk_8004CAF0_Vtbl;
typedef struct Unk_8004CAF0_Obj {
    Unk_8004CAF0_Vtbl *unk0;
    u8 pad_04[0x7C - 0x4];
    s16 unk7C;
    s16 unk7E;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    Unk_8004CAF0_Entry entries[8];
} Unk_8004CAF0_Obj;
typedef struct { s32 unk0; s32 unk4; s32 unk8; } Unk_8004BA40_Ent;
typedef struct { s32 unk0; s32 unk4; s32 unk8; } Unk_8004BA40_Out;
typedef struct { u8 pad_00[0x60]; s32 (*unk60)(void *, s32, s32, s32); void *unk64; Unk_800861D4 *unk68; } Unk_8004BA40_Obj;
extern s32 D_8008688C[];
extern Unk_8004BA40_Ent D_800868A8[];
typedef struct Unk_80049A14 {
    u8 pad_00[0x3C];
    s32 unk3C;
} Unk_80049A14;
extern u8 D_800865C8[];
extern u8 D_80086668[];
typedef struct Unk_8004ADC4 {
    u8 pad_00[0x60];
    s32 unk60;
    s32 unk64;
} Unk_8004ADC4;
typedef struct Unk_8004ADD0 {
    u8 pad_00[0xE8];
    s32 unkE8;
} Unk_8004ADD0;
typedef struct Unk_8004B570 {
    u8 pad_00[0x70];
    s32 unk70;
} Unk_8004B570;
typedef struct Unk_8004CFB0 {
    u8 pad_00[0x1DC];
    s32 unk1DC;
} Unk_8004CFB0;
extern u8 D_800866E8[];
extern u8 D_800869D8[];
extern char D_80086AA0[];
typedef struct Unk_8004C1C0_Obj { u8 pad_00[0x30]; s16 u30; s16 u32; } Unk_8004C1C0_Obj;
typedef struct Unk_8004C1C0_Range { u8 pad_00[0x18]; s32 unk18; s32 unk1C; s32 unk20; } Unk_8004C1C0_Range;
typedef struct Unk_8004C1C0_Pair { u8 pad_00[0x14]; Unk_8004C1C0_Range *unk14; } Unk_8004C1C0_Pair;
typedef struct Unk_8004C1C0_Ret { u8 pad_00[0x4]; Unk_8004C1C0_Obj *u4; u8 pad_08[0x4]; Unk_8004C1C0_Pair *uC; } Unk_8004C1C0_Ret;
typedef struct Unk_8004C1C0 Unk_8004C1C0;
typedef struct Unk_8004C1C0_Vtbl {
    u8 pad_00[0x118];
    Unk_8004C1C0_Ret *(*unk118)(Unk_8004C1C0 *, s32);
    Unk_8004C1C0_Ret *(*unk11C)(Unk_8004C1C0 *, s32 *);
} Unk_8004C1C0_Vtbl;
struct Unk_8004C1C0 {
    Unk_8004C1C0_Vtbl *unk0;
};
typedef struct Unk_8004C1C0_Out {
    u8 pad_00[0x2];
    s8 u2;
    s8 u3;
    s16 u4;
    u16 u6;
    s16 u8;
    s32 uC;
    s32 u10;
    s32 u14;
    s32 u18;
    s32 u1C;
    s32 u20;
    Unk_8004C1C0_Ret *u24;
    s32 u28;
} Unk_8004C1C0_Out;
typedef struct Unk_80049EB4 Unk_80049EB4;
typedef struct Unk_80049EB4_Vtbl Unk_80049EB4_Vtbl;
typedef struct Unk_80049EB4_Obj Unk_80049EB4_Obj;
typedef struct Unk_80049EB4_Tmp Unk_80049EB4_Tmp;
struct Unk_80049EB4_Vtbl {
    u8 pad_00[0x04];
    void (*unk4)(void *);
    u8 pad_08[0x48 - 0x08];
    void (*unk48)(void *);
    u8 pad_4C[0x60 - 0x4C];
    void (*unk60)(void *, s32);
    u8 pad_64[0x1B8 - 0x64];
    s32 (*unk1B8)(void *, s32);
    void (*unk1BC)(void *, void *);
};
struct Unk_80049EB4_Obj {
    Unk_80049EB4_Vtbl *unk0;
};
struct Unk_80049EB4_Tmp {
    s16 unk0;
    s16 unk2;
    s32 unk4;
};
struct Unk_80049EB4 {
    Unk_80049EB4_Vtbl *unk0;
    u8 pad_04[0x28 - 0x04];
    s32 unk28;
    u8 pad_2C[0x38 - 0x2C];
    Unk_80049EB4_Obj *unk38;
    s32 unk3C;
    u8 pad_40[0x4C - 0x40];
    Unk_80049EB4_Obj *unk4C;
};
extern void Heap_Free(void *);
extern void *func_80020C5C(void);
extern void *func_800428E4(void);
typedef struct Unk_8004A7C0_Vtbl {
    u8 pad_00[0x4];
    void *(*unk4)(void *);
    u8 pad_08[0xC - 0x8];
    void (*unkC)(void *);
    u8 pad_10[0x14 - 0x10];
    void (*unk14)(void *, void *);
    u8 pad_18[0x88 - 0x18];
    void (*unk88)(void *, s32, void *, s32);
} Unk_8004A7C0_Vtbl;
typedef struct Unk_8004A7C0_Obj {
    Unk_8004A7C0_Vtbl *unk0;
} Unk_8004A7C0_Obj;
typedef struct Unk_8004A7C0_Sub {
    Unk_8004A7C0_Vtbl *unk0;
    u8 pad_04[0x2C - 0x4];
    Unk_8004A7C0_Obj *unk2C;
} Unk_8004A7C0_Sub;
typedef struct Unk_8004A7C0_Slot {
    u8 pad_00[0x4];
    Unk_8004A7C0_Obj *unk4;
    Unk_8004A7C0_Sub *unk8;
    Unk_8004A7C0_Obj *unkC;
    Unk_8004A7C0_Obj **unk10;
    u8 pad_14[0x1C - 0x14];
} Unk_8004A7C0_Slot;
typedef struct Unk_8004A7C0 {
    Unk_8004A7C0_Vtbl *unk0;
    u8 pad_04[0xEC - 0x4];
    Unk_8004A7C0_Slot slots[7];
} Unk_8004A7C0;
s32 func_8004CAF0(Unk_8004CAF0_Obj *arg0, Unk_8004CAF0_Entry *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
s32 func_8004BCE0(Unk_8004BCE0 *arg0);
typedef struct Unk_8004BB3C_ObjVtbl {
    u8 pad_00[0x74];
    void (*unk74)(void *);
    void (*unk78)(void *, s32);
} Unk_8004BB3C_ObjVtbl;
typedef struct Unk_8004BB3C_Obj {
    Unk_8004BB3C_ObjVtbl *unk0;
    u8 pad_04[0x2A - 0x4];
    u16 u2A;
    s16 u2C;
    u8 pad_2E[0x30 - 0x2E];
    u16 u30;
} Unk_8004BB3C_Obj;
typedef struct Unk_8004BB3C_Slot {
    u16 u0;
    u8 pad_02[0x2];
    Unk_8004BB3C_Obj *obj;
    u8 pad_08[0x1C - 0x8];
} Unk_8004BB3C_Slot;
typedef struct Unk_8004BB3C_Vtbl {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32, Unk_8004BB3C_Slot *, s32);
    u8 pad_8C[0x108 - 0x8C];
    void (*unk108)(void *, Unk_8004BB3C_Slot *);
    u8 pad_10C[0x118 - 0x10C];
    Unk_8004BB3C_Slot *(*unk118)(void *, s32);
} Unk_8004BB3C_Vtbl;
typedef struct Unk_8004BB3C {
    Unk_8004BB3C_Vtbl *unk0;
    u8 pad_04[0xEC - 0x04];
    Unk_8004BB3C_Slot unkEC[7];
    s32 u1B0;
    s16 u1B4;
} Unk_8004BB3C;
typedef struct Unk_8004BB3C_Entry {
    s32 flag;
    u16 pos;
    u16 pad_06;
    s32 val;
} Unk_8004BB3C_Entry;
typedef struct Unk_8004BB3C_PosVal {
    u16 pos;
    u16 pad_02;
    s32 val;
    u8 pad_08[0x4];
} Unk_8004BB3C_PosVal;
extern u8 D_80086904[];
typedef struct Unk_8004B38C_Vtbl {
    u8 pad_00[0xF8];
    void (*unkF8)(void *, s32, s32 *, void *);
} Unk_8004B38C_Vtbl;
typedef struct Unk_8004B38C {
    Unk_8004B38C_Vtbl *unk0;
    u8 pad_04[0x54 - 0x4];
    s32 unk54[3];
    u8 pad_60[0x68 - 0x60];
    Unk_800861D4 *unk68;
    s32 unk6C;
    u8 pad_70[0xBC - 0x70];
    Unk_8004B44C unkBC;
} Unk_8004B38C;
s32 func_8004B930(Unk_8004B418 *arg0, s32 arg1, s32 arg2);
s32 func_8004BA40(Unk_8004BA40_Obj *arg0, Unk_8004BA40_Out *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern Unk_8004BA40_Out D_80086838[];
typedef struct Unk_8004B700 { u8 unk0; u8 unk1; } Unk_8004B700;
typedef struct Unk_8004A294 Unk_8004A294;
typedef struct Unk_8004A294_Vtbl {
    u8 pad_00[0x6C];
    void (*unk6C)(Unk_8004A294 *, s32);
} Unk_8004A294_Vtbl;
struct Unk_8004A294 {
    Unk_8004A294_Vtbl *vt;
};
struct Unk_80026CE8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
void func_8004A070(s32 arg0);
s32 func_8004A4C8(s32 arg0, s32 arg1);
s32 func_8004D254(void);
s32 func_80048E08(s32 arg0);
void Sym_LoadModels(void);
s32 func_8003B39C(s32 arg0);
s32 func_80043840(s32 arg0);
s32 Music_PickBank(s32 arg0);
void *func_800398E0(s32 arg0, s32 arg1, s32 arg2);
void func_80026F34(s32 arg0, s32 arg1, s32 arg2);
void *func_80042400(void);
typedef struct Unk_80049684_Vt {
    u8 pad_00[0x10];
    void (*unk10)(void *, void *);
    u8 pad_14[0x40 - 0x14];
    void (*unk40)(void *);
} Unk_80049684_Vt;
typedef struct Unk_80049684_Obj {
    u8 pad_00[0x5C];
    void (*unk5C)(void *);
    u8 pad_60[0x78 - 0x60];
    void (*unk78)(void *);
    u8 pad_7C[0x10C - 0x7C];
    void (*unk10C)(void *, void *);
    u8 pad_110[0x114 - 0x110];
    void (*unk114)(void *, void *);
} Unk_80049684_Obj;
typedef struct Unk_80049684_Sub {
    u8 pad_00[0x8];
    void *unk8;
    void *unkC;
    void *unk10;
} Unk_80049684_Sub;
typedef struct Unk_80049684 {
    Unk_80049684_Vt *unk0;
    u8 pad_04[0xC - 0x4];
    Unk_80049684_Sub *unkC;
    u8 pad_10[0x34 - 0x10];
    void *unk34;
    s32 unk38;
    u8 pad_3C[0x40 - 0x3C];
    void *unk40;
    void **unk44;
    void *unk48;
} Unk_80049684;
void GsLinkObject4(s32 objp, void *packet, s32 id);
typedef struct Unk_8004BE54_Vtbl {
    u8 pad_00[0x78];
    void *(*f78)(void *, void *, s32);
} Unk_8004BE54_Vtbl;
typedef struct Unk_8004BE54_Vtbl2 {
    u8 pad_00[0x4];
    void (*f04)(void *);
} Unk_8004BE54_Vtbl2;
typedef struct Unk_8004BE54_Obj {
    Unk_8004BE54_Vtbl2 *vt;
} Unk_8004BE54_Obj;
typedef struct Unk_8004BE54_D {
    u8 pad_00[0x4];
    s32 u4;
    s32 u8;
} Unk_8004BE54_D;
typedef struct Unk_8004BE54_B {
    u8 pad_00[0x10];
    Unk_8004BE54_D *u10;
} Unk_8004BE54_B;
typedef struct Unk_8004BE54_C {
    Unk_8004BE54_Vtbl *vt;
    u8 pad_04[0xC];
    void *u10;
    s32 u14;
    u8 pad_18[0x14];
    Unk_8004BE54_Obj *u2C;
} Unk_8004BE54_C;
typedef struct Unk_8004BE54_E Unk_8004BE54_E;
typedef struct Unk_8004BE54 {
    u8 pad_00[0x4];
    Unk_8004BE54_B *u4;
    Unk_8004BE54_C *u8;
    u8 pad_0C[0x4];
    Unk_8004BE54_E **u10;
} Unk_8004BE54;
typedef struct Unk_8004BE54_Vec {
    s32 x, y, z;
} Unk_8004BE54_Vec;
typedef struct Unk_8004BE54_Buf {
    u8 pad_00[0xC];
    Unk_8004BE54_Vec pos;
    u8 pad_18[0x2];
    u16 u1A;
    u8 pad_1C[0x12];
    u16 u2E;
    s32 u30;
    s32 u34;
    u8 pad_38[0x8];
} Unk_8004BE54_Buf;
typedef struct Unk_8004BE54_G {
    u8 pad_00[0x10];
    u16 u10;
    u16 u12;
    u16 u14;
} Unk_8004BE54_G;
typedef struct Unk_8004BE54_F {
    s32 u0;
    u8 pad_04[0x14];
    Unk_8004BE54_Vec pos;
    u8 pad_24[0x20];
    Unk_8004BE54_G *u44;
} Unk_8004BE54_F;
typedef struct Unk_8004BE54_H {
    u8 pad_00[0x10];
    s32 u10;
} Unk_8004BE54_H;
struct Unk_8004BE54_E {
    u8 pad_00[0x10];
    s32 u10;
    Unk_8004BE54_F *u14;
    s32 u18;
    u8 pad_1C[0x4];
    Unk_8004BE54_H *u20;
    u8 pad_24[0x12];
    u16 u36;
    s32 u38;
};
s32 func_8004D38C(void);
extern void *func_80048894(void);
extern void *func_8002C12C(s32);
typedef struct Unk_8004A534_Vec { s32 unk0; s32 unk4; s32 unk8; } Unk_8004A534_Vec;
extern Unk_8004A534_Vec D_8008682C;
typedef struct Unk_8004A534_ObjVtbl {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32);
} Unk_8004A534_ObjVtbl;
typedef struct Unk_8004A534_Obj {
    Unk_8004A534_ObjVtbl *unk0;
    u8 pad_04[0x10 - 0x4];
    s32 unk10;
    u8 pad_14[0x20 - 0x14];
    u16 unk20;
    u8 pad_22[0x32 - 0x22];
    s16 id;
} Unk_8004A534_Obj;
typedef struct Unk_8004A534_ElemVtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *, void *, void *);
    u8 pad_50[0x70 - 0x50];
    void (*unk70)(void *, s32);
} Unk_8004A534_ElemVtbl;
typedef struct Unk_8004A534_Elem {
    Unk_8004A534_ElemVtbl *unk0;
    u8 pad_04[0x10 - 0x4];
    s32 unk10;
} Unk_8004A534_Elem;
typedef struct Unk_8004A534_Slot {
    u16 unk0;
    u16 unk2;
    Unk_8004A534_Obj *unk4;
    void *unk8;
    Unk_8004A534_Elem *unkC;
    void **unk10;
    s32 unk14;
    s32 unk18;
} Unk_8004A534_Slot;
typedef struct Unk_8004A534 {
    Unk_8004A4C8 *unk0;
    u8 pad_04[0x54 - 0x4];
    Unk_8004A534_Vec unk54;
    u8 pad_60[0x6C - 0x60];
    s32 unk6C;
    s32 unk70;
    u8 pad_74[0xE8 - 0x74];
    s32 unkE8;
    Unk_8004A534_Slot slots[7];
    s32 unk1B0;
    u16 unk1B4;
    u8 pad_1B6[0x1B8 - 0x1B6];
    s32 unk1B8;
    u8 pad_1BC[0x1E0 - 0x1BC];
    s32 unk1E0;
    u8 pad_1E4[0x1E8 - 0x1E4];
} Unk_8004A534;
typedef struct Unk_8004CDA4_Entry {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8004CDA4_Entry;
typedef struct Unk_8004CDA4_Obj Unk_8004CDA4_Obj;
typedef struct Unk_8004CDA4_Vt {
    u8 pad0[0x124];
    s32 (*unk124)(Unk_8004CDA4_Obj *, s32);
} Unk_8004CDA4_Vt;
struct Unk_8004CDA4_Obj {
    Unk_8004CDA4_Vt *unk0;
    u8 pad4[0x88];
    Unk_8004CDA4_Entry entries[1];
};
extern Unk_8004CDA4_Entry D_80086990;
typedef struct Unk_8004CD38 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
} Unk_8004CD38;
/* Returns 0 when the point (arg1[0], arg1[1]) lies inside the box, 1 otherwise or without a box. */
extern Unk_8004C6A8_M D_8008E98C;
void RotMatrix(void *, void *);
void ApplyMatrixLV(s32 *, void *, void *);

s32 func_800494B4(void) {
    return 0xE;
}

Unk_800861D4 *func_800494BC(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 14;
    }
    return D_800861D4;
}

Unk_800861D4 *func_800494D8(s32 arg0) {
    return &func_800494BC(NULL)[arg0];
}

u32 Stage_FindChunkByMood(Unk_8004950C *arg0, s16 *arg1) {
    u32 i;
    s32 a2;
    s32 a3;
    s32 rows;
    s32 cols;
    s16 *p;

    for (i = 0; i < 0xE; i++) {
        p = D_80086590[i];
        rows = D_800861D6[i].unk_0;
        cols = D_800861D4[i].unk_0;
        for (a3 = 0; a3 < rows; a3++) {
            for (a2 = 0; a2 < cols; a2++) {
                if (*arg1 == *p) {
                    arg0->unk0 = a2;
                    arg0->unk1 = a3;
                    return i;
                }
                p++;
            }
        }
    }
    return -1;
}

s16 *Stage_GetChunkMood(s32 arg0, s8 *arg1) {
    return D_80086590[arg0] + arg1[1] * D_800861D4[arg0].unk_0 + arg1[0];
}

s32 func_80049608(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = Heap_Alloc(0x50);
    if (temp_v0 != 0) {
        func_8004A060()->unk8(temp_v0, arg0, arg1, arg2);
        return temp_v0;
    }
    return 0;
}

void func_80049684(Unk_80049684 *arg0, Unk_80049684_Sub *arg1, Unk_80049684_Obj **arg2, s32 arg3) {
    struct Unk_80026CE8 sp10;
    s32 temp_s0;
    Unk_80049684_Obj **temp_v0;
    Unk_80049684_Obj **temp_a0;

    temp_s0 = func_80048E08(0);
    func_8004A4B8()->unk8(arg0, temp_s0, 0);
    arg0->unk0 = (Unk_80049684_Vt *)func_8004A060();
    Sym_LoadModels();
    temp_v0 = (Unk_80049684_Obj **)func_8003B39C((s32)"ETC\\ETC.TIM");
    arg0->unk44 = temp_v0;
    (*temp_v0)->unk78(temp_v0);
    temp_a0 = arg0->unk44;
    (*temp_a0)->unk5C(temp_a0);
    sp10.unk0 = 0;
    sp10.unk4 = (s32)"ETC\\DREAMER.TMD";
    arg0->unk48 = (void *)func_80043840((s32)&sp10);
    arg0->unk40 = func_800398E0(Music_PickBank(0), 0, 1);
    func_8004A070(1);
    func_80026F34(arg3 == 0, 1, 1);
    arg0->unkC = arg1;
    arg1->unk10 = (void *)func_8004D254();
    arg1->unk8 = func_80042400();
    arg1->unkC = (void *)func_8004A4C8(0, 1);
    arg0->unk38 = (s32)arg2;
    arg0->unk0->unk10(arg0, arg2);
    (*arg2)->unk10C(arg2, arg0->unk34);
    (*arg2)->unk114(arg2, arg0->unk44);
    arg0->unk0->unk40(arg0);
}

void func_80049830(Unk_80049830 *arg0) {
    Unk_80049830_Sub *temp_s0;

    temp_s0 = arg0->unkC;
    arg0->unk0->unk14(arg0, arg0->unk38);
    temp_s0->unkC = temp_s0->unkC->unk0->unk4(temp_s0->unkC);
    temp_s0->unk8 = temp_s0->unk8->unk0->unk4(temp_s0->unk8);
    temp_s0->unk10 = temp_s0->unk10->unk0->unk4(temp_s0->unk10);
    arg0->unk40->unk0->unk4(arg0->unk40);
    arg0->unk48->unk0->unk4(arg0->unk48);
    arg0->unk44->unk0->unk4(arg0->unk44);
    Sym_FreeModels();
    ((Unk_80049830_Mgr *)((Unk_8004A130_80049830 *)func_8004A4B8()))->unkC(arg0);
}

void func_80049958(Unk_80049958 *arg0, s32 **arg1, s32 arg2) {
    s32 code;

    func_8004A4B8()->unk38(arg0, arg1, arg2);
    code = **arg1;
    if ((code & 0xFFFF) == 0x1F34) {
        arg0->unk0->unk80(arg0, arg1, arg2);
    } else if ((code & 0xFFFFF) == 0x2F230) {
        arg0->unk0->unk84(arg0, arg1, arg2);
    }
}

void func_80049A14(Unk_80049A14 *arg0) {
    arg0->unk3C = 0;
}

void func_80049A1C(Unk_80049A1C *arg0) {
    Unk_80049A1C_Obj *temp_s0;

    temp_s0 = arg0->unk38;
    temp_s0->unk0->unk10(temp_s0, arg0->unkC->unk4);
    temp_s0->unk0->unk10(temp_s0, arg0->unkC->unk8);
    temp_s0->unk0->unk110(temp_s0, arg0->unkC->unk10);
    ((Unk_80049A1C_Mgr *)func_8004A4B8())->unk44(arg0, arg0->unkC, 0);
}

void func_80049AC0(Unk_80049AC0 *arg0) {
    Unk_80049AC0_Obj *temp_s0;

    temp_s0 = arg0->unk38;
    ((Unk_80049AC0_Mgr *)func_8004A4B8())->unk48(arg0);
    temp_s0->unk0->unk110(temp_s0, 0);
    temp_s0->unk0->unk14(temp_s0, arg0->unkC->unk4);
    temp_s0->unk0->unk14(temp_s0, arg0->unk10);
}

void func_80049B54(Unk_80049B54 *arg0) {
    Unk_80049B54_Obj *temp_a0;
    Unk_80049B54_Obj *temp_s0;
    Unk_80049B54_Obj *temp_v0;

    temp_a0 = *arg0->unkC;
    temp_s0 = arg0->unk18;
    temp_s0->unk0->unk44(temp_s0, temp_a0->unk0->unk7C(temp_a0, 0));
    temp_v0 = temp_s0->unk0->unkAC(temp_s0);
    temp_v0->unk0->unk60(temp_v0, 1);
    temp_s0->unk0->unk4C(temp_s0, 0x4B0);
    temp_s0->unk0->unk70(temp_s0, arg0->unk38, D_80086650, D_8008665C, 0);
    temp_s0->unk0->unk8C(temp_s0);
    arg0->unk3C = 1;
}

void func_80049C50(Unk_80049C50 *arg0) {
    Unk_80049C50_Obj *temp_s0;

    temp_s0 = arg0->unk18;
    temp_s0->unk0->unk90(temp_s0);
    temp_s0->unk0->unk74(temp_s0);
}

void func_80049CA8(Unk_80049CA8 *arg0, s32 **arg1, s32 arg2) {
    s32 temp;

    ((Unk_80049CA8_Mgr *)func_8004A4B8())->unk54(arg0, arg1, arg2);
    if (arg2 != 2) {
        return;
    }
    if (arg0->unk3C == arg2) {
        return;
    }
    switch (arg0->unk3C) {
    case 2:
        return;
    case 1:
        temp = arg0->unk38->unk0->unk1B4(arg0->unk38);
        if (temp < 0) {
            arg0->unk38->unk0->unk1B8(arg0->unk38, 0);
            arg0->unk28 = arg2;
            arg0->unk0->unk60(arg0, 3);
            return;
        }
        break;
    case 3:
        arg0->unk4C->unk0->unk48(arg0->unk4C);
        arg0->unk4C->unk0->unk4(arg0->unk4C);
        temp = arg0->unk38->unk0->unk1E0(arg0->unk38);
        break;
    default:
        return;
    }
    func_80049E20((Unk_80049E20 *)arg0, temp);
}

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

void func_80049EB4(Unk_80049EB4 *arg0, s32 arg1, s32 arg2) {
    Unk_80049EB4_Obj *temp_a0;
    Unk_80049EB4_Obj *temp_a1;
    Unk_80049EB4_Vtbl *vt;
    Unk_80049EB4_Tmp tmp;
    s32 var_a1;
    s32 var_v1;

    switch (arg2) {
    case 4:
        temp_a0 = arg0->unk4C;
        temp_a0->unk0->unk48(temp_a0);
        temp_a0 = arg0->unk4C;
        temp_a0->unk0->unk4(temp_a0);
        temp_a0 = arg0->unk38;
        if (temp_a0->unk0->unk1B8(temp_a0, 0) == 0) {
            temp_a1 = arg0->unk38;
            temp_a1->unk0->unk1BC(&tmp, temp_a1);
            var_v1 = 2;
            if (tmp.unk2 < 0) {
                var_v1 = 1;
            }
            arg0->unk28 = var_v1;
        } else {
            arg0->unk28 = 3;
        }
        arg0->unk0->unk60(arg0, 3);
        return;
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        arg0->unk3C = 3;
        return;
    case 12:
    case 13:
        temp_a0 = arg0->unk4C;
        temp_a0->unk0->unk48(temp_a0);
        temp_a0 = arg0->unk4C;
        temp_a0->unk0->unk4(temp_a0);
        temp_a0 = arg0->unk38;
        vt = temp_a0->unk0;
        var_a1 = 1;
        if (arg2 != 12) {
            var_a1 = 2;
        }
        vt->unk1B8(temp_a0, var_a1);
        arg0->unk28 = 3;
        arg0->unk0->unk60(arg0, 3);
        return;
    default:
        return;
    }
}

Unk_80049608 *func_8004A060(void) {
    return (Unk_80049608 *)D_800865C8;
}

void func_8004A070(s32 arg0) {
    s32 sp10;
    s32 temp_s1;

    temp_s1 = (s32)func_80048D48(&sp10);
    switch (++D_8008A978) {
    case 1:
        if (arg0 != 0) {
            D_8008A978++;
        } else {
            D_8008A97C = sp10 /= 2;
        }
        break;
    case 2:
        sp10 -= D_8008A97C;
        break;
    default:
        sp10 = 0;
        break;
    }
    do {
    } while (func_80027024(temp_s1, sp10) == 0);
}

s32 func_8004A130(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = Heap_Alloc(0x38);
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

void func_8004A294(Unk_8004A294 *arg0) {
    arg0->vt->unk6C(arg0, -1);
}

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

Unk_8004A130 *func_8004A4B8(void) {
    return (Unk_8004A130 *)D_80086668;
}

s32 func_8004A4C8(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = Heap_Alloc(0x1E8);
    if (temp_s0 != 0) {
        func_8004D244()->unk8(temp_s0, arg0, arg1);
        return temp_s0;
    }
    return 0;
}

void func_8004A534(Unk_8004A534 *arg0, Unk_8004A534_Vec *arg1, s32 arg2) {
    Unk_8004A534_Vec sp10;
    Unk_8004A534_Slot *slot;
    Unk_8004A534_Obj *obj;
    Unk_8004A534_Elem *elem;
    void **p;
    void **end;
    s32 i;

    ((Unk_8004D254 *)func_800428E4())->unk8((s32)arg0);
    arg0->unk0 = func_8004D244();
    if (arg1 != NULL) {
        arg0->unk54 = *arg1;
    } else {
        arg0->unk54 = D_8008682C;
    }
    arg0->unk1B0 = 0;
    arg0->unk1B4 = 0;
    arg0->unk1B8 = 0;
    arg0->unk70 = 0;
    arg0->unk6C = 0;
    arg0->unkE8 = 0;
    arg0->unk1E0 = 0;
    for (i = 0; i < 7; i++) {
        slot = &arg0->slots[i];
        slot->unk4 = func_80048894();
        slot->unk4->unk20 = (slot->unk4->unk10 != 0);
        slot->unk4->id = i;
        obj = slot->unk4;
        obj->unk0->unk88(obj, arg2);
        slot->unk14 = 0;
        slot->unk18 = 0;
        slot->unk2 = i;
        slot->unk0 = 0;
        slot->unk8 = func_8002C12C(0);
        elem = (Unk_8004A534_Elem *)func_8004D38C();
        slot->unkC = elem;
        elem->unk0->unk4C(elem, arg0, &arg0->unk54);
        slot->unk10 = (void **)Heap_Alloc(0x668);
        if (slot->unk10 == NULL) {
            return;
        }
        sp10.unk0 = 0x400;
        sp10.unk4 = 0;
        sp10.unk8 = 0x400;
        end = (void **)((u8 *)slot->unk10 + 0x668);
        for (p = slot->unk10; p < end; p++) {
            elem = (Unk_8004A534_Elem *)func_8004D38C();
            *p = elem;
            elem->unk0->unk4C(elem, slot->unkC, &sp10);
            sp10.unk0 += 0x800;
            if (sp10.unk0 > 0xA400) {
                sp10.unk0 = 0x400;
                sp10.unk8 += 0x800;
            }
            elem = (Unk_8004A534_Elem *)*p;
            elem->unk0->unk70(elem, 1);
            elem = (Unk_8004A534_Elem *)*p;
            elem->unk10 = (s32)(elem->unk10 | 0x80000000);
        }
    }
    arg0->unk0->unk10(arg0, func_80020C5C());
    arg0->unk0->unk40(arg0);
}

void func_8004A7C0(Unk_8004A7C0 *arg0) {
    Unk_8004A7C0_Slot *slot;
    Unk_8004A7C0_Obj *obj;
    Unk_8004A7C0_Obj **p;
    Unk_8004A7C0_Obj **end;
    s32 i;

    arg0->unk0->unk14(arg0, func_80020C5C());
    for (i = 0; i < 7; i++) {
        slot = &arg0->slots[i];
        arg0->unk0->unk88(arg0, 6, slot, i);
        if (slot->unk4 != NULL) {
            slot->unk4->unk0->unk4(slot->unk4);
        }
        if (slot->unk8 != NULL) {
            if (slot->unk8->unk2C != NULL) {
                slot->unk8->unk2C->unk0->unk4(slot->unk8->unk2C);
            }
            slot->unk8 = (Unk_8004A7C0_Sub *)slot->unk8->unk0->unk4(slot->unk8);
        }
        if (slot->unkC != NULL) {
            slot->unkC->unk0->unk4(slot->unkC);
        }
        end = slot->unk10 + 410;
        for (p = slot->unk10; p < end; p++) {
            obj = *p;
            if (obj != NULL) {
                obj->unk0->unk4(obj);
            }
        }
        Heap_Free(slot->unk10);
    }
    ((Unk_8004A7C0_Vtbl *)func_800428E4())->unkC(arg0);
}

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

void func_8004AA6C(Unk_8004AA6C_Obj *arg0, s32 arg1, Unk_8004AA6C_Arg *arg2) {
    Unk_8004AA6C_Sub *temp;

    ((Unk_8004AA6C_Ret *)func_8001E57C())->unk88(arg0, arg1);
    switch (arg1) {
    case 6:
        temp = arg2->unk14;
        if (temp != NULL) {
            arg2->unk14 = temp->unk0->unk4(temp);
        }
        /* fallthrough */
    case 7:
        arg0->unk1BC = arg2;
        arg0->unk0->unk30(arg0, arg1);
        return;
    }
}

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

void func_8004ABD0(Unk_8004ABD0 *arg0) {
    Unk_8004ABD0_Slot *slot;
    Unk_8004ABD0_Sub *sub;
    s32 i;

    for (i = 0; i < 7; i++) {
        slot = &arg0->unkEC[i];
        slot->unk4->unk0->unk74(slot->unk4);
        slot->unk0 = 0;
        arg0->unk0->unk108(arg0, slot);
        sub = slot->unk8;
        if (sub->unk2C != NULL) {
            sub->unk2C = sub->unk2C->unk0->unk4(sub->unk2C);
        }
        arg0->unk0->unk88(arg0, 6, slot, i);
        slot->unk4->unk0->unk84(slot->unk4);
    }
    arg0->unk1B8 = 0;
    arg0->unk1B4 = 0;
    arg0->unk0->unk140(arg0);
}

void func_8004ACF8(Unk_8004ACF8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    Unk_8004ACF8_Child *child;

    for (i = 0; i < arg1; i++) {
        child = arg0->unk0->unkB8(arg0, i);
        child->unk0->unk44(child, 1, arg3);
        arg3 += 3;
        child->unk0->unk48(child, 1, arg2);
        arg2 += 6;
    }
}

void func_8004ADC4(Unk_8004ADC4 *arg0, s32 arg1, s32 arg2) {
    arg0->unk60 = arg1;
    arg0->unk64 = arg2;
}

void func_8004ADD0(Unk_8004ADD0 *arg0, s32 arg1) {
    arg0->unkE8 = arg1;
}

void func_8004ADD8(Unk_8004ADD8 *arg0, s32 **arg1, s32 arg2) {
    s32 *var_s0;
    s32 unused[6];

    switch (arg2) {
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
        var_s0 = arg0->unkE8;
        if ((var_s0 != NULL) && (*var_s0 != 0)) {
            do {
                if (*var_s0 == **arg1) {
                    arg0->unk0->unk12C(arg0, arg1, arg2);
                }
                var_s0++;
            } while (*var_s0 != 0);
        }
        break;
    }
}

s32 func_8004AEA4(Unk_8004AEA4 *arg0, Unk_8004AEA4_Arg *arg1, s32 arg2) {
    Unk_8004AEA4_Elem buf[3];
    Unk_8004AEA4_Elem out[3];
    Unk_8004AEA4_Elem *src;
    Unk_8004AEA4_Elem *dst;
    s32 saved;
    s32 ret;
    s32 a2;

    if (arg1->unkC != 0) {
        a2 = arg1->unk14 + 0x38;
    } else {
        a2 = 0;
    }
    ret = arg0->unk0->unk110(arg0, out, a2);
    if (ret != 0) {
        return ret;
    }
    saved = arg0->unk88;
    dst = buf;
    src = arg0->unk8C;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != &arg0->unk8C[3]);
    if (arg0->unk68->unk_4 == 0) {
        func_8004AFE0(arg0, out, 3);
    } else {
        func_8004B030(arg0, out, 3);
    }
    func_8004B100(arg0, arg1, arg2);
    arg0->unk88 = saved;
    dst = arg0->unk8C;
    src = buf;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != &buf[3]);
}

void func_8004AFE0(Unk_8004AFE0 *arg0, s8 *arg1, s32 arg2) {
    arg0->u7C = arg1[2] - 1;
    arg0->u7E = arg1[3] - 1;
    arg0->u80 = arg2;
    arg0->u84 = arg2;
    func_8004C93C();
}

void func_8004B030(Unk_8004B030_Obj *arg0, Unk_8004B030_Arg *arg1, s32 arg2) {
    s32 left = arg1->unk2;
    s32 top = arg1->unk3;
    s32 bottom = arg2;
    s32 right = bottom;
    s32 x = left;
    s32 y = top;

    if (x == 0) {
        right--;
    } else {
        left--;
    }
    if (x == 0x13) {
        right--;
    }
    if (y == 0) {
        bottom--;
    } else {
        top--;
    }
    if (y == 0x13) {
        bottom--;
    }
    arg0->unk88 = 1;
    arg0->unk8C = arg0->unk0->unk124(arg0, arg1->unk28);
    arg0->unk90 = left;
    arg0->unk92 = top;
    arg0->unk94 = right;
    arg0->unk96 = bottom;
}

void func_8004B100(Unk_8004AEA4 *arg0, Unk_8004AEA4_Arg *arg1, s32 arg2) {
    Unk_8004B100_Elem *e;
    Unk_8004B100_Slot *slot;
    Unk_8004B2D4 **row;
    Unk_8004B2D4 *node;
    s32 i;
    s32 j;
    s32 k;

    e = (Unk_8004B100_Elem *)arg0->unk8C;
    for (i = 0; i < arg0->unk88; i++) {
        slot = &arg0->slots[e->idx];
        if (slot->unk4->unk2C != 0) {
            row = slot->unk10 + e->a + e->b * 20;
            for (j = 0; j < e->d; j++) {
                for (k = 0; k < e->c; k++) {
                    arg0->unk1C0 = arg0->unkBC;
                    arg0->unk1C2 = e->a + k;
                    arg0->unk1C3 = e->b + j;
                    func_8004B2D4(*row, arg1, arg2);
                    node = (*row)->unk38;
                    while (node != NULL) {
                        func_8004B2D4(node, arg1, arg2);
                        node = node->unk38;
                    }
                    row++;
                }
                row += 20 - e->c;
            }
        }
        e++;
    }
}

void func_8004B2D4(Unk_8004B2D4 *arg0, Unk_8004AEA4_Arg *arg1, s32 arg2) {
    if ((arg0 != NULL) && (arg0->unk36 & 0x80)) {
        arg0->unk0->unk38(arg0);
    }
}

s32 func_8004B31C(s32 arg0) {
    return arg0 + 0x1C0;
}

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

void func_8004B38C(Unk_8004B38C *arg0, s32 *arg1, s32 arg2, Unk_8004B44C *arg3) {
    s32 sp18[3];

    arg0->unk6C = arg2;
    arg0->unkBC = *arg3;
    arg0->unk0->unkF8(arg0, func_8004B44C(arg1, sp18, arg0->unk68, arg0->unk54, arg3), sp18, D_80086904);
}

void func_8004B418(Unk_8004B418 *arg0, s32 *arg1, void *arg2) {
    s32 sp18[3];
    func_8004B44C(arg1, sp18, arg0->u68, arg0->u54, arg2);
}

s32 func_8004B44C(s32 *arg0, s32 *arg1, Unk_800861D4 *arg2, s32 *arg3, Unk_8004B44C *arg4) {
    s32 t0;
    s32 t1;
    s32 t4;
    s32 temp;
    s32 x;
    s32 bx;
    s32 bz;
    s32 ox;
    s32 oz;

    if (arg2->unk_4 == 0) {
        t0 = arg4->b;
        t1 = arg2->unk_2;
        t4 = arg4->a + arg2->unk_0 * t0;
    } else {
        t1 = 1;
        t0 = 0;
        t4 = 0;
    }
    temp = (arg3[0] - arg2->unk_0 * 0x5000) + arg4->a * 0xA000;
    x = arg3[2] - t1 * 0x5000;
    arg1[0] = temp;
    if (t0 & 1) {
        arg1[0] = temp - 0x5000;
    }
    arg1[1] = arg3[1];
    arg1[2] = x + t0 * 0xA000;
    bx = (arg4->c << 11) + arg1[0];
    ox = arg4->e + 0x400;
    arg0[0] = bx + ox;
    arg0[1] = arg4->f + arg1[1];
    bz = (arg4->d << 11) + arg1[2];
    oz = arg4->g + 0x400;
    arg0[2] = bz + oz;
    arg1[0] += 0x5000;
    arg1[2] += 0x5000;
    return t4;
}

void func_8004B570(Unk_8004B570 *arg0) {
    arg0->unk70 = 1;
}

void func_8004B57C(Unk_8004B57C *arg0) {
    arg0->unk0->unkC0(arg0);
    arg0->unk70 = 0;
}

s32 func_8004B5BC(Unk_8004B5BC_Obj *obj) {
    Unk_8004B5BC loc;
    s16 prev;
    s32 temp;

    if (obj->unk0->unk10C(obj, &loc, 0) == 0) {
        return 0;
    }
    temp = D_800868FC[loc.u24->u4->id];
    if (obj->u68->unk_4 == 0) {
        obj->unk0->unkF8(obj, loc.u28, loc.u0C, D_80086974[temp]);
    }
    obj->unk0->unk128(obj);
    prev = obj->u0BC.u00;
    obj->u0BC = loc;
    if (prev != loc.u00) {
        obj->unk0->unk30(obj, 5);
    }
    return temp;
}

void func_8004B700(Unk_8004C470 *arg0, s32 arg1, Unk_8004BA40_Out *arg2, Unk_8004B700 *arg3) {
    Unk_8004BA40_Out buf[7];
    s32 sp78;
    s32 step;
    s32 phase;
    s32 i;
    s32 n;
    Unk_8004C470_Obj *part;
    Unk_8004C470_Range *r;
    Unk_8004BA40_Out *ofs;

    if (arg3 != NULL) {
        step = arg0->u68->unk_0;
        n = 0;
        phase = (arg1 / step) & 1;
        sp78 = func_8004B930((Unk_8004B418 *)arg0, arg1, phase);
        for (i = 0; i < 7; i++, arg3++) {
            part = arg0->unk0->unk118(arg0, i);
            part->unk2 = arg3->unk0;
            if (arg3->unk1 != 0) {
                ofs = &D_80086838[arg3->unk0];
                r = part->unkC->unk14;
                if (arg0->u68->unk_4 == 0) {
                    r->unk18 = arg2->unk0 + ofs->unk0;
                    r->unk1C = arg2->unk4;
                    r->unk20 = arg2->unk8 + ofs->unk8;
                } else {
                    r->unk18 = arg2->unk0 - 0x5000;
                    r->unk1C = arg2->unk4 + ofs->unk4;
                    r->unk20 = arg2->unk8 - 0x5000;
                }
                part->unkC->unk14->unk0 = 0;
                func_8004BA40((Unk_8004BA40_Obj *)arg0, &buf[n], step, phase, arg1, sp78, arg3->unk0);
                n++;
            }
        }
        for (i = 0; i < 7; i++) {
            part = &arg0->parts[i];
            part->unk4->unk32 = part->unk2;
        }
        arg0->unk0->unkFC(arg0, buf, n);
    }
}

s32 func_8004B930(Unk_8004B418 *arg0, s32 arg1, s32 arg2) {
    Unk_800861D4 *grid;
    s32 width;
    s32 height;
    s32 mask;
    s32 i;

    grid = arg0->u68;
    width = grid->unk_0;
    height = grid->unk_2;
    if (grid->unk_4 == 0) {
        mask = -(arg1 < width) & 3;
        if (arg1 >= width * (height - 1)) {
            mask |= 0x60;
        }
        if (arg1 % width == 0) {
            if (arg2 != 0) {
                mask |= 0x25;
            } else {
                mask |= 4;
            }
        }
        if ((arg1 + 1) % width == 0) {
            if (arg2 != 0) {
                mask |= 0x10;
            } else {
                mask |= 0x52;
            }
        }
    } else {
        mask = -1;
        for (i = 0; i < height; i++) {
            mask *= 2;
        }
    }
    return ~mask;
}

s32 func_8004BA40(Unk_8004BA40_Obj *arg0, Unk_8004BA40_Out *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Unk_8004BA40_Ent *ent;
    s32 v;

    if (arg5 & D_8008688C[arg6]) {
        if (arg0->unk68->unk_4 != 0) {
            arg1->unk4 = arg4 + arg6;
        } else {
            ent = &D_800868A8[arg6];
            if (ent->unk0 == 0) {
                v = ent->unk4;
                arg1->unk4 = arg4 + v;
            } else {
                v = arg2 * ent->unk0;
                if (arg3 != 0) {
                    v += ent->unk4;
                } else {
                    v += ent->unk8;
                }
                arg1->unk4 = arg4 + v;
            }
        }
        arg1->unk0 = arg0->unk60(arg0->unk64, arg1->unk4, 0, 0);
        arg1->unk8 = arg6;
        return 1;
    }
    arg1->unk0 = 0;
    arg1->unk8 = arg6;
    return 0;
}

void func_8004BB3C(Unk_8004BB3C *arg0, Unk_8004BB3C_Entry *arg1, s32 arg2) {
    s32 i;
    Unk_8004BB3C_Slot *slot;

    for (i = 0; i < arg2; arg1++, i++) {
        slot = arg0->unk0->unk118(arg0, arg1->val);
        arg0->unk0->unk88(arg0, 6, slot, i);
        if (arg1->flag != 0) {
            if (slot->obj->u2C != 0) {
                arg0->unk0->unk108(arg0, slot);
            }
            slot->obj->u30 = arg1->pos;
            slot->obj->unk0->unk78(slot->obj, arg1->flag);
            slot->u0 = 1;
            arg0->u1B0 = 1;
        } else {
            if (slot->obj->u2C != 0) {
                arg0->unk0->unk108(arg0, slot);
            }
            if (slot->obj->u2A != 0) {
                slot->obj->unk0->unk74(slot->obj);
                slot->u0 = 0;
            }
        }
    }
    arg0->u1B4 = func_8004BCE0((Unk_8004BCE0 *) arg0);
}

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

void func_8004BD14(Unk_8004BD14 *arg0, s32 arg1, s32 arg2) {
    Unk_8004BD14_Slot *slot;
    Unk_8004BD14_Obj *obj;
    s32 i;
    s32 state;
    u16 temp;

    if (arg2 == 2) {
        for (i = 0; i < 7; i++) {
            slot = &arg0->slots[i];
            obj = slot->obj;
            if (obj->u2E != 0) {
                obj->u2E = 0;
                arg0->unk0->unk88(arg0, 7, slot, i);
            }
            state = arg0->u1B0;
            if (state == 1 && slot->u0 != 0) {
                obj = slot->obj;
                if (obj->u2C != 0) {
                    arg0->unk0->unk104(arg0, slot);
                    slot->obj->u2C = 2;
                    slot->u0 = 0;
                    temp = arg0->u1B4 - 1;
                    arg0->u1B4 = temp;
                    if (temp == 0) {
                        arg0->u1B4 = 0;
                        arg0->u1B0 = 0;
                        arg0->u1B8 = state;
                    }
                } else if (obj->u2A == 0) {
                    slot->u0 = 0;
                }
            }
        }
    }
}

void func_8004BE54(void *a0, Unk_8004BE54 *a1) {
    Unk_8004BE54_Buf sp10;
    void *sp50[4];
    Unk_8004BE54_B *b;
    Unk_8004BE54_D *d;
    Unk_8004BE54_C *obj;
    Unk_8004BE54_E **slot;
    Unk_8004BE54_G *g;
    void *r;
    s32 i;
    s32 j;
    s32 n8;
    Unk_8004BE54_E **base;

    b = a1->u4;
    obj = a1->u8;
    obj->u10 = (u8 *)b->u10 + b->u10->u4;
    obj->u14 = 0;
    if (obj->u2C != NULL) {
        obj->u2C->vt->f04(obj->u2C);
    }
    d = b->u10;
    n8 = d->u8;
    sp50[0] = (u8 *)d + d->u4 + n8;
    obj->u2C = (Unk_8004BE54_Obj *)func_80043840((s32)sp50);
    sp10.u34 = 0;
    i = 0;
    j = 400;
    for (;;) {
        r = obj->vt->f78(obj, &sp10, i);
        if (r == NULL) {
            break;
        }
        if (r == (void *)-1) {
            slot = &a1->u10[i];
            (*slot)->u10 |= 0x80000000;
            (*slot)->u20 = NULL;
            (*slot)->u18 = 0;
        } else {
            base = a1->u10;
            if (sp10.u30 != 0) {
                slot = &base[j++];
            } else {
                slot = &base[i];
            }
            (*slot)->u20 = r;
            (*slot)->u18 = (*slot)->u20->u10;
            GsLinkObject4((*slot)->u20->u10, (u8 *)(*slot) + 0x10, 0);
            (*slot)->u14->pos = sp10.pos;
            g = (*slot)->u14->u44;
            g->u10 = 0;
            g->u12 = sp10.u1A;
            g->u14 = 0;
            (*slot)->u36 = sp10.u2E;
            (*slot)->u14->u0 = 0;
            (*slot)->u10 |= 0x80000000;
        }
        if (sp10.u34 != 0) {
            (*slot)->u38 = (s32)a1->u10[j];
        } else {
            i++;
            (*slot)->u38 = 0;
        }
    }
}

void func_8004C0AC(s32 arg0, Unk_8004C0AC *arg1) {
    Unk_8004C0AC_Elem **p;
    Unk_8004C0AC_Elem **end;

    if (arg1->unk4->unk30 >= 0) {
        arg1->unk4->unk0->unk7C(arg1->unk4);
        end = arg1->unk10 + 0x19A;
        for (p = arg1->unk10; p < end; p++) {
            (*p)->unk10 = (*p)->unk10 | 0x80000000;
            (*p)->unk20 = 0;
            (*p)->unk18 = 0;
        }
    }
}

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

s32 func_8004C1C0(Unk_8004C1C0 *arg0, Unk_8004C1C0_Out *arg1, s32 *arg2) {
    Unk_8004C1C0_Ret *temp_v0;
    Unk_8004C1C0_Ret *temp_v0_2;
    Unk_8004C1C0_Range *temp_v1;
    Unk_8004C1C0_Range *temp_a1;
    s16 u30;
    s32 tmp4;
    s32 tmp8;
    temp_v0 = arg0->unk0->unk11C(arg0, arg2);
    if (temp_v0 != NULL) {
        u30 = temp_v0->u4->u30;
        arg1->u28 = u30;
        func_8004C368((Unk_8004C3F0 *)arg0, (u8 *)arg1, u30);
        temp_v0_2 = arg0->unk0->unk118(arg0, temp_v0->u4->u32);
        temp_v1 = temp_v0_2->uC->unk14;
        arg1->uC = temp_v1->unk18 + 0x5000;
        arg1->u10 = temp_v1->unk1C;
        arg1->u14 = temp_v1->unk20 + 0x5000;
        temp_a1 = temp_v0->uC->unk14;
        arg1->u18 = arg2[0] - arg1->uC;
        arg1->u1C = arg2[1];
        arg1->u20 = arg2[2] - arg1->u14;
        arg1->u2 = (arg2[0] - temp_a1->unk18) / 2048;
        arg1->u3 = (arg2[2] - temp_a1->unk20) / 2048;
        tmp4 = (u16)arg2[0] - 0x400;
        arg1->u4 = tmp4 - ((u16)temp_a1->unk18 + arg1->u2 * 2048);
        arg1->u6 = (u16)arg2[1];
        tmp8 = (u16)arg2[2] - 0x400;
        arg1->u8 = tmp8 - ((u16)temp_a1->unk20 + arg1->u3 * 2048);
        arg1->u24 = temp_v0;
        return 0;
    }
    return 1;
}

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

void *func_8004C470(Unk_8004C470 *arg0, s32 *arg1) {
    s32 i;

    for (i = 0; i < 7; i++) {
        Unk_8004C470_Obj *obj = arg0->unk0->unk118(arg0, i);
        Unk_8004C470_Range *r = obj->unkC->unk14;
        if (arg1[0] >= r->unk18 && arg1[0] < r->unk18 + 0xA000 && arg1[2] >= r->unk20 && arg1[2] < r->unk20 + 0xA000) {
            if (arg0->u68->unk_4 == 0) {
                return obj;
            }
            if (i * -0x800 < arg1[1]) {
                continue;
            }
            if (i * -0x800 - 0x800 < arg1[1]) {
                return obj;
            }
        }
    }
    return NULL;
}

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

void func_8004C6A8(Unk_8004C6A8 *self, s32 arg1, s32 arg2) {
    s8 buf[0x30];
    Unk_8004C6A8_M mat;
    Unk_8004C6A8_C *c;
    s16 *rot;
    u16 angle;
    s32 x;
    s32 y;
    s32 d;
    s32 vert;

    c = self->u6C->u14->u44;
    rot = c->rot;
    self->unk0->f10C(self, buf, 0);
    x = buf[2];
    y = buf[3];
    angle = c->rot[1];
    if (c->rot[1] < 0) {
        angle += 0x1000;
    }
    mat = D_8008E98C;
    mat.t[0] = 0;
    mat.t[1] = 0;
    mat.t[2] = self->u74;
    RotMatrix(rot, &mat);
    ApplyMatrixLV((s32 *)&mat, mat.t, mat.t);

    if ((angle >= 0x200 && angle < 0x600) || (angle >= 0xA00 && angle < 0xE00)) {
        d = mat.t[2];
        self->u80 = arg2;
        self->u84 = arg1;
        self->u7C = (mat.t[0] > 0) ? x : x - arg1 + 1;
        self->u7E = (mat.t[2] > 0) ? y - (u16)self->u78 - 1 : y - (u16)self->u78 + 1;
        vert = 0;
    } else if ((angle >= 0x600 && angle < 0xA00) || (angle < 0x200 || angle >= 0xE00)) {
        d = mat.t[0];
        self->u80 = arg1;
        self->u84 = arg2;
        self->u7C = (mat.t[0] > 0) ? x - (u16)self->u78 - 1 : x - (u16)self->u78 + 1;
        self->u7E = (mat.t[2] > 0) ? y : y - arg2 + 1;
        vert = 1;
    }
    d = d >> 11;
    if (d >= self->u78) {
        d = self->u78 - 1;
    }
    if (-self->u78 >= d) {
        d = -self->u78 + 1;
    }
    if (vert != 0) {
        self->u7C += d;
    } else {
        self->u7E += d;
    }
    func_8004C93C(self);
}

void func_8004C93C(Unk_8004CAF0_Obj *arg0) {
    s32 s0;
    s32 s1;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 flag;
    s32 ret;
    s32 t;
    Unk_8004CAF0_Entry *s3;

    flag = 0;
    s1 = arg0->unk7C;
    s6 = arg0->unk80;
    s7 = arg0->unk84;
    s4 = 3;
    if (s1 < 0) {
        s1 += 20;
        flag = 1;
        s4 = 2;
    }
    s5 = arg0->unk7E;
    s3 = arg0->entries;
    if (s5 < 0) {
        s5 += 20;
        if (flag != 0) {
            s1 -= 10;
            s4 = 0;
        } else {
            s4 = 0;
            if (s1 < 10) {
                s1 += 10;
            } else {
                s1 -= 10;
                s4 = 1;
            }
            s3 = arg0->entries;
        }
    }

    ret = arg0->unk0->unk120(arg0, s4);
    arg0->entries[0].unk0 = ret;
    arg0->entries[0].unk4 = s1 < 0 ? 0 : s1;
    arg0->entries[0].unk6 = s5;
    s0 = s1 + s6;
    if (s0 >= 21) {
        t = s0 - 20;
        arg0->entries[0].unk8 = s6 - t;
        s0 = t;
        s1 = func_8004CAF0(arg0, s3, 0, s4, s1, s5, s6, s7) + 1;
        s3 = &arg0->entries[s1];
        s3->unk0 = arg0->unk0->unk120(arg0, s4 + 1);
        s3->unk4 = 0;
        s3->unk6 = (u16)arg0->entries[0].unk6;
        s3->unk8 = s0;
        s3->unkA = (u16)arg0->entries[0].unkA;
    } else {
        arg0->entries[0].unk8 = s6;
        s1 = func_8004CAF0(arg0, s3, 0, s4, s1, s5, s6, s7);
    }
    s1 += 1;
    arg0->unk88 = s1;
}

s32 func_8004CAF0(Unk_8004CAF0_Obj *arg0, Unk_8004CAF0_Entry *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 over;
    s32 id;
    s32 n;

    if (arg5 + arg7 > 20) {
        over = arg5 + arg7 - 20;
        arg1->unkA = arg7 - over;
        arg2++;
        arg1 = &arg0->entries[arg2];
        if (arg4 < 10) {
            id = arg3 + 2;
            arg1->unk0 = arg0->unk0->unk120(arg0, id);
            arg1->unk4 = arg4 + 10;
            arg1->unkA = over;
        } else {
            id = arg3 + 3;
            arg1->unk0 = arg0->unk0->unk120(arg0, id);
            arg1->unk4 = arg4 - 10;
            arg1->unkA = over;
        }
        n = arg1->unk4 + arg6;
        arg1->unk6 = 0;
        if (n > 20) {
            arg1->unk8 = arg6 - (n - 20);
            arg2++;
            arg1 = &arg0->entries[arg2];
            arg1->unk0 = arg0->unk0->unk120(arg0, id + 1);
            arg1->unk4 = 0;
            arg1->unk6 = 0;
            arg1->unk8 = n - 20;
            arg1->unkA = over;
        } else {
            arg1->unk8 = arg6;
        }
    } else {
        arg1->unkA = arg7;
    }
    return arg2;
}

void func_8004CC74(void *arg0) {
    Unk_8004CC74 *self = arg0;
    Unk_8004CC74_Sp10 sp10;
    s32 s1;

    self->unk0->unk10C(self, &sp10, 0);
    self->unk88 = 0;
    self->unk88 = func_8004CDA4(self, s1, 0, sp10.unk_28);
    if (func_8004CD38(self->unk1DC, &sp10.unk_2) != 0) {
        if (sp10.unk_28 + 1 < self->unk68->unk_2) {
            self->unk88 = func_8004CDA4(self, s1, self->unk88, sp10.unk_28 + 1);
        }
    }
    if (sp10.unk_28 - 1 >= 0) {
        self->unk88 = func_8004CDA4(self, s1, self->unk88, sp10.unk_28 - 1);
    }
}

s32 func_8004CD38(void *arg0, void *arg1) {
    Unk_8004CD38 *box = arg0;
    u8 *pt = arg1;

    if (box != NULL && (s8)pt[0] >= box->unk0 && (s8)pt[0] <= box->unk4
        && (s8)pt[1] >= box->unk2 && (s8)pt[1] <= box->unk8) {
        return 0;
    }
    return 1;
}

s32 func_8004CDA4(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_8004CDA4_Obj *self = arg0;
    Unk_8004CDA4_Entry *entry = &self->entries[arg2];

    *entry = D_80086990;
    entry->unk0 = self->unk0->unk124(self, arg3);
    return arg2 + 1;
}

void func_8004CE24(void *arg0, s32 arg1) {
    Unk_8004CE24 *self = arg0;
    Unk_8004CE24_Entry *ent;
    s16 *var_a3;
    Unk_8004CE24_Slot *slot;
    s32 i;
    s32 row;
    s32 col;
    Unk_8004CE24_Node **p;
    Unk_8004CE24_Node *e;
    Unk_8004CE24_Node *node;
    s32 flags;

    ent = (Unk_8004CE24_Entry *)((u8 *)self + 0x8C);
    for (i = 0; i < self->unk88; i++) {
        slot = &self->slots[ent->slot];
        var_a3 = &ent->d;
        if (slot->obj->u2C != 0) {
            p = slot->base + var_a3[-3] + var_a3[-2] * 20;
            for (row = 0; row < var_a3[0]; row++) {
                for (col = 0; col < var_a3[-1]; col++) {
                    if (arg1 != 0) {
                        e = *p;
                        flags = e->unk10 & 0x7FFFFFFF;
                    } else {
                        e = *p;
                        flags = e->unk10 | 0x80000000;
                    }
                    e->unk10 = flags;
                    node = (*p)->unk38;
                    while (node != NULL) {
                        if (arg1 != 0) {
                            flags = node->unk10 & 0x7FFFFFFF;
                        } else {
                            flags = node->unk10 | 0x80000000;
                        }
                        node->unk10 = flags;
                        node = node->unk38;
                    }
                    p++;
                }
                p += 20 - var_a3[-1];
            }
        }
        ent++;
    }
}

s32 func_8004CFA8(s32 arg0) {
    return arg0 + 0x1CC;
}

void func_8004CFB0(Unk_8004CFB0 *arg0, s32 arg1) {
    arg0->unk1DC = arg1;
}

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

Unk_8004A4C8 *func_8004D244(void) {
    return (Unk_8004A4C8 *)D_800866E8;
}

s32 func_8004D254(void) {
    s32 temp_v0;

    temp_v0 = Heap_Alloc(0xDC);
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

Unk_8004D254 *func_8004D37C(void) {
    return (Unk_8004D254 *)D_800869D8;
}

s32 func_8004D38C(void) {
    s32 temp_v0;

    temp_v0 = Heap_Alloc(0x3C);
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

s32 func_8004D500(s32 arg0) {
    return arg0;
}

void *func_8004D508(void) {
    return D_80086AA0;
}

s32 func_8004D518(s32 arg0) {
    s32 temp_v0;

    temp_v0 = Heap_Alloc(0xC4);
    if (temp_v0 != 0) {
        func_8004E2D0()->unk8(temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

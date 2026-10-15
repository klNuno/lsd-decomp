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
    u8 pad_00[0x58];
    s32 (*unk58)(void *self);
    u8 pad_5C[0x4];
    Unk_80045DE0_Fn unk60;
    void (*unk64)(void *self);
    void (*unk68)(void *self);
};
struct Unk_80045DE0 {
    struct Unk_80045DE0_Vtbl *unk0;
    u8 pad_04[0x10];
    s32 unk14[2];
    s32 unk1C;
    u8 pad_20[0x14];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    struct Unk_800458B8_Sub *unk60;
    s32 unk64;
    void *unk68;
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
    u8 pad_00[0x8];
    void (*unk8)(void *, void *);
    void (*unkC)(void *arg0);
};
struct Unk_800452AC_Obj *func_800441A4(void);
struct Unk_80044B04 {
    u8 pad_00[0x7C];
    void (*unk7C)(struct Unk_80044B04 **arg0);
};
struct Unk_800449FC {
    u8 pad_00[0x8];
    s32 (*unk8)(s32, s32, s32);
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
Unk_80043B88 *func_80043E74(void);
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
    u8 pad_0C[0x58];
    s32 (*unk64)(void *arg0);
};
struct Unk_80044A0C_Obj *func_80044CC4(void);
struct Unk_800451B8_Obj {
    u8 pad_00[0x8];
    s32 (*unk8)(s32 arg0, s32 arg1);
    u8 pad_0C[0x58];
    s32 (*unk64)(void *arg0);
};
struct Unk_800451B8_Obj *func_80045428(void);
extern void func_80026E0C(void);
extern void func_80026E38(void);
typedef struct Unk_8004355C_Vtbl {
    u8 pad_00[0x80];
    void (*unk80)(void *, s32, s32);
} Unk_8004355C_Vtbl;
typedef struct Unk_8004355C {
    Unk_8004355C_Vtbl *unk0;
} Unk_8004355C;
typedef struct Unk_80044220_Vt {
    u8 pad_00[0x8];
    void (*unk8)(void *arg0);
} Unk_80044220_Vt;
typedef struct Unk_80044220_Obj {
    u8 pad_00[0x40];
    void (*unk40)(void **arg0, s32 arg1, s32 arg2);
} Unk_80044220_Obj;
Unk_80044220_Vt *func_8001E57C(void);
struct Unk_80044CD4_Vtbl {
    u8 pad_00[0x8];
    s32 (*unk8)(s32 arg0, s32 arg1, s32 arg2);
};
struct Unk_80044CD4_Vtbl *func_80044F20(void);
struct Unk_800435D0_Entry {
    u8 pad_00[0xC];
    Unk_8004464C_Color unkC;
    u8 pad_0F;
};
struct Unk_800435D0 {
    u8 pad_00[0x40];
    struct Unk_800435D0_Entry unk40[1];
};
void func_80043648(void *arg0, s32 arg1);
struct Unk_80043BE8_Svc {
    u8 pad_00[0x8];
    void (*unk8)(void *arg0);
};
struct Unk_80043BE8_Vtbl {
    u8 pad_00[0x6C];
    void (*unk6C)(void *self, s32 arg1);
};
struct Unk_80043BE8 {
    struct Unk_80043BE8_Vtbl *unk0;
    u8 pad_04[0x28];
    s32 unk2C;
    void *unk30;
    u8 pad_34[0x4];
    s32 unk38;
};
struct Unk_80043DFC {
    u8 pad_00[0x2C];
    s32 unk2C;
    struct Unk_80044808_Obj **unk30;
};
struct Unk_800455D4_Obj;
typedef struct Unk_800455D4_Obj *(*Unk_800455D4_Fn)(struct Unk_800455D4_Obj *self);
struct Unk_800455D4_Vtbl {
    u8 pad_00[0x4];
    Unk_800455D4_Fn unk4;
};
struct Unk_800455D4_Obj {
    struct Unk_800455D4_Vtbl *unk0;
};
struct Unk_800455D4 {
    u8 pad_00[0x60];
    struct Unk_800455D4_Obj *unk60;
};
struct Unk_800455D4_Mgr {
    u8 pad_00[0xC];
    void (*unkC)(struct Unk_800455D4 *arg0);
};
extern void DecDCTReset(s32 mode);
extern void DecDCToutCallback(void (*func)(void));
extern void func_8004575C(struct Unk_8004575C *arg0);
void *func_80018390(void);
struct Unk_800448F8_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *self);
};
struct Unk_800448F8_Obj {
    struct Unk_800448F8_Vtbl *unk0;
};
struct Unk_800448F8 {
    u8 pad_00[0x2C];
    struct Unk_800448F8_Obj *unk2C;
    struct Unk_800448F8_Obj *unk30;
    s32 unk34;
};
struct Unk_8004593C {
    u8 pad_00[0x50];
    s32 unk50;
};
void func_8004593C(struct Unk_8004593C *arg0); void func_8004593C(struct Unk_8004593C *arg0);
struct Unk_80045DE0_Vtbl;
struct Unk_800458B8_Sub;
typedef void (*Unk_800458B8_Fn48)(void *self);
typedef void (*Unk_800458B8_Fn58)(void *self);
typedef void (*Unk_800458B8_Fn7C)(void *self, void (*cb)(void), void *ctx);
struct Unk_800458B8_SubVtbl {
    u8 pad_00[0x44];
    s32 (*unk44)(void *self, void *arg1, s32 arg2);
    Unk_800458B8_Fn48 unk48;
    u8 pad_4C[0x4];
    void (*unk50)(void *self, s32 arg1, s32 arg2);
    u8 pad_54[0x4];
    Unk_800458B8_Fn58 unk58;
    u8 pad_5C[0x8];
    void (*unk64)(void *self);
    u8 pad_68[0x14];
    Unk_800458B8_Fn7C unk7C;
};
struct Unk_800458B8_Sub {
    struct Unk_800458B8_SubVtbl *unk0;
};
struct Unk_80044D40 {
    struct Unk_80044CD4_Vtbl *unk0;
    u8 pad_04[0x26];
    u16 unk2A;
    u8 pad_2C[0x10];
    s32 unk3C;
    u16 unk40;
    u16 unk42;
};
typedef s32 (*Unk_80045438_Fn)(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
struct Unk_80045438_Obj {
    u8 pad_00[0x8];
    Unk_80045438_Fn unk8;
};
struct Unk_80045438_Obj *func_80045E44(void);
struct Unk_80043F78;
struct Unk_800452AC_Obj;
struct Unk_80043EE4_Obj {
    u8 pad_00[0x64];
    void (*unk64)(void *arg0);
    u8 pad_68[0x4];
    void (*unk6C)(void *arg0, s32 arg1);
};
struct Unk_80043EE4 {
    struct Unk_80043EE4_Obj *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    s32 unk14;
};
struct Unk_80043EE4_Src {
    s32 unk0;
    s32 unk4;
};
struct Unk_80043954 {
    u8 pad_00[0x2C];
    struct Unk_800448F8_Obj **unk2C;
};
struct Unk_80044380_Obj {
    u8 pad_00[0x64];
    s32 unk64;
};
struct Unk_80044380_Src {
    u8 pad_00[0x8];
    s16 unk8;
    s16 unkA;
};
struct Unk_80044F90_Base_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *arg0);
};
struct Unk_80044F90_vt {
    u8 pad_00[0x64];
    void (*unk64)(void *arg0);
};
struct Unk_80044F90 {
    struct Unk_80044F90_vt *unk0;
    u8 pad_04[0x26];
    u16 unk2A;
    u8 pad_2C[0x4];
    u16 unk30;
    u16 unk32;
    s32 unk34;
};
struct Unk_80026CE8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
struct Unk_80026CE8 *func_80026CE8(struct Unk_80026CE8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_80043840(s32 arg0);
s32 func_800451B8(s32 arg0);
struct Unk_80044858_Vtbl {
    u8 pad_00[0x7C];
    void (*unk7C)(void *self);
};
struct Unk_80044858 {
    struct Unk_80044858_Vtbl *unk0;
    u8 pad_04[0xC];
    u8 *unk10;
    u8 pad_14[0x18];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
};
struct Unk_800449FC;
struct Unk_800446FC_Obj {
    u8 pad_00[0x64];
    s32 (*unk64)(void *arg0);
    u8 pad_68[0x4];
    void (*unk6C)(void *arg0, s32 arg1);
};
struct Unk_800446FC {
    struct Unk_800446FC_Obj *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    s32 unk14;
    u8 pad_18[0x1C];
    s32 unk34;
};
struct Unk_80044E64_Vtbl {
    u8 pad_00[0x5C];
    void (*unk5C)(void *self);
};
struct Unk_80044E64 {
    struct Unk_80044E64_Vtbl *unk0;
    u8 pad_04[0x28];
    u8 unk2C;
    u8 unk2D;
    u16 unk2E;
    s16 unk30;
    s32 unk34;
    s16 *unk38;
    struct Unk_80043B58 *unk3C;
    u16 unk40;
};
struct Unk_80045BC8 {
    u8 pad_00[0x1C];
    s32 unk1C;
    s16 unk20;
    u16 unk22;
    s32 unk24;
    u8 pad_28[0x4];
    u16 unk2C;
    u16 unk2E;
    u16 unk30;
    u8 pad_32[0x2];
    s32 unk34;
    s32 unk38;
    u8 pad_3C[0x8];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};
typedef struct Unk_80045BC8_Vtbl {
    u8 pad_00[0x58];
    void (*unk58)(void *self, void *arg1, s32 arg2);
    u8 pad_5C[0x78 - 0x5C];
    void (*unk78)(void *self, void *arg1, void *arg2);
} Unk_80045BC8_Vtbl;
typedef struct Unk_80045BC8_Obj {
    Unk_80045BC8_Vtbl *unk0;
} Unk_80045BC8_Obj;
Unk_80045BC8_Obj *func_80020C5C(void);
extern s32 DrawSync(s32 mode);
extern void DecDCTout(s32 p, s32 size);
s32 func_8004468C(s32 arg0);
struct Unk_80044B88_Vtbl {
    u8 pad_00[0x7C];
    void (*unk7C)(void *self);
};
struct Unk_80044B88 {
    struct Unk_80044B88_Vtbl *unk0;
    u8 pad_04[0xC];
    s32 *unk10;
    u8 pad_14[0x24];
    s32 unk38;
};
s32 func_80043E84(s32 arg0);
struct Unk_800452FC_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *self);
};
struct Unk_800452FC_Obj {
    struct Unk_800452FC_Vtbl *unk0;
};
struct Unk_800452FC_Tbl {
    u8 pad_00[0x4];
    s32 unk4;
    s32 unk8[1];
};
struct Unk_800452FC {
    u8 pad_00[0x10];
    struct Unk_800452FC_Tbl *unk10;
};
void func_80045E18(struct Unk_80045E18 *arg0);
extern void DecDCTin(s32 p, s32 mode);
extern Unk_8004464C_Color D_8008A938;
struct Unk_80044294 {
    u8 pad_00[0x44];
    u32 unk44;
    u16 unk48;
    u16 unk4A;
    s16 unk4C;
    s16 unk4E;
    u16 unk50;
    u16 unk52;
    Unk_8004464C_Color unk54;
    u8 pad_57[0x1];
    void *unk58;
    s16 unk5C;
    s16 unk5E;
    u16 unk60;
    u16 unk62;
    s32 unk64;
};
struct Unk_80044294_Src {
    u8 pad_00[0x2C];
    u8 unk2C;
    u8 unk2D;
    u16 unk2E;
    u16 unk30;
};
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
struct Unk_800450B4_Entry {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    u16 unk4;
    u16 unk6;
};
struct Unk_800450B4 {
    u8 pad_00[0x2C];
    struct Unk_800450B4_Entry *unk2C;
    u16 unk30;
};
struct Unk_8004564C_Vec {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
struct Unk_8004564C {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    struct Unk_8004564C_Vec unk20;
    struct Unk_8004564C_Vec unk2C;
    s32 unk38;
};
s32 func_8003B39C(s32 arg0);
s16 D_8008A934;
struct Unk_80043CB8_Vtbl {
    u8 pad_00[0x9C];
    void (*unk9C)(void *self, void *arg1);
};
struct Unk_80043CB8_Obj {
    struct Unk_80043CB8_Vtbl *unk0;
    u8 pad_04[0xC];
    u8 *unk10;
    s32 unk14;
    u8 pad_18[0x34];
    s32 unk4C;
};
struct Unk_80043CB8 {
    u8 pad_00[0x10];
    s32 *unk10;
    u8 pad_14[0x10];
    s32 unk24;
    u8 pad_28[0x4];
    s32 unk2C;
    struct Unk_80043CB8_Obj **unk30;
    s32 unk34;
    s32 unk38;
};
struct Unk_80043CB8_Sp {
    u8 pad_00[0x12];
    s16 unk12;
    u8 pad_14[0xC];
};
struct Unk_800454C4_Vtbl {
    u8 pad_00[0x40];
    void (*unk40)(void *self, s32 arg1, s32 arg2);
};
struct Unk_800454C4_Obj {
    struct Unk_800454C4_Vtbl *unk0;
};
struct Unk_800454C4 {
    struct Unk_80043EE4_Obj *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    u8 pad_14[0x3C];
    s32 unk50;
    u8 pad_54[0xC];
    struct Unk_800454C4_Obj *unk60;
};
void func_80045DE0(void);
struct Unk_800454C4_Obj *func_80046F0C(void *arg0, s32 arg1, s32 arg2);
s32 func_8004564C();
s32 D_8008A93C;
extern void *func_8001F250(s32 arg0);
struct Unk_800439EC_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *self);
    u8 pad_08[0x70];
    void (*unk78)(void *self);
};
struct Unk_800439EC_Elem {
    struct Unk_800439EC_Vtbl *unk0;
};
struct Unk_800439EC_Ent {
    u8 pad_00[0x1C];
};
struct Unk_800439EC_Count {
    u8 pad_00[0x8];
    u32 unk8;
    struct Unk_800439EC_Ent unkC[1];
};
struct Unk_800439EC_Mgr {
    u8 pad_00[0x64];
    void (*unk64)(void *arg0);
};
struct Unk_800439EC {
    struct Unk_800439EC_Vtbl *unk0;
    u8 pad_04[0xC];
    struct Unk_800439EC_Count *unk10;
    u8 pad_14[0x18];
    struct Unk_800439EC_Elem **unk2C;
};
extern struct Unk_80043008_Obj D_8006F0B8;
extern struct Unk_80043840_Obj D_8006F13C;
extern Unk_80043B88 D_8006F1C4;
extern struct Unk_800452AC_Obj D_8006F240;
extern struct Unk_800441B4_Mgr D_8006F2C4;
extern struct Unk_800449FC D_8006F384;
extern struct Unk_80044A0C_Obj D_8006F40C;
extern struct Unk_80044CD4_Vtbl D_8006F498;
extern struct Unk_80044F30 D_8006F514;
extern struct Unk_800451B8_Obj D_8006F590;
void func_800458AC(struct Unk_80045DE0 *arg0);
struct Unk_80045E3C {
    u8 pad_00[0x68];
    s32 unk68;
};
struct Unk_80045438_Obj;
extern u8 D_8006F614[];
void func_8004593C(struct Unk_8004593C *arg0);
typedef struct Unk_80043648_Rect {
    u16 unk0;
    u16 unk2;
    s16 unk4;
    u16 unk6;
} Unk_80043648_Rect;
typedef struct Unk_80043648 {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad_04[0x6];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
} Unk_80043648;
typedef struct Unk_80043648_Frame {
    Unk_80043648_Rect rect10;
    Unk_80043648_Rect rect18;
    u16 pix20[0x100];
    u16 pix220[0x100];
    u16 pad420[4];
} Unk_80043648_Frame;
s16 D_8008A92C;
void StoreImage(Unk_80043648_Rect *rect, u32 *arg1);
s32 LoadImage(Unk_80043648_Rect *rect, u32 *p);
typedef struct Unk_8004441C {
    u8 pad0[0x60];
    s16 unk60;
    s16 unk62;
} Unk_8004441C;
extern void DecDCTvlc(s32 p, s32 q);
struct Unk_80045AD8_Vtbl {
    u8 pad_00[0x54];
    void (*unk54)(void *self);
    u8 pad_58[0x14];
    s32 (*unk6C)(void *self, s32 *a, s32 *b, s32 c);
    void (*unk70)(void *self, s32 arg1);
};
struct Unk_80045AD8_Obj {
    struct Unk_80045AD8_Vtbl *unk0;
};
struct Unk_80045AD8 {
    u8 pad_00[0x14];
    s32 unk14[2];
    u8 pad_1C[0x20];
    s32 unk3C;
    u8 pad_40[0x8];
    s32 unk48;
    u8 pad_4C[0x14];
    struct Unk_80045AD8_Obj *unk60;
};
extern u8 D_8008A944[];

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

u32 func_800434DC(struct Unk_80043B18 *arg0) {
    u32 *p;
    u32 i;
    u32 max;
    

    p = arg0->unk10;
    i = 0;
    max = 0;
    
    for (; i < p[0]; i++) {
        if (max < p[i + 5]) {
            max = p[i + 5];
        }
    }
    return max;
}

void func_80043538(struct Unk_80043538 *arg0, s32 arg1, u16 arg2) {
    struct Unk_80043538_Entry *entry = &arg0->unk40[arg1];

    entry->unk0 = arg2;
    entry->unk2 = 1 << entry->unk0;
}

void func_8004355C(Unk_8004355C *arg0, s32 arg1) {
    s32 i;

    func_80026E0C();
    for (i = 0; i < 4; i++) {
        arg0->unk0->unk80(arg0, i, arg1);
    }
    func_80026E38();
}

void func_800435D0(struct Unk_800435D0 *arg0, s32 arg1, Unk_8004464C_Color *arg2) {
    struct Unk_800435D0_Entry *entry;

    func_80026E0C();
    entry = &arg0->unk40[arg1];
    entry->unkC = *arg2;
    func_80043648(entry, arg1);
    func_80026E38();
}

void func_80043648(void *arg0, s32 arg1) {
    Unk_80043648 *obj = arg0;
    Unk_80043648_Frame f;
    s32 i;
    s32 k;
    s32 s6;
    s32 t0;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 r;
    s32 g;
    s32 b;
    u32 a2;
    u16 v1;
    u8 c5;
    u8 c4;
    u8 c3;

    f.rect18.unk0 = 0;
    f.rect18.unk4 = 0x100;
    f.rect18.unk6 = 1;
    f.rect18.unk2 = (arg1 << D_8008A92C) + 0x1E0;
    StoreImage(&f.rect18, (u32 *) f.pix220);
    DrawSync(0);
    f.rect10.unk6 = 1;
    i = 0;
    f.rect10.unk0 = 0;
    f.rect10.unk2 = 0;
    f.rect10.unk4 = 0x100;
    c5 = obj->unkC;
    c4 = obj->unkD;
    c3 = obj->unkE;
    obj->unkA = obj->unk2;
    s6 = 0xC - obj->unk0;
    if (obj->unk2 - 1 > 0) {
        do {
            t0 = (i + 1) << s6;
            t4 = c5 * t0;
            t3 = c4 * t0;
            t2 = c3 * t0;
            t0 = 0x1000 - t0;
            for (k = 0; k < f.rect18.unk4; k++) {
                a2 = f.pix220[k];
                if (a2 == 0) {
                    f.pix20[k] = f.pix220[k];
                } else {
                    v1 = f.pix220[k];
                    r = (v1 & 0x1F) << 3;
                    g = (a2 >> 2) & 0xF8;
                    b = (a2 >> 7) & 0xF8;
                    r = (r * t0 + t4) >> 15;
                    g = (g * t0 + t3) >> 15;
                    b = (b * t0 + t2) >> 15;
                    f.pix20[k] = (v1 & 0x8000) | r | (g << 5) | (b << 10);
                }
            }
            f.rect10.unk2 = f.rect18.unk2 + i + f.rect18.unk6;
            DrawSync(0);
            LoadImage(&f.rect10, (u32 *) f.pix20);
            i++;
        } while (i < obj->unk2 - 1);
    }
}

struct Unk_80043008_Obj *func_80043830(void) {
    return &D_8006F0B8;
}

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

struct Unk_80043EE4 *func_800438B0(struct Unk_80043EE4 *arg0, struct Unk_80043EE4_Src *arg1) {
    s32 temp_v1;
    struct Unk_80043840_Obj *temp_v0;

    ((struct Unk_80043BE8_Svc *)func_80026CAC())->unk8(arg0);
    temp_v0 = func_80043B78();
    arg0->unk0 = (struct Unk_80043EE4_Obj *)temp_v0;
    if (arg1 != NULL) {
        temp_v1 = arg1->unk0;
        if (temp_v1 != 0) {
            arg0->unk10 = temp_v1;
            arg0->unk14 = 0;
            if (((s32 (*)(void *))arg0->unk0->unk64)(arg0) != 0) {
                goto fail;
            }
        } else {
            ((struct Unk_80043EE4_Obj *)temp_v0)->unk6C(arg0, arg1->unk4);
        }
    }
    return arg0;
fail:
    return NULL;
}

void func_80043954(struct Unk_80043954 *arg0) {
    struct Unk_800448F8_Obj **p;
    struct Unk_800448F8_Obj *obj;

    for (p = arg0->unk2C; *p != NULL; p++) {
        obj = *p;
        obj->unk0->unk4(obj);
    }
    func_80017CFC((s32)arg0->unk2C);
    func_80026CAC()->unkC(arg0);
}

s32 func_800439EC(struct Unk_800439EC *arg0) {
    struct Unk_800439EC_Elem **q;
    u32 i;

    q = (struct Unk_800439EC_Elem **)func_80017B34((arg0->unk10->unk8 + 1) * 4);
    if (q == NULL) {
        return 1;
    }
    arg0->unk2C = q;
    arg0->unk0->unk78(arg0);
    for (i = 0; i < arg0->unk10->unk8; i++) {
        *q = func_8001F250((s32)&arg0->unk10->unkC[i]);
        if (*q == NULL) {
            while (i != 0) {
                q--;
                (*q)->unk0->unk4(*q);
                i--;
            }
            func_80017CFC((s32)q);
            return 1;
        }
        q++;
    }
    *q = NULL;
    ((struct Unk_800439EC_Mgr *)func_80026CAC())->unk64(arg0);
    return 0;
}

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

struct Unk_80043840_Obj *func_80043B78(void) {
    return &D_8006F13C;
}

s32 func_80043B88(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x3C);
    if (temp_v0 != 0) {
        func_80043E74()->unk8(temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

void func_80043BE8(struct Unk_80043BE8 *arg0, s32 arg1) {
    ((struct Unk_80043BE8_Svc *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = (struct Unk_80043BE8_Vtbl *)func_80043E74();
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    arg0->unk38 = 0;
    if (arg1 != 0) {
        arg0->unk0->unk6C(arg0, arg1);
    }
}

void func_80043C60(struct Unk_80043C60 *arg0) {
    func_800183DC(arg0->unk30, arg0->unk2C);
    func_80017CFC(arg0->unk30);
    func_80026CAC()->unkC(arg0);
}

void func_80043CB8(struct Unk_80043CB8 *arg0) {
    struct Unk_80043CB8_Sp sp10;
    struct Unk_80043CB8_Obj **temp_v0;
    struct Unk_80043CB8_Obj *temp_v0_2;
    struct Unk_80043CB8_Obj **var_s1;
    s32 *var_s3;
    s32 var_s2;

    if ((arg0->unk24 & 0x200) || arg0->unk10 != NULL) {
        arg0->unk2C = *arg0->unk10;
        temp_v0 = (struct Unk_80043CB8_Obj **)func_80017B34(*arg0->unk10 * 4);
        arg0->unk30 = temp_v0;
        if (temp_v0 != NULL) {
            var_s1 = temp_v0;
            var_s3 = arg0->unk10 + 1;
            for (var_s2 = 0; var_s2 < arg0->unk2C; var_s2++) {
                temp_v0_2 = (struct Unk_80043CB8_Obj *)func_8003B39C(0);
                *var_s1 = temp_v0_2;
                temp_v0_2->unk10 = (u8 *)arg0->unk10 + *var_s3;
                (*var_s1)->unk14 = 0;
                var_s3++;
                (*var_s1)->unk0->unk9C(*var_s1, &sp10);
                (*var_s1)->unk4C = ((((s32)sp10.unk12 - 0x1E0) >> D_8008A934) * 0x10) + arg0->unk34;
                var_s1++;
            }
            arg0->unk38 = 1;
            ((struct Unk_80044808_Mgr *)func_80026CAC())->unk64(arg0);
        }
    }
}

void func_80043DFC(struct Unk_80043DFC *arg0) {
    s32 i;
    struct Unk_80044808_Obj **p;
    struct Unk_80044808_Obj *obj;
    void (*fn)(void *arg0);

    p = arg0->unk30;
    for (i = 0; i < arg0->unk2C; i++) {
        obj = *p;
        fn = obj->unk0->unk78;
        p++;
        fn(obj);
    }
}

Unk_80043B88 *func_80043E74(void) {
    return &D_8006F1C4;
}

s32 func_80043E84(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x2C);
    if (temp_v0 != 0) {
        func_800441A4()->unk8(temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

void func_80043EE4(struct Unk_80043EE4 *arg0, struct Unk_80043EE4_Src *arg1) {
    s32 temp_v1;
    struct Unk_800452AC_Obj *temp_v0;

    ((struct Unk_80043BE8_Svc *)func_80026CAC())->unk8(arg0);
    temp_v0 = func_800441A4();
    arg0->unk0 = (struct Unk_80043EE4_Obj *)temp_v0;
    temp_v1 = arg1->unk0;
    if (temp_v1 != 0) {
        arg0->unk10 = temp_v1;
        arg0->unk14 = 0;
        arg0->unk0->unk64(arg0);
        return;
    }
    ((struct Unk_80043EE4_Obj *)temp_v0)->unk6C(arg0, arg1->unk4);
}

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

struct Unk_800452AC_Obj *func_800441A4(void) {
    return &D_8006F240;
}

s32 func_800441B4(s32 arg0, s32 arg1) {
    void *temp_s0 = (void *)func_80017B34(0x68);

    if (temp_s0 != NULL) {
        func_8004467C()->unk8(temp_s0, arg0, arg1);
        return (s32)temp_s0;
    }
    return 0;
}

void func_80044220(void **arg0, s32 arg1, s32 arg2) {
    Unk_80044220_Obj *temp_v0;

    func_8001E57C()->unk8(arg0);
    temp_v0 = func_8004467C();
    *arg0 = temp_v0;
    temp_v0->unk40(arg0, arg1, arg2);
}

void func_80044294(struct Unk_80044294 *arg0, struct Unk_80044294_Src *arg1, s32 arg2) {
    if (arg2 == 0) {
        arg0->unk44 = 0x01000000;
        arg0->unk4C = arg1->unk2C * arg1->unk2E;
        arg0->unk4E = arg1->unk2D * arg1->unk30;
    } else if (arg2 == 1) {
        arg0->unk44 = 0x02000000;
        arg0->unk4C = 0x140;
        arg0->unk4E = 0xF0;
    }
    arg0->unk48 = 0;
    arg0->unk4A = 0;
    arg0->unk50 = 0;
    arg0->unk52 = 0;
    arg0->unk54 = D_8008A938;
    arg0->unk58 = &arg1->unk2C;
    arg0->unk60 = 0x1000;
    arg0->unk62 = 0x1000;
    arg0->unk64 = 0;
    arg0->unk5C = arg0->unk4C / 2;
    arg0->unk5E = arg0->unk4E / 2;
}

void func_80044380(struct Unk_80044380_Obj *arg0, s32 arg1, struct Unk_80044380_Src *arg2) {
    s16 temp_a0 = arg2->unk8;
    s16 temp_v1 = arg2->unkA;
    s32 temp_a0_2 = ((temp_a0 / temp_v1) << 12) + (((temp_a0 % temp_v1) << 12) / temp_v1);

    if (arg1 != 0) {
        arg0->unk64 = temp_a0_2;
        return;
    }
    arg0->unk64 = temp_a0_2 + arg0->unk64;
}

void func_8004441C(Unk_8004441C *arg0, s32 arg1, s16 *arg2) {
    s16 t1;
    s16 t2;
    s32 t3 = 0;
    s32 t4 = 0;
    s16 v;

    if (arg2[0] < 0 || arg2[1] < 0) {
        t3 = 1;
    }
    if (arg2[2] < 0 || arg2[3] < 0) {
        t4 = 1;
    }
    if (arg2[1] != 0) {
        s32 q = arg2[0] / arg2[1];
        s32 r = arg2[0] % arg2[1];
        t1 = (q << 12) + ((r << 12) / arg2[1]);
    }
    if (arg2[3] != 0) {
        s32 q = arg2[2] / arg2[3];
        s32 r = arg2[2] % arg2[3];
        t2 = (q << 12) + ((r << 12) / arg2[3]);
    }
    if (arg1 != 0) {
        if (arg2[1] == 0) {
            arg0->unk60 = 0x1000;
        } else {
            v = t1 >= 0x7531 ? 0x7530 : t1;
            arg0->unk60 = v;
        }
        if (arg2[3] == 0) {
            arg0->unk62 = 0x1000;
        } else {
            v = t2 >= 0x7531 ? 0x7530 : t2;
            arg0->unk62 = v;
        }
        return;
    }
    v = arg0->unk60;
    if (v + t1 >= 0x7531) {
        arg0->unk60 = t3 ? 1 : 0x7530;
    } else {
        arg0->unk60 = t1 + v;
    }
    v = arg0->unk62;
    if (v + t2 >= 0x7531) {
        arg0->unk62 = t4 ? 1 : 0x7530;
    } else {
        arg0->unk62 = t2 + v;
    }
}

void func_8004464C(struct Unk_8004464C *arg0, s32 arg1, Unk_8004464C_Color *arg2) {
    if (arg1 != 0) {
        arg0->unk54 = *arg2;
    }
}

void func_80044674(void) {
}

struct Unk_800441B4_Mgr *func_8004467C(void) {
    return &D_8006F2C4;
}

s32 func_8004468C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x38);
    if (temp_v0 != 0) {
        if (func_800449FC()->unk8(temp_v0, arg0, 1) != 0) {
            return temp_v0;
        }
        func_80017CFC(temp_v0);
    }
    return 0;
}

struct Unk_800446FC *func_800446FC(struct Unk_800446FC *arg0, struct Unk_80043EE4_Src *arg1, s32 arg2) {
    struct Unk_800446FC_Obj *temp_v0;
    s32 temp_v1;

    ((struct Unk_80043BE8_Svc *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = (struct Unk_800446FC_Obj *)func_800449FC();
    arg0->unk34 = arg2;
    temp_v1 = arg1->unk0;
    if (temp_v1 != 0) {
        temp_v0 = arg0->unk0;
        arg0->unk10 = temp_v1;
        arg0->unk14 = 0;
        if (temp_v0->unk64(arg0) == 0) {
            return arg0;
        }
    } else {
        arg0->unk0->unk6C(arg0, arg1->unk4);
        return arg0;
    }
    return NULL;
}

void func_800447B4(struct Unk_800447B4 **arg0) {
    (*arg0)->unk7C();
    func_80026CAC()->unkC(arg0);
}

void func_80044808(struct Unk_80044808_Obj *arg0) {
    ((struct Unk_80044808_Mgr *)func_80026CAC())->unk64(arg0);
    arg0->unk0->unk78(arg0);
}

s32 func_80044858(struct Unk_80044858 *arg0) {
    struct Unk_80026CE8 sp10;
    s32 temp_v0;
    s32 temp_v0_2;

    if (arg0->unk34 != 0) {
        func_80026CE8(&sp10, (s32)(arg0->unk10 + *(s32 *)(arg0->unk10 + 8)), 0, 1);
        temp_v0 = func_80043840((s32)&sp10);
        arg0->unk2C = temp_v0;
        if (temp_v0 != 0) {
            sp10.unk0 = (s32)(arg0->unk10 + 0xC);
            temp_v0_2 = func_800451B8((s32)&sp10);
            arg0->unk30 = temp_v0_2;
            if (temp_v0_2 != 0) {
                return 0;
            }
            arg0->unk30 = 0;
        }
        arg0->unk0->unk7C(arg0);
        return 1;
    }
    return 0;
}

void func_800448F8(struct Unk_800448F8 *arg0) {
    struct Unk_800448F8_Obj *temp_a0;

    if (arg0->unk34 != 0) {
        temp_a0 = arg0->unk30;
        if (temp_a0 != NULL) {
            temp_a0->unk0->unk4(temp_a0);
        }
        temp_a0 = arg0->unk2C;
        if (temp_a0 != NULL) {
            temp_a0->unk0->unk4(temp_a0);
        }
    }
}

s32 func_8004497C(struct Unk_8004497C *arg0) {
    struct Unk_8004497C_Obj *temp_a0 = arg0->unk30;

    return temp_a0->unk0->unk78(temp_a0);
}

void func_800449B8(struct Unk_800449B8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unk30->unk0->unk80(arg0->unk30, arg1, arg2, arg3, arg4, arg5);
}

struct Unk_800449FC *func_800449FC(void) {
    return &D_8006F384;
}

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

void **func_80044A7C(void **arg0, s32 *arg1) {
    struct Unk_80044A0C_Obj *temp_v0;

    func_800449FC()->unk8((s32)arg0, (s32)arg1, 0);
    temp_v0 = func_80044CC4();
    *arg0 = temp_v0;
    if (*arg1 != 0) {
        if (temp_v0->unk64(arg0) != 0) {
            return 0;
        }
    }
    return arg0;
}

void func_80044B04(struct Unk_80044B04 **arg0) {
    (*arg0)->unk7C(arg0);
    func_800449FC()->unkC(arg0);
}

void func_80044B58(struct Unk_80044B58 **arg0) {
    (*arg0)->unk78();
}

s32 func_80044B88(struct Unk_80044B88 *arg0) {
    struct Unk_80026CE8 sp10;
    s32 *entry;
    s32 count;
    s32 i;
    s32 r;

    func_80026CE8(&sp10, 0, 0, 1);
    entry = &arg0->unk10[2];
    count = arg0->unk10[1];
    arg0->unk38 = 0;
    for (i = 0; i < count; i++) {
        sp10.unk0 = (s32)((u8 *)arg0->unk10 + arg0->unk10[i + 2]);
        r = func_8004468C((s32)&sp10);
        *entry = r;
        if (r == 0) {
            goto fail;
        }
        arg0->unk38++;
        entry++;
    }
    return 0;
fail:
    arg0->unk0->unk7C(arg0);
    return 1;
}

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

struct Unk_80044A0C_Obj *func_80044CC4(void) {
    return &D_8006F40C;
}

s32 func_80044CD4(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x44);
    if (temp_s0 != 0) {
        func_80044F20()->unk8(temp_s0, arg0, arg1);
        return temp_s0;
    }
    return 0;
}

void func_80044D40(struct Unk_80044D40 *arg0, s32 arg1, s32 arg2) {
    s32 sp_buf[8];

    ((struct Unk_80043BE8_Svc *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = func_80044F20();
    arg0->unk3C = arg2;
    arg0->unk42 = 0;
    if (arg1 == 0) {
        arg0->unk40 = 1;
        arg0->unk2A = 0;
        ((struct Unk_80044808_Mgr *)arg0->unk0)->unk64(arg0);
    }
}

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

void func_80044E64(struct Unk_80044E64 *arg0) {
    s16 *buf;
    s16 *p;
    s32 i;
    s32 n;

    arg0->unk34 = (s32)arg0->unk3C->unk2C;
    if (arg0->unk40 != 0) {
        arg0->unk2E = 0x14;
        arg0->unk2C = 0x10;
        arg0->unk2D = 0x10;
        arg0->unk30 = 0xF;
        n = arg0->unk2E * arg0->unk30;
        buf = (s16 *)func_80017B34(n * 2);
        arg0->unk38 = buf;
        if (buf != NULL) {
            p = buf;
            for (i = 0; i < n; i++) {
                *p++ = i;
            }
            return;
        }
    }
    arg0->unk0->unk5C(arg0);
}

struct Unk_80044CD4_Vtbl *func_80044F20(void) {
    return &D_8006F498;
}

s32 func_80044F30(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x38);
    if (temp_v0 != 0) {
        func_800451A8()->unk8((void *)temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

void func_80044F90(struct Unk_80044F90 *arg0, s32 arg1) {
    char sp10[0x20]; /* unused: same 0x20 buffer as func_8004232C's strcpy target */

    ((struct Unk_80044F90_Base_vt *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = ((struct Unk_80044F90_vt *)func_800451A8());
    arg0->unk34 = 0;
    arg0->unk32 = 0;
    if (arg1 == 0) {
        arg0->unk30 = 1;
        arg0->unk2A = 0;
        arg0->unk0->unk64(arg0);
    }
}

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

void func_800450B4(struct Unk_800450B4 *arg0) {
    s32 i;
    s32 n;
    s32 u;
    s32 v;
    s32 x;
    s32 tpage;
    struct Unk_800450B4_Entry *p;
    struct Unk_800450B4_Entry *temp;

    if (arg0->unk30 != 0) {
        x = 0x280;
        v = 0;
        u = 0;
        tpage = GetTPage(2, 0, 0x280, 0) & 0xFFFF;
        temp = (struct Unk_800450B4_Entry *)func_80017B34(0x960);
        arg0->unk2C = temp;
        if (temp != NULL) {
            i = 0;
            p = temp;
            n = 0x12C;
            do {
                p->unk0 = u;
                u += 0x10;
                x += 0x10;
                p->unk6 = tpage;
                p->unk1 = v;
                p->unk2 = 0;
                p->unk4 = 0;
                if (x >= 0x3C0) {
                    u = 0;
                    x = 0x280;
                    v += 0x10;
                }
                if ((x & 0x3F) == 0) {
                    tpage = x >> 6;
                    if (v >= 0x100) {
                        tpage += 0x10;
                    }
                    u = 0;
                }
                i += 1;
                p++;
            } while (i < n);
        }
    }
}

struct Unk_80044F30 *func_800451A8(void) {
    return &D_8006F514;
}

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

void **func_80045228(void **arg0, s32 *arg1) {
    struct Unk_800451B8_Obj *temp_v0;

    func_800441A4()->unk8(arg0, arg1);
    temp_v0 = func_80045428();
    *arg0 = temp_v0;
    if (*arg1 != 0) {
        if (temp_v0->unk64(arg0) != 0) {
            return NULL;
        }
    }
    return arg0;
}

void func_800452AC(struct Unk_80043B18 *arg0) {
    u32 *temp = arg0->unk10;

    func_800183DC(temp + 2, temp[1]);
    func_800441A4()->unkC(arg0);
}

s32 func_800452FC(struct Unk_800452FC *arg0) {
    struct Unk_80026CE8 sp10;
    struct Unk_800452FC_Tbl *tbl;
    struct Unk_800452FC_Obj *obj;
    s32 i;
    s32 *out;
    s32 n;
    s32 r;

    func_80026CE8(&sp10, 0, 0, 1);
    out = arg0->unk10->unk8;
    n = arg0->unk10->unk4;
    for (i = 0; i < n; i++, out++) {
        tbl = arg0->unk10;
        sp10.unk0 = (s32)tbl + tbl->unk8[i];
        r = func_80043E84((s32)&sp10);
        *out = r;
        if (r == 0) {
            while (i != 0) {
                out--;
                obj = (struct Unk_800452FC_Obj *)*out;
                i--;
                obj->unk0->unk4(obj);
            }
            return 1;
        }
    }
    return 0;
}

s32 func_800453DC(struct Unk_800453DC *arg0, s32 arg1, s32 arg2) {
    return arg0->unk0->unk7C(arg0, arg1, arg2, &arg0->unk10[arg0->unk10[1]] + 4) & 0xFF;
}

struct Unk_800451B8_Obj *func_80045428(void) {
    return &D_8006F590;
}

s32 func_80045438(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x6C);
    if (temp_s0 == 0) {
        return 0;
    }
    if (func_80045E44()->unk8(temp_s0, arg0, arg1, arg2) != 0) {
        func_80017CFC(temp_s0);
        return 0;
    }
    return temp_s0;
}

s32 func_800454C4(struct Unk_800454C4 *arg0, s32 arg1, void *arg2, s32 arg3) {
    struct Unk_800454C4_Obj *obj;

    ((struct Unk_80043BE8_Svc *)func_80018390())->unk8(arg0);
    arg0->unk0 = ((struct Unk_80043EE4_Obj *)func_80045E44());
    obj = func_80046F0C(arg2, 0xF, 0);
    arg0->unk60 = obj;
    if (obj != NULL) {
        if (func_8004564C(arg0, arg1, arg3) == 0) {
            if (D_8008A93C == 0) {
                DecDCTReset(0);
            }
            D_8008A93C = 1;
            DecDCToutCallback(func_80045DE0);
            arg0->unk60->unk0->unk40(arg0->unk60, arg0->unk10, 0x12000);
            arg0->unk50 = 0;
            arg0->unk0->unk6C(arg0, 1);
            return 0;
        }
        return 1;
    }
    return 1;
}

void func_800455D4(struct Unk_800455D4 *arg0) {
    struct Unk_800455D4_Obj *temp_a0 = arg0->unk60;

    arg0->unk60 = temp_a0->unk0->unk4(temp_a0);
    DecDCToutCallback(0);
    DecDCTReset(0);
    func_8004575C((struct Unk_8004575C *)arg0);
    ((struct Unk_800455D4_Mgr *)func_80018390())->unkC(arg0);
}

s32 func_8004564C(struct Unk_8004564C *arg0, struct Unk_8004564C_Vec *arg1, s32 arg2) {
    s32 size;
    s32 p;
    s32 unused[2];

    arg0->unkC = arg2;
    if (arg2 == 0) {
        arg0->unk1C = 0;
        arg0->unk18 = 0;
        arg0->unk14 = 0;
        arg0->unk10 = 0;
        size = (arg1->unk4 * arg1->unk8 * 2) + 0x1000;
        p = func_80017B34(size);
        arg0->unk14 = p;
        if (p == 0) {
            goto fail;
        }
        p = func_80017B34(size);
        arg0->unk18 = p;
        if (p == 0) {
            goto fail;
        }
        p = func_80017B34(0x12000);
        arg0->unk10 = p;
        if (p == 0) {
            goto fail;
        }
        p = func_80017B34(arg1->unk8 << 5);
        arg0->unk1C = p;
        if (p == 0) {
            goto fail;
        }
    }
    arg0->unk2C = *arg1;
    arg0->unk20 = arg0->unk2C;
    arg0->unk2C.unk4 = 0x10;
    arg0->unk38 = (arg0->unk2C.unk8 * 0x10) >> 1;
    return 0;

fail:
    func_8004575C(arg0);
    return 1;
}

void func_8004575C(struct Unk_8004575C *arg0) {
    if (arg0->unkC == 0) {
        func_80017CFC(arg0->unk14);
        func_80017CFC(arg0->unk18);
        func_80017CFC(arg0->unk10);
        func_80017CFC(arg0->unk1C);
    }
}

s32 func_800457C0(struct Unk_80045DE0 *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct Unk_800458B8_Sub *sub;
    Unk_80045BC8_Obj *obj;

    if (D_8008A940 == NULL) {
        if (arg0->unk68 != NULL) {
            func_800458AC(arg0);
        }
        sub = arg0->unk60;
        arg0->unk5C = arg2;
        if (sub->unk0->unk44(sub, arg1, 100) == 0) {
            D_8008A940 = arg0;
            arg0->unk40 = 0;
            arg0->unk3C = 0;
            arg0->unk4C = 1;
            arg0->unk48 = 0;
            arg0->unk44 = 0;
            arg0->unk54 = arg3;
            arg0->unk58 = arg4;
            obj = func_80020C5C();
            obj->unk0->unk78(obj, D_8008A944, (u8 *)arg0 + 0x20);
            return 0;
        }
        return 1;
    }
    return 0;
}

void func_800458AC(struct Unk_80045DE0 *arg0) {
    arg0->unk50 = 1;
}

void func_800458B8(void *arg0) {
    struct Unk_80045DE0 *obj = D_8008A940;
    struct Unk_800458B8_Sub *sub;

    if (obj == arg0) {
        sub = obj->unk60;
        obj->unk40 = 0;
        obj->unk3C = 0;
        obj->unk4C = 1;
        obj->unk48 = 0;
        obj->unk44 = 0;
        sub->unk0->unk7C(sub, func_8004593C, obj);
        sub = obj->unk60;
        obj->unk64 = 0;
        sub->unk0->unk58(sub);
    }
}

void func_8004593C(struct Unk_8004593C *arg0) {
    arg0->unk50 = -1;
}

s32 func_80045948(struct Unk_80045DE0 *arg0) {
    struct Unk_80045DE0 *obj = D_8008A940;

    if (obj == arg0 && (obj->unk50 != 0 || obj->unk64 != 0)) {
        if (obj->unk50 != 0) {
            obj->unk60->unk0->unk50(obj->unk60, 1, obj->unk5C);
            if (obj->unk50 < 0) {
                if (obj->unk58 == 0 || --obj->unk58 == 0) {
                    obj->unk60->unk0->unk64(obj->unk60);
                }
            }
            arg0->unk50 = 0;
            arg0->unk64 = 1;
            return 0;
        }
        obj->unk0->unk68(obj);
    }
}

void func_80045A38(void *arg0) {
    struct Unk_80045DE0 *obj = D_8008A940;
    struct Unk_800458B8_Sub *sub;

    if (obj == arg0) {
        sub = obj->unk60;
        obj->unk48 = 1;
        obj->unk54 = 0;
        sub->unk0->unk48(sub);
        obj->unk44 = 1;
        if (obj->unk64 == 0) {
            sub = obj->unk60;
            sub->unk0->unk7C(sub, 0, 0);
            obj->unk64 = 1;
            obj->unk44 = 1;
        }
    }
}

void func_80045AC8(void) {
}

void func_80045AD0(void) {
}

s32 func_80045AD8(struct Unk_80045AD8 *arg0) {
    s32 sp10;
    s32 sp14;
    s32 temp;
    s32 idx;

    if (arg0->unk48 == 0) {
        temp = arg0->unk60->unk0->unk6C(arg0->unk60, &sp10, &sp14, 0x800000);
        if (temp != 0) {
            if (sp14 != 0) {
                idx = arg0->unk3C ^ 1;
                arg0->unk3C = idx;
                DecDCTvlc(sp10, arg0->unk14[idx]);
            }
            arg0->unk60->unk0->unk70(arg0->unk60, sp10);
            if (temp < 0) {
                arg0->unk48 = 1;
                arg0->unk60->unk0->unk54(arg0->unk60);
            }
            return 0;
        }
    }
    return 1;
}

void func_80045BC0(void) {
}

void func_80045BC8(struct Unk_80045BC8 *arg0) {
    Unk_80045BC8_Obj *obj;
    u16 temp;

    obj = func_80020C5C();
    obj->unk0->unk58(obj, &arg0->unk2C, arg0->unk1C);
    temp = arg0->unk2C + arg0->unk30;
    arg0->unk2C = temp;
    if ((s16)temp < arg0->unk20 + arg0->unk24) {
        if (arg0->unk34 < 0x80) {
            DrawSync(0);
        }
        DecDCTout(arg0->unk1C, arg0->unk38);
    } else {
        arg0->unk4C = 1;
        arg0->unk2C = arg0->unk20;
        arg0->unk2E = arg0->unk22;
        if (arg0->unk48 != 0) {
            arg0->unk44 = 1;
        }
    }
}

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

s32 func_80045CFC(struct Unk_80045DE0 *arg0) {
    struct Unk_80045DE0 *temp_s0;

    temp_s0 = D_8008A940;
    if (temp_s0 == arg0) {
        if (temp_s0->unk44 == 0) {
            if (temp_s0->unk40 != 0) {
                func_80045E18((struct Unk_80045E18 *)temp_s0);
                temp_s0->unk4C = 0;
                if (temp_s0->unk34 < 0x80) {
                    DrawSync(0);
                }
                DecDCTin(temp_s0->unk14[temp_s0->unk3C], 2);
                DecDCTout(temp_s0->unk1C, temp_s0->unk38);
            }
            arg0->unk40 = arg0->unk0->unk58(arg0) == 0;
            return 0;
        }
        temp_s0->unk0->unk64(temp_s0);
    }
}

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

void func_80045E3C(struct Unk_80045E3C *arg0, s32 arg1) {
    arg0->unk68 = arg1;
}

struct Unk_80045438_Obj *func_80045E44(void) {
    return (struct Unk_80045438_Obj *)D_8006F614;
}

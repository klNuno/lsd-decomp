#include "common.h"

typedef struct { s16 unk_0; s16 unk_2; s32 unk_4; } Unk_800861D4;
typedef struct { u8 pad[0xC]; s32 uC; u8 pad2[0x2F4 - 0x10]; s32 u2F4; } A;
typedef struct { u8 pad[0xBC]; A *uBC; } P;
typedef struct { s32 u0; s32 u4; } C;
typedef struct { u8 pad[0x18]; C *u18; } Q;
typedef struct Unk_8004E3F4 {
    u8 pad_00[0x60];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    u8 pad_6C[0x74 - 0x6C];
    s32 unk74;
    s32 unk78;
    s32 unk7C;
} Unk_8004E3F4;
extern s32 EnableEvent();
s32 func_8004F40C(s32 arg0, s32 (*arg1)(), s32 arg2);
s32 func_8004F4C8(s32 *arg0, s32 arg1);
extern s32 DisableEvent();
extern s32 TestEvent();
void func_8004B44C(s32 *arg0, s32 *arg1, Unk_800861D4 *arg2, s32 *arg3, void *arg4);
extern s32 CloseEvent();
void func_8004F3BC(s32 arg0);
typedef struct Unk_8004E40C { s32 unk0, unk4, unk8; void (*unkC)(s32); u8 pad_10[0x4]; void (*unk14)(void *, s32 **); void (*unk18)(void *); u8 pad_1C[0x38 - 0x1C]; void (*unk38)(void *, s32 **, s32); } Unk_8004E40C;
extern Unk_8004E40C *func_80018390(void);
typedef struct Unk_8004FFF4_vt { u8 pad[0x80]; void (*unk80)(void *, s32, s32, s32); } Unk_8004FFF4_vt;
typedef struct Unk_8004FFF4_obj { Unk_8004FFF4_vt *unk0; } Unk_8004FFF4_obj;
typedef struct Unk_8004FFF4 { u8 pad[0x6C]; Unk_8004FFF4_obj *unk6C; } Unk_8004FFF4;
typedef struct Unk_8004FF40_vt { u8 pad[4]; void *(*unk4)(void *); } Unk_8004FF40_vt;
typedef struct Unk_8004FF40_obj { Unk_8004FF40_vt *unk0; } Unk_8004FF40_obj;
typedef struct Unk_8004FF40 { u8 pad[0x70]; Unk_8004FF40_obj *unk70; } Unk_8004FF40;
s32 func_8004E7D0();
s32 func_8004E890();
typedef struct Unk_8004DABC_mgr { u8 pad[0x94]; void (*unk94)(void *); u8 pad_98[0xDC - 0x98]; void (*unkDC)(void *); void (*unkE0)(void *, s32); void (*unkE4)(void *, void *); } Unk_8004DABC_mgr;
typedef struct Unk_8004DABC_vt { u8 pad[0x19C]; void (*unk19C)(void *, s32 *); } Unk_8004DABC_vt;
typedef struct Unk_8004DABC_obj { Unk_8004DABC_vt *vt; } Unk_8004DABC_obj;
typedef struct Unk_8004DABC_sub { u8 pad[0x14]; s32 unk14; } Unk_8004DABC_sub;
typedef struct Unk_8004DABC { u8 pad[0x60]; Unk_8004DABC_sub *unk60; u8 pad2[0xA4 - 0x64]; Unk_8004DABC_obj *unkA4; } Unk_8004DABC;
extern Unk_8004DABC_mgr *func_8003DFBC(void);
typedef struct Unk_8004F5DC_Vtbl {
    u8 pad[0x14];
    void (*unk14)(void *, s32);
} Unk_8004F5DC_Vtbl;
typedef struct Unk_8004F5DC {
    Unk_8004F5DC_Vtbl *unk0;
    u8 pad_04[0x60 - 0x04];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
} Unk_8004F5DC;
struct Unk_8004FF90;
typedef struct Unk_8004FF90_Vtbl {
    u8 pad[0x90];
    void (*unk90)(struct Unk_8004FF90 *);
    void (*unk94)(struct Unk_8004FF90 *);
} Unk_8004FF90_Vtbl;
typedef struct Unk_8004FF90 {
    Unk_8004FF90_Vtbl *unk0;
    u8 pad_04[0x28 - 0x4];
    s32 unk28;
} Unk_8004FF90;
struct Unk_8004E1C4;
typedef struct Unk_8004E1C4_vt {
    u8 pad[0x128];
    void (*unk128)(struct Unk_8004E1C4 *);
} Unk_8004E1C4_vt;
typedef struct Unk_8004E1C4_obj_vt {
    u8 pad[0x74];
    void (*unk74)(void *, s32, s32, s32, s32);
} Unk_8004E1C4_obj_vt;
typedef struct Unk_8004E1C4_obj {
    Unk_8004E1C4_obj_vt *unk0;
} Unk_8004E1C4_obj;
typedef struct Unk_8004E1C4 {
    Unk_8004E1C4_vt *unk0;
    u8 pad_04[0xAC - 0x04];
    Unk_8004E1C4_obj *unkAC;
    u8 pad_B0[0xBC - 0xB0];
    s32 unkBC;
    s32 unkC0;
} Unk_8004E1C4;
s32 g_cardFileName;
s32 g_cardTitle;
typedef struct Unk_8004E2E0 {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32, s32);
} Unk_8004E2E0;
extern s32 func_80017B34(s32);
Unk_8004E2E0 *func_800507E8(void);
extern s32 format(char *);
extern char D_8008AA9C[];
extern char D_8008AAA4[];
typedef struct Unk_8004E940 { u8 pad[0xC]; s32 unkC; } Unk_8004E940;
s32 func_8004ECCC();
typedef struct Unk_8004D898_tbl {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8004D898_tbl;
typedef struct Unk_8004D898_vt {
    u8 pad_00[0x78];
    void (*unk78)(void *, void *, Unk_8004D898_tbl *);
} Unk_8004D898_vt;
typedef struct Unk_8004D898_obj {
    Unk_8004D898_vt *vt;
} Unk_8004D898_obj;
typedef struct Unk_8004D898 {
    u8 pad_00[0xC];
    Unk_8004D898_obj **unkC;
    u8 pad_10[0x93 - 0x10];
    u8 unk93;
} Unk_8004D898;
extern Unk_8004D898_tbl D_80086DAC[];
typedef struct Unk_8004DC08_vt { u8 pad_00[0x4]; void (*unk4)(void *); } Unk_8004DC08_vt;
typedef struct Unk_8004DC08_obj { Unk_8004DC08_vt *unk0; } Unk_8004DC08_obj;
typedef struct Unk_8004DC08 { u8 pad_00[0xB0]; Unk_8004DC08_obj *unkB0; } Unk_8004DC08;
typedef struct Unk_8004DC64_Vtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *, s32, void *);
} Unk_8004DC64_Vtbl;
typedef struct Unk_8004DC64_Obj {
    Unk_8004DC64_Vtbl *unk0;
} Unk_8004DC64_Obj;
typedef struct Unk_8004DC64 {
    u8 pad_00[0xB0];
    Unk_8004DC64_Obj *unkB0;
} Unk_8004DC64;
extern s32 D_8008A9B4;
typedef struct Unk_8004ECCC {
    u8 pad_00[0xC];
    s32 unkC;
} Unk_8004ECCC;
extern char D_8008AAAC[];
char *func_8004F32C(char *buf, s32 sel, char *suffix);
s32 open(char *name, s32 flags);
s32 close(s32 fd);
s32 delete(char *name);
s32 func_8004EDC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct Unk_8004F55C_vt {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
} Unk_8004F55C_vt;
typedef struct Unk_8004F55C {
    Unk_8004F55C_vt *unk0;
    u8 pad_04[0x24 - 0x04];
    s32 unk24;
    s32 unk28;
    u8 pad_2C[0x30 - 0x2C];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 pad_3C[0x68 - 0x3C];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
} Unk_8004F55C;
typedef struct Unk_8004F704 {
    u8 pad_00[0x38];
    s32 *unk38;
    s32 unk3C;
} Unk_8004F704;
typedef struct Unk_8004D704_vt { u8 pad[4]; void (*unk4)(void *); } Unk_8004D704_vt;
typedef struct Unk_8004D704_obj { Unk_8004D704_vt *unk0; } Unk_8004D704_obj;
typedef struct Unk_8004D704 { u8 pad[0xA8]; Unk_8004D704_obj *unkA8; Unk_8004D704_obj *unkAC; } Unk_8004D704;
typedef struct Unk_8004D704_mgr { u8 pad[0xC]; void (*unkC)(void *); } Unk_8004D704_mgr;
typedef struct Unk_8004D814_Vtbl {
    u8 pad_00[0x6C];
    void (*unk6C)(void *, s32);
    u8 pad_70[0xD4 - 0x70];
    void (*unkD4)(void *, void *, s32);
} Unk_8004D814_Vtbl;
typedef struct Unk_8004D814_ObjVtbl {
    u8 pad_00[0xF0];
    void (*unkF0)(void *, s32, s32);
} Unk_8004D814_ObjVtbl;
typedef struct Unk_8004D814_Obj {
    Unk_8004D814_ObjVtbl *vt;
} Unk_8004D814_Obj;
typedef struct Unk_8004D814 {
    Unk_8004D814_Vtbl *unk0;
    u8 pad_04[0x2C - 0x04];
    s32 unk2C;
    u8 pad_30[0x34 - 0x30];
    s32 unk34;
    u8 pad_38[0xA4 - 0x38];
    Unk_8004D814_Obj *unkA4;
} Unk_8004D814;
typedef struct Unk_8004D788_mgr {
    u8 pad[0x38];
    void (*unk38)(void *, void *, s32);
} Unk_8004D788_mgr;
typedef struct Unk_8004D788_vt {
    u8 pad[0x138];
    void (*unk138)(void *, void *, s32);
} Unk_8004D788_vt;
typedef struct Unk_8004D788_obj {
    Unk_8004D788_vt *vt;
} Unk_8004D788_obj;
s32 func_8004EA38(s32 arg0, s32 arg1, u8 *arg2);
typedef struct Unk_8004F784 {
    u8 pad_00[0x2C];
    s32 unk2C;
    u8 pad_30[0x38 - 0x30];
    s32 *unk38;
} Unk_8004F784;
extern s32 func_80017CFC(s32);
typedef struct Unk_8004E054_sub { u8 pad_00[0x4]; s32 unk4; } Unk_8004E054_sub;
typedef struct Unk_8004E054_vt {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
    void (*unk14)(void *, void *);
} Unk_8004E054_vt;
typedef struct Unk_8004E054_obj_vt {
    u8 pad_00[0x70];
    void (*unk70)(void *);
} Unk_8004E054_obj_vt;
typedef struct Unk_8004E054_obj {
    Unk_8004E054_obj_vt *unk0;
} Unk_8004E054_obj;
typedef struct Unk_8004E054 {
    Unk_8004E054_vt *unk0;
    u8 pad_04[0x8];
    Unk_8004E054_sub *unkC;
    s32 unk10;
    u8 pad_14[0xAC - 0x14];
    Unk_8004E054_obj *unkAC;
} Unk_8004E054;
typedef struct Unk_800501F0_vt {
    u8 pad_00[0x7C];
    void (*unk7C)(void *, s32);
    u8 pad_80[0x8C - 0x80];
    void (*unk8C)(void *, s32);
} Unk_800501F0_vt;
typedef struct Unk_800501F0 {
    Unk_800501F0_vt *unk0;
    u8 pad_04[0x28 - 0x04];
    s32 unk28;
    u8 pad_2C[0x5C - 0x2C];
    s32 unk5C;
} Unk_800501F0;
extern s32 EnterCriticalSection();
extern s32 ExitCriticalSection();
extern s32 OpenEvent(u32, s32, s32, s32);
extern s32 D_80086E78[];
typedef struct Unk_8004F810 {
    u8 pad_00[0x2C];
    s32 unk2C;
    u8 pad_30[0x38 - 0x30];
    s32 *unk38;
    s32 unk3C;
} Unk_8004F810;
typedef struct Unk_8004F40C {
    u8 pad_00[0x14];
    s32 unk14[4];
} Unk_8004F40C;
typedef struct Unk_8004E230_obj_vt {
    u8 pad_00[0x1A8];
    void (*unk1A8)(void *);
} Unk_8004E230_obj_vt;
typedef struct Unk_8004E230_obj {
    Unk_8004E230_obj_vt *unk0;
} Unk_8004E230_obj;
typedef struct Unk_8004E230_vt {
    u8 pad_00[0x124];
    void (*unk124)(void *, s32);
    u8 pad_128[0x12C - 0x128];
    void (*unk12C)(void *);
} Unk_8004E230_vt;
typedef struct Unk_8004E230 {
    Unk_8004E230_vt *unk0;
    u8 pad_04[0xA4 - 0x04];
    Unk_8004E230_obj *unkA4;
} Unk_8004E230;
s32 read(s32 fd, s32 buf, s32 n);
s32 strcpy(s32 dst, s32 src);
typedef struct Unk_8004EADC_vt { u8 pad_00[0x54]; s32 (*unk54)(void *, s32, s8 *); } Unk_8004EADC_vt;
typedef struct Unk_8004EADC_obj { Unk_8004EADC_vt *vt; } Unk_8004EADC_obj;
s8 *strcat(s8 *dst, s8 *src);
typedef struct Unk_80050730_vt {
    u8 pad_00[0x7C];
    void (*unk7C)(void *, s32);
    u8 pad_80[0xAC - 0x80];
    void (*unkAC)(void *);
} Unk_80050730_vt;
typedef struct Unk_80050730_obj {
    Unk_80050730_vt *unk0;
    u8 pad_04[0x80 - 0x04];
    s32 unk80;
} Unk_80050730_obj;
typedef struct Unk_80050730_src_vt {
    u8 pad_00[0x9C];
    s32 (*unk9C)(void *);
} Unk_80050730_src_vt;
typedef struct Unk_80050730_src {
    Unk_80050730_src_vt *unk0;
} Unk_80050730_src;
typedef struct Unk_80050410_vt {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x48 - 0x08];
    void (*unk48)(void *);
    void (*unk4C)(void *);
    void (*unk50)(void *);
} Unk_80050410_vt;
typedef struct Unk_80050410_obj {
    Unk_80050410_vt *vt;
} Unk_80050410_obj;
typedef struct Unk_80050410 {
    u8 pad_00[0x60];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    u8 pad_6C[0x74 - 0x6C];
    s32 unk74;
    Unk_80050410_obj *unk78;
} Unk_80050410;
typedef struct Unk_80050670_vt {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x48 - 0x08];
    void (*unk48)(void *);
    u8 pad_4C[0x50 - 0x4C];
    void (*unk50)(void *);
} Unk_80050670_vt;
typedef struct Unk_80050670_obj {
    Unk_80050670_vt *vt;
} Unk_80050670_obj;
s32 func_8004E77C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);
typedef struct Unk_8004D90C_mgr {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_8004D90C_mgr;
typedef struct Unk_8004D90C_vt {
    u8 pad_00[0x78];
    void (*unk78)(void *);
    void (*unk7C)(void *);
    u8 pad_80[0xF0 - 0x80];
    void (*unkF0)(void *, s32, s32);
    u8 pad_F4[0x124 - 0xF4];
    void (*unk124)(void *, s32);
} Unk_8004D90C_vt;
typedef struct Unk_8004D90C_sub {
    u8 pad_00[0x8];
    s32 unk8;
} Unk_8004D90C_sub;
typedef struct Unk_8004D90C {
    Unk_8004D90C_vt *unk0;
    u8 pad_04[0x4C - 0x4];
    Unk_8004D90C_sub *unk4C;
} Unk_8004D90C;
typedef struct Unk_800505A8_vt {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
} Unk_800505A8_vt;
typedef struct Unk_800505A8_obj_vt {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32);
    u8 pad_48[0x4C - 0x48];
    void (*unk4C)(void *, s32, s32, s32);
} Unk_800505A8_obj_vt;
typedef struct Unk_800505A8_obj {
    Unk_800505A8_obj_vt *vt;
} Unk_800505A8_obj;
typedef struct Unk_800505A8 {
    Unk_800505A8_vt *unk0;
    u8 pad_04[0x38 - 0x04];
    s32 unk38;
    u8 pad_3C[0x60 - 0x3C];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    u8 pad_70[0x74 - 0x70];
    s32 unk74;
    u8 pad_78[0x7C - 0x78];
    s32 unk7C;
} Unk_800505A8;
s32 func_80051A5C(s32 arg0, s32 arg1);
s32 func_8004EF6C(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6);
typedef struct Unk_800507F8_Pair {
    s8 x, y;
} Unk_800507F8_Pair;
typedef struct Unk_800507F8_Tri {
    Unk_800507F8_Pair p[3];
} Unk_800507F8_Tri;
typedef struct Unk_800507F8_Hex {
    Unk_800507F8_Tri a;
    Unk_800507F8_Tri b;
} Unk_800507F8_Hex;
typedef struct Unk_800507F8 {
    u8 pad_0[0x6];
    Unk_800507F8_Hex unk6;
    u8 pad_12[0x18 - 0x12];
    Unk_800507F8_Pair unk18;
} Unk_800507F8;
void func_800507F8(Unk_800507F8 *arg0, u8 *arg1);
typedef struct Unk_8004F638_vt {
    u8 pad_00[0x44];
    void (*unk44)(void *);
    void (*unk48)(void *);
    s32 (*unk4C)(void *, s32 *, s32 *, s32 *);
    u8 pad_50[0x54 - 0x50];
    s32 (*unk54)(void *, s32, s32);
    u8 pad_58[0x5C - 0x58];
    s32 (*unk5C)(void *, s32, s32, s32, s32);
    s32 (*unk60)(void *, s32, s32);
    u8 pad_64[0x7C - 0x64];
    void (*unk7C)(void *, s32);
} Unk_8004F638_vt;
typedef struct Unk_8004F638 {
    Unk_8004F638_vt *unk0;
    u8 pad_04[0x24 - 0x04];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    u8 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
} Unk_8004F638;
s32 func_8004F9D8();
void func_8004F810(Unk_8004F810 *arg0);
void func_8004F704(Unk_8004F704 *arg0);
void func_8004F784(Unk_8004F784 *arg0);
typedef struct Unk_80050340_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void *, void *);
} Unk_80050340_Vtbl;
typedef struct Unk_80050340_Obj_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32);
    u8 pad_48[0x4C - 0x48];
    void (*unk4C)(void *, s32, s32, s32);
} Unk_80050340_Obj_Vtbl;
typedef struct Unk_80050340_Obj {
    Unk_80050340_Obj_Vtbl *vt;
} Unk_80050340_Obj;
typedef struct Unk_80050340 {
    Unk_80050340_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    s32 unk48;
    u8 pad_4C[0x60 - 0x4C];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    u8 pad_70[0x74 - 0x70];
    s32 unk74;
    Unk_80050340_Obj *unk78;
} Unk_80050340;
void *func_80050BA8(s32 arg0, s32 arg1);
typedef struct Unk_800504D0_vt {
    u8 pad_00[0x78];
    void (*unk78)(void *, s32, s32, s32, s32, s32, s32, s32);
    void (*unk7C)(void *, s32);
    u8 pad_80[0xA0 - 0x80];
    void (*unkA0)(void *);
} Unk_800504D0_vt;
typedef struct Unk_800504D0 {
    Unk_800504D0_vt *unk0;
    u8 pad_04[0x40 - 0x04];
    s32 unk40;
    s32 unk44;
    s32 unk48;
    u8 unk4C;
    u8 pad_4D[0x50 - 0x4D];
    s32 unk50;
    s32 unk54;
    s32 unk58;
} Unk_800504D0;
typedef struct Unk_8004E0E4_vt {
    u8 pad_00[0x128];
    void (*unk128)(void *);
} Unk_8004E0E4_vt;
typedef struct Unk_8004E0E4_mgr_vt {
    u8 pad_00[0x19C];
    void (*unk19C)(void *, s32 *);
    u8 pad_1A0[0x1AC - 0x1A0];
    s32 (*unk1AC)(void *);
} Unk_8004E0E4_mgr_vt;
typedef struct Unk_8004E0E4_obj {
    Unk_8004E0E4_mgr_vt *vt;
} Unk_8004E0E4_obj;
typedef struct Unk_8004E0E4_draw_vt {
    u8 pad_00[0x78];
    void (*unk78)(void *, s32, s32, s32, s32, s32, s32, s32);
} Unk_8004E0E4_draw_vt;
typedef struct Unk_8004E0E4_draw {
    Unk_8004E0E4_draw_vt *vt;
} Unk_8004E0E4_draw;
typedef struct Unk_8004E0E4 {
    Unk_8004E0E4_vt *unk0;
    u8 pad_04[0x60 - 0x04];
    Unk_8004DABC_sub *unk60;
    u8 pad_64[0xA4 - 0x64];
    Unk_8004E0E4_obj *unkA4;
    s32 unkA8;
    Unk_8004E0E4_draw *unkAC;
    u8 pad_B0[0xBC - 0xB0];
    s32 unkBC;
    s32 unkC0;
} Unk_8004E0E4;
s32 lseek(s32 fd, s32 offset, s32 whence);
typedef struct Unk_8004FB04_vt {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32 **, s32);
    u8 pad_8C[0x98 - 0x8C];
    void (*unk98)(void *, s32 **, s32);
    u8 pad_9C[0xA4 - 0x9C];
    void (*unkA4)(void *, s32 **, s32);
    u8 pad_A8[0xB0 - 0xA8];
    void (*unkB0)(void *, s32 **, s32);
} Unk_8004FB04_vt;
typedef struct Unk_8004FB04_obj {
    Unk_8004FB04_vt *vt;
} Unk_8004FB04_obj;
typedef struct Unk_8004DB18_vt {
    u8 pad_00[0x1AC];
    s32 (*unk1AC)(void *);
} Unk_8004DB18_vt;
typedef struct Unk_8004DB18_obj {
    Unk_8004DB18_vt *vt;
} Unk_8004DB18_obj;
typedef struct Unk_8004DB18_rec {
    u8 pad_00[0xAA];
    u8 unkAA;
    u8 unkAB;
    u8 unkAC;
} Unk_8004DB18_rec;
typedef struct Unk_8004DB18 {
    u8 pad_00[0xA4];
    Unk_8004DB18_obj *unkA4;
    u8 pad_A8[0xB0 - 0xA8];
    Unk_8004DB18_rec *unkB0;
} Unk_8004DB18;
typedef struct Unk_8004DB18_arg1 {
    u8 pad_00[0x4];
    s32 unk4;
} Unk_8004DB18_arg1;
s32 D_8008AA14;
extern s32 func_800408CC(s32, s32, s32);
extern s8 *func_80040FC0(s8 *, u8 *);
extern s32 strlen(u8 *);
typedef struct Unk_8004DF64_C {
    u8 pad_00[0x4];
    s32 unk4;
} Unk_8004DF64_C;
typedef struct Unk_8004DF64_Vt {
    u8 pad_00[0x10];
    void (*unk10)(void *, void *);
    void (*unk14)(void *, s32);
} Unk_8004DF64_Vt;
typedef struct Unk_8004DF64_ObjVt {
    u8 pad_00[0x6C];
    void (*unk6C)(void *, s32, void *, s32, s32, s32, s32);
} Unk_8004DF64_ObjVt;
typedef struct Unk_8004DF64_Obj {
    Unk_8004DF64_ObjVt *vt;
} Unk_8004DF64_Obj;
typedef struct Unk_8004DF64 {
    Unk_8004DF64_Vt *unk0;
    u8 pad_04[0x8];
    Unk_8004DF64_C *unkC;
    s32 unk10;
    s32 unk14;
    u8 pad_18[0x48 - 0x18];
    s32 unk48;
    u8 pad_4C[0xA8 - 0x4C];
    s32 unkA8;
    Unk_8004DF64_Obj *unkAC;
} Unk_8004DF64;
s32 func_8003B39C(s32 arg0);
s32 func_8004E2E0(s32 arg0, s32 arg1);
extern u8 D_80086D6C[];
void *D_8008A9D0;
typedef struct Unk_8004E40C_8004E444 { s32 unk0, unk4, unk8; void (*unkC)(s32); u8 pad_10[0x8]; void (*unk18)(void *); } Unk_8004E40C_8004E444;
typedef struct Unk_8004E444 { u8 pad_00[0x10]; void (*unk10)(void *, s32 **); } Unk_8004E444;
typedef struct Unk_8004E3F4_8004E444 {
    u8 pad_00[0x60];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    u8 pad_6C[0x78 - 0x6C];
    s32 unk78;
    s32 unk7C;
} Unk_8004E3F4_8004E444;
typedef struct Unk_8004D9D4_mgr { u8 pad[0x90]; void (*unk90)(void *); } Unk_8004D9D4_mgr;
typedef struct Unk_8004D9D4_obj_vt { u8 pad[0xF0]; void (*unkF0)(void *, s32, s32); } Unk_8004D9D4_obj_vt;
typedef struct Unk_8004D9D4_obj { Unk_8004D9D4_obj_vt *vt; } Unk_8004D9D4_obj;
typedef struct Unk_8004D9D4_vt {
    u8 pad[0x94];
    void (*unk94)(void *);
    u8 pad_98[0x130 - 0x98];
    void (*unk130)(void *);
    void (*unk134)(void *);
} Unk_8004D9D4_vt;
typedef struct Unk_8004D9D4 {
    Unk_8004D9D4_vt *unk0;
    u8 pad_04[0x38 - 0x04];
    s32 unk38;
    u8 pad_3C[0x58 - 0x3C];
    s32 unk58;
    u8 pad_5C[0xA4 - 0x5C];
    Unk_8004D9D4_obj *unkA4;
} Unk_8004D9D4;
typedef struct Unk_8004E34C_Base {
    u8 pad0[0x8];
    void (*unk8)(void *);
} Unk_8004E34C_Base;
typedef struct Unk_8004E34C_Vtbl {
    u8 pad0[0x40];
    void (*unk40)(void *, s32);
} Unk_8004E34C_Vtbl;
void func_8004E3F4(Unk_8004E3F4 *);
void InitCARD(s32);
void StartCARD(void);
void _bu_init(void);
s32 D_8008AA30;
typedef struct Unk_8004E7D0 {
    u8 pad[0x10];
    s32 unk10;
} Unk_8004E7D0;
s32 _card_info(s32);
void _card_clear(s32);
void func_8004F3E4(s32);
s32 func_8004F4A4(s32);
typedef struct Unk_8004E890 {
    u8 pad_00[0x10];
    s32 unk10;
} Unk_8004E890;
extern s32 _card_load(s32);
void func_8004F3E4(s32 arg0);
s32 func_8004F4A4(s32 arg0);
extern s8 *D_80086E80[];
extern s32 D_80086EC4[];
extern s32 D_8008AA94[];
extern s8 D_8008AAB4[];
extern s8 D_8008AABC[];
typedef struct Unk_8004FE24_obj Unk_8004FE24_obj;
typedef struct Unk_8004FE24_vt {
    u8 pad_00[0x4];
    void (*unk4)(Unk_8004FE24_obj *self);
    u8 pad_08[0x44];
    void (*unk4C)(Unk_8004FE24_obj *self, s32 arg1, s32 *arg2);
    u8 pad_50[0x28];
    void (*unk78)(Unk_8004FE24_obj *self);
} Unk_8004FE24_vt;
struct Unk_8004FE24_obj {
    Unk_8004FE24_vt *vt;
};
Unk_8004FE24_obj *func_80041C9C(Unk_8004FE24_obj *arg0, s32 *arg1, s32 arg2);
typedef struct Unk_8004FE24 {
    u8 pad_00[0x68];
    s32 unk68;
    u8 pad_6C[0x4];
    void *unk70;
} Unk_8004FE24;
void *func_8004E2D0(void);
void SaveMenu_SetTitleDay(s32 arg0);
extern u8 D_80086D44[];
typedef struct Unk_8004D578_mgr {
    u8 pad[0x8];
    void (*unk8)(void *, void *, void *, s32);
} Unk_8004D578_mgr;
typedef struct Unk_8004D578_vt {
    u8 pad[0x40];
    void (*unk40)(void *, void *);
    u8 pad_44[0xD8 - 0x44];
    void (*unkD8)(void *, void *);
} Unk_8004D578_vt;
typedef struct Unk_8004D578_obj_vt {
    u8 pad[0x9C];
    void (*unk9C)(void *, s32);
} Unk_8004D578_obj_vt;
typedef struct Unk_8004D578_obj {
    Unk_8004D578_obj_vt *unk0;
} Unk_8004D578_obj;
typedef struct Unk_8004D578 {
    Unk_8004D578_vt *unk0;
    u8 pad_04[0x48 - 0x04];
    Unk_8004D578_obj *unk48;
    u8 pad_4C[0xA4 - 0x4C];
    void *unkA4;
    s32 unkA8;
    s32 unkAC;
    u8 pad_B0[0xBC - 0xB0];
    s32 unkBC;
    s32 unkC0;
} Unk_8004D578;
typedef struct Unk_8004D578_arg1_vt {
    u8 pad[0x1A0];
    s32 (*unk1A0)(void *, s32);
    u8 pad_1A4[0x1B0 - 0x1A4];
    s32 (*unk1B0)(void *, void *);
} Unk_8004D578_arg1_vt;
typedef struct Unk_8004D578_arg1 {
    Unk_8004D578_arg1_vt *unk0;
} Unk_8004D578_arg1;
typedef struct Unk_8004DE08_vt {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0xE0 - 0x64];
    void (*unkE0)(void *, s32);
    u8 pad_E4[0xF0 - 0xE4];
    void (*unkF0)(void *, s32, s32);
    u8 pad_F4[0x11C - 0xF4];
    void (*unk11C)(void *, s32, s32);
} Unk_8004DE08_vt;
typedef struct Unk_8004DE08_obj_vt {
    u8 pad_00[0xCC];
    void (*unkCC)(void *, s32);
    u8 pad_D0[0x19C - 0xD0];
    void (*unk19C)(void *, s32 *);
} Unk_8004DE08_obj_vt;
typedef struct Unk_8004DE08_obj {
    Unk_8004DE08_obj_vt *unk0;
    u8 pad_04[0xA9 - 0x04];
    u8 unkA9;
} Unk_8004DE08_obj;
typedef struct Unk_8004DE08 {
    Unk_8004DE08_vt *unk0;
    u8 pad_04[0x14 - 0x04];
    s32 unk14;
    u8 pad_18[0x4C - 0x18];
    s32 unk4C;
    u8 pad_50[0x58 - 0x50];
    s32 unk58;
    u8 pad_5C[0xA4 - 0x5C];
    Unk_8004DE08_obj *unkA4;
    u8 pad_A8[0xB0 - 0xA8];
    Unk_8004DE08_obj *unkB0;
} Unk_8004DE08;
typedef struct Unk_8004DCD0_rgb { s8 r, g, b; } Unk_8004DCD0_rgb;
typedef struct Unk_8004DCD0_vt { u8 pad_00[0xB8]; void (*unkB8)(void *, Unk_8004DCD0_rgb *); } Unk_8004DCD0_vt;
typedef struct Unk_8004DCD0_obj { Unk_8004DCD0_vt *vt; } Unk_8004DCD0_obj;
typedef struct Unk_8004DCD0 { u8 pad_00[0x3C]; s32 unk3C; u8 pad_40[0xB0 - 0x40]; Unk_8004DCD0_obj *unkB0; } Unk_8004DCD0;
u8 D_8008AA28;
s32 D_8008AA2C;
extern u8 D_80086B60[];
typedef struct Unk_8004E5D4 {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
} Unk_8004E5D4;
extern u8 D_80086DC4[];
typedef struct Unk_80050034_vt {
    u8 pad_00[0x74];
    void (*unk74)(void *, s32, s32, s32, s32);
    void (*unk78)(void *, s32, s32, s32, s32, s32, s32, s32);
    void (*unk7C)(void *, s32);
    u8 pad_80[0x8C - 0x80];
    void (*unk8C)(void *, s32);
} Unk_80050034_vt;
typedef struct Unk_80050034 {
    Unk_80050034_vt *unk0;
    u8 pad_04[0x24 - 0x04];
    s32 unk24;
    s32 unk28;
    u8 pad_2C[0x30 - 0x2C];
    s8 *unk30;
    u8 pad_34[0x38 - 0x34];
    s8 **unk38;
    s8 **unk3C;
    s8 *unk40;
    s8 *unk44;
    s32 unk48;
    u8 unk4C;
    u8 pad_4D[0x50 - 0x4D];
    s32 unk50;
    s32 unk54;
    s32 unk58;
    u8 pad_5C[0x80 - 0x5C];
    s32 unk80;
} Unk_80050034;
void *memcpy(void *dst, const void *src, u32 n);
typedef struct { u8 r, g, b, cd; s8 e; s8 f; } Unk_8004D6AC_Col;
typedef struct { u8 pad[0x12]; Unk_8004D6AC_Col col; } Unk_8004D6AC_Dst;
s8 *D_8008AA24;
void func_8004109C(s8 *arg0, s32 arg1, s32 arg2, s32 arg3);
Unk_800507F8_Pair *D_8008AAC4;
s32 atoi(u8 *s);
typedef struct Unk_8004FBE4_vt {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
    u8 pad_34[0x50 - 0x34];
    s32 (*unk50)(void *);
    u8 pad_54[0x58 - 0x54];
    void (*unk58)(void *, u8 *, s32, s32);
    u8 pad_5C[0x64 - 0x5C];
    s32 (*unk64)(void *, u8 *, s32, s32);
    s32 (*unk68)(void *, u8 *, s32, u8, s32, s32, s32);
    u8 pad_6C[0x7C - 0x6C];
    void (*unk7C)(void *, s32);
    void (*unk80)(void *, s32);
    void (*unk84)(void *);
    u8 pad_88[0x9C - 0x88];
    void (*unk9C)(void *);
    u8 pad_A0[0xA8 - 0xA0];
    void (*unkA8)(void *);
} Unk_8004FBE4_vt;
typedef struct Unk_8004FBE4 {
    Unk_8004FBE4_vt *unk0;
    u8 pad_04[0x24 - 0x04];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    u8 *unk40;
    s32 unk44;
    u8 pad_48[0x4C - 0x48];
    u8 unk4C;
    u8 pad_4D[0x50 - 0x4D];
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
} Unk_8004FBE4;
typedef struct Unk_8004EF6C_arg4 {
    u8 pad_00[0x10];
    u8 *unk10;
} Unk_8004EF6C_arg4;
typedef struct Unk_8004EF6C_H {
    u8 b[0x20];
} Unk_8004EF6C_H;
typedef struct Unk_8004EF6C_Icon {
    u8 b[0x80];
} Unk_8004EF6C_Icon;
s32 write(s32 fd, void *buf, s32 n);
s32 printf(char *fmt, ...);
s32 func_8004EF6C(s32, s32, s32, u8, s32, s32, s32);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011434);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011440);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011454);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011464);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011474);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_8001149C);

void func_8004D578(Unk_8004D578 *arg0, Unk_8004D578_arg1 *arg1) {
    ((Unk_8004D578_mgr *)func_8003DFBC())->unk8(arg0, D_80086D44, "ETC\\ETCSE", 0);
    arg0->unk0 = func_8004E2D0();
    arg0->unk48->unk0->unk9C(arg0->unk48, -1);
    arg0->unkA4 = arg1;
    arg0->unkAC = 0;
    arg0->unkBC = arg1->unk0->unk1B0(arg1, &arg0->unkC0);
    SaveMenu_SetTitleDay(arg1->unk0->unk1A0(arg1, 0));
    arg0->unk0->unkD8(arg0, D_80086D44);
    arg0->unk0->unk40(arg0, arg1);
}

void Menu_UpdateFlashbackItem(P *arg0, Q *arg1, void *arg2) {
    A *a = arg0->uBC;
    s32 r = 1;
    if (a->uC > 9999999) {
        r = a->u2F4 == 0;
    }
    arg1->u18->u4 = r;
}

void SaveMenu_SetTitleDay(s32 arg0) {
    func_8004109C(D_8008AA24, arg0, 3, 0);
    ((Unk_8004D6AC_Dst *)g_cardTitle)->col = *(Unk_8004D6AC_Col *)D_8008AA24;
}

void func_8004D704(Unk_8004D704 *arg0) {
    Unk_8004D704_obj *temp_a0;

    temp_a0 = arg0->unkAC;
    if (temp_a0 != NULL) {
        temp_a0->unk0->unk4(temp_a0);
        temp_a0 = arg0->unkA8;
        temp_a0->unk0->unk4(temp_a0);
    }
    ((Unk_8004D704_mgr *)func_8003DFBC())->unkC(arg0);
}

void func_8004D788(Unk_8004D788_obj *arg0, s32 **arg1, s32 arg2) {
    ((Unk_8004D788_mgr *)func_8003DFBC())->unk38(arg0, arg1, arg2);
    if ((**arg1 & 0xF) == 0xB) {
        arg0->vt->unk138(arg0, arg1, arg2);
    }
}

void func_8004D814(Unk_8004D814 *arg0) {
    Unk_8004D814_Obj *temp_a0;

    arg0->unk34 = 0;
    arg0->unk2C = 0x190;
    arg0->unk0->unkD4(arg0, "ETC\\TITLE.TIM", 0);
    arg0->unk0->unk6C(arg0, 10);
    temp_a0 = arg0->unkA4;
    temp_a0->vt->unkF0(temp_a0, 0, 0);
}

void func_8004D898(Unk_8004D898 *arg0) {
    u32 i;

    for (i = 0; i < 2; i++) {
        (*arg0->unkC)->vt->unk78(*arg0->unkC, &arg0->unk93, &D_80086DAC[i]);
    }
}

void func_8004D90C(Unk_8004D90C *arg0, s32 arg1) {
    ((Unk_8004D90C_mgr *)func_8003DFBC())->unk60(arg0, arg1);
    if (arg1 == 5) {
        arg0->unk0->unk124(arg0, 0);
    }
    if (arg1 == 0xA) {
        arg0->unk0->unk7C(arg0);
        arg0->unk0->unkF0(arg0, arg0->unk4C->unk8, 1);
        arg0->unk0->unk78(arg0);
    }
}

void func_8004D9D4(Unk_8004D9D4 *arg0) {
    void (*fn)(void *);
    Unk_8004D9D4_obj *temp_a0;

    ((Unk_8004D9D4_mgr *)func_8003DFBC())->unk90(arg0);
    switch (arg0->unk58) {
    case 1:
        temp_a0 = arg0->unkA4;
        arg0->unk38 = 0;
        temp_a0->vt->unkF0(temp_a0, 0, 1);
        fn = arg0->unk0->unk94;
        break;
    case 2:
        fn = arg0->unk0->unk130;
        break;
    case 3:
        fn = arg0->unk0->unk134;
        break;
    case 4:
        arg0->unk38 = 2;
        fn = arg0->unk0->unk94;
        break;
    default:
        return;
    }
    fn(arg0);
}

void func_8004DABC(Unk_8004DABC *arg0) {
    s32 sp10;
    Unk_8004DABC_obj *temp_a0;

    func_8003DFBC()->unk94(arg0);
    temp_a0 = arg0->unkA4;
    sp10 = arg0->unk60->unk14;
    temp_a0->vt->unk19C(temp_a0, &sp10);
}

void func_8004DB18(Unk_8004DB18 *arg0, Unk_8004DB18_arg1 *arg1) {
    s32 n;
    s32 v;
    s32 p;

    if (arg1 != NULL) {
        if (arg0->unkA4->vt->unk1AC(arg0->unkA4) != 0) {
            strcpy(g_cardTitle + 0x18, D_8008AA14);
            func_800507F8(g_cardTitle, 0);
        }
        n = ((u32)strlen(g_cardTitle) >> 1) + 4;
        p = func_80017B34(n);
        func_80040FC0((s8 *)p, (u8 *)g_cardTitle);
        v = func_800408CC(arg1->unk4, n, p);
        arg0->unkB0 = (Unk_8004DB18_rec *)v;
        arg0->unkB0->unkAB = 8;
        arg0->unkB0->unkAC = 4;
        arg0->unkB0->unkAA = 9;
        func_80017CFC(p);
    }
}

void func_8004DC08(Unk_8004DC08 *arg0) {
    Unk_8004DC08_obj *temp_a0;

    temp_a0 = arg0->unkB0;
    temp_a0->unk0->unk4(temp_a0);
    func_8003DFBC()->unkDC(arg0);
}

void func_8004DC64(Unk_8004DC64 *arg0, s32 arg1) {
    Unk_8004DC64_Obj *obj;

    func_8003DFBC()->unkE0(arg0, arg1);
    obj = arg0->unkB0;
    obj->unk0->unk4C(obj, arg1, &D_8008A9B4);
}

void func_8004DCD0(Unk_8004DCD0 *arg0, Unk_8004DCD0_rgb *arg1) {
    Unk_8004DCD0_rgb col;
    u8 *p;

    p = (u8 *)&col;
    func_8003DFBC()->unkE4(arg0, arg1);
    if (arg0->unk3C != 0) {
        col.r = 0;
        col.g = 0;
        col.b = 0;
        p[D_8008AA28] = 0x80;
    } else {
        col = *arg1;
        if (D_8008AA2C < 0x80) {
            p[0] += 0x80;
        } else {
            p[D_8008AA28] += 0x80;
        }
    }
    if (++D_8008AA28 >= 3) {
        D_8008AA28 = 0;
    }
    if (++D_8008AA2C >= 0x101) {
        D_8008AA2C = 0;
    }
    arg0->unkB0->vt->unkB8(arg0->unkB0, &col);
}

void func_8004DE08(Unk_8004DE08 *arg0) {
    s32 sp10;
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = arg0->unk58;
    temp_s1 = func_80017B34(arg0->unkB0->unkA9);
    func_80040FC0((s8 *)temp_s1, (u8 *)g_cardTitle);
    arg0->unkB0->unk0->unkCC(arg0->unkB0, temp_s1);
    func_80017CFC(temp_s1);
    Menu_UpdateFlashbackItem(arg0, arg0->unk4C, arg0->unkA4);
    arg0->unk0->unkE0(arg0, arg0->unk14);
    arg0->unkA4->unk0->unk19C(arg0->unkA4, &sp10);
    arg0->unk58 = 5;
    arg0->unk0->unk60(arg0, 0xB);
    arg0->unk0->unk11C(arg0, sp10, 1);
    arg0->unk0->unk60(arg0, 0xF);
    arg0->unk0->unkF0(arg0, temp_s2, 0);
    arg0->unkA4->unk0->unk19C(arg0->unkA4, &sp10);
}

void func_8004DF64(Unk_8004DF64 *arg0) {
    if (arg0->unkAC == NULL) {
        arg0->unkA8 = func_8003B39C((s32)"CARD\\FILEICN1.TIM");
        arg0->unkAC = (Unk_8004DF64_Obj *)func_8004E2E0(1, 0);
    }
    arg0->unkAC->vt->unk6C(arg0->unkAC, (s32)D_8008A9D0, D_80086D6C, arg0->unkC->unk4, arg0->unk10, arg0->unk14, arg0->unk48);
    arg0->unk0->unk10(arg0, arg0->unkAC);
    arg0->unk0->unk14(arg0, arg0->unkC->unk4);
    arg0->unk0->unk14(arg0, arg0->unk10);
}

void func_8004E054(Unk_8004E054 *arg0) {
    arg0->unk0->unk10(arg0, arg0->unkC->unk4);
    arg0->unk0->unk10(arg0, arg0->unk10);
    arg0->unk0->unk14(arg0, arg0->unkAC);
    arg0->unkAC->unk0->unk70(arg0->unkAC);
}

void SaveMenu_Save(Unk_8004E0E4 *arg0) {
    s32 sp20;

    sp20 = arg0->unk60->unk14;
    arg0->unkA4->vt->unk19C(arg0->unkA4, &sp20);
    arg0->unk0->unk128(arg0);
    if (arg0->unkA4->vt->unk1AC(arg0->unkA4) != 0) {
        *(s8 *)g_cardFileName = 0;
    }
    arg0->unkAC->vt->unk78(arg0->unkAC, g_cardFileName, g_cardTitle, 0xD, 3, arg0->unkA8, arg0->unkBC, arg0->unkC0);
}

void SaveMenu_Load(Unk_8004E1C4 *arg0) {
    arg0->unk0->unk128(arg0);
    arg0->unkAC->unk0->unk74(arg0->unkAC, g_cardFileName, g_cardTitle, arg0->unkBC, arg0->unkC0);
}

void func_8004E230(Unk_8004E230 *arg0, s32 arg1, s32 arg2) {
    Unk_8004E230_obj *temp_a0;

    if (arg2 < 0x18) {
        if (arg2 < 0x16) {
            return;
        }
        arg0->unk0->unk12C(arg0);
        if (arg2 == 0x16) {
            temp_a0 = arg0->unkA4;
            temp_a0->unk0->unk1A8(temp_a0);
            arg0->unk0->unk124(arg0, 0x16);
        }
    }
}

void *func_8004E2D0(void) {
    return D_80086B60;
}

s32 func_8004E2E0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x84);
    if (temp_v0 != 0) {
        func_800507E8()->unk8(temp_v0, arg0, arg1);
        return temp_v0;
    }
    return 0;
}

void func_8004E34C(Unk_8004E34C_Vtbl **arg0, s32 arg1, s32 arg2) {
    Unk_8004E34C_Vtbl *vt;
    s32 count;

    ((Unk_8004E34C_Base *)func_80018390())->unk8(arg0);
    vt = ((Unk_8004E34C_Vtbl *)func_800507E8());
    count = D_8008AA30;
    *arg0 = vt;
    D_8008AA30 = count + 1;
    if (count == 0) {
        InitCARD(arg1);
        StartCARD();
        _bu_init();
    }
    func_8004E3F4((Unk_8004E3F4 *)arg0);
    (*arg0)->unk40(arg0, arg2);
}

void func_8004E3F4(Unk_8004E3F4 *arg0) {
    arg0->unk60 = 0;
    arg0->unk64 = 0;
    arg0->unk68 = 0;
    arg0->unk78 = 0;
    arg0->unk7C = 0;
}

void func_8004E40C(s32 arg0) {
    func_80018390()->unkC(arg0);
}

void func_8004E444(Unk_8004E3F4_8004E444 *arg0, s32 **arg1) {
    if (arg1 != NULL) {
        ((Unk_8004E444 *)((Unk_8004E40C_8004E444 *)func_80018390()))->unk10(arg0, arg1);
        if ((**arg1 & 0xF) == 2) {
            arg0->unk60 = (s32)arg1;
            return;
        }
        if ((**arg1 & 0xF) == 5) {
            arg0->unk64 = (s32)arg1;
            return;
        }
        if ((**arg1 & 0xFF) == 16) {
            arg0->unk78 = (s32)arg1;
            return;
        }
        if ((**arg1 & 0xFF) == 32) {
            arg0->unk7C = (s32)arg1;
        }
    }
}

void func_8004E4E8(Unk_8004E3F4 *arg0, s32 **arg1) {
    s32 temp;

    if (arg1 != NULL) {
        temp = **arg1;
        if ((temp & 0xF) == 2) {
            arg0->unk60 = 0;
        } else if ((temp & 0xF) == 5) {
            arg0->unk64 = 0;
        } else if ((temp & 0xFF) == 0x10) {
            arg0->unk78 = 0;
        } else if ((temp & 0xFF) == 0x20) {
            arg0->unk7C = 0;
        }
        func_80018390()->unk14(arg0, arg1);
    }
}

void func_8004E588(Unk_8004E3F4 *arg0) {
    arg0->unk60 = 0;
    arg0->unk64 = 0;
    arg0->unk68 = 0;
    arg0->unk78 = 0;
    arg0->unk7C = 0;
    func_80018390()->unk18(arg0);
}

void func_8004E5D4(Unk_8004E5D4 *arg0, s32 arg1) {
    arg0->unkC = arg1;
    arg0->unk10 = arg1 << 4;
}

s32 func_8004E5E4(s32 *arg0) {
    s32 i;

    EnterCriticalSection();
    for (i = 0; i < 4; i++) {
        arg0[i + 5] = OpenEvent(0xF4000001, D_80086E78[i], 0x2000, 0);
    }
    ExitCriticalSection();
    func_8004F394(arg0);
    return 1;
}

s32 func_8004E678(s32 arg0) {
    func_8004F3BC(arg0);
    func_8004F40C(arg0, CloseEvent, 1);
    return 1;
}

s32 func_8004E6B8(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 sp10;
    s32 var_a1;
    s32 var_s2;

    var_s2 = 0xA;
    *arg2 = 0;
    var_a1 = func_8004E77C(arg0, arg1, &sp10, arg3);
    if (var_a1 == 0 || *arg1 != 0 || *arg3 == 0) {
        do {
            var_a1 = func_8004E77C(arg0, arg1, arg2, arg3);
        } while (var_s2-- != 0 && (var_a1 == 0 || *arg1 != 0 || *arg3 == 0));
    }
    *arg2 |= sp10;
    return var_a1;
}

s32 func_8004E77C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 ret;

    ret = func_8004E7D0(arg0, arg1, arg2);
    if (ret != 0) {
        ret = func_8004E890(arg0, arg1, arg3);
    }
    return ret;
}

s32 func_8004E7D0(Unk_8004E7D0 *arg0, s32 *arg1, s32 *arg2) {
    s32 ret;
    s32 status;

    ret = 1;
    *arg1 = 0;
    *arg2 = 0;
    func_8004F3E4((s32)arg0);
    do {
        status = _card_info(arg0->unk10);
    } while (status == 0);
    status = func_8004F4A4((s32)arg0);
    if (status == 0x100) {
        ret = 0;
    } else if (status == 0x8000) {
        ret = 0;
        *arg1 = 1;
    } else if (status == 0x2000) {
        *arg2 = 1;
        _card_clear(arg0->unk10);
    }
    return ret;
}

s32 func_8004E890(Unk_8004E890 *arg0, s32 *arg1, s32 *arg2) {
    s32 ret;
    s32 r;

    ret = 1;
    *arg1 = 0;
    *arg2 = 1;
    func_8004F3E4((s32)arg0);
    while (_card_load(arg0->unk10) == 0) {
    }
    r = func_8004F4A4((s32)arg0);
    if (r == 0x100) {
        ret = 0;
    } else if (r == 0x8000) {
        ret = 0;
        *arg1 = 1;
    } else if (r == 0x2000) {
        *arg2 = 0;
    }
    return ret;
}

s32 func_8004E940(Unk_8004E940 *arg0) {
    s32 r;
    s32 n = 10;
    do {
        r = format(arg0->unkC != 0 ? D_8008AA9C : D_8008AAA4);
        if (r != 0) {
            break;
        }
    } while (n-- != 0);
    return r;
}

s32 func_8004E9AC(s32 arg0, s32 arg1, u8 *arg2) {
    s32 temp;
    s32 var_s0 = 0;

    if ((arg2 == NULL) || (*arg2 == 0)) {
        return 0;
    }
    do {
        temp = func_8004EA38(arg0, arg1, arg2);
        if (temp != 0) {
            break;
        }
    } while (var_s0-- != 0);
    return temp;
}

s32 func_8004EA38(s32 arg0, s32 arg1, u8 *arg2) {
    char buf[32];
    s32 fd;
    s32 p;

    fd = open(func_8004F32C(buf, ((Unk_8004ECCC *)arg0)->unkC, (char *)arg2), 1);
    if (fd == -1) {
        return 0;
    }
    if (arg1 != 0) {
        p = func_80017B34(0x80);
        read(fd, p, 0x80);
        strcpy(arg1, p + 4);
        func_80017CFC(p);
    }
    close(fd);
    return 1;
}

s8 *func_8004EADC(Unk_8004EADC_obj *arg0, s8 *arg1, s8 *arg2, s8 **arg3) {
    while (*arg3 != NULL) {
        strcpy(arg1, arg2);
        strcat(arg1, *arg3);
        if (arg0->vt->unk54(arg0, 0, arg1) == 0) {
            return arg1;
        }
        arg3++;
    }
    return NULL;
}

s32 func_8004EB88(Unk_8004EADC_obj *arg0, s32 *arg1, s8 **arg2, s8 *arg3, s8 **arg4) {
    s8 buf[32];
    s8 **var_s0;
    s32 var_s3;

    var_s0 = arg4;
    var_s3 = 0;
    while (*var_s0 != NULL) {
        strcpy((s32)buf, (s32)arg3);
        strcat(buf, *var_s0);
        if (arg0->vt->unk54(arg0, *arg1, buf) != 0) {
            var_s3++;
            arg1++;
            *arg2++ = *var_s0;
        }
        var_s0++;
    }
    return var_s3;
}

s32 func_8004EC5C(s32 arg0, u8 arg1, s32 arg2) {
    s32 ret;
    s32 tries = 10;

    do {
        ret = func_8004ECCC(arg0, arg1, arg2);
    } while (ret == 0 && tries-- != 0);
    return ret;
}

s32 func_8004ECCC(Unk_8004ECCC *arg0, s32 arg1, s32 arg2) {
    char buf[32];
    s32 fd;
    u32 blocks;

    blocks = (u32)(arg2 + 0x21FF) >> 13;
    fd = open(func_8004F32C(buf, arg0->unkC, D_8008AAAC), (blocks << 16) | 0x200);
    if (fd != -1) {
        close(fd);
        delete(buf);
        return 1;
    }
    return 0;
}

s32 func_8004ED40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 ret;
    s32 tries = 10;

    do {
        ret = func_8004EDC0(arg0, arg1, arg2, arg3);
    } while (ret == 0 && tries-- != 0);
    return ret;
}

s32 func_8004EDC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    char buf[32];
    s32 fd;
    s32 p;
    s32 ofs;

    fd = open(func_8004F32C(buf, ((Unk_8004ECCC *)arg0)->unkC, (char *)arg1), 1);
    if (fd == -1) {
        return 0;
    }
    p = func_80017B34(0x80);
    read(fd, p, 0x80);
    ofs = (((u8 *)p)[2] << 7) - 0x780;
    func_80017CFC(p);
    lseek(fd, ofs, 0);
    read(fd, arg2, arg3);
    close(fd);
    return 1;
}

s32 func_8004EEA0(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 ret;
    s32 n;

    n = 10;
    func_800507F8(arg2, arg1);
    do {
        ret = func_8004EF6C(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    } while (ret == 0 && n-- != 0);
    if (ret == 0) {
        func_800507F8(arg2, 0);
    }
    return ret;
}

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_8001150C);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011518);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011524);

s32 func_8004EF6C(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6) {
    char sp10[0x20];
    char *name;
    s32 fd;
    u8 *buf;
    u8 *p;

    name = func_8004F32C(sp10, ((Unk_8004ECCC *)arg0)->unkC, (char *)arg1);
    delete(name);
    fd = open(name, (((u32)(arg6 + 0x21FF) >> 13) << 16) | 0x200);
    if (fd == -1) {
        printf("File not create in WriteFile\n");
        return 0;
    }
    close(fd);
    fd = open(name, 2);
    if (fd == -1) {
        return 0;
    }
    p = ((Unk_8004EF6C_arg4 *)arg4)->unk10;
    buf = (u8 *)func_80017B34(0x200);
    buf[0] = 0x53;
    buf[1] = 0x43;
    buf[2] = arg3 + 0x10;
    buf[3] = (u32)(arg6 + 0x1FFF) >> 13;
    strcpy((s32)(buf + 4), arg2);
    *(Unk_8004EF6C_H *)(buf + 0x60) = *(Unk_8004EF6C_H *)(p + 0x14);
    *(Unk_8004EF6C_Icon *)(buf + 0x80) = *(Unk_8004EF6C_Icon *)(p + 0x40);
    *(Unk_8004EF6C_Icon *)(buf + 0x100) = *(Unk_8004EF6C_Icon *)(p + 0xC0);
    *(Unk_8004EF6C_Icon *)(buf + 0x180) = *(Unk_8004EF6C_Icon *)(p + 0x140);
    write(fd, buf, (arg3 << 7) + 0x80);
    func_80017CFC((s32)buf);
    write(fd, (u8 *)arg5, ((u32)(arg6 + 0x7F) >> 7) << 7);
    close(fd);
    return 1;
}

char *func_8004F32C(char *buf, s32 sel, char *suffix) {
    char *src = D_8008AAA4;
    if (sel != 0) {
        src = D_8008AA9C;
    }
    memcpy(buf, src, 6);
    strcat((s8 *)buf, (s8 *)suffix);
    return buf;
}

void func_8004F394(s32 arg0) {
    func_8004F40C(arg0, EnableEvent, 1);
}

void func_8004F3BC(s32 arg0) {
    func_8004F40C(arg0, DisableEvent, 1);
}

void func_8004F3E4(s32 arg0) {
    func_8004F40C(arg0, TestEvent, 0);
}

s32 func_8004F40C(s32 arg0, s32 (*arg1)(), s32 arg2) {
    s32 ret;
    s32 i;

    if (arg2 != 0) {
        EnterCriticalSection();
    }
    for (i = 0; i < 4; i++) {
        ret = arg1(*(s32 *)(arg0 + 0x14 + i * 4));
        if (ret == 0) {
            break;
        }
    }
    if (arg2 != 0) {
        ExitCriticalSection();
    }
    return ret;
}

s32 func_8004F4A4(s32 arg0) {
    return func_8004F4C8(arg0 + 0x14, 4);
}

s32 func_8004F4C8(s32 *arg0, s32 arg1) {
    s32 i;

    for (;;) {
        for (i = 0; i < arg1; i++) {
            if (TestEvent(arg0[i]) != 0) {
                return D_80086E78[i];
            }
        }
    }
}

void func_8004F55C(Unk_8004F55C *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6) {
    arg0->unk30 = arg1;
    arg0->unk34 = arg2;
    arg0->unk38 = 0;
    arg0->unk68 = arg5;
    arg0->unk6C = arg6;
    arg0->unk0->unk10(arg0, (s32)arg3);
    arg0->unk0->unk10(arg0, arg4);
    arg0->unk70 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
}

void func_8004F5DC(Unk_8004F5DC *arg0) {
    arg0->unk6C = 0;
    arg0->unk68 = 0;
    arg0->unk0->unk14(arg0, arg0->unk60);
    arg0->unk0->unk14(arg0, arg0->unk64);
}

void func_8004F638(Unk_8004F638 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_a1;
    s32 temp_v0;

    arg0->unk40 = arg1;
    arg0->unk44 = arg2;
    arg0->unk54 = arg3;
    arg0->unk24 = 1;
    arg0->unk58 = arg4;
    if (func_8004F9D8() != 0) {
        func_8004F810((Unk_8004F810 *)arg0);
        func_8004F704((Unk_8004F704 *)arg0);
        temp_v0 = arg0->unk0->unk5C(arg0, arg0->unk38, arg0->unk3C, arg0->unk30, arg0->unk34);
        arg0->unk2C = temp_v0;
        if (temp_v0 != 0) {
            func_8004F784((Unk_8004F784 *)arg0);
            var_a1 = 0x12;
            if (arg0->unk28 == 0xE) {
                var_a1 = 0xF;
            }
        } else {
            var_a1 = 0xD;
            arg0->unk2C = 0xF;
        }
        arg0->unk0->unk7C(arg0, var_a1);
    }
}

void func_8004F704(Unk_8004F704 *arg0) {
    s32 i;

    if (arg0->unk38 == NULL) {
        arg0->unk38 = (s32 *)func_80017B34(0x40);
        for (i = 0; i < 0xF; i++) {
            arg0->unk38[i] = func_80017B34(0x41);
        }
        arg0->unk3C = func_80017B34(0x40);
    }
}

void func_8004F784(Unk_8004F784 *arg0) {
    s32 i;

    for (i = arg0->unk2C; i < 0xF; i++) {
        arg0->unk38[i] = func_80017CFC(arg0->unk38[i]);
    }
    arg0->unk38[i] = 0;
}

void func_8004F810(Unk_8004F810 *arg0) {
    s32 i;

    if (arg0->unk38 != NULL) {
        func_80017CFC(arg0->unk3C);
        for (i = 0; i < arg0->unk2C; i++) {
            func_80017CFC(arg0->unk38[i]);
        }
        func_80017CFC((s32)arg0->unk38);
        arg0->unk38 = NULL;
    }
}

void func_8004F8A4(Unk_8004F638 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 next;

    arg0->unk40 = arg1;
    arg0->unk44 = arg2;
    arg0->unk48 = arg3;
    arg0->unk24 = 2;
    arg0->unk4C = arg4;
    arg0->unk50 = arg5;
    arg0->unk54 = arg6;
    arg0->unk58 = arg7;
    if (func_8004F9D8(arg0) != 0) {
        if (arg0->unk0->unk54(arg0, 0, arg1) != 0) {
            next = 0xA;
            if (arg0->unk28 == 0xA) {
                next = 0x11;
            } else if (arg0->unk28 == 0x11) {
                next = 0xB;
            }
            arg0->unk0->unk7C(arg0, next);
        } else if (arg0->unk0->unk60(arg0, arg4, arg7) == 0) {
            arg0->unk0->unk7C(arg0, 9);
        } else {
            arg0->unk0->unk7C(arg0, arg0->unk28 == 0x11 ? 0xB : 0x11);
        }
    }
}

s32 func_8004F9D8(Unk_8004F638 *arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 s1;
    s32 s2;

    arg0->unk0->unk44(arg0);
    s1 = arg0->unk0->unk4C(arg0, &sp10, &sp14, &sp18);
    arg0->unk0->unk48(arg0);
    if (s1 != 0 && sp14 == 0 && sp18 != 0) {
        return 1;
    }
    if (s1 == 0) {
        s2 = 2;
    } else if (sp10 != 0) {
        s2 = 3;
    } else if (sp14 != 0) {
        s2 = 4;
    } else if (sp18 == 0) {
        s2 = 6;
        if (arg0->unk24 == 1) {
            s2 = 5;
        }
    }
    arg0->unk0->unk7C(arg0, s2);
    return 0;
}

void func_8004FB04(Unk_8004FB04_obj *arg0, s32 **arg1, s32 arg2) {
    Unk_8004FB04_vt *vt;
    s32 t;

    vt = arg0->vt;
    func_80018390()->unk38(arg0, arg1, arg2);
    t = **arg1;
    if ((t & 0xF) == 2) {
        vt->unk88(arg0, arg1, arg2);
    } else if ((t & 0xF) == 5) {
        vt->unk98(arg0, arg1, arg2);
    } else if ((t & 0xFF) == 0x10) {
        vt->unkA4(arg0, arg1, arg2);
    } else if ((t & 0xFF) == 0x20) {
        vt->unkB0(arg0, arg1, arg2);
    }
}

void func_8004FBE4(Unk_8004FBE4 *arg0, s32 arg1) {
    Unk_8004FBE4_vt *s2;
    s32 i;
    u8 *a1;
    s32 var_v0_2;
    void (*var_v0_3)(void *);
    u32 var_v0;

    s2 = arg0->unk0;
    if (arg0->unk28 == arg1) {
        arg1 = 0x17;
    }
    s2->unk30(arg0, arg1);
    s2->unk84(arg0);
    s2->unk80(arg0, arg1);
    arg0->unk5C = 0;
    switch (arg1) {
    case 19:
        var_v0_2 = s2->unk50(arg0);
        arg1 = 8;
        if (var_v0_2 != 0) {
            arg1 = 0x11;
        }
        goto block_12;
    case 20:
        a1 = arg0->unk40;
        if (*a1 == 0) {
            s2->unk58(arg0, a1, arg0->unk30, arg0->unk34);
        }
        var_v0_2 = s2->unk68(arg0, arg0->unk40, arg0->unk44, arg0->unk4C, arg0->unk50, arg0->unk54, arg0->unk58);
        arg1 = 0xC;
        goto block_10;
    case 21:
        var_v0_2 = s2->unk64(arg0, arg0->unk40, arg0->unk54, arg0->unk58);
        arg1 = 0x10;
block_10:
        if (var_v0_2 != 0) {
            arg1 = 0x16;
        }
block_12:
        s2->unk7C(arg0, arg1);
        var_v0 = arg1 - 0x16;
        break;
    case 17:
        var_v0_3 = s2->unk9C;
        goto block_15;
    case 18:
        var_v0_3 = s2->unkA8;
block_15:
        var_v0_3(arg0);
    default:
        var_v0 = arg1 - 0x16;
        break;
    }
    if (var_v0 < 2U) {
        if (arg0->unk24 == 1 && arg0->unk38 != 0) {
            func_80017CFC(arg0->unk3C);
            for (i = 0; i < arg0->unk2C; i++) {
                func_80017CFC(((s32 *)arg0->unk38)[i]);
            }
            func_80017CFC(arg0->unk38);
            arg0->unk38 = 0;
        }
        arg0->unk28 = 0;
        arg0->unk24 = 0;
    } else {
        arg0->unk28 = arg1;
    }
}

void func_8004FE24(Unk_8004FE24 *arg0, s32 arg1) {
    s8 buf[0x20];
    s8 *dst;
    s8 *str;
    Unk_8004FE24_obj *obj;
    Unk_8004FE24_obj *obj2;

    if (arg1 < 0x11 && arg0->unk68 != 0 && arg0->unk70 == 0) {
        dst = buf;
        dst[0] = 0;
        str = D_80086E80[arg1];
        strcat(dst, D_8008AAB4);
        strcat(dst, str);
        strcat(dst, D_8008AABC);
        obj = func_8003B39C(dst);
        obj->vt->unk78(obj);
        obj2 = func_80041C9C(obj, D_80086EC4, 0);
        arg0->unk70 = obj2;
        obj->vt->unk4(obj);
        obj2->vt->unk4C(obj2, arg0->unk68, D_8008AA94);
    }
}

void func_8004FF40(Unk_8004FF40 *arg0) {
    Unk_8004FF40_obj *obj = arg0->unk70;
    if (obj != NULL) {
        arg0->unk70 = obj->unk0->unk4(obj);
    }
}

void func_8004FF90(Unk_8004FF90 *arg0, s32 arg1, s32 arg2) {
    if (arg0->unk28 != 0) {
        if (arg2 == 0x19) {
            arg0->unk0->unk90(arg0);
        } else if (arg2 == 0x17) {
            arg0->unk0->unk94(arg0);
        }
    }
}

void func_8004FFF4(Unk_8004FFF4 *arg0, s32 arg1) {
    Unk_8004FFF4_obj *obj = arg0->unk6C;
    if (obj != NULL) {
        obj->unk0->unk80(obj, arg1, 0x7F, 0x7F);
    }
}

void func_80050034(Unk_80050034 *arg0) {
    Unk_80050034_vt *vt;

    vt = arg0->unk0;
    switch (arg0->unk28) {
    case 2:
    case 4:
    case 10:
    case 14:
        vt->unk8C(arg0, 0);
        if (arg0->unk28 == 14) {
            strcpy(arg0->unk40, arg0->unk30);
            strcat(arg0->unk40, arg0->unk3C[arg0->unk80]);
            strcpy(arg0->unk44, arg0->unk38[arg0->unk80]);
        }
        if (arg0->unk24 == 2) {
            vt->unk78(arg0, arg0->unk40, arg0->unk44, arg0->unk48, arg0->unk4C, arg0->unk50, arg0->unk54, arg0->unk58);
            return;
        } else if (arg0->unk24 == 1) {
            vt->unk74(arg0, arg0->unk40, arg0->unk44, arg0->unk54, arg0->unk58);
            return;
        }
        break;
    case 6:
        vt->unk8C(arg0, 0);
        vt->unk7C(arg0, 7);
        break;
    case 3:
    case 5:
    case 8:
    case 9:
    case 12:
    case 13:
    case 16:
        vt->unk8C(arg0, 0x10);
        vt->unk7C(arg0, 0x17);
        break;
    }
}

void func_800501F0(Unk_800501F0 *arg0) {
    switch (arg0->unk28) {
    case 4:
    case 6:
    case 0xA:
    case 0xE:
        arg0->unk0->unk8C(arg0, 0x10);
        arg0->unk0->unk7C(arg0, 0x17);
        break;
    }
}

void func_80050280(Unk_800501F0 *arg0) {
    if (arg0->unk28 == 7) {
        if (arg0->unk5C++ >= 6) {
            arg0->unk0->unk7C(arg0, 0x13);
        }
    } else if (arg0->unk28 == 0xB) {
        if (arg0->unk5C++ >= 6) {
            arg0->unk0->unk7C(arg0, 0x14);
        }
    } else if (arg0->unk28 == 0xF) {
        if (arg0->unk5C++ >= 6) {
            arg0->unk0->unk7C(arg0, 0x15);
        }
    }
}

void func_80050340(Unk_80050340 *arg0) {
    if (arg0->unk68 != 0 && arg0->unk60 != 0) {
        if (arg0->unk78 == NULL) {
            arg0->unk78 = func_80050BA8((arg0->unk48 * 2) + arg0->unk44, 1);
            arg0->unk74 = 1;
        }
        arg0->unk0->unk10(arg0, arg0->unk78);
        arg0->unk78->vt->unk44(arg0->unk78, arg0->unk68);
        arg0->unk78->vt->unk4C(arg0->unk78, arg0->unk60, arg0->unk64, arg0->unk6C);
    }
}

void func_80050410(Unk_80050410 *arg0) {
    Unk_80050410_obj *temp;

    if (arg0->unk68 != 0 && arg0->unk60 != 0) {
        temp = arg0->unk78;
        if (temp != NULL) {
            temp->vt->unk50(temp);
            arg0->unk78->vt->unk48(arg0->unk78);
            if (arg0->unk74 != 0) {
                arg0->unk78->vt->unk4(arg0->unk78);
                arg0->unk78 = NULL;
            }
        }
    }
}

void func_800504D0(Unk_800504D0 *arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
    case 2:
        arg0->unk0->unkA0(arg0);
        arg0->unk0->unk78(arg0, arg0->unk40, arg0->unk44, arg0->unk48, arg0->unk4C, arg0->unk50, arg0->unk54, arg0->unk58);
        break;
    case 3:
        arg0->unk0->unkA0(arg0);
        arg0->unk0->unk7C(arg0, 0x17);
        break;
    }
}

void func_800505A8(Unk_800505A8 *arg0) {
    Unk_800505A8_obj *temp_a0;

    if (arg0->unk68 != 0 && arg0->unk60 != 0) {
        if (arg0->unk7C == 0) {
            arg0->unk7C = func_80051A5C(arg0->unk38, 1);
            arg0->unk74 = 1;
        }
        arg0->unk0->unk10(arg0, arg0->unk7C);
        temp_a0 = (Unk_800505A8_obj *)arg0->unk7C;
        temp_a0->vt->unk44(temp_a0, arg0->unk68);
        temp_a0 = (Unk_800505A8_obj *)arg0->unk7C;
        temp_a0->vt->unk4C(temp_a0, arg0->unk60, arg0->unk64, arg0->unk6C);
    }
}

void func_80050670(Unk_8004E3F4 *arg0) {
    Unk_80050670_obj *obj;

    if (arg0->unk68 != 0 && arg0->unk60 != 0) {
        obj = (Unk_80050670_obj *)arg0->unk7C;
        if (obj != NULL) {
            obj->vt->unk50(obj);
            obj = (Unk_80050670_obj *)arg0->unk7C;
            obj->vt->unk48(obj);
            if (arg0->unk74 != 0) {
                obj = (Unk_80050670_obj *)arg0->unk7C;
                obj->vt->unk4(obj);
                arg0->unk7C = 0;
            }
        }
    }
}

void func_80050730(Unk_80050730_obj *arg0, Unk_80050730_src *arg1, s32 arg2) {
    switch (arg2) {
    case 2:
        arg0->unk80 = arg1->unk0->unk9C(arg1);
        arg0->unk0->unkAC(arg0);
        arg0->unk0->unk7C(arg0, 0xE);
        break;
    case 3:
        arg0->unk0->unkAC(arg0);
        arg0->unk0->unk7C(arg0, 0x17);
        break;
    }
}

Unk_8004E2E0 *func_800507E8(void) {
    return (Unk_8004E2E0 *)D_80086DC4;
}

void func_800507F8(Unk_800507F8 *arg0, u8 *arg1) {
    s32 t;
    s32 i;

    if (arg1 != NULL) {
        t = 0xD;
        if ((u32)(arg1[0xE] - 0x38) < 2U) {
            t = 0xE;
        }
        arg0->unk18 = D_8008AAC4[15];
        arg0->unk6 = *(Unk_800507F8_Hex *)&D_8008AAC4[15];
        i = atoi(arg1 + t) - 1;
        arg0->unk6.a.p[1] = D_8008AAC4[i];
    } else {
        arg0->unk6.a = *(Unk_800507F8_Tri *)&D_8008AAC4[15];
    }
}

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011550);

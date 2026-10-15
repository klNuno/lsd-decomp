#include "common.h"

extern void func_800183DC(void *, s32);
typedef struct { u8 p0[0x24]; u32 u24; u8 p1[0x70 - 0x28]; s32 u70; s32 u74; u8 p2[0x120 - 0x78]; u32 u120; s32 u124; } Unk_80059394;
typedef struct Unk_80089EA4 {
    u8 pad[0x6];
    s8 unk6;
    u8 pad_07[0x1];
    s8 unk8;
    s8 unk9;
    u8 padA[0x1];
    s8 unkB;
    u8 padC[0x4];
} Unk_80089EA4;
extern Unk_80089EA4 D_80089EA4[];
typedef struct Unk_8005D944 { u8 pad[0x98]; s32 unk98; } Unk_8005D944;
typedef struct Unk_80063CAC {
    u8 pad[0x4];
    s32 unk4;
    u8 pad0C[0x08];
    s32 unk10;
    u8 pad2[0x08];
    s32 unk1C;
    u8 pad3[0x10];
    s32 unk30;
    u8 pad4[0x10];
    s32 unk44;
} Unk_80063CAC;
typedef struct Unk_8005ED10_0 {
    u8 pad[0xFC];
    s32 uFC;
} Unk_8005ED10_0;
typedef struct Unk_8005ED10 {
    u8 pad0[0x10];
    s32 u10;
    u8 pad1[0x1C - 0x14];
    s32 u1C;
} Unk_8005ED10;
extern void func_80060D80(void);
void func_800573CC(void *arg0, s32 arg1, s32 *arg2);
extern s8 D_80089EAC[];
typedef struct Unk_8005D9D0 { u8 pad[0x98]; s32 unk98; } Unk_8005D9D0;
extern void func_80056D18(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct { u8 pad[0x84]; s32 unk84; } Unk_80061C04_0;
typedef struct { u8 p0[0x10]; s32 u10; u8 p1[0x08]; s32 u1C; s32 u20; } Unk_80061C04;
typedef struct Unk_80063C84 {
    u8 p0[0x10];
    s32 u10;
    u8 p1[0x8];
    s32 u1C;
    s32 u20;
    u8 p2[0xC];
    s32 u30;
    s32 u34;
    u8 p3[0xC];
    s32 u44;
    s32 u48;
} Unk_80063C84;
extern void func_800531CC(void *, void *);
typedef struct Unk_80065BFC {
    u8 pad[0x5C];
    s32 u5C;
} Unk_80065BFC;
s32 func_80065C5C();
typedef struct Unk_80065C2C {
    u8 pad[0x5C];
    s32 u5C;
} Unk_80065C2C;
extern void func_80065CEC();
extern s32 func_80065E1C(Unk_80059394 *arg0);
extern void func_80065F2C(Unk_80059394 *arg0);
void func_8002CC84(void *, void *);
typedef struct Unk_8005EF20_vt { u8 pad[0x48]; void (*fn48)(void *, s32, void *); } Unk_8005EF20_vt;
typedef struct Unk_8005EF20 { Unk_8005EF20_vt *vt; } Unk_8005EF20;
extern s32 D_80089DD8;
extern s32 D_80089E38;
typedef struct Unk_8005F6D4_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_8005F6D4_Vtbl;
typedef struct Unk_8005F6D4 {
    Unk_8005F6D4_Vtbl *vtbl;
} Unk_8005F6D4;
typedef struct Unk_8006519CVtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_8006519CVtbl;
typedef struct Unk_8006519C {
    Unk_8006519CVtbl *vtbl;
} Unk_8006519C;
typedef struct Unk_800651D0_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_800651D0_Vtbl;
typedef struct Unk_800651D0 {
    Unk_800651D0_Vtbl *vtbl;
} Unk_800651D0;
extern s32 D_80089DCC;
typedef struct Unk_80065204_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_80065204_Vtbl;
typedef struct Unk_80065204 {
    Unk_80065204_Vtbl *vtbl;
} Unk_80065204;
typedef struct Unk_8005C9A4 {
    u8 pad[0x2];
    s8 unk2;
    s8 unk3[3];
} Unk_8005C9A4;
extern s8 D_80089EA6[];
typedef struct Unk_8005D95C { u8 pad[0x98]; s32 unk98; } Unk_8005D95C;
void func_8005BF68(s32 arg0);
extern s8 D_80089EAB[];
typedef struct Unk_8005D994 { u8 pad[0x98]; s32 unk98; } Unk_8005D994;
extern void func_8002CD08(s32, void *);
typedef struct Unk_8005D6D4 {
    u8 pad0[0x58];
    s32 u58;
    u8 pad1[0x9C - 0x5C];
    u8 u9C;
    u8 pad2[0xFC - 0x9D];
    s32 uFC;
} Unk_8005D6D4;
typedef struct Unk_80061158_Vtbl {
    u8 pad[0xCC];
    void (*unkCC)(void *, s32, s32);
} Unk_80061158_Vtbl;
typedef struct Unk_80061158 {
    Unk_80061158_Vtbl *vtbl;
    u8 pad[0xF8];
    s32 uFC;
} Unk_80061158;
typedef struct Unk_800661D4_Vtbl {
    u8 pad[0x80];
    void (*unk80)(void *, s32, s32, s32);
} Unk_800661D4_Vtbl;
typedef struct Unk_800661D4_Obj {
    Unk_800661D4_Vtbl *unk0;
} Unk_800661D4_Obj;
typedef struct Unk_800661D4 {
    u8 pad[0x58];
    Unk_800661D4_Obj *unk58;
} Unk_800661D4;
typedef void (*Unk_8005D9F4_Fn)(void *self, s32 arg);
typedef struct Unk_8005D9F4_Vtbl {
    u8 pad_00[0x60];
    Unk_8005D9F4_Fn unk60;
} Unk_8005D9F4_Vtbl;
typedef struct Unk_8005D9F4 {
    Unk_8005D9F4_Vtbl *unk0;
    u8 pad_04[0x24 - 0x04];
    u32 unk24;
    u8 pad_28[0xF0 - 0x28];
    s32 unkF0;
} Unk_8005D9F4;
extern void func_80062570(void *arg0);
typedef struct Unk_80064CA4_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
} Unk_80064CA4_Vtbl;
typedef struct Unk_80064CA4 {
    Unk_80064CA4_Vtbl *unk0;
} Unk_80064CA4;
typedef struct Unk_8005CD58_Vtbl {
    u8 pad_00[0x200];
    s32 (*unk200)(void *);
} Unk_8005CD58_Vtbl;
typedef struct Unk_8005CD58 {
    Unk_8005CD58_Vtbl *vt;
} Unk_8005CD58;
Unk_8005CD58 *D_8008AC00;
extern s8 D_80088D16[];
typedef struct Unk_8005DAAC_Vtbl {
    u8 pad[0x30];
    void (*unk30)(void *, s32);
} Unk_8005DAAC_Vtbl;
typedef struct Unk_8005DAAC {
    Unk_8005DAAC_Vtbl *unk0;
    u8 pad[0xF4 - 0x4];
    s32 unkF4;
} Unk_8005DAAC;
typedef struct Unk_8005E480_0 {
    u8 pad[0x148];
    s32 (*fn148)(void *);
} Unk_8005E480_0;
typedef struct Unk_8005E480 {
    u8 pad0[0x4];
    s32 u4;
    u8 pad1[0x10 - 0x08];
    s32 u10;
    u8 pad2[0x1C - 0x14];
    s32 u1C;
    s32 u20;
} Unk_8005E480;
typedef struct Unk_8005E7A8 {
    u8 pad0[0x4];
    s32 u4;
    u8 pad1[0x10 - 0x8];
    s32 u10;
    u8 pad2[0x1C - 0x14];
    s32 u1C;
    u8 pad3[0x30 - 0x20];
    s32 u30;
    u8 pad4[0x44 - 0x34];
    s32 u44;
} Unk_8005E7A8;
typedef struct Unk_8005E7A8_Obj {
    u8 pad[0xC4];
    void (*unkC4)(void **, s32, s32);
} Unk_8005E7A8_Obj;
typedef struct Unk_8006573C_Vt { u8 pad[0xC]; void (*unkC)(void *); } Unk_8006573C_Vt;
typedef struct Unk_8006573C_Obj { u8 pad[0xF8]; void (*unkF8)(void *); } Unk_8006573C_Obj;
Unk_8006573C_Vt *func_80057C84(void);
typedef struct Unk_80065D64 {
    u8 pad_00[0x6C];
    s32 unk6C;
    s32 unk70;
    u8 *unk74;
} Unk_80065D64;
extern s32 D_80089DF0[];
extern s32 D_80089D78[];
typedef struct Unk_8005E694_Vtbl {
    u8 pad_00[0x48];
    void (*unk48)(void *, s32, void *);
    u8 pad_4C[0xBC - 0x4C];
    void (*unkBC)(void *, void *);
} Unk_8005E694_Vtbl;
typedef struct Unk_8005E694 {
    Unk_8005E694_Vtbl *unk0;
} Unk_8005E694;
typedef struct Unk_80064CEC_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
    u8 pad2[0xC4 - 0x4C];
    void (*unkC4)(void *, s32, s32);
} Unk_80064CEC_Vtbl;
typedef struct Unk_80064CEC {
    Unk_80064CEC_Vtbl *vtbl;
} Unk_80064CEC;
typedef struct Unk_8005DB8C_Vtbl {
    u8 pad[0x114];
    void (*unk114)(void *);
    u8 pad2[0x130 - 0x118];
    void (*unk130)(void *);
} Unk_8005DB8C_Vtbl;
typedef struct Unk_8005DB8C {
    Unk_8005DB8C_Vtbl *unk0;
    u8 pad[0x58 - 0x4];
    void *unk58;
    u8 pad2[0x9C - 0x5C];
    u8 unk9C[0xF8 - 0x9C];
    s32 unkF8;
} Unk_8005DB8C;
typedef struct Unk_8005C5E8_Vtbl {
    u8 pad0[0x4];
    void *(*unk4)(void *);
} Unk_8005C5E8_Vtbl;
typedef struct Unk_8005C5E8_Obj {
    Unk_8005C5E8_Vtbl *vt;
} Unk_8005C5E8_Obj;
typedef struct Unk_8005C5E8 {
    Unk_8005C5E8_Obj *obj;
    s32 unk4;
    u8 pad[0xC];
} Unk_8005C5E8;
extern Unk_8005C5E8 D_80088D28[];
typedef struct Unk_8005C76C_Vt {
    u8 pad[4];
    void *(*fn4)(void *);
} Unk_8005C76C_Vt;
typedef struct Unk_8005C76C {
    Unk_8005C76C_Vt *vt;
} Unk_8005C76C;
typedef struct Unk_8005C76C_Entry {
    Unk_8005C76C *obj;
    u8 pad[0x14 - 4];
} Unk_8005C76C_Entry;
extern Unk_8005C76C_Entry D_80088D2C[];
typedef struct Unk_8005D418_Vtbl {
    u8 pad[0x160];
    void (*unk160)(void *);
} Unk_8005D418_Vtbl;
typedef struct Unk_8005D418 {
    Unk_8005D418_Vtbl *unk0;
    u8 pad[0xC - 0x4];
    s32 unkC;
    u8 pad2[0x4C - 0x10];
    s32 unk4C;
} Unk_8005D418;
typedef struct Unk_80066818_Vtbl {
    u8 pad[0x8];
    s32 (*unk8)(void *, s32, s32);
    void (*unkC)(void *);
    u8 pad1[0x50 - 0x10];
    void (*unk50)(void *);
    u8 pad2[0xE0 - 0x54];
    void (*unkE0)(void *, void *, s32);
} Unk_80066818_Vtbl;
extern Unk_80066818_Vtbl *func_80066818(void);
typedef struct Unk_8005D7FC_Node {
    u8 pad[0x18];
    s32 unk18;
    u8 pad2[0x4];
    s32 unk20;
} Unk_8005D7FC_Node;
typedef struct Unk_8005D7FC_Pos {
    s32 unk0;
    u8 pad[0x4];
    s32 unk8;
} Unk_8005D7FC_Pos;
typedef struct Unk_8005D7FC_Arg0 {
    u8 pad[0x14];
    Unk_8005D7FC_Node *unk14;
} Unk_8005D7FC_Arg0;
typedef struct Unk_8005D7FC_Arg1 {
    u8 pad[0xC];
    s32 unkC;
    u8 pad2[0x4];
    u8 *unk14;
} Unk_8005D7FC_Arg1;
typedef struct Unk_80066748_Vt {
    u8 pad[0x10];
    void (*unk10)(void *, void *);
} Unk_80066748_Vt;
typedef struct Unk_80066748 {
    Unk_80066748_Vt *unk0;
    u8 pad[0x94 - 0x4];
    void *unk94;
} Unk_80066748;
typedef struct Unk_800667B0_Vt { u8 pad[0x14]; void (*fn14)(void *, void *); } Unk_800667B0_Vt;
typedef struct Unk_800667B0 {
    Unk_800667B0_Vt *vt;
    u8 pad[0x94 - 0x4];
    struct Unk_800667B0 *unk94;
} Unk_800667B0;
extern s32 rand(void);
typedef struct Unk_8005DA3C_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
    u8 pad_64[0x164 - 0x64];
    void (*unk164)(void *, s32);
    u8 pad_168[0x16C - 0x168];
    void (*unk16C)(void *);
} Unk_8005DA3C_Vtbl;
typedef struct Unk_8005DA3C {
    Unk_8005DA3C_Vtbl *unk0;
    u8 pad_04[0xF0 - 0x04];
    s32 unkF0;
} Unk_8005DA3C;
typedef struct Unk_80064AA4_Vtbl {
    u8 pad[0x48];
    void (*unk48)(void *, s32, void *);
    u8 pad2[0xCC - 0x4C];
    void (*unkCC)(void *, s32, s32);
} Unk_80064AA4_Vtbl;
typedef struct Unk_80064AA4 {
    Unk_80064AA4_Vtbl *vtbl;
    u8 pad[0xF8];
    s32 unkFC;
} Unk_80064AA4;
s32 D_8008ABF8;
typedef struct Unk_800654A0_vt {
    u8 pad_00[0x48];
    void (*unk48)(void *self, s32 arg1, void *arg2);
    u8 pad_4C[0x78];
    void (*unkC4)(void *self, s32 arg1, s32 arg2);
} Unk_800654A0_vt;
typedef struct Unk_800654A0 {
    Unk_800654A0_vt *vt;
    u8 pad_04[0x90];
    void *unk94;
} Unk_800654A0;
extern void func_8001EACC(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_80089E80;
typedef struct Unk_80065B80_Vt {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x108 - 0x8];
    void (*unk108)(void *);
} Unk_80065B80_Vt;
typedef struct Unk_80065B80 {
    Unk_80065B80_Vt *vt;
} Unk_80065B80;
typedef struct Unk_80066150_Vt {
    u8 pad[0xC4];
    void (*unkC4)(void *, s32, s32);
} Unk_80066150_Vt;
typedef struct Unk_80066150_Inner_Vt {
    u8 pad[0x88];
    void (*unk88)(void *, s32);
} Unk_80066150_Inner_Vt;
typedef struct Unk_80066150_Inner {
    Unk_80066150_Inner_Vt *vt;
} Unk_80066150_Inner;
typedef struct Unk_80066150 {
    Unk_80066150_Vt *unk0;
    u8 pad[0x64 - 0x4];
    s32 unk64;
    Unk_80066150_Inner *unk68;
} Unk_80066150;
typedef struct Unk_80063CC8_Vtbl {
    u8 pad[0x148];
    s32 (*fn148)(void *);
} Unk_80063CC8_Vtbl;
typedef struct Unk_80063CC8_Obj {
    Unk_80063CC8_Vtbl *unk0;
    u8 p0[0x80 - 0x4];
    s32 unk80;
} Unk_80063CC8_Obj;
typedef struct Unk_80063CC8 {
    u8 p0[0x4];
    s32 unk4;
    u8 p1[0x08];
    s32 unk10;
    u8 p2[0x08];
    s32 unk1C;
} Unk_80063CC8;
typedef struct Unk_80063E68 {
    u8 pad_00[0x4];
    s32 unk4;
    u8 pad_08[0x10 - 0x8];
    s32 unk10;
    u8 pad_14[0x1C - 0x14];
    s32 unk1C;
    s32 unk20;
} Unk_80063E68;
typedef struct Unk_80065CEC_Vtbl {
    u8 pad[0x100];
    s32 (*unk100)(void *);
    void (*unk104)(void *);
} Unk_80065CEC_Vtbl;
typedef struct Unk_80065CEC_Obj_Vtbl {
    u8 pad[0x4];
    void *(*unk4)(void *);
} Unk_80065CEC_Obj_Vtbl;
typedef struct Unk_80065CEC_Obj {
    Unk_80065CEC_Obj_Vtbl *vt;
} Unk_80065CEC_Obj;
typedef struct Unk_80065CEC {
    Unk_80065CEC_Vtbl *unk0;
    u8 pad[0x5C - 0x4];
    Unk_80065CEC_Obj *unk5C;
    s32 unk60;
} Unk_80065CEC;
typedef struct Unk_800660BC_Src {
    u8 pad[0x118];
    s32 unk118;
    s32 unk11C;
    s32 unk120;
} Unk_800660BC_Src;
typedef struct Unk_800660BC {
    Unk_800660BC_Src *unk0;
    u8 pad[0x78 - 0x4];
    s32 unk78;
} Unk_800660BC;
extern s8 D_80089AC4[];
extern s16 *D_80089A8C[];
s32 func_8005C930(s32 arg0, s32 arg1);
typedef struct Unk_80065A5C_Vt { u8 pad[0x60]; void (*unk60)(void *, s32); } Unk_80065A5C_Vt;
typedef struct Unk_80065A5C_Obj { Unk_80065A5C_Vt *vt; } Unk_80065A5C_Obj;
typedef struct Unk_80065A5C { u8 p0[0x6C]; s32 u6C; Unk_80065A5C_Obj **u70; } Unk_80065A5C;
typedef struct Unk_800662BC_Vtbl {
    u8 pad[0x138];
    void *(*unk138)(void *, void *, void *);
} Unk_800662BC_Vtbl;
typedef struct Unk_800662BC {
    Unk_800662BC_Vtbl *vt;
} Unk_800662BC;
s32 func_8005CFDC(s32 arg0, s32 arg1, s32 arg2);
extern void func_8005C6D8(s32);
s32 D_8008ABFC;
s32 D_8008AC04;
s32 D_8008AC08;
typedef struct Unk_8005D1EC_Obj_Vtbl {
    u8 pad[0x4];
    void (*unk4)(void *);
} Unk_8005D1EC_Obj_Vtbl;
typedef struct Unk_8005D1EC_Obj {
    Unk_8005D1EC_Obj_Vtbl *vt;
} Unk_8005D1EC_Obj;
typedef struct Unk_8005D1EC {
    u8 pad[0x100];
    Unk_8005D1EC_Obj *unk100;
    Unk_8005D1EC_Obj *unk104;
} Unk_8005D1EC;
extern s32 func_8002CC34(s32, void *, s32, void *, s32);
extern s32 D_80089EB0[];
typedef struct Unk_8005DAFC_Vtbl {
    u8 pad_00[0x110];
    void (*unk110)(void *);
    u8 pad_114[0x12C - 0x114];
    void (*unk12C)(void *);
} Unk_8005DAFC_Vtbl;
typedef struct Unk_8005DAFC {
    Unk_8005DAFC_Vtbl *unk0;
    u8 pad_04[0x58 - 0x04];
    s32 unk58;
    u8 pad_5C[0x98 - 0x5C];
    s32 unk98;
    u8 unk9C[0xF8 - 0x9C];
    s32 unkF8;
    s32 unkFC;
} Unk_8005DAFC;
s32 func_8005E02C(void *, s32);
typedef struct Unk_8005DF9C {
    Unk_8005DAAC_Vtbl *unk0;
    u8 pad[0x98 - 0x4];
    s32 unk98;
} Unk_8005DF9C;
typedef struct Unk_80060CF0 {
    Unk_8005D418_Vtbl *unk0;
    u8 pad4[0x44 - 0x4];
    s32 unk44;
    u8 pad48[0x80 - 0x48];
    s32 unk80;
    s32 unk84;
    u8 pad88[0xFC - 0x88];
    s32 unkFC;
} Unk_80060CF0;
typedef struct Unk_80064450_Vtbl {
    u8 pad[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad2[0x128 - 0xC8];
    void (*unk128)(void *, s32);
} Unk_80064450_Vtbl;
typedef struct Unk_80064450 {
    Unk_80064450_Vtbl *unk0;
    u8 pad[0x7C - 0x4];
    s32 unk7C;
    s32 unk80;
    u8 pad2[0xFC - 0x84];
    s32 unkFC;
} Unk_80064450;
typedef struct Unk_8005D278_Vtbl {
    u8 pad_00[0x70];
    void (*unk70)(void *, s32);
    u8 pad_74[0x10C - 0x74];
    void (*unk10C)(void *, s32);
    u8 pad_110[0x160 - 0x110];
    void (*unk160)(void *);
} Unk_8005D278_Vtbl;
typedef struct Unk_8005D278 {
    Unk_8005D278_Vtbl *unk0;
    u8 pad[0x98 - 0x4];
    s32 unk98;
} Unk_8005D278;
typedef struct Unk_800628D4_Vtbl {
    u8 pad[0x30];
    void (*unk30)(void *, s32);
    u8 pad2[0x130 - 0x34];
    void (*unk130)(void *);
} Unk_800628D4_Vtbl;
typedef struct Unk_800628D4 {
    Unk_800628D4_Vtbl *unk0;
    u8 pad[0x80 - 0x4];
    s32 unk80;
    u8 pad2[0x94 - 0x84];
    void *unk94;
    u8 pad3[0xFC - 0x98];
    s32 unkFC;
} Unk_800628D4;
typedef struct Unk_8005CFDC_Vtbl {
    u8 pad_00[0x8];
    s32 (*unk8)(s32, s32, s32, s32);
} Unk_8005CFDC_Vtbl;
Unk_8005CFDC_Vtbl *func_8005E150(void);
s32 func_80017B34(s32);
void func_80017CFC(s32);
typedef struct Unk_80066818_Vtbl_800659D0 {
    u8 pad[0x50];
    void (*unk50)(void *);
    u8 pad2[0xE0 - 0x54];
    void (*unkE0)(void *, void *, s32);
} Unk_80066818_Vtbl_800659D0;
typedef struct Unk_800659D0_Vtbl {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32);
    u8 pad_18[0x140 - 0x18];
    void (*unk140)(void *);
} Unk_800659D0_Vtbl;
typedef struct Unk_800659D0 {
    Unk_800659D0_Vtbl *unk0;
    u8 pad_04[0xC - 0x4];
    s32 unkC;
    u8 pad_10[0x50 - 0x10];
    s32 unk50;
} Unk_800659D0;
typedef struct Unk_80066818_Vtbl_800655D4 {
    u8 pad[0x8];
    s32 (*unk8)(void *, s32, s32);
    u8 pad2[0x50 - 0x0C];
    void (*unk50)(void *);
} Unk_80066818_Vtbl_800655D4;
typedef struct Unk_80065C5C {
    u8 pad[0xC];
    Unk_80065CEC_Obj *unkC;
} Unk_80065C5C;
extern Unk_80065CEC_Obj *func_8004468C(Unk_80065C5C *arg0);
extern Unk_8005CFDC_Vtbl *func_8005E150(void);
typedef struct Unk_8005D068_Vtbl {
    u8 pad_00[0x40];
    void (*unk40)(void *);
} Unk_8005D068_Vtbl;
typedef struct Unk_8005D068 {
    void *unk0;
    u8 pad_04[0x98 - 0x04];
    s32 unk98;
    s32 unk9C;
    u8 pad_A0[0x100 - 0xA0];
    s32 unk100;
    s32 unk104;
} Unk_8005D068;
s32 func_8005D714(void *arg0, u8 *arg1, s32 arg2, s32 arg3);
typedef struct Unk_8005E0B0_Vtbl {
    u8 pad_00[0x16C];
    void (*unk16C)(void *);
} Unk_8005E0B0_Vtbl;
typedef struct Unk_8005E0B0 {
    Unk_8005E0B0_Vtbl *unk0;
    u8 pad_04[0x14 - 0x04];
    u8 *unk14;
    u8 pad_18[0x98 - 0x18];
    s32 unk98;
    u8 pad_9C[0xF0 - 0x9C];
    s32 unkF0;
    u8 pad_F4[0xF8 - 0xF4];
    s32 unkF8;
} Unk_8005E0B0;
typedef struct Unk_800636E4_Vtbl {
    u8 pad[0x16C];
    void (*unk16C)(void *);
} Unk_800636E4_Vtbl;
typedef struct Unk_80063DC8_Vtbl {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
    u8 pad_34[0x16C - 0x34];
    void (*unk16C)(void *);
} Unk_80063DC8_Vtbl;
typedef struct Unk_80063DC8 {
    Unk_80063DC8_Vtbl *unk0;
    u8 pad4[0x44 - 0x4];
    s32 unk44;
    u8 pad48[0x80 - 0x48];
    s32 unk80;
    u8 pad84[0xFC - 0x84];
    s32 unkFC;
} Unk_80063DC8;
typedef struct Unk_80065790_CallVt { u8 pad[0x38]; void (*unk38)(void *, u16 **, s32); } Unk_80065790_CallVt;
typedef struct Unk_80065790_Vt { u8 pad[0x4]; void (*unk4)(void *); } Unk_80065790_Vt;
typedef struct Unk_80065790 {
    Unk_80065790_Vt *unk0;
    u8 pad[0x60 - 0x4];
    s32 unk60;
} Unk_80065790;
typedef struct Unk_80065AE0_Vt { u8 pad[0x70]; void (*unk70)(void *, s32); } Unk_80065AE0_Vt;
typedef struct Unk_80065AE0_Obj { Unk_80065AE0_Vt *unk0; } Unk_80065AE0_Obj;
typedef struct Unk_80065AE0 { u8 pad_00[0x6C]; s32 unk6C; Unk_80065AE0_Obj **unk70; } Unk_80065AE0;
extern void func_8001E600(void *arg0, void *arg1, void *arg2, s32 arg3);
typedef struct Unk_8005CF34_Vtbl {
    u8 pad[0x4C];
    void (*unk4C)(void *self, void *arg1, s32 arg2, s32 arg3, void *arg4);
    void (*unk50)(void *self);
} Unk_8005CF34_Vtbl;
typedef struct Unk_8005CF34_Obj {
    Unk_8005CF34_Vtbl *vt;
} Unk_8005CF34_Obj;
typedef struct Unk_8005CF34 {
    u8 pad[0x4];
    Unk_8005CF34_Obj *unk4;
    s32 unk8;
} Unk_8005CF34;
extern s16 D_80089C64[];
extern s16 D_80089C70[];
typedef struct Unk_func_800650F4_Obj {
    u8 pad[0x44];
    void (*unk44)(void *, s32, s16 *);
} Unk_func_800650F4_Obj;
extern s32 D_80089D54[];
typedef struct Unk_80063094_Vtbl {
    u8 pad_00[0xBC];
    void (*unkBC)(void *, void *);
    u8 pad_C0[0x130 - 0xC0];
    void (*unk130)(void *);
} Unk_80063094_Vtbl;
typedef struct Unk_80063094 {
    Unk_80063094_Vtbl *unk0;
    u8 pad[0x80 - 0x4];
    s32 unk80;
    s32 unk84;
    u8 pad2[0x94 - 0x88];
    void *unk94;
    u8 pad3[0xFC - 0x98];
    s32 unkFC;
} Unk_80063094;
extern s32 D_80089C7C[];
typedef struct Unk_800624BC_Vtbl {
    u8 pad[0x44];
    void (*unk44)(void *, s32, void *);
    u8 pad2[0xC4 - 0x48];
    void (*unkC4)(void *, s32, s32);
} Unk_800624BC_Vtbl;
typedef struct Unk_800624BC {
    Unk_800624BC_Vtbl *unk0;
    u8 pad[0x44 - 0x4];
    s32 unk44;
    u8 pad2[0xFC - 0x48];
    s32 uFC;
} Unk_800624BC;
typedef struct Unk_8005E6F0_Vtbl {
    u8 pad[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad2[0x148 - 0xC8];
    s32 (*fn148)(void *);
} Unk_8005E6F0_Vtbl;
typedef struct Unk_8005E6F0_Obj {
    Unk_8005E6F0_Vtbl *unk0;
    u8 p0[0x80 - 0x4];
    s32 unk80;
} Unk_8005E6F0_Obj;
typedef struct Unk_80065918_CallVt { u8 pad[0x4C]; void (*unk4C)(void *, s32, s32); } Unk_80065918_CallVt;
typedef struct Unk_80065918_Vtbl {
    u8 pad[0x10];
    void (*unk10)(void *, s32);
    u8 pad2[0x13C - 0x14];
    void (*unk13C)(void *, void *);
} Unk_80065918_Vtbl;
typedef struct Unk_80065918 {
    Unk_80065918_Vtbl *unk0;
    u8 pad[0xC - 0x4];
    s32 unkC;
    u8 pad2[0x50 - 0x10];
    s32 unk50;
} Unk_80065918;
typedef struct Unk_8005DEE0_Vtbl {
    u8 pad[0x168];
    void (*unk168)(void *);
} Unk_8005DEE0_Vtbl;
typedef struct Unk_8005DEE0 {
    Unk_8005DEE0_Vtbl *unk0;
    u8 pad_04[0x14 - 0x04];
    u8 *unk14;
    u8 pad_18[0x44 - 0x18];
    s32 unk44;
    u8 pad_48[0x98 - 0x48];
    s32 unk98;
    u8 pad_9C[0xF0 - 0x9C];
    s32 unkF0;
    u8 pad_F4[0xF8 - 0xF4];
    s32 unkF8;
} Unk_8005DEE0;
typedef struct Unk_8005E3C4_Vtbl {
    u8 pad[0x30];
    void (*unk30)(void *, s32);
    u8 pad2[0xC4 - 0x34];
    void (*unkC4)(void *, s32, s32);
} Unk_8005E3C4_Vtbl;
typedef struct Unk_8005E3C4 {
    Unk_8005E3C4_Vtbl *unk0;
    u8 pad[0x94 - 0x4];
    void *unk94;
    u8 pad2[0xFC - 0x98];
    s32 unkFC;
} Unk_8005E3C4;
typedef struct Unk_8005E3C4_Obj_Vtbl {
    u8 pad[0x130];
    void (*unk130)(void *, s32);
} Unk_8005E3C4_Obj_Vtbl;
typedef struct Unk_8005E3C4_Obj {
    Unk_8005E3C4_Obj_Vtbl *vt;
} Unk_8005E3C4_Obj;
typedef struct Unk_80064618_Vtbl {
    u8 pad[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad2[0x160 - 0xC8];
    void (*unk160)(void *);
} Unk_80064618_Vtbl;
typedef struct Unk_80064618_Vtbl100 {
    u8 pad[0xD4];
    void (*unkD4)(void *, void *, s32, s32);
} Unk_80064618_Vtbl100;
typedef struct Unk_80064618_Obj100 {
    Unk_80064618_Vtbl100 *vt;
} Unk_80064618_Obj100;
typedef struct Unk_80064618_Vtbl94 {
    u8 pad[0x21C];
    void (*unk21C)(void *);
} Unk_80064618_Vtbl94;
typedef struct Unk_80064618_Obj94 {
    Unk_80064618_Vtbl94 *vt;
} Unk_80064618_Obj94;
typedef struct Unk_80064618 {
    Unk_80064618_Vtbl *unk0;
    u8 pad4[0x50 - 0x4];
    void *unk50;
    u8 pad54[0x94 - 0x54];
    Unk_80064618_Obj94 *unk94;
    u8 pad98[0xF4 - 0x98];
    s32 unkF4;
    u8 padF8[0x100 - 0xF8];
    Unk_80064618_Obj100 *unk100;
} Unk_80064618;
extern s32 func_8005D108(void *, void *, s32, s32, s32);
typedef struct Unk_80065514_Vtbl {
    u8 pad_00[0xD0];
    void (*unkD0)(void *, s32, s32);
    u8 pad_D4[0x130 - 0xD4];
    void (*unk130)(void *);
} Unk_80065514_Vtbl;
typedef struct Unk_80065514 {
    Unk_80065514_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    u8 pad_48[0x94 - 0x48];
    void *unk94;
    u8 pad_98[0xFC - 0x98];
    s32 unkFC;
} Unk_80065514;
typedef struct Unk_8005F544_Vtbl {
    u8 pad0[0xD0];
    void (*unkD0)(void *, s32, s32);
    u8 pad1[0x148 - 0xD4];
    s32 (*fn148)(void *);
} Unk_8005F544_Vtbl;
typedef struct Unk_8005F544_Obj {
    Unk_8005F544_Vtbl *vt;
    u8 pad4[0x80 - 0x4];
    s32 unk80;
    u8 pad84[0xFC - 0x84];
    s32 uFC;
} Unk_8005F544_Obj;
void func_80063CAC(Unk_80063CAC *arg0);
typedef struct Unk_80063BC0_Vtbl {
    u8 pad_00[0x12C];
    void (*unk12C)(void *);
    void (*unk130)(void *);
    u8 pad_134[0x16C - 0x134];
    void (*unk16C)(void *);
} Unk_80063BC0_Vtbl;
typedef struct Unk_80063BC0 {
    Unk_80063BC0_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    u8 pad_48[0x80 - 0x48];
    s32 unk80;
    s32 unk84;
    u8 pad_88[0xFC - 0x88];
    s32 unkFC;
} Unk_80063BC0;
typedef struct Unk_8005DE18_Vtbl {
    u8 pad[0x164];
    void (*unk164)(void *, s32);
} Unk_8005DE18_Vtbl;
typedef struct Unk_8005DE18 {
    Unk_8005DE18_Vtbl *unk0;
    u8 pad_04[0x14 - 0x04];
    u8 *unk14;
    u8 pad_18[0x94 - 0x18];
    void *unk94;
    s32 unk98;
    u8 pad_9C[0xF0 - 0x9C];
    s32 unkF0;
    s32 unkF4;
} Unk_8005DE18;
typedef struct Unk_8005F608_Vtbl {
    u8 pad_00[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad_C8[0xCC - 0xC8];
    void (*unkCC)(void *, s32, s32);
} Unk_8005F608_Vtbl;
typedef struct Unk_8005F608 {
    Unk_8005F608_Vtbl *vtbl;
    u8 pad_04[0xFC - 0x04];
    s32 uFC;
} Unk_8005F608;
typedef struct Unk_8005FDFC_Vtbl {
    u8 pad0[0x48];
    void (*unk48)(void *, s32, void *);
    u8 pad1[0xC4 - 0x4C];
    void (*unkC4)(void *, s32, s32);
    u8 pad2[0x144 - 0xC8];
    s32 (*unk144)(void *, void *);
} Unk_8005FDFC_Vtbl;
typedef struct Unk_8005FDFC {
    Unk_8005FDFC_Vtbl *unk0;
    u8 pad4[0x44 - 0x4];
    s32 unk44;
    u8 pad48[0x94 - 0x48];
    void *unk94;
} Unk_8005FDFC;
typedef struct Unk_8005F0D8_Vtbl {
    u8 pad[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad2[0x148 - 0xC8];
    s32 (*fn148)(void *);
} Unk_8005F0D8_Vtbl;
typedef struct Unk_8005F0D8 {
    Unk_8005F0D8_Vtbl *unk0;
    u8 pad[0x80 - 0x4];
    s32 unk80;
} Unk_8005F0D8;
typedef struct Unk_80061E60_Vtbl {
    u8 pad[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad2[0x148 - 0xC8];
    s32 (*unk148)(void *);
} Unk_80061E60_Vtbl;
typedef struct Unk_80061E60 {
    Unk_80061E60_Vtbl *vt;
} Unk_80061E60;
extern s32 D_80089C88;
typedef struct Unk_80062660_ObjVtbl {
    u8 pad[0x44];
    void (*unk44)(void *, s32, void *);
    u8 pad2[0x130 - 0x48];
    void (*unk130)(void *, s32);
} Unk_80062660_ObjVtbl;
typedef struct Unk_80062660_Obj {
    Unk_80062660_ObjVtbl *vt;
} Unk_80062660_Obj;
typedef struct Unk_80062660_Vtbl {
    u8 pad[0x160];
    void (*unk160)(void *);
} Unk_80062660_Vtbl;
typedef struct Unk_80062660 {
    Unk_80062660_Vtbl *unk0;
    u8 pad[0x80 - 0x4];
    s32 unk80;
    u8 pad2[0x94 - 0x84];
    Unk_80062660_Obj *unk94;
    u8 pad3[0xFC - 0x98];
    s32 unkFC;
} Unk_80062660;
typedef struct Unk_80062970_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, void *);
    void (*unk48)(void *, s32, void *);
    u8 pad_4C[0x12C - 0x4C];
    void (*unk12C)(void *);
    void (*unk130)(void *);
} Unk_80062970_Vtbl;
typedef struct Unk_80062970 {
    Unk_80062970_Vtbl *unk0;
    u8 pad_04[0x80 - 0x04];
    s32 unk80;
    s32 unk84;
    u8 pad_88[0xF4 - 0x88];
    s32 unkF4;
} Unk_80062970;
extern s16 D_80089DFC[];
typedef struct Unk_800623E8_Obj {
    Unk_80063CC8_Vtbl *unk0;
    u8 p0[0x80 - 0x4];
    s32 unk80;
    s32 unk84;
} Unk_800623E8_Obj;
typedef struct Unk_800623E8 {
    u8 p0[0x4];
    s32 unk4;
    u8 p1[0x08];
    s32 unk10;
    u8 p2[0x08];
    s32 unk1C;
    s32 unk20;
    u8 p3[0x0C];
    s32 unk30;
    s32 unk34;
    u8 p4[0x0C];
    s32 unk44;
    s32 unk48;
} Unk_800623E8;
typedef struct Unk_800641C0_Vtbl {
    u8 pad[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad2[0x128 - 0xC8];
    void (*unk128)(void *, s32);
    u8 pad3[0x148 - 0x12C];
    s32 (*unk148)(void *);
} Unk_800641C0_Vtbl;
typedef struct Unk_800641C0 {
    Unk_800641C0_Vtbl *unk0;
    u8 pad[0x7C - 0x4];
    s32 unk7C;
    s32 unk80;
    u8 pad2[0xFC - 0x84];
    s32 unkFC;
} Unk_800641C0;
typedef struct Unk_8005D714_Vtbl {
    u8 pad_00[0x120];
    s32 (*unk120)(void *, s32, s32, void *, s32);
} Unk_8005D714_Vtbl;
typedef struct Unk_8005D714_Obj {
    Unk_8005D714_Vtbl *vt;
} Unk_8005D714_Obj;
typedef struct Unk_8005D714_Arg0 {
    u8 pad_00[0x94];
    Unk_8005D714_Obj *unk94;
    s32 unk98;
} Unk_8005D714_Arg0;
typedef struct Unk_8005D714_Arg1 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8005D714_Arg1;
s32 func_8005C8AC(s16 *arg0);
s32 func_8005C9A4(s32 arg0, Unk_8005C9A4 *arg1);
s32 func_8005C9DC(s32 arg0, Unk_8005C9A4 *arg1, s32 arg2);
void func_8005CF34(Unk_8005CF34 *arg0);
extern s32 func_80044A0C(s32 arg0);
extern void func_8005CAB4(s32 arg0, Unk_8005C9A4 *arg1, void *arg2, s32 arg3);
extern void *D_80089A44[];
typedef struct Unk_8005D480_Fn {
    u8 pad[0x98];
    void (*unk98)(void *, void *, s32);
} Unk_8005D480_Fn;
typedef struct Unk_8005D480_Vtbl {
    u8 pad[0x170];
    s32 (*unk170)(void *);
    void (*unk174)(void *);
    void (*unk178)(void *);
    s32 (*unk17C)(void *);
    void (*unk180)(void *);
} Unk_8005D480_Vtbl;
typedef struct Unk_8005D480 {
    Unk_8005D480_Vtbl *vt;
} Unk_8005D480;
extern s8 D_80089EAE[];
typedef struct Unk_8005D864_Vt {
    u8 pad0[0x144];
    s32 (*unk144)(void *, void *);
} Unk_8005D864_Vt;
typedef struct Unk_8005D864 {
    Unk_8005D864_Vt *vt;
    u8 pad4[0x94 - 0x4];
    void *unk94;
    s32 unk98;
    u8 pad9C[0xB0 - 0x9C];
    s32 unkB0;
} Unk_8005D864;
typedef struct Unk_8005EBB4_Vtbl {
    u8 pad[0x30];
    void (*unk30)(void *, s32);
    u8 pad2[0x148 - 0x34];
    s32 (*fn148)(void *);
} Unk_8005EBB4_Vtbl;
typedef struct Unk_8005EBB4 {
    Unk_8005EBB4_Vtbl *unk0;
    u8 pad[0x44 - 0x4];
    s32 unk44;
    u8 pad2[0x80 - 0x48];
    s32 unk80;
} Unk_8005EBB4;
extern s32 D_80089E50;
typedef struct Unk_8005EFF4_Vtbl {
    u8 pad_00[0x48];
    void (*fn48)(void *, s32, void *);
    u8 pad_4C[0xC4 - 0x4C];
    void (*fnC4)(void *, s32, s32);
    u8 pad_C8[0x148 - 0xC8];
    s32 (*fn148)(void *);
} Unk_8005EFF4_Vtbl;
typedef struct Unk_8005EFF4 {
    Unk_8005EFF4_Vtbl *vt;
    u8 pad_04[0xFC - 0x04];
    s32 uFC;
} Unk_8005EFF4;
typedef struct Unk_8005EFF4_Arg1 {
    u8 pad_00[0x4];
    s32 u4;
    u8 pad_08[0x10 - 0x08];
    s32 u10;
    u8 pad_14[0x1C - 0x14];
    s32 u1C;
} Unk_8005EFF4_Arg1;
typedef struct Unk_800620C4_Vtbl {
    u8 pad0[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad1[0xCC - 0xC8];
    void (*unkCC)(void *, s32, s32);
} Unk_800620C4_Vtbl;
typedef struct Unk_800620C4 {
    Unk_800620C4_Vtbl *unk0;
    u8 pad[0x44 - 0x04];
    s32 unk44;
    u8 pad2[0x94 - 0x48];
    void *unk94;
    u8 pad3[0xFC - 0x98];
    s32 unkFC;
} Unk_800620C4;
typedef struct Unk_80065FD8_Vtbl {
    u8 pad[0x134];
    s32 (*unk134)(void *, s32, s32);
} Unk_80065FD8_Vtbl;
typedef struct Unk_80065FD8_Ent {
    u8 pad[0x10];
    s32 unk10;
} Unk_80065FD8_Ent;
typedef struct Unk_80065FD8_Arr {
    u8 pad[0x8];
    Unk_80065FD8_Ent *unk8[1];
} Unk_80065FD8_Arr;
typedef struct Unk_80065FD8_Tbl {
    u8 pad[0x10];
    Unk_80065FD8_Arr *unk10;
} Unk_80065FD8_Tbl;
typedef struct Unk_80065FD8_Mid {
    u8 pad[0x30];
    Unk_80065FD8_Tbl *unk30;
} Unk_80065FD8_Mid;
typedef struct Unk_80065FD8 {
    Unk_80065FD8_Vtbl *unk0;
    u8 pad4[0x14 - 0x4];
    s32 *unk14;
    u8 pad18[0x24 - 0x18];
    s32 unk24;
    u8 pad28[0x5C - 0x28];
    Unk_80065FD8_Mid *unk5C;
    u8 pad60[0x78 - 0x60];
    void (*unk78)(void *);
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
} Unk_80065FD8;
extern s16 D_80089E8C[];
extern s32 D_80089DC0[];
typedef struct Unk_80060710_Vtbl {
    u8 pad_00[0x48];
    void (*unk48)(void *, s32, void *);
    u8 pad_4C[0xBC - 0x4C];
    void (*unkBC)(void *, void *);
} Unk_80060710_Vtbl;
typedef struct Unk_80060710 {
    Unk_80060710_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    u8 pad_48[0xFC - 0x48];
    s32 uFC;
} Unk_80060710;
typedef struct Unk_80060A4C_Vtbl {
    u8 pad0[0xC4];
    void (*unkC4)(void *, s32, s32);
    u8 pad1[0xCC - 0xC8];
    void (*unkCC)(void *, s32, s32);
    u8 pad2[0x148 - 0xD0];
    s32 (*fn148)(void *);
} Unk_80060A4C_Vtbl;
typedef struct Unk_80060A4C {
    Unk_80060A4C_Vtbl *vt;
    u8 pad0[0x84 - 0x4];
    s32 unk84;
    u8 pad1[0x94 - 0x88];
    void *unk94;
    u8 pad2[0xFC - 0x98];
    s32 uFC;
} Unk_80060A4C;
extern s32 D_80089CA0[];
typedef struct Unk_80062FAC_Vtbl {
    u8 pad[0x30];
    void (*unk30)(void *, s32);
    u8 pad2[0x44 - 0x34];
    void (*unk44)(void *, s32, void *);
    u8 pad3[0x148 - 0x48];
    s32 (*unk148)(void *);
} Unk_80062FAC_Vtbl;
typedef struct Unk_80062FAC {
    Unk_80062FAC_Vtbl *vt;
    u8 pad[0x40];
    s32 unk44;
    u8 pad2[0xF4 - 0x48];
    s32 unkF4;
} Unk_80062FAC;
typedef struct Unk_80065830_RetVt {
    u8 pad[0x60];
    void (*unk60)(void *, s32);
} Unk_80065830_RetVt;
typedef struct Unk_80065830_Vtbl {
    u8 pad_00[0xE4];
    void (*unkE4)(void *, s32);
    u8 pad_E8[0xF0 - 0xE8];
    void (*unkF0)(void *, s32);
    u8 pad_F4[0x10C - 0xF4];
    void (*unk10C)(void *, s32);
    u8 pad_110[0x114 - 0x110];
    void (*unk114)(void *);
    u8 pad_118[0x128 - 0x118];
    void (*unk128)(void *, s32);
    u8 pad_12C[0x130 - 0x12C];
    void (*unk130)(void *);
} Unk_80065830_Vtbl;
typedef struct Unk_80065830_Inner {
    u8 pad[0x20];
    s32 unk20;
} Unk_80065830_Inner;
typedef struct Unk_80065830 {
    Unk_80065830_Vtbl *unk0;
    u8 pad[0x68 - 0x4];
    Unk_80065830_Inner *unk68;
} Unk_80065830;
void func_8001E770(void *, s32);

INCLUDE_RODATA("asm/nonmatchings/game/8005C508", D_8001186C);

INCLUDE_RODATA("asm/nonmatchings/game/8005C508", D_8001187C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005C508);

void func_8005C5E8(void) {
    Unk_8005C5E8 *var_s0;
    u32 i;

    var_s0 = D_80088D28;
    for (i = 0; i < 1; i++) {
        if (var_s0->obj != NULL) {
            var_s0->obj = var_s0->obj->vt->unk4(var_s0->obj);
        }
        var_s0++;
    }
}

void func_8005C650(s32 arg0, s32 arg1, Unk_8005CD58 *arg2, s32 arg3, s32 arg4) {
    s32 sp10[4];
    Unk_8005C5E8 *var_s1;
    u32 i;

    var_s1 = D_80088D28;
    D_8008ABF8 = arg0;
    D_8008ABFC = arg1;
    D_8008AC00 = arg2;
    D_8008AC04 = arg3;
    D_8008AC08 = arg4;
    for (i = 0; i < 1; i++) {
        sp10[3] = (s32) var_s1->obj;
        var_s1->unk4 = func_8005CFDC(i + 0x62, sp10, D_8008AC04);
        var_s1++;
    }
    func_8005C6D8(arg0);
}

void func_8005C6D8(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((arg0 == 0xB) || (arg0 == 3)) {
        var_v1 = 1;
    }
    func_8005BF68(var_v1);
}

void func_8005C714(s32 arg0) {
    switch (arg0) {
        case 0xB:
        case 0x38:
        case 0x4E:
        case 0x5D:
            func_8005BF68(1);
            break;
    }
}

void func_8005C76C(void) {
    Unk_8005C76C_Entry *var_s0;
    u32 i;

    for (i = 0, var_s0 = D_80088D2C; i < 1; i++) {
        if (var_s0->obj != NULL) {
            var_s0->obj = var_s0->obj->vt->fn4(var_s0->obj);
        }
        var_s0++;
    }
}

s32 func_8005C7D4(s32 arg0, void *arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_8005C8AC((s16 *) arg1);
    if (temp_s0 != 0) {
        if (func_8005C9A4(arg2, (Unk_8005C9A4 *) temp_s0) != 0) {
            return func_8005C9DC(arg2, (Unk_8005C9A4 *) temp_s0, arg0);
        }
        if (D_8008ABF8 != 0) {
            if (rand() % 12 == 0 && !(arg2 & 1)) {
                func_8005CF34((Unk_8005CF34 *) D_80088D28);
            }
        }
    }
    return 0;
}

s32 func_8005C8AC(s16 *arg0) {
    s16 *var_a0;
    s32 var_a1;
    s32 temp_a2;
    s32 pad[2];

    temp_a2 = D_80089AC4[D_8008ABF8];
    var_a0 = D_80089A8C[D_8008ABF8];
    var_a1 = 0;
    if (temp_a2 > 0) {
        do {
            if (*arg0 == *var_a0) {
                return func_8005C930((s32) var_a0, var_a1);
            }
            var_a1++;
            var_a0 += 3;
        } while (var_a1 < temp_a2);
    }
    return 0;
}

s32 func_8005C930(s32 arg0, s32 arg1) {
    s32 mode = D_8008ABF8;

    if (mode == 4 && arg1 == 0x10) {
        if (D_8008AC00->vt->unk200(D_8008AC00) == mode) {
            arg0 += 30;
        }
    }
    return arg0;
}

s32 func_8005C9A4(s32 arg0, Unk_8005C9A4 *arg1) {
    s32 var_v0;
    s8 temp_v1;

    temp_v1 = arg1->unk2;
    var_v0 = 1;
    if (temp_v1 != 0) {
        arg0 = (arg0 % 2) + 1;
        var_v0 = temp_v1 != arg0;
    }
    return var_v0;
}

s32 func_8005C9DC(s32 arg0, Unk_8005C9A4 *arg1, s32 arg2) {
    s32 sp10[4];
    s32 ret;
    s8 *p;
    s8 *end;
    u8 *table;

    sp10[0] = arg2;
    ret = func_80044A0C((s32)sp10);
    if (ret != 0) {
        p = arg1->unk3;
        end = arg1->unk3 + 3;
        table = D_80089A44[D_8008ABF8];
        while (p < end && *p != -1) {
            func_8005CAB4(arg0, arg1, table + *p * 8, ret);
            p++;
        }
        return ret;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005CAB4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005CBC8);

s32 func_8005CD58(s32 arg0) {
    s32 temp_s0;

    temp_s0 = D_80088D16[arg0];
    return temp_s0 == D_8008AC00->vt->unk200(D_8008AC00);
}

s32 func_8005CDA8(s32 arg0, s32 arg1) {
    s32 i;
    s32 n;

    n = ((arg0 - 1) / 30) + 1;
    for (i = 0; i < 4; i++) {
        if (n == arg1) {
            return 1;
        }
        arg1 += 3;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005CDF8);

void func_8005CF34(Unk_8005CF34 *arg0) {
    s32 sp18[4];
    Unk_8005CF34_Obj *temp_a0;

    temp_a0 = arg0->unk4;
    if (temp_a0 != NULL) {
        temp_a0->vt->unk50(temp_a0);
        func_8001E600(D_8008AC00, sp18, &arg0->unk8, 0);
        arg0->unk4->vt->unk4C(arg0->unk4, D_8008AC00, D_8008AC08, D_8008ABFC, sp18);
        func_8001EACC(arg0->unk4, D_8008AC00, 1, 0, 0);
    }
}

s32 func_8005CFDC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x108);
    if (temp_s0 == 0) {
        return 0;
    }
    if (func_8005E150()->unk8(temp_s0, arg0, arg1, arg2) != 0) {
        return temp_s0;
    }
    func_80017CFC(temp_s0);
    return 0;
}

void *func_8005D068(Unk_8005D068 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_80066818()->unk8(arg0, arg2, arg3) != 0) {
        arg0->unk0 = func_8005E150();
        arg0->unk98 = arg1;
        arg0->unk9C = 0;
        arg0->unk100 = 0;
        arg0->unk104 = 0;
        ((Unk_8005D068_Vtbl *)arg0->unk0)->unk40(arg0);
        return arg0;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D108);

void func_8005D1EC(Unk_8005D1EC *arg0) {
    Unk_8005D1EC_Obj *temp;

    temp = arg0->unk100;
    if (temp != NULL) {
        temp->vt->unk4(temp);
    }
    temp = arg0->unk104;
    if (temp != NULL) {
        temp->vt->unk4(temp);
    }
    func_80066818()->unkC(arg0);
}

void func_8005D278(Unk_8005D278 *arg0) {
    if ((u8)D_80089EA6[arg0->unk98 * 16] - 1U < 9) {
        arg0->unk0->unk70(arg0, 1);
    }
    arg0->unk0->unk10C(arg0, 0x42);
    arg0->unk0->unk160(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D314);

void func_8005D418(Unk_8005D418 *arg0) {
    if (arg0->unkC != 0) {
        arg0->unk0->unk160(arg0);
        func_80066818()->unk50(arg0);
        arg0->unk4C = 0;
    }
}

void func_8005D480(Unk_8005D480 *arg0, void *arg1, s32 arg2) {
    if (arg0->vt->unk170(arg0) != 0) {
        arg0->vt->unk174(arg0);
    }
    if (arg0->vt->unk17C(arg0) != 0) {
        arg0->vt->unk180(arg0);
    }
    arg0->vt->unk178(arg0);
    ((Unk_8005D480_Fn *)func_80066818())->unk98(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D560);

void func_8005D658(Unk_8005D418 *arg0, void *arg1, s32 arg2) {
    func_80066818()->unkE0(arg0, arg1, arg2);
    if (arg2 == 4) {
        arg0->unk0->unk160(arg0);
    }
}

void func_8005D6D4(Unk_8005D6D4 *arg0) {
    func_8002CD08(arg0->u58, &arg0->u9C);
    arg0->uFC++;
}

s32 func_8005D714(void *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    Unk_8005D714_Arg1 sp18;
    u8 temp_v1;

    sp18 = *(Unk_8005D714_Arg1 *)arg1;
    temp_v1 = *(u8 *)(D_80089EA6 + (((Unk_8005D714_Arg0 *)arg0)->unk98 * 0x10));
    if ((u32)((temp_v1 + 9) & 0xFF) < 9U) {
        sp18.unk4 += (s32)(temp_v1 << 0x18) >> 0xE;
    }
    if (arg3 < 0) {
        arg3 = 0x800 / (s32)(~arg3 + 1);
    } else {
        arg3 = arg3 << 0xB;
    }
    return ((Unk_8005D714_Arg0 *)arg0)->unk94->vt->unk120(((Unk_8005D714_Arg0 *)arg0)->unk94, 0, arg2 << 0xB, &sp18, arg3);
}

s32 func_8005D7FC(Unk_8005D7FC_Arg0 *arg0, Unk_8005D7FC_Arg1 *arg1) {
    Unk_8005D7FC_Pos *var_a2;
    Unk_8005D7FC_Node *temp_a0;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;

    var_a2 = NULL;
    if (arg1->unkC != 0) {
        var_a2 = (Unk_8005D7FC_Pos *)(arg1->unk14 + 0x38);
    }
    temp_a0 = arg0->unk14;
    var_a1 = temp_a0->unk18 - var_a2->unk0;
    if (var_a1 < 0) {
        var_a1 = ~var_a1 + 1;
    }
    temp_v0 = temp_a0->unk20 - var_a2->unk8;
    if (temp_v0 >= 0) {
        var_v0 = var_a1 + temp_v0;
    } else {
        var_v0 = var_a1 - temp_v0;
    }
    return var_v0;
}

s32 func_8005D864(Unk_8005D864 *arg0) {
    s32 temp_v0;
    s32 temp_v1;

    if (arg0->unk94 != NULL) {
        temp_v0 = arg0->vt->unk144(arg0, arg0->unk94);
        temp_v1 = D_80089EAE[arg0->unk98 * 16] << 11;
        if (temp_v1 >= temp_v0) {
            return temp_v0 / (temp_v1 / arg0->unkB0);
        }
    }
    return -1;
}

Unk_80089EA4 *func_8005D944(Unk_8005D944 *arg0) {
    return &D_80089EA4[arg0->unk98];
}

s32 func_8005D95C(Unk_8005D95C *arg0) {
    return D_80089EA6[arg0->unk98 * 16] * 1000;
}

s32 func_8005D994(Unk_8005D994 *arg0) {
    s8 temp_v0;

    temp_v0 = D_80089EAB[arg0->unk98 * 16];
    if (temp_v0 < 0) {
        return ~temp_v0;
    }
    return temp_v0 - 1;
}

s32 func_8005D9D0(Unk_8005D9D0 *arg0) {
    return D_80089EAC[arg0->unk98 * 16] - 1;
}

void func_8005D9F4(Unk_8005D9F4 *arg0) {
    arg0->unk0->unk60(arg0, 1);
    arg0->unkF0 = 1;
    arg0->unk24 = 0;
}

void func_8005DA3C(Unk_8005DA3C *arg0) {
    arg0->unk0->unk60(arg0, 0);
    arg0->unk0->unk16C(arg0);
    arg0->unk0->unk164(arg0, 0);
    arg0->unkF0 = 0;
}

void func_8005DAAC(Unk_8005DAAC *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->unk0->unk30(arg0, 9);
    }
    arg0->unkF4 = arg1;
}

void func_8005DAFC(Unk_8005DAFC *arg0) {
    func_8002CC34(arg0->unk58, &arg0->unk9C, arg0->unk98 + 1, arg0, D_80089EB0[arg0->unk98 * 4]);
    arg0->unk0->unk12C(arg0);
    arg0->unk0->unk110(arg0);
    arg0->unkFC = 0;
    arg0->unkF8 = 1;
}

void func_8005DB8C(Unk_8005DB8C *arg0) {
    func_8002CC84(arg0->unk58, &arg0->unk9C);
    arg0->unk0->unk130(arg0);
    arg0->unk0->unk114(arg0);
    arg0->unkF8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DBF0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DD18);

s32 func_8005DE18(Unk_8005DE18 *arg0) {
    s32 var_a2;
    u8 *temp_a1;
    Unk_80089EA4 *temp_s1;

    temp_s1 = &D_80089EA4[arg0->unk98];
    if (arg0->unkF0 != 0) {
        if (arg0->unkF4 == 0) {
            temp_a1 = arg0->unk14 + 0x18;
            var_a2 = temp_s1->unk6;
            if (var_a2 < 0) {
                var_a2 = ~var_a2 + 1;
            }
            if (func_8005D714(arg0, temp_a1, var_a2, temp_s1->unk9) != 0) {
                arg0->unk0->unk164(arg0, 1);
            }
        }
        if (temp_s1->unk6 < 0) {
            func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
        }
    }
    return arg0->unkF4;
}

s32 func_8005DEE0(Unk_8005DEE0 *arg0) {
    Unk_80089EA4 *ent;
    s32 temp_a2;
    u8 *temp_a1;

    if (arg0->unkF0 != 0) {
        if (arg0->unkF8 == 0) {
            if (arg0->unk44 != 1) {
                ent = &D_80089EA4[arg0->unk98];
                temp_a2 = ent->unkB;
                if (temp_a2 != 0) {
                    temp_a1 = arg0->unk14 + 0x18;
                    if (temp_a2 < 0) {
                        temp_a2 = ~temp_a2 + 1;
                    }
                    if (func_8005D714(arg0, temp_a1, temp_a2, ent->unk9) != 0) {
                        arg0->unk0->unk168(arg0);
                    }
                }
            }
        }
    }
    return arg0->unkF8;
}

void func_8005DF9C(Unk_8005DF9C *arg0) {
    s8 temp_v0;

    if (D_80089EAB[arg0->unk98 * 16] < 0) {
        temp_v0 = D_80089EAC[arg0->unk98 * 16];
        if ((temp_v0 != 0) && (func_8005E02C(arg0, temp_v0 << 9) != 0)) {
            arg0->unk0->unk30(arg0, 0xA);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E02C);

s32 func_8005E0B0(Unk_8005E0B0 *arg0) {
    Unk_80089EA4 *ent;
    s8 temp_a2;

    if (arg0->unkF0 != 0) {
        if (arg0->unkF8 != 0) {
            ent = &D_80089EA4[arg0->unk98];
            temp_a2 = ent->unkB;
            if ((temp_a2 < 0) && (func_8005D714(arg0, arg0->unk14 + 0x18, ~temp_a2 + 1, ent->unk9) == 0)) {
                arg0->unk0->unk16C(arg0);
            }
        }
    }
    return arg0->unkF8;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E150);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E160);

void func_8005E3C4(Unk_8005E3C4 *arg0, Unk_8005E7A8 *arg1) {
    arg1->u10 = 0;
    if (arg1->u4 == 0) {
        arg1->u1C = 0x14;
        arg1->u30 = 0x14;
        arg1->u44 = 0x14;
        ((Unk_8005E3C4_Obj *)arg0->unk94)->vt->unk130(arg0->unk94, 1);
    }
    func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
    arg0->unk0->unkC4(arg0, -0x5A, 0);
    if (arg0->unkFC == 0x1E) {
        arg0->unk0->unk30(arg0, 0xA);
    }
}

void func_8005E480(void **arg0, Unk_8005E480 *arg1) {
    arg1->u10 = ((Unk_8005E480_0 *)*arg0)->fn148(arg0);
    if (arg1->u4 == 0) {
        arg1->u1C = 0x17;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E4D0);

void func_8005E694(Unk_8005E694 *arg0) {
    arg0->unk0->unk48(arg0, 1, D_80089DF0);
    arg0->unk0->unkBC(arg0, D_80089D78);
}

void func_8005E6F0(Unk_8005E6F0_Obj *arg0, Unk_8005E480 *arg1) {
    arg1->u10 = arg0->unk0->fn148(arg0);
    if (arg1->u4 % (arg0->unk80 / 2) == 0) {
        arg1->u1C = 0xA;
    }
    arg0->unk0->unkC4(arg0, -0x1E, 0);
}

void func_8005E7A8(void **arg0, Unk_8005E7A8 *arg1) {
    arg1->u10 = 0;
    if (arg1->u4 == 0) {
        arg1->u1C = 0xB;
        arg1->u30 = 0xB;
        arg1->u44 = 0xB;
    }
    ((Unk_8005E7A8_Obj *)*arg0)->unkC4(arg0, -0x1E, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E7F8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005EA94);

void func_8005EBB4(Unk_8005EBB4 *arg0, Unk_8005E480 *arg1) {
    arg1->u10 = arg0->unk0->fn148(arg0);
    if (arg1->u4 == 0) {
        arg1->u1C = 0xC;
        arg0->unk44 = arg0->unk44 + 1;
    } else if (arg1->u4 >= arg0->unk80 - 1) {
        arg1->u4 = -1;
    }
    if (arg0->unk44 == 0x24) {
        if (rand() % 3 == 0) {
            arg0->unk0->unk30(arg0, 0xB);
        }
    }
}

void func_8005EC98(void **arg0, Unk_8005E480 *arg1) {
    arg1->u10 = ((Unk_8005E480_0 *)*arg0)->fn148(arg0);
    if (((Unk_80061C04_0 *)arg0)->unk84 == 0xA) {
        arg1->u1C = 0xD;
    }
    ((Unk_8005E7A8_Obj *)*arg0)->unkC4(arg0, -0xA, 0);
}

void func_8005ED10(Unk_8005ED10_0 *arg0, Unk_8005ED10 *arg1) {
    if (arg0->uFC == 0) {
        arg1->u10 = 0;
        arg1->u1C = 0xF;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005ED30);

void func_8005EF20(Unk_8005EF20 *arg0) {
    arg0->vt->fn48(arg0, 1, &D_80089DD8);
}

void func_8005EF54(void **arg0, Unk_8005E480 *arg1) {
    arg1->u10 = ((Unk_8005E480_0 *)*arg0)->fn148(arg0);
    if (arg1->u4 == (arg1->u4 / 10) * 10) {
        arg1->u1C = 0x11;
    }
    ((Unk_8005E7A8_Obj *)*arg0)->unkC4(arg0, -0x100, 0);
}

void func_8005EFF4(Unk_8005EFF4 *arg0, Unk_8005EFF4_Arg1 *arg1) {
    if (arg0->uFC == 0) {
        if (rand() % 7 == 0) {
            arg0->vt->fn48(arg0, 1, &D_80089E50);
        }
    }
    if (!(arg1->u4 & 3)) {
        arg1->u10 = arg0->vt->fn148(arg0);
        arg1->u1C = 0x1C;
    }
    arg0->vt->fnC4(arg0, -0x64, 0);
}

void func_8005F0D8(Unk_8005F0D8 *arg0, Unk_80063CAC *arg1) {
    s32 temp_hi;

    arg1->unk10 = arg0->unk0->fn148(arg0);
    temp_hi = arg1->unk4 % (arg0->unk80 / 2);
    if (temp_hi == 0) {
        arg1->unk1C = 0xA;
    } else if (temp_hi == 3) {
        arg1->unk30 = 0xD;
    }
    arg0->unk0->unkC4(arg0, -0x1E, 1);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F1A8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F1D4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F368);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F454);

void func_8005F544(Unk_8005F544_Obj *arg0, Unk_8005E480 *arg1) {
    if (arg1->u4 % arg0->unk80 == 0) {
        arg1->u10 = arg0->vt->fn148(arg0);
        arg1->u1C = 0x1A;
    }
    arg0->vt->unkD0(arg0, (arg0->uFC == 0x6E) ? -0x2D00 : -0x180, 0);
}

void func_8005F608(Unk_8005F608 *arg0, Unk_8005E7A8 *arg1) {
    if (arg1->u4 % 70 == 0) {
        arg1->u10 = 0;
        arg1->u1C = 0x1B;
    }
    arg0->vtbl->unkC4(arg0, -0x80, 0);
    if (arg0->uFC < 0x64) {
        arg0->vtbl->unkCC(arg0, 0x20, 0);
    } else if (arg0->uFC > 300) {
        arg0->vtbl->unkCC(arg0, -0x20, 0);
    }
}

void func_8005F6D4(Unk_8005F6D4 *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089E38);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F708);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F800);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F970);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FA64);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FA94);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FB6C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FC58);

void func_8005FDFC(Unk_8005FDFC *arg0) {
    if (arg0->unk44 == 0) {
        arg0->unk0->unk48(arg0, 1, (rand() & 1) ? D_80089DF0 : &D_80089E38);
        arg0->unk44 = 0xB;
    }
    func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
    if (arg0->unk0->unk144(arg0, arg0->unk94) < 0x7000) {
        arg0->unk0->unkC4(arg0, 0x100, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FEC8);

void func_8005FEF8(void **arg0, Unk_8005E480 *arg1) {
    if (arg1->u4 % 120 == 0) {
        arg1->u10 = ((Unk_8005E480_0 *)*arg0)->fn148(arg0);
        arg1->u1C = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FF7C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060148);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800602AC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800603C4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800604DC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800605D0);

void func_80060710(Unk_80060710 *arg0) {
    s32 temp;

    if (arg0->uFC == 0) {
        temp = rand() % 10;
        if (temp >= 8) {
            arg0->unk0->unk48(arg0, 1, D_80089E8C);
        } else if (temp >= 5) {
            arg0->unk44 = 0xA;
        }
    }
    if (arg0->unk44 == 0xA && arg0->uFC >= 0xC9) {
        arg0->unk0->unkBC(arg0, D_80089DC0);
    }
}

void func_800607F8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060800);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8006090C);

void func_80060A4C(Unk_80060A4C *arg0, Unk_8005E480 *arg1) {
    s32 var_a1;
    Unk_80060A4C_Vtbl *vt;

    if (arg0->unk84 == 0x26) {
        func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
        arg1->u10 = arg0->vt->fn148(arg0);
        arg1->u1C = 6;
    }
    var_a1 = 0x1E;
    vt = arg0->vt;
    if ((arg0->uFC % 10) < 5) {
        var_a1 = -0x1E;
    }
    vt->unkCC(arg0, var_a1, 0);
    arg0->vt->unkC4(arg0, -0x1E, 1);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060B34);

void func_80060CF0(Unk_80060CF0 *arg0, Unk_80063CAC *arg1) {
    s32 temp_a0;

    if (arg0->unkFC < (arg0->unk80 * 5)) {
        temp_a0 = arg0->unk84;
        if ((temp_a0 == 0xF) || (temp_a0 == 0x46)) {
            arg1->unk10 = 0;
            arg1->unk1C = 7;
            arg1->unk30 = 7;
            arg1->unk44 = 7;
        }
    } else {
        arg0->unk0->unk160(arg0);
        arg0->unk44 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060D80);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060F38);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061070);

void func_80061158(Unk_80061158 *arg0) {
    if (arg0->uFC == 0) {
        arg0->vtbl->unkCC(arg0, -0xC8, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061198);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061400);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061778);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061A90);

void func_80061C04(Unk_80061C04_0 *arg0, Unk_80061C04 *arg1) {
    if (arg0->unk84 == 0x1E) {
        arg1->u1C = 0x12;
        arg1->u10 = 0;
        arg1->u20 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061C2C);

void func_80061E60(Unk_80061E60 *arg0, Unk_8005E480 *arg1) {
    s32 phase;

    phase = arg1->u4 % 300;
    arg1->u10 = arg0->vt->unk148(arg0);
    if (phase < 0x14) {
        arg1->u1C = 5;
        arg1->u20 = -2;
    } else if (phase == 0x16) {
        arg1->u1C = -2;
    }
    arg0->vt->unkC4(arg0, -0xA, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061F30);

void func_8006204C(void **arg0, Unk_8005E480 *arg1) {
    arg1->u10 = ((Unk_8005E480_0 *)*arg0)->fn148(arg0);
    if (arg1->u4 == ((arg1->u4 / 30) * 30)) {
        arg1->u1C = 0xD;
    }
}

void func_800620C4(Unk_800620C4 *arg0) {
    if (arg0->unkFC == 0) {
        if (rand() % 3 == 0) {
            arg0->unk44 = 0xB;
        }
    }
    if (arg0->unk44 == 0xB) {
        if (arg0->unkFC == 0x1F6) {
            arg0->unk0->unkCC(arg0, 0x800, 0);
            func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
        }
        if (arg0->unkFC >= 0x1F5) {
            arg0->unk0->unkC4(arg0, -0x200, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800621A8);

void func_800623E8(Unk_800623E8_Obj *arg0, Unk_800623E8 *arg1) {
    arg1->unk10 = arg0->unk0->fn148(arg0);
    if (arg0->unk84 == arg0->unk80 - 1) {
        arg1->unk1C = 0x19;
        arg1->unk20 = -2;
    }
    if ((arg1->unk4 & 3) == 0) {
        arg1->unk30 = 0x15;
        arg1->unk34 = -1;
    }
    if (arg1->unk4 % 200 == 0) {
        arg1->unk44 = 0xD;
        arg1->unk48 = 1;
    }
}

void func_800624BC(Unk_800624BC *arg0) {
    s32 var_a1;

    if (arg0->uFC == 0 && (rand() & 1)) {
        arg0->unk44 = 0xB;
    }
    if (arg0->uFC == 0x12C) {
        arg0->unk0->unk44(arg0, 0, D_80089C7C);
    }
    if (arg0->uFC < 0x258) {
        Unk_800624BC_Vtbl *vt = arg0->unk0;

        var_a1 = 0x100;
        if (arg0->unk44 == 0) {
            var_a1 = -0x100;
        }
        vt->unkC4(arg0, var_a1, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062570);

void func_80062660(Unk_80062660 *arg0, Unk_80063CAC *arg1) {
    s32 temp_v1;

    temp_v1 = arg1->unk4;
    arg1->unk10 = 0;
    if (temp_v1 == 0) {
        arg0->unk94->vt->unk44(arg0->unk94, 1, &D_80089C88);
        arg0->unk94->vt->unk130(arg0->unk94, 1);
        arg1->unk1C = 0x19;
        arg1->unk30 = 0x19;
        arg1->unk44 = 0x19;
    } else if (temp_v1 == 0x14) {
        arg1->unk30 = 0xD;
    }
    if (arg0->unkFC == (arg0->unk80 - 1)) {
        arg0->unk0->unk160(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062730);

void func_800628D4(Unk_800628D4 *arg0, Unk_80063CAC *arg1) {
    if (arg1->unk4 == 0) {
        arg1->unk10 = 0;
        arg1->unk1C = 0x19;
        arg1->unk30 = 0x19;
        arg1->unk44 = 0x19;
        func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
    }
    if (arg0->unkFC == arg0->unk80) {
        arg0->unk0->unk130(arg0);
        arg0->unk0->unk30(arg0, 0xA);
    }
}

void func_80062970(Unk_80062970 *arg0) {
    if (arg0->unkF4 != 0) {
        arg0->unk0->unk12C(arg0);
        if (arg0->unk84 == arg0->unk80 - 1) {
            arg0->unk0->unk130(arg0);
            arg0->unk0->unk48(arg0, 0, D_80089DFC);
        }
    } else {
        arg0->unk0->unk130(arg0);
        arg0->unk0->unk44(arg0, 0, D_80089C64);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062A40);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062C58);

void func_80062FAC(Unk_80062FAC *arg0, Unk_8005E480 *arg1) {
    arg1->u10 = arg0->vt->unk148(arg0);
    if (arg1->u4 % 10 == 0) {
        arg1->u1C = 0x19;
        arg1->u20 = 2;
    }
    arg0->vt->unk44(arg0, 0, D_80089CA0);
    if ((arg0->unk44 == 0) && (arg0->unkF4 != 0)) {
        arg0->vt->unk30(arg0, 0xB);
        arg0->unk44 = 0xB;
    }
}

void func_80063094(Unk_80063094 *arg0, Unk_80063CAC *arg1) {
    if (arg0->unkFC < arg0->unk80) {
        switch (arg0->unk84) {
        case 0:
            break;
        case 0x14:
            arg1->unk10 = 0;
            arg1->unk1C = 0x10;
            break;
        }
    } else {
        arg0->unk0->unk130(arg0);
        arg0->unk0->unkBC(arg0, D_80089D54);
    }
    func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063144);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800634A8);

void func_800636E4(Unk_80060CF0 *arg0, Unk_80061C04 *arg1) {
    if (arg0->unk84 == ((arg0->unk84 / 15) * 15)) {
        arg1->u1C = 12;
        arg1->u10 = 0;
        arg1->u20 = 2;
    }
    if (arg0->unkFC == arg0->unk80) {
        arg1->u1C = -2;
        ((Unk_800636E4_Vtbl *)arg0->unk0)->unk16C(arg0);
        arg0->unk44 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063784);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063874);

void func_80063BC0(Unk_80063BC0 *arg0, void *arg1) {
    if (arg0->unkFC < 0xA) {
        arg0->unk0->unk130(arg0);
    } else if (arg0->unkFC == 0xA) {
        arg0->unk0->unk12C(arg0);
    }
    if (arg0->unk84 == 0xA) {
        func_80063CAC((Unk_80063CAC *)arg1);
    }
    if (arg0->unkFC == arg0->unk80 + 0xA) {
        arg0->unk0->unk16C(arg0);
        arg0->unk44 = 1;
    }
}

void func_80063C84(Unk_80063C84 *arg0) {
    arg0->u10 = 0;
    arg0->u1C = 7;
    arg0->u20 = -2;
    arg0->u30 = 7;
    arg0->u34 = -2;
    arg0->u44 = 7;
    arg0->u48 = -2;
}

void func_80063CAC(Unk_80063CAC *arg0) {
    arg0->unk1C = 0x12;
    arg0->unk10 = 0;
    arg0->unk30 = 3;
    arg0->unk44 = 3;
}

void func_80063CC8(Unk_80063CC8_Obj *arg0, Unk_80063CC8 *arg1) {
    arg1->unk10 = arg0->unk0->fn148(arg0);
    if (arg1->unk4 == 0) {
        arg1->unk1C = 0x12;
    }
    if (arg1->unk4 >= arg0->unk80 - 1) {
        arg1->unk4 = -1;
    }
}

void func_80063D40(Unk_80063CC8_Obj *arg0, Unk_80063CC8 *arg1) {
    arg1->unk10 = arg0->unk0->fn148(arg0);
    if (arg1->unk4 == arg0->unk80 / 2) {
        arg1->unk1C = 0x12;
    }
    if (arg1->unk4 >= arg0->unk80 - 1) {
        arg1->unk4 = -1;
    }
}

void func_80063DC8(Unk_80063DC8 *arg0, Unk_80063CAC *arg1) {
    s32 temp_v1;

    temp_v1 = arg0->unkFC;
    if (temp_v1 == 0x14) {
        arg1->unk1C = 0x12;
        arg1->unk10 = 0;
        arg1->unk30 = 3;
        return;
    }
    if (temp_v1 == arg0->unk80) {
        arg0->unk0->unk16C(arg0);
        arg0->unk44 = 1;
        if (rand() & 1) {
            arg0->unk0->unk30(arg0, 0xB);
        }
    }
}

void func_80063E68(Unk_80063CC8_Obj *arg0, Unk_80063E68 *arg1) {
    s32 var_v1;

    arg1->unk10 = arg0->unk0->fn148(arg0);
    if (arg1->unk4 == 0) {
        if (rand() & 1) {
            var_v1 = 2;
        } else {
            var_v1 = 1;
        }
        arg1->unk1C = var_v1;
        arg1->unk20 = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063ED4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064078);

void func_800641C0(Unk_800641C0 *arg0, Unk_8005E7A8 *arg1) {
    arg1->u10 = arg0->unk0->unk148(arg0);
    if (arg1->u4 % 10 == 0) {
        arg1->u1C = 3;
    }
    if (arg0->unkFC == arg0->unk80) {
        arg0->unk0->unk128(arg0, 1);
    }
    if (arg0->unk7C == 1) {
        arg0->unk0->unkC4(arg0, -0x80, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064294);

void func_80064450(Unk_80064450 *arg0) {
    if (arg0->unkFC == 0) {
        arg0->unk0->unk128(arg0, 3);
    } else if (arg0->unkFC == arg0->unk80) {
        arg0->unk0->unk128(arg0, 1);
    }
    if (arg0->unk7C == 1) {
        arg0->unk0->unkC4(arg0, -0x80, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800644E8);

void func_80064618(Unk_80064618 *arg0) {
    if (arg0->unkF4 != 0 && func_8005D108(arg0, 0, 0, 0xA, 0)) {
        arg0->unk100->vt->unkD4(arg0->unk100, arg0->unk50, 7, 0);
        arg0->unk0->unk160(arg0);
        arg0->unk94->vt->unk21C(arg0->unk94);
    }
    arg0->unk0->unkC4(arg0, -0x1E, 1);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800646D8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064928);

void func_80064AA4(Unk_80064AA4 *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089DCC);
    if (arg0->unkFC >= 201 && arg0->unkFC < 300) {
        arg0->vtbl->unkCC(arg0, -0x20, 0);
    }
}

void func_80064B14(Unk_8005D9F4 *arg0) {
    arg0->unk0->unk60(arg0, (rand() % 20) == 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064B80);

void func_80064CA4(Unk_80064CA4 *arg0) {
    func_80062570(arg0);
    arg0->unk0->unk48(arg0, 1, &D_80089E38);
}

void func_80064CEC(Unk_80064CEC *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089DD8);
    arg0->vtbl->unkC4(arg0, -10, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064D48);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064E34);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064FBC);

void func_800650D4(void) {
    func_80060D80();
}

void func_800650F4(Unk_func_800650F4_Obj **arg0) {
    s16 *tbl;

    if (rand() % 3 == 0) {
        return;
    }
    if (rand() % 3 != 0) {
        tbl = D_80089C64;
    } else {
        tbl = D_80089C70;
    }
    (*arg0)->unk44(arg0, 0, tbl);
}

void func_8006519C(Unk_8006519C *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089E38);
}

void func_800651D0(Unk_800651D0 *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089E38);
}

void func_80065204(Unk_80065204 *arg0) {
    arg0->vtbl->unk48(arg0, 1, &D_80089DCC);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065238);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8006536C);

void func_800654A0(Unk_800654A0 *arg0) {
    func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
    arg0->vt->unk48(arg0, 1, &D_80089E80);
    arg0->vt->unkC4(arg0, -0x1E, 1);
}

void func_80065514(Unk_80065514 *arg0) {
    if (arg0->unkFC == 0) {
        arg0->unk44 = (rand() % 2) + 0xA;
    }
    arg0->unk0->unk130(arg0);
    if (arg0->unkFC >= 0xC9) {
        func_8001EACC(arg0, arg0->unk94, 1, 0, 0);
        if (arg0->unk44 == 0xA) {
            arg0->unk0->unkD0(arg0, -0x200, 0);
        }
    }
}

void *func_800655D4(s32 arg0, s32 arg1) {
    void *temp_s0;

    temp_s0 = ((void *)func_80017B34(0x98));
    if (temp_s0 != NULL) {
        if (((Unk_80066818_Vtbl_800655D4 *)func_80066818())->unk8(temp_s0, arg0, arg1) == 0) {
            func_80017CFC((s32)temp_s0);
            return NULL;
        }
        return temp_s0;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065650);

void func_8006573C(Unk_8006573C_Obj **arg0) {
    (*arg0)->unkF8(arg0);
    func_80057C84()->unkC(arg0);
}

void func_80065790(Unk_80065790 *arg0, u16 **arg1, s32 arg2) {
    ((Unk_80065790_CallVt *)func_80057C84())->unk38(arg0, arg1, arg2);
    if ((**arg1 == 0x5F03) && (arg2 == 1) && (arg0->unk60 == 0)) {
        arg0->unk0->unk4(arg0);
    }
}

void func_80065830(Unk_80065830 *arg0) {
    Unk_80065830_Inner *temp_v0;

    ((Unk_80065830_RetVt *)func_80057C84())->unk60(arg0, 0);
    arg0->unk0->unkF0(arg0, 1);
    arg0->unk0->unkE4(arg0, 0x12C);
    arg0->unk0->unk114(arg0);
    arg0->unk0->unk10C(arg0, 0x41);
    arg0->unk0->unk130(arg0);
    arg0->unk0->unk128(arg0, 0);
    temp_v0 = arg0->unk68;
    if (temp_v0 != NULL) {
        func_8001E770(arg0, temp_v0->unk20);
    }
}

void func_80065918(Unk_80065918 *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->unkC == 0) {
        ((Unk_80065918_CallVt *)func_80057C84())->unk4C(arg0, arg3, arg4);
        if ((arg2 != 0) && (arg0->unk50 == 0)) {
            arg0->unk0->unk10(arg0, arg2);
        }
        arg0->unk0->unk13C(arg0, arg1);
    }
}

void func_800659D0(Unk_800659D0 *arg0) {
    s32 temp_a1;

    if (arg0->unkC != 0) {
        arg0->unk0->unk140(arg0);
        temp_a1 = arg0->unk50;
        if (temp_a1 != 0) {
            arg0->unk0->unk14(arg0, temp_a1);
        }
        ((Unk_80066818_Vtbl_800659D0 *)func_80057C84())->unk50(arg0);
    }
}

void func_80065A5C(Unk_80065A5C *arg0, s32 arg1) {
    Unk_80065A5C_Obj **p;
    s32 i;

    p = arg0->u70;
    for (i = 0; i < arg0->u6C; i++, p++) {
        (*p)->vt->unk60(*p, arg1);
    }
}

void func_80065AE0(Unk_80065AE0 *arg0, s32 arg1) {
    Unk_80065AE0_Obj **p;
    s32 i;

    p = arg0->unk70;
    for (i = 0; i < arg0->unk6C; i++, p++) {
        (*p)->unk0->unk70(*p, arg1);
    }
    ((Unk_80065AE0_Vt *)func_80057C84())->unk70(arg0, arg1);
}

void func_80065B80(Unk_80065B80 *arg0, s32 arg1, s32 arg2) {
    if (arg2 == 2) {
        arg0->vt->unk108(arg0);
    }
    if (arg2 == 4) {
        arg0->vt->unk4(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065BF4);

s32 func_80065BFC(Unk_80065BFC *arg0) {
    if (arg0->u5C == 0) {
        return func_80065C5C();
    }
    return 0;
}

void func_80065C2C(Unk_80065C2C *arg0) {
    if (arg0->u5C != 0) {
        func_80065CEC();
    }
}

s32 func_80065C5C(Unk_80065CEC *arg0, Unk_80065C5C *arg1) {
    if (arg1->unkC != NULL) {
        arg0->unk5C = arg1->unkC;
        arg0->unk60 = 0;
    } else {
        arg0->unk5C = func_8004468C(arg1);
        arg0->unk60 = 1;
    }
    if (arg0->unk5C != NULL) {
        return arg0->unk0->unk100(arg0);
    }
    func_80065CEC(arg0);
    return 1;
}

void func_80065CEC(Unk_80065CEC *arg0) {
    Unk_80065CEC_Obj *var_v0;

    arg0->unk0->unk104(arg0);
    if (arg0->unk60 != 0) {
        var_v0 = arg0->unk5C->vt->unk4(arg0->unk5C);
    } else {
        var_v0 = 0;
    }
    arg0->unk5C = var_v0;
}

s32 func_80065D64(Unk_80065D64 *arg0, u8 arg1) {
    u8 *p;
    s32 i;

    if (arg0->unk74 != NULL) {
        p = arg0->unk74;
        for (i = 0; i < arg0->unk6C; i++, p++) {
            if (*p == arg1) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_80065DBC(Unk_80059394 *arg0) {
    if (arg0->u70 == 0) {
        return func_80065E1C(arg0);
    }
    return 0;
}

void func_80065DEC(Unk_80059394 *arg0) {
    if (arg0->u70 != 0) {
        func_80065F2C(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065E1C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065F2C);

void func_80065FD8(Unk_80065FD8 *arg0) {
    arg0->unk24 = arg0->unk24 + 1;
    if (arg0->unk8C != 0) {
        arg0->unk78(arg0);
    }
    if ((arg0->unk90 != 0) && (arg0->unk80 >= 2)) {
        arg0->unk88 = arg0->unk0->unk134(arg0, arg0->unk88, 0);
        if (++arg0->unk84 >= arg0->unk80) {
            arg0->unk84 = 0;
            arg0->unk88 = arg0->unk5C->unk30->unk10->unk8[arg0->unk7C]->unk10 + 8;
        }
    }
    *arg0->unk14 = 0;
}

void func_800660BC(Unk_800660BC *arg0, s32 arg1) {
    switch (arg1 & 0xFF) {
    case 0x41:
        arg0->unk78 = arg0->unk0->unk118;
        return;
    case 0x42:
        arg0->unk78 = arg0->unk0->unk11C;
        return;
    case 0x43:
        arg0->unk78 = arg0->unk0->unk120;
        return;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8006613C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80066148);

void func_80066150(Unk_80066150 *arg0) {
    Unk_80066150_Inner *temp_a0;

    arg0->unk0->unkC4(arg0, -0x1E, 0);
    if (arg0->unk64 == 1) {
        temp_a0 = arg0->unk68;
        if (temp_a0 != NULL) {
            temp_a0->vt->unk88(temp_a0, 6);
        }
    }
}

void func_800661C4(void) {
}

void func_800661CC(void) {
}

void func_800661D4(Unk_800661D4 *arg0, s32 arg1) {
    Unk_800661D4_Obj *temp_a0;

    temp_a0 = arg0->unk58;
    if (temp_a0 != NULL) {
        temp_a0->unk0->unk80(temp_a0, arg1, 0x6E, 0x6E);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80066214);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800662A8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800662B4);

void *func_800662BC(Unk_800662BC *arg0, u8 *arg1, void *arg2) {
    u32 temp_s2;
    u32 var_s0;
    u32 pad[2];

    temp_s2 = *(u16 *)(arg1 + 2);
    arg1 = arg1 + 8;
    var_s0 = 0;
    if (temp_s2 != 0) {
        do {
            var_s0++;
            arg1 = arg0->vt->unk138(arg0, arg1, arg2);
        } while (var_s0 < temp_s2);
    }
    return arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80066340);

void func_80066748(Unk_80066748 *arg0, Unk_80066748 *arg1) {
    if (arg1 != NULL) {
        arg1->unk0->unk10(arg1, arg0);
        arg0->unk0->unk10(arg0, arg1);
        arg0->unk94 = arg1;
    }
}

void func_800667B0(Unk_800667B0 *arg0) {
    Unk_800667B0 *temp_a0;

    temp_a0 = arg0->unk94;
    if (temp_a0 != NULL) {
        temp_a0->vt->fn14(temp_a0, arg0);
        arg0->vt->fn14(arg0, arg0->unk94);
        arg0->unk94 = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80066818);

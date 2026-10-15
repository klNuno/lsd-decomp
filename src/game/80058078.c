#include "common.h"

extern void func_800183DC(void *, s32);
typedef struct { u8 p0[0x24]; u32 u24; u8 p1[0x70 - 0x28]; s32 u70; s32 u74; u8 p2[0x120 - 0x78]; u32 u120; s32 u124; } Unk_80059394;
u8 *D_8008ACB4;
s32 *D_8008ACB8;
extern s32 D_8008ABF0[];
s32 D_8008ACC4;
s32 D_8008ACBC;
typedef struct { u8 pad[5]; s8 u5; } S6;
extern S6 *D_80088BA4[];
s32 D_8008ACC8;
typedef struct Unk_8005A2D0 {
    u8 pad[0x678];
    s32 unk678;
} Unk_8005A2D0;
typedef struct Unk_8005B5A4 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Unk_8005B5A4;
typedef struct Unk_80059360 {
    u8 pad[0x24];
    u32 unk24;
} Unk_80059360;
typedef struct Unk_8005A168 {
    u8 pad[0xAC];
    s32 unkAC;
    s32 unkB0;
} Unk_8005A168;
extern s16 D_80087F14[];
typedef struct Unk_8005A184 {
    u8 pad[0xAC];
    s32 unkAC;
    s32 unkB0;
} Unk_8005A184;
typedef struct Unk_8005A2E4 {
    u8 pad[0x17C];
    s32 unk17C;
    s32 unk180;
} Unk_8005A2E4;
typedef struct { u8 pad[0x924]; s32 u924; } Unk_8005BA20;
void func_800573CC(void *arg0, s32 arg1, s32 *arg2);
extern void func_80056D18(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_800531CC(void *, void *);
typedef struct { s32 u0; s32 u4; u8 pad[0x14]; s32 u1C; s32 u20; u8 pad2[0xC]; s32 u30; s32 u34; } S;
typedef struct Unk_8005A134_Vtbl {
    u8 pad_00[0xBC];
    void (*unkBC)(void *, s32 *);
} Unk_8005A134_Vtbl;
typedef struct Unk_8005A134 {
    Unk_8005A134_Vtbl *unk0;
    u8 pad[0x58 - 0x04];
    void *u58;
    Unk_80059360 *unk5C;
    u8 pad2[0xC4 - 0x60];
    s32 uC4;
    s32 uC8;
    u8 uCC[1];
} Unk_8005A134;
void func_8002CC84(void *, void *);
typedef struct Unk_8005A1B0 {
    u8 pad[0x124];
    s32 unk124;
    s32 unk128;
    s32 unk12C;
    s32 unk130;
} Unk_8005A1B0;
typedef struct Unk_80059328 {
    u8 pad_00[0x134];
    s32 unk134;
} Unk_80059328;
typedef struct Unk_8005A304 {
    u8 pad_00[0x17C];
    s32 unk17C;
    s32 unk180;
} Unk_8005A304;
typedef struct Unk_8005B4E0_Vtbl {
    u8 pad_00[0x1FC];
    void (*unk1FC)(void *, s16 *);
} Unk_8005B4E0_Vtbl;
typedef struct Unk_8005B4E0 {
    Unk_8005B4E0_Vtbl *unk0;
} Unk_8005B4E0;
s8 func_8005B518(s16 *arg0);
typedef struct Unk_8005B5B8 {
    s8 unk0;
    s8 unk1;
} Unk_8005B5B8;
extern u8 D_80088748[];
extern s32 D_80088710[];
extern s32 D_80088664[];
s32 func_8005C150(void *arg0, void *arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 arg6);
extern u8 D_800889F0[];
extern void *D_80088980[];
extern void *D_80088820[];
typedef struct Unk_8005B3A4_Vtbl {
    u8 pad_00[0x208];
    void (*unk208)(void *, void *, s16 *);
} Unk_8005B3A4_Vtbl;
typedef struct Unk_8005B3A4 {
    Unk_8005B3A4_Vtbl *unk0;
    u8 pad_04[0x144 - 0x4];
    u8 unk144[0x164 - 0x144];
    s32 unk164;
} Unk_8005B3A4;
s16 *func_800495B8(s32 arg0, s8 *arg1);
extern u8 D_80088B5C;
extern s32 D_80088B24;
extern s32 D_80088A80;
s32 D_8008ABE4;
extern u8 D_80088CBC[];
extern s32 D_80088C4C[];
typedef struct Unk_800593D8 {
    u8 pad_00[0x80];
    void (*unk80)(void);
    u8 pad_84[0x98 - 0x84];
    void (*unk98)(struct Unk_800593D8 *);
} Unk_800593D8;
typedef struct Unk_800597C0_Vtbl {
    u8 pad_00[0x144];
    void (*unk144)(void *);
    void (*unk148)(void *);
} Unk_800597C0_Vtbl;
typedef struct Unk_800597C0 {
    Unk_800597C0_Vtbl *unk0;
} Unk_800597C0;
s32 func_8005BB30(void *, s32, s32);
s32 func_8005A928();
typedef struct Unk_8005A580 {
    u8 pad_00[0x24];
    s32 unk24;
    u8 pad_28[0x44 - 0x28];
    s32 unk44;
    u8 pad_48[0x164 - 0x48];
    s32 unk164;
    u8 pad_168[0x16C - 0x168];
    u8 unk16C[1];
} Unk_8005A580;
typedef struct Unk_80059610_Vtbl {
    u8 pad[0x138];
    void (*unk138)(void *, s32);
    void (*unk13C)();
} Unk_80059610_Vtbl;
typedef struct Unk_80059610 {
    Unk_80059610_Vtbl *unk0;
} Unk_80059610;
typedef struct Unk_80059E3C_Vtbl {
    u8 pad_00[0x84];
    void (*unk84)(void *, s32);
} Unk_80059E3C_Vtbl;
typedef struct Unk_80059E3C_Obj {
    Unk_80059E3C_Vtbl *vt;
} Unk_80059E3C_Obj;
typedef struct Unk_80059E3C {
    u8 pad_00[0x58];
    Unk_80059E3C_Obj *u58;
    u8 pad_5C[0xBC - 0x5C];
    s32 uBC;
} Unk_80059E3C;
typedef struct Unk_800590E8 {
    u8 pad[0x68];
    s32 unk68;
    u8 pad2[0x180 - 0x6C];
    s32 unk180;
} Unk_800590E8;
typedef struct Unk_8005A050 Unk_8005A050;
typedef struct Unk_8005A050_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(Unk_8005A050 *, s32, void *);
} Unk_8005A050_Vtbl;
struct Unk_8005A050 {
    Unk_8005A050_Vtbl *unk0;
    u8 pad_04[0xA4 - 0x04];
    s32 unkA4;
};
extern u8 D_80087E80[];
typedef struct Unk_8005AFDC_VtblA {
    u8 pad_00[0x1F4];
    void (*unk1F4)(void *, s32);
} Unk_8005AFDC_VtblA;
typedef struct Unk_8005AFDC_A {
    Unk_8005AFDC_VtblA *vt;
} Unk_8005AFDC_A;
typedef struct Unk_8005AFDC_VtblB {
    u8 pad_00[0x10C];
    s32 (*unk10C)(void *, s32, s32);
} Unk_8005AFDC_VtblB;
typedef struct Unk_8005AFDC_B {
    Unk_8005AFDC_VtblB *vt;
} Unk_8005AFDC_B;
typedef struct Unk_800581C4_Obj {
    u8 pad_00[0x70];
    void (*unk70)(void *, s32);
    u8 pad_74[0x94 - 0x74];
    void (*unk94)(void *);
} Unk_800581C4_Obj;
typedef struct Unk_800581C4 {
    Unk_800581C4_Obj *unk0;
    u8 pad_04[0x238 - 0x04];
    s32 unk238;
} Unk_800581C4;
typedef struct Unk_80059AEC_Vtbl {
    u8 pad_00[0x164];
    s32 (*unk164)(void *, s32);
    u8 pad_168[0x170 - 0x168];
    void (*unk170)(void *, s32);
} Unk_80059AEC_Vtbl;
typedef struct Unk_80059AEC {
    Unk_80059AEC_Vtbl *unk0;
    u8 pad_04[0x70 - 0x04];
    s32 unk70;
    u8 pad_74[0xA0 - 0x74];
    s32 unkA0;
} Unk_80059AEC;
void func_8005BCB4(void *, void *, s32);
typedef struct Unk_80058078_Vtbl {
    u8 pad_00[0x6C];
    void (*unk6C)(void *, s32);
    u8 pad_70[0xD4 - 0x70];
    void (*unkD4)(void *, void *, s32);
    u8 pad_D8[0x158 - 0xD8];
    void (*unk158)(void *);
    void (*unk15C)(void *);
    void (*unk160)(void *);
    u8 pad_164[0x174 - 0x164];
    void (*unk174)(void *);
    u8 pad_178[0x204 - 0x178];
    void (*unk204)(void *, void *);
    void (*unk208)(void *, void *, s32);
} Unk_80058078_Vtbl;
typedef struct Unk_80058078 {
    Unk_80058078_Vtbl *vt;
    u8 pad_04[0x2C - 0x04];
    s32 unk2C;
    u8 pad_30[0x6C - 0x30];
    s32 unk6C;
    u8 pad_70[0x84 - 0x70];
    s32 unk84;
    u8 pad_88[0x144 - 0x88];
    u8 unk144[0x10];
    u8 unk154[0x10];
} Unk_80058078;
typedef struct Unk_80059148_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, s32);
    u8 pad_48[0x180 - 0x48];
    void (*unk180)(void *, s32);
} Unk_80059148_Vtbl;
typedef struct Unk_80059148 {
    Unk_80059148_Vtbl *unk0;
    u8 pad_04[0x6C - 0x04];
    s32 unk6C;
    u8 pad_70[0x884 - 0x70];
    s32 unk884;
} Unk_80059148;
typedef struct Unk_8005AF64_Vtbl {
    u8 pad_00[0xBC];
    void (*unkBC)(void *, s32 *);
} Unk_8005AF64_Vtbl;
typedef struct Unk_8005AF64 {
    Unk_8005AF64_Vtbl *unk0;
} Unk_8005AF64;
s32 func_8005BA7C(void);
typedef struct Unk_8005B6E0 {
    u8 pad[0x184];
    s32 unk184;
    s32 unk188;
    s32 unk18C;
} Unk_8005B6E0;
typedef struct Unk_80058390_Vt {
    u8 pad_00[0x44];
    void (*unk44)(void *, void *, s32);
} Unk_80058390_Vt;
typedef struct Unk_80058390 {
    u8 pad_00[0x38];
    s32 unk38;
    u8 pad_3C[0x238 - 0x3C];
    s32 unk238;
} Unk_80058390;
extern Unk_80058390_Vt *func_8003DFBC(void);
typedef struct Unk_80058A94_Vt {
    u8 pad_00[0x14];
    void (*unk14)(void *, void *);
} Unk_80058A94_Vt;
typedef struct Unk_80058A94_ObjVt {
    u8 pad_00[0xF0];
    void (*unkF0)(void *);
} Unk_80058A94_ObjVt;
typedef struct Unk_80058A94_Obj {
    Unk_80058A94_ObjVt *vt;
} Unk_80058A94_Obj;
typedef struct Unk_80058A94 {
    Unk_80058A94_Vt *unk0;
    u8 pad_04[0x4C - 0x4];
    Unk_80058A94_Obj *unk4C;
} Unk_80058A94;
typedef struct Unk_80058A94_RetVt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    u8 pad_0C[0x50 - 0x0C];
    void (*unk50)(void *);
    u8 pad_54[0x9C - 0x54];
    void (*unk9C)(void *, s32 **, s32);
    u8 pad_A0[0xDC - 0xA0];
    void (*unkDC)(void *, s32 **, s32);
} Unk_80058A94_RetVt;
Unk_80058A94_RetVt *func_80057C84(void);
extern u16 D_8008875C[];
typedef struct Unk_8005BE28 {
    u8 pad_00[4];
    u16 u4;
} Unk_8005BE28;
s32 D_8008ABE0;
extern void func_8005BA50(u8 *arg0, s32 *arg1);
extern void *memset(void *arg0, s32 arg1, s32 arg2);
typedef struct Unk_8005A258 {
    u8 pad_00[0x178];
    s32 unk178;
    s32 unk17C;
    s32 unk180;
    s32 unk184;
    s32 unk188;
    s32 unk18C;
    u8 pad_190[0x46C - 0x190];
    s32 unk46C;
    u8 pad_470[0x5D8 - 0x470];
    u8 unk5D8;
    u8 pad_5D9[0x5DF - 0x5D9];
    u8 unk5DF;
    u8 unk5E0[0x600 - 0x5E0];
    s32 unk600[(0x678 - 0x600) / 4];
    s32 unk678;
    s32 unk67C;
    s32 unk680;
    u8 unk684[0x1F4];
} Unk_8005A258;
s32 func_8005C28C(void *arg0, s32 *arg1, void *arg2, s32 arg3);
typedef struct Unk_8005A508_Vtbl {
    u8 pad_00[0x104];
    s32 (*unk104)(void *, s32);
    u8 pad_108[0x1EC - 0x108];
    void (*unk1EC)(void *, void *, s32);
} Unk_8005A508_Vtbl;
typedef struct Unk_8005A508 {
    Unk_8005A508_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    u8 pad_48[0x164 - 0x48];
    s32 unk164;
    u8 pad_168[0x16C - 0x168];
    u8 unk16C[1];
    u8 pad_16D[0x180 - 0x16D];
    s32 unk180;
} Unk_8005A508;
void *func_80017B34(s32 size);
typedef struct Unk_8005BA40_Vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32, s32);
} Unk_8005BA40_Vt;
Unk_8005BA40_Vt *func_8005BA40(void);
extern s32 D_80087E08[];
typedef struct Unk_800588EC_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, void *);
    u8 pad_48[0x60 - 0x48];
    void (*unk60)(void *, s32);
} Unk_800588EC_Vtbl;
typedef struct Unk_800588EC {
    Unk_800588EC_Vtbl *unk0;
    u8 pad_04[0x78 - 0x04];
    s32 unk78;
    u8 pad_7C[0x80 - 0x7C];
    s32 unk80;
    u8 pad_84[0x98 - 0x84];
    s32 unk98;
    u8 pad_9C[0xCC - 0x9C];
    s32 unkCC;
    u8 pad_D0[0x908 - 0xD0];
    s32 unk908;
    s32 unk90C;
    s32 unk910;
    u8 pad_914[0x924 - 0x914];
    s32 unk924;
} Unk_800588EC;
typedef struct Unk_8005966C_unk0 {
    u8 pad_00[0x140];
    s32 unk140;
    u8 pad_144[0x14C - 0x144];
    s32 unk14C;
    s32 unk150;
} Unk_8005966C_unk0;
typedef struct Unk_8005966C {
    Unk_8005966C_unk0 *unk0;
    u8 pad_04[0x80 - 0x04];
    s32 unk80;
    s32 unk84;
} Unk_8005966C;
s32 func_8005B66C(s32, s32, s32);
void func_80017CFC(s32);
typedef struct Unk_80058308_ObjVt {
    u8 pad_00[4];
    void (*unk4)(void *);
} Unk_80058308_ObjVt;
typedef struct Unk_80058308_Obj {
    Unk_80058308_ObjVt *vt;
} Unk_80058308_Obj;
typedef struct Unk_80058308_Ret {
    u8 pad_00[0xDC];
    void (*unkDC)(void *);
} Unk_80058308_Ret;
typedef struct Unk_80058308 {
    u8 pad_00[0xA8];
    Unk_80058308_Obj *unkA8[100];
    u8 pad_238[0x240 - 0x238];
    s32 unk240;
} Unk_80058308;
typedef struct Unk_80058E8C_Vtbl {
    u8 pad_00[0x1E4];
    void (*unk1E4)(void *, s32 **, s32);
} Unk_80058E8C_Vtbl;
typedef struct Unk_80058E8C {
    Unk_80058E8C_Vtbl *unk0;
} Unk_80058E8C;
typedef struct Unk_8005A7A0 {
    u8 pad_00[0x24];
    s32 unk24;
    u8 pad_28[0x44 - 0x28];
    s32 unk44;
    u8 pad_48[0x164 - 0x48];
    s32 unk164;
    u8 pad_168[0x16C - 0x168];
    u8 unk16C[1];
    u8 pad_16D[0x880 - 0x16D];
    s32 *unk880;
    s32 unk884;
    s32 unk888;
} Unk_8005A7A0;
s32 func_8005BE90();
s32 *func_8005BF48(void);
typedef struct Unk_80058F18_Vtbl {
    u8 pad_00[0x1E8];
    void (*unk1E8)(void *, s32 **, s32);
} Unk_80058F18_Vtbl;
typedef struct Unk_80058F18 {
    Unk_80058F18_Vtbl *unk0;
} Unk_80058F18;
extern s32 D_80087EA4[];
extern void func_8002CD08(s32, void *);
extern s8 D_80087E14[][3];
typedef struct Unk_8005B904_B28 {
    s32 unk[10];
} Unk_8005B904_B28;
typedef struct Unk_8005B904_B50 {
    s32 unk0;
    u8 pad_04[0x40];
    Unk_8005B904_B28 *unk44;
    u8 pad_48[0x8];
} Unk_8005B904_B50;
typedef struct Unk_8005B904 {
    u8 pad_00[0x14];
    Unk_8005B904_B50 *unk14;
    u8 pad_18[0x890 - 0x18];
    Unk_8005B904_B50 unk890;
    Unk_8005B904_B28 unk8E0;
} Unk_8005B904;
typedef struct Unk_8005A700 {
    u8 pad_00[0x24];
    s32 unk24;
    u8 pad_28[0x44 - 0x28];
    s32 unk44;
    u8 pad_48[0xA8 - 0x48];
    s32 unkA8;
    u8 pad_AC[0x164 - 0xAC];
    s32 unk164;
    u8 pad_168[0x16C - 0x168];
    u8 unk16C[1];
    u8 pad_16D[0x880 - 0x16D];
    s32 *unk880;
    s32 unk884;
    s32 unk888;
} Unk_8005A700;
void func_8001E6F8(Unk_8005A700 *arg0, s32 *arg1);
s32 func_8005BCF8(void *arg0, s16 *arg1, s32 arg2);
s32 func_8005BD3C(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2);
typedef struct Unk_8005A368_Vtbl {
    u8 pad_00[0x1C0];
    void (*unk1C0)(void *);
    u8 pad_1C4[0x1CC - 0x1C4];
    void (*unk1CC)(void *, s32);
    u8 pad_1D0[0x1F0 - 0x1D0];
    void (*unk1F0)(void *, s32);
} Unk_8005A368_Vtbl;
typedef struct Unk_8005A368 {
    Unk_8005A368_Vtbl *unk0;
    u8 pad_04[0x24 - 0x04];
    s32 unk24;
    u8 pad_28[0x68 - 0x28];
    s32 unk68;
    u8 pad_6C[0x164 - 0x6C];
    s32 unk164;
    u8 unk168[0x180 - 0x168];
    s32 unk180;
    u8 pad_184[0x87C - 0x184];
    s32 unk87C;
    u8 pad_880[0x88C - 0x880];
    s32 unk88C;
} Unk_8005A368;
s32 func_8005C438(void *arg0, s32 arg1);
typedef struct Unk_8005B420_Vtbl {
    u8 pad_00[0x20C];
    void (*unk20C)(void *, void *, s16 *);
} Unk_8005B420_Vtbl;
typedef struct Unk_8005B420 {
    Unk_8005B420_Vtbl *unk0;
    u8 pad_04[0x144 - 0x04];
    u8 unk144[0x154 - 0x144];
    u8 unk154[0x160 - 0x154];
    s32 unk160;
} Unk_8005B420;
typedef struct Unk_8005A41C_Vtbl {
    u8 pad_00[0x198];
    void (*unk198)(void *);
    u8 pad_19C[0x1A4 - 0x19C];
    void (*unk1A4)(void *);
    u8 pad_1A8[0x1C0 - 0x1A8];
    void (*unk1C0)(void *);
    u8 pad_1C4[0x1CC - 0x1C4];
    void (*unk1CC)(void *, s32);
    u8 pad_1D0[0x1F0 - 0x1D0];
    void (*unk1F0)(void *, s32);
    u8 pad_1F4[0x1FC - 0x1F4];
    void (*unk1FC)(void *, void *);
    u8 pad_200[0x210 - 0x200];
    void (*unk210)(void *);
} Unk_8005A41C_Vtbl;
typedef struct Unk_8005A41C {
    Unk_8005A41C_Vtbl *unk0;
    u8 pad_04[0x24 - 0x04];
    s32 unk24;
    u8 pad_28[0x68 - 0x28];
    s32 unk68;
    u8 pad_6C[0x164 - 0x6C];
    s32 unk164;
    u8 pad_168[0x180 - 0x168];
    s32 unk180;
    u8 pad_184[0x190 - 0x184];
    s16 unk190[(0x878 - 0x190) / 2];
    s32 unk878;
    s32 unk87C;
    u8 pad_880[0x88C - 0x880];
    s32 unk88C;
} Unk_8005A41C;
typedef struct Unk_80058694_Vtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *, s32, void *);
} Unk_80058694_Vtbl;
typedef struct Unk_80058694_Obj {
    Unk_80058694_Vtbl *vt;
} Unk_80058694_Obj;
typedef struct Unk_80058694 {
    u8 pad_00[0x1C];
    u32 unk1C;
    u8 pad_20[0xA8 - 0x20];
    Unk_80058694_Obj *unkA8[100];
    s32 unk238;
    u32 unk23C;
    s8 *unk240;
} Unk_80058694;
extern s32 D_8008ABBC;
extern s32 rand(void);
extern s16 D_80088CCC[42];
extern s32 D_8008ABF4;
typedef struct Unk_8005C438 {
    s16 unk0;
    s16 unk2;
} Unk_8005C438;
extern s32 func_8002CC34(s32, void *, s32, void *, s32);
typedef struct Unk_800596E8_Vtbl {
    u8 pad_00[0x154];
    s32 unk154;
    u8 pad_158[0x178 - 0x158];
    s32 unk178;
    void (*unk17C)(void *, s32);
    u8 pad_180[0x194 - 0x180];
    s32 unk194;
} Unk_800596E8_Vtbl;
typedef struct Unk_800596E8 {
    Unk_800596E8_Vtbl *unk0;
    u8 pad_04[0x58 - 0x04];
    s32 unk58;
    u8 pad_5C[0x98 - 0x5C];
    s32 unk98;
    s32 unk9C;
    u8 pad_A0[0xC4 - 0xA0];
    s32 unkC4;
    s32 unkC8;
    u8 unkCC[1];
} Unk_800596E8;
typedef struct Unk_8005AD68_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, void *);
} Unk_8005AD68_Vtbl;
typedef struct Unk_8005AD68 {
    Unk_8005AD68_Vtbl *vt;
    u8 pad_04[0xA0 - 0x04];
    s32 unkA0;
    s32 unkA4;
    u8 pad_A8[0xAC - 0xA8];
    s32 unkAC;
    u8 pad_B0[0x914 - 0xB0];
    s32 unk914;
    u8 pad_918[0x91C - 0x918];
    s16 unk91C[3];
} Unk_8005AD68;
extern s16 D_8008ABD0[];
extern u8 D_80087EFC[];
void func_8005AF64(Unk_8005AF64 *, s16 *, s16 *);
extern u8 D_8008ABAC[];
extern s32 D_8008ABB4[];
void *func_800404D0(s32 arg0, s32 arg1, s32 arg2);
typedef struct Unk_80058228 {
    u8 pad_00[0xA8];
    void *unkA8[100];
    u8 pad_238[0x240 - 0x238];
    void *unk240;
} Unk_80058228;
typedef struct Unk_80058228Bytes {
    s8 c[3];
} Unk_80058228Bytes;
extern Unk_80058228Bytes D_8008ABB8;
typedef struct Unk_8005942C_Arg0 {
    void *vt;
    u8 pad_04[0x0C - 0x04];
    s32 unkC;
    u8 pad_10[0x14 - 0x10];
    u8 *unk14;
    u8 pad_18[0x5C - 0x18];
    u8 *unk5C;
} Unk_8005942C_Arg0;
typedef struct Unk_8005942C_Vec {
    s32 x;
    s32 y;
    s32 z;
} Unk_8005942C_Vec;
extern s32 D_80087EE8[];
extern void func_8001E600(void *arg0, void *arg1, void *arg2, s32 arg3);
s32 func_8001EF14(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_8005950C(Unk_8005B5A4 *arg0, Unk_8005B5A4 *arg1, s32 arg2);
typedef struct Unk_800580E0_Vt {
    u8 pad_00[0x5C];
    void (*unk5C)(void *, void *, s32);
} Unk_800580E0_Vt;
typedef struct Unk_800580E0_Res {
    u8 pad_00[0x4];
    s32 unk4;
    s32 unk8;
} Unk_800580E0_Res;
typedef struct Unk_800580E0_A4_Vtbl {
    u8 pad_00[0x1B0];
    Unk_800580E0_Res *(*unk1B0)(void *, s32);
} Unk_800580E0_A4_Vtbl;
typedef struct Unk_800580E0_A4 {
    Unk_800580E0_A4_Vtbl *vt;
} Unk_800580E0_A4;
typedef struct Unk_800580E0_A8_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_800580E0_A8_Vtbl;
typedef struct Unk_800580E0_A8 {
    Unk_800580E0_A8_Vtbl *vt;
} Unk_800580E0_A8;
typedef struct Unk_800580E0_Vtbl {
    u8 pad_00[0x124];
    void (*unk124)(void *);
} Unk_800580E0_Vtbl;
typedef struct Unk_800580E0 {
    Unk_800580E0_Vtbl *vt;
    u8 pad_04[0x1C - 0x04];
    s32 unk1C;
    u8 pad_20[0x3C - 0x20];
    s32 unk3C;
    u8 pad_40[0xA4 - 0x40];
    Unk_800580E0_A4 *unkA4;
    Unk_800580E0_A8 *unkA8;
} Unk_800580E0;
extern u8 D_80088758[];
extern u8 *D_80088858[];
extern u8 *D_800889B8[];
s32 D_8008ACC0;
s32 func_8005BE28(Unk_8005BE28 *arg0, u8 arg1);
extern u8 *D_80088C84[];
extern u8 *D_80088BDC[];
extern s16 D_8008ABC0[];
typedef struct Unk_8005A928_Vtbl {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
} Unk_8005A928_Vtbl;
typedef struct Unk_8005A928_ObjVtbl {
    u8 pad_00[0x80];
    void (*unk80)(void *, s32, s32, s32);
} Unk_8005A928_ObjVtbl;
typedef struct Unk_8005A928_Obj {
    Unk_8005A928_ObjVtbl *vt;
} Unk_8005A928_Obj;
typedef struct Unk_8005A928 {
    Unk_8005A928_Vtbl *vt;
    u8 pad_04[0x24 - 0x04];
    s32 unk24;
    u8 pad_28[0x44 - 0x28];
    s32 unk44;
    u8 pad_48[0x58 - 0x48];
    Unk_8005A928_Obj *unk58;
    u8 pad_5C[0x68 - 0x5C];
    s32 unk68;
    u8 pad_6C[0x164 - 0x6C];
    s32 unk164;
} Unk_8005A928;
typedef struct Unk_8005B81C_Vt {
    u8 pad_00[0x214];
    void (*unk214)(void *, s32, s32, s32 *, s32, s32, s32);
} Unk_8005B81C_Vt;
typedef struct Unk_8005B81C_ObjVt {
    u8 pad_00[0x10C];
    s32 (*unk10C)(void *, s32, s32);
} Unk_8005B81C_ObjVt;
typedef struct Unk_8005B81C_Obj {
    Unk_8005B81C_ObjVt *vt;
} Unk_8005B81C_Obj;
typedef struct Unk_8005B81C {
    Unk_8005B81C_Vt *unk0;
    u8 pad_04[0x4C - 0x4];
    Unk_8005B81C_Obj *unk4C;
    u8 pad_50[0x164 - 0x50];
    s32 unk164;
    u8 pad_168[0x180 - 0x168];
    s32 unk180;
} Unk_8005B81C;
s32 D_8008ABE8;
typedef struct Unk_8005BE90 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
} Unk_8005BE90;
typedef struct Unk_80059814 {
    u8 pad_00[0x5C];
    Unk_80059360 *unk5C;
    u8 pad_60[0x88 - 0x60];
    s32 unk88;
    s32 unk8C;
} Unk_80059814;
extern s32 D_80087E50[];
extern s32 D_80087E5C[];
typedef struct Unk_800587F0_ArgVtbl {
    u8 pad_00[0x80];
    s32 (*unk80)(void *, s32);
} Unk_800587F0_ArgVtbl;
typedef struct Unk_800587F0_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
    u8 pad_14[0x40 - 0x14];
    void (*unk40)(void *);
    u8 pad_44[0x104 - 0x44];
    void (*unk104)(void *, s32);
    u8 pad_108[0x198 - 0x108];
    void (*unk198)(void *);
} Unk_800587F0_Vtbl;
typedef struct Unk_800587F0 {
    Unk_800587F0_Vtbl *unk0;
    u8 pad_04[0x58 - 0x04];
    s32 unk58;
    s32 unk5C;
    void **unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    u8 pad_74[0x878 - 0x74];
    s32 unk878;
} Unk_800587F0;
typedef struct Unk_8005B1F4 {
    u8 pad_00[0x17C];
    s32 unk17C;
    s32 unk180;
    u8 pad_184[0x190 - 0x184];
    Unk_8005B5B8 unk190[365];
} Unk_8005B1F4;
extern s8 D_80087EB0[];
extern s8 D_80087EC8[];
typedef struct Unk_80059D1C_Vtbl {
    u8 pad_00[0x80];
    s32 (*unk80)(void *, s32, s32, s32);
    u8 pad_84[0x9C - 0x84];
    void (*unk9C)(void *, s32);
} Unk_80059D1C_Vtbl;
typedef struct Unk_80059D1C_Obj {
    Unk_80059D1C_Vtbl *vt;
} Unk_80059D1C_Obj;
typedef struct Unk_80059D1C {
    u8 pad_00[0x58];
    Unk_80059D1C_Obj *unk58;
    u8 pad_5C[0xB8 - 0x5C];
    s32 unkB8;
    s32 unkBC;
} Unk_80059D1C;
typedef struct Unk_80058968_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void *, void *);
    u8 pad_14[0x44 - 0x14];
    void (*unk44)(void *, s32, void *);
    u8 pad_48[0x104 - 0x48];
    void (*unk104)(void *, s32);
} Unk_80058968_Vtbl;
typedef struct Unk_80058968_Elem {
    u8 pad_00[0xE];
    u8 unkE[0x1A - 0xE];
    s16 unk1A;
    u8 pad_1C[0x24 - 0x1C];
} Unk_80058968_Elem;
typedef struct Unk_80058968 {
    Unk_80058968_Vtbl *unk0;
    u8 pad_04[0x44 - 0x04];
    s32 unk44;
    u8 pad_48[0x6C - 0x48];
    s32 unk6C;
    u8 pad_70[0x470 - 0x70];
    Unk_80058968_Elem unk470[10];
    u8 pad_5D8[0x87C - 0x5D8];
    s32 unk87C;
    u8 pad_880[0x888 - 0x880];
    void *unk888;
} Unk_80058968;
typedef struct Unk_80058968_ArgVtbl {
    u8 pad_00[0xE4];
    void (*unkE4)(void *, void *, void *, void *);
} Unk_80058968_ArgVtbl;
typedef struct Unk_80058968_RetVtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *, void *, void *);
} Unk_80058968_RetVtbl;
extern s16 D_8008ABC8[];
extern u8 D_80087F08[];
typedef struct Unk_8005AC24 {
    Unk_8005AD68_Vtbl *vt;
    u8 pad_04[0x88 - 0x04];
    s32 unk88;
    u8 pad_8C[0xA0 - 0x8C];
    s32 unkA0;
    s32 unkA4;
    u8 pad_A8[0xAC - 0xA8];
    s32 unkAC;
    u8 pad_B0[0x914 - 0xB0];
    s32 unk914;
    u8 pad_918[0x91C - 0x918];
    s16 unk91C[3];
} Unk_8005AC24;
typedef struct Unk_80058B08_Ret {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32);
} Unk_80058B08_Ret;
typedef struct Unk_80058B08_Vt {
    u8 pad_00[0x1D4];
    void (*unk1D4)(void *, s32);
    u8 pad_1D8[0x224 - 0x1D8];
    void (*unk224)(void *);
} Unk_80058B08_Vt;
typedef struct Unk_80058B08_Sub {
    u8 pad_00[0x2C];
    s16 unk2C;
} Unk_80058B08_Sub;
typedef struct Unk_80058B08_Ret11C {
    u8 pad_00[4];
    Unk_80058B08_Sub *unk4;
} Unk_80058B08_Ret11C;
typedef struct Unk_80058B08_ObjVt {
    u8 pad_00[0x10C];
    s32 (*unk10C)(void *, s32, s32);
    u8 pad_110[0x11C - 0x110];
    Unk_80058B08_Ret11C *(*unk11C)(void *, s32);
} Unk_80058B08_ObjVt;
typedef struct Unk_80058B08_Obj {
    Unk_80058B08_ObjVt *vt;
} Unk_80058B08_Obj;
typedef struct Unk_80058B08_Unk28 {
    u8 pad_00[0x36];
    u16 unk36;
} Unk_80058B08_Unk28;
typedef struct Unk_80058B08 {
    Unk_80058B08_Vt *unk0;
    u8 pad_04[0x14 - 0x04];
    s32 unk14;
    u8 pad_18[0x28 - 0x18];
    Unk_80058B08_Unk28 *unk28;
    u8 pad_2C[0x44 - 0x2C];
    s32 unk44;
    u8 pad_48[0x4C - 0x48];
    Unk_80058B08_Obj *unk4C;
    u8 pad_50[0xB8 - 0x50];
    s32 unkB8;
    u8 pad_BC[0x164 - 0xBC];
    s32 unk164;
} Unk_80058B08;

void func_80058078(Unk_80058078 *arg0) {
    arg0->unk84 = 5;
    arg0->unk2C = 0x190;
    arg0->vt->unkD4(arg0, "ETC\\HGRAPH.TIM", 0);
    arg0->vt->unk6C(arg0, 10);
}

void func_800580E0(Unk_800580E0 *arg0, void *arg1, s32 arg2) {
    Unk_800580E0_Res *res;

    ((Unk_800580E0_Vt *)func_8003DFBC())->unk5C(arg0, arg1, arg2);
    if (arg0->unk3C == 1) {
        res = arg0->unkA4->vt->unk1B0(arg0->unkA4, 0);
        if (res->unk4 != 0 || res->unk8 != 0) {
            arg0->unkA8->vt->unk60(arg0->unkA8, arg0->unk1C & 1);
        }
    }
    arg0->vt->unk124(arg0);
}

void func_800581C4(Unk_800581C4 *arg0) {
    if (arg0->unk238 == 0) {
        arg0->unk0->unk70(arg0, 0x10);
        arg0->unk0->unk94(arg0);
    }
}

void func_80058228(Unk_80058228 *arg0) {
    Unk_80058228Bytes sp;
    s32 i;
    s32 step;

    arg0->unkA8[0] = func_800404D0((s32)D_8008ABAC, (s32)D_8008ABB4, 0);
    sp = D_8008ABB8;
    i = 1;
    do {
        arg0->unkA8[i] = func_800404D0((s32)D_8008ABAC, (s32)&sp, 0);
        step = (i < 7) ? 0x14 : 1;
        i++;
        sp.c[0] -= step;
        sp.c[1] -= step;
        sp.c[2] -= step;
    } while (i < 100);
    arg0->unk240 = func_80017B34(4);
}

void func_80058308(Unk_80058308 *arg0) {
    s32 i;
    Unk_80058308_Obj *obj;

    func_80017CFC(arg0->unk240);
    for (i = 0; i < 100; i++) {
        obj = arg0->unkA8[i];
        obj->vt->unk4(obj);
    }
    ((Unk_80058308_Ret *)func_8003DFBC())->unkDC(arg0);
}

s32 func_80058390(Unk_80058390 *arg0, void *arg1, s32 arg2) {
    s32 ret;

    func_8003DFBC()->unk44(arg0, arg1, arg2);
    ret = 2;
    if (arg0->unk238 == 0) {
        ret = arg0->unk38;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058404);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800585B4);

void func_80058694(Unk_80058694 *arg0) {
    u32 temp_a0;
    u32 temp_a1;
    Unk_80058694_Obj *obj;

    if (arg0->unk238 != 0) {
        temp_a0 = arg0->unk1C;
        if (temp_a0 >= 0x1F) {
            temp_a1 = arg0->unk23C;
            if ((temp_a1 < 4) && (temp_a0 % 24 == 0)) {
                obj = arg0->unkA8[arg0->unk240[temp_a1]];
                obj->vt->unkB8(obj, 1, &D_8008ABBC);
                arg0->unk23C = arg0->unk23C + 1;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058764);

void *func_80058774(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v0;

    temp_v0 = func_80017B34(0x928);
    if (temp_v0 != 0) {
        func_8005BA40()->unk8(temp_v0, arg0, arg1, arg2);
        return temp_v0;
    }
    return 0;
}

void func_800587F0(Unk_800587F0 *arg0, void **arg1, s32 arg2, s32 arg3) {
    func_80057C84()->unk8(arg0);
    arg0->unk0 = (Unk_800587F0_Vtbl *)func_8005BA40();
    arg0->unk58 = arg2;
    arg0->unk5C = arg3;
    arg0->unk64 = 0;
    arg0->unk60 = arg1;
    arg0->unk0->unk10(arg0, ((Unk_800587F0_ArgVtbl *)*arg1)->unk80(arg1, 0));
    arg0->unk0->unk104(arg0, -1);
    arg0->unk70 = 1;
    arg0->unk6C = 0;
    arg0->unk878 = 1;
    arg0->unk0->unk198(arg0);
    arg0->unk0->unk40(arg0);
}

void func_800588EC(Unk_800588EC *arg0) {
    arg0->unk0->unk60(arg0, 0);
    arg0->unk0->unk44(arg0, 1, D_80087E08);
    arg0->unk80 = 0;
    arg0->unk98 = 0;
    arg0->unkCC = 0;
    arg0->unk908 = 0;
    arg0->unk90C = 0;
    arg0->unk910 = 0;
    arg0->unk78 = 0;
    arg0->unk924 = 0;
}

void func_80058968(Unk_80058968 *arg0, void **arg1) {
    s32 sp10[4];
    Unk_80058968_Elem *elem;
    void *temp_a2;

    ((Unk_80058968_ArgVtbl *)*arg1)->unkE4(arg1, sp10, arg0, (u8 *)arg0 + 0x16C);
    ((Unk_80058968_RetVtbl *)func_80057C84())->unk4C(arg0, arg1, sp10);
    arg0->unk0->unk10(arg0, arg1);
    if (arg0->unk44 == 0xE) {
        elem = &arg0->unk470[arg0->unk87C];
        arg0->unk0->unk44(arg0, 1, elem->unkE);
        arg0->unk0->unk104(arg0, elem->unk1A + 4);
        arg0->unk87C++;
    }
    if (arg0->unk6C != 0) {
        temp_a2 = arg0->unk888;
        if (temp_a2 != 0) {
            arg0->unk0->unk44(arg0, 1, temp_a2);
        }
    }
}

void func_80058A94(Unk_80058A94 *arg0) {
    Unk_80058A94_Obj *temp_a0;

    temp_a0 = arg0->unk4C;
    temp_a0->vt->unkF0(temp_a0);
    arg0->unk0->unk14(arg0, arg0->unk4C);
    func_80057C84()->unk50(arg0);
}

void func_80058B08(Unk_80058B08 *arg0, s32 arg1) {
    s32 temp_v0;
    Unk_80058B08_Obj *temp_a0;
    Unk_80058B08_Obj *temp_a0_2;

    ((Unk_80058B08_Ret *)func_80057C84())->unk88(arg0, arg1);
    switch (arg1) {
    case -1:
        temp_v0 = arg0->unk28->unk36 & 0x7F;
        arg0->unkB8 = temp_v0;
        if (temp_v0 >= 0x18) {
            arg0->unkB8 = 0;
        }
        if (arg0->unk44 == 0xF && arg0->unkB8 == 0) {
            arg0->unkB8 = 2;
        }
        if (arg0->unk164 == 9) {
            temp_a0 = arg0->unk4C;
            arg0->unk0->unk1D4(arg0, temp_a0->vt->unk10C(temp_a0, 0, 0));
        }
        return;
    case -2:
        temp_a0_2 = arg0->unk4C;
        if (temp_a0_2->vt->unk11C(temp_a0_2, arg0->unk14 + 0x18)->unk4->unk2C == 2) {
            temp_a0 = arg0->unk4C;
            arg0->unk0->unk1D4(arg0, temp_a0->vt->unk10C(temp_a0, 0, 0));
        } else {
            arg0->unk0->unk224(arg0);
        }
        return;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058C58);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058D94);

void func_80058E8C(Unk_80058E8C *arg0, s32 **arg1, s32 arg2) {
    func_80057C84()->unk9C(arg0, arg1, arg2);
    if ((**arg1 & 0xFFF) == 0x114) {
        arg0->unk0->unk1E4(arg0, arg1, arg2);
    }
}

void func_80058F18(Unk_80058F18 *arg0, s32 **arg1, s32 arg2) {
    func_80057C84()->unkDC(arg0, arg1, arg2);
    if ((**arg1 & 0xFFFFF) == 0x1F234) {
        arg0->unk0->unk1E8(arg0, arg1, arg2);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80058FAC);

void func_800590E0(void) {
}

s32 func_800590E8(Unk_800590E8 *arg0, s32 *arg1, s32 arg2) {
    s32 temp_s1;

    temp_s1 = arg0->unk68;
    if (arg2 < 0) {
        *arg1 = ((s32 (*)(void *))func_8005B518)((u8 *)arg0 + (arg0->unk180 * 2 + 0x190));
    } else {
        arg0->unk68 = arg2;
    }
    return temp_s1;
}

void func_80059148(Unk_80059148 *arg0, s32 arg1) {
    s32 temp_a2;

    arg0->unk6C = arg1;
    if (arg1 != 0) {
        arg0->unk0->unk180(arg0, 1);
        temp_a2 = arg0->unk884;
        if (temp_a2 != 0) {
            arg0->unk0->unk44(arg0, 1, temp_a2);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800591B4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059310);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005931C);

s32 func_80059328(Unk_80059328 *arg0, s32 arg1) {
    s32 old;

    if (arg1 >= 0) {
        arg1 *= 15;
    }
    old = arg0->unk134;
    arg0->unk134 = arg1;
    if (old >= 0) {
        old = (u32)old / 15;
    }
    return old;
}

u32 func_80059360(Unk_80059360 *arg0) {
    return arg0->unk24 / 15;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005937C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059384);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005938C);

void func_80059394(Unk_80059394 *arg0) {
    if (arg0->u70 == 0) {
        arg0->u74 = 0;
        arg0->u124 = arg0->u24 % arg0->u120 == 0;
    }
}

void func_800593D8(Unk_800593D8 *arg0) {
    if (arg0->unk80 != NULL) {
        arg0->unk80();
    }
    if (arg0->unk98 != NULL) {
        arg0->unk98(arg0);
    }
}

s32 func_8005942C(Unk_8005942C_Arg0 *arg0, Unk_8005942C_Vec *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    Unk_8005942C_Vec sp10;
    s32 temp_v0;
    s32 *temp;

    D_80087EE8[0] = arg2;
    func_8001E600(arg0, &sp10, &D_80087EE8[-2], 0);
    temp_v0 = func_8005950C((Unk_8005B5A4 *)(arg0->unk5C + 0x14), (Unk_8005B5A4 *)(arg0->unk5C + 0x20), arg2);
    if (arg0->unkC != 0) {
        temp = (s32 *)(arg0->unk14 + 0x38);
    } else {
        temp = NULL;
    }
    sp10.y = temp_v0 + temp[1];
    if (arg1 != NULL) {
        *arg1 = sp10;
    }
    if (arg3 != NULL) {
        return func_8001EF14((s32 *)&sp10, arg4, arg3);
    }
    return 0;
}

s32 func_8005950C(Unk_8005B5A4 *arg0, Unk_8005B5A4 *arg1, s32 arg2) {
    s32 span;

    arg2 /= 1024;
    span = (arg1->unk8 - arg0->unk8) / 1024;
    if (span == 0) {
        span = 1;
    }
    return ((arg1->unk4 - arg0->unk4) * arg2) / span + arg0->unk4;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059590);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059598);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800595A0);

void func_800595A8(Unk_80059610 *arg0, s32 arg1) {
    arg0->unk0->unk13C(arg0, 0);
    if (arg1 != 0) {
        arg0->unk0->unk138(arg0, 0);
    }
}

void func_80059610(Unk_80059610 *arg0, s32 arg1, s32 arg2) {
    arg0->unk0->unk13C(arg0);
    arg0->unk0->unk138(arg0, arg2);
}

void func_8005966C(Unk_8005966C *arg0, s32 arg1) {
    Unk_8005966C_unk0 *temp_v1 = arg0->unk0;

    arg0->unk84 = arg1;
    switch (arg1) {
    case 0:
        arg0->unk80 = 0;
        return;
    case 1:
        arg0->unk80 = temp_v1->unk140;
        return;
    case 2:
        arg0->unk80 = temp_v1->unk14C;
        return;
    case 3:
        arg0->unk80 = temp_v1->unk150;
        return;
    }
}

void func_800596E8(Unk_800596E8 *arg0, s32 arg1) {
    Unk_800596E8_Vtbl *vt;

    vt = arg0->unk0;
    if (arg0->unk9C == 2) {
        vt->unk17C(arg0, 0);
    }
    arg0->unk9C = arg1;
    switch (arg1) {
    case 0:
        arg0->unk98 = 0;
        return;
    case 1:
        arg0->unk98 = vt->unk154;
        return;
    case 2: {
        s32 temp_v0;
        Unk_800596E8_Vtbl *temp_v1;

        temp_v0 = vt->unk178;
        temp_v1 = arg0->unk0;
        arg0->unkC4 = 1;
        arg0->unkC8 = 1;
        arg0->unk98 = temp_v0;
        func_8002CC34(arg0->unk58, arg0->unkCC, 1, arg0, temp_v1->unk194);
        return;
    }
    }
}

void func_800597C0(Unk_800597C0 *arg0) {
    arg0->unk0->unk144(arg0);
    arg0->unk0->unk148(arg0);
}

void func_80059814(Unk_80059814 *arg0) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1_3;
    Unk_80059360 *temp_v0_2;
    Unk_80059360 *temp_v1_4;
    s32 temp_v1;

    temp_v1 = arg0->unk88;
    if (temp_v1 != 0) {
        temp_a2 = D_80087E50[temp_v1];
        temp_v1_3 = D_80087E5C[temp_v1];
        temp_a1 = temp_a2 + arg0->unk8C;
        if ((temp_a1 < 0 ? ~temp_a1 + 1 : temp_a1) < temp_v1_3) {
            temp_v1_4 = arg0->unk5C;
            temp_v1_4->unk24 = (u32) (temp_a2 + temp_v1_4->unk24);
            arg0->unk8C = temp_a1;
        }
        arg0->unk88 = 0;
        return;
    }
    temp_v0 = arg0->unk8C;
    if (temp_v0 != 0) {
        temp_a2 = -0x258;
        if (temp_v0 < 0) {
            temp_a2 = 0x258;
        }
        temp_v0_2 = arg0->unk5C;
        temp_v0_2->unk24 = (u32) (temp_a2 + temp_v0_2->unk24);
        arg0->unk8C = (s32) (temp_a2 + arg0->unk8C);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_800598E8);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059A1C);

void func_80059A48(void) {
}

void func_80059A50(void) {
}

void func_80059A58(Unk_80058078 *arg0) {
    if (arg0->unk6C == 0) {
        arg0->vt->unk174(arg0);
        arg0->vt->unk158(arg0);
    } else if (arg0->unk6C == 2) {
        arg0->vt->unk160(arg0);
    } else {
        arg0->vt->unk15C(arg0);
    }
}

void func_80059AEC(Unk_80059AEC *arg0) {
    if (arg0->unk70 == 0) {
        arg0->unk0->unk170(arg0, arg0->unk0->unk164(arg0, 1));
    }
}

void func_80059B50(Unk_80059AEC *arg0) {
    arg0->unkA0 = 1;
    if (arg0->unk70 == 0) {
        arg0->unk0->unk170(arg0, arg0->unk0->unk164(arg0, 1));
    } else {
        arg0->unk0->unk164(arg0, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059BD4);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059BE0);

void func_80059D1C(Unk_80059D1C *arg0) {
    Unk_80059D1C_Obj *obj = arg0->unk58;
    s32 idx = arg0->unkB8;
    Unk_80059D1C_Vtbl *vt = obj->vt;
    s32 t;

    if (idx != 0) {
        t = D_80087EB0[idx] * 0x10;
        vt->unk9C(obj, D_80087EC8[idx]);
        arg0->unkBC = vt->unk80(obj, t, 0x6E, 0x6E);
        if (arg0->unkB8 != 0x16) {
            arg0->unkBC = -1;
        }
        if (arg0->unkB8 == 0xB) {
            vt->unk9C(obj, 1);
            vt->unk80(obj, t, 0x6E, 0x6E);
            vt->unk9C(obj, 2);
            vt->unk80(obj, 0x90, 0x6E, 0x6E);
        }
    }
}

void func_80059E3C(Unk_80059E3C *arg0) {
    s32 temp_a1;
    Unk_80059E3C_Obj *temp_a0;

    temp_a1 = arg0->uBC;
    if (temp_a1 >= 0) {
        temp_a0 = arg0->u58;
        temp_a0->vt->unk84(temp_a0, temp_a1);
        arg0->uBC = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_80059E98);

void func_8005A050(Unk_8005A050 *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unkA4;
    if (temp_v0 != 0) {
        arg0->unk0->unk44(arg0, 0, D_80087E80 + temp_v0 * 12);
        arg0->unkA4 = 0;
    }
}

void func_8005A0B0(Unk_8005A134 *arg0) {
    Unk_80059360 *temp_v1;

    if (arg0->uC4 != 0) {
        arg0->unk0->unkBC(arg0, D_80087EA4);
        temp_v1 = arg0->unk5C;
        temp_v1->unk24 = temp_v1->unk24 - 0x258;
    }
    if (arg0->uC8 != 0) {
        func_8002CD08((s32) arg0->u58, arg0->uCC);
    }
}

void func_8005A134(Unk_8005A134 *arg0, s32 arg1) {
    arg0->uC4 = 0;
    arg0->uC8 = arg1;
    if (arg1 != 0) {
        func_8002CC84(arg0->u58, arg0->uCC);
    }
}

s32 func_8005A168(Unk_8005A168 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0->unkAC;
    if (arg1 >= 0) {
        arg0->unkAC = arg1;
        arg0->unkB0 = arg1;
    }
    return temp_v0;
}

void func_8005A184(Unk_8005A184 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0->unkAC;
    if (temp_v0 != arg1) {
        arg0->unkB0 = temp_v0;
        arg0->unkAC = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A1A4);

void func_8005A1B0(Unk_8005A1B0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg1 >= 0) {
        arg0->unk124 = arg1;
    }
    if (arg2 >= 0) {
        arg0->unk128 = arg2;
    }
    if (arg3 >= 0) {
        arg0->unk12C = arg3;
    }
    if (arg4 >= 0) {
        arg0->unk130 = arg4;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A1EC);

void func_8005A1F4(s32 arg0, S *arg1) {
    s32 r;
    if (arg1->u0 == 1) {
        r = arg1->u4 % 20; if (r == 0) {
            arg1->u1C = 9;
            arg1->u20 = -1;
        } else {
            arg1->u30 = 9;
            arg1->u34 = -1;
        }
    }
}

void func_8005A258(Unk_8005A258 *arg0) {
    arg0->unk178 = D_8008ABE0;
    arg0->unk17C = 0;
    arg0->unk180 = 0;
    arg0->unk184 = 0;
    arg0->unk188 = 0;
    arg0->unk18C = 0;
    arg0->unk46C = 0;
    arg0->unk5DF = 0;
    arg0->unk5D8 = 0;
    arg0->unk678 = 1;
    arg0->unk67C = 0;
    arg0->unk680 = 0;
    func_8005BA50(arg0->unk5E0, arg0->unk600);
    memset(arg0->unk684, 0, 0x1F4);
}

void func_8005A2D0(Unk_8005A2D0 *arg0, s32 *arg1) {
    s32 temp_v1;

    temp_v1 = arg0->unk678;
    arg0->unk678 = *arg1;
    *arg1 = temp_v1;
}

s32 func_8005A2E4(Unk_8005A2E4 *arg0, s32 *arg1) {
    if (arg1 != NULL) {
        *arg1 = arg0->unk17C;
    }
    return arg0->unk180 + 1;
}

s32 func_8005A304(Unk_8005A304 *arg0) {
    if (++arg0->unk180 >= 365) {
        arg0->unk180 = 0;
        arg0->unk17C++;
    }
    return arg0->unk180;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A33C);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A344);

s32 func_8005A350(s32 arg0, s32 *arg1) {
    if (arg1 != NULL) {
        *arg1 = 0x700;
    }
    return arg0 + 0x178;
}

s32 func_8005A368(Unk_8005A368 *arg0) {
    s32 temp;

    arg0->unk87C = 0;
    arg0->unk24 = 0;
    arg0->unk88C = arg0->unk180;
    if (arg0->unk68 != 0) {
        arg0->unk0->unk1CC(arg0, 1);
        return arg0->unk164;
    }
    temp = func_8005C438(arg0->unk168, arg0->unk180 + 1);
    arg0->unk0->unk1F0(arg0, temp);
    if (temp == 0) {
        arg0->unk0->unk1C0(arg0);
        return arg0->unk164;
    }
    return -1;
}

s32 func_8005A41C(Unk_8005A41C *arg0, s32 arg1) {
    arg0->unk180 = arg0->unk88C;
    if (arg0->unk68 == 0 && arg1 == 0) {
        arg0->unk0->unk210(arg0);
        arg0->unk0->unk1FC(arg0, &arg0->unk190[arg0->unk180]);
        arg0->unk0->unk1A4(arg0);
    } else if (arg1 == 2) {
        arg0->unk0->unk198(arg0);
        arg0->unk878 = 1;
    }
    return arg0->unk68;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A4E8);

void func_8005A508(Unk_8005A508 *arg0) {
    s32 sp10;
    s32 sp14;

    arg0->unk0->unk1EC(arg0, &sp10, 1);
    arg0->unk164 = func_8005C28C(arg0->unk16C, &sp14, &sp10, arg0->unk180);
    sp14 = arg0->unk0->unk104(arg0, sp14);
    arg0->unk44 = 0xB;
}

void func_8005A580(Unk_8005A580 *arg0) {
    if (arg0->unk44 == 0) {
        func_8005A928(arg0, func_8005BB30(arg0->unk16C, arg0->unk164, arg0->unk24), 0xC, 1);
    }
}

s32 func_8005A5D8(Unk_8005A580 *arg0, void *arg1) {
    s32 temp_v0;

    if (arg0->unk44 == 0) {
        temp_v0 = ((s32 (*)(void *, void *, s32))func_8005BCB4)(arg0->unk16C, arg1, arg0->unk164);
        if (temp_v0 >= 0) {
            func_8005A928(arg0, temp_v0, 0xD, 1);
            return 1;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A63C);

s32 func_8005A700(Unk_8005A700 *arg0, s16 *arg1) {
    s32 sp10[4];
    s32 temp;

    if (arg0->unk44 != 0) {
        return 0;
    }
    temp = func_8005BCF8(arg0->unk16C, arg1, arg0->unk164);
    if (temp < 0) {
        return 0;
    }
    func_8001E6F8(arg0, sp10);
    if (func_8005BD3C(&arg0->unk888, &arg0->unk884, sp10) == 0) {
        return 0;
    }
    if (arg0->unkA8 == 0) {
        return 0;
    }
    func_8005A928(arg0, temp, 0xF, 0);
    return 1;
}

s32 func_8005A7A0(Unk_8005A7A0 *arg0, s32 arg1) {
    s32 temp_s1;

    if (arg0->unk44 == 0) {
        temp_s1 = func_8005BE90(arg0->unk16C, arg0->unk164, arg1, arg0->unk24);
        if (temp_s1 >= 0) {
            arg0->unk880 = func_8005BF48();
            arg0->unk884 = 0;
            arg0->unk888 = 0;
            func_8005A928(arg0, temp_s1, 0x10, 0);
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A82C);

s32 func_8005A928(Unk_8005A928 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk44 = arg2;
    arg0->vt->unk30(arg0, arg2);
    if (arg0->unk44 == 0) {
        return 0;
    }
    arg0->unk164 = arg1;
    if (arg0->unk68 != 0) {
        arg0->unk24 = 0;
    }
    if (arg3 != 0) {
        Unk_8005A928_Obj *obj = arg0->unk58;
        obj->vt->unk80(obj, 0x90, 0x6E, 0x6E);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005A9CC);

s32 func_8005AB2C(Unk_8005AD68 *arg0) {
    s32 temp_v1;

    if (arg0->unk914 == 0) {
        func_8005AF64((Unk_8005AF64 *)arg0, D_8008ABC0, arg0->unk91C);
    }
    if (arg0->unkAC != 4) {
        temp_v1 = arg0->unk914;
        if (temp_v1 >= 0x85) {
            return 1;
        }
        if ((temp_v1 >= 0x2B && temp_v1 < 0x3A) || (temp_v1 >= 0x4B && temp_v1 < 0x5A)) {
            arg0->unkA4 = 2;
        }
    } else {
        temp_v1 = arg0->unk914;
        if (temp_v1 >= 0x13) {
            return 1;
        }
        if ((temp_v1 >= 8 && temp_v1 < 0xA) || (temp_v1 >= 0xD && temp_v1 < 0xF)) {
            arg0->vt->unk44(arg0, 0, D_80087EFC);
        }
    }
    arg0->unkA0 = 1;
    arg0->unk914++;
    return 0;
}

s32 func_8005AC24(Unk_8005AC24 *arg0) {
    s32 flag;

    if (arg0->unk914 == 0) {
        func_8005AF64((Unk_8005AF64 *)arg0, D_8008ABC8, arg0->unk91C);
    }
    if (arg0->unkAC != 4) {
        if (arg0->unk914 >= 0x95) {
            return 1;
        }
        if ((u32)(arg0->unk914 - 0x16) < 0xF || (u32)(arg0->unk914 - 0x39) < 0x10 || (u32)(arg0->unk914 - 0x6E) < 0xF) {
            arg0->unkA4 = 1;
        }
        flag = (u32)(arg0->unk914 - 0x39) < 0x35;
    } else {
        if (arg0->unk914 >= 0x19) {
            return 1;
        }
        if ((u32)(arg0->unk914 - 6) < 2 || (u32)(arg0->unk914 - 0xB) < 2 || (u32)(arg0->unk914 - 0x14) < 2) {
            arg0->vt->unk44(arg0, 0, D_80087F08);
        }
        flag = (u32)(arg0->unk914 - 3) < 0xE;
    }
    if (flag) {
        arg0->unk88 = 2;
    }
    arg0->unkA0 = 1;
    arg0->unk914++;
    return 0;
}

s32 func_8005AD68(Unk_8005AD68 *arg0) {
    if (arg0->unk914 == 0) {
        func_8005AF64((Unk_8005AF64 *)arg0, D_8008ABD0, arg0->unk91C);
    }
    if (arg0->unkAC != 4) {
        if (arg0->unk914 > 100) {
            return 1;
        }
        if (arg0->unk914 >= 43 && arg0->unk914 < 58) {
            arg0->unkA4 = 2;
        }
    } else {
        if (arg0->unk914 > 14) {
            return 1;
        }
        if (arg0->unk914 >= 8 && arg0->unk914 < 10) {
            arg0->vt->unk44(arg0, 0, D_80087EFC);
        }
    }
    arg0->unkA0 = 1;
    arg0->unk914++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AE40);

void func_8005AF64(Unk_8005AF64 *arg0, s16 *arg1, s16 *arg2) {
    s32 sp10[3];

    sp10[0] = arg1[0] - arg2[0];
    sp10[1] = arg1[1] - arg2[1];
    sp10[2] = arg1[2] - arg2[2];
    sp10[1] = 0;
    arg0->unk0->unkBC(arg0, sp10);
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005AFD0);

void func_8005AFDC(Unk_8005AFDC_A *arg0, Unk_8005AFDC_B *arg1, s32 arg2) {
    if (arg2 == 5) {
        arg0->vt->unk1F4(arg0, arg1->vt->unk10C(arg1, 0, 0));
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B03C);

void func_8005B1F4(Unk_8005B1F4 *arg0, Unk_8005B5B8 *arg1, s32 arg2) {
    s32 sum1 = 0;
    s32 sum0 = 0;
    s32 count;
    s32 i;
    Unk_8005B5B8 *p;

    if (arg2 != 0) {
        if (arg0->unk17C != 0 || arg0->unk180 != 0) {
            sum0 = arg0->unk190[arg0->unk180 - 1].unk0;
            sum1 = arg0->unk190[arg0->unk180 - 1].unk1;
        }
    } else {
        count = 365;
        if (arg0->unk17C == 0) {
            count = arg0->unk180;
        }
        if (count != 0) {
            p = arg0->unk190;
            for (i = 0; i < count; i++, p++) {
                sum0 += p->unk0;
                sum1 += p->unk1;
            }
            sum0 = sum0 / count;
            sum1 = sum1 / count;
        }
    }
    arg1->unk0 = sum0;
    arg1->unk1 = sum1;
}

void func_8005B2F4(Unk_80058078 *arg0, s32 arg1) {
    u8 *temp_s2 = arg0->unk144;
    u8 *temp_s3 = arg0->unk154;

    arg0->vt->unk204(arg0, temp_s2);
    arg0->vt->unk204(arg0, temp_s3);
    if (arg1 != 0) {
        arg0->vt->unk208(arg0, temp_s2, arg1);
        arg0->vt->unk208(arg0, temp_s3, arg1);
    }
}

void func_8005B3A4(Unk_8005B3A4 *arg0, s8 *arg1) {
    arg0->unk0->unk208(arg0, arg0->unk144, func_800495B8(arg0->unk164, arg1));
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B3F0);

void func_8005B420(Unk_8005B420 *arg0, Unk_8005B5B8 *arg1) {
    s16 sp10;
    s16 sp12;

    arg0->unk0->unk20C(arg0, arg0->unk144, &sp10);
    arg0->unk0->unk20C(arg0, arg0->unk154, &sp12);
    if (arg0->unk160 == 0) {
        sp12 = sp10;
    }
    arg1->unk0 = ((s8)sp10 + (s8)sp12) / 2;
    arg1->unk1 = (((s8 *)&sp10)[1] + ((s8 *)&sp12)[1]) / 2;
}

void func_8005B4E0(Unk_8005B4E0 *arg0) {
    s16 sp10;

    arg0->unk0->unk1FC(arg0, &sp10);
    func_8005B518(&sp10);
}

s8 func_8005B518(s16 *arg0) {
    s8 buf[2];
    s8 *p;
    s32 i;
    s8 v;


    *(u16 *)buf = *(u16 *)arg0;
    p = buf;
    i = 0;
    do {
        v = *p;
        if (v >= 4) {
            *p = 2;
        } else if (v < -3) {
            *p = 0;
        } else {
            *p = 1;
        }
        i++;
        p++;
    } while (i < 2);
    return D_80087E14[buf[0]][buf[1]];
}

void func_8005B5A4(s32 arg0, Unk_8005B5A4 *arg1) {
    arg1->unk0 = 0;
    arg1->unk8 = 0;
    arg1->unk4 = 0;
    arg1->unkC = 0;
}

void func_8005B5B8(s32 arg0, Unk_8005B5A4 *arg1, Unk_8005B5B8 *arg2) {
    s32 temp_v1;

    temp_v1 = arg1->unk4;
    arg1->unk0 = *(u16 *)arg2;
    arg1->unk4 = arg2->unk0 + temp_v1;
    arg1->unk8 = arg2->unk1 + arg1->unk8;
    arg1->unkC = arg1->unkC + 1;
}

void func_8005B5F0(s32 arg0, Unk_8005B5A4 *arg1, Unk_8005B5B8 *arg2) {
    if (arg1->unkC != 0) {
        arg2->unk0 = func_8005B66C(((Unk_8005B5B8 *)arg1)->unk0, arg1->unk4, arg1->unkC);
        arg2->unk1 = func_8005B66C(((Unk_8005B5B8 *)arg1)->unk1, arg1->unk8, arg1->unkC);
        return;
    }
    *(u16 *)arg2 = *(u16 *)arg1;
}

s32 func_8005B66C(s32 arg0, s32 arg1, s32 arg2) {
    s32 r = arg1 / arg2 + arg0 / 3;
    if (r > 9) {
        r = -9;
    } else if (r < -9) {
        r = 9;
    }
    return r;
}

void func_8005B6E0(Unk_8005B6E0 *arg0) {
    s32 temp;

    arg0->unk188 = func_8005BA7C();
    temp = arg0->unk18C;
    if (temp < 0) {
        arg0->unk18C = 0;
    } else if (temp > 0x02FAF080) {
        arg0->unk18C = 0x02FAF080;
    }
    arg0->unk184 = arg0->unk188 + arg0->unk18C;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B74C);

void func_8005B81C(Unk_8005B81C *arg0, s32 arg1, s32 arg2) {
    s32 sp20[4];
    s32 temp_s0;
    Unk_8005B81C_Obj *temp_a0;

    if (arg0->unk4C != NULL) {
        if (rand() % 3 == 0) {
            temp_a0 = arg0->unk4C;
            temp_s0 = temp_a0->vt->unk10C(temp_a0, 0, 0);
            func_8001E6F8((Unk_8005A700 *)arg0, sp20);
            arg0->unk0->unk214(arg0, arg0->unk164, temp_s0, sp20, arg1, arg2, arg0->unk180);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005B8FC);

void func_8005B904(Unk_8005B904 *arg0) {
    Unk_8005B904_B50 *src = arg0->unk14;

    arg0->unk890 = *src;
    arg0->unk8E0 = *src->unk44;
}

void func_8005B990(Unk_8005B904 *arg0) {
    Unk_8005B904_B50 *dst = arg0->unk14;

    *dst = arg0->unk890;
    *dst->unk44 = arg0->unk8E0;
    dst->unk0 = 0;
}

s32 func_8005BA20(Unk_8005BA20 *arg0, s32 arg1) {
    s32 temp;

    if (arg1 < 0) {
        return arg0->u924;
    }
    temp = arg0->u924;
    arg0->u924 = arg1;
    return temp;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BA40);

void func_8005BA50(u8 *arg0, s32 *arg1) {
    s32 i;
    for (i = 29; i >= 0; i--) {
        arg0[i] = 0;
    }
    D_8008ACB4 = arg0;
    *arg1 = 0;
    D_8008ACB8 = arg1;
}

s32 func_8005BA7C(void) {
    s32 i;
    s32 sum = 0;

    for (i = 0; i < 30; i++) {
        if (((s8 *)D_8008ACB4)[i] != 0) {
            sum += 1000000;
        }
    }
    if (sum > 29999999) {
        sum = 50000000;
    }
    sum -= *D_8008ACB8 * 11024;
    if (sum < 0) {
        sum = 0;
    }
    return sum;
}

s16 func_8005BB14(s32 arg0) {
    return D_80087F14[arg0];
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BB30);

void func_8005BCB4(void *arg0, void *arg1, s32 arg2) {
    func_8005C150(arg0, arg1, arg2, D_80088748, D_80088710, D_80088664, 1);
}

s32 func_8005BCF8(void *arg0, s16 *arg1, s32 arg2) {
    return func_8005C150(arg0, arg1, arg2, D_800889F0, D_80088980, D_80088820, 1);
}

s32 func_8005BD3C(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2) {
    u8 temp;

    temp = D_800889B8[D_8008ACBC][D_8008ACC0];
    if (func_8005BE28(arg2, temp) != 0) {
        if (arg1 != NULL) {
            *arg1 = D_80088758 + temp * 12;
        }
        if (arg0 != NULL) {
            *arg0 = D_80088758 + D_80088858[D_8008ACC4][D_8008ACC8] * 12;
        }
        return 1;
    }
    return 0;
}

s32 func_8005BE28(Unk_8005BE28 *arg0, u8 arg1) {
    s32 diff = arg0->u4 - D_8008875C[arg1 * 6];
    s16 temp = diff;
    s16 var_a1;

    var_a1 = diff;
    if (temp > 0xB4) {
        var_a1 -= 0x168;
    } else if (temp < -0xB4) {
        var_a1 += 0x168;
    }
    return (u16)(var_a1 + 0x2C) < 0x59U;
}

s32 func_8005BE90(void *arg0, s32 arg1, Unk_8005BE90 *arg2, s32 arg3) {
    s32 ret;

    if (arg1 != 3 && arg1 != 1 && arg1 != 5 && arg1 != 9 && arg1 != 12) {
        return -1;
    }
    if (arg1 == 5) {
        if (arg2->unk6 >= -0xFFF && arg2->unk0 != D_8008ABE8) {
            return -1;
        }
    } else if (arg1 == 9) {
        if (arg2->unk6 < 0x800) {
            return -1;
        }
    }
    if (arg3 & 1) {
        arg1 = -12;
    }
    ret = func_8005BB30(arg0, arg1, arg3);
    D_8008ACC4 = ret;
    return ret;
}

s32 *func_8005BF48(void) {
    s32 *r = NULL;
    if (D_8008ACC4 != 12) {
        r = D_8008ABF0;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005BF68);

s32 func_8005BF74(void *arg0, void *arg1, s32 arg2) {
    if (D_8008ABE4 != 0) {
        return func_8005C150(arg0, arg1, arg2, &D_80088B5C, &D_80088B24, &D_80088A80, 0);
    }
    return -1;
}

s32 func_8005BFC4(void) {
    return D_8008ACBC == 0 ? 10 : 0;
}

s32 func_8005BFDC(void *arg0, void *arg1, s32 arg2) {
    if (arg2 == 0) {
        return func_8005C150(arg0, arg1, 0, D_80088CBC, D_80088C4C, (s32 *)D_80088BA4, 0);
    }
    return -1;
}

s32 func_8005C02C(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2) {
    u8 temp_s0;

    temp_s0 = D_80088C84[D_8008ACBC][D_8008ACC0];
    if (func_8005BE28(arg2, temp_s0) != 0) {
        if (arg1 != 0) {
            *arg1 = D_80088758 + temp_s0 * 12;
        }
        if (arg0 != 0) {
            *arg0 = D_80088758 + D_80088BDC[D_8008ACC4][D_8008ACC8] * 12;
        }
        return 1;
    }
    return 0;
}

s32 func_8005C118(void) {
    return D_80088BA4[D_8008ACC4][D_8008ACC8].u5;
}

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005C150);

INCLUDE_ASM("asm/nonmatchings/game/80058078", func_8005C28C);

s32 func_8005C438(void *arg0, s32 arg1) {
    Unk_8005C438 *o = arg0;
    s32 i;

    for (i = 0; i < sizeof(D_80088CCC) / sizeof(D_80088CCC[0]); i++) {
        if (arg1 == D_80088CCC[i]) {
            o->unk2 = rand() % 6;
            o->unk0 = i % 12;
            return (s32) &D_8008ABF4;
        }
    }
    return 0;
}

#include "common.h"

extern void func_800183DC(void *, s32);
typedef struct { u8 p0[0x24]; u32 u24; u8 p1[0x70 - 0x28]; s32 u70; s32 u74; u8 p2[0x120 - 0x78]; u32 u120; s32 u124; } Unk_80059394;
typedef struct Unk_80089EA4 {
    u8 pad[0x8];
    s8 unk8;
    u8 pad9[0x7];
} Unk_80089EA4;
extern Unk_80089EA4 D_80089EA4[];
typedef struct Unk_8005D944 { u8 pad[0x98]; s32 unk98; } Unk_8005D944;
typedef struct Unk_80063CAC {
    u8 pad[0x10];
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
s32 func_80065C5C(void);
typedef struct Unk_80065C2C {
    u8 pad[0x5C];
    s32 u5C;
} Unk_80065C2C;
extern void func_80065CEC(void);
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
    u8 pad[0x200];
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
    u8 pad[0x10];
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
    u8 pad[0x50];
    void (*unk50)(void *);
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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005C650);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005C7D4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005C8AC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005C930);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005C9DC);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005CF34);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005CFDC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D068);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D108);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D1EC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D278);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D314);

void func_8005D418(Unk_8005D418 *arg0) {
    if (arg0->unkC != 0) {
        arg0->unk0->unk160(arg0);
        func_80066818()->unk50(arg0);
        arg0->unk4C = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D480);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D560);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D658);

void func_8005D6D4(Unk_8005D6D4 *arg0) {
    func_8002CD08(arg0->u58, &arg0->u9C);
    arg0->uFC++;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D714);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005D864);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DA3C);

void func_8005DAAC(Unk_8005DAAC *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->unk0->unk30(arg0, 9);
    }
    arg0->unkF4 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DAFC);

void func_8005DB8C(Unk_8005DB8C *arg0) {
    func_8002CC84(arg0->unk58, &arg0->unk9C);
    arg0->unk0->unk130(arg0);
    arg0->unk0->unk114(arg0);
    arg0->unkF8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DBF0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DD18);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DE18);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DEE0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005DF9C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E02C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E0B0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E150);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E160);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E3C4);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005E6F0);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005EBB4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005EC98);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005EF54);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005EFF4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F0D8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F1A8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F1D4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F368);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F454);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F544);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005F608);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FDFC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FEC8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FEF8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8005FF7C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060148);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800602AC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800603C4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800604DC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800605D0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060710);

void func_800607F8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060800);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8006090C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060A4C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060B34);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80060CF0);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061E60);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80061F30);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8006204C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800620C4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800621A8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800623E8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800624BC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062570);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062660);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062730);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800628D4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062970);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062A40);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062C58);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80062FAC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063094);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063144);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800634A8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800636E4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063784);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063874);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063BC0);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063CC8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063D40);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063DC8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063E68);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80063ED4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064078);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800641C0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064294);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064450);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800644E8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064618);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800646D8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064928);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064AA4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80064B14);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800650F4);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800654A0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065514);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800655D4);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065650);

void func_8006573C(Unk_8006573C_Obj **arg0) {
    (*arg0)->unkF8(arg0);
    func_80057C84()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065790);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065830);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065918);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800659D0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065A5C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065AE0);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065B80);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065C5C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065CEC);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80065FD8);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800660BC);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_8006613C);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80066148);

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_80066150);

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

INCLUDE_ASM("asm/nonmatchings/game/8005C508", func_800662BC);

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

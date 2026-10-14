#include "common.h"

typedef struct { u8 pad[0x74]; s16 u74; s16 u76; u8 pad2[0xAC - 0x78]; } Unk_800305F4;
extern Unk_800305F4 *D_800902E8[];
/* One bss record of 0x20 bytes (config/symbol_addrs.txt): bytes up to 0x15, then s16 fields. */
typedef struct { u8 u0[0x16]; s16 u16; s16 u18; s16 u1A; s16 u1C; s16 u1E; } Unk_8008EA0C;
extern Unk_8008EA0C D_8008EA0C;
typedef struct { u8 pad[0x60]; s32 unk60; } Unk_8002CBF4;
s32 D_8008A8B0;
s32 D_8008A8B4;
u8 func_800300D0(s16 arg0, s16 arg1, s16 arg2, u16 arg3);
typedef struct Unk_8002C238 { u8 pad[0x30]; s32 unk30; } Unk_8002C238;
typedef struct { u8 pad[0x64]; void (*unk64)(Unk_8002C238 *); } Unk_8002C238_vt;
void *func_80026CAC(void);
void func_80031890(s16 arg0);
void func_80031F3C(s32 arg0);
typedef struct { u8 pad[0x56]; s16 unk56; } Unk_8002CB9C;
void SsSetMute(s16 arg0);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C12C);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C18C);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C200);

void func_8002C238(Unk_8002C238 *arg0) {
    arg0->unk30 = 1;
    ((Unk_8002C238_vt *)func_80026CAC())->unk64(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C278);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C3A8);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C3B8);

void func_8002C3C0(void) {
}

void func_8002C3C8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C3D0);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C3E0);

void func_8002C3F0(void) {
}

void func_8002C3F8(void) {
}

void func_8002C400(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C408);

void func_8002C410(void) {
}

void func_8002C418(void) {
}

void func_8002C420(void) {
}

void func_8002C428(void) {
}

void func_8002C430(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C438);

s32 func_8002C448(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = D_8008A8B4;
    }
    return D_8008A8B0;
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C468);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C478);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C480);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C4E0);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C638);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C6FC);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C824);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C890);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CA3C);

s32 func_8002CB18(s32 arg0, s32 arg1) {
    if (arg1 < 0x18) {
        func_80031890(arg1);
    } else {
        func_80031F3C(0);
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CB58);

void func_8002CB9C(Unk_8002CB9C *arg0) {
    if (arg0->unk56 != 0) {
        SsSetMute(0);
        arg0->unk56 = 0;
    }
}

void func_8002CBDC(void) {
}

void func_8002CBE4(void) {
}

void func_8002CBEC(void) {
}

void func_8002CBF4(Unk_8002CBF4 *arg0, s32 arg1) {
    arg0->unk60 = arg1 * 12 - 24;
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CC0C);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CC1C);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CC28);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CC34);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CC84);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CD08);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002CF18);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002D1B4);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002D6A4);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002D8E0);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002DDBC);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002DF7C);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002E038);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002E138);

void func_8002E2F8(void) {
}

void func_8002E300(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002E308);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002E4D8);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002E874);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002EA44);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002EDD4);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002F20C);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002F2A4);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002F368);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002F3E8);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002F610);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002F700);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002FAC4);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_800300D0);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_800302DC);

void func_800303C8(s16 arg0, s16 arg1, u16 arg2) {
    func_800300D0(0x21, arg0, arg1, arg2);
}

void func_800303FC(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_80030404);

s32 func_80030584(s32 arg0, s16 *arg1, s16 *arg2) {
    Unk_800305F4 *t = D_800902E8[arg0 & 0xFF];
    s16 *p = &D_8008EA0C.u16;
    *p = arg0;
    *arg1 = t[(arg0 & 0xFF00) >> 8].u74;
    *arg2 = t[(arg0 & 0xFF00) >> 8].u76;
    return *p;
}

s32 func_800305F4(s32 arg0) {
    s32 lo = arg0 & 0xFF;
    s32 hi = (arg0 & 0xFF00) >> 8;
    Unk_800305F4 *p = &D_800902E8[lo][hi];
    D_8008EA0C.u16 = lo;
    return p->u74;
}

s32 func_80030648(s32 arg0) {
    Unk_800305F4 *t = D_800902E8[arg0 & 0xFF];
    D_8008EA0C.u16 = arg0;
    return t[(arg0 & 0xFF00) >> 8].u76;
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8003069C);

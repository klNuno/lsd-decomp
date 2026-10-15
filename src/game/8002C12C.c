#include "common.h"

typedef struct { u8 pad[0x74]; s16 u74; s16 u76; u8 pad2[0xAC - 0x78]; } Unk_800305F4;
extern Unk_800305F4 *D_800902E8[];
/* One bss record of 0x20 bytes (config/symbol_addrs.txt): bytes up to 0x15, then s16 fields. */
typedef struct Unk_8008EA0C {
    u8 unk0[0x16];
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
} Unk_8008EA0C;
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
typedef struct { u8 pad[0xC]; void (*unkC)(s32); } Unk_8002C200;
typedef struct Unk_8002CB58 { u8 pad[0x56]; s16 unk56; } Unk_8002CB58;
typedef struct { s32 unk0; s32 unk4[4]; } Unk_8002CC34_Entry;
typedef struct Unk_8002CC34 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    Unk_8002CC34_Entry entries[3];
} Unk_8002CC34;
typedef struct Unk_8002C12C {
    /* 0x00 */ u8 pad_00[0x8];
    /* 0x08 */ void (*unk8)(void *, s32);
    /* 0x0C */ u8 pad_0C[0x60];
    /* 0x6C */ void (*unk6C)(void *, s32);
} Unk_8002C12C;
void *func_80017B34(s32 size);
Unk_8002C12C *func_8002C3A8(void);
typedef struct Unk_8002C480_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32);
} Unk_8002C480_vt;
Unk_8002C480_vt *func_8002CC0C(void);
typedef struct Unk_8002C824_vt {
    u8 pad_00[0x7C];
    void (*unk7C)(void *);
} Unk_8002C824_vt;
typedef struct Unk_8002C824 {
    Unk_8002C824_vt *unk0;
    u8 pad_04[0x54];
    s16 unk58;
    u16 unk5A;
} Unk_8002C824;
s16 SsVabTransCompleted(s16 immediateFlag);
typedef struct Unk_8002C18C {
    Unk_8002C12C *unk0;
    u8 pad_04[0x28];
    s32 unk2C;
    s32 unk30;
} Unk_8002C18C;
typedef struct Unk_8002C18C_sys_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8002C18C_sys_vt;
typedef struct Unk_8002CC84_vt {
    u8 pad_00[0x84];
    s32 (*unk84)(void *, s32);
} Unk_8002CC84_vt;
typedef struct Unk_8002CC84 {
    Unk_8002CC84_vt *vt;
} Unk_8002CC84;
extern u8 D_8008E9D0;
s32 func_8002CF18(s32 arg0);
void func_8002DDBC(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_8002C12C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = (s32)func_80017B34(0x34);
    if (temp_v0 != 0) {
        func_8002C3A8()->unk8((void *)temp_v0, arg0);
        return temp_v0;
    }
    return 0;
}

void func_8002C18C(Unk_8002C18C *arg0, s32 arg1) {
    ((Unk_8002C18C_sys_vt *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = func_8002C3A8();
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    if (arg1 != 0) {
        arg0->unk0->unk6C(arg0, arg1);
    }
}

void func_8002C200(s32 arg0) {
    ((Unk_8002C200 *)func_80026CAC())->unkC(arg0);
}

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

void *func_8002C480(s32 arg0) {
    void *temp;

    temp = func_80017B34(0x64);
    if (temp != 0) {
        func_8002CC0C()->unk8(temp, arg0);
        return temp;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C4E0);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C638);

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002C6FC);

s32 func_8002C824(Unk_8002C824 *arg0, s32 arg1) {
    s32 ret = 0;

    if (arg0->unk5A != 0) {
        if (arg1 != 0) {
            SsVabTransCompleted(1);
            arg0->unk5A = 0;
            arg0->unk58 = 1;
            arg0->unk0->unk7C(arg0);
            ret = 1;
        }
    }
    return ret;
}

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

void func_8002CB58(Unk_8002CB58 *arg0) {
    if (arg0->unk56 == 0) {
        SsSetMute(1);
        arg0->unk56 = 1;
    }
}

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

s32 func_8002CC34(s32 arg0, Unk_8002CC34 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk_8002CC34_Entry *entry;
    s32 none;
    s32 i;

    if (arg1->unk0 != 0) {
        return 0;
    }
    entry = arg1->entries;
    none = -1;
    arg1->unk0 = arg2;
    arg1->unk8 = arg3;
    arg1->unkC = arg4;
    for (i = 2; i >= 0; i--) {
        entry->unk0 = none;
        entry++;
    }
    arg1->unk4 = 0;
    arg1->unk14 = 0xA;
    return 1;
}

void func_8002CC84(Unk_8002CC84 *arg0, Unk_8002CC34 *arg1) {
    Unk_8002CC34_Entry *entry;
    s32 i;

    entry = arg1->entries;
    for (i = 0; i < 3; i++, entry++) {
        if (entry->unk0 >= 0) {
            entry->unk0 = arg0->vt->unk84(arg0, entry->unk0);
        }
    }
    arg1->unk0 = 0;
}

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

void func_8002F20C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_v0;

    D_8008EA0C.unk0[0xF] = 0x7F;
    temp_v0 = func_8002CF18(0xFF) & 0xFF;
    D_8008EA0C.unk1A = temp_v0;
    if (temp_v0 < D_8008E9D0) {
        func_8002DDBC((u8) D_8008EA0C.unk1A, arg0 & 0xFFFF, arg1 & 0xFFFF, arg2 & 0xFFFF, arg3 & 0xFFFF);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8002F2A4);

void func_8002F368(s32 arg0, s32 arg1) {
    s32 temp;

    D_8008EA0C.unk0[0xF] = 0x7F;
    temp = func_8002CF18(0xFF) & 0xFF;
    D_8008EA0C.unk1A = temp;
    if (temp < D_8008E9D0) {
        func_8002DDBC((u8) D_8008EA0C.unk1A, arg0 & 0xFFFF, arg1 & 0xFFFF, 0x80FF, 0x5FC8);
    }
}

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
    s16 *p = &D_8008EA0C.unk16;
    *p = arg0;
    *arg1 = t[(arg0 & 0xFF00) >> 8].u74;
    *arg2 = t[(arg0 & 0xFF00) >> 8].u76;
    return *p;
}

s32 func_800305F4(s32 arg0) {
    s32 lo = arg0 & 0xFF;
    s32 hi = (arg0 & 0xFF00) >> 8;
    Unk_800305F4 *p = &D_800902E8[lo][hi];
    D_8008EA0C.unk16 = lo;
    return p->u74;
}

s32 func_80030648(s32 arg0) {
    Unk_800305F4 *t = D_800902E8[arg0 & 0xFF];
    D_8008EA0C.unk16 = arg0;
    return t[(arg0 & 0xFF00) >> 8].u76;
}

INCLUDE_ASM("asm/nonmatchings/game/8002C12C", func_8003069C);

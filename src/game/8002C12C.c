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
u8 SpuVmKeyOff(s16 arg0, s16 arg1, s16 arg2, u16 arg3);
typedef struct Unk_8002C238 { u8 pad[0x30]; s32 unk30; } Unk_8002C238;
typedef struct { u8 pad[0x64]; void (*unk64)(Unk_8002C238 *); } Unk_8002C238_vt;
void *func_80026CAC(void);
void SsUtKeyOffV(s16 arg0);
void SsUtAllKeyOff(s32 arg0);
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
    u8 pad_00[0x80];
    s32 (*unk80)(void *, s32, s32, s32);
    s32 (*unk84)(void *, s32);
    u8 pad_88[0x14];
    void (*unk9C)(void *, s32);
} Unk_8002CC84_vt;
typedef struct Unk_8002CC84 {
    Unk_8002CC84_vt *vt;
} Unk_8002CC84;
extern u8 D_8008E9D0;
s32 SpuVmAlloc(s32 arg0);
void vmNoiseOn2(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
/* copied from src/game/8002C12C.c */
extern u16 D_8006DAD8[];
typedef struct Unk_8002C638 {
    u8 pad_00[0x4C];
    s32 unk4C;
    s32 unk50;
    s16 unk54;
    u8 pad_56[0x6];
    s32 unk5C;
} Unk_8002C638;
s32 D_8008A8B8;
s32 D_8008A8BC;
s32 D_8008A8C0;
s32 D_8008A8C4;
void SsVabClose(s16 arg0);
s32 func_8003A05C(void);
void func_800329D8(void);
void func_80032A7C(void);
void func_80017CFC(s32 arg0);
typedef struct Unk_8002F2A4 {
    u8 pad_00[0x194];
    s16 unk194;
    s16 unk196;
} Unk_8002F2A4;
extern u8 D_8008D98C[];
extern u8 D_8008D9A3[];
extern Unk_8002F2A4 *D_8006DAD4;
void SpuVmVSetUp(s16 arg0, s16 arg1);
s16 SpuVmPBVoice(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
typedef struct Unk_8002E038 {
    u8 pad_00[0x4];
    u8 unk4;
    u8 unk5;
    u8 pad_06[0x1A];
} Unk_8002E038;
extern Unk_8002E038 *D_8008E978;
typedef struct Unk_8002C6FC_vt {
    u8 pad_00[0x58];
    void (*unk58)(void *, void *, s32);
    u8 pad_5C[0x1C];
    void (*unk78)(void *, s32);
} Unk_8002C6FC_vt;
typedef struct Unk_8002C6FC {
    /* 0x00 */ Unk_8002C6FC_vt *unk0;
    /* 0x04 */ u8 pad_04[0xC];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad_14[0x10];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 pad_28[0x2];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u8 pad_2C[0x28];
    /* 0x54 */ s16 unk54;
    /* 0x56 */ u8 pad_56[0x4];
    /* 0x5A */ u16 unk5A;
    /* 0x5C */ s32 unk5C;
} Unk_8002C6FC;
extern s8 D_8008A8D4[];
s32 D_8008A8C8;
s16 SsVabOpenHead(void *vh, s16 vabid);
s16 SsVabTransBody(void *vb, s16 vabid);
s8 *func_800270C4(s8 *arg0, s8 *arg1, s8 *arg2, s8 *arg3);
typedef struct Unk_8002C278_rec {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    s32 unk8;
} Unk_8002C278_rec;
typedef struct Unk_8002C278_vt {
    u8 pad_00[0x80];
    s32 (*unk80)(void *, u16, s32, void *);
} Unk_8002C278_vt;
typedef struct Unk_8002C278_obj {
    Unk_8002C278_vt *vt;
} Unk_8002C278_obj;
typedef struct Unk_8002C278_ctx {
    u8 pad_00[0x10];
    u8 *unk10;
    u8 pad_14[0x18];
    Unk_8002C278_obj *unk2C;
} Unk_8002C278_ctx;
typedef struct Unk_8002C278 {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad_18[0x2];
    s16 unk1A;
    u8 pad_1C[0x10];
    s16 unk2C;
    s16 unk2E;
    s32 unk30;
    s32 unk34;
    s32 unk38;
} Unk_8002C278;
typedef struct Unk_8002C4E0_sys_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8002C4E0_sys_vt;
typedef struct Unk_8002C4E0_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32);
    u8 pad_0C[0x60];
    void (*unk6C)(void *, s8 *);
    u8 pad_70[0x2C];
    void (*unk9C)(void *, s32);
} Unk_8002C4E0_vt;
typedef struct Unk_8002C4E0 {
    /* 0x00 */ Unk_8002C4E0_vt *unk0;
    /* 0x04 */ u8 pad_04[0x26];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u8 pad_2C[0x20];
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ u16 unk5A;
    /* 0x5C */ s32 unk5C;
} Unk_8002C4E0;
s32 D_8008A8CC;
extern s8 D_8008A8D0[];
void func_80032368(void);
s32 func_8003A068(void);
void SsSetTableSize(s8 *arg0, s16 arg1, s16 arg2);
void func_80032588(s32 arg0);
s32 strlen(u8 *s);
s8 *strcpy(s8 *dst, s8 *src);
void SpuVmKeyOn(s32 arg0, s16 arg1, s16 arg2, u16 arg3, u16 arg4, u16 arg5);
/* Only unk16 is used here: the asm stores the arg0 halfword at D_8008EA0C + 0x16. */
typedef struct { s16 s0; u8 pad[0x34 - 2]; } Unk_8008D996;
extern Unk_8008D996 D_8008D996[];
extern u8 D_8008D7F0[];
extern u8 D_8008D970[];
extern Unk_8002C12C D_8006D940;
extern u8 D_8006D9BC[];
extern Unk_8002C480_vt D_8006DA34;
extern u8 D_8008D9B0[];
extern u8 D_8008D9B2[];
extern u8 D_8008D9B4[];
extern u8 D_8008D9B6[];
extern u8 D_8008D9B8[];
extern u8 D_8008D9BA[];
typedef struct Unk_8002C890_vt {
    u8 pad_00[0x5C];
    void (*unk5C)(void);
} Unk_8002C890_vt;
typedef struct Unk_8002C890 {
    Unk_8002C890_vt *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    u8 pad_14[0x18];
    u8 unk2C[0x12];
    u16 unk3E;
    u16 unk40;
    u8 pad_42[0xA];
    u8 *unk4C;
    u8 **unk50;
    s16 unk54;
    u8 pad_56[0x2];
    u16 unk58;
} Unk_8002C890;
s16 SsUtGetVabHdr(s16 vabId, void *vabhdr);
s16 SsUtGetProgAtr(s16 vabId, s16 progNum, u8 *progatr);
s16 SsUtGetVagAtr(s16 vabId, s16 progNum, s16 toneNum, u8 *vagatr);
void func_80032998(void);
void SsSetMVol(s16 voll, s16 volr);
typedef struct Unk_8002CA3C_Tone {
    u8 pad_00[4];
    u8 unk4;
    u8 unk5;
    u8 pad_06[0x1A];
} Unk_8002CA3C_Tone;
typedef struct Unk_8002CA3C {
    u8 pad_00[0x50];
    Unk_8002CA3C_Tone **unk50;
    s16 unk54;
    u8 pad_56[0xA];
    u16 unk60;
} Unk_8002CA3C;
s16 SsUtKeyOn(s16 vabId, s16 prog, s16 tone, s16 note, s16 fine, s16 voll, s16 volr);
s16 SsUtAutoVol(s16 vc, s16 start_vol, s16 end_vol, s16 delta_time);

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

s32 func_8002C278(Unk_8002C278_ctx *arg0, Unk_8002C278 *arg1, s32 arg2) {
    Unk_8002C278_rec *rec;
    s32 next;
    u16 id;
    s32 val6;
    u8 *base;

    if (arg2 < 0x190) {
        next = arg1->unk34;
        if (next != 0) {
            base = arg0->unk10;
            rec = (Unk_8002C278_rec *)(base + next);
            arg1->unk30 = 1;
        } else {
            rec = (Unk_8002C278_rec *)(arg2 * 0xC + 8 + arg0->unk10);
            arg1->unk30 = 0;
        }
        arg1->unk34 = rec->unk8;
        if (rec->unk0 != 0) {
            arg1->unkC = ((arg2 % 20) << 0xB) + 0x400;
            val6 = rec->unk6;
            arg1->unk14 = ((arg2 / 20) << 0xB) + 0x400;
            arg1->unk10 = val6 << 0xB;
            arg1->unk1A = rec->unk5 << 0xA;
            arg1->unk2C = rec->unk1;
            arg1->unk2E = rec->unk4;
            id = rec->unk2;
            arg1->unk38 = id;
            return arg0->unk2C->vt->unk80(arg0->unk2C, id, arg2, arg1);
        }
        return -1;
    }
    return 0;
}

Unk_8002C12C *func_8002C3A8(void) {
    return &D_8006D940;
}

s32 func_8002C3B8(void) {
    return 0;
}

void func_8002C3C0(void) {
}

void func_8002C3C8(void) {
}

void func_8002C3D0(void) {
    u8 buf[0x40];
}

void func_8002C3E0(void) {
    u8 buf[0x40];
}

void func_8002C3F0(void) {
}

void func_8002C3F8(void) {
}

void func_8002C400(void) {
}

s32 func_8002C408(void) {
    return 0;
}

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

void *func_8002C438(void) {
    return D_8006D9BC;
}

s32 func_8002C448(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = D_8008A8B4;
    }
    return D_8008A8B0;
}

s32 func_8002C468(s32 arg0, s32 arg1) {
    D_8008A8B0 = arg0;
    D_8008A8B4 = arg1;
    return 1;
}

s32 func_8002C478(void) {
    return 0;
}

void *func_8002C480(s32 arg0) {
    void *temp;

    temp = func_80017B34(0x64);
    if (temp != 0) {
        func_8002CC0C()->unk8(temp, arg0);
        return temp;
    }
    return 0;
}

void func_8002C4E0(Unk_8002C4E0 *arg0, s8 *arg1) {
    s8 sp10[0x20];
    s8 *temp;

    ((Unk_8002C4E0_sys_vt *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = (Unk_8002C4E0_vt *)func_8002CC0C();
    arg0->unk4C = 0;
    arg0->unk50 = 0;
    arg0->unk54 = 0;
    arg0->unk56 = 0;
    arg0->unk0->unk9C(arg0, 0);
    arg0->unk58 = 0;
    arg0->unk5A = 0;
    arg0->unk5C = 0;
    if (D_8008A8B8 == 0) {
        func_80032368();
        D_8008A8B8 = 1;
        SsSetTableSize((s8 *)func_8003A068(), 2, 1);
    }
    if (D_8008A8BC == 0) {
        D_8008A8CC = 0x3C;
        func_80032588(1);
        D_8008A8BC = 1;
    }
    D_8008A8C4 += 1;
    if (arg1 != 0) {
        temp = func_80017B34(strlen((u8 *)arg1) + 1);
        if (temp != NULL) {
            arg0->unk5C = (s32)temp;
            strcpy(temp, arg1);
            func_800270C4(sp10, temp, (s8 *)0, D_8008A8D0);
            arg0->unk2A = 1;
            arg0->unk0->unk6C(arg0, sp10);
        }
    }
}

void func_8002C638(Unk_8002C638 *arg0) {
    SsVabClose(arg0->unk54);
    if (--D_8008A8C4 < 0) {
        D_8008A8C4 = 0;
    }
    if (D_8008A8C4 == 0 && func_8003A05C() == 0) {
        D_8008A8B8 = 0;
        D_8008A8C0 = 0;
        D_8008A8BC = 0;
        func_800329D8();
        func_80032A7C();
    }
    func_80017CFC(arg0->unk4C);
    func_80017CFC(arg0->unk50);
    func_80017CFC(arg0->unk5C);
    ((Unk_8002C200 *)func_80026CAC())->unkC((s32)arg0);
}

void func_8002C6FC(Unk_8002C6FC *arg0) {
    u8 sp10[0x20];
    s32 old;
    s16 ret;

    switch (arg0->unk2A) {
        case 0:
            break;
        case 1:
            if (arg0->unk24 & 0x200) {
                arg0->unk54 = SsVabOpenHead((void *)arg0->unk10, -1);
                func_800270C4((s8 *)sp10, (s8 *)arg0->unk5C, (s8 *)0, D_8008A8D4);
                arg0->unk2A = 6;
                old = arg0->unk10;
                arg0->unk10 = 0;
                D_8008A8C8 = old;
                arg0->unk0->unk58(arg0, sp10, old);
                if (arg0->unk5C != 0) {
                    func_80017CFC(arg0->unk5C);
                    arg0->unk5C = 0;
                }
            }
            break;
        case 6:
            if (arg0->unk24 & 0x200) {
                ret = SsVabTransBody((void *)arg0->unk10, arg0->unk54);
                arg0->unk54 = ret;
                if (ret != -1) {
                    arg0->unk5A = 1;
                    arg0->unk0->unk78(arg0, 1);
                }
            }
            break;
    }
}

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

void func_8002C890(Unk_8002C890 *arg0) {
    s32 i;
    s32 j;
    u8 *vagp;
    u8 progAtr[0x10];

    if (arg0->unk58 == 0) {
        return;
    }
    arg0->unk0->unk5C();
    arg0->unk10 = D_8008A8C8;
    if (SsUtGetVabHdr(arg0->unk54, &arg0->unk2C) == -1) {
        return;
    }
    arg0->unk4C = func_80017B34(arg0->unk40 << 5);
    if (arg0->unk4C == NULL) {
        return;
    }
    arg0->unk50 = (u8 **)func_80017B34(arg0->unk3E << 2);
    if (arg0->unk50 == NULL) {
        return;
    }
    vagp = arg0->unk4C;
    for (i = 0; i < arg0->unk3E; i++) {
        arg0->unk50[i] = vagp;
        if (SsUtGetProgAtr(arg0->unk54, i, progAtr) == -1) {
            return;
        }
        for (j = 0; j < progAtr[0]; j++) {
            if (SsUtGetVagAtr(arg0->unk54, i, j, vagp) == -1) {
                return;
            }
            vagp += 0x20;
        }
    }
    if (D_8008A8C0 == 0) {
        func_80032998();
        SsSetMVol(0x78, 0x78);
        D_8008A8C0 = 1;
    }
}

s16 func_8002CA3C(Unk_8002CA3C *arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 prog;
    Unk_8002CA3C_Tone *t;
    s16 vc;

    if (arg1 < 0) {
        return -1;
    }
    prog = arg1 >> 4;
    t = arg0->unk50[prog];
    t += arg1 - (prog << 4);
    vc = SsUtKeyOn(arg0->unk54, prog, arg1 - (prog << 4), t->unk4 + arg0->unk60, t->unk5, arg2, arg2);
    if (vc < 0) {
        return -1;
    }
    SsUtAutoVol(vc, arg2, arg3, 2);
    return vc;
}

s32 func_8002CB18(s32 arg0, s32 arg1) {
    if (arg1 < 0x18) {
        SsUtKeyOffV(arg1);
    } else {
        SsUtAllKeyOff(0);
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

Unk_8002C480_vt *func_8002CC0C(void) {
    return &D_8006DA34;
}

s32 func_8002CC1C(void) {
    return D_8008A8C4;
}

s32 func_8002CC28(void) {
    return D_8008A8CC;
}

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

void func_8002CD08(Unk_8002CC84 *arg0, Unk_8002CC34 *arg1) {
    Unk_8002CC34_Entry *e;
    void (*cb)(s32, void *);
    s32 i;
    s32 slot;

    if (arg1->unk0 > 0) {
        for (e = arg1->entries, i = 0; i < 3; i++, e++) {
            e->unk4[0] = -1;
            e->unk4[1] = 0;
            e->unk4[2] = 0x7F;
            e->unk4[3] = 0x40;
        }
        cb = (void (*)(s32, void *)) arg1->unkC;
        arg1->unk10 = 0;
        if (cb != NULL) {
            cb(arg1->unk8, arg1);
        }
        if (arg1->unk10 >= 0) {
            for (e = arg1->entries, i = 0; i < 3; i++, e++) {
                if (e->unk4[0] >= 0) {
                    slot = e->unk0;
                    if (slot >= 0) {
                        arg0->vt->unk84(arg0, slot);
                    }
                    arg0->vt->unk9C(arg0, e->unk4[1]);
                    e->unk0 = arg0->vt->unk80(arg0, e->unk4[0] << 4, e->unk4[2] - (e->unk4[2] / arg1->unk14) * arg1->unk10, e->unk4[3] - (e->unk4[3] / arg1->unk14) * arg1->unk10);
                } else if (e->unk4[0] == -2) {
                    slot = e->unk0;
                    if (slot >= 0) {
                        arg0->vt->unk84(arg0, slot);
                    }
                }
            }
        }
        arg1->unk4++;
    }
}

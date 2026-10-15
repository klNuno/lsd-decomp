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
    u8 pad_6C[0x78 - 0x6C];
    s32 unk78;
    s32 unk7C;
} Unk_8004E3F4;
extern s32 EnableEvent();
extern void func_8004F40C(s32, s32 (*)(), s32);
s32 func_8004F4C8(s32 *arg0, s32 arg1);
extern s32 DisableEvent();
extern s32 TestEvent();
void func_8004B44C(s32 *arg0, s32 *arg1, Unk_800861D4 *arg2, s32 *arg3, void *arg4);
extern s32 CloseEvent();
void func_8004F3BC(s32 arg0);
typedef struct Unk_8004E40C { s32 unk0, unk4, unk8; void (*unkC)(s32); u8 pad_10[0x8]; void (*unk18)(void *); } Unk_8004E40C;
extern Unk_8004E40C *func_80018390(void);
typedef struct Unk_8004FFF4_vt { u8 pad[0x80]; void (*unk80)(void *, s32, s32, s32); } Unk_8004FFF4_vt;
typedef struct Unk_8004FFF4_obj { Unk_8004FFF4_vt *unk0; } Unk_8004FFF4_obj;
typedef struct Unk_8004FFF4 { u8 pad[0x6C]; Unk_8004FFF4_obj *unk6C; } Unk_8004FFF4;
typedef struct Unk_8004FF40_vt { u8 pad[4]; void *(*unk4)(void *); } Unk_8004FF40_vt;
typedef struct Unk_8004FF40_obj { Unk_8004FF40_vt *unk0; } Unk_8004FF40_obj;
typedef struct Unk_8004FF40 { u8 pad[0x70]; Unk_8004FF40_obj *unk70; } Unk_8004FF40;
s32 func_8004E7D0();
void func_8004E890(s32, s32, s32);
typedef struct Unk_8004DABC_mgr { u8 pad[0x94]; void (*unk94)(void *); u8 pad_98[0xDC - 0x98]; void (*unkDC)(void *); void (*unkE0)(void *, s32); } Unk_8004DABC_mgr;
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
s32 D_8008AA10;
s32 D_8008AA18;
typedef struct Unk_8004E2E0 {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32, s32);
} Unk_8004E2E0;
extern s32 func_80017B34(s32);
extern Unk_8004E2E0 *func_800507E8(void);
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
s32 func_8004EDC0(s32, s32, s32, s32);
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
s32 func_8004EA38(s32, s32, u8 *);
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

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011434);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011440);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011454);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011464);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011474);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_8001149C);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_800114DC);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D578);

void func_8004D678(P *arg0, Q *arg1) {
    A *a = arg0->uBC;
    s32 r = 1;
    if (a->uC > 9999999) {
        r = a->u2F4 == 0;
    }
    arg1->u18->u4 = r;
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D6AC);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D90C);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D9D4);

void func_8004DABC(Unk_8004DABC *arg0) {
    s32 sp10;
    Unk_8004DABC_obj *temp_a0;

    func_8003DFBC()->unk94(arg0);
    temp_a0 = arg0->unkA4;
    sp10 = arg0->unk60->unk14;
    temp_a0->vt->unk19C(temp_a0, &sp10);
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DB18);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DCD0);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DE08);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_800114F8);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DF64);

void func_8004E054(Unk_8004E054 *arg0) {
    arg0->unk0->unk10(arg0, arg0->unkC->unk4);
    arg0->unk0->unk10(arg0, arg0->unk10);
    arg0->unk0->unk14(arg0, arg0->unkAC);
    arg0->unkAC->unk0->unk70(arg0->unkAC);
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E0E4);

void func_8004E1C4(Unk_8004E1C4 *arg0) {
    arg0->unk0->unk128(arg0);
    arg0->unkAC->unk0->unk74(arg0->unkAC, D_8008AA10, D_8008AA18, arg0->unkBC, arg0->unkC0);
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E230);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E2D0);

s32 func_8004E2E0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x84);
    if (temp_v0 != 0) {
        func_800507E8()->unk8(temp_v0, arg0, arg1);
        return temp_v0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E34C);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E444);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E4E8);

void func_8004E588(Unk_8004E3F4 *arg0) {
    arg0->unk60 = 0;
    arg0->unk64 = 0;
    arg0->unk68 = 0;
    arg0->unk78 = 0;
    arg0->unk7C = 0;
    func_80018390()->unk18(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E5D4);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E6B8);

void func_8004E77C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_8004E7D0() != 0) {
        func_8004E890(arg0, arg1, arg3);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E7D0);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E890);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EA38);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EADC);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EB88);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EDC0);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EEA0);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_8001150C);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011518);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011524);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011530);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EF6C);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F32C);

void func_8004F394(s32 arg0) {
    func_8004F40C(arg0, EnableEvent, 1);
}

void func_8004F3BC(s32 arg0) {
    func_8004F40C(arg0, DisableEvent, 1);
}

void func_8004F3E4(s32 arg0) {
    func_8004F40C(arg0, TestEvent, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F40C);

void func_8004F4A4(s32 arg0) {
    func_8004F4C8(arg0 + 0x14, 4);
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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F638);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F8A4);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F9D8);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004FB04);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004FBE4);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004FE24);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_80050034);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_80050280);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_80050340);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_80050410);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_800504D0);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_800505A8);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_80050670);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_80050730);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_800507E8);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_800507F8);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_80011550);

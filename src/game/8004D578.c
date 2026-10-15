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
void func_8004F4C8(s32, s32);
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
typedef struct Unk_8004DABC_mgr { u8 pad[0x94]; void (*unk94)(void *); } Unk_8004DABC_mgr;
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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D704);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D788);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_800114E8);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D814);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004D898);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DC08);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DC64);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DCD0);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DE08);

INCLUDE_RODATA("asm/nonmatchings/game/8004D578", D_800114F8);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004DF64);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E054);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E0E4);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E1C4);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E230);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E2D0);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E2E0);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E5E4);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E940);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004E9AC);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EA38);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EADC);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EB88);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004EC5C);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004ECCC);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004ED40);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F4C8);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F55C);

void func_8004F5DC(Unk_8004F5DC *arg0) {
    arg0->unk6C = 0;
    arg0->unk68 = 0;
    arg0->unk0->unk14(arg0, arg0->unk60);
    arg0->unk0->unk14(arg0, arg0->unk64);
}

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F638);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F704);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F784);

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_8004F810);

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

INCLUDE_ASM("asm/nonmatchings/game/8004D578", func_800501F0);

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

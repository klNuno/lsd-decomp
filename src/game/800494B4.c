#include "common.h"

typedef struct { s16 unk_0; s16 unk_2; s32 unk_4; } Unk_800861D4;
extern Unk_800861D4 D_800861D4[];
extern s16 *D_80086590[];
typedef struct { u8 pad[0x74]; s32 u74; s16 u78; s16 u7A; } Unk_8004B32C;
typedef struct { u8 pad[0x32]; s16 id; } Obj;
typedef struct { s32 unk0; Obj *obj; u8 pad[0x14]; } Slot;
typedef struct { u8 pad[0xEC]; Slot slots[7]; } Owner;
typedef struct { u8 pad[0xC]; s32 uC; u8 pad2[0x2F4 - 0x10]; s32 u2F4; } A;
typedef struct { u8 pad[0xBC]; A *uBC; } P;
typedef struct { s32 u0; s32 u4; } C;
typedef struct { u8 pad[0x18]; C *u18; } Q;
typedef struct { u8 pad[0x60]; s32 u60, u64, u68, pad6C[3], u78, u7C; } Unk_8004E3F4;
extern s32 EnableEvent();
extern void func_8004F40C(s32, s32 (*)(), s32);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_800494B4);

Unk_800861D4 *func_800494BC(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 14;
    }
    return D_800861D4;
}

Unk_800861D4 *func_800494D8(s32 arg0) {
    return &func_800494BC(NULL)[arg0];
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004950C);

s16 *func_800495B8(s32 arg0, s8 *arg1) {
    return D_80086590[arg0] + arg1[1] * D_800861D4[arg0].unk_0 + arg1[0];
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049608);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049684);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049830);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049958);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049A14);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049A1C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049AC0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049B54);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049C50);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049CA8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049E20);

void func_80049EA4(void) {
}

void func_80049EAC(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80049EB4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A060);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A070);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A130);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A19C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A228);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A294);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A2C4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A324);

void func_8004A35C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A364);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A3EC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A458);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A478);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A4B8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A4C8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A534);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A7C0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004A984);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AA10);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AA6C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AB24);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AB88);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ABD0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ACF8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ADC4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ADD0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ADD8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AEA4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004AFE0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B030);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B100);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B2D4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B31C);

void func_8004B324(void) {
}

void func_8004B32C(Unk_8004B32C *arg0, s32 arg1) {
    arg0->u74 = arg1;
    arg0->u7A = arg1 >> 11;
    arg0->u78 = arg1 >> 12;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B344);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B38C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B418);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B44C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B570);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B57C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B5BC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B700);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B930);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BA40);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BB3C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BCE0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BD14);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BE54);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C0AC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C158);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C1C0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C368);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C3F0);

Slot *func_8004C434(Owner *arg0, s32 arg1) {
    s32 i;
    Slot *s;
    for (i = 0; i < 7; i++) {
        s = &arg0->slots[i];
        if (s->obj->id == arg1) {
            return s;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C470);

s32 func_8004C588(Owner *arg0, s32 arg1) {
    s32 found = 0;
    s32 i;
    Slot *s;
    for (i = 0; i < 7; i++) {
        s = &arg0->slots[i];
        if (s->obj->id == arg1) {
            found = i;
            break;
        }
    }
    return found;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C5D0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C620);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C6A8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004C93C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CAF0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CC74);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CD38);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CDA4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CE24);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CFA8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CFB0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004CFB8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D028);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D088);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D0D0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D108);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D140);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D1D0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D244);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D254);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D2A4);

void func_8004D2F8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D300);

void func_8004D35C(void) {
}

void func_8004D364(void) {
}

void func_8004D36C(void) {
}

void func_8004D374(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D37C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D38C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D3DC);

void func_8004D42C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D434);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D47C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D500);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D508);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D518);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D578);

void func_8004D678(P *arg0, Q *arg1) {
    A *a = arg0->uBC;
    s32 r = 1;
    if (a->uC > 9999999) {
        r = a->u2F4 == 0;
    }
    arg1->u18->u4 = r;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D6AC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D704);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D788);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D814);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D898);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D90C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004D9D4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004DABC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004DB18);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004DC08);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004DC64);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004DCD0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004DE08);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004DF64);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E054);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E0E4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E1C4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E230);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E2D0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E2E0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E34C);

void func_8004E3F4(Unk_8004E3F4 *arg0) {
    arg0->u60 = 0;
    arg0->u64 = 0;
    arg0->u68 = 0;
    arg0->u78 = 0;
    arg0->u7C = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E40C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E444);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E4E8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E588);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E5D4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E5E4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E678);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E6B8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E77C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E7D0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E890);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E940);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004E9AC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004EA38);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004EADC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004EB88);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004EC5C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ECCC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004ED40);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004EDC0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004EEA0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004EF6C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F32C);

void func_8004F394(s32 arg0) {
    func_8004F40C(arg0, EnableEvent, 1);
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F3BC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F3E4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F40C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F4A4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F4C8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F55C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F5DC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F638);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F704);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F784);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F810);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F8A4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004F9D8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004FB04);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004FBE4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004FE24);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004FF40);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004FF90);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004FFF4);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80050034);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_800501F0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80050280);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80050340);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80050410);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_800504D0);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_800505A8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80050670);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_80050730);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_800507E8);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_800507F8);

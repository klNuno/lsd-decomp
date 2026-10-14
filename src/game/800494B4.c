#include "common.h"

typedef struct { s16 unk_0; s16 unk_2; s32 unk_4; } Unk_800861D4;
extern Unk_800861D4 D_800861D4[];
extern s16 *D_80086590[];
typedef struct { u8 pad[0x74]; s32 u74; s16 u78; s16 u7A; } Unk_8004B32C;
typedef struct { u8 pad[0x32]; s16 id; } Obj;
typedef struct { s32 unk0; Obj *obj; u8 pad[0x14]; } Slot;
typedef struct { u8 pad[0xEC]; Slot slots[7]; } Owner;
extern void func_8004F40C(s32, s32 (*)(), s32);
typedef struct { u8 pad[0x2C]; s32 u2C; } Unk_8004A458;
void func_8004F4C8(s32, s32);
typedef struct { s16 pad[3]; s16 u6; } T;
typedef struct { u8 pad[0x1E0]; s32 u1E0; T *u1E4; } S;
extern T D_8008699C, D_800869A8, D_800869B4, D_800869C0;
typedef struct { u8 pad[0x54]; s32 u54[3]; u8 pad2[0x68 - 0x60]; Unk_800861D4 *u68; } Unk_8004B418;
void func_8004B44C(s32 *arg0, s32 *arg1, Unk_800861D4 *arg2, s32 *arg3, void *arg4);
typedef struct Unk_8004BCE0_Slot {
    u16 unk0;
    u8 pad_02[0x1C - 0x2];
} Unk_8004BCE0_Slot;
typedef struct Unk_8004BCE0 {
    u8 pad_00[0xEC];
    Unk_8004BCE0_Slot unkEC[7];
} Unk_8004BCE0;

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

INCLUDE_RODATA("asm/nonmatchings/game/800494B4", D_800113EC);

INCLUDE_RODATA("asm/nonmatchings/game/800494B4", D_800113F8);

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

void func_8004A458(Unk_8004A458 *arg0, s32 arg1) {
    arg0->u2C = arg1;
    if (arg1 >= 0) {
        arg0->u2C = arg1 * 20;
    }
}

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

void func_8004B418(Unk_8004B418 *arg0, s32 *arg1, void *arg2) {
    s32 sp18[3];
    func_8004B44C(arg1, sp18, arg0->u68, arg0->u54, arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B44C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B570);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B57C);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B5BC);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B700);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004B930);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BA40);

INCLUDE_ASM("asm/nonmatchings/game/800494B4", func_8004BB3C);

s32 func_8004BCE0(Unk_8004BCE0 *arg0) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (arg0->unkEC[i].unk0 != 0) {
            count++;
        }
    }
    return count;
}

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

void func_8004CFB8(S *arg0, s32 arg1, s32 arg2) {
    T *p;
    if (arg1 > 0) {
        p = &D_8008699C;
        if (arg2 != 0) {
            arg0->u1E4 = &D_800869A8;
        } else {
            arg0->u1E4 = p;
        }
    } else {
        p = &D_800869B4;
        if (arg2 != 0) {
            p = &D_800869C0;
        }
        arg0->u1E4 = p;
    }
    arg0->u1E0 = arg0->u1E4->u6 * (arg1 < 0 ? ~arg1 + 1 : arg1);
}

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

#include "common.h"

typedef struct Unk_80025C84_Vtbl {
    u8 pad[0x50];
    void (*unk50)(void *, s32);
} Unk_80025C84_Vtbl;
typedef struct Unk_80025C84 {
    Unk_80025C84_Vtbl *unk0;
    u8 pad4[0x8];
    s16 unkC;
    u8 padE[0x2];
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Unk_80025C84;
extern s32 PadRead(u16);
typedef struct Unk_80025C30 {
    u8 pad0[0xC];
    void (*unkC)(s32);
} Unk_80025C30;
void PadStop(void);
void *func_80018390(void);
s32 D_8008A848;
typedef struct Unk_80025B34 {
    u8 pad0[0x8];
    void (*unk8)(s32, s32, s32);
} Unk_80025B34;
s32 func_80017B34(s32);
Unk_80025B34 *func_80025E9C(void);
extern s32 D_8008B388[16];
typedef struct Unk_80025BA0_Base {
    u8 pad0[0x8];
    void (*unk8)(void *);
} Unk_80025BA0_Base;
typedef struct Unk_80025BA0_Vtbl {
    u8 pad0[0x40];
    void (*unk40)(void *, s32);
} Unk_80025BA0_Vtbl;
void PadInit(s32);
extern Unk_80025B34 D_8006D370;

s32 func_80025B34(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x20);
    if (temp_v0 != 0) {
        func_80025E9C()->unk8(temp_v0, arg0, arg1);
        return temp_v0;
    }
    return 0;
}

void func_80025BA0(Unk_80025BA0_Vtbl **arg0, s32 arg1, s32 arg2) {
    Unk_80025BA0_Vtbl *vt;
    s32 count;

    ((Unk_80025BA0_Base *)func_80018390())->unk8(arg0);
    vt = (Unk_80025BA0_Vtbl *)func_80025E9C();
    count = D_8008A848;
    *arg0 = vt;
    D_8008A848 = count + 1;
    if (count == 0) {
        PadInit(arg1);
    }
    (*arg0)->unk40(arg0, arg2);
}

void func_80025C30(s32 arg0) {
    if (--D_8008A848 == 0) {
        PadStop();
    }
    ((Unk_80025C30 *)func_80018390())->unkC(arg0);
}

void func_80025C84(Unk_80025C84 *arg0, s32 arg1) {
    s32 temp = arg1 != 0;
    arg0->unkC = temp;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk18 = 0;
    arg0->unk0->unk50(arg0, temp);
}

void func_80025CC4(Unk_80025C84 *arg0) {
    s32 cur;
    s32 prev;
    s32 changed;

    cur = PadRead(arg0->unkC);
    prev = arg0->unk10;
    arg0->unk10 = cur;
    changed = cur ^ prev;
    arg0->unk14 = changed & prev;
    arg0->unk18 = changed & cur;
}

INCLUDE_ASM("asm/nonmatchings/game/80025B34", func_80025D10);

void func_80025E14(void) {
}

void func_80025E1C(void) {
    s32 *dst = D_8008B388;
    s32 local[16] = {
        0x1000, 0x4000, 0x8000, 0x2000,
        0x10, 0x40, 0x80, 0x20,
        0x200, 0x400, 0x100, 0x8,
        0x2, 0x4, 0x1, 0x800,
    };
    s32 i;

    for (i = 0; i < 16; i++) {
        *dst++ = local[i];
    }
}

void func_80025E94(void) {
}

Unk_80025B34 *func_80025E9C(void) {
    return &D_8006D370;
}

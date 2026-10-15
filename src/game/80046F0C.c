#include "common.h"

void StFreeRing(void *ring);
void StUnSetRing(void);
extern void StClearRing(void);
extern s32 CdSync(s32, u8 *);
typedef struct Unk_800470C8 {
    u8 pad_00[0x2C];
    s32 unk2C;
    u8 pad_30[0x50 - 0x30];
    s32 unk50;
} Unk_800470C8;
extern void StSetRing(s32, u32);
void SpuSetCommonAttr(void *attr);
typedef struct Unk_80047240 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} Unk_80047240;
typedef struct Unk_80047074 {
    u8 pad_00[0x48];
    void (*unk48)(void *);
} Unk_80047074;
typedef struct Unk_80047074_Ret {
    u8 pad_00[0xC];
    void (*unkC)(void *);
} Unk_80047074_Ret;
Unk_80047074_Ret *func_80018390(void);
typedef struct Unk_80047574 Unk_80047574;
typedef struct Unk_80047574Vt {
    u8 pad_00[0x4C];
    void (*unk4C)(Unk_80047574 *self, void *arg);
} Unk_80047574Vt;
struct Unk_80047574 {
    Unk_80047574Vt *unk0;
    u8 pad_04[0xC - 0x4];
    u8 unkC[0x2C - 0xC];
    s32 unk2C;
};
Unk_80047574 *D_8008A950;
extern void CdSyncCallback(void *cb);
typedef struct Unk_80047388 {
    u8 pad_00[0x44];
    void *unk44;
    u8 pad_48[0x54 - 0x48];
    void (*unk54)(void *);
} Unk_80047388;
s32 CdControl(s32 com, u8 *param, s32 result);
typedef struct Unk_80047638 {
    u8 pad_00[0x30];
    s32 unk30;
} Unk_80047638;

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80046F0C);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80046F88);

void func_80047074(Unk_80047074 **arg0) {
    (*arg0)->unk48(arg0);
    func_80018390()->unkC(arg0);
}

void func_800470C8(Unk_800470C8 *arg0, s32 arg1, u32 arg2) {
    if (arg0->unk2C == 0) {
        StSetRing(arg1, arg2 >> 0xB);
        arg0->unk50 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047114);

s32 func_80047240(void) {
    Unk_80047240 attr;

    attr.unk0 = 0x2C3;
    attr.unk4 = 0x3FFF;
    attr.unk6 = 0x3FFF;
    attr.unk10 = 0x7FFF;
    attr.unk12 = 0x7FFF;
    attr.unk18 = 1;
    SpuSetCommonAttr(&attr);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_8004728C);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800472EC);

void func_80047388(u8 arg0) {
    Unk_80047388 *obj;

    if (D_8008A950 != NULL && arg0 == 2) {
        CdSyncCallback(0);
        obj = D_8008A950;
        if (obj->unk54 != NULL) {
            obj->unk54(obj->unk44);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800473E4);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800474C8);

void func_80047574(Unk_80047574 *arg0) {
    if (arg0->unk2C == 4 && D_8008A950 == arg0) {
        D_8008A950->unk2C = 0;
        D_8008A950->unk0->unk4C(D_8008A950, D_8008A950->unkC);
    }
}

void func_800475C8(void) {
}

void func_800475D0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800475D8);

void func_80047638(Unk_80047638 *arg0) {
    if (arg0->unk30 != 0 && D_8008A950 == arg0) {
        while (CdControl(0xC, 0, 0) == 0) {
        }
        arg0->unk30 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047694);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_800477B0);

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047810);

void func_80047870(s32 arg0, void *arg1) {
    StFreeRing(arg1);
}

void func_80047890(void) {
    StUnSetRing();
}

void func_800478B0(void) {
    StClearRing();
}

void func_800478D0(u8 *arg0, s32 arg1) {
    CdSync(arg1, arg0 + 0x24);
}

void func_800478F8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047900);

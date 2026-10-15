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
    u8 pad_50[0x64 - 0x50];
    void (*unk64)(Unk_80047574 *self);
    u8 pad_68[0x74 - 0x68];
    void (*unk74)(Unk_80047574 *self);
    void (*unk78)(Unk_80047574 *self);
} Unk_80047574Vt;
struct Unk_80047574 {
    Unk_80047574Vt *unk0;
    u8 pad_04[0xC - 0x4];
    u8 unkC[0x2C - 0xC];
    s32 unk2C;
    s32 unk30;
    u8 pad_34[0x54 - 0x34];
    void *unk54;
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
typedef struct Unk_8004728CVt {
    u8 pad_00[0x54];
    void (*unk54)(void *self);
} Unk_8004728CVt;
typedef struct Unk_800477B0Vt {
    u8 pad_00[0x70];
    void (*unk70)(void *self, void *arg);
} Unk_800477B0Vt;
typedef struct Unk_800477B0 Unk_800477B0;
struct Unk_800477B0 {
    Unk_800477B0Vt *unk0;
    u8 pad_04[0x44 - 0x04];
    void *unk44;
    void (*unk48)(void *);
};
typedef struct Unk_80047810 Unk_80047810;
typedef struct Unk_80047810Vt {
    u8 pad_00[0x48];
    void (*unk48)(Unk_80047810 *self);
} Unk_80047810Vt;
struct Unk_80047810 {
    Unk_80047810Vt *unk0;
    u8 pad_04[0x44 - 0x04];
    void *unk44;
    void (*unk48)(void *arg);
    s32 unk4C;
};
void *func_80017B34(s32 size);
typedef struct Unk_80046F0C {
    u8 pad_00[0x8];
    void (*unk8)(void *self, s32 arg0, s32 arg1, s32 arg2);
} Unk_80046F0C;
Unk_80046F0C *func_80047900(void);
s32 CdControlF(s32 com, u8 *param);
void func_80047388(u8 arg0);
typedef struct Unk_800473E4 Unk_800473E4;
typedef struct Unk_800473E4Vt {
    u8 pad_00[0x64];
    void (*unk64)(Unk_800473E4 *self);
    void (*unk68)(Unk_800473E4 *self);
} Unk_800473E4Vt;
struct Unk_800473E4 {
    Unk_800473E4Vt *unk0;
    u8 pad_04[0xC - 0x4];
    u8 unkC[0x2C - 0xC];
    s32 unk2C;
    u8 pad_30[0x34 - 0x30];
    s32 unk34;
    u8 pad_38[0x40 - 0x38];
    s32 unk40;
    u8 pad_44[0x58 - 0x44];
    s32 unk58;
};
s32 CdRead2(s32 mode);
void StSetStream(s32 a, s32 b, s32 c, s32 d, s32 e);

s32 func_80046F0C(s32 arg0, s32 arg1, s32 arg2) {
    void *temp;

    temp = func_80017B34(0x5C);
    if (temp != NULL) {
        func_80047900()->unk8(temp, arg0, arg1, arg2);
        return (s32)temp;
    }
    return 0;
}

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

void func_8004728C(Unk_80047574 *arg0) {
    Unk_80047574 *temp_s0;

    if (arg0->unk2C != 0) {
        temp_s0 = D_8008A950;
        if (temp_s0 == arg0) {
            ((Unk_8004728CVt *)temp_s0->unk0)->unk54(temp_s0);
            temp_s0->unk2C = 0;
            D_8008A950 = NULL;
        }
    }
}

void func_800472EC(Unk_80047574 *arg0, u8 *arg1) {
    if (arg0->unk2C != 2 && D_8008A950 == arg0) {
        if (arg0->unk54 != NULL) {
            CdSyncCallback((void *)func_80047388);
            CdControlF(0x15, arg1);
        } else {
            while (CdControl(0x15, arg1, 0) == 0) {
            }
        }
        arg0->unk2C = 1;
    }
}

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

void func_800473E4(Unk_800473E4 *arg0, s32 arg1, s32 arg2) {
    s32 var_s1;

    if (arg0->unk2C == 1 && (Unk_800473E4 *)D_8008A950 == arg0) {
        var_s1 = 0x140;
        if (arg0->unk34 < 4) {
            var_s1 = 0x1C0;
        }
        if (arg2 != 0) {
            arg0->unk40 = arg2;
        }
        arg0->unk58 = 0;
        StSetStream(0, arg1, -1, 0, 0);
        arg0->unk0->unk64(arg0);
        do {
            while (CdControl(2, arg0->unkC, 0) == 0) {}
        } while (CdRead2(var_s1) == 0);
        arg0->unk0->unk68(arg0);
        arg0->unk2C = 2;
    }
}

void func_800474C8(Unk_80047574 *arg0) {
    if (arg0->unk2C == 2 && D_8008A950 == arg0) {
        arg0->unk0->unk64(arg0);
        arg0->unk0->unk78(arg0);
        arg0->unk0->unk74(arg0);
        while (CdControl(9, 0, 0) == 0) {
        }
        arg0->unk2C = 4;
    }
}

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

void func_800475D8(Unk_80047574 *arg0) {
    if (arg0->unk30 == 0 && D_8008A950 == arg0) {
        while (CdControl(0xB, 0, 0) == 0) {
        }
        arg0->unk30 = 1;
    }
}

void func_80047638(Unk_80047638 *arg0) {
    if (arg0->unk30 != 0 && D_8008A950 == arg0) {
        while (CdControl(0xC, 0, 0) == 0) {
        }
        arg0->unk30 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80046F0C", func_80047694);

void func_800477B0(Unk_800477B0 *arg0, void *arg1) {
    void (*temp)(void *);

    temp = arg0->unk48;
    if (temp != NULL) {
        temp(arg0->unk44);
        arg0->unk0->unk70(arg0, arg1);
    }
}

void func_80047810(Unk_80047810 *arg0) {
    if (arg0->unk4C != 0) {
        arg0->unk48(arg0->unk44);
        arg0->unk0->unk48(arg0);
    }
}

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

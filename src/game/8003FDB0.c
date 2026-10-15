#include "common.h"

typedef struct Unk_800408A8 {
    u8 pad[0x68];
    s32 unk68;
} Unk_800408A8;
void func_80040790();
s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct Unk_800407F8Pair {
    s32 unk0;
    s32 unk4;
} Unk_800407F8Pair;
typedef struct Unk_800407F8 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x50 - 0x10];
    Unk_800407F8Pair unk50;
} Unk_800407F8;
typedef struct Unk_80040824 {
    u8 pad[0xC];
    s32 unkC;
    u8 pad2[0x60 - 0x10];
    u16 unk60;
    u16 unk62;
} Unk_80040824;
typedef struct Unk_800403F8 {
    u8 pad0[0x78];
    s32 unk78;
} Unk_800403F8;
extern u8 D_8006EA90[][3];
extern u8 D_8006EAA8[3];
typedef struct Unk_80040490 {
    u8 pad0[0x50];
    Unk_800407F8Pair unk50;
    u8 pad58[0x60 - 0x58];
    u16 unk60;
    u16 unk62;
    u8 pad64[0x88 - 0x64];
    u16 unk88;
    u8 pad8A[0x8C - 0x8A];
    u16 unk8C;
    u8 pad8E[0x90 - 0x8E];
    Unk_800407F8Pair unk90;
} Unk_80040490;
typedef struct Unk_80040EDC_obj Unk_80040EDC_obj;
typedef struct Unk_80040EDC_vt {
    u8 pad[0xC4];
    void (*unkC4)(Unk_80040EDC_obj *, u8, Unk_80040EDC_obj **);
} Unk_80040EDC_vt;
struct Unk_80040EDC_obj {
    Unk_80040EDC_vt *unk0;
};
typedef struct Unk_80040EDC {
    u8 pad[0xB4];
    Unk_80040EDC_obj **unkB4;
} Unk_80040EDC;
typedef struct Unk_80040854_Vtbl {
    u8 pad[0x4C];
    void (*unk4C)(void);
} Unk_80040854_Vtbl;
typedef struct Unk_80040854 {
    Unk_80040854_Vtbl *unk0;
    u8 pad4[0x44];
    s32 unk48;
    s32 unk4C;
} Unk_80040854;
typedef struct Unk_80040A30_obj {
    u8 pad[0xC];
    void (*unkC)(void *);
} Unk_80040A30_obj;
typedef struct Unk_80040A30 {
    u8 pad[0xA9];
    u8 unkA9;
    u8 padAA[0xB4 - 0xAA];
    Unk_80040EDC_obj **unkB4;
} Unk_80040A30;
void func_800183DC(void *, s32);
void *func_80017CFC(void *);
Unk_80040A30_obj *func_80041C3C(void);
typedef struct Unk_8004042C {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x50 - 0x10];
    Unk_800407F8Pair unk50;
    u8 pad58[0x60 - 0x58];
    u16 unk60;
    u16 unk62;
    u8 pad64[0x88 - 0x64];
    s32 unk88;
    s32 unk8C;
    Unk_800407F8Pair unk90;
} Unk_8004042C;
typedef struct Unk_80040A88_vt {
    u8 pad[0xCC];
    void (*unkCC)(void *, s32);
    s32 unkD0;
    void (*unkD4)(void *, s32);
} Unk_80040A88_vt;
typedef struct Unk_80040A88 {
    Unk_80040A88_vt *unk0;
} Unk_80040A88;
typedef struct Unk_8003FED8 Unk_8003FED8;
typedef struct Unk_8003FED8_vt {
    u8 pad14[0x14];
    void (*unk14)(Unk_8003FED8 *, s32);
    u8 pad18[0x30 - 0x18];
    void (*unk30)(Unk_8003FED8 *, s32);
    u8 pad34[0x60 - 0x34];
    void (*unk60)(Unk_8003FED8 *, s32);
    void (*unk64)(Unk_8003FED8 *, s32);
    u8 pad68[0xB8 - 0x68];
    void (*unkB8)(Unk_8003FED8 *, s32, u8 *);
} Unk_8003FED8_vt;
struct Unk_8003FED8 {
    Unk_8003FED8_vt *unk0;
    u8 pad4[0x6C - 0x4];
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    u8 pad80[0x98 - 0x80];
    s32 unk98;
};
typedef struct Unk_8003FDB0_tbl {
    u8 pad0[0x8];
    void (*unk8)(void *, s32, s32, s32);
    u8 pad_0C[0x40 - 0xC];
    void (*unk40)(void *, s32);
} Unk_8003FDB0_tbl;
void *func_80017B34(s32 size);
Unk_8003FDB0_tbl *func_800404C0(void);
typedef struct Unk_800404D0 {
    u8 pad0[0x8];
    void (*unk8)(void *, s32, u8 *, s32);
    u8 pad_0C[0x40 - 0xC];
    void (*unk40)(void *, s32, s32, s32);
} Unk_800404D0;
Unk_800404D0 *func_800408BC(void);
typedef struct Unk_80040790 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} Unk_80040790;
typedef struct Unk_80040664_vt {
    u8 pad[0xBC];
    void (*unkBC)(void *, s32);
} Unk_80040664_vt;
typedef struct Unk_80040664 {
    Unk_80040664_vt *unk0;
    u8 pad4[0x8];
    s32 unkC;
} Unk_80040664;
typedef struct Unk_80040664_mgr {
    u8 pad[0x4C];
    void (*unk4C)(Unk_80040664 *, s32, s32);
} Unk_80040664_mgr;
Unk_80040664_mgr *func_8001E57C(void);
typedef struct Unk_800405D0 Unk_800405D0;
typedef struct Unk_800405D0_vt {
    u8 pad[0xB8];
    void (*unkB8)(void *, s32, u8 *);
    u8 padBC[0xCC - 0xBC];
    void (*unkCC)(void *, s32);
} Unk_800405D0_vt;
struct Unk_800405D0 {
    Unk_800405D0_vt *unk0;
    u8 pad4[0x44 - 0x4];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    u8 pad50[0x58 - 0x50];
    s32 unk58;
    u16 unk5C;
    u16 unk5E;
    u16 unk60;
    u16 unk62;
};
extern u8 D_8008A924[];
typedef struct Unk_8004054C_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *arg0);
} Unk_8004054C_vt;
typedef struct Unk_800408CC_obj {
    u8 pad[0x8];
    void (*unk8)(void *, s32, s32, s32);
} Unk_800408CC_obj;
Unk_800408CC_obj *func_80040FB0(void);
typedef struct Unk_80040D74_obj Unk_80040D74_obj;
typedef struct Unk_80040D74_vt {
    u8 pad[0xB8];
    void (*unkB8)(void *, s32);
} Unk_80040D74_vt;
struct Unk_80040D74_obj {
    Unk_80040D74_vt *unk0;
};
typedef struct Unk_80040D74 {
    u8 pad[0xAB];
    u8 unkAB;
    u8 unkAC;
    u8 padAD[0xB4 - 0xAD];
    Unk_80040D74_obj **unkB4;
} Unk_80040D74;
typedef struct Unk_80040CD0_obj Unk_80040CD0_obj;
typedef struct Unk_80040CD0_vt {
    u8 pad[0x60];
    s32 (*unk60)(Unk_80040CD0_obj *, void *, s32);
} Unk_80040CD0_vt;
struct Unk_80040CD0_obj {
    Unk_80040CD0_vt *unk0;
};
typedef struct Unk_80040CD0 {
    u8 pad[0xAB];
    u8 unkAB;
    u8 unkAC;
    u8 padAD[0xB4 - 0xAD];
    Unk_80040CD0_obj **unkB4;
} Unk_80040CD0;
typedef struct Unk_80040E14_vt {
    u8 pad[0xBC];
    void (*unkBC)(void *, void *);
} Unk_80040E14_vt;
typedef struct Unk_80040E14_obj {
    Unk_80040E14_vt *unk0;
} Unk_80040E14_obj;
typedef struct Unk_80040E14 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0xA9 - 0x10];
    u8 unkA9;
    u8 padAA[0xB0 - 0xAA];
    s32 unkB0;
    Unk_80040E14_obj **unkB4;
} Unk_80040E14;
typedef struct Unk_80040C00_obj Unk_80040C00_obj;
typedef struct Unk_80040C00_vt {
    u8 pad[0x50];
    void (*unk50)(Unk_80040C00_obj *);
} Unk_80040C00_vt;
struct Unk_80040C00_obj {
    Unk_80040C00_vt *unk0;
};
typedef struct Unk_80040C00_tbl {
    u8 pad[0x50];
    void (*unk50)(void *);
} Unk_80040C00_tbl;
typedef struct Unk_80040C00 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0xAB - 0x10];
    u8 unkAB;
    u8 unkAC;
    u8 padAD[0xB4 - 0xAD];
    Unk_80040C00_obj **unkB4;
} Unk_80040C00;
typedef struct Unk_8003FF44_vt {
    u8 pad[0xE0];
    void (*unkE0)(void *);
} Unk_8003FF44_vt;
typedef struct Unk_8003FF44 {
    Unk_8003FF44_vt *unk0;
    u8 pad4[0x64 - 0x4];
    u8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67[0x74 - 0x67];
    u8 unk74;
    u8 pad75[0x78 - 0x75];
    s32 unk78;
    s32 unk7C;
    s32 unk80;
} Unk_8003FF44;
typedef struct Unk_80040A30_80040948 {
    Unk_8003FDB0_tbl *unk0;
    u8 pad[0xA9 - 0x4];
    u8 unkA9;
    u8 unkAA;
    u8 unkAB;
    u8 unkAC;
    u8 padAD[0xB4 - 0xAD];
    Unk_80040EDC_obj **unkB4;
} Unk_80040A30_80040948;
typedef struct Unk_80040948_tbl {
    u8 pad0[0x8];
    void (*unk8)(void *, s32, s32);
} Unk_80040948_tbl;
void *func_80041AB4(s32, u8);
s8 *itoa(s32 value);
s8 *strcpy(s8 *dst, s8 *src);
s32 strlen(u8 *s);
void *memset(void *dst, s32 c, s32 n);
s8 *func_80041020(s8 *arg0, u8 *arg1);
typedef struct Unk_80040AE8_obj Unk_80040AE8_obj;
typedef struct Unk_80040AE8_vt {
    u8 pad[0x4C];
    void (*unk4C)(void *, void *, Unk_800407F8Pair *);
} Unk_80040AE8_vt;
struct Unk_80040AE8_obj {
    Unk_80040AE8_vt *unk0;
};
typedef struct Unk_80040AE8_mgr {
    u8 pad[0x4C];
    void (*unk4C)(void *, s32, Unk_800407F8Pair *);
} Unk_80040AE8_mgr;
typedef struct Unk_80040AE8 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0xAA - 0x10];
    u8 unkAA;
    u8 unkAB;
    u8 unkAC;
    u8 padAD[0xB0 - 0xAD];
    s32 unkB0;
    Unk_80040AE8_obj **unkB4;
} Unk_80040AE8;

void *func_8003FDB0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp;

    temp = func_80017B34(0xA0);
    if (temp != NULL) {
        func_800404C0()->unk8(temp, arg0, arg1, arg2);
        return temp;
    }
    return NULL;
}

void func_8003FE2C(void **arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_800404D0 *temp_a3;
    u8 *var_a2;
    Unk_8003FDB0_tbl *temp_v0;

    temp_a3 = func_800408BC();
    if (arg2 != 0) {
        var_a2 = D_8006EA90[arg2];
    } else {
        var_a2 = D_8006EAA8;
    }
    temp_a3->unk8(arg0, arg1, var_a2, arg3);
    temp_v0 = func_800404C0();
    *arg0 = temp_v0;
    temp_v0->unk40(arg0, arg2);
}

void func_8003FED8(Unk_8003FED8 *arg0, s32 arg1) {
    arg0->unk70 = arg1;
    arg0->unk6C = 0;
    arg0->unk74 = 0xA;
    arg0->unk78 = 0;
    arg0->unk7C = 0;
    arg0->unk0->unk60(arg0, 0);
    arg0->unk0->unk64(arg0, 0);
    arg0->unk98 = 0;
}

void func_8003FF44(Unk_8003FF44 *arg0, s32 arg1, s32 arg2) {
    if (arg2 == 2) {
        if (arg0->unk80-- > 0) {
            if (arg0->unk7C != 9) {
                if (arg0->unk78 & 4) {
                    arg0->unk64 += arg0->unk74;
                }
                if (arg0->unk78 & 2) {
                    arg0->unk65 += arg0->unk74;
                }
                if (arg0->unk78 & 1) {
                    arg0->unk66 += arg0->unk74;
                }
            }
        } else {
            arg0->unk0->unkE0(arg0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_8004001C);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040024);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800400B0);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040154);

void func_800402F0(Unk_8003FED8 *arg0, s32 arg1) {
    Unk_8003FED8_vt *vt = arg0->unk0;
    s32 sel;

    if (arg0->unk6C == 0) {
        return;
    }
    if (arg0->unk6C == 1) {
        sel = 5;
        if (arg0->unk98 == 0) {
            vt->unk60(arg0, 0);
            vt->unk64(arg0, 0);
        }
    } else {
        sel = 6;
        if (arg0->unk98 != 0) {
            if (arg0->unk78 == 0xF) {
                vt->unkB8(arg0, 1, D_8006EAA8);
            }
            vt->unk64(arg0, 0);
        }
    }
    vt->unk14(arg0, arg1);
    if (arg0->unk74 < 0) {
        arg0->unk74 = -arg0->unk74;
    }
    arg0->unk6C = 0;
    vt->unk30(arg0, sel);
}

u8 *func_800403F8(Unk_800403F8 *arg0) {
    s32 index = arg0->unk78;

    if (index == 0xF) {
        return D_8006EAA8;
    }
    return D_8006EA90[index];
}

void func_8004042C(Unk_8004042C *arg0, u16 *arg1, Unk_800407F8Pair *arg2) {
    if (arg0->unkC != 0) {
        arg0->unk88 = arg0->unk60;
        arg0->unk8C = arg0->unk62;
        arg0->unk90 = arg0->unk50;
        arg0->unk60 = arg1[0];
        arg0->unk62 = arg1[2];
        arg0->unk50 = *arg2;
    }
}

void func_80040490(Unk_80040490 *arg0) {
    arg0->unk50 = arg0->unk90;
    arg0->unk60 = arg0->unk88;
    arg0->unk62 = arg0->unk8C;
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800404B4);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800404C0);

void *func_800404D0(s32 arg0, s32 arg1, s32 arg2) {
    void *obj;

    obj = func_80017B34(0x6C);
    if (obj != NULL) {
        func_800408BC()->unk8(obj, arg0, arg1, arg2);
        return obj;
    }
    return NULL;
}

void func_8004054C(void **arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_800404D0 *temp_v0;

    ((Unk_8004054C_vt *)func_8001E57C())->unk8(arg0);
    temp_v0 = func_800408BC();
    *arg0 = temp_v0;
    temp_v0->unk40(arg0, arg1, arg2, arg3);
}

void func_800405D0(Unk_800405D0 *arg0, u16 *arg1, u8 *arg2, s32 arg3) {
    Unk_800405D0_vt *vt;

    arg0->unk44 = arg3;
    arg0->unk48 = 1;
    arg0->unk4C = 0;
    arg0->unk58 = 0;
    arg0->unk5C = 0;
    arg0->unk5E = 0;
    arg0->unk60 = arg1[0];
    arg0->unk62 = arg1[2];
    vt = arg0->unk0;
    if (arg2 == NULL) {
        arg2 = D_8008A924;
    }
    vt->unkB8(arg0, 1, arg2);
    arg0->unk0->unkCC(arg0, 0xD);
}

void func_80040664(Unk_80040664 *arg0, s32 arg1, s32 arg2) {
    if (arg0->unkC == 0) {
        func_8001E57C()->unk4C(arg0, arg1, 0);
        arg0->unk0->unkBC(arg0, arg2);
    }
}

s32 func_800406E4(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x58), 0x1F, 1, arg1 == 0) == 0;
}

void func_80040714(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x58), 0x1E, 1, arg1 != 0);
}

void func_80040740(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x58), 0x1C, 2, arg1);
}

void func_8004076C(u8 *arg0, s32 arg1, u8 *arg2) {
    func_80040790(arg0, arg0 + 0x64, arg2, arg1);
}

void func_80040790(void *arg0, Unk_80040790 *arg1, Unk_80040790 *arg2, s32 arg3) {
    if (arg3 != 0) {
        *arg1 = *arg2;
        return;
    }
    arg1->unk0 += arg2->unk0;
    arg1->unk1 += arg2->unk1;
    arg1->unk2 += arg2->unk2;
}

void func_800407F8(Unk_800407F8 *arg0, Unk_800407F8Pair *arg1) {
    if (arg0->unkC != 0) {
        arg0->unk50 = *arg1;
    }
}

void func_80040824(Unk_80040824 *arg0, u16 *arg1) {
    if (arg0->unkC != 0) {
        arg0->unk60 = arg1[0];
        arg0->unk62 = arg1[2];
    }
}

void func_80040854(Unk_80040854 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0->unk4C();
    arg0->unk48 = 0;
    arg0->unk4C = arg3;
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800408A0);

void func_800408A8(Unk_800408A8 *arg0, s32 arg1) {
    arg0->unk68 = (1 << arg1) - 1;
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_800408BC);

s32 func_800408CC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0 = func_80017B34(0xB8);

    if (temp_v0 != 0) {
        func_80040FB0()->unk8((void *)temp_v0, arg0, arg1, arg2);
        return temp_v0;
    }
    return 0;
}

void func_80040948(Unk_80040A30_80040948 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_80040EDC_obj **var_s1;
    s32 i;

    ((Unk_80040948_tbl *)((Unk_80040A30_obj *)func_80041C3C()))->unk8(arg0, arg1, 0x20);
    arg0->unk0 = (Unk_8003FDB0_tbl *)((Unk_800408CC_obj *)func_80040FB0());
    arg0->unkA9 = arg2;
    arg0->unkAB = arg2;
    arg0->unkAC = 0;
    arg0->unkAA = 0;
    var_s1 = ((void *)func_80017B34(arg2 * 4));
    if (var_s1 != NULL) {
        arg0->unkB4 = var_s1;
        for (i = 0; i < arg2; i++) {
            *var_s1 = func_80041AB4(arg1, 0x20);
            var_s1 += 1;
        }
        arg0->unk0->unk40(arg0, arg3);
    }
}

void func_80040A30(Unk_80040A30 *arg0) {
    func_800183DC(arg0->unkB4, arg0->unkA9);
    arg0->unkB4 = func_80017CFC(arg0->unkB4);
    func_80041C3C()->unkC(arg0);
}

void func_80040A88(Unk_80040A88 *arg0, s32 arg1) {
    arg0->unk0->unkD4(arg0, 7);
    arg0->unk0->unkCC(arg0, arg1);
}

void func_80040AE8(Unk_80040AE8 *arg0, s32 arg1, Unk_800407F8Pair *arg2) {
    Unk_800407F8Pair pos;
    Unk_80040AE8_obj **p;
    s32 i;

    if (arg0->unkC == 0) {
        ((Unk_80040AE8_mgr *)func_80041C3C())->unk4C(arg0, arg1, arg2);
        pos = *arg2;
        p = &arg0->unkB4[arg0->unkAC];
        for (i = arg0->unkAC; i < arg0->unkAC + arg0->unkAB; i++) {
            if (arg0->unkAA != 0 && i == arg0->unkAA) {
                pos.unk0 += 0x10;
            }
            (*p)->unk0->unk4C(*p, arg0, &pos);
            pos.unk0 += arg0->unkB0;
            p++;
        }
    }
}

void func_80040C00(Unk_80040C00 *arg0) {
    s32 i;
    Unk_80040C00_obj **p;
    Unk_80040C00_obj *obj;

    if (arg0->unkC != 0) {
        if (arg0->unkB4 != NULL) {
            p = &arg0->unkB4[arg0->unkAC];
            for (i = arg0->unkAC; i < arg0->unkAC + arg0->unkAB; i++) {
                obj = *p++;
                obj->unk0->unk50(obj);
            }
        }
        ((Unk_80040C00_tbl *)func_80041C3C())->unk50(arg0);
    }
}

s32 func_80040CD0(Unk_80040CD0 *arg0, void *arg1, s32 arg2) {
    s32 i;
    Unk_80040CD0_obj **p;
    Unk_80040CD0_obj *obj;

    p = &arg0->unkB4[arg0->unkAC];
    for (i = arg0->unkAC; i < arg0->unkAC + arg0->unkAB; i++) {
        obj = *p++;
        arg2 = obj->unk0->unk60(obj, arg1, arg2);
    }
    return arg2;
}

void func_80040D74(Unk_80040D74 *arg0, s32 arg1) {
    s32 i;
    Unk_80040D74_obj **p;
    Unk_80040D74_obj *obj;

    p = &arg0->unkB4[arg0->unkAC];
    for (i = arg0->unkAC; i < arg0->unkAC + arg0->unkAB; i++) {
        obj = *p++;
        obj->unk0->unkB8(obj, arg1);
    }
}

void func_80040E14(Unk_80040E14 *arg0, Unk_800407F8Pair *arg1) {
    Unk_800407F8Pair pos;
    Unk_80040E14_obj **var_s2;
    Unk_80040E14_obj *temp_a0;
    s32 var_s0;

    if (arg0->unkC != 0) {
        ((Unk_80040E14_vt *)func_80041C3C())->unkBC(arg0, arg1);
        pos = *arg1;
        var_s2 = arg0->unkB4;
        for (var_s0 = 0; var_s0 < arg0->unkA9; var_s2++, var_s0++) {
            temp_a0 = *var_s2;
            temp_a0->unk0->unkBC(temp_a0, &pos);
            pos.unk0 += arg0->unkB0;
        }
    }
}

void func_80040EDC(Unk_80040EDC *arg0, s32 arg1, s32 arg2) {
    Unk_80040EDC_obj **temp_a2 = &arg0->unkB4[arg2];
    Unk_80040EDC_obj *temp_a0 = *temp_a2;

    temp_a0->unk0->unkC4(temp_a0, arg1, temp_a2);
}

void func_80040F20(void) {
}

void func_80040F28(Unk_80040EDC *arg0, u8 *arg1) {
    Unk_80040EDC_obj **p = arg0->unkB4;

    if (arg1 != NULL) {
        while (*arg1 != 0) {
            Unk_80040EDC_obj *obj = *p;

            ((void (*)(Unk_80040EDC_obj *, u8))obj->unk0->unkC4)(obj, *arg1++);
            p++;
        }
    }
}

void func_80040FA0(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040FA8);

INCLUDE_ASM("asm/nonmatchings/game/8003FDB0", func_80040FB0);

s8 *func_80040FC0(s8 *arg0, u8 *arg1) {
    s8 *var_a0 = arg0;
    s8 *var_a2;
    u8 c;
    s32 v;
    s32 k;

    c = *arg1++;
    if (c != 0) {
        k = 0x40;
        var_a2 = arg0;
        do {
            var_a2++;
            c = *arg1;
            var_a0++;
            if (c >= 0x80 || c == k) {
                v = c - 0x20;
            } else {
                v = c - 0x1F;
            }
            var_a2[-1] = v;
            arg1++;
        } while (*arg1++ != 0);
    }
    *var_a0 = 0;
    return var_a0;
}

s8 *func_80041020(s8 *arg0, u8 *arg1) {
    s8 *next;
    s8 *out;
    u8 c;
    s32 hi;
    s32 lo;

    next = arg0;
    out = arg0;
    while (*arg1 != 0) {
        next++;
        hi = 0x81;
        if (*arg1 >= 0x30) {
            hi = 0x82;
        }
        *out = hi;
        out = next;
        c = *arg1;
        next++;
        if (c >= 0x60 || c == 0x20) {
            lo = c + 0x20;
        } else {
            lo = c + 0x1F;
        }
        arg1++;
        *out = lo;
        out = next;
    }
    *next = 0;
    return next;
}

void func_8004109C(s8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    char bufA[arg2 + 1];
    char bufB[arg2 + 1];
    s32 pad;
    u8 *out;

    pad = strlen(strcpy(bufA, itoa(arg1)));
    pad = arg2 - pad;
    if (arg3 == 0) {
        memset(bufB, 0x30, arg2);
        strcpy(bufB + pad, bufA);
    }
    out = bufB;
    if (arg3 != 0) {
        out = bufA;
    }
    func_80041020(arg0, out);
}

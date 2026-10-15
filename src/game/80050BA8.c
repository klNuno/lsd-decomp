#include "common.h"

typedef struct Unk_80018390 { s32 unk0, unk4, unk8; void (*unkC)(); u8 pad_10[0x4]; void (*unk14)(void *, s32 **); void (*unk18)(void *); u8 pad_1C[0x38 - 0x1C]; void (*unk38)(void **, s32 **, s32); } Unk_80018390;
extern void func_80017CFC(s32);
extern Unk_80018390 *func_80018390(void);
typedef struct { u8 pad[0x20]; s32 u20; u8 pad2[0x24]; s32 u48; } Unk_800517EC;
extern void func_800183DC(void *, s32);
extern void func_800531CC(void *, void *);
void func_8002CC84(void *, void *);
typedef struct Unk_8005161C_Vtbl {
    u8 pad[0x80];
    void (*unk80)(void *, s32, s32, s32);
} Unk_8005161C_Vtbl;
typedef struct Unk_8005161C_Obj {
    Unk_8005161C_Vtbl *vtbl;
} Unk_8005161C_Obj;
typedef struct Unk_8005161C {
    u8 pad[0x3C];
    Unk_8005161C_Obj *u3C;
} Unk_8005161C;
struct Unk_80051814;
struct Unk_80051814_vtbl {
    u8 pad_00[0xA8];
    void (*unkA8)(struct Unk_80051814 *, s32, s32, s32);
};
struct Unk_80051814 {
    struct Unk_80051814_vtbl *unk0;
    u8 pad_04[0x10];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x28];
    s32 unk48;
};
typedef struct Unk_80050E34 {
    u8 pad_00[0x34];
    s32 **unk34;
    s32 **unk38;
    u8 pad_3C[0x48 - 0x3C];
    s32 unk48;
} Unk_80050E34;
typedef struct Unk_80051E20 {
    u8 pad_00[0x34];
    s32 unk34;
    s32 unk38;
    u8 pad_3C[0x50 - 0x3C];
    s32 unk50;
} Unk_80051E20;
typedef struct Unk_80051270_Vtbl {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32);
} Unk_80051270_Vtbl;
typedef struct Unk_80051270 {
    Unk_80051270_Vtbl *unk0;
    u8 pad_04[0x30];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} Unk_80051270;
struct Unk_8005165C;
typedef struct Unk_8005165C_vtbl {
    u8 pad_00[0xA4];
    void (*unkA4)(struct Unk_8005165C *, s32, s32);
} Unk_8005165C_vtbl;
typedef struct Unk_8005165C {
    Unk_8005165C_vtbl *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    u8 pad_14[0x4];
    s32 unk18;
    u8 pad_1C[0x48 - 0x1C];
    s32 unk48;
} Unk_8005165C;
typedef struct Unk_80051720_vtbl {
    u8 pad_00[0xA8];
    void (*unkA8)(void *, s32, s32, s32);
} Unk_80051720_vtbl;
typedef struct Unk_80051720 {
    Unk_80051720_vtbl *unk0;
    u8 pad_04[0x10];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x28];
    s32 unk48;
} Unk_80051720;
typedef struct Unk_80051370_Vtbl {
    u8 pad_00[0x54];
    void (*unk54)(void *, s32);
} Unk_80051370_Vtbl;
typedef struct Unk_80051370 {
    Unk_80051370_Vtbl *unk0;
    u8 pad_04[0x28];
    s32 unk2C;
    s32 unk30;
} Unk_80051370;
typedef struct Unk_800516C0_Vtbl {
    u8 pad_00[0xA4];
    void (*unkA4)(void *, s32, s32);
} Unk_800516C0_Vtbl;
typedef struct Unk_800516C0 {
    Unk_800516C0_Vtbl *unk0;
    u8 pad_04[0x14];
    s32 unk18;
    u8 pad_1C[0x2C];
    s32 unk48;
} Unk_800516C0;
typedef struct Unk_80050BA8 {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32);
} Unk_80050BA8;
extern void *func_80017B34(s32 size);
extern Unk_80050BA8 *func_80051A4C(void);
typedef struct Unk_80050F28 {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
    u8 pad_14[0x4];
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x4];
    u8 *unk24;
    s8 *unk28;
} Unk_80050F28;
s8 *func_80040FC0(s8 *arg0, u8 *arg1);
s8 *strcpy(s8 *arg0, u8 *arg1);
typedef struct Unk_80051200_Vtbl {
    u8 pad_00[0x10];
    void (*unk10)(void *, s32);
} Unk_80051200_Vtbl;
typedef struct Unk_80051200 {
    Unk_80051200_Vtbl *unk0;
    u8 pad_04[0x1C];
    s32 unk20;
    u8 pad_24[0x8];
    s32 unk2C;
    u8 pad_30[0xC];
    s32 unk3C;
} Unk_80051200;
typedef struct Unk_80051A5C {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32);
} Unk_80051A5C;
Unk_80051A5C *func_80052B60(void);
typedef struct Unk_80051DA0 {
    u8 pad_00[0x34];
    s32 **unk34;
    s32 **unk38;
} Unk_80051DA0;
typedef struct Unk_80051174_Obj Unk_80051174_Obj;
typedef struct Unk_80051174_Vtbl {
    u8 pad_00[0x4];
    void *(*unk4)(void *);
} Unk_80051174_Vtbl;
struct Unk_80051174_Obj {
    Unk_80051174_Vtbl *vtbl;
};
typedef struct Unk_80051174 {
    u8 pad_00[0x40];
    Unk_80051174_Obj *unk40;
    Unk_80051174_Obj *unk44;
    Unk_80051174_Obj *unk48;
} Unk_80051174;
typedef struct Unk_80051C84 {
    u8 pad_00[0x10];
    s32 unk10;
    u8 pad_14[0x4];
    s32 *unk18;
    s32 unk1C;
} Unk_80051C84;
typedef struct Unk_80018390_80050D30 { s32 unk0, unk4, unk8; void (*unkC)(); void (*unk10)(void *, s32 **); u8 pad_14[0x4]; void (*unk18)(void *); } Unk_80018390_80050D30;
typedef struct Unk_80018390_80051D1C { s32 unk0, unk4, unk8; void (*unkC)(); void (*unk10)(void *, void *); u8 pad_14[0x4]; void (*unk18)(void *); } Unk_80018390_80051D1C;
typedef struct Unk_80051858_vtbl {
    u8 pad_00[0xA4];
    void (*unkA4)(void *, s32, s32);
    void (*unkA8)(void *, s32, s32, s32);
} Unk_80051858_vtbl;
typedef struct Unk_80051858 {
    Unk_80051858_vtbl *unk0;
    u8 pad_04[0xC];
    s32 unk10;
    u8 pad_14[0x4];
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x28];
    s32 unk48;
} Unk_80051858;
typedef struct Unk_800518F4 Unk_800518F4;
typedef struct Unk_800518F4_Vt {
    u8 pad_00[0x60];
    void (*unk60)(Unk_800518F4 *, s32);
} Unk_800518F4_Vt;
typedef struct Unk_800518F4_ObjVt {
    u8 pad_00[0xBC];
    void (*unkBC)(void *, s32 *);
} Unk_800518F4_ObjVt;
typedef struct Unk_800518F4_Obj {
    Unk_800518F4_ObjVt *unk0;
} Unk_800518F4_Obj;
struct Unk_800518F4 {
    Unk_800518F4_Vt *unk0;
    u8 pad_04[0x18 - 0x4];
    s32 unk18;
    u8 pad_1C[0x40 - 0x1C];
    Unk_800518F4_Obj *unk40;
    u8 pad_44[0x48 - 0x44];
    s32 unk48;
};
s32 D_8008AADC;
s32 D_8008AAE0;
typedef struct Unk_800512C8_Vtbl {
    u8 pad_00[0x14];
    void (*unk14)(void *, s32 **);
    u8 pad_18[0x30 - 0x18];
    void (*unk30)(void *, s32);
    u8 pad_34[0x48 - 0x34];
    void (*unk48)(void *);
} Unk_800512C8_Vtbl;
typedef struct Unk_800512C8 {
    Unk_800512C8_Vtbl *unk0;
    u8 pad_04[0x28];
    s32 unk2C;
    s32 unk30;
    s32 **unk34;
} Unk_800512C8;
typedef struct Unk_80050E78 {
    u8 pad_00[0x58];
    void (*unk58)(void *, s32 **, s32);
    void (*unk5C)(void *, s32 **, s32);
} Unk_80050E78;
typedef struct Unk_80051E64 {
    u8 pad_00[0x58];
    void (*unk58)(void **, s32 **, s32);
    void (*unk5C)(void **, s32 **, s32);
} Unk_80051E64;
typedef struct Unk_80051998_Vt {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_80051998_Vt;
typedef struct Unk_80051998_ObjVt {
    u8 pad_00[0xC4];
    void (*unkC4)(void *, s32, s32);
} Unk_80051998_ObjVt;
typedef struct Unk_80051998_Obj {
    Unk_80051998_ObjVt *vtbl;
} Unk_80051998_Obj;
typedef struct Unk_80051998 {
    Unk_80051998_Vt *unk0;
    u8 pad_04[0x14];
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x8];
    u8 *unk28;
    u8 pad_2C[0x44 - 0x2C];
    Unk_80051998_Obj *unk44;
    s32 unk48;
} Unk_80051998;
u8 *D_8008AAE4;

void *func_80050BA8(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_80017B34(0x4C);
    if (temp_v0 != NULL) {
        func_80051A4C()->unk8(temp_v0, arg0, arg1);
        return temp_v0;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050C14);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050CD8);

void func_80050CE8(u8 *arg0) {
    func_80017CFC(*(s32 *)(arg0 + 0x28));
    func_80018390()->unkC(arg0);
}

void func_80050D30(Unk_80050E34 *arg0, s32 **arg1) {
    s32 temp_v1;

    if (arg1 != NULL) {
        ((Unk_80018390_80050D30 *)func_80018390())->unk10(arg0, arg1);
        temp_v1 = **arg1 & 0xF;
        if (temp_v1 == 2) {
            arg0->unk34 = arg1;
            return;
        }
        if (temp_v1 == 5) {
            arg0->unk38 = arg1;
        }
    }
}

void func_80050DB4(Unk_80050E34 *arg0, s32 **arg1) {
    s32 temp_v1;

    if (arg1 != NULL) {
        temp_v1 = **arg1 & 0xF;
        if (temp_v1 == 2) {
            arg0->unk34 = NULL;
        } else if (temp_v1 == 5) {
            arg0->unk38 = NULL;
        }
        func_80018390()->unk14(arg0, arg1);
    }
}

void func_80050E34(Unk_80050E34 *arg0) {
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk48 = 0;
    func_80018390()->unk18(arg0);
}

void func_80050E78(Unk_80050E78 **arg0, s32 **arg1, s32 arg2) {
    s32 temp_v1;

    func_80018390()->unk38(arg0, arg1, arg2);
    temp_v1 = **arg1 & 0xF;
    if (temp_v1 == 2) {
        (*arg0)->unk5C(arg0, arg1, arg2);
    } else if (temp_v1 == 5) {
        (*arg0)->unk58(arg0, arg1, arg2);
    }
}

void func_80050F28(Unk_80050F28 *arg0, u8 *arg1, s32 arg2) {
    arg0->unkC = arg2;
    arg0->unk24 = arg1;
    arg0->unk18 = 0;
    arg0->unk1C = 0;
    if (arg2 == 1) {
        func_80040FC0(arg0->unk28, arg1);
        arg0->unk10 = arg0->unk10 / 2;
    } else {
        strcpy(arg0->unk28, arg1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_800115D0);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_80011610);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_8001161C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050F98);

void func_80051174(Unk_80051174 *arg0) {
    Unk_80051174_Obj *temp_a0;

    temp_a0 = arg0->unk48;
    if (temp_a0 != NULL) {
        arg0->unk48 = temp_a0->vtbl->unk4(temp_a0);
        temp_a0 = arg0->unk44;
        temp_a0->vtbl->unk4(temp_a0);
        temp_a0 = arg0->unk40;
        temp_a0->vtbl->unk4(temp_a0);
    }
}

void func_80051200(Unk_80051200 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0->unk10(arg0, arg1);
    arg0->unk0->unk10(arg0, arg2);
    arg0->unk3C = arg3;
    arg0->unk2C = 0;
    arg0->unk20 = 0;
}

void func_80051270(Unk_80051270 *arg0) {
    arg0->unk0->unk14(arg0, arg0->unk34);
    arg0->unk0->unk14(arg0, arg0->unk38);
    arg0->unk3C = 0;
}

void func_800512C8(Unk_800512C8 *arg0, s32 arg1) {
    arg0->unk30 = 0;
    switch (arg1) {
    case 2:
    case 3:
        arg0->unk0->unk14(arg0, arg0->unk34);
        arg0->unk0->unk48(arg0);
        arg0->unk2C = arg1;
        break;
    case 4:
        arg0->unk0->unk30(arg0, arg0->unk2C);
        break;
    }
}

void func_80051370(Unk_80051370 *arg0) {
    s32 temp_v1;
    s32 temp_v1_2;

    temp_v1 = arg0->unk2C;
    if (temp_v1 < 4) {
        if (temp_v1 >= 2) {
            temp_v1_2 = arg0->unk30;
            arg0->unk30 = temp_v1_2 + 1;
            if (temp_v1_2 != 0) {
                arg0->unk0->unk54(arg0, 4);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800513D0);

void func_8005161C(Unk_8005161C *arg0, s32 arg1) {
    Unk_8005161C_Obj *temp_a0;

    temp_a0 = arg0->u3C;
    if (temp_a0 != NULL) {
        temp_a0->vtbl->unk80(temp_a0, arg1, 0x60, 0x60);
    }
}

void func_8005165C(Unk_8005165C *arg0) {
    s32 temp_a1;
    s32 temp_v1;

    if (arg0->unk48 != 0) {
        temp_v1 = arg0->unk18;
        temp_a1 = temp_v1 + 1;
        arg0->unk18 = temp_a1;
        if (temp_a1 < arg0->unk10) {
            arg0->unk0->unkA4(arg0, temp_a1, 1);
            return;
        }
        arg0->unk18 = temp_v1;
    }
}

void func_800516C0(Unk_800516C0 *arg0) {
    s32 temp_v0;
    s32 temp_a1;

    if (arg0->unk48 != 0) {
        temp_v0 = arg0->unk18;
        temp_a1 = temp_v0 - 1;
        arg0->unk18 = temp_a1;
        if (temp_a1 >= 0) {
            arg0->unk0->unkA4(arg0, temp_a1, 1);
            return;
        }
        arg0->unk18 = temp_v0;
    }
}

void func_80051720(Unk_80051720 *arg0) {
    s32 temp_a2;

    if (arg0->unk48 != 0) {
        temp_a2 = arg0->unk1C + 1;
        arg0->unk1C = temp_a2;
        if (temp_a2 < arg0->unk14) {
            arg0->unk0->unkA8(arg0, arg0->unk18, temp_a2, 1);
            return;
        }
        arg0->unk1C = 0;
    }
}

void func_80051784(struct Unk_80051814 *arg0) {
    s32 temp_a2;

    if (arg0->unk48 != 0) {
        temp_a2 = arg0->unk1C - 1;
        arg0->unk1C = temp_a2;
        if (temp_a2 > 0) {
            arg0->unk0->unkA8(arg0, arg0->unk18, temp_a2, 1);
            return;
        }
        arg0->unk1C = arg0->unk14;
    }
}

void func_800517EC(Unk_800517EC *arg0) {
    if (arg0->u48 != 0) {
        arg0->u20 ^= 1;
    }
}

void func_80051814(struct Unk_80051814 *arg0) {
    if (arg0->unk48 != 0) {
        arg0->unk1C = 0;
        arg0->unk0->unkA8(arg0, arg0->unk18, 0, 1);
    }
}

void func_80051858(Unk_80051858 *arg0) {
    s32 i;

    if (arg0->unk48 != 0) {
        arg0->unk1C = 0;
        for (i = arg0->unk10 - 1; i >= 0; i--) {
            arg0->unk18 = i;
            arg0->unk0->unkA8(arg0, i, arg0->unk1C, 0);
        }
        arg0->unk0->unkA4(arg0, arg0->unk18, 1);
    }
}

void func_800518F4(Unk_800518F4 *arg0, s32 arg1, s32 arg2) {
    s32 sp[2];
    Unk_800518F4_Obj *temp_a0;

    if (arg0->unk48 != 0) {
        sp[1] = D_8008AAE0;
        sp[0] = arg1 * 7 + D_8008AADC;
        temp_a0 = arg0->unk40;
        temp_a0->unk0->unkBC(temp_a0, sp);
        arg0->unk18 = arg1;
        if (arg2 != 0) {
            arg0->unk0->unk60(arg0, 0);
        }
    }
}

void func_80051998(Unk_80051998 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Unk_80051998_Obj *temp_a0;

    if (arg0->unk48 != 0) {
        arg0->unk28[arg1] = D_8008AAE4[arg2];
        temp_a0 = arg0->unk44;
        temp_a0->vtbl->unkC4(temp_a0, D_8008AAE4[arg2], arg1);
        arg0->unk18 = arg1;
        arg0->unk1C = arg2;
        if (arg3 != 0) {
            arg0->unk0->unk60(arg0, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051A4C);

s32 func_80051A5C(s32 arg0, s32 arg1) {
    void *p;

    p = func_80017B34(0x54);
    if (p != NULL) {
        func_80052B60()->unk8(p, arg0, arg1);
        return (s32)p;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051AC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051C74);

void func_80051C84(Unk_80051C84 *arg0) {
    s32 i;

    for (i = 0; i < arg0->unk10; i++) {
        func_80017CFC(arg0->unk18[i]);
    }
    func_80017CFC(arg0->unk1C);
    func_80017CFC((s32)arg0->unk18);
    func_80018390()->unkC(arg0);
}

void func_80051D1C(Unk_80050E34 *arg0, s32 **arg1) {
    s32 temp_v1;

    if (arg1 != NULL) {
        ((Unk_80018390_80051D1C *)func_80018390())->unk10(arg0, arg1);
        temp_v1 = **arg1 & 0xF;
        if (temp_v1 == 2) {
            arg0->unk34 = arg1;
            return;
        }
        if (temp_v1 == 5) {
            arg0->unk38 = arg1;
        }
    }
}

void func_80051DA0(Unk_80051DA0 *arg0, s32 **arg1) {
    s32 temp_v1;

    if (arg1 != NULL) {
        temp_v1 = **arg1 & 0xF;
        if (temp_v1 == 2) {
            arg0->unk34 = NULL;
        } else if (temp_v1 == 5) {
            arg0->unk38 = NULL;
        }
        func_80018390()->unk14(arg0, arg1);
    }
}

void func_80051E20(Unk_80051E20 *arg0) {
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk50 = 0;
    func_80018390()->unk18(arg0);
}

void func_80051E64(Unk_80051E64 **arg0, s32 **arg1, s32 arg2) {
    s32 temp;

    func_80018390()->unk38(arg0, arg1, arg2);
    temp = **arg1 & 0xF;
    if (temp == 2) {
        (*arg0)->unk5C(arg0, arg1, arg2);
    } else if (temp == 5) {
        (*arg0)->unk58(arg0, arg1, arg2);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051F14);

#include "common.h"

struct Unk_8001D600 {
    u8 pad_00[0x20];
    s32 unk20;
};
void func_8001F51C(s32);
s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct Unk_8001CD20 {
    u8 pad_00[0x18];
    void (*unk18)(s32);
} Unk_8001CD20;
void func_8001E7B0(s32 arg0);
Unk_8001CD20 *func_80018390(void);
extern void GsLinkObject4(u32 *src, void *dst, s32 id);
struct Unk_8001E770_Data {
    u8 pad_00[0xC];
    s32 unkC;
    s32 unk10;
};
struct Unk_8001E770 {
    u8 pad_00[0x10];
    u8 unk10[8];
    s32 unk18;
    u8 pad_1C[4];
    struct Unk_8001E770_Data *unk20;
};
typedef struct Unk_8001CA94_vt {
    u8 pad_00[0x8];
    s32 (*unk8)(s32);
} Unk_8001CA94_vt;
Unk_8001CA94_vt *func_8001E57C(void);
s32 func_80017B34(s32);
void func_80017CFC(s32);
typedef struct Unk_8001D1A4_Sub {
    u8 pad_00[0x48];
    s32 unk48;
} Unk_8001D1A4_Sub;
typedef struct Unk_8001D1A4_Vt {
    u8 pad_00[0x14];
    void (*unk14)(void *, void *);
} Unk_8001D1A4_Vt;
typedef struct Unk_8001D1A4_Obj {
    Unk_8001D1A4_Vt *vt;
} Unk_8001D1A4_Obj;
struct Unk_8001D1A4 {
    u8 pad_00[0xC];
    Unk_8001D1A4_Obj *unkC;
    u8 pad_10[4];
    Unk_8001D1A4_Sub *unk14;
};
typedef struct Unk_8001D6B4_Vtbl {
    u8 pad[0xA0];
    void (*unkA0)(void *, s32, s32);
} Unk_8001D6B4_Vtbl;
typedef struct Unk_8001D6B4 {
    Unk_8001D6B4_Vtbl *unk0;
    u8 pad4[0x24];
    s32 unk28;
} Unk_8001D6B4;

s32 func_8001CA94(void) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x44);
    if (temp_s0 == 0) {
        return 0;
    }
    if (func_8001E57C()->unk8(temp_s0) != 0) {
        return temp_s0;
    }
    func_80017CFC(temp_s0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CAF4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CBA4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CC48);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CCB4);

void func_8001CD20(s32 arg0) {
    func_8001E7B0(arg0);
    func_80018390()->unk18(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CD60);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CE30);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001CEB4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D008);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D0EC);

void *func_8001D1A4(struct Unk_8001D1A4 *arg0) {
    Unk_8001D1A4_Obj *temp;

    temp = arg0->unkC;
    if (temp != NULL) {
        temp->vt->unk14(temp, arg0);
        arg0->unk14->unk48 = 0;
        arg0->unkC = NULL;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D204);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D280);

void func_8001D33C(void) {
}

s32 func_8001D344(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 0x1F, 1, arg1 == 0) == 0;
}

void func_8001D374(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0x1E, 1, arg1 != 0);
}

void func_8001D3A0(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0x1C, 2, arg1);
}

void func_8001D3CC(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 6, 1, arg1 == 0);
}

void func_8001D3F8(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 3, 3, arg1);
}

void func_8001D424(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 0, 3, arg1);
}

s32 func_8001D450(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 7, 1, arg1 == 0) == 0;
}

void func_8001D480(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x10), 9, 3, arg1);
}

s32 func_8001D4AC(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x10), 8, 1, arg1 == 0) == 0;
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D4DC);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D568);

void func_8001D600(struct Unk_8001D600 *arg0) {
    func_8001F51C(arg0->unk20);
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D624);

void func_8001D6A4(void) {
}

void func_8001D6AC(void) {
}

void func_8001D6B4(Unk_8001D6B4 *arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
        case 2:
        case 3:
            arg0->unk0->unkA0(arg0, arg1, arg2);
            break;
        case 4:
            arg0->unk28 = arg1;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D714);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001D950);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001DA28);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001DDF4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E110);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E2E8);

void func_8001E49C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E4A4);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E57C);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E58C);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E600);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E6F8);

void func_8001E770(struct Unk_8001E770 *arg0, struct Unk_8001E770_Data *arg1) {
    arg0->unk20 = arg1;
    arg0->unk18 = arg1->unk10;
    GsLinkObject4((u32 *)(arg0->unk20->unkC + 0xC), &arg0->unk10, 0);
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E7B0);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001E7BC);

void func_8001EA8C(s32 *arg0, s16 *arg1, s16 *arg2) {
    arg0[0] = arg2[0] - arg1[0];
    arg0[1] = arg2[1] - arg1[1];
    arg0[2] = arg2[2] - arg1[2];
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EACC);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EC84);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001ECFC);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EDAC);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EE04);

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EE98);

s32 func_8001EF14(s32 *arg0, s32 arg1, s32 *arg2) {
    s32 i;

    for (i = 0; i < 3; i++, arg0++, arg2++) {
        if (*arg2 < *arg0 - arg1) {
            return 0;
        }
        if (*arg0 + arg1 < *arg2) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/game/8001CA94", func_8001EF60);

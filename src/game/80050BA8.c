#include "common.h"

typedef struct VTable { s32 unk0, unk4, unk8; void (*fnC)(); } VTable;
extern void func_80017CFC(s32);
extern VTable *func_80018390(void);
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
    u8 pad_04[0x14];
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x28];
    s32 unk48;
};

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050BA8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050C14);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050CD8);

void func_80050CE8(u8 *arg0) {
    func_80017CFC(*(s32 *)(arg0 + 0x28));
    func_80018390()->fnC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050D30);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050DB4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050E34);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050E78);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050F28);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_800115D0);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_80011610);

INCLUDE_RODATA("asm/nonmatchings/game/80050BA8", D_8001161C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80050F98);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051174);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051200);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051270);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800512C8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051370);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800513D0);

void func_8005161C(Unk_8005161C *arg0, s32 arg1) {
    Unk_8005161C_Obj *temp_a0;

    temp_a0 = arg0->u3C;
    if (temp_a0 != NULL) {
        temp_a0->vtbl->unk80(temp_a0, arg1, 0x60, 0x60);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_8005165C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800516C0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051720);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051784);

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

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051858);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_800518F4);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051998);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051A4C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051A5C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051AC8);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051C74);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051C84);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051D1C);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051DA0);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051E20);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051E64);

INCLUDE_ASM("asm/nonmatchings/game/80050BA8", func_80051F14);

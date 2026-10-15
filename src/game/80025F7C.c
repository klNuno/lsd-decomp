#include "common.h"

typedef struct Unk_80026C88 {
    u8 pad[0x24];
    u32 unk24;
} Unk_80026C88;
void func_8004A070(s32);
struct Unk_80026CE8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
s32 D_8008A84C;
void func_800280D0(void);
void func_800280E0(void);
s32 func_80027EC8(void);
s32 func_80027ED4(void);
s32 func_80027EE0(void);
s32 func_80027EEC(void);
void *func_80027E68(void);
void *func_8002C438(void);
s32 func_8002C448(s32 *arg0);
s32 func_80027EF8(s32 *arg0);
s32 func_8002C478(void);
s32 func_80028B6C(void);
typedef struct Unk_80026AB4_Vtbl {
    u8 pad_00[0x48];
    void (*unk48)(void);
    u8 pad_4C[0x5C - 0x4C];
    void (*unk5C)(void *);
} Unk_80026AB4_Vtbl;
typedef struct Unk_80026AB4 {
    Unk_80026AB4_Vtbl *vtbl;
} Unk_80026AB4;
void func_80048CFC(s32, s32);
typedef struct Unk_80026A50_Vtbl {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_80026A50_Vtbl;
typedef struct Unk_80026A50 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad_04[0x8];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad_18[0x8];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
} Unk_80026A50;
void *func_80018390(void);
s32 func_80026C9C(void);
typedef struct Unk_80026108 {
    u8 pad_00[0x18];
    s32 unk18;
} Unk_80026108;
typedef struct Unk_80026108_Obj {
    u8 pad_00[0x44];
    void (*unk44)(Unk_80026108 *, s32, s32, s32);
} Unk_80026108_Obj;
extern void *func_8003B20C(void);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80025F7C);

INCLUDE_RODATA("asm/nonmatchings/game/80025F7C", D_800107A4);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80025FDC);

void func_800260A4(void) {
    func_80048CFC(*(s32 *)0x1F800000 % 365, 0);
}

void func_80026108(Unk_80026108 *arg0, s32 arg1, s32 arg2) {
    if (arg0->unk18 == 0) {
        ((Unk_80026108_Obj *)func_8003B20C())->unk44(arg0, arg1, arg2, 0);
    }
}

INCLUDE_RODATA("asm/nonmatchings/game/80025F7C", D_800107B4);

INCLUDE_RODATA("asm/nonmatchings/game/80025F7C", D_800107C8);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026170);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026254);

void func_80026328(void) {
    func_8004A070(0);
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026348);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026410);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026518);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_8002658C);

void func_80026690(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026698);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_8002677C);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026900);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800269E0);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800269F0);

void func_80026A50(Unk_80026A50 *arg0) {
    ((Unk_80026A50_Vtbl *)func_80018390())->unk8(arg0);
    arg0->unk0 = func_80026C9C();
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk20 = 0;
    arg0->unk22 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2A = 0;
}

void func_80026AB4(Unk_80026AB4 *arg0) {
    arg0->vtbl->unk48();
    arg0->vtbl->unk5C(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026B08);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026C20);

void func_80026C80(void) {
}

void func_80026C88(Unk_80026C88 *arg0) {
    arg0->unk24 |= 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026C9C);

void *func_80026CAC(void) {
    if (D_8008A84C == 0x23) {
        return func_8002C438();
    }
    return func_80027E68();
}

struct Unk_80026CE8 *func_80026CE8(struct Unk_80026CE8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = arg3;
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026CFC);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026D88);

void func_80026E0C(void) {
    if (D_8008A84C == 0x13) {
        func_800280D0();
    }
}

void func_80026E38(void) {
    if (D_8008A84C == 0x13) {
        func_800280E0();
    }
}

s32 func_80026E64(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EC8();
    }
    return 0;
}

s32 func_80026E98(void) {
    if (D_8008A84C == 0x13) {
        return func_80027ED4();
    }
    return 1;
}

s32 func_80026ECC(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EE0();
    }
    return 0;
}

s32 func_80026F00(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EEC();
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026F34);

s32 func_80026FAC(s32 *arg0) {
    if (D_8008A84C == 0x13) {
        return func_80027EF8(arg0);
    }
    return func_8002C448(arg0);
}

s32 func_80026FE8(void) {
    if (D_8008A84C == 0x13) {
        return func_80028B6C();
    }
    return func_8002C478();
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80027024);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270AC);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270B8);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270C4);

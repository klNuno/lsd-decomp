#include "common.h"

typedef struct Unk_8003B02C_Pair {
    s32 unk0;
    s32 unk4;
} Unk_8003B02C_Pair;
struct Unk_8003B02C {
    u8 pad_00[0xC];
    Unk_8003B02C_Pair unkC;
    s32 unk14;
};
typedef struct Unk_8003AF8C_Vtbl {
    u8 pad_00[0x40];
    void (*unk40)(void *, void *, s32);
} Unk_8003AF8C_Vtbl;
typedef struct Unk_8003AF8C {
    Unk_8003AF8C_Vtbl *unk0;
    u8 pad_04[0x18 - 0x4];
    s32 unk18;
} Unk_8003AF8C;
typedef struct Unk_8003AF8C_Mgr {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8003AF8C_Mgr;
void *func_80018390(void);
void *func_8003B20C(void);
void func_80026CFC(s32 arg0);
s32 CdInit(void);
s32 D_8008A8DC;
extern char D_8008A8E0[];

void func_8003AF8C(Unk_8003AF8C *arg0, s32 arg1) {
    ((Unk_8003AF8C_Mgr *)func_80018390())->unk8(arg0);
    arg0->unk0 = func_8003B20C();
    if (D_8008A8DC == 0) {
        CdInit();
        D_8008A8DC = 1;
    }
    arg0->unk18 = 0;
    func_80026CFC(arg1);
    arg0->unk0->unk40(arg0, D_8008A8E0, 0);
}

void func_8003B024(void) {
}

void func_8003B02C(struct Unk_8003B02C *arg0, Unk_8003B02C_Pair *arg1, s32 arg2) {
    arg0->unkC = *arg1;
    arg0->unk14 = arg2;
}

INCLUDE_ASM("asm/nonmatchings/game/8003AF8C", func_8003B044);

void func_8003B108(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8003AF8C", func_8003B110);

INCLUDE_ASM("asm/nonmatchings/game/8003AF8C", func_8003B20C);

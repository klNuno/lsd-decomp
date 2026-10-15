#include "common.h"

void GsSetFlatLight(s32 id, void *light, void *arg2);
typedef struct Unk_800429E8 {
    u8 pad0[0xC];
    s32 unkC;
    u8 unk10[0xC];
    s8 unk1C;
    s8 unk1D;
    s8 unk1E;
} Unk_800429E8;
typedef struct Unk_8004297C_Mgr {
    u8 pad_00[0x8];
    void (*unk8)(void **);
} Unk_8004297C_Mgr;
typedef struct Unk_8004297C {
    u8 pad_00[0x8];
    void (*unk8)(s32, s32);
    u8 pad_0C[0x34];
    void (*unk40)(void **, s32);
} Unk_8004297C;
void *func_80018390(void);
Unk_8004297C *func_80042A7C(void);
s32 func_80017B34(s32 size);

s32 func_8004291C(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_80017B34(0x20);
    if (temp_s0 != 0) {
        func_80042A7C()->unk8(temp_s0, arg0);
        return temp_s0;
    }
    return 0;
}

void func_8004297C(void **arg0, s32 arg1) {
    Unk_8004297C *temp_v0;

    ((Unk_8004297C_Mgr *)func_80018390())->unk8(arg0);
    temp_v0 = func_80042A7C();
    *arg0 = temp_v0;
    temp_v0->unk40(arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/8004291C", func_800429E0);

void func_800429E8(Unk_800429E8 *arg0, s32 arg1, s8 *arg2) {
    s32 r;
    s32 g;
    s32 b;

    if (arg1 != 0) {
        r = arg2[0];
        g = arg2[1];
        b = arg2[2];
        arg0->unk1C = r;
        arg0->unk1D = g;
        arg0->unk1E = b;
    }
    GsSetFlatLight(arg0->unkC, arg0->unk10, arg2);
}

void func_80042A2C(Unk_800429E8 *arg0, s32 arg1, s16 *arg2) {
    if (arg1 != 0) {
        *(s32 *)&arg0->unk10[0] = arg2[0];
        *(s32 *)&arg0->unk10[4] = arg2[1];
        *(s32 *)&arg0->unk10[8] = arg2[2];
    }
    GsSetFlatLight(arg0->unkC, arg0->unk10, arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/8004291C", func_80042A7C);

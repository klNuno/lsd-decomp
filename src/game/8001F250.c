#include "common.h"

struct Unk_8001F360 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
};
struct Unk_8001F33C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u32 *unkC;
};
extern void GsMapModelingData(u32 *p);
struct Unk_8001F314_Data {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
};
struct Unk_8001F314 {
    u8 pad_00[0x14];
    struct Unk_8001F314_Data unk14;
};
extern u8 D_8008B21C[];
void func_8001F3B0(void *arg0, u8 *arg1);
struct Unk_800204D0_Q {
    u8 pad_00[0x6];
    u16 unk6;
};
struct Unk_800204D0_P {
    u8 pad_00[0x10];
    struct Unk_800204D0_Q *unk10;
};
struct Unk_800204D0 {
    u8 pad_00[0x10];
    struct Unk_800204D0_P *unk10;
};
struct Unk_800204D0_Arg1 {
    s32 unk0;
    s32 unk4;
};
struct Unk_80020510_Sub {
    u8 pad_00[0x6];
    s16 unk6;
};
struct Unk_80020510_Mid {
    u8 pad_00[0x10];
    struct Unk_80020510_Sub *unk10;
};
struct Unk_80020510 {
    u8 pad_00[0x10];
    struct Unk_80020510_Mid *unk10;
};
struct Unk_80020510_Arg {
    s16 unk0;
    s16 unk2;
};
typedef struct Unk_8001F2B0_Ret {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8001F2B0_Ret;
typedef struct Unk_8001F2B0 {
    s32 unk0;
    u8 pad_04[0x8];
    s32 unkC;
    s32 unk10;
} Unk_8001F2B0;
void *func_80018390(void);
s32 func_8001F384(void);
void func_8001F394(void *arg0);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F250);

void func_8001F2B0(Unk_8001F2B0 *arg0, s32 arg1) {
    s32 temp;

    ((Unk_8001F2B0_Ret *)func_80018390())->unk8(arg0);
    temp = func_8001F384();
    arg0->unk10 = arg1;
    arg0->unk0 = temp;
    arg0->unkC = arg1 - 0xC;
    func_8001F394(arg0);
}

void func_8001F314(struct Unk_8001F314 *arg0, struct Unk_8001F314_Data *arg1) {
    arg0->unk14 = *arg1;
}

void func_8001F33C(struct Unk_8001F33C *arg0) {
    GsMapModelingData(arg0->unkC + 1);
}

s32 func_8001F360(struct Unk_8001F360 *arg0, s32 arg1) {
    s32 offset = arg1 * 0x1C + 0xC;
    return offset + arg0->unkC;
}

void func_8001F37C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F384);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F394);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F3A4);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F3B0);

void func_8001F4E4(void *arg0) {
    func_8001F3B0(arg0, D_8008B21C);
}

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F50C);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F51C);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F66C);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_8001F8B8);

INCLUDE_ASM("asm/nonmatchings/game/8001F250", func_80020050);

void func_800204D0(struct Unk_800204D0 *arg0, struct Unk_800204D0_Arg1 *arg1) {
    struct Unk_800204D0_Q *q = arg0->unk10->unk10;
    q->unk6 += arg1->unk0 / 16;
    q->unk6 += arg1->unk4 * 64;
}

void func_80020510(struct Unk_80020510 *arg0, struct Unk_80020510_Arg *arg1) {
    struct Unk_80020510_Sub *sub = arg0->unk10->unk10;

    sub->unk6 = arg1->unk0 / 16;
    sub->unk6 += arg1->unk2 * 64;
}

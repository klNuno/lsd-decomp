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
struct Unk_8001F250 {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32);
};
void *func_80017B34(s32 size);
struct Unk_8001F51C {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 unk2A;
    u16 unk2C;
    u16 unk2E;
    u16 unk30;
    u16 unk32;
};
struct Unk_8001F51C_tmp {
    s32 one;
    u16 buf[6];
};

void *func_8001F250(s32 arg0) {
    void *temp;

    temp = func_80017B34(0x24);
    if (temp != 0) {
        ((struct Unk_8001F250 *)func_8001F384())->unk8(temp, arg0);
        return temp;
    }
    return 0;
}

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

void func_8001F51C(void *arg0, struct Unk_8001F51C *arg1) {
    struct Unk_8001F51C_tmp t;

    func_8001F3B0(arg0, (u8 *)t.buf);
    t.one = 1;
    arg1->unk4 = t.buf[0];
    arg1->unk6 = t.buf[1];
    arg1->unk8 = t.buf[2];
    arg1->unkA = t.buf[0];
    arg1->unkC = t.buf[4];
    arg1->unkE = t.buf[2];
    arg1->unk10 = t.buf[3];
    arg1->unk12 = t.buf[4];
    arg1->unk14 = t.buf[2];
    arg1->unk16 = t.buf[3];
    arg1->unk18 = t.buf[1];
    arg1->unk1A = t.buf[2];
    arg1->unk1C = t.buf[0];
    arg1->unk1E = t.buf[1];
    arg1->unk20 = t.buf[5];
    arg1->unk22 = t.buf[0];
    arg1->unk24 = t.buf[4];
    arg1->unk26 = t.buf[5];
    arg1->unk28 = t.buf[3];
    arg1->unk2A = t.buf[4];
    arg1->unk2C = t.buf[5];
    arg1->unk2E = t.buf[3];
    arg1->unk30 = t.buf[1];
    arg1->unk32 = t.buf[5];
    arg1->unk0 = 1;
}

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

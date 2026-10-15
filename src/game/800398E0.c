#include "common.h"

extern void SsSeqSetVol(s16, s16, s16);
struct Unk_80039DF4 {
    u8 pad_00[0x14];
    s16 unk14;
};
extern void SsSeqReplay(s16);
typedef struct Unk_80039DB0 {
    u8 pad_00[0x14];
    s16 unk14;
    u8 pad_16[0x6];
    u16 unk1C;
} Unk_80039DB0;
extern void SsSeqPause(s16);
struct Unk_80039D68 {
    u8 pad_00[0x14];
    s16 unk14;
    u8 pad_16[0x6];
    u16 unk1C;
};
extern void SsSeqStop(s16);
extern void SsSeqClose(s16);
typedef struct Unk_80039D14 {
    u8 pad_00[0x14];
    s16 unk14;
    u8 pad_16[0x4];
    s16 unk1A;
    u8 pad_1C[0x2];
    u16 unk1E;
} Unk_80039D14;
extern void SsSeqPlay(s16, s16, s16);
typedef struct Unk_80039CBC {
    u8 pad_00[0x14];
    s16 unk14;
    u8 pad_16[0x8];
    u16 unk1E;
} Unk_80039CBC;
extern s32 func_8002CC28(void);
extern void SsSeqSetCrescendo(s16, s16, s32);
extern s32 func_80039C04(void);
typedef struct Unk_80039B90Vt {
    u8 pad_00[0x44];
    void (*unk44)(void *);
} Unk_80039B90Vt;
typedef struct Unk_80039B90 {
    Unk_80039B90Vt *unk0;
    u8 pad_04[0x16];
    u16 unk1A;
    u8 pad_1C[0x4];
    s32 unk20;
} Unk_80039B90;
extern void *func_80017B34(s32 size);
typedef struct Unk_800398E0Vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32, s32);
} Unk_800398E0Vt;
Unk_800398E0Vt *func_8003A04C(void);
extern void *func_80018390(void);
typedef struct Unk_80039B04Vt {
    u8 pad_00[0x38];
    void (*unk38)(void **, s32 **, s32);
} Unk_80039B04Vt;
typedef struct Unk_80039B04 {
    u8 pad_00[0x40];
    void (*unk40)(void **, s32 **, s32);
} Unk_80039B04;
extern s32 func_80020C5C(void);
s32 D_8008A8D8;
typedef struct Unk_80039A34Vt {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0xC];
    void (*unk14)(void *, s32);
    u8 pad_18[0x30];
    void (*unk48)(void *);
} Unk_80039A34Vt;
typedef struct Unk_80039A34Obj {
    Unk_80039A34Vt *vt;
} Unk_80039A34Obj;
typedef struct Unk_80039A34 {
    Unk_80039A34Vt *unk0;
    u8 pad_04[0x8];
    Unk_80039A34Obj *unkC;
    Unk_80039A34Obj *unk10;
    s16 unk14;
} Unk_80039A34;
typedef struct Unk_80039A34Mgr {
    u8 pad_00[0xC];
    void (*unkC)(void *);
} Unk_80039A34Mgr;

void *func_800398E0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v0;

    temp_v0 = func_80017B34(0x24);
    if (temp_v0 != NULL) {
        func_8003A04C()->unk8(temp_v0, arg0, arg1, arg2);
        return temp_v0;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003995C);

void func_80039A34(Unk_80039A34 *arg0) {
    Unk_80039A34Obj *temp_a0;

    D_8008A8D8 = 0;
    arg0->unk0->unk48(arg0);
    SsSeqClose(arg0->unk14);
    temp_a0 = arg0->unkC;
    if (temp_a0 != NULL) {
        temp_a0->vt->unk4(temp_a0);
    }
    temp_a0 = arg0->unk10;
    if (temp_a0 != NULL) {
        temp_a0->vt->unk4(temp_a0);
    }
    arg0->unk0->unk14(arg0, func_80020C5C());
    ((Unk_80039A34Mgr *)func_80018390())->unkC(arg0);
}

void func_80039B04(void **arg0, s32 **arg1, s32 arg2) {
    ((Unk_80039B04Vt *)func_80018390())->unk38(arg0, arg1, arg2);
    if ((**arg1 & 0xF) == 1) {
        ((Unk_80039B04 *)*arg0)->unk40(arg0, arg1, arg2);
    }
}

void func_80039B90(Unk_80039B90 *arg0, s32 arg1, s32 arg2) {
    if ((arg2 == 2) && (arg0->unk1A == 1) && (func_80039C04() != 0) && (arg0->unk20 != 0)) {
        arg0->unk0->unk44(arg0);
    }
}

INCLUDE_RODATA("asm/nonmatchings/game/800398E0", D_80010FEC);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039C04);

void func_80039CBC(Unk_80039CBC *arg0) {
    if (arg0->unk1E == 0) {
        SsSeqSetVol(arg0->unk14, 0x34, 0x34);
        SsSeqPlay(arg0->unk14, 1, 0);
        arg0->unk1E = 1;
    }
}

void func_80039D14(Unk_80039D14 *arg0) {
    if (arg0->unk1E != 0) {
        SsSeqStop(arg0->unk14);
        SsSeqClose(arg0->unk14);
        arg0->unk1E = 0;
        arg0->unk1A = 0;
    }
}

void func_80039D68(struct Unk_80039D68 *arg0) {
    if (arg0->unk1C == 0) {
        SsSeqPause(arg0->unk14);
        arg0->unk1C = 1;
    }
}

void func_80039DB0(Unk_80039DB0 *arg0) {
    if (arg0->unk1C != 0) {
        SsSeqReplay(arg0->unk14);
        arg0->unk1C = 0;
    }
}

void func_80039DF4(struct Unk_80039DF4 *arg0, s16 arg1, s16 arg2) {
    SsSeqSetVol(arg0->unk14, arg1, arg2);
}

void func_80039E24(struct Unk_80039DF4 *arg0, s16 arg1, s32 arg2) {
    SsSeqSetCrescendo(arg0->unk14, arg1, func_8002CC28() * arg2);
}

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039E7C);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039F64);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003A04C);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003A05C);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003A068);

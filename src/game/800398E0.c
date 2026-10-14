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

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_800398E0);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003995C);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039A34);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039B04);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039B90);

INCLUDE_RODATA("asm/nonmatchings/game/800398E0", D_80010FEC);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039C04);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039CBC);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039D14);

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

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039E24);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039E7C);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_80039F64);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003A04C);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003A05C);

INCLUDE_ASM("asm/nonmatchings/game/800398E0", func_8003A068);

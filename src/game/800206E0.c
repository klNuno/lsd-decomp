#include "common.h"

typedef struct Unk_8002089C {
    u8 pad[0x10];
    s32 unk10;
} Unk_8002089C;
typedef struct Unk_80020B4C {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad_14[0xC];
    /* 0x20 */ s32 unk20;
} Unk_80020B4C;
void GsSwapDispBuff(void);
extern int GsGetActiveBuff(void);
typedef struct Unk_80020970 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
} Unk_80020970;
typedef struct Unk_80020C08 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad_0C[0x8];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} Unk_80020C08;
typedef struct Unk_8002085C_Obj {
    u8 pad_00[0x68];
    void (*unk68)(void);
} Unk_8002085C_Obj;
typedef struct Unk_8002085C {
    /* 0x00 */ Unk_8002085C_Obj *unk0;
    /* 0x04 */ u8 pad_04[0xC];
    /* 0x10 */ s32 unk10;
} Unk_8002085C;
typedef struct Unk_800206E0 {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_800206E0;
void *func_80017B34(s32 size);
Unk_800206E0 *func_80020C4C(void);
typedef struct Unk_80020A24 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
} Unk_80020A24;
void func_80020970(Unk_80020970 *arg0, Unk_80020970 *arg1);
void MoveImage(Unk_80020A24 *rect, s32 x, s32 y);
typedef struct Unk_80020784_Obj {
    u8 pad_00[0x70];
    void (*unk70)(void *, s32);
    u8 pad_74[0xC];
    void (*unk80)(void *, s32);
} Unk_80020784_Obj;
typedef struct Unk_80020784 {
    /* 0x00 */ Unk_80020784_Obj *unk0;
    /* 0x04 */ u8 pad_04[0xC];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad_14[0x1C];
    /* 0x30 */ s32 unk30;
} Unk_80020784;
typedef struct Unk_80020AF4 {
    /* 0x00 */ u8 pad_00[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 pad_10[0x10];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
} Unk_80020AF4;
Unk_80020AF4 *func_80020C5C(void);
typedef struct Unk_80020730 {
    u8 pad_00[0x40];
    void (*unk40)(void *);
} Unk_80020730;
void *func_80018390(void);
typedef struct Unk_800208F8 {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad_14[0x18];
    /* 0x2C */ s32 unk2C;
} Unk_800208F8;
s32 LoadImage(Unk_80020A24 *rect, u32 *p);
s32 DrawSync(s32 mode);
typedef struct Unk_800209A0 {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad_14[0x18];
    /* 0x2C */ s32 unk2C;
} Unk_800209A0;
extern s32 DrawSync(s32);
void StoreImage(Unk_80020A24 *rect, u32 *arg1);
void GsInitGraph(u16 x, u16 y, u16 intmode, u16 dith, u16 vrammode);
void GsDefDispBuff(u16 x0, u16 y0, u16 x1, u16 y1);
typedef struct Unk_800207DC_Pair {
    s32 unk0;
    s32 unk4;
} Unk_800207DC_Pair;
typedef struct Unk_800207DC {
    u8 pad_00[0x14];
    Unk_800207DC_Pair unk14;
    s32 unk1C;
} Unk_800207DC;
typedef struct Unk_800207DC_Src {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
} Unk_800207DC_Src;
typedef struct Unk_80020A74_vt {
    /* 0x00 */ u8 pad_00[0x30];
    /* 0x30 */ void (*unk30)(void *, s32);
} Unk_80020A74_vt;
typedef struct Unk_80020A74 {
    /* 0x00 */ Unk_80020A74_vt *unk0;
    /* 0x04 */ u8 pad_04[0xC];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad_14[0xC];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad_24[0xC];
    /* 0x30 */ void (*unk30)(void);
} Unk_80020A74;
s32 VSync(s32 mode);
typedef struct Unk_80020B74 {
    u8 pad_00[0x78];
    void (*unk78)(void **, void *, Unk_80020A24 *);
    void (*unk7C)(void **, Unk_80020A24 *);
} Unk_80020B74;
void ClearImage(Unk_80020A24 *rect, u8 r, u8 g, u8 b);
extern Unk_800206E0 D_8006C070;
Unk_80020AF4 *D_8008A83C;

void *func_800206E0(void) {
    void *temp;

    temp = func_80017B34(0x34);
    if (temp != 0) {
        func_80020C4C()->unk8(temp);
        return temp;
    }
    return 0;
}

void func_80020730(void **arg0) {
    void *temp_v0;

    ((Unk_800206E0 *)func_80018390())->unk8(arg0);
    temp_v0 = func_80020C4C();
    *arg0 = temp_v0;
    ((Unk_80020730 *)temp_v0)->unk40(arg0);
}

void func_80020784(Unk_80020784 *arg0) {
    arg0->unk10 = 0;
    arg0->unk0->unk70(arg0, 3);
    arg0->unk0->unk80(arg0, 1);
    arg0->unk30 = 0;
}

void func_800207DC(Unk_800207DC *arg0, Unk_800207DC_Src *arg1, s32 arg2) {
    GsInitGraph(arg1->unk0, arg1->unk4, 0, 1, arg2);
    GsDefDispBuff(0, 0, 0, arg1->unk4);
    arg0->unk14 = *(Unk_800207DC_Pair *)arg1;
    arg0->unk1C = arg2;
}

void func_8002085C(Unk_8002085C *arg0) {
    if (arg0->unk10 == 0) {
        arg0->unk10 = 1;
        arg0->unk0->unk68();
    }
}

void func_8002089C(Unk_8002089C *arg0) {
    if (arg0->unk10 != 0) {
        arg0->unk10 = 0;
    }
}

void func_800208B8(void) {
    GsSwapDispBuff();
}

void func_800208D8(void) {
    GsGetActiveBuff();
}

void func_800208F8(Unk_800208F8 *arg0, Unk_80020970 *arg1, u32 *arg2) {
    Unk_80020A24 sp10;

    if ((arg0->unk10 == 0) || (arg0->unk2C != 0)) {
        func_80020970((Unk_80020970 *)&sp10, arg1);
        LoadImage(&sp10, arg2);
        if (arg0->unk2C != 0) {
            DrawSync(0);
        }
    }
}

void func_80020970(Unk_80020970 *arg0, Unk_80020970 *arg1) {
    arg0->unk0 = arg1->unk0;
    arg0->unk2 = arg1->unk2;
    arg0->unk4 = arg1->unk4;
    arg0->unk6 = arg1->unk8;
}

void func_800209A0(Unk_800209A0 *arg0, u32 *arg1, Unk_80020970 *arg2) {
    Unk_80020A24 sp10;

    if ((arg0->unk10 == 0) || (arg0->unk2C != 0)) {
        func_80020970((Unk_80020970 *)&sp10, arg2);
        StoreImage(&sp10, arg1);
        if (arg0->unk2C != 0) {
            DrawSync(0);
        }
    }
}

s32 func_80020A1C(void) {
    return 0;
}

void func_80020A24(void *arg0, Unk_80020970 *arg1, s16 arg2, s16 arg3) {
    Unk_80020A24 sp10;

    func_80020970((Unk_80020970 *)&sp10, arg1);
    MoveImage(&sp10, arg2, arg3);
}

void func_80020A74(Unk_80020A74 *arg0) {
    while (arg0->unk10 != 0) {
        VSync(arg0->unk20);
        if (arg0->unk30 != NULL) {
            arg0->unk30();
        }
        arg0->unk0->unk30(arg0, 2);
    }
}

void func_80020AF4(void) {
    Unk_80020AF4 *temp;

    temp = func_80020C5C();
    if (++temp->unk24 >= temp->unk20 && temp->unkC == 0) {
        temp->unkC = 1;
        temp->unk24 = 0;
    }
}

void func_80020B4C(Unk_80020B4C *arg0, s32 arg1) {
    if (arg0->unk10 == 0) {
        arg0->unk20 = arg1;
    }
}

s32 func_80020B68(Unk_80020B4C *arg0) {
    return arg0->unk20;
}

void func_80020B74(void **arg0, u8 *arg1, s32 arg2) {
    Unk_80020970 sp10;
    Unk_80020A24 sp20;

    if (arg2 == 0) {
        ((Unk_80020B74 *)*arg0)->unk7C(arg0, (Unk_80020A24 *)&sp10);
        ((Unk_80020B74 *)*arg0)->unk78(arg0, arg1, (Unk_80020A24 *)&sp10);
        return;
    }
    func_80020970((Unk_80020970 *)&sp20, (Unk_80020970 *)arg2);
    ClearImage(&sp20, arg1[0], arg1[1], arg1[2]);
}

s32 *func_80020C08(Unk_80020C08 *arg0, Unk_80020C08 *arg1) {
    if (arg1 != NULL) {
        arg1->unk0 = 0;
        arg1->unk2 = 0;
        arg1->unk4 = arg0->unk14;
        arg1->unk8 = arg0->unk18 * 2;
    }
    return &arg0->unk14;
}

void func_80020C3C(Unk_800209A0 *arg0, s32 arg1) {
    arg0->unk2C = arg1;
}

void func_80020C44(Unk_80020784 *arg0, s32 arg1) {
    arg0->unk30 = arg1;
}

Unk_800206E0 *func_80020C4C(void) {
    return &D_8006C070;
}

Unk_80020AF4 *func_80020C5C(void) {
    return D_8008A83C;
}

void func_80020C68(Unk_80020AF4 *arg0) {
    D_8008A83C = arg0;
}

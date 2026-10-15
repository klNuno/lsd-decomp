#include "common.h"

typedef struct { u8 pad[0xA8]; u8 unkA8; } Unk_80041C28;
struct Unk_800425D8 {
    struct Unk_800425EC_vt *unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
};
struct Unk_80042828 {
    u8 pad_00[0x44];
    s32 unk44[1];
};
struct Unk_80041E2C {
    s32 unk0;
    s32 unk4;
};
struct Unk_80041E2C_obj {
    u8 pad_00[0xC];
    s32 unkC;
    u8 pad_10[0x90];
    struct Unk_80041E2C unkA0;
};
s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
struct Unk_80041BAC;
struct Unk_80041BAC_vtbl {
    u8 pad_00[0xC4];
    void (*unkC4)(struct Unk_80041BAC *, u8);
};
struct Unk_80041BAC {
    struct Unk_80041BAC_vtbl *unk0;
};
typedef struct {
    u8 pad[0xC];
    s32 uC;
    u8 pad2[0x6C - 0x10];
    u16 u6C;
    u16 u6E;
    u8 pad3[0x7C - 0x70];
    u16 u7C;
    u16 u7E;
} Unk_80041E58;
typedef struct Unk_8004229C_Rgb {
    s8 r;
    s8 g;
    s8 b;
} Unk_8004229C_Rgb;
struct Unk_8004229C {
    u8 pad_00[0x78];
    Unk_8004229C_Rgb unk78;
};
struct Unk_800423A8;
struct Unk_800423A8_vt {
    u8 pad_00[0xC];
    void (*unkC)(struct Unk_800423A8 *);
};
struct Unk_800423A8 {
    u8 pad_00[0x2C];
    s32 unk2C;
};
struct Unk_800423A8_vt *func_80026CAC(void);
struct Unk_800424A8 {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    void (*unkC)(s32);
    u8 pad_10[0x14];
    void (*unk24)(void *, s32);
};
struct Unk_800424A8 *func_80018390(void);
struct Unk_80041BDC {
    u8 pad_00[0x72];
    u8 unk72;
    u8 unk73;
    u8 pad_74[0xA8 - 0x74];
    u8 unkA8;
};
void func_80041C4C();
struct Unk_80042400_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    u8 pad_0C[0x34];
    void (*unk40)(void *, s32);
};
void *func_80017B34(s32 arg0);
struct Unk_80042400_vt *func_80042684(void);
struct Unk_80042694_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
};
struct Unk_80042694_vt *func_800428E4(void);
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_8004202C_Src;
struct Unk_8004202C {
    u8 pad_00[0x48];
    s32 unk48;
    Unk_8004202C_Src unk4C;
    s32 unk58;
    u8 pad_5C[0x64 - 0x5C];
    u8 unk64[1];
};
void func_8004208C(u8 *arg0, s32 arg1, Unk_8004202C_Src *arg2, s32 arg3);
struct Unk_800422CC_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32);
};
struct Unk_800422CC_vt *func_800423F0(void);
struct Unk_800425EC_vt {
    u8 pad_00[0x30];
    void (*unk30)(void *, s32);
};
typedef struct Unk_80041C3C {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32);
    u8 pad_0C[0x34];
    void (*unk40)(void *, s32);
} Unk_80041C3C;
void *func_80017B34(s32 size);
Unk_80041C3C *func_80041C3C(void);
struct Unk_80041C4C {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    s32 unk8;
};
extern struct Unk_80041C4C D_8006ED40;
struct Unk_800424E0_Node {
    struct Unk_800424E0_Node *unk0;
    s32 unk4;
};
struct Unk_800424E0 {
    u8 pad_00[0x18];
    struct Unk_800424E0_Node *unk18;
};
struct Unk_80041ED8_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32, s32);
};
struct Unk_80041ED8_vt *func_80041ED8(void);
struct Unk_80041DAC_vt;
struct Unk_80041DAC {
    struct Unk_80041DAC_vt *unk0;
    u8 pad_04[0x8];
    s32 unkC;
};
struct Unk_80041DAC_vt {
    u8 pad_00[0xBC];
    void (*unkBC)(struct Unk_80041DAC *, s32);
};
struct Unk_80041DAC_mgr_vt {
    u8 pad_00[0x4C];
    void (*unk4C)(struct Unk_80041DAC *, s32, void *);
};
struct Unk_80041DAC_mgr_vt *func_800422BC(void);
extern s32 D_8006EE10[3];
typedef struct Unk_80042790_vt {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0xB8 - 0x8];
    void **(*unkB8)(void *, s32);
} Unk_80042790_vt;
typedef struct Unk_80042790_ret_vt {
    u8 pad_00[0xC];
    void (*unkC)(void *);
} Unk_80042790_ret_vt;
Unk_80042790_ret_vt *func_8001E57C(void);
void func_80041C4C(struct Unk_80041C4C *arg0, u32 arg1);
struct Unk_80041D18;
struct Unk_80041D18_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32, s32);
    u8 pad_0C[0x34];
    void (*unk40)(void *);
};
struct Unk_80041D18 {
    struct Unk_80041D18_vt *unk0;
};
struct Unk_80041D18_mgr_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32, s32, s32, s32, s32);
};
struct Unk_80041DAC;
struct Unk_80042170 {
    u8 pad_00[0x84];
    s32 unk84;
};
struct Unk_80042170_src {
    u8 pad_00[0x8];
    s16 unk8;
    s16 unkA;
};
struct Unk_8004232C_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
};
struct Unk_8004232C_unk0_vt {
    u8 pad_00[0x6C];
    void (*unk6C)(void *, s8 *);
};
struct Unk_8004232C {
    struct Unk_8004232C_unk0_vt *unk0;
    u8 pad_04[0x28];
    s32 unk2C;
};
s8 *strcpy(s8 *dst, s8 *src);
struct Unk_80041F88_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
};
struct Unk_80041F88_mgr_vt {
    u8 pad_00[0x40];
    void (*unk40)(void *, s32, s32, s32, s32, s32);
};
struct Unk_8004283C {
    u8 pad_00[0x50];
    Unk_8004229C_Rgb unk50;
};
void GsSetAmbient(s32 r, s32 g, s32 b);

void *func_80041AB4(s32 arg0, u8 arg1) {
    void *temp;

    temp = func_80017B34(0xAC);
    if (temp != NULL) {
        func_80041C3C()->unk8(temp, arg0, arg1);
        return temp;
    }
    return NULL;
}

void func_80041B20(void **arg0, s32 arg1, u8 arg2) {
    struct Unk_80041C4C sp10;
    Unk_80041C3C *vt;

    func_80041C4C(&sp10, 0x20);
    func_80041ED8()->unk8(arg0, arg1, (s32)&sp10, 0);
    vt = func_80041C3C();
    *arg0 = vt;
    vt->unk40(arg0, arg2);
}

void func_80041BAC(struct Unk_80041BAC *arg0, u8 arg1) {
    arg0->unk0->unkC4(arg0, arg1);
}

void func_80041BDC(struct Unk_80041BDC *arg0, u8 arg1) {
    u8 sp10[12];

    arg0->unkA8 = arg1;
    func_80041C4C(sp10, arg1);
    arg0->unk72 = sp10[0];
    arg0->unk73 = sp10[2];
}

u8 func_80041C28(Unk_80041C28 *arg0) {
    s32 buf[4];
    return arg0->unkA8;
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041C3C);

void func_80041C4C(struct Unk_80041C4C *arg0, u32 arg1) {
    *arg0 = D_8006ED40;
    arg1 = arg1 & 0xFF;
    arg0->unk0 = arg0->unk0 + ((arg1 & 0x1F) * 8);
    arg0->unk2 = arg0->unk2 + ((arg1 >> 5) * 8);
}

void *func_80041C9C(s32 arg0, s32 arg1, s32 arg2) {
    void *temp;

    temp = func_80017B34(0xA8);
    if (temp != 0) {
        func_80041ED8()->unk8(temp, arg0, arg1, arg2);
        return temp;
    }
    return 0;
}

void func_80041D18(struct Unk_80041D18 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    ((struct Unk_80041D18_mgr_vt *)func_800422BC())->unk8(arg0, arg1, 0, arg2, 0, arg3);
    arg0->unk0 = (struct Unk_80041D18_vt *)func_80041ED8();
    arg0->unk0->unk40(arg0);
}

void func_80041DA4(void) {
}

void func_80041DAC(struct Unk_80041DAC *arg0, s32 arg1, s32 arg2) {
    if (arg0->unkC == 0) {
        func_800422BC()->unk4C(arg0, arg1, D_8006EE10);
        arg0->unk0->unkBC(arg0, arg2);
    }
}

void func_80041E2C(struct Unk_80041E2C_obj *arg0, struct Unk_80041E2C *arg1) {
    if (arg0->unkC != 0) {
        arg0->unkA0 = *arg1;
    }
}

void func_80041E58(Unk_80041E58 *arg0, s32 arg1) {
    if (arg0->uC != 0) {
        switch (arg1) {
        case 0:
            arg0->u7C = arg0->u6C >> 1;
            arg0->u7E = arg0->u6E >> 1;
            break;
        case 1:
            arg0->u7C = 0;
            break;
        case 2:
            arg0->u7C = arg0->u6C;
            break;
        case 3:
            arg0->u7E = 0;
            break;
        case 4:
            arg0->u7E = arg0->u6E;
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80041ED8);

void *func_80041EE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp;

    temp = func_80017B34(0xA0);
    if (temp != 0) {
        ((struct Unk_80041D18_mgr_vt *)func_800422BC())->unk8(temp, arg0, arg1, arg2, arg3, arg4);
        return temp;
    }
    return 0;
}

void func_80041F88(void **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *temp;

    ((struct Unk_80041F88_vt *)func_8001E57C())->unk8(arg0);
    temp = func_800422BC();
    *arg0 = temp;
    ((struct Unk_80041F88_mgr_vt *)temp)->unk40(arg0, arg1, arg2, arg3, arg4, arg5);
}

void func_8004202C(struct Unk_8004202C *arg0, s32 arg1, s32 arg2, Unk_8004202C_Src *arg3) {
    arg0->unk48 = arg1 + 0x2C;
    arg0->unk4C = *arg3;
    func_8004208C(arg0->unk64, arg2, arg3, arg0->unk48);
    arg0->unk58 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004208C);

void func_80042170(struct Unk_80042170 *arg0, s32 arg1, struct Unk_80042170_src *arg2) {
    s32 temp_a0_2;

    temp_a0_2 = ((arg2->unk8 / arg2->unkA) << 12) + (((arg2->unk8 % arg2->unkA) << 12) / arg2->unkA);
    if (arg1 != 0) {
        arg0->unk84 = temp_a0_2;
        return;
    }
    arg0->unk84 = temp_a0_2 + arg0->unk84;
}

s32 func_8004220C(u8 *arg0, s32 arg1) {
    return func_8001EDAC((s32 *)(arg0 + 0x64), 0x1F, 1, arg1 == 0) == 0;
}

void func_8004223C(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x64), 0x1E, 1, arg1 != 0);
}

void func_80042268(u8 *arg0, s32 arg1) {
    func_8001EDAC((s32 *)(arg0 + 0x64), 0x1C, 2, arg1);
}

void func_80042294(void) {
}

void func_8004229C(struct Unk_8004229C *arg0, Unk_8004229C_Rgb *arg1) {
    arg0->unk78 = *arg1;
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800422BC);

s32 func_800422CC(s32 arg0) {
    void *temp;

    temp = func_80017B34(0x30);
    if (temp != 0) {
        func_800423F0()->unk8(temp, arg0);
        return (s32)temp;
    }
    return 0;
}

void func_8004232C(struct Unk_8004232C *arg0, s8 *arg1) {
    char sp10[0x20];

    ((struct Unk_8004232C_vt *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = ((struct Unk_8004232C_unk0_vt *)func_800423F0());
    arg0->unk2C = 0;
    if (arg1 != NULL) {
        strcpy(sp10, arg1);
        arg0->unk0->unk6C(arg0, sp10);
    }
}

void func_800423A8(struct Unk_800423A8 *arg0) {
    arg0->unk2C = 0;
    func_80026CAC()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800423E4);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800423F0);

void *func_80042400(void) {
    void *temp;

    temp = func_80017B34(0x1C);
    if (temp != 0) {
        func_80042684()->unk8(temp);
        return temp;
    }
    return 0;
}

void func_80042450(void **arg0) {
    struct Unk_80042400_vt *temp_v0;

    func_80018390()->unk8(arg0);
    temp_v0 = func_80042684();
    *arg0 = temp_v0;
    temp_v0->unk40(arg0, 0);
}

void func_800424A8(s32 arg0) {
    func_80018390()->unkC(arg0);
}

void func_800424E0(struct Unk_800424E0 *arg0, s32 arg1) {
    struct Unk_800424E0_Node *node;

    node = arg0->unk18;
    if (node != NULL && arg1 == node->unk4) {
        arg0->unk18 = node->unk0;
    }
    func_80018390()->unk24(arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042550);

void func_800425D8(struct Unk_800425D8 *arg0, s32 arg1) {
    arg0->unkC = arg1;
    arg0->unk14 = 0;
    arg0->unk10 = 0;
    arg0->unk18 = 0;
}

void func_800425EC(struct Unk_800425D8 *arg0) {
    s32 var_a1 = 4;

    if (arg0->unk14 == 0) {
        var_a1 = 3;
        if (arg0->unk10 == 0) {
            var_a1 = 2;
            arg0->unkC++;
        }
    }
    arg0->unk0->unk30(arg0, var_a1);
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004264C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042658);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042664);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_8004266C);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042678);

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042684);

void *func_80042694(void) {
    void *temp;

    temp = func_80017B34(0x54);
    if (temp != 0) {
        func_800428E4()->unk8(temp);
        return temp;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800426E4);

void func_80042790(void **arg0) {
    s32 i;
    void **child;

    for (i = 0; i < 3; i++) {
        child = ((Unk_80042790_vt *)*arg0)->unkB8(arg0, i);
        ((Unk_80042790_vt *)*child)->unk4(child);
    }
    func_8001E57C()->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_80042814);

void func_80042820(void) {
}

s32 func_80042828(struct Unk_80042828 *arg0, s32 arg1) {
    return arg0->unk44[arg1];
}

void func_8004283C(struct Unk_8004283C *arg0, Unk_8004229C_Rgb *arg1, s32 arg2) {
    Unk_8004229C_Rgb sp10;

    if (arg2 != 0) {
        sp10 = arg0->unk50;
        arg0->unk50 = *arg1;
        *arg1 = sp10;
    } else {
        arg0->unk50 = *arg1;
    }
    GsSetAmbient((u8)arg0->unk50.r * 0x10, (u8)arg0->unk50.g * 0x10, (u8)arg0->unk50.b * 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game/80041AB4", func_800428E4);

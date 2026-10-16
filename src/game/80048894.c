#include "common.h"

extern u8 D_80081A04[];
extern s16 g_videoTable[];
s32 D_8008A964;
s32 D_8008A968;
u8 *Stage_GetPathBase(s32 arg0);
s32 *func_80048DF8(void);
extern void srand(u32 seed);
extern s32 rand(void);
void *func_80048D48(s32 *arg0);
s32 Heap_Free(s32);
typedef struct Unk_80048C98 {
    u8 pad_00[0x2E];
    s16 unk2E;
    u8 pad_30[4];
    s32 unk34;
} Unk_80048C98;
u8 *func_8004903C(s32 arg0);
typedef struct Unk_80048A68 {
    u8 pad_00[0x2A];
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
} Unk_80048A68;
typedef struct Unk_80048A68_Vtbl {
    u8 pad_00[0xC];
    void (*unkC)(void *);
    u8 pad_10[0x64];
    void (*unk74)(Unk_80048A68 *);
} Unk_80048A68_Vtbl;
Unk_80048A68_Vtbl *func_80026CAC(void);
s32 func_800491CC(s32 *arg0);
struct Unk_80048B78_Vtbl {
    u8 pad_00[0x5C];
    void (*unk5C)(void);
};
struct Unk_80048B78 {
    struct Unk_80048B78_Vtbl *unk0;
    u8 pad_04[0x28];
    s16 unk2C;
    u8 pad_2E[2];
    s16 unk30;
};
typedef struct Unk_80048894 {
    u8 pad_00[8];
    void (*unk8)(s32);
} Unk_80048894;
Unk_80048894 *func_80048CE0(void);
s32 Heap_Alloc(s32 arg0);
extern s16 D_800819E8[];
typedef struct { s16 unk_0; s16 unk_2; s32 unk_4; } Unk_800861D4;
Unk_800861D4 *func_800494D8(s32 arg0);
u8 *func_80049060(s32 arg0, s32 arg1);
u8 *func_80049240(s32 *arg0);
typedef struct Unk_80048960 Unk_80048960;
typedef struct Unk_80048960_Vtbl {
    u8 pad_00[0x84];
    void (*unk84)(Unk_80048960 *);
} Unk_80048960_Vtbl;
struct Unk_80048960 {
    Unk_80048960_Vtbl *vt;
};
u8 *Cine_GetEventPath(s32 *arg0, s32 arg1);
s32 Cine_GetSpecialDayPaths(s32 *arg0, s32 arg1);
typedef struct Unk_80049334 {
    s16 unk0;
    s16 unk2;
} Unk_80049334;
typedef struct Unk_800488E4_vt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_800488E4_vt;
typedef struct Unk_800488E4 {
    Unk_800488E4_vt *unk0;
    u8 pad_04[0xC];
    void *unk10;
    s32 unk14;
    u8 pad_18[0x14];
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s32 unk34;
    s32 unk38;
} Unk_800488E4;
typedef struct Unk_800489B4_Vtbl {
    u8 pad_00[0x80];
    void (*unk80)(void);
} Unk_800489B4_Vtbl;
typedef struct Unk_800489B4_GVtbl {
    u8 pad_00[0x64];
    void (*unk64)(void *);
} Unk_800489B4_GVtbl;
typedef struct Unk_800489B4 {
    Unk_800489B4_Vtbl *unk0;
    u8 pad_04[0x20];
    s32 unk24;
    u8 pad_28[2];
    u16 unk2A;
    s16 unk2C;
    s16 unk2E;
    u8 pad_30[8];
    s32 unk38;
} Unk_800489B4;
s32 Rand_SeedAndNext();
u8 *func_80048F60(s32 arg0);
u8 *func_80048E80(s32 arg0);
typedef struct Unk_80048AAC_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, s32, s32);
    void (*unk48)(void *);
    u8 pad_4C[0x8];
    void (*unk54)(void *, void *, s32);
    u8 pad_58[0x1C];
    void (*unk74)(void *);
} Unk_80048AAC_Vtbl;
typedef struct Unk_80048AAC {
    Unk_80048AAC_Vtbl *unk0;
    u8 pad_04[0xC];
    void *unk10;
    u8 pad_14[0x16];
    u16 unk2A;
    s16 unk2C;
} Unk_80048AAC;
typedef struct Unk_80048BC0 Unk_80048BC0;
typedef struct Unk_80048BC0_Vtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(Unk_80048BC0 *, s32, s32);
    u8 pad_50[4];
    void (*unk54)(Unk_80048BC0 *, s32, s32);
    u8 pad_58[0x2C];
    void (*unk84)(Unk_80048BC0 *);
} Unk_80048BC0_Vtbl;
typedef struct Unk_80048BC0_Sub {
    u8 pad_00[2];
    u16 unk2;
    u8 pad_04[0xC];
    s32 unk10;
    s32 unk14;
} Unk_80048BC0_Sub;
struct Unk_80048BC0 {
    Unk_80048BC0_Vtbl *unk0;
    u8 pad_04[0xC];
    Unk_80048BC0_Sub *unk10;
    u8 pad_14[0x16];
    u16 unk2A;
    u8 pad_2C[8];
    s32 unk34;
};
u8 *func_80048D64(void);
s32 func_80049110(s32 *arg0);
typedef struct Unk_80048CD8 {
    u8 pad_00[0x38];
    s32 unk38;
} Unk_80048CD8;
extern u8 D_80081940[];
void *D_8008A960;
extern u8 D_800819CC[];
extern s32 D_8008A96C[];

s32 func_80048894(void) {
    s32 temp_v0;

    temp_v0 = Heap_Alloc(0x3C);
    if (temp_v0 != 0) {
        func_80048CE0()->unk8(temp_v0);
        return temp_v0;
    }
    return 0;
}

void func_800488E4(Unk_800488E4 *arg0) {
    ((Unk_800488E4_vt *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = ((Unk_800488E4_vt *)func_80048CE0());
    arg0->unk30 = -1;
    arg0->unk2C = 0;
    arg0->unk2E = 0;
    arg0->unk32 = 0;
    arg0->unk34 = 0;
    arg0->unk38 = 1;
    arg0->unk10 = ((void *)Heap_Alloc(0xB358));
    if (arg0->unk10 != NULL) {
        arg0->unk14 = 0xB358;
    }
}

void func_80048960(Unk_80048960 *arg0) {
    arg0->vt->unk84(arg0);
    func_80026CAC()->unkC(arg0);
}

void func_800489B4(Unk_800489B4 *arg0) {
    u16 temp_v1;

    temp_v1 = arg0->unk2A;
    if (temp_v1 == 9) {
        if (arg0->unk24 & 0x80) {
            s32 temp_v1_2 = arg0->unk38;

            arg0->unk2A = 0;
            arg0->unk2C = 1;
            if (temp_v1_2 != 0) {
                arg0->unk0->unk80();
            }
        }
    } else if (temp_v1 == 0xA) {
        if (arg0->unk24 & 0x80) {
            arg0->unk2E = 1;
            arg0->unk2A = 0;
        }
    }
    ((Unk_800489B4_GVtbl *)func_80026CAC())->unk64(arg0);
}

void func_80048A68(Unk_80048A68 *arg0) {
    func_80026CAC()->unk74(arg0);
    arg0->unk2C = 0;
    arg0->unk2E = 0;
    arg0->unk2A = 0;
}

void func_80048AAC(Unk_80048AAC *arg0, s32 arg1) {
    if ((arg0->unk10 != NULL) && (arg1 != 0)) {
        if (arg0->unk2A == 0) {
            arg0->unk2C = 0;
        } else {
            arg0->unk0->unk74(arg0);
        }
        arg0->unk2A = 9;
        arg0->unk0->unk48(arg0);
        arg0->unk0->unk44(arg0, arg1, 1, 0);
        arg0->unk0->unk54(arg0, arg0->unk10, 0xB358);
    }
}

void func_80048B78(struct Unk_80048B78 *arg0) {
    arg0->unk0->unk5C();
    arg0->unk2C = 0;
    arg0->unk30 = -1;
}

s32 func_80048BC0(Unk_80048BC0 *arg0) {
    s32 temp_s1;
    s32 temp_v0;

    if ((arg0->unk10->unk2 != 0) && (arg0->unk2A == 0)) {
        arg0->unk0->unk84(arg0);
        temp_s1 = arg0->unk10->unk14;
        temp_v0 = Heap_Alloc(temp_s1);
        arg0->unk34 = temp_v0;
        if (temp_v0 != 0) {
            arg0->unk2A = 10;
            arg0->unk0->unk4C(arg0, arg0->unk10->unk10, 0);
            arg0->unk0->unk54(arg0, arg0->unk34, temp_s1);
            return 1;
        }
    }
    return 0;
}

void func_80048C98(Unk_80048C98 *arg0) {
    s32 temp_a0;

    temp_a0 = arg0->unk34;
    arg0->unk2E = 0;
    if (temp_a0 != 0) {
        arg0->unk34 = Heap_Free(temp_a0);
    }
}

void func_80048CD8(Unk_80048CD8 *arg0, s32 arg1) {
    arg0->unk38 = arg1;
}

Unk_80048894 *func_80048CE0(void) {
    return (Unk_80048894 *)D_80081940;
}

void *func_80048CF0(void) {
    return D_8008A960;
}

s32 Rand_SeedAndNext(seed)
    s32 seed;
{
    if (seed != 0) {
        srand(seed);
    }
    return rand();
}

void Music_SetOverride(s32 arg0, s32 arg1) {
    if (arg0 >= 0) {
        D_8008A964 = arg0;
    }
    if (arg1 >= 0) {
        D_8008A968 = arg1;
    }
}

void *func_80048D48(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0x230;
    }
    return D_80081A04;
}

u8 *func_80048D64(void) {
    return D_800819CC;
}

s32 Music_PickBank(s32 arg0) {
    s32 r;
    u8 *p;
    s32 ofs;

    r = (u32)Rand_SeedAndNext(0, arg0) % 7;
    p = func_80048D64();
    if (D_8008A964 != 0) {
        ofs = (D_8008A964 - 1) * 4;
    } else {
        ofs = r * 4;
    }
    return *(s32 *)(p + ofs);
}

s32 *func_80048DF8(void) {
    return D_8008A96C;
}

s32 func_80048E08(void) {
    return *func_80048DF8();
}

u8 *Stage_GetPathBase(s32 arg0) {
    return (u8 *)func_80048D48(NULL) + D_800819E8[arg0] * 0x1C;
}

u8 *func_80048E80(s32 arg0) {
    return Stage_GetPathBase(arg0);
}

u8 *Stage_PickTexturePath(s32 arg0, s32 arg1, s32 arg2) {
    s32 row;
    s32 r;

    row = ((arg2 - 1) % 40) / 10 + 1;
    r = Rand_SeedAndNext(0, arg1) % row;
    return func_80048E80(arg0) + r * 0x1C;
}

u8 *func_80048F60(s32 arg0) {
    return Stage_GetPathBase(arg0) + 0x70;
}

u8 *Music_PickTrack(s32 arg0) {
    u32 var_s0;
    u8 *temp_a0;
    s32 var_v0;

    var_s0 = (u32)Rand_SeedAndNext(0) % 5;
    if (arg0 == 9) {
        if (var_s0 == 2) {
            var_s0 = 3;
        }
        if (D_8008A968 == 3) {
            D_8008A968 = 4;
        }
    }
    temp_a0 = func_80048F60(arg0);
    if (D_8008A968 != 0) {
        var_v0 = (D_8008A968 - 1) * 7;
    } else {
        var_v0 = var_s0 * 7;
    }
    return temp_a0 + (var_v0 * 4);
}

u8 *func_8004903C(s32 arg0) {
    return Stage_GetPathBase(arg0) + 0xFC;
}

u8 *func_80049060(s32 arg0, s32 arg1) {
    return func_8004903C(arg0) + arg1 * 0x1C;
}

void func_80049098(s32 arg0, s32 arg1, s32 arg2) {
    func_80049060(arg0, arg1 + (func_800494D8(arg0)->unk_0 * arg2));
}

INCLUDE_RODATA("asm/nonmatchings/game/80048894", D_80011384);

char *func_800490F4(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0x31;
    }
    return "ETC\\ASMK.STR";
}

s32 func_80049110(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0;
    }
    return (s32)func_80048D48(NULL) + 0x3D40;
}

s32 func_8004913C(s32 *arg0) {
    s32 sp10;
    s32 r;
    s32 ret;

    r = (u32)Rand_SeedAndNext(0) % 7;
    ret = func_80049110(&sp10);
    if (arg0 != NULL) {
        *arg0 = r + sp10;
    }
    return ret + r * 0x1C;
}

s32 func_800491CC(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 7;
    }
    return (s32)func_80048D48(NULL) + 0x3E04;
}

s32 func_800491FC(s32 *arg0) {
    s32 sp10;
    s32 temp_v1;

    temp_v1 = func_800491CC(&sp10);
    if (arg0 != NULL) {
        *arg0 = sp10;
    }
    return temp_v1;
}

u8 *func_80049240(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 8;
    }
    return (u8 *)func_80048D48(NULL) + 0x3E20;
}

u8 *Cine_GetEventPath(s32 *arg0, s32 arg1) {
    s32 sp10;
    u8 *temp_v1;

    temp_v1 = func_80049240(&sp10);
    if (arg0 != NULL) {
        *arg0 = arg1 + sp10;
    }
    return temp_v1 + arg1 * 0x1C;
}

s32 Cine_GetSpecialDayPaths(s32 *arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = (s32)func_80048D48(NULL) + 0x3EC8;
    if (arg0 != NULL) {
        *arg0 = (arg1 * 2) + 0xE;
    }
    return temp_v1 + (arg1 * 0xA8);
}

s32 Cine_GetPath(s32 *arg0, Unk_80049334 arg1) {
    s32 sp10;
    s32 temp_v0;
    s32 var_v1;

    if (arg1.unk0 >= 0) {
        temp_v0 = Cine_GetSpecialDayPaths(&sp10, arg1.unk0);
        if (arg0 != NULL) {
            if ((u16)arg1.unk2 < 2U) {
                var_v1 = arg1.unk2 + sp10;
            } else {
                var_v1 = -1;
            }
            *arg0 = var_v1;
        }
        return temp_v0 + (arg1.unk2 * 0x1C);
    }
    return (s32)Cine_GetEventPath(arg0, arg1.unk2);
}

s16 func_800493C8(s32 arg0) {
    return g_videoTable[arg0];
}

s32 func_800493E4(s32 *arg0, s32 arg1, s32 arg2) {
    s32 start;
    s32 ret;
    s32 i;

    ret = Cine_GetSpecialDayPaths(&start, arg1);
    *arg0 = 0;
    arg2 *= 2;
    arg2 += start;
    for (i = start; i < arg2; i++) {
        *arg0 += 10 + g_videoTable[i];
    }
    *arg0 -= 10;
    return ret;
}

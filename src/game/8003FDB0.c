#include "common.h"

s32 func_8001EDAC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct PosPair {
    s32 unk_00;
    s32 unk_04;
} PosPair;
typedef struct Unk_800407F8 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x50 - 0x10];
    PosPair unk_50;
} Unk_800407F8;
typedef struct Unk_80040824 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x60 - 0x10];
    u16 unk_60;
    u16 unk_62;
} Unk_80040824;
extern u8 g_fadePalette[][3];
extern u8 D_8006EAA8[3];
typedef struct Unk_80040490 {
    u8 pad_00[0x50];
    PosPair unk_50;
    u8 pad_58[0x60 - 0x58];
    u16 unk_60;
    u16 unk_62;
    u8 pad_64[0x88 - 0x64];
    u16 unk_88;
    u8 pad_8A[0x8C - 0x8A];
    u16 unk_8C;
    u8 pad_8E[0x90 - 0x8E];
    PosPair unk_90;
} Unk_80040490;
typedef struct Unk_80040EDC_obj Unk_80040EDC_obj;
typedef struct Unk_80040EDC_vt {
    u8 pad_00[0xC4];
    void (*unk_C4)(Unk_80040EDC_obj *, u8, Unk_80040EDC_obj **);
} Unk_80040EDC_vt;
struct Unk_80040EDC_obj {
    Unk_80040EDC_vt *unk_00;
};
typedef struct Unk_80040EDC {
    u8 pad_00[0xB4];
    Unk_80040EDC_obj **unk_B4;
} Unk_80040EDC;
typedef struct Unk_80040854_Vtbl {
    u8 pad_00[0x4C];
    void (*unk_4C)(void);
} Unk_80040854_Vtbl;
typedef struct Unk_80040854 {
    Unk_80040854_Vtbl *unk_00;
    u8 pad_04[0x44];
    s32 unk_48;
    s32 unk_4C;
} Unk_80040854;
typedef struct Unk_80040A30_obj {
    u8 pad_00[0xC];
    void (*unk_0C)(void *);
} Unk_80040A30_obj;
typedef struct Unk_80040A30 {
    u8 pad_00[0xA9];
    u8 unk_A9;
    u8 pad_AA[0xB4 - 0xAA];
    Unk_80040EDC_obj **unk_B4;
} Unk_80040A30;
void Object_DeleteArray(void *, s32);
void *Heap_Free(void *);
Unk_80040A30_obj *func_80041C3C(void);
typedef struct Unk_8004042C {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x50 - 0x10];
    PosPair unk_50;
    u8 pad_58[0x60 - 0x58];
    u16 unk_60;
    u16 unk_62;
    u8 pad_64[0x88 - 0x64];
    s32 unk_88;
    s32 unk_8C;
    PosPair unk_90;
} Unk_8004042C;
typedef struct Unk_80040A88_vt {
    u8 pad_00[0xCC];
    void (*unk_CC)(void *, s32);
    s32 unk_D0;
    void (*unk_D4)(void *, s32);
} Unk_80040A88_vt;
typedef struct Unk_80040A88 {
    Unk_80040A88_vt *unk_00;
} Unk_80040A88;
typedef struct FadeObj FadeObj;
typedef struct FadeObjVtbl {
    u8 pad_00[0x10];
    void (*unk_10)(FadeObj *);
    void (*unk_14)(FadeObj *, s32);
    u8 pad_18[0x30 - 0x18];
    void (*unk_30)(FadeObj *, s32);
    u8 pad_34[0x60 - 0x34];
    void (*unk_60)(FadeObj *, s32);
    void (*unk_64)(FadeObj *, s32);
    void (*unk_68)(FadeObj *, s32);
    u8 pad_6C[0xB8 - 0x6C];
    void (*unk_B8)(FadeObj *, s32, u8 *);
    u8 pad_BC[0xDC - 0xBC];
    s32 (*unk_DC)(FadeObj *, s32, s32, s32);
} FadeObjVtbl;
struct FadeObj {
    FadeObjVtbl *unk_00;
    u8 pad_04[0x68 - 0x4];
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    u8 pad_88[0x98 - 0x88];
    s32 unk_98;
    s32 unk_9C;
};
typedef struct EffectVtbl {
    u8 pad_00[0x8];
    void (*unk_08)(void *, s32, s32, s32);
    u8 pad_0C[0x40 - 0xC];
    void (*unk_40)(void *, s32);
} EffectVtbl;
void *Heap_Alloc(s32 size);
EffectVtbl *Effect_GetVtbl(void);
typedef struct Unk_800404D0 {
    u8 pad_00[0x8];
    void (*unk_08)(void *, s32, u8 *, s32);
    u8 pad_0C[0x40 - 0xC];
    void (*unk_40)(void *, s32, s32, s32);
} Unk_800404D0;
Unk_800404D0 *func_800408BC(void);
typedef struct Rgb {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} Rgb;

void Rgb_CopyOrAdd(void *arg0, Rgb *dst, Rgb *src, s32 copy);
typedef struct Unk_80040664_vt {
    u8 pad_00[0xBC];
    void (*unk_BC)(void *, s32);
} Unk_80040664_vt;
typedef struct Unk_80040664 {
    Unk_80040664_vt *unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} Unk_80040664;
typedef struct Unk_80040664_mgr {
    u8 pad_00[0x4C];
    void (*unk_4C)(Unk_80040664 *, s32, s32);
} Unk_80040664_mgr;
Unk_80040664_mgr *func_8001E57C(void);
typedef struct Unk_800405D0 Unk_800405D0;
typedef struct Unk_800405D0_vt {
    u8 pad_00[0xB8];
    void (*unk_B8)(void *, s32, u8 *);
    u8 pad_BC[0xCC - 0xBC];
    void (*unk_CC)(void *, s32);
} Unk_800405D0_vt;
struct Unk_800405D0 {
    Unk_800405D0_vt *unk_00;
    u8 pad_04[0x44 - 0x4];
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    u8 pad_50[0x58 - 0x50];
    s32 unk_58;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
};
extern u8 D_8008A924[];
typedef struct Unk_8004054C_vt {
    u8 pad_00[0x8];
    void (*unk_08)(void *slot);
} Unk_8004054C_vt;
typedef struct Unk_800408CC_obj {
    u8 pad_00[0x8];
    void (*unk_08)(void *, s32, s32, s32);
} Unk_800408CC_obj;
Unk_800408CC_obj *func_80040FB0(void);
typedef struct Unk_80040D74_obj Unk_80040D74_obj;
typedef struct Unk_80040D74_vt {
    u8 pad_00[0xB8];
    void (*unk_B8)(void *, s32);
} Unk_80040D74_vt;
struct Unk_80040D74_obj {
    Unk_80040D74_vt *unk_00;
};
typedef struct Unk_80040D74 {
    u8 pad_00[0xAB];
    u8 unk_AB;
    u8 unk_AC;
    u8 pad_AD[0xB4 - 0xAD];
    Unk_80040D74_obj **unk_B4;
} Unk_80040D74;
typedef struct Unk_80040CD0_obj Unk_80040CD0_obj;
typedef struct Unk_80040CD0_vt {
    u8 pad_00[0x60];
    s32 (*unk_60)(Unk_80040CD0_obj *, void *, s32);
} Unk_80040CD0_vt;
struct Unk_80040CD0_obj {
    Unk_80040CD0_vt *unk_00;
};
typedef struct Unk_80040CD0 {
    u8 pad_00[0xAB];
    u8 unk_AB;
    u8 unk_AC;
    u8 pad_AD[0xB4 - 0xAD];
    Unk_80040CD0_obj **unk_B4;
} Unk_80040CD0;
typedef struct Unk_80040E14_vt {
    u8 pad_00[0xBC];
    void (*unk_BC)(void *, void *);
} Unk_80040E14_vt;
typedef struct Unk_80040E14_obj {
    Unk_80040E14_vt *unk_00;
} Unk_80040E14_obj;
typedef struct Unk_80040E14 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xA9 - 0x10];
    u8 unk_A9;
    u8 pad_AA[0xB0 - 0xAA];
    s32 unk_B0;
    Unk_80040E14_obj **unk_B4;
} Unk_80040E14;
typedef struct Unk_80040C00_obj Unk_80040C00_obj;
typedef struct Unk_80040C00_vt {
    u8 pad_00[0x50];
    void (*unk_50)(Unk_80040C00_obj *);
} Unk_80040C00_vt;
struct Unk_80040C00_obj {
    Unk_80040C00_vt *unk_00;
};
typedef struct Unk_80040C00_tbl {
    u8 pad_00[0x50];
    void (*unk_50)(void *);
} Unk_80040C00_tbl;
typedef struct Unk_80040C00 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xAB - 0x10];
    u8 unk_AB;
    u8 unk_AC;
    u8 pad_AD[0xB4 - 0xAD];
    Unk_80040C00_obj **unk_B4;
} Unk_80040C00;
typedef struct RgbFadeObjVtbl {
    u8 pad_00[0xE0];
    void (*unk_E0)(void *);
} RgbFadeObjVtbl;
typedef struct RgbFadeObj {
    RgbFadeObjVtbl *unk_00;
    u8 pad_04[0x64 - 0x4];
    u8 unk_64;
    u8 unk_65;
    u8 unk_66;
    u8 pad_67[0x74 - 0x67];
    u8 unk_74;
    u8 pad_75[0x78 - 0x75];
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
} RgbFadeObj;
typedef struct Unk_80040A30_80040948 {
    EffectVtbl *unk_00;
    u8 pad_04[0xA9 - 0x4];
    u8 unk_A9;
    u8 unk_AA;
    u8 unk_AB;
    u8 unk_AC;
    u8 pad_AD[0xB4 - 0xAD];
    Unk_80040EDC_obj **unk_B4;
} Unk_80040A30_80040948;
typedef struct Unk_80040948_tbl {
    u8 pad_00[0x8];
    void (*unk_08)(void *, s32, s32);
} Unk_80040948_tbl;
void *func_80041AB4(s32, u8);
s8 *itoa(s32 value);
s8 *strcpy(s8 *dst, s8 *src);
s32 strlen(u8 *s);
void *memset(void *dst, s32 c, s32 n);
s8 *Text_Encode(s8 *dst, u8 *src);
typedef struct Unk_80040AE8_obj Unk_80040AE8_obj;
typedef struct Unk_80040AE8_vt {
    u8 pad_00[0x4C];
    void (*unk_4C)(void *, void *, PosPair *);
} Unk_80040AE8_vt;
struct Unk_80040AE8_obj {
    Unk_80040AE8_vt *unk_00;
};
typedef struct Unk_80040AE8_mgr {
    u8 pad_00[0x4C];
    void (*unk_4C)(void *, s32, PosPair *);
} Unk_80040AE8_mgr;
typedef struct Unk_80040AE8 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xAA - 0x10];
    u8 unk_AA;
    u8 unk_AB;
    u8 unk_AC;
    u8 pad_AD[0xB0 - 0xAD];
    s32 unk_B0;
    Unk_80040AE8_obj **unk_B4;
} Unk_80040AE8;
extern u8 g_effectVtbl[];
typedef struct Unk_800408A0 {
    u8 pad_00[0x44];
    s32 unk_44;
} Unk_800408A0;
extern u8 D_8006EAC0[];
typedef struct Unk_80040FA8 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} Unk_80040FA8;
extern u8 D_8006EB90[];

void *Effect_Create(s32 arg0, s32 arg1, s32 arg2) {
    void *obj;

    obj = Heap_Alloc(0xA0);
    if (obj != NULL) {
        Effect_GetVtbl()->unk_08(obj, arg0, arg1, arg2);
        return obj;
    }
    return NULL;
}

void Effect_Spawn(void **slot, s32 arg1, s32 colorIndex, s32 arg3) {
    Unk_800404D0 *mgr;
    u8 *color;
    EffectVtbl *obj;

    mgr = func_800408BC();
    if (colorIndex != 0) {
        color = g_fadePalette[colorIndex];
    } else {
        color = D_8006EAA8;
    }
    mgr->unk_08(slot, arg1, color, arg3);
    obj = Effect_GetVtbl();
    *slot = obj;
    obj->unk_40(slot, colorIndex);
}

void Fade_Init(FadeObj *fade, s32 step) {
    fade->unk_70 = step;
    fade->unk_6C = 0;
    fade->unk_74 = 0xA;
    fade->unk_78 = 0;
    fade->unk_7C = 0;
    fade->unk_00->unk_60(fade, 0);
    fade->unk_00->unk_64(fade, 0);
    fade->unk_98 = 0;
}

void RgbFade_Step(RgbFadeObj *fade, s32 arg1, s32 mode) {
    if (mode == 2) {
        if (fade->unk_80-- > 0) {
            if (fade->unk_7C != 9) {
                if (fade->unk_78 & 4) {
                    fade->unk_64 += fade->unk_74;
                }
                if (fade->unk_78 & 2) {
                    fade->unk_65 += fade->unk_74;
                }
                if (fade->unk_78 & 1) {
                    fade->unk_66 += fade->unk_74;
                }
            }
        } else {
            fade->unk_00->unk_E0(fade);
        }
    }
}

void Fade_SetStep(FadeObj *fade, s32 step) {
    fade->unk_74 = step;
}

void Fade_Start(FadeObj *fade, s32 arg1, s32 arg2, s32 arg3) {
    s32 idx;
    if (fade->unk_6C == 0) {
        idx = fade->unk_00->unk_DC(fade, arg1, arg2, arg3);
        fade->unk_00->unk_B8(fade, 1, g_fadePalette[idx]);
        fade->unk_6C = 1;
        fade->unk_74 = -fade->unk_74;
    }
}

void Fade_StartDirect(FadeObj *fade, s32 arg1, s32 arg2, s32 arg3) {
    if (fade->unk_6C == 0) {
        arg2 = fade->unk_00->unk_DC(fade, arg1, arg2, arg3);
        if (fade->unk_98 != 0) {
            fade->unk_80--;
        } else {
            fade->unk_00->unk_B8(fade, 1, &D_8006EAA8[arg2 * 3]);
        }
        fade->unk_6C = 2;
    }
}

s32 Fade_Update(FadeObj *fade, s32 arg1, s32 arg2, s32 arg3) {
    FadeObjVtbl *vt;
    s32 colorIndex;
    s32 mode;
    s32 steps;

    vt = fade->unk_00;
    colorIndex = arg2;
    if (colorIndex < 0) {
        colorIndex = fade->unk_70;
    } else {
        fade->unk_70 = colorIndex;
    }
    mode = 1;
    if (colorIndex != 0) {
        fade->unk_78 = colorIndex;
    } else {
        mode = 2;
        fade->unk_78 = 0xF;
    }
    fade->unk_78 = colorIndex;
    if (colorIndex == 0) {
        fade->unk_78 = 0xF;
    }
    steps = 0x100 / fade->unk_74;
    fade->unk_7C = arg3;
    fade->unk_80 = steps;
    if (fade->unk_98 != 0) {
        fade->unk_80 = steps - steps / fade->unk_9C;
    }
    arg2 = fade->unk_68 / fade->unk_80;
    fade->unk_84 = arg2;
    vt->unk_10(fade);
    vt->unk_64(fade, 1);
    vt->unk_68(fade, mode);
    vt->unk_60(fade, 1);
    return colorIndex;
}

void Fade_Stop(FadeObj *fade, s32 arg1) {
    FadeObjVtbl *vt = fade->unk_00;
    s32 sel;

    if (fade->unk_6C == 0) {
        return;
    }
    if (fade->unk_6C == 1) {
        sel = 5;
        if (fade->unk_98 == 0) {
            vt->unk_60(fade, 0);
            vt->unk_64(fade, 0);
        }
    } else {
        sel = 6;
        if (fade->unk_98 != 0) {
            if (fade->unk_78 == 0xF) {
                vt->unk_B8(fade, 1, D_8006EAA8);
            }
            vt->unk_64(fade, 0);
        }
    }
    vt->unk_14(fade, arg1);
    if (fade->unk_74 < 0) {
        fade->unk_74 = -fade->unk_74;
    }
    fade->unk_6C = 0;
    vt->unk_30(fade, sel);
}

u8 *Fade_GetColor(FadeObj *fade) {
    s32 index = fade->unk_78;

    if (index == 0xF) {
        return D_8006EAA8;
    }
    return g_fadePalette[index];
}

void Pos_SetSaved(Unk_8004042C *obj, u16 *pos16, PosPair *pos) {
    if (obj->unk_0C != 0) {
        obj->unk_88 = obj->unk_60;
        obj->unk_8C = obj->unk_62;
        obj->unk_90 = obj->unk_50;
        obj->unk_60 = pos16[0];
        obj->unk_62 = pos16[2];
        obj->unk_50 = *pos;
    }
}

void Pos_Restore(Unk_80040490 *obj) {
    obj->unk_50 = obj->unk_90;
    obj->unk_60 = obj->unk_88;
    obj->unk_62 = obj->unk_8C;
}

void Fade_SetFlag(FadeObj *fade, s32 flag, s32 divisor) {
    fade->unk_98 = flag;
    fade->unk_9C = divisor;
}

EffectVtbl *Effect_GetVtbl(void) {
    return (EffectVtbl *)g_effectVtbl;
}

void *func_800404D0(s32 arg0, s32 arg1, s32 arg2) {
    void *obj;

    obj = Heap_Alloc(0x6C);
    if (obj != NULL) {
        func_800408BC()->unk_08(obj, arg0, arg1, arg2);
        return obj;
    }
    return NULL;
}

void func_8004054C(void **slot, s32 arg1, s32 arg2, s32 arg3) {
    Unk_800404D0 *obj;

    ((Unk_8004054C_vt *)func_8001E57C())->unk_08(slot);
    obj = func_800408BC();
    *slot = obj;
    obj->unk_40(slot, arg1, arg2, arg3);
}

void func_800405D0(Unk_800405D0 *obj, u16 *pos16, u8 *data, s32 arg3) {
    Unk_800405D0_vt *vt;

    obj->unk_44 = arg3;
    obj->unk_48 = 1;
    obj->unk_4C = 0;
    obj->unk_58 = 0;
    obj->unk_5C = 0;
    obj->unk_5E = 0;
    obj->unk_60 = pos16[0];
    obj->unk_62 = pos16[2];
    vt = obj->unk_00;
    if (data == NULL) {
        data = D_8008A924;
    }
    vt->unk_B8(obj, 1, data);
    obj->unk_00->unk_CC(obj, 0xD);
}

void func_80040664(Unk_80040664 *obj, s32 arg1, s32 arg2) {
    if (obj->unk_0C == 0) {
        func_8001E57C()->unk_4C(obj, arg1, 0);
        obj->unk_00->unk_BC(obj, arg2);
    }
}

s32 func_800406E4(u8 *obj, s32 arg1) {
    return func_8001EDAC((s32 *)(obj + 0x58), 0x1F, 1, arg1 == 0) == 0;
}

void func_80040714(u8 *obj, s32 arg1) {
    func_8001EDAC((s32 *)(obj + 0x58), 0x1E, 1, arg1 != 0);
}

void func_80040740(u8 *obj, s32 arg1) {
    func_8001EDAC((s32 *)(obj + 0x58), 0x1C, 2, arg1);
}

void Rgb_ApplyToObj(u8 *obj, s32 copy, u8 *src) {
    Rgb_CopyOrAdd(obj, obj + 0x64, src, copy);
}

void Rgb_CopyOrAdd(void *arg0, Rgb *dst, Rgb *src, s32 copy) {
    if (copy != 0) {
        *dst = *src;
        return;
    }
    dst->unk_00 += src->unk_00;
    dst->unk_01 += src->unk_01;
    dst->unk_02 += src->unk_02;
}

void Pos_Set(Unk_800407F8 *obj, PosPair *pos) {
    if (obj->unk_0C != 0) {
        obj->unk_50 = *pos;
    }
}

void Pos_Set16(Unk_80040824 *obj, u16 *pos16) {
    if (obj->unk_0C != 0) {
        obj->unk_60 = pos16[0];
        obj->unk_62 = pos16[2];
    }
}

void func_80040854(Unk_80040854 *obj, s32 arg1, s32 arg2, s32 value) {
    obj->unk_00->unk_4C();
    obj->unk_48 = 0;
    obj->unk_4C = value;
}

void func_800408A0(Unk_800408A0 *obj, s32 value) {
    obj->unk_44 = value;
}

void Fade_SetMask(FadeObj *fade, s32 bits) {
    fade->unk_68 = (1 << bits) - 1;
}

Unk_800404D0 *func_800408BC(void) {
    return (Unk_800404D0 *)D_8006EAC0;
}

s32 func_800408CC(s32 arg0, s32 arg1, s32 arg2) {
    s32 obj = Heap_Alloc(0xB8);

    if (obj != 0) {
        func_80040FB0()->unk_08((void *)obj, arg0, arg1, arg2);
        return obj;
    }
    return 0;
}

void Object_InitArray(Unk_80040A30_80040948 *arr, s32 arg1, s32 count, s32 arg3) {
    Unk_80040EDC_obj **items;
    s32 i;

    ((Unk_80040948_tbl *)((Unk_80040A30_obj *)func_80041C3C()))->unk_08(arr, arg1, 0x20);
    arr->unk_00 = (EffectVtbl *)((Unk_800408CC_obj *)func_80040FB0());
    arr->unk_A9 = count;
    arr->unk_AB = count;
    arr->unk_AC = 0;
    arr->unk_AA = 0;
    items = ((void *)Heap_Alloc(count * 4));
    if (items != NULL) {
        arr->unk_B4 = items;
        for (i = 0; i < count; i++) {
            *items = func_80041AB4(arg1, 0x20);
            items += 1;
        }
        arr->unk_00->unk_40(arr, arg3);
    }
}

void Object_DestroyArray(Unk_80040A30 *arr) {
    Object_DeleteArray(arr->unk_B4, arr->unk_A9);
    arr->unk_B4 = Heap_Free(arr->unk_B4);
    func_80041C3C()->unk_0C(arr);
}

void func_80040A88(Unk_80040A88 *obj, s32 arg1) {
    obj->unk_00->unk_D4(obj, 7);
    obj->unk_00->unk_CC(obj, arg1);
}

void Object_PlaceArray(Unk_80040AE8 *arr, s32 arg1, PosPair *origin) {
    PosPair pos;
    Unk_80040AE8_obj **p;
    s32 i;

    if (arr->unk_0C == 0) {
        ((Unk_80040AE8_mgr *)func_80041C3C())->unk_4C(arr, arg1, origin);
        pos = *origin;
        p = &arr->unk_B4[arr->unk_AC];
        for (i = arr->unk_AC; i < arr->unk_AC + arr->unk_AB; i++) {
            if (arr->unk_AA != 0 && i == arr->unk_AA) {
                pos.unk_00 += 0x10;
            }
            (*p)->unk_00->unk_4C(*p, arr, &pos);
            pos.unk_00 += arr->unk_B0;
            p++;
        }
    }
}

void func_80040C00(Unk_80040C00 *arr) {
    s32 i;
    Unk_80040C00_obj **p;
    Unk_80040C00_obj *obj;

    if (arr->unk_0C != 0) {
        if (arr->unk_B4 != NULL) {
            p = &arr->unk_B4[arr->unk_AC];
            for (i = arr->unk_AC; i < arr->unk_AC + arr->unk_AB; i++) {
                obj = *p++;
                obj->unk_00->unk_50(obj);
            }
        }
        ((Unk_80040C00_tbl *)func_80041C3C())->unk_50(arr);
    }
}

s32 Object_QueryArray(Unk_80040CD0 *arr, void *arg1, s32 arg2) {
    s32 i;
    Unk_80040CD0_obj **p;
    Unk_80040CD0_obj *obj;

    p = &arr->unk_B4[arr->unk_AC];
    for (i = arr->unk_AC; i < arr->unk_AC + arr->unk_AB; i++) {
        obj = *p++;
        arg2 = obj->unk_00->unk_60(obj, arg1, arg2);
    }
    return arg2;
}

void Object_SendArray(Unk_80040D74 *arr, s32 arg1) {
    s32 i;
    Unk_80040D74_obj **p;
    Unk_80040D74_obj *obj;

    p = &arr->unk_B4[arr->unk_AC];
    for (i = arr->unk_AC; i < arr->unk_AC + arr->unk_AB; i++) {
        obj = *p++;
        obj->unk_00->unk_B8(obj, arg1);
    }
}

void Object_PlaceAll(Unk_80040E14 *arr, PosPair *origin) {
    PosPair pos;
    Unk_80040E14_obj **p;
    Unk_80040E14_obj *obj;
    s32 i;

    if (arr->unk_0C != 0) {
        ((Unk_80040E14_vt *)func_80041C3C())->unk_BC(arr, origin);
        pos = *origin;
        p = arr->unk_B4;
        for (i = 0; i < arr->unk_A9; p++, i++) {
            obj = *p;
            obj->unk_00->unk_BC(obj, &pos);
            pos.unk_00 += arr->unk_B0;
        }
    }
}

void Object_SendAt(Unk_80040EDC *arr, s32 arg1, s32 index) {
    Unk_80040EDC_obj **slot = &arr->unk_B4[index];
    Unk_80040EDC_obj *obj = *slot;

    obj->unk_00->unk_C4(obj, arg1, slot);
}

void func_80040F20(void) {
}

void Object_SendText(Unk_80040EDC *arr, u8 *text) {
    Unk_80040EDC_obj **p = arr->unk_B4;

    if (text != NULL) {
        while (*text != 0) {
            Unk_80040EDC_obj *obj = *p;

            ((void (*)(Unk_80040EDC_obj *, u8))obj->unk_00->unk_C4)(obj, *text++);
            p++;
        }
    }
}

void func_80040FA0(void) {
}

void Object_SetSpacing(Unk_80040FA8 *obj, s32 spacing) {
    obj->unk_B0 = spacing;
}

Unk_800408CC_obj *func_80040FB0(void) {
    return (Unk_800408CC_obj *)D_8006EB90;
}

s8 *Text_Decode(s8 *dst, u8 *src) {
    s8 *end = dst;
    s8 *out;
    u8 c;
    s32 value;
    s32 k;

    c = *src++;
    if (c != 0) {
        k = 0x40;
        out = dst;
        do {
            out++;
            c = *src;
            end++;
            if (c >= 0x80 || c == k) {
                value = c - 0x20;
            } else {
                value = c - 0x1F;
            }
            out[-1] = value;
            src++;
        } while (*src++ != 0);
    }
    *end = 0;
    return end;
}

s8 *Text_Encode(s8 *dst, u8 *src) {
    s8 *next;
    s8 *out;
    u8 c;
    s32 hi;
    s32 lo;

    next = dst;
    out = dst;
    while (*src != 0) {
        next++;
        hi = 0x81;
        if (*src >= 0x30) {
            hi = 0x82;
        }
        *out = hi;
        out = next;
        c = *src;
        next++;
        if (c >= 0x60 || c == 0x20) {
            lo = c + 0x20;
        } else {
            lo = c + 0x1F;
        }
        src++;
        *out = lo;
        out = next;
    }
    *next = 0;
    return next;
}

void Text_FormatNumber(s8 *dst, s32 value, s32 width, s32 noPad) {
    char digits[width + 1];
    char padded[width + 1];
    s32 pad;
    u8 *src;

    pad = strlen(strcpy(digits, itoa(value)));
    pad = width - pad;
    if (noPad == 0) {
        memset(padded, 0x30, width);
        strcpy(padded + pad, digits);
    }
    src = padded;
    if (noPad != 0) {
        src = digits;
    }
    Text_Encode(dst, src);
}

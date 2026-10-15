#include "common.h"

typedef struct Unk_80026C88 {
    u8 pad[0x24];
    u32 unk24;
} Unk_80026C88;
void func_8004A070(s32);
struct Unk_80026CE8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
s32 D_8008A84C;
void func_800280D0(void);
void func_800280E0(void);
s32 func_80027EC8(void);
s32 func_80027ED4(void);
s32 func_80027EE0(void);
s32 func_80027EEC(void);
void *func_80027E68(void);
void *func_8002C438(void);
s32 func_8002C448(s32 *arg0);
s32 func_80027EF8(s32 *arg0);
s32 func_8002C478(void);
s32 func_80028B6C(void);
typedef struct Unk_80026AB4_Vtbl {
    u8 pad_00[0x48];
    void (*unk48)(void);
    u8 pad_4C[0x5C - 0x4C];
    void (*unk5C)(void *);
} Unk_80026AB4_Vtbl;
typedef struct Unk_80026AB4 {
    Unk_80026AB4_Vtbl *vtbl;
} Unk_80026AB4;
void func_80048CFC(s32, s32);
typedef struct Unk_80026A50_Vtbl {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_80026A50_Vtbl;
typedef struct Unk_80026A50 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad_04[0x8];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad_18[0x8];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
} Unk_80026A50;
void *func_80018390(void);
s32 func_80026C9C(void);
typedef struct Unk_80026108 {
    u8 pad_00[0x18];
    s32 unk18;
} Unk_80026108;
typedef struct Unk_80026108_Obj {
    u8 pad_00[0x44];
    void (*unk44)(Unk_80026108 *, s32, s32, s32);
} Unk_80026108_Obj;
extern void *func_8003B20C(void);
typedef struct Unk_800269F0_Vtbl {
    u8 pad_00[0xC];
    void (*unkC)(void *);
} Unk_800269F0_Vtbl;
typedef struct Unk_800269F0 {
    Unk_800269F0_Vtbl *vt;
    u8 pad_04[0x20 - 0x4];
    s16 unk20;
} Unk_800269F0;
void func_80017CFC(void *);
typedef struct Unk_80026C20 {
    u8 pad_00[0x10];
    void *unk10;
    s32 unk14;
    u8 pad_18[0x20 - 0x18];
    u16 unk20;
} Unk_80026C20;
s8 *strcat(s8 *, s8 *);
typedef struct Unk_80026518_Vtbl {
    u8 pad_00[0x4];
    s32 (*unk4)(void *);
    u8 pad_08[0x44 - 0x8];
    s32 (*unk44)(void *, s32, s32);
} Unk_80026518_Vtbl;
typedef struct Unk_80026518 {
    Unk_80026518_Vtbl *vt;
} Unk_80026518;
typedef struct Unk_80025F7C {
    s32 unk0;
    void (*unk4)(void);
    void (*unk8)(s32, s32);
} Unk_80025F7C;
s32 func_80017B34(s32);
Unk_80025F7C *func_800269E0(void);
s32 func_8002C468(s32, s32, s32);
s32 func_80027F18(s32, s32, s32);
typedef struct Unk_80026D88 {
    u8 pad_00[0x40];
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    u8 pad_5C[0x68 - 0x5C];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
} Unk_80026D88;
s32 D_8008A850;
void func_80027FD8(s32);
void func_80027FE4(s32);
s32 func_80027FF0(void);
s32 func_80027FFC(s32, s32);
void func_80026D88(Unk_80026D88 *arg0, Unk_80026D88 *arg1);
extern s32 (*D_8006D4AC[])();
typedef struct Unk_80025FDC_Obj {
    u8 pad_00[0x8];
    void (*unk8)(void *, s32);
    u8 pad_0C[0x40 - 0xC];
    void (*unk40)(void *);
} Unk_80025FDC_Obj;
typedef struct Unk_80025FDC_Vtbl {
    u8 pad_000[0x228];
    void (*unk228)(void *, s32);
} Unk_80025FDC_Vtbl;
typedef struct Unk_80025FDC_VObj {
    Unk_80025FDC_Vtbl *vt;
} Unk_80025FDC_VObj;
typedef struct Unk_80025FDC_Arg1 {
    s32 unk0;
    u8 pad_04[0x10];
    s32 unk14;
} Unk_80025FDC_Arg1;
typedef struct Unk_80025FDC {
    Unk_80025F7C *unk0;
    u8 pad_04[0x20 - 0x4];
    void *unk20;
    s32 unk24;
    Unk_80025FDC_VObj *unk28;
} Unk_80025FDC;
void *func_80048CF0(void);
void func_800270AC(void *);
s32 func_80043840(s32 arg0);
void *func_80058774(s32 arg0, s32 arg1, s32 arg2);
typedef struct Unk_80026348_Sub {
    u8 pad_00[0x8];
    s32 unk8;
    s32 unkC;
} Unk_80026348_Sub;
typedef struct Unk_80026348 {
    u8 pad_00[0x1C];
    s32 unk1C;
    Unk_80026348_Sub *unk20;
} Unk_80026348;
typedef struct Unk_80026348_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x44 - 0x8];
    void (*unk44)(void *, s32, char *, s32, s32);
} Unk_80026348_Vtbl;
typedef struct Unk_80026348_Obj {
    Unk_80026348_Vtbl *vt;
} Unk_80026348_Obj;
void func_80026F34(s32 arg0, s32 arg1, s32 arg2);
s32 func_8003B854(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8004913C(s32 *arg0, s32 arg1);
s32 func_800493C8(s32 arg0);
typedef struct Unk_80026254_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x44 - 0x8];
    void (*unk44)(void *, s32, s32);
    u8 pad_48[0x6C - 0x48];
    void (*unk6C)(void *, s32);
    u8 pad_70[0x98 - 0x70];
    void (*unk98)(void *, void (*)(void), void *);
    u8 pad_9C[0xD4 - 0x9C];
    void (*unkD4)(void *, void *, s32);
} Unk_80026254_Vtbl;
typedef struct Unk_80026254_Obj {
    Unk_80026254_Vtbl *vt;
} Unk_80026254_Obj;
s32 func_8003BE94(s32, s32, s32);
void func_80026328(void);
typedef struct Unk_80026900_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x44 - 0x8];
    void (*unk44)(void *, s32, s32, s32, s32);
    u8 pad_48[0x12C - 0x48];
    void (*unk12C)(void *, s32);
} Unk_80026900_Vtbl;
typedef struct Unk_80026900_Obj {
    Unk_80026900_Vtbl *vt;
} Unk_80026900_Obj;
s32 func_800491FC(s32 *arg0, s32 arg1);
char *func_800490F4(s32 *arg0);
typedef struct Unk_80026698_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x44 - 0x8];
    s32 (*unk44)(void *);
    u8 pad_48[0x1A0 - 0x48];
    s32 (*unk1A0)(void *, s32 *);
} Unk_80026698_Vtbl;
typedef struct Unk_80026698_Obj {
    Unk_80026698_Vtbl *vt;
} Unk_80026698_Obj;
typedef struct Unk_80026348_Sub_80026698 {
    u8 pad_00[0x4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Unk_80026348_Sub_80026698;
typedef struct Unk_80026348_80026698 {
    u8 pad_00[0x1C];
    s32 unk1C;
    Unk_80026348_Sub_80026698 *unk20;
    s32 unk24;
    Unk_80026698_Obj *unk28;
} Unk_80026348_80026698;
s32 func_80049608(s32, s32, s32);
void func_8002677C(Unk_80026348_80026698 *arg0);
typedef struct Unk_8002658C_Vtbl {
    u8 pad_00[0x4];
    void (*unk4)(void *);
    u8 pad_08[0x44 - 0x8];
    void (*unk44)(void *, s32, s32, s32, s32);
    u8 pad_48[0x6C - 0x48];
    void (*unk6C)(void *, s32);
    u8 pad_70[0x12C - 0x70];
    void (*unk12C)(void *, s32);
} Unk_8002658C_Vtbl;
typedef struct Unk_8002658C_Obj {
    Unk_8002658C_Vtbl *vt;
} Unk_8002658C_Obj;
typedef struct Unk_8002658C_Local {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Unk_8002658C_Local;
s32 func_800493E4(s32 *arg0, s32 arg1, s32 arg2);
s32 func_80026518(Unk_80026518 *(*arg0)(s32), s32 arg1, s32 arg2);
extern Unk_80026518 *func_80057F68(s32 arg0);
extern Unk_80026518 *func_8004D518(s32 arg0);
typedef struct Unk_80026B08_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, s32, s32);
    void (*unk48)(void *);
    s32 (*unk4C)(void *, s32, s32);
    u8 pad_50[0x54 - 0x50];
    void (*unk54)(void *, s32, s32);
} Unk_80026B08_Vtbl;
typedef struct Unk_80026B08 {
    Unk_80026B08_Vtbl *vt;
    u8 pad_04[0x0C - 0x04];
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Unk_80026B08;

s32 func_80025F7C(s32 arg0) {
    s32 p;

    p = func_80017B34(0x2C);
    /* No return on the NULL path: v0 still holds p (0) from the allocator. */
    if (p != 0) {
        func_800269E0()->unk8(p, arg0);
        return p;
    }
}

void func_80025FDC(Unk_80025FDC *arg0, Unk_80025FDC_Arg1 *arg1) {
    struct Unk_80026CE8 sp10;

    ((Unk_80025FDC_Obj *)func_8003B20C())->unk8(arg0, arg1->unk0);
    arg0->unk0 = func_800269E0();
    arg0->unk20 = arg1;
    func_800270AC(func_80048CF0());
    sp10.unk0 = 0;
    sp10.unk4 = (s32)"ETC\\DREAME5.TMD";
    arg0->unk28 = (Unk_80025FDC_VObj *)func_80058774(func_80043840((s32)&sp10), 0, 0);
    arg0->unk24 = 0;
    arg0->unk28->vt->unk228(arg0->unk28, arg1->unk14);
    ((Unk_80025FDC_Obj *)arg0->unk0)->unk40(arg0);
}

void func_800260A4(void) {
    func_80048CFC(*(s32 *)0x1F800000 % 365, 0);
}

void func_80026108(Unk_80026108 *arg0, s32 arg1, s32 arg2) {
    if (arg0->unk18 == 0) {
        ((Unk_80026108_Obj *)func_8003B20C())->unk44(arg0, arg1, arg2, 0);
    }
}

void func_80026170(Unk_80026348 *arg0) {
    s32 sp18;
    Unk_80026348_Obj *temp_s1;
    char *temp_s0;

    if (arg0->unk20->unkC != 0) {
        func_80026F34(0, 0, 0);
        func_80026254(arg0, "ETC\\ASMKLOGO.TIM");
        temp_s1 = func_8003B854(0, 0, 0, 0);
        temp_s0 = func_800490F4(&sp18);
        temp_s1->vt->unk44(temp_s1, arg0->unk1C, temp_s0, func_800493C8(sp18), 1);
        temp_s1->vt->unk4(temp_s1);
        func_80026254(arg0, "ETC\\OSDLOGO.TIM");
    }
}

void func_80026254(Unk_80026348 *arg0, void *arg1) {
    Unk_80026254_Obj *obj;

    obj = (Unk_80026254_Obj *)func_8003BE94(0, 0, 0);
    obj->vt->unk98(obj, func_80026328, arg0);
    obj->vt->unk6C(obj, 0);
    obj->vt->unkD4(obj, arg1, 0);
    obj->vt->unk44(obj, arg0->unk1C, 0);
    obj->vt->unk4(obj);
}

void func_80026328(void) {
    func_8004A070(0);
}

void func_80026348(Unk_80026348 *arg0) {
    s32 sp18;
    s32 temp_s0;
    Unk_80026348_Obj *temp_s1;

    if (arg0->unk20->unk8 != 0) {
        func_80026F34(0, 0, 0);
        temp_s1 = (Unk_80026348_Obj *)func_8003B854(0, 0, 0, 0);
        temp_s0 = func_8004913C(&sp18, 0);
        temp_s1->vt->unk44(temp_s1, arg0->unk1C, temp_s0, func_800493C8(sp18), 1);
        temp_s1->vt->unk4(temp_s1);
    }
}

s32 func_80026410(Unk_80026348_80026698 *arg0) {
    s32 temp_v0;

    if (arg0->unk20->unk10 != 0) {
        func_80026F34(0, 0, 0);
        if (arg0->unk28->vt->unk1A0(arg0->unk28, 0) != 1 && arg0->unk24 == 0 &&
            func_80026518(func_80057F68, (s32)arg0->unk28, arg0->unk1C) == 2) {
            func_8002658C(arg0);
        }
        for (;;) {
            temp_v0 = func_80026518(func_8004D518, (s32)arg0->unk28, arg0->unk1C);
            if (temp_v0 != 2) {
                break;
            }
            func_80026518(func_80057F68, (s32)arg0->unk28, arg0->unk1C);
        }
        arg0->unk24 = 0;
        return temp_v0 == 0 ? 2 : 0;
    }
    return 2;
}

s32 func_80026518(Unk_80026518 *(*arg0)(s32), s32 arg1, s32 arg2) {
    Unk_80026518 *temp_v0 = arg0(arg1);
    s32 temp_s0 = temp_v0->vt->unk44(temp_v0, arg2, 0);
    temp_v0->vt->unk4(temp_v0);
    return temp_s0;
}

void func_8002658C(Unk_80026348 *arg0) {
    Unk_8002658C_Local sp18;
    Unk_8002658C_Obj *temp_s0;
    s32 temp_s1;

    if (arg0->unk20->unk8 != 0) {
        func_80026F34(0, 0, 0);
        temp_s0 = (Unk_8002658C_Obj *)func_8003B854(0, 0, 0, 0);
        temp_s1 = func_800493E4(&sp18.unk8, 0, 0xA);
        temp_s0->vt->unk6C(temp_s0, (u32)sp18.unk8 / 15);
        temp_s0->vt->unk12C(temp_s0, 0);
        temp_s0->vt->unk44(temp_s0, arg0->unk1C, temp_s1, -1, 1);
        temp_s0->vt->unk4(temp_s0);
    }
}

void func_80026690(void) {
}

s32 func_80026698(Unk_80026348_80026698 *arg0) {
    Unk_80026698_Obj *temp_v0;
    s32 temp_s0;
    Unk_80026698_Obj *temp_a0;
    s32 temp_v0_2;
    s32 sp10[2];
    s32 result;

    temp_v0 = (Unk_80026698_Obj *)func_80049608(arg0->unk1C, (s32)arg0->unk28, arg0->unk20->unk4);
    temp_s0 = temp_v0->vt->unk44(temp_v0);
    temp_v0->vt->unk4(temp_v0);
    switch (temp_s0) {
    case 2:
        func_8002677C(arg0);
        break;
    case 3:
        arg0->unk24 = 1;
        break;
    }
    temp_a0 = arg0->unk28;
    temp_v0_2 = temp_a0->vt->unk1A0(temp_a0, sp10);
    result = 0;
    if (sp10[0] != 0) {
        result = temp_v0_2 == 1;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_8002677C);

void func_80026900(Unk_80026348 *arg0) {
    s32 sp18;
    s32 temp_s0;
    Unk_80026900_Obj *temp_s1;

    if (arg0->unk20->unk8 != 0) {
        func_80026F34(0, 0, 0);
        temp_s1 = (Unk_80026900_Obj *)func_8003B854(0, 0, 0, 0);
        temp_s1->vt->unk12C(temp_s1, 0);
        temp_s0 = func_800491FC(&sp18, 0);
        temp_s1->vt->unk44(temp_s1, arg0->unk1C, temp_s0, func_800493C8(sp18), 1);
        temp_s1->vt->unk4(temp_s1);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800269E0);

s32 func_800269F0(Unk_800269F0 *arg0) {
    arg0->unk20 = 0;
    arg0->vt->unkC(arg0);
    ((Unk_800269F0_Vtbl *)func_80018390())->unkC(arg0);
    func_80017CFC(arg0);
    return 0;
}

void func_80026A50(Unk_80026A50 *arg0) {
    ((Unk_80026A50_Vtbl *)func_80018390())->unk8(arg0);
    arg0->unk0 = func_80026C9C();
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk20 = 0;
    arg0->unk22 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2A = 0;
}

void func_80026AB4(Unk_80026AB4 *arg0) {
    arg0->vtbl->unk48();
    arg0->vtbl->unk5C(arg0);
}

void func_80026B08(Unk_80026B08 *arg0, s32 arg1) {
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;

    if (arg0->unk10 == 0) {
        temp_s3 = arg0->unkC;
        arg0->unkC = 0;
        arg0->vt->unk44(arg0, arg1, 1, 0);
        temp_v0 = arg0->vt->unk4C(arg0, 0, 2);
        temp_v0_2 = func_80017B34(temp_v0);
        if (temp_v0_2 != 0) {
            arg0->vt->unk4C(arg0, 0, 0);
            arg0->vt->unk54(arg0, temp_v0_2, temp_v0);
            arg0->vt->unk48(arg0);
            arg0->unk10 = temp_v0_2;
            arg0->unk14 = temp_v0;
            arg0->unkC = temp_s3;
            return;
        }
        func_80017CFC(0);
        arg0->vt->unk48(arg0);
    }
}

void func_80026C20(Unk_80026C20 *arg0) {
    if (arg0->unk10 != 0 && arg0->unk14 != 0 && arg0->unk20 == 0) {
        func_80017CFC(arg0->unk10);
        arg0->unk10 = 0;
    }
}

void func_80026C80(void) {
}

void func_80026C88(Unk_80026C88 *arg0) {
    arg0->unk24 |= 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_80026C9C);

void *func_80026CAC(void) {
    if (D_8008A84C == 0x23) {
        return func_8002C438();
    }
    return func_80027E68();
}

struct Unk_80026CE8 *func_80026CE8(struct Unk_80026CE8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = arg3;
    return arg0;
}

void func_80026CFC(s32 arg0) {
    s32 (**var_s0)();
    void *var_v0;
    s32 var_a0;

    var_s0 = D_8006D4AC;
    D_8008A84C = arg0;
    if (arg0 == 0x13) {
        var_v0 = func_80027E68();
    } else {
        var_v0 = func_8002C438();
    }
    var_a0 = func_80026C9C();
    func_80026D88((Unk_80026D88 *)var_a0, var_v0);
    while (*var_s0 != NULL) {
        var_a0 = (*var_s0)();
        var_s0++;
        func_80026D88((Unk_80026D88 *)var_a0, var_v0);
    }
}

void func_80026D88(Unk_80026D88 *arg0, Unk_80026D88 *arg1) {
    arg0->unk40 = arg1->unk40;
    arg0->unk44 = arg1->unk44;
    arg0->unk48 = arg1->unk48;
    arg0->unk4C = arg1->unk4C;
    arg0->unk50 = arg1->unk50;
    arg0->unk54 = arg1->unk54;
    arg0->unk58 = arg1->unk58;
    arg0->unk68 = arg1->unk68;
    arg0->unk6C = arg1->unk6C;
    arg0->unk70 = arg1->unk70;
    arg0->unk74 = arg1->unk74;
}

void func_80026E0C(void) {
    if (D_8008A84C == 0x13) {
        func_800280D0();
    }
}

void func_80026E38(void) {
    if (D_8008A84C == 0x13) {
        func_800280E0();
    }
}

s32 func_80026E64(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EC8();
    }
    return 0;
}

s32 func_80026E98(void) {
    if (D_8008A84C == 0x13) {
        return func_80027ED4();
    }
    return 1;
}

s32 func_80026ECC(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EE0();
    }
    return 0;
}

s32 func_80026F00(void) {
    if (D_8008A84C == 0x13) {
        return func_80027EEC();
    }
    return 0;
}

void func_80026F34(s32 arg0, s32 arg1, s32 arg2) {
    s32 (*var_s0)(s32, s32, s32);

    var_s0 = func_8002C468;
    if (D_8008A84C == 0x13) {
        var_s0 = func_80027F18;
    }
    while (var_s0(arg0, arg1, arg2) == 0) {
    }
}

s32 func_80026FAC(s32 *arg0) {
    if (D_8008A84C == 0x13) {
        return func_80027EF8(arg0);
    }
    return func_8002C448(arg0);
}

s32 func_80026FE8(void) {
    if (D_8008A84C == 0x13) {
        return func_80028B6C();
    }
    return func_8002C478();
}

s32 func_80027024(s32 arg0, s32 arg1) {
    s32 temp_v0;

    if (D_8008A84C == 0x13) {
        D_8008A850 = 1;
        func_80027FD8(arg0);
        temp_v0 = func_80027FF0();
        func_80027FE4(temp_v0 + arg1);
        return func_80027FFC(arg0 + (temp_v0 * 0x1C), arg1);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270AC);

INCLUDE_ASM("asm/nonmatchings/game/80025F7C", func_800270B8);

s8 *func_800270C4(s8 *arg0, s8 *arg1, s8 *arg2, s8 *arg3) {
    *arg0 = 0;
    if (arg2 != NULL) {
        strcat(arg0, arg2);
    }
    strcat(arg0, arg1);
    strcat(arg0, arg3);
    return arg0;
}

#include "common.h"

extern void GsGetTimInfo(u32 *im, void *tim);
typedef struct Unk_8003B5F0 {
    u8 pad_00[0x10];
    u32 *unk10;
} Unk_8003B5F0;
typedef struct Unk_8003B470 {
    u8 pad_00[0xC];
    void (*unkC)(s32);
} Unk_8003B470;
void *func_80026CAC(void);
void *func_80017B34(s32 size);
void *func_8003B614(void);
typedef struct Unk_8003B39C {
    u8 pad_00[8];
    void (*unk8)(void *, s32);
    u8 pad_0C[0x60];
    void (*unk6C)(void *, s32);
} Unk_8003B39C;
typedef struct Unk_8003B3FC_Mgr {
    u8 pad_00[8];
    void (*unk8)(void *);
} Unk_8003B3FC_Mgr;
typedef struct Unk_8003B3FC {
    Unk_8003B39C *unk0;
    u8 pad_04[0x44];
    s32 unk48;
    s32 unk4C;
} Unk_8003B3FC;
typedef struct Unk_8003B624_Vtbl {
    u8 pad_00[0x64];
    void (*unk64)(void *, void *, s32, s32);
} Unk_8003B624_Vtbl;
typedef struct Unk_8003B624_Obj {
    Unk_8003B624_Vtbl *vt;
} Unk_8003B624_Obj;
typedef struct Unk_8003B624 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
} Unk_8003B624;
typedef struct Unk_8003B624_Pos {
    s16 unk0;
    s16 unk2;
} Unk_8003B624_Pos;
typedef struct Unk_8003B624_Rect {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    s32 unk8;
} Unk_8003B624_Rect;
Unk_8003B624_Obj *func_80020C5C(void);
extern u8 D_8006E558[];

s32 func_8003B39C(s32 arg0) {
    void *temp;

    temp = func_80017B34(0x50);
    if (temp != 0) {
        ((Unk_8003B39C *)func_8003B614())->unk8(temp, arg0);
        return (s32)temp;
    }
    return 0;
}

void func_8003B3FC(Unk_8003B3FC *arg0, s32 arg1) {
    ((Unk_8003B3FC_Mgr *)func_80026CAC())->unk8(arg0);
    arg0->unk0 = func_8003B614();
    arg0->unk48 = 0;
    arg0->unk4C = 0;
    if (arg1 != 0) {
        arg0->unk0->unk6C(arg0, arg1);
    }
}

void func_8003B470(s32 arg0) {
    ((Unk_8003B470 *)func_80026CAC())->unkC(arg0);
}

INCLUDE_ASM("asm/nonmatchings/game/8003B39C", func_8003B4A8);

void func_8003B5AC(void) {
}

void func_8003B5B4(void) {
}

void func_8003B5BC(void) {
}

void func_8003B5C4(void) {
}

void func_8003B5CC(void) {
}

void func_8003B5D4(void) {
}

void func_8003B5DC(void) {
}

void func_8003B5E4(Unk_8003B3FC *arg0) {
    arg0->unk48 = 1;
}

void func_8003B5F0(Unk_8003B5F0 *arg0, void *arg1) {
    GsGetTimInfo(arg0->unk10 + 1, arg1);
}

void *func_8003B614(void) {
    return D_8006E558;
}

void func_8003B624(Unk_8003B624 *arg0, s32 arg1, Unk_8003B624_Pos *arg2) {
    Unk_8003B624_Rect rect;
    s32 i;
    Unk_8003B624_Obj *obj;
    void (*fn)(void *, void *, s32, s32);

    obj = func_80020C5C();
    fn = obj->vt->unk64;
    if (arg1 != 0) {
        for (i = 0; i < arg1; i++) {
                rect.unk0 = arg0->unk0 + arg0->unk4 - 1;
                rect.unk2 = arg0->unk2;
                rect.unk4 = 1;
                rect.unk8 = arg0->unk8;
                fn(obj, &rect, arg2->unk0, arg2->unk2);
                rect.unk0 = arg0->unk0;
                rect.unk2 = arg0->unk2;
                rect.unk4 = arg0->unk4 - 1;
                rect.unk8 = arg0->unk8;
                fn(obj, &rect, arg0->unk0 + 1, arg0->unk2);
                rect.unk0 = arg2->unk0;
                rect.unk2 = arg2->unk2;
                rect.unk4 = 1;
                rect.unk8 = arg0->unk8;
                fn(obj, &rect, arg0->unk0, arg0->unk2);
        }
    }
}

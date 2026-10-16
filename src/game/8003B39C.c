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
void *Heap_Alloc(s32 size);
void *func_8003B614(void);
typedef struct Unk_8003B39C {
    u8 pad_00[8];
    void (*unk8)(void *, s32);
    u8 pad_0C[0x60];
    void (*unk6C)(void *, s32);
    u8 pad_70[0x2C];
    void (*unk9C)(void *, void *);
} Unk_8003B39C;
typedef struct Unk_8003B3FC_Mgr {
    u8 pad_00[8];
    void (*unk8)(void *);
} Unk_8003B3FC_Mgr;
typedef struct Unk_8003B3FC {
    Unk_8003B39C *unk0;
    u8 pad_04[0xC];
    void *unk10;
    u8 pad_14[0x18];
    u32 unk2C;
    u16 unk30;
    u16 unk32;
    u16 unk34;
    u16 unk36;
    s32 unk38;
    u16 unk3C;
    u16 unk3E;
    u16 unk40;
    u16 unk42;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
} Unk_8003B3FC;
typedef struct Unk_8003B624_Vtbl {
    u8 pad_00[0x58];
    void (*unk58)(void *, void *, s32);
    u8 pad_5C[0x8];
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

    temp = Heap_Alloc(0x50);
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

void func_8003B4A8(Unk_8003B3FC *arg0) {
    Unk_8003B624_Obj *obj;
    u32 *flags;
    Unk_8003B624_Rect rect;

    obj = func_80020C5C();
    flags = &arg0->unk2C;
    if (arg0->unk10 != NULL) {
        arg0->unk0->unk9C(arg0, flags);
        rect.unk0 = arg0->unk30;
        rect.unk2 = arg0->unk32;
        rect.unk4 = arg0->unk34;
        rect.unk8 = arg0->unk36;
        obj->vt->unk58(obj, &rect, arg0->unk38);
        if ((arg0->unk2C >> 3) & 1) {
            rect.unk0 = arg0->unk3C;
            rect.unk2 = arg0->unk3E;
            rect.unk4 = arg0->unk40;
            rect.unk8 = arg0->unk42;
            obj->vt->unk58(obj, &rect, arg0->unk44);
        }
    }
}

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

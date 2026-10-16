#include "common.h"

typedef struct Unk_8003B02C_Pair {
    s32 unk0;
    s32 unk4;
} Unk_8003B02C_Pair;
struct Unk_8003B02C {
    u8 pad_00[0xC];
    Unk_8003B02C_Pair unkC;
    s32 unk14;
};
typedef struct Unk_8003AF8C_Vtbl {
    u8 pad_00[0x40];
    void (*unk40)(void *, void *, s32);
    u8 pad_44[0xC];
    void (*unk50)(void);
    void (*unk54)(void *);
    s32 (*unk58)(void *);
    void (*unk5C)(void *);
    s32 (*unk60)(void *);
    void (*unk64)(void *);
} Unk_8003AF8C_Vtbl;
typedef struct Unk_8003AF8C {
    Unk_8003AF8C_Vtbl *unk0;
    u8 pad_04[0x18 - 0x4];
    s32 unk18;
} Unk_8003AF8C;
typedef struct Unk_8003AF8C_Mgr {
    u8 pad_00[0x8];
    void (*unk8)(void *);
} Unk_8003AF8C_Mgr;
void *Object_GetBaseVtbl(void);
void *func_8003B20C(void);
void func_80026CFC(s32 arg0);
s32 CdInit(void);
s32 D_8008A8DC;
extern char D_8008A8E0[];
typedef struct Unk_8003B044_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, void *, s32);
} Unk_8003B044_Vtbl;
typedef struct Unk_8003B044_Node {
    void *unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Unk_8003B044_Node;
typedef struct Unk_8003B044 {
    u8 pad_00[0xC];
    Unk_8003B02C_Pair unkC;
    s32 unk14;
    s32 unk18;
    Unk_8003B044_Node *unk1C;
} Unk_8003B044;
void func_80020C68(void **arg0);
void func_80032368(void);
void GsInit3D(void);
void *Heap_Alloc(s32 size);
extern u8 D_8006E4F0[];

void func_8003AF8C(Unk_8003AF8C *arg0, s32 arg1) {
    ((Unk_8003AF8C_Mgr *)Object_GetBaseVtbl())->unk8(arg0);
    arg0->unk0 = func_8003B20C();
    if (D_8008A8DC == 0) {
        CdInit();
        D_8008A8DC = 1;
    }
    arg0->unk18 = 0;
    func_80026CFC(arg1);
    arg0->unk0->unk40(arg0, D_8008A8E0, 0);
}

void func_8003B024(void) {
}

void func_8003B02C(struct Unk_8003B02C *arg0, Unk_8003B02C_Pair *arg1, s32 arg2) {
    arg0->unkC = *arg1;
    arg0->unk14 = arg2;
}

void func_8003B044(Unk_8003B044 *arg0, void **arg1, s32 arg2) {
    Unk_8003B044_Node *temp_v0;

    if (arg0->unk18 == 0) {
        func_80020C68(arg1);
        ((Unk_8003B044_Vtbl *)*arg1)->unk44(arg1, &arg0->unkC, arg0->unk14);
        func_80032368();
        GsInit3D();
        temp_v0 = Heap_Alloc(0x14);
        arg0->unk1C = temp_v0;
        temp_v0->unk0 = arg1;
        arg0->unk1C->unk4 = arg2;
        arg0->unk1C->unk8 = 0;
        arg0->unk1C->unkC = 0;
        arg0->unk1C->unk10 = 0;
        arg0->unk18 = 1;
    }
}

void func_8003B108(void) {
}

void func_8003B110(Unk_8003AF8C *arg0) {
    s32 r;

    if (arg0->unk18 != 0) {
        arg0->unk0->unk50();
        for (;;) {
            arg0->unk0->unk54(arg0);
            for (;;) {
                r = arg0->unk0->unk58(arg0);
                if (r == 1) {
                    arg0->unk0->unk5C(arg0);
                    continue;
                }
                if (r == 2) {
                    if (arg0->unk0->unk60(arg0) != 0) {
                        arg0->unk0->unk64(arg0);
                    }
                }
                if (r == 0) {
                    break;
                }
            }
        }
    }
}

void *func_8003B20C(void) {
    return D_8006E4F0;
}

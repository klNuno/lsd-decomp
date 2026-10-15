#include "common.h"

struct Heap;
typedef struct Unk_800118DC_Vtbl {
    u8 pad0[0x44];
    void (*unk44)(void *, void *, s32);
    u8 pad1[0x4];
    void (*unk4C)(void *);
} Unk_800118DC_Vtbl;
typedef struct Unk_800118DC_Obj {
    Unk_800118DC_Vtbl *vt;
} Unk_800118DC_Obj;
struct Heap *D_8008A808;
Unk_800118DC_Obj *D_8008AC20;
extern s32 D_80066828[];
void __main(void);
void SetMem(s32);
struct Heap *func_80017A20(u32, s32);
void func_80017A9C(struct Heap *);
s32 func_80025F7C(s32);
void *func_800206E0(void);
s32 func_80025B34(s32, s32);

void func_800118DC(void) {
    void *temp_s0;

    __main();
    SetMem(2);
    D_8008A808 = func_80017A20(0x166C00, 0);
    func_80017A9C(D_8008A808);
    D_8008AC20 = (Unk_800118DC_Obj *)func_80025F7C((s32)D_80066828);
    temp_s0 = func_800206E0();
    D_8008AC20->vt->unk44(D_8008AC20, temp_s0, func_80025B34(0, 0));
    D_8008AC20->vt->unk4C(D_8008AC20);
}

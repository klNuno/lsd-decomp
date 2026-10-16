#include "common.h"

typedef struct Unk_80057FC8 Unk_80057FC8;
typedef struct { u8 pad[0x8]; void (*f8)(Unk_80057FC8 *, s32, char *, s32); } Unk_80057FC8_VtA;
typedef struct { u8 pad[0x40]; void (*f40)(Unk_80057FC8 *, s32); u8 pad2[0xD8 - 0x44]; void (*fD8)(Unk_80057FC8 *, s32); } Unk_80057FC8_VtB;
typedef struct Unk_80057FC8_C { struct { u8 pad[0x9C]; void (*f9C)(struct Unk_80057FC8_C *, s32); } *vt; } Unk_80057FC8_C;
struct Unk_80057FC8 { Unk_80057FC8_VtB *vt; u8 pad[0x44]; Unk_80057FC8_C *u48; u8 pad2[0xA4 - 0x4C]; s32 uA4; };
extern Unk_80057FC8_VtA *MenuScreen_GetVtbl(void);
extern Unk_80057FC8_VtB *Graph_GetVtable(void);

void func_80057FC8(Unk_80057FC8 *arg0, s32 arg1) {
    MenuScreen_GetVtbl()->f8(arg0, 0, "ETC\\ETCSE", 0);
    arg0->vt = Graph_GetVtable();
    arg0->u48->vt->f9C(arg0->u48, -1);
    arg0->uA4 = arg1;
    arg0->vt->fD8(arg0, 0);
    arg0->vt->f40(arg0, arg1);
}

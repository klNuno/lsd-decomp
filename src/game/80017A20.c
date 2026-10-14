#include "common.h"

extern void free(void *);
typedef struct Block { u32 hdr; struct Block *next; struct Block *prev; } Block;
typedef struct Heap { Block *base; u32 size; Block *head; Block *tail; s32 ready; } Heap;
Heap *D_8008A818;
typedef struct VTable { s32 unk0, unk4, unk8; void (*fnC)(); } VTable;
typedef struct { VTable *vt; } Object;
extern void func_80017CFC(Object *);
extern s32 D_8006B58C[];
s32 D_8008A820;
s32 D_8008A830;
s32 D_8008A834;

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80017A20);

void func_80017A9C(Heap *arg0) {
    D_8008A818 = arg0;
}

void func_80017AA8(void *arg0) {
    free(arg0);
}

void func_80017AC8(Heap *arg0) {
    Heap *h = D_8008A818;
    Block *b;
    u8 *end;
    if (h == NULL) {
        h = arg0;
    }
    h->ready = 1;
    b = h->base;
    h->head = b;
    h->tail = b;
    b->hdr = h->size | 0x40000000;
    h->head->next = NULL;
    h->tail->prev = NULL;
    end = (u8 *)b + (b->hdr & 0xFFFFFFF);
    ((Block **)end)[-1] = b;
    *(u32 *)end = 0x80000000;
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80017B34);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80017CFC);

void func_80017EA8(void) {
}

s32 func_80017EB0(Object *arg0) {
    arg0->vt->fnC();
    func_80017CFC(arg0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80017EF8);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80017F2C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80017F98);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80017FF0);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018040);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800180BC);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800180FC);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001811C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001813C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001816C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800181AC);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018208);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018288);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800182CC);

void func_80018350(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018358);

s32 *func_80018390(void) {
    return D_8006B58C;
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800183A0);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800183DC);

void func_8001844C(s32 arg0) {
    D_8008A820 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018458);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018464);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001934C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800193C0);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800194A4);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800195EC);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800196D4);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800196E8);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800196FC);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80019710);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80019724);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001974C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80019774);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001979C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800197C4);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001989C);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800199EC);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80019B24);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80019C04);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80019D84);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80019EE4);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001A064);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001A224);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001A268);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001A380);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001A3EC);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001A4C0);

void func_8001A54C(s32 arg0, s32 arg1) {
    D_8008A830 = arg0;
    if (arg0 != 0) {
        D_8008A834 = arg1;
    }
}

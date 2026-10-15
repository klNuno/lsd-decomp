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
extern s32 func_800181AC();
void func_80018208(void *arg0);
extern s32 *func_80018390(void);
typedef struct Unk_80017EF8 { s32 *unk0; s32 unk4; s32 unk8; } Unk_80017EF8;
typedef struct Unk_80018358_Vtbl {
    u8 pad[0x14];
    void (*unk14)(void);
} Unk_80018358_Vtbl;
typedef struct Unk_80018358 {
    Unk_80018358_Vtbl *vtbl;
} Unk_80018358;
typedef struct Unk_800183A0 {
    struct Unk_800183A0 *unk0;
    s32 unk4;
} Unk_800183A0;
typedef struct Unk_800180BC { s32 unk0; s32 unk4; } Unk_800180BC;
void func_800183A0(s32 *arg0, Unk_800183A0 **arg1);
typedef struct Unk_8001816C { s32 unk0; s32 unk4; s32 unk8; } Unk_8001816C;
typedef struct Unk_80018288 {
    struct Unk_80018288 *next;
} Unk_80018288;
typedef struct Unk_80017FF0 {
    u8 pad[0x24];
    void (*unk24)(void *, void *);
} Unk_80017FF0;
typedef struct Unk_80017F2C_Vtbl {
    u8 pad0[0x18];
    void (*unk18)(void *);
    u8 pad1[0xC];
    void (*unk28)(void *);
    u8 pad2[0x4];
    void (*unk30)(void *, s32);
} Unk_80017F2C_Vtbl;
typedef struct Unk_80017F2C {
    Unk_80017F2C_Vtbl *vt;
} Unk_80017F2C;
extern s32 D_8008E248;
typedef struct Unk_8001934C {
    u8 pad_00[3];
    u8 unk3;
    u8 pad_04[3];
    u8 unk7;
} Unk_8001934C;
typedef struct Unk_8001934C_Dst {
    u8 pad_00[0x14];
    u8 unk14;
    u8 unk15;
    u8 pad_16[0x1C - 0x16];
    s32 unk1C;
} Unk_8001934C_Dst;
typedef struct Unk_800183DC_Vtbl {
    s32 unk0;
    void *(*unk4)(void *);
} Unk_800183DC_Vtbl;
typedef struct Unk_800183DC {
    Unk_800183DC_Vtbl *vt;
} Unk_800183DC;
extern void *malloc(u32);
extern s32 printf(const char *fmt, ...);
extern void func_80017AC8(Heap *arg0);
typedef struct Unk_80018040_Vtbl {
    u8 pad[0x14];
    void (*unk14)(void *, s32);
} Unk_80018040_Vtbl;
typedef struct Unk_80018040 {
    Unk_80018040_Vtbl *vt;
    Unk_800183A0 *unk4;
} Unk_80018040;
typedef struct Unk_80017F98 {
    u8 pad[0x20];
    void (*unk20)(void *, void *);
} Unk_80017F98;
void *func_80017B34(s32 size);
typedef struct Unk_800181AC {
    void *unk0;
    s32 unk4;
} Unk_800181AC;

Heap *func_80017A20(u32 size) {
    Heap *heap;

    if (size < 0x400) {
        size = 0x400;
    }
    heap = malloc(size + 0x20);
    if (heap != NULL) {
        heap->base = (Block *)((u8 *)heap + 0x1C);
        heap->size = size;
        func_80017AC8(heap);
    } else {
        printf("bMemPMgr = %p, poolSize = %ld in BMemPMgrInit\n", 0, size);
    }
    return heap;
}

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

void func_80017EF8(Unk_80017EF8 *arg0) {
    arg0->unk0 = func_80018390();
    arg0->unk8 = 0;
    arg0->unk4 = 0;
}

void func_80017F2C(Unk_80017F2C *arg0) {
    arg0->vt->unk30(arg0, 1);
    arg0->vt->unk18(arg0);
    arg0->vt->unk28(arg0);
}

void func_80017F98(u8 *arg0, Unk_80017F98 **arg1) {
    if (func_800181AC(arg0 + 4) != 0) {
        (*arg1)->unk20(arg1, arg0);
    }
}

void func_80017FF0(void *arg0, Unk_80017FF0 **arg1) {
    func_80018208((u8 *)arg0 + 4);
    (*arg1)->unk24(arg1, arg0);
}

void func_80018040(Unk_80018040 *arg0) {
    s32 sp10;
    s32 *p;
    Unk_800183A0 *sp14;

    p = &sp10;
    sp14 = arg0->unk4;
    func_800183A0(p, &sp14);
    while (sp10 != 0) {
        arg0->vt->unk14(arg0, sp10);
        func_800183A0(p, &sp14);
    }
}

void func_800180BC(Unk_800180BC *arg0, s32 *arg1, s32 *arg2) {
    if (*arg1 == 0) {
        *arg2 = arg0->unk4;
    }
    func_800183A0(arg1, (Unk_800183A0 **)arg2);
}

void func_800180FC(s32 arg0) {
    func_800181AC(arg0 + 8);
}

void func_8001811C(void *arg0) {
    func_80018208((u8 *)arg0 + 8);
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_8001813C);

void func_8001816C(Unk_8001816C *arg0, s32 *arg1, s32 *arg2) {
    if (*arg1 == 0) {
        *arg2 = arg0->unk8;
    }
    func_800183A0(arg1, (Unk_800183A0 **)arg2);
}

s32 func_800181AC(void **arg0, s32 arg1) {
    Unk_800181AC *temp_v0;

    temp_v0 = func_80017B34(8);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = *arg0;
        temp_v0->unk4 = arg1;
        *arg0 = temp_v0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018208);

void func_80018288(Unk_80018288 **arg0) {
    Unk_80018288 *node;
    Unk_80018288 *cur;

    node = *arg0;
    while (node != NULL) {
        cur = node;
        node = node->next;
        func_80017CFC(cur);
    }
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_800182CC);

void func_80018350(void) {
}

void func_80018358(Unk_80018358 *arg0, s32 arg1, s32 arg2) {
    if (arg2 == 1) {
        arg0->vtbl->unk14();
    }
}

s32 *func_80018390(void) {
    return D_8006B58C;
}

void func_800183A0(s32 *arg0, Unk_800183A0 **arg1) {
    Unk_800183A0 *temp_v0;

    temp_v0 = *arg1;
    if (temp_v0 != NULL) {
        *arg0 = temp_v0->unk4;
        *arg1 = (*arg1)->unk0;
        return;
    }
    *arg0 = 0;
}

void func_800183DC(Unk_800183DC **arg0, s32 arg1) {
    while (arg1-- > 0) {
        *arg0 = (*arg0)->vt->unk4(*arg0);
        arg0++;
    }
}

void func_8001844C(s32 arg0) {
    D_8008A820 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018458);

INCLUDE_ASM("asm/nonmatchings/game/80017A20", func_80018464);

void func_8001934C(Unk_8001934C *arg0, Unk_8001934C_Dst *arg1) {
    if (arg1->unk1C != 0) {
        arg0->unk7 |= 2;
    } else {
        arg0->unk7 &= ~2;
    }
    if (D_8008E248 != 0) {
        arg0->unk7 |= 1;
    } else {
        arg0->unk7 &= ~1;
    }
    arg1->unk14 = arg0->unk3;
    arg1->unk15 = arg0->unk7;
}

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

void func_8001A224(u8 **arg0, u8 *arg1, s32 arg2) {
    u8 **slot;
    u8 *entry;

    entry = arg1 + 0x18;
    if (arg2 == 4) {
        slot = (u8 **)(arg1 + 0xF0);
    } else {
        slot = (u8 **)(arg1 + 0xA8);
    }
    while (arg2-- > 0) {
        *slot = entry;
        *arg0 = entry;
        entry += 0x18;
        slot++;
        arg0++;
    }
}

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

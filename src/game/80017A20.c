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
void func_80018208();
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
void *func_80017B34(u32 size, Heap *arg1);
typedef struct Unk_800181AC {
    void *unk0;
    s32 unk4;
} Unk_800181AC;
typedef struct Unk_800182CC {
    u8 pad0[0x8];
    Unk_800183A0 *unk8;
} Unk_800182CC;
typedef struct Unk_800182CC_Vtbl {
    u8 pad0[0x38];
    void (*unk38)(void *, void *, void *);
} Unk_800182CC_Vtbl;
typedef struct Unk_800182CC_Obj {
    Unk_800182CC_Vtbl *vtbl;
} Unk_800182CC_Obj;
typedef struct Unk_800197C4 {
    u8 pad_00[0x30];
    s32 *unk30;
    u8 pad_34[0x78 - 0x34];
    s32 unk78;
} Unk_800197C4;
extern u8 D_8008ACD0[];
extern void *RCpolyF3(void *, void *);
typedef struct { u8 b0, b1, b2, b3; } Unk_8001A380_Quad;
typedef struct Unk_8001A380 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u16 unkC;
    u16 unkE;
    Unk_8001A380_Quad unk10;
    s32 unk14;
} Unk_8001A380;
typedef struct Unk_8001A380_Src {
    u8 pad_00[0x30];
    s32 unk30;
} Unk_8001A380_Src;
void func_8001A380(Unk_8001A380 *arg0, Unk_8001A380_Src *arg1, Unk_8001A380_Quad *arg2, s32 arg3, u16 arg4, u16 arg5);
void func_8001A3EC(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4);
typedef struct Unk_80019B24 {
    u8 pad_00[0x30];
    u32 *unk30;
    u8 pad_34[0x78 - 0x34];
    s32 unk78;
} Unk_80019B24;
extern u8 D_8008AEE8[];
void func_8001A4C0(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);
extern void *RCpolyF4(void *, void *);
extern void *RCpolyFT3(void *, void *);
typedef struct Unk_8001989C_Col {
    u8 r, g, b, cd;
} Unk_8001989C_Col;
typedef struct Unk_8001989C {
    u32 unk0;
    Unk_8001989C_Col unk4;
    u32 unk8;
    Unk_8001989C_Col unkC;
    u32 unk10;
    Unk_8001989C_Col unk14;
    u32 unk18;
} Unk_8001989C;
typedef struct Unk_800199EC_Tri {
    u8 pad_00[0x8];
    u16 unk8;
    u16 unkA;
    Unk_8001989C_Col unkC;
} Unk_800199EC_Tri;
typedef struct Unk_800199EC_Poly {
    u32 unk0;
    s32 unk4;
    s32 unk8;
    u16 unkC;
    u16 unkE;
    s32 unk10;
    u16 unk14;
    u16 unk16;
    s32 unk18;
    u16 unk1C;
    u16 unk1E;
} Unk_800199EC_Poly;
typedef struct Unk_800199EC {
    u8 pad_00[0x30];
    u32 *unk30;
    u8 pad_34[0x78 - 0x34];
    s32 unk78;
    u8 pad_7C[0x88 - 0x7C];
    Unk_800199EC_Tri *unk88;
    Unk_800199EC_Tri *unk8C;
    Unk_800199EC_Tri *unk90;
    Unk_800199EC_Tri *unk94;
    Unk_800199EC_Tri *unk98;
    Unk_800199EC_Tri *unk9C;
    Unk_800199EC_Tri *unkA0;
    s32 unkA4;
} Unk_800199EC;
extern void *RCpolyFT4(void *, void *);
typedef struct Unk_80019D84 {
    u32 unk0;
    s32 unk4;
    s32 unk8;
    u16 unkC;
    u16 unkE;
    s32 unk10;
    u16 unk14;
    u16 unk16;
    s32 unk18;
    u16 unk1C;
    u16 unk1E;
    s32 unk20;
    u16 unk24;
} Unk_80019D84;
typedef struct Unk_8001A4C0_Pair { u8 b[8]; } Unk_8001A4C0_Pair;
typedef struct Unk_8001A4C0_Quad { u8 r, g, b, cd; } Unk_8001A4C0_Quad;
typedef struct Unk_8001A4C0_Blk {
    Unk_8001A4C0_Pair head;
    u8 pad[8];
    Unk_8001A4C0_Quad tail;
} Unk_8001A4C0_Blk;
typedef struct Unk_8001A4C0_Ref {
    u8 pad[0xC];
    Unk_8001A4C0_Blk *unkC;
} Unk_8001A4C0_Ref;
typedef struct Unk_8001A3EC_Pair { u8 b[8]; } Unk_8001A3EC_Pair;
typedef struct Unk_8001A3EC_Quad { u8 r, g, b, cd; } Unk_8001A3EC_Quad;
typedef struct Unk_8001A3EC_Blk {
    Unk_8001A3EC_Pair head;
    u8 pad[8];
    Unk_8001A3EC_Quad tail;
} Unk_8001A3EC_Blk;
typedef struct Unk_8001A3EC_Ref {
    Unk_8001A3EC_Blk *unk0;
    Unk_8001A3EC_Blk *unk4;
    Unk_8001A3EC_Blk *unk8;
} Unk_8001A3EC_Ref;
typedef struct Unk_8001A268_Pt {
    s16 x;
    s16 y;
} Unk_8001A268_Pt;
typedef struct Unk_8001A268 {
    u8 pad_00[0x60];
    Unk_8001A268_Pt unk60[4];
    Unk_8001A268_Pt unk70;
    Unk_8001A268_Pt unk74;
    s32 unk78;
} Unk_8001A268;
extern void func_8001A4C0(void *, void *, void *, void *, void *, void *);
extern void *RCpolyG4(void *, void *);
typedef struct Unk_80019C04_Col {
    u8 r, g, b, cd;
} Unk_80019C04_Col;
typedef struct Unk_80019C04_Poly {
    u32 unk0;
    Unk_80019C04_Col unk4;
    s16 unk8;
    s16 unkA;
    Unk_80019C04_Col unkC;
    s16 unk10;
    s16 unk12;
    Unk_80019C04_Col unk14;
    s16 unk18;
    s16 unk1A;
    Unk_80019C04_Col unk1C;
    s16 unk20;
    s16 unk22;
} Unk_80019C04_Poly;
typedef struct Unk_80019C04_Tri {
    u8 pad_00[0x8];
    u16 unk8;
    u16 unkA;
    Unk_80019C04_Col unkC;
} Unk_80019C04_Tri;
typedef struct Unk_80019C04 {
    u8 pad_00[0x30];
    u32 *unk30;
    u8 pad_34[0x78 - 0x34];
    s32 unk78;
    u8 pad_7C[0x94 - 0x7C];
    Unk_80019C04_Tri *unk94;
    Unk_80019C04_Tri *unk98;
    Unk_80019C04_Tri *unk9C;
    Unk_80019C04_Tri *unkA0;
    s32 unkA4;
} Unk_80019C04;
extern void *RCpolyG3(void *, void *);
extern void func_8001A3EC(void *, void *, void *, void *, void *);
extern s32 D_80090C18;
s32 D_8008A824;
s32 D_8008A828;
typedef struct Unk_80019EE4 {
    u32 unk0;
    Unk_8001989C_Col unk4;
    s32 unk8;
    u16 unkC;
    u16 unkE;
    Unk_8001989C_Col unk10;
    s32 unk14;
    u16 unk18;
    u16 unk1A;
    Unk_8001989C_Col unk1C;
    s32 unk20;
    u16 unk24;
    u16 unk26;
} Unk_80019EE4;
extern void *RCpolyGT3(void *, void *);
typedef struct Unk_8001A064 {
    u32 unk0;
    Unk_8001989C_Col unk4;
    s32 unk8;
    u16 unkC;
    u16 unkE;
    Unk_8001989C_Col unk10;
    s32 unk14;
    u16 unk18;
    u16 unk1A;
    Unk_8001989C_Col unk1C;
    s32 unk20;
    u16 unk24;
    u16 unk26;
    Unk_8001989C_Col unk28;
    s32 unk2C;
    u16 unk30;
    u16 unk32;
} Unk_8001A064;
extern void *RCpolyGT4(void *, void *);
extern void func_8001844C(s32 arg0);
void func_80018288(Unk_80018288 **arg0);
typedef struct Unk_8001813C {
    u8 pad[8];
    Unk_80018288 *unk8;
} Unk_8001813C;

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

void *func_80017B34(u32 size, Heap *arg1) {
    Heap *heap;
    Block *blk;
    Block *rem;
    Block *prev;
    Block *next;
    Block *after;
    Block *before;
    void *result;
    u32 hdr;
    u32 bsize;
    u32 tmp;
    u32 pad;

    func_8001844C(1);
    result = NULL;
    heap = D_8008A818;
    if (heap == NULL) {
        heap = arg1;
    }
    if (size != 0) {
        pad = size & 3;
        if (pad != 0) {
            tmp = size + 4;
            size = tmp - pad;
        }
        if (size < 0xC) {
            size = 0xC;
        }
        size += 4;
        blk = heap->head;
        while (blk != NULL) {
            hdr = blk->hdr;
            bsize = hdr & 0x0FFFFFFF;
            if (bsize >= size) {
                blk->hdr = hdr & 0xBFFFFFFF;
                result = (char *)blk + 4;
                if (bsize < size + 0x10) {
                    rem = (Block *)((char *)blk + (blk->hdr & 0x0FFFFFFF));
                    rem->hdr &= 0x7FFFFFFF;
                    next = blk->next;
                    prev = blk->prev;
                    if (next != NULL) {
                        next->prev = prev;
                    } else {
                        heap->tail = prev;
                    }
                    before = blk->prev;
                    after = blk->next;
                    if (before != NULL) {
                        before->next = after;
                    } else {
                        heap->head = after;
                    }
                } else {
                    blk->hdr = (blk->hdr & 0xF0000000) | size;
                    rem = (Block *)((char *)blk + (blk->hdr & 0x0FFFFFFF));
                    rem->hdr = (bsize - size) | 0x40000000;
                    rem->next = blk->next;
                    rem->prev = blk->prev;
                    if (blk->next != NULL) {
                        blk->next->prev = rem;
                    } else {
                        heap->tail = rem;
                    }
                    if (blk->prev != NULL) {
                        blk->prev->next = rem;
                    } else {
                        heap->head = rem;
                    }
                    *(Block **)((char *)rem + (rem->hdr & 0x0FFFFFFF) - 4) = rem;
                }
                break;
            }
            blk = blk->next;
        }
    }
    func_8001844C(0);
    return result;
}

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

void func_8001813C(Unk_8001813C *arg0) {
    func_80018288(&arg0->unk8);
    arg0->unk8 = NULL;
}

void func_8001816C(Unk_8001816C *arg0, s32 *arg1, s32 *arg2) {
    if (*arg1 == 0) {
        *arg2 = arg0->unk8;
    }
    func_800183A0(arg1, (Unk_800183A0 **)arg2);
}

s32 func_800181AC(void **arg0, s32 arg1) {
    Unk_800181AC *temp_v0;

    temp_v0 = ((void *(*)(s32))func_80017B34)(8);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = *arg0;
        temp_v0->unk4 = arg1;
        *arg0 = temp_v0;
        return 1;
    }
    return 0;
}

void func_80018208(Unk_800183A0 **arg0, s32 arg1) {
    Unk_800183A0 *var_a0;
    Unk_800183A0 *var_v1;

    var_a0 = *arg0;
    var_v1 = NULL;
    while (var_a0 != NULL) {
        if (var_a0->unk4 == arg1) {
            if (var_v1 != NULL) {
                var_v1->unk0 = var_a0->unk0;
            } else {
                *arg0 = var_a0->unk0;
            }
            func_80017CFC((Object *)var_a0);
            return;
        }
        var_v1 = var_a0;
        var_a0 = var_a0->unk0;
    }
}

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

void func_800182CC(Unk_800182CC *arg0, void *arg1) {
    Unk_800182CC_Obj *sp10;
    Unk_800183A0 *sp14;

    sp14 = arg0->unk8;
    func_800183A0(&sp10, &sp14);
    while (sp10 != NULL) {
        sp10->vtbl->unk38(sp10, arg0, arg1);
        func_800183A0(&sp10, &sp14);
    }
}

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

s32 func_80018458(void) {
    return D_8008A820;
}

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

void *func_800197C4(u8 *arg0, Unk_800197C4 *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008ACD0, arg1, arg0 + 4, 0, 0, 0);
        func_8001A3EC((u8 *)arg1 + 0x88, (u8 *)arg1 + 0xA4, arg0 + 8, arg0 + 0xC, arg0 + 0x10);
        return RCpolyF3(arg0, D_8008ACD0);
    }
    *(s32 *)arg0 = (*(s32 *)arg0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((s32)arg0 & 0xFFFFFF);
    return arg0 + 0x14;
}

void *func_8001989C(Unk_8001989C *arg0, Unk_800199EC *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008ACD0, arg1, &arg0->unk4, 0, 0, 0);
        func_8001A3EC(&arg1->unk88, &arg1->unkA4, &arg0->unk8, &arg0->unk10, &arg0->unk18);
        arg1->unk88->unkA = arg0->unkC.cd;
        arg1->unk8C->unkA = arg0->unkC.cd;
        arg1->unk90->unkA = arg0->unk14.cd;
        arg1->unk88->unkC = arg0->unk4;
        arg1->unk8C->unkC = arg0->unkC;
        arg1->unk90->unkC = arg0->unk14;
        return RCpolyG3(arg0, D_8008ACD0);
    }
    arg0->unk0 = (arg0->unk0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((u32)arg0 & 0xFFFFFF);
    return arg0 + 1;
}

void *func_800199EC(Unk_800199EC_Poly *arg0, Unk_800199EC *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008ACD0, arg1, &arg0->unk4, 1, arg0->unkE, arg0->unk16);
        func_8001A3EC(&arg1->unk88, &arg1->unkA4, &arg0->unk8, &arg0->unk10, &arg0->unk18);
        arg1->unk88->unkA = arg0->unk1E;
        arg1->unk8C->unkA = arg0->unk1E;
        arg1->unk90->unkA = arg0->unk1E;
        arg1->unk88->unk8 = arg0->unkC;
        arg1->unk8C->unk8 = arg0->unk14;
        arg1->unk90->unk8 = arg0->unk1C;
        return RCpolyFT3(arg0, D_8008ACD0);
    }
    arg0->unk0 = (arg0->unk0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((u32)arg0 & 0xFFFFFF);
    return (u8 *)arg0 + 0x20;
}

void *func_80019B24(u32 *arg0, Unk_80019B24 *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008AEE8, arg1, (u8 *)arg0 + 4, 0, 0, 0);
        func_8001A4C0((u8 *)arg1 + 0x94, (u8 *)arg1 + 0xA4, (u8 *)arg0 + 8, (u8 *)arg0 + 0xC, (u8 *)arg0 + 0x10, (u8 *)arg0 + 0x14);
        return RCpolyF4(arg0, D_8008AEE8);
    }
    *arg0 = (*arg0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((u32)arg0 & 0xFFFFFF);
    return (u8 *)arg0 + 0x18;
}

void *func_80019C04(Unk_80019C04_Poly *arg0, Unk_80019C04 *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008AEE8, arg1, &arg0->unk4, 0, 0, 0);
        func_8001A4C0(&arg1->unk94, &arg1->unkA4, &arg0->unk8, &arg0->unk10, &arg0->unk18, &arg0->unk20);
        arg1->unk94->unkA = arg0->unkC.cd;
        arg1->unk98->unkA = arg0->unkC.cd;
        arg1->unk9C->unkA = arg0->unk14.cd;
        arg1->unkA0->unkA = arg0->unk1C.cd;
        arg1->unk94->unkC = arg0->unk4;
        arg1->unk98->unkC = arg0->unkC;
        arg1->unk9C->unkC = arg0->unk14;
        arg1->unkA0->unkC = arg0->unk1C;
        return RCpolyG4(arg0, D_8008AEE8);
    }
    arg0->unk0 = (arg0->unk0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((u32)arg0 & 0xFFFFFF);
    return arg0 + 1;
}

void *func_80019D84(Unk_80019D84 *arg0, Unk_800199EC *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008AEE8, arg1, &arg0->unk4, 1, arg0->unkE, arg0->unk16);
        func_8001A4C0(&arg1->unk94, &arg1->unkA4, &arg0->unk8, &arg0->unk10, &arg0->unk18, &arg0->unk20);
        arg1->unk94->unkA = arg0->unk1E;
        arg1->unk98->unkA = arg0->unk1E;
        arg1->unk9C->unkA = arg0->unk1E;
        arg1->unkA0->unkA = arg0->unk1E;
        arg1->unk94->unk8 = arg0->unkC;
        arg1->unk98->unk8 = arg0->unk14;
        arg1->unk9C->unk8 = arg0->unk1C;
        arg1->unkA0->unk8 = arg0->unk24;
        return RCpolyFT4(arg0, D_8008AEE8);
    }
    arg0->unk0 = (arg0->unk0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((u32)arg0 & 0xFFFFFF);
    return (u8 *)arg0 + 0x28;
}

void *func_80019EE4(Unk_80019EE4 *arg0, Unk_800199EC *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008ACD0, arg1, &arg0->unk4, 1, arg0->unkE, arg0->unk1A);
        func_8001A3EC(&arg1->unk88, &arg1->unkA4, &arg0->unk8, &arg0->unk14, &arg0->unk20);
        arg1->unk88->unkA = arg0->unk26;
        arg1->unk8C->unkA = arg0->unk26;
        arg1->unk90->unkA = arg0->unk26;
        arg1->unk88->unkC = arg0->unk4;
        arg1->unk8C->unkC = arg0->unk10;
        arg1->unk90->unkC = arg0->unk1C;
        arg1->unk88->unk8 = arg0->unkC;
        arg1->unk8C->unk8 = arg0->unk18;
        arg1->unk90->unk8 = arg0->unk24;
        return RCpolyGT3(arg0, D_8008ACD0);
    }
    arg0->unk0 = (arg0->unk0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((u32)arg0 & 0xFFFFFF);
    return arg0 + 1;
}

void *func_8001A064(Unk_8001A064 *arg0, Unk_800199EC *arg1) {
    if (arg1->unk78 != 0) {
        func_8001A380(D_8008AEE8, arg1, &arg0->unk4, 1, arg0->unkE, arg0->unk1A);
        func_8001A4C0(&arg1->unk94, &arg1->unkA4, &arg0->unk8, &arg0->unk14, &arg0->unk20, &arg0->unk2C);
        arg1->unk94->unkA = arg0->unk26;
        arg1->unk98->unkA = arg0->unk26;
        arg1->unk9C->unkA = arg0->unk32;
        arg1->unkA0->unkA = arg0->unk32;
        arg1->unk94->unkC = arg0->unk4;
        arg1->unk98->unkC = arg0->unk10;
        arg1->unk9C->unkC = arg0->unk1C;
        arg1->unkA0->unkC = arg0->unk28;
        arg1->unk94->unk8 = arg0->unkC;
        arg1->unk98->unk8 = arg0->unk18;
        arg1->unk9C->unk8 = arg0->unk24;
        arg1->unkA0->unk8 = arg0->unk30;
        return RCpolyGT4(arg0, D_8008AEE8);
    }
    arg0->unk0 = (arg0->unk0 & 0xFF000000) | (*arg1->unk30 & 0xFFFFFF);
    *arg1->unk30 = (*arg1->unk30 & 0xFF000000) | ((u32)arg0 & 0xFFFFFF);
    return arg0 + 1;
}

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

void func_8001A268(Unk_8001A268 *arg0, s32 arg1) {
    Unk_8001A268_Pt *p;

    arg0->unk74 = arg0->unk60[0];
    arg0->unk70 = arg0->unk74;
    for (p = &arg0->unk60[1]; p < (Unk_8001A268_Pt *)((u8 *)arg0 + arg1 * 4 + 0x5C); p++) {
        if (p->x < arg0->unk70.x) {
            arg0->unk70.x = p->x;
        }
        if (p->y < arg0->unk70.y) {
            arg0->unk70.y = p->y;
        }
        if (arg0->unk74.x < p->x) {
            arg0->unk74.x = p->x;
        }
        if (arg0->unk74.y < p->y) {
            arg0->unk74.y = p->y;
        }
    }
    if (arg0->unk74.x - arg0->unk70.x > 0x100) {
        arg0->unk78 = 1;
    }
    if (arg0->unk74.y - arg0->unk70.y > 0x100) {
        arg0->unk78 = 1;
    }
}

void func_8001A380(Unk_8001A380 *arg0, Unk_8001A380_Src *arg1, Unk_8001A380_Quad *arg2, s32 arg3, u16 arg4, u16 arg5) {
    s32 var_a0;

    if (D_8008A830 != 0) {
        var_a0 = D_8008A834;
    } else {
        var_a0 = D_80090C18;
    }
    arg0->unk0 = var_a0;
    arg0->unk4 = D_8008A824;
    arg0->unk8 = D_8008A828;
    if (arg3 != 0) {
        arg0->unkC = arg4;
        arg0->unkE = arg5;
    }
    arg0->unk10 = *arg2;
    arg0->unk14 = arg1->unk30;
}

void func_8001A3EC(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    Unk_8001A3EC_Ref *dst = arg0;
    Unk_8001A3EC_Ref *src = arg1;

    dst->unk0->head = src->unk0->head;
    dst->unk4->head = src->unk4->head;
    dst->unk8->head = src->unk8->head;
    dst->unk0->tail = *(Unk_8001A3EC_Quad *)arg2;
    dst->unk4->tail = *(Unk_8001A3EC_Quad *)arg3;
    dst->unk8->tail = *(Unk_8001A3EC_Quad *)arg4;
}

void func_8001A4C0(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5) {
    Unk_8001A4C0_Ref *dst = arg0;
    Unk_8001A4C0_Ref *src = arg1;

    func_8001A3EC(arg0, arg1, arg2, arg3, arg4);
    dst->unkC->head = src->unkC->head;
    dst->unkC->tail = *(Unk_8001A4C0_Quad *)arg5;
}

void func_8001A54C(s32 arg0, s32 arg1) {
    D_8008A830 = arg0;
    if (arg0 != 0) {
        D_8008A834 = arg1;
    }
}

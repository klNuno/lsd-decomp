#include "common.h"

typedef struct Unk_80028A34 {
    u8 pad[0xC];
    s32 unkC;
} Unk_80028A34;
s32 D_8008A85C;
s32 D_8008A860;
s32 D_8008A864;
s32 D_8008A870;
s32 D_8008A874;
s32 D_8008A878;
s32 *D_8008A894;
s32 D_8008A898;
s32 D_8008A8A0;
void func_800280D0(void);
void func_800280E0(void);
s32 D_8008A890;
typedef struct Unk_80028A50 {
    u8 pad[0xC];
    s32 unkC;
    u8 pad2[0xC];
    u32 unk1C;
} Unk_80028A50;
void func_80028218(void);
typedef struct Unk_800288E0 {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    void (*unkC)(s32);
} Unk_800288E0;
Unk_800288E0 *func_80026C9C(void);
void *func_80027E68(void);
void func_80027E78(void);
typedef struct Unk_80027228 {
    void *unk0;
    u8 pad4[0x24];
    s16 unk28;
} Unk_80027228;
typedef struct Unk_80027228Fn {
    u8 pad[8];
    void (*unk8)(Unk_80027228 *);
} Unk_80027228Fn;
s32 D_8008A868;
typedef struct Unk_800271D8 {
    u8 pad[0x8];
    void (*unk8)(s32);
} Unk_800271D8;
s32 func_80017B34(s32);
s32 D_8008A858;
void CdSetDebug(s32 level);
s32 CdControlB(s32 com, u8 *param, s32 result);
typedef struct Unk_80028898 {
    void *unk0;
    u8 pad_04[0x8];
    s32 unkC;
} Unk_80028898;
typedef struct Unk_80027274 Unk_80027274;
typedef struct {
    u8 pad[0x5C];
    void (*unk5C)(Unk_80027274 *);
    u8 pad2[0x74 - 0x60];
    void (*unk74)(void);
} Unk_80027274_Vt;
struct Unk_80027274 {
    Unk_80027274_Vt *vt;
};
s32 D_8008A89C;
s32 D_8008A8A4;
s32 func_800280EC(void);
void VSyncCallback(void (*func)(void));
s8 *func_800270B8(void);
s8 *strcpy(s8 *dst, s8 *src);
s8 *strcat(s8 *dst, s8 *src);
extern s8 D_8008A8A8[]; /* ";1" in .sdata */
s32 D_8008A86C;
char *strstr(char *haystack, char *needle);
typedef struct Unk_800282AC {
    u8 pad[0x8];
    s32 unk8;
    void *unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad2[0x6];
    u16 unk22;
    s32 unk24;
} Unk_800282AC;
void func_800281B0(void);
Unk_800282AC *func_8002832C(void);
typedef struct Unk_800283C4 Unk_800283C4;
struct Unk_800283C4 {
    void *unk0;
    s32 unk4;
    u8 pad[0x14];
    Unk_800283C4 *unk1C;
    Unk_800283C4 *unk20;
};
void func_80017CFC(void *);
typedef struct Unk_80027480 {
    u8 pad[0xC];
    s32 unkC;
    u8 pad2[0x28 - 0x10];
    u16 unk28;
} Unk_80027480;
void func_80028844(s32 arg0, s32 arg1);
void func_80028864(void);
typedef struct Unk_80027C80_Vt {
    u8 pad[0x58];
    void (*unk58)(Unk_800282AC *, char *);
} Unk_80027C80_Vt;
s32 func_800284C4(char *arg0);
void func_800282AC(Unk_800282AC *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
typedef struct Unk_80020AF4 {
    /* 0x00 */ u8 pad_00[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 pad_10[0x10];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
} Unk_80020AF4;
Unk_80020AF4 *func_80020C5C(void);
typedef struct Unk_80027F18_Vt {
    u8 pad[0x84];
    void (*unk84)(void *, void (*)(void));
} Unk_80027F18_Vt;
typedef struct Unk_80027F18 {
    Unk_80027F18_Vt *vt;
} Unk_80027F18;
typedef struct Unk_800280EC {
    u8 pad[0x68];
    void (*unk68)(void);
} Unk_800280EC;
s32 D_8008A88C;
s32 func_80018458(void);
void func_8002858C(void);
void func_800286E4(void);

s32 func_800271D8(void) {
    s32 temp_v0;

    temp_v0 = func_80017B34(0x2C);
    if (temp_v0 != 0) {
        ((Unk_800271D8 *)func_80027E68())->unk8(temp_v0);
        return temp_v0;
    }
    return 0;
}

void func_80027228(Unk_80027228 *arg0) {
    ((Unk_80027228Fn *)func_80026C9C())->unk8(arg0);
    arg0->unk0 = func_80027E68();
    arg0->unk28 = 0;
    func_80027E78();
}

void func_80027274(Unk_80027274 *arg0) {
    arg0->vt->unk74();
    arg0->vt->unk5C(arg0);
}

void func_800272C8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800272D0);

void func_80027480(Unk_80027480 *arg0) {
    if (D_8008A85C == 0 && D_8008A860 == 0) {
        func_80028A34();
        return;
    }
    func_800280D0();
    if (arg0->unk28 != 0) {
        if (D_8008A864 == 0) {
            func_80028844(0, 0);
            arg0->unkC = 0;
            func_80028864();
        }
    } else {
        func_800282AC(arg0, 0, 3, 0, 0);
    }
    func_800280E0();
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027528);

void func_800276C8(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800276D0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027800);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027A24);

void func_80027C80(Unk_800282AC *arg0, char *arg1) {
    Unk_800283C4 *uninit;

    func_800280D0();
    if (arg1 != 0) {
        if (D_8008A85C != 0) {
            uninit->unk4 = 1;
            func_800282AC(arg0, func_800284C4(arg1), 7, 0, 0);
        } else {
            (*(Unk_80027C80_Vt **)arg0)->unk58(arg0, arg1);
            if (arg0->unk22 == 0) {
                arg0->unk24 = arg0->unk24 | 4;
            }
        }
    }
    func_800280E0();
}

void func_80027D40(void) {
    func_800280D0();
    func_80028218();
    func_800280E0();
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027D70);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027E68);

void func_80027E78(void) {
    u8 param;

    if (D_8008A858 == 0) {
        CdSetDebug(0);
        param = 0x80;
        while (CdControlB(0xE, &param, 0) == 0) {
        }
        D_8008A858 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027EC8);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027ED4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027EE0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027EEC);

s32 func_80027EF8(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = D_8008A860;
    }
    return D_8008A85C;
}

s32 func_80027F18(s32 arg0, s32 arg1, s32 arg2) {
    Unk_80027F18 *temp;

    if (D_8008A864 == 0) {
        if (arg2 == 0) {
            temp = (Unk_80027F18 *)func_80020C5C();
            if (D_8008A85C == 0) {
                if (arg0 != 0) {
                    temp->vt->unk84(temp, func_800280EC);
                }
            } else {
                if (arg0 == 0) {
                    temp->vt->unk84(temp, NULL);
                }
            }
        }
        D_8008A8A4 = arg2;
        D_8008A85C = arg0;
        D_8008A860 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FD8);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FE4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FF0);

INCLUDE_RODATA("asm/nonmatchings/game/800271D8", D_800107D8);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80027FFC);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800280D0);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800280E0);

s32 func_800280EC(void) {
    if (D_8008A88C == 0) {
        if (func_80018458() == 0) {
            if (D_8008A8A4 != 0) {
                VSyncCallback(0);
            }
            if (D_8008A898 == 1) {
                func_8002858C();
            } else if (D_8008A898 == 2) {
                func_800286E4();
            }
            if (D_8008A890 != 0) {
                ((Unk_800280EC *)func_80027E68())->unk68();
            }
            if (D_8008A8A4 != 0) {
                VSyncCallback(func_800280EC);
            }
        }
    }
    return 0;
}

void func_800281B0(void) {
    func_800280D0();
    if (D_8008A89C == 0) {
        if (D_8008A8A4 != 0) {
            VSyncCallback(&func_800280EC);
        }
        D_8008A89C = 1;
    }
    D_8008A890 = 1;
    func_800280E0();
}

void func_80028218(void) {
    func_800280D0();
    if ((D_8008A898 == 0) && (D_8008A89C != 0)) {
        if (D_8008A8A4 != 0) {
            VSyncCallback(0);
        }
        D_8008A89C = 0;
        D_8008A890 = 0;
    }
    func_800280E0();
}

void func_80028280(void) {
    func_800280D0();
    D_8008A890 = 0;
    func_800280E0();
}

void func_800282AC(Unk_800282AC *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk_800282AC *temp_v0;

    temp_v0 = func_8002832C();
    temp_v0->unk8 = arg2;
    temp_v0->unk14 = arg3;
    temp_v0->unkC = arg0;
    temp_v0->unk10 = arg1;
    temp_v0->unk18 = arg4;
    arg0->unk24 = 0;
    arg0->unk22 = arg0->unk22 + 1;
    func_800281B0();
}

Unk_800282AC *func_8002832C(void) {
    Unk_800283C4 *temp_v0;
    Unk_800283C4 *var_v1;

    func_800280D0();
    temp_v0 = (Unk_800283C4 *)func_80017B34(0x24);
    if (temp_v0 != NULL) {
        temp_v0->unk1C = NULL;
        temp_v0->unk20 = NULL;
        temp_v0->unk0 = NULL;
        temp_v0->unk4 = 0;
        if (D_8008A894 != NULL) {
            var_v1 = (Unk_800283C4 *)D_8008A894;
            while (var_v1->unk20 != NULL) {
                var_v1 = var_v1->unk20;
            }
            var_v1->unk20 = temp_v0;
            temp_v0->unk1C = var_v1;
        } else {
            D_8008A894 = (s32 *)temp_v0;
        }
    }
    func_800280E0();
    return (Unk_800282AC *)temp_v0;
}

void func_800283C4(Unk_800283C4 *arg0) {
    func_800280D0();
    if (arg0 != NULL) {
        if (arg0->unk1C != NULL) {
            arg0->unk1C->unk20 = arg0->unk20;
        } else {
            D_8008A894 = (s32 *)arg0->unk20;
        }
        if (arg0->unk20 != NULL) {
            arg0->unk20->unk1C = arg0->unk1C;
        }
        func_80017CFC(arg0);
    }
    func_800280E0();
}

s32 func_80028448(char *arg0) {
    s32 entry;
    s32 i;

    entry = D_8008A868;
    i = 0;
    func_800280D0();
    do {
        if (strstr((char *)entry, arg0) != NULL) {
            func_800280E0();
            return entry;
        }
        i++;
        entry += 0x1C;
    } while (i < D_8008A86C);
    return 0;
}

s32 func_800284C4(char *arg0) {
    s32 entry;
    s32 i;

    entry = D_8008A868;
    i = 0;
    func_800280D0();
    do {
        if (strstr((char *)entry, arg0) != NULL) {
            func_800280E0();
            return i;
        }
        entry += 0x1C;
        i++;
    } while (i < D_8008A86C);
    return -1;
}

s32 func_80028540(s32 arg0) {
    s32 temp_s0;

    temp_s0 = D_8008A868;
    func_800280D0();
    temp_s0 += arg0 * 0x1C;
    func_800280E0();
    return temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_8002858C);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_800286E4);

void func_80028844(s32 arg0, s32 arg1) {
    D_8008A864 = 1;
    D_8008A874 = arg0;
    D_8008A878 = arg1;
    D_8008A870 = 0;
    *D_8008A894 = 1;
}

void func_80028864(void) {
    D_8008A874 = 0;
    D_8008A878 = 0;
    D_8008A898 = 0;
    D_8008A870 = 1;
    D_8008A8A0 = 0;
    D_8008A864 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028888);

void func_80028898(Unk_80028898 *arg0) {
    func_80026C9C()->unk8(arg0);
    arg0->unk0 = func_80027E68();
    arg0->unkC = 0;
}

void func_800288E0(s32 arg0) {
    func_80026C9C()->unkC(arg0);
}

void func_80028918(void) {
}

INCLUDE_RODATA("asm/nonmatchings/game/800271D8", D_800107F4);

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028920);

s8 *func_800289CC(s8 *arg0, s8 *arg1) {
    *arg0 = 0x5C;
    strcpy(arg0 + 1, func_800270B8());
    strcat(arg0, arg1);
    strcat(arg0, D_8008A8A8);
    return arg0;
}

void func_80028A34(Unk_80028A34 *arg0) {
    if (arg0->unkC != 0) {
        arg0->unkC = 0;
    }
}

s32 func_80028A50(Unk_80028A50 *arg0) {
    if (arg0->unkC != 0) {
        return ((arg0->unk1C >> 0xB) + 1) << 0xB;
    }
    return 0;
}

void func_80028A7C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028A84);

void func_80028B64(void) {
}

INCLUDE_ASM("asm/nonmatchings/game/800271D8", func_80028B6C);

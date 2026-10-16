#include "common.h"
#include "game/dreamsys.h"

extern void Object_DeleteArray(void *, s32);
u8 *g_navFlags;
s32 *g_dynamicLinkCount;
extern s32 D_8008ABF0[];
s32 D_8008ACC4;
s32 D_8008ACBC;
typedef struct { u8 pad[5]; s8 u5; } S6;
extern S6 *D_80088BA4[];
s32 D_8008ACC8;
typedef struct Unk_8005B5A4 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Unk_8005B5A4;
extern s16 g_stageTimeLimits[];
void func_800573CC(void *arg0, s32 arg1, s32 *arg2);
extern void func_80056D18(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_800531CC(void *, void *);
typedef struct { s32 u0; s32 u4; u8 pad[0x14]; s32 u1C; s32 u20; u8 pad2[0xC]; s32 u30; s32 u34; } S;
void func_8002CC84(void *, void *);
s32 Mood_GetColor(s16 *arg0);
extern u8 D_80088748[];
extern s32 D_80088710[];
extern s32 D_80088664[];
s32 func_8005C150(void *arg0, void *arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 arg6);
extern u8 D_800889F0[];
extern void *D_80088980[];
extern void *D_80088820[];
s16 *Stage_GetChunkMood(s32 arg0, s8 *arg1);
extern u8 D_80088B5C;
extern s32 D_80088B24;
extern s32 D_80088A80;
s32 D_8008ABE4;
extern u8 D_80088CBC[];
extern s32 D_80088C4C[];
s32 Spawn_PickRandom(void *arg0, s32 arg1, s32 arg2);
s32 DreamSys_ExecuteLink();
extern u8 D_80087E80[];
typedef struct Unk_8005AFDC_VtblB {
    u8 pad_00[0x10C];
    s32 (*unk10C)(void *, s32, s32);
} Unk_8005AFDC_VtblB;
typedef struct Unk_8005AFDC_B {
    Unk_8005AFDC_VtblB *vt;
} Unk_8005AFDC_B;
typedef struct Unk_800581C4_Obj {
    u8 pad_00[0x70];
    void (*unk70)(void *, s32);
    u8 pad_74[0x94 - 0x74];
    void (*unk94)(void *);
} Unk_800581C4_Obj;
typedef struct Unk_800581C4 {
    Unk_800581C4_Obj *unk0;
    u8 pad_04[0x238 - 0x04];
    s32 unk238;
} Unk_800581C4;
s32 func_8005BCB4(void *, void *, s32);
typedef struct Unk_80058078_Vtbl {
    u8 pad_00[0x6C];
    void (*unk6C)(void *, s32);
    u8 pad_70[0xD4 - 0x70];
    void (*unkD4)(void *, void *, s32);
    u8 pad_D8[0x158 - 0xD8];
    void (*unk158)(void *);
    void (*unk15C)(void *);
    void (*unk160)(void *);
    u8 pad_164[0x174 - 0x164];
    void (*unk174)(void *);
    u8 pad_178[0x204 - 0x178];
    void (*unk204)(void *, void *);
    void (*unk208)(void *, void *, s32);
} Unk_80058078_Vtbl;
typedef struct Unk_80058078 {
    Unk_80058078_Vtbl *vt;
    u8 pad_04[0x2C - 0x04];
    s32 unk2C;
    u8 pad_30[0x6C - 0x30];
    s32 unk6C;
    u8 pad_70[0x84 - 0x70];
    s32 unk84;
    u8 pad_88[0x144 - 0x88];
    u8 unk144[0x10];
    u8 unk154[0x10];
} Unk_80058078;
s32 Nav_CalcScore(void);
typedef struct Unk_80058390_Vt {
    u8 pad_00[0x44];
    void (*unk44)(void *, void *, s32);
} Unk_80058390_Vt;
typedef struct Unk_80058390 {
    u8 pad_00[0x38];
    s32 unk38;
    u8 pad_3C[0x238 - 0x3C];
    s32 unk238;
} Unk_80058390;
extern Unk_80058390_Vt *func_8003DFBC(void);
typedef struct Unk_80058A94_RetVt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    u8 pad_0C[0x50 - 0x0C];
    void (*unk50)(void *);
    u8 pad_54[0x9C - 0x54];
    void (*unk9C)(void *, s32 **, s32);
    u8 pad_A0[0xDC - 0xA0];
    void (*unkDC)(void *, s32 **, s32);
    void (*unkE0)(void *, s32 **, s32);
} Unk_80058A94_RetVt;
Unk_80058A94_RetVt *func_80057C84(void);
extern u16 D_8008875C[];
typedef struct Unk_8005BE28 {
    u8 pad_00[4];
    u16 u4;
} Unk_8005BE28;
s32 g_saveMagic;
extern void Nav_InitFlags(u8 *arg0, s32 *arg1);
extern void *memset(void *arg0, s32 arg1, s32 arg2);
s32 Spawn_PickFromMood(void *arg0, s32 *arg1, void *arg2, s32 arg3);
void *Heap_Alloc(s32 size);
DreamSysVtbl *DreamSys_GetVtable(void);
extern s32 D_80087E08[];
s32 Mood_CalcAxis(s32, s32, s32);
void Heap_Free(s32);
typedef struct Unk_80058308_ObjVt {
    u8 pad_00[4];
    void (*unk4)(void *);
} Unk_80058308_ObjVt;
typedef struct Unk_80058308_Obj {
    Unk_80058308_ObjVt *vt;
} Unk_80058308_Obj;
typedef struct Unk_80058308_Ret {
    u8 pad_00[0xDC];
    void (*unkDC)(void *);
} Unk_80058308_Ret;
typedef struct Unk_80058308 {
    u8 pad_00[0xA8];
    Unk_80058308_Obj *unkA8[100];
    u8 pad_238[0x240 - 0x238];
    s32 unk240;
} Unk_80058308;
s32 func_8005BE90();
s32 *func_8005BF48(void);
extern s32 D_80087EA4[];
extern void func_8002CD08(s32, void *);
extern s8 g_moodColors[][3];
void func_8001E6F8(DreamSys *dreamSys, s32 *arg1);
s32 func_8005BCF8(void *arg0, s16 *arg1, s32 arg2);
s32 func_8005BD3C(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2);
s32 Day_FindSpecial(void *arg0, s32 arg1);
typedef struct Unk_80058694_Vtbl {
    u8 pad_00[0xB8];
    void (*unkB8)(void *, s32, void *);
} Unk_80058694_Vtbl;
typedef struct Unk_80058694_Obj {
    Unk_80058694_Vtbl *vt;
} Unk_80058694_Obj;
typedef struct Unk_80058694 {
    u8 pad_00[0x1C];
    u32 unk1C;
    u8 pad_20[0xA8 - 0x20];
    Unk_80058694_Obj *unkA8[100];
    s32 unk238;
    u32 unk23C;
    s8 *unk240;
} Unk_80058694;
extern s32 D_8008ABBC;
extern s32 rand(void);
extern s16 g_specialDays[42];
extern s32 D_8008ABF4;
typedef struct Unk_8005C438 {
    s16 unk0;
    s16 unk2;
} Unk_8005C438;
extern s32 func_8002CC34(s32, void *, s32, void *, s32);
extern s16 D_8008ABD0[];
extern u8 D_80087EFC[];
void func_8005AF64(DreamSys *, s16 *, s16 *);
extern u8 D_8008ABAC[];
extern s32 D_8008ABB4[];
void *func_800404D0(s32 arg0, s32 arg1, s32 arg2);
typedef struct Unk_80058228 {
    u8 pad_00[0xA8];
    void *unkA8[100];
    u8 pad_238[0x240 - 0x238];
    void *unk240;
} Unk_80058228;
typedef struct Unk_80058228Bytes {
    s8 c[3];
} Unk_80058228Bytes;
extern Unk_80058228Bytes D_8008ABB8;
typedef struct Unk_8005942C_Vec {
    s32 x;
    s32 y;
    s32 z;
} Unk_8005942C_Vec;
extern s32 D_80087EE8[];
extern void func_8001E600(void *arg0, void *arg1, void *arg2, s32 arg3);
s32 func_8001EF14(s32 *arg0, s32 arg1, s32 *arg2);
s32 func_8005950C(Unk_8005B5A4 *arg0, Unk_8005B5A4 *arg1, s32 arg2);
typedef struct Unk_800580E0_Vt {
    u8 pad_00[0x5C];
    void (*unk5C)(void *, void *, s32);
} Unk_800580E0_Vt;
typedef struct Unk_800580E0_Res {
    u8 pad_00[0x4];
    s32 unk4;
    s32 unk8;
} Unk_800580E0_Res;
typedef struct Unk_800580E0_A4_Vtbl {
    u8 pad_00[0x1B0];
    Unk_800580E0_Res *(*unk1B0)(void *, s32);
} Unk_800580E0_A4_Vtbl;
typedef struct Unk_800580E0_A4 {
    Unk_800580E0_A4_Vtbl *vt;
} Unk_800580E0_A4;
typedef struct Unk_800580E0_A8_Vtbl {
    u8 pad_00[0x60];
    void (*unk60)(void *, s32);
} Unk_800580E0_A8_Vtbl;
typedef struct Unk_800580E0_A8 {
    Unk_800580E0_A8_Vtbl *vt;
} Unk_800580E0_A8;
typedef struct Unk_800580E0_Vtbl {
    u8 pad_00[0x124];
    void (*unk124)(void *);
} Unk_800580E0_Vtbl;
typedef struct Unk_800580E0 {
    Unk_800580E0_Vtbl *vt;
    u8 pad_04[0x1C - 0x04];
    s32 unk1C;
    u8 pad_20[0x3C - 0x20];
    s32 unk3C;
    u8 pad_40[0xA4 - 0x40];
    Unk_800580E0_A4 *unkA4;
    Unk_800580E0_A8 *unkA8;
} Unk_800580E0;
extern u8 D_80088758[];
extern u8 *D_80088858[];
extern u8 *D_800889B8[];
s32 D_8008ACC0;
s32 func_8005BE28(Unk_8005BE28 *arg0, u8 arg1);
extern u8 *D_80088C84[];
extern u8 *D_80088BDC[];
extern s16 D_8008ABC0[];
s32 D_8008ABE8;
typedef struct Unk_8005BE90 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
} Unk_8005BE90;
extern s32 D_80087E50[];
extern s32 D_80087E5C[];
typedef struct Unk_800587F0_ArgVtbl {
    u8 pad_00[0x80];
    s32 (*unk80)(void *, s32);
} Unk_800587F0_ArgVtbl;
extern s8 D_80087EB0[];
extern s8 D_80087EC8[];
typedef struct Unk_80058968_ArgVtbl {
    u8 pad_00[0xE4];
    void (*unkE4)(void *, void *, void *, void *);
} Unk_80058968_ArgVtbl;
typedef struct Unk_80058968_RetVtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *, void *, void *);
} Unk_80058968_RetVtbl;
extern s16 D_8008ABC8[];
extern u8 D_80087F08[];
typedef struct Unk_80058B08_Ret {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32);
} Unk_80058B08_Ret;
extern s16 D_8008ABD8[];
typedef struct Unk_8001E6F8_Out {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Unk_8001E6F8_Out;
extern s32 D_80087E68[];
extern s32 D_80087E74[];
extern s16 D_80087E84[];
void func_80059A1C(DreamSys *dreamSys);
extern s32 g_graphVtbl[];
extern u8 g_dreamSysVtbl[];
s32 Graph_CheckReel(void *a0, void *a1);
typedef struct Unk_80058404_Vt {
    u8 pad_00[0xE0];
    void (*unkE0)(void *, void *);
} Unk_80058404_Vt;
typedef struct Unk_80058404_Res {
    u8 pad_00[0x4];
    s32 unk4;
    s32 unk8;
    u8 pad_0C[0x18 - 0x0C];
    s8 unk18[0x16D][2];
} Unk_80058404_Res;
typedef struct Unk_80058404_A4_Vtbl {
    u8 pad_00[0x1B0];
    Unk_80058404_Res *(*unk1B0)(void *, s32);
} Unk_80058404_A4_Vtbl;
typedef struct Unk_80058404_A4 {
    Unk_80058404_A4_Vtbl *vt;
} Unk_80058404_A4;
typedef struct Unk_80058404_A8_Vtbl {
    u8 pad_00[0xC4];
    void (*unkC4)(void *, void *, void *, s32);
} Unk_80058404_A8_Vtbl;
typedef struct Unk_80058404_A8 {
    Unk_80058404_A8_Vtbl *vt;
} Unk_80058404_A8;
typedef struct Unk_80058404_Pt {
    s32 x;
    s32 y;
} Unk_80058404_Pt;
typedef struct Unk_80058404 {
    u8 pad_00[0xA4];
    Unk_80058404_A4 *unkA4;
    Unk_80058404_A8 *unkA8[100];
    s32 unk238;
} Unk_80058404;
extern s32 D_80087E20[];
extern s8 D_80087E34[];
extern void (*D_80087E3C[])(void *, s32, s32);
typedef struct Unk_8005B03C_ObjVtbl {
    u8 pad_00[0x38];
    void (*unk38)(void *, void *, s32);
    u8 pad_3C[0x14C - 0x3C];
    s32 (*unk14C)(void *);
    s32 (*unk150)(void *);
    s32 (*unk154)(void *);
    s32 (*unk158)(void *);
} Unk_8005B03C_ObjVtbl;
s32 func_8005BFDC(void *arg0, void *arg1, s32 arg2);
s32 func_8005C02C(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2);
s32 func_8005C118(void);
extern s32 (*g_linkSteps[])(void *);
typedef struct { u8 r, g, b, cd; } Unk_8005C150_C;
typedef struct { Unk_8005C150_C c; s16 v; } Unk_8005C150_E;
typedef struct { Unk_8005C150_C c; u8 idx; s8 flag; } Unk_8005C150_Y;
typedef struct { s16 a; s16 b; s8 c; u8 d; } Unk_8005C150_T;
typedef struct { Unk_8005C150_C a; Unk_8005C150_E b; } Unk_8005C150;
extern Unk_8005C150_E D_80087F30[];
s32 func_8005BF74(void *arg0, void *arg1, s32 arg2);
s32 func_8005BFC4(void);
extern Unk_8005C150_Y *D_800885B8[];
extern u8 D_800885F0[];
s32 rand();
u32 Stage_FindChunkByMood(void *arg0, void *arg1);
typedef struct Unk_800585B4_Entry { s16 v; } Unk_800585B4_Entry;
typedef struct Unk_800585B4_A0 { u8 pad[0x23C]; u32 unk23C; s8 *unk240; } Unk_800585B4_A0;
typedef struct Unk_800585B4_A1 {
    u8 pad_00[4];
    s32 unk4;
    s32 unk8;
    u8 pad_0C[0xC];
    Unk_800585B4_Entry unk18[0x16D]; /* ring buffer, newest at unk8 - 1 */
    u8 pad_2F2[0x467 - 0x2F2];
    s8 unk467;
} Unk_800585B4_A1;
extern Unk_800585B4_Entry g_reelPoints[];
/* Looks for each of the 4 codes of g_reelPoints among the last n ring entries (n at most 100). */

void Graph_LoadImage(Unk_80058078 *arg0) {
    arg0->unk84 = 5;
    arg0->unk2C = 0x190;
    arg0->vt->unkD4(arg0, "ETC\\HGRAPH.TIM", 0);
    arg0->vt->unk6C(arg0, 10);
}

void func_800580E0(Unk_800580E0 *arg0, void *arg1, s32 arg2) {
    Unk_800580E0_Res *res;

    ((Unk_800580E0_Vt *)func_8003DFBC())->unk5C(arg0, arg1, arg2);
    if (arg0->unk3C == 1) {
        res = arg0->unkA4->vt->unk1B0(arg0->unkA4, 0);
        if (res->unk4 != 0 || res->unk8 != 0) {
            arg0->unkA8->vt->unk60(arg0->unkA8, arg0->unk1C & 1);
        }
    }
    arg0->vt->unk124(arg0);
}

void func_800581C4(Unk_800581C4 *arg0) {
    if (arg0->unk238 == 0) {
        arg0->unk0->unk70(arg0, 0x10);
        arg0->unk0->unk94(arg0);
    }
}

void Graph_CreateSprites(Unk_80058228 *arg0) {
    Unk_80058228Bytes sp;
    s32 i;
    s32 step;

    arg0->unkA8[0] = func_800404D0((s32)D_8008ABAC, (s32)D_8008ABB4, 0);
    sp = D_8008ABB8;
    i = 1;
    do {
        arg0->unkA8[i] = func_800404D0((s32)D_8008ABAC, (s32)&sp, 0);
        step = (i < 7) ? 0x14 : 1;
        i++;
        sp.c[0] -= step;
        sp.c[1] -= step;
        sp.c[2] -= step;
    } while (i < 100);
    arg0->unk240 = Heap_Alloc(4);
}

void Graph_FreeSprites(Unk_80058308 *arg0) {
    s32 i;
    Unk_80058308_Obj *obj;

    Heap_Free(arg0->unk240);
    for (i = 0; i < 100; i++) {
        obj = arg0->unkA8[i];
        obj->vt->unk4(obj);
    }
    ((Unk_80058308_Ret *)func_8003DFBC())->unkDC(arg0);
}

s32 func_80058390(Unk_80058390 *arg0, void *arg1, s32 arg2) {
    s32 ret;

    func_8003DFBC()->unk44(arg0, arg1, arg2);
    ret = 2;
    if (arg0->unk238 == 0) {
        ret = arg0->unk38;
    }
    return ret;
}

void Graph_Draw(Unk_80058404 *arg0, void *arg1) {
    Unk_80058404_Pt sp10;
    Unk_80058404_Pt sp18;
    Unk_80058404_Pt unused;
    Unk_80058404_A4 *temp_a0;
    Unk_80058404_A8 *obj;
    Unk_80058404_Res *res;
    s32 flag;
    s32 k;
    s32 i;
    s32 n;

    ((Unk_80058404_Vt *)func_8003DFBC())->unkE0(arg0, arg1);
    temp_a0 = arg0->unkA4;
    res = temp_a0->vt->unk1B0(temp_a0, 0);
    arg0->unk238 = Graph_CheckReel(arg0, res);
    flag = 0;
    if (res->unk4 == 0) {
        n = res->unk8;
        if (n >= 0x65) {
            n = 0x64;
        }
    } else {
        n = 0x64;
    }
    k = 0;
    i = res->unk8 - 1;
    if (n > 0) {
        do {
            if (i < 0) {
                i = 0x16C;
            }
            sp10.x = res->unk18[i][0] * 10 - 5;
            sp10.y = -res->unk18[i][1] * 10 - 5;
            if (k == 0) {
                sp18 = sp10;
                flag = 1;
            } else {
                obj = arg0->unkA8[k];
                obj->vt->unkC4(obj, arg1, &sp10, 0);
            }
            k += 1;
            i -= 1;
        } while (k < n);
    }
    if (flag != 0) {
        obj = arg0->unkA8[0];
        obj->vt->unkC4(obj, arg1, &sp18, 0);
    }
}

s32 Graph_CheckReel(void *a0, void *a1) {
    Unk_800585B4_A0 *arg0 = a0;
    Unk_800585B4_A1 *arg1 = a1;
    s32 n, j, k, count;
    u32 i;

    if (arg1->unk467 != 0) return 0;
    if (arg1->unk4 != 0) n = 100;
    else { n = arg1->unk8; if (n > 100) n = 100; }
    i = 0;
loop:
    count = 0;
    k = arg1->unk8 - 1;
    for (j = 0; j < n; j++) {
        if (k < 0) k = 0x16C;
        if (g_reelPoints[i].v == arg1->unk18[k].v) { count++; arg0->unk240[i] = j; }
        k--;
    }
    if (count == 0) return 0;
    if (++i < 4) goto loop;
    arg1->unk467 = 1;
    arg0->unk23C = 0;
    return 1;
}

void Graph_BlinkReel(Unk_80058694 *arg0) {
    u32 temp_a0;
    u32 temp_a1;
    Unk_80058694_Obj *obj;

    if (arg0->unk238 != 0) {
        temp_a0 = arg0->unk1C;
        if (temp_a0 >= 0x1F) {
            temp_a1 = arg0->unk23C;
            if ((temp_a1 < 4) && (temp_a0 % 24 == 0)) {
                obj = arg0->unkA8[arg0->unk240[temp_a1]];
                obj->vt->unkB8(obj, 1, &D_8008ABBC);
                arg0->unk23C = arg0->unk23C + 1;
            }
        }
    }
}

void *Graph_GetVtable(void) {
    return g_graphVtbl;
}

void *DreamSys_New(s32 arg0, s32 arg1, s32 arg2) {
    void *dreamSys;

    dreamSys = Heap_Alloc(0x928);
    if (dreamSys != 0) {
        DreamSys_GetVtable()->init(dreamSys, arg0, arg1, arg2);
        return dreamSys;
    }
    return 0;
}

void DreamSys_Init(DreamSys *dreamSys, void **arg1, s32 arg2, s32 camera) {
    func_80057C84()->unk8(dreamSys);
    dreamSys->vtbl = (DreamSysVtbl *)DreamSys_GetVtable();
    dreamSys->unk58 = arg2;
    dreamSys->camera.obj = camera;
    dreamSys->unk64 = 0;
    dreamSys->unk60 = arg1;
    dreamSys->vtbl->unk10(dreamSys, ((Unk_800587F0_ArgVtbl *)*arg1)->unk80(arg1, 0));
    dreamSys->vtbl->swapTimeLimit(dreamSys, -1);
    dreamSys->unk70 = 1;
    dreamSys->unk6C = 0;
    dreamSys->neverSaved = 1;
    dreamSys->vtbl->initNewGame(dreamSys);
    dreamSys->vtbl->unk40(dreamSys);
}

void func_800588EC(DreamSys *dreamSys) {
    dreamSys->vtbl->unk60(dreamSys, 0);
    dreamSys->vtbl->unk44(dreamSys, 1, D_80087E08);
    dreamSys->unk80 = 0;
    dreamSys->unk98 = 0;
    dreamSys->unkCC.word = 0;
    dreamSys->unk908 = 0;
    dreamSys->unk90C = 0;
    dreamSys->linkStep = 0;
    dreamSys->unk78 = 0;
    dreamSys->unk924 = 0;
}

void func_80058968(DreamSys *dreamSys, void **arg1) {
    s32 sp10[4];
    Flashback *elem;
    void *temp_a2;

    ((Unk_80058968_ArgVtbl *)*arg1)->unkE4(arg1, sp10, dreamSys, (u8 *)dreamSys + 0x16C);
    ((Unk_80058968_RetVtbl *)func_80057C84())->unk4C(dreamSys, arg1, sp10);
    dreamSys->vtbl->unk10(dreamSys, arg1);
    if (dreamSys->transition == 0xE) {
        elem = &dreamSys->flashbacks[dreamSys->nextFlashback];
        dreamSys->vtbl->unk44(dreamSys, 1, elem->rotation.bytes);
        dreamSys->vtbl->swapTimeLimit(dreamSys, elem->length + 4);
        dreamSys->nextFlashback++;
    }
    if (dreamSys->unk6C != 0) {
        temp_a2 = dreamSys->unk888;
        if (temp_a2 != 0) {
            dreamSys->vtbl->unk44(dreamSys, 1, temp_a2);
        }
    }
}

void func_80058A94(DreamSys *dreamSys) {
    DreamPlayer *player;

    player = dreamSys->player;
    player->vt->unkF0(player);
    dreamSys->vtbl->unk14(dreamSys, dreamSys->player);
    func_80057C84()->unk50(dreamSys);
}

void func_80058B08(DreamSys *dreamSys, s32 arg1) {
    s32 temp_v0;
    DreamPlayer *player;
    DreamPlayer *player2;

    ((Unk_80058B08_Ret *)func_80057C84())->unk88(dreamSys, arg1);
    switch (arg1) {
    case -1:
        temp_v0 = dreamSys->unk28->unk36 & 0x7F;
        dreamSys->unkB8 = temp_v0;
        if (temp_v0 >= 0x18) {
            dreamSys->unkB8 = 0;
        }
        if (dreamSys->transition == 0xF && dreamSys->unkB8 == 0) {
            dreamSys->unkB8 = 2;
        }
        if (dreamSys->stage == 9) {
            player = dreamSys->player;
            dreamSys->vtbl->unk1D4(dreamSys, player->vt->unk10C(player, 0, 0));
        }
        return;
    case -2:
        player2 = dreamSys->player;
        if (player2->vt->unk11C(player2, dreamSys->unk14.bytes + 0x18)->unk4->unk2C == 2) {
            player = dreamSys->player;
            dreamSys->vtbl->unk1D4(dreamSys, player->vt->unk10C(player, 0, 0));
        } else {
            dreamSys->vtbl->unk224(dreamSys);
        }
        return;
    }
}

void func_80058C58(DreamSys *dreamSys, s32 arg1, s32 arg2) {
    if (dreamSys->unk6C == 0 && dreamSys->unk70 == 0) {
        arg2 -= 2;
        if (dreamSys->unk908 == 0) {
            switch (arg2) {
                case 0:
                    dreamSys->unkA0 = 1;
                    break;
                case 1:
                    dreamSys->unkA0 = 2;
                    break;
                case 2:
                    dreamSys->unkA4 = 1;
                    break;
                case 3:
                    dreamSys->unkA4 = 2;
                    break;
                case 4:
                    dreamSys->unk88 = 1;
                    break;
                case 5:
                    if (dreamSys->unkA0 == 1) {
                        dreamSys->vtbl->unk184(dreamSys, 4);
                    }
                    break;
                case 6:
                    dreamSys->unk88 = 2;
                    break;
                case 11:
                    dreamSys->unk90 = 2;
                    break;
                case 12:
                    dreamSys->unkA0 = 4;
                    break;
                case 13:
                    dreamSys->unk90 = 1;
                    break;
                case 14:
                    dreamSys->unkA0 = 3;
                    break;
                case 23:
                    dreamSys->unk74 = 1;
                    break;
                case 32:
                    dreamSys->vtbl->unk188(dreamSys, arg1, arg2);
                    break;
                case 47:
                    break;
            }
        }
    }
}

void DreamSys_TickTimer(DreamSys *dreamSys, s32 sender, s32 message) {
    u32 ticks;

    if (message == 2) {
        ticks = dreamSys->timer;
        dreamSys->timer = ticks + 1;
        if (ticks >= (u32) dreamSys->timeLimit) {
            if (dreamSys->flashbackMode != 0) {
                if (dreamSys->transition != 0 || dreamSys->vtbl->loadNextFlashback(dreamSys, 0) != 0) {
                reset:
                    dreamSys->timer = 0;
                    return;
                }
            } else {
                dreamSys->vtbl->maybeSaveFlashback(dreamSys, 0, 0x10);
            }
            dreamSys->vtbl->unk30(dreamSys, 0xA);
            goto reset;
        }
        dreamSys->vtbl->unk118(dreamSys);
        dreamSys->vtbl->unk11C(dreamSys);
    }
}

void func_80058E8C(DreamSys *dreamSys, s32 **sender, s32 message) {
    func_80057C84()->unk9C(dreamSys, sender, message);
    if ((**sender & 0xFFF) == 0x114) {
        dreamSys->vtbl->unk1E4(dreamSys, sender, message);
    }
}

void func_80058F18(DreamSys *dreamSys, s32 **sender, s32 message) {
    func_80057C84()->unkDC(dreamSys, sender, message);
    if ((**sender & 0xFFFFF) == 0x1F234) {
        dreamSys->vtbl->onEntityEvent(dreamSys, sender, message);
    }
}

void DreamSys_OnWallTouch(DreamSys *dreamSys, s32 **sender, s32 message) {
    DreamPlayer *player;
    DreamPlace *src;

    func_80057C84()->unkE0(dreamSys, sender, message);
    if (message == 4 && dreamSys->transition == 0) {
        player = dreamSys->player;
        src = player->vt->unkD4(player, sender);
        dreamSys->place = *src;
        if (dreamSys->vtbl->linkStatic(dreamSys, &dreamSys->place) == 0 && dreamSys->dynamicLinkOn != 0) {
            dreamSys->vtbl->linkDynamic(dreamSys);
        }
        dreamSys->vtbl->unk224(dreamSys);
        dreamSys->vtbl->unkE8(dreamSys);
    }
}

void func_800590E0(void) {
}

s32 DreamSys_SetFlashbackMode(DreamSys *dreamSys, s32 *colorOut, s32 mode) {
    s32 oldMode;

    oldMode = dreamSys->flashbackMode;
    if (mode < 0) {
        *colorOut = Mood_GetColor((s16 *)((u8 *)dreamSys + (dreamSys->day * 2 + 0x190)));
    } else {
        dreamSys->flashbackMode = mode;
    }
    return oldMode;
}

void func_80059148(DreamSys *dreamSys, s32 arg1) {
    s32 temp_a2;

    dreamSys->unk6C = arg1;
    if (arg1 != 0) {
        dreamSys->vtbl->unk180(dreamSys, 1);
        temp_a2 = dreamSys->unk884;
        if (temp_a2 != 0) {
            dreamSys->vtbl->unk44(dreamSys, 1, temp_a2);
        }
    }
}

void func_800591B4(DreamSys *dreamSys, s32 arg1, s32 arg2) {
    Unk_8001E6F8_Out sp18;

    dreamSys->vtbl->logChunkMood(dreamSys, &dreamSys->place);
    dreamSys->vtbl->unk138(dreamSys, 1);
    dreamSys->vtbl->unk13C(dreamSys, 1);
    dreamSys->vtbl->unk180(dreamSys, arg1);
    dreamSys->unkBC = -1;
    dreamSys->unkB4 = 0;
    dreamSys->unkB8 = 0;
    dreamSys->unkA0 = 0;
    dreamSys->unkA4 = 0;
    dreamSys->unk88 = 0;
    dreamSys->unk90 = 0;
    dreamSys->unk8C = 0;
    dreamSys->unk94 = 0;
    dreamSys->vtbl->unk18C(dreamSys, 0, 1, 1, 1);
    dreamSys->vtbl->unk190(dreamSys, arg2);
    dreamSys->cinematic.id.variant = -1;
    dreamSys->unk70 = 0;
    dreamSys->transition = 0;
    dreamSys->unk74 = 0;
    dreamSys->unk908 = 0;
    dreamSys->unk90C = 0;
    dreamSys->linkStep = 0;
    dreamSys->unk78 = 0;
    func_8001E6F8(dreamSys, (s32 *)&sp18);
    sp18.unk8 = 0;
    sp18.unkA = 1;
    dreamSys->vtbl->unk44(dreamSys, 1, &sp18);
}

void func_80059310(DreamSys *dreamSys) {
    dreamSys->unk70 = 1;
}

s32 func_8005931C(DreamSys *dreamSys) {
    return dreamSys->unk74;
}

s32 DreamSys_SwapTimeLimit(DreamSys *dreamSys, s32 seconds) {
    s32 old;

    if (seconds >= 0) {
        seconds *= 15;
    }
    old = dreamSys->timeLimit;
    dreamSys->timeLimit = seconds;
    if (old >= 0) {
        old = (u32)old / 15;
    }
    return old;
}

u32 DreamSys_GetElapsedSeconds(DreamSys *dreamSys) {
    return dreamSys->timer / 15;
}

void func_8005937C(DreamSys *dreamSys, s32 value) {
    dreamSys->unk58 = value;
}

void func_80059384(DreamSys *dreamSys, s32 value) {
    dreamSys->camera.obj = value;
}

void func_8005938C(DreamSys *dreamSys, s32 value) {
    dreamSys->unk64 = value;
}

void func_80059394(DreamSys *dreamSys) {
    if (dreamSys->unk70 == 0) {
        dreamSys->unk74 = 0;
        dreamSys->dynamicLinkOn = dreamSys->timer % dreamSys->unk120 == 0;
    }
}

void func_800593D8(DreamSys *dreamSys) {
    if (dreamSys->unk80 != NULL) {
        dreamSys->unk80();
    }
    if (dreamSys->unk98 != NULL) {
        dreamSys->unk98(dreamSys);
    }
}

s32 func_8005942C(DreamSys *dreamSys, Unk_8005942C_Vec *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    Unk_8005942C_Vec sp10;
    s32 temp_v0;
    s32 *temp;

    D_80087EE8[0] = arg2;
    func_8001E600(dreamSys, &sp10, &D_80087EE8[-2], 0);
    temp_v0 = func_8005950C((Unk_8005B5A4 *)(dreamSys->camera.bytes + 0x14), (Unk_8005B5A4 *)(dreamSys->camera.bytes + 0x20), arg2);
    if (dreamSys->unkC != 0) {
        temp = (s32 *)(dreamSys->unk14.bytes + 0x38);
    } else {
        temp = NULL;
    }
    sp10.y = temp_v0 + temp[1];
    if (arg1 != NULL) {
        *arg1 = sp10;
    }
    if (arg3 != NULL) {
        return func_8001EF14((s32 *)&sp10, arg4, arg3);
    }
    return 0;
}

s32 func_8005950C(Unk_8005B5A4 *start, Unk_8005B5A4 *end, s32 pos) {
    s32 span;

    pos /= 1024;
    span = (end->unk8 - start->unk8) / 1024;
    if (span == 0) {
        span = 1;
    }
    return ((end->unk4 - start->unk4) * pos) / span + start->unk4;
}

void func_80059590(DreamSys *dreamSys) {
    dreamSys->unk7C = 0;
}

void func_80059598(DreamSys *dreamSys) {
    dreamSys->unk78 = 0;
}

s32 func_800595A0(void) {
    return 0;
}

void func_800595A8(DreamSys *dreamSys, s32 arg1) {
    dreamSys->vtbl->unk13C(dreamSys, 0);
    if (arg1 != 0) {
        dreamSys->vtbl->unk138(dreamSys, 0);
    }
}

void func_80059610(DreamSys *dreamSys, s32 arg1, s32 arg2) {
    dreamSys->vtbl->unk13C(dreamSys);
    dreamSys->vtbl->unk138(dreamSys, arg2);
}

void func_8005966C(DreamSys *dreamSys, s32 mode) {
    DreamSysVtbl *vtbl = dreamSys->vtbl;

    dreamSys->unk84 = mode;
    switch (mode) {
    case 0:
        dreamSys->unk80 = 0;
        return;
    case 1:
        dreamSys->unk80 = vtbl->unk140;
        return;
    case 2:
        dreamSys->unk80 = vtbl->unk14C;
        return;
    case 3:
        dreamSys->unk80 = vtbl->unk150;
        return;
    }
}

void func_800596E8(DreamSys *dreamSys, s32 mode) {
    DreamSysVtbl *vt;

    vt = dreamSys->vtbl;
    if (dreamSys->unk9C == 2) {
        vt->unk17C(dreamSys, 0);
    }
    dreamSys->unk9C = mode;
    switch (mode) {
    case 0:
        dreamSys->unk98 = 0;
        return;
    case 1:
        dreamSys->unk98 = vt->unk154;
        return;
    case 2: {
        s32 handler;
        DreamSysVtbl *temp_v1;

        handler = vt->unk178;
        temp_v1 = dreamSys->vtbl;
        dreamSys->unkC4 = 1;
        dreamSys->unkC8 = 1;
        dreamSys->unk98 = handler;
        func_8002CC34(dreamSys->unk58, dreamSys->unkCC.bytes, 1, dreamSys, temp_v1->unk194);
        return;
    }
    }
}

void func_800597C0(DreamSys *dreamSys) {
    dreamSys->vtbl->unk144(dreamSys);
    dreamSys->vtbl->unk148(dreamSys);
}

void func_80059814(DreamSys *dreamSys) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1_3;
    DreamCamera *camera2;
    DreamCamera *camera;
    s32 temp_v1;

    temp_v1 = dreamSys->unk88;
    if (temp_v1 != 0) {
        temp_a2 = D_80087E50[temp_v1];
        temp_v1_3 = D_80087E5C[temp_v1];
        temp_a1 = temp_a2 + dreamSys->unk8C;
        if ((temp_a1 < 0 ? ~temp_a1 + 1 : temp_a1) < temp_v1_3) {
            camera = dreamSys->camera.obj;
            camera->unk24 = (u32) (temp_a2 + camera->unk24);
            dreamSys->unk8C = temp_a1;
        }
        dreamSys->unk88 = 0;
        return;
    }
    temp_v0 = dreamSys->unk8C;
    if (temp_v0 != 0) {
        temp_a2 = -0x258;
        if (temp_v0 < 0) {
            temp_a2 = 0x258;
        }
        camera2 = dreamSys->camera.obj;
        camera2->unk24 = (u32) (temp_a2 + camera2->unk24);
        dreamSys->unk8C = (s32) (temp_a2 + dreamSys->unk8C);
    }
}

void func_800598E8(DreamSys *dreamSys) {
    s32 step;
    s32 sum;
    s32 lim;

    dreamSys->unkA8 = dreamSys->unkA0 == 1;
    if (dreamSys->unk90 != 0) {
        step = D_80087E68[dreamSys->unk90];
        sum = step + dreamSys->unk94;
        lim = D_80087E74[dreamSys->unk90];
        if ((sum < 0 ? ~sum + 1 : sum) < lim) {
            D_80087E84[0] = step;
            dreamSys->vtbl->unk44(dreamSys, 0, &D_80087E84[-2]);
            dreamSys->unk94 = sum;
        }
        dreamSys->unk90 = 0;
        func_80059A1C(dreamSys);
    } else if (dreamSys->unk94 != 0) {
        step = dreamSys->unk94 < 0 ? 0x2D : -0x2D;
        D_80087E84[0] = step;
        dreamSys->vtbl->unk44(dreamSys, 0, &D_80087E84[-2]);
        dreamSys->unk94 += step;
        func_80059A1C(dreamSys);
    }
}

void func_80059A1C(DreamSys *dreamSys) {
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = dreamSys->unkA0;
    dreamSys->unkA8 = 0;
    if (temp_v1 != 0) {
        if (temp_v1 & 1) {
            var_v0 = temp_v1 + 1;
        } else {
            var_v0 = temp_v1 - 1;
        }
        dreamSys->unkA0 = var_v0;
    }
}

void func_80059A48(void) {
}

void func_80059A50(void) {
}

void func_80059A58(DreamSys *dreamSys) {
    if (dreamSys->unk6C == 0) {
        dreamSys->vtbl->unk174(dreamSys);
        dreamSys->vtbl->unk158(dreamSys);
    } else if (dreamSys->unk6C == 2) {
        dreamSys->vtbl->unk160(dreamSys);
    } else {
        dreamSys->vtbl->unk15C(dreamSys);
    }
}

void func_80059AEC(DreamSys *dreamSys) {
    if (dreamSys->unk70 == 0) {
        dreamSys->vtbl->unk170(dreamSys, dreamSys->vtbl->unk164(dreamSys, 1));
    }
}

void func_80059B50(DreamSys *dreamSys) {
    dreamSys->unkA0 = 1;
    if (dreamSys->unk70 == 0) {
        dreamSys->vtbl->unk170(dreamSys, dreamSys->vtbl->unk164(dreamSys, 1));
    } else {
        dreamSys->vtbl->unk164(dreamSys, 0);
    }
}

void func_80059BD4(DreamSys *dreamSys) {
    dreamSys->unkA0 = 1;
}

s32 func_80059BE0(DreamSys *dreamSys, void *arg1) {
    s32 var_s1 = 0;
    s32 var_s3;
    s32 temp_a0;
    s32 bit;
    s32 step;
    DreamCamera *camera = arg1;

    var_s3 = 0;
    if (dreamSys->unkA0 != 0) {
        var_s3 = dreamSys->unkA0;
        temp_a0 = dreamSys->unkB4 + 1;
        dreamSys->unkB4 = temp_a0;
        if (temp_a0 < 4) {
            if (dreamSys->unkAC == 4) {
                bit = temp_a0 & 1;
                var_s1 = bit == 0;
            }
        } else {
            dreamSys->unkA0 = 0;
            var_s1 = 1;
        }
        if (var_s1 != 0) {
            dreamSys->vtbl->unk168(dreamSys);
        }
        camera = dreamSys->camera.obj;
        if (camera != 0 && dreamSys->shake != 0 && arg1 != 0) {
            step = -0x32;
            if (dreamSys->unkB4 >= 3) {
                step = 0x32;
            }
            camera->unk18 += step;
            camera->unk24 += step;
        }
        if (dreamSys->unkA0 == 0) {
            dreamSys->unkB4 = 0;
        }
    }
    if (var_s1 == 0) {
        dreamSys->vtbl->unk16C(dreamSys, camera);
    }
    return var_s3;
}

void func_80059D1C(DreamSys *dreamSys) {
    DreamSysObj58 *obj = dreamSys->unk58;
    s32 idx = dreamSys->unkB8;
    DreamSysObj58Vtbl *vt = obj->vt;
    s32 t;

    if (idx != 0) {
        t = D_80087EB0[idx] * 0x10;
        vt->unk9C(obj, D_80087EC8[idx]);
        dreamSys->unkBC = vt->unk80(obj, t, 0x6E, 0x6E);
        if (dreamSys->unkB8 != 0x16) {
            dreamSys->unkBC = -1;
        }
        if (dreamSys->unkB8 == 0xB) {
            vt->unk9C(obj, 1);
            vt->unk80(obj, t, 0x6E, 0x6E);
            vt->unk9C(obj, 2);
            vt->unk80(obj, 0x90, 0x6E, 0x6E);
        }
    }
}

void func_80059E3C(DreamSys *dreamSys) {
    s32 temp_a1;
    DreamSysObj58 *temp_a0;

    temp_a1 = dreamSys->unkBC;
    if (temp_a1 >= 0) {
        temp_a0 = dreamSys->unk58;
        temp_a0->vt->unk84(temp_a0, temp_a1);
        dreamSys->unkBC = -1;
    }
}

void func_80059E98(DreamSys *dreamSys, s32 arg1) {
    s32 temp_s3;
    s32 place;
    DreamPlayer *player;
    DreamBody *body;

    if (arg1 != 0) {
        temp_s3 = D_80087E34[arg1] * D_80087E20[dreamSys->unkAC];
        dreamSys->vtbl->unk12C(dreamSys);
        player = dreamSys->player;
        place = player->vt->unk10C(player, 0, 0);
        if (dreamSys->vtbl->unk1DC(dreamSys, place) == 0 && dreamSys->vtbl->unk1D8(dreamSys, place) == 0 && dreamSys->vtbl->unk1D0(dreamSys, place) == 0) {
            dreamSys->vtbl->unk220(dreamSys);
            D_80087E3C[arg1](dreamSys, temp_s3, dreamSys->unk90C == 0);
            if (dreamSys->stage == 0) {
                body = dreamSys->unk14.body;
                if (body->unk1C < -0x7D0 && body->unk18 >= -0x1F3) {
                    dreamSys->vtbl->onWallTouch(dreamSys, dreamSys, 4);
                }
            }
        }
        dreamSys->unk14.body->unk0 = 0;
    }
}

void func_8005A050(DreamSys *dreamSys) {
    s32 temp_v0;

    temp_v0 = dreamSys->unkA4;
    if (temp_v0 != 0) {
        dreamSys->vtbl->unk44(dreamSys, 0, D_80087E80 + temp_v0 * 12);
        dreamSys->unkA4 = 0;
    }
}

void func_8005A0B0(DreamSys *dreamSys) {
    DreamCamera *camera;

    if (dreamSys->unkC4 != 0) {
        dreamSys->vtbl->unkBC(dreamSys, D_80087EA4);
        camera = dreamSys->camera.obj;
        camera->unk24 = camera->unk24 - 0x258;
    }
    if (dreamSys->unkC8 != 0) {
        func_8002CD08((s32) dreamSys->unk58, dreamSys->unkCC.bytes);
    }
}

void func_8005A134(DreamSys *dreamSys, s32 arg1) {
    dreamSys->unkC4 = 0;
    dreamSys->unkC8 = arg1;
    if (arg1 != 0) {
        func_8002CC84(dreamSys->unk58, dreamSys->unkCC.bytes);
    }
}

s32 func_8005A168(DreamSys *dreamSys, s32 arg1) {
    s32 temp_v0;

    temp_v0 = dreamSys->unkAC;
    if (arg1 >= 0) {
        dreamSys->unkAC = arg1;
        dreamSys->unkB0 = arg1;
    }
    return temp_v0;
}

void func_8005A184(DreamSys *dreamSys, s32 arg1) {
    s32 temp_v0;

    temp_v0 = dreamSys->unkAC;
    if (temp_v0 != arg1) {
        dreamSys->unkB0 = temp_v0;
        dreamSys->unkAC = arg1;
    }
}

void func_8005A1A4(DreamSys *dreamSys) {
    dreamSys->unkAC = dreamSys->unkB0;
}

void func_8005A1B0(DreamSys *dreamSys, s32 dynamicLinkOn, s32 arg2, s32 arg3, s32 arg4) {
    if (dynamicLinkOn >= 0) {
        dreamSys->dynamicLinkOn = dynamicLinkOn;
    }
    if (arg2 >= 0) {
        dreamSys->unk128 = arg2;
    }
    if (arg3 >= 0) {
        dreamSys->unk12C = arg3;
    }
    if (arg4 >= 0) {
        dreamSys->unk130 = arg4;
    }
}

void func_8005A1EC(DreamSys *dreamSys, s32 arg1) {
    dreamSys->unk120 = arg1;
}

void func_8005A1F4(s32 arg0, S *arg1) {
    s32 r;
    if (arg1->u0 == 1) {
        r = arg1->u4 % 20; if (r == 0) {
            arg1->u1C = 9;
            arg1->u20 = -1;
        } else {
            arg1->u30 = 9;
            arg1->u34 = -1;
        }
    }
}

void DreamSys_InitNewGame(DreamSys *dreamSys) {
    dreamSys->magic = g_saveMagic;
    dreamSys->year = 0;
    dreamSys->day = 0;
    dreamSys->unlockScore = 0;
    dreamSys->navScore = 0;
    dreamSys->instanceScore = 0;
    dreamSys->flashbackCount = 0;
    dreamSys->reelSeen = 0;
    dreamSys->unk5D8 = 0;
    dreamSys->shake = 1;
    dreamSys->unk67C = 0;
    dreamSys->unk680 = 0;
    Nav_InitFlags(dreamSys->navFlags, &dreamSys->dynamicLinkCount);
    memset(dreamSys->unk684, 0, 0x1F4);
}

void DreamSys_SwapShake(DreamSys *dreamSys, s32 *shake) {
    s32 old;

    old = dreamSys->shake;
    dreamSys->shake = *shake;
    *shake = old;
}

s32 DreamSys_GetDayNumber(DreamSys *dreamSys, s32 *yearOut) {
    if (yearOut != NULL) {
        *yearOut = dreamSys->year;
    }
    return dreamSys->day + 1;
}

s32 DreamSys_AdvanceDay(DreamSys *dreamSys) {
    if (++dreamSys->day >= 365) {
        dreamSys->day = 0;
        dreamSys->year++;
    }
    return dreamSys->day;
}

void DreamSys_ClearNeverSaved(DreamSys *dreamSys) {
    dreamSys->neverSaved = 0;
}

s32 DreamSys_IsNeverSaved(DreamSys *dreamSys) {
    return dreamSys->neverSaved;
}

s32 DreamSys_GetSaveBlock(s32 dreamSys, s32 *sizeOut) {
    if (sizeOut != NULL) {
        *sizeOut = 0x700;
    }
    return dreamSys + 0x178;
}

s32 DreamSys_StartDay(DreamSys *dreamSys) {
    s32 temp;

    dreamSys->nextFlashback = 0;
    dreamSys->timer = 0;
    dreamSys->savedDay = dreamSys->day;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->vtbl->loadNextFlashback(dreamSys, 1);
        return dreamSys->stage;
    }
    temp = Day_FindSpecial(dreamSys->cinematic.bytes, dreamSys->day + 1);
    dreamSys->vtbl->resetMoodAccumulators(dreamSys, temp);
    if (temp == 0) {
        dreamSys->vtbl->chooseStart(dreamSys);
        return dreamSys->stage;
    }
    return -1;
}

s32 DreamSys_EndDay(DreamSys *dreamSys, s32 reason) {
    dreamSys->day = dreamSys->savedDay;
    if (dreamSys->flashbackMode == 0 && reason == 0) {
        dreamSys->vtbl->calcUnlockScore(dreamSys);
        dreamSys->vtbl->computeDayPoint(dreamSys, &dreamSys->graph[dreamSys->day]);
        dreamSys->vtbl->advanceDay(dreamSys);
    } else if (reason == 2) {
        dreamSys->vtbl->initNewGame(dreamSys);
        dreamSys->neverSaved = 1;
    }
    return dreamSys->flashbackMode;
}

CineRef DreamSys_GetCinematic(DreamSys *dreamSys) {
    return dreamSys->cinematic.ref;
}

void DreamSys_ChooseStart(DreamSys *dreamSys) {
    s32 prevPoint;
    s32 seconds;

    dreamSys->vtbl->getPreviousPoint(dreamSys, &prevPoint, 1);
    dreamSys->stage = Spawn_PickFromMood(&dreamSys->place, &seconds, &prevPoint, dreamSys->day);
    seconds = dreamSys->vtbl->swapTimeLimit(dreamSys, seconds);
    dreamSys->transition = 0xB;
}

void DreamSys_LinkDynamic(DreamSys *dreamSys) {
    if (dreamSys->transition == 0) {
        DreamSys_ExecuteLink(dreamSys, Spawn_PickRandom(&dreamSys->place, dreamSys->stage, dreamSys->timer), 0xC, 1);
    }
}

s32 DreamSys_LinkStatic(DreamSys *dreamSys, void *target) {
    s32 newStage;

    if (dreamSys->transition == 0) {
        newStage = func_8005BCB4(&dreamSys->place, target, dreamSys->stage);
        if (newStage >= 0) {
            DreamSys_ExecuteLink(dreamSys, newStage, 0xD, 1);
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 DreamSys_LoadNextFlashback(DreamSys *dreamSys, s32 arg1) {
    Flashback *elem;
    s32 idx;

    idx = dreamSys->nextFlashback;
    if (idx < dreamSys->flashbackCount) {
        dreamSys->transition = 0xE;
        elem = &dreamSys->flashbacks[idx];
        if (arg1 == 0) {
            dreamSys->vtbl->unk30(dreamSys, 0xE);
        }
        dreamSys->day = elem->day;
        dreamSys->stage = elem->stage;
        dreamSys->place = elem->place;
        return 1;
    }
    return 0;
}

s32 func_8005A700(DreamSys *dreamSys, s16 *arg1) {
    s32 sp10[4];
    s32 temp;

    if (dreamSys->transition != 0) {
        return 0;
    }
    temp = func_8005BCF8(&dreamSys->place, arg1, dreamSys->stage);
    if (temp < 0) {
        return 0;
    }
    func_8001E6F8(dreamSys, sp10);
    if (func_8005BD3C(&dreamSys->unk888, &dreamSys->unk884, sp10) == 0) {
        return 0;
    }
    if (dreamSys->unkA8 == 0) {
        return 0;
    }
    DreamSys_ExecuteLink(dreamSys, temp, 0xF, 0);
    return 1;
}

s32 func_8005A7A0(DreamSys *dreamSys, s32 arg1) {
    s32 newStage;

    if (dreamSys->transition == 0) {
        newStage = func_8005BE90(&dreamSys->place, dreamSys->stage, arg1, dreamSys->timer);
        if (newStage >= 0) {
            dreamSys->unk880 = func_8005BF48();
            dreamSys->unk884 = 0;
            dreamSys->unk888 = 0;
            DreamSys_ExecuteLink(dreamSys, newStage, 0x10, 0);
            return 1;
        }
    }
    return 0;
}

s32 func_8005A82C(DreamSys *dreamSys, void *arg1) {
    s32 sp10[4];
    s32 bonusSeconds;
    s32 newStage;

    newStage = func_8005BF74(&dreamSys->place, arg1, dreamSys->stage);
    if (newStage >= 0) {
        bonusSeconds = func_8005BFC4();
        if (DreamSys_ExecuteLink(dreamSys, newStage, 0x11, 0) != 0) {
            dreamSys->transition = 0;
            dreamSys->player->vt->unkE8(dreamSys->player, sp10, &dreamSys->place);
            dreamSys->vtbl->unkB8(dreamSys, sp10);
            if (bonusSeconds != 0 && dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->swapTimeLimit(dreamSys, dreamSys->vtbl->getElapsedSeconds(dreamSys) + bonusSeconds);
            }
        }
        return 1;
    }
    return 0;
}

s32 DreamSys_ExecuteLink(DreamSys *dreamSys, s32 newStage, s32 transition, s32 arg3) {
    dreamSys->transition = transition;
    dreamSys->vtbl->unk30(dreamSys, transition);
    if (dreamSys->transition == 0) {
        return 0;
    }
    dreamSys->stage = newStage;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->timer = 0;
    }
    if (arg3 != 0) {
        DreamSysObj58 *obj = dreamSys->unk58;
        obj->vt->unk80(obj, 0x90, 0x6E, 0x6E);
    }
    return 1;
}

s32 func_8005A9CC(DreamSys *dreamSys, DreamPlace *target) {
    s32 sp10[4];

    if (dreamSys->transition == 0) {
        if (dreamSys->linkStep != 0) {
            if (dreamSys->linkStep(dreamSys) != 0) {
                dreamSys->unk908 = 0;
                dreamSys->linkStep = 0;
                dreamSys->unk90C = 0;
                if (dreamSys->unkAC == 4) {
                    dreamSys->vtbl->unk188(dreamSys);
                    return 0;
                }
            }
            return 0;
        }
        if (func_8005BFDC(&dreamSys->place, target, dreamSys->stage) >= 0) {
            func_8001E6F8(dreamSys, sp10);
            if (func_8005C02C((u8 **)&dreamSys->unk888, (u8 **)&dreamSys->unk884, (Unk_8005BE28 *)sp10) != 0 && dreamSys->unkA8 != 0) {
                dreamSys->linkTarget = *target;
                dreamSys->unk908 = 1;
                dreamSys->unk90C = 1;
                dreamSys->linkStepTick = 0;
                dreamSys->linkStep = g_linkSteps[func_8005C118()];
                dreamSys->vtbl->unk44(dreamSys, 1, dreamSys->unk884);
                dreamSys->linkStep(dreamSys);
            }
        }
    }
    return 0;
}

s32 func_8005AB2C(DreamSys *dreamSys) {
    s32 temp_v1;

    if (dreamSys->linkStepTick == 0) {
        func_8005AF64(dreamSys, D_8008ABC0, dreamSys->linkTarget.vec);
    }
    if (dreamSys->unkAC != 4) {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x85) {
            return 1;
        }
        if ((temp_v1 >= 0x2B && temp_v1 < 0x3A) || (temp_v1 >= 0x4B && temp_v1 < 0x5A)) {
            dreamSys->unkA4 = 2;
        }
    } else {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x13) {
            return 1;
        }
        if ((temp_v1 >= 8 && temp_v1 < 0xA) || (temp_v1 >= 0xD && temp_v1 < 0xF)) {
            dreamSys->vtbl->unk44(dreamSys, 0, D_80087EFC);
        }
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 func_8005AC24(DreamSys *dreamSys) {
    s32 flag;

    if (dreamSys->linkStepTick == 0) {
        func_8005AF64(dreamSys, D_8008ABC8, dreamSys->linkTarget.vec);
    }
    if (dreamSys->unkAC != 4) {
        if (dreamSys->linkStepTick >= 0x95) {
            return 1;
        }
        if ((u32)(dreamSys->linkStepTick - 0x16) < 0xF || (u32)(dreamSys->linkStepTick - 0x39) < 0x10 || (u32)(dreamSys->linkStepTick - 0x6E) < 0xF) {
            dreamSys->unkA4 = 1;
        }
        flag = (u32)(dreamSys->linkStepTick - 0x39) < 0x35;
    } else {
        if (dreamSys->linkStepTick >= 0x19) {
            return 1;
        }
        if ((u32)(dreamSys->linkStepTick - 6) < 2 || (u32)(dreamSys->linkStepTick - 0xB) < 2 || (u32)(dreamSys->linkStepTick - 0x14) < 2) {
            dreamSys->vtbl->unk44(dreamSys, 0, D_80087F08);
        }
        flag = (u32)(dreamSys->linkStepTick - 3) < 0xE;
    }
    if (flag) {
        dreamSys->unk88 = 2;
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 func_8005AD68(DreamSys *dreamSys) {
    if (dreamSys->linkStepTick == 0) {
        func_8005AF64(dreamSys, D_8008ABD0, dreamSys->linkTarget.vec);
    }
    if (dreamSys->unkAC != 4) {
        if (dreamSys->linkStepTick > 100) {
            return 1;
        }
        if (dreamSys->linkStepTick >= 43 && dreamSys->linkStepTick < 58) {
            dreamSys->unkA4 = 2;
        }
    } else {
        if (dreamSys->linkStepTick > 14) {
            return 1;
        }
        if (dreamSys->linkStepTick >= 8 && dreamSys->linkStepTick < 10) {
            dreamSys->vtbl->unk44(dreamSys, 0, D_80087EFC);
        }
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 func_8005AE40(DreamSys *dreamSys) {
    s32 temp_v1;
    s32 var;

    if (dreamSys->linkStepTick == 0) {
        func_8005AF64(dreamSys, D_8008ABD8, dreamSys->linkTarget.vec);
    }
    if (dreamSys->unkAC != 4) {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x71) {
            return 1;
        }
        if ((u32)(temp_v1 - 0x1E) < 0xF || (u32)(temp_v1 - 0x52) < 0xF) {
            dreamSys->unkA4 = 1;
        }
        var = (u32)(dreamSys->linkStepTick - 0x1E) < 0x34;
    } else {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x13) {
            return 1;
        }
        if ((u32)(temp_v1 - 6) < 2 || (u32)(temp_v1 - 0xF) < 2) {
            dreamSys->vtbl->unk44(dreamSys, 0, D_80087F08);
        }
        var = (u32)dreamSys->linkStepTick < 9;
    }
    if (var) {
        dreamSys->unk88 = 2;
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

void func_8005AF64(DreamSys *dreamSys, s16 *from, s16 *to) {
    s32 delta[3];

    delta[0] = from[0] - to[0];
    delta[1] = from[1] - to[1];
    delta[2] = from[2] - to[2];
    delta[1] = 0;
    dreamSys->vtbl->unkBC(dreamSys, delta);
}

s32 DreamSys_GetStage(DreamSys *dreamSys) {
    return dreamSys->stage;
}

void func_8005AFDC(DreamSys *dreamSys, Unk_8005AFDC_B *sender, s32 message) {
    if (message == 5) {
        dreamSys->vtbl->logChunkMood(dreamSys, sender->vt->unk10C(sender, 0, 0));
    }
}

void DreamSys_OnEntityEvent(DreamSys *dreamSys, Unk_8005B03C_ObjVtbl **entity, s32 message) {
    s32 oldStage;

    if (dreamSys->transition == 0) {
        switch (message) {
        case 4:
            (*entity)->unk38(entity, dreamSys, message);
            return;
        case 9:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->logEntityMood(dreamSys, (*entity)->unk14C(entity));
                dreamSys->instanceScore = (*entity)->unk150(entity) + dreamSys->instanceScore;
                dreamSys->vtbl->maybeSaveFlashback(dreamSys, 0, 0x10);
                return;
            }
            break;
        case 10:
            oldStage = dreamSys->stage;
            dreamSys->stage = -(*entity)->unk154(entity);
            dreamSys->vtbl->linkDynamic(dreamSys);
            if (dreamSys->stage < 0) {
                dreamSys->stage = oldStage;
                return;
            }
            break;
        case 11:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->cinematic.id.category = -1;
                dreamSys->timer = dreamSys->timeLimit;
                dreamSys->cinematic.id.variant = (*entity)->unk158(entity);
                return;
            }
            break;
        case 12:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->timer = dreamSys->timeLimit;
            }
            break;
        }
    }
}

void DreamSys_GetPreviousPoint(DreamSys *dreamSys, MoodPoint *out, s32 yesterday) {
    s32 sum1 = 0;
    s32 sum0 = 0;
    s32 count;
    s32 i;
    MoodPoint *p;

    if (yesterday != 0) {
        if (dreamSys->year != 0 || dreamSys->day != 0) {
            sum0 = dreamSys->graph[dreamSys->day - 1].x;
            sum1 = dreamSys->graph[dreamSys->day - 1].y;
        }
    } else {
        count = 365;
        if (dreamSys->year == 0) {
            count = dreamSys->day;
        }
        if (count != 0) {
            p = dreamSys->graph;
            for (i = 0; i < count; i++, p++) {
                sum0 += p->x;
                sum1 += p->y;
            }
            sum0 = sum0 / count;
            sum1 = sum1 / count;
        }
    }
    out->x = sum0;
    out->y = sum1;
}

void DreamSys_ResetMoodAccumulators(DreamSys *dreamSys, s32 point) {
    MoodAccum *chunk = &dreamSys->chunkMood;
    MoodAccum *entity = &dreamSys->entityMood;

    dreamSys->vtbl->moodReset(dreamSys, chunk);
    dreamSys->vtbl->moodReset(dreamSys, entity);
    if (point != 0) {
        dreamSys->vtbl->moodLog(dreamSys, chunk, point);
        dreamSys->vtbl->moodLog(dreamSys, entity, point);
    }
}

void DreamSys_LogChunkMood(DreamSys *dreamSys, s8 *place) {
    dreamSys->vtbl->moodLog(dreamSys, &dreamSys->chunkMood, Stage_GetChunkMood(dreamSys->stage, place));
}

void DreamSys_LogEntityMood(DreamSys *dreamSys, s32 point) {
    dreamSys->vtbl->moodLog(dreamSys, &dreamSys->entityMood, point);
}

void DreamSys_ComputeDayPoint(DreamSys *dreamSys, MoodPoint *out) {
    s16 chunkPoint;
    s16 entityPoint;

    dreamSys->vtbl->moodResolve(dreamSys, &dreamSys->chunkMood, &chunkPoint);
    dreamSys->vtbl->moodResolve(dreamSys, &dreamSys->entityMood, &entityPoint);
    if (dreamSys->entityMood.count == 0) {
        entityPoint = chunkPoint;
    }
    out->x = ((s8)chunkPoint + (s8)entityPoint) / 2;
    out->y = (((s8 *)&chunkPoint)[1] + ((s8 *)&entityPoint)[1]) / 2;
}

void DreamSys_GetDreamColor(DreamSys *dreamSys) {
    s16 point;

    dreamSys->vtbl->computeDayPoint(dreamSys, &point);
    Mood_GetColor(&point);
}

s32 Mood_GetColor(s16 *point) {
    s8 buf[2];
    s8 *p;
    s32 i;
    s8 v;


    *(u16 *)buf = *(u16 *)point;
    p = buf;
    i = 0;
    do {
        v = *p;
        if (v >= 4) {
            *p = 2;
        } else if (v < -3) {
            *p = 0;
        } else {
            *p = 1;
        }
        i++;
        p++;
    } while (i < 2);
    return g_moodColors[buf[0]][buf[1]];
}

void Mood_Reset(DreamSys *dreamSys, MoodAccum *accum) {
    accum->last = 0;
    accum->sumY = 0;
    accum->sumX = 0;
    accum->count = 0;
}

void Mood_Log(DreamSys *dreamSys, MoodAccum *accum, MoodPoint *point) {
    s32 sumX;

    sumX = accum->sumX;
    accum->last = *(u16 *)point;
    accum->sumX = point->x + sumX;
    accum->sumY = point->y + accum->sumY;
    accum->count = accum->count + 1;
}

void Mood_Resolve(DreamSys *dreamSys, MoodAccum *accum, MoodPoint *point) {
    if (accum->count != 0) {
        point->x = Mood_CalcAxis(((MoodPoint *)accum)->x, accum->sumX, accum->count);
        point->y = Mood_CalcAxis(((MoodPoint *)accum)->y, accum->sumY, accum->count);
        return;
    }
    *(u16 *)point = *(u16 *)accum;
}

s32 Mood_CalcAxis(s32 last, s32 sum, s32 count) {
    s32 r = sum / count + last / 3;
    if (r > 9) {
        r = -9;
    } else if (r < -9) {
        r = 9;
    }
    return r;
}

void DreamSys_CalcUnlockScore(DreamSys *dreamSys) {
    s32 temp;

    dreamSys->navScore = Nav_CalcScore();
    temp = dreamSys->instanceScore;
    if (temp < 0) {
        dreamSys->instanceScore = 0;
    } else if (temp > 0x02FAF080) {
        dreamSys->instanceScore = 0x02FAF080;
    }
    dreamSys->unlockScore = dreamSys->navScore + dreamSys->instanceScore;
}

void DreamSys_AddFlashback(DreamSys *dreamSys, s32 stage, DreamPlace *place, DreamRotation *rotation, s32 arg4, s32 length, s32 day) {
    Flashback *ent;
    s32 n;

    ent = dreamSys->flashbacks;
    n = dreamSys->flashbackCount;
    if (n < 10) {
        dreamSys->flashbackCount = n + 1;
        ent += n;
    } else {
        ent += dreamSys->timer % 9;
    }
    ent->stage = stage;
    ent->place = *place;
    ent->rotation.rot = *rotation;
    ent->unk1C = arg4;
    ent->length = length;
    ent->day = day;
}

void DreamSys_MaybeSaveFlashback(DreamSys *dreamSys, s32 arg1, s32 length) {
    s32 rotation[4];
    s32 place;
    DreamPlayer *player;

    if (dreamSys->player != NULL) {
        if (rand() % 3 == 0) {
            player = dreamSys->player;
            place = player->vt->unk10C(player, 0, 0);
            func_8001E6F8(dreamSys, rotation);
            dreamSys->vtbl->addFlashback(dreamSys, dreamSys->stage, place, rotation, arg1, length, dreamSys->day);
        }
    }
}

void DreamSys_ClearFlashbacks(DreamSys *dreamSys) {
    dreamSys->flashbackCount = 0;
}

void func_8005B904(DreamSys *dreamSys) {
    DreamBody *src = dreamSys->unk14.body;

    dreamSys->bodyCopy = *src;
    dreamSys->bodyExtraCopy = *src->unk44;
}

void func_8005B990(DreamSys *dreamSys) {
    DreamBody *dst = dreamSys->unk14.body;

    *dst = dreamSys->bodyCopy;
    *dst->unk44 = dreamSys->bodyExtraCopy;
    dst->unk0 = 0;
}

s32 func_8005BA20(DreamSys *dreamSys, s32 value) {
    s32 temp;

    if (value < 0) {
        return dreamSys->unk924;
    }
    temp = dreamSys->unk924;
    dreamSys->unk924 = value;
    return temp;
}

DreamSysVtbl *DreamSys_GetVtable(void) {
    return (DreamSysVtbl *)g_dreamSysVtbl;
}

void Nav_InitFlags(u8 *flags, s32 *linkCount) {
    s32 i;
    for (i = 29; i >= 0; i--) {
        flags[i] = 0;
    }
    g_navFlags = flags;
    *linkCount = 0;
    g_dynamicLinkCount = linkCount;
}

s32 Nav_CalcScore(void) {
    s32 i;
    s32 sum = 0;

    for (i = 0; i < 30; i++) {
        if (((s8 *)g_navFlags)[i] != 0) {
            sum += 1000000;
        }
    }
    if (sum > 29999999) {
        sum = 50000000;
    }
    sum -= *g_dynamicLinkCount * 11024;
    if (sum < 0) {
        sum = 0;
    }
    return sum;
}

s16 Stage_GetTimeLimit(s32 stage) {
    return g_stageTimeLimits[stage];
}

s32 Spawn_PickRandom(void *place, s32 stage, s32 arg2) {
    s32 newStage;
    s32 n;
    Unk_8005C150 *out;
    Unk_8005C150_Y *rec;

    n = 6;
    if (stage >= 0) {
        newStage = rand() % n;
        if (newStage == stage) {
            newStage += 1;
            if (newStage >= 6) {
                newStage = 0;
            }
        }
    } else {
        newStage = -stage;
    }
    rec = (Unk_8005C150_Y *)((s32)D_800885B8[newStage] + (rand() % D_800885F0[newStage]) * 6);
    out = place;
    out->a = rec->c;
    out->b = D_80087F30[rec->idx];
    *g_dynamicLinkCount += 1;
    return newStage;
}

s32 func_8005BCB4(void *arg0, void *arg1, s32 arg2) {
    return func_8005C150(arg0, arg1, arg2, D_80088748, D_80088710, D_80088664, 1);
}

s32 func_8005BCF8(void *arg0, s16 *arg1, s32 arg2) {
    return func_8005C150(arg0, arg1, arg2, D_800889F0, D_80088980, D_80088820, 1);
}

s32 func_8005BD3C(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2) {
    u8 temp;

    temp = D_800889B8[D_8008ACBC][D_8008ACC0];
    if (func_8005BE28(arg2, temp) != 0) {
        if (arg1 != NULL) {
            *arg1 = D_80088758 + temp * 12;
        }
        if (arg0 != NULL) {
            *arg0 = D_80088758 + D_80088858[D_8008ACC4][D_8008ACC8] * 12;
        }
        return 1;
    }
    return 0;
}

s32 func_8005BE28(Unk_8005BE28 *arg0, u8 arg1) {
    s32 diff = arg0->u4 - D_8008875C[arg1 * 6];
    s16 temp = diff;
    s16 var_a1;

    var_a1 = diff;
    if (temp > 0xB4) {
        var_a1 -= 0x168;
    } else if (temp < -0xB4) {
        var_a1 += 0x168;
    }
    return (u16)(var_a1 + 0x2C) < 0x59U;
}

s32 func_8005BE90(void *arg0, s32 arg1, Unk_8005BE90 *arg2, s32 arg3) {
    s32 ret;

    if (arg1 != 3 && arg1 != 1 && arg1 != 5 && arg1 != 9 && arg1 != 12) {
        return -1;
    }
    if (arg1 == 5) {
        if (arg2->unk6 >= -0xFFF && arg2->unk0 != D_8008ABE8) {
            return -1;
        }
    } else if (arg1 == 9) {
        if (arg2->unk6 < 0x800) {
            return -1;
        }
    }
    if (arg3 & 1) {
        arg1 = -12;
    }
    ret = Spawn_PickRandom(arg0, arg1, arg3);
    D_8008ACC4 = ret;
    return ret;
}

s32 *func_8005BF48(void) {
    s32 *r = NULL;
    if (D_8008ACC4 != 12) {
        r = D_8008ABF0;
    }
    return r;
}

void func_8005BF68(s32 arg0) {
    D_8008ABE4 = arg0;
}

s32 func_8005BF74(void *arg0, void *arg1, s32 arg2) {
    if (D_8008ABE4 != 0) {
        return func_8005C150(arg0, arg1, arg2, &D_80088B5C, &D_80088B24, &D_80088A80, 0);
    }
    return -1;
}

s32 func_8005BFC4(void) {
    return D_8008ACBC == 0 ? 10 : 0;
}

s32 func_8005BFDC(void *arg0, void *arg1, s32 arg2) {
    if (arg2 == 0) {
        return func_8005C150(arg0, arg1, 0, D_80088CBC, D_80088C4C, (s32 *)D_80088BA4, 0);
    }
    return -1;
}

s32 func_8005C02C(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2) {
    u8 temp_s0;

    temp_s0 = D_80088C84[D_8008ACBC][D_8008ACC0];
    if (func_8005BE28(arg2, temp_s0) != 0) {
        if (arg1 != 0) {
            *arg1 = D_80088758 + temp_s0 * 12;
        }
        if (arg0 != 0) {
            *arg0 = D_80088758 + D_80088BDC[D_8008ACC4][D_8008ACC8] * 12;
        }
        return 1;
    }
    return 0;
}

s32 func_8005C118(void) {
    return D_80088BA4[D_8008ACC4][D_8008ACC8].u5;
}

s32 func_8005C150(void *arg0, void *arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 arg6) {
    Unk_8005C150_T *t0;
    Unk_8005C150_Y *y;
    Unk_8005C150 *o;
    s16 *a1;
    s32 n;
    s32 i;
    s32 c;
    s32 d;

    o = arg0;
    a1 = arg1;
    n = arg3[arg2];
    if (n != 0) {
        t0 = (Unk_8005C150_T *)arg4[arg2];
        for (i = 0; i < n; i++, t0++) {
            if (a1[0] == t0->a && (a1[1] == t0->b || t0->b < 0)) {
                D_8008ACBC = arg2;
                D_8008ACC0 = i;
                c = t0->c;
                D_8008ACC4 = c;
                d = t0->d;
                y = (Unk_8005C150_Y *)arg5[c] + d;
                D_8008ACC8 = d;
                o->a = y->c;
                o->b = D_80087F30[y->idx];
                if (arg6 != 0) {
                    g_navFlags[y->flag] = 1;
                }
                return D_8008ACC4;
            }
        }
    }
    return -1;
}

s32 Spawn_PickFromMood(void *place, s32 *secondsOut, void *point, s32 day) {
    s16 key[4];
    s32 idx;
    s32 cnt;
    s32 i;
    Unk_8005C150_Y *rec;
    Unk_8005C150 *out;

    idx = Stage_FindChunkByMood(key, point);
    if (idx >= 0) {
        *secondsOut = g_stageTimeLimits[idx];
        cnt = D_800885F0[idx];
        rec = D_800885B8[idx];
        for (i = 0; i < cnt; i++, rec++) {
            if (key[0] == *(s16 *)rec) {
                goto found;
            }
        }
        rec = D_800885B8[idx] + key[0] % cnt;
found:
        out = place;
        out->a = rec->c;
        out->b = D_80087F30[rec->idx];
        return idx;
    }
    idx = Spawn_PickRandom(place, idx, day);
    *secondsOut = g_stageTimeLimits[idx];
    return idx;
}

s32 Day_FindSpecial(void *cinematic, s32 dayNumber) {
    Unk_8005C438 *o = cinematic;
    s32 i;

    for (i = 0; i < sizeof(g_specialDays) / sizeof(g_specialDays[0]); i++) {
        if (dayNumber == g_specialDays[i]) {
            o->unk2 = rand() % 6;
            o->unk0 = i % 12;
            return (s32) &D_8008ABF4;
        }
    }
    return 0;
}

#include "common.h"

void func_8003221C(s32 arg0);
extern void ResetCallback(void);
extern void SpuInit(void);
extern void SpuInitHot(void);
extern void SpuVmInit(s32);
extern s32 GetVideoMode(void);
extern u16 D_8006DC5C[];
extern u16 D_8006DC6C[];
extern s32 D_8006DC8C;
extern s32 D_8006DC90;
extern s32 D_8006DC94;
extern s32 D_8006DC98;
extern void (*D_8006DC9C)(void);
extern s32 D_8008E934;
extern s32 D_8008EA00;
extern s32 D_8009024C;
extern s32 D_80090368[][16];

void func_8003221C(s32 arg0) {
    s32 i;
    s32 j;
    u16 *p;
    u16 *src;
    u16 *base;
    u16 tmp;

    ResetCallback();
    if (arg0 == 0) {
        SpuInit();
    } else {
        SpuInitHot();
    }
    p = (u16 *)0x1F801C00;
    i = 0;
    base = D_8006DC5C;
    for (; i < 0x18; i++) {
        j = 0;
        src = base;
        for (; j < 8; j++) {
            tmp = *src;
            src++;
            *p = tmp;
            p++;
        }
    }
    p = (u16 *)0x1F801D80;
    i = 0;
    src = D_8006DC6C;
    for (; i < 0x10; i++) {
        tmp = *src;
        src++;
        *p = tmp;
        p++;
    }
    SpuVmInit(0x18);
    for (j = 0; j < 0x20; j++) {
        for (i = 0xF; i >= 0; i--) {
            D_80090368[j][i] = 0;
        }
    }
    D_8009024C = 0x3C;
    D_8008EA00 = 0;
    D_8006DC8C = 0;
    D_8006DC90 = -1;
    D_8006DC94 = 0;
    D_8006DC9C = 0;
    D_8006DC98 = GetVideoMode();
    D_8008E934 = 0;
}

void func_80032368(void) {
    func_8003221C(0);
}

void func_80032388(void) {
    func_8003221C(1);
}

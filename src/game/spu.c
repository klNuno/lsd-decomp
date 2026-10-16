#include "common.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

void Spu_Reset(s32 hot);
extern void ResetCallback(void);
extern void SpuInit(void);
extern void SpuInitHot(void);
extern void SpuVmInit(s32);
extern s32 GetVideoMode(void);
extern u16 g_spuVoiceInit[];
extern u16 g_spuControlInit[];
extern s32 g_seqVsyncCount;
extern s32 g_seqIrq;
extern s32 g_seqHalfRate;
extern s32 g_videoMode;
extern void (*g_seqPrevHandler)(void);
extern s32 D_8008E934;
extern s32 D_8008EA00;
extern s32 D_8009024C;
extern s32 D_80090368[][16];

/*
 * Resets the SPU: loads the 24 voice registers (0x1F801C00) and the 16 control registers
 * (0x1F801D80) from their tables, clears the voice table and the sound state, and reads the video mode.
 * hot 0 runs the cold SpuInit, hot 1 runs SpuInitHot.
 */
void Spu_Reset(s32 hot) {
    s32 i;
    s32 j;
    u16 *spuReg;
    u16 *src;
    u16 *voiceTable;
    u16 value;

    ResetCallback();
    if (hot == 0) {
        SpuInit();
    } else {
        SpuInitHot();
    }
    spuReg = (u16 *)0x1F801C00;
    i = 0;
    voiceTable = g_spuVoiceInit;
    for (; i < 0x18; i++) {
        j = 0;
        src = voiceTable;
        for (; j < 8; j++) {
            value = *src;
            src++;
            *spuReg = value;
            spuReg++;
        }
    }
    spuReg = (u16 *)0x1F801D80;
    i = 0;
    src = g_spuControlInit;
    for (; i < 0x10; i++) {
        value = *src;
        src++;
        *spuReg = value;
        spuReg++;
    }
    SpuVmInit(0x18);
    for (j = 0; j < 0x20; j++) {
        for (i = 0xF; i >= 0; i--) {
            D_80090368[j][i] = 0;
        }
    }
    D_8009024C = 0x3C;
    D_8008EA00 = 0;
    g_seqVsyncCount = 0;
    g_seqIrq = -1;
    g_seqHalfRate = 0;
    g_seqPrevHandler = 0;
    g_videoMode = GetVideoMode();
    D_8008E934 = 0;
}

/* Cold SPU reset. */
void Spu_ResetCold(void) {
    Spu_Reset(0);
}

/* Hot SPU reset. */
void Spu_ResetHot(void) {
    Spu_Reset(1);
}

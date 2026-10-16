#include "common.h"
#include "game/seq_timer.h"
#include "psyq/libapi.h"
#include "psyq/libetc.h"
#include "psyq/libspu.h"
#include "psyq/libsnd.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

extern s32 g_seqToggle;
static void Seq_ArmTimer(s32 immediate);
extern s32 g_seqExternal;
extern s32 g_seqRate;
static void Seq_OnTick(void);
static void Seq_OnTickHalf(void);

/*
 * Sets the rate in g_seqRate from the low 12 bits of rate; bit 0x1000 sets g_seqExternal. Rates 0, 1, 4
 * and 5 depend on the video mode in g_videoMode (1 is PAL, 50 Hz; 0 is NTSC, 60 Hz). g_seqTicksPerSecond gets
 * the period for the rate.
 */
void Seq_SetRate(s32 rate) {
    if (rate & 0x1000) {
        g_seqExternal = 1;
        g_seqRate = rate & 0xFFF;
    } else {
        g_seqExternal = 0;
        g_seqRate = rate;
    }
    if (g_seqRate < 6) {
        switch (g_seqRate) {
        case 4:
            g_seqTicksPerSecond = 0x32;
            if (g_videoMode == 1) {
                g_seqRate = 5;
            } else {
                g_seqRate = 0x32;
            }
            return;
        case 1:
            g_seqTicksPerSecond = 0x3C;
            if (g_videoMode == 0) {
                g_seqRate = 5;
            } else {
                g_seqRate = 0x3C;
            }
            return;
        case 3:
            g_seqTicksPerSecond = 0x78;
            return;
        case 2:
            g_seqTicksPerSecond = 0xF0;
            return;
        case 5:
            switch (g_videoMode) {
            case 1:
                g_seqTicksPerSecond = 0x32;
                return;
            default:
            case 0:
                g_seqTicksPerSecond = 0x3C;
                return;
            }
            break;
        case 0:
            if (g_videoMode != 0) {
                if (g_videoMode == 1) {
                    g_seqTicksPerSecond = 0x32;
                    return;
                }
                g_seqTicksPerSecond = 0x3C;
                return;
            }
            g_seqTicksPerSecond = 0x3C;
            return;
        default:
            g_seqTicksPerSecond = 0x3C;
            return;
        }
    } else {
        g_seqTicksPerSecond = g_seqRate;
    }
}

/*
 * Arms the sequencer timer. With rate 5, immediate not 0 uses root counter 3 (vsync) and immediate 0
 * defers the tick to the next vsync (g_seqVsyncCount). Rate 0 does nothing; the other rates return when
 * g_seqExternal is set. Rates below 70 Hz count g_seqHalfRate.
 */
static void Seq_ArmTimer(s32 immediate) {
    s32 counter;
    u16 target;
    s32 i;

    for (i = 999; i >= 0; i--);
    switch (g_seqRate) {
    case 5:
        if (immediate == 0) {
            g_seqVsyncCount++;
        } else {
            counter = 0xF2000003;
            g_seqIrq = 0;
            target = 1;
        }
        break;
    case 3:
        counter = 0xF2000002;
        target = 0x89D0;
        g_seqIrq = 6;
        break;
    case 2:
        counter = 0xF2000002;
        target = 0x44E8;
        g_seqIrq = 6;
        break;
    case 0:
        return;
    default:
        if (g_seqExternal != 0) {
            return;
        }
        counter = 0xF2000002;
        g_seqIrq = 6;
        if (g_seqRate < 70) {
            target = 0x204CC0 / g_seqRate;
            g_seqHalfRate++;
        } else {
            target = 0x409980 / g_seqRate;
        }
        break;
    }
    if (g_seqVsyncCount != 0) {
        VSyncCallback(SsSeqCalledTbyT);
        return;
    }
    EnterCriticalSection();
    ResetRCnt(counter);
    SetRCnt(counter, target, 0x1000);
    for (i = 1999; i >= 0; i--);
    for (i = 1999; i >= 0; i--);
    StartRCnt(counter);
    if (g_seqIrq == 0) {
        g_seqPrevHandler = InterruptCallback(0, NULL);
        InterruptCallback(g_seqIrq, Seq_OnTick);
    } else if (g_seqHalfRate == 0) {
        InterruptCallback(g_seqIrq, SsSeqCalledTbyT);
    } else {
        InterruptCallback(g_seqIrq, Seq_OnTickHalf);
    }
    ExitCriticalSection();
}

/* Starts the timer at once (immediate 1). */
void Seq_StartTimer(void) {
    Seq_ArmTimer(1);
}

/* Starts the timer with the vsync-deferred tick (immediate 0). */
static void Seq_StartTimerVsync(void) {
    Seq_ArmTimer(0);
}

/* Stops the timer, unless g_seqExternal is set: cancels the pending vsync tick or the interrupt, then clears g_seqIrq. */
void Seq_StopTimer(void) {
    if (g_seqExternal == 0) {
        g_seqHalfRate = 0;
        EnterCriticalSection();
        if (g_seqVsyncCount != 0) {
            VSyncCallback(0);
            g_seqVsyncCount = 0;
        } else if (g_seqIrq != -1) {
            if (g_seqIrq == 0) {
                InterruptCallback(0, g_seqPrevHandler);
            } else {
                InterruptCallback(g_seqIrq, 0);
            }
            g_seqIrq = -1;
        }
        ExitCriticalSection();
    }
}

/* Quits the SPU. */
void Spu_Quit(void) {
    SpuQuit();
}

/* Timer interrupt: calls the saved previous handler, then the sequencer tick. */
static void Seq_OnTick(void) {
    if (g_seqPrevHandler != NULL) {
        g_seqPrevHandler();
    }
    SsSeqCalledTbyT();
}

/* Half-rate tick: g_seqToggle toggles, and the sequencer runs on every second interrupt. */
static void Seq_OnTickHalf(void) {
    if (g_seqToggle == 0) {
        g_seqToggle = 1;
    } else {
        g_seqToggle = 0;
        SsSeqCalledTbyT();
    }
}

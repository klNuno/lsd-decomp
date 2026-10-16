#ifndef GAME_SEQ_TIMER_H
#define GAME_SEQ_TIMER_H

#include "common.h"

/* Functions of src/game/seq_timer.c that other files call or reference (docs/naming.md, Prototypes) */
void Seq_SetRate(s32 rate);
void Seq_StartTimer(void);
void Seq_StopTimer(void);
void Spu_Quit(void);

/* Its data other files read */
extern void (*g_seqPrevHandler)(void);
extern s32 g_seqVsyncCount;
extern s32 g_seqIrq;
extern s32 g_seqHalfRate;
extern s32 g_videoMode;
extern s32 g_seqTicksPerSecond;

#endif

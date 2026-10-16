#ifndef PSYQ_LIBETC_H
#define PSYQ_LIBETC_H

#include "types.h"

/* LIBETC functions the game calls: vertical sync, interrupt callbacks, video mode, pads. */

s32 VSync(s32 mode);
void VSyncCallback(void (*func)(void));
void *InterruptCallback(s32 irq, void (*func)(void));
void ResetCallback(void);
s32 GetVideoMode(void);

void PadInit(s32 mode);
s32 PadRead(u16 id);
void PadStop(void);

#endif

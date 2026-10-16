#ifndef PSYQ_LIBGPU_H
#define PSYQ_LIBGPU_H

#include "types.h"

/*
 * LIBGPU functions the game calls. The RECT argument is void *: display.c and tix.c each read it
 * through their own struct (Rect, ClutRect).
 */

void ResetGraph(s32 mode);
s32 DrawSync(s32 mode);
s32 LoadImage(void *rect, u32 *p);
void StoreImage(void *rect, u32 *p);
void MoveImage(void *rect, s32 x, s32 y);
void ClearImage(void *rect, u8 r, u8 g, u8 b);
u16 GetTPage(s32 tp, s32 abr, s16 x, s16 y);

#endif

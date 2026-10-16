#ifndef GAME_TIM_H
#define GAME_TIM_H

#include "common.h"
#include "game/loader.h"
#include "game/scene.h"

/* Functions of src/game/tim.c that other files call or reference (docs/naming.md, Prototypes) */
Tim *Tim_New(char *path);
TimVtbl *Tim_GetVtbl(void);
void Display_RotateRect(ScreenRect *rect, s32 count, ScreenRect *spare);

#endif

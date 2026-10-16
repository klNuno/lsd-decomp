#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/* Functions of src/game/screen.c that other files call or reference (docs/naming.md, Prototypes) */
void Screen_OnNotify(Screen *screen, Object *sender, s32 message);
void Screen_Finish(Screen *screen);
void Screen_OnDisplay(Screen *screen, Display *display, s32 message);
void Screen_StartLoop(Screen *screen);
void Screen_StopLoop(Screen *screen);

#endif

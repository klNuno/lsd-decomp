#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "common.h"
#include "game/scene.h"

/* Functions of src/game/display.c that other files call or reference (docs/naming.md, Prototypes) */
Display *Display_New(void);
Display *Display_GetCurrent(void);
void Display_SetCurrent(Display *display);

#endif

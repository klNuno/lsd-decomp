#ifndef GAME_APP_H
#define GAME_APP_H

#include "common.h"
#include "game/scene.h"

/* Functions of src/game/app.c that other files call or reference (docs/naming.md, Prototypes) */
void App_Destroy(void);
void func_8003B108(void);
void App_Run(App *app);
AppVtbl *App_GetVtbl(void);

#endif

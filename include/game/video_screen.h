#ifndef GAME_VIDEO_SCREEN_H
#define GAME_VIDEO_SCREEN_H

#include "common.h"
#include "game/scene.h"
#include "game/sound.h"

/* Functions of src/game/video_screen.c that other files call or reference (docs/naming.md, Prototypes) */
VideoScreen *VideoScreen_New(MenuDef *menu, char *soundPath, SoundBank *sound, ScreenRect *area);

#endif

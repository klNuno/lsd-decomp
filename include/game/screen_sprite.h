#ifndef GAME_SCREEN_SPRITE_H
#define GAME_SCREEN_SPRITE_H

#include "common.h"
#include "game/display.h"

/* Functions of src/game/screen_sprite.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/screen_sprite.c */
struct ScreenSprite;
struct Tim;
struct ScreenSpriteVtbl;
struct SpriteRect;
struct ScreenSprite *ScreenSprite_Create(struct Tim *image, struct SpriteRect *rect, s32 unused);
void ScreenSprite_Attach(struct ScreenSprite *sprite, s32 parent, ScreenPoint *position);
void ScreenSprite_SetPosition(struct ScreenSprite *sprite, ScreenPoint *position);
void ScreenSprite_SetPivot(struct ScreenSprite *sprite, s32 pivot);
struct ScreenSpriteVtbl *ScreenSprite_GetVtbl(void);

#endif

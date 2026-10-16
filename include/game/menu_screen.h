#ifndef GAME_MENU_SCREEN_H
#define GAME_MENU_SCREEN_H

#include "common.h"
#include "game/gs.h"
#include "game/loader.h"
#include "game/scene.h"
#include "game/sound.h"

/* Functions of src/game/menu_screen.c that other files call or reference (docs/naming.md, Prototypes) */
MenuScreen *MenuScreen_New(MenuDef *menu, char *soundPath, SoundBank *sound);
void MenuScreen_Destroy(MenuScreen *screen);
s32 MenuScreen_Run(MenuScreen *screen, ScreenEnv *env, s32 noLoop);
void MenuScreen_Begin(MenuScreen *screen);
void MenuScreen_End(MenuScreen *screen);
void MenuScreen_OnPad(MenuScreen *screen, Pad *pad, s32 code);
void MenuScreen_OnClock(MenuScreen *screen, Clock *clock, s32 message);
void MenuScreen_SetState(MenuScreen *screen, s32 state);
void MenuScreen_SetTimeout(MenuScreen *screen, s32 seconds);
void MenuScreen_PlaySound(MenuScreen *screen, s32 tone);
void MenuScreen_OnStart(MenuScreen *screen);
void MenuScreen_OnCircle(MenuScreen *screen);
void MenuScreen_OnCross(MenuScreen *screen);
void MenuScreen_OnUp(MenuScreen *screen);
void MenuScreen_OnDown(MenuScreen *screen);
void MenuScreen_Confirm(MenuScreen *screen);
void MenuScreen_Close(MenuScreen *screen);
void MenuScreen_SetOnClose();
void MenuScreen_SetFadeIn(MenuScreen *screen, s32 enabled);
void MenuScreen_SetFadeOut(MenuScreen *screen, s32 enabled);
void MenuScreen_SetColors(MenuScreen *screen, Color3 *startColor, Color3 *endColor, Color3 *color96);
void MenuScreen_SetFadeSpeed(MenuScreen *screen, s32 fadeSpeed);
s32 MenuScreen_FadeIn(MenuScreen *screen);
s32 MenuScreen_FadeInStep(MenuScreen *screen);
s32 MenuScreen_FadeOut(MenuScreen *screen);
s32 MenuScreen_FadeOutStep(MenuScreen *screen);
void MenuScreen_SetPicture(MenuScreen *screen, char *path, Tim *image);
void MenuScreen_SetMenu(MenuScreen *screen, MenuDef *menu);
void MenuScreen_FreeMenu(MenuScreen *screen);
void MenuScreen_ShowItems(MenuScreen *screen, SceneNode *root);
void MenuScreen_SetItemsColor(MenuScreen *screen, Color3 *color);
void MenuScreen_NextItem(MenuScreen *screen);
void MenuScreen_PrevItem(MenuScreen *screen);
void MenuScreen_SelectItem(MenuScreen *screen, s32 index, s32 playSound);
s32 MenuScreen_GetSelectedItem(MenuScreen *screen);
void MenuScreen_MakeOptions(MenuScreen *screen, OptionListDef *list, Tim *font);
void MenuScreen_FreeOptions(MenuScreen *screen);
void MenuScreen_ShowOptions(MenuScreen *screen, SceneNode *root, s32 open);
void MenuScreen_SetOptionsColor(MenuScreen *screen, Color3 *color);
void MenuScreen_OpenOptions(MenuScreen *screen);
void MenuScreen_AcceptOption(MenuScreen *screen);
void MenuScreen_CancelOptions(MenuScreen *screen);
void MenuScreen_NextOption(MenuScreen *screen);
void MenuScreen_PrevOption(MenuScreen *screen);
void MenuScreen_SelectOption(MenuScreen *screen, s32 index, s32 playSound);
s32 MenuScreen_GetSelectedOption(MenuScreen *screen);
ScreenVtbl *MenuScreen_GetVtbl(void);
ScreenRect *MenuScreen_GetPictureRect(void);

#endif

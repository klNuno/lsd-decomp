#ifndef GAME_MENU_SCREEN_H
#define GAME_MENU_SCREEN_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"
#include "game/pad.h"
#include "game/sound_bank.h"
#include "game/tim.h"
#include "game/screen.h"
#include "game/clock.h"

/*
 * MenuScreen (src/game/menu_screen.c): vtable g_menuScreenVtbl (tag 0x130), 0xA4 bytes, made by
 * MenuScreen_New. A Screen (screen.h) plus a sound bank, a picture, fade in and fade out, a timeout
 * and a menu of items with option lists. The logos and the special-day pictures use it as is
 * (src/game/scene.c); the main menu (src/game/menu.c) derives from it.
 */

/* MenuScreen +0x3C: where the pad goes. */
#define MENU_FOCUS_NONE 0
#define MENU_FOCUS_ITEMS 1
#define MENU_FOCUS_OPTIONS 2

/* The option list of one menu item. */
typedef struct OptionListDef {
    s32 unk0;
    s32 selected;           /* 0x04 the chosen option, written back on accept */
    Color3 color;           /* 0x08 the highlighted option */
    u8 pad_0B[0x10 - 0x0B];
    ScreenPoint pos;        /* 0x10 position of the chosen option; the list opens around it, 10 per line */
    u8 **texts;             /* 0x18 NULL-terminated */
} OptionListDef;

/* A menu: static data handed to MenuScreen_SetMenu (slot 0xD8) or to init. */
typedef struct MenuDef {
    char *fontPath;         /* 0x00 a TIM loaded for the menu's texts, or 0 to use font */
    struct Tim *font;       /* 0x04 the loaded image is stored back here */
    s32 initialItem;        /* 0x08 selected when the screen becomes active */
    s32 closeItem;          /* 0x0C confirming this item closes the screen */
    Color3 color;           /* 0x10 items and options */
    Color3 selectColor;     /* 0x13 the selected item */
    u8 pad_16[0x18 - 0x16];
    s32 *hidden;            /* 0x18 per item: hidden and skipped by the cursor */
    u8 **texts;             /* 0x1C NULL-terminated */
    s32 *positions;         /* 0x20 per item: x, y */
    OptionListDef **options; /* 0x24 per item, NULL when the item has none */
} MenuDef;

typedef struct MenuScreen {
    ScreenVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    ScreenEnv *env;
    Clock *clock;
    SceneNode *root;
    struct View *view;
    s32 ticks;
    s32 state;
    s32 noLoop;
    /* MenuScreen */
    s32 viewOtBits;         /* 0x28 3, given to the view on begin */
    s32 viewPacketCount;    /* 0x2C 300 */
    s32 viewPacketSize;     /* 0x30 0x40 */
    s32 clearOnEnd;         /* 0x34 end clears the screen with endColor */
    s32 result;             /* 0x38 what run returns: 1 on timeout, 2 when a video is skipped */
    s32 focus;              /* 0x3C MENU_FOCUS_* */
    s32 timeout;            /* 0x40 in clock ticks, negative: none */
    char *soundPath;        /* 0x44 init loads the bank when set, and deletes it */
    struct SoundBank *sound; /* 0x48 */
    MenuDef *menu;          /* 0x4C */
    s32 itemCount;          /* 0x50 */
    Widget **items;         /* 0x54 one text per item */
    s32 selected;           /* 0x58 */
    s32 *optionCounts;      /* 0x5C per item */
    s32 *optionSelected;    /* 0x60 per item */
    Widget ***options;      /* 0x64 per item, one text per option */
    Widget *optionBox;      /* 0x68 drawn behind an open option list */
    u8 pad_6C[0x70 - 0x6C];
    char *picturePath;      /* 0x70 setPicture loads and owns the picture when set */
    struct Tim *picture;    /* 0x74 */
    struct ScreenBg *bg;    /* 0x78 Bg over bgMap: draws VRAM x 640 (the picture area) full screen, takes the fade color */
    struct ScreenBg *bgMap; /* 0x7C BgMap over bgCells */
    struct ScreenBg *bgCells; /* 0x80 BgCells: 300 cells of 16x16 on VRAM x 640 to 960 (include/game/bg_cells.h) */
    s32 fadeSpeed;          /* 0x84 brightness added per tick, 9 */
    s32 (*fadeInStep)();    /* 0x88 NULL: no fade in */
    s32 (*fadeOutStep)();   /* 0x8C NULL: no fade out */
    Color3 startColor;      /* 0x90 fade in starts from it; begin clears the screen with it */
    Color3 endColor;        /* 0x93 end clears the screen with it */
    Color3 unk96;           /* 0x96 (128, 128, 128) by default, not read in this unit */
    u8 pad_99[0x9C - 0x99];
    void (*onClose)();      /* 0x9C called with onCloseArg by close */
    s32 onCloseArg;         /* 0xA0 */
} MenuScreen;

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

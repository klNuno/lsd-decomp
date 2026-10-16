#ifndef GAME_VIDEO_SCREEN_H
#define GAME_VIDEO_SCREEN_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"
#include "game/sound_bank.h"
#include "game/menu_screen.h"
#include "game/screen.h"
#include "game/clock.h"

/*
 * VideoScreen (src/game/video_screen.c): vtable g_videoScreenVtbl (tag 0x1130), 0xDC bytes, made by
 * VideoScreen_New: a MenuScreen (menu_screen.h) that plays one STR video (docs/discoveries.md,
 * special days).
 */
typedef struct VideoScreen {
    ScreenVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    ScreenEnv *env;
    Clock *clock;
    SceneNode *root;
    struct View *view;
    s32 ticks;
    s32 state;
    s32 unk24;
    s32 viewOtBits;
    s32 viewPacketCount;
    s32 viewPacketSize;
    s32 clearOnEnd;
    s32 result;
    s32 focus;
    s32 timeout;            /* 0x40 set in seconds x 15, the video rate */
    char *soundPath;
    struct SoundBank *sound;
    MenuDef *menu;
    s32 itemCount;
    Widget **items;
    s32 selected;
    s32 *optionCounts;
    s32 *optionSelected;
    Widget ***options;
    Widget *optionBox;
    u8 pad_6C[0x70 - 0x6C];
    char *picturePath;
    struct Tim *picture;  
    struct ScreenBg *bg;
    struct ScreenBg *bgMap;
    struct ScreenBg *bgCells;
    s32 fadeSpeed;
    s32 (*fadeInStep)();
    s32 (*fadeOutStep)();
    Color3 startColor;
    Color3 endColor;
    Color3 unk96;
    u8 pad_99[0x9C - 0x99];
    void (*onClose)();
    s32 onCloseArg;
    /* VideoScreen */
    s32 finished;           /* 0xA4 the movie reported the end */
    ScreenRect area;        /* 0xA8 VRAM rect the video goes to, default MenuScreen_GetPictureRect: (640, 0) 320 x 240 */
    struct ScreenMovie *movie; /* 0xB4 the Movie of Movie_Create (include/game/movie.h) */
    char *path;             /* 0xB8 the .STR file */
    s32 frameCount;         /* 0xBC from g_videoTable, -1 when the length comes from setTimeout; Movie +0x5C */
    s32 unkC0;              /* 0xC0 handed to Movie slot 0x6C (Movie +0x68) */
    s32 movieRepeat;        /* 0xC4 Movie +0x54, 0 */
    s32 movieLoops;         /* 0xC8 Movie +0x58, -1 */
    s32 skippable;          /* 0xCC CIRCLE ends the video with result 2; 1 by default */
    s32 unkD0;              /* 0xD0 0, not read in this unit */
    s32 unkD4;              /* 0xD4 1: close stops the movie at once instead of fading out */
    s32 closing;            /* 0xD8 */
} VideoScreen;

/* Functions of src/game/video_screen.c that other files call or reference (docs/naming.md, Prototypes) */
VideoScreen *VideoScreen_New(MenuDef *menu, char *soundPath, SoundBank *sound, ScreenRect *area);

#endif

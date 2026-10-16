#include "common.h"
#include "game/heap.h"
#include "game/scene.h"
#include "game/loader.h"
#include "game/sound.h"

/*
 * Screens and the view (include/game/scene.h): VideoScreen (VideoScreen_New to VideoScreen_GetVtbl),
 * MenuScreen (MenuScreen_New to MenuScreen_GetPictureRect), Screen (Screen_Init to Screen_GetVtbl) and
 * View (View_New to the end).
 */

/* Pad codes: 0x12 + button index when a button is pressed (docs/discoveries.md, pad codes). */
#define PAD_PRESSED_UP 0x12
#define PAD_PRESSED_DOWN 0x13
#define PAD_PRESSED_CROSS 0x17
#define PAD_PRESSED_CIRCLE 0x19
#define PAD_PRESSED_START 0x21

/* Bg, BgMap and BgCells (src/game/80043008.c, include/game/loader.h): the slots this unit calls. */
typedef struct ScreenBgVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();
    u8 pad_08[0x4C - 0x08];
    void (*show)();      /* 0x4C (bg, root, 0) */
    void (*hide)();      /* 0x50 */
    u8 pad_54[0xB8 - 0x54];
    void (*setColor)();  /* 0xB8 Bg_SetColor (bg, 1, color) */
} ScreenBgVtbl;

typedef struct ScreenBg {
    ScreenBgVtbl *vtbl;
} ScreenBg;

/* The STR movie Movie_Create makes (src/game/80043008.c, vtable g_movieVtbl). */
typedef struct ScreenMovieVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();
    u8 pad_08[0x40 - 0x08];
    s32 (*open)();       /* 0x40 (movie, path, frameCount, a, b): non-zero when it fails */
    u8 pad_44[0x48 - 0x44];
    s32 (*poll)();       /* 0x48 non-zero once the video has ended */
    void (*stop)();      /* 0x4C */
    u8 pad_50[0x6C - 0x50];
    void (*setUnk68)();  /* 0x6C */
} ScreenMovieVtbl;

typedef struct ScreenMovie {
    ScreenMovieVtbl *vtbl;
} ScreenMovie;

/* View_SetTwist's argument: rz = num / den in 4.12 fixed point. */
typedef struct ViewRatio {
    s16 num;
    s16 den;
} ViewRatio;

ObjectVtbl *Object_GetBaseVtbl(void);
extern void Object_DeleteArray(void *, s32);
void *Heap_Alloc(s32 size);
void Heap_Free(void *);
extern s32 strlen(u8 *);
extern s32 DrawSync(s32);
extern void SetGeomScreen(s32);
void GsSetRefView2(void *);
void ResetGraph(s32 mode);
void GsSortClear(u8 r, u8 g, u8 b, GsOT *ot);
void GsDrawOt(GsOT *ot);
void GsClearOt(s32, s32, GsOT *);
void GsSetLightMode(s32);
void SetFarColor(u8, u8, u8);
void SetFogNear(s32, s32);
void func_8003FB0C(s32);
void func_8003FBE4(void *packets);
SceneNode *SceneNode_New(void);
void *Clock_Create(void);
void *RootNode_Create(void);
SoundBank *Sound_CreateBank(char *path);
Tim *Tim_New(char *path);
void *Fade_Create(s32, s32, s32);
extern void *Box_Create(s32, s32, s32);
Widget *Label_Create(Tim *font, s32 length, u8 *text);
ScreenBg *Bg_Create(ScreenBg *, s32);
ScreenBg *BgMap_Create(s32, ScreenBg *);
ScreenBg *BgCells_Create(s32);
ScreenMovie *Movie_Create(ScreenRect *area, s32, s32);

ScreenVtbl *VideoScreen_GetVtbl(void);
ScreenVtbl *MenuScreen_GetVtbl(void);
ScreenRect *MenuScreen_GetPictureRect(void);
ScreenVtbl *Screen_GetVtbl(void);
View *View_New(void);
ViewVtbl *View_GetVtbl(void);
SceneNode *SceneNode_GetRoot(SceneNode *node);
void View_SetGeomScreen(s32 projection);

extern ScreenVtbl g_videoScreenVtbl[]; /* VideoScreen */
extern ScreenVtbl g_menuScreenVtbl[]; /* MenuScreen */
extern ScreenVtbl g_screenVtbl[]; /* Screen */
extern ViewVtbl g_viewVtbl[];   /* View */
extern s32 g_pictureRect[];        /* ScreenRect (640, 0) 320 x 240: the VRAM area of pictures and videos */
extern u8 g_menuScreenColors[];         /* MenuScreen_Reset colors: (0, 0, 0), (0, 0, 0), (128, 128, 128) */
extern s32 g_screenZeroVec[];        /* ScreenVec (0, 0, 0) */
extern s32 g_optionBoxSize[];        /* option box: (320, 240) */
extern u8 g_optionBoxColor[];         /* option box: "  @" */
extern s32 g_viewNoTwist;          /* ViewRatio (0, 1): no twist */
extern Color3 g_viewDefaultColor;       /* black */
/* .sdata owned by this unit (config/splat.yaml), defined at the end of the file: read whole by View_Reset */
extern ScreenPoint g_viewDefaultScreenSize;
extern s32 g_overlayPos;          /* ScreenPoint (-100, -100): where the overlay hangs */
extern s32 g_overlaySize;          /* the overlay: 320, 240, 10, 10 */

/* VideoScreen */

VideoScreen *VideoScreen_New(MenuDef *menu, char *soundPath, SoundBank *sound, ScreenRect *area) {
    VideoScreen *video;

    video = Heap_Alloc(0xDC);
    if (video != NULL) {
        VideoScreen_GetVtbl()->init(video, menu, soundPath, sound, area);
        return video;
    }
    return NULL;
}

void VideoScreen_Init(VideoScreen *video, MenuDef *menu, char *soundPath, SoundBank *sound, ScreenRect *area) {
    MenuScreen_GetVtbl()->init(video, menu, soundPath, sound);
    video->vtbl = VideoScreen_GetVtbl();
    if (area != NULL) {
        video->area = *area;
    } else {
        video->area = *MenuScreen_GetPictureRect();
    }
    video->movie = Movie_Create(MenuScreen_GetPictureRect(), 0, 0);
    video->path = NULL;
    video->vtbl->reset(video);
}

void VideoScreen_Destroy(VideoScreen *video) {
    ScreenMovie *movie = video->movie;
    movie->vtbl->delete_(movie);
    MenuScreen_GetVtbl()->destroy(video);
}

void VideoScreen_Reset(VideoScreen *video) {
    video->movieLoops = -1;
    video->movieRepeat = 0;
    video->skippable = 1;
    video->unkD0 = 0;
    video->unkD4 = 1;
}

/* Slot 0x44: plays path until it ends, CIRCLE skips it (when skippable) or the timeout runs out. */
void VideoScreen_Play(VideoScreen *video, ScreenEnv *env, char *path, s32 frameCount, s32 arg4) {
    video->path = path;
    video->frameCount = frameCount;
    video->unkC0 = arg4;
    MenuScreen_GetVtbl()->run(video, env, 0);
}

void VideoScreen_Begin(VideoScreen *video) {
    ScreenMovie *movie;

    MenuScreen_GetVtbl()->begin(video);
    movie = video->movie;
    video->finished = 0;
    movie->vtbl->setUnk68(movie, video->unkC0);
    if (video->movie->vtbl->open(video->movie, video->path, video->frameCount, video->movieRepeat, video->movieLoops) != 0) {
        /* the video does not open: time out at once */
        video->vtbl->setTimeout(video, 0);
    }
}

void VideoScreen_OnClock(VideoScreen *video, Clock *clock, s32 message) {
    ScreenMovie *movie;
    s32 finished;

    MenuScreen_GetVtbl()->onClock(video, clock, message);
    if (video->finished == 0) {
        movie = video->movie;
        finished = movie->vtbl->poll(movie);
        video->finished = finished;
        if ((finished != 0) && (video->closing == 0)) {
            video->vtbl->setState(video, SCREEN_CLOSING);
        }
    }
}

void VideoScreen_SetState(VideoScreen *video, s32 state) {
    MenuScreen_GetVtbl()->setState(video, state);
    switch (state) {
    case SCREEN_ACTIVE:
        video->closing = 0;
        break;
    case SCREEN_CLOSING:
        video->closing = 1;
        break;
    case SCREEN_CLOSED:
        if (video->unkD4 == 0) {
            video->movie->vtbl->stop(video->movie);
        }
        break;
    case SCREEN_SKIP:
        video->vtbl->close(video);
        break;
    }
}

/* 15 ticks per second here, 20 in MenuScreen_SetTimeout */
void VideoScreen_SetTimeout(VideoScreen *video, s32 seconds) {
    video->timeout = seconds;
    if (seconds >= 0) {
        video->timeout = seconds * 15;
    }
}

void VideoScreen_OnCircle(VideoScreen *video) {
    MenuScreen_GetVtbl()->onCircle(video);
    if (video->skippable != 0) {
        video->result = 2;
        video->vtbl->setState(video, SCREEN_SKIP);
    }
}

void VideoScreen_OnUp(VideoScreen *video) {
    MenuScreen_GetVtbl()->onUp(video);
}

void VideoScreen_OnDown(VideoScreen *video) {
    MenuScreen_GetVtbl()->onDown(video);
}

void func_8003BDE4(void) {
}

void func_8003BDEC(void) {
}

void VideoScreen_Close(VideoScreen *video) {
    if (video->unkD4 != 0) {
        video->movie->vtbl->stop(video->movie);
        return;
    }
    video->vtbl->setState(video, SCREEN_CLOSING);
}

void VideoScreen_SetMovieRepeat(VideoScreen *video, s32 value) {
    video->movieRepeat = value;
}

void VideoScreen_SetMovieLoops(VideoScreen *video, s32 value) {
    video->movieLoops = value;
}

void VideoScreen_SetSkippable(VideoScreen *video, s32 skippable) {
    video->skippable = skippable;
}

void func_8003BE74(VideoScreen *video, s32 value) {
    video->unkD0 = value;
}

void VideoScreen_SetCloseAtOnce(VideoScreen *video, s32 value) {
    video->unkD4 = value;
}

ScreenVtbl *VideoScreen_GetVtbl(void) {
    return g_videoScreenVtbl;
}

/* MenuScreen */

MenuScreen *MenuScreen_New(MenuDef *menu, char *soundPath, SoundBank *sound) {
    MenuScreen *screen;

    screen = Heap_Alloc(0xA4);
    if (screen != NULL) {
        MenuScreen_GetVtbl()->init(screen, menu, soundPath, sound);
        return screen;
    }
    return NULL;
}

void MenuScreen_Init(MenuScreen *screen, MenuDef *menu, char *soundPath, SoundBank *sound) {
    ScreenVtbl *vtbl;
    ScreenBg *bgCells;
    ScreenBg *bgMap;

    Screen_GetVtbl()->init(screen);
    vtbl = MenuScreen_GetVtbl();
    screen->vtbl = vtbl;
    vtbl->setMenu(screen, menu);
    if (soundPath != 0) {
        screen->sound = Sound_CreateBank(soundPath);
    } else {
        screen->sound = sound;
    }
    screen->soundPath = soundPath;
    screen->vtbl->setPicture(screen, 0, 0);
    bgCells = BgCells_Create(0);
    screen->bgCells = bgCells;
    bgMap = BgMap_Create(0, bgCells);
    screen->bgMap = bgMap;
    screen->bg = Bg_Create(bgMap, 1);
    screen->vtbl->reset(screen);
}

void MenuScreen_Destroy(MenuScreen *screen) {
    screen->bg->vtbl->delete_(screen->bg);
    screen->bgMap->vtbl->delete_(screen->bgMap);
    screen->bgCells->vtbl->delete_(screen->bgCells);
    if (screen->soundPath != 0) {
        screen->sound->vtbl->delete_(screen->sound);
    }
    if (screen->picturePath != 0) {
        screen->picture->vtbl->base.delete_(screen->picture);
    }
    screen->vtbl->freeMenu(screen);
    Screen_GetVtbl()->destroy(screen);
}

void MenuScreen_Reset(MenuScreen *screen) {
    ScreenVtbl *vtbl;

    vtbl = screen->vtbl;
    vtbl->setTimeout(screen, -1);
    vtbl->setColors(screen, g_menuScreenColors, g_menuScreenColors + 3, g_menuScreenColors + 6);
    vtbl->setFadeIn(screen, 1);
    vtbl->setFadeOut(screen, 1);
    screen->fadeSpeed = 9;
    screen->viewOtBits = 3;
    screen->viewPacketCount = 0x12C;
    screen->viewPacketSize = 0x40;
    screen->onClose = 0;
    screen->onCloseArg = 0;
    screen->clearOnEnd = 1;
    screen->focus = MENU_FOCUS_NONE;
}

s32 MenuScreen_Run(MenuScreen *screen, ScreenEnv *env, s32 noLoop) {
    Screen_GetVtbl()->run(screen, env, noLoop);
    return screen->result;
}

void MenuScreen_Begin(MenuScreen *screen) {
    View *view;
    ViewVtbl *viewVtbl;

    view = screen->view;
    viewVtbl = view->vtbl;
    screen->vtbl->showItems(screen, screen->root);
    screen->bg->vtbl->show(screen->bg, screen->root, 0);
    if (screen->fadeInStep != 0) {
        screen->vtbl->setItemsColor(screen, &screen->startColor);
        screen->bg->vtbl->setColor(screen->bg, 1, &screen->startColor);
    }
    if (screen->picture == 0) {
        screen->env->display->vtbl->clearImage(screen->env->display, &screen->startColor, g_pictureRect);
    }
    screen->env->display->vtbl->clearImage(screen->env->display, &screen->startColor, 0);
    viewVtbl->setOtBits(view, screen->viewOtBits);
    viewVtbl->setPacketCount(view, screen->viewPacketCount);
    viewVtbl->setPacketSize(view, screen->viewPacketSize);
    viewVtbl->setCamera(view, screen->root, g_screenZeroVec, g_screenZeroVec, 0);
    viewVtbl->allocOt(view);
    screen->result = 0;
}

void MenuScreen_End(MenuScreen *screen) {
    View *view;
    ScreenBg *bg;
    Display *display;

    view = screen->view;
    view->vtbl->freeOt(view);
    view->vtbl->detach(view);
    bg = screen->bg;
    bg->vtbl->hide(bg);
    if (screen->clearOnEnd != 0) {
        display = screen->env->display;
        display->vtbl->clearImage(display, &screen->endColor, 0);
    }
}

/* The pad handler: only while the screen has the focus, and only presses. */
void MenuScreen_OnPad(MenuScreen *screen, Pad *pad, s32 code) {
    ScreenVtbl *vtbl = screen->vtbl;
    void (*handler)();

    if (screen->focus != MENU_FOCUS_NONE) {
        switch (code) {
        case PAD_PRESSED_UP:
            handler = vtbl->onUp;
            break;
        case PAD_PRESSED_DOWN:
            handler = vtbl->onDown;
            break;
        case PAD_PRESSED_START:
            handler = vtbl->onStart;
            break;
        case PAD_PRESSED_CROSS:
            handler = vtbl->onCross;
            break;
        case PAD_PRESSED_CIRCLE:
            handler = vtbl->onCircle;
            break;
        default:
            return;
        }
        handler(screen, pad);
    }
}

void MenuScreen_OnClock(MenuScreen *screen, Clock *clock, s32 message) {
    ScreenVtbl *vtbl = screen->vtbl;

    Screen_GetVtbl()->onClock(screen, clock, message);
    if (screen->focus != MENU_FOCUS_NONE && (u32) screen->ticks > (u32) screen->timeout) {
        vtbl->setState(screen, SCREEN_TIMEOUT);
    }
    switch (screen->state) {
    case SCREEN_START:
        vtbl->setState(screen, SCREEN_FADING_IN);
        break;
    case SCREEN_FADING_IN:
        vtbl->fadeIn(screen);
        break;
    case SCREEN_CLOSING:
        vtbl->fadeOut(screen);
        break;
    case SCREEN_CLOSED:
        vtbl->setState(screen, SCREEN_STOP);
        break;
    }
}

void MenuScreen_SetState(MenuScreen *screen, s32 state) {
    ScreenVtbl *vtbl;
    void (*handler)();

    vtbl = screen->vtbl;
    Screen_GetVtbl()->setState(screen, state);
    switch (state) {
    case SCREEN_ACTIVE:
        vtbl->setItemsColor(screen, &screen->menu->color);
        vtbl->selectItem(screen, screen->menu->initialItem, 0);
        screen->ticks = 0;
        screen->focus = MENU_FOCUS_ITEMS;
        return;
    case SCREEN_TIMEOUT:
        screen->result = 1;
        handler = vtbl->close;
        break;
    case SCREEN_FADING_IN:
    case SCREEN_CLOSING:
        screen->ticks = 0;
        screen->focus = MENU_FOCUS_NONE;
        return;
    case SCREEN_CLOSED:
        screen->ticks = 0;
        return;
    case SCREEN_ITEM_MOVED:
    case SCREEN_START_PRESSED:
    case SCREEN_CONFIRM:
    case SCREEN_OPTIONS_OPENED:
    case SCREEN_OPTION_CONFIRM:
    case SCREEN_OPTION_ACCEPTED:
    case SCREEN_OPTION_CANCEL:
        screen->state = SCREEN_ACTIVE;
        screen->ticks = 0;
        switch (state) {
        case SCREEN_CONFIRM:
            handler = vtbl->confirm;
            break;
        case SCREEN_OPTION_CONFIRM:
            handler = vtbl->acceptOption;
            break;
        case SCREEN_OPTION_CANCEL:
            handler = vtbl->cancelOptions;
            break;
        default:
            return;
        }
        break;
    default:
        return;
    }
    handler(screen);
}

/* 20 ticks per second */
void MenuScreen_SetTimeout(MenuScreen *screen, s32 seconds) {
    screen->timeout = seconds;
    if (seconds >= 0) {
        screen->timeout = seconds * 20;
    }
}

void MenuScreen_PlaySound(MenuScreen *screen, s32 tone) {
    SoundBank *sound;

    sound = screen->sound;
    if (sound != NULL) {
        sound->vtbl->playTone(sound, tone, 0x60, 0x60);
    }
}

void MenuScreen_OnStart(MenuScreen *screen) {
    if (screen->menu != 0) {
        screen->vtbl->playSound(screen, 0x10);
        screen->vtbl->setState(screen, SCREEN_START_PRESSED);
    }
}

void MenuScreen_OnCircle(MenuScreen *screen) {
    s32 state;

    if (screen->menu != 0) {
        screen->vtbl->playSound(screen, 0x10);
        state = SCREEN_OPTION_CONFIRM;
        if (screen->focus == MENU_FOCUS_ITEMS) {
            state = SCREEN_CONFIRM;
        }
        screen->vtbl->setState(screen, state);
    }
}

void MenuScreen_OnCross(MenuScreen *screen) {
    if (screen->menu != 0 && screen->focus != MENU_FOCUS_ITEMS) {
        screen->vtbl->playSound(screen, 0x10);
        screen->vtbl->setState(screen, SCREEN_OPTION_CANCEL);
    }
}

void MenuScreen_OnUp(MenuScreen *screen) {
    if (screen->menu != 0) {
        if (screen->focus == MENU_FOCUS_ITEMS) {
            screen->vtbl->prevItem(screen);
        } else if (screen->focus == MENU_FOCUS_OPTIONS) {
            screen->vtbl->prevOption(screen);
        }
    }
}

void MenuScreen_OnDown(MenuScreen *screen) {
    if (screen->menu != 0) {
        if (screen->focus == MENU_FOCUS_ITEMS) {
            screen->vtbl->nextItem(screen);
        } else if (screen->focus == MENU_FOCUS_OPTIONS) {
            screen->vtbl->nextOption(screen);
        }
    }
}

/* CIRCLE on an item: opens its option list, or closes the screen on the close item. */
void MenuScreen_Confirm(MenuScreen *screen) {
    MenuDef *menu = screen->menu;
    s32 selected = screen->selected;
    void (*handler)();

    if (menu->options[selected] != 0) {
        handler = screen->vtbl->openOptions;
    } else if (selected == menu->closeItem) {
        handler = screen->vtbl->close;
    } else {
        return;
    }
    handler(screen, menu, selected);
}

void MenuScreen_Close(MenuScreen *screen) {
    if (screen->onClose != NULL) {
        screen->onClose(screen->onCloseArg);
    }
    screen->vtbl->setState(screen, SCREEN_CLOSING);
}

void MenuScreen_SetOnClose(MenuScreen *screen, void (*onClose)(), s32 onCloseArg) {
    screen->onClose = onClose;
    screen->onCloseArg = onCloseArg;
}

void MenuScreen_SetFadeIn(MenuScreen *screen, s32 enabled) {
    ScreenVtbl *vtbl = screen->vtbl;

    switch (enabled) {
    case 0:
        screen->fadeInStep = 0;
        break;
    case 1:
        screen->fadeInStep = vtbl->fadeInStep;
        break;
    }
}

void MenuScreen_SetFadeOut(MenuScreen *screen, s32 enabled) {
    ScreenVtbl *vtbl = screen->vtbl;

    switch (enabled) {
    case 0:
        screen->fadeOutStep = 0;
        return;
    case 1:
        screen->fadeOutStep = vtbl->fadeOutStep;
        return;
    }
}

void MenuScreen_SetColors(MenuScreen *screen, Color3 *startColor, Color3 *endColor, Color3 *color96) {
    screen->startColor = *startColor;
    screen->endColor = *endColor;
    screen->unk96 = *color96;
}

void MenuScreen_SetFadeSpeed(MenuScreen *screen, s32 fadeSpeed) {
    screen->fadeSpeed = fadeSpeed;
}

s32 MenuScreen_FadeIn(MenuScreen *screen) {
    s32 (*step)();
    s32 done;

    step = screen->fadeInStep;
    done = 1;
    if (step != NULL) {
        done = step();
    }
    if (done != 0) {
        screen->vtbl->setState(screen, SCREEN_ACTIVE);
    }
    return done;
}

/* Brightness rises by fadeSpeed per tick from startColor; done past 128. */
s32 MenuScreen_FadeInStep(MenuScreen *screen) {
    s8 color[3];
    s32 level;
    ScreenBg *bg;

    level = screen->ticks * screen->fadeSpeed;
    color[0] = level + screen->startColor.r;
    color[1] = level + screen->startColor.g;
    color[2] = level + screen->startColor.b;
    screen->vtbl->setItemsColor(screen, color);
    bg = screen->bg;
    bg->vtbl->setColor(bg, 1, color);
    return (u8)level >= 0x81;
}

s32 MenuScreen_FadeOut(MenuScreen *screen) {
    s32 done = 1;

    if (screen->fadeOutStep == NULL || (done = screen->fadeOutStep()) != 0) {
        screen->vtbl->setState(screen, SCREEN_CLOSED);
    }
    return done;
}

/* Brightness falls from 128 by fadeSpeed per tick. */
s32 MenuScreen_FadeOutStep(MenuScreen *screen) {
    s8 color[3];
    s32 level;
    ScreenBg *bg;

    level = 0x80 - (screen->ticks * screen->fadeSpeed);
    color[0] = level;
    color[1] = level;
    color[2] = level;
    screen->vtbl->setItemsColor(screen, color);
    bg = screen->bg;
    bg->vtbl->setColor(bg, 1, color);
    return (u8)level > 0x80;
}

void MenuScreen_SetPicture(MenuScreen *screen, char *path, Tim *image) {
    Tim *picture;
    Tim *loaded;

    if (path != 0) {
        if (screen->picturePath != 0) {
            picture = screen->picture;
            picture->vtbl->base.delete_(picture);
        }
        loaded = Tim_New(path);
        screen->picture = loaded;
        loaded->vtbl->upload(loaded);
        picture = screen->picture;
        picture->vtbl->base.freeData(picture);
    } else {
        screen->picture = image;
    }
    screen->picturePath = path;
}

/* Makes one text per item with the menu's font, and the option texts of items that have a list. */
void MenuScreen_SetMenu(MenuScreen *screen, MenuDef *menu) {
    u8 **text;
    s32 count;
    s32 i;
    s32 size;
    OptionListDef *options;
    Widget **items;
    Tim *font;

    screen->menu = menu;
    if (menu != NULL) {
        text = menu->texts;
        count = 0;
        while (*text++ != 0) {
            count++;
        }
        size = count * 4;
        items = Heap_Alloc(size);
        screen->items = items;
        screen->optionCounts = Heap_Alloc(size);
        screen->optionSelected = Heap_Alloc(size);
        screen->options = Heap_Alloc(size);
        screen->itemCount = count;
        if (menu->fontPath != 0) {
            font = Tim_New(menu->fontPath);
            font->vtbl->upload(font);
            font->vtbl->base.freeData(font);
        } else {
            font = menu->font;
        }
        text = menu->texts;
        i = 0;
        if (*text != 0) {
            do {
                options = menu->options[i];
                *items = Label_Create(font, strlen(*text), *text);
                items++;
                if (options != 0) {
                    screen->selected = i;
                    screen->vtbl->makeOptions(screen, options, font);
                }
                text++;
                i++;
            } while (*text != 0);
        }
        screen->optionBox = Box_Create((s32)g_optionBoxSize, (s32)g_optionBoxColor, 0);
        menu->font = font;
    }
}

void MenuScreen_FreeMenu(MenuScreen *screen) {
    s32 i;
    s32 stackPad[2];
    MenuDef *menu;
    Widget **items;
    Widget *widget;
    Tim *font;

    menu = screen->menu;
    if (menu != NULL) {
        if (menu->fontPath != 0) {
            font = menu->font;
            font->vtbl->base.delete_(font);
        }
        widget = screen->optionBox;
        i = 0;
        widget->vtbl->delete_(widget);
        items = screen->items;
        if (screen->itemCount > 0) {
            do {
                if (screen->menu->options[i] != 0) {
                    screen->selected = i;
                    screen->vtbl->freeOptions(screen);
                }
                widget = *items;
                widget->vtbl->delete_(widget);
                i++;
                items++;
            } while (i < screen->itemCount);
        }
        Heap_Free(screen->options);
        Heap_Free(screen->optionSelected);
        Heap_Free(screen->optionCounts);
        Heap_Free(screen->items);
    }
}

void MenuScreen_ShowItems(MenuScreen *screen, SceneNode *root) {
    s32 *position;
    Widget **items;
    s32 i;

    if (screen->menu != NULL) {
        items = screen->items;
        position = screen->menu->positions;
        for (i = 0; i < screen->itemCount; i++, items++, position += 2) {
            if (screen->menu->hidden[i] == 0) {
                (*items)->vtbl->show(*items, root, position);
                if (screen->menu->options[i] != 0) {
                    screen->selected = i;
                    screen->vtbl->showOptions(screen, root, 0);
                }
            } else {
                (*items)->vtbl->hide(*items);
            }
        }
    }
}

void MenuScreen_SetItemsColor(MenuScreen *screen, Color3 *color) {
    s32 i;
    s32 saved;
    Widget **items;
    Widget *item;

    if (screen->menu != NULL) {
        items = screen->items;
        saved = screen->selected;
        for (i = 0; i < screen->itemCount; i++, items++) {
            item = *items;
            item->vtbl->setColor(item, color);
            if (screen->menu->options[i] != 0) {
                screen->selected = i;
                screen->vtbl->setOptionsColor(screen, color);
            }
        }
        screen->selected = saved;
    }
}

void MenuScreen_NextItem(MenuScreen *screen) {
    s32 i;

    if (screen->menu != NULL) {
        i = screen->selected;
        do {
            i++;
            if (i >= screen->itemCount) {
                i = 0;
            }
        } while (i != screen->selected && screen->menu->hidden[i] != 0);
        screen->vtbl->selectItem(screen, i, 1);
    }
}

void MenuScreen_PrevItem(MenuScreen *screen) {
    s32 i;

    if (screen->menu != NULL) {
        i = screen->selected;
        do {
            i--;
            if (i < 0) {
                i = screen->itemCount - 1;
            }
        } while (i != screen->selected && screen->menu->hidden[i] != 0);
        screen->vtbl->selectItem(screen, i, 1);
    }
}

void MenuScreen_SelectItem(MenuScreen *screen, s32 index, s32 playSound) {
    Widget *previous;
    Widget *item;

    if (screen->menu != 0) {
        previous = screen->items[screen->selected];
        item = screen->items[index];
        if (screen->selected >= 0) {
            previous->vtbl->setColor(previous, &screen->menu->color);
        }
        item->vtbl->setColor(item, &screen->menu->selectColor);
        screen->selected = index;
        if (playSound != 0) {
            screen->vtbl->playSound(screen, 0);
        }
        screen->vtbl->setState(screen, SCREEN_ITEM_MOVED);
    }
}

s32 MenuScreen_GetSelectedItem(MenuScreen *screen) {
    return screen->selected;
}

/* The option texts of the selected item. */
void MenuScreen_MakeOptions(MenuScreen *screen, OptionListDef *list, Tim *font) {
    u8 **text;
    s32 count;
    s32 index;
    Widget **texts;
    s32 length;

    text = list->texts;
    index = screen->selected;
    count = 0;
    while (*text++ != 0) {
        count++;
    }
    texts = Heap_Alloc(count * 4);
    screen->options[index] = texts;
    screen->optionSelected[index] = list->selected;
    screen->optionCounts[index] = count;
    text = list->texts;
    while (*text != 0) {
        length = strlen(*text);
        *texts++ = Label_Create(font, length, *text);
        text++;
    }
}

void MenuScreen_FreeOptions(MenuScreen *screen) {
    Object_DeleteArray(screen->options[screen->selected], screen->optionCounts[screen->selected]);
    Heap_Free(screen->options[screen->selected]);
}

/* Shows the option list of the selected item: all options in the box when open, else the chosen one only. */
void MenuScreen_ShowOptions(MenuScreen *screen, SceneNode *root, s32 open) {
    ScreenPoint position;
    ScreenSize size;
    s32 stackPad[4];
    OptionListDef *list;
    Widget **texts;
    Widget *widget;
    s32 index;
    s32 count;
    s32 current;
    s32 i;

    index = screen->selected;
    texts = screen->options[index];
    current = screen->menu->options[index]->selected;
    count = screen->optionCounts[index];

    i = 0;
    if (count > 0) {
        do {
            widget = *texts;
            texts++;
            widget->vtbl->hide(widget);
            i++;
        } while (i < count);
    }

    list = screen->menu->options[index];
    position = list->pos;
    position.y -= current * 10;

    if (open != 0) {
        widget = screen->optionBox;
        widget->vtbl->show(widget, screen->root, &position);
        size.w = 0x28;
        size.h = count * 12;
        widget = screen->optionBox;
        widget->vtbl->setSize(widget, &size);
    } else {
        widget = screen->optionBox;
        widget->vtbl->hide(widget);
    }

    texts = screen->options[index];
    i = 0;
    if (count > 0) {
        do {
            (*texts)->vtbl->show(*texts, root, &position);
            i++;
            (*texts)->vtbl->setVisible(*texts, open);
            position.y += 10;
            texts++;
        } while (i < count);
    }

    texts = screen->options[index];
    widget = texts[current];
    widget->vtbl->setVisible(widget, 1);
}

void MenuScreen_SetOptionsColor(MenuScreen *screen, Color3 *color) {
    Widget **texts;
    s32 count;
    s32 i;

    texts = screen->options[screen->selected];
    count = screen->optionCounts[screen->selected];
    for (i = 0; i < count; i++) {
        Widget *widget = *texts;
        texts++;
        widget->vtbl->setColor(widget, color);
    }
}

void MenuScreen_OpenOptions(MenuScreen *screen) {
    s32 i;
    Widget *option;

    if (screen->focus == MENU_FOCUS_ITEMS) {
        i = screen->selected;
        screen->vtbl->showOptions(screen, screen->root, 1);
        option = screen->options[i][screen->optionSelected[i]];
        option->vtbl->setColor(option, &screen->menu->options[i]->color);
        screen->focus = MENU_FOCUS_OPTIONS;
        screen->vtbl->setState(screen, SCREEN_OPTIONS_OPENED);
    }
}

/* Keeps the highlighted option: it stays shown next to the item, the list closes. */
void MenuScreen_AcceptOption(MenuScreen *screen) {
    ScreenPoint position;
    ScreenPoint unused;
    Widget **texts;
    Widget *option;
    s32 index;
    s32 chosen;
    s32 count;
    s32 i;

    if (screen->focus == MENU_FOCUS_OPTIONS) {
        index = screen->selected;
        chosen = screen->optionSelected[index];
        position = screen->menu->options[index]->pos;
        position.y -= chosen * 10;
        texts = screen->options[index];
        count = screen->optionCounts[index];
        if (count > 0) {
            i = 0;
            do {
                (*texts)->vtbl->setVisible(*texts, 0);
                i += 1;
                (*texts)->vtbl->setPosition(*texts, &position);
                position.y += 10;
                texts++;
            } while (i < count);
        }
        option = screen->options[index][chosen];
        option->vtbl->setVisible(option, 1);
        option->vtbl->setColor(option, &screen->menu->color);
        screen->menu->options[index]->selected = chosen;
        screen->optionBox->vtbl->hide(screen->optionBox);
        screen->focus = MENU_FOCUS_ITEMS;
        screen->vtbl->setState(screen, SCREEN_OPTION_ACCEPTED);
    }
}

/* Goes back to the option chosen before the list opened. */
void MenuScreen_CancelOptions(MenuScreen *screen) {
    s32 i;
    s32 current;
    s32 previous;
    Widget **texts;
    Widget *option;

    if (screen->focus == MENU_FOCUS_OPTIONS) {
        i = screen->selected;
        current = screen->optionSelected[i];
        screen->vtbl->showOptions(screen, screen->root, 0);
        texts = screen->options[i];
        option = texts[current];
        option->vtbl->setColor(option, &screen->menu->color);
        previous = screen->menu->options[i]->selected;
        screen->optionSelected[i] = previous;
        option = texts[previous];
        option->vtbl->setVisible(option, 1);
        screen->focus = MENU_FOCUS_ITEMS;
        screen->vtbl->setState(screen, SCREEN_OPTION_CANCEL);
    }
}

void MenuScreen_NextOption(MenuScreen *screen) {
    s32 next;

    next = screen->optionSelected[screen->selected];
    next = next + 1;
    if (next >= screen->optionCounts[screen->selected]) {
        next = 0;
    }
    screen->vtbl->selectOption(screen, next, 1);
}

void MenuScreen_PrevOption(MenuScreen *screen) {
    s32 previous;

    previous = screen->optionSelected[screen->selected];
    previous--;
    if (previous < 0) {
        previous = screen->optionCounts[screen->selected] - 1;
    }
    screen->vtbl->selectOption(screen, previous, 1);
}

void MenuScreen_SelectOption(MenuScreen *screen, s32 index, s32 playSound) {
    s32 i = screen->selected;
    s32 *selected = &screen->optionSelected[i];
    Widget ***options = &screen->options[i];
    Widget **texts = *options;
    Widget *previous = texts[*selected];
    Widget *option = texts[index];

    previous->vtbl->setColor(previous, &screen->menu->color);
    option->vtbl->setColor(option, &screen->menu->options[i]->color);
    screen->optionSelected[i] = index;
    if (playSound != 0) {
        screen->vtbl->playSound(screen, 0);
    }
    screen->vtbl->setState(screen, SCREEN_ITEM_MOVED);
}

s32 MenuScreen_GetSelectedOption(MenuScreen *screen) {
    return screen->optionSelected[screen->selected];
}

ScreenVtbl *MenuScreen_GetVtbl(void) {
    return g_menuScreenVtbl;
}

ScreenRect *MenuScreen_GetPictureRect(void) {
    return (ScreenRect *)g_pictureRect;
}

/* Screen */

void Screen_Init(Screen *screen) {
    ScreenVtbl *vtbl;

    Object_GetBaseVtbl()->init(screen);
    vtbl = Screen_GetVtbl();
    screen->vtbl = vtbl;
    vtbl->reset(screen);
}

/* Dispatches on the sender's type, the low 4 bits of its vtable tag. */
void Screen_OnNotify(Screen *screen, Object *sender, s32 message) {
    s32 type;

    Object_GetBaseVtbl()->onNotify(screen, sender, message);
    type = sender->vtbl->classWord & 0xF;
    if (type == 1) {
        screen->vtbl->onDisplay(screen, sender, message);
    } else if (type == 2) {
        screen->vtbl->onPad(screen, sender, message);
    } else if (type == 5) {
        screen->vtbl->onClock(screen, sender, message);
    }
}

void Screen_Reset(Screen *screen) {
    screen->ticks = 0;
    screen->state = 0;
}

/* Slot 0x44: watches the env's objects, begins, then runs the display loop until state 3. */
void Screen_Run(Screen *screen, ScreenEnv *env, s32 noLoop) {
    ScreenVtbl *vtbl;
    View *view;
    SceneNode *root;
    s32 object;

    vtbl = screen->vtbl;
    object = (s32)env->clock;
    if (object == 0) {
        object = (s32)Clock_Create();
    }
    screen->clock = (Clock *)object;
    object = (s32)env->root;
    if (object == 0) {
        object = (s32)RootNode_Create();
    }
    screen->root = (SceneNode *)object;
    object = (s32)env->view;
    if (object == 0) {
        object = (s32)View_New();
    }
    screen->view = (View *)object;
    screen->env = env;
    view = screen->view;
    vtbl->watch(screen, env->display);
    vtbl->watch(screen, env->pad);
    vtbl->watch(screen, screen->clock);
    vtbl->begin(screen, 0, 0, 0);
    screen->unk24 = noLoop;
    if (noLoop == 0) {
        view->vtbl->watch(view, env->display);
        view->vtbl->watch(view, screen->clock);
        root = screen->root;
        root->vtbl->watch(root, screen->clock);
        vtbl->setState(screen, SCREEN_START);
        vtbl->finish(screen);
    }
}

/* Ends, unwatches everything, deletes the clock, root and view it made itself. */
void Screen_Finish(Screen *screen) {
    ScreenVtbl *vtbl;
    View *view;
    SceneNode *root;
    SceneNode *ownRoot;
    Clock *clock;

    vtbl = screen->vtbl;
    vtbl->end(screen);
    view = screen->view;
    if (screen->unk24 == 0) {
        root = screen->root;
        root->vtbl->unwatch(root, screen->clock);
        view->vtbl->unwatch(view, screen->clock);
        view->vtbl->unwatch(view, screen->env->display);
    }
    vtbl->unwatch(screen, screen->clock);
    vtbl->unwatch(screen, screen->env->pad);
    vtbl->unwatch(screen, screen->env->display);
    if (screen->env->view != view) {
        screen->view = view->vtbl->delete_(view);
    }
    ownRoot = screen->root;
    if (screen->env->root != ownRoot) {
        screen->root = ownRoot->vtbl->delete_(ownRoot);
    }
    clock = screen->clock;
    if (screen->env->clock != clock) {
        screen->clock = clock->vtbl->delete_(clock);
    }
}

/* Each frame of the display: steps the clock, reads the pad and sends its codes. */
void Screen_OnDisplay(Screen *screen, Display *display, s32 message) {
    Clock *clock;
    Pad *pad;

    if (message == 2) {
        clock = screen->clock;
        clock->vtbl->step(clock);
        pad = screen->env->pad;
        pad->vtbl->read(pad);
        pad->vtbl->send(pad);
    }
}

void Screen_OnClock(Screen *screen) {
    screen->ticks++;
}

void Screen_SetState(Screen *screen, s32 state) {
    ScreenVtbl *vtbl = screen->vtbl;

    screen->state = state;
    vtbl->notify(screen, state);
    if (state == SCREEN_START) {
        vtbl->startLoop(screen);
    } else if (state == SCREEN_STOP) {
        vtbl->stopLoop(screen);
    }
}

void Screen_StartLoop(Screen *screen) {
    screen->ticks = 0;
    screen->env->display->vtbl->startLoop(screen->env->display);
}

void Screen_StopLoop(Screen *screen) {
    Display *display;

    display = screen->env->display;
    display->vtbl->stopLoop(display);
    screen->ticks = 0;
}

ScreenVtbl *Screen_GetVtbl(void) {
    return g_screenVtbl;
}

/* View */

View *View_New(void) {
    View *view;

    view = Heap_Alloc(0xBC);
    if (view != NULL) {
        View_GetVtbl()->init(view);
        return view;
    }
    return NULL;
}

void View_Init(View *view) {
    Fade *overlay;

    Object_GetBaseVtbl()->init(view);
    view->vtbl = View_GetVtbl();
    view->display = 0;
    view->node = 0;
    view->root = SceneNode_New();
    overlay = Fade_Create((s32)&g_overlaySize, 0, 0);
    view->overlay = overlay;
    overlay->vtbl->show(overlay, view->root, &g_overlayPos);
    view->vtbl->reset(view);
}

void View_Destroy(View *view) {
    SceneNode *root;

    view->vtbl->freeOt();
    view->vtbl->detach(view);
    root = view->root;
    root->vtbl->delete_(root);
    view->vtbl->setOverlay(view, 0);
    Object_GetBaseVtbl()->destroy(view);
}

/* Watching a display draws for it; watching a scene node takes its coordinate as the view's super. */
void View_Watch(View *view, Object *other) {
    s32 type;

    Object_GetBaseVtbl()->watch(view, other);
    type = other->vtbl->classWord & 0xF;
    if (type == 4) {
        view->node = (SceneNode *)other;
        view->super = ((SceneNode *)other)->coord;
    } else if (type == 1) {
        view->display = (Display *)other;
    }
}

void View_Unwatch(View *view, Object *other) {
    s32 type;

    type = other->vtbl->classWord & 0xF;
    if (type == 4) {
        view->super = 0;
        view->node = 0;
    } else if (type == 1) {
        view->display = 0;
    }
    Object_GetBaseVtbl()->unwatch(view, other);
}

void View_UnwatchAll(View *view) {
    view->super = 0;
    view->node = 0;
    view->display = 0;
    Object_GetBaseVtbl()->unwatchAll(view);
}

void View_OnNotify(View *view, Object *sender, s32 message) {
    s32 type;

    Object_GetBaseVtbl()->onNotify(view, sender, message);
    type = sender->vtbl->classWord & 0xF;
    if (type == 5) {
        view->vtbl->onClock(view, sender, message);
    } else if (type == 1) {
        view->vtbl->onDisplay(view, sender, message);
    }
}

void View_Reset(View *view) {
    view->clockCount = 0;
    view->otReady = 0;
    view->screenSize = g_viewDefaultScreenSize;
    view->otBits = 0xD;
    view->packetCount = 0x7D0;
    view->packetSize = 0x40;
    view->projection = 0x100;
    view->unk4C = 0xA;
    view->unk50 = 0x10000;
    view->lightMode = 0;
    view->fogNear = 0x4E20;
    view->fogColor = g_viewDefaultColor;
    view->clearColor = g_viewDefaultColor;
    view->unkB4 = 0;
    view->unkB8 = 1;
}

void View_SetScreenSize(View *view, ScreenPoint *value) {
    view->screenSize = *value;
}

void View_SetOtBits(View *view, s32 otBits) {
    view->otBits = otBits;
}

/* The packet sizes only change while the ordering tables are not allocated. */
void View_SetPacketCount(View *view, s32 packetCount) {
    if (view->otReady == 0) {
        view->packetCount = packetCount;
    }
}

void View_SetPacketSize(View *view, s32 packetSize) {
    if (view->otReady == 0) {
        view->packetSize = packetSize;
    }
}

void View_SetProjection(View *view, s32 projection) {
    view->projection = projection;
}

void func_8003EA6C(void) {
}

void func_8003EA74(void) {
}

void View_SetLightMode(View *view, s32 lightMode) {
    view->lightMode = lightMode;
}

void View_SetClearColor(View *view, Color3 *color) {
    view->clearColor = *color;
}

void View_SetFogColor(View *view, Color3 *color) {
    view->fogColor = *color;
}

void View_SetFogNear(View *view, s32 fogNear) {
    view->fogNear = fogNear;
}

/* Only when no node is watched yet: watches node, sets viewpoint, reference point and twist. */
void View_SetCamera(View *view, SceneNode *node, ScreenVec *viewpoint, ScreenVec *refPoint, ViewRatio *twist) {
    ViewVtbl *vtbl;
    ViewRatio *ratio;

    vtbl = view->vtbl;
    if (view->node == 0) {
        vtbl->watch(); /* (view, node): both are still in the argument registers */
        vtbl->setViewpoint(view, viewpoint);
        vtbl->setRefPoint(view, refPoint);
        ratio = twist;
        if (ratio == NULL) {
            ratio = (ViewRatio *)&g_viewNoTwist;
        }
        vtbl->setTwist(view, ratio);
        GsSetRefView2(&view->viewpoint);
    }
}

void View_Detach(View *view) {
    SceneNode *node = view->node;
    if (node != 0) {
        view->vtbl->unwatch(view, node);
    }
}

void View_SetViewpoint(View *view, ScreenVec *viewpoint) {
    if (view->node != 0) {
        view->viewpoint = *viewpoint;
    }
}

void View_SetRefPoint(View *view, ScreenVec *refPoint) {
    if (view->node != 0) {
        view->refPoint = *refPoint;
    }
}

void View_SetTwist(View *view, ViewRatio *ratio) {
    s16 num;
    s16 den;

    if (view->node != 0) {
        num = ratio->num;
        den = ratio->den;
        view->twist = ((num / den) << 12) + (((num % den) << 12) / den);
    }
}

void func_8003ECC0(void) {
}

void func_8003ECC8(void) {
}

/*
 * One heap block for both buffers, each: a GsOT header (0x14 bytes), 2^otBits entries, then
 * packetCount x packetSize bytes of GPU packets.
 */
void View_AllocOt(View *view) {
    s32 size;
    u8 *block;

    if (view->otReady == 0) {
        size = 0x14 + (4 << view->otBits) + view->packetSize * view->packetCount;
        block = (u8 *) Heap_Alloc(size * 2);
        if (block != NULL) {
            view->ot[0] = (GsOT *) block;
            block = block + 0x14;
            view->otEntries[0] = block;
            view->packets[0] = (void *) ((4 << view->otBits) + (s32)block);
            view->ot[1] = (GsOT *) (size + (u8 *) view->ot[0]);
            view->otEntries[1] = (void *) (size + (u8 *) view->otEntries[0]);
            view->packets[1] = (void *) (size + (u8 *) view->packets[0]);
            view->ot[0]->length = view->otBits;
            view->ot[0]->org = view->otEntries[0];
            view->ot[1]->length = view->otBits;
            view->ot[1]->org = view->otEntries[1];
            GsClearOt(0, 0, view->ot[0]);
            GsClearOt(0, 0, view->ot[1]);
            view->otReady = 1;
            view->buffer = 0;
        }
    }
}

void View_FreeOt(View *view) {
    if (view->otReady != 0) {
        DrawSync(0);
        Heap_Free(view->ot[0]);
        view->otReady = 0;
    }
}

/* Clock messages 2 (tick) and 3 (paused) render a frame. */
void View_OnClock(View *view, Clock *clock, s32 message) {
    s32 render;

    render = (message == 2 || message == 3);
    view->clockCount++;
    if (render) {
        view->vtbl->render(view, clock, render);
    }
}

void View_OnDisplay(View *view, Display *display, s32 message) {
    if (message == 2) {
        view->vtbl->present(view);
    }
}

/* Sorts the root and the watched node's tree into the ordering table of this buffer. */
void View_Render(View *view) {
    if (view->otReady != 0) {
        if (view->node->parent != NULL) {
            view->vtbl->drawNode(view, view->node);
        }
        View_SetGeomScreen(view->projection);
        func_8003FB0C(view->unk4C);
        GsSetLightMode(view->lightMode);
        if (view->lightMode == 1 || view->lightMode == 3) {
            SetFarColor(view->fogColor.r, view->fogColor.g, view->fogColor.b);
            SetFogNear(view->fogNear, view->projection);
        }
        GsSetRefView2(&view->viewpoint);
        view->super->flg = 0;
        view->unk98 = ((u32)(view->unk50 - view->unk4C) / (u32)(1 << view->otBits)) + 1;
        func_8003FBE4(view->packets[view->buffer]);
        GsClearOt(0, 0, view->ot[view->buffer]);
        view->vtbl->drawNode(view, view->root);
        if (view->node != NULL) {
            view->vtbl->drawNode(view, SceneNode_GetRoot(view->node));
        }
    }
}

/* Each display frame: clears with clearColor and draws the ordering table, then flips the buffer. */
void View_Present(View *view) {
    if (view->otReady != 0) {
        view->buffer = view->display->vtbl->getActiveBuffer(view->display);
        if (view->unkB8 != 0) {
            ResetGraph(1);
            view->display->vtbl->swapBuffers(view->display);
            if (view->unkB4 != 0 && view->buffer == 0) {
                view->display->vtbl->swapBuffers(view->display);
            }
            GsSortClear(view->clearColor.r, view->clearColor.g, view->clearColor.b, view->ot[view->buffer]);
            GsDrawOt(view->ot[view->buffer]);
            if (view->unkB4 != 0 && view->buffer == 0) {
                view->display->vtbl->swapBuffers(view->display);
            }
        }
        view->buffer = view->buffer == 0;
    }
}

void View_SetOverlay(View *view, Fade *overlay) {
    Fade *previous;

    if (view->node == 0) {
        previous = view->overlay;
        if (previous != NULL) {
            previous->vtbl->delete_(previous);
        }
        view->overlay = overlay;
        if (overlay != NULL) {
            overlay->vtbl->show(overlay, view->root, &g_overlayPos);
        }
    }
}

Fade *View_GetOverlay(View *view) {
    return view->overlay;
}

void View_SetExtraSwap(View *view, s32 value) {
    view->unkB4 = value;
}

void View_SetPresentEnabled(View *view, s32 value) {
    view->unkB8 = value;
}

ViewVtbl *View_GetVtbl(void) {
    return g_viewVtbl;
}

SceneNode *SceneNode_GetRoot(SceneNode *node) {
    while (node->parent != NULL) {
        node = node->parent;
    }
    return node;
}

void View_SetGeomScreen(s32 projection) {
    SetGeomScreen(projection);
}

ScreenPoint g_viewDefaultScreenSize = { 0x100, 0xF0 };

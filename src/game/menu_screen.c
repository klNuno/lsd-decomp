#include "common.h"
#include "game/menu_screen.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"
#include "game/pad.h"
#include "game/sound_bank.h"
#include "game/tim.h"
#include "game/screen.h"
#include "game/view.h"
#include "game/box.h"
#include "game/label.h"
#include "game/clock.h"
#include "game/bg.h"
#include "game/bg_map.h"
#include "game/bg_cells.h"
#include "psyq/libc.h"

/*
 * MenuScreen (include/game/menu_screen.h): a Screen with sound bank, picture, fades, timeout and an item
 * menu (vtable 0x8006E730): logos, special-day pictures, the main menu.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* Pad codes: PAD_PRESSED (pad.h) + button index when a button is pressed (docs/discoveries.md, pad codes). */
#define PAD_PRESSED_UP (PAD_PRESSED + 0)
#define PAD_PRESSED_DOWN (PAD_PRESSED + 1)
#define PAD_PRESSED_CROSS (PAD_PRESSED + 5)
#define PAD_PRESSED_CIRCLE (PAD_PRESSED + 7)
#define PAD_PRESSED_START (PAD_PRESSED + 15)

extern ScreenVtbl g_menuScreenVtbl[]; /* MenuScreen */
extern s32 g_pictureRect[];        /* ScreenRect (640, 0) 320 x 240: the VRAM area of pictures and videos */
extern u8 g_menuScreenColors[];         /* MenuScreen_Reset colors: (0, 0, 0), (0, 0, 0), (128, 128, 128) */
extern s32 g_screenZeroVec[];        /* Vec3 (0, 0, 0) */
extern BoxSize g_optionBoxSize[];    /* option box: (320, 240) */
extern u8 g_optionBoxColor[];        /* option box: "  @" */

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
    BgCells *bgCells;
    BgMap *bgMap;

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
    screen->bgMap->vtbl->base.delete_(screen->bgMap);
    screen->bgCells->vtbl->base.delete_(screen->bgCells);
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
    Bg *bg;
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
    Bg *bg;

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
    Bg *bg;

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
                *items = (Widget *)Label_Create(font, strlen(*text), *text);
                items++;
                if (options != 0) {
                    screen->selected = i;
                    screen->vtbl->makeOptions(screen, options, font);
                }
                text++;
                i++;
            } while (*text != 0);
        }
        screen->optionBox = (Widget *)Box_Create(g_optionBoxSize, g_optionBoxColor, 0);
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
        *texts++ = (Widget *)Label_Create(font, length, *text);
        text++;
    }
}

void MenuScreen_FreeOptions(MenuScreen *screen) {
    Object_DeleteArray((Object **)screen->options[screen->selected], screen->optionCounts[screen->selected]);
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

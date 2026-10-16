#include "common.h"
#include "game/scene.h"
#include "game/menu.h"
#include "game/heap.h"
#include "game/tim.h"
#include "game/menu_screen.h"
#include "game/label.h"
#include "game/text.h"
#include "game/card.h"

/*
 * The main menu (class Menu, vtable g_menuVtbl 0x80086B60). It drives the memory card object of
 * src/game/card.c. Types and states: include/game/menu.h.
 *
 * File boundaries: likely (docs/layout.md)
 */

static MenuVtbl *Menu_GetVtbl(void);

/* Allocates the menu (0xC4 bytes) and runs slot 0x8 of its class, Menu_Init. */
s32 Menu_New(s32 arg0) {
    s32 obj;

    obj = Heap_Alloc(0xC4);
    if (obj != 0) {
        Menu_GetVtbl()->init(obj, arg0);
        return obj;
    }
    return 0;
}
s32 g_cardFileName;
s32 g_cardTitle;
extern MenuFillRect g_menuFillRects[];
extern s32 D_8008A9B4;
s32 open(char *name, s32 flags);
s32 close(s32 fd);
s32 strcpy(s32 dst, s32 src);
s32 g_cardBlankComment;
extern s32 strlen(u8 *);
extern u8 g_cardFileSuffixes[];
void *g_cardFilePrefix;
static MenuVtbl *Menu_GetVtbl(void);
static void SaveMenu_SetTitleDay(s32 dayNumber);
extern u8 g_mainMenuDesc[];
u8 g_titleBlinkChannel;
s32 g_titleBlinkTick;
extern u8 g_menuVtbl[];
s8 *g_titleDayDigits;

INCLUDE_RODATA("asm/nonmatchings/game/menu", D_80011434);

INCLUDE_RODATA("asm/nonmatchings/game/menu", D_80011440);

INCLUDE_RODATA("asm/nonmatchings/game/menu", D_80011454);

INCLUDE_RODATA("asm/nonmatchings/game/menu", D_80011464);

INCLUDE_RODATA("asm/nonmatchings/game/menu", D_80011474);

INCLUDE_RODATA("asm/nonmatchings/game/menu", D_8001149C);

/* Menu slot 0x08: base constructor with the menu description and ETC\ETCSE, then the save block. */
void Menu_Init(Menu *menu, DreamSys *dreamSys) {
    MenuScreen_GetVtbl()->init(menu, g_mainMenuDesc, "ETC\\ETCSE", 0);
    menu->vtbl = Menu_GetVtbl();
    menu->sound->vtbl->setOctave(menu->sound, -1);
    menu->dreamSys = dreamSys;
    menu->card = 0;
    menu->saveBlock = dreamSys->vtbl->getSaveBlock(dreamSys, &menu->saveSize);
    SaveMenu_SetTitleDay(dreamSys->vtbl->getDayNumber(dreamSys, 0));
    menu->vtbl->setMenu(menu, g_mainMenuDesc);
    menu->vtbl->reset(menu, dreamSys);
}

/* FLASHBACK is drawn only with an unlock score above 9,999,999 and one flashback kept. */
static void Menu_UpdateFlashbackItem(Menu *menu, MenuDef *desc, DreamSys *dreamSys) {
    SaveBlock *save = menu->saveBlock;
    s32 hidden = 1;
    if (save->unlockScore > 9999999) {
        hidden = save->flashbackCount == 0;
    }
    desc->hidden[MENU_ITEM_FLASHBACK] = hidden;
}

/* Writes the day number as three full-width digits into the card title. */
static void SaveMenu_SetTitleDay(s32 dayNumber) {
    Text_FormatNumber(g_titleDayDigits, dayNumber, 3, 0);
    ((CardTitle *)g_cardTitle)->day = *(SjisChar3 *)g_titleDayDigits;
}

/* Menu slot 0x0C: deletes the card and the file icon, then the base destructor. */
void Menu_Destroy(Menu *menu) {
    Card *card;
    MenuPicture *icon;

    card = menu->card;
    if (card != NULL) {
        card->vtbl->delete_(card);
        icon = menu->fileIcon;
        icon->vt->delete_(icon);
    }
    MenuScreen_GetVtbl()->destroy(menu);
}

/* Menu slot 0x38: messages from the card (class word & 0xF == 0xB) go to slot 0x138. */
void Menu_OnNotify(Menu *menu, s32 **sender, s32 message) {
    MenuScreen_GetVtbl()->onNotify(menu, sender, message);
    if ((**sender & 0xF) == 0xB) {
        menu->vtbl->onCardNotify(menu, sender, message);
    }
}

/* Menu slot 0x40 (reset): title picture, 10 s timeout, and flashback mode off. */
void Menu_Reset(Menu *menu) {
    DreamSys *dreamSys;

    menu->clearOnEnd = 0;
    menu->viewPacketCount = 0x190;
    menu->vtbl->setPicture(menu, "ETC\\TITLE.TIM", 0);
    menu->vtbl->setTimeout(menu, 10);
    dreamSys = menu->dreamSys;
    dreamSys->vtbl->setFlashbackMode(dreamSys, 0, 0);
}

/* Menu slot 0x50 (end): clears both 320 x 240 buffers to the end colour. */
void Menu_End(Menu *menu) {
    u32 i;

    for (i = 0; i < 2; i++) {
        menu->env->display->vtbl->clearImage(menu->env->display, menu->endColor, &g_menuFillRects[i]);
    }
}

/*
 * Menu slot 0x60 (setState, states SCREEN_* of scene.h): on 5 (active) reloads the save title
 * and SHAKE; on 10 (START pressed) closes the option list, selects START and confirms it.
 */
void Menu_SetState(Menu *menu, s32 state) {
    MenuScreen_GetVtbl()->setState(menu, state);
    if (state == 5) {
        menu->vtbl->refreshFromSave(menu, 0);
    }
    if (state == 0xA) {
        menu->vtbl->onCross(menu);
        menu->vtbl->selectItem(menu, menu->desc->initialItem, 1);
        menu->vtbl->onCircle(menu);
    }
}

/* Menu slot 0x90 (confirm): CIRCLE on an item (START closes through the base). */
void Menu_Confirm(Menu *menu) {
    void (*fn)(Menu *);
    DreamSys *dreamSys;

    MenuScreen_GetVtbl()->confirm(menu);
    switch (menu->selected) {
    case MENU_ITEM_FLASHBACK:
        dreamSys = menu->dreamSys;
        menu->result = 0;
        dreamSys->vtbl->setFlashbackMode(dreamSys, 0, 1);
        fn = menu->vtbl->close;
        break;
    case MENU_ITEM_SAVE:
        fn = menu->vtbl->save;
        break;
    case MENU_ITEM_LOAD:
        fn = menu->vtbl->load;
        break;
    case MENU_ITEM_GRAPH:
        menu->result = 2;
        fn = menu->vtbl->close;
        break;
    default:
        return;
    }
    fn(menu);
}

/* Menu slot 0x94 (close): closes the menu and stores the SHAKE choice in DreamSys. */
void Menu_Close(Menu *menu) {
    s32 shake;
    DreamSys *dreamSys;

    MenuScreen_GetVtbl()->close(menu);
    dreamSys = menu->dreamSys;
    shake = menu->optionSelected[MENU_ITEM_SHAKE];
    dreamSys->vtbl->swapShake(dreamSys, &shake);
}

/* Menu slot 0xD8 (setMenu): makes the title label; a game never saved gets a blank comment and no letter. */
void Menu_CreateTitleLabel(Menu *menu, MenuDef *desc) {
    s32 size;
    s32 label;
    s32 text;

    if (desc != NULL) {
        if (menu->dreamSys->vtbl->isNeverSaved(menu->dreamSys) != 0) {
            strcpy(g_cardTitle + 0x18, g_cardBlankComment);
            Card_SetTitleLetter(g_cardTitle, 0);
        }
        size = ((u32)strlen(g_cardTitle) >> 1) + 4;
        text = Heap_Alloc(size);
        Text_Decode((s8 *)text, (u8 *)g_cardTitle);
        label = Label_Create(desc->font, size, text);
        menu->titleLabel = (Label *)label;
        menu->titleLabel->shownCount = 8;
        menu->titleLabel->firstShown = 4;
        menu->titleLabel->gapAt = 9;
        Heap_Free(text);
    }
}

/* Menu slot 0xDC (freeMenu) */
void Menu_FreeMenu(Menu *menu) {
    Label *label;

    label = menu->titleLabel;
    label->vtbl->delete_(label);
    MenuScreen_GetVtbl()->freeMenu(menu);
}

/* Menu slot 0xE0 (showItems) */
void Menu_ShowItems(Menu *menu, s32 root) {
    Label *label;

    MenuScreen_GetVtbl()->showItems(menu, root);
    label = menu->titleLabel;
    label->vtbl->show(label, root, &D_8008A9B4);
}

/*
 * Menu slot 0xE4 (setItemsColor): the title label blinks. While the menu has focus one channel is lit at
 * 0x80, a different one each call (g_titleBlinkChannel); otherwise the label colour gets 0x80 more red
 * for 128 calls, then 0x80 more on the cycling channel (g_titleBlinkTick counts 0 to 256).
 */
void Menu_SetItemsColor(Menu *menu, MenuRgb *color) {
    MenuRgb blink;
    u8 *channels;

    channels = (u8 *)&blink;
    MenuScreen_GetVtbl()->setItemsColor(menu, color);
    if (menu->focus != 0) {
        blink.r = 0;
        blink.g = 0;
        blink.b = 0;
        channels[g_titleBlinkChannel] = 0x80;
    } else {
        blink = *color;
        if (g_titleBlinkTick < 0x80) {
            channels[0] += 0x80;
        } else {
            channels[g_titleBlinkChannel] += 0x80;
        }
    }
    if (++g_titleBlinkChannel >= 3) {
        g_titleBlinkChannel = 0;
    }
    if (++g_titleBlinkTick >= 0x101) {
        g_titleBlinkTick = 0;
    }
    menu->titleLabel->vtbl->setColor(menu->titleLabel, &blink);
}

/*
 * Menu slot 0x124: on opening (message 5) and after a load or a save, redraws the title
 * label and FLASHBACK, and sets the SHAKE item from DreamSys. The first swap trades an
 * unset value for the saved SHAKE, the second puts the saved value back.
 */
void Menu_RefreshFromSave(Menu *menu) {
    s32 shake;
    s32 text;
    s32 selected;

    selected = menu->selected;
    text = Heap_Alloc(menu->titleLabel->count);
    Text_Decode((s8 *)text, (u8 *)g_cardTitle);
    menu->titleLabel->vtbl->setText(menu->titleLabel, text);
    Heap_Free(text);
    Menu_UpdateFlashbackItem(menu, menu->desc, menu->dreamSys);
    menu->vtbl->showItems(menu, menu->root);
    menu->dreamSys->vtbl->swapShake(menu->dreamSys, &shake);
    menu->selected = MENU_ITEM_SHAKE;
    menu->vtbl->setState(menu, 0xB);
    menu->vtbl->selectOption(menu, shake, 1);
    menu->vtbl->setState(menu, 0xF);
    menu->vtbl->selectItem(menu, selected, 0);
    menu->dreamSys->vtbl->swapShake(menu->dreamSys, &shake);
}

/* Menu slot 0x128: makes the card (first time) and hands it the pad and the clock. */
void Menu_OpenCard(Menu *menu) {
    if (menu->card == NULL) {
        menu->fileIcon = (MenuPicture *)Tim_New((s32)"CARD\\FILEICN1.TIM");
        menu->card = Card_New(1, 0);
    }
    menu->card->vtbl->open(menu->card, g_cardFilePrefix, g_cardFileSuffixes, menu->env->pad, menu->clock, menu->root, menu->sound);
    menu->vtbl->watch(menu, menu->card);
    menu->vtbl->unwatch(menu, menu->env->pad);
    menu->vtbl->unwatch(menu, menu->clock);
}

/* Menu slot 0x12C: takes the pad and the clock back and closes the card. */
void Menu_CloseCard(Menu *menu) {
    menu->vtbl->watch(menu, menu->env->pad);
    menu->vtbl->watch(menu, menu->clock);
    menu->vtbl->unwatch(menu, menu->card);
    menu->card->vtbl->close(menu->card);
}

/* Menu slot 0x130: SHAKE into DreamSys, then saves the block; a game never saved gets a new file. */
void SaveMenu_Save(Menu *menu) {
    s32 shake;

    shake = menu->optionSelected[MENU_ITEM_SHAKE];
    menu->dreamSys->vtbl->swapShake(menu->dreamSys, &shake);
    menu->vtbl->openCard(menu);
    if (menu->dreamSys->vtbl->isNeverSaved(menu->dreamSys) != 0) {
        *(s8 *)g_cardFileName = 0;
    }
    menu->card->vtbl->save(menu->card, g_cardFileName, g_cardTitle, 0xD, 3, menu->fileIcon, menu->saveBlock, menu->saveSize);
}

/* Menu slot 0x134 */
void SaveMenu_Load(Menu *menu) {
    menu->vtbl->openCard(menu);
    menu->card->vtbl->load(menu->card, g_cardFileName, g_cardTitle, menu->saveBlock, menu->saveSize);
}

/* Menu slot 0x138: the card reached CARD_STATE_DONE or CARD_STATE_CLOSED. */
void Menu_OnCardNotify(Menu *menu, s32 **sender, s32 state) {
    DreamSys *dreamSys;

    if (state < CARD_STATE_CLOSED + 1) {
        if (state < CARD_STATE_DONE) {
            return;
        }
        menu->vtbl->closeCard(menu);
        if (state == CARD_STATE_DONE) {
            dreamSys = menu->dreamSys;
            dreamSys->vtbl->clearNeverSaved(dreamSys);
            menu->vtbl->refreshFromSave(menu, CARD_STATE_DONE);
        }
    }
}

static MenuVtbl *Menu_GetVtbl(void) {
    return (MenuVtbl *)g_menuVtbl;
}

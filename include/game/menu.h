#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "common.h"
#include "game/sound_bank.h"
#include "game/menu_screen.h"
#include "game/screen.h"
#include "game/label.h"
#include "game/dream_sys.h"

/*
 * The main menu (START, FLASHBACK, SAVE, LOAD, GRAPH, SHAKE) of src/game/menu.c. The memory card
 * object it drives is in card.h.
 *
 * Menu: class vtable g_menuVtbl 0x80086B60 (class word 0x1F130). It derives from the menu
 * screen class of src/game/menu_screen.c (vtable 0x8006E730, class word 0x130, returned by
 * MenuScreen_GetVtbl), whose slots it overrides at 0x08 to 0x0C, 0x38, 0x40, 0x50, 0x60, 0x90, 0x94
 * and 0xD8 to 0xE4, and adds 0x124 to 0x138. The glossary's Menu and SaveMenu are this one class.
 *
 * Class words: slot 0 of a vtable holds a class word; onNotify handlers tell senders apart with
 * (word & 0xF) or (word & 0xFF). Seen here: 2 the pad (sends the pad codes 0x17 CROSS and
 * 0x19 CIRCLE), 5 the clock, 0xB the card, 0x10 the comment keyboard (vtable 0x80086ED0,
 * made by CommentObject_New), 0x20 the file chooser (made by StringList_New).
 */

/* Menu items, in the order of the label table 0x80086CF8 (menu description +0x1C). */
#define MENU_ITEM_START 0
#define MENU_ITEM_FLASHBACK 1
#define MENU_ITEM_SAVE 2
#define MENU_ITEM_LOAD 3
#define MENU_ITEM_GRAPH 4
#define MENU_ITEM_SHAKE 5

typedef struct MenuRgb {
    s8 r, g, b;
} MenuRgb;

/* The two rectangles g_menuFillRects: {x and y packed, width, height}, 320 x 240 at y 0 and 240. */
typedef struct MenuFillRect {
    s32 xy;
    s32 w;
    s32 h;
} MenuFillRect;

/* A picture object (Tim_New); slot 0x4 deletes it. */
typedef struct MenuPictureVtbl {
    u8 pad_00[0x4];
    void (*delete_)(void *self);
} MenuPictureVtbl;

typedef struct MenuPicture {
    MenuPictureVtbl *vt;
    u8 pad_04[0x10 - 0x04];
    struct CardIconTim *tim; /* 0x10 the TIM file: palette at +0x14, 16x16 4-bit frames from +0x40 (card.c) */
} MenuPicture;

struct Menu;

struct Card;

/*
 * g_menuVtbl, and the base class vtable 0x8006E730 (same layout up to 0x120; the base init
 * takes four arguments, the menu's two, so init is unprototyped). Slots named after what
 * the base class or src/game/menu.c stores there.
 */
typedef struct MenuVtbl {
    s32 classWord;                                       /* 0x000 0x1F130 */
    void *(*delete_)();                                  /* 0x004 Object_Delete */
    void (*init)();                                      /* 0x008 Menu_Init */
    void (*destroy)(struct Menu *);                      /* 0x00C Menu_Destroy */
    void (*watch)();                                     /* 0x010 Object_Watch */
    void (*unwatch)();                                   /* 0x014 Object_Unwatch */
    u8 pad_18[0x38 - 0x18];
    void (*onNotify)(struct Menu *, s32 **, s32);        /* 0x038 Menu_OnNotify */
    u8 pad_3C[0x40 - 0x3C];
    void (*reset)(struct Menu *, void *);                /* 0x040 Menu_Reset */
    u8 pad_44[0x60 - 0x44];
    void (*setState)(struct Menu *, s32);                /* 0x060 Menu_SetState (SCREEN_* of screen.h) */
    u8 pad_64[0x6C - 0x64];
    void (*setTimeout)(struct Menu *, s32);              /* 0x06C MenuScreen_SetTimeout */
    u8 pad_70[0x78 - 0x70];
    void (*onCircle)(struct Menu *);                     /* 0x078 MenuScreen_OnCircle */
    void (*onCross)(struct Menu *);                      /* 0x07C MenuScreen_OnCross */
    u8 pad_80[0x90 - 0x80];
    void (*confirm)(struct Menu *);                      /* 0x090 Menu_Confirm */
    void (*close)(struct Menu *);                        /* 0x094 Menu_Close */
    u8 pad_98[0xD4 - 0x98];
    void (*setPicture)(struct Menu *, char *, s32);      /* 0x0D4 MenuScreen_SetPicture */
    void (*setMenu)(struct Menu *, MenuDef *);          /* 0x0D8 Menu_CreateTitleLabel */
    void (*freeMenu)(struct Menu *);                     /* 0x0DC Menu_FreeMenu */
    void (*showItems)(struct Menu *, s32);               /* 0x0E0 Menu_ShowItems (menu, root) */
    void (*setItemsColor)(struct Menu *, MenuRgb *);     /* 0x0E4 Menu_SetItemsColor */
    u8 pad_E8[0xF0 - 0xE8];
    void (*selectItem)(struct Menu *, s32, s32);         /* 0x0F0 MenuScreen_SelectItem (menu, item, playSound) */
    u8 pad_F4[0x11C - 0xF4];
    void (*selectOption)(struct Menu *, s32, s32);       /* 0x11C MenuScreen_SelectOption (menu, option, playSound) */
    u8 pad_120[0x124 - 0x120];
    void (*refreshFromSave)(struct Menu *, s32);         /* 0x124 Menu_RefreshFromSave */
    void (*openCard)(struct Menu *);                     /* 0x128 Menu_OpenCard */
    void (*closeCard)(struct Menu *);                    /* 0x12C Menu_CloseCard */
    void (*save)(struct Menu *);                         /* 0x130 Menu_Save */
    void (*load)(struct Menu *);                         /* 0x134 Menu_Load */
    void (*onCardNotify)(struct Menu *, s32 **, s32);    /* 0x138 Menu_OnCardNotify */
} MenuVtbl;

/* The main menu object. Fields below 0xA4 are MenuScreen's (include/game/menu_screen.h, src/game/menu_screen.c). */
typedef struct Menu {
    MenuVtbl *vtbl;
    u8 pad_04[0x0C - 0x04];
    ScreenEnv *env;       /* 0x0C display and pad (screen.h) */
    void *clock;          /* 0x10 class 5, handed to the card with env->pad */
    s32 root;             /* 0x14 the scene node the texts are shown under */
    u8 pad_18[0x2C - 0x18];
    s32 viewPacketCount;  /* 0x2C 0x190 here, 300 in the base reset */
    u8 pad_30[0x34 - 0x30];
    s32 clearOnEnd;       /* 0x34 the base end clears the screen when set; 0 here */
    s32 result;           /* 0x38 what the screen returns: 0 START or FLASHBACK, 2 GRAPH */
    s32 focus;            /* 0x3C 0 none, 1 items, 2 option list (menu_screen.h MENU_FOCUS_*) */
    u8 pad_40[0x48 - 0x40];
    SoundBank *sound;     /* 0x48 ETC\ETCSE, the menu sound effects */
    MenuDef *desc;        /* 0x4C g_mainMenuDesc 0x80086D44 (menu_screen.h MenuDef): ETC\FONTICON.TIM; START, FLASHBACK, SAVE, LOAD, GRAPH, SHAKE */
    u8 pad_50[0x58 - 0x50];
    s32 selected;         /* 0x58 selected item, MENU_ITEM_* */
    u8 pad_5C[0x60 - 0x5C];
    s32 *optionSelected;  /* 0x60 chosen option per item (SHAKE: 0 Off, 1 On) */
    u8 pad_64[0x93 - 0x64];
    u8 endColor[3];       /* 0x93 */
    u8 pad_96[0xA4 - 0x96];
    DreamSys *dreamSys;   /* 0xA4 */
    MenuPicture *fileIcon; /* 0xA8 CARD\FILEICN1.TIM, the icon of the save file */
    struct Card *card;    /* 0xAC made on the first SAVE or LOAD */
    Label *titleLabel;    /* 0xB0 the save title drawn on the menu (label.h Label) */
    u8 pad_B4[0xBC - 0xB4];
    SaveBlock *saveBlock; /* 0xBC DreamSys_GetSaveBlock */
    s32 saveSize;         /* 0xC0 0x700 */
} Menu;

/* Functions of src/game/menu.c that other files call or reference (docs/naming.md, Prototypes) */
Screen *Menu_New(DreamSys *dreamSys);

#endif

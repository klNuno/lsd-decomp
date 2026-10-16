#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "common.h"
#include "game/heap.h"
#include "game/dreamsys.h"
#include "game/scene.h"

/*
 * The main menu (START, FLASHBACK, SAVE, LOAD, GRAPH, SHAKE) and the memory card object it
 * drives, both from src/game/menu.c and src/game/card.c.
 *
 * Menu: class vtable g_menuVtbl 0x80086B60 (class word 0x1F130). It derives from the menu
 * screen class of src/game/menu_screen.c (vtable 0x8006E730, class word 0x130, returned by
 * MenuScreen_GetVtbl), whose slots it overrides at 0x08 to 0x0C, 0x38, 0x40, 0x50, 0x60, 0x90, 0x94
 * and 0xD8 to 0xE4, and adds 0x124 to 0x138. The glossary's Menu and SaveMenu are this one class.
 *
 * Card: class vtable g_cardVtbl 0x80086DC4 (class word 0xB), 0x84 bytes (Card_New). It wraps
 * the PSY-Q card BIOS (InitCARD, _card_info, _card_load, the "bu00:" and "bu10:" devices) and
 * runs the save and load dialogs as a state machine (CARD_STATE_*): each state shows the
 * picture CARD\<name>.TIM named by g_cardMessageNames[state].
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

/* Card states (Card.state); 2 to 16 index g_cardMessageNames, the picture shown. */
#define CARD_STATE_IDLE 0
#define CARD_STATE_NO_CARD 2          /* NOCONECT: no answer from the card */
#define CARD_STATE_ERROR 3            /* ERROR */
#define CARD_STATE_CHANGED 4          /* CHANGE: a new card was put in */
#define CARD_STATE_UNFORMATTED_LOAD 5 /* UNFORM1 */
#define CARD_STATE_UNFORMATTED_SAVE 6 /* UNFORM2: CIRCLE formats */
#define CARD_STATE_FORMATTING 7       /* FORMING */
#define CARD_STATE_FORMAT_ERROR 8     /* FORMERR */
#define CARD_STATE_FULL 9             /* SAVEEMPT: no room for a new file */
#define CARD_STATE_OVERWRITE 10       /* SAVEWAR: the file exists, CIRCLE overwrites */
#define CARD_STATE_SAVING 11          /* SAVING */
#define CARD_STATE_SAVE_ERROR 12      /* SAVEERR */
#define CARD_STATE_NOT_FOUND 13       /* NOTFOUND: no save file on the card */
#define CARD_STATE_LOAD_CONFIRM 14    /* LOADWAR: CIRCLE loads the chosen file */
#define CARD_STATE_LOADING 15         /* LOADING */
#define CARD_STATE_LOAD_ERROR 16      /* LOADERR */
#define CARD_STATE_KEYBOARD 17        /* the comment keyboard is open */
#define CARD_STATE_CHOOSE 18          /* the file chooser is open */
#define CARD_STATE_DO_FORMAT 19       /* 7 clock ticks after FORMING */
#define CARD_STATE_DO_SAVE 20         /* 7 clock ticks after SAVING */
#define CARD_STATE_DO_LOAD 21         /* 7 clock ticks after LOADING */
#define CARD_STATE_DONE 22            /* success: told to the menu, then back to idle */
#define CARD_STATE_CLOSED 23          /* cancelled or failed: back to idle */

/* Card.operation */
#define CARD_OP_NONE 0
#define CARD_OP_LOAD 1
#define CARD_OP_SAVE 2

/* One full-width (Shift-JIS) character of the card title. */
typedef struct SjisChar {
    s8 hi;
    s8 lo;
} SjisChar;

typedef struct SjisChar3 {
    SjisChar c[3];
} SjisChar3;

/* Title +0x06: the save letter between two spaces, then "Ｄａｙ". */
typedef struct CardTitleMark {
    SjisChar3 letter; /* c[1] is the letter of the file: ａ for -01 up to ｏ for -15 */
    SjisChar3 dayWord;
} CardTitleMark;

/* The card title g_cardTitle (string 0x8001149C): "ＬＳＤ　ａ　Ｄａｙ００１" then the comment. */
typedef struct CardTitle {
    SjisChar3 game;      /* 0x00 "ＬＳＤ" */
    CardTitleMark mark;  /* 0x06 */
    SjisChar3 day;       /* 0x12 day number, three digits (SaveMenu_SetTitleDay) */
    SjisChar comment[19]; /* 0x18 typed on the comment keyboard, blank for a new game */
} CardTitle;

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
    u8 *tim;         /* 0x10 the TIM file: palette at +0x14, 16x16 4-bit frames from +0x40 */
} MenuPicture;

struct Menu;
struct Card;
struct CardDialog;
struct CardMessage;

/*
 * g_menuVtbl, and the base class vtable 0x8006E730 (same layout up to 0x120; the base init
 * takes four arguments, the menu's two, so init is unprototyped). Slots named after what
 * the base class or this unit stores there.
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
    void (*setState)(struct Menu *, s32);                /* 0x060 Menu_SetState (SCREEN_* of scene.h) */
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
    void (*save)(struct Menu *);                         /* 0x130 SaveMenu_Save */
    void (*load)(struct Menu *);                         /* 0x134 SaveMenu_Load */
    void (*onCardNotify)(struct Menu *, s32 **, s32);    /* 0x138 Menu_OnCardNotify */
} MenuVtbl;

/* The main menu object. Fields below 0xA4 are MenuScreen's (include/game/scene.h, src/game/menu_screen.c). */
typedef struct Menu {
    MenuVtbl *vtbl;
    u8 pad_04[0x0C - 0x04];
    ScreenEnv *env;       /* 0x0C display and pad (scene.h) */
    void *clock;          /* 0x10 class 5, handed to the card with env->pad */
    s32 root;             /* 0x14 the scene node the texts are shown under */
    u8 pad_18[0x2C - 0x18];
    s32 viewPacketCount;  /* 0x2C 0x190 here, 300 in the base reset */
    u8 pad_30[0x34 - 0x30];
    s32 clearOnEnd;       /* 0x34 the base end clears the screen when set; 0 here */
    s32 result;           /* 0x38 what the screen returns: 0 START or FLASHBACK, 2 GRAPH */
    s32 focus;            /* 0x3C 0 none, 1 items, 2 option list (scene.h MENU_FOCUS_*) */
    u8 pad_40[0x48 - 0x40];
    SoundBank *sound;     /* 0x48 ETC\ETCSE, the menu sound effects */
    MenuDef *desc;        /* 0x4C g_mainMenuDesc 0x80086D44 (scene.h MenuDef): ETC\FONTICON.TIM; START, FLASHBACK, SAVE, LOAD, GRAPH, SHAKE */
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
    Label *titleLabel;    /* 0xB0 the save title drawn on the menu (scene.h Label) */
    u8 pad_B4[0xBC - 0xB4];
    SaveBlock *saveBlock; /* 0xBC DreamSys_GetSaveBlock */
    s32 saveSize;         /* 0xC0 0x700 */
} Menu;

/* The keyboard (class 0x10) and the file chooser (class 0x20) the card opens. */
typedef struct CardDialogVtbl {
    u8 pad_00[0x4];
    void (*delete_)(struct CardDialog *);
    u8 pad_08[0x44 - 0x08];
    void (*unk44)(struct CardDialog *, s32);
    void (*unk48)(struct CardDialog *);
    void (*unk4C)(struct CardDialog *, void *, void *, void *);
    void (*unk50)(struct CardDialog *);
    u8 pad_54[0x9C - 0x54];
    s32 (*getChoice)(struct CardDialog *);               /* 0x9C chooser: the file picked */
} CardDialogVtbl;

typedef struct CardDialog {
    CardDialogVtbl *vt;
} CardDialog;

/* The picture of the current message (CARD\<name>.TIM). */
typedef struct CardMessageVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(struct CardMessage *);
    u8 pad_08[0x4C - 0x08];
    void (*attach)(struct CardMessage *, s32, s32 *); /* 0x4C ScreenSprite_Attach (sprite, parent, 2D position) */
    u8 pad_50[0x78 - 0x50];
    void (*unk78)(struct CardMessage *);
} CardMessageVtbl;

typedef struct CardMessage {
    CardMessageVtbl *vt;
} CardMessage;

/* g_cardVtbl. Slots 0x1C to 0x34 are the Object ones. */
typedef struct CardVtbl {
    s32 classWord;                                                      /* 0x00 0xB */
    void *(*delete_)(struct Card *);                                    /* 0x04 Object_Delete */
    void (*init)(struct Card *, s32, s32);                              /* 0x08 Card_Init */
    void (*destroy)(struct Card *);                                     /* 0x0C Card_Destroy */
    void (*watch)(struct Card *, void *);                               /* 0x10 Card_Watch */
    void (*unwatch)(struct Card *, void *);                             /* 0x14 Card_Unwatch */
    void (*unwatchAll)(struct Card *);                                  /* 0x18 Card_UnwatchAll */
    u8 pad_1C[0x30 - 0x1C];
    void (*notify)(struct Card *, s32);                                 /* 0x30 Object_Notify */
    u8 pad_34[0x38 - 0x34];
    void (*onNotify)(struct Card *, s32 **, s32);                       /* 0x38 Card_OnNotify */
    u8 pad_3C[0x40 - 0x3C];
    void (*setPort)(struct Card *, s32);                                /* 0x40 Card_SetPort */
    s32 (*openEvents)(struct Card *);                                   /* 0x44 Card_OpenEvents */
    s32 (*closeEvents)(struct Card *);                                  /* 0x48 Card_CloseEvents */
    s32 (*probe)(struct Card *, s32 *, s32 *, s32 *);                   /* 0x4C Card_Probe */
    s32 (*format)(struct Card *);                                       /* 0x50 Card_Format */
    s32 (*findFile)(struct Card *, s32, char *);                        /* 0x54 Card_FindFile */
    char *(*findFreeName)(struct Card *, char *, char *, char **);      /* 0x58 Card_FindFreeName */
    s32 (*listFiles)(struct Card *, char **, char **, char *, char **); /* 0x5C Card_ListFiles */
    s32 (*hasSpace)(struct Card *, s32, s32);                           /* 0x60 Card_HasSpace */
    s32 (*readFile)(struct Card *, char *, void *, s32);                /* 0x64 Card_ReadFile */
    s32 (*writeFile)(struct Card *, char *, char *, u8, MenuPicture *, void *, s32); /* 0x68 Card_WriteFile */
    void (*open)(struct Card *, char *, char **, void *, void *, s32, SoundBank *); /* 0x6C Card_Open */
    void (*close)(struct Card *);                                       /* 0x70 Card_Close */
    void (*load)(struct Card *, char *, char *, void *, s32);           /* 0x74 Card_Load */
    void (*save)(struct Card *, char *, char *, s32, s32, MenuPicture *, void *, s32); /* 0x78 Card_Save */
    void (*setState)(struct Card *, s32);                               /* 0x7C Card_SetState */
    void (*showMessage)(struct Card *, s32);                            /* 0x80 Card_ShowMessage */
    void (*hideMessage)(struct Card *);                                 /* 0x84 Card_HideMessage */
    void (*onPad)(struct Card *, void *, s32);                          /* 0x88 Card_OnPad */
    void (*playSound)(struct Card *, s32);                              /* 0x8C Card_PlaySound */
    void (*onConfirm)(struct Card *);                                   /* 0x90 Card_OnConfirm */
    void (*onCancel)(struct Card *);                                    /* 0x94 Card_OnCancel */
    void (*onTick)(struct Card *, void *, s32);                         /* 0x98 Card_OnTick */
    void (*openKeyboard)(struct Card *);                                /* 0x9C Card_OpenKeyboard */
    void (*closeKeyboard)(struct Card *);                               /* 0xA0 Card_CloseKeyboard */
    void (*onKeyboard)(struct Card *, void *, s32);                     /* 0xA4 Card_OnKeyboard */
    void (*openChooser)(struct Card *);                                 /* 0xA8 Card_OpenChooser */
    void (*closeChooser)(struct Card *);                                /* 0xAC Card_CloseChooser */
    void (*onChooser)(struct Card *, CardDialog *, s32);                /* 0xB0 Card_OnChooser */
} CardVtbl;

/* The memory card object, 0x84 bytes. */
typedef struct Card {
    CardVtbl *vtbl;
    ListNode *watched;      /* 0x04 Object */
    ListNode *watchers;     /* 0x08 */
    s32 port;               /* 0x0C 0 "bu00:", else "bu10:" */
    s32 channel;            /* 0x10 port << 4, for _card_info and _card_load */
    s32 events[4];          /* 0x14 card BIOS events, specs g_cardEventSpecs */
    s32 operation;          /* 0x24 CARD_OP_* */
    s32 state;              /* 0x28 CARD_STATE_* */
    s32 fileCount;          /* 0x2C save files found by a load */
    char *prefix;           /* 0x30 "BISLPS-01556" */
    char **suffixes;        /* 0x34 g_cardFileSuffixes "-01" to "-15", NULL ended */
    char **titles;          /* 0x38 15 title buffers of 0x41 bytes, one per file found */
    char **foundSuffixes;   /* 0x3C the suffix of each file found */
    char *fileName;         /* 0x40 */
    char *title;            /* 0x44 */
    s32 unk48;              /* 0x48 0xD from SaveMenu_Save; the keyboard gets title + 2 x this */
    u8 iconFrames;          /* 0x4C 3 */
    MenuPicture *icon;      /* 0x50 the file icon, CARD\FILEICN1.TIM */
    void *data;             /* 0x54 */
    s32 size;               /* 0x58 */
    s32 ticks;              /* 0x5C counted by Card_OnTick */
    void *pad;              /* 0x60 class 2, the menu's env->pad */
    void *clock;            /* 0x64 class 5, the menu's clock */
    s32 root;               /* 0x68 the menu's root, where the pictures and dialogs are shown */
    SoundBank *sound;       /* 0x6C */
    CardMessage *message;   /* 0x70 */
    s32 ownsDialog;         /* 0x74 the keyboard or chooser was made here and is deleted on close */
    CardDialog *keyboard;   /* 0x78 class 0x10 */
    CardDialog *chooser;    /* 0x7C class 0x20 */
    s32 choice;             /* 0x80 index of the file picked in the chooser */
} Card;

#endif

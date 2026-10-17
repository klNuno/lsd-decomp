#ifndef GAME_CARD_H
#define GAME_CARD_H

#include "common.h"
#include "game/heap.h"
#include "game/sound_bank.h"
#include "game/text.h"
#include "game/menu.h"

/*
 * Card (src/game/card.c): class vtable g_cardVtbl 0x80086DC4 (class word 0xB), 0x84 bytes (Card_New).
 * It wraps the PSY-Q card BIOS (InitCARD, _card_info, _card_load, the "bu00:" and "bu10:" devices)
 * and runs the save and load dialogs of the main menu (menu.h) as a state machine (CARD_STATE_*):
 * each state shows the picture CARD\<name>.TIM named by g_cardMessageNames[state].
 */

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

/* Title +0x06: the save letter between two spaces, then "Ｄａｙ". */
typedef struct CardTitleMark {
    SjisChar3 letter; /* c[1] is the letter of the file: ａ for -01 up to ｏ for -15 */
    SjisChar3 dayWord;
} CardTitleMark;

/* The card title g_cardTitle (string 0x8001149C): "ＬＳＤ　ａ　Ｄａｙ００１" then the comment. */
typedef struct CardTitle {
    SjisChar3 game;      /* 0x00 "ＬＳＤ" */
    CardTitleMark mark;  /* 0x06 */
    SjisChar3 day;       /* 0x12 day number, three digits (Menu_SetTitleDay) */
    SjisChar comment[19]; /* 0x18 typed on the comment keyboard, blank for a new game */
} CardTitle;

struct CardDialog;

struct CardMessage;

/* The keyboard (class 0x10) and the file chooser (class 0x20) the card opens. */
typedef struct CardDialogVtbl {
    u8 pad_00[0x4];
    void (*delete_)(struct CardDialog *);
    u8 pad_08[0x44 - 0x08];
    void (*open)(struct CardDialog *, s32);
    void (*close)(struct CardDialog *);
    void (*watchPair)(struct CardDialog *, void *, void *, void *);
    void (*unwatchPair)(struct CardDialog *);
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
    void (*setZSort)(struct CardMessage *);
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
    s32 (*findFile)(struct Card *, char *, char *);                     /* 0x54 Card_FindFile */
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
    void (*onChooser)(struct Card *, void *, s32);                      /* 0xB0 Card_OnChooser (card, the chooser, message) */
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
    s32 commentStart;              /* 0x48 0xD from Menu_Save; the keyboard gets title + 2 x this */
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

/* Functions of src/game/card.c that other files call or reference (docs/naming.md, Prototypes) */
Card *Card_New(s32 sharePad, s32 port);
void Card_SetTitleLetter(CardTitle *title, u8 *fileName);

#endif

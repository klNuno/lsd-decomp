#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "common.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"
#include "game/pad.h"
#include "game/clock.h"

/*
 * Screen (src/game/screen.c): vtable g_screenVtbl (tag 0x30), derived from Object. A modal state
 * machine: run (slot 0x44) watches the display, the pad and the clock of its ScreenEnv, then state 2
 * starts the display's frame loop, which only returns when state 3 stops it. MenuScreen
 * (menu_screen.h) derives from it, and VideoScreen (video_screen.h) from MenuScreen.
 *
 * The low 4 bits of a vtable's first word give the sender type Screen_OnNotify and View_OnNotify
 * dispatch on: 1 display (Display_GetVtbl class), 2 pad (vtable 0x8006D370), 4 scene node
 * (the SceneNode_New class and its children), 5 clock (vtable 0x8006EF50).
 * Slots are left unprototyped, as in heap.h: the code calls some with fewer arguments.
 */

/*
 * What every screen runs with: the scene keeps it at +0x1C (App_Start in src/game/app.c
 * builds it with the display and the pad, the other three 0). A NULL clock, root or view makes the screen create
 * its own for the run and delete it after.
 */
typedef struct ScreenEnv {
    Display *display;
    Pad *pad;
    Clock *clock;            /* default Clock_Create */
    SceneNode *root;         /* default RootNode_Create: a RootNode (vtable 0x8006EFAC, src/game/root_node.c), lights at +0x44, ambient color at +0x50 */
    struct View *view;       /* default View_New, a new View */
} ScreenEnv;

/* The states Screen_SetState and MenuScreen_SetState handle. */
#define SCREEN_START 2          /* starts the display loop */
#define SCREEN_STOP 3           /* stops it: run returns */
#define SCREEN_FADING_IN 4
#define SCREEN_ACTIVE 5         /* faded in, the pad works */
#define SCREEN_TIMEOUT 6
#define SCREEN_CLOSING 7        /* fading out */
#define SCREEN_CLOSED 8
#define SCREEN_ITEM_MOVED 9
#define SCREEN_START_PRESSED 10
#define SCREEN_CONFIRM 11       /* CIRCLE on an item */
#define SCREEN_OPTIONS_OPENED 14
#define SCREEN_OPTION_CONFIRM 15 /* CIRCLE in an option list */
#define SCREEN_OPTION_ACCEPTED 16
#define SCREEN_OPTION_CANCEL 17 /* CROSS in an option list */
#define SCREEN_SKIP 0x12        /* CIRCLE on a skippable video */

/* Every screen vtable: Screen up to 0x68, MenuScreen up to 0x120, VideoScreen up to 0x134. */
typedef struct ScreenVtbl {
    s32 classWord;               /* 0x000 0x30, 0x130, 0x1130 */
    void *(*delete_)();         /* 0x004 Object_Delete */
    void (*init)();             /* 0x008 */
    void (*destroy)();          /* 0x00C */
    void (*watch)();            /* 0x010 Object_Watch */
    void (*unwatch)();          /* 0x014 */
    void (*unwatchAll)();       /* 0x018 */
    void (*nextWatched)();      /* 0x01C */
    void (*addWatcher)();       /* 0x020 */
    void (*removeWatcher)();    /* 0x024 */
    void (*freeWatchers)();     /* 0x028 */
    void (*nextWatcher)();      /* 0x02C */
    void (*notify)();           /* 0x030 Object_Notify */
    void (*unk34)();            /* 0x034 */
    void (*onNotify)();         /* 0x038 Screen_OnNotify */
    void (*unk3C)();            /* 0x03C 0 */
    void (*reset)();            /* 0x040 */
    s32 (*run)();               /* 0x044 (screen, env, ...): returns the result */
    void (*finish)();           /* 0x048 */
    void (*begin)();            /* 0x04C */
    void (*end)();              /* 0x050 */
    void (*onDisplay)();        /* 0x054 sender type 1 */
    void (*onPad)();            /* 0x058 sender type 2 (screen, pad, code) */
    void (*onClock)();          /* 0x05C sender type 5 */
    void (*setState)();         /* 0x060 */
    void (*startLoop)();        /* 0x064 */
    void (*stopLoop)();         /* 0x068 */
    /* MenuScreen */
    void (*setTimeout)();       /* 0x06C seconds, negative: none */
    void (*playSound)();        /* 0x070 */
    void (*onStart)();          /* 0x074 */
    void (*onCircle)();         /* 0x078 */
    void (*onCross)();          /* 0x07C */
    void (*onUp)();             /* 0x080 */
    void (*onDown)();           /* 0x084 */
    void (*unk88)();            /* 0x088 */
    void (*unk8C)();            /* 0x08C */
    void (*confirm)();          /* 0x090 */
    void (*close)();            /* 0x094 */
    void (*setOnClose)();       /* 0x098 (screen, callback, argument) */
    void (*setFadeIn)();        /* 0x09C */
    void (*setFadeOut)();       /* 0x0A0 */
    void (*setColors)();        /* 0x0A4 */
    void (*setFadeSpeed)();     /* 0x0A8 */
    s32 (*fadeIn)();            /* 0x0AC */
    s32 (*fadeInStep)();        /* 0x0B0 */
    void (*unkB4)();            /* 0x0B4 0 */
    void (*unkB8)();            /* 0x0B8 0 */
    void (*unkBC)();            /* 0x0BC 0 */
    s32 (*fadeOut)();           /* 0x0C0 */
    s32 (*fadeOutStep)();       /* 0x0C4 */
    void (*unkC8)();            /* 0x0C8 0 */
    void (*unkCC)();            /* 0x0CC 0 */
    void (*unkD0)();            /* 0x0D0 0 */
    void (*setPicture)();       /* 0x0D4 (screen, path, image) */
    void (*setMenu)();          /* 0x0D8 */
    void (*freeMenu)();         /* 0x0DC */
    void (*showItems)();        /* 0x0E0 (screen, root) */
    void (*setItemsColor)();    /* 0x0E4 */
    void (*nextItem)();         /* 0x0E8 */
    void (*prevItem)();         /* 0x0EC */
    void (*selectItem)();       /* 0x0F0 (screen, index, playSound) */
    s32 (*getSelectedItem)();   /* 0x0F4 */
    void (*makeOptions)();      /* 0x0F8 */
    void (*freeOptions)();      /* 0x0FC */
    void (*showOptions)();      /* 0x100 (screen, root, open) */
    void (*setOptionsColor)();  /* 0x104 */
    void (*openOptions)();      /* 0x108 */
    void (*acceptOption)();     /* 0x10C */
    void (*cancelOptions)();    /* 0x110 */
    void (*nextOption)();       /* 0x114 */
    void (*prevOption)();       /* 0x118 */
    void (*selectOption)();     /* 0x11C (screen, index, playSound) */
    s32 (*getSelectedOption)(); /* 0x120 */
    /* VideoScreen */
    void (*setMovieRepeat)();   /* 0x124 */
    void (*setMovieLoops)();    /* 0x128 */
    void (*setSkippable)();     /* 0x12C */
    void (*setUnkD0)();         /* 0x130 */
    void (*setUnkD4)();         /* 0x134 */
} ScreenVtbl;

typedef struct Screen {
    ScreenVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    ScreenEnv *env;         /* 0x0C */
    Clock *clock;           /* 0x10 env->clock or its own */
    SceneNode *root;        /* 0x14 env->root or its own; menu texts hang from it */
    struct View *view;      /* 0x18 env->view or its own */
    s32 ticks;              /* 0x1C clock messages since the last state change */
    s32 state;              /* 0x20 SCREEN_* */
    s32 unk24;              /* 0x24 run's third argument: when set, run only watches and returns */
} Screen;

/* One object of the classes the menu uses (src/game/fade.c, src/game/box.c and src/game/label.c): texts, the option box, a 2D overlay. */
typedef struct WidgetVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();      /* 0x04 */
    u8 pad_08[0x4C - 0x08];
    void (*show)();          /* 0x4C (widget, root, position): SceneNode_Attach and its overrides */
    void (*hide)();          /* 0x50 */
    u8 pad_54[0x60 - 0x54];
    void (*setVisible)();    /* 0x60 */
    void (*setSemiTrans)();  /* 0x64 Box and Fade */
    void (*setBlendMode)();  /* 0x68 Box and Fade */
    u8 pad_6C[0x78 - 0x6C];
    void (*unk78)();         /* 0x78 one argument (src/game/comment_object.c) */
    u8 pad_7C[0x80 - 0x7C];
    void (*unk80)();         /* 0x80 (widget, value, 0x60, 0x60) from the keyboard's SetBoxValue */
    u8 pad_84[0xB8 - 0x84];
    void (*setColor)();      /* 0xB8 */
    void (*setPosition)();   /* 0xBC */
    void (*setSize)();       /* 0xC0 */
    void (*extra)();         /* 0xC4 per class: Box_ShowAbsolute on boxes, the character on glyphs and labels */
} WidgetVtbl;

typedef struct Widget {
    WidgetVtbl *vtbl;
} Widget;

/* Functions of src/game/screen.c that other files call or reference (docs/naming.md, Prototypes) */
void Screen_OnNotify(Screen *screen, Object *sender, s32 message);
void Screen_Finish(Screen *screen);
void Screen_OnDisplay(Screen *screen, Display *display, s32 message);
void Screen_StartLoop(Screen *screen);
void Screen_StopLoop(Screen *screen);

#endif

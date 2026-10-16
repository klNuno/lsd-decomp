#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "common.h"
#include "game/heap.h"
#include "game/gs.h"

/*
 * Screens and the view: the classes of src/game/8003B854.c, each derived from Object.
 *
 *   Screen       vtable g_screenVtbl (tag 0x30), base only. A modal state machine: run (slot 0x44)
 *                watches the display, the pad and the clock of its ScreenEnv, then state 2 starts
 *                the display's frame loop, which only returns when state 3 stops it.
 *   MenuScreen   vtable g_menuScreenVtbl (tag 0x130), 0xA4 bytes, made by MenuScreen_New. Screen plus a
 *                sound bank, a picture, fade in and fade out, a timeout and a menu of items with
 *                option lists. The logos and the special-day pictures use it as is
 *                (src/game/80025F7C.c); the main menu (src/game/8004D578.c) derives from it.
 *   VideoScreen  vtable g_videoScreenVtbl (tag 0x1130), 0xDC bytes, made by VideoScreen_New: a MenuScreen
 *                that plays one STR video (docs/discoveries.md, special days).
 *   View         vtable g_viewVtbl (tag 7), 0xBC bytes, made by View_New: the GsRVIEW2,
 *                two ordering tables with their packet areas, fog, light mode and clear color.
 *
 * The low 4 bits of a vtable's first word give the sender type Screen_OnNotify and View_OnNotify
 * dispatch on: 1 display (Display_GetVtbl class), 2 pad (vtable 0x8006D370), 4 scene node
 * (the SceneNode_New class and its children), 5 clock (vtable 0x8006EF50).
 * Slots are left unprototyped, as in heap.h: the code calls some with fewer arguments.
 */

/* A pair of words copied whole: a screen position, a size, the view's screen size. */
typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

/* Three words copied whole: GsRVIEW2 viewpoint or reference point. */
typedef struct ScreenVec {
    s32 x;
    s32 y;
    s32 z;
} ScreenVec;

/* A VRAM rect as the display reads it (x, y, w as s16 at 0, 2, 4; h at 8), copied whole. */
typedef struct ScreenRect {
    s16 x;
    s16 y;
    s32 w;
    s32 h;
} ScreenRect;

/* A width and a height. */
typedef struct ScreenSize {
    s32 w;
    s32 h;
} ScreenSize;

/* A {numerator, denominator} pair: scene node rotations in degrees and scales (Fraction_ToFixed). */
typedef struct Fraction {
    s16 num;
    s16 den;
} Fraction;

/*
 * Objects of other units a screen talks to, with the slots this unit calls.
 */

/* The display (Display_GetVtbl 0x8006C070, src/game/800206E0.c, sender type 1): sends message 2 once per frame while its loop runs. */
typedef struct DisplayVtbl {
    ObjectVtbl base;
    s32 unk3C;                /* 0x3C 0 */
    void (*reset)();          /* 0x40 Display_Reset: vsync mode 3, transfers synced, no callback */
    void (*initGraph)();      /* 0x44 Display_InitGraph (display, size, vramMode) */
    void (*startLoop)();      /* 0x48 Display_StartLoop */
    void (*stopLoop)();       /* 0x4C Display_StopLoop */
    void (*swapBuffers)();    /* 0x50 Display_SwapBuffers */
    s32 (*getActiveBuffer)(); /* 0x54 Display_GetActiveBuffer: GsGetActiveBuff */
    void (*loadImage)();      /* 0x58 Display_LoadImage (display, rect, pixels) */
    void (*storeImage)();     /* 0x5C Display_StoreImage (display, pixels, rect) */
    s32 (*unk60)();           /* 0x60 func_80020A1C: returns 0 */
    void (*moveImage)();      /* 0x64 Display_MoveImage (display, rect, x, y) */
    void (*frameLoop)();      /* 0x68 Display_RunFrameLoop */
    void (*countFrame)();     /* 0x6C Display_CountFrame, works on the current display */
    void (*setVSyncMode)();   /* 0x70 Display_SetVSyncMode, ignored while the loop runs */
    s32 (*getVSyncMode)();    /* 0x74 Display_GetVSyncMode */
    void (*clearImage)();     /* 0x78 Display_ClearImage (display, color, rect): the whole screen when rect is 0 */
    s32 *(*getScreenRect)();  /* 0x7C Display_GetScreenRect (display, rect): returns &size */
    void (*setSyncDraw)();    /* 0x80 Display_SetSyncDraw */
    void (*setFrameCallback)(); /* 0x84 Display_SetFrameCallback: File_Enable hooks File_OnVSync here */
} DisplayVtbl;

typedef struct Display {
    DisplayVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 unk0C;                /* 0x0C set to 1 by countFrame when frameCount reaches vsyncMode */
    s32 running;              /* 0x10 the frame loop runs: VRAM transfers then need syncDraw */
    ScreenSize size;           /* 0x14 the screen size given to GsInitGraph */
    s32 vramMode;             /* 0x1C GsInitGraph's vrammode */
    s32 vsyncMode;            /* 0x20 VSync's argument each frame */
    s32 frameCount;           /* 0x24 countFrame's counter */
    u8 pad_28[0x2C - 0x28];
    s32 syncDraw;             /* 0x2C transfers also run during the loop, and wait for DrawSync */
    void (*frameCallback)(void); /* 0x30 called after each VSync, 0 for none */
} Display;

/* The pad (vtable 0x8006D370, class word 2, src/game/80025B34.c, sender type 2): docs/discoveries.md, pad codes. */
typedef struct PadVtbl {
    s32 classWord;          /* 0x00 2 */
    void *(*delete_)();    /* 0x04 Object_Delete */
    void (*init)();        /* 0x08 Pad_Init (pad, padInitMode, padId) */
    void (*destroy)();     /* 0x0C Pad_Destroy */
    u8 pad_10[0x30 - 0x10];
    void (*notify)();      /* 0x30 Object_Notify: sends one code */
    u8 pad_34[0x40 - 0x34];
    void (*reset)();       /* 0x40 Pad_Reset (pad, padId) */
    void (*read)();        /* 0x44 Pad_Read */
    void (*send)();        /* 0x48 Pad_SendEvents */
    void (*unk4C)();       /* 0x4C func_80025E14, empty */
    void (*initButtons)(); /* 0x50 Pad_InitButtons */
    void (*unk54)();       /* 0x54 func_80025E94, empty */
} PadVtbl;

typedef struct Pad {
    PadVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s16 padId;   /* 0x0C PadRead's argument, 0 or 1 */
    u8 pad_0E[0x10 - 0x0E];
    s32 held;    /* 0x10 the last PadRead */
    s32 released; /* 0x14 bits that went up this frame */
    s32 pressed; /* 0x18 bits that went down this frame */
} Pad;

/* The clock (vtable g_clockVtbl 0x8006EF50, class word 5, src/game/80041AB4.c, sender type 5): each
   step counts and sends CLOCK_MSG_TICK, or CLOCK_MSG_PAUSED when paused, CLOCK_MSG_STOPPED when stopped. */
#define CLOCK_MSG_TICK 2
#define CLOCK_MSG_PAUSED 3
#define CLOCK_MSG_STOPPED 4

typedef struct ClockVtbl {
    s32 classWord;           /* 0x00 5 */
    void *(*delete_)();      /* 0x04 Object_Delete */
    void (*init)(void *);    /* 0x08 Clock_Init */
    void (*destroy)();       /* 0x0C Clock_Destroy */
    u8 pad_10[0x24 - 0x10];
    void (*removeWatcher)(); /* 0x24 Clock_RemoveWatcher */
    u8 pad_28[0x30 - 0x28];
    void (*notify)(void *, s32);  /* 0x30 Clock_Notify */
    u8 pad_34[0x40 - 0x34];
    void (*reset)(void *, s32);   /* 0x40 Clock_Reset (clock, ticks) */
    void (*step)();          /* 0x44 Clock_Step */
    s32 (*getTicks)();       /* 0x48 Clock_GetTicks */
    void (*pause)();         /* 0x4C Clock_Pause */
    void (*resume)();        /* 0x50 Clock_Resume */
    s32 (*isPaused)();       /* 0x54 Clock_IsPaused */
    void (*stop)();          /* 0x58 Clock_Stop */
} ClockVtbl;

typedef struct Clock {
    ClockVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 ticks;              /* 0x0C steps counted while running */
    s32 paused;             /* 0x10 */
    s32 stopped;            /* 0x14 */
    ListNode *notifyIter;   /* 0x18 the watcher list cursor while Clock_Notify runs */
} Clock;

/* 16-byte value at +0x14 of a ModelObject, copied in by ModelObject_SetValue */
typedef struct ModelObjectValue {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} ModelObjectValue;

/*
 * One model object (src/game/8001F250.c, sender type 9): the 0x24-byte Object subclass made by
 * ModelObject_Create, one per TMD object; a scene node links one at +0x20.
 * Its vtable is g_modelObjectVtbl (g_modelObjectVtbl). The first three fields are the Object root
 * of heap.h, kept as s32 because the constructor stores an s32 in them (see the report).
 */
typedef struct ModelObject {
    s32 vtbl;               /* +0x00 ObjectVtbl * in heap.h */
    ListNode *watched;      /* +0x04 */
    ListNode *watchers;     /* +0x08 */
    s32 tmdObjectBase;      /* +0x0C tmdObject - 0xC, see ModelObject_GetObjectAt */
    s32 tmdObject;          /* +0x10 address of the TMD object entry */
    ModelObjectValue value; /* +0x14 */
} ModelObject;

/* A scene node (vtable g_sceneNodeVtbl, class word 4, 0x44 bytes, src/game/8001CA94.c; sender type 4):
   a GsDOBJ2 with a parent; Scene_DrawNode draws a tree of them. Slots are left unprototyped. */
typedef struct SceneNodeVtbl {
    s32 classWord;             /* 0x00 4: sender type scene node */
    void *(*delete_)();       /* 0x04 Object_Delete */
    void *(*init)();          /* 0x08 SceneNode_Init, returns the node or NULL */
    void (*destroy)();        /* 0x0C SceneNode_Destroy */
    void (*watch)();          /* 0x10 SceneNode_Watch */
    void (*unwatch)();        /* 0x14 SceneNode_Unwatch */
    void (*unwatchAll)();     /* 0x18 SceneNode_UnwatchAll */
    void (*nextWatched)();    /* 0x1C Object_NextWatched */
    void (*addWatcher)();     /* 0x20 Object_AddWatcher */
    void (*removeWatcher)();  /* 0x24 Object_RemoveWatcher */
    void (*freeWatchers)();   /* 0x28 Object_FreeWatchers */
    void (*nextWatcher)();    /* 0x2C Object_NextWatcher */
    void (*notify)();         /* 0x30 Object_Notify */
    void (*unk34)();          /* 0x34 func_80018350, empty */
    void (*onNotify)();       /* 0x38 SceneNode_OnNotify */
    void (*unk3C)();          /* 0x3C 0 */
    void (*reset)();          /* 0x40 SceneNode_Reset */
    void (*setRotation)();    /* 0x44 SceneNode_SetRotation (node, assign, Fraction[3] degrees) */
    void (*setScale)();       /* 0x48 SceneNode_SetScale (node, assign, Fraction[3]) */
    void (*attach)();         /* 0x4C SceneNode_Attach (node, parent, position) */
    void (*detach)();         /* 0x50 SceneNode_Detach */
    void (*detachChildren)(); /* 0x54 SceneNode_DetachChildren */
    void (*nextChild)();      /* 0x58 SceneNode_NextChild (node, &child, &iter) */
    void (*unk5C)();          /* 0x5C func_8001D33C, empty */
    s32 (*setVisible)();      /* 0x60 SceneNode_SetVisible, GsDOFF */
    void (*setSemiTrans)();   /* 0x64 SceneNode_SetSemiTrans, GsALON */
    void (*setBlendRate)();   /* 0x68 SceneNode_SetBlendRate, GsAZERO to GsATHREE */
    void (*setLit)();         /* 0x6C SceneNode_SetLit, GsLOFF */
    void (*setLightFlags)();  /* 0x70 SceneNode_SetLightFlags, GsFOG, GsMATE, GsLLMOD */
    void (*setDim)();         /* 0x74 SceneNode_SetDim, GsLDIM0 to GsLDIM7 */
    s32 (*setZSort)();        /* 0x78 SceneNode_SetZSort, GsZIGNR */
    void (*setDivision)();    /* 0x7C SceneNode_SetDivision, GsDIV1 to GsDIV5 */
    s32 (*setBackfaceClip)(); /* 0x80 SceneNode_SetBackfaceClip, GsNBACKC */
    void (*getRotMatrix)();   /* 0x84 SceneNode_GetRotMatrix (node, matrix, invert) */
    void (*sendBoxes)();      /* 0x88 SceneNode_SendBoxes (node, message) */
    void (*getBoxList)();     /* 0x8C SceneNode_GetBoxList (node, box list) */
    void (*sendShape)();      /* 0x90 SceneNode_SendShape (node, box list, message) */
    void (*onPad)();          /* 0x94 SceneNode_OnPad, empty: messages of a pad (sender type 2) */
    void (*onClock)();        /* 0x98 SceneNode_OnClock, empty: messages of a clock (sender type 5) */
    void (*onNode)();         /* 0x9C SceneNode_OnNode: messages of another node (sender type 4) */
    void (*checkContact)();   /* 0xA0 SceneNode_CheckContact (node, sender) */
    void (*worldToLocal)();   /* 0xA4 SceneNode_WorldToLocal (node, offset, dst, src, count) */
    s32 (*boxesOverlap)();    /* 0xA8 SceneNode_BoxesOverlap (node, box list, offset) */
    s32 (*rayTestBoxes)();    /* 0xAC SceneNode_RayTestBoxes (node, &sender hit mask, hit position, box list) */
    void (*unkB0)();          /* 0xB0 func_8001E49C, empty */
    void (*unkB4)();          /* 0xB4 SceneNode_AddActorWatchers */
} SceneNodeVtbl;

typedef struct SceneNode {
    SceneNodeVtbl *vtbl;
    ListNode *watched;           /* 0x04 objects this one watches: its children among them */
    ListNode *watchers;          /* 0x08 */
    struct SceneNode *parent; /* 0x0C */
    s32 attribute;               /* 0x10 GsDOBJ2.attribute: bit 31 GsDOFF hides the node */
    Coord2 *coord;               /* 0x14 GsDOBJ2.coord2: a view watching the node takes it as super */
    s32 tmd;                     /* 0x18 GsDOBJ2.tmd */
    s32 id;                      /* 0x1C GsDOBJ2.id */
    ModelObject *model;          /* 0x20 the watched model object (sender type 9) */
    s32 unk24;                   /* 0x24 cleared by reset */
    struct SceneNode *contact; /* 0x28 the last node that hit this one (message 4) */
    s32 hitMask;                 /* 0x2C boxes hit by the last test, one bit per box */
    s32 *boxList;                /* 0x30 the box list being sent, NULL otherwise */
    u8 pad_34[0x44 - 0x34];
} SceneNode;

/*
 * What every screen runs with: the scene keeps it at +0x1C (App_Start in src/game/8003AF8C.c
 * builds it with the display and the pad, the other three 0). A NULL clock, root or view makes the screen create
 * its own for the run and delete it after.
 */
typedef struct ScreenEnv {
    Display *display;
    Pad *pad;
    Clock *clock;            /* default Clock_Create */
    SceneNode *root;         /* default RootNode_Create: a RootNode (vtable 0x8006EFAC, src/game/80041AB4.c), lights at +0x44, ambient color at +0x50 */
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

/* One object of the classes the menu uses (src/game/8003FDB0.c): texts, the option box, a 2D overlay. */
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
    void (*unk78)();         /* 0x78 one argument (src/game/80050BA8.c) */
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

/*
 * Fade (vtable g_fadeVtbl at 0x8006E99C, class word 0x164, 0xA0 bytes, src/game/8003FDB0.c): a Box
 * that fades from or to a color. The color index is a 3-bit RGB channel mask (g_fadePalette: 1 blue,
 * 2 green, 4 red, 7 white); 0 means black and stores the mask 0xF. Each tick of the watched object
 * adds the step to the masked channels; at the end the fade notifies its watchers: 5 after a fade in,
 * 6 after a fade out. It is the view's 320 x 240 overlay (View +0xB0), the Place fader and the
 * Grey Man white flash (entity.h Entity.effect).
 */
typedef struct Fade Fade;
typedef struct FadeVtbl {
    u8 pad_00[0x4];
    void *(*delete_)();                       /* 0x04 Object_Delete */
    void (*init)(void *fade, s32 size, s32 channels, s32 priority); /* 0x08 Fade_Construct */
    u8 pad_0C[0x10 - 0xC];
    void (*watch)(Fade *fade);                /* 0x10 (fade, ticker) */
    void (*unwatch)(Fade *fade, s32 ticker);  /* 0x14 */
    u8 pad_18[0x30 - 0x18];
    void (*notify)(Fade *fade, s32 message);  /* 0x30 */
    u8 pad_34[0x40 - 0x34];
    void (*reset)(void *fade, s32 channels);  /* 0x40 Fade_Init */
    u8 pad_44[0x4C - 0x44];
    void (*show)();                           /* 0x4C Box_Show (fade, root, position) */
    void (*hide)();                           /* 0x50 */
    u8 pad_54[0x60 - 0x54];
    void (*setVisible)(Fade *fade, s32 visible);   /* 0x60 */
    void (*setSemiTrans)(Fade *fade, s32 on);      /* 0x64 */
    void (*setBlendMode)(Fade *fade, s32 mode);    /* 0x68 */
    u8 pad_6C[0xB8 - 0x6C];
    void (*setColor)(Fade *fade, s32 copy, u8 *color); /* 0xB8 */
    u8 pad_BC[0xD0 - 0xBC];
    void (*setStep)();                        /* 0xD0 Fade_SetStep (fade, step): 5, 6, 10 or 30 */
    void (*startIn)();                        /* 0xD4 Fade_StartIn (fade, ticker, channels, arg3) */
    void (*startOut)();                       /* 0xD8 Fade_StartOut (fade, ticker, channels, arg3) */
    s32 (*begin)(Fade *fade, s32 ticker, s32 channels, s32 arg3); /* 0xDC Fade_Begin */
    void (*stop)(void *fade);                 /* 0xE0 Fade_Stop (fade, ticker) */
    void *(*getColor)();                      /* 0xE4 Fade_GetColor */
    u8 pad_E8[0xF0 - 0xE8];
    s32 (*setTint)();                         /* 0xF0 Fade_SetTint (fade, tint, divisor) */
} FadeVtbl;

/* The step at +0x74 is an s32, read as its low byte by Fade_Step */
typedef union FadeStep {
    s32 value;
    u8 low;
} FadeStep;

/* A size saved by Fade_SaveAndSetRect as an s32 and read back by Fade_RestoreRect as a u16 */
typedef union FadeSaved {
    s32 value;
    u16 half;
} FadeSaved;

/* Fade messages to its watchers */
#define FADE_MSG_IN_DONE 5
#define FADE_MSG_OUT_DONE 6

struct Fade {
    FadeVtbl *vtbl;
    u8 pad_04[0xC - 0x4];
    s32 parent;             /* 0x0C */
    u8 pad_10[0x50 - 0x10];
    ScreenPoint position;   /* 0x50 */
    s32 attribute;          /* 0x58 */
    u16 x;                  /* 0x5C */
    u16 y;                  /* 0x5E */
    u16 width;              /* 0x60 */
    u16 height;             /* 0x62 */
    Color3 color;           /* 0x64 */
    u8 pad_67;
    s32 mask;               /* 0x68 */
    s32 state;              /* 0x6C 0 idle, 1 fading in, 2 fading out */
    s32 defaultChannels;    /* 0x70 used when Fade_Begin gets a negative index */
    FadeStep step;          /* 0x74 added to the channels each tick, 10 by default */
    s32 channels;           /* 0x78 */
    s32 unk_7C;             /* third argument of Fade_Begin: 9 holds the color */
    s32 remaining;          /* 0x80 ticks left */
    s32 unk_84;             /* mask / ticks */
    FadeSaved savedWidth;   /* 0x88 */
    FadeSaved savedHeight;  /* 0x8C */
    ScreenPoint savedPosition; /* 0x90 */
    s32 tint;               /* 0x98 set in flashbacks: the fade stops short and the color stays */
    s32 tintDivisor;        /* 0x9C the fade runs ticks - ticks / tintDivisor */
};

/*
 * Label (vtable g_labelVtbl, class word 0x11144, 0xB8 bytes, src/game/8003FDB0.c): a glyph that owns
 * a row of glyphs (src/game/80041AB4.c), one per character, laid out from its position with spacing
 * pixels between them. Label_Create makes the menu texts and the save title (menu.h Menu +0xB0).
 */
typedef struct LabelVtbl {
    u8 pad_00[0x4];
    void (*delete_)(void *label);             /* 0x04 Object_Delete */
    void (*init)(void *label, s32 font, s32 count, s32 text); /* 0x08 Label_Construct */
    u8 pad_0C[0x40 - 0xC];
    void (*reset)(void *label, s32 text);     /* 0x40 Label_Init */
    u8 pad_44[0x4C - 0x44];
    void (*show)(void *label, s32 root, void *position); /* 0x4C Label_Show */
    u8 pad_50[0xB8 - 0x50];
    void (*setColor)(void *label, void *color); /* 0xB8 Label_SetColor */
    u8 pad_BC[0xCC - 0xBC];
    void (*setText)(void *label, s32 text);   /* 0xCC */
    s32 unk_D0;
    void (*setSpacing)(void *label, s32 spacing); /* 0xD4 */
} LabelVtbl;

typedef struct Label {
    LabelVtbl *vtbl;
    u8 pad_04[0xC - 0x4];
    s32 parent;             /* 0x0C */
    u8 pad_10[0xA9 - 0x10];
    u8 count;               /* 0xA9 glyphs, the longest text setText takes */
    u8 gapAt;               /* 0xAA when nonzero, 16 more pixels before this glyph */
    u8 shownCount;          /* 0xAB */
    u8 firstShown;          /* 0xAC */
    u8 pad_AD[0xB0 - 0xAD];
    s32 spacing;            /* 0xB0 */
    struct Glyph **glyphs;  /* 0xB4 */
} Label;

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
    s32 unk24;
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
    struct ScreenBg *bgCells; /* 0x80 BgCells: 300 cells of 16x16 on VRAM x 640 to 960 (include/game/loader.h) */
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
    struct ScreenMovie *movie; /* 0xB4 the Movie of Movie_Create (include/game/loader.h) */
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

/* The view's slots past Object (vtable g_viewVtbl). */
typedef struct ViewVtbl {
    s32 classWord;               /* 0x00 7 */
    void *(*delete_)();
    void (*init)();
    void (*destroy)();
    void (*watch)();            /* 0x10 View_Watch */
    void (*unwatch)();          /* 0x14 View_Unwatch */
    void (*unwatchAll)();
    void (*nextWatched)();
    void (*addWatcher)();
    void (*removeWatcher)();
    void (*freeWatchers)();
    void (*nextWatcher)();
    void (*notify)();
    void (*unk34)();
    void (*onNotify)();         /* 0x38 */
    void (*unk3C)();
    void (*reset)();            /* 0x40 */
    void (*setScreenSize)();    /* 0x44 */
    void (*setOtBits)();        /* 0x48 */
    void (*setPacketCount)();   /* 0x4C */
    void (*setPacketSize)();    /* 0x50 */
    void (*setProjection)();    /* 0x54 */
    void (*unk58)();            /* 0x58 empty */
    void (*unk5C)();            /* 0x5C empty */
    void (*setLightMode)();     /* 0x60 */
    void (*setClearColor)();    /* 0x64 */
    void (*setFogColor)();      /* 0x68 */
    void (*setFogNear)();       /* 0x6C */
    void (*setCamera)();        /* 0x70 (view, node, viewpoint, refPoint, twist) */
    void (*detach)();           /* 0x74 */
    void (*setViewpoint)();     /* 0x78 */
    void (*setRefPoint)();      /* 0x7C */
    void (*setTwist)();         /* 0x80 */
    void (*unk84)();            /* 0x84 empty */
    void (*unk88)();            /* 0x88 empty */
    void (*allocOt)();          /* 0x8C */
    void (*freeOt)();           /* 0x90 */
    void (*onClock)();          /* 0x94 sender type 5 */
    void (*onDisplay)();        /* 0x98 sender type 1 */
    void (*render)();           /* 0x9C */
    void (*drawNode)();         /* 0xA0 Scene_DrawNode */
    void (*present)();          /* 0xA4 */
    void (*setOverlay)();       /* 0xA8 */
    struct Fade *(*getOverlay)(); /* 0xAC View_GetOverlay */
    void (*setUnkB4)();         /* 0xB0 */
    void (*setUnkB8)();         /* 0xB4 */
} ViewVtbl;

typedef struct View {
    ViewVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    Display *display;       /* 0x0C the watched type 1 object */
    SceneNode *node;        /* 0x10 the watched type 4 object; rendered with its root */
    /* 0x14 GsRVIEW2, given to GsSetRefView2 */
    ScreenVec viewpoint;    /* 0x14 */
    ScreenVec refPoint;     /* 0x20 */
    s32 twist;              /* 0x2C rz, 4.12 */
    Coord2 *super;          /* 0x30 node's coordinate; render clears its flg */
    ScreenPoint screenSize; /* 0x34 (0x100, 0xF0): Scene_DrawNode (src/game/80012064.c) sizes boxes and sprites by its half */
    s32 otBits;             /* 0x3C 13 */
    s32 projection;         /* 0x40 h of SetGeomScreen, 0x100 */
    s32 packetCount;        /* 0x44 2000 */
    s32 packetSize;         /* 0x48 0x40 */
    s32 unk4C;              /* 0x4C 10, func_8003FB0C */
    s32 unk50;              /* 0x50 0x10000; (unk50 - unk4C) / OT length + 1 is unk98 */
    s32 lightMode;          /* 0x54 GsSetLightMode; 1 and 3 turn the fog on */
    Color3 clearColor;      /* 0x58 GsSortClear */
    Color3 fogColor;        /* 0x5B SetFarColor */
    u8 pad_5E[0x60 - 0x5E];
    s32 fogNear;            /* 0x60 SetFogNear, 20000 */
    u8 pad_64[0x70 - 0x64];
    s32 otReady;            /* 0x70 */
    s32 buffer;             /* 0x74 the display's active buffer */
    GsOT *ot[2];            /* 0x78 */
    void *otEntries[2];     /* 0x80 */
    void *packets[2];       /* 0x88 GPU packet areas, packetCount x packetSize each */
    s32 clockCount;         /* 0x90 clock messages received */
    u8 pad_94[0x98 - 0x94];
    s32 unk98;              /* 0x98 */
    u8 pad_9C[0xAC - 0x9C];
    SceneNode *root;        /* 0xAC SceneNode_New, drawn every frame; the overlay hangs from it */
    Fade *overlay;          /* 0xB0 a 320 x 240 Fade at (-100, -100); Place uses it as its fader (place.h) */
    s32 unkB4;              /* 0xB4 when set, present swaps buffers once more on buffer 0 */
    s32 unkB8;              /* 0xB8 present draws only when set, 1 */
} View;

/* ------------------------------------------------------------------------------------------ */
/* App and Scene.                                                                              */

/*
 * The application base class (vtable g_appVtbl, 0x20 bytes), the class Scene derives from
 * (vtable 0x8006D3C8, src/game/80025F7C.c). main (src/game/800118DC.c) makes the scene, starts it
 * with a display and a pad (slot 0x44), then runs it (slot 0x4C), which never returns.
 * Slots 0x50 to 0x64 are 0 here; Scene fills them (docs/discoveries.md, the ending video).
 */
typedef struct AppVtbl {
    ObjectVtbl base;
    s32 unk3C;                /* 0x3C 0 */
    void (*setScreenMode)();  /* 0x40 App_SetScreenMode (app, size, vramMode) */
    void (*start)();          /* 0x44 App_Start (app, display, pad) */
    void (*unk48)();          /* 0x48 func_8003B108, empty */
    void (*run)();            /* 0x4C App_Run, the main loop */
    void (*showLogos)();      /* 0x50 Scene: the logos, called with no argument */
    void (*playOpening)();    /* 0x54 Scene: the opening video */
    s32 (*runTitle)();        /* 0x58 Scene: the title, returns 0, 1 or 2 */
    void (*onTitle1)();       /* 0x5C Scene: empty, run when the title returns 1 */
    s32 (*runDream)();        /* 0x60 Scene: the dream, non-zero when the ending must play */
    void (*playEnding)();     /* 0x64 Scene: ETC\ENDING.STR */
} AppVtbl;

typedef struct App {
    AppVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    ScreenSize screenSize;    /* 0x0C g_appScreenSize (320, 240) at init */
    s32 vramMode;             /* 0x14 GsInitGraph's vrammode: 0 at init */
    s32 started;              /* 0x18 1 once start has run */
    ScreenEnv *env;           /* 0x1C display and pad, what every screen runs with */
} App;


typedef struct SceneSettings {
    s32 fileBackend; /* 0x00 FILE_BACKEND_*, given to the base init (File_SetBackend) */
    s32 unk4;        /* 0x04 DreamRunner_New's third argument: DreamRunner_Init calls File_EnableWait(unk4 == 0, 1, 1) */
    s32 videos;      /* 0x08 opening, reel, cinematic and ending videos */
    s32 logos;       /* 0x0C */
    s32 title;       /* 0x10 the graph and the main menu */
    s32 unk14;       /* 0x14 handed to DreamSys slot 0x228, which keeps it at +0x924 */
} SceneSettings;

/*
 * Scene (vtable g_sceneVtbl 0x8006D3C8, src/game/80025F7C.c), the App the game runs: main
 * (src/game/800118DC.c) makes it with g_sceneSettings, then calls setup (0x44) and run (0x4C).
 * Every slot of g_sceneVtbl; 0x00 to 0x3C are Object's, 0x48 and 0x4C the base class's.
 */
typedef struct SceneVtbl {
    s32 classWord;          /* 0x00 0x1F60 */
    void *(*delete_)();    /* 0x04 Object_Delete */
    void (*init)();        /* 0x08 Scene_Init (scene, settings) */
    void (*destroy)();     /* 0x0C App_Destroy, empty */
    u8 pad_10[0x40 - 0x10];
    void (*seedRandom)();  /* 0x40 Scene_SeedRandom */
    void (*setup)();       /* 0x44 Scene_Setup (scene, display, pad) */
    void (*unk48)();       /* 0x48 func_8003B108, empty */
    void (*run)();         /* 0x4C App_Run, the scene loop */
    void (*showLogos)();   /* 0x50 Scene_ShowLogos */
    void (*playOpening)(); /* 0x54 Scene_PlayOpening */
    s32 (*runTitle)();     /* 0x58 Scene_RunTitle */
    void (*unk5C)();       /* 0x5C func_80026690, empty: run when the title returns 1, which it never does */
    s32 (*runDream)();     /* 0x60 Scene_RunDream */
    void (*playEnding)();  /* 0x64 Scene_PlayEnding */
} SceneVtbl;

typedef struct Scene {
    SceneVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    /* App */
    ScreenSize screenSize;   /* 0x0C g_appScreenSize (320, 240), App_SetScreenMode */
    s32 vramMode;            /* 0x14 GsInitGraph's vrammode: 0 */
    s32 started;             /* 0x18 App_Start has built env */
    ScreenEnv *env;          /* 0x1C what every screen of the scene runs with */
    /* Scene */
    SceneSettings *settings; /* 0x20 */
    s32 skipGraph;           /* 0x24 the dream ended in flashback mode, an end or an erase: no graph before the next menu */
    struct DreamSys *dreamSys; /* 0x28 the game state, made with ETC\DREAME5.TMD */
} Scene;

#endif

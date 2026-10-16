#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "common.h"
#include "game/heap.h"

/* A pair of words copied whole: a screen position, a size, the view's screen size. */
typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

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

/* The display (Display_GetVtbl 0x8006C070, src/game/display.c, sender type 1): sends message 2 once per frame while its loop runs. */
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
    s32 (*unk60)();           /* 0x60 Display_EmptySlot60: returns 0 */
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

/* Functions of src/game/display.c that other files call or reference (docs/naming.md, Prototypes) */
Display *Display_New(void);
Display *Display_GetCurrent(void);
void Display_SetCurrent(Display *display);

#endif

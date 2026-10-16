#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

/*
 * The display (vtable g_displayVtbl, 0x34 bytes, Display_New, sender type 1 in Screen_OnNotify):
 * the PSY-Q graphics setup, the frame loop and VRAM transfers. main makes one and the
 * application's start makes it the current display (Display_SetCurrent, read back by Display_GetCurrent).
 * The frame loop (slot 0x68) runs while +0x10 is set: VSync(vsyncMode), the frame callback,
 * then message 2 to every watcher. include/game/scene.h has the slots screens call.
 */
/* A rect as callers pass it ({u16 x, u16 y, s32 w, s32 h}), read through halfwords */
typedef struct DisplayRect {
    u16 x;
    u16 y;
    u16 w;                    /* low half of the s32 width */
    u16 unk6;
    u16 h;                    /* 0x08 low half of the s32 height */
} DisplayRect;

/* PSY-Q RECT */
typedef struct Rect {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Rect;

/* A screen size ({s32 w, s32 h}) read through halfwords */
typedef struct DisplaySizeHalves {
    u16 w;
    u16 unk2;
    u16 h;
    u16 unk6;
} DisplaySizeHalves;

void GsSwapDispBuff(void);
extern int GsGetActiveBuff(void);
void *Heap_Alloc(s32 size);
DisplayVtbl *Display_GetVtbl(void);
void Display_ConvertRect(Rect *rect, DisplayRect *src);
void MoveImage(Rect *rect, s32 x, s32 y);
Display *Display_GetCurrent(void);
ObjectVtbl *Object_GetBaseVtbl(void);
s32 LoadImage(Rect *rect, u32 *p);
s32 DrawSync(s32 mode);
extern s32 DrawSync(s32);
void StoreImage(Rect *rect, u32 *pixels);
void GsInitGraph(u16 x, u16 y, u16 intmode, u16 dith, u16 vrammode);
void GsDefDispBuff(u16 x0, u16 y0, u16 x1, u16 y1);
s32 VSync(s32 mode);
void ClearImage(Rect *rect, u8 r, u8 g, u8 b);
extern DisplayVtbl g_displayVtbl;
Display *g_currentDisplay;

Display *Display_New(void) {
    Display *display;

    display = Heap_Alloc(0x34);
    if (display != 0) {
        Display_GetVtbl()->base.init(display);
        return display;
    }
    return 0;
}

void Display_Init(Display *display) {
    DisplayVtbl *vtbl;

    Object_GetBaseVtbl()->init(display);
    vtbl = Display_GetVtbl();
    display->vtbl = vtbl;
    vtbl->reset(display);
}

void Display_Reset(Display *display) {
    display->running = 0;
    display->vtbl->setVSyncMode(display, 3);
    display->vtbl->setSyncDraw(display, 1);
    display->frameCallback = 0;
}

/* Interlace off, dithering on; the second display buffer starts at y = height. */
void Display_InitGraph(Display *display, DisplaySizeHalves *size, s32 vramMode) {
    GsInitGraph(size->w, size->h, 0, 1, vramMode);
    GsDefDispBuff(0, 0, 0, size->h);
    display->size = *(ScreenSize *)size;
    display->vramMode = vramMode;
}

void Display_StartLoop(Display *display) {
    if (display->running == 0) {
        display->running = 1;
        display->vtbl->frameLoop();
    }
}

void Display_StopLoop(Display *display) {
    if (display->running != 0) {
        display->running = 0;
    }
}

void Display_SwapBuffers(void) {
    GsSwapDispBuff();
}

void Display_GetActiveBuffer(void) {
    GsGetActiveBuff();
}

void Display_LoadImage(Display *display, DisplayRect *rect, u32 *pixels) {
    Rect vramRect;

    if ((display->running == 0) || (display->syncDraw != 0)) {
        Display_ConvertRect(&vramRect, rect);
        LoadImage(&vramRect, pixels);
        if (display->syncDraw != 0) {
            DrawSync(0);
        }
    }
}

void Display_ConvertRect(Rect *rect, DisplayRect *src) {
    rect->x = src->x;
    rect->y = src->y;
    rect->w = src->w;
    rect->h = src->h;
}

void Display_StoreImage(Display *display, u32 *pixels, DisplayRect *rect) {
    Rect vramRect;

    if ((display->running == 0) || (display->syncDraw != 0)) {
        Display_ConvertRect(&vramRect, rect);
        StoreImage(&vramRect, pixels);
        if (display->syncDraw != 0) {
            DrawSync(0);
        }
    }
}

s32 Display_EmptySlot60(void) {
    return 0;
}

void Display_MoveImage(Display *display, DisplayRect *rect, s16 x, s16 y) {
    Rect vramRect;

    Display_ConvertRect(&vramRect, rect);
    MoveImage(&vramRect, x, y);
}

void Display_RunFrameLoop(Display *display) {
    while (display->running != 0) {
        VSync(display->vsyncMode);
        if (display->frameCallback != NULL) {
            display->frameCallback();
        }
        display->vtbl->base.notify(display, 2);
    }
}

void Display_CountFrame(void) {
    Display *display;

    display = Display_GetCurrent();
    if (++display->frameCount >= display->vsyncMode && display->unk0C == 0) {
        display->unk0C = 1;
        display->frameCount = 0;
    }
}

void Display_SetVSyncMode(Display *display, s32 vsyncMode) {
    if (display->running == 0) {
        display->vsyncMode = vsyncMode;
    }
}

s32 Display_GetVSyncMode(Display *display) {
    return display->vsyncMode;
}

void Display_ClearImage(Display *display, u8 *color, s32 rect) {
    DisplayRect screenRect; /* 10 bytes: getScreenRect writes 12, the 2 extra land in the frame's padding */
    Rect vramRect;

    if (rect == 0) {
        display->vtbl->getScreenRect(display, &screenRect);
        display->vtbl->clearImage(display, color, &screenRect);
        return;
    }
    Display_ConvertRect(&vramRect, (DisplayRect *)rect);
    ClearImage(&vramRect, color[0], color[1], color[2]);
}

s32 *Display_GetScreenRect(Display *display, ScreenRect *rect) {
    if (rect != NULL) {
        rect->x = 0;
        rect->y = 0;
        rect->w = display->size.w;
        rect->h = display->size.h * 2;
    }
    return &display->size.w;
}

void Display_SetSyncDraw(Display *display, s32 syncDraw) {
    display->syncDraw = syncDraw;
}

void Display_SetFrameCallback(Display *display, s32 callback) {
    display->frameCallback = (void (*)(void))callback;
}

DisplayVtbl *Display_GetVtbl(void) {
    return &g_displayVtbl;
}

Display *Display_GetCurrent(void) {
    return g_currentDisplay;
}

void Display_SetCurrent(Display *display) {
    g_currentDisplay = display;
}

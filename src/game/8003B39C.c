#include "common.h"
#include "game/heap.h"
#include "game/loader.h"
#include "game/scene.h"

/*
 * The TIM image class (vtable g_timVtbl, 0x50 bytes, Tim_New): a file object
 * (include/game/loader.h) holding one TIM. Slot 0x78 uploads its pixels and its CLUT to VRAM
 * through the current display; slots 0x7C to 0x94 are empty. A TimPack makes one per image of
 * a TIX and points +0x4C at the fade of its palette row (src/game/80043008.c).
 */
typedef struct TimVtbl {
    FileVtbl base;
    void (*upload)();         /* 0x78 Tim_Upload */
    void (*unk7C)();          /* 0x7C to 0x94: empty */
    void (*unk80)();
    void (*unk84)();
    void (*unk88)();
    void (*unk8C)();
    void (*unk90)();
    void (*unk94)();
    void (*setUnk48)();       /* 0x98 func_8003B5E4: +0x48 = 1 */
    void (*getInfo)(void *, void *); /* 0x9C Tim_GetInfo: GsGetTimInfo into a GsIMAGE */
} TimVtbl;

/* PSY-Q GsIMAGE as this unit reads it (loader.h GsImage has s16 positions and pointers) */
typedef struct TimImage {
    u32 pmode;                /* 0x00 bit 3: the TIM has a CLUT */
    u16 px;
    u16 py;
    u16 pw;
    u16 ph;
    s32 pixel;                /* 0x0C */
    u16 cx;
    u16 cy;
    u16 cw;
    u16 ch;
    s32 clut;                 /* 0x18 */
} TimImage;

typedef struct Tim {
    TimVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    u32 *data;                /* 0x10 the TIM file: id word, then the TIM */
    u8 pad_14[0x2C - 0x14];   /* file fields (loader.h) */
    TimImage image;           /* 0x2C filled by getInfo before each upload */
    s32 unk48;                /* 0x48 0 at init, 1 after slot 0x98; not read in this unit */
    s32 fade;                 /* 0x4C address of the TixFade of its palette row, 0 at init */
} Tim;

/* The current display (Display_GetCurrent, src/game/800206E0.c): the two slots used here */
typedef struct TimDisplayVtbl {
    u8 pad_00[0x58];
    void (*loadImage)(void *, void *, s32);           /* 0x58 (display, rect, pixels): LoadImage */
    u8 pad_5C[0x64 - 0x5C];
    void (*moveImage)(void *, void *, s32, s32);      /* 0x64 (display, rect, x, y): MoveImage */
} TimDisplayVtbl;

typedef struct TimDisplay {
    TimDisplayVtbl *vtbl;
} TimDisplay;

extern void GsGetTimInfo(u32 *im, void *tim);
FileVtbl *File_GetBackendVtbl(void);
void *Heap_Alloc(s32 size);
TimVtbl *Tim_GetVtbl(void);
TimDisplay *Display_GetCurrent(void);
extern u8 g_timVtbl[];

Tim *Tim_New(char *path) {
    Tim *tim;

    tim = Heap_Alloc(0x50);
    if (tim != 0) {
        Tim_GetVtbl()->base.init(tim, path);
        return tim;
    }
    return 0;
}

/* path 0: the creator sets the data (a TimPack borrows it), else the file is queued for loading. */
void Tim_Init(Tim *tim, char *path) {
    File_GetBackendVtbl()->init(tim);
    tim->vtbl = Tim_GetVtbl();
    tim->unk48 = 0;
    tim->fade = 0;
    if (path != 0) {
        tim->vtbl->base.loadAsync(tim, path);
    }
}

void Tim_Destroy(Tim *tim) {
    File_GetBackendVtbl()->destroy(tim);
}

void Tim_Upload(Tim *tim) {
    TimDisplay *display;
    TimImage *image;
    MovieRect rect;

    display = Display_GetCurrent();
    image = &tim->image;
    if (tim->data != NULL) {
        tim->vtbl->getInfo(tim, image);
        rect.x = tim->image.px;
        rect.y = tim->image.py;
        rect.w = tim->image.pw;
        rect.h = tim->image.ph;
        display->vtbl->loadImage(display, &rect, tim->image.pixel);
        if ((tim->image.pmode >> 3) & 1) {
            rect.x = tim->image.cx;
            rect.y = tim->image.cy;
            rect.w = tim->image.cw;
            rect.h = tim->image.ch;
            display->vtbl->loadImage(display, &rect, tim->image.clut);
        }
    }
}

void func_8003B5AC(void) {
}

void func_8003B5B4(void) {
}

void func_8003B5BC(void) {
}

void func_8003B5C4(void) {
}

void func_8003B5CC(void) {
}

void func_8003B5D4(void) {
}

void func_8003B5DC(void) {
}

void func_8003B5E4(Tim *tim) {
    tim->unk48 = 1;
}

void Tim_GetInfo(Tim *tim, void *image) {
    GsGetTimInfo(tim->data + 1, image);
}

TimVtbl *Tim_GetVtbl(void) {
    return (TimVtbl *)g_timVtbl;
}

/*
 * Rotates the VRAM area rect one column to the right, count times, through the spare column
 * at (spare->x, spare->y): the last column goes to the spare, the rest moves right by one, the
 * spare comes back as the first column. The place cycles CLUT rows with it: 248 entries of
 * rows 0x1F0 to 0x1F7 in stage 2, of rows 0x1F8 to 0x1FF in stages 3 to 5 (func_80055A24).
 */
void Display_RotateRect(ScreenRect *rect, s32 count, ScreenRect *spare) {
    MovieRect move;
    s32 i;
    TimDisplay *display;
    void (*moveImage)(void *, void *, s32, s32);

    display = Display_GetCurrent();
    moveImage = display->vtbl->moveImage;
    if (count != 0) {
        for (i = 0; i < count; i++) {
                move.x = rect->x + rect->w - 1;
                move.y = rect->y;
                move.w = 1;
                move.h = rect->h;
                moveImage(display, &move, spare->x, spare->y);
                move.x = rect->x;
                move.y = rect->y;
                move.w = rect->w - 1;
                move.h = rect->h;
                moveImage(display, &move, rect->x + 1, rect->y);
                move.x = spare->x;
                move.y = spare->y;
                move.w = 1;
                move.h = rect->h;
                moveImage(display, &move, rect->x, rect->y);
        }
    }
}

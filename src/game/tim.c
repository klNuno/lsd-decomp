#include "common.h"
#include "game/loader.h"
#include "game/scene.h"
#include "game/tim.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/file_base.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

extern void GsGetTimInfo(u32 *im, void *tim);
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
    Display *display;
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

void Tim_EmptySlot7C(void) {
}

void Tim_EmptySlot80(void) {
}

void Tim_EmptySlot84(void) {
}

void Tim_EmptySlot88(void) {
}

void Tim_EmptySlot8C(void) {
}

void Tim_EmptySlot90(void) {
}

void Tim_EmptySlot94(void) {
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
 * rows 0x1F0 to 0x1F7 in stage 2, of rows 0x1F8 to 0x1FF in stages 3 to 5 (Stage_CyclePalettes).
 */
void Display_RotateRect(ScreenRect *rect, s32 count, ScreenRect *spare) {
    MovieRect move;
    s32 i;
    Display *display;
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

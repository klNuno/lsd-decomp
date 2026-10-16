#include "common.h"
#include "game/loader.h"

/*
 * TimPack: one part of a TIX, a list of TIM images (include/game/loader.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The TIM image class (Tim_New, vtable 0x8006E558, 0x50 bytes) as this unit uses it */
/* Psy-Q GsIMAGE, as slot 0x9C of a TIM fills it (0x1C bytes, 4 more reserved) */
typedef struct GsImage {
    u32 pmode;
    s16 px;
    s16 py;
    u16 pw;
    u16 ph;
    u32 *pixel;
    s16 cx;
    s16 cy;                    /* the CLUT's VRAM row */
    u16 cw;
    u16 ch;
    u32 *clut;
    u8 pad_1C[0x20 - 0x1C];
} GsImage;
extern void Object_DeleteArray(void *, s32);
extern void Heap_Free(s32);
extern s32 Heap_Alloc(s32 size);
FileVtbl *File_GetBackendVtbl(void);
s32 Tim_New(s32 path);
TimPackVtbl *TimPack_GetVtbl(void);
s32 TimPack_Create(s32 path);
extern TimPackVtbl g_timPackVtbl;
s16 g_clutPaletteShift;                /* 3: CLUT row - 0x1E0 >> this = palette index */

/* ---- TimPack: one part of a TIX ---- */

s32 TimPack_Create(s32 path) {
    s32 timPack;

    timPack = Heap_Alloc(0x3C);
    if (timPack != 0) {
        TimPack_GetVtbl()->base.init(timPack, path);
        return timPack;
    }
    return 0;
}

void TimPack_Init(TimPack *timPack, s32 path) {
    File_GetBackendVtbl()->init(timPack);
    timPack->vtbl = TimPack_GetVtbl();
    timPack->count = 0;
    timPack->tims = 0;
    timPack->loaded = 0;
    if (path != 0) {
        timPack->vtbl->base.loadAsync(timPack, path);
    }
}

void TimPack_Destroy(TimPack *timPack) {
    Object_DeleteArray(timPack->tims, timPack->count);
    Heap_Free(timPack->tims);
    File_GetBackendVtbl()->destroy(timPack);
}

/*
 * Slot 0x64: one TIM object per image, borrowing its data; each TIM's +0x4C gets the fade of
 * its palette, fades + ((CLUT row - 0x1E0) >> 3) * sizeof(TixFade).
 */
void TimPack_OnLoaded(TimPack *timPack) {
    GsImage info;
    Tim **tims;
    Tim *tim;
    Tim **slot;
    s32 *offset;
    s32 i;

    if ((timPack->flags & 0x200) || timPack->data.words != NULL) {
        timPack->count = *timPack->data.words;
        tims = (Tim **)Heap_Alloc(*timPack->data.words * 4);
        timPack->tims = tims;
        if (tims != NULL) {
            slot = tims;
            offset = timPack->data.words + 1;
            for (i = 0; i < timPack->count; i++) {
                tim = (Tim *)Tim_New(0);
                *slot = tim;
                tim->data = (u32 *)((u8 *)timPack->data.words + *offset);
                (*slot)->size = 0;
                offset++;
                (*slot)->vtbl->getInfo(*slot, &info);
                (*slot)->fade = ((((s32)info.cy - 0x1E0) >> g_clutPaletteShift) * 0x10) + timPack->fades;
                slot++;
            }
            timPack->loaded = 1;
            File_GetBackendVtbl()->onLoaded(timPack);
        }
    }
}

void TimPack_UploadAll(TimPack *timPack) {
    s32 i;
    Tim **p;
    Tim *tim;
    void (*upload)(void *tim);

    p = timPack->tims;
    for (i = 0; i < timPack->count; i++) {
        tim = *p;
        upload = tim->vtbl->upload;
        p++;
        upload(tim);
    }
}

TimPackVtbl *TimPack_GetVtbl(void) {
    return &g_timPackVtbl;
}

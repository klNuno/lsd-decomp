#include "common.h"
#include "game/tim_pack.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/tim.h"
#include "game/tix.h"

/*
 * TimPack: one part of a TIX, a list of TIM images (include/game/tim_pack.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern TimPackVtbl g_timPackVtbl;
s16 g_clutPaletteShift;                /* 3: CLUT row - 0x1E0 >> this = palette index */

TimPack *TimPack_Create(char *path) {
    TimPack *timPack;

    timPack = Heap_Alloc(0x3C);
    if (timPack != NULL) {
        TimPack_GetVtbl()->base.init(timPack, path);
        return timPack;
    }
    return NULL;
}

void TimPack_Init(TimPack *timPack, char *path) {
    File_GetBackendVtbl()->init(timPack);
    timPack->vtbl = TimPack_GetVtbl();
    timPack->count = 0;
    timPack->tims = 0;
    timPack->loaded = 0;
    if (path != NULL) {
        timPack->vtbl->base.loadAsync(timPack, path);
    }
}

void TimPack_Destroy(TimPack *timPack) {
    Object_DeleteArray((Object **)timPack->tims, timPack->count);
    Heap_Free(timPack->tims);
    File_GetBackendVtbl()->destroy(timPack);
}

/*
 * Slot 0x64: one TIM object per image, borrowing its data; each TIM's +0x4C gets the fade of
 * its palette, fades + ((CLUT row - 0x1E0) >> 3) * sizeof(TixFade).
 */
void TimPack_OnLoaded(TimPack *timPack) {
    TimImage info;
    Tim **tims;
    Tim *tim;
    Tim **slot;
    s32 *offset;
    s32 i;

    if ((timPack->flags & 0x200) || timPack->data.words != NULL) {
        timPack->count = *timPack->data.words;
        tims = Heap_Alloc(*timPack->data.words * 4);
        timPack->tims = tims;
        if (tims != NULL) {
            slot = tims;
            offset = timPack->data.words + 1;
            for (i = 0; i < timPack->count; i++) {
                tim = Tim_New(NULL);
                *slot = tim;
                tim->data.bytes = timPack->data.bytes + *offset;
                (*slot)->size = 0;
                offset++;
                (*slot)->vtbl->getInfo(*slot, &info);
                (*slot)->fade = timPack->fades + (((s32)info.cy - 0x1E0) >> g_clutPaletteShift);
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

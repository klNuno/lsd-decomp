#include "common.h"
#include "game/tix.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/tim_pack.h"
#include "psyq/libgpu.h"

/*
 * Tix: a TEXx.TIX texture set file and its palette fades (include/game/tix.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The TIX header, copied as bytes (alignment 1) */
typedef struct TixHeaderBytes {
    u8 bytes[0x24];
} TixHeaderBytes;

/* The palette rows Tix_BuildFade reads and writes */
typedef struct ClutRect {
    u16 x;
    u16 y;
    s16 w;
    u16 h;
} ClutRect;

typedef struct ClutRows {
    ClutRect dst;
    ClutRect src;
    u16 faded[0x100];
    u16 source[0x100];
    u16 pad420[4];
} ClutRows;

static u32 Tix_GetMaxPartSize(Tix *tix);
static void Tix_BuildFade(TixFade *fade, s32 palette);

extern TixVtbl g_tixVtbl;
s16 g_clutFadeShift;                /* 3: a palette fade has 1 << this rows */

Tix *Tix_Create(char *path) {
    Tix *tix;

    tix = Heap_Alloc(0x84);
    if (tix != NULL) {
        Tix_GetVtbl()->base.init(tix, path);
        return tix;
    }
    return NULL;
}

/* Slot 0x08: opens the file and reads its first 0x800 bytes (state 9) */
void Tix_Init(Tix *tix, char *path) {
    s32 i;
    s16 rowOffset;
    s16 rows;
    u32 *header;
    u8 *buffer;
    TixFade *fade;

    File_GetBackendVtbl()->init(tix);
    tix->vtbl = Tix_GetVtbl();
    tix->partIndex = 0;
    tix->parts = 0;
    tix->loaded = 0;
    tix->buffer = NULL;
    tix->bufferSize = 0;
    rows = 1 << g_clutFadeShift;
    rowOffset = 0;
    for (i = 0; i < 4; i++) {
        fade = &tix->fades[i];
        fade->shift = g_clutFadeShift;
        fade->rows = rows;
        fade->x = 0;
        fade->y = rowOffset + 0x1E0;
        fade->w = 0x100;
        fade->h = 1;
        rowOffset += rows;
    }

    header = Heap_Alloc(0x24);
    if (header != NULL) {
        buffer = Heap_Alloc(0x800);
        tix->buffer = buffer;
        if (buffer != NULL) {
            tix->size = 0x24;
            tix->header = header;
            tix->state = 9;
            tix->failed = 0;
            tix->vtbl->base.open(tix, path, 1, 0);
            tix->vtbl->base.read(tix, tix->buffer, 0x800);
        }
    }
}

void Tix_Destroy(Tix *tix) {
    Object_DeleteArray((Object **)tix->parts, tix->partIndex);
    Heap_Free(tix->parts);
    File_GetBackendVtbl()->destroy(tix);
}

/*
 * Slot 0x64, run when a read completes. State 9: keeps the header, makes the part table and a
 * buffer for the largest part, reads part 0. State 10: makes a TimPack over the buffer,
 * uploads it, reads the next part; after the last one frees the buffer and sets loaded.
 * A failed allocation sets failed and stops.
 */
void Tix_OnReadDone(Tix *tix) {
    u32 index;
    u32 maxSize;
    TimPack **slot;

    File_LockBackend();
    switch (tix->state) {
    case 9:
        if (tix->flags & 0x80) {
            *(TixHeaderBytes *)tix->header = *(TixHeaderBytes *)tix->buffer;
            Heap_Free(tix->buffer);
            maxSize = Tix_GetMaxPartSize(tix);
            if (((tix->parts = Heap_Alloc(tix->header[0] * 4)) != NULL)
                && ((tix->buffer = Heap_Alloc(maxSize)) != NULL)) {
                tix->bufferSize = maxSize;
                tix->vtbl->base.seek(tix, tix->header[1], 0);
                tix->vtbl->base.read(tix, tix->buffer, maxSize);
                tix->state = 0xA;
            } else {
                goto fail;
            }
        }
        break;
    case 10:
        if (tix->flags & 0x80) {
            index = tix->partIndex;
            slot = tix->parts + index;
            *slot = TimPack_Create(NULL);
            (*slot)->data.bytes = tix->buffer;
            (*slot)->size = 0;
            (*slot)->fades = tix->fades;
            index = index + 1;
            (*slot)->vtbl->base.onLoaded(*slot);
            (*slot)->vtbl->uploadAll(*slot);
            tix->partIndex = index;
            if (index < tix->header[0]) {
                tix->vtbl->base.seek(tix, tix->header[index + 1], 0);
                tix->vtbl->base.read(tix, tix->buffer, tix->bufferSize);
                tix->state = 0xA;
            } else {
                Heap_Free(tix->buffer);
                tix->buffer = NULL;
                tix->bufferSize = 0;
                tix->state = 0;
                tix->loaded = 1;
                File_GetBackendVtbl()->onLoaded(tix);
            }
        }
        break;
    }
    goto end;
fail:
    tix->failed = 1;
end:
    File_UnlockBackend();
}

/* The largest part size of the header (sizes at words 5 to 8) */
static u32 Tix_GetMaxPartSize(Tix *tix) {
    u32 *header;
    u32 i;
    u32 max;

    header = tix->header;
    i = 0;
    max = 0;

    for (; i < header[0]; i++) {
        if (max < header[i + 5]) {
            max = header[i + 5];
        }
    }
    return max;
}

void Tix_SetFadeShift(Tix *tix, s32 palette, u16 shift) {
    TixFade *fade = &tix->fades[palette];

    fade->shift = shift;
    fade->rows = 1 << fade->shift;
}

void Tix_SetFadeColorAll(Tix *tix, Color3 *color) {
    s32 i;

    File_LockBackend();
    for (i = 0; i < 4; i++) {
        tix->vtbl->setFadeColor(tix, i, color);
    }
    File_UnlockBackend();
}

void Tix_SetFadeColor(Tix *tix, s32 palette, Color3 *color) {
    TixFade *fade;

    File_LockBackend();
    fade = &tix->fades[palette];
    fade->color = *color;
    Tix_BuildFade(fade, palette);
    File_UnlockBackend();
}

/*
 * Reads the palette's CLUT row (VRAM y 0x1E0 + palette << g_clutFadeShift) and writes rows
 * 1 to rows - 1 under it, row k blended toward the fade colour by k / rows (4.12 weights,
 * 5-bit channels). Colour 0 (transparent) stays 0; the semi-transparency bit is kept.
 */
static void Tix_BuildFade(TixFade *fade, s32 palette) {
    ClutRows work;
    s32 i;
    s32 k;
    s32 weightShift;
    s32 weight;
    s32 blueTerm;
    s32 greenTerm;
    s32 redTerm;
    s32 r;
    s32 g;
    s32 b;
    u32 pixel;
    u16 pixel16;
    u8 red;
    u8 green;
    u8 blue;

    work.src.x = 0;
    work.src.w = 0x100;
    work.src.h = 1;
    work.src.y = (palette << g_clutFadeShift) + 0x1E0;
    StoreImage(&work.src, (u32 *) work.source);
    DrawSync(0);
    work.dst.h = 1;
    i = 0;
    work.dst.x = 0;
    work.dst.y = 0;
    work.dst.w = 0x100;
    red = fade->color.r;
    green = fade->color.g;
    blue = fade->color.b;
    fade->h = fade->rows;
    weightShift = 0xC - fade->shift;
    if (fade->rows - 1 > 0) {
        do {
            weight = (i + 1) << weightShift;
            redTerm = red * weight;
            greenTerm = green * weight;
            blueTerm = blue * weight;
            weight = 0x1000 - weight;
            for (k = 0; k < work.src.w; k++) {
                pixel = work.source[k];
                if (pixel == 0) {
                    work.faded[k] = work.source[k];
                } else {
                    pixel16 = work.source[k];
                    r = (pixel16 & 0x1F) << 3;
                    g = (pixel >> 2) & 0xF8;
                    b = (pixel >> 7) & 0xF8;
                    r = (r * weight + redTerm) >> 15;
                    g = (g * weight + greenTerm) >> 15;
                    b = (b * weight + blueTerm) >> 15;
                    work.faded[k] = (pixel16 & 0x8000) | r | (g << 5) | (b << 10);
                }
            }
            work.dst.y = work.src.y + i + work.src.h;
            DrawSync(0);
            LoadImage(&work.dst, (u32 *) work.faded);
            i++;
        } while (i < fade->rows - 1);
    }
}

TixVtbl *Tix_GetVtbl(void) {
    return &g_tixVtbl;
}

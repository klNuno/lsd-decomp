#include "common.h"
#include "game/loader.h"
#include "game/scene.h"

/*
 * File loaders: TIX texture sets with their palette fades, TMD models, TOD animations, MOM and
 * MML model files, the GsBG background classes and the MDEC movie player. Classes and their
 * vtables: include/game/loader.h.
 */

/* The TIX header, copied as bytes (alignment 1) */
typedef struct TixHeaderBytes {
    u8 bytes[0x24];
} TixHeaderBytes;

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

/* Movie as Movie_OnSlice reads it: the two rects by u16 halves */
typedef struct MovieSliceView {
    u8 pad_00[0x1C];
    s32 slice;                 /* 0x1C */
    s16 frameX;                /* 0x20 */
    u16 frameY;
    s32 frameW;
    u8 pad_28[0x2C - 0x28];
    u16 sliceX;                /* 0x2C */
    u16 sliceY;
    u16 sliceW;                /* low half of sliceRect.w (16) */
    u8 pad_32[0x34 - 0x32];
    s32 sliceH;                /* 0x34 */
    s32 sliceWords;            /* 0x38 */
    u8 pad_3C[0x44 - 0x3C];
    s32 stopped;               /* 0x44 */
    s32 streamEnded;           /* 0x48 */
    s32 frameDone;             /* 0x4C */
} MovieSliceView;

/* BgMap as Bg_SetMap reads it: cellsY unsigned (signed in BgMap_Build) */
typedef struct BgMapView {
    u8 pad_00[0x2C];
    u8 cellW;                  /* 0x2C the GsMAP */
    u8 cellH;
    u16 cellsX;
    u16 cellsY;
} BgMapView;

/* Bg_SetRotation's argument: a fraction at +8 */
typedef struct BgAngle {
    u8 pad_00[0x8];
    s16 num;
    s16 den;
} BgAngle;

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

extern void GsMapModelingData(u32 *p);
extern void Object_DeleteArray(void *, s32);
extern void Heap_Free(s32);
extern s32 Heap_Alloc(s32 size);
extern void File_LockBackend(void);
extern void File_UnlockBackend(void);
FileVtbl *File_GetBackendVtbl(void);
FileSource *File_MakeSource(FileSource *source, s32 data, s32 path, s32 unk08);
ObjectVtbl *SceneNode_GetVtbl(void);
ObjectVtbl *Object_GetBaseVtbl(void);
extern void *ModelObject_Create(s32 tmdObject);
s32 Tim_New(s32 path);
Display *Display_GetCurrent(void);
Stream *Stream_New(void *arg0, s32 arg1, s32 arg2);
extern s32 DrawSync(s32 mode);
extern void DecDCTReset(s32 mode);
extern void DecDCToutCallback(void (*func)(void));
extern void DecDCTout(s32 p, s32 size);
extern void DecDCTin(s32 p, s32 mode);
extern void DecDCTvlc(s32 p, s32 q);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
void StoreImage(ClutRect *rect, u32 *p);
s32 LoadImage(ClutRect *rect, u32 *p);

TixVtbl *Tix_GetVtbl(void);
TmdVtbl *Tmd_GetVtbl(void);
TimPackVtbl *TimPack_GetVtbl(void);
TodVtbl *Tod_GetVtbl(void);
BgVtbl *Bg_GetVtbl(void);
MomVtbl *Mom_GetVtbl(void);
MomVtbl *Mml_GetVtbl(void);
BgMapVtbl *BgMap_GetVtbl(void);
BgCellsVtbl *BgCells_GetVtbl(void);
TodVtbl *TodPack_GetVtbl(void);
MovieVtbl *Movie_GetVtbl(void);
u32 Tix_GetMaxPartSize(Tix *tix);
void Tix_BuildFade(TixFade *fade, s32 palette);
s32 Tmd_Create(s32 source);
s32 TimPack_Create(s32 path);
s32 Tod_Create(s32 source);
u32 *Tod_ReadPacket(void *tod, u32 *packet, s8 *id, s8 *type, s8 *flag, s8 *length);
s32 Mom_Create(s32 source);
s32 TodPack_Create(s32 source);
s32 Movie_AllocBuffers();
void Movie_FreeBuffers(Movie *movie);
void func_800458AC(Movie *movie);
void Movie_OnStreamCallback(Movie *movie);
void Movie_OnMdecOut(void);
void Movie_WaitFrame(Movie *movie);

extern TixVtbl g_tixVtbl;
extern TmdVtbl g_tmdVtbl;
extern TimPackVtbl g_timPackVtbl;
extern TodVtbl g_todVtbl;
extern BgVtbl g_bgVtbl;
extern MomVtbl g_momVtbl;
extern MomVtbl g_mmlVtbl;
extern BgMapVtbl g_bgMapVtbl;
extern BgCellsVtbl g_bgCellsVtbl;
extern TodVtbl g_todPackVtbl;
extern u8 g_movieVtbl[];

Movie *g_activeMovie;             /* the movie playing */
s32 g_movieRestartCounter;                /* calls of Movie_OnStopped since the last restart (starts at 1) */
s16 g_clutPaletteShift;                /* 3: CLUT row - 0x1E0 >> this = palette index */
s32 g_mdecReady;                /* 1 once DecDCTReset ran */
s16 g_clutFadeShift;                /* 3: a palette fade has 1 << this rows */
extern Color3 g_bgDefaultColor;    /* {0x80, 0x80, 0x80}, the neutral GsBG colour */
extern u8 D_8008A944[];

/* ---- TIX texture set ---- */

s32 Tix_Create(s32 path) {
    s32 tix;

    tix = Heap_Alloc(0x84);
    if (tix != 0) {
        Tix_GetVtbl()->base.init(tix, path);
        return tix;
    }
    return 0;
}

/* Slot 0x08: opens the file and reads its first 0x800 bytes (state 9) */
void Tix_Init(Tix *tix, s32 path) {
    s32 i;
    s16 rowOffset;
    s16 rows;
    s32 header;
    s32 buffer;
    TixFade *fade;

    File_GetBackendVtbl()->init(tix);
    tix->vtbl = Tix_GetVtbl();
    tix->partIndex = 0;
    tix->parts = 0;
    tix->loaded = 0;
    tix->buffer = 0;
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
    if (header != 0) {
        buffer = Heap_Alloc(0x800);
        tix->buffer = buffer;
        if (buffer != 0) {
            tix->size = 0x24;
            tix->header = (u32 *)header;
            tix->state = 9;
            tix->failed = 0;
            tix->vtbl->base.open(tix, path, 1, 0);
            tix->vtbl->base.read(tix, tix->buffer, 0x800);
        }
    }
}

void Tix_Destroy(Tix *tix) {
    Object_DeleteArray(tix->parts, tix->partIndex);
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
            if (((tix->parts = (TimPack **)Heap_Alloc(tix->header[0] * 4)) != 0)
                && ((tix->buffer = Heap_Alloc(maxSize)) != 0)) {
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
            *slot = (TimPack *)TimPack_Create(0);
            (*slot)->data.addr = tix->buffer;
            (*slot)->size = 0;
            (*slot)->fades = (s32)tix->fades;
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
                tix->buffer = 0;
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
u32 Tix_GetMaxPartSize(Tix *tix) {
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
void Tix_BuildFade(TixFade *fade, s32 palette) {
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

/* ---- TMD model ---- */

s32 Tmd_Create(s32 source) {
    s32 tmd;

    tmd = Heap_Alloc(0x30);
    if (tmd != 0) {
        if (Tmd_GetVtbl()->base.init(tmd, source) != 0) {
            return tmd;
        }
        Heap_Free(tmd);
    }
    return 0;
}

/* Slot 0x08: borrows source->data and parses it at once, or queues source->path; NULL on failure */
Tmd *Tmd_Init(Tmd *tmd, FileSource *source) {
    s32 data;
    TmdVtbl *vtbl;

    File_GetBackendVtbl()->init(tmd);
    vtbl = Tmd_GetVtbl();
    tmd->vtbl = vtbl;
    if (source != NULL) {
        data = source->data;
        if (data != 0) {
            tmd->data.addr = data;
            tmd->size = 0;
            if (tmd->vtbl->base.onLoaded(tmd) != 0) {
                goto fail;
            }
        } else {
            vtbl->base.loadAsync(tmd, source->path);
        }
    }
    return tmd;
fail:
    return NULL;
}

void Tmd_Destroy(Tmd *tmd) {
    Object **p;
    Object *model;

    for (p = tmd->models; *p != NULL; p++) {
        model = *p;
        model->vtbl->delete_(model);
    }
    Heap_Free((s32)tmd->models);
    File_GetBackendVtbl()->destroy(tmd);
}

/* Slot 0x64: maps the TMD and makes one model per TMD object; 1 on failure */
s32 Tmd_OnLoaded(Tmd *tmd) {
    Object **model;
    u32 i;

    model = (Object **)Heap_Alloc((tmd->data.header->objectCount + 1) * 4);
    if (model == NULL) {
        return 1;
    }
    tmd->models = model;
    tmd->vtbl->mapModelingData(tmd);
    for (i = 0; i < tmd->data.header->objectCount; i++) {
        *model = ModelObject_Create((s32)&tmd->data.header->objects[i]);
        if (*model == NULL) {
            while (i != 0) {
                model--;
                (*model)->vtbl->delete_(*model);
                i--;
            }
            Heap_Free((s32)model);
            return 1;
        }
        model++;
    }
    *model = NULL;
    File_GetBackendVtbl()->onLoaded(tmd);
    return 0;
}

void Tmd_MapModelingData(Tmd *tmd) {
    GsMapModelingData(tmd->data.words + 1);
}

/* Address of TMD object index (entries of 0x1C bytes from +0xC) */
s32 Tmd_GetObject(Tmd *tmd, s32 index) {
    s32 offset = index * 0x1C + 0xC;
    return offset + tmd->data.addr;
}

s32 Tmd_GetModel(Tmd *tmd, s32 index) {
    return (s32)tmd->models[index];
}

void func_80043B70(void) {
}

TmdVtbl *Tmd_GetVtbl(void) {
    return &g_tmdVtbl;
}

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

/* ---- TOD animation ---- */

s32 Tod_Create(s32 source) {
    s32 tod;

    tod = Heap_Alloc(0x2C);
    if (tod != 0) {
        Tod_GetVtbl()->base.init(tod, source);
        return tod;
    }
    return 0;
}

void Tod_Init(Tod *tod, FileSource *source) {
    s32 data;
    TodVtbl *vtbl;

    File_GetBackendVtbl()->init(tod);
    vtbl = Tod_GetVtbl();
    tod->vtbl = vtbl;
    data = source->data;
    if (data != 0) {
        tod->data = data;
        tod->size = 0;
        tod->vtbl->base.onLoaded(tod);
        return;
    }
    vtbl->base.loadAsync(tod, source->path);
}

void Tod_Destroy(Tod *tod) {
    File_GetBackendVtbl()->destroy(tod);
}

/* Slot 0x78: slot 0x7C on the first frame, after the 8-byte file header */
s32 Tod_ScanFirstFrame(Tod *tod, s32 ids, s32 tmdId) {
    return tod->vtbl->scanFrame(tod, ids, tmdId, tod->data + 8) & 0xFF;
}

/*
 * Slot 0x7C: returns how many objects the frame creates (type 8, flag 0) and stores their ids
 * in ids. With ids and tmdId, *tmdId becomes the index among them of the object the type 2
 * packet with TMD *tmdId names; with tmdId alone, the count of type 2 packets.
 */
s32 Tod_ScanFrame(Tod *tod, u8 *ids, s32 *tmdId, void *packet) {
    u8 fields[4];              /* id, type, flag, length */
    u16 count;
    u32 i;
    u8 created;
    s32 found;
    s32 j;

    count = ((TodFrame *)packet)->packetCount;
    packet = (u8 *)packet + 8;
    i = 0;
    created = 0;
    found = 0;
    for (; i < count; i++) {
        Tod_ReadPacket(tod, (u32 *)packet, (s8 *)&fields[0], (s8 *)&fields[1], (s8 *)&fields[2], (s8 *)&fields[3]);
        if (fields[1] == 8 && fields[2] == 0) {
            created++;
            if (ids != NULL) {
                *ids++ = fields[0];
            }
        } else if (fields[1] == 2) {
            if (ids != NULL) {
                if (tmdId != NULL && ((TodPacket *)packet)->tmdId == *tmdId) {
                    j = 0;
                    ids -= created;
                    for (; j < created; j++) {
                        if (*ids++ == fields[0]) {
                            found = j;
                            break;
                        }
                    }
                }
            } else if (tmdId != NULL) {
                found++;
            }
        }
        packet = (u8 *)packet + fields[3] * 4;
    }
    if (tmdId != NULL) {
        *tmdId = found;
    }
    return created;
}

/* Slot 0x80: splits a TOD packet header; returns the word after it */
u32 *Tod_ReadPacket(void *tod, u32 *packet, s8 *id, s8 *type, s8 *flag, s8 *length) {
    u32 header = *packet;

    *id = header;
    *type = (header >> 16) & 0xF;
    *flag = (header >> 20) & 0xF;
    *length = header >> 24;
    return packet + 1;
}

TodVtbl *Tod_GetVtbl(void) {
    return &g_todVtbl;
}

/* ---- Bg: GsBG background ---- */

s32 Bg_Create(s32 map, s32 mode) {
    void *bg = (void *)Heap_Alloc(0x68);

    if (bg != NULL) {
        Bg_GetVtbl()->init(bg, map, mode);
        return (s32)bg;
    }
    return 0;
}

void Bg_Init(Bg *bg, s32 map, s32 mode) {
    BgVtbl *vtbl;

    SceneNode_GetVtbl()->init(bg);
    vtbl = Bg_GetVtbl();
    bg->vtbl = vtbl;
    vtbl->setMap(bg, map, mode);
}

/* Slot 0x40: mode 0 sizes the GsBG from the map (8-bit), mode 1 makes it 320x240 (16-bit) */
void Bg_SetMap(Bg *bg, BgMapView *map, s32 mode) {
    if (mode == 0) {
        bg->bg.attribute = 0x01000000;
        bg->bg.w = map->cellW * map->cellsX;
        bg->bg.h = map->cellH * map->cellsY;
    } else if (mode == 1) {
        bg->bg.attribute = 0x02000000;
        bg->bg.w = 0x140;
        bg->bg.h = 0xF0;
    }
    bg->bg.x = 0;
    bg->bg.y = 0;
    bg->bg.scrollX = 0;
    bg->bg.scrollY = 0;
    bg->bg.color = g_bgDefaultColor;
    bg->bg.map = &map->cellW;
    bg->bg.scaleX = 0x1000;
    bg->bg.scaleY = 0x1000;
    bg->bg.rotate = 0;
    bg->bg.mx = bg->bg.w / 2;
    bg->bg.my = bg->bg.h / 2;
}

/* Slot 0x44: rotate = num / den in fixed point 12 bits, set when set != 0, else added */
void Bg_SetRotation(Bg *bg, s32 set, BgAngle *angle) {
    s16 num = angle->num;
    s16 den = angle->den;
    s32 value = ((num / den) << 12) + (((num % den) << 12) / den);

    if (set != 0) {
        bg->bg.rotate = value;
        return;
    }
    bg->bg.rotate = value + bg->bg.rotate;
}

/*
 * Slot 0x48: scaleX = s[0] / s[1] and scaleY = s[2] / s[3] in fixed point 12 bits (a zero
 * divisor gives 1.0 when setting), capped at 30000; set != 0 sets them, else adds. An added
 * value past the cap gives 1 when that fraction had a negative term.
 */
void Bg_SetScale(Bg *bg, s32 set, s16 *fractions) {
    s16 scaleX;
    s16 scaleY;
    s32 negativeX = 0;
    s32 negativeY = 0;
    s16 value;

    if (fractions[0] < 0 || fractions[1] < 0) {
        negativeX = 1;
    }
    if (fractions[2] < 0 || fractions[3] < 0) {
        negativeY = 1;
    }
    if (fractions[1] != 0) {
        s32 q = fractions[0] / fractions[1];
        s32 r = fractions[0] % fractions[1];
        scaleX = (q << 12) + ((r << 12) / fractions[1]);
    }
    if (fractions[3] != 0) {
        s32 q = fractions[2] / fractions[3];
        s32 r = fractions[2] % fractions[3];
        scaleY = (q << 12) + ((r << 12) / fractions[3]);
    }
    if (set != 0) {
        if (fractions[1] == 0) {
            bg->bg.scaleX = 0x1000;
        } else {
            value = scaleX >= 0x7531 ? 0x7530 : scaleX;
            bg->bg.scaleX = value;
        }
        if (fractions[3] == 0) {
            bg->bg.scaleY = 0x1000;
        } else {
            value = scaleY >= 0x7531 ? 0x7530 : scaleY;
            bg->bg.scaleY = value;
        }
        return;
    }
    value = bg->bg.scaleX;
    if (value + scaleX >= 0x7531) {
        bg->bg.scaleX = negativeX ? 1 : 0x7530;
    } else {
        bg->bg.scaleX = scaleX + value;
    }
    value = bg->bg.scaleY;
    if (value + scaleY >= 0x7531) {
        bg->bg.scaleY = negativeY ? 1 : 0x7530;
    } else {
        bg->bg.scaleY = scaleY + value;
    }
}

void Bg_SetColor(Bg *bg, s32 set, Color3 *color) {
    if (set != 0) {
        bg->bg.color = *color;
    }
}

void func_80044674(void) {
}

BgVtbl *Bg_GetVtbl(void) {
    return &g_bgVtbl;
}

/* ---- MOM model: a TMD and a TodPack ---- */

s32 Mom_Create(s32 source) {
    s32 mom;

    mom = Heap_Alloc(0x38);
    if (mom != 0) {
        if (Mom_GetVtbl()->base.init(mom, source, 1) != 0) {
            return mom;
        }
        Heap_Free(mom);
    }
    return 0;
}

Mom *Mom_Init(Mom *mom, FileSource *source, s32 hasParts) {
    MomVtbl *vtbl;
    s32 data;

    File_GetBackendVtbl()->init(mom);
    mom->vtbl = Mom_GetVtbl();
    mom->hasParts = hasParts;
    data = source->data;
    if (data != 0) {
        vtbl = mom->vtbl;
        mom->data = (u8 *)data;
        mom->size = 0;
        if (vtbl->base.onLoaded(mom) == 0) {
            return mom;
        }
    } else {
        mom->vtbl->base.loadAsync(mom, source->path);
        return mom;
    }
    return NULL;
}

/* Slot 0x7C is called without arguments: a0 still holds mom */
void Mom_Destroy(Mom *mom) {
    mom->vtbl->freeParts();
    File_GetBackendVtbl()->destroy(mom);
}

void Mom_OnLoaded(Mom *mom) {
    File_GetBackendVtbl()->onLoaded(mom);
    mom->vtbl->loadParts(mom);
}

/* Slot 0x78: the TMD at data + data[2] and the TodPack at data + 0xC; 1 (parts freed) on failure */
s32 Mom_LoadParts(Mom *mom) {
    FileSource source;
    s32 tmd;
    s32 motions;

    if (mom->hasParts != 0) {
        File_MakeSource(&source, (s32)(mom->data + *(s32 *)(mom->data + 8)), 0, 1);
        tmd = Tmd_Create((s32)&source);
        mom->tmd = (Tmd *)tmd;
        if (tmd != 0) {
            source.data = (s32)(mom->data + 0xC);
            motions = TodPack_Create((s32)&source);
            mom->motions = (TodPack *)motions;
            if (motions != 0) {
                return 0;
            }
            mom->motions = 0;
        }
        mom->vtbl->freeParts(mom);
        return 1;
    }
    return 0;
}

void Mom_FreeParts(Mom *mom) {
    Object *part;

    if (mom->hasParts != 0) {
        part = (Object *)mom->motions;
        if (part != NULL) {
            part->vtbl->delete_(part);
        }
        part = (Object *)mom->tmd;
        if (part != NULL) {
            part->vtbl->delete_(part);
        }
    }
}

s32 Mom_ScanFirstFrame(Mom *mom) {
    TodPack *motions = mom->motions;

    return motions->vtbl->scanFirstFrame(motions);
}

void Mom_ReadPacket(Mom *mom, s32 packet, s32 id, s32 type, s32 flag, s32 length) {
    mom->motions->vtbl->readPacket(mom->motions, packet, id, type, flag, length);
}

MomVtbl *Mom_GetVtbl(void) {
    return &g_momVtbl;
}

/* ---- MML: the MOM list of a map square ---- */

s32 Mml_Create(s32 source) {
    s32 mml;

    mml = Heap_Alloc(0x3C);
    if (mml != 0) {
        if (Mml_GetVtbl()->base.init(mml, source) == 0) {
            Heap_Free(mml);
            return 0;
        }
        return mml;
    }
    return 0;
}

Mml *Mml_Init(Mml *mml, FileSource *source) {
    MomVtbl *vtbl;

    Mom_GetVtbl()->base.init(mml, source, 0);
    vtbl = Mml_GetVtbl();
    mml->vtbl = vtbl;
    if (source->data != 0) {
        if (vtbl->base.onLoaded(mml) != 0) {
            return 0;
        }
    }
    return mml;
}

void Mml_Destroy(Mml *mml) {
    mml->vtbl->freeParts(mml);
    Mom_GetVtbl()->base.destroy(mml);
}

/* Slot 0x78 is called without arguments: a0 still holds mml */
void Mml_OnLoaded(Mml *mml) {
    mml->vtbl->loadParts();
}

/* Slot 0x78: one Mom per offset, written over the offset; 1 (Moms freed) on failure */
s32 Mml_LoadParts(Mml *mml) {
    FileSource source;
    s32 *entry;
    s32 count;
    s32 i;
    s32 mom;

    File_MakeSource(&source, 0, 0, 1);
    entry = &mml->data[2];
    count = mml->data[1];
    mml->momCount = 0;
    for (i = 0; i < count; i++) {
        source.data = (s32)((u8 *)mml->data + mml->data[i + 2]);
        mom = Mom_Create((s32)&source);
        *entry = mom;
        if (mom == 0) {
            goto fail;
        }
        mml->momCount++;
        entry++;
    }
    return 0;
fail:
    mml->vtbl->freeParts(mml);
    return 1;
}

void Mml_FreeParts(Mml *mml) {
    Object_DeleteArray(mml->data + 2, mml->momCount);
    mml->momCount = 0;
}

/* Slot 0x88: Mom number index, 0 past the count */
u32 Mml_GetMom(Mml *mml, u32 index) {
    u32 *words = (u32 *)mml->data;

    if (index < words[1]) {
        return words[index + 2];
    }
    return 0;
}

MomVtbl *Mml_GetVtbl(void) {
    return &g_mmlVtbl;
}

/* ---- BgMap: GsMAP over a BgCells ---- */

s32 BgMap_Create(s32 arg0, s32 cells) {
    s32 bgMap;

    bgMap = Heap_Alloc(0x44);
    if (bgMap != 0) {
        BgMap_GetVtbl()->base.init(bgMap, arg0, cells);
        return bgMap;
    }
    return 0;
}

void BgMap_Init(BgMap *bgMap, s32 arg1, BgCells *cells) {
    s32 unused[8];

    File_GetBackendVtbl()->init(bgMap);
    bgMap->vtbl = BgMap_GetVtbl();
    bgMap->cellSource = cells;
    bgMap->built = 0;
    if (arg1 == 0) {
        bgMap->fullScreen = 1;
        bgMap->state = 0;
        bgMap->vtbl->base.onLoaded(bgMap);
    }
}

void BgMap_Destroy(BgMap *bgMap) {
    Heap_Free(bgMap->index);
    File_GetBackendVtbl()->destroy(bgMap);
}

/* Slot 0x78 is called without arguments: a0 still holds bgMap */
void BgMap_OnLoaded(BgMap *bgMap) {
    if (bgMap->state == 0) {
        bgMap->vtbl->build();
        bgMap->built = 1;
    }
}

/* Slot 0x78: 20x15 cells of 16x16 numbered in order; frees the data when it cannot */
void BgMap_Build(BgMap *bgMap) {
    s16 *index;
    s16 *p;
    s32 i;
    s32 n;

    bgMap->cells = (s32)bgMap->cellSource->cells;
    if (bgMap->fullScreen != 0) {
        bgMap->cellsX = 0x14;
        bgMap->cellW = 0x10;
        bgMap->cellH = 0x10;
        bgMap->cellsY = 0xF;
        n = bgMap->cellsX * bgMap->cellsY;
        index = (s16 *)Heap_Alloc(n * 2);
        bgMap->index = index;
        if (index != NULL) {
            p = index;
            for (i = 0; i < n; i++) {
                *p++ = i;
            }
            return;
        }
    }
    bgMap->vtbl->base.freeData(bgMap);
}

BgMapVtbl *BgMap_GetVtbl(void) {
    return &g_bgMapVtbl;
}

/* ---- BgCells: the GsCELL table ---- */

s32 BgCells_Create(s32 arg0) {
    s32 bgCells;

    bgCells = Heap_Alloc(0x38);
    if (bgCells != 0) {
        BgCells_GetVtbl()->base.init(bgCells, arg0);
        return bgCells;
    }
    return 0;
}

void BgCells_Init(BgCells *bgCells, s32 arg1) {
    char unused[0x20]; /* same 0x20 buffer as SeqFile_Init's strcpy target */

    File_GetBackendVtbl()->init(bgCells);
    bgCells->vtbl = BgCells_GetVtbl();
    bgCells->unk_34 = 0;
    bgCells->built = 0;
    if (arg1 == 0) {
        bgCells->fullScreen = 1;
        bgCells->state = 0;
        bgCells->vtbl->base.onLoaded(bgCells);
    }
}

void BgCells_Destroy(BgCells *bgCells) {
    Heap_Free(bgCells->unk_34);
    Heap_Free(bgCells->cells);
    File_GetBackendVtbl()->destroy(bgCells);
}

void BgCells_OnLoaded(BgCells *bgCells) {
    s32 unused[8];

    if (bgCells->state == 0) {
        bgCells->vtbl->build(bgCells);
        bgCells->built = 1;
    }
}

/*
 * Slot 0x78: 300 cells of 16x16, 20 per row over VRAM x 640 to 960, rows of 16 lines;
 * the texture page follows x (x >> 6, + 0x10 from line 256).
 */
void BgCells_Build(BgCells *bgCells) {
    s32 i;
    s32 n;
    s32 u;
    s32 v;
    s32 x;
    s32 tpage;
    GsCell *p;
    GsCell *cells;

    if (bgCells->fullScreen != 0) {
        x = 0x280;
        v = 0;
        u = 0;
        tpage = GetTPage(2, 0, 0x280, 0) & 0xFFFF;
        cells = (GsCell *)Heap_Alloc(0x960);
        bgCells->cells = cells;
        if (cells != NULL) {
            i = 0;
            p = cells;
            n = 0x12C;
            do {
                p->u = u;
                u += 0x10;
                x += 0x10;
                p->tpage = tpage;
                p->v = v;
                p->cba = 0;
                p->flag = 0;
                if (x >= 0x3C0) {
                    u = 0;
                    x = 0x280;
                    v += 0x10;
                }
                if ((x & 0x3F) == 0) {
                    tpage = x >> 6;
                    if (v >= 0x100) {
                        tpage += 0x10;
                    }
                    u = 0;
                }
                i += 1;
                p++;
            } while (i < n);
        }
    }
}

BgCellsVtbl *BgCells_GetVtbl(void) {
    return &g_bgCellsVtbl;
}

/* ---- TodPack: a list of TOD files ---- */

s32 TodPack_Create(s32 source) {
    s32 todPack;

    todPack = Heap_Alloc(0x2C);
    if (todPack == 0) {
        return 0;
    }
    if (TodPack_GetVtbl()->base.init(todPack, source) != 0) {
        return todPack;
    }
    Heap_Free(todPack);
    return 0;
}

TodPack *TodPack_Init(TodPack *todPack, FileSource *source) {
    TodVtbl *vtbl;

    Tod_GetVtbl()->base.init(todPack, source);
    vtbl = TodPack_GetVtbl();
    todPack->vtbl = vtbl;
    if (source->data != 0) {
        if (vtbl->base.onLoaded(todPack) != 0) {
            return NULL;
        }
    }
    return todPack;
}

/* The offsets hold Tod objects once loaded */
void TodPack_Destroy(TodPack *todPack) {
    u32 *words = todPack->data.words;

    Object_DeleteArray(words + 2, words[1]);
    Tod_GetVtbl()->base.destroy(todPack);
}

/* Slot 0x64: one Tod per offset, written over the offset; 1 (Tods freed) on failure */
s32 TodPack_OnLoaded(TodPack *todPack) {
    FileSource source;
    TodPackHeader *header;
    Tod *tod;
    s32 i;
    s32 *out;
    s32 n;
    s32 made;

    File_MakeSource(&source, 0, 0, 1);
    out = todPack->data.header->offsets;
    n = todPack->data.header->count;
    for (i = 0; i < n; i++, out++) {
        header = todPack->data.header;
        source.data = (s32)header + header->offsets[i];
        made = Tod_Create((s32)&source);
        *out = made;
        if (made == 0) {
            while (i != 0) {
                out--;
                tod = (Tod *)*out;
                i--;
                tod->vtbl->base.delete_(tod);
            }
            return 1;
        }
    }
    return 0;
}

/* Slot 0x78: slot 0x7C on the first frame of the first TOD (past the offsets and its 8-byte header) */
s32 TodPack_ScanFirstFrame(TodPack *todPack, s32 ids, s32 tmdId) {
    return todPack->vtbl->scanFrame(todPack, ids, tmdId, &todPack->data.words[todPack->data.words[1]] + 4) & 0xFF;
}

TodVtbl *TodPack_GetVtbl(void) {
    return &g_todPackVtbl;
}

/* ---- Movie: the MDEC player ---- */

s32 Movie_Create(s32 rect, s32 streamArg, s32 skipAlloc) {
    s32 movie;

    movie = Heap_Alloc(0x6C);
    if (movie == 0) {
        return 0;
    }
    if (Movie_GetVtbl()->init(movie, rect, streamArg, skipAlloc) != 0) {
        Heap_Free(movie);
        return 0;
    }
    return movie;
}

/* Slot 0x08: the stream, the buffers, the MDEC callback; 0 on success */
s32 Movie_Init(Movie *movie, s32 rect, void *streamArg, s32 skipAlloc) {
    Stream *stream;

    Object_GetBaseVtbl()->init(movie);
    movie->vtbl = Movie_GetVtbl();
    stream = Stream_New(streamArg, 0xF, 0);
    movie->stream = stream;
    if (stream != NULL) {
        if (Movie_AllocBuffers(movie, rect, skipAlloc) == 0) {
            if (g_mdecReady == 0) {
                DecDCTReset(0);
            }
            g_mdecReady = 1;
            DecDCToutCallback(Movie_OnMdecOut);
            movie->stream->vtbl->setRing(movie->stream, movie->streamBuffer, 0x12000);
            movie->unk_50 = 0;
            movie->vtbl->setUnk68(movie, 1);
            return 0;
        }
        return 1;
    }
    return 1;
}

void Movie_Destroy(Movie *movie) {
    Stream *stream = movie->stream;

    movie->stream = stream->vtbl->delete_(stream);
    DecDCToutCallback(0);
    DecDCTReset(0);
    Movie_FreeBuffers(movie);
    Object_GetBaseVtbl()->destroy(movie);
}

/* The buffers (unless skipAlloc) and the frame and slice rects; 1 (buffers freed) on failure */
s32 Movie_AllocBuffers(Movie *movie, MovieRect *rect, s32 skipAlloc) {
    s32 size;
    s32 buffer;
    s32 unused[2];

    movie->skipAlloc = skipAlloc;
    if (skipAlloc == 0) {
        movie->slice = 0;
        movie->runLevel[1] = 0;
        movie->runLevel[0] = 0;
        movie->streamBuffer = 0;
        size = (rect->w * rect->h * 2) + 0x1000;
        buffer = Heap_Alloc(size);
        movie->runLevel[0] = buffer;
        if (buffer == 0) {
            goto fail;
        }
        buffer = Heap_Alloc(size);
        movie->runLevel[1] = buffer;
        if (buffer == 0) {
            goto fail;
        }
        buffer = Heap_Alloc(0x12000);
        movie->streamBuffer = buffer;
        if (buffer == 0) {
            goto fail;
        }
        buffer = Heap_Alloc(rect->h << 5);
        movie->slice = buffer;
        if (buffer == 0) {
            goto fail;
        }
    }
    movie->sliceRect = *rect;
    movie->frame = movie->sliceRect;
    movie->sliceRect.w = 0x10;
    movie->sliceWords = (movie->sliceRect.h * 0x10) >> 1;
    return 0;

fail:
    Movie_FreeBuffers(movie);
    return 1;
}

void Movie_FreeBuffers(Movie *movie) {
    if (movie->skipAlloc == 0) {
        Heap_Free(movie->runLevel[0]);
        Heap_Free(movie->runLevel[1]);
        Heap_Free(movie->streamBuffer);
        Heap_Free(movie->slice);
    }
}

/* Slot 0x40: opens source on the stream and makes this the playing movie; 1 when it cannot */
s32 Movie_Open(Movie *movie, void *source, s32 unk5C, s32 repeat, s32 loops) {
    Stream *stream;
    Display *gfx;

    if (g_activeMovie == NULL) {
        if (movie->unk_68 != 0) {
            func_800458AC(movie);
        }
        stream = movie->stream;
        movie->unk_5C = unk5C;
        if (stream->vtbl->open(stream, source, 100) == 0) {
            g_activeMovie = movie;
            movie->frameReady = 0;
            movie->runLevelIndex = 0;
            movie->frameDone = 1;
            movie->streamEnded = 0;
            movie->stopped = 0;
            movie->repeat = repeat;
            movie->loops = loops;
            gfx = Display_GetCurrent();
            gfx->vtbl->clearImage(gfx, D_8008A944, &movie->frame);
            return 0;
        }
        return 1;
    }
    return 0;
}

void func_800458AC(Movie *movie) {
    movie->unk_50 = 1;
}

/* Slot 0x44: restarts the playing movie, with Movie_OnStreamCallback as the stream callback */
void Movie_Start(Movie *movie) {
    Movie *active = g_activeMovie;
    Stream *stream;

    if (active == movie) {
        stream = active->stream;
        active->frameReady = 0;
        active->runLevelIndex = 0;
        active->frameDone = 1;
        active->streamEnded = 0;
        active->stopped = 0;
        stream->vtbl->setCallback(stream, Movie_OnStreamCallback, active);
        stream = active->stream;
        active->unk_64 = 0;
        stream->vtbl->rewind(stream);
    }
}

void Movie_OnStreamCallback(Movie *movie) {
    movie->unk_50 = -1;
}

/* Slot 0x48, each tick: handles a stream callback (counts loops), else decodes a frame */
s32 Movie_Update(Movie *movie) {
    Movie *active = g_activeMovie;

    if (active == movie && (active->unk_50 != 0 || active->unk_64 != 0)) {
        if (active->unk_50 != 0) {
            active->stream->vtbl->start(active->stream, 1, active->unk_5C);
            if (active->unk_50 < 0) {
                if (active->loops == 0 || --active->loops == 0) {
                    active->stream->vtbl->mute(active->stream);
                }
            }
            movie->unk_50 = 0;
            movie->unk_64 = 1;
            return 0;
        }
        active->vtbl->decodeFrame(active);
    }
}

/* Slot 0x4C */
void Movie_Stop(Movie *movie) {
    Movie *active = g_activeMovie;
    Stream *stream;

    if (active == movie) {
        stream = active->stream;
        active->streamEnded = 1;
        active->repeat = 0;
        stream->vtbl->close(stream);
        active->stopped = 1;
        if (active->unk_64 == 0) {
            stream = active->stream;
            stream->vtbl->setCallback(stream, 0, 0);
            active->unk_64 = 1;
            active->stopped = 1;
        }
    }
}

void func_80045AC8(void) {
}

void func_80045AD0(void) {
}

/* Slot 0x58: VLC-decodes the stream's next frame into the other run-level buffer; 1 when none */
s32 Movie_ReadFrame(Movie *movie) {
    s32 frame;
    s32 fresh;
    s32 status;
    s32 index;

    if (movie->streamEnded == 0) {
        status = movie->stream->vtbl->getFrame(movie->stream, &frame, &fresh, 0x800000);
        if (status != 0) {
            if (fresh != 0) {
                index = movie->runLevelIndex ^ 1;
                movie->runLevelIndex = index;
                DecDCTvlc(frame, movie->runLevel[index]);
            }
            movie->stream->vtbl->releaseFrame(movie->stream, frame);
            if (status < 0) {
                movie->streamEnded = 1;
                movie->stream->vtbl->stop(movie->stream);
            }
            return 0;
        }
    }
    return 1;
}

void func_80045BC0(void) {
}

/* Slot 0x60, from the MDEC callback: loads the slice into VRAM and starts the next one */
void Movie_OnSlice(MovieSliceView *movie) {
    Display *gfx;
    u16 x;

    gfx = Display_GetCurrent();
    gfx->vtbl->loadImage(gfx, &movie->sliceX, movie->slice);
    x = movie->sliceX + movie->sliceW;
    movie->sliceX = x;
    if ((s16)x < movie->frameX + movie->frameW) {
        if (movie->sliceH < 0x80) {
            DrawSync(0);
        }
        DecDCTout(movie->slice, movie->sliceWords);
    } else {
        movie->frameDone = 1;
        movie->sliceX = movie->frameX;
        movie->sliceY = movie->frameY;
        if (movie->streamEnded != 0) {
            movie->stopped = 1;
        }
    }
}

/* Slot 0x64: restarts a repeating movie every 100 calls; else the movie stops being active */
s32 Movie_OnStopped(Movie *movie) {
    if (movie->repeat != 0) {
        if (g_movieRestartCounter++ > 100) {
            g_movieRestartCounter = 1;
            movie->vtbl->start(movie);
        }
        return 0;
    }
    g_activeMovie = NULL;
    return 1;
}

/* Slot 0x68: sends the ready frame to the MDEC, then VLC-decodes the next one */
s32 Movie_DecodeFrame(Movie *movie) {
    Movie *active;

    active = g_activeMovie;
    if (active == movie) {
        if (active->stopped == 0) {
            if (active->frameReady != 0) {
                Movie_WaitFrame(active);
                active->frameDone = 0;
                if (active->sliceRect.h < 0x80) {
                    DrawSync(0);
                }
                DecDCTin(active->runLevel[active->runLevelIndex], 2);
                DecDCTout(active->slice, active->sliceWords);
            }
            movie->frameReady = movie->vtbl->readFrame(movie) == 0;
            return 0;
        }
        active->vtbl->onStopped(active);
    }
}

/* The DecDCToutCallback */
void Movie_OnMdecOut(void) {
    Movie *movie = g_activeMovie;

    if (movie != NULL) {
        movie->vtbl->onSlice(movie);
    }
}

void Movie_WaitFrame(Movie *movie) {
    while (movie->frameDone == 0) {
    }
}

void func_80045E3C(Movie *movie, s32 value) {
    movie->unk_68 = value;
}

MovieVtbl *Movie_GetVtbl(void) {
    return (MovieVtbl *)g_movieVtbl;
}

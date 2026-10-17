#include "common.h"
#include "game/movie.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/stream.h"
#include "psyq/libgpu.h"
#include "psyq/libpress.h"

/*
 * The MDEC movie player (vtable g_movieVtbl, include/game/movie.h). It owns a CD stream of
 * src/game/stream.c (Movie +0x60).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* Movie as Movie_OnSlice reads it: the two rects by u16 halves */
typedef struct MovieSliceView {
    u8 pad_00[0x1C];
    u32 *slice;                /* 0x1C */
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
static MovieVtbl *Movie_GetVtbl(void);
static s32 Movie_AllocBuffers();
static void Movie_FreeBuffers(Movie *movie);
static void Movie_RequestStart(Movie *movie);
static void Movie_OnStreamCallback(Movie *movie);
static void Movie_OnMdecOut(void);
static void Movie_WaitFrame(Movie *movie);
extern u8 g_movieVtbl[];

Movie *g_activeMovie;             /* the movie playing */
s32 g_movieRestartCounter;                /* calls of Movie_OnStopped since the last restart (starts at 1) */
s32 g_mdecReady;                /* 1 once DecDCTReset ran */
extern u8 g_movieClearColor[];

Movie *Movie_Create(ScreenRect *rect, s32 streamArg, s32 skipAlloc) {
    Movie *movie;

    movie = Heap_Alloc(0x6C);
    if (movie == NULL) {
        return NULL;
    }
    if (Movie_GetVtbl()->init(movie, rect, streamArg, skipAlloc) != 0) {
        Heap_Free(movie);
        return NULL;
    }
    return movie;
}

/* Slot 0x08: the stream, the buffers, the MDEC callback; 0 on success */
s32 Movie_Init(Movie *movie, MovieRect *rect, s32 streamArg, s32 skipAlloc) {
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
            movie->startRequest = 0;
            movie->vtbl->setAutoStart(movie, 1);
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
static s32 Movie_AllocBuffers(Movie *movie, MovieRect *rect, s32 skipAlloc) {
    s32 size;
    u32 *buffer;
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

static void Movie_FreeBuffers(Movie *movie) {
    if (movie->skipAlloc == 0) {
        Heap_Free(movie->runLevel[0]);
        Heap_Free(movie->runLevel[1]);
        Heap_Free(movie->streamBuffer);
        Heap_Free(movie->slice);
    }
}

/* Slot 0x40: opens source on the stream and makes this the playing movie; 1 when it cannot */
s32 Movie_Open(Movie *movie, void *source, s32 frameCount, s32 repeat, s32 loops) {
    Stream *stream;
    Display *gfx;

    if (g_activeMovie == NULL) {
        if (movie->autoStart != 0) {
            Movie_RequestStart(movie);
        }
        stream = movie->stream;
        movie->frameCount = frameCount;
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
            gfx->vtbl->clearImage(gfx, g_movieClearColor, &movie->frame);
            return 0;
        }
        return 1;
    }
    return 0;
}

static void Movie_RequestStart(Movie *movie) {
    movie->startRequest = 1;
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
        active->streamStarted = 0;
        stream->vtbl->rewind(stream);
    }
}

static void Movie_OnStreamCallback(Movie *movie) {
    movie->startRequest = -1;
}

/* Slot 0x48, each tick: handles a stream callback (counts loops), else decodes a frame */
s32 Movie_Update(Movie *movie) {
    Movie *active = g_activeMovie;

    if (active == movie && (active->startRequest != 0 || active->streamStarted != 0)) {
        if (active->startRequest != 0) {
            active->stream->vtbl->start(active->stream, 1, active->frameCount);
            if (active->startRequest < 0) {
                if (active->loops == 0 || --active->loops == 0) {
                    active->stream->vtbl->mute(active->stream);
                }
            }
            movie->startRequest = 0;
            movie->streamStarted = 1;
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
        if (active->streamStarted == 0) {
            stream = active->stream;
            stream->vtbl->setCallback(stream, 0, 0);
            active->streamStarted = 1;
            active->stopped = 1;
        }
    }
}

void Movie_EmptySlot50(void) {
}

void Movie_EmptySlot54(void) {
}

/* Slot 0x58: VLC-decodes the stream's next frame into the other run-level buffer; 1 when none */
s32 Movie_ReadFrame(Movie *movie) {
    u32 *frame;
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

void Movie_EmptySlot5C(void) {
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
static void Movie_OnMdecOut(void) {
    Movie *movie = g_activeMovie;

    if (movie != NULL) {
        movie->vtbl->onSlice(movie);
    }
}

static void Movie_WaitFrame(Movie *movie) {
    while (movie->frameDone == 0) {
    }
}

void Movie_SetAutoStart(Movie *movie, s32 value) {
    movie->autoStart = value;
}

static MovieVtbl *Movie_GetVtbl(void) {
    return (MovieVtbl *)g_movieVtbl;
}

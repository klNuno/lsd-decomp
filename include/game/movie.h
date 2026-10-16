#ifndef GAME_MOVIE_H
#define GAME_MOVIE_H

#include "common.h"
#include "game/heap.h"
#include "game/display.h"

/*
 * Movie (vtable g_movieVtbl, 0x6C bytes, Movie_Create): the MDEC player. A stream object
 * (Stream_New) hands it frames; it decodes the VLC data into one of two run-level buffers,
 * sends it through DecDCTin and gets 16-pixel-wide slices back through DecDCTout, each loaded
 * into VRAM by Movie_OnSlice from the MDEC callback. g_activeMovie is the one
 * playing.
 */
typedef struct MovieRect {
    u16 x;                    /* the rect of the GPU object's slot 0x58 (Tim_Upload builds the same) */
    u16 y;
    s32 w;
    s32 h;
} MovieRect;

typedef struct MovieVtbl {
    s32 unk_00;               /* 0x70 */
    void *(*delete_)();       /* 0x04 Object_Delete */
    s32 (*init)();            /* 0x08 Movie_Init (self, rect, streamArg, skipAlloc) */
    void (*destroy)();        /* 0x0C Movie_Destroy */
    u8 pad_10[0x40 - 0x10];
    s32 (*open)();            /* 0x40 Movie_Open (self, source, unk_5C, repeat, loops) */
    void (*start)();          /* 0x44 Movie_Start */
    s32 (*update)();          /* 0x48 Movie_Update */
    void (*stop)();           /* 0x4C Movie_Stop */
    void (*unk_50)();         /* Movie_EmptySlot50, empty */
    void (*unk_54)();         /* Movie_EmptySlot54, empty */
    s32 (*readFrame)();       /* 0x58 Movie_ReadFrame */
    void (*unk_5C)();         /* Movie_EmptySlot5C, empty */
    void (*onSlice)();        /* 0x60 Movie_OnSlice */
    s32 (*onStopped)();       /* 0x64 Movie_OnStopped */
    s32 (*decodeFrame)();     /* 0x68 Movie_DecodeFrame */
    void (*setAutoStart)();       /* 0x6C Movie_SetAutoStart */
} MovieVtbl;

typedef struct Movie {
    MovieVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 skipAlloc;            /* 0x0C nonzero: the buffers are neither allocated nor freed */
    s32 streamBuffer;         /* 0x10 0x12000 bytes handed to the stream */
    s32 runLevel[2];          /* 0x14 w * h * 2 + 0x1000 bytes each, used in turn */
    s32 slice;                /* 0x1C one decoded 16-pixel column, h * 32 bytes */
    MovieRect frame;          /* 0x20 where the frame goes in VRAM */
    MovieRect sliceRect;      /* 0x2C the next slice, w = 16 */
    s32 sliceWords;           /* 0x38 DecDCTout size: 16 * h / 2 */
    s32 runLevelIndex;        /* 0x3C */
    s32 frameReady;           /* 0x40 a frame is VLC-decoded and waits for the MDEC */
    s32 stopped;              /* 0x44 */
    s32 streamEnded;          /* 0x48 */
    s32 frameDone;            /* 0x4C every slice of the frame is out */
    s32 startRequest;               /* -1 from the stream callback Movie_OnStreamCallback, 1 from Movie_RequestStart */
    s32 repeat;               /* 0x54 restart when stopped */
    s32 loops;                /* 0x58 0 = no limit */
    s32 frameCount;               /* passed to the stream's slot 0x50 */
    struct Stream *stream;      /* 0x60 */
    s32 streamStarted;
    s32 autoStart;               /* set by slot 0x6C (1 from init) */
} Movie;

/* Functions of src/game/movie.c that other files call or reference (docs/naming.md, Prototypes) */
Movie *Movie_Create(ScreenRect *rect, s32 streamArg, s32 skipAlloc);

#endif

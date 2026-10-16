#ifndef GAME_STREAM_H
#define GAME_STREAM_H

#include "common.h"
#include "game/heap.h"

/*
 * The CD stream (vtable g_streamVtbl, 0x5C bytes, Stream_New, src/game/stream.c): plays one STR file
 * through the PSY-Q streaming library; the movie player owns one (Movie +0x60).
 */
typedef struct Stream Stream;

/* g_streamVtbl: Object methods, then the stream slots */
typedef struct StreamVtbl {
    s32 unk_00;             /* 0x40 */
    void *(*delete_)();     /* 0x04 Object_Delete */
    void (*init)();         /* 0x08 Stream_Init (self, speedMode, fps, unk3C) */
    void (*destroy)();      /* 0x0C Stream_Destroy */
    u8 pad_10[0x40 - 0x10]; /* Object methods, then 0 */
    void (*setRing)();      /* 0x40 Stream_SetRing (self, buffer, size) */
    s32 (*open)();          /* 0x44 Stream_Open (self, name, retries) */
    void (*close)();        /* 0x48 Stream_Close */
    void (*seek)();         /* 0x4C Stream_Seek (self, CdlLOC) */
    void (*start)();        /* 0x50 Stream_Start (self, start frame, end frame) */
    void (*stop)();         /* 0x54 Stream_Stop */
    void (*rewind)();       /* 0x58 Stream_Rewind */
    void (*unk_5C)();       /* Stream_EmptySlot5C, empty */
    void (*unk_60)();       /* Stream_EmptySlot60, empty */
    void (*mute)();         /* 0x64 Stream_Mute */
    void (*demute)();       /* 0x68 Stream_Demute */
    s32 (*getFrame)();      /* 0x6C Stream_GetFrame (self, &frame, &frameNumber, polls) */
    void (*releaseFrame)(); /* 0x70 Stream_ReleaseFrame (self, frame) */
    void (*unsetRing)();    /* 0x74 Stream_UnsetRing */
    void (*clearRing)();    /* 0x78 Stream_ClearRing */
    void (*setCallback)();  /* 0x7C Stream_SetCallback, empty: nothing sets +0x48 */
} StreamVtbl;

/* PSY-Q CdlFILE */
typedef struct StreamFile {
    u8 pos[4];              /* CdlLOC of the first sector */
    u32 size;               /* bytes */
    s8 name[16];
} StreamFile;

struct Stream {
    StreamVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    StreamFile file;        /* 0x0C CdSearchFile result */
    u8 result[0x2C - 0x24]; /* 0x24 CdSync result (Stream_Sync) */
    s32 state;              /* 0x2C 0 closed, 1 seeked, 2 reading, 4 stopped */
    s32 muted;              /* 0x30 */
    s32 speedMode;          /* 0x34 below 4: double speed (CdRead2 mode 0x1C0, 300 in frameBytes), else 0x140 and 150 */
    u32 frameBytes;         /* 0x38 file bytes per frame */
    s32 unk3C;
    s32 endFrame;           /* 0x40 frame count: file size / frameBytes, or slot 0x50's end frame */
    void *callbackArg;      /* 0x44 */
    void (*callback)(void *); /* 0x48 run for each frame and at the end; 0 from init */
    s32 closeAtEnd;              /* 0x4C non-zero: the end runs the callback and closes */
    s32 ring;               /* 0x50 the ring buffer of slot 0x40; 0 = open fails */
    void (*seekDone)(void *); /* 0x54 non-zero: seeks are asynchronous and call it with callbackArg */
    u32 lastFrame;          /* 0x58 */
};

/* Functions of src/game/stream.c that other files call or reference (docs/naming.md, Prototypes) */
Stream *Stream_New(s32 speedMode, s32 fps, s32 unk3C);

#endif

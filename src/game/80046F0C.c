#include "common.h"
#include "game/heap.h"

/*
 * The CD stream class (vtable g_streamVtbl, 0x5C bytes, created by Stream_New): plays one STR
 * file through the PSY-Q streaming library (StSetRing, StSetStream, CdRead2, StGetNext). The
 * movie player of src/game/80043008.c owns one (Movie +0x60, MovieStreamVtbl there). Only one
 * stream holds the drive at a time, g_activeStream, set by slot 0x44 and cleared by slot 0x48;
 * every other slot does nothing for another stream.
 */

void StFreeRing(void *ring);
void StUnSetRing(void);
extern void StClearRing(void);
extern s32 CdSync(s32, u8 *);
extern void StSetRing(s32, u32);
void SpuSetCommonAttr(void *attr);

/* The first 0x24 bytes of a PSY-Q SpuCommonAttr: master and CD audio volumes */
typedef struct StreamSpuAttr {
    s32 mask;               /* 0x2C3: master volume left and right, CD volume left and right, CD mix */
    s16 masterLeft;
    s16 masterRight;
    s32 masterMode;
    s32 masterX;
    s16 cdLeft;             /* 0x10 */
    s16 cdRight;
    s32 cdReverb;
    s32 cdMix;              /* 0x18 1: CD audio on */
    s32 extVolume;
    s32 extReverb;
} StreamSpuAttr;

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
    void (*unk_5C)();       /* func_800475C8, empty */
    void (*unk_60)();       /* func_800475D0, empty */
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

/* The sector header StGetNext hands out with each frame (PSY-Q StHEADER) */
typedef struct StreamSectorHeader {
    u8 pad_00[0x8];
    u32 frameNumber;
} StreamSectorHeader;

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
    s32 unk4C;              /* 0x4C non-zero: the end runs the callback and closes */
    s32 ring;               /* 0x50 the ring buffer of slot 0x40; 0 = open fails */
    void (*seekDone)(void *); /* 0x54 non-zero: seeks are asynchronous and call it with callbackArg */
    u32 lastFrame;          /* 0x58 */
};

Stream *g_activeStream;         /* the stream that holds the drive */
extern void CdSyncCallback(void *cb);
s32 CdControl(s32 com, u8 *param, s32 result);
void *Heap_Alloc(s32 size);
StreamVtbl *Stream_GetVtbl(void);
s32 CdControlF(s32 com, u8 *param);
void Stream_OnCdSync(u8 status);
s32 CdRead2(s32 mode);
void StSetStream(s32 a, s32 b, s32 c, s32 d, s32 e);
s8 *File_GetPathPrefix(void);
s8 *strcpy(s8 *dst, s8 *src);
s8 *strcat(s8 *dst, s8 *src);
s32 CdSearchFile(void *, s8 *);
s32 Stream_EnableCdAudio();
s32 g_streamCdAudioOn;             /* 1 once Stream_EnableCdAudio turned the CD audio on */
extern s8 g_streamVersionSuffix[];     /* ";1" */
s32 StGetNext(void **frame, StreamSectorHeader **header);
void Stream_NotifyFrame();
void Stream_NotifyEnd();
ObjectVtbl *Object_GetBaseVtbl(void);
extern StreamVtbl g_streamVtbl;

s32 Stream_New(s32 speedMode, s32 fps, s32 unk3C) {
    void *stream;

    stream = Heap_Alloc(0x5C);
    if (stream != NULL) {
        Stream_GetVtbl()->init(stream, speedMode, fps, unk3C);
        return (s32)stream;
    }
    return 0;
}

/* Slot 0x08 */
void Stream_Init(Stream *stream, u32 speedMode, s32 fps, s32 unk3C) {
    Object_GetBaseVtbl()->init(stream);
    stream->vtbl = Stream_GetVtbl();
    stream->speedMode = speedMode;
    stream->muted = 0;
    stream->frameBytes = (speedMode < 4 ? 300 : 150) / fps / 2 * 0x806;
    stream->unk3C = unk3C;
    stream->ring = 0;
    stream->unk4C = 0;
    stream->callback = 0;
    stream->seekDone = 0;
    stream->state = 0;
}

/* Slot 0x0C */
void Stream_Destroy(Stream *stream) {
    stream->vtbl->close(stream);
    Object_GetBaseVtbl()->destroy(stream);
}

/* Slot 0x40: the ring buffer, size in bytes (StSetRing takes sectors) */
void Stream_SetRing(Stream *stream, s32 buffer, u32 size) {
    if (stream->state == 0) {
        StSetRing(buffer, size >> 0xB);
        stream->ring = buffer;
    }
}

/*
 * Slot 0x44: finds \<root>\<name>;1 on the disc, trying retries more times (no limit when
 * negative), takes the drive and seeks to the file; 0 on success.
 */
s32 Stream_Open(Stream *stream, s8 *name, s32 retries) {
    s8 path[0x20];
    void *file;
    s32 initialRetries;

    initialRetries = retries;
    if (stream->state == 0) {
        if (stream->ring != 0) {
            if (g_activeStream == NULL) {
                path[0] = 0x5C;
                strcpy(path + 1, File_GetPathPrefix());
                strcat(path, name);
                strcat(path, g_streamVersionSuffix);
                file = (u8 *)stream + 0xC;
                while (CdSearchFile(file, path) == 0) {
                    if (initialRetries >= 0) {
                        retries -= 1;
                        if (retries < 0) {
                            return 1;
                        }
                    }
                }
                stream->endFrame = (s32)(stream->file.size / stream->frameBytes);
                g_streamCdAudioOn = Stream_EnableCdAudio(stream);
                g_activeStream = stream;
                stream->vtbl->seek(stream, file);
                return 0;
            }
            return 0;
        }
    }
    return 1;
}

/* Master volume half up, CD audio (the STR sound) on at full volume */
s32 Stream_EnableCdAudio(void) {
    StreamSpuAttr attr;

    attr.mask = 0x2C3;
    attr.masterLeft = 0x3FFF;
    attr.masterRight = 0x3FFF;
    attr.cdLeft = 0x7FFF;
    attr.cdRight = 0x7FFF;
    attr.cdMix = 1;
    SpuSetCommonAttr(&attr);
    return 1;
}

/* Slot 0x48: stops and gives the drive back */
void Stream_Close(Stream *stream) {
    Stream *active;

    if (stream->state != 0) {
        active = g_activeStream;
        if (active == stream) {
            active->vtbl->stop(active);
            active->state = 0;
            g_activeStream = NULL;
        }
    }
}

/* Slot 0x4C: CdlSeekL to pos, through Stream_OnCdSync when seekDone is set */
void Stream_Seek(Stream *stream, u8 *pos) {
    if (stream->state != 2 && g_activeStream == stream) {
        if (stream->seekDone != NULL) {
            CdSyncCallback((void *)Stream_OnCdSync);
            CdControlF(0x15, pos);
        } else {
            while (CdControl(0x15, pos, 0) == 0) {
            }
        }
        stream->state = 1;
    }
}

/* CdSyncCallback: on CdlComplete, runs the active stream's seekDone */
void Stream_OnCdSync(u8 status) {
    Stream *active;

    if (g_activeStream != NULL && status == 2) {
        CdSyncCallback(0);
        active = g_activeStream;
        if (active->seekDone != NULL) {
            active->seekDone(active->callbackArg);
        }
    }
}

/* Slot 0x50: StSetStream, CdlSetloc to the file, CdRead2 in streaming mode */
void Stream_Start(Stream *stream, s32 startFrame, s32 endFrame) {
    s32 mode;

    if (stream->state == 1 && g_activeStream == stream) {
        mode = 0x140;
        if (stream->speedMode < 4) {
            mode = 0x1C0;
        }
        if (endFrame != 0) {
            stream->endFrame = endFrame;
        }
        stream->lastFrame = 0;
        StSetStream(0, startFrame, -1, 0, 0);
        stream->vtbl->mute(stream);
        do {
            while (CdControl(2, stream->file.pos, 0) == 0) {}
        } while (CdRead2(mode) == 0);
        stream->vtbl->demute(stream);
        stream->state = 2;
    }
}

/* Slot 0x54: CdlPause after clearing and releasing the ring */
void Stream_Stop(Stream *stream) {
    if (stream->state == 2 && g_activeStream == stream) {
        stream->vtbl->mute(stream);
        stream->vtbl->clearRing(stream);
        stream->vtbl->unsetRing(stream);
        while (CdControl(9, 0, 0) == 0) {
        }
        stream->state = 4;
    }
}

/* Slot 0x58: back to the start of the file */
void Stream_Rewind(Stream *stream) {
    if (stream->state == 4 && g_activeStream == stream) {
        g_activeStream->state = 0;
        g_activeStream->vtbl->seek(g_activeStream, g_activeStream->file.pos);
    }
}

void func_800475C8(void) {
}

void func_800475D0(void) {
}

/* Slot 0x64: CdlMute */
void Stream_Mute(Stream *stream) {
    if (stream->muted == 0 && g_activeStream == stream) {
        while (CdControl(0xB, 0, 0) == 0) {
        }
        stream->muted = 1;
    }
}

/* Slot 0x68: CdlDemute */
void Stream_Demute(Stream *stream) {
    if (stream->muted != 0 && g_activeStream == stream) {
        while (CdControl(0xC, 0, 0) == 0) {
        }
        stream->muted = 0;
    }
}

/*
 * Slot 0x6C: polls StGetNext up to polls times (0x800000 when negative); 0 when no frame came,
 * 1 for a frame, -1 for the last one (past endFrame, or a frame number going back: then
 * *frameNumber is 0).
 */
s32 Stream_GetFrame(Stream *stream, void **frame, s32 *frameNumber, s32 polls) {
    StreamSectorHeader *header;
    s32 n;
    u32 number;

    n = polls;
    if (n < 0) {
        n = 0x800000;
    }
    for (;;) {
        if (StGetNext(frame, &header) == 0) {
            break;
        }
        n--;
        if (n < 0) {
            stream->vtbl->releaseFrame(stream, frame);
            return 0;
        }
    }
    n--;
    number = header->frameNumber;
    *frameNumber = number;
    if (stream->endFrame <= 0) {
        goto ret1;
    }
    if (number < (u32)stream->endFrame) {
        if (number >= stream->lastFrame) {
            goto store;
        }
    }
    if (number < stream->lastFrame) {
        *frameNumber = 0;
    }
    Stream_NotifyFrame(stream, *frame, *frameNumber);
    Stream_NotifyEnd(stream);
    return -1;
store:
    stream->lastFrame = number;
ret1:
    Stream_NotifyFrame(stream, *frame, *frameNumber);
    return 1;
}

/* With a callback: runs it, then releases the frame */
void Stream_NotifyFrame(Stream *stream, void *frame) {
    void (*callback)(void *);

    callback = stream->callback;
    if (callback != NULL) {
        callback(stream->callbackArg);
        stream->vtbl->releaseFrame(stream, frame);
    }
}

void Stream_NotifyEnd(Stream *stream) {
    if (stream->unk4C != 0) {
        stream->callback(stream->callbackArg);
        stream->vtbl->close(stream);
    }
}

/* Slot 0x70 */
void Stream_ReleaseFrame(s32 unused, void *frame) {
    StFreeRing(frame);
}

/* Slot 0x74 */
void Stream_UnsetRing(void) {
    StUnSetRing();
}

/* Slot 0x78 */
void Stream_ClearRing(void) {
    StClearRing();
}

/* No caller found: CdSync into the result bytes */
void Stream_Sync(u8 *stream, s32 mode) {
    CdSync(mode, stream + 0x24);
}

/* Slot 0x7C */
void Stream_SetCallback(void) {
}

StreamVtbl *Stream_GetVtbl(void) {
    return &g_streamVtbl;
}

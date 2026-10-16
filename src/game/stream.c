#include "common.h"
#include "game/stream.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "psyq/libcd.h"
#include "psyq/libspu.h"
#include "psyq/libc.h"

/*
 * The CD stream class (vtable g_streamVtbl, 0x5C bytes, created by Stream_New): plays one STR
 * file through the PSY-Q streaming library (StSetRing, StSetStream, CdRead2, StGetNext). The
 * movie player of src/game/movie.c owns one (Movie +0x60); Stream and StreamVtbl are in include/game/stream.h. Only one
 * stream holds the drive at a time, g_activeStream, set by slot 0x44 and cleared by slot 0x48;
 * every other slot does nothing for another stream.
 *
 * File boundaries: proven (docs/layout.md)
 */


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

/* The sector header StGetNext hands out with each frame (PSY-Q StHEADER) */
typedef struct StreamSectorHeader {
    u8 pad_00[0x8];
    u32 frameNumber;
} StreamSectorHeader;

Stream *g_activeStream;         /* the stream that holds the drive */
static StreamVtbl *Stream_GetVtbl(void);
static void Stream_OnCdSync(u8 status);
static s32 Stream_EnableCdAudio();
s32 g_streamCdAudioOn;             /* 1 once Stream_EnableCdAudio turned the CD audio on */
extern s8 g_streamVersionSuffix[];     /* ";1" */
static void Stream_NotifyFrame();
static void Stream_NotifyEnd();
extern StreamVtbl g_streamVtbl;

Stream *Stream_New(s32 speedMode, s32 fps, s32 unk3C) {
    Stream *stream;

    stream = Heap_Alloc(0x5C);
    if (stream != NULL) {
        Stream_GetVtbl()->init(stream, speedMode, fps, unk3C);
        return stream;
    }
    return NULL;
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
    stream->closeAtEnd = 0;
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
static s32 Stream_EnableCdAudio(void) {
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
static void Stream_OnCdSync(u8 status) {
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

void Stream_EmptySlot5C(void) {
}

void Stream_EmptySlot60(void) {
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
static void Stream_NotifyFrame(Stream *stream, void *frame) {
    void (*callback)(void *);

    callback = stream->callback;
    if (callback != NULL) {
        callback(stream->callbackArg);
        stream->vtbl->releaseFrame(stream, frame);
    }
}

static void Stream_NotifyEnd(Stream *stream) {
    if (stream->closeAtEnd != 0) {
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
static void Stream_Sync(u8 *stream, s32 mode) {
    CdSync(mode, stream + 0x24);
}

/* Slot 0x7C */
void Stream_SetCallback(void) {
}

static StreamVtbl *Stream_GetVtbl(void) {
    return &g_streamVtbl;
}

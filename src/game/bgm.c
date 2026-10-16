#include "common.h"
#include "game/heap.h"
#include "game/sound.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

/*
 * The background music object (vtable g_bgmVtbl, 0x24 bytes, Bgm_New; "WBgm" in its
 * error string): a sound bank (Sound_CreateBank) and a SEQ file (SeqFile_Create), played with
 * the libsnd SsSeq calls. It watches the current display: on each frame message (2) while it
 * waits (state 1), it opens the SEQ once both files are loaded, and plays it when autoPlay is
 * set. The dream runner makes one with the day's bank (Music_PickBank) and no SEQ; the place
 * sets the SEQ Music_PickTrack chose with slot 0x5C and pauses it with slots 0x4C and 0x50.
 */
typedef struct BgmVtbl {
    ObjectVtbl base;
    s32 unk3C;                 /* 0x3C 0 */
    void (*onDisplayEvent)();  /* 0x40 Bgm_OnDisplayEvent (bgm, display, message) */
    void (*play)();            /* 0x44 Bgm_Play */
    void (*stop)();            /* 0x48 Bgm_Stop: stops and closes the SEQ */
    void (*pause)();           /* 0x4C Bgm_Pause */
    void (*resume)();          /* 0x50 Bgm_Resume */
    void (*setVolume)();       /* 0x54 Bgm_SetVolume (bgm, left, right) */
    void (*fadeVolume)();      /* 0x58 Bgm_FadeVolume (bgm, volume, seconds) */
    void (*setSeq)();          /* 0x5C Bgm_SetSeq (bgm, path) */
    void (*setBank)();         /* 0x60 Bgm_SetBank (bgm, path) */
} BgmVtbl;

/* The SEQ file as this unit reads it; the bank is a SoundBank (sound.h) */
typedef struct BgmFileVtbl {
    u8 pad_00[0x4];
    void (*delete_)(void *);
} BgmFileVtbl;

/* The SEQ file of SeqFile_Create (src/game/seq_file.c), a file object */
typedef struct BgmSeq {
    BgmFileVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    s32 data;                  /* 0x10 the SEQ data */
    u8 pad_14[0x2C - 0x14];
    s32 loaded;                /* 0x2C set to 1 once the file is read */
} BgmSeq;

/* SEQ state at +0x1A */
#define BGM_NONE 0              /* no SEQ open */
#define BGM_WAITING 1           /* bank or SEQ still loading: the next frames retry */
#define BGM_OPEN 2              /* SsSeqOpen done */

typedef struct Bgm {
    BgmVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    SoundBank *bank;           /* 0x0C */
    BgmSeq *seq;               /* 0x10 */
    s16 seqId;                 /* 0x14 SsSeqOpen's access number */
    u8 pad_16[0x1A - 0x16];
    u16 state;                 /* 0x1A BGM_NONE, BGM_WAITING, BGM_OPEN */
    u16 paused;                /* 0x1C */
    u16 playing;               /* 0x1E */
    s32 autoPlay;              /* 0x20 play as soon as the SEQ opens */
} Bgm;

extern void SsSeqSetVol(s16, s16, s16);
extern void SsSeqReplay(s16);
extern void SsSeqPause(s16);
extern void SsSeqStop(s16);
extern void SsSeqClose(s16);
extern void SsSeqPlay(s16, s16, s16);
extern s32 Sound_GetTickRate(void);
extern void SsSeqSetCrescendo(s16, s16, s32);
extern s32 Bgm_Open();
extern void *Heap_Alloc(s32 size);
BgmVtbl *Bgm_GetVtbl(void);
extern ObjectVtbl *Object_GetBaseVtbl(void);
extern s32 Display_GetCurrent(void);
s32 g_bgmActive;
extern void *SeqFile_Create(s32);
void *Sound_CreateBank(s32 path);
extern s16 SsSeqOpen(s32, s16);
extern s32 printf(const char *fmt, ...);
extern BgmVtbl g_bgmVtbl;
extern u8 g_seqTable[];

void *Bgm_New(s32 bankPath, s32 seqPath, s32 autoPlay) {
    void *bgm;

    bgm = Heap_Alloc(0x24);
    if (bgm != NULL) {
        Bgm_GetVtbl()->base.init(bgm, bankPath, seqPath, autoPlay);
        return bgm;
    }
    return NULL;
}

void Bgm_Init(Bgm *bgm, s32 bankPath, s32 seqPath, s32 autoPlay) {
    Object_GetBaseVtbl()->init(bgm);
    bgm->vtbl = Bgm_GetVtbl();
    bgm->bank = 0;
    bgm->seq = 0;
    bgm->seqId = 0;
    bgm->state = BGM_NONE;
    bgm->paused = 0;
    bgm->playing = 0;
    bgm->autoPlay = autoPlay;
    g_bgmActive = 1;
    bgm->vtbl->setSeq(bgm, seqPath);
    bgm->vtbl->setBank(bgm, bankPath);
    bgm->vtbl->base.watch(bgm, Display_GetCurrent());
}

void Bgm_Destroy(Bgm *bgm) {
    Object *file;

    g_bgmActive = 0;
    bgm->vtbl->stop(bgm);
    SsSeqClose(bgm->seqId);
    file = (Object *)bgm->bank;
    if (file != NULL) {
        file->vtbl->delete_(file);
    }
    file = (Object *)bgm->seq;
    if (file != NULL) {
        file->vtbl->delete_(file);
    }
    bgm->vtbl->base.unwatch(bgm, Display_GetCurrent());
    Object_GetBaseVtbl()->destroy(bgm);
}

/* Messages from the display (sender type 1) go to slot 0x40. */
void Bgm_OnNotify(Bgm *bgm, Object *sender, s32 message) {
    Object_GetBaseVtbl()->onNotify(bgm, sender, message);
    if ((sender->vtbl->classWord & 0xF) == 1) {
        bgm->vtbl->onDisplayEvent(bgm, sender, message);
    }
}

void Bgm_OnDisplayEvent(Bgm *bgm, s32 display, s32 message) {
    /* Bgm_Open gets no argument here: bgm is still in a0 */
    if ((message == 2) && (bgm->state == BGM_WAITING) && (Bgm_Open() != 0) && (bgm->autoPlay != 0)) {
        bgm->vtbl->play(bgm);
    }
}

/* Opens the SEQ with the bank's VAB once both are loaded; returns 1 when opened. */
s32 Bgm_Open(Bgm *bgm) {
    SoundBank *bank;
    BgmSeq *seq;
    s16 seqId;

    bank = bgm->bank;
    if (bank == NULL) {
        return 0;
    }
    seq = bgm->seq;
    if (seq == NULL) {
        return 0;
    }
    if (bank->transferDone == 0) {
        return 0;
    }
    if (seq->loaded == 0) {
        return 0;
    }
    seqId = SsSeqOpen(seq->data, bank->vabId);
    bgm->seqId = seqId;
    if (seqId == -1) {
        printf("Seq Open error in WBgmHandleMonitorEvent");
    }
    SsSeqSetVol(bgm->seqId, 0x34, 0x34);
    bgm->state = BGM_OPEN;
    return 1;
}

/* SsSeqPlay(SSPLAY_PLAY, 0): the SEQ loops forever. */
void Bgm_Play(Bgm *bgm) {
    if (bgm->playing == 0) {
        SsSeqSetVol(bgm->seqId, 0x34, 0x34);
        SsSeqPlay(bgm->seqId, 1, 0);
        bgm->playing = 1;
    }
}

void Bgm_Stop(Bgm *bgm) {
    if (bgm->playing != 0) {
        SsSeqStop(bgm->seqId);
        SsSeqClose(bgm->seqId);
        bgm->playing = 0;
        bgm->state = BGM_NONE;
    }
}

void Bgm_Pause(Bgm *bgm) {
    if (bgm->paused == 0) {
        SsSeqPause(bgm->seqId);
        bgm->paused = 1;
    }
}

void Bgm_Resume(Bgm *bgm) {
    if (bgm->paused != 0) {
        SsSeqReplay(bgm->seqId);
        bgm->paused = 0;
    }
}

void Bgm_SetVolume(Bgm *bgm, s16 left, s16 right) {
    SsSeqSetVol(bgm->seqId, left, right);
}

/* Sound_GetTickRate is the sound tick rate (60 per second), so seconds become ticks. */
void Bgm_FadeVolume(Bgm *bgm, s16 volume, s32 seconds) {
    SsSeqSetCrescendo(bgm->seqId, volume, Sound_GetTickRate() * seconds);
}

/* Stops the current SEQ, frees its file, loads path (0: none) and opens it when it can. */
void Bgm_SetSeq(Bgm *bgm, s32 path) {
    BgmSeq *seq;

    if (bgm->playing != 0) {
        bgm->vtbl->stop(bgm);
    }
    seq = bgm->seq;
    if (seq != NULL) {
        seq->vtbl->delete_(seq);
        bgm->seq = NULL;
    }
    if (path != 0) {
        bgm->seq = SeqFile_Create(path);
        if (Bgm_Open(bgm) != 0) {
            if (bgm->autoPlay != 0) {
                bgm->vtbl->play(bgm);
            }
        } else if (bgm->state == BGM_NONE) {
            bgm->state = BGM_WAITING;
        }
    }
}

/* The same for the sound bank. */
void Bgm_SetBank(Bgm *bgm, s32 path) {
    SoundBank *bank;

    if (bgm->playing != 0) {
        bgm->vtbl->stop(bgm);
    }
    bank = bgm->bank;
    if (bank != NULL) {
        bank->vtbl->delete_(bank);
        bgm->bank = NULL;
    }
    if (path != 0) {
        bgm->bank = Sound_CreateBank(path);
        if (Bgm_Open(bgm) != 0) {
            if (bgm->autoPlay != 0) {
                bgm->vtbl->play(bgm);
            }
        } else if (bgm->state == BGM_NONE) {
            bgm->state = BGM_WAITING;
        }
    }
}

BgmVtbl *Bgm_GetVtbl(void) {
    return &g_bgmVtbl;
}

/* 1 while a Bgm exists: Sound_DestroyBank keeps the sound system up then. */
s32 Bgm_IsActive(void) {
    return g_bgmActive;
}

/* The SEQ attribute table area given to SsSetTableSize (src/game/sound_bank.c). */
s32 Bgm_GetSeqTable(void) {
    return (s32)g_seqTable;
}

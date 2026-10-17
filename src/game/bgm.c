#include "common.h"
#include "game/bgm.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/sound_bank.h"
#include "game/seq_file.h"
#include "psyq/libsnd.h"
#include "psyq/libc.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

static s32 Bgm_Open();
static BgmVtbl *Bgm_GetVtbl(void);
s32 g_bgmActive;
extern BgmVtbl g_bgmVtbl;
extern s8 g_seqTable[];

void *Bgm_New(s8 *bankPath, s8 *seqPath, s32 autoPlay) {
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
    SoundBank *bank;
    SeqFile *seq;

    g_bgmActive = 0;
    bgm->vtbl->stop(bgm);
    SsSeqClose(bgm->seqId);
    bank = bgm->bank;
    if (bank != NULL) {
        bank->vtbl->delete_(bank);
    }
    seq = bgm->seq;
    if (seq != NULL) {
        seq->vtbl->delete_(seq);
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
static s32 Bgm_Open(Bgm *bgm) {
    SoundBank *bank;
    SeqFile *seq;
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
void Bgm_SetSeq(Bgm *bgm, s8 *path) {
    SeqFile *seq;

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
void Bgm_SetBank(Bgm *bgm, s8 *path) {
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

static BgmVtbl *Bgm_GetVtbl(void) {
    return &g_bgmVtbl;
}

/* 1 while a Bgm exists: Sound_DestroyBank keeps the sound system up then. */
s32 Bgm_IsActive(void) {
    return g_bgmActive;
}

/* The SEQ attribute table area given to SsSetTableSize (src/game/sound_bank.c). */
s8 *Bgm_GetSeqTable(void) {
    return g_seqTable;
}

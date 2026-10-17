#ifndef GAME_BGM_H
#define GAME_BGM_H

#include "common.h"
#include "game/heap.h"
#include "game/sound_bank.h"
#include "game/seq_file.h"

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

/* The bank is a SoundBank (sound_bank.h), the SEQ a SeqFile (seq_file.h). */
/* SEQ state at +0x1A */
#define BGM_NONE 0              /* no SEQ open */
#define BGM_WAITING 1           /* bank or SEQ still loading: the next frames retry */
#define BGM_OPEN 2              /* SsSeqOpen done */

typedef struct Bgm {
    BgmVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    SoundBank *bank;           /* 0x0C */
    SeqFile *seq;               /* 0x10 */
    s16 seqId;                 /* 0x14 SsSeqOpen's access number */
    u8 pad_16[0x1A - 0x16];
    u16 state;                 /* 0x1A BGM_NONE, BGM_WAITING, BGM_OPEN */
    u16 paused;                /* 0x1C */
    u16 playing;               /* 0x1E */
    s32 autoPlay;              /* 0x20 play as soon as the SEQ opens */
} Bgm;

/* Functions of src/game/bgm.c that other files call or reference (docs/naming.md, Prototypes) */
void *Bgm_New(s8 *bankPath, s8 *seqPath, s32 autoPlay);
s32 Bgm_IsActive(void);
s8 *Bgm_GetSeqTable(void);

#endif

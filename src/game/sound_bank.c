#include "common.h"
#include "game/sound.h"

/*
 * Sound: the PSY-Q sound bank (VAB) that a model holds at +0x58 and its tone table (vtable
 * g_soundBankVtbl). Several functions see the bank through a view struct where a field has another
 * type or width there.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* Heap and root object services. */
void *Heap_Alloc(s32 size);
void Heap_Free(s32 block);
void *File_GetBackendVtbl(void);

/* Vtable of the root object class returned by File_GetBackendVtbl (heap.h ObjectVtbl: init 0x08, destroy 0x0C). */
typedef struct ObjectRootVtbl {
    u8 pad_00[0x8];
    void (*init)(void *object);     /* 0x08 */
    void (*destroy)(s32 object);    /* 0x0C, the caller passes the pointer as s32 */
    u8 pad_10[0x54];
    void (*unk_64)(void *object);   /* 0x64, not named in heap.h */
} ObjectRootVtbl;

/* One tone of a program: 0x20 bytes, the layout SsUtGetVagAtr fills (center and fine are read here). */
/* Sound_LoadProgramTable view of the bank: the VAB header at 0x2C and the tables built from it. */
typedef struct SoundBankVab {
    SoundBankVtbl *vt;
    u8 pad_04[0xC];
    s32 vabBuffer;
    u8 pad_14[0x18];
    u8 vabHeader[0x12];        /* 0x2C, filled by SsUtGetVabHdr (ps at +0x12, ts at +0x14) */
    u16 programCount;          /* 0x3E */
    u16 toneCount;             /* 0x40 */
    u8 pad_42[0xA];
    u8 *toneData;              /* 0x4C */
    u8 **programTones;         /* 0x50 */
    s16 vabId;                 /* 0x54 */
    u8 pad_56[0x2];
    u16 transferDone;          /* 0x58 */
} SoundBankVab;

/* Sound_PlayTone view of the bank: the tone table pointers and the note shift (u16 there). */
typedef struct SoundBankTones {
    u8 pad_00[0x50];
    SoundTone **programTones;  /* 0x50 */
    s16 vabId;                 /* 0x54 */
    u8 pad_56[0xA];
    u16 noteShift;             /* 0x60 */
} SoundBankTones;

extern SoundBankVtbl g_soundBankVtbl;
SoundBankVtbl *Sound_GetBankClass(void);
s32 g_spuReady;
s32 g_soundRateSet;
s32 g_seqTimerStarted;
s32 g_bankCount;
s32 g_vabBuffer;
s32 g_soundTickRate;
extern s8 g_vabHeaderExt[];
extern s8 g_vabBodyExt[];

/* Sound services of PSY-Q and the SPU helpers. */
void SsUtKeyOffV(s16 voice);
void SsUtAllKeyOff(s32 arg0);
void SsSetMute(s16 mute);
s16 SsVabTransCompleted(s16 immediateFlag);
void SsVabClose(s16 vabId);
s16 SsVabOpenHead(void *vabBuffer, s16 vabId);
s16 SsVabTransBody(void *vabBuffer, s16 vabId);
s16 SsUtGetVabHdr(s16 vabId, void *vabhdr);
s16 SsUtGetProgAtr(s16 vabId, s16 progNum, u8 *progatr);
s16 SsUtGetVagAtr(s16 vabId, s16 progNum, s16 toneNum, u8 *vagatr);
void SsSetMVol(s16 voll, s16 volr);
s16 SsUtKeyOn(s16 vabId, s16 prog, s16 tone, s16 note, s16 fine, s16 voll, s16 volr);
s16 SsUtAutoVol(s16 vc, s16 start_vol, s16 end_vol, s16 delta_time);
void SsSetTableSize(s8 *arg0, s16 arg1, s16 arg2);

/* Other functions of the game code used here. */
s8 *File_JoinPath(s8 *arg0, s8 *arg1, s8 *arg2, s8 *arg3);
s32 Bgm_IsActive(void);
void Seq_StopTimer(void);
void Spu_Quit(void);
void Spu_ResetCold(void);
s32 Bgm_GetSeqTable(void);
void Seq_SetRate(s32 arg0);
void Seq_StartTimer(void);
s32 strlen(u8 *s);
s8 *strcpy(s8 *dst, s8 *src);

void *Sound_CreateBank(s32 initParam) {
    void *bank;

    bank = Heap_Alloc(0x64);
    if (bank != 0) {
        Sound_GetBankClass()->init(bank, initParam);
        return bank;
    }
    return 0;
}

void Sound_InitBank(SoundBank *bank, s8 *path) {
    s8 fullPath[0x20];
    s8 *pathCopy;

    ((ObjectRootVtbl *)File_GetBackendVtbl())->init(bank);
    bank->vtbl = Sound_GetBankClass();
    bank->toneData = 0;
    bank->programTones = 0;
    bank->vabId = 0;
    bank->muted = 0;
    bank->vtbl->setOctave(bank, 0);
    bank->transferDone = 0;
    bank->transferring = 0;
    bank->path = 0;
    if (g_spuReady == 0) {
        Spu_ResetCold();
        g_spuReady = 1;
        SsSetTableSize((s8 *)Bgm_GetSeqTable(), 2, 1);
    }
    if (g_soundRateSet == 0) {
        g_soundTickRate = 0x3C;
        Seq_SetRate(1);
        g_soundRateSet = 1;
    }
    g_bankCount += 1;
    if (path != 0) {
        pathCopy = Heap_Alloc(strlen((u8 *)path) + 1);
        if (pathCopy != NULL) {
            bank->path = (s32)pathCopy;
            strcpy(pathCopy, path);
            File_JoinPath(fullPath, pathCopy, (s8 *)0, g_vabHeaderExt);
            bank->state = 1;
            bank->vtbl->unk_6C(bank, fullPath);
        }
    }
}

void Sound_DestroyBank(SoundBank *bank) {
    SsVabClose(bank->vabId);
    if (--g_bankCount < 0) {
        g_bankCount = 0;
    }
    if (g_bankCount == 0 && Bgm_IsActive() == 0) {
        g_spuReady = 0;
        g_seqTimerStarted = 0;
        g_soundRateSet = 0;
        Seq_StopTimer();
        Spu_Quit();
    }
    Heap_Free(bank->toneData);
    Heap_Free(bank->programTones);
    Heap_Free(bank->path);
    ((ObjectRootVtbl *)File_GetBackendVtbl())->destroy((s32)bank);
}

void Sound_UpdateBank(SoundBank *bank) {
    u8 fullPath[0x20];
    s32 oldVabBuffer;
    s16 ret;

    switch (bank->state) {
        case 0:
            break;
        case 1:
            if (bank->unk_24 & 0x200) {
                bank->vabId = SsVabOpenHead((void *)bank->vabBuffer, -1);
                File_JoinPath((s8 *)fullPath, (s8 *)bank->path, (s8 *)0, g_vabBodyExt);
                bank->state = 6;
                oldVabBuffer = bank->vabBuffer;
                bank->vabBuffer = 0;
                g_vabBuffer = oldVabBuffer;
                bank->vtbl->unk_58(bank, fullPath, oldVabBuffer);
                if (bank->path != 0) {
                    Heap_Free(bank->path);
                    bank->path = 0;
                }
            }
            break;
        case 6:
            if (bank->unk_24 & 0x200) {
                ret = SsVabTransBody((void *)bank->vabBuffer, bank->vabId);
                bank->vabId = ret;
                if (ret != -1) {
                    bank->transferring = 1;
                    bank->vtbl->pollTransfer(bank, 1);
                }
            }
            break;
    }
}

s32 Sound_PollTransfer(SoundBank *bank, s32 allowFinish) {
    s32 ret = 0;

    if (bank->transferring != 0) {
        if (allowFinish != 0) {
            SsVabTransCompleted(1);
            bank->transferring = 0;
            bank->transferDone = 1;
            bank->vtbl->loadProgramTable(bank);
            ret = 1;
        }
    }
    return ret;
}

void Sound_LoadProgramTable(SoundBankVab *bank) {
    s32 i;
    s32 j;
    u8 *vagp;
    u8 progAtr[0x10];

    if (bank->transferDone == 0) {
        return;
    }
    bank->vt->unk_5C();
    bank->vabBuffer = g_vabBuffer;
    if (SsUtGetVabHdr(bank->vabId, &bank->vabHeader) == -1) {
        return;
    }
    bank->toneData = Heap_Alloc(bank->toneCount << 5);
    if (bank->toneData == NULL) {
        return;
    }
    bank->programTones = (u8 **)Heap_Alloc(bank->programCount << 2);
    if (bank->programTones == NULL) {
        return;
    }
    vagp = bank->toneData;
    for (i = 0; i < bank->programCount; i++) {
        bank->programTones[i] = vagp;
        if (SsUtGetProgAtr(bank->vabId, i, progAtr) == -1) {
            return;
        }
        for (j = 0; j < progAtr[0]; j++) {
            if (SsUtGetVagAtr(bank->vabId, i, j, vagp) == -1) {
                return;
            }
            vagp += 0x20;
        }
    }
    if (g_seqTimerStarted == 0) {
        Seq_StartTimer();
        SsSetMVol(0x78, 0x78);
        g_seqTimerStarted = 1;
    }
}

s16 Sound_PlayTone(SoundBankTones *bank, s32 sound, s16 volume, s16 endVolume) {
    s32 program;
    SoundTone *tone;
    s16 voice;

    if (sound < 0) {
        return -1;
    }
    program = sound >> 4;
    tone = bank->programTones[program];
    tone += sound - (program << 4);
    voice = SsUtKeyOn(bank->vabId, program, sound - (program << 4), tone->center + bank->noteShift, tone->fine, volume, volume);
    if (voice < 0) {
        return -1;
    }
    SsUtAutoVol(voice, volume, endVolume, 2);
    return voice;
}

s32 Sound_StopVoice(s32 bank, s32 voice) {
    if (voice < 0x18) {
        SsUtKeyOffV(voice);
    } else {
        SsUtAllKeyOff(0);
    }
    return -1;
}

void Sound_MuteBank(SoundBank *bank) {
    if (bank->muted == 0) {
        SsSetMute(1);
        bank->muted = 1;
    }
}

void Sound_UnmuteBank(SoundBank *bank) {
    if (bank->muted != 0) {
        SsSetMute(0);
        bank->muted = 0;
    }
}

void Sound_EmptySlot90(void) {
}

void Sound_EmptySlot94(void) {
}

void Sound_EmptySlot98(void) {
}

void Sound_SetOctave(SoundBank *bank, s32 octave) {
    bank->noteShift = octave * 12 - 24;
}

SoundBankVtbl *Sound_GetBankClass(void) {
    return &g_soundBankVtbl;
}

s32 Sound_GetBankCount(void) {
    return g_bankCount;
}

s32 Sound_GetTickRate(void) {
    return g_soundTickRate;
}

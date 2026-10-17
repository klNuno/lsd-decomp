#include "common.h"
#include "game/sound_bank.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/bgm.h"
#include "psyq/libsnd.h"
#include "psyq/libc.h"

/*
 * Sound: the PSY-Q sound bank (VAB) that a model holds at +0x58 and its tone table (vtable
 * g_soundBankVtbl).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern SoundBankVtbl g_soundBankVtbl;
s32 g_spuReady;
s32 g_soundRateSet;
s32 g_seqTimerStarted;
s32 g_bankCount;
u8 *g_vabBuffer;
s32 g_soundTickRate;
extern s8 g_vabHeaderExt[];
extern s8 g_vabBodyExt[];


SoundBank *Sound_CreateBank(s8 *path) {
    SoundBank *bank;

    bank = Heap_Alloc(0x64);
    if (bank != NULL) {
        Sound_GetBankClass()->init(bank, path);
        return bank;
    }
    return NULL;
}

void Sound_InitBank(SoundBank *bank, s8 *path) {
    s8 fullPath[0x20];
    s8 *pathCopy;

    File_GetBackendVtbl()->init(bank);
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
        SsInit();
        g_spuReady = 1;
        SsSetTableSize(Bgm_GetSeqTable(), 2, 1);
    }
    if (g_soundRateSet == 0) {
        g_soundTickRate = 0x3C;
        SsSetTickMode(1);
        g_soundRateSet = 1;
    }
    g_bankCount += 1;
    if (path != 0) {
        pathCopy = Heap_Alloc(strlen((u8 *)path) + 1);
        if (pathCopy != NULL) {
            bank->path = pathCopy;
            strcpy(pathCopy, path);
            File_JoinPath(fullPath, pathCopy, NULL, g_vabHeaderExt);
            bank->state = 1;
            bank->vtbl->loadAsync(bank, fullPath);
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
        SsEnd();
        SsQuit();
    }
    Heap_Free(bank->toneData);
    Heap_Free(bank->programTones);
    Heap_Free(bank->path);
    File_GetBackendVtbl()->destroy(bank);
}

void Sound_OnBankLoaded(SoundBank *bank) {
    s8 fullPath[0x20];
    u8 *oldVabBuffer;
    s16 ret;

    switch (bank->state) {
        case 0:
            break;
        case 1:
            if (bank->flags & 0x200) {
                bank->vabId = SsVabOpenHead(bank->data, -1);
                File_JoinPath(fullPath, bank->path, NULL, g_vabBodyExt);
                bank->state = 6;
                oldVabBuffer = bank->data;
                bank->data = 0;
                g_vabBuffer = oldVabBuffer;
                bank->vtbl->load(bank, fullPath, oldVabBuffer);
                if (bank->path != 0) {
                    Heap_Free(bank->path);
                    bank->path = 0;
                }
            }
            break;
        case 6:
            if (bank->flags & 0x200) {
                ret = SsVabTransBody(bank->data, bank->vabId);
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

void Sound_LoadProgramTable(SoundBank *bank) {
    s32 i;
    s32 j;
    u8 *vagp;
    u8 progAtr[0x10];

    if (bank->transferDone == 0) {
        return;
    }
    bank->vtbl->freeData();
    bank->data = g_vabBuffer;
    if (SsUtGetVabHdr(bank->vabId, &bank->vabHeader) == -1) {
        return;
    }
    bank->toneData = Heap_Alloc(bank->toneCount << 5);
    if (bank->toneData == NULL) {
        return;
    }
    bank->programTones = Heap_Alloc(bank->programCount << 2);
    if (bank->programTones == NULL) {
        return;
    }
    vagp = bank->toneData;
    for (i = 0; i < bank->programCount; i++) {
        bank->programTones[i] = (SoundTone *)vagp;
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
        SsStart();
        SsSetMVol(0x78, 0x78);
        g_seqTimerStarted = 1;
    }
}

s16 Sound_PlayTone(SoundBank *bank, s32 sound, s16 volume, s16 endVolume) {
    s32 program;
    SoundTone *tone;
    s16 voice;

    if (sound < 0) {
        return -1;
    }
    program = sound >> 4;
    tone = bank->programTones[program];
    tone += sound - (program << 4);
    voice = SsUtKeyOn(bank->vabId, program, sound - (program << 4), tone->center + bank->noteShift.low, tone->fine, volume, volume);
    if (voice < 0) {
        return -1;
    }
    SsUtAutoVol(voice, volume, endVolume, 2);
    return voice;
}

s32 Sound_StopVoice(SoundBank *bank, s32 voice) {
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
    bank->noteShift.word = octave * 12 - 24;
}

SoundBankVtbl *Sound_GetBankClass(void) {
    return &g_soundBankVtbl;
}

/* Returns g_bankCount; nothing in the executable calls it or holds its address. */
static s32 Sound_GetBankCount(void) {
    return g_bankCount;
}

s32 Sound_GetTickRate(void) {
    return g_soundTickRate;
}

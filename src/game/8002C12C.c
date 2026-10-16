#include "common.h"
#include "game/sound.h"

/*
 * Sound: the PSY-Q sound bank (VAB) that a model holds at +0x58, its tone table, and the handler
 * nodes that play sounds from the bank once per tick (see 8005C508.c). Several functions see the
 * bank through a view struct where a field has another type or width there.
 */

/* Heap and root object services. */
void *Heap_Alloc(s32 size);
void Heap_Free(s32 block);
void *File_GetBackendVtbl(void);

/* The object that MapModels_OnLoaded marks: only 0x30 is used here. */
typedef struct RootObject {
    u8 pad_00[0x30];
    s32 unk_30;
} RootObject;

/* Vtable of the root object class returned by File_GetBackendVtbl (heap.h ObjectVtbl: init 0x08, destroy 0x0C). */
typedef struct ObjectRootVtbl {
    u8 pad_00[0x8];
    void (*init)(void *object);     /* 0x08 */
    void (*destroy)(s32 object);    /* 0x0C, the caller passes the pointer as s32 */
    u8 pad_10[0x54];
    void (*unk_64)(void *object);   /* 0x64, not named in heap.h */
} ObjectRootVtbl;

/* Vtable of the 0x34-byte object class at g_mapModelsVtbl (MapModels_New; stage.h calls it a model set). */
typedef struct ModelSetVtbl {
    u8 pad_00[0x8];
    void (*init)(void *modelSet, s32 param);   /* 0x08 */
    u8 pad_0C[0x60];
    void (*unk_6C)(void *modelSet, s32 param); /* 0x6C */
} ModelSetVtbl;

typedef struct ModelSet {
    ModelSetVtbl *vt;     /* 0x00 */
    u8 pad_04[0x28];
    s32 unk_2C;
    s32 unk_30;
} ModelSet;

extern ModelSetVtbl g_mapModelsVtbl;
ModelSetVtbl *MapModels_GetVtbl(void);

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

/* Globals of the bank code, in their original order. */
s32 g_fileNullEnabled;
s32 g_fileNullOption;
s32 g_spuReady;
s32 g_soundRateSet;
s32 g_seqTimerStarted;
s32 g_bankCount;
s32 g_vabBuffer;
s32 g_soundTickRate;
extern s8 g_vabHeaderExt[];
extern s8 g_vabBodyExt[];
extern u8 g_fileNullVtbl[];

/* One cell of the 20 by 20 grid: 0xC bytes, 400 cells, a chain of records through unk_08. */
typedef struct GridRecord {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    s16 unk_06;
    s32 unk_08;   /* offset of the next record, 0 at the end of the chain */
} GridRecord;

/* The grid item that MapModels_NextModel fills for one cell (0x3C bytes). */
typedef struct GridItem {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
    u8 pad_1C[0x10];
    s16 unk_2C;
    s16 unk_2E;
    s32 unk_30;
    s32 unk_34;   /* offset of the next record in the chain */
    s32 unk_38;
} GridItem;

typedef struct GridObjectVtbl {
    u8 pad_00[0x80];
    s32 (*unk_80)(void *object, u16 id, s32 cell, void *item);
} GridObjectVtbl;

typedef struct GridObject {
    GridObjectVtbl *vt;
} GridObject;

/* The grid context: the record table at unk_10 and the object at unk_2C that places the item. */
typedef struct GridContext {
    u8 pad_00[0x10];
    u8 *unk_10;
    u8 pad_14[0x18];
    GridObject *unk_2C;
} GridContext;

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
s32 MapModels_New(s32 initParam) {
    s32 modelSet;

    modelSet = (s32)Heap_Alloc(0x34);
    if (modelSet != 0) {
        MapModels_GetVtbl()->init((void *)modelSet, initParam);
        return modelSet;
    }
    return 0;
}

void MapModels_Init(ModelSet *modelSet, s32 initParam) {
    ((ObjectRootVtbl *)File_GetBackendVtbl())->init(modelSet);
    modelSet->vt = MapModels_GetVtbl();
    modelSet->unk_2C = 0;
    modelSet->unk_30 = 0;
    if (initParam != 0) {
        modelSet->vt->unk_6C(modelSet, initParam);
    }
}

void MapModels_Destroy(s32 object) {
    ((ObjectRootVtbl *)File_GetBackendVtbl())->destroy(object);
}

void MapModels_OnLoaded(RootObject *object) {
    object->unk_30 = 1;
    ((ObjectRootVtbl *)File_GetBackendVtbl())->unk_64(object);
}

s32 MapModels_NextModel(GridContext *context, GridItem *item, s32 cellIndex) {
    GridRecord *record;
    s32 nextOffset;
    u16 itemId;
    s32 val6;
    u8 *base;

    if (cellIndex < 0x190) {
        nextOffset = item->unk_34;
        if (nextOffset != 0) {
            base = context->unk_10;
            record = (GridRecord *)(base + nextOffset);
            item->unk_30 = 1;
        } else {
            record = (GridRecord *)(cellIndex * 0xC + 8 + context->unk_10);
            item->unk_30 = 0;
        }
        item->unk_34 = record->unk_08;
        if (record->unk_00 != 0) {
            item->unk_0C = ((cellIndex % 20) << 0xB) + 0x400;
            val6 = record->unk_06;
            item->unk_14 = ((cellIndex / 20) << 0xB) + 0x400;
            item->unk_10 = val6 << 0xB;
            item->unk_1A = record->unk_05 << 0xA;
            item->unk_2C = record->unk_01;
            item->unk_2E = record->unk_04;
            itemId = record->unk_02;
            item->unk_38 = itemId;
            return context->unk_2C->vt->unk_80(context->unk_2C, itemId, cellIndex, item);
        }
        return -1;
    }
    return 0;
}

ModelSetVtbl *MapModels_GetVtbl(void) {
    return &g_mapModelsVtbl;
}

s32 func_8002C3B8(void) {
    return 0;
}

void File_NullInit(void) {
}

void File_NullDestroy(void) {
}

void func_8002C3D0(void) {
    u8 buf[0x40];
}

void File_NullOpen(void) {
    u8 buf[0x40];
}

void File_NullClose(void) {
}

void File_NullSeek(void) {
}

void func_8002C400(void) {
}

s32 File_NullRead(void) {
    return 0;
}

void File_NullLoad(void) {
}

void File_NullRunQueue(void) {
}

void File_NullLoadAsync(void) {
}

void File_NullStop(void) {
}

void File_NullCancel(void) {
}

void *File_GetNullVtbl(void) {
    return g_fileNullVtbl;
}

s32 File_NullGetEnabled(s32 *valueOut) {
    if (valueOut != NULL) {
        *valueOut = g_fileNullOption;
    }
    return g_fileNullEnabled;
}

s32 File_NullEnable(s32 firstValue, s32 secondValue) {
    g_fileNullEnabled = firstValue;
    g_fileNullOption = secondValue;
    return 1;
}

s32 File_NullGetVSyncMode(void) {
    return 0;
}

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
                    bank->vtbl->unk_78(bank, 1);
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
            bank->vtbl->unk_7C(bank);
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

void func_8002CBDC(void) {
}

void func_8002CBE4(void) {
}

void func_8002CBEC(void) {
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

s32 HandlerNode_Start(s32 arg0, HandlerNode *node, s32 nodeId, s32 owner, s32 handler) {
    HandlerVoice *voice;
    s32 noVoice;
    s32 i;

    if (node->id != 0) {
        return 0;
    }
    voice = node->voices;
    noVoice = -1;
    node->id = nodeId;
    node->owner = owner;
    node->handler = handler;
    for (i = 2; i >= 0; i--) {
        voice->voice = noVoice;
        voice++;
    }
    node->tick = 0;
    node->fadeSteps = 0xA;
    return 1;
}

void HandlerNode_Stop(SoundBank *bank, HandlerNode *node) {
    HandlerVoice *voice;
    s32 i;

    voice = node->voices;
    for (i = 0; i < 3; i++, voice++) {
        if (voice->voice >= 0) {
            voice->voice = bank->vtbl->stopVoice(bank, voice->voice);
        }
    }
    node->id = 0;
}

void HandlerNode_Run(SoundBank *bank, HandlerNode *node) {
    HandlerVoice *voice;
    void (*callback)(s32, void *);
    s32 i;
    s32 activeVoice;

    if (node->id > 0) {
        for (voice = node->voices, i = 0; i < 3; i++, voice++) {
            voice->sound = -1;
            voice->octave = 0;
            voice->volume = 0x7F;
            voice->endVolume = 0x40;
        }
        callback = (void (*)(s32, void *)) node->handler;
        node->fade = 0;
        if (callback != NULL) {
            callback(node->owner, node);
        }
        if (node->fade >= 0) {
            for (voice = node->voices, i = 0; i < 3; i++, voice++) {
                if (voice->sound >= 0) {
                    activeVoice = voice->voice;
                    if (activeVoice >= 0) {
                        bank->vtbl->stopVoice(bank, activeVoice);
                    }
                    bank->vtbl->setOctave(bank, voice->octave);
                    voice->voice = bank->vtbl->playTone(bank, voice->sound << 4, voice->volume - (voice->volume / node->fadeSteps) * node->fade, voice->endVolume - (voice->endVolume / node->fadeSteps) * node->fade);
                } else if (voice->sound == -2) {
                    activeVoice = voice->voice;
                    if (activeVoice >= 0) {
                        bank->vtbl->stopVoice(bank, activeVoice);
                    }
                }
            }
        }
        node->tick++;
    }
}

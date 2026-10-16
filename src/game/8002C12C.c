#include "common.h"

/*
 * Sound: the PSY-Q sound bank (VAB) that a model holds at +0x58, its tone table, and the handler
 * nodes that play sounds from the bank once per tick (see 8005C508.c). Several functions see the
 * bank through a view struct where a field has another type or width there.
 */

/* Heap and root object services. */
void *Heap_Alloc(s32 size);
void Heap_Free(s32 block);
void *func_80026CAC(void);

/* The object that func_8002C238 marks: only 0x30 is used here. */
typedef struct RootObject {
    u8 pad_00[0x30];
    s32 unk_30;
} RootObject;

/* Vtable of the root object class returned by func_80026CAC (heap.h ObjectVtbl: init 0x08, destroy 0x0C). */
typedef struct ObjectRootVtbl {
    u8 pad_00[0x8];
    void (*init)(void *object);     /* 0x08 */
    void (*destroy)(s32 object);    /* 0x0C, the caller passes the pointer as s32 */
    u8 pad_10[0x54];
    void (*unk_64)(void *object);   /* 0x64, not named in heap.h */
} ObjectRootVtbl;

/* Vtable of the 0x34-byte object class at D_8006D940 (func_8002C12C; stage.h calls it a model set). */
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

extern ModelSetVtbl D_8006D940;
ModelSetVtbl *func_8002C3A8(void);

/* One tone of a program: 0x20 bytes, the layout SsUtGetVagAtr fills (center and fine are read here). */
typedef struct SoundTone {
    u8 pad_00[4];
    u8 center;   /* 0x04 passed to SsUtKeyOn as the note */
    u8 fine;     /* 0x05 passed to SsUtKeyOn as the fine tuning */
    u8 pad_06[0x1A];
} SoundTone;

/* Vtable of the sound bank class at D_8006DA34 (Sound_GetBankClass); slots 0x80, 0x84, 0x9C are the sound calls. */
typedef struct SoundBankVtbl {
    u8 pad_00[0x8];
    void (*init)(void *bank, s32 param);                                     /* 0x08 Sound_CreateBank */
    u8 pad_0C[0x4C];
    void (*unk_58)(void *bank, void *fullPath, s32 vabBuffer);               /* 0x58 */
    void (*unk_5C)(void);                                                    /* 0x5C */
    u8 pad_60[0xC];
    void (*unk_6C)(void *bank, s8 *fullPath);                                /* 0x6C */
    u8 pad_70[0x8];
    void (*unk_78)(void *bank, s32 param);                                   /* 0x78 */
    void (*unk_7C)(void *bank);                                              /* 0x7C */
    s32 (*playTone)(void *bank, s32 sound, s32 volume, s32 endVolume);      /* 0x80 Sound_PlayTone */
    s32 (*stopVoice)(void *bank, s32 voice);                                 /* 0x84 Sound_StopVoice */
    u8 pad_88[0x14];
    void (*setOctave)(void *bank, s32 octave);                               /* 0x9C Sound_SetOctave */
} SoundBankVtbl;

/* The sound bank: 0x64 bytes, allocated by Sound_CreateBank with the class vtable at D_8006DA34. */
typedef struct SoundBank {
    /* 0x00 */ SoundBankVtbl *vt;
    /* 0x04 */ u8 pad_04[0xC];
    /* 0x10 */ s32 vabBuffer;     /* VAB data being loaded; g_vabBuffer keeps it between calls */
    /* 0x14 */ u8 pad_14[0x10];
    /* 0x24 */ s32 unk_24;        /* flags: bit 0x200 means the file has been read */
    /* 0x28 */ u8 pad_28[0x2];
    /* 0x2A */ u16 state;         /* 0 idle, 1 open the VAB header, 6 transfer the body */
    /* 0x2C */ u8 pad_2C[0x20];   /* the VAB header, see SoundBankVab */
    /* 0x4C */ s32 toneData;      /* SoundBankVab: u8 *, one 0x20-byte tone per entry */
    /* 0x50 */ s32 programTones;  /* SoundBankVab: u8 **, SoundBankTones: SoundTone ** */
    /* 0x54 */ s16 vabId;
    /* 0x56 */ s16 muted;         /* 1 after SsSetMute(1) */
    /* 0x58 */ u16 transferDone;  /* 1 once SsVabTransCompleted has run */
    /* 0x5A */ u16 transferring;  /* 1 while the VAB body is sent */
    /* 0x5C */ s32 path;          /* heap copy of the file path given to Sound_InitBank */
    /* 0x60 */ s32 noteShift;     /* octave * 12 - 24, set by Sound_SetOctave */
} SoundBank;

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

extern SoundBankVtbl D_8006DA34;
SoundBankVtbl *Sound_GetBankClass(void);

/* Globals of the bank code, in their original order. */
s32 D_8008A8B0;
s32 D_8008A8B4;
s32 D_8008A8B8;
s32 D_8008A8BC;
s32 D_8008A8C0;
s32 g_bankCount;
s32 g_vabBuffer;
s32 D_8008A8CC;
extern s8 D_8008A8D0[];
extern s8 D_8008A8D4[];
extern u8 D_8006D9BC[];

/* One voice of a handler node (5 words, 0x14 bytes); see 8005C508.c HandlerVoice. */
typedef struct HandlerVoice {
    s32 voice;     /* 0x00 SPU voice playing, -1 none */
    s32 sound;     /* 0x04 sound to start this tick, -1 none, -2 stops the voice */
    s32 octave;    /* 0x08 bank slot 0x9C: notes shift by octave * 12 - 24 */
    s32 volume;    /* 0x0C start volume, 0x7F by default */
    s32 endVolume; /* 0x10 volume the fade slides to, 0x40 by default */
} HandlerVoice;

/* A handler node (0x54 bytes), the second argument of a handler; see 8005C508.c HandlerNode. */
typedef struct HandlerNode {
    s32 id;                  /* 0x00 entity type + 1 while running, 0 once stopped */
    s32 tick;                /* 0x04 runs so far, counted by func_8002CD08 */
    s32 owner;               /* 0x08 the entity, the handler's first argument */
    s32 handler;             /* 0x0C the handler function */
    s32 fade;                /* 0x10 set by the handler, lowers both volumes by volume / fadeSteps */
    s32 fadeSteps;           /* 0x14 10 */
    HandlerVoice voices[3];  /* 0x18 */
} HandlerNode;

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

/* The grid item that func_8002C278 fills for one cell (0x3C bytes). */
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
s8 *func_800270C4(s8 *arg0, s8 *arg1, s8 *arg2, s8 *arg3);
s32 func_8003A05C(void);
void func_800329D8(void);
void func_80032A7C(void);
void func_80032368(void);
s32 func_8003A068(void);
void func_80032588(s32 arg0);
void func_80032998(void);
s32 strlen(u8 *s);
s8 *strcpy(s8 *dst, s8 *src);
s32 func_8002C12C(s32 initParam) {
    s32 modelSet;

    modelSet = (s32)Heap_Alloc(0x34);
    if (modelSet != 0) {
        func_8002C3A8()->init((void *)modelSet, initParam);
        return modelSet;
    }
    return 0;
}

void func_8002C18C(ModelSet *modelSet, s32 initParam) {
    ((ObjectRootVtbl *)func_80026CAC())->init(modelSet);
    modelSet->vt = func_8002C3A8();
    modelSet->unk_2C = 0;
    modelSet->unk_30 = 0;
    if (initParam != 0) {
        modelSet->vt->unk_6C(modelSet, initParam);
    }
}

void func_8002C200(s32 object) {
    ((ObjectRootVtbl *)func_80026CAC())->destroy(object);
}

void func_8002C238(RootObject *object) {
    object->unk_30 = 1;
    ((ObjectRootVtbl *)func_80026CAC())->unk_64(object);
}

s32 func_8002C278(GridContext *context, GridItem *item, s32 cellIndex) {
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

ModelSetVtbl *func_8002C3A8(void) {
    return &D_8006D940;
}

s32 func_8002C3B8(void) {
    return 0;
}

void func_8002C3C0(void) {
}

void func_8002C3C8(void) {
}

void func_8002C3D0(void) {
    u8 buf[0x40];
}

void func_8002C3E0(void) {
    u8 buf[0x40];
}

void func_8002C3F0(void) {
}

void func_8002C3F8(void) {
}

void func_8002C400(void) {
}

s32 func_8002C408(void) {
    return 0;
}

void func_8002C410(void) {
}

void func_8002C418(void) {
}

void func_8002C420(void) {
}

void func_8002C428(void) {
}

void func_8002C430(void) {
}

void *func_8002C438(void) {
    return D_8006D9BC;
}

s32 func_8002C448(s32 *valueOut) {
    if (valueOut != NULL) {
        *valueOut = D_8008A8B4;
    }
    return D_8008A8B0;
}

s32 func_8002C468(s32 firstValue, s32 secondValue) {
    D_8008A8B0 = firstValue;
    D_8008A8B4 = secondValue;
    return 1;
}

s32 func_8002C478(void) {
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

    ((ObjectRootVtbl *)func_80026CAC())->init(bank);
    bank->vt = Sound_GetBankClass();
    bank->toneData = 0;
    bank->programTones = 0;
    bank->vabId = 0;
    bank->muted = 0;
    bank->vt->setOctave(bank, 0);
    bank->transferDone = 0;
    bank->transferring = 0;
    bank->path = 0;
    if (D_8008A8B8 == 0) {
        func_80032368();
        D_8008A8B8 = 1;
        SsSetTableSize((s8 *)func_8003A068(), 2, 1);
    }
    if (D_8008A8BC == 0) {
        D_8008A8CC = 0x3C;
        func_80032588(1);
        D_8008A8BC = 1;
    }
    g_bankCount += 1;
    if (path != 0) {
        pathCopy = Heap_Alloc(strlen((u8 *)path) + 1);
        if (pathCopy != NULL) {
            bank->path = (s32)pathCopy;
            strcpy(pathCopy, path);
            func_800270C4(fullPath, pathCopy, (s8 *)0, D_8008A8D0);
            bank->state = 1;
            bank->vt->unk_6C(bank, fullPath);
        }
    }
}

void Sound_DestroyBank(SoundBank *bank) {
    SsVabClose(bank->vabId);
    if (--g_bankCount < 0) {
        g_bankCount = 0;
    }
    if (g_bankCount == 0 && func_8003A05C() == 0) {
        D_8008A8B8 = 0;
        D_8008A8C0 = 0;
        D_8008A8BC = 0;
        func_800329D8();
        func_80032A7C();
    }
    Heap_Free(bank->toneData);
    Heap_Free(bank->programTones);
    Heap_Free(bank->path);
    ((ObjectRootVtbl *)func_80026CAC())->destroy((s32)bank);
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
                func_800270C4((s8 *)fullPath, (s8 *)bank->path, (s8 *)0, D_8008A8D4);
                bank->state = 6;
                oldVabBuffer = bank->vabBuffer;
                bank->vabBuffer = 0;
                g_vabBuffer = oldVabBuffer;
                bank->vt->unk_58(bank, fullPath, oldVabBuffer);
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
                    bank->vt->unk_78(bank, 1);
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
            bank->vt->unk_7C(bank);
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
    if (D_8008A8C0 == 0) {
        func_80032998();
        SsSetMVol(0x78, 0x78);
        D_8008A8C0 = 1;
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
    return &D_8006DA34;
}

s32 Sound_GetBankCount(void) {
    return g_bankCount;
}

s32 func_8002CC28(void) {
    return D_8008A8CC;
}

s32 func_8002CC34(s32 arg0, HandlerNode *node, s32 nodeId, s32 owner, s32 handler) {
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

void func_8002CC84(SoundBank *bank, HandlerNode *node) {
    HandlerVoice *voice;
    s32 i;

    voice = node->voices;
    for (i = 0; i < 3; i++, voice++) {
        if (voice->voice >= 0) {
            voice->voice = bank->vt->stopVoice(bank, voice->voice);
        }
    }
    node->id = 0;
}

void func_8002CD08(SoundBank *bank, HandlerNode *node) {
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
                        bank->vt->stopVoice(bank, activeVoice);
                    }
                    bank->vt->setOctave(bank, voice->octave);
                    voice->voice = bank->vt->playTone(bank, voice->sound << 4, voice->volume - (voice->volume / node->fadeSteps) * node->fade, voice->endVolume - (voice->endVolume / node->fadeSteps) * node->fade);
                } else if (voice->sound == -2) {
                    activeVoice = voice->voice;
                    if (activeVoice >= 0) {
                        bank->vt->stopVoice(bank, activeVoice);
                    }
                }
            }
        }
        node->tick++;
    }
}

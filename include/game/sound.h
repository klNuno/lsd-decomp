#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#include "common.h"

/*
 * Sound banks and handler voices (src/game/8002C12C.c).
 * A sound bank (class vtable g_soundBankVtbl, Sound_GetBankClass, 0x64 bytes) loads one VAB into sound
 * RAM, builds its tone tables and starts and stops voices with SsUtKeyOn. Menus and screens own one
 * (scene.h MenuScreen +0x48, menu.h Menu +0x48 and Card +0x6C), tasks may own one (stage.h Task +0x34),
 * and every model has one at +0x58 (Model in src/game/8005C508.c, DreamSys +0x58, Entity +0x58):
 * the voices a behaviour handler asks for play on it (HandlerNode, HandlerNode_Run).
 */

/* One tone of the VAB, 0x20 bytes. */
typedef struct SoundTone {
    u8 pad_00[4];
    u8 center;   /* 0x04 passed to SsUtKeyOn as the note */
    u8 fine;     /* 0x05 passed to SsUtKeyOn as the fine tuning */
    u8 pad_06[0x1A];
} SoundTone;

/* Vtable g_soundBankVtbl (Sound_GetBankClass); slots 0x80, 0x84, 0x9C are the sound calls. */
typedef struct SoundBankVtbl {
    u8 pad_00[0x4];
    void *(*delete_)();                                                      /* 0x04 Object_Delete */
    void (*init)(void *bank, s32 param);                                     /* 0x08 Sound_InitBank, from Sound_CreateBank */
    u8 pad_0C[0x58 - 0x0C];
    void (*unk_58)(void *bank, void *fullPath, s32 vabBuffer);               /* 0x58 */
    void (*unk_5C)(void);                                                    /* 0x5C */
    u8 pad_60[0x6C - 0x60];
    void (*unk_6C)(void *bank, s8 *fullPath);                                /* 0x6C */
    u8 pad_70[0x78 - 0x70];
    void (*pollTransfer)(void *bank, s32 param);                                   /* 0x78 */
    void (*loadProgramTable)(void *bank);                                              /* 0x7C */
    s32 (*playTone)(void *bank, s32 sound, s32 volume, s32 endVolume);      /* 0x80 Sound_PlayTone: SsUtKeyOn, then SsUtAutoVol */
    s32 (*stopVoice)(void *bank, s32 voice);                                 /* 0x84 Sound_StopVoice */
    u8 pad_88[0x9C - 0x88];
    void (*setOctave)(void *bank, s32 octave);                               /* 0x9C Sound_SetOctave; -1 from the menu */
} SoundBankVtbl;

/* The sound bank, 0x64 bytes. Sound_LoadProgramTable and Sound_PlayTone read +0x4C to +0x60 with
   other types (views SoundBankVab and SoundBankTones in src/game/8002C12C.c). */
typedef struct SoundBank {
    /* 0x00 */ SoundBankVtbl *vtbl;
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

/* One of the three voices of a HandlerNode (0x14 bytes); HandlerNode_Run resets sound, octave and volumes before each run. */
typedef struct HandlerVoice {
    s32 voice;     /* 0x00 SPU voice playing (sound bank slot 0x80), -1 none */
    s32 sound;     /* 0x04 bank program to start this tick, -1 none, -2 stops the voice */
    s32 octave;    /* 0x08 sound bank slot 0x9C (Sound_SetOctave): notes shift by octave * 12 - 24, 0 by default */
    s32 volume;    /* 0x0C start volume, 0x7F by default */
    s32 endVolume; /* 0x10 volume SsUtAutoVol slides to, 0x40 by default */
} HandlerVoice;

/* The handler node (0x54 bytes) at Entity +0x9C, the handler's second argument: HandlerNode_Start registers it,
   HandlerNode_Stop removes it, HandlerNode_Run runs handler(owner, node) once per tick. */
typedef struct HandlerNode {
    s32 id;                  /* 0x00 entity type + 1 while registered, 0 once stopped */
    s32 tick;                /* 0x04 runs so far, counted by HandlerNode_Run */
    s32 owner;               /* 0x08 the entity, passed back as the handler's first argument */
    s32 handler;             /* 0x0C the record's handler */
    s32 fade;                /* 0x10 each step lowers both volumes by volume / fadeSteps; < 0 plays nothing (slot 0x148 by distance) */
    s32 fadeSteps;           /* 0x14 10 */
    HandlerVoice voices[3];  /* 0x18 */
} HandlerNode;

#endif

#ifndef GAME_SOUND_BANK_H
#define GAME_SOUND_BANK_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * Sound banks (src/game/sound_bank.c).
 * A sound bank (class vtable g_soundBankVtbl, Sound_GetBankClass, 0x64 bytes) loads one VAB into sound
 * RAM, builds its tone tables and starts and stops voices with SsUtKeyOn. Menus and screens own one
 * (menu_screen.h MenuScreen +0x48, menu.h Menu +0x48, card.h Card +0x6C), tasks may own one (task.h Task +0x34),
 * and every model has one at +0x58 (Model in src/game/model.c, DreamSys +0x58, Entity +0x58):
 * the voices a behaviour handler asks for play on it (HandlerNode in handler_node.h, HandlerNode_Run).
 */

/* One tone of a program, 0x20 bytes: the layout SsUtGetVagAtr fills (sound_bank.c reads center and fine). */
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
    void (*init)(void *bank, s8 *path);                                      /* 0x08 Sound_InitBank, from Sound_CreateBank */
    u8 pad_0C[0x58 - 0x0C];
    void (*load)(void *bank, void *fullPath, u8 *vabBuffer);               /* 0x58 */
    void (*freeData)(void);                                                    /* 0x5C */
    u8 pad_60[0x6C - 0x60];
    void (*loadAsync)(void *bank, s8 *fullPath);                                /* 0x6C */
    u8 pad_70[0x78 - 0x70];
    void (*pollTransfer)(void *bank, s32 param);                                   /* 0x78 */
    void (*loadProgramTable)(void *bank);                                              /* 0x7C */
    s32 (*playTone)(void *bank, s32 sound, s32 volume, s32 endVolume);      /* 0x80 Sound_PlayTone: SsUtKeyOn, then SsUtAutoVol */
    s32 (*stopVoice)(void *bank, s32 voice);                                 /* 0x84 Sound_StopVoice */
    u8 pad_88[0x9C - 0x88];
    void (*setOctave)(void *bank, s32 octave);                               /* 0x9C Sound_SetOctave; -1 from the menu */
} SoundBankVtbl;

/* The sound bank, 0x64 bytes: a file object (file_base.h) whose data is the VAB being loaded. */
typedef struct SoundBank {
    /* 0x00 */ SoundBankVtbl *vtbl;   /* 0x00 to 0x2B: the File header (file_base.h) */
    /* 0x04 */ ListNode *watched;
    /* 0x08 */ ListNode *watchers;
    /* 0x0C */ s32 isOpen;
    /* 0x10 */ u8 *data;          /* the VAB header, then the body; g_vabBuffer keeps it between calls */
    /* 0x14 */ s32 size;
    /* 0x18 */ CdlLocDir cdPos;
    /* 0x1C */ u32 cdSize;
    /* 0x20 */ u16 keepData;
    /* 0x22 */ u16 pending;
    /* 0x24 */ u32 flags;         /* bit 0x200: the file has been read */
    /* 0x28 */ u16 direct;
    /* 0x2A */ u16 state;         /* 0 idle, 1 open the VAB header, 6 transfer the body */
    /* 0x2C */ u8 vabHeader[0x12]; /* the 0x20-byte VabHdr SsUtGetVabHdr fills */
    /* 0x3E */ u16 programCount;  /* VabHdr.ps */
    /* 0x40 */ u16 toneCount;     /* VabHdr.ts */
    /* 0x42 */ u8 pad_42[0xA];
    /* 0x4C */ u8 *toneData;      /* one 0x20-byte SoundTone per tone, filled by SsUtGetVagAtr */
    /* 0x50 */ SoundTone **programTones; /* one pointer per program into toneData */
    /* 0x54 */ s16 vabId;
    /* 0x56 */ s16 muted;         /* 1 after SsSetMute(1) */
    /* 0x58 */ u16 transferDone;  /* 1 once SsVabTransCompleted has run */
    /* 0x5A */ u16 transferring;  /* 1 while the VAB body is sent */
    /* 0x5C */ s8 *path;          /* heap copy of the file path given to Sound_InitBank */
    /* 0x60 */ union {
        s32 word;                 /* octave * 12 - 24, set by Sound_SetOctave */
        u16 low;                  /* Sound_PlayTone adds the low half to the note */
    } noteShift;
} SoundBank;

/* Functions of src/game/sound_bank.c that other files call or reference (docs/naming.md, Prototypes) */
SoundBank *Sound_CreateBank(s8 *path);
SoundBankVtbl *Sound_GetBankClass(void);
s32 Sound_GetTickRate(void);

#endif

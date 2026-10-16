#ifndef GAME_SOUND_BANK_H
#define GAME_SOUND_BANK_H

#include "common.h"
#include "game/sound.h"

/* Functions of src/game/sound_bank.c that other files call or reference (docs/naming.md, Prototypes) */
void *Sound_CreateBank(s32 initParam);
SoundBankVtbl *Sound_GetBankClass(void);
s32 Sound_GetTickRate(void);

#endif

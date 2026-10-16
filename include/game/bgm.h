#ifndef GAME_BGM_H
#define GAME_BGM_H

#include "common.h"

/* Functions of src/game/bgm.c that other files call or reference (docs/naming.md, Prototypes) */
void *Bgm_New(s32 bankPath, s32 seqPath, s32 autoPlay);
s32 Bgm_IsActive(void);
s32 Bgm_GetSeqTable(void);

#endif

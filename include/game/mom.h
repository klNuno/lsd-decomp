#ifndef GAME_MOM_H
#define GAME_MOM_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/mom.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Mom_Create(s32 source);
s32 Mom_ScanFirstFrame(Mom *mom);
void Mom_ReadPacket(Mom *mom, s32 packet, s32 id, s32 type, s32 flag, s32 length);
MomVtbl *Mom_GetVtbl(void);

#endif

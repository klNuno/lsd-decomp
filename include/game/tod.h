#ifndef GAME_TOD_H
#define GAME_TOD_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/tod.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Tod_Create(s32 source);
s32 Tod_ScanFrame(Tod *tod, u8 *ids, s32 *tmdId, void *packet);
u32 *Tod_ReadPacket(void *tod, u32 *packet, s8 *id, s8 *type, s8 *flag, s8 *length);
TodVtbl *Tod_GetVtbl(void);

#endif

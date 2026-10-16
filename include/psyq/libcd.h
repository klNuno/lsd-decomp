#ifndef PSYQ_LIBCD_H
#define PSYQ_LIBCD_H

#include "types.h"

/* LIBCD functions the game calls: the drive (file_cd.c, app.c) and streaming (stream.c). */

s32 CdInit(void);
void CdSetDebug(s32 level);
s32 CdControl(s32 com, u8 *param, s32 result);
s32 CdControlF(s32 com, u8 *param);
s32 CdControlB(s32 com, u8 *param, s32 result);
s32 CdSync(s32 mode, u8 *result);
void CdSyncCallback(void *func);
s32 CdRead(s32 sectors, void *buf, s32 mode);
s32 CdReadSync(s32 mode, u8 *result);
s32 CdRead2(s32 mode);
void CdFlush(void);
s32 CdSearchFile(void *fp, s8 *name);
s32 CdPosToInt(u8 *pos);
void CdIntToPos(s32 i, u8 *pos);

/* Streaming ring (movies) */
void StSetRing(s32 ring, u32 size);
void StClearRing(void);
void StUnSetRing(void);
void StFreeRing(void *ring);
void StSetStream(s32 mode, s32 start, s32 end, s32 func1, s32 func2);
s32 StGetNext(void *addr, void *header);

#endif

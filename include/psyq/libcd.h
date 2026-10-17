#ifndef PSYQ_LIBCD_H
#define PSYQ_LIBCD_H

#include "types.h"

/* LIBCD functions the game calls: the drive (file_cd.c, app.c) and streaming (stream.c). */

/* A CD position, minute, second, sector and track in BCD (Sony's CdlLOC). */
typedef struct CdlLOC {
    u8 minute;
    u8 second;
    u8 sector;
    u8 track;
} CdlLOC;

/* What CdSearchFile fills (Sony's CdlFILE): position, size in bytes, name. */
typedef struct CdlFILE {
    CdlLOC pos;
    u32 size;
    s8 name[16];
} CdlFILE;

/* The CdControl family takes a CdlLOC for the seek commands and mode bytes for others, CdIntToPos
   writes into the game's u8 scratch buffer as well as into CdlLOC fields: void * for both. */

s32 CdInit(void);
void CdSetDebug(s32 level);
s32 CdControl(s32 com, void *param, s32 result);
s32 CdControlF(s32 com, void *param);
s32 CdControlB(s32 com, u8 *param, s32 result);
s32 CdSync(s32 mode, u8 *result);
void CdSyncCallback(void *func);
s32 CdRead(s32 sectors, void *buf, s32 mode);
s32 CdReadSync(s32 mode, u8 *result);
s32 CdRead2(s32 mode);
void CdFlush(void);
s32 CdSearchFile(CdlFILE *fp, s8 *name);
s32 CdPosToInt(CdlLOC *pos);
void CdIntToPos(s32 i, void *pos);

/* Streaming ring (movies) */
void StSetRing(s32 ring, u32 size);
void StClearRing(void);
void StUnSetRing(void);
void StFreeRing(void *ring);
void StSetStream(s32 mode, s32 start, s32 end, s32 func1, s32 func2);
s32 StGetNext(void *addr, void *header);

#endif

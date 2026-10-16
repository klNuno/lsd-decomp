#ifndef PSYQ_LIBAPI_H
#define PSYQ_LIBAPI_H

#include "types.h"

/*
 * LIBAPI functions the game calls (BIOS calls and the heap), declared from the game's own call
 * sites: memory card files and events in card.c, root counters in seq_timer.c, the heap in heap.c.
 */

/* Heap */
void SetMem(s32 megabytes);
void *malloc(u32 size);
void free(void *ptr);

/* Critical sections and events */
s32 EnterCriticalSection(void);
s32 ExitCriticalSection(void);
s32 OpenEvent(u32 desc, s32 spec, s32 mode, s32 func);
s32 CloseEvent(s32 event);
s32 EnableEvent(s32 event);
s32 DisableEvent(s32 event);
s32 TestEvent(s32 event);

/* Root counters */
void SetRCnt(s32 spec, u16 target, s32 mode);
void StartRCnt(s32 spec);
void ResetRCnt(s32 spec);

/* Memory card BIOS */
void InitCARD(s32 padEnable);
void StartCARD(void);
void _bu_init(void);
s32 _card_info(s32 channel);
s32 _card_load(s32 channel);

/* Files (the memory card device "bu00:") */
s32 open(char *name, s32 flags);
s32 close(s32 fd);
s32 read(s32 fd, void *buf, s32 n);
s32 write(s32 fd, void *buf, s32 n);
s32 lseek(s32 fd, s32 offset, s32 whence);
s32 delete(char *name);
s32 format(char *fs);

#endif

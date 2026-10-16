#ifndef GAME_FILE_CD_H
#define GAME_FILE_CD_H

#include "common.h"

/* Functions of src/game/file_cd.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/file_cd.c */
struct DirEntry;
void *File_GetVtable(void);
s32 File_IsBusy(void);
s32 File_IsDone(void);
s32 File_GetOpKind(void);
s32 File_GetState(void);
s32 File_GetEnabled(s32 *outValue);
s32 File_Enable(s32 enabled, s32 param1, s32 mode);
void File_SetDirTable(s32 table);
void File_SetDirCount(s32 count);
s32 File_GetDirCount(void);
s32 File_ResolveEntries(struct DirEntry *entries, s32 count);
void File_Lock(void);
void File_Unlock(void);
s32 File_GetVSyncMode(void);

#endif

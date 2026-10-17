#ifndef GAME_FILE_CD_H
#define GAME_FILE_CD_H

#include "common.h"

/* Functions of src/game/file_cd.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/file_cd.c */
/* The CD position of a directory entry: minute, second, sector, track (a CdlLOC). */
typedef struct CdlLocDir {
    u8 minute, second, sector, track;
} CdlLocDir;

/* One entry of the CD directory table (g_fileDirTable) and of the path table, 0x1C bytes. */
typedef struct DirEntry {
    s8 name[0x14];
    CdlLocDir pos;
    s32 size;
} DirEntry;

struct FileVtbl;
struct FileVtbl *File_GetVtable(void);
s32 File_IsBusy(void);
s32 File_IsDone(void);
s32 File_GetOpKind(void);
s32 File_GetState(void);
s32 File_GetEnabled(s32 *outValue);
s32 File_Enable(s32 enabled, s32 param1, s32 mode);
void File_SetDirTable(DirEntry *table);
void File_SetDirCount(s32 count);
s32 File_GetDirCount(void);
s32 File_ResolveEntries(DirEntry *entries, s32 count);
void File_Lock(void);
void File_Unlock(void);
s32 File_GetVSyncMode(void);

#endif

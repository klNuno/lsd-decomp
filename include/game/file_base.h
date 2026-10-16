#ifndef GAME_FILE_BASE_H
#define GAME_FILE_BASE_H

#include "common.h"
#include "game/loader.h"

/* Functions of src/game/file_base.c that other files call or reference (docs/naming.md, Prototypes) */
s32 File_Delete(File *file);
void File_LoadWhole(); /* unprototyped: file_cd.c calls it with no arguments */
void File_FreeData(File *file);
void func_80026C80(void);
void File_MarkLoaded(File *file);
FileVtbl *File_GetBaseVtbl(void);
FileVtbl *File_GetBackendVtbl(void);
FileSource *File_MakeSource(FileSource *source, s32 data, s32 path, s32 unk_08);
void File_SetBackend(s32 backend);
void File_LockBackend(void);
void File_UnlockBackend(void);
void File_EnableWait(s32 enabled, s32 option, s32 vsyncMode);
s32 File_AddDirEntries(s32 table, s32 count);
void File_SetPathPrefix(void *rootDir);
s8 *File_GetPathPrefix(void);
s8 *File_JoinPath(s8 *dst, s8 *name, s8 *prefix, s8 *suffix);

#endif

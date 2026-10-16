#ifndef GAME_FILE_NULL_H
#define GAME_FILE_NULL_H

#include "common.h"

/* Functions of src/game/file_null.c that other files call or reference (docs/naming.md, Prototypes) */
void *File_GetNullVtbl(void);
s32 File_NullGetEnabled(s32 *valueOut);
s32 File_NullEnable(s32 firstValue, s32 secondValue);
s32 File_NullGetVSyncMode(void);

#endif

#ifndef GAME_SEQ_FILE_H
#define GAME_SEQ_FILE_H

#include "common.h"
#include "game/file_base.h"

/* Functions of src/game/seq_file.c that other files call or reference (docs/naming.md, Prototypes) */
s32 SeqFile_Create(s32 path);
FileVtbl *SeqFile_GetVtbl(void);

#endif

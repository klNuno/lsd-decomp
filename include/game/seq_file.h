#ifndef GAME_SEQ_FILE_H
#define GAME_SEQ_FILE_H

#include "common.h"
#include "game/file_base.h"

/* A file object (file_base.h) whose data is a SEQ file. */
typedef struct SeqFile {
    FileVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    s32 data;               /* 0x10 the SEQ, given to SsSeqOpen */
    s32 size;               /* 0x14 */
    u8 pad_18[0x2C - 0x18];
    s32 loaded;             /* 0x2C set by SeqFile_OnLoaded */
} SeqFile;

/* Functions of src/game/seq_file.c that other files call or reference (docs/naming.md, Prototypes) */
SeqFile *SeqFile_Create(s8 *path);
FileVtbl *SeqFile_GetVtbl(void);

#endif

#ifndef GAME_SEQ_FILE_H
#define GAME_SEQ_FILE_H

#include "common.h"
#include "game/file_base.h"

/* A file object (file_base.h) whose data is a SEQ file. */
typedef struct SeqFile {
    FileVtbl *vtbl;           /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    s32 data;                 /* 0x10 the SEQ, given to SsSeqOpen (an s32 there) */
    s32 size;
    CdlLocDir cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
    s32 loaded;             /* 0x2C set by SeqFile_OnLoaded */
} SeqFile;

/* Functions of src/game/seq_file.c that other files call or reference (docs/naming.md, Prototypes) */
SeqFile *SeqFile_Create(s8 *path);
FileVtbl *SeqFile_GetVtbl(void);

#endif

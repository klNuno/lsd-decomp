#include "common.h"
#include "game/seq_file.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "psyq/libc.h"

/*
 * SeqFile: vtable g_seqFileVtbl 0x8006EED8 (tag 0xB03), 0x30 bytes, SeqFile_Create: a file class
 * (file_base.h) loaded with loadAsync; the music player (src/game/bgm.c) hands its data to SsSeqOpen
 * once +0x2C is set.
 *
 * File boundaries: likely (docs/layout.md)
 */

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

extern FileVtbl g_seqFileVtbl;

s32 SeqFile_Create(s32 path) {
    void *file;

    file = Heap_Alloc(0x30);
    if (file != 0) {
        SeqFile_GetVtbl()->init(file, path);
        return (s32)file;
    }
    return 0;
}

/* Slot 0x08: starts loading the path, copied first. */
void SeqFile_Init(SeqFile *file, s8 *path) {
    char name[0x20];

    File_GetBackendVtbl()->init(file);
    file->vtbl = SeqFile_GetVtbl();
    file->loaded = 0;
    if (path != NULL) {
        strcpy(name, path);
        file->vtbl->loadAsync(file, name);
    }
}

/* Slot 0x0C */
void SeqFile_Destroy(SeqFile *file) {
    file->loaded = 0;
    File_GetBackendVtbl()->destroy(file);
}

/* Slot 0x64 */
void SeqFile_OnLoaded(SeqFile *file) {
    file->loaded = 1;
}

FileVtbl *SeqFile_GetVtbl(void) {
    return &g_seqFileVtbl;
}

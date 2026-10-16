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

extern FileVtbl g_seqFileVtbl;

SeqFile *SeqFile_Create(s8 *path) {
    SeqFile *file;

    file = Heap_Alloc(0x30);
    if (file != NULL) {
        SeqFile_GetVtbl()->init(file, path);
        return file;
    }
    return NULL;
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

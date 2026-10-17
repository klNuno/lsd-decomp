#include "common.h"
#include "game/file_base.h"
#include "game/heap.h"
#include "game/file_cd.h"
#include "game/file_null.h"
#include "psyq/libc.h"

/*
 * The file base class (vtable g_fileBaseVtbl, returned by File_GetBaseVtbl, include/game/file_base.h):
 * delete, init, destroy, load the whole file, free its data. File_SetBackend picks the back end
 * (0x13 the CD, 0x23 an empty one) and copies its I/O slots into every file class; the helpers
 * at the end forward to the CD functions of src/game/file_cd.c only when the CD back end is on.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The back end ids: the tag word of the back end's vtable. */
#define FILE_BACKEND_CD 0x13   /* g_fileVtbl, src/game/file_cd.c */
#define FILE_BACKEND_NULL 0x23 /* g_fileNullVtbl: every I/O slot is empty */
s32 g_fileBackend;
s32 g_fileDirTableSet;
static void File_CopyIoSlots(FileVtbl *dst, FileVtbl *src);
extern FileVtbl *(*g_fileClassGetters[])();
extern FileVtbl g_fileBaseVtbl[];
s8 *g_filePathPrefix;

/* File base slot 0x04, shared by every file class. */
s32 File_Delete(File *file) {
    file->keepData = 0;
    file->vtbl->destroy(file);
    Object_GetBaseVtbl()->destroy(file);
    Heap_Free(file);
    return 0;
}

/* File base slot 0x08. */
void File_InitBase(File *file) {
    Object_GetBaseVtbl()->init(file);
    file->vtbl = File_GetBaseVtbl();
    file->isOpen = 0;
    file->data = 0;
    file->size = 0;
    file->keepData = 0;
    file->pending = 0;
    file->flags = 0;
    file->direct = 0;
    file->state = 0;
}

/* File base slot 0x0C: close, then free the data. */
void File_DestroyBase(File *file) {
    file->vtbl->close();
    file->vtbl->freeData(file);
}

/* File base slot 0x58: open path, read the whole file into a new block, close. */
void File_LoadWhole(File *file, char *path) {
    s32 wasOpen;
    s32 size;
    u8 *buffer;

    if (file->data == NULL) {
        wasOpen = file->isOpen;
        file->isOpen = 0;
        file->vtbl->open(file, path, 1, 0);
        size = file->vtbl->seek(file, 0, 2);
        buffer = Heap_Alloc(size);
        if (buffer != NULL) {
            file->vtbl->seek(file, 0, 0);
            file->vtbl->read(file, buffer, size);
            file->vtbl->close(file);
            file->data = buffer;
            file->size = size;
            file->isOpen = wasOpen;
            return;
        }
        Heap_Free(0);
        file->vtbl->close(file);
    }
}

/* File base slot 0x5C: frees owned data (size != 0) unless keepData is set. */
void File_FreeData(File *file) {
    if (file->data != 0 && file->size != 0 && file->keepData == 0) {
        Heap_Free(file->data);
        file->data = 0;
    }
}

void File_EmptySlot60(void) {
}

/* File base slot 0x64 (onLoaded). */
void File_MarkLoaded(File *file) {
    file->flags |= 1;
}

FileVtbl *File_GetBaseVtbl(void) {
    return g_fileBaseVtbl;
}

/* The vtable of the back end in use. */
FileVtbl *File_GetBackendVtbl(void) {
    if (g_fileBackend == FILE_BACKEND_NULL) {
        return File_GetNullVtbl();
    }
    return File_GetVtbl();
}

FileSource *File_MakeSource(FileSource *source, u8 *data, char *path, s32 unk_08) {
    source->data = data;
    source->path = path;
    source->unk_08 = unk_08;
    return source;
}

/* Picks the back end and copies its I/O slots into the base class and every class of g_fileClassGetters. */
void File_SetBackend(s32 backend) {
    FileVtbl *(**getter)();
    FileVtbl *io;
    FileVtbl *vtbl;

    getter = g_fileClassGetters;
    g_fileBackend = backend;
    if (backend == FILE_BACKEND_CD) {
        io = File_GetVtbl();
    } else {
        io = File_GetNullVtbl();
    }
    vtbl = File_GetBaseVtbl();
    File_CopyIoSlots(vtbl, io);
    while (*getter != NULL) {
        vtbl = (*getter)();
        getter++;
        File_CopyIoSlots(vtbl, io);
    }
}

/* Copies the I/O slots 0x40 to 0x58 and 0x68 to 0x74. */
static void File_CopyIoSlots(FileVtbl *dst, FileVtbl *src) {
    dst->unk_40 = src->unk_40;
    dst->open = src->open;
    dst->close = src->close;
    dst->seek = src->seek;
    dst->unk_50 = src->unk_50;
    dst->read = src->read;
    dst->load = src->load;
    dst->runQueue = src->runQueue;
    dst->loadAsync = src->loadAsync;
    dst->stop = src->stop;
    dst->cancel = src->cancel;
}

void File_LockBackend(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        File_Lock();
    }
}

void File_UnlockBackend(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        File_Unlock();
    }
}

/* File_IsBackendBusy to File_GetBackendVSyncMode: the back-end dispatch of the CD status getters
   (the empty back end answers idle); nothing in the executable calls it or holds its address. */
static s32 File_IsBackendBusy(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_IsBusy();
    }
    return 0;
}

static s32 File_IsBackendDone(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_IsDone();
    }
    return 1;
}

static s32 File_GetBackendOpKind(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetOpKind();
    }
    return 0;
}

static s32 File_GetBackendState(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetState();
    }
    return 0;
}

/* File_Enable (or the empty back end's) until it accepts: it refuses while a CD operation runs. */
void File_EnableWait(s32 enabled, s32 option, s32 vsyncMode) {
    s32 (*enable)(s32, s32, s32);

    enable = File_NullEnable;
    if (g_fileBackend == FILE_BACKEND_CD) {
        enable = File_Enable;
    }
    while (enable(enabled, option, vsyncMode) == 0) {
    }
}

static s32 File_GetBackendEnabled(s32 *optionOut) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetEnabled(optionOut);
    }
    return File_NullGetEnabled(optionOut);
}

static s32 File_GetBackendVSyncMode(void) {
    if (g_fileBackend == FILE_BACKEND_CD) {
        return File_GetVSyncMode();
    }
    return File_NullGetVSyncMode();
}

/* Appends count entries of 0x1C bytes to the CD directory and resolves the new ones. */
s32 File_AddDirEntries(DirEntry *table, s32 count) {
    s32 oldCount;

    if (g_fileBackend == FILE_BACKEND_CD) {
        g_fileDirTableSet = 1;
        File_SetDirTable(table);
        oldCount = File_GetDirCount();
        File_SetDirCount(oldCount + count);
        return File_ResolveEntries(table + oldCount, count);
    }
    return 1;
}

/* The disc folder every path starts with, "CDI\" (File_BuildPath). */
void File_SetPathPrefix(void *rootDir) {
    g_filePathPrefix = rootDir;
}

s8 *File_GetPathPrefix(void) {
    return g_filePathPrefix;
}

/* dst = prefix (when not NULL) + name + suffix. */
s8 *File_JoinPath(s8 *dst, s8 *name, s8 *prefix, s8 *suffix) {
    *dst = 0;
    if (prefix != NULL) {
        strcat(dst, prefix);
    }
    strcat(dst, name);
    strcat(dst, suffix);
    return dst;
}

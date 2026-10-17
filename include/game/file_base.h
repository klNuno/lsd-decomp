#ifndef GAME_FILE_BASE_H
#define GAME_FILE_BASE_H

#include "common.h"
#include "game/heap.h"
#include "game/file_cd.h"

/*
 * The file class of src/game/file_base.c, the base of every file loader (tix.h, tim.h, tim_pack.h,
 * tmd.h, tod.h, tod_pack.h, mom.h, mml.h, bg_cells.h, bg_map.h, map_chunk.h, seq_file.h,
 * sound_bank.h; base vtable 0x8006D430, returned by File_GetBaseVtbl; File_GetBackendVtbl
 * returns the CD or PC back end, picked by g_fileBackend). At boot File_SetBackend copies the back
 * end's I/O slots (0x40 to 0x58 and 0x68 to 0x74) into the base vtable and into every class
 * vtable listed at 0x8006D4AC, which holds the vtable getters of the loader classes: in the data those
 * slots are 0.
 *
 * A file object can own its data (slot 0x58 loads the whole file into +0x10, +0x14 = size) or
 * borrow it from a parent file (data set by the creator, size 0: slot 0x5C frees only when the
 * size is not 0). Creators take a FileSource: a parent's data address, or a path to load.
 * Slots are left unprototyped: the code calls some of them with fewer arguments.
 */

/* File_MakeSource(source, data, path, unk_08): data != 0 borrows it, else the path is loaded */
typedef struct FileSource {
    u8 *data;   /* address inside a parent file, or NULL */
    char *path; /* used when data is NULL */
    s32 unk_08; /* 1 from every creator here and in Sym_ResetGroupsAndLoadSpy */
} FileSource;

/* Slots 0x00 to 0x74 of every file class vtable */
typedef struct FileVtbl {
    s32 classWord;             /* 0x003 in the base, 0xF03 in the TIX class, other values per class */
    void *(*delete_)();        /* 0x04 File_Delete */
    s32 (*init)();             /* 0x08 */
    void (*destroy)();         /* 0x0C */
    u8 pad_10[0x3C - 0x10];    /* Object methods, see ObjectVtbl */
    s32 unk_3C;                /* 0 */
    void (*unk_40)();          /* CD: File_EmptySlot40, empty */
    void (*open)();            /* 0x44 (self, path, 1, 0), CD: File_OpenByName (CdSearchFile) */
    void (*close)();           /* 0x48 CD: File_Close */
    s32 (*seek)();             /* 0x4C (self, offset, whence); whence 2 returns the size (File_LoadWhole) */
    void (*unk_50)();          /* CD: File_EmptySlot50, empty */
    s32 (*read)();             /* 0x54 (self, buffer, size), CD: File_Read (CdRead) */
    void (*load)();            /* 0x58 (self, path): the whole file into +0x10 (File_LoadWhole, File_LoadWholeCd) */
    void (*freeData)();        /* 0x5C File_FreeData: frees +0x10 when +0x14 != 0 */
    void (*unk_60)();          /* File_EmptySlot60, empty */
    s32 (*onLoaded)();         /* 0x64 run after each queued request (File_ServiceQueue) and by creators of
                                  borrowed data; classes parse their data here; base File_MarkLoaded: flags |= 1 */
    void (*runQueue)();        /* 0x68 CD: File_ServiceQueue, runs the queued requests */
    void (*loadAsync)();       /* 0x6C (self, path), CD: File_RequestLoad queues slot 0x58 */
    void (*stop)();          /* CD: File_Stop */
    void (*cancel)();          /* 0x74 CD: File_CancelRequests, drops the object's queued requests */
} FileVtbl;

/*
 * The file object (0x2C bytes, base vtable 0x8006D430, src/game/file_base.c and the CD back end of
 * src/game/file_cd.c). Every file class starts with these fields, with its own vtable type and
 * often a union for data (the parts its onLoaded parses).
 */
typedef struct File {
    FileVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;      /* 0x0C set by open (File_OpenByName), cleared by close (File_Close) */
    u8 *data;        /* 0x10 the whole file, or a parent's bytes */
    s32 size;        /* 0x14 0 when the data is borrowed */
    CdlLocDir cdPos; /* 0x18 CdlLOC of the file, copied whole from its directory entry */
    u32 cdSize;      /* 0x1C its size on the disc, from the same entry */
    u16 keepData;    /* 0x20 when set, freeData keeps the data */
    u16 pending;     /* 0x22 queued requests: File_QueueRequest adds one */
    u32 flags;       /* 0x24 done requests (File_ServiceQueue); bit 0 set by the base onLoaded */
    u16 direct;      /* 0x28 the CD back end runs requests at once instead of queueing them */
    u16 state;       /* 0x2A per class: 9 and 10 while a TIX or a map chunk reads its parts */
} File;

/* Functions of src/game/file_base.c that other files call or reference (docs/naming.md, Prototypes) */
s32 File_Delete(File *file);
void File_LoadWhole(); /* unprototyped: file_cd.c calls it with no arguments */
void File_FreeData(File *file);
void File_EmptySlot60(void);
void File_MarkLoaded(File *file);
FileVtbl *File_GetBaseVtbl(void);
FileVtbl *File_GetBackendVtbl(void);
FileSource *File_MakeSource(FileSource *source, u8 *data, char *path, s32 unk_08);
void File_SetBackend(s32 backend);
void File_LockBackend(void);
void File_UnlockBackend(void);
void File_EnableWait(s32 enabled, s32 option, s32 vsyncMode);
struct DirEntry;
s32 File_AddDirEntries(struct DirEntry *table, s32 count);
void File_SetPathPrefix(void *rootDir);
s8 *File_GetPathPrefix(void);
s8 *File_JoinPath(s8 *dst, s8 *name, s8 *prefix, s8 *suffix);

#endif

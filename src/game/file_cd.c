#include "common.h"
#include "game/loader.h"
#include "game/scene.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

typedef struct FileLoadedView {
    u8 pad[0xC];
    s32 isOpen;          /* File.isOpen: File_ClearLoaded drops it */
} FileLoadedView;
s32 g_fileEnabled;
s32 g_fileOption;
s32 g_fileBusy;
s32 g_fileDone;
s32 g_fileOpKind;
s32 g_fileState;
s32 *g_fileRequestHead;
s32 g_fileAsyncMode;
s32 g_fileRetryCount;
void File_Lock(void);
void File_Unlock(void);
s32 g_fileVSyncPending;
typedef struct FileSizeView {
    u8 pad[0xC];
    s32 isOpen;          /* File.isOpen */
    u8 pad2[0xC];
    u32 cdSize;          /* File.cdSize, rounded up to whole sectors */
} FileSizeView;
void File_UnhookVSync(void);
typedef struct ObjectClassTable {
    u8 pad_00[0x8];
    void (*init)(void *);    /* 0x08 Object_Init */
    void (*destroy)(s32);    /* 0x0C Object_Destroy */
} ObjectClassTable;
ObjectClassTable *File_GetBaseVtbl(void);
void *File_GetVtable(void);
void File_InitCd(void);
typedef struct FileInitObject {
    void *vtbl;              /* File.vtbl, the back end vtable */
    u8 pad4[0x24];
    s16 direct;              /* File.direct, 0: requests are queued */
} FileInitObject;
typedef struct FileInitClassTable {
    u8 pad[8];
    void (*init)(FileInitObject *);  /* 0x08 Object_Init */
} FileInitClassTable;
s32 g_fileDirTable;
typedef struct FileVtSlot8 {
    u8 pad[0x8];
    void (*init)(s32);       /* 0x08 File_InitObject */
} FileVtSlot8;
s32 Heap_Alloc(s32);
s32 g_fileCdReady;
void CdSetDebug(s32 level);
s32 CdControlB(s32 com, u8 *param, s32 result);
typedef struct FileInitRecord {
    void *vtbl;              /* File.vtbl */
    u8 pad_04[0x8];
    s32 isOpen;              /* File.isOpen, 0 until File_Locate finds the file */
} FileInitRecord;
typedef struct FileStepObject FileStepObject;
typedef struct {
    u8 pad[0x5C];
    void (*onLoaded)(FileStepObject *); /* 0x5C File_MarkLoaded: flags |= 1 */
    u8 pad2[0x74 - 0x60];
    void (*cancel)(void);               /* 0x74 File_CancelRequests */
} FileStepVt;
struct FileStepObject {
    FileStepVt *vt;
};
s32 g_fileVSyncHooked;
s32 g_fileVSyncMode;
s32 File_OnVSync(void);
void VSyncCallback(void (*func)(void));
s8 *File_GetPathPrefix(void);
s8 *strcpy(s8 *dst, s8 *src);
s8 *strcat(s8 *dst, s8 *src);
extern s8 g_fileVersionSuffix[]; /* ";1" in .sdata */
s32 g_fileDirCount;
char *strstr(char *haystack, char *needle);
void File_HookVSync(void);
struct FileRequest *File_NewRequest(void);
typedef struct FileHandle FileHandle;
typedef struct {
    u8 pad[0x44];
    void (*open)(FileHandle *, s32, s32, s32);  /* 0x44 File_LoadByName */
    void (*close)(FileHandle *);               /* 0x48 File_Unload */
    void (*seek)(FileHandle *, s32, s32);       /* 0x4C File_Seek */
    u8 pad2[0x54 - 0x50];
    void (*read)(FileHandle *, s32, s32);       /* 0x54 File_Read */
    void (*load)(FileHandle *, s32);            /* 0x58 File_Open */
    u8 pad3[0x64 - 0x5C];
    void (*onLoaded)(FileHandle *);             /* 0x64 File_MarkLoaded */
    u8 pad4[0x70 - 0x68];
    void (*unk70)(FileHandle *);                /* 0x70 File_Stop, called once the queue drains */
} FileHandleVt;
struct FileHandle {
    FileHandleVt *vt;
    u8 pad[0x1E];
    u16 pending;         /* File.pending, queued requests */
    s32 flags;           /* File.flags, one bit per finished request */
    u16 direct;          /* File.direct, 1 while a queued request runs */
};
typedef struct FileRequest FileRequest;
struct FileRequest {
    void *running;       /* 0x00 0 while queued, 1 once File_BeginOp starts it */
    s32 markLoaded;      /* 0x04 1: the finished request sets bit 0 of the file's flags */
    s32 kind;            /* 0x08 2 open, 3 close, 4 seek, 5 read, 7 load whole */
    FileHandle *file;    /* 0x0C the file the request belongs to */
    s32 index;           /* 0x10 directory index, File_EntryAt for kinds 2 and 7 */
    s32 param0;          /* 0x14 open mode, seek offset, or read buffer */
    s32 param1;          /* 0x18 open param, seek mode, or read size */
    FileRequest *prev;   /* 0x1C */
    FileRequest *next;   /* 0x20 */
};
void Heap_Free(void *);
typedef struct FileStateView {
    u8 pad[0xC];
    s32 isOpen;          /* File.isOpen */
    u8 pad2[0x28 - 0x10];
    u16 direct;          /* File.direct */
} FileStateView;
void File_BeginOp(s32 kind, s32 state);
void File_EndOp(void);
typedef struct FileVtPathSlot {
    u8 pad[0x58];
    void (*load)(File *, char *); /* 0x58 File_Open */
} FileVtPathSlot;
s32 File_FindIndex(char *name);
void File_QueueRequest(File *obj, s32 index, s32 kind, s32 param3, s32 param4);
typedef struct VSyncObject {
    /* 0x00 */ u8 pad_00[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 pad_10[0x10];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
} VSyncObject;
VSyncObject *Display_GetCurrent(void);
typedef struct FileVtVSyncSlot {
    u8 pad[0x68];
    void (*runQueue)(void); /* 0x68 File_ServiceQueue */
} FileVtVSyncSlot;
s32 g_fileLock;
s32 Heap_IsBusy(void);
void File_PollIo(void);
void File_StepIo(void);
typedef struct FileVtSlot48 {
    u8 pad[0x48];
    void (*close)(void *);   /* 0x48 File_Unload */
} FileVtSlot48;
typedef struct FileSeekView {
    FileVtSlot48 *vtbl;  /* File.vtbl */
    u8 pad4[0x8];
    s32 isOpen;          /* File.isOpen */
    u8 pad10[0x8];
    u8 cdPos[0x8];       /* File.cdPos, the CdlLOC given to CdControl command 2 */
} FileSeekView;
s32 CdControl(s32 com, u8 *param, s32 result);
s32 CdRead(s32 sectors, void *buf, s32 mode);
s32 CdReadSync(s32 mode, u8 *result);
s32 CdSync(s32 mode, u8 *result);
typedef struct FileRequestLink FileRequestLink;
struct FileRequestLink {
    void *running;       /* FileRequest.running */
    u8 pad4[0x8];
    void *file;          /* FileRequest.file */
    u8 pad10[0x10];
    FileRequestLink *next; /* FileRequest.next */
};
s32 g_fileCurEntry;
s32 g_filePrevEntry;
void CdFlush(void);
s32 CdControlF(s32 com, u8 *param);
void File_SetState(s32 state);
s32 g_fileReadSector;
s32 g_fileReadBuf;
s32 File_ReadSync(FileSeekView *obj, void *dst, u32 offset);
extern u8 g_fileVtable[];
typedef struct FileEntryView {
    u8 pad[0xC];
    s32 isOpen;          /* File.isOpen */
    u8 pad2[0x18 - 0x10];
    u8 cdPos[4];         /* File.cdPos */
    u32 cdSize;          /* File.cdSize */
    u8 pad3[0x28 - 0x20];
    u16 direct;          /* File.direct */
} FileEntryView;
extern u8 g_fileScratchPos[];
s32 File_GetSize(FileSizeView *obj);
s32 CdPosToInt(u8 *pos);
void CdIntToPos(s32 i, u8 *pos);
extern s32 printf(const char *fmt, ...);
s32 CdSearchFile(void *, s8 *);
s8 *File_BuildPath();
typedef struct CdlLoc {
    u8 m, s, f, t;
} CdlLoc;
typedef struct CdlFile {
    CdlLoc pos;
    s32 size;
    u8 name[0x10];
} CdlFile;
typedef struct FileLoadState {
    u8 pad[0xC];
    s32 isOpen;          /* File.isOpen, set once CdSearchFile finds it */
    u8 pad2[0x8];
    CdlLoc cdPos;        /* File.cdPos */
    s32 cdSize;          /* File.cdSize */
} FileLoadState;
typedef struct CdlLocDir {
    u8 minute, second, sector, track;
} CdlLocDir;
typedef struct CdlFileDir {
    CdlLocDir pos;
    s32 size;
    s8 name[16];
} CdlFileDir;
typedef struct DirEntry {
    s8 name[0x14];
    CdlLocDir pos;
    s32 size;
} DirEntry;
typedef struct CdlLocTail {
    u8 m;
    u8 s;
    u8 f;
    u8 t;
} CdlLocTail;
typedef struct DirEntryTail {
    u8 pad[0x14];
    CdlLocTail pos;      /* DirEntry.pos, the CdlLOC at +0x14 */
    s32 size;            /* DirEntry.size */
} DirEntryTail;
typedef struct CdlFileTail {
    CdlLocTail pos;
    s32 size;
    u8 name[0x10];
} CdlFileTail;
s32 File_FindEntry(char *name);
typedef struct FileVtOpen {
    u8 pad[0x48];
    void (*close)(void *);   /* 0x48 File_Unload */
    u8 pad2[0x64 - 0x4C];
    void (*onLoaded)(void *); /* 0x64 File_MarkLoaded */
} FileVtOpen;
typedef struct FileOpenObject {
    FileVtOpen *vtbl;    /* File.vtbl */
    u8 pad4[0xC];
    s32 data;            /* File.data, the buffer the whole file is read into */
    s32 size;            /* File.size, the buffer size in bytes */
    u8 pad18[0x8];
    u16 keepData;        /* File.keepData, reuses the buffer when set */
    u8 pad22[0x2];
    s32 flags;           /* File.flags */
    u16 direct;          /* File.direct */
} FileOpenObject;
typedef struct DirEntrySize {
    u8 pad[0x18];
    u32 size;            /* DirEntry.size, rounded up to sectors by File_Open */
} DirEntrySize;
void File_LoadWhole();

s32 File_Create(void) {
    s32 obj;

    obj = Heap_Alloc(0x2C);
    if (obj != 0) {
        ((FileVtSlot8 *)File_GetVtable())->init(obj);
        return obj;
    }
    return 0;
}

void File_InitObject(FileInitObject *obj) {
    ((FileInitClassTable *)File_GetBaseVtbl())->init(obj);
    obj->vtbl = File_GetVtable();
    obj->direct = 0;
    File_InitCd();
}

void File_Step(FileStepObject *obj) {
    obj->vt->cancel();
    obj->vt->onLoaded(obj);
}

void File_EmptySlot40(void) {
}

void File_LoadByName(File *obj, char *name, s32 param2, s32 param3) {
    s8 path[0x40];
    CdlFileTail file;
    s32 result;

    if (g_fileEnabled == 0 && g_fileOption == 0) {
        File_Locate(obj);
        return;
    }
    File_Lock();
    if (obj->direct != 0) {
        if (g_fileBusy == 0 && obj->isOpen == 0) {
            File_BeginOp(1, 1);
            if (g_fileEnabled != 0) {
                g_fileCurEntry = File_FindEntry(name);
                if (g_fileCurEntry == 0) {
                    return;
                }
                *(CdlLocTail *)&obj->cdPos = ((DirEntryTail *)g_fileCurEntry)->pos;
                obj->cdSize = ((DirEntryTail *)g_fileCurEntry)->size;
                g_fileAsyncMode = 1;
                obj->isOpen = 1;
            } else {
                File_BuildPath(path, (s8 *)name);
                while (CdSearchFile(&file, path) == 0) {
                }
                *(CdlLocTail *)&obj->cdPos = file.pos;
                obj->cdSize = file.size;
                do {
                    CdControl(2, (u8 *)&obj->cdPos, 0);
                    do {
                        result = CdSync(0, 0);
                    } while (result == 0);
                } while (result == 5);
                obj->isOpen = 1;
                File_EndOp();
            }
        }
    } else {
        File_QueueRequest(obj, File_FindIndex(name), 2, param2, param3);
    }
    File_Unlock();
}

void File_Unload(FileStateView *obj) {
    if (g_fileEnabled == 0 && g_fileOption == 0) {
        File_ClearLoaded();
        return;
    }
    File_Lock();
    if (obj->direct != 0) {
        if (g_fileBusy == 0) {
            File_BeginOp(0, 0);
            obj->isOpen = 0;
            File_EndOp();
        }
    } else {
        File_QueueRequest(obj, 0, 3, 0, 0);
    }
    File_Unlock();
}

s32 File_Seek(FileEntryView *obj, u32 offset, s32 mode) {
    u8 *buf;
    u32 sector;
    s32 base;
    s32 status;
    u32 v;

    if (g_fileEnabled == 0 && g_fileOption == 0) {
        return File_GetSize((FileSizeView *)obj);
    }
    File_Lock();
    if (obj->direct != 0) {
        if (g_fileBusy == 0 && obj->isOpen != 0) {
            File_BeginOp(2, 1);
            sector = offset >> 11;
            if (offset & 0x7FF) {
                sector++;
            }
            base = CdPosToInt(obj->cdPos);
            buf = g_fileScratchPos;
            CdIntToPos(base + sector, buf);
            if (mode == 0) {
                if (g_fileEnabled != 0) {
                    g_fileCurEntry = (s32)buf - 0x14;
                    g_fileAsyncMode = 1;
                } else {
                    do {
                        CdControl(2, g_fileScratchPos, 0);
                        while ((status = CdSync(0, 0)) == 0) {}
                    } while (status == 5);
                    File_EndOp();
                }
            } else {
                File_EndOp();
                File_Unlock();
                v = obj->cdSize;
                if (v & 0x7FF) {
                    return ((v >> 11) + 1) << 11;
                }
                return v;
            }
        }
    } else {
        File_QueueRequest((File *)obj, 0, 4, offset, mode);
    }
    File_Unlock();
    return 0;
}

void File_EmptySlot50(void) {
}

s32 File_Read(FileStateView *obj, s32 buf, u32 offset) {
    s32 status;

    if ((g_fileEnabled == 0) && (g_fileOption == 0)) {
        File_ReadSync((FileSeekView *)obj, (void *)buf, offset);
        return 0;
    }
    File_Lock();
    if (obj->direct != 0) {
        if ((g_fileBusy == 0) && (obj->isOpen != 0)) {
            File_BeginOp(3, 7);
            if (g_fileEnabled != 0) {
                g_fileReadSector = offset >> 11;
                g_fileReadBuf = buf;
                g_fileAsyncMode = 1;
            } else {
            retry:
                CdRead(offset >> 11, (void *)buf, 0x80);
                while ((status = CdReadSync(0, 0)) > 0) {
                }
                if (status == -1) {
                    goto retry;
                }
                File_EndOp();
            }
        }
    } else {
        File_QueueRequest((File *)obj, 0, 5, buf, offset);
    }
    File_Unlock();
    return 0;
}

void File_Open(FileOpenObject *obj, char *name) {
    s32 size;
    s32 entry;
    s32 buf;
    s32 r;
    s32 cur;
    u32 sectors;

    if (g_fileEnabled == 0 && g_fileOption == 0) {
        File_LoadWhole();
        obj->flags |= 0x200;
        obj->vtbl->onLoaded(obj);
        return;
    }
    File_Lock();
    if (obj->direct != 0) {
        if (g_fileBusy == 0 && (obj->data == 0 || obj->keepData != 0)) {
            File_BeginOp(4, 1);
            g_filePrevEntry = g_fileCurEntry;
            entry = File_FindEntry(name);
            g_fileCurEntry = entry;
            if (entry == 0) {
                return;
            }
            sectors = ((DirEntrySize *)entry)->size >> 11;
            g_fileReadSector = sectors;
            if (((DirEntrySize *)entry)->size & 0x7FF) {
                g_fileReadSector = sectors + 1;
            }
            cur = obj->data;
            size = g_fileReadSector << 11;
            if (cur == 0) {
                buf = Heap_Alloc(size);
                if (buf == 0) {
                    obj->vtbl->close(obj);
                    return;
                }
                g_fileReadBuf = buf;
                obj->data = buf;
            } else {
                g_fileReadBuf = cur;
            }
            if (g_fileEnabled != 0) {
                obj->size = size;
                g_fileAsyncMode = 2;
            } else {
            retry:
                do {
                    CdControl(2, (u8 *)(g_fileCurEntry + 0x14), 0);
                    while ((r = CdSync(0, 0)) == 0) {}
                } while (r == 5);
                CdRead(g_fileReadSector, (void *)obj->data, 0x80);
                while ((r = CdReadSync(0, 0)) > 0) {}
                if (r == -1) {
                    goto retry;
                }
                obj->size = size;
                *g_fileRequestHead = 1;
                File_EndOp();
            }
        }
    } else {
        File_QueueRequest((File *)obj, File_FindIndex(name), 7, 0, 0);
    }
    File_Unlock();
}

void File_ServiceQueue(void) {
    s32 kind;
    FileRequest *req;
    FileHandle *obj;

    File_Lock();
    req = (FileRequest *)g_fileRequestHead;
    if (req != NULL) {
        obj = req->file;
        kind = req->kind;
        if (req->running == NULL) {
            obj->direct = 1;
            switch (kind) {
            case 2:
                obj->vt->open(obj, File_EntryAt(req->index), req->param0, req->param1);
                break;
            case 3:
                obj->vt->close(obj);
                break;
            case 4:
                obj->vt->seek(obj, req->param0, req->param1);
                break;
            case 5:
                obj->vt->read(obj, req->param0, req->param1);
                break;
            case 7:
                obj->vt->load(obj, File_EntryAt(req->index));
                break;
            }
            obj->direct = 0;
        } else if (g_fileDone != 0) {
            if (req->markLoaded != 0) {
                obj->flags |= 1;
            }
            obj->flags |= 2;
            obj->pending--;
            if (obj->pending == 0) {
                obj->flags |= 4;
            }
            switch (kind) {
            case 2:
                obj->flags |= 0x10;
                break;
            case 3:
                obj->flags |= 0x20;
                break;
            case 4:
                obj->flags |= 0x40;
                break;
            case 5:
                obj->flags |= 0x80;
                break;
            case 7:
                obj->flags |= 0x200;
                break;
            }
            obj->vt->onLoaded(obj);
            File_FreeRequest(req);
            if (g_fileRequestHead == NULL) {
                obj->vt->unk70(obj);
            }
        }
    }
    File_Unlock();
}

void File_RequestOpen(File *obj, char *name) {
    FileRequest *uninit;

    File_Lock();
    if (name != 0) {
        if (g_fileEnabled != 0) {
            uninit->markLoaded = 1;
            File_QueueRequest(obj, File_FindIndex(name), 7, 0, 0);
        } else {
            (*(FileVtPathSlot **)obj)->load(obj, name);
            if (obj->pending == 0) {
                obj->flags = obj->flags | 4;
            }
        }
    }
    File_Unlock();
}

void File_Stop(void) {
    File_Lock();
    File_UnhookVSync();
    File_Unlock();
}

void File_CancelRequests(File *obj) {
    FileRequestLink *node;
    FileRequestLink *cur;
    FileRequestLink *next;
    s32 tmp;

    File_Lock();
    node = (FileRequestLink *)g_fileRequestHead;
    if (node != NULL && obj->pending != 0) {
        obj->flags = 0;
        if (node->file == obj && node->running != NULL && g_fileDone == 0) {
            CdFlush();
            File_EndOp();
            tmp = g_filePrevEntry;
            g_filePrevEntry = 0;
            g_fileCurEntry = tmp;
        }
        cur = (FileRequestLink *)g_fileRequestHead;
        while (cur != NULL) {
            next = cur->next;
            if (cur->file == obj) {
                File_FreeRequest(cur);
                obj->pending--;
            }
            cur = next;
        }
    }
    File_Unlock();
}

void *File_GetVtable(void) {
    return g_fileVtable;
}

void File_InitCd(void) {
    u8 param;

    if (g_fileCdReady == 0) {
        CdSetDebug(0);
        param = 0x80;
        while (CdControlB(0xE, &param, 0) == 0) {
        }
        g_fileCdReady = 1;
    }
}

s32 File_IsBusy(void) {
    return g_fileBusy;
}

s32 File_IsDone(void) {
    return g_fileDone;
}

s32 File_GetOpKind(void) {
    return g_fileOpKind;
}

s32 File_GetState(void) {
    return g_fileState;
}

s32 File_GetEnabled(s32 *outValue) {
    if (outValue != NULL) {
        *outValue = g_fileOption;
    }
    return g_fileEnabled;
}

s32 File_Enable(s32 enabled, s32 param1, s32 mode) {
    Display *temp;

    if (g_fileBusy == 0) {
        if (mode == 0) {
            temp = (Display *)Display_GetCurrent();
            if (g_fileEnabled == 0) {
                if (enabled != 0) {
                    temp->vtbl->setFrameCallback(temp, File_OnVSync);
                }
            } else {
                if (enabled == 0) {
                    temp->vtbl->setFrameCallback(temp, NULL);
                }
            }
        }
        g_fileVSyncMode = mode;
        g_fileEnabled = enabled;
        g_fileOption = param1;
        return 1;
    }
    return 0;
}

void File_SetDirTable(s32 table) {
    g_fileDirTable = table;
}

void File_SetDirCount(s32 count) {
    g_fileDirCount = count;
}

s32 File_GetDirCount(void) {
    return g_fileDirCount;
}

s32 File_ResolveEntries(DirEntry *entries, s32 count) {
    s8 path[0x40];
    CdlFileDir file;
    DirEntry *end;
    s32 i;

    end = entries + count;
    File_InitCd();
    for (; entries < end; entries++) {
        File_BuildPath(path, entries->name);
        i = 0;
        while (CdSearchFile(&file, path) == 0) {
            i++;
            if (i >= 101) {
                printf("File not found. file = %s\n", path);
                break;
            }
        }
        entries->pos = file.pos;
        entries->size = file.size;
    }
    return 1;
}

void File_Lock(void) {
    g_fileLock = 1;
}

void File_Unlock(void) {
    g_fileLock = 0;
}

s32 File_OnVSync(void) {
    if (g_fileLock == 0) {
        if (Heap_IsBusy() == 0) {
            if (g_fileVSyncMode != 0) {
                VSyncCallback(0);
            }
            if (g_fileAsyncMode == 1) {
                File_PollIo();
            } else if (g_fileAsyncMode == 2) {
                File_StepIo();
            }
            if (g_fileVSyncPending != 0) {
                ((FileVtVSyncSlot *)File_GetVtable())->runQueue();
            }
            if (g_fileVSyncMode != 0) {
                VSyncCallback(File_OnVSync);
            }
        }
    }
    return 0;
}

void File_HookVSync(void) {
    File_Lock();
    if (g_fileVSyncHooked == 0) {
        if (g_fileVSyncMode != 0) {
            VSyncCallback(&File_OnVSync);
        }
        g_fileVSyncHooked = 1;
    }
    g_fileVSyncPending = 1;
    File_Unlock();
}

void File_UnhookVSync(void) {
    File_Lock();
    if ((g_fileAsyncMode == 0) && (g_fileVSyncHooked != 0)) {
        if (g_fileVSyncMode != 0) {
            VSyncCallback(0);
        }
        g_fileVSyncHooked = 0;
        g_fileVSyncPending = 0;
    }
    File_Unlock();
}

void File_ClearVSyncPending(void) {
    File_Lock();
    g_fileVSyncPending = 0;
    File_Unlock();
}

void File_QueueRequest(File *obj, s32 index, s32 kind, s32 param3, s32 param4) {
    FileRequest *req;

    req = File_NewRequest();
    req->kind = kind;
    req->param0 = param3;
    req->file = obj;
    req->index = index;
    req->param1 = param4;
    obj->flags = 0;
    obj->pending = obj->pending + 1;
    File_HookVSync();
}

FileRequest *File_NewRequest(void) {
    FileRequest *node;
    FileRequest *last;

    File_Lock();
    node = (FileRequest *)Heap_Alloc(0x24);
    if (node != NULL) {
        node->prev = NULL;
        node->next = NULL;
        node->running = NULL;
        node->markLoaded = 0;
        if (g_fileRequestHead != NULL) {
            last = (FileRequest *)g_fileRequestHead;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = node;
            node->prev = last;
        } else {
            g_fileRequestHead = (s32 *)node;
        }
    }
    File_Unlock();
    return node;
}

void File_FreeRequest(FileRequest *node) {
    File_Lock();
    if (node != NULL) {
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            g_fileRequestHead = (s32 *)node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        Heap_Free(node);
    }
    File_Unlock();
}

s32 File_FindEntry(char *name) {
    s32 entry;
    s32 i;

    entry = g_fileDirTable;
    i = 0;
    File_Lock();
    do {
        if (strstr((char *)entry, name) != NULL) {
            File_Unlock();
            return entry;
        }
        i++;
        entry += 0x1C;
    } while (i < g_fileDirCount);
    return 0;
}

s32 File_FindIndex(char *name) {
    s32 entry;
    s32 i;

    entry = g_fileDirTable;
    i = 0;
    File_Lock();
    do {
        if (strstr((char *)entry, name) != NULL) {
            File_Unlock();
            return i;
        }
        entry += 0x1C;
        i++;
    } while (i < g_fileDirCount);
    return -1;
}

s32 File_EntryAt(s32 index) {
    s32 entry;

    entry = g_fileDirTable;
    File_Lock();
    entry += index * 0x1C;
    File_Unlock();
    return entry;
}

void File_PollIo(void) {
    File_Lock();
    switch (g_fileState) {
    case 1:
        if (CdControlF(2, (u8 *)(g_fileCurEntry + 0x14)) != 0) {
            File_SetState(2);
        }
        break;
    case 2:
        switch (CdSync(1, 0)) {
        case 5:
            File_SetState(1);
            break;
        case 0:
            if (++g_fileRetryCount > 0x258) {
                File_SetState(1);
            }
            break;
        case 2:
            File_EndOp();
            break;
        }
        break;
    case 7:
        if (CdRead(g_fileReadSector, (void *)g_fileReadBuf, 0x80) != 0) {
            File_SetState(8);
        }
        break;
    case 8:
        switch (CdReadSync(1, 0)) {
        case 0:
            File_EndOp();
            break;
        case -1:
            CdFlush();
            File_SetState(1);
            break;
        }
        break;
    }
    File_Unlock();
}

void File_StepIo(void) {
    s32 nextState;
    s32 state;
    s32 retryCount;
    s32 prevDir;
    s32 syncResult;

    File_Lock();
    state = g_fileState;
    switch (state) {
    case 1:
        if (CdControlF(2, (u8 *)(g_fileCurEntry + 0x14)) != 0) {
            nextState = 2;
            goto tail;
        }
        break;
    case 2:
        syncResult = CdSync(1, 0);
        if (syncResult != state) {
            if (syncResult < 3) {
                if (syncResult == 0) {
                    goto count;
                }
            } else {
                nextState = 1;
                if (syncResult == 5) {
                    goto tail;
                }
            }
            break;
        } else {
            nextState = 7;
            goto tail;
        }
    count:
        retryCount = g_fileRetryCount + 1;
        g_fileRetryCount = retryCount;
        if (retryCount >= 0x259) {
            nextState = 1;
            goto tail;
        }
        break;
    case 7:
        if (CdRead(g_fileReadSector, (void *)g_fileReadBuf, 0x80) != 0) {
            nextState = 8;
            goto tail;
        }
        break;
    case 8:
        syncResult = CdReadSync(1, 0);
        if (syncResult == -1) {
            nextState = 1;
            goto tail;
        }
        if (syncResult == 0) {
            File_EndOp();
            prevDir = g_filePrevEntry;
            g_filePrevEntry = 0;
            g_fileCurEntry = prevDir;
        }
        break;
    }
    goto end;
tail:
    File_SetState(nextState);
end:
    File_Unlock();
}

void File_BeginOp(s32 kind, s32 state) {
    g_fileBusy = 1;
    g_fileOpKind = kind;
    g_fileState = state;
    g_fileDone = 0;
    *g_fileRequestHead = 1;
}

void File_EndOp(void) {
    g_fileOpKind = 0;
    g_fileState = 0;
    g_fileAsyncMode = 0;
    g_fileDone = 1;
    g_fileRetryCount = 0;
    g_fileBusy = 0;
}

void File_SetState(s32 state) {
    g_fileState = state;
    g_fileRetryCount = 0;
}

void File_InitRecord(FileInitRecord *obj) {
    File_GetBaseVtbl()->init(obj);
    obj->vtbl = File_GetVtable();
    obj->isOpen = 0;
}

void File_Destroy(s32 handle) {
    File_GetBaseVtbl()->destroy(handle);
}

void func_80028918(void) {
}

void File_Locate(FileLoadState *obj) {
    s32 tries;
    CdlFile file;
    s8 name[0x40];

    tries = 0;
    if (obj->isOpen == 0) {
        File_BuildPath(name);
    again:
        if (CdSearchFile(&file, name) != 0) {
            goto found;
        }
        if (tries++ < 100) {
            goto again;
        }
        printf("File not found. path = %s\n", name);
        return;
    found:
        obj->cdPos = file.pos;
        obj->cdSize = file.size;
        obj->isOpen = 1;
    }
}

s8 *File_BuildPath(s8 *path, s8 *name) {
    *path = 0x5C;
    strcpy(path + 1, File_GetPathPrefix());
    strcat(path, name);
    strcat(path, g_fileVersionSuffix);
    return path;
}

void File_ClearLoaded(FileLoadedView *obj) {
    if (obj->isOpen != 0) {
        obj->isOpen = 0;
    }
}

s32 File_GetSize(FileSizeView *obj) {
    if (obj->isOpen != 0) {
        return ((obj->cdSize >> 0xB) + 1) << 0xB;
    }
    return 0;
}

void func_80028A7C(void) {
}

s32 File_ReadSync(FileSeekView *obj, void *dst, u32 offset) {
    u8 buf[0x800];
    u8 result[0x10];
    s32 status;
    s32 ret;
    s32 sectors;

    if (obj->isOpen == 0) {
        goto fallback;
    }
retry:
    sectors = offset >> 11;
    CdControl(2, obj->cdPos, 0);
sync:
    status = CdSync(0, result);
    if (status == 0) {
        goto sync;
    }
    if (status == 5) {
        goto retry;
    }
    if (sectors == 0) {
        return 0;
    }
    CdRead(sectors, dst, 0x80);
    do {
        ret = CdReadSync(0, 0);
    } while (ret > 0);
    if (ret == -1) {
        goto retry;
    }
    return 0;
fallback:
    obj->vtbl->close(obj);
    return 0;
}

void func_80028B64(void) {
}

s32 File_GetVSyncMode(void) {
    return g_fileVSyncMode;
}

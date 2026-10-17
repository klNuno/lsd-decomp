#include "common.h"
#include "game/file_cd.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/file_base.h"
#include "psyq/libetc.h"
#include "psyq/libcd.h"
#include "psyq/libc.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

s32 g_fileEnabled;
s32 g_fileOption;
s32 g_fileBusy;
s32 g_fileDone;
s32 g_fileOpKind;
s32 g_fileState;
struct FileRequest *g_fileRequestHead;
s32 g_fileAsyncMode;
s32 g_fileRetryCount;
s32 g_fileVSyncPending;
static void File_UnhookVSync(void);
static void File_InitCd(void);
DirEntry *g_fileDirTable;
s32 g_fileCdReady;
s32 g_fileVSyncHooked;
s32 g_fileVSyncMode;
static s32 File_OnVSync(void);
extern s8 g_fileVersionSuffix[]; /* ";1" in .sdata */
s32 g_fileDirCount;
static void File_HookVSync(void);
static struct FileRequest *File_NewRequest(void);
typedef struct FileRequest FileRequest;
struct FileRequest {
    s32 running;         /* 0x00 0 while queued, 1 once File_BeginOp starts it */
    s32 markLoaded;      /* 0x04 1: the finished request sets bit 0 of the file's flags */
    s32 kind;            /* 0x08 2 open, 3 close, 4 seek, 5 read, 7 load whole */
    File *file;          /* 0x0C the file the request belongs to */
    s32 index;           /* 0x10 directory index, File_EntryAt for kinds 2 and 7 */
    s32 param0;          /* 0x14 open mode, seek offset, or read buffer */
    s32 param1;          /* 0x18 open param, seek mode, or read size */
    FileRequest *prev;   /* 0x1C */
    FileRequest *next;   /* 0x20 */
};
static void File_BeginOp(s32 kind, s32 state);
static void File_EndOp(void);
static s32 File_FindIndex(char *name);
static void File_QueueRequest(File *obj, s32 index, s32 kind, s32 param3, s32 param4);
s32 g_fileLock;
static void File_PollIo(void);
static void File_StepIo(void);
DirEntry *g_fileCurEntry;
DirEntry *g_filePrevEntry;
static void File_SetState(s32 state);
s32 g_fileReadSectorCount;
u8 *g_fileReadBuf;
static s32 File_ReadSync(File *obj, void *dst, u32 offset);
extern FileVtbl g_fileVtable;
extern u8 g_fileScratchPos[];
static s32 File_GetSize(File *obj);
s8 *File_BuildPath();
/* Left unprototyped: File_CloseSync is called with no argument (a0 still holds the file). */
static void File_Locate(File *obj);
static void File_CloseSync();
static void File_FreeRequest(FileRequest *node);
static DirEntry *File_EntryAt(s32 index);
typedef struct CdlFileDir {
    CdlLocDir pos;
    s32 size;
    s8 name[16];
} CdlFileDir;
static DirEntry *File_FindEntry(char *name);
/* File_LoadWholeCd calls slot 0x64 as a void function: with FileVtbl's s32 slot gcc no longer
   shares the call with the close call below it, so this one function keeps its own view of File. */
typedef struct FileVtOpen {
    u8 pad[0x48];
    void (*close)(void *);   /* 0x48 File_Close */
    u8 pad2[0x64 - 0x4C];
    void (*onLoaded)(void *); /* 0x64 File_MarkLoaded */
} FileVtOpen;
typedef struct FileOpenObject {
    FileVtOpen *vtbl;    /* File's fields (file_base.h), with this vtable type */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    u8 *data;            /* 0x10 the buffer the whole file is read into */
    s32 size;            /* 0x14 the buffer size in bytes */
    CdlLocDir cdPos;
    u32 cdSize;
    u16 keepData;        /* 0x20 reuses the buffer when set */
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
} FileOpenObject;

static File *File_Create(void) {
    File *obj;

    obj = Heap_Alloc(0x2C);
    if (obj != NULL) {
        File_GetVtable()->init(obj);
        return obj;
    }
    return NULL;
}

void File_InitCdObject(File *obj) {
    File_GetBaseVtbl()->init(obj);
    obj->vtbl = File_GetVtable();
    obj->direct = 0;
    File_InitCd();
}

void File_DestroyCd(File *obj) {
    obj->vtbl->cancel();
    obj->vtbl->freeData(obj);
}

void File_EmptySlot40(void) {
}

void File_OpenByName(File *obj, char *name, s32 param2, s32 param3) {
    s8 path[0x40];
    CdlFileDir file;
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
                obj->cdPos = g_fileCurEntry->pos;
                obj->cdSize = g_fileCurEntry->size;
                g_fileAsyncMode = 1;
                obj->isOpen = 1;
            } else {
                File_BuildPath(path, (s8 *)name);
                while (CdSearchFile(&file, path) == 0) {
                }
                obj->cdPos = file.pos;
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

void File_Close(File *obj) {
    if (g_fileEnabled == 0 && g_fileOption == 0) {
        File_CloseSync();
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

s32 File_Seek(File *obj, u32 offset, s32 mode) {
    u8 *buf;
    u32 sector;
    s32 base;
    s32 status;
    u32 v;

    if (g_fileEnabled == 0 && g_fileOption == 0) {
        return File_GetSize(obj);
    }
    File_Lock();
    if (obj->direct != 0) {
        if (g_fileBusy == 0 && obj->isOpen != 0) {
            File_BeginOp(2, 1);
            sector = offset >> 11;
            if (offset & 0x7FF) {
                sector++;
            }
            base = CdPosToInt((u8 *)&obj->cdPos);
            buf = g_fileScratchPos;
            CdIntToPos(base + sector, buf);
            if (mode == 0) {
                if (g_fileEnabled != 0) {
                    /* an entry whose pos is the seek target: File_PollIo seeks to g_fileCurEntry->pos */
                    g_fileCurEntry = (DirEntry *)(buf - 0x14);
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
        File_QueueRequest(obj, 0, 4, offset, mode);
    }
    File_Unlock();
    return 0;
}

void File_EmptySlot50(void) {
}

s32 File_Read(File *obj, u8 *buf, u32 offset) {
    s32 status;

    if ((g_fileEnabled == 0) && (g_fileOption == 0)) {
        File_ReadSync(obj, buf, offset);
        return 0;
    }
    File_Lock();
    if (obj->direct != 0) {
        if ((g_fileBusy == 0) && (obj->isOpen != 0)) {
            File_BeginOp(3, 7);
            if (g_fileEnabled != 0) {
                g_fileReadSectorCount = offset >> 11;
                g_fileReadBuf = buf;
                g_fileAsyncMode = 1;
            } else {
            retry:
                CdRead(offset >> 11, buf, 0x80);
                while ((status = CdReadSync(0, 0)) > 0) {
                }
                if (status == -1) {
                    goto retry;
                }
                File_EndOp();
            }
        }
    } else {
        File_QueueRequest(obj, 0, 5, (s32)buf, offset);
    }
    File_Unlock();
    return 0;
}

void File_LoadWholeCd(FileOpenObject *obj, char *name) {
    s32 size;
    DirEntry *entry;
    u8 *buf;
    s32 r;
    u8 *cur;
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
            sectors = entry->size >> 11;
            g_fileReadSectorCount = sectors;
            if (entry->size & 0x7FF) {
                g_fileReadSectorCount = sectors + 1;
            }
            cur = obj->data;
            size = g_fileReadSectorCount << 11;
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
                    CdControl(2, (u8 *)&g_fileCurEntry->pos, 0);
                    while ((r = CdSync(0, 0)) == 0) {}
                } while (r == 5);
                CdRead(g_fileReadSectorCount, obj->data, 0x80);
                while ((r = CdReadSync(0, 0)) > 0) {}
                if (r == -1) {
                    goto retry;
                }
                obj->size = size;
                g_fileRequestHead->running = 1;
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
    File *obj;

    File_Lock();
    req = g_fileRequestHead;
    if (req != NULL) {
        obj = req->file;
        kind = req->kind;
        if (req->running == 0) {
            obj->direct = 1;
            switch (kind) {
            case 2:
                obj->vtbl->open(obj, File_EntryAt(req->index), req->param0, req->param1);
                break;
            case 3:
                obj->vtbl->close(obj);
                break;
            case 4:
                obj->vtbl->seek(obj, req->param0, req->param1);
                break;
            case 5:
                obj->vtbl->read(obj, req->param0, req->param1);
                break;
            case 7:
                obj->vtbl->load(obj, File_EntryAt(req->index));
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
            obj->vtbl->onLoaded(obj);
            File_FreeRequest(req);
            if (g_fileRequestHead == NULL) {
                obj->vtbl->stop(obj);
            }
        }
    }
    File_Unlock();
}

void File_RequestLoad(File *obj, char *name) {
    FileRequest *uninit;

    File_Lock();
    if (name != 0) {
        if (g_fileEnabled != 0) {
            uninit->markLoaded = 1;
            File_QueueRequest((File *)obj, File_FindIndex(name), 7, 0, 0);
        } else {
            obj->vtbl->load(obj, name);
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
    FileRequest *node;
    FileRequest *cur;
    FileRequest *next;
    DirEntry *tmp;

    File_Lock();
    node = g_fileRequestHead;
    if (node != NULL && obj->pending != 0) {
        obj->flags = 0;
        if (node->file == obj && node->running != 0 && g_fileDone == 0) {
            CdFlush();
            File_EndOp();
            tmp = g_filePrevEntry;
            g_filePrevEntry = 0;
            g_fileCurEntry = tmp;
        }
        cur = g_fileRequestHead;
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

FileVtbl *File_GetVtable(void) {
    return &g_fileVtable;
}

static void File_InitCd(void) {
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

void File_SetDirTable(DirEntry *table) {
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

static s32 File_OnVSync(void) {
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
                File_GetVtable()->runQueue();
            }
            if (g_fileVSyncMode != 0) {
                VSyncCallback(File_OnVSync);
            }
        }
    }
    return 0;
}

static void File_HookVSync(void) {
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

static void File_UnhookVSync(void) {
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

static void File_ClearVSyncPending(void) {
    File_Lock();
    g_fileVSyncPending = 0;
    File_Unlock();
}

static void File_QueueRequest(File *obj, s32 index, s32 kind, s32 param3, s32 param4) {
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

static FileRequest *File_NewRequest(void) {
    FileRequest *node;
    FileRequest *last;

    File_Lock();
    node = Heap_Alloc(0x24);
    if (node != NULL) {
        node->prev = NULL;
        node->next = NULL;
        node->running = 0;
        node->markLoaded = 0;
        if (g_fileRequestHead != NULL) {
            last = g_fileRequestHead;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = node;
            node->prev = last;
        } else {
            g_fileRequestHead = node;
        }
    }
    File_Unlock();
    return node;
}

static void File_FreeRequest(FileRequest *node) {
    File_Lock();
    if (node != NULL) {
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            g_fileRequestHead = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        Heap_Free(node);
    }
    File_Unlock();
}

static DirEntry *File_FindEntry(char *name) {
    DirEntry *entry;
    s32 i;

    entry = g_fileDirTable;
    i = 0;
    File_Lock();
    do {
        if (strstr(entry->name, name) != NULL) {
            File_Unlock();
            return entry;
        }
        i++;
        entry++;
    } while (i < g_fileDirCount);
    return NULL;
}

static s32 File_FindIndex(char *name) {
    DirEntry *entry;
    s32 i;

    entry = g_fileDirTable;
    i = 0;
    File_Lock();
    do {
        if (strstr(entry->name, name) != NULL) {
            File_Unlock();
            return i;
        }
        entry++;
        i++;
    } while (i < g_fileDirCount);
    return -1;
}

static DirEntry *File_EntryAt(s32 index) {
    DirEntry *entry;

    entry = g_fileDirTable;
    File_Lock();
    entry += index;
    File_Unlock();
    return entry;
}

static void File_PollIo(void) {
    File_Lock();
    switch (g_fileState) {
    case 1:
        if (CdControlF(2, (u8 *)&g_fileCurEntry->pos) != 0) {
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
        if (CdRead(g_fileReadSectorCount, g_fileReadBuf, 0x80) != 0) {
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

static void File_StepIo(void) {
    s32 nextState;
    s32 state;
    s32 retryCount;
    DirEntry *prevDir;
    s32 syncResult;

    File_Lock();
    state = g_fileState;
    switch (state) {
    case 1:
        if (CdControlF(2, (u8 *)&g_fileCurEntry->pos) != 0) {
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
        if (CdRead(g_fileReadSectorCount, g_fileReadBuf, 0x80) != 0) {
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

static void File_BeginOp(s32 kind, s32 state) {
    g_fileBusy = 1;
    g_fileOpKind = kind;
    g_fileState = state;
    g_fileDone = 0;
    g_fileRequestHead->running = 1;
}

static void File_EndOp(void) {
    g_fileOpKind = 0;
    g_fileState = 0;
    g_fileAsyncMode = 0;
    g_fileDone = 1;
    g_fileRetryCount = 0;
    g_fileBusy = 0;
}

static void File_SetState(s32 state) {
    g_fileState = state;
    g_fileRetryCount = 0;
}

static void File_InitSync(File *obj) {
    File_GetBaseVtbl()->init(obj);
    obj->vtbl = File_GetVtable();
    obj->isOpen = 0;
}

static void File_DestroySync(s32 handle) {
    File_GetBaseVtbl()->destroy(handle);
}

static void func_80028918(void) {
}

static void File_Locate(File *obj) {
    s32 tries;
    CdlFileDir file;
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

static void File_CloseSync(File *obj) {
    if (obj->isOpen != 0) {
        obj->isOpen = 0;
    }
}

static s32 File_GetSize(File *obj) {
    if (obj->isOpen != 0) {
        return ((obj->cdSize >> 0xB) + 1) << 0xB;
    }
    return 0;
}

static void func_80028A7C(void) {
}

static s32 File_ReadSync(File *obj, void *dst, u32 offset) {
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
    CdControl(2, (u8 *)&obj->cdPos, 0);
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

static void func_80028B64(void) {
}

s32 File_GetVSyncMode(void) {
    return g_fileVSyncMode;
}

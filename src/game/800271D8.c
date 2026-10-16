#include "common.h"

typedef struct FileLoadedView {
    u8 pad[0xC];
    s32 unkC;
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
    s32 unkC;
    u8 pad2[0xC];
    u32 unk1C;
} FileSizeView;
void File_UnhookVSync(void);
typedef struct ObjectClassTable {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    void (*unkC)(s32);
} ObjectClassTable;
ObjectClassTable *File_GetBaseVtbl(void);
void *File_GetVtable(void);
void File_InitCd(void);
typedef struct FileInitObject {
    void *unk0;
    u8 pad4[0x24];
    s16 unk28;
} FileInitObject;
typedef struct FileInitClassTable {
    u8 pad[8];
    void (*unk8)(FileInitObject *);
} FileInitClassTable;
s32 g_fileDirTable;
typedef struct FileVtSlot8 {
    u8 pad[0x8];
    void (*unk8)(s32);
} FileVtSlot8;
s32 Heap_Alloc(s32);
s32 g_fileCdReady;
void CdSetDebug(s32 level);
s32 CdControlB(s32 com, u8 *param, s32 result);
typedef struct FileInitRecord {
    void *unk0;
    u8 pad_04[0x8];
    s32 unkC;
} FileInitRecord;
typedef struct FileStepObject FileStepObject;
typedef struct {
    u8 pad[0x5C];
    void (*unk5C)(FileStepObject *);
    u8 pad2[0x74 - 0x60];
    void (*unk74)(void);
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
typedef struct FileObject {
    u8 pad[0x8];
    s32 unk8;
    void *unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad2[0x2];
    u16 unk22;
    s32 unk24;
    u16 unk28;
} FileObject;
void File_HookVSync(void);
FileObject *File_NewRequest(void);
typedef struct FileHandle FileHandle;
typedef struct {
    u8 pad[0x44];
    void (*unk44)(FileHandle *, s32, s32, s32);
    void (*unk48)(FileHandle *);
    void (*unk4C)(FileHandle *, s32, s32);
    u8 pad2[0x54 - 0x50];
    void (*unk54)(FileHandle *, s32, s32);
    void (*unk58)(FileHandle *, s32);
    u8 pad3[0x64 - 0x5C];
    void (*unk64)(FileHandle *);
    u8 pad4[0x70 - 0x68];
    void (*unk70)(FileHandle *);
} FileHandleVt;
struct FileHandle {
    FileHandleVt *vt;
    u8 pad[0x1E];
    u16 unk22;
    s32 unk24;
    u16 unk28;
};
typedef struct FileRequest FileRequest;
struct FileRequest {
    void *unk0;
    s32 unk4;
    s32 unk8;
    FileHandle *unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    FileRequest *unk1C;
    FileRequest *unk20;
};
void Heap_Free(void *);
typedef struct FileStateView {
    u8 pad[0xC];
    s32 unkC;
    u8 pad2[0x28 - 0x10];
    u16 unk28;
} FileStateView;
void File_BeginOp(s32 kind, s32 state);
void File_EndOp(void);
typedef struct FileVtPathSlot {
    u8 pad[0x58];
    void (*unk58)(FileObject *, char *);
} FileVtPathSlot;
s32 File_FindIndex(char *name);
void File_QueueRequest(FileObject *obj, s32 index, s32 kind, s32 param3, s32 param4);
typedef struct VSyncObject {
    /* 0x00 */ u8 pad_00[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 pad_10[0x10];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
} VSyncObject;
VSyncObject *Display_GetCurrent(void);
typedef struct VSyncHookVt {
    u8 pad[0x84];
    void (*unk84)(void *, void (*)(void));
} VSyncHookVt;
typedef struct VSyncHook {
    VSyncHookVt *vt;
} VSyncHook;
typedef struct FileVtVSyncSlot {
    u8 pad[0x68];
    void (*unk68)(void);
} FileVtVSyncSlot;
s32 g_fileLock;
s32 Heap_IsBusy(void);
void File_PollIo(void);
void File_StepIo(void);
typedef struct FileVtSlot48 {
    u8 pad[0x48];
    void (*unk48)(void *);
} FileVtSlot48;
typedef struct FileSeekView {
    FileVtSlot48 *unk0;
    u8 pad4[0x8];
    s32 unkC;
    u8 pad10[0x8];
    u8 unk18[0x8];
} FileSeekView;
s32 CdControl(s32 com, u8 *param, s32 result);
s32 CdRead(s32 sectors, void *buf, s32 mode);
s32 CdReadSync(s32 mode, u8 *result);
s32 CdSync(s32 mode, u8 *result);
typedef struct FileRequestLink FileRequestLink;
struct FileRequestLink {
    void *unk0;
    u8 pad4[0x8];
    void *unkC;
    u8 pad10[0x10];
    FileRequestLink *unk20;
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
    s32 unkC;
    u8 pad2[0x18 - 0x10];
    u8 unk18[4];
    u32 unk1C;
    u8 pad3[0x28 - 0x20];
    u16 unk28;
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
    s32 unkC;
    u8 pad2[0x8];
    CdlLoc unk18;
    s32 unk1C;
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
    CdlLocTail unk14;
    s32 unk18;
} DirEntryTail;
typedef struct CdlFileTail {
    CdlLocTail pos;
    s32 size;
    u8 name[0x10];
} CdlFileTail;
s32 File_FindEntry(char *name);
typedef struct FileVtOpen {
    u8 pad[0x48];
    void (*unk48)(void *);
    u8 pad2[0x64 - 0x4C];
    void (*unk64)(void *);
} FileVtOpen;
typedef struct FileOpenObject {
    FileVtOpen *unk0;
    u8 pad4[0xC];
    s32 unk10;
    s32 unk14;
    u8 pad18[0x8];
    u16 unk20;
    u8 pad22[0x2];
    s32 unk24;
    u16 unk28;
} FileOpenObject;
typedef struct DirEntrySize {
    u8 pad[0x18];
    u32 unk18;
} DirEntrySize;
void File_LoadWhole();

s32 File_Create(void) {
    s32 obj;

    obj = Heap_Alloc(0x2C);
    if (obj != 0) {
        ((FileVtSlot8 *)File_GetVtable())->unk8(obj);
        return obj;
    }
    return 0;
}

void File_InitObject(FileInitObject *obj) {
    ((FileInitClassTable *)File_GetBaseVtbl())->unk8(obj);
    obj->unk0 = File_GetVtable();
    obj->unk28 = 0;
    File_InitCd();
}

void File_Step(FileStepObject *obj) {
    obj->vt->unk74();
    obj->vt->unk5C(obj);
}

void func_800272C8(void) {
}

void File_LoadByName(FileObject *obj, char *name, s32 param2, s32 param3) {
    s8 path[0x40];
    CdlFileTail file;
    s32 result;

    if (g_fileEnabled == 0 && g_fileOption == 0) {
        File_Locate(obj);
        return;
    }
    File_Lock();
    if (obj->unk28 != 0) {
        if (g_fileBusy == 0 && obj->unkC == 0) {
            File_BeginOp(1, 1);
            if (g_fileEnabled != 0) {
                g_fileCurEntry = File_FindEntry(name);
                if (g_fileCurEntry == 0) {
                    return;
                }
                *(CdlLocTail *)&obj->unk18 = ((DirEntryTail *)g_fileCurEntry)->unk14;
                obj->unk1C = ((DirEntryTail *)g_fileCurEntry)->unk18;
                g_fileAsyncMode = 1;
                obj->unkC = (void *)1;
            } else {
                File_BuildPath(path, (s8 *)name);
                while (CdSearchFile(&file, path) == 0) {
                }
                *(CdlLocTail *)&obj->unk18 = file.pos;
                obj->unk1C = file.size;
                do {
                    CdControl(2, (u8 *)&obj->unk18, 0);
                    do {
                        result = CdSync(0, 0);
                    } while (result == 0);
                } while (result == 5);
                obj->unkC = (void *)1;
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
    if (obj->unk28 != 0) {
        if (g_fileBusy == 0) {
            File_BeginOp(0, 0);
            obj->unkC = 0;
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
    if (obj->unk28 != 0) {
        if (g_fileBusy == 0 && obj->unkC != 0) {
            File_BeginOp(2, 1);
            sector = offset >> 11;
            if (offset & 0x7FF) {
                sector++;
            }
            base = CdPosToInt(obj->unk18);
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
                v = obj->unk1C;
                if (v & 0x7FF) {
                    return ((v >> 11) + 1) << 11;
                }
                return v;
            }
        }
    } else {
        File_QueueRequest((FileObject *)obj, 0, 4, offset, mode);
    }
    File_Unlock();
    return 0;
}

void func_800276C8(void) {
}

s32 File_Read(FileStateView *obj, s32 buf, u32 offset) {
    s32 status;

    if ((g_fileEnabled == 0) && (g_fileOption == 0)) {
        File_ReadSync((FileSeekView *)obj, (void *)buf, offset);
        return 0;
    }
    File_Lock();
    if (obj->unk28 != 0) {
        if ((g_fileBusy == 0) && (obj->unkC != 0)) {
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
        File_QueueRequest((FileObject *)obj, 0, 5, buf, offset);
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
        obj->unk24 |= 0x200;
        obj->unk0->unk64(obj);
        return;
    }
    File_Lock();
    if (obj->unk28 != 0) {
        if (g_fileBusy == 0 && (obj->unk10 == 0 || obj->unk20 != 0)) {
            File_BeginOp(4, 1);
            g_filePrevEntry = g_fileCurEntry;
            entry = File_FindEntry(name);
            g_fileCurEntry = entry;
            if (entry == 0) {
                return;
            }
            sectors = ((DirEntrySize *)entry)->unk18 >> 11;
            g_fileReadSector = sectors;
            if (((DirEntrySize *)entry)->unk18 & 0x7FF) {
                g_fileReadSector = sectors + 1;
            }
            cur = obj->unk10;
            size = g_fileReadSector << 11;
            if (cur == 0) {
                buf = Heap_Alloc(size);
                if (buf == 0) {
                    obj->unk0->unk48(obj);
                    return;
                }
                g_fileReadBuf = buf;
                obj->unk10 = buf;
            } else {
                g_fileReadBuf = cur;
            }
            if (g_fileEnabled != 0) {
                obj->unk14 = size;
                g_fileAsyncMode = 2;
            } else {
            retry:
                do {
                    CdControl(2, (u8 *)(g_fileCurEntry + 0x14), 0);
                    while ((r = CdSync(0, 0)) == 0) {}
                } while (r == 5);
                CdRead(g_fileReadSector, (void *)obj->unk10, 0x80);
                while ((r = CdReadSync(0, 0)) > 0) {}
                if (r == -1) {
                    goto retry;
                }
                obj->unk14 = size;
                *g_fileRequestHead = 1;
                File_EndOp();
            }
        }
    } else {
        File_QueueRequest((FileObject *)obj, File_FindIndex(name), 7, 0, 0);
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
        obj = req->unkC;
        kind = req->unk8;
        if (req->unk0 == NULL) {
            obj->unk28 = 1;
            switch (kind) {
            case 2:
                obj->vt->unk44(obj, File_EntryAt(req->unk10), req->unk14, req->unk18);
                break;
            case 3:
                obj->vt->unk48(obj);
                break;
            case 4:
                obj->vt->unk4C(obj, req->unk14, req->unk18);
                break;
            case 5:
                obj->vt->unk54(obj, req->unk14, req->unk18);
                break;
            case 7:
                obj->vt->unk58(obj, File_EntryAt(req->unk10));
                break;
            }
            obj->unk28 = 0;
        } else if (g_fileDone != 0) {
            if (req->unk4 != 0) {
                obj->unk24 |= 1;
            }
            obj->unk24 |= 2;
            obj->unk22--;
            if (obj->unk22 == 0) {
                obj->unk24 |= 4;
            }
            switch (kind) {
            case 2:
                obj->unk24 |= 0x10;
                break;
            case 3:
                obj->unk24 |= 0x20;
                break;
            case 4:
                obj->unk24 |= 0x40;
                break;
            case 5:
                obj->unk24 |= 0x80;
                break;
            case 7:
                obj->unk24 |= 0x200;
                break;
            }
            obj->vt->unk64(obj);
            File_FreeRequest(req);
            if (g_fileRequestHead == NULL) {
                obj->vt->unk70(obj);
            }
        }
    }
    File_Unlock();
}

void File_RequestOpen(FileObject *obj, char *name) {
    FileRequest *uninit;

    File_Lock();
    if (name != 0) {
        if (g_fileEnabled != 0) {
            uninit->unk4 = 1;
            File_QueueRequest(obj, File_FindIndex(name), 7, 0, 0);
        } else {
            (*(FileVtPathSlot **)obj)->unk58(obj, name);
            if (obj->unk22 == 0) {
                obj->unk24 = obj->unk24 | 4;
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

void File_CancelRequests(FileObject *obj) {
    FileRequestLink *node;
    FileRequestLink *cur;
    FileRequestLink *next;
    s32 tmp;

    File_Lock();
    node = (FileRequestLink *)g_fileRequestHead;
    if (node != NULL && obj->unk22 != 0) {
        obj->unk24 = 0;
        if (node->unkC == obj && node->unk0 != NULL && g_fileDone == 0) {
            CdFlush();
            File_EndOp();
            tmp = g_filePrevEntry;
            g_filePrevEntry = 0;
            g_fileCurEntry = tmp;
        }
        cur = (FileRequestLink *)g_fileRequestHead;
        while (cur != NULL) {
            next = cur->unk20;
            if (cur->unkC == obj) {
                File_FreeRequest(cur);
                obj->unk22--;
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
    VSyncHook *temp;

    if (g_fileBusy == 0) {
        if (mode == 0) {
            temp = (VSyncHook *)Display_GetCurrent();
            if (g_fileEnabled == 0) {
                if (enabled != 0) {
                    temp->vt->unk84(temp, File_OnVSync);
                }
            } else {
                if (enabled == 0) {
                    temp->vt->unk84(temp, NULL);
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
                ((FileVtVSyncSlot *)File_GetVtable())->unk68();
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

void File_QueueRequest(FileObject *obj, s32 index, s32 kind, s32 param3, s32 param4) {
    FileObject *req;

    req = File_NewRequest();
    req->unk8 = kind;
    req->unk14 = param3;
    req->unkC = obj;
    req->unk10 = index;
    req->unk18 = param4;
    obj->unk24 = 0;
    obj->unk22 = obj->unk22 + 1;
    File_HookVSync();
}

FileObject *File_NewRequest(void) {
    FileRequest *node;
    FileRequest *last;

    File_Lock();
    node = (FileRequest *)Heap_Alloc(0x24);
    if (node != NULL) {
        node->unk1C = NULL;
        node->unk20 = NULL;
        node->unk0 = NULL;
        node->unk4 = 0;
        if (g_fileRequestHead != NULL) {
            last = (FileRequest *)g_fileRequestHead;
            while (last->unk20 != NULL) {
                last = last->unk20;
            }
            last->unk20 = node;
            node->unk1C = last;
        } else {
            g_fileRequestHead = (s32 *)node;
        }
    }
    File_Unlock();
    return (FileObject *)node;
}

void File_FreeRequest(FileRequest *node) {
    File_Lock();
    if (node != NULL) {
        if (node->unk1C != NULL) {
            node->unk1C->unk20 = node->unk20;
        } else {
            g_fileRequestHead = (s32 *)node->unk20;
        }
        if (node->unk20 != NULL) {
            node->unk20->unk1C = node->unk1C;
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
    File_GetBaseVtbl()->unk8(obj);
    obj->unk0 = File_GetVtable();
    obj->unkC = 0;
}

void File_Destroy(s32 handle) {
    File_GetBaseVtbl()->unkC(handle);
}

void func_80028918(void) {
}

void File_Locate(FileLoadState *obj) {
    s32 tries;
    CdlFile file;
    s8 name[0x40];

    tries = 0;
    if (obj->unkC == 0) {
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
        obj->unk18 = file.pos;
        obj->unk1C = file.size;
        obj->unkC = 1;
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
    if (obj->unkC != 0) {
        obj->unkC = 0;
    }
}

s32 File_GetSize(FileSizeView *obj) {
    if (obj->unkC != 0) {
        return ((obj->unk1C >> 0xB) + 1) << 0xB;
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

    if (obj->unkC == 0) {
        goto fallback;
    }
retry:
    sectors = offset >> 11;
    CdControl(2, obj->unk18, 0);
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
    obj->unk0->unk48(obj);
    return 0;
}

void func_80028B64(void) {
}

s32 File_GetVSyncMode(void) {
    return g_fileVSyncMode;
}

#ifndef GAME_TMD_H
#define GAME_TMD_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/model_object.h"

/*
 * TMD model file (vtable g_tmdVtbl, 0x30 bytes, Tmd_Create): ETC\DREAMER.TMD,
 * ETC\DREAME5.TMD and the TMD inside each MOM. onLoaded maps it with GsMapModelingData and
 * makes one model object (ModelObject_Create) per TMD object.
 */

typedef struct TmdHeader {
    u32 id;               /* 0x41 */
    u32 flags;            /* GsMapModelingData gets its address */
    u32 objectCount;
    ModelEntry objects[1]; /* the Sony TMD object table, 0x1C bytes each (model_object.h) */
} TmdHeader;

typedef struct TmdVtbl {
    FileVtbl base;
    void (*mapModelingData)(); /* 0x78 Tmd_MapModelingData */
    ModelEntry *(*getObject)(); /* 0x7C Tmd_GetObject (self, index): address of TMD object index */
    ModelObject *(*getModel)(); /* 0x80 Tmd_GetModel (self, index) */
    void (*unk_84)();          /* Tmd_EmptySlot84, empty */
} TmdVtbl;

typedef struct Tmd {
    TmdVtbl *vtbl;            /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    union {
        u8 *bytes;
        u32 *words;
        TmdHeader *header;
    } data;                   /* 0x10 */
    s32 size;
    CdlLocDir cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
    ModelObject **models;     /* 0x2C one model per TMD object, NULL-terminated */
} Tmd;

/* Functions of src/game/tmd.c that other files call or reference (docs/naming.md, Prototypes) */
Tmd *Tmd_Create(FileSource *source);
TmdVtbl *Tmd_GetVtbl(void);

#endif

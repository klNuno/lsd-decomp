#ifndef GAME_TMD_H
#define GAME_TMD_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * TMD model file (vtable g_tmdVtbl, 0x30 bytes, Tmd_Create): ETC\DREAMER.TMD,
 * ETC\DREAME5.TMD and the TMD inside each MOM. onLoaded maps it with GsMapModelingData and
 * makes one model object (ModelObject_Create) per TMD object.
 */
typedef struct TmdObjectEntry {
    u32 vertices;         /* Sony TMD object table entry, 0x1C bytes */
    u32 vertexCount;
    u32 normals;
    u32 normalCount;
    u32 primitives;
    u32 primitiveCount;
    s32 scale;
} TmdObjectEntry;

typedef struct TmdHeader {
    u32 id;               /* 0x41 */
    u32 flags;            /* GsMapModelingData gets its address */
    u32 objectCount;
    TmdObjectEntry objects[1];
} TmdHeader;

typedef struct TmdVtbl {
    FileVtbl base;
    void (*mapModelingData)(); /* 0x78 Tmd_MapModelingData */
    s32 (*getObject)();        /* 0x7C Tmd_GetObject (self, index): address of TMD object index */
    s32 (*getModel)();         /* 0x80 Tmd_GetModel (self, index) */
    void (*unk_84)();          /* Tmd_EmptySlot84, empty */
} TmdVtbl;

typedef struct Tmd {
    TmdVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    union {
        s32 addr;
        u32 *words;
        TmdHeader *header;
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
    Object **models;          /* 0x2C one model per TMD object, NULL-terminated */
} Tmd;

/* Functions of src/game/tmd.c that other files call or reference (docs/naming.md, Prototypes) */
s32 Tmd_Create(s32 source);
TmdVtbl *Tmd_GetVtbl(void);

#endif

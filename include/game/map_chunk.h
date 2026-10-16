#ifndef GAME_MAP_CHUNK_H
#define GAME_MAP_CHUNK_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"

/* The chunk object of a slot (MapChunk_New, 0x3C bytes, src/game/map_chunk.c): a file object (file_base.h
   File) that reads one STGxx\Mxxx.LBD chunk file, then its entity part. Vtable g_mapChunkVtbl: the file
   class slots, then the chunk's own. */
typedef struct MapChunkVtbl {
    s32 classWord;           /* 0x903 */
    void *(*delete_)();      /* 0x04 File_Delete */
    void (*init)();          /* 0x08 MapChunk_Init */
    void (*destroy)();       /* 0x0C MapChunk_Destroy */
    u8 pad_10[0x44 - 0x10];  /* Object methods, then 0 */
    void (*open)();          /* 0x44 (self, path, 1, 0) */
    void (*close)();         /* 0x48 */
    void (*seek)();          /* 0x4C (self, offset, whence) */
    u8 pad_50[0x54 - 0x50];
    void (*read)();          /* 0x54 (self, buffer, size) */
    u8 pad_58[0x5C - 0x58];
    void (*freeData)();      /* 0x5C File_FreeData */
    void (*unk_60)();        /* 0x60 func_80026C80, empty */
    void (*onLoaded)();      /* 0x64 MapChunk_OnLoaded */
    u8 pad_68[0x74 - 0x68];
    void (*unload)();        /* 0x74 MapChunk_Unload, replaces the file class cancel slot */
    void (*load)();          /* 0x78 MapChunk_Load (chunk, data from the stage's chunk loader) */
    void (*clear)();         /* 0x7C MapChunk_Clear */
    void (*loadEntities)();  /* 0x80 MapChunk_LoadEntities */
    void (*freeEntities)();  /* 0x84 MapChunk_FreeEntities */
    void (*setLoadEntities)(); /* 0x88 MapChunk_SetLoadEntities (chunk, flag given to StageMap_Init) */
} MapChunkVtbl;

/* The header of a chunk file: the model list, then the TMD, then the entity part. */
typedef struct MapChunkData {
    u8 pad_00[2];
    u16 hasEntities;         /* 0x02 non-zero: the file has an entity part (slot 0x80) */
    s32 modelsOffset;        /* 0x04 the model list, handed to the slot's model set */
    s32 modelsSize;          /* 0x08 the TMD follows the list */
    u8 pad_0C[0x10 - 0x0C];
    s32 entitiesOffset;      /* 0x10 file offset of the entity part */
    s32 entitiesSize;        /* 0x14 */
} MapChunkData;

typedef struct MapChunk {
    MapChunkVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    MapChunkData *data;      /* 0x10 the 0xB358-byte chunk buffer */
    s32 size;                /* 0x14 0xB358 once the buffer exists */
    u8 pad_18[0x20 - 0x18];
    u16 keepData;            /* 0x20 File.keepData: set to data != NULL at creation */
    u8 pad_22[0x24 - 0x22];
    s32 flags;               /* 0x24 done file requests: 0x80 read */
    u8 pad_28[0x2A - 0x28];
    u16 state;               /* 0x2A 9 reading the chunk, 10 reading its entity part, 0 idle */
    s16 loaded;              /* 0x2C 0 empty; non-zero once its data is in, 2 after StageMap_BuildTiles built its tiles */
    s16 entitiesLoaded;      /* 0x2E StageMap_PollLoads clears it and sends slot message 7 */
    s16 index;               /* 0x30 chunk index in the stage grid (row * cols + col), -1 when empty */
    s16 id;                  /* 0x32 neighbour position 0 to 6 (StageMap_LoadAround) */
    s32 entities;            /* 0x34 the entity part (heap), first argument of Sym_SpawnOrSpy (Place_SpawnCell) */
    s32 loadEntities;        /* 0x38 read the entity part as soon as the chunk is in */
} MapChunk;

/* Functions of src/game/map_chunk.c that other files call or reference (docs/naming.md, Prototypes) */
s32 MapChunk_New(void);
MapChunkVtbl *MapChunk_GetVtbl(void);

#endif

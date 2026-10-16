#include "common.h"
#include "game/loader.h"
#include "game/stage.h"
#include "game/map_chunk.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * The map chunk file class (vtable g_mapChunkVtbl, 0x3C bytes, created by MapChunk_New for each
 * StageMap slot): a file object of src/game/file_base.c with a 0xB358-byte buffer that receives a
 * stage's STGxx\Mxxx.LBD chunk file (slot 0x78), then, when the header says so, a second read of
 * the chunk's entity part into its own heap block (slot 0x80). include/game/stage.h holds the
 * part of it StageMap reads (MapChunk); MapChunk below is the whole object.
 *
 * File boundaries: likely (docs/layout.md)
 */

extern u8 g_mapChunkVtbl[];      /* MapChunkVtbl */

s32 MapChunk_New(void) {
    s32 chunk;

    chunk = Heap_Alloc(0x3C);
    if (chunk != 0) {
        MapChunk_GetVtbl()->init(chunk);
        return chunk;
    }
    return 0;
}

/* Slot 0x08 */
void MapChunk_Init(MapChunk *chunk) {
    File_GetBackendVtbl()->init(chunk);
    chunk->vtbl = MapChunk_GetVtbl();
    chunk->index = -1;
    chunk->loaded = 0;
    chunk->entitiesLoaded = 0;
    chunk->id = 0;
    chunk->entities = 0;
    chunk->loadEntities = 1;
    chunk->data = ((void *)Heap_Alloc(0xB358));
    if (chunk->data != NULL) {
        chunk->size = 0xB358;
    }
}

/* Slot 0x0C */
void MapChunk_Destroy(MapChunk *chunk) {
    chunk->vtbl->freeEntities(chunk);
    File_GetBackendVtbl()->destroy(chunk);
}

/* Slot 0x64, after each finished file request */
void MapChunk_OnLoaded(MapChunk *chunk) {
    u16 state;

    state = chunk->state;
    if (state == 9) {
        if (chunk->flags & 0x80) {
            s32 loadEntities = chunk->loadEntities;

            chunk->state = 0;
            chunk->loaded = 1;
            if (loadEntities != 0) {
                chunk->vtbl->loadEntities();
            }
        }
    } else if (state == 0xA) {
        if (chunk->flags & 0x80) {
            chunk->entitiesLoaded = 1;
            chunk->state = 0;
        }
    }
    File_GetBackendVtbl()->onLoaded(chunk);
}

/* Slot 0x74: drops the pending requests */
void MapChunk_Unload(MapChunk *chunk) {
    File_GetBackendVtbl()->cancel(chunk);
    chunk->loaded = 0;
    chunk->entitiesLoaded = 0;
    chunk->state = 0;
}

/* Slot 0x78: reads the chunk file at path into the buffer */
void MapChunk_Load(MapChunk *chunk, s32 path) {
    if ((chunk->data != NULL) && (path != 0)) {
        if (chunk->state == 0) {
            chunk->loaded = 0;
        } else {
            chunk->vtbl->unload(chunk);
        }
        chunk->state = 9;
        chunk->vtbl->close(chunk);
        chunk->vtbl->open(chunk, path, 1, 0);
        chunk->vtbl->read(chunk, chunk->data, 0xB358);
    }
}

/* Slot 0x7C */
void MapChunk_Clear(MapChunk *chunk) {
    chunk->vtbl->freeData();
    chunk->loaded = 0;
    chunk->index = -1;
}

/* Slot 0x80: reads the entity part of the chunk file into a new heap block; 1 when started */
s32 MapChunk_LoadEntities(MapChunk *chunk) {
    s32 size;
    s32 entities;

    if ((chunk->data->hasEntities != 0) && (chunk->state == 0)) {
        chunk->vtbl->freeEntities(chunk);
        size = chunk->data->entitiesSize;
        entities = Heap_Alloc(size);
        chunk->entities = entities;
        if (entities != 0) {
            chunk->state = 10;
            chunk->vtbl->seek(chunk, chunk->data->entitiesOffset, 0);
            chunk->vtbl->read(chunk, chunk->entities, size);
            return 1;
        }
    }
    return 0;
}

/* Slot 0x84 */
void MapChunk_FreeEntities(MapChunk *chunk) {
    s32 entities;

    entities = chunk->entities;
    chunk->entitiesLoaded = 0;
    if (entities != 0) {
        chunk->entities = Heap_Free(entities);
    }
}

/* Slot 0x88 */
void MapChunk_SetLoadEntities(MapChunk *chunk, s32 loadEntities) {
    chunk->loadEntities = loadEntities;
}

MapChunkVtbl *MapChunk_GetVtbl(void) {
    return (MapChunkVtbl *)g_mapChunkVtbl;
}

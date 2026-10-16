#ifndef GAME_MAP_MODELS_H
#define GAME_MAP_MODELS_H

#include "common.h"
#include "game/heap.h"

/* The model set of a slot (MapModels_New(0)): slot 0x78 hands out the chunk's models one by one. */
typedef struct MapModelsVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();     /* 0x04 */
    u8 pad_08[0x78 - 0x08];
    void *(*nextModel)();   /* 0x78 (models, out record, index): NULL at the end, -1 for an empty square */
} MapModelsVtbl;

typedef struct MapModels {
    MapModelsVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    void *data;             /* 0x10 */
    s32 size;
    u8 pad_18[0x2C - 0x18];
    struct Tmd *tmd;        /* 0x2C the chunk's TMD, Tmd_Create (tmd.h) */
} MapModels;

/* Functions of src/game/map_models.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/map_models.c */
struct ModelSetVtbl;
MapModels *MapModels_New(s32 path);
struct ModelSetVtbl *MapModels_GetVtbl(void);

#endif

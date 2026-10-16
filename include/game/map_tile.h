#ifndef GAME_MAP_TILE_H
#define GAME_MAP_TILE_H

#include "common.h"
#include "game/gs.h"
#include "game/scene_node.h"

/* A tile (class 0x80086AA0, 0x3C bytes): a GsDOBJ2 at +0x10 (GsLinkObject4 in StageMap_BuildTiles). */
typedef struct MapTileVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();     /* 0x04 */
    void (*init)();         /* 0x08 MapTile_Init */
    u8 pad_0C[0x38 - 0x0C];
    void (*onNotify)();        /* 0x38 run on the tiles of the view by MapTile_Tell */
    u8 pad_3C[0x48 - 0x3C];
    void (*setScale)();        /* 0x48 (tile, 0 or 1, 12-byte record) from StageMap_AddTileStretchStep and StageMap_ResetOneTileScale */
    void (*attach)();        /* 0x4C (tile, parent, position) */
    u8 pad_50[0x70 - 0x50];
    void (*setLightFlags)();
    u8 pad_74[0xA0 - 0x74];
    void (*checkContact)();        /* 0xA0 SceneNode_CheckContact */
    u8 pad_A4[0xB8 - 0xA4];
    void (*onActorMessage)();        /* 0xB8 MapTile_OnActorMessage */
} MapTileVtbl;

typedef struct MapTileModel {
    u8 pad_00[0x10];
    u32 *tmd;               /* 0x10 handed to GsLinkObject4 */
} MapTileModel;

typedef struct MapTile {
    MapTileVtbl *vtbl;
    u8 pad_04[0x10 - 0x04];
    s32 attribute;          /* 0x10 GsDOBJ2.attribute; bit 31 (GsDOFF) hides the tile */
    Coord2 *coord;          /* 0x14 GsDOBJ2.coord2 */
    u32 *tmd;               /* 0x18 GsDOBJ2.tmd */
    u8 pad_1C[0x20 - 0x1C];
    MapTileModel *model;    /* 0x20 */
    u8 pad_24[0x34 - 0x24];
    s16 unk34;
    u16 flags;              /* 0x36 bit 0x80: told through slot 0x38 by MapTile_Tell */
    struct MapTile *next;   /* 0x38 more tiles on the same square (from index 400 of the slot's array) */
} MapTile;

#define MAP_TILE_HIDDEN 0x80000000
#define MAP_SLOT_TILES 410      /* 20 x 20 squares and 10 extra tiles */

/* Functions of src/game/map_tile.c that other files call or reference (docs/naming.md, Prototypes) */
MapTile *MapTile_New(void);

#endif

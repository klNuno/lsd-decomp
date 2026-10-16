#include "common.h"
#include "game/stage.h"
#include "game/scene.h"

/*
 * MapTile (vtable g_mapTileVtbl 0x80086AA0, types in game/stage.h): one tile model of a chunk, a
 * GsDOBJ2 at +0x10.
 *
 * File boundaries: likely (docs/layout.md)
 */

extern char g_mapTileVtbl[];

s32 Heap_Alloc(s32 size);
SceneNodeVtbl *SceneNode_GetVtbl(void);
MapTileVtbl *MapTile_GetVtbl(void);
s32 MapTile_New(void);

s32 MapTile_New(void) {
    s32 tile;

    tile = Heap_Alloc(0x3C);
    if (tile != 0) {
        MapTile_GetVtbl()->init(tile);
        return tile;
    }
    return 0;
}

void MapTile_Init(MapTile *tile) {
    SceneNode_GetVtbl()->init(tile);
    tile->vtbl = MapTile_GetVtbl();
    tile->unk34 = 0;
    tile->flags = 0;
    tile->next = 0;
}

void MapTile_Reset(void) {
}

void MapTile_OnNode(MapTile *tile, u8 **message) {
    if (**message == 0x34) {
        tile->vtbl->unkB8(tile);
    }
}

void MapTile_OnActorMessage(MapTile *tile, void *sender, s32 message) {
    SceneNode_GetVtbl()->onNode(tile, sender, message);
    if (message < 9) {
        if (message >= 5) {
            tile->vtbl->unkA0(tile, sender, message);
        }
    }
}

s32 MapTile_GetSelf(s32 tile) {
    return tile;
}

MapTileVtbl *MapTile_GetVtbl(void) {
    return (MapTileVtbl *)g_mapTileVtbl;
}

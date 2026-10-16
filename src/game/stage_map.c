#include "common.h"
#include "game/stage_map.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"
#include "game/map_models.h"
#include "game/root_node.h"
#include "game/tmd.h"
#include "game/map_chunk.h"
#include "game/stage.h"
#include "game/map_tile.h"
#include "psyq/libgte.h"
#include "psyq/libgs.h"

/*
 * StageMap (vtable g_stageMapVtbl 0x800866E8, types in game/stage_map.h): the map that keeps the 7
 * chunks around the dreamer loaded and shows the tiles in view.
 *
 * File boundaries: likely (docs/layout.md)
 */

extern u8 g_stageMapVtbl[];
extern Vec3 g_mapDefaultOrigin;         /* default map origin (0, 0, 0) */
extern Vec3 g_chunkNeighborOffsets[];       /* per neighbour: offset of its chunk corner from the centre chunk's centre */
extern s32 g_neighborBits[];        /* per neighbour: 1 << neighbour */
extern HexNeighbor g_chunkNeighborSteps[];
extern s8 g_neighborLayoutById[];         /* per chunk id: which g_neighborLoadLists list to load around it */
extern NeighborUse g_allNeighbors[];
extern NeighborUse *g_neighborLoadLists[];
extern MapView g_wholeChunkView;      /* {slot -1, 0, 0, 20, 20}: a whole chunk */
extern MapTileStep g_tileStretchSlowUp, g_tileStretchFastUp, g_tileStretchSlowDown, g_tileStretchFastDown;
extern s32 g_tileScaleOne;

extern Matrix GsIDMATRIX;    /* in .bss; StageMap_ComputeFlatView copies it, RotMatrix fills the rotation */

/* What StageMap slot 0xB8 (RootNode_GetLight) returns. */
typedef struct MapChildVtbl {
    u8 pad_00[0x44];
    void (*setColor)();
    void (*setVector)();
} MapChildVtbl;

typedef struct MapChild {
    MapChildVtbl *vtbl;
} MapChild;

/* The record MapModels slot 0x78 fills for each model, 0x40 bytes. */
typedef struct MapModelRecord {
    u8 pad_00[0x0C];
    Vec3 pos;                   /* 0x0C position in the chunk */
    u8 pad_18[0x1A - 0x18];
    u16 rotY;                   /* 0x1A yaw, into the tile's rotate[1] */
    u8 pad_1C[0x2E - 0x1C];
    u16 flags;                  /* 0x2E into MapTile.flags */
    s32 extra;                  /* 0x30 placed from tile 400 on instead of on its square */
    s32 chained;                /* 0x34 the next model stacks on the same square */
    u8 pad_38[0x40 - 0x38];
} MapModelRecord;

/* The box +0x1DC points to (StageMap_IsOutsideBounds): tiles x0..x1, y0..y1. */
typedef struct MapBox {
    s16 x0;
    s16 y0;
    s32 x1;
    s32 y1;
} MapBox;

s32 g_mapDefaultViewDistance; /* view distance StageMap_Reset sets */

static StageMapVtbl *StageMap_GetVtbl(void);
/* not from game/scene_node.h: other files read this vtable through their own views of the slots */
SceneNodeVtbl *SceneNode_GetVtbl(void);
/* the vtable of root_node.c through this file's view of its slots, so not from game/root_node.h */
SceneNodeVtbl *RootNode_GetVtbl(void);
static s32 Stage_PlaceToWorld(Vec3 *pos, Vec3 *chunkCenter, StageGrid *grid, Vec3 *origin, StagePlace *place);
static s32 StageMap_CountLoading(StageMap *map);
static void MapTile_Tell(MapTile *tile, MapActor *sender, s32 message);
static void StageMap_SetNearView();
static void StageMap_SetNearViewStacked();
static void StageMap_TellViewTiles(StageMap *map, MapActor *sender, s32 message);
static s32 StageMap_GetNeighborMask(StageMap *map, s32 chunkIndex, s32 oddRow);
static s32 StageMap_RequestNeighbor(StageMap *map, ChunkRequest *request, s32 cols, s32 oddRow, s32 chunkIndex, s32 mask, s32 neighbor);
static void StageMap_ChunkColRow(StageMap *map, StagePlace *place, s32 chunkIndex);
static void StageMap_ComputeFlatView(StageMap *map, s32 width, s32 depth);
static void StageMap_SplitView();
static s32 StageMap_SplitViewRows(StageMap *map, MapView *view, s32 index, s32 neighbor, s32 x, s32 y, s32 cols, s32 rows);
static void StageMap_ComputeStackedView(StageMap *map);
static s32 StageMap_IsOutsideBounds(void *box, void *tile);
static s32 StageMap_AddChunkView(StageMap *map, s32 unused, s32 index, s32 chunkIndex);
static void StageMap_ShowView(StageMap *map, s32 show);
static void StageMap_AddTileStretchStep();
static void StageMap_ResetOneTileScale(s32 map, MapTile *tile);
static void StageMap_ForEachTile(StageMap *map, void (*perTile)(), void (*perSlot)(void *, void *));
static void StageMap_ForEachSlotTile(StageMap *map, void (*perTile)(), MapSlot *slot);

s32 StageMap_New(s32 origin, s32 loadEntities) {
    s32 map;

    map = Heap_Alloc(0x1E8);
    if (map != 0) {
        StageMap_GetVtbl()->init(map, origin, loadEntities);
        return map;
    }
    return 0;
}

/* Constructor: 7 slots, each with its chunk object, model set, origin node and 410 tiles laid 0x800 apart. */
void StageMap_Init(StageMap *map, Vec3 *origin, s32 loadEntities) {
    Vec3 pos;
    MapSlot *slot;
    MapChunk *chunk;
    MapTile *tile;
    MapTile **p;
    MapTile **end;
    s32 i;

    RootNode_GetVtbl()->init(map);
    map->vtbl = StageMap_GetVtbl();
    if (origin != NULL) {
        map->origin = *origin;
    } else {
        map->origin = g_mapDefaultOrigin;
    }
    map->swapping = 0;
    map->pendingSlots = 0;
    map->ready = 0;
    map->active = 0;
    map->target = NULL;
    map->messageFilter = NULL;
    map->stretchTicks = 0;
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        slot->chunk = MapChunk_New();
        slot->chunk->keepData = (slot->chunk->data != 0);
        slot->chunk->id = i;
        chunk = slot->chunk;
        chunk->vtbl->setLoadEntities(chunk, loadEntities);
        slot->spawned = 0;
        slot->unk18 = 0;
        slot->index = i;
        slot->loading = 0;
        slot->models = MapModels_New(0);
        tile = (MapTile *)MapTile_New();
        slot->root = tile;
        tile->vtbl->attach(tile, map, &map->origin);
        slot->tiles = (MapTile **)Heap_Alloc(0x668);
        if (slot->tiles == NULL) {
            return;
        }
        pos.x = 0x400;
        pos.y = 0;
        pos.z = 0x400;
        end = (MapTile **)((u8 *)slot->tiles + 0x668);
        for (p = slot->tiles; p < end; p++) {
            tile = (MapTile *)MapTile_New();
            *p = tile;
            tile->vtbl->attach(tile, slot->root, &pos);
            pos.x += 0x800;
            if (pos.x > 0xA400) {
                pos.x = 0x400;
                pos.z += 0x800;
            }
            tile = *p;
            tile->vtbl->setLightFlags(tile, 1);
            tile = *p;
            tile->attribute = (s32)(tile->attribute | MAP_TILE_HIDDEN);
        }
    }
    map->vtbl->watch(map, Display_GetCurrent());
    map->vtbl->reset(map);
}

void StageMap_Destroy(StageMap *map) {
    MapSlot *slot;
    MapTile *tile;
    MapTile **p;
    MapTile **end;
    s32 i;

    map->vtbl->unwatch(map, Display_GetCurrent());
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        map->vtbl->onSlotMessage(map, 6, slot, i);
        if (slot->chunk != NULL) {
            slot->chunk->vtbl->delete_(slot->chunk);
        }
        if (slot->models != NULL) {
            if (slot->models->tmd != NULL) {
                slot->models->tmd->vtbl->delete_(slot->models->tmd);
            }
            slot->models = slot->models->vtbl->delete_(slot->models);
        }
        if (slot->root != NULL) {
            slot->root->vtbl->delete_(slot->root);
        }
        end = slot->tiles + MAP_SLOT_TILES;
        for (p = slot->tiles; p < end; p++) {
            tile = *p;
            if (tile != NULL) {
                tile->vtbl->delete_(tile);
            }
        }
        Heap_Free(slot->tiles);
    }
    RootNode_GetVtbl()->destroy(map);
}

void StageMap_OnNotify(StageMap *map, s32 **sender, s32 message) {
    SceneNode_GetVtbl()->onNotify(map, sender, message);
    if ((**sender & 0xF) == 1) {
        map->vtbl->pollLoads(map, sender, message);
    }
}

void StageMap_Reset(StageMap *map) {
    map->grid = NULL;
    map->messageFilter = NULL;
    map->viewCount = 0;
    map->vtbl->setViewDistance(map, g_mapDefaultViewDistance);
    map->unk1CC[0] = -1;
    map->unk1CC[1] = -1;
    map->unk1CC[2] = -1;
    map->unk1CC[3] = -1;
}

/* Message 6 (slot emptied) deletes the slot's +0x14 object; 6 and 7 make it the current slot and notify the watchers. */
void StageMap_OnSlotMessage(StageMap *map, s32 message, MapSlot *slot) {
    Object *obj;

    SceneNode_GetVtbl()->sendBoxes(map, message);
    switch (message) {
    case 6:
        obj = slot->spawned;
        if (obj != NULL) {
            slot->spawned = obj->vtbl->delete_(obj);
        }
        /* fallthrough */
    case 7:
        map->currentSlot = slot;
        map->vtbl->notify(map, message);
        return;
    }
}

void StageMap_Tick(StageMap *map) {
    if (map->active != 0) {
        map->vtbl->follow(map);
        map->vtbl->stepTileStretch(map);
    }
}

/* Message 0x34 goes to slot 0xD0 with the same arguments still in a1 and a2. */
void StageMap_OnNode(StageMap *map, u8 **message) {
    if (**message == 0x34) {
        map->vtbl->filterMessage(map);
    }
}

void StageMap_ClearSlots(StageMap *map) {
    MapSlot *slot;
    MapModels *models;
    s32 i;

    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        slot->chunk->vtbl->unload(slot->chunk);
        slot->loading = 0;
        map->vtbl->hideSlot(map, slot);
        models = slot->models;
        if (models->tmd != NULL) {
            models->tmd = models->tmd->vtbl->delete_(models->tmd);
        }
        map->vtbl->onSlotMessage(map, 6, slot, i);
        slot->chunk->vtbl->freeEntities(slot->chunk);
    }
    map->ready = 0;
    map->pendingSlots = 0;
    map->vtbl->resetTileScale(map);
}

void StageMap_SetLights(StageMap *map, s32 count, s32 vectors, s32 colors) {
    s32 i;
    MapChild *child;

    for (i = 0; i < count; i++) {
        child = map->vtbl->getLight(map, i);
        child->vtbl->setColor(child, 1, colors);
        colors += 3;
        child->vtbl->setVector(child, 1, vectors);
        vectors += 6;
    }
}

void StageMap_SetChunkLoader(StageMap *map, void *loader, void *context) {
    map->loadChunk = loader;
    map->loadContext = context;
}

void StageMap_SetMessageFilter(StageMap *map, s32 *filter) {
    map->messageFilter = filter;
}

/* Passes messages 2, 3 and 5 to 8 whose sender's class id is in the filter list to slot 0x12C. */
void StageMap_FilterMessage(StageMap *map, s32 **sender, s32 message) {
    s32 *code;
    s32 unused[6];

    switch (message) {
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
        code = map->messageFilter;
        if ((code != NULL) && (*code != 0)) {
            do {
                if (*code == **sender) {
                    map->vtbl->tellView(map, sender, message);
                }
                code++;
            } while (*code != 0);
        }
        break;
    }
}

/* Tells the tiles around the sender (3 x 3 tiles, or its whole floor on a stacked stage), keeping the view. */
s32 StageMap_TellNearTiles(StageMap *map, MapActor *sender, s32 message) {
    MapViewSave saved[3];
    MapViewSave location[3]; /* a MapLocation, in a 48-byte buffer */
    MapViewSave *src;
    MapViewSave *dst;
    s32 savedCount;
    s32 ret;
    Vec3 *pos;

    if (sender->attached != 0) {
        pos = &sender->coord->workm.t;
    } else {
        pos = NULL;
    }
    ret = map->vtbl->locate(map, location, pos);
    if (ret != 0) {
        return ret;
    }
    savedCount = map->viewCount;
    dst = saved;
    src = map->v.save;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != &map->v.save[3]);
    if (map->grid->stacked == 0) {
        StageMap_SetNearView(map, location, 3);
    } else {
        StageMap_SetNearViewStacked(map, location, 3);
    }
    StageMap_TellViewTiles(map, sender, message);
    map->viewCount = savedCount;
    dst = map->v.save;
    src = saved;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != &saved[3]);
}

/* A size x size view starting one tile before the location's tile; StageMap_SplitView (map still in a0) splits it. */
static void StageMap_SetNearView(StageMap *map, MapLocation *location, s32 size) {
    map->viewX = location->at.place.tileX - 1;
    map->viewY = location->at.place.tileY - 1;
    map->viewCols = size;
    map->viewRows = size;
    StageMap_SplitView();
}

/* The same on a stacked stage: one rectangle, clipped at the chunk edges (tiles 0 and 19). */
static void StageMap_SetNearViewStacked(StageMap *map, MapLocation *location, s32 size) {
    s32 firstX = location->at.place.tileX;
    s32 firstY = location->at.place.tileY;
    s32 rows = size;
    s32 cols = rows;
    s32 x = firstX;
    s32 y = firstY;

    if (x == 0) {
        cols--;
    } else {
        firstX--;
    }
    if (x == 0x13) {
        cols--;
    }
    if (y == 0) {
        rows--;
    } else {
        firstY--;
    }
    if (y == 0x13) {
        rows--;
    }
    map->viewCount = 1;
    map->v.views[0].slot = map->vtbl->slotIndexByChunk(map, location->chunkIndex);
    map->v.views[0].tileX = firstX;
    map->v.views[0].tileY = firstY;
    map->v.views[0].cols = cols;
    map->v.views[0].rows = rows;
}

static void StageMap_TellViewTiles(StageMap *map, MapActor *sender, s32 message) {
    MapView *view;
    MapSlot *slot;
    MapTile **row;
    MapTile *tile;
    s32 i;
    s32 j;
    s32 k;

    view = map->v.views;
    for (i = 0; i < map->viewCount; i++) {
        slot = &map->slots[view->slot];
        if (slot->chunk->loaded != 0) {
            row = slot->tiles + view->tileX + view->tileY * 20;
            for (j = 0; j < view->rows; j++) {
                for (k = 0; k < view->cols; k++) {
                    map->tellKey = map->location.at.chunkKeyU;
                    map->tellX = view->tileX + k;
                    map->tellY = view->tileY + j;
                    MapTile_Tell(*row, sender, message);
                    tile = (*row)->next;
                    while (tile != NULL) {
                        MapTile_Tell(tile, sender, message);
                        tile = tile->next;
                    }
                    row++;
                }
                row += 20 - view->cols;
            }
        }
        view++;
    }
}

static void MapTile_Tell(MapTile *tile, MapActor *sender, s32 message) {
    if ((tile != NULL) && (tile->flags & 0x80)) {
        tile->vtbl->onNotify(tile);
    }
}

/* &map->tellKey */
s32 StageMap_GetTellKey(s32 map) {
    return map + 0x1C0;
}

void StageMap_EmptySlotD8(void) {
}

void StageMap_SetViewDistance(StageMap *map, s32 distance) {
    map->viewDistance = distance;
    map->viewTiles = distance >> 11;
    map->viewHalf = distance >> 12;
}

void StageMap_SetGrid(StageMap *map, StageGrid *grid) {
    map->vtbl->reset(map);
    map->grid = grid;
}

/* Puts the target at a place: its world position into pos, then loads the chunk there and its 6 neighbours. */
void StageMap_SetTarget(StageMap *map, Vec3 *pos, MapActor *target, StagePlace *place) {
    Vec3 chunkCenter;

    map->target = target;
    map->location.at.place = *place;
    map->vtbl->loadAround(map, Stage_PlaceToWorld(pos, &chunkCenter, map->grid, &map->origin, place), &chunkCenter, g_allNeighbors);
}

void StageMap_PlaceToWorld(StageMap *map, Vec3 *pos, StagePlace *place) {
    Vec3 chunkCenter;
    Stage_PlaceToWorld(pos, &chunkCenter, map->grid, &map->origin, place);
}

/*
 * World position of a place: chunk (col, row) from the grid origin, 0xA000 per chunk with odd rows
 * half a chunk to the left, then the tile (0x800) and the offset from the tile centre. Writes the
 * chunk centre and returns the chunk index (0 on a stacked stage).
 */
static s32 Stage_PlaceToWorld(Vec3 *pos, Vec3 *chunkCenter, StageGrid *grid, Vec3 *origin, StagePlace *place) {
    s32 row;
    s32 rows;
    s32 index;
    s32 x;
    s32 z;
    s32 tileX;
    s32 tileZ;
    s32 offsetX;
    s32 offsetZ;

    if (grid->stacked == 0) {
        row = place->row;
        rows = grid->rows;
        index = place->col + grid->cols * row;
    } else {
        rows = 1;
        row = 0;
        index = 0;
    }
    x = (origin->x - grid->cols * 0x5000) + place->col * 0xA000;
    z = origin->z - rows * 0x5000;
    chunkCenter->x = x;
    if (row & 1) {
        chunkCenter->x = x - 0x5000;
    }
    chunkCenter->y = origin->y;
    chunkCenter->z = z + row * 0xA000;
    tileX = (place->tileX << 11) + chunkCenter->x;
    offsetX = place->x + 0x400;
    pos->x = tileX + offsetX;
    pos->y = place->y + chunkCenter->y;
    tileZ = (place->tileY << 11) + chunkCenter->z;
    offsetZ = place->z + 0x400;
    pos->z = tileZ + offsetZ;
    chunkCenter->x += 0x5000;
    chunkCenter->z += 0x5000;
    return index;
}

void StageMap_Activate(StageMap *map) {
    map->active = 1;
}

void StageMap_Deactivate(StageMap *map) {
    map->vtbl->clearSlots(map);
    map->active = 0;
}

/*
 * Each tick while active: locate the target; on a flat stage reload the neighbours of its chunk,
 * redraw the view, keep the location and notify 5 when the chunk changed.
 */
s32 StageMap_Follow(StageMap *map) {
    MapLocation location;
    s16 prevKey;
    s32 layout;

    if (map->vtbl->getLocation(map, &location, 0) == 0) {
        return 0;
    }
    layout = g_neighborLayoutById[location.slot->chunk->id];
    if (map->grid->stacked == 0) {
        map->vtbl->loadAround(map, location.chunkIndex, &location.chunkCenter, g_neighborLoadLists[layout]);
    }
    map->vtbl->updateView(map);
    prevKey = map->location.at.chunkKey;
    map->location = location;
    if (prevKey != location.at.chunkKey) {
        map->vtbl->notify(map, 5);
    }
    return layout;
}

/* Places the 7 slots around a chunk (or the floors of a stacked stage) and asks the loader for their data. */
void StageMap_LoadAround(StageMap *map, s32 chunkIndex, Vec3 *center, NeighborUse *use) {
    ChunkRequest requests[7];
    s32 mask;
    s32 cols;
    s32 oddRow;
    s32 i;
    s32 count;
    MapSlot *slot;
    Coord2 *coord;
    Vec3 *offset;

    if (use != NULL) {
        cols = map->grid->cols;
        count = 0;
        oddRow = (chunkIndex / cols) & 1;
        mask = StageMap_GetNeighborMask(map, chunkIndex, oddRow);
        for (i = 0; i < 7; i++, use++) {
            slot = map->vtbl->slotById(map, i);
            slot->index = use->neighbor;
            if (use->enabled != 0) {
                offset = &g_chunkNeighborOffsets[use->neighbor];
                coord = slot->root->coord;
                if (map->grid->stacked == 0) {
                    coord->coord.t.x = center->x + offset->x;
                    coord->coord.t.y = center->y;
                    coord->coord.t.z = center->z + offset->z;
                } else {
                    coord->coord.t.x = center->x - 0x5000;
                    coord->coord.t.y = center->y + offset->y;
                    coord->coord.t.z = center->z - 0x5000;
                }
                slot->root->coord->flg = 0;
                StageMap_RequestNeighbor(map, &requests[count], cols, oddRow, chunkIndex, mask, use->neighbor);
                count++;
            }
        }
        for (i = 0; i < 7; i++) {
            slot = &map->slots[i];
            slot->chunk->id = slot->index;
        }
        map->vtbl->assignChunks(map, requests, count);
    }
}

/* Bit i set when neighbour i of the chunk lies inside the grid; a stacked stage sets one bit per floor. */
static s32 StageMap_GetNeighborMask(StageMap *map, s32 chunkIndex, s32 oddRow) {
    StageGrid *grid;
    s32 cols;
    s32 rows;
    s32 outside;
    s32 i;

    grid = map->grid;
    cols = grid->cols;
    rows = grid->rows;
    if (grid->stacked == 0) {
        outside = -(chunkIndex < cols) & 3;
        if (chunkIndex >= cols * (rows - 1)) {
            outside |= 0x60;
        }
        if (chunkIndex % cols == 0) {
            if (oddRow != 0) {
                outside |= 0x25;
            } else {
                outside |= 4;
            }
        }
        if ((chunkIndex + 1) % cols == 0) {
            if (oddRow != 0) {
                outside |= 0x10;
            } else {
                outside |= 0x52;
            }
        }
    } else {
        outside = -1;
        for (i = 0; i < rows; i++) {
            outside *= 2;
        }
    }
    return ~outside;
}

static s32 StageMap_RequestNeighbor(StageMap *map, ChunkRequest *request, s32 cols, s32 oddRow, s32 chunkIndex, s32 mask, s32 neighbor) {
    HexNeighbor *step;
    s32 delta;

    if (mask & g_neighborBits[neighbor]) {
        if (map->grid->stacked != 0) {
            request->chunkIndex = chunkIndex + neighbor;
        } else {
            step = &g_chunkNeighborSteps[neighbor];
            if (step->rowStep == 0) {
                delta = step->colStepOdd;
                request->chunkIndex = chunkIndex + delta;
            } else {
                delta = cols * step->rowStep;
                if (oddRow != 0) {
                    delta += step->colStepOdd;
                } else {
                    delta += step->colStepEven;
                }
                request->chunkIndex = chunkIndex + delta;
            }
        }
        request->data = map->loadChunk(map->loadContext, request->chunkIndex, 0, 0);
        request->neighbor = neighbor;
        return 1;
    }
    request->data = 0;
    request->neighbor = neighbor;
    return 0;
}

void StageMap_AssignChunks(StageMap *map, ChunkRequest *request, s32 count) {
    s32 i;
    MapSlot *slot;

    for (i = 0; i < count; request++, i++) {
        slot = map->vtbl->slotById(map, request->neighbor);
        map->vtbl->onSlotMessage(map, 6, slot, i);
        if (request->data != 0) {
            if (slot->chunk->loaded != 0) {
                map->vtbl->hideSlot(map, slot);
            }
            slot->chunk->index = request->chunkIndex;
            slot->chunk->vtbl->load(slot->chunk, request->data);
            slot->loading = 1;
            map->swapping = 1;
        } else {
            if (slot->chunk->loaded != 0) {
                map->vtbl->hideSlot(map, slot);
            }
            if (slot->chunk->state != 0) {
                slot->chunk->vtbl->unload(slot->chunk);
                slot->loading = 0;
            }
        }
    }
    map->pendingSlots = StageMap_CountLoading(map);
}

static s32 StageMap_CountLoading(StageMap *map) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (map->slots[i].loading != 0) {
            count++;
        }
    }
    return count;
}

/* On update (message 2): a slot whose chunk data arrived gets its tiles; when none is left the map is ready. */
void StageMap_PollLoads(StageMap *map, s32 sender, s32 message) {
    MapSlot *slot;
    MapChunk *chunk;
    s32 i;
    s32 swapping;
    u16 pending;

    if (message == 2) {
        for (i = 0; i < 7; i++) {
            slot = &map->slots[i];
            chunk = slot->chunk;
            if (chunk->entitiesLoaded != 0) {
                chunk->entitiesLoaded = 0;
                map->vtbl->onSlotMessage(map, 7, slot, i);
            }
            swapping = map->swapping;
            if (swapping == 1 && slot->loading != 0) {
                chunk = slot->chunk;
                if (chunk->loaded != 0) {
                    map->vtbl->buildTiles(map, slot);
                    slot->chunk->loaded = 2;
                    slot->loading = 0;
                    pending = map->pendingSlots - 1;
                    map->pendingSlots = pending;
                    if (pending == 0) {
                        map->pendingSlots = 0;
                        map->swapping = 0;
                        map->ready = swapping;
                    }
                } else if (chunk->state == 0) {
                    slot->loading = 0;
                }
            }
        }
    }
}

/*
 * Builds a slot's tiles from its chunk data: the TMD after the model list, then one model per
 * square from the model set, linked into the square's GsDOBJ2 (GsLinkObject4); extra models go
 * from index 400 on and chain behind the square's tile.
 */
void StageMap_BuildTiles(StageMap *map, MapSlot *slot) {
    MapModelRecord record;
    void *tmdFile[4];
    MapChunk *chunk;
    MapChunkData *data;
    MapModels *models;
    MapTile **tile;
    Coord2Param *param;
    void *model;
    s32 i;
    s32 j;
    s32 modelsSize;
    MapTile **tiles;

    chunk = slot->chunk;
    models = slot->models;
    models->data = (u8 *)chunk->data + chunk->data->modelsOffset;
    models->size = 0;
    if (models->tmd != NULL) {
        models->tmd->vtbl->delete_(models->tmd);
    }
    data = chunk->data;
    modelsSize = data->modelsSize;
    tmdFile[0] = (u8 *)data + data->modelsOffset + modelsSize;
    models->tmd = (Object *)Tmd_Create((s32)tmdFile);
    record.chained = 0;
    i = 0;
    j = 400;
    for (;;) {
        model = models->vtbl->nextModel(models, &record, i);
        if (model == NULL) {
            break;
        }
        if (model == (void *)-1) {
            tile = &slot->tiles[i];
            (*tile)->attribute |= MAP_TILE_HIDDEN;
            (*tile)->model = NULL;
            (*tile)->tmd = 0;
        } else {
            tiles = slot->tiles;
            if (record.extra != 0) {
                tile = &tiles[j++];
            } else {
                tile = &tiles[i];
            }
            (*tile)->model = model;
            (*tile)->tmd = (*tile)->model->tmd;
            GsLinkObject4((*tile)->model->tmd, &(*tile)->attribute, 0);
            (*tile)->coord->coord.t = record.pos;
            param = (*tile)->coord->param;
            param->rotate.axis[0] = 0;
            param->rotate.axis[1] = record.rotY;
            param->rotate.axis[2] = 0;
            (*tile)->flags = record.flags;
            (*tile)->coord->flg = 0;
            (*tile)->attribute |= MAP_TILE_HIDDEN;
        }
        if (record.chained != 0) {
            (*tile)->next = slot->tiles[j];
        } else {
            i++;
            (*tile)->next = NULL;
        }
    }
}

void StageMap_HideSlot(StageMap *map, MapSlot *slot) {
    MapTile **p;
    MapTile **end;

    if (slot->chunk->index >= 0) {
        slot->chunk->vtbl->clear(slot->chunk);
        end = slot->tiles + MAP_SLOT_TILES;
        for (p = slot->tiles; p < end; p++) {
            (*p)->attribute = (*p)->attribute | MAP_TILE_HIDDEN;
            (*p)->model = 0;
            (*p)->tmd = 0;
        }
    }
}

/* The kept location; with out, first locates the target into out and returns NULL when that fails. */
void *StageMap_GetLocation(StageMap *map, MapLocation *out, s32 **outPos) {
    s32 *pos = &map->target->coord->coord.t.x;

    if (outPos != NULL) {
        *outPos = pos;
    }
    if (out == NULL || map->vtbl->locate(map, out, pos) == 0) {
        return &map->location;
    }
    return NULL;
}

/* Where a world position falls: slot, chunk, tile and offsets. Returns 1 when no slot holds it. */
s32 StageMap_Locate(StageMap *map, MapLocation *out, s32 *pos) {
    MapSlot *slot;
    MapSlot *idSlot;
    Coord2 *coord;
    Coord2 *slotCoord;
    s16 chunkIndex;
    s32 x;
    s32 z;
    slot = map->vtbl->slotAt(map, pos);
    if (slot != NULL) {
        chunkIndex = slot->chunk->index;
        out->chunkIndex = chunkIndex;
        StageMap_ChunkColRow(map, &out->at.place, chunkIndex);
        idSlot = map->vtbl->slotById(map, slot->chunk->id);
        coord = idSlot->root->coord;
        out->chunkCenter.x = coord->coord.t.x + 0x5000;
        out->chunkCenter.y = coord->coord.t.y;
        out->chunkCenter.z = coord->coord.t.z + 0x5000;
        slotCoord = slot->root->coord;
        out->offset.x = pos[0] - out->chunkCenter.x;
        out->offset.y = pos[1];
        out->offset.z = pos[2] - out->chunkCenter.z;
        out->at.place.tileX = (pos[0] - slotCoord->coord.t.x) / 2048;
        out->at.place.tileY = (pos[2] - slotCoord->coord.t.z) / 2048;
        x = (u16)pos[0] - 0x400;
        out->at.place.x = x - ((u16)slotCoord->coord.t.x + out->at.place.tileX * 2048);
        out->at.place.y = (u16)pos[1];
        z = (u16)pos[2] - 0x400;
        out->at.place.z = z - ((u16)slotCoord->coord.t.z + out->at.place.tileY * 2048);
        out->slot = slot;
        return 0;
    }
    return 1;
}

static void StageMap_ChunkColRow(StageMap *map, StagePlace *place, s32 chunkIndex) {
    place->col = chunkIndex % map->grid->cols;
    place->row = chunkIndex / map->grid->cols;
}

MapSlot *StageMap_GetCurrentSlot(StageMap *map, StagePlace *place) {
    StageMap_ChunkColRow(map, place, map->currentSlot->chunk->index);
    return map->currentSlot;
}

MapSlot *StageMap_SlotById(StageMap *map, s32 id) {
    s32 i;
    MapSlot *slot;
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        if (slot->chunk->id == id) {
            return slot;
        }
    }
}

/* The slot whose chunk square holds the position; on a stacked stage slot i is the floor from -0x800 * i up. */
MapSlot *StageMap_SlotAt(StageMap *map, s32 *pos) {
    s32 i;

    for (i = 0; i < 7; i++) {
        MapSlot *slot = map->vtbl->slotById(map, i);
        Coord2 *coord = slot->root->coord;
        if (pos[0] >= coord->coord.t.x && pos[0] < coord->coord.t.x + 0xA000 && pos[2] >= coord->coord.t.z && pos[2] < coord->coord.t.z + 0xA000) {
            if (map->grid->stacked == 0) {
                return slot;
            }
            if (i * -0x800 < pos[1]) {
                continue;
            }
            if (i * -0x800 - 0x800 < pos[1]) {
                return slot;
            }
        }
    }
    return NULL;
}

s32 StageMap_SlotIndexById(StageMap *map, s32 id) {
    s32 found = 0;
    s32 i;
    MapSlot *slot;
    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        if (slot->chunk->id == id) {
            found = i;
            break;
        }
    }
    return found;
}

s32 StageMap_SlotIndexByChunk(StageMap *map, s32 chunkIndex) {
    s32 i;
    MapSlot *slot;

    for (i = 0; i < 7; i++) {
        slot = &map->slots[i];
        if (slot->chunk->index == chunkIndex && slot->chunk->loaded != 0) {
            return i;
        }
    }
    return -1;
}

/* Hides the old view's tiles, computes the new view and shows its tiles, once the chunks are loaded. */
void StageMap_UpdateView(StageMap *map) {
    s32 width;

    if (map->ready != 0) {
        width = map->viewHalf * 2;
        StageMap_ShowView(map, 0);
        if (map->grid->stacked == 0) {
            StageMap_ComputeFlatView(map, width, map->viewTiles);
        } else {
            StageMap_ComputeStackedView(map);
        }
        StageMap_ShowView(map, 1);
    }
}

/*
 * The view of a flat stage: a rectangle of width x depth tiles in front of the target, oriented by
 * its yaw (param rotate[1]) to the nearest axis, shifted toward the point viewDistance ahead.
 */
static void StageMap_ComputeFlatView(StageMap *map, s32 width, s32 depth) {
    s8 location[0x30];
    Matrix mat;
    Coord2Param *param;
    s16 *rot;
    u16 angle;
    s32 x;
    s32 y;
    s32 d;
    s32 alongX;

    param = map->target->coord->param;
    rot = param->rotate.axis;
    map->vtbl->getLocation(map, location, 0);
    x = location[2];
    y = location[3];
    angle = param->rotate.axis[1];
    if (param->rotate.axis[1] < 0) {
        angle += 0x1000;
    }
    mat = GsIDMATRIX;
    mat.t.x = 0;
    mat.t.y = 0;
    mat.t.z = map->viewDistance;
    RotMatrix(rot, &mat);
    ApplyMatrixLV((s32 *)&mat, &mat.t, &mat.t);

    if ((angle >= 0x200 && angle < 0x600) || (angle >= 0xA00 && angle < 0xE00)) {
        d = mat.t.z;
        map->viewCols = depth;
        map->viewRows = width;
        map->viewX = (mat.t.x > 0) ? x : x - width + 1;
        map->viewY = (mat.t.z > 0) ? y - (u16)map->viewHalf - 1 : y - (u16)map->viewHalf + 1;
        alongX = 0;
    } else if ((angle >= 0x600 && angle < 0xA00) || (angle < 0x200 || angle >= 0xE00)) {
        d = mat.t.x;
        map->viewCols = width;
        map->viewRows = depth;
        map->viewX = (mat.t.x > 0) ? x - (u16)map->viewHalf - 1 : x - (u16)map->viewHalf + 1;
        map->viewY = (mat.t.z > 0) ? y : y - depth + 1;
        alongX = 1;
    }
    d = d >> 11;
    if (d >= map->viewHalf) {
        d = map->viewHalf - 1;
    }
    if (-map->viewHalf >= d) {
        d = -map->viewHalf + 1;
    }
    if (alongX != 0) {
        map->viewX += d;
    } else {
        map->viewY += d;
    }
    StageMap_SplitView(map);
}

/*
 * Splits the view rectangle over the chunks it covers: a negative first tile starts in a neighbour
 * (10 tiles across on the half-shifted rows), a rectangle past tile 20 continues in the next one.
 * x is reused for the rectangle count.
 */
static void StageMap_SplitView(StageMap *map) {
    s32 endX;
    s32 x;
    s32 neighbor;
    s32 y;
    s32 cols;
    s32 rows;
    s32 wrapped;
    s32 slot;
    s32 over;
    MapView *view;

    wrapped = 0;
    x = map->viewX;
    cols = map->viewCols;
    rows = map->viewRows;
    neighbor = 3;
    if (x < 0) {
        x += 20;
        wrapped = 1;
        neighbor = 2;
    }
    y = map->viewY;
    view = map->v.views;
    if (y < 0) {
        y += 20;
        if (wrapped != 0) {
            x -= 10;
            neighbor = 0;
        } else {
            neighbor = 0;
            if (x < 10) {
                x += 10;
            } else {
                x -= 10;
                neighbor = 1;
            }
            view = map->v.views;
        }
    }

    slot = map->vtbl->slotIndexById(map, neighbor);
    map->v.views[0].slot = slot;
    map->v.views[0].tileX = x < 0 ? 0 : x;
    map->v.views[0].tileY = y;
    endX = x + cols;
    if (endX >= 21) {
        over = endX - 20;
        map->v.views[0].cols = cols - over;
        endX = over;
        x = StageMap_SplitViewRows(map, view, 0, neighbor, x, y, cols, rows) + 1;
        view = &map->v.views[x];
        view->slot = map->vtbl->slotIndexById(map, neighbor + 1);
        view->tileX = 0;
        view->tileY = (u16)map->v.views[0].tileY;
        view->cols = endX;
        view->rows = (u16)map->v.views[0].rows;
    } else {
        map->v.views[0].cols = cols;
        x = StageMap_SplitViewRows(map, view, 0, neighbor, x, y, cols, rows);
    }
    x += 1;
    map->viewCount = x;
}

/* Splits rectangle index of the view at the bottom edge of its chunk; returns the last index written. */
static s32 StageMap_SplitViewRows(StageMap *map, MapView *view, s32 index, s32 neighbor, s32 x, s32 y, s32 cols, s32 rows) {
    s32 over;
    s32 id;
    s32 endX;

    if (y + rows > 20) {
        over = y + rows - 20;
        view->rows = rows - over;
        index++;
        view = &map->v.views[index];
        if (x < 10) {
            id = neighbor + 2;
            view->slot = map->vtbl->slotIndexById(map, id);
            view->tileX = x + 10;
            view->rows = over;
        } else {
            id = neighbor + 3;
            view->slot = map->vtbl->slotIndexById(map, id);
            view->tileX = x - 10;
            view->rows = over;
        }
        endX = view->tileX + cols;
        view->tileY = 0;
        if (endX > 20) {
            view->cols = cols - (endX - 20);
            index++;
            view = &map->v.views[index];
            view->slot = map->vtbl->slotIndexById(map, id + 1);
            view->tileX = 0;
            view->tileY = 0;
            view->cols = endX - 20;
            view->rows = over;
        } else {
            view->cols = cols;
        }
    } else {
        view->rows = rows;
    }
    return index;
}

/* The view of a stacked stage: the target's whole floor, the one above when inside the bounds box, and the one below. */
static void StageMap_ComputeStackedView(StageMap *map) {
    MapLocation location;
    s32 unset;

    map->vtbl->getLocation(map, &location, 0);
    map->viewCount = 0;
    map->viewCount = StageMap_AddChunkView(map, unset, 0, location.chunkIndex);
    if (StageMap_IsOutsideBounds(map->bounds, &location.at.place.tileX) != 0) {
        if (location.chunkIndex + 1 < map->grid->rows) {
            map->viewCount = StageMap_AddChunkView(map, unset, map->viewCount, location.chunkIndex + 1);
        }
    }
    if (location.chunkIndex - 1 >= 0) {
        map->viewCount = StageMap_AddChunkView(map, unset, map->viewCount, location.chunkIndex - 1);
    }
}

/* Returns 0 when the tile (tile[0], tile[1]) lies inside the box, 1 otherwise or without a box. */
static s32 StageMap_IsOutsideBounds(void *box, void *tile) {
    MapBox *b = box;
    u8 *pt = tile;

    if (b != NULL && (s8)pt[0] >= b->x0 && (s8)pt[0] <= b->x1
        && (s8)pt[1] >= b->y0 && (s8)pt[1] <= b->y1) {
        return 0;
    }
    return 1;
}

/* Adds a whole-chunk rectangle (g_wholeChunkView: 20 x 20 tiles) for a chunk index; returns the next index. */
static s32 StageMap_AddChunkView(StageMap *map, s32 unused, s32 index, s32 chunkIndex) {
    MapView *view = &map->v.views[index];

    *view = g_wholeChunkView;
    view->slot = map->vtbl->slotIndexByChunk(map, chunkIndex);
    return index + 1;
}

/* Shows (show != 0) or hides the tiles of the view rectangles; rows[-3] is tileX, rows[-2] tileY, rows[-1] cols. */
static void StageMap_ShowView(StageMap *map, s32 show) {
    MapView *view;
    s16 *rows;
    MapSlot *slot;
    s32 i;
    s32 row;
    s32 col;
    MapTile **p;
    MapTile *tile;
    MapTile *next;
    s32 attribute;

    view = (MapView *)((u8 *)map + 0x8C);
    for (i = 0; i < map->viewCount; i++) {
        slot = &map->slots[view->slot];
        rows = &view->rows;
        if (slot->chunk->loaded != 0) {
            p = slot->tiles + rows[-3] + rows[-2] * 20;
            for (row = 0; row < rows[0]; row++) {
                for (col = 0; col < rows[-1]; col++) {
                    if (show != 0) {
                        tile = *p;
                        attribute = tile->attribute & 0x7FFFFFFF;
                    } else {
                        tile = *p;
                        attribute = tile->attribute | MAP_TILE_HIDDEN;
                    }
                    tile->attribute = attribute;
                    next = (*p)->next;
                    while (next != NULL) {
                        if (show != 0) {
                            attribute = next->attribute & 0x7FFFFFFF;
                        } else {
                            attribute = next->attribute | MAP_TILE_HIDDEN;
                        }
                        next->attribute = attribute;
                        next = next->next;
                    }
                    p++;
                }
                p += 20 - rows[-1];
            }
        }
        view++;
    }
}

/* &map->unk1CC */
s32 func_8004CFA8(s32 map) {
    return map + 0x1CC;
}

void StageMap_SetBounds(StageMap *map, void *bounds) {
    map->bounds = bounds;
}

/* Picks the tile step record by sign and fast; +0x1E0 = its ticks x |count|. */
void StageMap_StartTileStretch(StageMap *map, s32 count, s32 fast) {
    MapTileStep *step;
    if (count > 0) {
        step = &g_tileStretchSlowUp;
        if (fast != 0) {
            map->stretchStep = &g_tileStretchFastUp;
        } else {
            map->stretchStep = step;
        }
    } else {
        step = &g_tileStretchSlowDown;
        if (fast != 0) {
            step = &g_tileStretchFastDown;
        }
        map->stretchStep = step;
    }
    map->stretchTicks = map->stretchStep->ticks * (count < 0 ? ~count + 1 : count);
}

void StageMap_StepTileStretch(StageMap *map) {
    if (map->stretchTicks > 0) {
        StageMap_ForEachTile(map, StageMap_AddTileStretchStep, 0);
        if (--map->stretchTicks == 0) {
            map->stretchTicks = -1;
        }
    }
}

void StageMap_ResetTileScale(StageMap *map) {
    if (map->stretchTicks != 0) {
        StageMap_ForEachTile(map, StageMap_ResetOneTileScale, 0);
        map->stretchTicks = 0;
    }
}

static void StageMap_AddTileStretchStep(StageMap *map, MapTile *tile) {
    tile->vtbl->setScale(tile, 0, map->stretchStep);
}

static void StageMap_ResetOneTileScale(s32 map, MapTile *tile) {
    tile->vtbl->setScale(tile, 1, &g_tileScaleOne);
}

/* Calls perTile(map, tile) on the tiles of the 7 slots, after perSlot(map, slot) when given. */
static void StageMap_ForEachTile(StageMap *map, void (*perTile)(), void (*perSlot)(void *, void *)) {
    s32 i;
    u8 *slot;

    for (i = 0; i < 7; i++) {
        slot = (u8 *)map + 0xEC + i * 0x1C;
        if (perSlot != NULL) {
            perSlot(map, slot);
        }
        StageMap_ForEachSlotTile(map, perTile, slot);
    }
}

static void StageMap_ForEachSlotTile(StageMap *map, void (*perTile)(), MapSlot *slot) {
    MapTile **p;
    MapTile **end;

    end = slot->tiles + 0x19A;
    for (p = slot->tiles; p < end; p++) {
        perTile(map, *p);
    }
}

static StageMapVtbl *StageMap_GetVtbl(void) {
    return (StageMapVtbl *)g_stageMapVtbl;
}

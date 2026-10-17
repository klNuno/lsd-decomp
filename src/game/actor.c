#include "common.h"
#include "game/actor.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/model_object.h"
#include "game/stage.h"
#include "game/stage_map.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/*
 * The contact search of Actor_SnapToGround over the map's grid: 20 x 20 tiles per slot
 * (MapSlot.tiles), each a chain of tiles (MapTile.next); a rect gives the slot's tiles to walk.
 */
typedef struct GridRect {
    s16 left;
    s16 top;
    s32 width;
    s32 height;
} GridRect;

static void Actor_ApplyPos(void *self, s32 set, Vec3 *vec);
extern s16 g_actorMoveVecZ[];
void Actor_MoveAxis(void *self, s16 *field, s32 value, s32 notify, s32 message);
extern s16 g_actorMoveVec[];
s32 Actor_SnapToGround();
static MapTile *Actor_FindGroundInCells(Actor *actor, s32 *delta, u8 *pos, s32 count, GridRect *rects, MapSlot **cells);
static MapTile *Actor_FindGroundInRect(Actor *actor, s32 *delta, u8 *pos, GridRect *r, MapSlot *cell);
static s32 Actor_GetGroundRects(Actor *actor, GridRect *rects, MapSlot **cells, MapLocation *in, s32 size);
static MapTile *Actor_ProbeGroundAt();
extern ActorVtbl g_actorVtbl;
static void Actor_MoveThenSnap(Actor *actor, void (*move)(void *, s32, s32), s32 value, s32 notify);

/* Allocate a kind 0 part: an object of the base class g_actorVtbl (0x58 bytes). */
void *Actor_New(void) {
    void *part;

    part = Heap_Alloc(0x58);
    if (part == 0) {
        return 0;
    }
    if (Actor_GetVtbl()->init(part) != 0) {
        return part;
    }
    Heap_Free(part);
    return 0;
}

/* Slot 0x08 of the base class g_actorVtbl */
void *Actor_Init(Actor *actor) {
    if (SceneNode_GetVtbl()->init(actor) != 0) {
        actor->vtbl = Actor_GetVtbl();
        actor->state = 0;
        actor->map = 0;
        actor->clock = 0;
        actor->vtbl->reset(actor);
        return actor;
    }
    return 0;
}

/* Slot 0x10, watch: keep a map (class id ending in 0x114) at +0x4C, a class id ending in 5 at +0x50. */
void Actor_Watch(Actor *actor, s32 **other) {
    s32 classId;

    SceneNode_GetVtbl()->watch(actor, other);
    classId = **other;
    if ((classId & 0xFFF) == 0x114) {
        actor->map = (StageMap *)other;
        return;
    }
    if ((classId & 0xF) == 5) {
        actor->clock = other;
    }
}

/* Slot 0x14, unwatch */
void Actor_Unwatch(Actor *actor, s32 **other) {
    s32 classId;

    classId = **other;
    if ((classId & 0xFFF) == 0x114) {
        actor->map = 0;
    } else if ((classId & 0xF) == 5) {
        actor->clock = 0;
    }
    SceneNode_GetVtbl()->unwatch(actor, other);
}

/* Slot 0x18, unwatch all */
void Actor_UnwatchAll(Actor *actor) {
    actor->map = 0;
    actor->clock = 0;
    SceneNode_GetVtbl()->unwatchAll(actor);
}

/* Slot 0x40 */
void Actor_Reset(Actor *actor) {
    actor->speed = 0x12C;
    actor->boxMargin = 0;
}

/* Slot 0x88: messages 5 to 8 while the actor's model has boxes (ModelObject_GetBoxCount). */
void Actor_SendBoxes(Actor *actor, s32 message) {
    union {
        NodeBoxList node;
        ModelBoxList shift;
    } buf;
    Actor *contact;

    SceneNode_GetVtbl()->sendBoxes(actor, message);
    if (message < 9) {
        if (message >= 5) {
            if ((actor->model != 0) && (ModelObject_GetBoxCount(actor->model) != 0)) {
                actor->vtbl->getBoxList(actor, &buf.node);
                if (message != 5) {
                    ModelBox_ShiftList(&buf.shift, message == 7, actor->speed >= 0,
                                  actor->speed >= 0 ? actor->speed + actor->boxMargin : actor->speed - actor->boxMargin);
                }
                actor->vtbl->sendShape(actor, &buf.node, message);
                contact = actor->contact;
                if (contact != NULL) {
                    if (contact->vtbl->classByte == 0x34) {
                        contact->vtbl->afterTouch(contact, contact->vtbl);
                    }
                }
            }
        }
    }
}

/* Slot 0x9C: the class byte of the sender's vtable picks the slot, 0x34 (an Actor) slot 0xDC, 0x24 (a MapTile)
   slot 0xE0 (both called without arguments, the registers still hold them). */
void Actor_OnNode(Actor *actor, u8 **sender) {
    u8 c = **sender;

    if (c == 0x34) {
        actor->vtbl->onActorContact();
    } else if (c == 0x24) {
        actor->vtbl->onTileContact();
    }
}

/* Slot 0xB8: set the position. */
void Actor_SetPos(void *actor, Vec3 *pos) {
    Actor_ApplyPos(actor, 1, pos);
}

/* Slot 0xBC: move by a vector. */
void Actor_MovePos(void *actor, Vec3 *delta) {
    Actor_ApplyPos(actor, 0, delta);
}

static void Actor_ApplyPos(void *self, s32 set, Vec3 *vec) {
    Actor *actor = self;
    Coord2 *block = actor->object.coord;
    if (set != 0) {
        block->coord.t = *vec;
    } else {
        block->coord.t.x += vec->x;
        block->coord.t.y += vec->y;
        block->coord.t.z += vec->z;
    }
    actor->object.coord->flg = 0;
}

/* Slot 0xC0 */
void Actor_MoveLocal(Actor *actor, ModelVec *local) {
    Vec3 delta;

    SceneNode_RotateVector((SceneNode *)actor, &delta, local);
    actor->vtbl->movePos(actor, &delta);
}

/* Slots 0xC4 to 0xCC: one of the three s16 of g_actorMoveVec/g_actorMoveVecZ set for slot 0xC0, then message 6, 7 or 8. */
void Actor_MoveZ(void *actor, s32 value, s32 notify) {
    Actor_MoveAxis(actor, g_actorMoveVecZ, value, notify, 6);
}

void Actor_MoveX(void *actor, s32 value, s32 notify) {
    Actor_MoveAxis(actor, g_actorMoveVec, value, notify, 7);
}

void Actor_MoveY(void *actor, s32 value, s32 notify) {
    Actor_MoveAxis(actor, g_actorMoveVec + 1, value, notify, 8);
}

void Actor_MoveAxis(void *self, s16 *field, s32 value, s32 notify, s32 message) {
    Actor *actor = self;

    actor->speed = *field = value;
    actor->vtbl->moveLocal(actor, g_actorMoveVec);
    *field = 0;
    if (notify != 0) {
        actor->vtbl->sendBoxes(actor, message);
    }
}

/* Slot 0xD0 */
void Actor_MoveZOnGround(Actor *actor, s32 value, s32 notify) {
    Actor_MoveThenSnap(actor, actor->vtbl->moveZ, value, notify);
}

/* Slot 0xD4 */
void Actor_MoveXOnGround(Actor *actor, s32 value, s32 notify) {
    Actor_MoveThenSnap(actor, actor->vtbl->moveX, value, notify);
}

void Actor_EmptySlotD8(void) {
}

/* Run a move, then look for a contact when the move found none. */
static void Actor_MoveThenSnap(Actor *actor, void (*move)(void *, s32, s32), s32 value, s32 notify) {
    actor->contact = 0;
    move(actor, value, notify);
    if (actor->contact == 0) {
        Actor_SnapToGround(actor);
    }
}

/* Look for an object in the map cells around the actor's position (+0x14 block, +0x18). */
s32 Actor_SnapToGround(Actor *actor) {
    MapLocation cell;
    GridRect rects[4];
    MapSlot *cells[4];
    s32 delta[4];
    u8 *pos;
    s32 count;
    MapTile *found;

    if (actor->map != NULL) {
        pos = (u8 *)actor->object.coord + 0x18;
        if (actor->map->vtbl->locate(actor->map, &cell, pos) == 0) {
            count = Actor_GetGroundRects(actor, rects, cells, &cell, 1);
            found = Actor_FindGroundInCells(actor, delta, pos, count, rects, cells);
            actor->contact = found;
            if (found != 0) {
                actor->vtbl->movePos(actor, delta);
                actor->vtbl->sendBoxes(actor, -1);
                return 1;
            }
            actor->vtbl->sendBoxes(actor, -2);
        }
    }
    return 0;
}

/* The rectangles of cells to search: the cell itself and the slots above and below it (n == 1), else the n x n square clipped to the 20 x 20 grid. */
static s32 Actor_GetGroundRects(Actor *actor, GridRect *rects, MapSlot **cells, MapLocation *in, s32 size) {
    s32 n = size;
    s32 x = in->at.place.tileX;
    s32 y = in->at.place.tileY;
    s32 left, top, w, h, count;

    if (!(n & 1)) {
        h = ++n;
    } else {
        h = n;
    }
    w = h;
    left = x;
    count = 1;
    top = y;
    if (n == 1) {
        StageMap *map;
        MapSlot *slot;
        StageGrid *grid;
        s16 idx;

        rects[0].left = left;
        rects[0].top = top;
        rects[0].width = w;
        rects[0].height = h;
        slot = in->slot;
        cells[0] = slot;
        map = actor->map;
        grid = map->grid;
        if (grid->stacked != 1) {
            return 1;
        }
        idx = slot->chunk->id;
        if (idx + 1 < grid->rows) {
            cells[1] = map->vtbl->slotById(map, idx + 1);
            count = 2;
            rects[1] = rects[0];
        }
        if (idx - 1 >= 0) {
            cells[count] = map->vtbl->slotById(map, idx - 1);
            rects[count] = rects[0];
            count++;
        }
        return count;
    }
    if (x == 0) {
        w--;
    } else {
        left--;
    }
    if (x == 0x13) {
        w--;
    }
    if (y == 0x13) {
        h--;
    } else {
        top++;
    }
    rects[0].left = left;
    if (y == 0) {
        h--;
    }
    rects[0].top = top;
    rects[0].width = w;
    rects[0].height = h;
    cells[0] = in->slot;
    return 1;
}

static MapTile *Actor_FindGroundInCells(Actor *actor, s32 *delta, u8 *pos, s32 count, GridRect *rects, MapSlot **cells) {
    MapTile *found;
    MapSlot *cell;
    s32 i;

    i = 0;
    while (i < count) {
        cell = *cells;
        i += 1;
        if (cell->chunk->loaded != 0) {
            found = Actor_FindGroundInRect(actor, delta, pos, rects, cell);
            if (found != 0) {
                return found;
            }
        }
        rects += 1;
        cells += 1;
    }
    return 0;
}

/* Walk a rectangle of a cell's 20-wide tile grid (MapSlot.tiles) and each tile's chain (MapTile.next). */
static MapTile *Actor_FindGroundInRect(Actor *actor, s32 *delta, u8 *pos, GridRect *r, MapSlot *cell) {
    MapTile *entry;
    s32 col;
    s32 row;
    MapTile **slot;

    slot = cell->tiles + r->top * 20 + r->left;
    for (row = 0; row < r->height; row++) {
        for (col = 0; col < r->width; col++) {
            if (Actor_ProbeGroundAt(*slot, delta, pos) != 0) {
                return *slot;
            }
            entry = (*slot)->next;
            if (entry != 0) {
                do {
                    if (Actor_ProbeGroundAt(entry, delta, pos) != 0) {
                        return entry;
                    }
                    entry = entry->next;
                } while (entry != 0);
            }
            slot += 1;
        }
        slot -= r->width + 0x14;
    }
    return 0;
}

static MapTile *Actor_ProbeGroundAt(MapTile *entry) {
    if (entry != 0 && SceneNode_ProbeHeight() != 0) {
        return entry;
    }
    return 0;
}

/* Slot 0xDC: the base slot 0x9C, then slot 0xA0 for messages 5 to 8. */
void Actor_OnActorContact(Actor *actor, void *sender, s32 message) {
    SceneNode_GetVtbl()->onNode(actor, sender, message);
    if (message < 9) {
        if (message >= 5) {
            actor->vtbl->checkContact(actor, sender, message);
        }
    }
}

/* Slot 0xE0 */
void Actor_OnTileContact(Actor *actor, void *sender, s32 message) {
    SceneNode_GetVtbl()->onNode(actor, sender, message);
}

/* Slot 0xE4 */
void Actor_SetSpeed(Actor *actor, s16 value) {
    actor->speed = value;
}

void Actor_EmptySlotE8(void) {
}

/* Slot 0xEC */
void Actor_SetBoxMargin(Actor *actor, s32 value) {
    actor->boxMargin = value;
}

ActorVtbl *Actor_GetVtbl(void) {
    return &g_actorVtbl;
}

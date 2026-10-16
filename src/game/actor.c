#include "common.h"
#include "game/dreamsys.h"
#include "game/place.h"
#include "game/actor.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/model_object.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/*
 * The base class of the scenery objects and their kind 0 parts: vtable g_actorVtbl (Actor_GetVtbl),
 * constructor Actor_Construct, 0x58 bytes. The scenery vtable and DreamSys's reuse its slots
 * 0x10 to 0x18 and 0xB8 to 0xE8; its methods end this unit.
 */
typedef struct ActorVtbl {
    u8 pad_00[0x08];
    s32 (*construct)();   /* 0x08 Actor_Construct */
    void (*destruct)();   /* 0x0C SceneNode_Destroy */
    u8 pad_10[0x40 - 0x10];
    void (*init)();       /* 0x40 Actor_Init */
    u8 pad_44[0x88 - 0x44];
    void (*sendBoxes)();      /* 0x88 Actor_SendBoxes */
    void (*getBoxList)();
    void (*sendShape)();
    u8 pad_94[0xA0 - 0x94];
    void (*checkContact)();
    u8 pad_A4[0xBC - 0xA4];
    void (*movePos)();    /* 0xBC Actor_MovePos */
    void (*moveLocal)();
    void (*moveZ)();
    void (*moveX)();
    u8 pad_CC[0xDC - 0xCC];
    void (*onTouch34)();  /* 0xDC Actor_OnNode34: Actor_OnNode on message byte 0x34 */
    void (*onTouch24)();  /* 0xE0 Actor_OnNode24: on message byte 0x24 */
    u8 pad_E4[0xE8 - 0xE4];
    void (*unkE8)();
} ActorVtbl;

/* The vtable of the class SceneNode_GetVtbl returns (src/game/scene_node.c), base of Actor. */
typedef struct ActorBaseVtbl {
    u8 pad_00[0x08];
    s32 (*construct)();   /* 0x08 */
    u8 pad_0C[0x10 - 0x0C];
    void (*watch)();      /* 0x10 */
    void (*unwatch)();    /* 0x14 */
    void (*unwatchAll)(); /* 0x18 */
    u8 pad_1C[0x88 - 0x1C];
    void (*sendBoxes)();
    u8 pad_8C[0x9C - 0x8C];
    void (*onNode)();
} ActorBaseVtbl;

typedef struct Actor {
    ActorVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    Coord2 *posBlock;     /* 0x14 its GsCOORDINATE2 (gs.h): flg cleared after each move */
    u8 pad_18[0x20 - 0x18];
    s32 model;            /* 0x20 tested by ModelObject_IsReady */
    u8 pad_24[0x28 - 0x24];
    s32 contact;          /* 0x28 the object found by Actor_SnapToGround, 0 when none */
    u8 pad_2C[0x44 - 0x2C];
    s32 unk44;            /* 0x44 cleared by the constructor */
    s16 speed;            /* 0x48 0x12C at init */
    u8 pad_4A[0x4C - 0x4A];
    s32 map;              /* 0x4C the watched object whose class id ends in 0x114 (the map) */
    s32 clock;            /* 0x50 the watched object whose class id ends in 5 */
    s32 boxMargin;            /* 0x54 slot 0xEC */
} Actor;

/* A cell of the map grid as Actor_FindGroundInRect reads it: 20 x 20 entry words at +0x10 (0x50 per row). */
typedef struct GridCell {
    u8 pad_00[0x10];
    s32 entries;
} GridCell;

/* An object in a grid entry, chained by +0x38. */
typedef struct GridEntry {
    u8 pad_00[0x38];
    s32 next;
} GridEntry;

/*
 * The contact search of Actor_SnapToGround over the map's grid: 20 x 20 entry words per cell
 * (GridCell), each a chain of objects; the query gives the cell and the actor's x, y in it.
 */
typedef struct GridRect {
    s16 left;
    s16 top;
    s32 width;
    s32 height;
} GridRect;

typedef struct GridActor GridActor;

typedef struct GridActorVtbl {
    u8 pad_00[0x88];
    void (*sendBoxes)(GridActor *, s32);  /* -1 contact found, -2 none */
    u8 pad_8C[0xBC - 0x8C];
    void (*movePos)(GridActor *, void *);
} GridActorVtbl;

/* An Actor as Actor_SnapToGround reads it. */
struct GridActor {
    GridActorVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    u8 *posBlock;
    u8 pad_18[0x28 - 0x18];
    s32 contact;
    u8 pad_2C[0x4C - 0x2C];
    StageMap *map;        /* 0x4C */
};
static void Actor_ApplyPos(void *self, s32 set, s32 *vec);
extern s16 g_actorMoveVecZ[];
void Actor_MoveAxis(void *self, s16 *field, s32 value, s32 notify, s32 message);
extern s16 g_actorMoveVec[];
/* not in game/actor.h: each file that calls it reads the vtable through its own view of the slots */
ActorVtbl *Actor_GetVtbl(void);
/* the vtable of scene_node.c through this file's view of its slots, so not from game/scene_node.h */
ActorBaseVtbl *SceneNode_GetVtbl(void);
s32 Actor_SnapToGround();
static s32 Actor_FindGroundInRect(s32 actor, s32 delta, s32 pos, s32 rect, void *cell);
static s32 Actor_GetGroundRects(void *actor, void *outRects, void *outCells, void *cellInfo, s32 size);
static s32 Actor_ProbeGroundAt();
extern u8 g_actorVtbl[];
static void Actor_MoveThenSnap(Actor *actor, void (*move)(void *, s32, s32), s32 value, s32 notify);

/* Allocate a kind 0 part: an object of the base class g_actorVtbl (0x58 bytes). */
void *Actor_New(void) {
    void *part;

    part = Heap_Alloc(0x58);
    if (part == 0) {
        return 0;
    }
    if (Actor_GetVtbl()->construct(part) != 0) {
        return part;
    }
    Heap_Free(part);
    return 0;
}

/* Slot 0x08 of the base class g_actorVtbl */
void *Actor_Construct(Actor *actor) {
    if (SceneNode_GetVtbl()->construct(actor) != 0) {
        actor->vt = Actor_GetVtbl();
        actor->unk44 = 0;
        actor->map = 0;
        actor->clock = 0;
        actor->vt->init(actor);
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
        actor->map = (s32)other;
        return;
    }
    if ((classId & 0xF) == 5) {
        actor->clock = (s32)other;
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
void Actor_Init(Actor *actor) {
    actor->speed = 0x12C;
    actor->boxMargin = 0;
}

/* Slot 0x88: messages 5 to 8 while unk20 passes ModelObject_IsReady. */
void Actor_SendBoxes(Actor *actor, s32 message) {
    s32 *buf[14];
    Actor *contact;

    SceneNode_GetVtbl()->sendBoxes(actor, message);
    if (message < 9) {
        if (message >= 5) {
            if ((actor->model != 0) && (ModelObject_IsReady(actor->model) != 0)) {
                actor->vt->getBoxList(actor, buf);
                if (message != 5) {
                    ModelBox_ShiftList(buf, message == 7, actor->speed >= 0,
                                  actor->speed >= 0 ? actor->speed + actor->boxMargin : actor->speed - actor->boxMargin);
                }
                actor->vt->sendShape(actor, buf, message);
                contact = (Actor *)actor->contact;
                if (contact != NULL) {
                    if (*(u8 *)contact->vt == 0x34) {
                        contact->vt->unkE8(contact, contact->vt);
                    }
                }
            }
        }
    }
}

/* Slot 0x9C: message byte 0x34 goes to slot 0xDC, 0x24 to 0xE0 (both called without arguments). */
void Actor_OnNode(Actor *actor, u8 **message) {
    u8 c = **message;

    if (c == 0x34) {
        actor->vt->onTouch34();
    } else if (c == 0x24) {
        actor->vt->onTouch24();
    }
}

/* Slot 0xB8: set the position. */
void Actor_SetPos(void *actor, s32 *pos) {
    Actor_ApplyPos(actor, 1, pos);
}

/* Slot 0xBC: move by a vector. */
void Actor_MovePos(void *actor, s32 *delta) {
    Actor_ApplyPos(actor, 0, delta);
}

static void Actor_ApplyPos(void *self, s32 set, s32 *vec) {
    Actor *actor = self;
    Coord2 *block = actor->posBlock;
    if (set != 0) {
        block->coord.t = *(Vec3 *)vec;
    } else {
        block->coord.t.x += vec[0];
        block->coord.t.y += vec[1];
        block->coord.t.z += vec[2];
    }
    actor->posBlock->flg = 0;
}

/* Slot 0xC0 */
void Actor_MoveLocal(Actor *actor, void *local) {
    s32 delta[3];

    SceneNode_RotateVector(actor, delta, local);
    actor->vt->movePos(actor, delta);
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
    actor->vt->moveLocal(actor, g_actorMoveVec);
    *field = 0;
    if (notify != 0) {
        actor->vt->sendBoxes(actor, message);
    }
}

/* Slot 0xD0 */
void Actor_MoveZOnGround(Actor *actor, s32 value, s32 notify) {
    Actor_MoveThenSnap(actor, actor->vt->moveZ, value, notify);
}

/* Slot 0xD4 */
void Actor_MoveXOnGround(Actor *actor, s32 value, s32 notify) {
    Actor_MoveThenSnap(actor, actor->vt->moveX, value, notify);
}

void Actor_StubD8(void) {
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
s32 Actor_SnapToGround(GridActor *actor) {
    s32 cell[0xC];
    s32 rects[0xC];
    void *cells[4];
    s32 delta[4];
    u8 *pos;
    s32 found;

    if (actor->map != NULL) {
        pos = actor->posBlock + 0x18;
        if (actor->map->vtbl->locate(actor->map, cell, pos) == 0) {
            found = Actor_GetGroundRects(actor, rects, cells, cell, 1);
            found = Actor_FindGroundInCells((s32)actor, (s32)delta, (s32)pos, found, (s32)rects, cells);
            actor->contact = found;
            if (found != 0) {
                actor->vt->movePos(actor, delta);
                actor->vt->sendBoxes(actor, -1);
                return 1;
            }
            actor->vt->sendBoxes(actor, -2);
        }
    }
    return 0;
}

/* The rectangles of cells to search: the cell itself and the slots above and below it (n == 1), else the n x n square clipped to the 20 x 20 grid. */
static s32 Actor_GetGroundRects(void *actor, void *outRects, void *outCells, void *cellInfo, s32 size) {
    MapSlot **cells;
    GridRect *rects;
    MapLocation *in = cellInfo;
    s32 n = size;
    s32 x = in->at.place.tileX;
    s32 y = in->at.place.tileY;
    s32 left, top, w, h, count;

    rects = outRects;
    cells = outCells;

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
        map = ((GridActor *) actor)->map;
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

static s32 Actor_FindGroundInCells(s32 actor, s32 delta, s32 pos, s32 count, s32 rects, void **cells) {
    s32 found;
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
        rects += 0xC;
        cells += 1;
    }
    return 0;
}

/* Walk a rectangle of a cell's 20-wide grid (+0x10) and each entry's chain (+0x38). */
static s32 Actor_FindGroundInRect(s32 actor, s32 delta, s32 pos, s32 rect, void *cell) {
    GridRect *r = (GridRect *)rect;
    GridCell *grid = (GridCell *)cell;
    s32 entry;
    s32 col;
    s32 row;
    s32 *slot;

    slot = (s32 *)(grid->entries + r->top * 0x50 + r->left * 4);
    for (row = 0; row < r->height; row++) {
        for (col = 0; col < r->width; col++) {
            if (Actor_ProbeGroundAt(*slot, delta, pos) != 0) {
                return *slot;
            }
            entry = ((GridEntry *)*slot)->next;
            if (entry != 0) {
                do {
                    if (Actor_ProbeGroundAt(entry, delta, pos) != 0) {
                        return entry;
                    }
                    entry = ((GridEntry *)entry)->next;
                } while (entry != 0);
            }
            slot += 1;
        }
        slot -= r->width + 0x14;
    }
    return 0;
}

static s32 Actor_ProbeGroundAt(s32 entry) {
    if (entry != 0 && SceneNode_ProbeHeight() != 0) {
        return entry;
    }
    return 0;
}

/* Slot 0xDC: the base slot 0x9C, then slot 0xA0 for messages 5 to 8. */
void Actor_OnNode34(Actor *actor, void *sender, s32 message) {
    SceneNode_GetVtbl()->onNode(actor, sender, message);
    if (message < 9) {
        if (message >= 5) {
            actor->vt->checkContact(actor, sender, message);
        }
    }
}

/* Slot 0xE0 */
void Actor_OnNode24(s32 actor, s32 sender, s32 message) {
    SceneNode_GetVtbl()->onNode(actor, sender, message);
}

/* Slot 0xE4 */
void Actor_SetSpeed(Actor *actor, s16 value) {
    actor->speed = value;
}

void Actor_StubE8(void) {
}

/* Slot 0xEC */
void Actor_SetBoxMargin(Actor *actor, s32 value) {
    actor->boxMargin = value;
}

ActorVtbl *Actor_GetVtbl(void) {
    return (ActorVtbl *)g_actorVtbl;
}

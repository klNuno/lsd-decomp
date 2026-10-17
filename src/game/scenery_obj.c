#include "common.h"
#include "game/scenery_obj.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/model_object.h"
#include "game/view.h"
#include "game/place.h"
#include "game/actor.h"
#include "game/scenery_part.h"
#include "psyq/libc.h"

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
    void (*afterTouch)();
} ActorVtbl;

static void Scenery_CreateSpriteParts(Scenery *scenery, s32 unused, s32 index, s16 *scale);
static void Scenery_Follow();
static void Scenery_DeleteParts();
static void Scenery_DeleteKind0Parts(Scenery *scenery);
static void Scenery_DeleteKind2Parts(Scenery *scenery);
static void Scenery_DeleteKind3Parts(Scenery *scenery);
/* not from game/actor.h: other files read this vtable through their own views of the slots */
ActorVtbl *Actor_GetVtbl(void);
extern s32 g_sceneryModelIndexes[];
extern struct ClutPos g_sceneryModelClut;
PlaceObj *g_sceneryModels;
void *g_sceneryFont;
View *g_sceneryView;
SceneryVtbl *Scenery_GetVtbl(void);
static void Scenery_Build(void *self, StageMap *map, Vec3 *origin);
extern u8 g_sceneryKind3Scales[];
static void Scenery_AddOffset(Vec3 *out, Vec3 *a, Vec3 *b);
s32 g_sceneryViewY;
static void Scenery_UpdateKind0(void *self, Vec3 *origin);
static void Scenery_UpdateKind2(void *scenery, Vec3 *origin);
static void Scenery_UpdateKind3(Scenery *scenery, Vec3 *origin);
static void Scenery_AttachPart(void *self, void *parent, Vec3 *pos, u8 *rotation, s16 *scale);
static void Scenery_PlaceKind0Parts(void *self, s32 move);
static void Scenery_BuildKind2(Scenery *scenery, s32 unused);
static void Scenery_BuildKind3(Scenery *scenery, s32 unused);
extern s32 g_sceneryKind2Offsets[];
extern s16 g_sceneryKind2ScaleB[];
extern Vec3 g_sceneryKind2Move;
extern s16 g_sceneryKind2ScaleC[];
extern s16 g_sceneryKind2ScaleA[];
extern SceneryVtbl g_sceneryVtbl;
extern s32 g_sceneryKind0Speeds[];
extern Vec3 g_sceneryKind0SpinOrigin;
extern s32 g_sceneryKind0Spin[];
extern Vec3 g_sceneryKind0Origin;
extern s32 g_sceneryPartSpacing[];

/* Allocate a scenery object (0x98 bytes) of a kind from params at map, origin. */
Scenery *Scenery_New(s32 kind, SceneryParams *params, StageMap *map, Vec3 *origin) {
    Scenery *scenery;

    scenery = Heap_Alloc(0x98);
    if (scenery == 0) {
        return 0;
    }
    if (Scenery_GetVtbl()->construct(scenery, kind, params, map, origin) != 0) {
        return scenery;
    }
    Heap_Free(scenery);
    return 0;
}

/* Slot 0x08 */
Scenery *Scenery_Construct(Scenery *scenery, s32 kind, SceneryParams *params, StageMap *map, Vec3 *origin) {
    if (Actor_GetVtbl()->construct(scenery) != 0) {
        scenery->vt = Scenery_GetVtbl();
        scenery->state = 0;
        scenery->kind = kind;
        scenery->vt->init(scenery, params);
        Scenery_Build(scenery, map, origin);
        return scenery;
    }
    return NULL;
}

/* Slot 0x0C (Scenery_DeleteParts is called without the object; a0 still holds it). */
void Scenery_Destruct(s32 scenery) {
    Scenery_DeleteParts();
    Actor_GetVtbl()->destruct(scenery);
}

/* Slot 0x40: copy the parameters to +0x58. */
void Scenery_Init(Scenery *scenery, SceneryParams *params) {
    *(SceneryParams *)((u8 *)scenery + 0x58) = *params;
    scenery->ticks = 0;
}

/* Slot 0xEC, every tick (Scenery_Follow is called without arguments; a0 and a1 still hold them). */
void Scenery_Update(Scenery *scenery) {
    scenery->ticks++;
    Scenery_Follow();
}

/* Place it at origin + offset and build its parts by kind. */
static void Scenery_Build(void *self, StageMap *map, Vec3 *origin) {
    Scenery *scenery = self;
    Vec3 pos;
    s32 kind;

    g_sceneryViewY = g_sceneryView->viewpoint.y;
    Scenery_AddOffset(&pos, origin, &scenery->offset);
    Scenery_AttachPart(scenery, map, &pos, scenery->rotation, scenery->scale);
    kind = scenery->kind;
    if (kind < 2) {
        SceneNode_LinkModel(self, g_sceneryModels->vt->getModel(g_sceneryModels, g_sceneryModelIndexes[kind]));
    }
    switch (scenery->kind) {
    case 0:
        Scenery_PlaceKind0Parts(scenery, 0);
        return;
    case 2:
        Scenery_BuildKind2(scenery, 0);
        return;
    case 3:
        Scenery_BuildKind3(scenery, 0);
        return;
    }
}

/* Follow the origin (and the view's height since it was made), then update the parts by kind. */
static void Scenery_Follow(Scenery *scenery, Vec3 *origin) {
    Vec3 pos;

    Scenery_AddOffset(&pos, origin, &scenery->offset);
    pos.y += g_sceneryView->viewpoint.y - g_sceneryViewY;
    scenery->vt->setPos(scenery, &pos);
    switch (scenery->kind) {
    case 0:
        Scenery_UpdateKind0(scenery, origin);
        return;
    case 2:
        Scenery_UpdateKind2(scenery, origin);
        return;
    case 3:
        Scenery_UpdateKind3(scenery, origin);
        return;
    }
}

/* Delete the parts by kind. */
static void Scenery_DeleteParts(Scenery *scenery) {
    switch (scenery->kind) {
    case 0:
        Scenery_DeleteKind0Parts(scenery);
        break;
    case 2:
        Scenery_DeleteKind2Parts(scenery);
        break;
    case 3:
        Scenery_DeleteKind3Parts(scenery);
        break;
    }
}

static void Scenery_AddOffset(Vec3 *out, Vec3 *a, Vec3 *b) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

/* Slots 0x4C, 0x44 and 0x48 of a scenery object or part (pos is not used). */
static void Scenery_AttachPart(void *self, void *parent, Vec3 *pos, u8 *rotation, s16 *scale) {
    SceneryPart *obj = self;

    obj->vt->attach(obj, parent);
    obj->vt->setRotation(obj, 1, rotation);
    obj->vt->setScale(obj, 1, scale);
}

/* Kind 0: make (move == 0) or move its two parts, set apart along direction unk6C (1 to 4). */
static void Scenery_PlaceKind0Parts(void *self, s32 move) {
    Scenery *scenery = self;
    Vec3 pos;
    s32 dir;
    SceneryPart **part;
    s32 i;

    dir = scenery->direction;
    if (dir != 0) {
        pos = g_sceneryKind0Origin;
        part = scenery->u.pair;
        for (i = 0; i < 2; i++) {
            if (dir < 3) {
                pos.x += *scenery->scale * g_sceneryPartSpacing[dir];
            } else {
                pos.y += g_sceneryPartSpacing[dir];
            }
            if (move != 0) {
                SceneryPart *obj = *part;
                obj->vt->setColor(obj, &pos);
            } else {
                *part = Actor_New();
                SceneNode_LinkModel((SceneNode *)*part, scenery->model);
                Scenery_AttachPart(*part, scenery, &pos, scenery->rotation, scenery->scale);
            }
            part++;
        }
    }
}

/* Kind 0 tick: past 500 ticks, with a speed in g_sceneryKind0Speeds[unk70], move the parts every 0x5FB4 / speed ticks. */
static void Scenery_UpdateKind0(void *self, Vec3 *origin) {
    Scenery *scenery = self;
    SceneryPart **part;
    Vec3 pos;
    s32 *speed;
    s32 idx;
    s32 i;
    s32 off;
    s32 period;
    u32 ticks;

    idx = scenery->variant;
    if (scenery->direction != 0) {
        if (g_sceneryKind0Speeds[idx] != 0) {
            part = scenery->u.pair;
            if (scenery->ticks >= 0x1F5) {
                scenery->vt->setRotation(scenery, 0, &g_sceneryKind0Spin);
                i = 0;
                speed = &g_sceneryKind0Speeds[idx];
                off = 0;
                do {
                    pos = g_sceneryKind0SpinOrigin;
                    pos.z += off + *speed;
                    (*part)->vt->setPosition(*part, &pos);
                    i++;
                    off += 3;
                    (*part)->vt->setRotation(*part, 0, &g_sceneryKind0Spin);
                    part++;
                } while (i < 2);
                period = 0x5FB4 / g_sceneryKind0Speeds[idx];
                ticks = scenery->ticks;
                if (period >= 0) {
                    if (ticks % (u32)period == 0) {
                        Scenery_PlaceKind0Parts(scenery, 1);
                    }
                } else {
                    if (ticks % (u32)(~period + 1) == 0) {
                        Scenery_PlaceKind0Parts(scenery, 1);
                    }
                }
            }
        }
    }
    *scenery->posBlock = 0;
}

static void Scenery_DeleteKind0Parts(Scenery *scenery) {
    if (scenery->direction != 0) {
        Object_DeleteArray((Object **)scenery->u.pair, 2);
    }
}

/* Kind 2: five parts, then part 1 placed from g_sceneryKind2Offsets[unk70] or coloured, part 2 shown. */
static void Scenery_BuildKind2(Scenery *scenery, s32 unused) {
    SceneryPart *part;
    SceneryPartVtbl *vt;
    Vec3 *value;
    s32 coin;
    s16 *scale;
    s16 *partScale;
    s32 arg;

    coin = rand() % 2;
    partScale = 0;
    if (coin == 0) {
        partScale = g_sceneryKind2ScaleB;
    }
    Scenery_CreateSpriteParts(scenery, 0, 0, partScale);
    if (scenery->variant >= 2) {
        value = &g_sceneryKind2Move;
        part = scenery->u.many.parts[1];
        value->x = g_sceneryKind2Offsets[scenery->variant];
        Actor_MovePos(part, value);
        arg = scenery->dayMark;
        vt = part->vt;
        if (arg == 0) {
            arg = scenery->color;
        }
        vt->setColor(part, arg);
    } else {
        part = scenery->u.many.parts[1];
        part->vt->setSemiTrans(part, 1);
        part->vt->setBlendRate(part, 0);
        vt = part->vt;
        scale = g_sceneryKind2ScaleC;
        if (coin != 0) {
            scale = g_sceneryKind2ScaleA;
        }
        vt->setScale(part, 1, scale);
    }
    scenery->u.many.parts[2]->vt->setVisible(scenery->u.many.parts[2], 0);
}

/* Kinds 2 and 3: five parts of class g_sceneryPartVtbl in the place's font. */
static void Scenery_CreateSpriteParts(Scenery *scenery, s32 unused, s32 index, s16 *scale) {
    SceneryPart **part;
    s32 i;

    part = scenery->u.many.parts;
    for (i = 0; i < 5; i++) {
        *part = SceneryPart_New(index, 0, g_sceneryFont);
        (*part)->vt->attach(*part, scenery, 0);
        (*part)->vt->setColor(*part, scenery->color);
        if (scale != 0) {
            (*part)->vt->setScale(*part, 1, scale);
        }
        part++;
    }
}

static void Scenery_UpdateKind2(void *scenery, Vec3 *origin) {
}

static void Scenery_DeleteKind2Parts(Scenery *scenery) {
    Object_DeleteArray((Object **)scenery->u.many.parts, 5);
}

static void Scenery_BuildKind3(Scenery *scenery, s32 unused) {
    Scenery_CreateSpriteParts(scenery, 0, 0, 0);
}

/* Kind 3 tick: parts 1 to 4 get a random colour of g_sceneryKind3Scales and a random angle. */
static void Scenery_UpdateKind3(Scenery *scenery, Vec3 *origin) {
    s32 i;
    SceneryPart **part;

    part = &scenery->u.many.parts[1];
    for (i = 0; i < 4; i++) {
        (*part)->vt->setScale(*part, 1, g_sceneryKind3Scales + ((u32)rand() % 6) * 12);
        (*part)->angle = (rand() % 360) << 12;
        part++;
    }
}

static void Scenery_DeleteKind3Parts(Scenery *scenery) {
    Object_DeleteArray((Object **)scenery->u.many.parts, 5);
}

SceneryVtbl *Scenery_GetVtbl(void) {
    return &g_sceneryVtbl;
}

/* Keep the place's models, font and view for the scenery, and prepare models g_sceneryModelIndexes[0..1]. */
void Scenery_SetPlaceRefs(s32 family, PlaceObj *models, void *font, View *view) {
    s32 i;

    g_sceneryModels = models;
    g_sceneryFont = font;
    g_sceneryView = view;
    for (i = 0; i < 2; i++) {
        ModelObject_SetClut(models->vt->getModel(models, g_sceneryModelIndexes[i]), &g_sceneryModelClut);
    }
}

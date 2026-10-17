#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/sound_bank.h"
#include "game/mom.h"
#include "game/model_object.h"
#include "game/render.h"

struct SceneNode;
struct StageMap;

/* What Model_LoadFile loads a model from: a ready file object at +0xC, else what Mom_Create reads. */
typedef struct ModelSource {
    FileSource source;
    Mom *file;       /* 0x0C */
} ModelSource;

/*
 * The model class vtable g_modelVtbl 0x8008A6C4 (Model_GetVtbl), 0x144 bytes. Slots 0x00 to 0xEC
 * are ActorVtbl's (actor.h) under the same names, Model's overrides noted; 0xF0 on are Model's own.
 * Entity's vtable (EntityVtbl, entity.h) derives from it.
 */
typedef struct ModelVtbl {
    u8 pad_00[0x4];                                        /* 0x00 class word 0x234 */
    void *(*delete_)(void *self);                          /* 0x04 Object_Delete */
    s32 (*init)(void *self, ModelSource *source, SoundBank *soundBank); /* 0x08 Model_Construct */
    void (*destroy)(void *self);                           /* 0x0C Model_Destruct */
    void (*watch)(void *self, void *other);                /* 0x10 Actor_Watch */
    void (*unwatch)(void *self, void *other);              /* 0x14 Actor_Unwatch */
    u8 pad_18[0x40 - 0x18];
    void (*reset)(void *self);                             /* 0x40 Model_Init */
    u8 pad_44[0x4C - 0x44];
    void (*attach)(void *self, void *target, void *watched, void *map, void *placement); /* 0x4C Model_Attach */
    void (*detach)(void *self);                            /* 0x50 Model_Detach */
    u8 pad_54[0x98 - 0x54];
    void (*onClock)(void *self, void *sender, s32 phase);  /* 0x98 Model_Update */
    u8 pad_9C[0xC4 - 0x9C];
    void (*moveZ)(void *self, s32 amount, s32 animate);    /* 0xC4 Actor_MoveZ */
    u8 pad_C8[0xDC - 0xC8];
    void (*onTouch34)(void *self, void *sender, s32 message); /* 0xDC Actor_OnNode34, Entity_OnActorTouch in the entity class */
    void (*onTouch24)(void *self, void *sender, s32 message); /* 0xE0 Actor_OnNode24, Entity_OnWallTouch in the entity class */
    void (*setSpeed)(void *self, s32 speed);               /* 0xE4 Actor_SetSpeed */
    u8 pad_E8[0xF0 - 0xE8];
    void (*setForwardContact)(void *self, s32 value);      /* 0xF0 Model_SetForwardContact */
    s32 (*load)(void *self, ModelSource *source);          /* 0xF4 Model_Load */
    void (*unload)(void *self);                            /* 0xF8 Model_Unload */
    u8 pad_FC[0x100 - 0xFC];                               /* 0xFC Model_FindPart */
    s32 (*createParts)(void *self);                        /* 0x100 Model_CreateParts */
    void (*freeParts)(void *self);                         /* 0x104 Model_FreeParts */
    void (*tick)(void *self);                              /* 0x108 Model_Tick */
    void (*setTickMode)(void *self, s32 mode);             /* 0x10C Model_SetTickMode: 0x41, 0x42 or 0x43 */
    void (*startTick)(void *self);                         /* 0x110 Model_StartTick */
    void (*stopTick)(void *self);                          /* 0x114 Model_StopTick */
    void (*tickA)(void *self);                             /* 0x118 Model_TickForward */
    void (*tickB)(void *self);                             /* 0x11C empty here, the entity's handler run (Entity_RunHandler) */
    void (*tickC)(void *self);                             /* 0x120 empty */
    u8 pad_124[0x128 - 0x124];                             /* 0x124 Model_PlaySound */
    void (*setAnimation)(void *self, s32 animation);       /* 0x128 Model_SetAnimation */
    u8 pad_12C[0x130 - 0x12C];                             /* 0x12C Model_PlayAnimation */
    void (*stopAnimation)(void *self);                     /* 0x130 Model_StopAnimation */
    u8 *(*applyFrame)(void *self, u8 *frame, void *context);  /* 0x134 Model_ApplyFrame */
    u8 *(*applyCommand)(void *self, u8 *command, void *context); /* 0x138 Model_ApplyCommand */
    void (*setTarget)(void *self, void *target);           /* 0x13C Model_SetTarget */
    void (*clearTarget)(void *self);                       /* 0x140 Model_ClearTarget */
} ModelVtbl;

/*
 * The model class, 0x98 bytes (Model_New): a model file split into parts, one animation played
 * frame by frame, a per-tick function, a sound bank and a target it watches. Entity derives from it.
 * Fields up to +0x58 are Actor's (actor.h) under the same names, with the vtable typed as ModelVtbl
 * and ticks unsigned (Entity_CheckSleep compares it unsigned).
 */
typedef struct Model {
    ModelVtbl *vtbl;             /* 0x00 g_modelVtbl or a subclass's */
    ListNode *watched;           /* 0x04 Actor.watched */
    ListNode *watchers;          /* 0x08 */
    struct SceneNode *parent;    /* 0x0C set by the parent's attach */
    DObj2 object;                /* 0x10 */
    s32 id;                      /* 0x1C */
    ModelObject *model;          /* 0x20 */
    u32 ticks;                   /* 0x24 counted by the tick functions */
    void *contact;               /* 0x28 */
    s32 hitMask;                 /* 0x2C */
    NodeBoxList *boxList;        /* 0x30 */
    u8 pad_34[0x44 - 0x34];
    s32 state;                   /* 0x44 */
    s16 speed;                   /* 0x48 */
    u8 pad_4A[0x4C - 0x4A];
    struct StageMap *map;        /* 0x4C */
    void *clock;                 /* 0x50 the object Model_Attach watches, unwatched by Model_Detach */
    s32 boxMargin;               /* 0x54 */
    SoundBank *soundBank;        /* 0x58 */
    Mom *file;                   /* 0x5C */
    s32 ownsFile;                /* 0x60 1 when the file was loaded here, 0 when borrowed */
    s32 forwardContact;          /* 0x64 1 makes tickA play part animation 6 */
    struct SceneNode *part;      /* 0x68 the part the file names as current */
    s32 partCount;               /* 0x6C */
    struct SceneNode **parts;    /* 0x70 one Actor (Actor_New) per object of the file's TMD */
    u8 *partIds;                 /* 0x74 one id per part, the file's numbering */
    void (*tickFn)(void *self);  /* 0x78 run each tick while tickEnabled, chosen by setTickMode */
    s32 animation;               /* 0x7C */
    s32 animLength;              /* 0x80 */
    s32 animFrame;               /* 0x84 */
    u8 *animData;                /* 0x88 */
    s32 tickEnabled;             /* 0x8C */
    s32 animPlaying;             /* 0x90 */
    struct Model *target;        /* 0x94 */
} Model;

/* Functions of src/game/model.c that other files call or reference (docs/naming.md, Prototypes) */
void Model_OnNotify(Model *model, u16 **sender, s32 message);
void Model_SetVisible(Model *model, s32 visible);
void Model_SetLightFlags(Model *model, s32 flags);
void Model_SetForwardContact(Model *model, s32 value);
s32 Model_Load(Model *model);
void Model_Unload(Model *model);
s32 Model_FindPart(Model *model, u8 id);
s32 Model_CreateParts(Model *model);
void Model_FreeParts(Model *model);
void Model_Tick(Model *model);
void Model_SetTickMode(Model *model, s32 mode);
void Model_StartTick(Model *model);
void Model_StopTick(Model *model);
void Model_TickForward(Model *model);
void Model_TickC(void);
void Model_PlaySound(Model *model, s32 sound);
void Model_SetAnimation(Model *model, s32 animation);
void Model_PlayAnimation(Model *model);
void Model_StopAnimation(Model *model);
void *Model_ApplyFrame(Model *model, u8 *frame, void *context);
s32 Model_ApplyCommand(Model *model, s32 command);
void Model_SetTarget(Model *model, Model *target);
void Model_ClearTarget(Model *model);
ModelVtbl *Model_GetVtbl(void);

#endif

#include "common.h"
#include "game/model.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/sound_bank.h"
#include "game/mom.h"
#include "game/actor.h"
#include "game/entity.h"

/*
 * Model: the model base class every entity derives from (vtable g_modelVtbl 0x8008A6C4, 0x98
 * bytes): model file, parts, animation, per-tick function, sound bank.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* What Model_LoadFile loads a model from: a ready file object at +0xC, else what Mom_Create reads. */
typedef struct ModelSource {
    FileSource source;
    Mom *file;       /* 0x0C */
} ModelSource;

/* The parent class of Model (returned by Actor_GetVtbl, unit 80051F24): the slots Model's methods chain to. */
typedef struct ModelParentVtbl {
    u8 pad_00[0x8];
    s32 (*construct)();   /* 0x08 */
    void (*destroy)();    /* 0x0C */
    u8 pad_10[0x38 - 0x10];
    void (*onNotify)();   /* 0x38 */
    u8 pad_3C[0x4C - 0x3C];
    void (*attach)();     /* 0x4C */
    void (*detach)();     /* 0x50 */
    u8 pad_54[0x60 - 0x54];
    void (*setVisible)(); /* 0x60 Model_SetVisible */
    u8 pad_64[0x70 - 0x64];
    void (*setLightFlags)(); /* 0x70 Model_SetLightFlags */
} ModelParentVtbl;

/*
 * The model class, vtable 0x8008A6C4 (Model_GetVtbl), 0x98 bytes (Model_New): a model file
 * split into parts, one animation played frame by frame, a per-tick function, a sound bank and a
 * target it watches. Entity (vtable 0x80089AD4) derives from it. Slots named from the functions
 * stored in the vtable read from the executable.
 */
typedef struct ModelVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(void *self);                          /* 0x04 Object_Delete */
    s32 (*construct)(void *self, ModelSource *source, SoundBank *soundBank); /* 0x08 Model_Construct */
    u8 pad_0C[0x10 - 0x0C];
    void (*watch)(void *self, void *other);                /* 0x10 */
    void (*unwatch)(void *self, void *other);              /* 0x14 */
    u8 pad_18[0x40 - 0x18];
    void (*init)(void *self);                              /* 0x40 Model_Init */
    u8 pad_44[0x98 - 0x44];
    void (*update)(void *self, void *sender, s32 phase);   /* 0x98 Model_Update */
    u8 pad_9C[0xC4 - 0x9C];
    void (*moveZ)(void *self, s32 amount, s32 animate);    /* 0xC4 Actor_MoveZ */
    u8 pad_C8[0xDC - 0xC8];
    void (*onActorTouch)(void *self, void *sender, s32 message); /* 0xDC Actor_OnNode34, Entity_OnActorTouch in the entity class */
    void (*onWallTouch)(void *self, void *sender, s32 message);  /* 0xE0 Actor_OnNode24, Entity_OnWallTouch in the entity class */
    void (*setSpeed)(void *self, s32 speed);               /* 0xE4 Actor_SetSpeed */
    u8 pad_E8[0xF0 - 0xE8];
    void (*setAnim6Flag)(void *self, s32 value);           /* 0xF0 Model_SetAnim6Flag */
    s32 (*load)(void *self, ModelSource *source);   /* 0xF4 Model_Load */
    void (*unload)(void *self);                            /* 0xF8 Model_Unload */
    u8 pad_FC[0x100 - 0xFC];
    s32 (*createParts)(void *self);                        /* 0x100 Model_CreateParts */
    void (*freeParts)(void *self);                         /* 0x104 Model_FreeParts */
    void (*tickAnimation)(void *self);                     /* 0x108 Model_TickAnimation */
    void (*setTickMode)(void *self, s32 mode);             /* 0x10C Model_SetTickMode: 0x41, 0x42 or 0x43 */
    void (*startTick)(void *self);                         /* 0x110 Model_StartTick */
    void (*stopTick)(void *self);                          /* 0x114 Model_StopTick */
    void (*tickA)(void *self);                             /* 0x118 Model_TickForward */
    void (*tickB)(void *self);                             /* 0x11C empty here, the entity's handler run (Entity_RunHandler) */
    void (*tickC)(void *self);                             /* 0x120 empty */
    u8 pad_124[0x128 - 0x124];
    void (*setAnimation)(void *self, s32 animation);       /* 0x128 Model_SetAnimation */
    u8 pad_12C[0x130 - 0x12C];
    void (*stopAnimation)(void *self);                     /* 0x130 Model_StopAnimation */
    u8 *(*applyFrame)(void *self, u8 *frame, void *context);  /* 0x134 Model_ApplyFrame */
    u8 *(*applyCommand)(void *self, u8 *command, void *context); /* 0x138 Model_ApplyCommand */
    void (*setTarget)(void *self, void *target);           /* 0x13C Model_SetTarget */
    void (*clearTarget)(void *self);                       /* 0x140 Model_ClearTarget */
} ModelVtbl;

typedef struct Model {
    ModelVtbl *vt;
    u8 pad_04[0xC - 0x4];
    s32 attached;              /* 0x0C set by the parent's attach */
    u8 pad_10[0x14 - 0x10];
    Coord2 *coord;         /* 0x14 */
    u8 pad_18[0x24 - 0x18];
    u32 timer;                 /* 0x24 ticks, counted by tickAnimation */
    u8 pad_28[0x50 - 0x28];
    void *clock;             /* 0x50 the object Model_Attach watches, unwatched by Model_Detach */
    u8 pad_54[0x58 - 0x54];
    struct SoundBank *soundBank; /* 0x58 */
    Mom *file;                 /* 0x5C */
    s32 ownsFile;              /* 0x60 1 when the file was loaded here, 0 when borrowed */
    s32 anim6Flag;             /* 0x64 setAnim6Flag; 1 makes tickA play part animation 6 */
    SceneNode *part;           /* 0x68 the part the file names as current */
    s32 partCount;             /* 0x6C */
    SceneNode **parts;         /* 0x70 one actor (Actor_New) per object of the file's TMD */
    u8 *partIds;               /* 0x74 one id per part, the file's numbering */
    void (*tickFn)(void *self); /* 0x78 run each tick while tickEnabled, chosen by setTickMode */
    s32 animation;             /* 0x7C */
    s32 animLength;            /* 0x80 */
    s32 animFrame;             /* 0x84 */
    u8 *animData;              /* 0x88 */
    s32 tickEnabled;           /* 0x8C */
    s32 animPlaying;           /* 0x90 */
    struct Model *target;      /* 0x94 */
} Model;

static s32 Model_LoadFile();
static void Model_FreeFile();
static s32 Model_BuildParts(Model *model);
static void Model_ReleaseParts(Model *model);
/* the vtable of actor.c through this file's view of its slots, so not from game/actor.h */
ModelParentVtbl *Actor_GetVtbl(void);
typedef struct ModelBaseVtbl {
    u8 pad[0x8];
    s32 (*construct)(void *, ModelSource *, SoundBank *); /* 0x08 Model_Construct */
    void (*destruct)(void *);                           /* 0x0C Model_Destruct */
    u8 pad1[0x4C - 0x10];
    void (*attach)(void *, void *, void *, s32, s32);   /* 0x4C Model_Attach */
    void (*detach)(void *);                             /* 0x50 Model_Detach */
    u8 pad2[0x98 - 0x54];
    void (*update)(void *, void *, s32);                /* 0x98 Model_Update */
    u8 pad3[0xDC - 0x9C];
    void (*onActorTouch)(void *, void *, s32);          /* 0xDC Entity_OnActorTouch */
    void (*onWallTouch)(void *, void *, s32);           /* 0xE0 Entity_OnWallTouch */
} ModelBaseVtbl;
static void Model_ReleaseParts(Model *model);
extern ModelBaseVtbl g_modelVtbl;

Model *Model_New(ModelSource *source, SoundBank *soundBank) {
    Model *model;

    model = Heap_Alloc(0x98);
    if (model != NULL) {
        if (Model_GetVtbl()->construct(model, source, soundBank) == 0) {
            Heap_Free(model);
            return NULL;
        }
        return model;
    }
    return NULL;
}

void *Model_Construct(Model *model, ModelSource *source, SoundBank *soundBank) {
    if (Actor_GetVtbl()->construct(model) != 0) {
        model->vt = (ModelVtbl *)Model_GetVtbl();
        model->soundBank = soundBank;
        model->file = 0;
        model->part = 0;
        model->parts = 0;
        model->target = 0;
        if (model->vt->load(model, source) == 0) {
            model->vt->watch(model, model->file);
            model->vt->init(model);
            return model;
        }
        Actor_GetVtbl()->destroy(model);
        return 0;
    }
    return 0;
}

void Model_Destruct(Model *model) {
    model->vt->unload(model);
    Actor_GetVtbl()->destroy(model);
}

/* Slot 0x38: when the file it borrows (class id 0x5F03) is destroyed (message 1), the model deletes itself. */
void Model_OnNotify(Model *model, u16 **sender, s32 message) {
    Actor_GetVtbl()->onNotify(model, sender, message);
    if ((**sender == 0x5F03) && (message == 1) && (model->ownsFile == 0)) {
        model->vt->delete_(model);
    }
}

void Model_Init(Model *model) {
    SceneNode *part;

    Actor_GetVtbl()->setVisible(model, 0);
    model->vt->setAnim6Flag(model, 1);
    model->vt->setSpeed(model, 0x12C);
    model->vt->stopTick(model);
    model->vt->setTickMode(model, 0x41);
    model->vt->stopAnimation(model);
    model->vt->setAnimation(model, 0);
    part = model->part;
    if (part != NULL) {
        SceneNode_LinkModel((SceneNode *)model, part->model);
    }
}

void Model_Attach(Model *model, void *target, void *watched, s32 parent, s32 child) {
    if (model->attached == 0) {
        Actor_GetVtbl()->attach(model, parent, child);
        if ((watched != 0) && (model->clock == 0)) {
            model->vt->watch(model, watched);
        }
        model->vt->setTarget(model, target);
    }
}

void Model_Detach(Model *model) {
    void *watched;

    if (model->attached != 0) {
        model->vt->clearTarget(model);
        watched = model->clock;
        if (watched != 0) {
            model->vt->unwatch(model, watched);
        }
        Actor_GetVtbl()->detach(model);
    }
}

void Model_SetVisible(Model *model, s32 visible) {
    SceneNode **p;
    s32 i;

    p = model->parts;
    for (i = 0; i < model->partCount; i++, p++) {
        (*p)->vtbl->setVisible(*p, visible);
    }
}

void Model_SetLightFlags(Model *model, s32 flags) {
    SceneNode **p;
    s32 i;

    p = model->parts;
    for (i = 0; i < model->partCount; i++, p++) {
        (*p)->vtbl->setLightFlags(*p, flags);
    }
    Actor_GetVtbl()->setLightFlags(model, flags);
}

/* Slot 0x98, the update: phase 2 runs the animation tick, phase 4 deletes the model. */
void Model_Update(Model *model, s32 sender, s32 phase) {
    if (phase == 2) {
        model->vt->tickAnimation(model);
    }
    if (phase == 4) {
        model->vt->delete_(model);
    }
}

void Model_SetAnim6Flag(Model *model, s32 value) {
    model->anim6Flag = value;
}

s32 Model_Load(Model *model) {
    if (model->file == 0) {
        return Model_LoadFile();
    }
    return 0;
}

void Model_Unload(Model *model) {
    if (model->file != 0) {
        Model_FreeFile();
    }
}

/* Takes the source's file object when it has one (borrowed), else loads one (owned), then makes the parts. */
static s32 Model_LoadFile(Model *model, ModelSource *source) {
    if (source->file != NULL) {
        model->file = source->file;
        model->ownsFile = 0;
    } else {
        model->file = Mom_Create(&source->source);
        model->ownsFile = 1;
    }
    if (model->file != NULL) {
        return model->vt->createParts(model);
    }
    Model_FreeFile(model);
    return 1;
}

static void Model_FreeFile(Model *model) {
    Mom *file;

    model->vt->freeParts(model);
    if (model->ownsFile != 0) {
        file = model->file->vtbl->base.delete_(model->file);
    } else {
        file = 0;
    }
    model->file = file;
}

/* Slot 0xFC: index of the part whose file id is id, -1 when none. */
s32 Model_FindPart(Model *model, u8 id) {
    u8 *p;
    s32 i;

    if (model->partIds != NULL) {
        p = model->partIds;
        for (i = 0; i < model->partCount; i++, p++) {
            if (*p == id) {
                return i;
            }
        }
    }
    return -1;
}

s32 Model_CreateParts(Model *model) {
    if (model->parts == 0) {
        return Model_BuildParts(model);
    }
    return 0;
}

void Model_FreeParts(Model *model) {
    if (model->parts != 0) {
        Model_ReleaseParts(model);
    }
}

static s32 Model_BuildParts(Model *model) {
    Mom *file;
    s32 current;
    s32 n;
    s32 i;
    SceneNode **p;
    SceneNode *part;

    file = model->file;
    n = file->vtbl->scanFirstFrame(file, 0, &current) & 0xFF;
    model->parts = Heap_Alloc(n * 4);
    if (model->parts != NULL) {
        model->partIds = Heap_Alloc(n);
        if (model->partIds != NULL) {
            file = model->file;
            file->vtbl->scanFirstFrame(file, model->partIds, &current);
            p = model->parts;
            model->partCount = 0;
            for (i = 0; i < n; i++) {
                part = Actor_New();
                *p++ = part;
                if (part == 0) {
                    goto fail;
                }
                model->partCount++;
            }
            model->part = model->parts[current];
            return 0;
        }
    }
    model->partIds = NULL;
fail:
    Model_ReleaseParts(model);
    return 1;
}

static void Model_ReleaseParts(Model *model) {
    SceneNode **p;
    SceneNode *part;

    if (model->parts != NULL && model->partIds != NULL) {
        p = model->parts;
        while (model->partCount-- > 0) {
            part = *p++;
            part->vtbl->delete_(part);
        }
        model->part = 0;
    }
    model->partIds = Heap_Free(model->partIds);
    model->parts = Heap_Free(model->parts);
}

/* Slot 0x108: counts the tick, runs the tick function, then plays one frame of the animation. */
void Model_TickAnimation(Model *model) {
    model->timer = model->timer + 1;
    if (model->tickEnabled != 0) {
        model->tickFn(model);
    }
    if ((model->animPlaying != 0) && (model->animLength >= 2)) {
        model->animData = model->vt->applyFrame(model, model->animData, 0);
        if (++model->animFrame >= model->animLength) {
            model->animFrame = 0;
            model->animData = model->file->motions->data.header->table.tods[model->animation]->data.bytes + 8;
        }
    }
    model->coord->flg = 0;
}

void Model_SetTickMode(Model *model, s32 mode) {
    switch (mode & 0xFF) {
    case 0x41:
        model->tickFn = model->vt->tickA;
        return;
    case 0x42:
        model->tickFn = model->vt->tickB;
        return;
    case 0x43:
        model->tickFn = model->vt->tickC;
        return;
    }
}

void Model_StartTick(Model *model) {
    model->tickEnabled = 1;
}

void Model_StopTick(Model *model) {
    model->tickEnabled = 0;
}

void Model_TickForward(Model *model) {
    SceneNode *part;

    model->vt->moveZ(model, -0x1E, 0);
    if (model->anim6Flag == 1) {
        part = model->part;
        if (part != NULL) {
            part->vtbl->sendBoxes(part, 6);
        }
    }
}

void Model_TickB(void) {
}

void Model_TickC(void) {
}

/* Slot 0x124: plays a sound of the model's bank at volume 0x6E. */
void Model_PlaySound(Model *model, s32 sound) {
    SoundBank *bank;

    bank = model->soundBank;
    if (bank != NULL) {
        bank->vtbl->playTone(bank, sound, 0x6E, 0x6E);
    }
}

void Model_SetAnimation(Model *model, s32 animation) {
    model->animation = animation;
    model->animLength = model->file->motions->data.header->table.tods[animation]->data.header->frameCount;
    model->animData = model->file->motions->data.header->table.tods[model->animation]->data.bytes + 8;
    model->animFrame = 0;
    model->vt->applyFrame(model, model->animData, 0);
}

void Model_PlayAnimation(Model *model) {
    model->animPlaying = 1;
}

void Model_StopAnimation(Model *model) {
    model->animPlaying = 0;
}

/* Slot 0x134: runs the frame's commands (u16 count at +2, commands from +8), returns the next frame. */
void *Model_ApplyFrame(Model *model, u8 *frame, void *context) {
    u32 count;
    u32 i;
    u32 pad[2];

    count = *(u16 *)(frame + 2);
    frame = frame + 8;
    i = 0;
    if (count != 0) {
        do {
            i++;
            frame = model->vt->applyCommand(model, frame, context);
        } while (i < count);
    }
    return frame;
}

/*
 * Slot 0x138: one frame command on one part. Type 0 masks and sets the part's flags; type 1 rotates
 * (degrees * 4096 / 360), scales and moves it, adding when flags bit 0 is set, else setting; type 2
 * gives it a texture; type 3 attaches it to the model or to another part.
 */
s32 Model_ApplyCommand(Model *model, s32 command) {
    u8 id;
    u8 type;
    u8 flags;
    u8 size;
    s32 *data;
    s32 n;
    SceneNode *part;
    Coord2 *coord;
    Coord2Param *param;
    s16 *s;
    s16 *r;
    s32 *v;
    s32 i;

    data = model->file->vtbl->readPacket(model->file, command, &id, &type, &flags, &size);
    n = Model_FindPart(model, id);
    if (n >= 0) {
        part = model->parts[n];
        coord = part->coord;
        coord->flg = 0;
        param = coord->param;
        switch (type) {
        case 0:
            part->attribute = (part->attribute & data[0]) | data[1];
            break;
        case 1:
            if (flags & 1) {
                if (flags & 2) {
                    r = param->rotate.axis;
                    for (i = 0; i < 3; i++, r++) {
                        *r += data[i] / 360;
                        *r %= 4096;
                    }
                    data += 3;
                }
                if (flags & 4) {
                    v = param->scale;
                    s = (s16 *)data;
                    for (i = 0; i < 3; i++) {
                        *v = s[i] * *v / 4096;
                        v++;
                    }
                    data += 2;
                }
                if (flags & 8) {
                    v = &param->trans.x;
                    for (i = 0; i < 3; i++) {
                        *v += data[i];
                        v++;
                    }
                    part->coord->coord.t = param->trans;
                }
            } else {
                if (flags & 2) {
                    r = param->rotate.axis;
                    for (i = 0; i < 3; i++) {
                        *r = data[i] / 360;
                        r++;
                    }
                    data += 3;
                }
                if (flags & 4) {
                    v = param->scale;
                    s = (s16 *)data;
                    for (i = 0; i < 3; i++) {
                        *v = s[i];
                        v++;
                    }
                    data += 2;
                }
                if (flags & 8) {
                    v = &param->trans.x;
                    for (i = 0; i < 3; i++) {
                        *v = data[i];
                        v++;
                    }
                    part->coord->coord.t = param->trans;
                }
            }
            break;
        case 2:
            if (*(u16 *)data != 0 && part->model == NULL) {
                SceneNode_LinkModel(part, model->file->tmd->vtbl->getModel(model->file->tmd, *(u16 *)data - 1));
            }
            break;
        case 3:
            if (data[0] == 0 || data[0] == 0xFFFF) {
                part->vtbl->attach(part, model, 0);
            } else {
                part->vtbl->attach(part, model->parts[Model_FindPart(model, data[0])], 0);
            }
            break;
        }
    }
    return command + size * 4;
}

/* Slot 0x13C: the model and the target watch each other; the target is kept at +0x94. */
void Model_SetTarget(Model *model, Model *target) {
    if (target != NULL) {
        target->vt->watch(target, model);
        model->vt->watch(model, target);
        model->target = target;
    }
}

void Model_ClearTarget(Model *model) {
    Model *target;

    target = model->target;
    if (target != NULL) {
        target->vt->unwatch(target, model);
        model->vt->unwatch(model, model->target);
        model->target = NULL;
    }
}

ModelBaseVtbl *Model_GetVtbl(void) {
    return &g_modelVtbl;
}

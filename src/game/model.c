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


static s32 Model_LoadFile();
static void Model_FreeFile();
static s32 Model_BuildParts(Model *model);
static void Model_ReleaseParts(Model *model);
static void Model_ReleaseParts(Model *model);
extern ModelVtbl g_modelVtbl;

Model *Model_New(ModelSource *source, SoundBank *soundBank) {
    Model *model;

    model = Heap_Alloc(0x98);
    if (model != NULL) {
        if (Model_GetVtbl()->init(model, source, soundBank) == 0) {
            Heap_Free(model);
            return NULL;
        }
        return model;
    }
    return NULL;
}

void *Model_Construct(Model *model, ModelSource *source, SoundBank *soundBank) {
    if (Actor_GetVtbl()->init(model) != 0) {
        model->vtbl = Model_GetVtbl();
        model->soundBank = soundBank;
        model->file = 0;
        model->part = 0;
        model->parts = 0;
        model->target = 0;
        if (model->vtbl->load(model, source) == 0) {
            model->vtbl->watch(model, model->file);
            model->vtbl->reset(model);
            return model;
        }
        Actor_GetVtbl()->destroy(model);
        return 0;
    }
    return 0;
}

void Model_Destruct(Model *model) {
    model->vtbl->unload(model);
    Actor_GetVtbl()->destroy(model);
}

/* Slot 0x38: when the file it borrows (class id 0x5F03) is destroyed (message 1), the model deletes itself. */
void Model_OnNotify(Model *model, u16 **sender, s32 message) {
    Actor_GetVtbl()->onNotify(model, sender, message);
    if ((**sender == 0x5F03) && (message == 1) && (model->ownsFile == 0)) {
        model->vtbl->delete_(model);
    }
}

void Model_Init(Model *model) {
    SceneNode *part;

    Actor_GetVtbl()->setVisible(model, 0);
    model->vtbl->setForwardContact(model, 1);
    model->vtbl->setSpeed(model, 0x12C);
    model->vtbl->stopTick(model);
    model->vtbl->setTickMode(model, 0x41);
    model->vtbl->stopAnimation(model);
    model->vtbl->setAnimation(model, 0);
    part = model->part;
    if (part != NULL) {
        SceneNode_LinkModel((SceneNode *)model, part->model);
    }
}

void Model_Attach(Model *model, void *target, void *watched, s32 parent, s32 child) {
    if (model->parent == 0) {
        Actor_GetVtbl()->attach(model, parent, child);
        if ((watched != 0) && (model->clock == 0)) {
            model->vtbl->watch(model, watched);
        }
        model->vtbl->setTarget(model, target);
    }
}

void Model_Detach(Model *model) {
    void *watched;

    if (model->parent != 0) {
        model->vtbl->clearTarget(model);
        watched = model->clock;
        if (watched != 0) {
            model->vtbl->unwatch(model, watched);
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
        model->vtbl->tick(model);
    }
    if (phase == 4) {
        model->vtbl->delete_(model);
    }
}

void Model_SetForwardContact(Model *model, s32 value) {
    model->forwardContact = value;
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
        return model->vtbl->createParts(model);
    }
    Model_FreeFile(model);
    return 1;
}

static void Model_FreeFile(Model *model) {
    Mom *file;

    model->vtbl->freeParts(model);
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
void Model_Tick(Model *model) {
    model->ticks = model->ticks + 1;
    if (model->tickEnabled != 0) {
        model->tickFn(model);
    }
    if ((model->animPlaying != 0) && (model->animLength >= 2)) {
        model->animData = model->vtbl->applyFrame(model, model->animData, 0);
        if (++model->animFrame >= model->animLength) {
            model->animFrame = 0;
            model->animData = model->file->motions->data.header->table.tods[model->animation]->data.bytes + 8;
        }
    }
    model->object.coord->flg = 0;
}

void Model_SetTickMode(Model *model, s32 mode) {
    switch (mode & 0xFF) {
    case 0x41:
        model->tickFn = model->vtbl->tickA;
        return;
    case 0x42:
        model->tickFn = model->vtbl->tickB;
        return;
    case 0x43:
        model->tickFn = model->vtbl->tickC;
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

    model->vtbl->moveZ(model, -0x1E, 0);
    if (model->forwardContact == 1) {
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
    model->vtbl->applyFrame(model, model->animData, 0);
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
            frame = model->vtbl->applyCommand(model, frame, context);
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
        coord = part->object.coord;
        coord->flg = 0;
        param = coord->param;
        switch (type) {
        case 0:
            part->object.attribute = (part->object.attribute & data[0]) | data[1];
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
                    part->object.coord->coord.t = param->trans;
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
                    part->object.coord->coord.t = param->trans;
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
        target->vtbl->watch(target, model);
        model->vtbl->watch(model, target);
        model->target = target;
    }
}

void Model_ClearTarget(Model *model) {
    Model *target;

    target = model->target;
    if (target != NULL) {
        target->vtbl->unwatch(target, model);
        model->vtbl->unwatch(model, model->target);
        model->target = NULL;
    }
}

ModelVtbl *Model_GetVtbl(void) {
    return &g_modelVtbl;
}

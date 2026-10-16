#include "common.h"
#include "game/entity.h"
#include "game/sound.h"
#include "game/scene.h"

/*
 * Behaviour handlers (record +0xC, the second half of this unit) and the model base class.
 * A handler runs once per tick as handler(entity, node): Entity_StartHandler registers it in the
 * node at Entity +0x9C (HandlerNode_Start) and slot 0x11C (Entity_RunHandler) runs HandlerNode_Run, which
 * calls the handler, then plays the sounds the handler asked for on the entity's sound bank (+0x58).
 */

/* The animations of a model file (+0x30): animation i is anims->list->entries[i]->data. */
typedef struct ModelAnimData {
    u8 pad_00[0x4];
    s32 frameCount; /* 0x04 */
    /* 0x08 the first frame: u16 command count at +2, commands from +8 (Model_ApplyFrame) */
} ModelAnimData;

typedef struct ModelAnimEntry {
    u8 pad_00[0x10];
    ModelAnimData *data; /* 0x10 */
} ModelAnimEntry;

typedef struct ModelAnimList {
    u8 pad_00[0x8];
    ModelAnimEntry *entries[1]; /* 0x08 */
} ModelAnimList;

typedef struct ModelAnimSet {
    u8 pad_00[0x10];
    ModelAnimList *list; /* 0x10 */
} ModelAnimSet;

/* The object at +0x2C of a model file: frame command 2 asks its slot 0x80 for a texture. */
typedef struct ModelTexturesVtbl {
    u8 pad_00[0x80];
    s32 (*unk80)(void *self, s32 index);
} ModelTexturesVtbl;

typedef struct ModelTextures {
    ModelTexturesVtbl *vt;
} ModelTextures;

/* A model's file object at +0x5C: part ids, frame commands, animations. */
typedef struct ModelFileVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(void *self);            /* 0x04 */
    u8 pad_08[0x64 - 0x08];
    void (*unk64)(void *self, void *arg1);   /* 0x64 */
    u8 pad_68[0x80 - 0x68];
    s32 (*getPartIds)();                     /* 0x80 (self, ids, &current): fills the part ids, returns their count */
    s32 *(*readCommand)();                   /* 0x84 (self, command, &part, &type, &flags, &size): a frame command's data */
} ModelFileVtbl;

typedef struct ModelFile {
    ModelFileVtbl *vt;
    u8 pad_04[0x2C - 0x04];
    ModelTextures *textures; /* 0x2C */
    ModelAnimSet *anims;     /* 0x30 */
} ModelFile;

/* An entity's position block (+0x14), as the handlers read it (entity.h Coord2). */
typedef union BehaviorPos {
    u8 *bytes;
    Coord2 *coord;
} BehaviorPos;

/*
 * The DreamSys (g_symDreamSys) as the handlers see it through Entity +0x94: the dreamer they face,
 * push and test. Slots 0x44 to 0xCC are the model base class's (ModelVtbl).
 */
typedef struct BehaviorDreamSysVtbl {
    u8 pad_00[0x44];
    void (*rotate)(void *self, s32 absolute, void *angles); /* 0x44 SceneNode_SetRotation */
    u8 pad_48[0x94 - 0x48];
    void (*unk94)(void *self, s32 arg1, s32 arg2);          /* 0x94 DreamSys_OnPad */
    u8 pad_98[0xB8 - 0x98];
    void (*setPosition)(void *self, void *pos);             /* 0xB8 Actor_SetPos */
    u8 pad_BC[0xC4 - 0xBC];
    void (*moveZ)(void *self, s32 amount, s32 animate);     /* 0xC4 Actor_MoveZ */
    void (*moveX)(void *self, s32 amount, s32 animate);     /* 0xC8 Actor_MoveX */
    void (*moveY)(void *self, s32 amount, s32 animate);     /* 0xCC Actor_MoveY */
    u8 pad_D0[0x100 - 0xD0];
    s32 (*unk100)(void *self);                              /* 0x100 DreamSys_WasCirclePressed, returns DreamSys +0x74 */
    u8 pad_104[0x130 - 0x104];
    void (*unk130)(void *self, s32 arg1);                   /* 0x130 DreamSys_StopControls */
    void (*unk134)(void *self, s32 arg1, s32 arg2);         /* 0x134 DreamSys_SetControls */
    u8 pad_138[0x1A0 - 0x138];
    s32 (*getDayNumber)(void *self, s32 *out);              /* 0x1A0 DreamSys_GetDayNumber */
    u8 pad_1A4[0x200 - 0x1A4];
    s32 (*getDreamColor)(void *self);                       /* 0x200 DreamSys_GetDreamColor */
    u8 pad_204[0x21C - 0x204];
    void (*clearFlashbacks)(void *self);                    /* 0x21C DreamSys_ClearFlashbacks */
} BehaviorDreamSysVtbl;

typedef struct BehaviorDreamSys {
    BehaviorDreamSysVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    BehaviorPos pos;         /* 0x14 */
    u8 pad_18[0x5C - 0x18];
    ModelFile *model;        /* 0x5C */
} BehaviorDreamSys;

/*
 * Entity class vtable 0x80089AD4 as the handlers call it. Slots up to 0x140 belong to the model
 * base class (vtable 0x8008A6C4, ModelVtbl); 0x144 on are entity.h's EntityVtbl.
 */
typedef struct BehaviorEntityVtbl {
    u8 pad_00[0x30];
    void (*postEvent)(void *self, s32 event);                /* 0x30 entity event: 10 link, 11 video end, 12 end */
    u8 pad_34[0x44 - 0x34];
    void (*rotate)(void *self, s32 absolute, void *angles);  /* 0x44 SceneNode_SetRotation: degrees as {num, den} s16 pairs */
    void (*scale)(void *self, s32 absolute, void *factors);  /* 0x48 SceneNode_SetScale: {num, den} s16 pairs */
    u8 pad_4C[0x60 - 0x4C];
    void (*unk60)(void *self, s32 arg1);                     /* 0x60 Model_SetVisible, 1 on wake, 0 on sleep */
    u8 pad_64[0xB8 - 0x64];
    void (*setPosition)(void *self, void *pos);              /* 0xB8 Actor_SetPos */
    void (*move)(void *self, void *delta);                   /* 0xBC Actor_MovePos: adds a world vector to the position */
    u8 pad_C0[0xC4 - 0xC0];
    void (*moveZ)(void *self, s32 amount, s32 animate);      /* 0xC4 Actor_MoveZ: along the model's own z axis */
    void (*moveX)();                                         /* 0xC8 Actor_MoveX (self, amount, animate): own x axis */
    void (*moveY)(void *self, s32 amount, s32 animate);      /* 0xCC Actor_MoveY: own y axis, negative is up */
    void (*moveZOnGround)(void *self, s32 amount, s32 animate); /* 0xD0 Actor_MoveZOnGround: moveZ, then the ground test Actor_SnapToGround */
    u8 pad_D4[0x128 - 0xD4];
    void (*setAnimation)(void *self, s32 animation);         /* 0x128 Model_SetAnimation */
    void (*playAnimation)(void *self);                       /* 0x12C Model_PlayAnimation */
    void (*stopAnimation)(void *self);                       /* 0x130 Model_StopAnimation */
    u8 *(*applyFrame)(void *self, u8 *frame, void *arg2);    /* 0x134 Model_ApplyFrame: runs one frame's commands, returns the next frame */
    u8 pad_138[0x144 - 0x138];
    s32 (*distanceTo)();                                     /* 0x144 Entity_GroundDistance */
    s32 (*getSoundFade)(void *self);                         /* 0x148 Entity_GetSoundFade */
    u8 pad_14C[0x15C - 0x14C];
    void (*wake)(void *self);                                /* 0x15C Entity_Wake */
    void (*sleep)(void *self);                               /* 0x160 Entity_Sleep */
    u8 pad_164[0x168 - 0x164];
    void (*startHandler)(void *self);                        /* 0x168 Entity_StartHandler */
    void (*stopHandler)(void *self);                         /* 0x16C Entity_StopHandler */
} BehaviorEntityVtbl;

/* The object at Entity +0x4C (the map the entity stands on: Actor_SnapToGround asks its slot 0x110 for the ground). */
typedef struct BehaviorMapVtbl {
    u8 pad_00[0x138];
    void (*unk138)(void *self, s32 arg1, s32 arg2);
} BehaviorMapVtbl;

typedef struct BehaviorMap {
    BehaviorMapVtbl *vt;
} BehaviorMap;

/* A part of a model (one per object of its TMD, made by Actor_New). */
typedef struct ModelPartVtbl {
    u8 pad_00[0x4];
    void *(*delete_)(void *self);                         /* 0x04 */
    u8 pad_08[0x4C - 0x08];
    void (*attach)(void *self, void *parent, s32 arg2);   /* 0x4C */
    u8 pad_50[0x60 - 0x50];
    void (*unk60)(void *self, s32 arg1);                  /* 0x60 */
    u8 pad_64[0x70 - 0x64];
    void (*unk70)(void *self, s32 arg1);                  /* 0x70 */
    u8 pad_74[0x88 - 0x74];
    void (*unk88)(void *self, s32 arg1);                  /* 0x88 */
} ModelPartVtbl;

typedef struct ModelPart {
    ModelPartVtbl *vt;
    u8 pad_04[0x10 - 0x04];
    s32 flags;              /* 0x10 frame command 0 masks and sets it */
    Coord2 *coord;      /* 0x14 */
    u8 pad_18[0x20 - 0x18];
    s32 unk20;              /* 0x20 frame command 2 gives it a texture only while it is 0 */
} ModelPart;

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
    void (*unk60)();      /* 0x60 */
    u8 pad_64[0x70 - 0x64];
    void (*unk70)();      /* 0x70 */
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
    s32 (*construct)(void *self, s32 arg1, s32 arg2);      /* 0x08 Model_Construct */
    u8 pad_0C[0x10 - 0x0C];
    void (*watch)(void *self, void *other);                /* 0x10 */
    void (*unwatch)(void *self, void *other);              /* 0x14 */
    u8 pad_18[0x40 - 0x18];
    void (*init)(void *self);                              /* 0x40 Model_Init */
    u8 pad_44[0xC4 - 0x44];
    void (*moveZ)(void *self, s32 amount, s32 animate);    /* 0xC4 Actor_MoveZ */
    u8 pad_C8[0xE4 - 0xC8];
    void (*unkE4)(void *self, s32 arg1);                   /* 0xE4 Actor_SetSpeed */
    u8 pad_E8[0xF0 - 0xE8];
    void (*setUnk64)(void *self, s32 value);               /* 0xF0 func_80065BF4 */
    s32 (*load)(void *self, s32 arg1);                     /* 0xF4 Model_Load */
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
    u8 *(*applyFrame)(void *self, u8 *frame, void *arg2);  /* 0x134 Model_ApplyFrame */
    u8 *(*applyCommand)(void *self, u8 *command, void *arg2); /* 0x138 Model_ApplyCommand */
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
    void *unk50;               /* 0x50 watched while attached */
    u8 pad_54[0x58 - 0x54];
    struct SoundBank *soundBank; /* 0x58 */
    ModelFile *file;           /* 0x5C */
    s32 ownsFile;              /* 0x60 1 when the file was loaded here, 0 when borrowed */
    s32 unk64;                 /* 0x64 setUnk64; 1 makes tickA play part animation 6 */
    ModelPart *part;           /* 0x68 the part the file names as current */
    s32 partCount;             /* 0x6C */
    ModelPart **parts;         /* 0x70 */
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

/* What Model_LoadFile loads a model from: a ready file object at +0xC, else what Mom_Create reads. */
typedef struct ModelSource {
    u8 pad_00[0xC];
    ModelFile *file; /* 0x0C */
} ModelSource;

/*
 * The entity (entity.h Entity, 0x108 bytes) with the model base class fields the handlers use.
 * Model fields (+0x00 to +0x94): see Model below.
 */
typedef struct BehaviorEntity {
    BehaviorEntityVtbl *vt;
    u8 pad_04[0xC - 0x4];
    s32 attached;              /* 0x0C */
    u8 pad_10[0x14 - 0x10];
    BehaviorPos pos;           /* 0x14 */
    u8 pad_18[0x24 - 0x18];
    u32 timer;                 /* 0x24 */
    s32 unk28;                 /* 0x28 result of the ground test after moveZOnGround */
    u8 pad_2C[0x44 - 0x2C];
    s32 state;                 /* 0x44 handler state; 1 stops Entity_CheckWake for good */
    s16 speed;                 /* 0x48 last amount given to moveX, moveY or moveZ (Actor_MoveAxis) */
    u8 pad_4A[0x4C - 0x4A];
    BehaviorMap *map;          /* 0x4C */
    void *unk50;               /* 0x50 */
    u8 pad_54[0x6C - 0x54];
    s32 partCount;             /* 0x6C */
    ModelPart **parts;         /* 0x70 */
    u8 pad_74[0x7C - 0x74];
    s32 animation;             /* 0x7C current animation (setAnimation) */
    s32 animLength;            /* 0x80 frames of the current animation */
    s32 animFrame;             /* 0x84 current frame, 0 to animLength - 1 */
    u8 *animData;              /* 0x88 the next frame's commands (applyFrame) */
    s32 tickEnabled;           /* 0x8C */
    s32 animPlaying;           /* 0x90 playAnimation sets it, stopAnimation clears it */
    BehaviorDreamSys *dreamSys; /* 0x94 */
    s32 type;                  /* 0x98 */
    HandlerNode node;          /* 0x9C */
    s32 awake;                 /* 0xF0 */
    s32 touched;               /* 0xF4 */
    s32 handlerActive;         /* 0xF8 */
    s32 handlerTicks;          /* 0xFC */
    Fade *effect;    /* 0x100 */
} BehaviorEntity;

extern void Object_DeleteArray(void *, s32);
extern EntityRecord g_entityRecords[];
extern void Behavior_Type51();
void Actor_ApplyPos(void *arg0, s32 arg1, s32 *arg2);
extern s8 g_entityRecordVideo[];
extern void Scenery_CreateSpriteParts(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void Place_CheckTextureLoad(void *, void *);
s32 Model_LoadFile();
extern void Model_FreeFile();
s32 Model_BuildParts(Model *model);
void Model_ReleaseParts(Model *model);
void HandlerNode_Stop(void *, void *);
extern s32 g_scaleHalf;
extern s32 g_scaleSix;
extern s32 g_scaleQuarter;
extern s8 g_entityRecordPoints[];
void Link_SetExtraListOn(s32 arg0);
extern s8 g_entityRecordLink[];
extern void HandlerNode_Run(s32, void *);
extern void Behavior_Type71();
typedef struct Unk_8005CD58_Vtbl {
    u8 pad_00[0x200];
    s32 (*unk200)(void *);
} Unk_8005CD58_Vtbl;
typedef struct Unk_8005CD58 {
    Unk_8005CD58_Vtbl *vt;
} Unk_8005CD58;
Unk_8005CD58 *g_symDreamSys;
extern s8 g_ruleColors[];
ModelParentVtbl *Actor_GetVtbl(void);
extern s32 g_scaleDouble[];
extern s32 g_moveYNeg64[];
typedef struct Unk_8005C5E8_Vtbl {
    u8 pad0[0x4];
    void *(*unk4)(void *);
} Unk_8005C5E8_Vtbl;
typedef struct Unk_8005C5E8_Obj {
    Unk_8005C5E8_Vtbl *vt;
} Unk_8005C5E8_Obj;
/* g_spyModel: the model loaded from ETC\SYMSPY.MOM and the Grey Man entity built on it */
typedef struct SpyModel {
    Unk_8005C5E8_Obj *model;
    Entity *spy;
    s32 unk8;
    u8 pad_0C[0x8];
} SpyModel;
extern SpyModel g_spyModel[];
typedef struct Unk_8005C76C_Vt {
    u8 pad[4];
    void *(*fn4)(void *);
} Unk_8005C76C_Vt;
typedef struct Unk_8005C76C {
    Unk_8005C76C_Vt *vt;
} Unk_8005C76C;
typedef struct Unk_8005C76C_Entry {
    Unk_8005C76C *obj;
    u8 pad[0x14 - 4];
} Unk_8005C76C_Entry;
extern Unk_8005C76C_Entry g_spyEntity[];
typedef struct Unk_80066818_Vtbl {
    u8 pad[0x8];
    s32 (*unk8)(void *, s32, s32);
    void (*unkC)(void *);
    u8 pad1[0x4C - 0x10];
    void (*unk4C)(void *, void *, void *, s32, s32);
    void (*unk50)(void *);
    u8 pad2[0xE0 - 0x54];
    void (*unkE0)(void *, void *, s32);
} Unk_80066818_Vtbl;
Unk_80066818_Vtbl *Model_GetVtbl(void);
extern s32 rand(void);
s32 g_currentStage;
extern void Entity_FaceDreamer(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 g_scaleTiny;
typedef struct Unk_80065CEC_Obj_Vtbl {
    u8 pad[0x4];
    void *(*unk4)(void *);
} Unk_80065CEC_Obj_Vtbl;
typedef struct Unk_80065CEC_Obj {
    Unk_80065CEC_Obj_Vtbl *vt;
} Unk_80065CEC_Obj;
extern s8 g_spawnSlotCounts[];
extern s16 *g_spawnSlots[];
s32 Sym_PickSlotVariant(s32 arg0, s32 arg1);
s32 Entity_Create(s32 arg0, s32 arg1, s32 arg2);
extern void Sym_InitExtraList(s32);
s32 g_symMap;
s32 g_symSoundBank;
s32 D_8008AC08;
extern s32 HandlerNode_Start(s32, void *, s32, void *, s32);
extern s32 g_entityRecordHandler[];
s32 Entity_IsDreamerNear();
EntityVtbl *Entity_GetVtbl(void);
s32 Heap_Alloc(s32);
void *Heap_Free();
typedef struct Unk_80065C5C {
    u8 pad[0xC];
    Unk_80065CEC_Obj *unkC;
} Unk_80065C5C;
extern Unk_80065CEC_Obj *Mom_Create(Unk_80065C5C *arg0);
s32 Entity_IsInRange(Entity *entity, u8 *pos, s32 range, s32 param);
extern void SceneNode_LocalToWorld(void *arg0, void *arg1, void *arg2, s32 arg3);
extern s16 g_rotY9[];
extern s16 g_rotYNeg9[];
extern s32 g_moveYNeg512[];
extern s32 g_rotY180[];
extern s32 Entity_StartEffect();
void Behavior_QueueSound18And3(HandlerNode *node);
extern s32 g_rotY90;
extern s16 g_scaleShrinkStep[];
s32 Sym_FindSlot(s16 *arg0);
s32 Sym_CheckDayParity(s32 dayNumber, SpawnSlot *slot);
s32 Sym_SpawnSlot(s32 dayNumber, SpawnSlot *slot, s32 square);
void Sym_SpawnSpy(SpyModel *spyModel);
extern s32 Mml_Create(s32 arg0);
extern s32 Sym_SpawnGroup();
extern void *g_spawnGroups[];
typedef struct Unk_8005D480_Fn {
    u8 pad[0x98];
    void (*unk98)(void *, void *, s32);
} Unk_8005D480_Fn;
extern s8 g_entityRecordSoundRange[];
extern s32 g_scaleTallTwo;
extern s16 g_scaleWideThree[];
extern s32 g_moveZNeg256[];
extern s32 g_rotY2[];
void SceneNode_LinkModel(void *, s32);
extern s32 g_rotY4[];
extern s32 g_scaleTwoFifths[];
extern s8 g_rotXEighth[];
void Behavior_RollWideOrSlide(BehaviorEntity *entity);
typedef struct Unk_8005D560_Fn {
    u8 pad[0xDC];
    void (*unkDC)(void *, void *, s32);
} Unk_8005D560_Fn;
extern s32 g_rotY1;
extern s32 g_scaleTriple;
struct Unk_80026CE8 {
    s32 unk0;
    char *unk4;
    s32 unk8;
};
struct Unk_80026CE8 *File_MakeSource(struct Unk_80026CE8 *arg0, s32 arg1, char *arg2, s32 arg3);
extern s8 g_spawnGroupCounts[];
void *Fade_Create(void *arg0, s32 arg1, s32 arg2);
extern s32 g_effectDefaultPos[];
extern s32 g_effectDefaultSize[];
extern s8 g_entityRecordWakeMode[];
extern s8 g_entityRecordHandlerRange[];
extern s32 Heap_Alloc(s32);
extern void *Actor_New(void);
extern void Model_ReleaseParts(Model *model);
extern s32 g_rotYNeg90;
extern s32 g_scaleThinTall[];
extern s16 g_scaleSquash[];
typedef struct Unk_8005CAB4_Vtbl {
    u8 pad[0x88];
    s32 (*unk88)(void *self, s32 arg1);
} Unk_8005CAB4_Vtbl;
typedef struct Unk_8005CAB4_Obj {
    Unk_8005CAB4_Vtbl *vt;
} Unk_8005CAB4_Obj;
void Sym_CheckExtraListType(s32 arg0);
s32 Sym_CheckRule(s32 dayNumber, SpawnGroup *group);
s32 Sym_SpawnAtPlace(s32 type, s32 *params, SpawnSlot *slot, s32 place);
extern s32 g_moveYNeg1500Z1024[];
extern s16 g_rotYNegHalf[];
void Behavior_TrainRun(BehaviorEntity *entity, HandlerNode *node, s32 turnTick, s32 leaveTick, s32 speed);
extern s32 g_moveYNeg4096[];
extern s32 g_moveY64[];
extern s32 g_moveXNeg64[];
void Entity_CheckLinkRadius();
extern s32 Entity_IsInRange(Entity *entity, u8 *pos, s32 range, s32 param);
s32 Ambience_IsEvenFamily(void);
s32 Sym_CheckColorRule(s32 arg0);
s32 Sym_CheckMonthRule(s32 arg0, s32 arg1);
extern u8 g_entityVtbl[];
extern u8 g_modelVtbl[];
extern s8 D_8008AC1C[];
extern s32 g_moveYNeg256[];
extern s32 g_scaleTallFour[];
extern s32 g_moveY256[];
extern s32 g_rotZ9[];
extern s32 g_moveY8[];
extern s32 g_rotYNegThird;
extern s32 g_scaleOne;
extern s32 g_scaleEighth;
extern s32 g_rotYNeg120[];
extern s32 g_astronautBarPose[];
extern s32 g_moveY64ZNeg64[];
s32 Model_FindPart(Model *model, u8 id);
extern s16 g_type41ScaleDepthDen[];
s32 Entity_IsDreamerNear(Entity *entity, s32 radius);
extern s16 g_rotZ1[];
extern s16 g_rotZNeg9[];
s32 Entity_StartEffect(Entity *entity, void *arg1, void *arg2, s32 arg3, s32 arg4);
void Behavior_QueueLowSound7(HandlerNode *node);
extern s32 g_rotZNeg90[];
typedef struct Unk_8005CDF8_C {
    u8 r, g, b, cd;
} Unk_8005CDF8_C;
typedef struct Unk_8005CDF8_Rec {
    Unk_8005CDF8_C c;
    s16 d;
} Unk_8005CDF8_Rec;
typedef struct Unk_8005CDF8 {
    u16 a;
    u16 b;
    Unk_8005CDF8_Rec rec;
} Unk_8005CDF8;
typedef struct Unk_8005CDF8_Vtbl {
    u8 pad_00[0x44];
    void (*unk44)(void *, s32, void *);
    s32 pad_48;
    void (*unk4C)(void *, void *, s32, s32, void *);
    u8 pad_50[0xE8 - 0x50];
    void (*unkE8)(void *, void *, void *);
} Unk_8005CDF8_Vtbl;
typedef struct Unk_8005CDF8_Obj {
    Unk_8005CDF8_Vtbl *vt;
} Unk_8005CDF8_Obj;
extern SpawnPlace g_spawnPlaces[];
extern Unk_8005CDF8_Rec D_80088D3C[];
extern u8 g_spawnPlaceRotations[];
extern s32 g_rotX90;
s32 g_type78Stopped;
extern s32 g_scaleGrowStep[];

void Sym_LoadModels(void) {
    struct Unk_80026CE8 file;
    u32 i;
    s32 j;

    /* clear the done flag of every spawn group of every stage */
    for (i = 0; i < 14; i++) {
        for (j = 0; j < g_spawnGroupCounts[i]; j++) {
            ((u8 *)g_spawnGroups[i])[j * 8] = 0;
        }
    }
    File_MakeSource(&file, 0, "ETC\\SYMSPY.MOM", 1);
    /* one pass: SYMDOG.MOM would be the second model, the loop never reaches it */
    for (i = 0; i < 1; i++) {
        g_spyModel[i].model = (Unk_8005C5E8_Obj *)Mom_Create((Unk_80065C5C *)&file);
        file.unk4 = "ETC\\SYMDOG.MOM";
    }
}

void Sym_FreeModels(void) {
    SpyModel *entry;
    u32 i;

    entry = g_spyModel;
    for (i = 0; i < 1; i++) {
        if (entry->model != NULL) {
            entry->model = entry->model->vt->unk4(entry->model);
        }
        entry++;
    }
}

void Sym_InitStage(s32 stage, s32 arg1, Unk_8005CD58 *dreamSys, s32 arg3, s32 arg4) {
    s32 params[4];
    SpyModel *entry;
    u32 i;

    entry = g_spyModel;
    g_currentStage = stage;
    g_symMap = arg1;
    g_symDreamSys = dreamSys;
    g_symSoundBank = arg3;
    D_8008AC08 = arg4;
    /* entity type 0x62 = 98, the Grey Man */
    for (i = 0; i < 1; i++) {
        params[3] = (s32) entry->model;
        entry->spy = Entity_Create(i + 0x62, params, g_symSoundBank);
        entry++;
    }
    Sym_InitExtraList(stage);
}

void Sym_InitExtraList(s32 stage) {
    s32 extraList;

    extraList = 0;
    if ((stage == 0xB) || (stage == 3)) {
        extraList = 1;
    }
    Link_SetExtraListOn(extraList);
}

void Sym_CheckExtraListType(s32 type) {
    switch (type) {
        case 0xB:
        case 0x38:
        case 0x4E:
        case 0x5D:
            Link_SetExtraListOn(1);
            break;
    }
}

void Sym_FreeSpy(void) {
    Unk_8005C76C_Entry *entry;
    u32 i;

    for (i = 0, entry = g_spyEntity; i < 1; i++) {
        if (entry->obj != NULL) {
            entry->obj = entry->obj->vt->fn4(entry->obj);
        }
        entry++;
    }
}

s32 Sym_SpawnOrSpy(s32 square, void *chunkKey, s32 dayNumber) {
    s32 slot;

    slot = Sym_FindSlot((s16 *) chunkKey);
    if (slot != 0) {
        if (Sym_CheckDayParity(dayNumber, (SpawnSlot *) slot) != 0) {
            return Sym_SpawnSlot(dayNumber, (SpawnSlot *) slot, square);
        }
        if (g_currentStage != 0) {
            if (rand() % 12 == 0 && !(dayNumber & 1)) {
                Sym_SpawnSpy(g_spyModel);
            }
        }
    }
    return 0;
}

s32 Sym_FindSlot(s16 *chunkKey) {
    s16 *slot;
    s32 i;
    s32 count;
    s32 pad[2];

    count = g_spawnSlotCounts[g_currentStage];
    slot = g_spawnSlots[g_currentStage];
    i = 0;
    if (count > 0) {
        do {
            if (*chunkKey == *slot) {
                return Sym_PickSlotVariant((s32) slot, i);
            }
            i++;
            slot += 3;
        } while (i < count);
    }
    return 0;
}

/* Stage 4, slot 16: on a red day (colour 4) use slot 21, 30 bytes further. */
s32 Sym_PickSlotVariant(s32 slot, s32 index) {
    s32 stage = g_currentStage;

    if (stage == 4 && index == 0x10) {
        if (g_symDreamSys->vt->unk200(g_symDreamSys) == stage) {
            slot += 30;
        }
    }
    return slot;
}

s32 Sym_CheckDayParity(s32 dayNumber, SpawnSlot *slot) {
    s32 pass;
    s8 parity;

    parity = slot->dayParity;
    pass = 1;
    if (parity != 0) {
        dayNumber = (dayNumber % 2) + 1;
        pass = parity != dayNumber;
    }
    return pass;
}

s32 Sym_SpawnSlot(s32 dayNumber, SpawnSlot *slot, s32 square) {
    s32 params[4];
    s32 squareObj;
    s8 *group;
    s8 *end;
    u8 *groups;

    params[0] = square;
    squareObj = Mml_Create((s32)params);
    if (squareObj != 0) {
        group = slot->groups;
        end = slot->groups + 3;
        groups = g_spawnGroups[g_currentStage];
        while (group < end && *group != -1) {
            Sym_SpawnGroup(dayNumber, slot, groups + *group * 8, squareObj);
            group++;
        }
        return squareObj;
    }
    return 0;
}

s32 Sym_SpawnGroup(s32 dayNumber, SpawnSlot *slot, SpawnGroup *group, Unk_8005CAB4_Obj *squareObj) {
    s32 params[4];
    s8 *place;
    s8 *placesEnd;
    s32 model;

    if (Sym_CheckRule(dayNumber, group) != 0) {
        place = group->places;
        Sym_CheckExtraListType(group->type);
        model = squareObj->vt->unk88(squareObj, group->model);
        params[3] = model;
        placesEnd = group->places + 4;
        if (model != 0) {
            for (; place < placesEnd && *place != -1; place++) {
                if (Sym_SpawnAtPlace(group->type, params, slot, (u8)*place) != 0) {
                    return 1;
                }
            }
        }
        /* a type 2 group also tries the group seven entries further (0x38 bytes) */
        if (group->type == 2) {
            return Sym_SpawnGroup(dayNumber, slot, group + 7, squareObj);
        }
    }
    return 0;
}

s32 Sym_CheckRule(s32 dayNumber, SpawnGroup *group) {
    SpawnGroup *p;
    s8 rule;
    s32 n;
    s32 pass;

    p = group;
    rule = p->rule;
    if (rule == 1) {
        p->done = 1;
        return 1;
    }
    /* a negative rule passes once, until Sym_LoadModels clears the flag */
    if (rule < 0 && p->done != 0) {
        return 0;
    }
    n = rule < 0 ? ~rule + 1 : rule;
    switch (n) {
        case 2:
        case 3:
        case 4:
            pass = Sym_CheckMonthRule(dayNumber, n - 1);
            break;
        case 5:
            if (dayNumber == (dayNumber / 3) * 3) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 6:
            if (dayNumber != (dayNumber / 3) * 3) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 7:
            pass = Ambience_IsEvenFamily();
            break;
        case 8:
        case 9:
            if (dayNumber % 3 == n - 7) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 20:
            if ((dayNumber & 1) == 0) {
                p->done = 1;
                return 1;
            }
            return 0;
        case 21:
            pass = dayNumber & 1;
            break;
        default:
            if (n < 10) {
                p->done = 1;
                return 1;
            }
            pass = Sym_CheckColorRule(n);
            break;
    }
    if (pass != 0) {
        p->done = 1;
        return 1;
    }
    return 0;
}

/* Rules 10 to 17: g_ruleColors[rule] is the mood colour the day must have (DreamSys vtable 0x200). */
s32 Sym_CheckColorRule(s32 rule) {
    s32 colour;

    colour = g_ruleColors[rule];
    return colour == g_symDreamSys->vt->unk200(g_symDreamSys);
}

/* Rules 2 to 4: the 30-day month (day - 1) / 30 + 1 equals month, month + 3, + 6 or + 9. */
s32 Sym_CheckMonthRule(s32 dayNumber, s32 month) {
    s32 i;
    s32 n;

    n = ((dayNumber - 1) / 30) + 1;
    for (i = 0; i < 4; i++) {
        if (n == month) {
            return 1;
        }
        month += 3;
    }
    return 0;
}

s32 Sym_SpawnAtPlace(s32 type, s32 *params, SpawnSlot *slot, s32 place) {
    Unk_8005CDF8 query;
    s32 placement[4];
    Entity *entity;
    SpawnPlace *placeInfo;
    s32 recIndex;

    entity = (Entity *) Entity_Create(type, (s32) params, g_symSoundBank);
    if (entity != NULL) {
        query.a = *(u16 *) slot;
        placeInfo = &g_spawnPlaces[place];
        query.b = placeInfo->unk0;
        recIndex = placeInfo->unk3;
        query.rec = D_80088D3C[recIndex];
        ((Unk_8005CDF8_Obj *) g_symMap)->vt->unkE8((void *) g_symMap, placement, &query);
        entity->vt->rotate(entity, 1, &g_spawnPlaceRotations[placeInfo->unk2 * 12]);
        entity->vt->attach(entity, g_symDreamSys, D_8008AC08, g_symMap, placement);
        return 0;
    }
    return 1;
}

void Sym_SpawnSpy(SpyModel *spyModel) {
    s32 placement[4];
    Entity *spy;

    spy = spyModel->spy;
    if (spy != NULL) {
        spy->vt->detach(spy);
        SceneNode_LocalToWorld(g_symDreamSys, placement, &spyModel->unk8, 0);
        spyModel->spy->vt->attach(spyModel->spy, g_symDreamSys, D_8008AC08, g_symMap, placement);
        Entity_FaceDreamer(spyModel->spy, g_symDreamSys, 1, 0, 0);
    }
}

s32 Entity_Create(s32 type, s32 params, s32 arg2) {
    s32 mem;

    mem = Heap_Alloc(0x108);
    if (mem == 0) {
        return 0;
    }
    if (Entity_GetVtbl()->construct(mem, type, params, arg2) != 0) {
        return mem;
    }
    Heap_Free(mem);
    return 0;
}

void *Entity_Construct(Entity *entity, s32 type, s32 arg2, s32 arg3) {
    if (Model_GetVtbl()->unk8(entity, arg2, arg3) != 0) {
        entity->vt = Entity_GetVtbl();
        entity->type = type;
        entity->handlerNode.id = 0;
        entity->effect = 0;
        entity->unk104 = 0;
        ((EntityVtbl *)entity->vt)->init(entity);
        return entity;
    }
    return NULL;
}

s32 Entity_StartEffect(Entity *entity, void *arg1, void *arg2, s32 arg3, s32 arg4) {
    Fade *effect;

    if (entity->effect == NULL) {
        if (arg1 == NULL) {
            arg1 = g_effectDefaultSize;
        }
        effect = Fade_Create(arg1, 0, arg4);
        if (effect == NULL) {
            return 0;
        }
        entity->effect = effect;
    } else {
        effect = entity->effect;
    }
    effect->vtbl->hide(effect);
    effect->vtbl->show(effect, entity, arg2 ? arg2 : g_effectDefaultPos);
    effect->vtbl->setStep(effect, arg3);
    return (s32)effect;
}

void Entity_Destruct(Entity *entity) {
    Fade *effect;

    effect = entity->effect;
    if (effect != NULL) {
        effect->vtbl->delete_(effect);
    }
    effect = entity->unk104;
    if (effect != NULL) {
        effect->vtbl->delete_(effect);
    }
    Model_GetVtbl()->unkC(entity);
}

void Entity_Init(Entity *entity) {
    /* record points byte (+2) of 1 to 9 */
    if ((u8)g_entityRecordPoints[entity->type * 16] - 1U < 9) {
        entity->vt->unk70(entity, 1);
    }
    entity->vt->setTickMode(entity, 0x42);
    entity->vt->sleep(entity);
}

void Entity_Attach(Entity *entity, void *dreamSys, void *arg2, s32 arg3, s32 arg4) {
    if (entity->attached == 0) {
        Model_GetVtbl()->unk4C(entity, dreamSys, arg2, arg3, arg4);
        entity->map = arg3;
        /* record +3 wake mode 0: awake at spawn; +0xB handler range 0: handler from the start */
        if (g_entityRecordWakeMode[entity->type * 16] == 0) {
            entity->vt->wake(entity);
            if (g_entityRecordHandlerRange[entity->type * 16] == 0) {
                entity->vt->startHandler(entity);
            }
        }
    }
}

void Entity_Detach(Entity *entity) {
    if (entity->attached != 0) {
        entity->vt->sleep(entity);
        Model_GetVtbl()->unk50(entity);
        entity->map = 0;
    }
}

void Entity_Update(Entity *entity, void *arg1, s32 arg2) {
    if (entity->vt->checkWake(entity) != 0) {
        entity->vt->checkSleep(entity);
    }
    if (entity->vt->checkHandlerStart(entity) != 0) {
        entity->vt->checkHandlerStop(entity);
    }
    entity->vt->checkTouch(entity);
    ((Unk_8005D480_Fn *)Model_GetVtbl())->unk98(entity, arg1, arg2);
}

void Entity_OnActorTouch(Entity *entity, void *arg1, s32 message) {
    s32 link;

    /* record +7 link */
    link = g_entityRecordLink[entity->type * 16];
    if (message < 2 || message >= 9 || link > 0) {
        ((Unk_8005D560_Fn *)Model_GetVtbl())->unkDC(entity, arg1, message);
        /* entity events: 10 link, 11 end with the record's video (+8), 12 end; link 0x7F ends the dream */
        if (message == 4 && link > 0) {
            if (link != 0x7F) {
                message = 0xA;
            } else {
                message = 0xC;
                if (g_entityRecordVideo[entity->type * 16] != 0) {
                    message = 0xB;
                }
            }
            entity->vt->postEvent(entity, message);
        }
    }
}

void Entity_OnWallTouch(Entity *entity, void *arg1, s32 message) {
    Model_GetVtbl()->unkE0(entity, arg1, message);
    if (message == 4) {
        entity->vt->sleep(entity);
    }
}

void Entity_RunHandler(Entity *entity) {
    HandlerNode_Run(entity->soundBank, &entity->handlerNode);
    entity->handlerTicks++;
}

/* Is pos within range << 11 of the dreamer; the record's points byte (+2), when -9 to -1, raises the tested height by points * 1024. */
s32 Entity_IsInRange(Entity *entity, u8 *pos, s32 range, s32 param) {
    Vec3 point;
    u8 points;

    point = *(Vec3 *)pos;
    points = *(u8 *)(g_entityRecordPoints + (entity->type * 0x10));
    if ((u32)((points + 9) & 0xFF) < 9U) {
        point.y += (s32)(points << 0x18) >> 0xE;
    }
    if (param < 0) {
        param = 0x800 / (s32)(~param + 1);
    } else {
        param = param << 0xB;
    }
    return entity->dreamSys->vt->unk120(entity->dreamSys, 0, range << 0xB, &point, param);
}

/* Ground distance |dx| + |dz| from this entity to the position copy of other. */
s32 Entity_GroundDistance(Entity *entity, Entity *other) {
    Vec3 *otherPos;
    Coord2 *block;
    s32 dz;
    s32 dx;
    s32 dist;

    otherPos = NULL;
    if (other->attached != 0) {
        otherPos = (Vec3 *)(other->pos.bytes + 0x38);
    }
    block = entity->pos.coord;
    dx = block->coord.t.x - otherPos->x;
    if (dx < 0) {
        dx = ~dx + 1;
    }
    dz = block->coord.t.z - otherPos->z;
    if (dz >= 0) {
        dist = dx + dz;
    } else {
        dist = dx - dz;
    }
    return dist;
}

s32 Entity_GetSoundFade(Entity *entity) {
    s32 dist;
    s32 range;

    if (entity->dreamSys != NULL) {
        dist = entity->vt->distanceTo(entity, entity->dreamSys);
        range = g_entityRecordSoundRange[entity->type * 16] << 11;
        if (range >= dist) {
            return dist / (range / entity->handlerNode.fadeSteps);
        }
    }
    return -1;
}

EntityRecord *Entity_GetRecord(Entity *entity) {
    return &g_entityRecords[entity->type];
}

s32 Entity_GetPoints(Entity *entity) {
    return g_entityRecordPoints[entity->type * 16] * 1000;
}

s32 Entity_GetLinkStage(Entity *entity) {
    s8 link;

    link = g_entityRecordLink[entity->type * 16];
    if (link < 0) {
        return ~link;
    }
    return link - 1;
}

s32 Entity_GetVideo(Entity *entity) {
    return g_entityRecordVideo[entity->type * 16] - 1;
}

void Entity_Wake(Entity *entity) {
    entity->vt->unk60(entity, 1);
    entity->awake = 1;
    entity->timer = 0;
}

void Entity_Sleep(Entity *entity) {
    entity->vt->unk60(entity, 0);
    entity->vt->stopHandler(entity);
    entity->vt->setTouched(entity, 0);
    entity->awake = 0;
}

void Entity_SetTouched(Entity *entity, s32 touched) {
    if (touched != 0) {
        entity->vt->postEvent(entity, 9);
    }
    entity->touched = touched;
}

void Entity_StartHandler(Entity *entity) {
    /* register the record's handler (+0xC) */
    HandlerNode_Start(entity->soundBank, &entity->handlerNode, entity->type + 1, entity, g_entityRecordHandler[entity->type * 4]);
    entity->vt->playAnimation(entity);
    entity->vt->startTick(entity);
    entity->handlerTicks = 0;
    entity->handlerActive = 1;
}

void Entity_StopHandler(Entity *entity) {
    HandlerNode_Stop(entity->soundBank, &entity->handlerNode);
    entity->vt->stopAnimation(entity);
    entity->vt->stopTick(entity);
    entity->handlerActive = 0;
}

s32 Entity_CheckWake(Entity *entity) {
    EntityRecord *record;
    s32 wake;

    if (entity->awake == 0 && entity->state != 1) {
        wake = 0;
        record = &g_entityRecords[entity->type];
        if (record->wakeMode == 0) {
            goto done;
        }
        if (record->wakeMode == 4) {
            goto rnd;
        }
        if (record->wakeRange == 0) {
            goto done;
        }
        if (Entity_IsInRange(entity, entity->pos.bytes + 0x18, record->wakeRange, record->unk9) != 0) {
            if (record->wakeMode == 1) {
                goto set1;
            }
            if (record->wakeMode == 3) {
                goto rnd;
            }
            goto done;
        }
        if (record->wakeMode == 2) {
            wake = 1;
        }
        goto done;
rnd:
        if ((rand() & 0x7F) != 0) {
            goto done;
        }
set1:
        wake = 1;
done:
        if (wake != 0) {
            entity->vt->wake(entity);
        }
    }
    return entity->awake;
}

s32 Entity_CheckSleep(Entity *entity) {
    EntityRecord *record;
    s32 sleep;
    s32 inRange;
    u8 mode;

    if (entity->awake != 0) {
        record = &g_entityRecords[entity->type];
        Entity_CheckLinkRadius(entity, 0);
        mode = record->sleepMode;
        sleep = 0;
        if (mode != 0 && mode != 3) {
            if (mode >= 10) {
                sleep = entity->timer == (u32)(mode * 15);
            } else if (record->wakeRange != 0) {
                inRange = Entity_IsInRange(entity, entity->pos.bytes + 0x18, record->wakeRange, record->unk9);
                if (inRange != 0) {
                    if (record->sleepMode == 1) {
                        sleep = 1;
                    }
                } else if (record->sleepMode == 2) {
                    sleep = 1;
                }
            }
        }
        if (sleep != 0) {
            entity->vt->sleep(entity);
        }
    }
    return entity->awake;
}

s32 Entity_CheckTouch(Entity *entity) {
    s32 range;
    u8 *pos;
    EntityRecord *record;

    record = &g_entityRecords[entity->type];
    if (entity->awake != 0) {
        if (entity->touched == 0) {
            pos = entity->pos.bytes + 0x18;
            range = record->touchRange;
            if (range < 0) {
                range = ~range + 1;
            }
            if (Entity_IsInRange(entity, pos, range, record->unk9) != 0) {
                entity->vt->setTouched(entity, 1);
            }
        }
        if (record->touchRange < 0) {
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        }
    }
    return entity->touched;
}

s32 Entity_CheckHandlerStart(Entity *entity) {
    EntityRecord *record;
    s32 range;
    u8 *pos;

    if (entity->awake != 0) {
        if (entity->handlerActive == 0) {
            if (entity->state != 1) {
                record = &g_entityRecords[entity->type];
                range = record->handlerRange;
                if (range != 0) {
                    pos = entity->pos.bytes + 0x18;
                    if (range < 0) {
                        range = ~range + 1;
                    }
                    if (Entity_IsInRange(entity, pos, range, record->unk9) != 0) {
                        entity->vt->startHandler(entity);
                    }
                }
            }
        }
    }
    return entity->handlerActive;
}

/* With a negative link (+7), link as soon as the dreamer is within the record's +8 << 9. */
void Entity_CheckLinkRadius(Entity *entity, s32 arg1) {
    s8 radius;

    if (g_entityRecordLink[entity->type * 16] < 0) {
        radius = g_entityRecordVideo[entity->type * 16];
        if ((radius != 0) && (Entity_IsDreamerNear(entity, radius << 9) != 0)) {
            entity->vt->postEvent(entity, 0xA);
        }
    }
}

/* The dreamer is within 0x200 in height and closer than radius on the ground. */
s32 Entity_IsDreamerNear(Entity *entity, s32 radius) {
    Entity *other;
    s32 y;
    s32 my;

    other = entity->dreamSys;
    y = other->pos.coord->coord.t.y;
    my = entity->pos.coord->coord.t.y;
    if (y + 0x200 >= my && my >= y - 0x200 && entity->vt->distanceTo(entity, other, y) < radius) {
        return 1;
    }
    return 0;
}

s32 Entity_CheckHandlerStop(Entity *entity) {
    EntityRecord *record;
    s8 range;

    if (entity->awake != 0) {
        if (entity->handlerActive != 0) {
            record = &g_entityRecords[entity->type];
            range = record->handlerRange;
            if ((range < 0) && (Entity_IsInRange(entity, entity->pos.bytes + 0x18, ~range + 1, record->unk9) == 0)) {
                entity->vt->stopHandler(entity);
            }
        }
    }
    return entity->handlerActive;
}

EntityVtbl *Entity_GetVtbl(void) {
    return (EntityVtbl *)g_entityVtbl;
}

void Behavior_Astronaut(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;

    if (node->tick == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) == 5) {
            entity->state = 0x64;
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->state == 0) {
        if (node->tick % 10 == 0) {
            node->voices[0].sound = 5;
            node->voices[0].octave = -2;
        }
        if (entity->handlerTicks == 0x960) {
            entity->handlerTicks = -1;
            return;
        }
        if (entity->handlerTicks < 0x4B0) {
            entity->vt->moveZ(entity, 0x32, 0);
        } else {
            entity->vt->moveZ(entity, -0x32, 0);
        }
        return;
    }
    if (entity->handlerTicks < 0xFA) {
        if (node->tick % 10 == 0) {
            node->voices[0].sound = 5;
            node->voices[0].octave = -2;
        }
        if (entity->handlerTicks < 0x64) {
            entity->vt->moveZ(entity, 0x32, 0);
        } else if (entity->handlerTicks < 0xFA) {
            entity->vt->move(entity, g_moveY64ZNeg64);
        }
    } else {
        if (entity->handlerTicks == 0xFA) {
            entity->vt->stopAnimation(entity);
            node->voices[0].sound = -2;
            return;
        }
        if (entity->handlerTicks >= 0x105 && entity->handlerTicks < 0x238) {
            entity->vt->moveZ(entity, -0x32, 0);
            entity->vt->rotate(entity, 1, g_rotYNeg120);
            return;
        }
        if (entity->handlerTicks >= 0x239) {
            entity->vt->rotate(entity, 1, g_astronautBarPose);
        }
    }
}

void Behavior_Type1(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = 0;
    if (node->tick == 0) {
        node->voices[0].sound = 0x14;
        node->voices[1].sound = 0x14;
        node->voices[2].sound = 0x14;
        entity->dreamSys->vt->unk130(entity->dreamSys, 1);
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    entity->vt->moveZ(entity, -0x5A, 0);
    if (entity->handlerTicks == 0x1E) {
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type5(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0x17;
    }
}

void Behavior_Type7(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animFrame == entity->animLength / 2) {
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
        node->voices[1].sound = 3;
        node->voices[1].octave = -2;
    }
    if (node->tick % 90 < 3) {
        node->voices[2].sound = 6;
        node->voices[2].octave = -1;
    }
    if (entity->handlerTicks >= 0x79) {
        entity->vt->rotate(entity, 0, g_rotY2);
        entity->vt->moveZ(entity, -0x140, 0);
        return;
    }
    if (entity->handlerTicks >= 0x38 || Entity_IsInRange(entity, entity->pos.bytes + 0x18, 1, 1) != 0) {
        entity->vt->move(entity, g_moveYNeg64);
        return;
    }
    if (entity->handlerTicks >= 0xA) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        entity->vt->moveZ(entity, -0x100, 0);
        return;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_PurpleBeast(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, g_scaleDouble);
    entity->vt->move(entity, g_moveYNeg64);
}

void Behavior_Type9(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type10(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = 0;
    if (node->tick == 0) {
        node->voices[0].sound = 0xB;
        node->voices[1].sound = 0xB;
        node->voices[2].sound = 0xB;
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_WalkingGeisha(BehaviorEntity *entity, HandlerNode *node) {
    void *turn;
    BehaviorDreamSys *dreamSys;

    entity->speed = -0x14;
    node->fade = entity->vt->getSoundFade(entity);
    turn = NULL;
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
        node->voices[0].octave = 1;
    }
    if (entity->state == 11) {
        if (entity->handlerTicks == 0xA8C) {
            turn = &g_rotYNeg90;
        }
        if (entity->handlerTicks == 0xC6C) {
            turn = &g_rotY90;
        }
        if (entity->handlerTicks == 0xE10) {
            turn = &g_rotYNeg90;
        }
        if (entity->handlerTicks >= 0xD5D && entity->handlerTicks < 0xDD5) {
            dreamSys = entity->dreamSys;
            if (dreamSys->vt->unk100(dreamSys) != 0) {
                entity->handlerTicks = 0;
                entity->state = 0xD;
            }
        }
    } else if (entity->state == 12) {
        if (entity->handlerTicks == 0x7BC) {
            turn = &g_rotYNeg90;
        }
    } else if (entity->state == 13) {
        entity->speed = -0x78;
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        entity->vt->scale(entity, 1, &g_scaleHalf);
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->vt->postEvent(entity, 0xB);
        }
    }
    if (entity->handlerTicks == 0x618) {
        if (rand() & 1) {
            turn = &g_rotY90;
            entity->state = 0xB;
        } else {
            turn = &g_rotYNeg90;
            entity->state = 0xC;
        }
    }
    if (turn != NULL) {
        entity->vt->rotate(entity, 0, turn);
    }
    entity->vt->moveZOnGround(entity, entity->speed, 0);
    if (entity->state != 0xC && entity->unk28 != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type12(BehaviorEntity *entity) {

    if (entity->handlerTicks == 0 && !(rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->pos.coord->coord.t.y < 0x7D0) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    }
    if (entity->state == 11) {
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0xA00) {
            entity->map->vt->unk138(entity->map, 1, 1);
            entity->handlerTicks = 1;
            entity->state = 0xC;
        }
    } else if (entity->state == 12) {
        if (entity->handlerTicks++ == 300) {
            entity->vt->postEvent(entity, 0xC);
        }
    }
}

void Behavior_Type13(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0xC;
        entity->state = entity->state + 1;
    } else if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
    if (entity->state == 0x24) {
        if (rand() % 3 == 0) {
            entity->vt->postEvent(entity, 0xB);
        }
    }
}

void Behavior_Type14(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animFrame == 0xA) {
        node->voices[0].sound = 0xD;
    }
    entity->vt->moveZ(entity, -0xA, 0);
}

void Behavior_Type15(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        node->fade = 0;
        node->voices[0].sound = 0xF;
    }
}

void Behavior_Type16(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->state == 0) {
        if (entity->handlerTicks < 0x40) {
            entity->vt->moveZ(entity, -0x5A, 0);
            return;
        }
        if (entity->handlerTicks == 0x40) {
            entity->vt->rotate(entity, 0, (rand() & 1) ? &g_rotY90 : &g_rotYNeg90);
            entity->vt->move(entity, g_moveY256);
            return;
        }
        entity->vt->moveZOnGround(entity, -0x176, rand() % 2);
        return;
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks % 5 == 0) {
            entity->vt->rotate(entity, 0, &g_rotY90);
        }
        entity->vt->moveZ(entity, -0x800, 0);
        entity->vt->unk60(entity, (rand() % 7) == 0);
    }
}

void Behavior_Type17(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleHalf);
}

void Behavior_Type19(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == (node->tick / 10) * 10) {
        node->voices[0].sound = 0x11;
    }
    entity->vt->moveZ(entity, -0x100, 0);
}

void Behavior_Type20(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        if (rand() % 7 == 0) {
            entity->vt->scale(entity, 1, &g_scaleTallTwo);
        }
    }
    if (!(node->tick & 3)) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0x1C;
    }
    entity->vt->moveZ(entity, -0x64, 0);
}

void Behavior_MinotaurRickshaw(BehaviorEntity *entity, HandlerNode *node) {
    s32 phase;

    node->fade = entity->vt->getSoundFade(entity);
    phase = node->tick % (entity->animLength / 2);
    if (phase == 0) {
        node->voices[0].sound = 0xA;
    } else if (phase == 3) {
        node->voices[1].sound = 0xD;
    }
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type22(BehaviorEntity *entity) {
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type23(BehaviorEntity *entity) {
    BehaviorEntityVtbl *vt;
    s32 ticks;
    s32 speed;

    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    if (entity->touched != 0) {
        if (entity->handlerTicks >= 0x41) {
            entity->handlerTicks = 0;
        }
        if (entity->handlerTicks >= 7) {
            entity->vt->move(entity, g_moveYNeg64);
            entity->vt->moveZ(entity, 0xA, 0);
        } else {
            entity->vt->move(entity, g_moveXNeg64);
        }
        return;
    }
    ticks = entity->handlerTicks;
    if (ticks == 0) {
        entity->vt->move(entity, g_moveYNeg4096);
    } else if (ticks < 0x41) {
        entity->vt->move(entity, g_moveY64);
    } else if (ticks < 0x47) {
        entity->vt->move(entity, g_moveYNeg64);
        entity->vt->moveZ(entity, -0x1E, 0);
    } else {
        vt = entity->vt;
        if (ticks < 0x100) {
            speed = -ticks - 0x41;
        } else {
            speed = 0xFF;
        }
        vt->moveZ(entity, speed, 0);
    }
}

void Behavior_Type24(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % 15 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
    }
    entity->vt->scale(entity, 1, g_scaleDouble);
    entity->vt->rotate(entity, 0, g_rotY2);
    entity->vt->moveZ(entity, -0x200, 0);
}

void Behavior_Type25(BehaviorEntity *entity, HandlerNode *node) {
    s32 ticks;

    node->fade = 0;
    ticks = entity->handlerTicks;
    if (ticks < 0x64) {
        if (node->tick % 3 == 0) {
            node->voices[0].sound = 0x16;
            node->voices[0].octave = 1;
        }
        entity->vt->moveY(entity, -0x40, 0);
    } else if (ticks < 0x12C) {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
        node->voices[1].sound = 0xC;
        node->voices[1].octave = -1;
        node->voices[2].sound = 0xC;
        node->voices[2].octave = -1;
        entity->vt->moveY(entity, -0x100, 0);
    } else {
        entity->vt->rotate(entity, 0, g_rotXEighth);
        entity->vt->moveY(entity, -0x200, 0);
    }
}

void Behavior_Type26(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % entity->animLength == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0x1A;
    }
    entity->vt->moveZOnGround(entity, (entity->handlerTicks == 0x6E) ? -0x2D00 : -0x180, 0);
}

void Behavior_Type27(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % 70 == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x1B;
    }
    entity->vt->moveZ(entity, -0x80, 0);
    if (entity->handlerTicks < 0x64) {
        entity->vt->moveY(entity, 0x20, 0);
    } else if (entity->handlerTicks > 300) {
        entity->vt->moveY(entity, -0x20, 0);
    }
}

void Behavior_Type119(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type29(BehaviorEntity *entity) {
    BehaviorDreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) == 7) {
            entity->vt->scale(entity, 1, &g_scaleTriple);
            entity->vt->moveY(entity, -0x7800, 0);
        }
        entity->state = rand() % 5;
    }
    if (entity->state == 0) {
        entity->vt->rotate(entity, 0, &g_rotY1);
    }
}

void Behavior_Type30(BehaviorEntity *entity) {
    BehaviorDreamSys *dreamSys;
    s32 state;

    if (entity->state == 0) {
        dreamSys = entity->dreamSys;
        state = dreamSys->vt->getDreamColor(dreamSys);
        if (state == 1) {
            state = 0xB;
        } else {
            state = 0xC;
        }
        entity->state = state;
    }
    if (entity->state == 0xC) {
        entity->vt->scale(entity, 1, g_scaleDouble);
        entity->vt->moveY(entity, -0x1E, 0);
        return;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    if (entity->state == 0xB) {
        entity->vt->moveZ(entity, -0x64, 0);
        if ((u32)(entity->handlerTicks - 0x55) < 0x1E) {
            entity->vt->moveY(entity, 0x50, 0);
            return;
        }
        if (entity->handlerTicks == 0x78) {
            entity->state = 0xD;
        }
        return;
    }
    if (entity->state == 0xD) {
        entity->vt->setPosition(entity, entity->dreamSys->pos.bytes + 0x18);
        entity->vt->move(entity, g_moveYNeg1500Z1024);
    }
}

void Behavior_Type31(BehaviorEntity *entity, HandlerNode *node) {
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    entity->dreamSys->vt->unk130(entity->dreamSys, 1);
    if ((node->tick % 10) < 3) {
        node->fade = 0;
        node->voices[0].sound = 0xD;
        node->voices[1].sound = 0xD;
        node->voices[2].sound = 0xD;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->stopAnimation(entity);
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type32(BehaviorEntity *entity) {
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type33(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->touched != 0) {
        entity->vt->scale(entity, 1, &g_scaleQuarter);
    } else if (node->tick % 30 == 0) {
        node->fade = 0;
        node->voices[0].sound = 3;
    }
    entity->vt->moveZOnGround(entity, -0x1E, 0);
    if (entity->unk28 != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type34(BehaviorEntity *entity) {
    s32 ticks;

    ticks = entity->handlerTicks;
    if (ticks >= 0x190 && ticks < 0x19A) {
        entity->vt->rotate(entity, 0, g_rotY9);
    } else if ((ticks >= 0x2BC && ticks < 0x2C6) || (ticks >= 0x33E && ticks < 0x342)) {
        entity->vt->rotate(entity, 0, g_rotYNeg9);
    } else if (ticks >= 0x353) {
        entity->vt->sleep(entity);
    }
    entity->vt->moveZ(entity, (entity->handlerTicks < 0x320) ? -0x3C : -0x200, 1);
}

void Behavior_Type35(BehaviorEntity *entity) {
    s32 phase;

    phase = entity->handlerTicks % 500;
    entity->vt->moveY(entity, (entity->handlerTicks % 6 < 3) ? -0x40 : 0x40, 0);
    entity->vt->moveX(entity, (entity->handlerTicks % 12 < 6) ? -0x40 : 0x40, 0);
    entity->vt->moveZ(entity, (entity->handlerTicks % 64 < 0x20) ? -0x80 : 0x80, 0);
    if (phase < 0x20) {
        entity->vt->move(entity, g_moveYNeg64);
    } else if (phase < 0x40) {
        entity->vt->move(entity, g_moveY64);
    }
}

void Behavior_Type36(BehaviorEntity *entity) {
    if (entity->state == 0) {
        entity->vt->scale(entity, 1, (rand() & 1) ? g_scaleDouble : &g_scaleSix);
        entity->state = 0xB;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x7000) {
        entity->vt->moveZ(entity, 0x100, 0);
    }
}

void Behavior_Type37(BehaviorEntity *entity) {
    entity->vt->moveY(entity, -0x5A, 0);
}

void Behavior_OperaSinger(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick % 120 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 1;
    }
}

void Behavior_Mushroom(BehaviorEntity *entity, HandlerNode *node) {
    s32 dayRest;
    void (*fn)(void *);

    if (entity->handlerTicks == 0) {
        dayRest = entity->dreamSys->vt->getDayNumber(entity->dreamSys, 0) % 3;
        if (dayRest == 0) {
            if (rand() % 3 == 0) {
                entity->vt->scale(entity, 1, g_scaleTallFour);
            }
        } else if (dayRest == 2) {
            entity->vt->scale(entity, 1, g_scaleTallFour);
        }
    }
    if (node->tick == (node->tick / 22) * 22) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 2;
    }
    if (rand() % 12 == 0) {
        fn = entity->vt->stopAnimation;
    } else if (rand() % 6 == 0) {
        fn = entity->vt->playAnimation;
    } else {
        return;
    }
    fn(entity);
}

void Behavior_Type40(BehaviorEntity *entity, HandlerNode *node) {
    void *s2 = 0;

    if (node->tick % 7 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 3;
        node->voices[0].volume = 0x40;
        node->voices[0].endVolume = 0x40;
    }

    if (entity->handlerTicks == 0xC8) {
        s2 = &g_rotYNeg90;
    } else if (entity->handlerTicks == 0x190) {
        s2 = g_rotY180;
    } else if (entity->handlerTicks == 0x258) {
        s2 = &g_rotY90;
    } else if (entity->handlerTicks == 0x320) {
        s2 = g_rotY180;
        entity->handlerTicks = -1;
    }

    if (s2 != 0) {
        entity->vt->rotate(entity, 0, s2);
    }
    entity->vt->moveZOnGround(entity, -0x1E, 0);
    if (entity->unk28 != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type41(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        entity->state = rand() % 5 + 0xA;
    }
    if (entity->state < 0xE || entity->handlerTicks < 0x140) {
        Behavior_TrainRun(entity, node, 0xBB8, 0x1F4, -0x100);
        return;
    }
    if (entity->state == 0xE && !(entity->handlerTicks & 3)) {
        g_type41ScaleDepthDen[0] = rand() % 32 + 1;
        entity->vt->scale(entity, 1, &g_type41ScaleDepthDen[-5]);
    }
}

void Behavior_Type42(BehaviorEntity *entity, HandlerNode *node) {
    s32 sound;

    if (entity->handlerTicks < 0x14) {
        entity->vt->stopAnimation(entity);
        entity->vt->moveZ(entity, -0x1E, 0);
        return;
    }
    if (entity->handlerTicks == 0x14) {
        entity->vt->playAnimation(entity);
        sound = 5;
        node->fade = 0;
    } else {
        if (entity->handlerTicks % (entity->animLength * 3 + 0x14) != 0) {
            return;
        }
        entity->vt->stopAnimation(entity);
        sound = -2;
    }
    node->voices[0].sound = sound;
}

void Behavior_Type43(BehaviorEntity *entity, HandlerNode *node) {
    s16 *angles;
    s32 amount;

    Behavior_RollWideOrSlide(entity);
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animFrame == 0 || entity->animFrame == 0xF) {
        node->voices[0].sound = 0x12;
        node->voices[1].sound = 0x12;
    }
    if (entity->handlerTicks >= 0x141) {
        if (rand() & 1) {
            amount = -0x3C;
        } else {
            amount = 0x3C;
        }
        entity->vt->moveX(entity, amount, 0);
        if (rand() & 3) {
            angles = g_rotYNeg9;
        } else {
            angles = g_rotY9;
        }
        entity->vt->rotate(entity, 0, angles);
    }
}

void Behavior_Type44(BehaviorEntity *entity, HandlerNode *node) {
    s16 *angles;
    s32 amount;

    Behavior_RollWideOrSlide(entity);
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animFrame == 7 || entity->animFrame == 0x16) {
        node->voices[0].sound = 3;
    }
    if ((u32)(entity->handlerTicks - 0x12C) < 0x14) {
        entity->vt->moveZ(entity, -0x3C, 0);
    } else if ((u32)(entity->handlerTicks - 0x141) < 0x13) {
        entity->vt->rotate(entity, 0, g_rotYNeg9);
    } else if (entity->handlerTicks >= 0x141) {
        if (rand() & 1) {
            amount = 0x80;
        } else {
            amount = -0x80;
        }
        entity->vt->moveX(entity, amount, 1);
        if (rand() & 3) {
            angles = g_rotYNeg9;
        } else {
            angles = g_rotY9;
        }
        entity->vt->rotate(entity, 0, angles);
    }
}

void Behavior_RollWideOrSlide(BehaviorEntity *entity) {
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand() % 10;
        if (roll >= 8) {
            entity->vt->scale(entity, 1, g_scaleWideThree);
        } else if (roll >= 5) {
            entity->state = 0xA;
        }
    }
    if (entity->state == 0xA && entity->handlerTicks >= 0xC9) {
        entity->vt->move(entity, g_moveZNeg256);
    }
}

void Behavior_Type45(void) {
}

void Behavior_Flower(BehaviorEntity *entity, HandlerNode *node) {
    s32 dayRest;
    s32 roll;

    if (entity->handlerTicks == 0) {
        dayRest = entity->dreamSys->vt->getDayNumber(entity->dreamSys, 0) % 3;
        if (dayRest == 0) {
            roll = rand();
            if (roll % 3 == 0) {
                entity->vt->scale(entity, 1, &g_scaleSix);
            }
        } else if (dayRest == 1) {
            entity->vt->scale(entity, 1, &g_scaleSix);
        }
    }
    if (node->tick == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x12;
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type47(BehaviorEntity *entity) {
    if (entity->touched != 0) {
        if (entity->state == 0) {
            entity->state = 0xC;
            entity->handlerTicks = 0;
            return;
        } else if (entity->state == 0xC) {
            if (entity->handlerTicks < 0x1E) {
                if (entity->dreamSys->vt->unk100(entity->dreamSys) != 0) {
                    entity->dreamSys->vt->unk130(entity->dreamSys, 0);
                    entity->handlerTicks = 0;
                    entity->state = 0xB;
                    return;
                }
            } else {
                entity->vt->postEvent(entity, 0xB);
                entity->state = 0xA;
                return;
            }
        } else if (entity->state == 0xB) {
            if (entity->handlerTicks == 0x64) {
                entity->vt->postEvent(entity, 0xC);
                return;
            }
            entity->dreamSys->vt->moveY(entity->dreamSys, -0x64, 0);
        }
    }
}

void Behavior_FloatingLips(BehaviorEntity *entity, HandlerNode *node) {
    s32 amount;
    BehaviorEntityVtbl *vt;

    if (entity->animFrame == 0x26) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 6;
    }
    amount = 0x1E;
    vt = entity->vt;
    if ((entity->handlerTicks % 10) < 5) {
        amount = -0x1E;
    }
    vt->moveY(entity, amount, 0);
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type49(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSysVtbl *dreamSysVtbl;
    s32 state;
    s32 standPos;

    if (node->tick == 6) {
        node->fade = 0;
        node->voices[0].sound = 4;
        node->voices[1].sound = 4;
        node->voices[2].sound = 4;
    }
    if (entity->touched != 0) {
        state = entity->state;
        if (state == 0) {
            entity->state = 0xA;
            entity->handlerTicks = 0;
        } else if (state == 0xA) {
            if (entity->handlerTicks == 0xA) {
                entity->vt->postEvent(entity, 0xA);
            } else if (entity->dreamSys->vt->unk100(entity->dreamSys) != 0) {
                dreamSysVtbl = entity->dreamSys->vt;
                if (entity->attached != 0) {
                    standPos = entity->pos.bytes + 0x38;
                } else {
                    standPos = 0;
                }
                dreamSysVtbl->setPosition(entity->dreamSys, standPos);
                entity->dreamSys->vt->rotate(entity->dreamSys, 1, &g_rotYNeg90);
                entity->dreamSys->vt->unk130(entity->dreamSys, 0);
                entity->handlerTicks = 0;
                entity->state = 0xB;
            }
        } else if (state == 0xB) {
            dreamSysVtbl = entity->dreamSys->vt;
            dreamSysVtbl->setPosition(entity->dreamSys, entity->attached ? entity->pos.bytes + 0x38 : 0);
            if (entity->handlerTicks == 0x64) {
                entity->vt->postEvent(entity, 0xA);
            }
        }
    }
    entity->vt->moveZ(entity, -0x100, 0);
}

void Behavior_Type50(BehaviorEntity *entity, HandlerNode *node) {
    s32 frame;

    if (entity->handlerTicks < (entity->animLength * 5)) {
        frame = entity->animFrame;
        if ((frame == 0xF) || (frame == 0x46)) {
            node->fade = 0;
            node->voices[0].sound = 7;
            node->voices[1].sound = 7;
            node->voices[2].sound = 7;
        }
    } else {
        entity->vt->sleep(entity);
        entity->state = 1;
    }
}

void Behavior_Type51(BehaviorEntity *entity, HandlerNode *node) {
    void *turn;
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if ((roll == ((roll / 5) * 5)) && (entity->state == 0)) {
            entity->vt->scale(entity, 1, &g_scaleSix);
            entity->vt->moveY(entity, 0x320, 0);
            entity->state = 0xB;
        }
    }
    turn = NULL;
    if (node->tick == ((node->tick / 5) * 5)) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 8;
    }
    if (entity->handlerTicks == 0x5A) {
        turn = &g_rotYNeg90;
    } else if (entity->handlerTicks == 0xA0) {
        turn = &g_rotY90;
    } else if (entity->handlerTicks == 0xDC) {
        if (rand() & 1) {
            turn = g_rotY180;
        }
    }
    if (turn != NULL) {
        entity->vt->rotate(entity, 0, turn);
    }
    entity->vt->moveZ(entity, -0x50, 1);
}

void Behavior_Type52(BehaviorEntity *entity, HandlerNode *node) {
    s32 ticks;

    node->fade = entity->vt->getSoundFade(entity);
    ticks = entity->handlerTicks;
    if (ticks < 0xBC) {
        if (ticks == 0x54) {
            entity->vt->rotate(entity, 0, g_rotY180);
        }
        if (node->tick % 20 == 0) {
            node->voices[0].sound = 9;
        }
    } else if (ticks < 0xC8) {
        entity->vt->rotate(entity, 0, g_rotY9);
    } else {
        entity->vt->sleep(entity);
        node->voices[1].sound = 0x1E;
        entity->state = 1;
    }
    entity->vt->moveZOnGround(entity, -0x200, 0);
}

void Behavior_Type55(BehaviorEntity *entity, HandlerNode *node) {
    s32 frame;

    frame = entity->animFrame;
    if (entity->handlerTicks == 0) {
        if (rand() % 3 == 0) {
            entity->vt->scale(entity, 1, &g_scaleTallTwo);
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
    if (frame >= 0x20) {
        frame -= 0x20;
    }
    if ((frame == 9) || (frame == 0x11) || (frame == 0x17)) {
        node->voices[0].sound = 0x13;
        if (frame == 0x17) {
            node->voices[1].sound = 0x13;
        }
    }
}

void Behavior_Type56(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type57(BehaviorEntity *entity, HandlerNode *node) {
    Fade *effect;
    s32 frame;

    if (entity->handlerTicks == 0) {
        entity->state = rand() % 3;
        if (entity->state == 0) {
            entity->vt->stopAnimation(entity);
            entity->vt->moveY(entity, 0x1800, 0);
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->state != 0) {
        frame = entity->animFrame;
        if (frame < 0x1E) {
            node->voices[0].sound = 0xC;
            node->voices[0].octave = -1;
            return;
        }
        if (frame == 0x1E) {
            node->voices[0].sound = -2;
            return;
        }
        if (frame == 0x23) {
            node->voices[2].sound = 0x16;
            node->voices[2].octave = -2;
            return;
        }
        if (frame == 0x30) {
            if (Entity_IsInRange(entity, entity->pos.bytes + 0x18, 0xF, 0xA) != 0) {
                if (Entity_StartEffect((Entity *)entity, 0, 0, 0xA, 0) != 0) {
                    effect = entity->effect;
                    effect->vtbl->startIn(effect, entity->unk50, 4, 0);
                }
                if (rand() & 1) {
                    entity->vt->postEvent(entity, 0xB);
                    return;
                }
            }
        } else if (frame == 0x3B) {
            entity->vt->sleep(entity);
            entity->state = 1;
        }
    } else {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
        entity->vt->moveZ(entity, -0x200, 0);
        if (entity->handlerTicks >= 0x80 && entity->handlerTicks < 0x142) {
            entity->vt->moveY(entity, -0x80, 0);
            return;
        }
        if (entity->handlerTicks == 0x142) {
            entity->vt->playAnimation(entity);
            entity->state = 1;
        }
    }
}

void Behavior_Type58(BehaviorEntity *entity, HandlerNode *node) {
    s32 ticksD;
    s32 ticksE;
    BehaviorDreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        node->fade = 0;
        node->voices[0].sound = 0xC;
        if (entity->dreamSys->vt->getDreamColor(entity->dreamSys) == 6) {
            entity->state = 0xB;
        } else if (rand() % 3 == 0) {
            entity->state = 0xC;
        }
    }
    if (node->tick % 100 == 0) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
    }
    if (entity->state == 0xB) {
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->dreamSys->vt->unk130(entity->dreamSys, 0);
            entity->state = 0xD;
            entity->handlerTicks = 0;
        }
    } else if (entity->state == 0xC) {
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
            entity->vt->stopAnimation(entity);
            entity->state = 0xE;
            entity->handlerTicks = 0;
        }
    }
    if (entity->state == 0xD) {
        ticksD = entity->handlerTicks;
        if (ticksD < 0x32) {
            entity->dreamSys->vt->moveY(entity->dreamSys, -0x14, 0);
        } else if (ticksD < 0x1F4) {
            dreamSys = entity->dreamSys;
            dreamSys->vt->moveX(dreamSys, ticksD % 40 < 0x14 ? -5 : 5, 0);
        } else if (ticksD == 0x1F4) {
            entity->vt->postEvent(entity, 0xC);
        }
    }
    if (entity->state == 0xE) {
        ticksE = entity->handlerTicks;
        if (ticksE < 0xA) {
            entity->vt->moveY(entity, 0xC8, 0);
            return;
        }
        if (ticksE == 0xA) {
            node->voices[0].sound = 0x12;
            node->fade = 0;
            node->voices[1].sound = 3;
            entity->vt->rotate(entity, 1, g_rotZNeg90);
            entity->vt->moveX(entity, 0x960, 0);
            entity->vt->moveY(entity, 0x5DC, 0);
            entity->parts[1]->vt->unk60(entity->parts[1], 0);
            entity->state = 1;
        }
    }
}

void Behavior_Type115(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    s32 ticks;

    if (entity->state == 0 && Entity_IsDreamerNear((Entity *)entity, 0x800) != 0) {
        entity->state = 0xB;
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        Entity_FaceDreamer(entity->dreamSys, entity, 1, 1, 0);
        entity->vt->wake(entity);
        entity->vt->startHandler(entity);
        dreamSys = entity->dreamSys;
        dreamSys->vt->unk130(dreamSys, 1);
        node->fade = 0;
        node->voices[0].sound = 0xC;
        entity->handlerTicks = 0;
    }
    if (entity->state == 0) {
        entity->vt->sleep(entity);
        entity->vt->stopHandler(entity);
    } else {
        if (node->tick % 100 == 0) {
            node->fade = entity->vt->getSoundFade(entity);
            node->voices[0].sound = 0xC;
            node->voices[0].octave = -1;
        }
        ticks = entity->handlerTicks;
        if (ticks < 3) {
            entity->vt->moveY(entity, 0x96, 0);
        } else if (ticks < 7) {
            entity->vt->moveY(entity, (ticks & 1) ? -0x32 : 0x32, 0);
        } else if (ticks == 0x64) {
            if (rand() & 1) {
                entity->state = 0xC;
                entity->vt->stopAnimation(entity);
            }
        } else if (ticks == 0xF0) {
            dreamSys = entity->dreamSys;
            dreamSys->vt->unk134(dreamSys, 1, 1);
        }
        if (entity->state == 0xC) {
            ticks = entity->handlerTicks;
            if (ticks < 0x82) {
                entity->vt->moveY(entity, 0xA, 0);
            } else if (ticks < 0xA0) {
                entity->vt->moveZ(entity, -0x1E, 0);
            } else if (ticks >= 0x12D) {
                Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
                entity->vt->moveZ(entity, -0x1E, 0);
            }
        }
    }
    if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x200) {
        entity->vt->sleep(entity);
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type59(BehaviorEntity *entity, HandlerNode *node) {
    s32 roll;
    BehaviorMap *map;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if (roll == ((roll / 10) * 10)) {
            entity->state = 0xC;
        }
    }
    if (node->tick == ((node->tick / 10) * 10)) {
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -1;
    }
    if (entity->handlerTicks == 0) {
        if (rand() & 1) {
            entity->vt->moveY(entity, 0x800, 0);
        }
    }
    entity->vt->moveZ(entity, -0x80, 0);
    if ((entity->state == 0xC) && (entity->handlerTicks == 0x12C)) {
        map = entity->map;
        map->vt->unk138(map, 1, 1);
    }
}

void Behavior_Type61(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->animFrame == 0x1E) {
        node->voices[0].sound = 0x12;
        node->fade = 0;
        node->voices[0].octave = -1;
    }
}

void Behavior_Type62(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    BehaviorMap *map;
    s32 state;

    if (entity->animFrame % 30 == 0) {
        node->voices[0].sound = 3;
        node->fade = 0;
        node->voices[0].octave = -2;
    }
    if (entity->handlerTicks >= 0x65) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    }
    entity->vt->moveZ(entity, -5, 0);
    if (entity->handlerTicks == 0x12C && entity->vt->distanceTo(entity, entity->dreamSys) < 0x1000) {
        dreamSys = entity->dreamSys;
        dreamSys->vt->unk130(dreamSys, 0);
    } else if (entity->handlerTicks == 0x1F4) {
        dreamSys = entity->dreamSys;
        dreamSys->vt->unk134(dreamSys, 1, 1);
    }
    if (entity->state == 0 && entity->vt->distanceTo(entity, entity->dreamSys) < 0x400) {
        if (rand() & 1) {
            node->voices[1].sound = 6;
            node->fade = 0;
            node->voices[1].octave = -1;
            if (rand() & 1) {
                map = entity->map;
                map->vt->unk138(map, -1, 0);
            }
            state = 0xA;
            entity->handlerTicks = 0;
        } else {
            state = 0xB;
        }
        entity->state = state;
    }
    if (entity->state == 0xA && entity->handlerTicks == 0x46) {
        entity->vt->postEvent(entity, (rand() & 1) ? 0xC : 0xB);
    }
}

void Behavior_Type64(BehaviorEntity *entity, HandlerNode *node) {
    s32 phase;

    phase = node->tick % 300;
    node->fade = entity->vt->getSoundFade(entity);
    if (phase < 0x14) {
        node->voices[0].sound = 5;
        node->voices[0].octave = -2;
    } else if (phase == 0x16) {
        node->voices[0].sound = -2;
    }
    entity->vt->moveZ(entity, -0xA, 0);
}

void Behavior_Type65(BehaviorEntity *entity) {
    s32 roll;

    if (entity->handlerTicks == 0) {
        roll = rand();
        if (roll % 3 == 0) {
            entity->vt->scale(entity, 1, &g_scaleHalf);
            entity->vt->moveY(entity, -0x12C, 0);
            entity->vt->rotate(entity, 1, &g_rotY90);
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0x7D0) {
            entity->vt->rotate(entity, 0, &g_rotYNeg90);
        }
        entity->vt->moveZ(entity, -0x14, 0);
    }
}

void Behavior_Type66(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == ((node->tick / 30) * 30)) {
        node->voices[0].sound = 0xD;
    }
}

void Behavior_Type67(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        if (rand() % 3 == 0) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0x1F6) {
            entity->vt->moveY(entity, 0x800, 0);
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        }
        if (entity->handlerTicks >= 0x1F5) {
            entity->vt->moveZ(entity, -0x200, 0);
        }
    }
}

void Behavior_Type68(BehaviorEntity *entity, HandlerNode *node) {
    s16 speed;
    s32 bit;

    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        speed = (rand() & 1) ? -0x176 : -0xC0;
        entity->speed = speed;
    }
    if (entity->state == 0) {
        if (node->tick % 10 == 0) {
            node->voices[0].sound = 0x1C;
        }
        if (node->tick % 20 == 0) {
            node->voices[1].sound = 0x17;
            node->voices[1].octave = -1;
            node->voices[2].sound = 0x17;
            node->voices[2].octave = -1;
        } else if (node->tick % 20 == 0xE) {
            node->voices[1].sound = -2;
            node->voices[2].sound = -2;
        }
        if (!(entity->handlerTicks & 1)) {
            if (entity->dreamSys->vt->unk100(entity->dreamSys) != 0) {
                entity->handlerTicks = -1;
                entity->state = 10;
                node->voices[0].sound = 0x12;
            }
        }
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        entity->vt->moveZ(entity, entity->speed, 1);
        return;
    } else if (entity->state == 10) {
        if (entity->handlerTicks < 8) {
            entity->vt->rotate(entity, 0, g_rotZ9);
            entity->vt->move(entity, g_moveY8);
            return;
        }
        node->voices[0].sound = 0x12;
        node->voices[1].sound = 3;
        entity->vt->stopHandler(entity);
        bit = rand() & 1;
        entity->state = bit == 0;
        return;
    }
}

void Behavior_Type69(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animFrame == entity->animLength - 1) {
        node->voices[0].sound = 0x19;
        node->voices[0].octave = -2;
    }
    if ((node->tick & 3) == 0) {
        node->voices[1].sound = 0x15;
        node->voices[1].octave = -1;
    }
    if (node->tick % 200 == 0) {
        node->voices[2].sound = 0xD;
        node->voices[2].octave = 1;
    }
}

void Behavior_Type70(BehaviorEntity *entity) {
    s32 speed;

    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = 0xB;
    }
    if (entity->handlerTicks == 0x12C) {
        entity->vt->rotate(entity, 0, g_rotY180);
    }
    if (entity->handlerTicks < 0x258) {
        BehaviorEntityVtbl *vt = entity->vt;

        speed = 0x100;
        if (entity->state == 0) {
            speed = -0x100;
        }
        vt->moveZ(entity, speed, 0);
    }
}

void Behavior_Type71(BehaviorEntity *entity, HandlerNode *node) {
    s32 roll;

    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0;
        roll = rand() % 3;
        entity->vt->moveX(entity, roll * 0xC800, 0, roll);
    }
    if (entity->handlerTicks >= 0x961) {
        Entity_FaceDreamer(entity, (void *)entity->dreamSys, 1, 0, 0);
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type73(BehaviorEntity *entity, HandlerNode *node) {
    s32 tick;

    tick = node->tick;
    node->fade = 0;
    if (tick == 0) {
        entity->dreamSys->vt->rotate(entity->dreamSys, 1, &g_rotY90);
        entity->dreamSys->vt->unk130(entity->dreamSys, 1);
        node->voices[0].sound = 0x19;
        node->voices[1].sound = 0x19;
        node->voices[2].sound = 0x19;
    } else if (tick == 0x14) {
        node->voices[1].sound = 0xD;
    }
    if (entity->handlerTicks == (entity->animLength - 1)) {
        entity->vt->sleep(entity);
    }
}

void Behavior_Type74(BehaviorEntity *entity) {
    s32 ticks;

    if (entity->handlerTicks == 0) {
        entity->dreamSys->model->vt->unk64(entity->dreamSys->model, D_8008AC1C);
        entity->state = rand() % 3;
        if (entity->dreamSys->pos.coord->coord.t.z < 0x262) {
            entity->state = 0;
        }
    }
    if (entity->state != 0) {
        if (entity->animLength / 2 < entity->handlerTicks) {
            entity->dreamSys->vt->moveZ(entity->dreamSys, 0x80, 0);
        }
        if (entity->handlerTicks == entity->animLength - 0x1E) {
            entity->vt->postEvent(entity, 0xA);
        }
    } else {
        ticks = entity->handlerTicks;
        if (ticks >= 0x14 && ticks < 0x78) {
            entity->dreamSys->vt->moveZ(entity->dreamSys, -((ticks - 0x13) << 5), 1);
            if (entity->handlerTicks == 0x55) {
                entity->dreamSys->vt->unk134(entity->dreamSys, 1, 1);
            }
        }
    }
}

void Behavior_Type75(BehaviorEntity *entity, HandlerNode *node) {
    if (node->tick == 0) {
        node->fade = 0;
        node->voices[0].sound = 0x19;
        node->voices[1].sound = 0x19;
        node->voices[2].sound = 0x19;
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->stopAnimation(entity);
        entity->vt->postEvent(entity, 0xA);
    }
}

void Behavior_Type76(BehaviorEntity *entity) {
    if (entity->touched != 0) {
        entity->vt->playAnimation(entity);
        if (entity->animFrame == entity->animLength - 1) {
            entity->vt->stopAnimation(entity);
            entity->vt->scale(entity, 0, g_scaleShrinkStep);
        }
    } else {
        entity->vt->stopAnimation(entity);
        entity->vt->rotate(entity, 0, g_rotY9);
    }
}

void Behavior_Type77(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % 5 == 0) {
        node->voices[0].sound = 0x11;
        node->voices[0].octave = -2;
    }
    if (entity->animation == 0) {
        if (entity->handlerTicks == entity->animLength) {
            entity->vt->setAnimation(entity, 1);
            if (rand() & 1) {
                entity->state = 0xB;
            }
        }
    } else {
        if (entity->state == 0) {
            if (entity->handlerTicks == 0x3C || entity->handlerTicks == 0xD4 || entity->handlerTicks == 0x122 || entity->handlerTicks == 0x140) {
                entity->vt->rotate(entity, 0, &g_rotY90);
            }
            if (entity->handlerTicks == 0x18E) {
                entity->vt->rotate(entity, 0, &g_rotYNeg90);
            }
            entity->vt->moveZOnGround(entity, -0x32, 0);
        } else {
            if (entity->handlerTicks == 0x3C || entity->handlerTicks == 0x8C) {
                entity->vt->rotate(entity, 0, &g_rotY90);
            }
            if (entity->handlerTicks < 0xAE) {
                entity->vt->moveZOnGround(entity, -0x32, 0);
            }
            if (entity->handlerTicks == 0xAE) {
                entity->vt->stopHandler(entity);
                entity->state = 1;
            }
        }
    }
}

void Behavior_Type78(BehaviorEntity *entity, HandlerNode *node) {
    s32 roll;
    s32 ticks;
    s32 length;
    void *factors;

    if (node->tick == 0) {
        g_type78Stopped = 0;
        roll = rand() % 3;
        if (roll == 1) {
            entity->state = 0xB;
        }
        if (roll == 2) {
            entity->state = 0xC;
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
    if (entity->animPlaying != 0 && !(node->tick & 3)) {
        node->voices[0].sound = 0x1C;
    }
    length = entity->animLength;
    ticks = entity->handlerTicks;
    if (ticks == length - 1) {
        entity->handlerTicks = -1;
    } else if (ticks >= length / 2 + length / 4) {
        entity->vt->playAnimation(entity);
    } else if (ticks >= length / 2) {
        if (ticks == length / 2) {
            node->voices[0].sound = 0x10;
        }
        entity->vt->moveZ(entity, 0x6E, 0);
    } else if (ticks >= length / 4) {
        entity->vt->stopAnimation(entity);
        entity->vt->moveZ(entity, -0x6E, 0);
    }
    if (entity->state == 0xB && node->tick == 0x1FE) {
        entity->vt->moveY(entity, -0x17C, 0);
        entity->vt->rotate(entity, 0, &g_rotX90);
        entity->vt->stopHandler(entity);
        entity->state = 1;
        g_type78Stopped = 1;
    } else if (entity->state >= 0xC) {
        if (node->tick >= 0x14A && node->tick % 60 == 30) {
            roll = 0;
            if (rand() & 1) {
                factors = &g_scaleTallTwo;
                if (entity->state == 0xC) {
                    roll = 0x190;
                }
                entity->state = 0xD;
            } else {
                factors = &g_scaleOne;
                if (entity->state == 0xD) {
                    roll = -0x190;
                }
                entity->state = 0xC;
            }
            entity->vt->scale(entity, 1, factors);
            entity->vt->moveY(entity, roll, 0);
        }
    }
    if (node->tick == 0x208 && g_type78Stopped != 0) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type79(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % 10 == 0) {
        node->voices[0].sound = 0x19;
        node->voices[0].octave = 2;
    }
    entity->vt->rotate(entity, 0, g_rotY2);
    if ((entity->state == 0) && (entity->touched != 0)) {
        entity->vt->postEvent(entity, 0xB);
        entity->state = 0xB;
    }
}

void Behavior_Type80(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks < entity->animLength) {
        switch (entity->animFrame) {
        case 0:
            break;
        case 0x14:
            node->fade = 0;
            node->voices[0].sound = 0x10;
            break;
        }
    } else {
        entity->vt->stopAnimation(entity);
        entity->vt->move(entity, g_moveYNeg512);
    }
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
}

void Behavior_Type81(BehaviorEntity *entity, HandlerNode *node) {
    s32 turn;
    s32 mode;

    if (entity->handlerTicks == 0 && (rand() & 1)) {
        entity->state = rand() % 3;
    }
    if (entity->state != 0 && entity->touched != 0) {
        if (node->tick >= 0x3D) {
            node->tick = 0;
        }
        if (node->tick % 20 == 0) {
            node->fade = 0;
            node->voices[0].sound = 0x17;
            node->voices[0].octave = -1;
            node->voices[1].sound = 0x17;
            node->voices[1].octave = -1;
            node->voices[2].sound = 0x17;
            node->voices[2].octave = -2;
        } else if (node->tick % 20 == 14) {
            node->voices[0].sound = -2;
            node->voices[1].sound = -2;
            node->voices[2].sound = -2;
        }
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        mode = entity->state;
        if (mode == 1) {
            entity->vt->scale(entity, 0, g_scaleGrowStep);
            turn = -0x176;
            if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x200) {
                entity->vt->sleep(entity);
                entity->state = mode;
            }
        } else {
            entity->dreamSys->vt->unk130(entity->dreamSys, 1);
            Entity_FaceDreamer(entity->dreamSys, entity, 1, 1, 0);
            if (entity->state == 2) {
                if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x960) {
                    entity->state = 0xB;
                    entity->vt->postEvent(entity, 0xC);
                }
                turn = -0x60;
            } else {
                turn = 0;
            }
        }
    } else {
        node->fade = entity->vt->getSoundFade(entity);
        if (node->tick % 22 == 0) {
            node->voices[0].sound = 0x1C;
        }
        if (entity->handlerTicks >= 0x1F5) {
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        }
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x800) {
            entity->dreamSys->vt->moveZ(entity->dreamSys, -0x800, 0);
        }
        turn = -0x14;
    }
    entity->vt->moveZOnGround(entity, turn, 1);
    if (entity->unk28 != 0) {
        entity->vt->moveY(entity, -0xC8, 0);
    }
}

void Behavior_Type82(BehaviorEntity *entity, HandlerNode *node) {
    s32 state;
    BehaviorDreamSys *dreamSys;

    if (entity->state == 0 && entity->handlerTicks == 0) {
        if (rand() % 3) {
            state = (rand() & 1) ? 0xB : 0xC;
            entity->state = state;
        } else {
            entity->vt->stopHandler(entity);
            entity->vt->moveZ(entity, -0x5000, 0);
            rand();
        }
    }
    if (entity->state == 0xC) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        if (entity->handlerTicks == 0x14) {
            node->voices[0].sound = 0x12;
            node->fade = 0;
            node->voices[1].sound = 3;
            dreamSys = entity->dreamSys;
            dreamSys->vt->unk130(dreamSys, 1);
        }
        if (entity->handlerTicks >= 0x15) {
            entity->vt->moveZ(entity, -0x28, 0);
        }
        if (entity->handlerTicks == 0x28) {
            entity->vt->postEvent(entity, 0xA);
        }
    } else if (entity->state == 0xB) {
        entity->vt->stopAnimation(entity);
        if (entity->vt->distanceTo(entity, entity->dreamSys) < 0x200) {
            if (rand() % 3) {
                entity->vt->sleep(entity);
            } else {
                entity->vt->stopHandler(entity);
            }
        }
    }
}

void Behavior_Type83(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->animFrame == ((entity->animFrame / 15) * 15)) {
        node->voices[0].sound = 12;
        node->fade = 0;
        node->voices[0].octave = 2;
    }
    if (entity->handlerTicks == entity->animLength) {
        node->voices[0].sound = -2;
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type84(BehaviorEntity *entity, HandlerNode *node) {
    s32 frame;

    node->fade = entity->vt->getSoundFade(entity);
    frame = entity->animFrame;
    if (frame < 0x28) {
        node->voices[0].sound = 0xC;
        node->voices[0].octave = -2;
        node->voices[2].sound = 5;
        node->voices[2].octave = -1;
    } else if (frame == 0x28) {
        node->voices[0].sound = -2;
        node->voices[2].sound = -2;
    } else if (frame == 0x2D) {
        node->voices[1].sound = 0x12;
        node->voices[1].octave = 1;
    } else if (frame == 0x40) {
        node->voices[0].sound = 7;
    } else if (frame == 0x59) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_Type85(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->state == 0) {
        if (entity->animFrame == 5) {
            Behavior_QueueLowSound7(node);
        }
        if (entity->handlerTicks == entity->animLength) {
            entity->vt->stopAnimation(entity);
            entity->state = 0xA;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xA) {
        if (entity->handlerTicks < 0xA) {
            entity->vt->rotate(entity, 0, g_rotY9);
            if (entity->dreamSys->vt->unk100(entity->dreamSys) != 0) {
                Behavior_QueueLowSound7(node);
                entity->state = 0xC;
                entity->handlerTicks = -1;
            }
        } else {
            entity->dreamSys->vt->unk130(entity->dreamSys, 1);
            entity->state = 0xB;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xB) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        if (entity->handlerTicks < 0x1E) {
            entity->vt->moveZ(entity, -10, 0);
        } else {
            Behavior_QueueLowSound7(node);
            if (Entity_StartEffect((Entity *)entity, 0, 0, 0x1E, 0) != 0) {
                entity->effect->vtbl->startIn(entity->effect, entity->unk50, 7, 0);
            }
            entity->state = 0xD;
            entity->handlerTicks = -1;
        }
    } else if (entity->state == 0xD) {
        if (entity->handlerTicks < 0x5A) {
            if (entity->handlerTicks == 0x1E) {
                if (Entity_StartEffect((Entity *)entity, 0, 0, 0xA, 0) != 0) {
                    entity->effect->vtbl->startOut(entity->effect, entity->unk50, 0, 0);
                }
            }
            entity->dreamSys->vt->rotate(entity->dreamSys, 0, g_rotZ1);
        } else {
            Behavior_QueueSound18And3(node);
            entity->dreamSys->vt->rotate(entity->dreamSys, 1, g_rotY180);
            entity->vt->postEvent(entity, rand() % 5 ? 0xA : 0xC);
            entity->state = 0xE;
        }
    } else if (entity->state == 0xC) {
        if (entity->handlerTicks < 0xA) {
            entity->vt->rotate(entity, 0, g_rotZNeg9);
        } else {
            Behavior_QueueSound18And3(node);
            entity->vt->stopHandler(entity);
            entity->state = 1;
        }
    }
}

void Behavior_Type86(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks < 0xA) {
        entity->vt->stopAnimation(entity);
    } else if (entity->handlerTicks == 0xA) {
        entity->vt->playAnimation(entity);
    }
    if (entity->animFrame == 0xA) {
        Behavior_QueueSound18And3(node);
    }
    if (entity->handlerTicks == entity->animLength + 0xA) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
}

void Behavior_QueueLowSound7(HandlerNode *node) {
    node->fade = 0;
    node->voices[0].sound = 7;
    node->voices[0].octave = -2;
    node->voices[1].sound = 7;
    node->voices[1].octave = -2;
    node->voices[2].sound = 7;
    node->voices[2].octave = -2;
}

void Behavior_QueueSound18And3(HandlerNode *node) {
    node->voices[0].sound = 0x12;
    node->fade = 0;
    node->voices[1].sound = 3;
    node->voices[2].sound = 3;
}

void Behavior_Type87(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        node->voices[0].sound = 0x12;
    }
    if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
}

void Behavior_Type88(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == entity->animLength / 2) {
        node->voices[0].sound = 0x12;
    }
    if (node->tick >= entity->animLength - 1) {
        node->tick = -1;
    }
}

void Behavior_Type89(BehaviorEntity *entity, HandlerNode *node) {
    s32 ticks;

    ticks = entity->handlerTicks;
    if (ticks == 0x14) {
        node->voices[0].sound = 0x12;
        node->fade = 0;
        node->voices[1].sound = 3;
        return;
    }
    if (ticks == entity->animLength) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
        if (rand() & 1) {
            entity->vt->postEvent(entity, 0xB);
        }
    }
}

void Behavior_Type90(BehaviorEntity *entity, HandlerNode *node) {
    s32 sound;

    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == 0) {
        if (rand() & 1) {
            sound = 2;
        } else {
            sound = 1;
        }
        node->voices[0].sound = sound;
        node->voices[0].octave = 2;
    }
}

void Behavior_Type91(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        if (Entity_StartEffect(entity, 0, 0, 5, 0)) {
            if (rand() & 1) {
                entity->vt->move(entity, g_moveYNeg256);
            }
            entity->effect->vtbl->startIn(entity->effect, entity->unk50, 0, 0);
        }
    } else if (entity->animFrame == 0) {
        do {
            entity->animData = entity->vt->applyFrame(entity, entity->animData, 0);
            entity->animFrame++;
        } while (entity->animFrame < 0x18);
    }
    if (entity->animFrame >= 0x19) {
        entity->vt->moveZ(entity, -0x14, 0);
        entity->dreamSys->vt->unk130(entity->dreamSys, 1);
    }
    if (entity->handlerTicks == 0x32) {
        entity->vt->postEvent(entity, 0xA);
    } else if (entity->handlerTicks == 0xC) {
        node->fade = 0;
        node->voices[0].sound = 0x15;
    }
    entity->vt->scale(entity, 1, g_scaleSquash);
}

void Behavior_Type92(BehaviorEntity *entity, HandlerNode *node) {
    s32 frame;

    if (entity->animation == 0) {
        if (entity->touched != 0) {
            Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
            entity->vt->setAnimation(entity, 1);
            entity->dreamSys->vt->unk130(entity->dreamSys, 1);
        } else if (entity->animFrame == 0) {
            do {
                entity->animData = entity->vt->applyFrame(entity, entity->animData, 0);
                frame = entity->animFrame + 1;
                entity->animFrame = frame;
            } while (frame < 0x18);
        }
    } else {
        if (entity->animFrame == 0) {
            node->fade = 0;
            node->voices[0].sound = 0x16;
        } else if (entity->animFrame == entity->animLength - 1) {
            node->fade = 0;
            node->voices[1].sound = 0x12;
            entity->vt->postEvent(entity, 0xA);
        }
    }
    entity->vt->scale(entity, 1, g_scaleSquash);
}

void Behavior_Type93(BehaviorEntity *entity, HandlerNode *node) {
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % 10 == 0) {
        node->voices[0].sound = 3;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->setAnimation(entity, 1);
    }
    if (entity->animation == 1) {
        entity->vt->moveZ(entity, -0x80, 1);
    }
}

void Behavior_Type94(BehaviorEntity *entity, HandlerNode *node) {
    s32 roll;
    BehaviorDreamSys *dreamSys;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) != 7) {
            entity->state = 0xB;
        }
    }
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick == (node->tick / 10) * 10) {
        node->voices[0].sound = 0xE;
    }
    if (entity->handlerTicks == entity->animLength) {
        entity->vt->setAnimation(entity, 1);
        if (entity->state != 0 && !(rand() & 1)) {
            entity->vt->scale(entity, 1, &g_scaleSix);
            entity->vt->moveY(entity, 0x800, 0);
        }
        roll = rand();
        if (roll == (roll / 3) * 3) {
            entity->vt->rotate(entity, 0, &g_rotY180);
        }
    }
    if (entity->animation != 0) {
        entity->vt->moveZ(entity, -0x80, 1);
    }
}

void Behavior_Type95(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        entity->vt->setAnimation(entity, 3);
    } else if (entity->handlerTicks == entity->animLength) {
        entity->vt->setAnimation(entity, 1);
    }
    if (entity->animation == 1) {
        entity->vt->moveZ(entity, -0x80, 0);
    }
}

void Behavior_Type96(BehaviorEntity *entity, HandlerNode *node) {
    if (entity->handlerTicks == 0) {
        entity->vt->setAnimation(entity, rand() % 4);
        return;
    }
    if (entity->handlerTicks % entity->animLength == 0) {
        entity->vt->setAnimation(entity, rand() % 4);
        node->fade = entity->vt->getSoundFade(entity);
        node->voices[0].sound = 0x16;
        node->voices[0].octave = 2;
        node->voices[0].volume = 0x40;
        node->voices[0].endVolume = 0x20;
    }
}

void Behavior_EraseFlashbacks(BehaviorEntity *entity) {
    if (entity->touched != 0 && Entity_StartEffect(entity, 0, 0, 0xA, 0)) {
        entity->effect->vtbl->startIn(entity->effect, entity->unk50, 7, 0);
        entity->vt->sleep(entity);
        entity->dreamSys->vt->clearFlashbacks(entity->dreamSys);
    }
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type102(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    void *factors;
    s32 length;
    s32 ticks;

    if (entity->handlerTicks == 0) {
        entity->vt->moveY(entity, -0x200, 0);
    }
    node->fade = entity->vt->getSoundFade(entity);
    length = entity->animLength;
    if (entity->animFrame == length / 2) {
        node->voices[0].sound = 7;
        node->voices[0].octave = -2;
        node->voices[1].sound = 3;
        node->voices[1].octave = -2;
    }
    if (entity->handlerTicks >= 0x33) {
        entity->vt->rotate(entity, 0, &g_rotYNegThird);
    }
    if (entity->handlerTicks >= 0x30D) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        ticks = entity->handlerTicks;
        if (ticks >= 0x790) {
            factors = &g_scaleOne;
        } else if (ticks >= 0x78B) {
            factors = g_scaleSquash;
        } else if (ticks >= 0x786) {
            factors = &g_scaleHalf;
        } else {
            factors = &g_scaleEighth;
            if (ticks >= 0x781) {
                factors = &g_scaleQuarter;
            }
        }
        entity->vt->scale(entity, 1, factors);
        if (entity->handlerTicks < 0x7D0) {
            entity->vt->moveZ(entity, -0x40, 0);
        } else {
            entity->state = 1;
        }
    } else {
        entity->vt->moveZ(entity, -0x100, 0);
    }
    if ((entity->touched != 0) && (entity->state == 0)) {
        dreamSys = entity->dreamSys;
        entity->state = 0xC;
        dreamSys->vt->unk130(dreamSys, 1);
        entity->vt->postEvent(entity, 0xA);
    }
    if (entity->state == 0xC) {
        dreamSys = entity->dreamSys;
        dreamSys->vt->moveZ(dreamSys, 0x100, 0);
    }
}

void Behavior_Type103(BehaviorEntity *entity) {
    s32 roll;
    BehaviorMap *map;

    if (entity->handlerTicks == 0x2BC) {
        roll = rand();
        if (roll == (roll / 3) * 3) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks < 0x3FC) {
            entity->vt->rotate(entity, 0, g_rotYNegHalf);
            entity->vt->moveY(entity, 0x1E, 0);
        }
        if (entity->handlerTicks == 0x3A2) {
            entity->vt->postEvent(entity, 0xA);
        }
    } else if (entity->handlerTicks == 0x64 || entity->handlerTicks == 0x320) {
        if (rand() % 5 == 0) {
            map = entity->map;
            map->vt->unk138(map, 4, 0);
        }
    }
    entity->vt->moveZ(entity, -0x1E, 0);
}

void Behavior_Type104(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleQuarter);
    if (entity->handlerTicks >= 201 && entity->handlerTicks < 300) {
        entity->vt->moveY(entity, -0x20, 0);
    }
}

void Behavior_Type105(BehaviorEntity *entity) {
    entity->vt->unk60(entity, (rand() % 20) == 0);
}

void Behavior_Type106(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        if ((rand() & 1) == 0) {
            entity->state = 0xB;
        }
    }
    if (entity->state == 0xB) {
        if (entity->handlerTicks == 0) {
            entity->vt->stopAnimation(entity);
        }
        entity->vt->scale(entity, 1, g_scaleThinTall);
    } else {
        if (entity->handlerTicks == 0) {
            entity->vt->setAnimation(entity, 1);
        }
        entity->vt->moveX(entity, (entity->handlerTicks % 20) < 10 ? 0x20 : -0x20, 0);
    }
}

void Behavior_Type108(BehaviorEntity *entity, HandlerNode *node) {
    Behavior_Type71(entity, node);
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_YellowDayBeast(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleHalf);
    entity->vt->moveZ(entity, -10, 0);
}

void Behavior_BridgeGeisha(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, g_scaleTwoFifths);
    entity->vt->stopAnimation(entity);
    if (entity->state == 0 && entity->vt->distanceTo(entity, entity->dreamSys) < 0x800) {
        entity->state = 0xA;
        entity->handlerTicks = 0;
    }
    if (entity->state == 0xA) {
        if (entity->handlerTicks < 0x2D) {
            entity->vt->rotate(entity, 0, g_rotY4);
        }
        if (entity->handlerTicks >= 0x1F5) {
            entity->state = 0;
        }
    }
}

void Behavior_FlyingTrain(BehaviorEntity *entity, HandlerNode *node) {
    BehaviorDreamSys *dreamSys;
    s32 ticks;

    if (entity->handlerTicks == 0) {
        dreamSys = entity->dreamSys;
        if (dreamSys->vt->getDreamColor(dreamSys) == 5) {
            entity->state = 0xB;
        }
    }
    if (entity->state != 0 && entity->handlerTicks >= 0x870) {
        ticks = entity->handlerTicks;
        if ((u32)(ticks - 0x870) < 0x191U) {
            if (ticks == 0x870) {
                entity->vt->stopAnimation(entity);
                node->voices[0].sound = -2;
                node->voices[1].sound = -2;
                node->voices[2].sound = -2;
                return;
            }
            if ((u32)(ticks - 0x9F6) < 0xAU) {
                node->voices[0].sound = 5;
                node->voices[0].octave = -2;
                return;
            }
            if (ticks == 0xA00) {
                entity->vt->playAnimation(entity);
                node->tick = 1;
            }
        } else if (ticks >= 0xA03) {
            if (ticks >= 0xAF1) {
                entity->vt->moveY(entity, -0x20, 0);
            }
            Behavior_TrainRun(entity, node, 0x1E1, 0xFA0, -0x3C);
        }
    } else {
        Behavior_TrainRun(entity, node, 0x1E1, 0x884, -0x3C);
    }
}

void Behavior_TrainRun(BehaviorEntity *entity, HandlerNode *node, s32 turnTick, s32 leaveTick, s32 speed) {
    node->fade = 0;
    if (node->tick == 6) {
        node->voices[0].sound = 4;
        node->voices[1].sound = 4;
        node->voices[2].sound = 4;
    }
    if ((entity->handlerTicks >= turnTick && entity->handlerTicks <= turnTick + 0x5B) ||
        (entity->handlerTicks >= turnTick + 0x155 && entity->handlerTicks <= turnTick + 0x1B1) ||
        (entity->handlerTicks >= turnTick + 0x2BA && entity->handlerTicks <= turnTick + 0x317)) {
        entity->vt->rotate(entity, 0, &g_rotY1);
    }
    entity->vt->moveZ(entity, speed, 0);
    if (entity->handlerTicks == leaveTick) {
        entity->vt->sleep(entity);
        entity->state = 1;
    }
}

void Behavior_Type113(BehaviorEntity *entity, HandlerNode *node) {
    Behavior_Type51(entity, node);
}

void Behavior_RedDayGunman(BehaviorEntity *entity) {
    s16 *angles;

    if (rand() % 3 == 0) {
        return;
    }
    if (rand() % 3 != 0) {
        angles = g_rotY9;
    } else {
        angles = g_rotYNeg9;
    }
    entity->vt->rotate(entity, 0, angles);
}

void Behavior_Type117(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type118(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleSix);
}

void Behavior_Type121(BehaviorEntity *entity) {
    entity->vt->scale(entity, 1, &g_scaleQuarter);
}

void Behavior_Type123(BehaviorEntity *entity) {

    if (entity->handlerTicks == 0) {
        if (rand() % 5 == 0) {
            entity->state = 0xB;
        }
    }
    entity->vt->stopAnimation(entity);
    entity->vt->moveZ(entity, 0x64, 0);
    if (entity->handlerTicks == 0x3E8) {
        entity->vt->stopHandler(entity);
        entity->state = 1;
    }
    if ((entity->state == 0xB) && (entity->handlerTicks >= 0x12D)) {
        entity->dreamSys->vt->unk94(entity->dreamSys, 0, 2);
        entity->dreamSys->vt->unk94(entity->dreamSys, 0, 7);
    }
}

void Behavior_OddDayGeisha(BehaviorEntity *entity, HandlerNode *node) {
    if (((entity->handlerTicks == 0) && !(rand() & 3)) || (entity->handlerTicks == 0xE10)) {
        entity->vt->sleep(entity);
        entity->state = 1;
    }
    entity->vt->scale(entity, 1, g_scaleTwoFifths);
    node->fade = entity->vt->getSoundFade(entity);
    if (node->tick % (entity->animLength / 2) == 0) {
        node->voices[0].sound = 0xA;
        node->voices[0].octave = 1;
    }
    entity->vt->moveZ(entity, -0xA, 0);
}

void Behavior_TinyLips(BehaviorEntity *entity) {
    Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
    entity->vt->scale(entity, 1, &g_scaleTiny);
    entity->vt->moveZ(entity, -0x1E, 1);
}

void Behavior_Type129(BehaviorEntity *entity) {
    if (entity->handlerTicks == 0) {
        entity->state = (rand() % 2) + 0xA;
    }
    entity->vt->stopAnimation(entity);
    if (entity->handlerTicks >= 0xC9) {
        Entity_FaceDreamer(entity, entity->dreamSys, 1, 0, 0);
        if (entity->state == 0xA) {
            entity->vt->moveZOnGround(entity, -0x200, 0);
        }
    }
}

void *Model_New(s32 source, s32 soundBank) {
    void *model;

    model = ((void *)Heap_Alloc(0x98));
    if (model != NULL) {
        if (((ModelVtbl *)Model_GetVtbl())->construct(model, source, soundBank) == 0) {
            Heap_Free((s32)model);
            return NULL;
        }
        return model;
    }
    return NULL;
}

void *Model_Construct(Model *model, s32 source, SoundBank *soundBank) {
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
    ModelPart *part;

    Actor_GetVtbl()->unk60(model, 0);
    model->vt->setUnk64(model, 1);
    model->vt->unkE4(model, 0x12C);
    model->vt->stopTick(model);
    model->vt->setTickMode(model, 0x41);
    model->vt->stopAnimation(model);
    model->vt->setAnimation(model, 0);
    part = model->part;
    if (part != NULL) {
        SceneNode_LinkModel(model, part->unk20);
    }
}

void Model_Attach(Model *model, void *target, void *watched, s32 arg3, s32 arg4) {
    if (model->attached == 0) {
        Actor_GetVtbl()->attach(model, arg3, arg4);
        if ((watched != 0) && (model->unk50 == 0)) {
            model->vt->watch(model, watched);
        }
        model->vt->setTarget(model, target);
    }
}

void Model_Detach(Model *model) {
    void *watched;

    if (model->attached != 0) {
        model->vt->clearTarget(model);
        watched = model->unk50;
        if (watched != 0) {
            model->vt->unwatch(model, watched);
        }
        Actor_GetVtbl()->detach(model);
    }
}

void Model_SetVisible(Model *model, s32 arg1) {
    ModelPart **p;
    s32 i;

    p = model->parts;
    for (i = 0; i < model->partCount; i++, p++) {
        (*p)->vt->unk60(*p, arg1);
    }
}

void Model_SetLightFlags(Model *model, s32 arg1) {
    ModelPart **p;
    s32 i;

    p = model->parts;
    for (i = 0; i < model->partCount; i++, p++) {
        (*p)->vt->unk70(*p, arg1);
    }
    Actor_GetVtbl()->unk70(model, arg1);
}

/* Slot 0x98, the update: phase 2 runs the animation tick, phase 4 deletes the model. */
void Model_Update(Model *model, s32 arg1, s32 phase) {
    if (phase == 2) {
        model->vt->tickAnimation(model);
    }
    if (phase == 4) {
        model->vt->delete_(model);
    }
}

void func_80065BF4(Model *model, s32 value) {
    model->unk64 = value;
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
s32 Model_LoadFile(Model *model, ModelSource *source) {
    if (source->file != NULL) {
        model->file = source->file;
        model->ownsFile = 0;
    } else {
        model->file = Mom_Create(source);
        model->ownsFile = 1;
    }
    if (model->file != NULL) {
        return model->vt->createParts(model);
    }
    Model_FreeFile(model);
    return 1;
}

void Model_FreeFile(Model *model) {
    ModelFile *file;

    model->vt->freeParts(model);
    if (model->ownsFile != 0) {
        file = model->file->vt->delete_(model->file);
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

s32 Model_BuildParts(Model *model) {
    ModelFile *file;
    s32 current;
    s32 n;
    s32 i;
    ModelPart **p;
    ModelPart *part;

    file = model->file;
    n = file->vt->getPartIds(file, 0, &current) & 0xFF;
    model->parts = (ModelPart **)Heap_Alloc(n * 4);
    if (model->parts != NULL) {
        model->partIds = (u8 *)Heap_Alloc(n);
        if (model->partIds != NULL) {
            file = model->file;
            file->vt->getPartIds(file, model->partIds, &current);
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

void Model_ReleaseParts(Model *model) {
    ModelPart **p;
    ModelPart *part;

    if (model->parts != NULL && model->partIds != NULL) {
        p = model->parts;
        while (model->partCount-- > 0) {
            part = *p++;
            part->vt->delete_(part);
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
            model->animData = (u8 *)model->file->anims->list->entries[model->animation]->data + 8;
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
    ModelPart *part;

    model->vt->moveZ(model, -0x1E, 0);
    if (model->unk64 == 1) {
        part = model->part;
        if (part != NULL) {
            part->vt->unk88(part, 6);
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
    model->animLength = model->file->anims->list->entries[animation]->data->frameCount;
    model->animData = (u8 *) model->file->anims->list->entries[model->animation]->data + 8;
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
void *Model_ApplyFrame(Model *model, u8 *frame, void *arg2) {
    u32 count;
    u32 i;
    u32 pad[2];

    count = *(u16 *)(frame + 2);
    frame = frame + 8;
    i = 0;
    if (count != 0) {
        do {
            i++;
            frame = model->vt->applyCommand(model, frame, arg2);
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
    ModelPart *part;
    Coord2 *coord;
    Coord2Param *param;
    s16 *s;
    s16 *r;
    s32 *v;
    s32 i;

    data = model->file->vt->readCommand(model->file, command, &id, &type, &flags, &size);
    n = Model_FindPart(model, id);
    if (n >= 0) {
        part = model->parts[n];
        coord = part->coord;
        coord->flg = 0;
        param = coord->param;
        switch (type) {
        case 0:
            part->flags = (part->flags & data[0]) | data[1];
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
            if (*(u16 *)data != 0 && part->unk20 == 0) {
                SceneNode_LinkModel(part, model->file->textures->vt->unk80(model->file->textures, *(u16 *)data - 1));
            }
            break;
        case 3:
            if (data[0] == 0 || data[0] == 0xFFFF) {
                part->vt->attach(part, model, 0);
            } else {
                part->vt->attach(part, model->parts[Model_FindPart(model, data[0])], 0);
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

Unk_80066818_Vtbl *Model_GetVtbl(void) {
    return (Unk_80066818_Vtbl *)g_modelVtbl;
}

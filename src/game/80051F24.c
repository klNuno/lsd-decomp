#include "common.h"
#include "game/heap.h"
#include "game/dreamsys.h"
#include "game/entity.h"
#include "game/place.h"

/*
 * The memory card file list window (vtable g_stringListVtbl, returned by StringList_GetVtbl; its first
 * methods are in src/game/80050BA8.c): background CARD\SELECT.TIM, up to 4 visible rows of
 * 26 characters built by Label_Create, the selected row in g_stringListCursorColor (0x80, 0x80, 0), the
 * others in g_stringListRowColor (0x50, 0x50, 0x50). Slots 0x7C to 0x88 scroll it, 0x8C to 0x98 draw it.
 */
typedef struct CardListVtbl {
    u8 pad_00[0x10];
    void (*watch)();      /* 0x10 Object_Watch */
    void (*unwatch)();    /* 0x14 Object_Unwatch */
    u8 pad_18[0x30 - 0x18];
    void (*notify)();     /* 0x30 Object_Notify */
    u8 pad_34[0x48 - 0x34];
    void (*close)();      /* 0x48 StringList_Close */
    u8 pad_4C[0x54 - 0x4C];
    void (*setMode)();    /* 0x54 StringList_SetState */
    u8 pad_58[0x60 - 0x58];
    void (*setBoxValue)();      /* 0x60 StringList_SetBoxValue */
    u8 pad_64[0x7C - 0x64];
    void (*scrollRight)(); /* 0x7C StringList_ScrollRight */
    void (*scrollLeft)(); /* 0x80 StringList_ScrollLeft */
    void (*moveUp)();     /* 0x84 StringList_CursorUp */
    void (*moveDown)();   /* 0x88 StringList_CursorDown */
    void (*createRows)(); /* 0x8C StringList_CreateRows */
    void (*deleteRows)(); /* 0x90 StringList_DeleteRows */
    void (*drawRows)();   /* 0x94 StringList_RedrawRows */
    void (*moveCursor)(); /* 0x98 StringList_MoveHighlight */
} CardListVtbl;

/* A row text, the background, a loaded file: the slots called on them here. */
typedef struct CardTextVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();   /* 0x04 Object_Delete */
    u8 pad_08[0x4C - 0x08];
    void (*attach)();      /* 0x4C (obj, parent, position) */
    u8 pad_50[0x78 - 0x50];
    void (*upload)();      /* 0x78 called on a file right after Tim_New */
    u8 pad_7C[0xB8 - 0x7C];
    void (*setColor)();   /* 0xB8 g_stringListCursorColor or g_stringListRowColor */
    u8 pad_BC[0xCC - 0xBC];
    void (*setText)();    /* 0xCC */
} CardTextVtbl;

typedef struct CardText {
    CardTextVtbl *vt;
} CardText;

typedef struct CardListOwnerVtbl {
    u8 pad_00[0x80];
    void (*unk80)();
} CardListOwnerVtbl;

typedef struct CardListOwner {
    CardListOwnerVtbl *vt;
} CardListOwner;

typedef struct CardList {
    CardListVtbl *vt;
    u8 pad_04[0x10 - 0x04];
    s32 count;            /* 0x10 rows in the list */
    s32 width;            /* 0x14 characters of the longest row */
    s32 *offsets;         /* 0x18 row i starts at text + offsets[i] */
    u8 pad_1C[0x20 - 0x1C];
    s32 top;              /* 0x20 first visible row */
    s32 column;           /* 0x24 first visible character (text base for StringList_FormatRow) */
    s32 cursor;           /* 0x28 selected row */
    s32 mode;             /* 0x2C 2 or 3 (setMode) */
    s32 modeTicks;        /* 0x30 */
    s32 watchedA;            /* 0x34 unwatched by setMode and the destructor */
    s32 watchedB;
    s32 owner;
    CardText *rows[4];    /* 0x40 visible rows */
    CardText *background; /* 0x50 CARD\SELECT.TIM, 0 while closed */
} CardList;

/* The texture-set loader of Tix_Create (class g_tixVtbl, 0x84 bytes), as Place sees it. */
typedef struct PlaceTexLoaderVtbl {
    u8 pad_00[0x04];
    void (*delete_)();    /* 0x04 Object_Delete */
    u8 pad_08[0x7C - 0x08];
    void (*apply)();      /* 0x7C called with the ambience colour once done */
} PlaceTexLoaderVtbl;

typedef struct PlaceTexLoader {
    PlaceTexLoaderVtbl *vt;
    u8 pad_04[0x3C - 0x04];
    s32 done;             /* 0x3C */
    u8 pad_40[0x80 - 0x40];
    s32 failed;           /* 0x80 set by Tix_OnReadDone when Heap_Alloc returned 0 */
} PlaceTexLoader;

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

/* The vtable of the class SceneNode_GetVtbl returns (src/game/8001CA94.c), base of Actor. */
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

/* The scenery part class g_sceneryPartVtbl (0xA8 bytes, SceneryPart_New), built on the class of SpriteNode_GetVtbl. */
typedef struct TextPartVtbl {
    u8 pad_00[0x08];
    void (*construct)();  /* 0x08 SceneryPart_Construct */
    u8 pad_0C[0x40 - 0x0C];
    void (*init)();       /* 0x40 SceneryPart_Init */
} TextPartVtbl;

typedef struct TextPart {
    TextPartVtbl *vt;
    u8 pad_04[0x58 - 0x04];
    void *unk58;          /* 0x58 slot 0x48 scales +0x5C and +0x60 while set, else stores the ratios at +0x80 */
    s32 unk5C;
    s32 unk60;
    u8 pad_64[0x74 - 0x64];
    u16 clutX;            /* 0x74 g_sceneryPartCluts[index * 2] */
    u16 clutY;            /* 0x76 g_sceneryPartClutsY[index * 2] */
    u8 pad_78[0x80 - 0x78];
    s16 scaleX;
    s16 scaleY;
    u8 pad_84[0xA0 - 0x84];
    s32 index;            /* 0xA0 */
    s32 unkA4;
} TextPart;

/* The vtable of Graph_GetVtable, slot 0x08 only. */
typedef struct GraphCtorVtbl {
    u8 pad[8];
    void (*construct)(void *, s32);
} GraphCtorVtbl;

/* The dream runner's object at +0xC (src/game/800494B4.c): slot 0xC8 registers a callback with an argument. */
typedef struct PlaceOwnerObjVtbl {
    u8 pad_00[0xC8];
    void (*setCallback)(void *, void (*)(Place *, s32, s32, s32), void *);
} PlaceOwnerObjVtbl;
typedef struct PlaceOwnerObj {
    PlaceOwnerObjVtbl *vt;
} PlaceOwnerObj;
typedef struct PlaceOwner {
    u8 pad_00[0xC];
    PlaceOwnerObj *callbackObj;
} PlaceOwner;

/* The class SpriteNode_GetVtbl returns, base of TextPart. */
typedef struct TextPartBaseVtbl { u8 pad_00[0x8]; void (*construct)(void *, s32, s32, void *, s32, s32); } TextPartBaseVtbl;

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

/* One word of g_sceneryParams, as Scenery_CreateKind2 writes unk1C and unk20. */
typedef struct ParamWord {
    s32 v;
} ParamWord;

/* A screen position, {x, y} (the band layout g_bandPos, g_bandSize). */
typedef struct Point {
    s32 x;
    s32 y;
} Point;

/* The ambience band objects (Box_Create): 18 in g_ambienceBands for family 0, one at g_ambienceTint. */
typedef struct AmbienceBandVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();   /* 0x04 Object_Delete */
    u8 pad_08[0x4C - 0x08];
    void (*attach)();     /* 0x4C (band, parent, position) */
    u8 pad_50[0x64 - 0x50];
    void (*setSemiTrans)();
    void (*setBlendMode)();
    u8 pad_6C[0xB8 - 0x6C];
    void (*setColor)();   /* 0xB8 (band, 1, RGB) */
    void (*setPos)();     /* 0xBC */
} AmbienceBandVtbl;

typedef struct AmbienceBand {
    AmbienceBandVtbl *vt;
} AmbienceBand;

/* The parameters g_sceneryParams holds for the next scenery object (copied whole by its init, Scenery_Init). */
typedef struct SceneryParams {
    s32 x;        /* 0x00 offset from the origin: random +-22 tiles (<< 11) in Scenery_RandomizeParams */
    s32 y;        /* 0x04 */
    s32 z;        /* 0x08 */
    u8 *rotation;     /* 0x0C 12-byte entry of g_sceneryRotations */
    u8 *scale;    /* 0x10 12-byte entry of g_sceneryScales, or g_sceneryKind1Scale */
    s32 direction;    /* 0x14 rand() % 5 */
    s32 variant;    /* 0x18 */
    u8 *color;    /* 0x1C 3-byte entry of g_sceneryKind3Colors or g_sceneryKind2Colors */
    s32 dayMark;    /* 0x20 kind 2: day number % 20, or D_80087430 */
} SceneryParams;

/* A part of a scenery object (classes g_actorVtbl for kind 0, g_sceneryPartVtbl for kinds 2 and 3). */
typedef struct SceneryPartVtbl {
    u8 pad_00[0x44];
    void (*setRotation)();
    void (*setScale)();
    void (*attach)();
    u8 pad_50[0x60 - 0x50];
    void (*setVisible)();
    void (*setSemiTrans)();
    void (*setBlendRate)();
    u8 pad_6C[0xB8 - 0x6C];
    void (*setColor)();
    void (*setPosition)();
} SceneryPartVtbl;

typedef struct SceneryPart {
    SceneryPartVtbl *vt;
    u8 pad_04[0x84 - 0x04];
    s32 angle;    /* 0x84 random angle (rand() % 360) << 12 for kind 3 */
} SceneryPart;

/*
 * A scenery object (class g_sceneryVtbl returned by Scenery_GetVtbl, 0x98 bytes, made by Scenery_New):
 * one of 4 kinds made around the dreamer at a place's first tick (Scenery_CreateAll, work/hunt6/F-findings.md).
 * Its base class is g_actorVtbl (constructor Actor_Construct, 0x58 bytes).
 */
typedef struct SceneryVtbl {
    u8 pad_00[0x08];
    s32 (*construct)();   /* 0x08 Scenery_Construct */
    void (*destruct)();   /* 0x0C Scenery_Destruct */
    u8 pad_10[0x40 - 0x10];
    void (*init)();       /* 0x40 Scenery_Init */
    void (*setRotation)();
    void (*setScale)();
    void (*attach)();
    u8 pad_50[0xB8 - 0x50];
    void (*setPos)();     /* 0xB8 Actor_SetPos */
    void (*movePos)();    /* 0xBC Actor_MovePos */
    u8 pad_C0[0xEC - 0xC0];
    void (*update)();     /* 0xEC Scenery_Update */
} SceneryVtbl;

typedef struct Scenery {
    SceneryVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    s32 *posBlock;        /* 0x14 its first word is cleared once moved */
    u8 pad_18[0x20 - 0x18];
    void *model;          /* 0x20 */
    u32 ticks;            /* 0x24 counted by update (Scenery_Update) */
    u8 pad_28[0x44 - 0x28];
    s32 unk44;            /* 0x44 cleared by the constructor */
    u8 pad_48[0x54 - 0x48];
    s32 kind;             /* 0x54 0 to 3 */
    Vec3 offset;          /* 0x58 params x, y, z: offset from the origin */
    s32 rotation;            /* 0x64 params unkC */
    s16 *scale;           /* 0x68 params unk10 */
    s32 direction;            /* 0x6C params unk14, kind 0: direction 1 to 4 of its two parts */
    s32 variant;            /* 0x70 params unk18 */
    s32 color;            /* 0x74 params unk1C */
    s32 dayMark;
    union {
        SceneryPart *pair[2];                                 /* 0x7C kind 0 */
        struct { u8 pad_7C[0x84 - 0x7C]; SceneryPart *parts[5]; } many; /* 0x84 kinds 2 and 3 */
    } u;
} Scenery;

/*
 * A spot: an 8-byte record of g_stageSoundSpots[stage] (count g_stageSoundSpotCounts[stage]) with a map tile
 * record, a handler index idx and a range class. While the dreamer is within g_soundSpotRanges[range]
 * (ground distance |dx| + |dz|), one of the two slots g_soundSpotSlots holds it and its handler
 * g_soundSpotHandlers[range] runs (SoundSpot_Acquire); the range is negated while it is held.
 */
typedef struct SpotTile {
    u8 b0, b1, b2, b3;    /* handed to map slot 0xE8 with the g_soundSpotTileExtras entry */
} SpotTile;

typedef struct SpotTileExtra {
    SpotTile tile;
    s16 v;
} SpotTileExtra;

typedef struct SpotRecord {
    SpotTile tile;        /* 0x0 */
    u8 idx;               /* 0x4 index of g_soundSpotTileExtras */
    u8 unk5;
    s8 range;             /* 0x6 > 0 free, < 0 held by a slot */
    u8 unk7;
} SpotRecord;

typedef struct SpotQuery {
    SpotTile a;
    SpotTileExtra b;
} SpotQuery;

/* The two slots (g_soundSpotSlots points into g_soundSpotSlotData, 0x68 bytes each). */
typedef struct SpotSlot {
    SpotRecord *record;   /* 0x00 */
    s32 pos[3];           /* 0x04 the spot's position (map slot 0xE8) */
    s32 distance;         /* 0x10 ground distance to the dreamer */
    s32 node;             /* 0x14 handler node, registered with HandlerNode_Start */
    u8 pad_18[0x28 - 0x18];
    s32 fadeSteps;            /* 0x28 SoundSpot_CalcFade divides the range by it */
    u8 pad_2C[0x68 - 0x2C];
} SpotSlot;

/* The same slot as SoundSpot_Release reads it (the range byte unsigned). */
typedef struct SpotRecordU {
    u8 pad_00[6];
    u8 range;
} SpotRecordU;

typedef struct SpotSlotU {
    SpotRecordU *record;
    s32 pos[3];
    s32 distance;
    s32 node;
} SpotSlotU;

/* The handler state the spot handlers SoundSpot_Type1 to SoundSpot_Type14 get: a tick count and three {value, step} channels. */
typedef struct SpotState {
    u8 pad_00[0x4];
    s32 tick;             /* 0x04 the handler sets -1 to stop */
    u8 pad_08[0x10 - 0x8];
    s32 level;            /* 0x10 SoundSpot_CalcFade: distance / (range / slot +0x28) */
    u8 pad_14[0x1C - 0x14];
    s32 sound0;
    s32 octave0;
    s32 volume0;
    s32 endVolume0;
    u8 pad_2C[0x30 - 0x2C];
    s32 sound1;
    s32 octave1;
    s32 volume1;
    s32 endVolume1;
    u8 pad_40[0x44 - 0x40];
    s32 sound2;
    s32 octave2;
    s32 volume2;
    s32 endVolume2;
} SpotState;


/* .sdata owned by this unit (config/splat.yaml), defined at the end of the file: pairs read whole by Ambience_UpdateBands, Ambience_CreateBands */
extern Point g_bandPos;
extern Point g_bandSize;
s32 g_ambienceFamily;
extern void Object_DeleteArray(void *, s32);
void Actor_ApplyPos(void *self, s32 set, s32 *vec);
void Scenery_CreateSpriteParts(Scenery *scenery, s32 unused, s32 index, s32 color);
void Place_CheckTextureLoad(void *place_, void *loader_);
extern void Scenery_Follow();
extern s32 g_soundSpotRanges[];
s32 g_bandLayout;
s32 g_sceneryCount;
extern u8 g_scenery[];
void HandlerNode_Stop(void *, void *);
extern s32 SceneNode_ProbeHeight(void);
PlaceBaseVtbl *Task_GetVtbl();
extern s16 g_actorMoveVecZ[];
void Actor_MoveAxis(void *self, s16 *field, s32 value, s32 notify, s32 message);
extern s16 g_actorMoveVec[];
extern u16 g_sceneryPartCluts[];
extern u16 g_sceneryPartClutsY[];
void Stage_GetChunkPath(s32);
void Stage_GetChunkPathAt(s32, s32, s32);
void Scenery_DeleteParts();
ActorVtbl *Actor_GetVtbl(void);
ActorBaseVtbl *SceneNode_GetVtbl(void);
s32 g_ambienceTintColor;
AmbienceBand *g_ambienceTint;
s32 SoundSpot_CalcFade(SpotSlot *slot);
s32 Scenery_Tick(s32 mapPos, s32 ignored, s32 found);
void HandlerNode_Run(s32, s32);
PlaceRefs *g_placeRefs;
extern void SceneNode_RotateVector(void *, void *, void *);
s32 Actor_SnapToGround();
extern u8 g_stringListCursorColor[];
void *Heap_Alloc(s32 size);
GraphCtorVtbl *Graph_GetVtable(void);
void Place_StartFade(void *place_, s32 color, s32 channels, s32 duration, s32 watch);
extern u8 g_ambienceColors[];
extern s32 g_ambienceDepths[];
extern void Display_RotateRect(s32 *arg0, s32 arg1, s32 *arg2);
extern s32 g_clutCycleRectA[];
extern s32 g_clutCycleSpareA[];
extern s32 g_clutCycleRectB[];
extern s32 g_clutCycleSpareB[];
s32 g_placeStage;
extern void Sym_FreeSpy(void);
extern void Scenery_Teardown(void);
s32 g_sceneryMap;
s32 g_placeTicks;
s32 g_placeDayNumber;
s32 D_8008AC78;
extern s32 g_soundSpotSlot1;
Ambience *Ambience_Get(void);
extern SpotSlot *g_soundSpotSlots[];
void Heap_Free(void *);
TextPartVtbl *SceneryPart_GetVtbl(void);
extern s32 g_sceneryModelIndexes[];
extern s16 g_sceneryModelClut[];
PlaceObj *g_sceneryModels;
void *g_sceneryFont;
View *g_sceneryView;
void ModelObject_SetClut(void *, void *);
void Place_GetChunkPath(Place *place, s32 result, s32 col, s32 row);
PlaceVtbl *Place_GetVtbl(void);
SceneryVtbl *Scenery_GetVtbl(void);
extern AmbienceRecord *g_stageAmbience[];
extern Ambience g_ambience;
AmbienceRecord *Ambience_PickFamily(void);
extern void Ambience_Fill(Ambience *ambience, AmbienceRecord *record);
void Scenery_Build(void *self, s32 map, s32 origin);
void Scenery_RandomizeParams(void *origin, s32 height);
extern s32 g_sceneryHeights2;
extern u8 g_sceneryKind1Scale[];
extern SceneryParams g_sceneryParams;
s32 Sym_SpawnOrSpy(s32, void *, s32);
extern u8 g_sceneryPartRects[];
TextPartBaseVtbl *SpriteNode_GetVtbl(void);
void SoundSpot_Type11(void *slot, SpotState *state);
extern AmbienceBand *g_ambienceBands[];
extern void *Box_Create(s32 arg0, s32 arg1, s32 arg2);
extern s32 g_ambienceTintPos[];
extern s32 g_ambienceTintSize[];
SpotRecord *SoundSpot_FindInRange(void *pos, void *distance, s32 origin);
extern s32 g_soundSpotHandlers[];
extern s32 HandlerNode_Start(s32, void *, s32, void *, s32);
s32 Actor_FindGroundInRect(s32 actor, s32 delta, s32 pos, s32 rect, void *cell);
extern s32 strlen(u8 *s);
extern void *memcpy(void *dst, void *src, s32 n);
extern void *SceneryPart_New(s32 index, s32 blendRate, s32 font);
extern s32 rand(void);
extern u8 g_sceneryKind3Scales[];
extern s8 g_sceneryKind0Counts[];
void Scenery_SetPlaceRefs(s32 family, PlaceObj *models, void *font, View *view);
s32 *Scenery_CreateKind0(s32 *out, s32 count, void *origin);
s32 *Scenery_CreateKind1(s32 *out, s32 count, void *origin);
s32 *Scenery_CreateKind3(s32 *out, s32 origin);
s32 *Scenery_CreateKind2(s32 *out, s32 origin);
s32 g_ambienceIndex;
void *g_bandPalette;
u8 *g_bandClearColor;
extern s8 g_ambienceFamilyCycle[];
extern s8 g_ambienceFamilyCounts[];
extern u8 g_bandPaletteA[];
extern u8 g_bandPaletteB[];
extern AmbienceRecord *g_ambienceFamilies[];
extern void Scenery_AddOffset(Vec3 *out, Vec3 *a, Vec3 *b);
s32 g_sceneryViewY;
void Scenery_UpdateKind0(void *self, Vec3 *origin);
extern void Scenery_UpdateKind2(void *scenery, Vec3 *origin);
extern void Scenery_UpdateKind3(Scenery *scenery, Vec3 *origin);
extern u8 g_stringListRowColor[];
void Scenery_AttachPart(void *self, s32 parent, Vec3 *pos, s32 rotation, s32 scale);
void SceneNode_LinkModel(void *arg0, void *arg1);
void Scenery_PlaceKind0Parts(void *self, s32 move);
void Scenery_BuildKind2(void *self, s32 unused);
void Scenery_BuildKind3(Scenery *scenery, s32 unused);
extern s32 Label_Create(s32, s32, s32);
extern u8 g_pauseText[];
extern s32 g_pauseTextPos[];
extern s32 g_pauseTextColor[];
s32 g_stringListRowX;
s32 g_stringListRowY;
u8 *StringList_FormatRow(CardList *list, u8 *out, s32 i, s32 top, u8 *text);
void StringList_SetView(CardList *list, s32 top, s32 column, s32 cursor, s32 highlight);
s32 Actor_GetGroundRects(void *actor, void *outRects, void *outCells, void *cellInfo, s32 size);
s32 ModelObject_IsReady(s32);
void ModelBox_ShiftList(s32 **arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 Actor_ProbeGroundAt();
extern s32 g_sceneryHeights1;
extern u8 g_sceneryRotations[];
extern s32 g_sceneryKind2Offsets[];
extern s32 D_80087868[];
extern s32 D_80087880[];
extern u8 D_80087874[];
extern u8 D_8008785C[];
void Actor_MovePos(void *actor, s32 *delta);
extern s8 *File_JoinPath(s8 *, s8 *, s8 *, s8 *);
extern CardText *Tim_New(s32);
extern CardText *ScreenSprite_Create(CardText *, s32 *, s32);
extern s8 g_selectTimName[];
extern s8 g_cardDirName[];
extern s8 g_timExtension[];
extern s32 g_stringListBgPos[];
extern s32 g_stringListBgRect[];
void Scenery_RandomizeParamsDay7();
void *Scenery_New(s32 kind, s32 params, s32 map, s32 origin);
extern s32 g_sceneryHeights[];
extern u8 g_sceneryScales[];
s32 g_soundSpotNext;
extern SpotSlot g_soundSpotSlotData[];
void Ambience_CreateBands(void);
void Ambience_UpdateBands(void);
void Stage_CyclePalettes(void);
extern u8 g_stringListVtbl[];
extern u8 g_placeVtbl[];
extern u8 g_sceneryVtbl[];
extern u8 g_actorVtbl[];
extern u8 g_sceneryPartVtbl[];
extern s32 g_sceneryKind0Speeds[];
extern Vec3 D_8008782C;
extern s32 g_sceneryKind0Spin[];
extern void Sym_InitStage(s32 stage, StageMap *map, DreamSys *dreamSys, PlaceObj *arg3, PlaceObj *arg4);
extern void *Stage_GetGrid(s32 stage);
extern s32 g_placeViewpoint[];
extern s32 g_placeRefPoint[];
extern s32 g_placeMapMessageFilter[];
s32 g_placeProjectionOffset;
extern SpotTileExtra g_soundSpotTileExtras[];
extern SpotRecord *g_stageSoundSpots[];
extern u8 g_stageSoundSpotCounts[];
extern s32 g_stageBoxMargins[];
extern s32 D_80087150[];
Ambience *Scenery_Begin(s32 map, s32 stage, PlaceRefs *refs, s32 dayNumber, s32 unused);
s32 Stage_PickTexturePath(s32, s32, s32);
s32 Music_PickTrack(s32, s32);
void *Tix_Create(s32 path);
s32 SceneNode_SetRayHeightCheck(s32);
void Actor_MoveThenSnap(Actor *actor, void (*move)(void *, s32, s32), s32 value, s32 notify);
extern u8 g_sceneryKind3Colors[];
void Scenery_RandomizeParamsDay7(void);
void Ambience_ShiftRgb(u8 *out, u8 *rgb, s32 shift);
extern Vec3 D_800877EC;
extern s32 g_sceneryPartSpacing[];
void *Actor_New(void);
extern s32 D_80087430;
extern u8 g_sceneryKind2Colors[];

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116A4);

/* Slot 0x44: open the list with background CARD\SELECT.TIM and the rows in FONTICON. */
void StringList_Open(CardList *list, s32 parent) {
    s8 path[0x20];
    CardText *file;
    CardText *background;
    CardText *iconFile;

    if ((parent != 0) && (list->background == NULL)) {
        file = Tim_New((s32)File_JoinPath(path, g_selectTimName, g_cardDirName, g_timExtension));
        file->vt->upload(file);
        list->background = ScreenSprite_Create(file, g_stringListBgRect, 0);
        file->vt->delete_(file);
        background = list->background;
        background->vt->attach(background, parent, g_stringListBgPos);
        iconFile = Tim_New((s32)File_JoinPath(path, (s8 *)"FONTICON\0\0\0\0\0\0\0", g_cardDirName, g_timExtension));
        iconFile->vt->upload(iconFile);
        list->vt->createRows(list, parent, iconFile, list->top, list->column, list->cursor);
        iconFile->vt->delete_(iconFile);
    }
}

/* Slot 0x48: delete the rows and the background. */
void StringList_Close(CardList *list) {
    CardText *background;

    if (list->background != NULL) {
        list->vt->deleteRows(list);
        background = list->background;
        list->background = background->vt->delete_(background);
    }
}

void StringList_WatchPair(CardList *list, s32 first, s32 second, s32 owner) {
    list->vt->watch(list, first);
    list->vt->watch(list, second);
    list->owner = owner;
    list->mode = 0;
}

void StringList_UnwatchPair(CardList *list) {
    list->vt->unwatch(list, list->watchedA);
    list->vt->unwatch(list, list->watchedB);
    list->owner = 0;
}

void StringList_SetState(CardList *list, s32 mode) {
    list->modeTicks = 0;
    switch (mode) {
    case 2:
    case 3:
        list->vt->unwatch(list, list->watchedA);
        list->vt->close(list);
        list->mode = mode;
        break;
    case 4:
        list->vt->notify(list, list->mode);
        break;
    }
}

void StringList_Tick(CardList *list) {
    s32 mode;
    s32 ticks;

    mode = list->mode;
    if (mode >= 4) {
        return;
    }
    if (mode < 2) {
        return;
    }
    ticks = list->modeTicks;
    list->modeTicks = ticks + 1;
    if (ticks != 0) {
        list->vt->setMode(list, 4);
    }
}

/* Pad codes minus 4: 25 and 23 close the list (modes 2, 3), 5, 4, 18, 19 move and scroll it. */
void StringList_OnKey(CardList *list, s32 sender, s32 code) {
    void (*fn)(CardList *, s32, s32);
    u32 idx = code - 4;

    switch (idx) {
    case 21:
        list->vt->setBoxValue(list, 0x10, idx);
        list->vt->setMode(list, 2);
        return;
    case 19:
        list->vt->setBoxValue(list, 0x10, idx);
        list->vt->setMode(list, 3);
        return;
    case 1:
        fn = list->vt->scrollRight;
        break;
    case 0:
        fn = list->vt->scrollLeft;
        break;
    case 14:
        fn = list->vt->moveUp;
        break;
    case 15:
        fn = list->vt->moveDown;
        break;
    default:
        return;
    }
    fn(list, sender, idx);
}

void StringList_SetBoxValue(CardList *list, s32 value) {
    CardListOwner *owner = (CardListOwner *)list->owner;
    if (owner != NULL) {
        owner->vt->unk80(owner, value, 0x60, 0x60);
    }
}

/* Slot 0x7C: show one more character on the right while the longest row goes past 26. */
void StringList_ScrollRight(CardList *list) {
    if (list->background != 0 && (list->column + 0x1A) < list->width) {
        list->vt->drawRows(list, list->top, ++list->column, list->cursor, 1);
    }
}

/* Slot 0x80: back one character. */
void StringList_ScrollLeft(CardList *list) {
    s32 column;

    if (list->background != 0) {
        column = list->column - 1;
        if (column >= 0) {
            list->column = column;
            list->vt->drawRows(list, list->top, column, list->cursor, 1);
        }
    }
}

/* Slot 0x84: cursor up, scrolling when it is on the top row. */
void StringList_CursorUp(CardList *list) {
    s32 top;
    s32 cursor;

    if (list->background != 0) {
        if (list->cursor - 1 >= 0) {
            if (list->cursor - list->top > 0) {
                list->vt->moveCursor(list, 0, 1);
                return;
            }
            top = --list->top;
            cursor = --list->cursor;
            list->vt->drawRows(list, top, list->column, cursor, 1);
        }
    }
}

/* Slot 0x88: cursor down, scrolling past the fourth row. */
void StringList_CursorDown(CardList *list) {
    s32 top;
    s32 cursor;
    s32 aboveTop;

    if (list->background != 0) {
        cursor = list->cursor;
        if ((cursor + 1) < list->count) {
            top = list->top;
            aboveTop = top - 1;
            if ((cursor - aboveTop) < 4) {
                list->vt->moveCursor(list, 1, 1);
                return;
            }
            list->top = top + 1;
            list->vt->drawRows(list, top + 1, list->column, ++list->cursor, 1);
        }
    }
}

/* Slot 0x8C: build up to 4 row texts 10 pixels apart, then highlight the cursor row. */
void StringList_CreateRows(CardList *list, s32 parent, s32 font, s32 top, s32 column, s32 cursor) {
    u8 text[0x1C];
    s32 pos[4];
    s32 i;
    s32 n;
    CardText **row;
    CardText *created;
    CardText *obj;

    if (list->background != 0) {
        pos[0] = g_stringListRowX;
        pos[1] = g_stringListRowY;
        n = list->count;
        row = list->rows;
        if (n >= 5) {
            n = 4;
        }
        i = 0;
        if (n > 0) {
            do {
                StringList_FormatRow(list, text, i, top, (u8 *)column);
                created = (CardText *)Label_Create(font, 0x1A, (s32)text);
                *row = created;
                created->vt->attach(created, parent, pos);
                obj = *row;
                i += 1;
                obj->vt->setColor(obj, g_stringListRowColor);
                pos[1] += 0xA;
                row += 1;
            } while (i < n);
        }
        StringList_SetView(list, top, column, cursor, 1);
    }
}

/* Slot 0x90 */
void StringList_DeleteRows(CardList *list) {
    s32 i;
    s32 n;
    CardText *obj;

    if (list->background != 0) {
        n = list->count;
        if (n >= 5) {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            obj = list->rows[i];
            obj->vt->delete_(obj);
            list->rows[i] = NULL;
        }
    }
}

/* Slot 0x94: refill the row texts from top and column. */
void StringList_RedrawRows(CardList *list, s32 top, s32 column, s32 cursor, s32 notify) {
    u8 text[0x20];
    s32 i;
    s32 n;
    CardText **row;
    CardText *obj;

    if (list->background != 0) {
        row = list->rows;
        n = list->count;
        if (n >= 5) {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            StringList_FormatRow(list, text, i, top, column);
            obj = *row;
            obj->vt->setText(obj, text);
            row++;
        }
        StringList_SetView(list, top, column, cursor, 0);
        if (notify != 0) {
            list->vt->setBoxValue(list, 0);
        }
    }
}

/* Copy row (top + i) into out, padded with spaces to 26 characters. */
u8 *StringList_FormatRow(CardList *list, u8 *out, s32 i, s32 top, u8 *text) {
    s32 idx = top + i;
    s32 len;
    s32 j;

    len = strlen(text + list->offsets[idx]);
    if (len >= 0x1B) {
        len = 0x1A;
    }
    memcpy(out, text + list->offsets[idx], len);
    for (j = len; j < 0x1A; j++) {
        out[j] = 0x20;
    }
    out[0x1A] = 0;
    return out;
}

void StringList_SetView(CardList *list, s32 top, s32 column, s32 cursor, s32 highlight) {
    s32 row;
    CardText *obj;

    list->top = top;
    list->column = column;
    list->cursor = cursor;
    if (highlight != 0) {
        row = cursor - top;
        obj = list->rows[row];
        obj->vt->setColor(obj, g_stringListCursorColor, column, row);
    }
}

/* Slot 0x98: move the highlight one row down (down != 0) or up. */
void StringList_MoveHighlight(CardList *list, s32 down, s32 notify) {
    CardText **row;
    CardText *obj;

    if (list->background != 0) {
        row = &list->rows[list->cursor - list->top];
        obj = *row;
        obj->vt->setColor(obj, g_stringListRowColor);
        if (down != 0) {
            row++;
            list->cursor++;
        } else {
            row--;
            list->cursor--;
        }
        obj = *row;
        obj->vt->setColor(obj, g_stringListCursorColor);
        if (notify != 0) {
            list->vt->setBoxValue(list, 0);
        }
    }
}

s32 StringList_GetCursor(CardList *list) {
    return list->cursor;
}

CardListVtbl *StringList_GetVtbl(void) {
    return (CardListVtbl *)g_stringListVtbl;
}

/* Allocate a place (0x88 bytes) and construct it (slot 0x08); called by the dream runner DreamRunner_CreateStage. */
void *Place_New(s32 handlerList, s32 music, s32 font, s32 models, s32 stage) {
    void *place;

    place = Heap_Alloc(0x88);
    if (place != NULL) {
        Place_GetVtbl()->construct(place, handlerList, music, font, models, stage);
        return place;
    }
    return NULL;
}

/* Slot 0x08 */
void Place_Construct(Place *place, s32 handlerList, PlaceObj *music, void *font, PlaceObj *models, s32 stage) {
    Task_GetVtbl()->construct(place, 0, handlerList);
    place->vt = Place_GetVtbl();
    place->ready = 0;
    place->started = 0;
    place->texLoading = 1;
    place->music = music;
    place->stage = stage;
    place->refs.handlerList = handlerList;
    place->refs.font = font;
    place->refs.models = models;
    place->pauseOpen = 0;
    place->exitArmed = 0;
    place->vt->unk40(place);
}

/* Slot 0x0C */
void Place_Destruct(s32 place) {
    Task_GetVtbl(place)->destruct(place);
}

/*
 * Slot 0x38: a watched object sent a message. The first word of the sender's vtable is its
 * class id: DreamSys (0x1F34) goes to slot 0x90, ids ending in 0x164 (the fader) to 0xB0,
 * ids ending in 0x114 (the map) to 0xB4.
 */
void Place_OnNotify(Place *place, s32 **sender, s32 message) {
    s32 classId;

    Task_GetVtbl()->onNotify(place, sender, message);
    classId = **sender;
    if ((classId & 0xFFF) == 0x114) {
        place->vt->onMapNotify(place, sender, message);
    } else if ((classId & 0xFFF) == 0x164) {
        place->vt->onFaderNotify(place, sender, message);
    } else if ((classId & 0xFFFF) == 0x1F34) {
        place->vt->onDreamSysNotify(place, sender, message);
    }
}

void Place_Stub40(void) {
}

/* Slot 0x44: keep the DreamSys and register Place_GetChunkPath with the runner's object. */
void Place_Attach(Place *place, PlaceOwner *owner, DreamSys *dreamSys) {
    PlaceOwnerObj *obj;

    obj = owner->callbackObj;
    obj->vt->setCallback(obj, &Place_GetChunkPath, place);
    place->dreamSys = dreamSys;
    Task_GetVtbl()->attach(place, owner, 1);
    place->vt->watch(place, dreamSys);
}

void Place_GetChunkPath(Place *place, s32 result, s32 col, s32 row) {
    if (result >= 0) {
        Stage_GetChunkPath(place->stage);
    } else {
        Stage_GetChunkPathAt(place->stage, col, row);
    }
}

/* Slot 0x48 */
void Place_Detach(Place *place) {
    place->vt->unwatch(place, place->dreamSys);
    Task_GetVtbl()->detach(place);
}

/*
 * Slot 0x4C, when a stage loads: picks the music track (Music_PickTrack) and starts the
 * texture-set loader (Stage_PickTexturePath, Tix_Create), starts the scenery
 * (Scenery_Begin, which gives the ambience) and sets the state to 5.
 */
void Place_Load(Place *place, s32 viewDistance, Ambience *ambience, s32 ambienceGiven) {
    View *view;
    s32 mode;

    view = place->view;
    view->vtbl->detach(view);
    place->texLoading = 1;
    place->music->vt->unk5C(place->music, Music_PickTrack(place->stage, 0));
    place->texLoader = Tix_Create(Stage_PickTexturePath(place->stage, 0, place->dreamSys->vtbl->getDayNumber(place->dreamSys, 0)));
    view->vtbl->setCamera(view, place->dreamSys, g_placeViewpoint, g_placeRefPoint, 0);
    place->refs.view = view;
    place->ambience = Scenery_Begin((s32)place->map, place->stage, &place->refs, place->dreamSys->vtbl->getDayNumber(place->dreamSys, 0), 0);
    if (ambience != 0) {
        place->ambience = ambience;
    }
    place->unk4C = ambienceGiven;
    if (place->stage != 0) {
        place->unk40 = 0x10;
        place->unk44 = 3;
        mode = place->stage == 5;
        if (place->stage == 6) {
            mode = 1;
        }
        if (place->stage == 3) {
            mode = 1;
        }
        place->map->vtbl->unk134(place->map, NULL);
    } else {
        place->unk40 = 0x10;
        place->unk44 = 2;
        mode = 1;
        place->map->vtbl->unk134(place->map, D_80087150);
    }
    place->unk48 = viewDistance;
    if (viewDistance == 0) {
        place->unk48 = 0xA000;
    }
    SceneNode_SetRayHeightCheck(mode);
    place->dreamSys->vtbl->unkEC(place->dreamSys, g_stageBoxMargins[place->stage]);
    place->state = 5;
}

/* Slot 0x50: teardown (called without the place), free the scenery, stop the music object. */
void Place_Unload(Place *place) {
    PlaceObj *music;

    place->vt->teardown();
    Sym_FreeSpy();
    Scenery_Teardown();
    music = place->music;
    music->vt->unk48(music);
}

/* Slot 0x54 */
void Place_OnDisplay(Place *place, s32 sender, s32 event) {
    if (event == 2) {
        Place_CheckTextureLoad(place, place->texLoader);
    }
}

/*
 * Check the texture-set loader. When it failed (+0x80, a heap allocation returned 0) the set
 * is dropped and the time limit becomes elapsed + 30 s (discoveries "the 30-second dreams");
 * when it is done the ambience colour goes to it. Then, once the map is ready, start the place.
 */
void Place_CheckTextureLoad(void *place_, void *loader_) {
    PlaceTexLoader *loader = loader_;
    Place *place = place_;
    PlaceTexLoaderVtbl *vt;
    Ambience *ambience;
    u8 *color;

    if (place->texLoading != 0) {
        if (loader->failed != 0) {
            loader->vt->delete_(loader);
            place->texLoading = 0;
            place->vt->setup(place);
            place->dreamSys->vtbl->swapTimeLimit(place->dreamSys, place->dreamSys->vtbl->getElapsedSeconds(place->dreamSys) + 0x1E);
        } else if (loader->done != 0) {
            ambience = place->ambience;
            vt = loader->vt;
            if (ambience->mode != 2) {
                color = ambience->colorB;
            } else {
                color = ambience->colorA;
            }
            vt->apply(loader, color);
            loader->vt->delete_(loader);
            place->texLoading = 0;
            place->vt->setup(place);
        }
        if (place->texLoading != 0) {
            return;
        }
    }
    if (place->map->pendingSlots == 0 && place->started == 0) {
        place->ready = 1;
        place->vt->start(place);
    }
}

/* Slot 0x58, the pad handler: 33 START, 12 SELECT held, 22 TRIANGLE, 44 SELECT released (discoveries "the hidden exit"). */
void Place_OnPad(Place *place, s32 sender, s32 code) {
    PlaceVtbl *vt;
    void (*fn)();

    vt = place->vt;
    if (place->started != 0) {
        switch (code) {
        case 33:
            fn = vt->togglePause;
            break;
        case 12:
            fn = vt->armExit;
            break;
        case 22:
            fn = vt->confirmExit;
            break;
        case 44:
            fn = vt->disarmExit;
            break;
        default:
            return;
        }
        fn(place);
    }
}

/* Slot 0x5C, every tick once started: the pause window while it is open, else the update. */
void Place_Tick(Place *place) {
    if (place->started != 0) {
        place->ticks = place->ticks + 1;
        if (place->pauseOpen != 0) {
            place->vt->updatePause(place);
        } else {
            place->vt->update(place);
        }
    }
}

/* Slot 0x74, START */
void Place_TogglePause(Place *place) {
    PlaceVtbl *vt;

    vt = place->vt;
    if (place->pauseOpen != 0) {
        vt->disarmExit(place);
        vt->closePause(place);
    } else {
        vt->updatePause(place);
    }
}

void Place_Stub7C(void) {
}

/* Slot 0x80, after the texture set: hands the stage to the spawn code (Sym_InitStage) and sets up the map. */
void Place_Setup(Place *place) {
    View *view;
    StageMap *map;
    Ambience *ambience;
    PlaceObj *first;
    DreamSys *dreamSys;

    view = place->view;
    ambience = place->ambience;
    view->vtbl->detach(view);
    first = *place->unkC;
    view->vtbl->setProjection(view, ((((s32) *first->vt->unk7C(first, 0) / 2) * 5) / 3) + g_placeProjectionOffset);
    view->vtbl->setCamera(view, place->dreamSys, g_placeViewpoint, g_placeRefPoint, 0);
    Sym_InitStage(place->stage, place->map, place->dreamSys, place->unk34, place->unk10);
    map = place->map;
    place->vt->watch(place, map);
    map->vtbl->setAmbient(map, ambience->unk8, 0);
    map->vtbl->unkC4(map, 3, ambience->unk0, ambience->unk4);
    map->vtbl->setGrid(map, Stage_GetGrid(place->stage));
    dreamSys = place->dreamSys;
    dreamSys->vtbl->unk4C(dreamSys, map);
    map->vtbl->setViewDistance(map, place->unk48);
    map->vtbl->setMessageFilter(map, g_placeMapMessageFilter);
}

/* Slot 0x84 */
void Place_Teardown(Place *place) {
    place->vt->closePause(place);
    place->dreamSys->vtbl->unkFC(place->dreamSys);
    place->dreamSys->vtbl->unk50(place->dreamSys);
    place->view->vtbl->detach(place->view);
    place->vt->unwatch(place, place->map);
}

/* Slot 0x88: the place starts; the view takes the ambience colours and the fader the day's colour. */
void Place_Start(Place *place) {
    s32 color;
    DreamSys *dreamSys;
    StageMap *map;
    View *view;
    Ambience *ambience;
    Fade *fader;
    s32 flashbackMode;

    place->started = 1;
    place->dreamSys->vtbl->unkF8(place->dreamSys, place->unk44, place->unk40);
    map = place->map;
    map->vtbl->activate(map);
    view = place->view;
    ambience = place->ambience;
    view->vtbl->setLightMode(view, 1);
    view->vtbl->setClearColor(view, ambience->colorA);
    view->vtbl->setFogNear(view, ambience->depth);
    view->vtbl->setFogColor(view, ambience->mode != 1 ? ambience->colorB : ambience->colorA);
    view->vtbl->setUnkB4(view, 0);
    view->vtbl->setUnkB8(view, 1);
    fader = view->vtbl->getOverlay(view);
    place->vt->watch(place, fader);
    dreamSys = place->dreamSys;
    flashbackMode = dreamSys->vtbl->setFlashbackMode(dreamSys, &color, -1);
    fader->vtbl->setTint(fader, flashbackMode, flashbackMode != 0 ? 3 : 0);
    fader->vtbl->startIn(fader, place->unk10, flashbackMode != 0 ? color : -1, 0);
}

/* Slot 0x8C, every tick while not paused: the scenery tick at the map's position. */
void Place_Update(Place *place) {
    StageMap *map = place->map;
    Scenery_Tick((s32)map->vtbl->getLocation(map, 0, 0), 0, 0);
}

/* Slot 0x90: DreamSys messages 10 to 17 go to slots 0x94 to 0xAC while the state is 0. */
void Place_OnDreamSysNotify(Place *place, s32 sender, s32 message) {
    s32 event;

    if (place->state == 0) {
        event = message - 10;
        switch (event) {
            case 0:
                place->vt->onEvent10(place, sender, event);
                break;
            case 1:
                break;
            case 2:
                place->vt->onEvent12(place, sender, event);
                break;
            case 3:
                place->vt->onEvent13(place, sender, event);
                break;
            case 4:
                place->vt->onEvent14(place, sender, event);
                break;
            case 5:
                place->vt->onEvent15(place, sender, event);
                break;
            case 6:
                place->vt->onEvent16(place, sender, event);
                break;
            case 7:
                place->vt->onEvent17(place, sender, event);
                break;
        }
    } else if (message >= 9) {
        place->dreamSys->transition = 0;
    }
}

/* Slot 0x94: state 4; out of a flashback, (ticks + stage) & 3 picks no fade (notify 4) or colour 0, 4 or 7. */
void Place_OnTimeUp(Place *place) {
    s32 color;
    s32 phase;
    s32 pick;
    s32 flashbackMode;
    s32 duration;
    DreamSys *dreamSys;

    dreamSys = place->dreamSys;
    place->state = 4;
    flashbackMode = dreamSys->vtbl->setFlashbackMode(dreamSys, &color, -1);
    if (flashbackMode == 0) {
        phase = (place->ticks + place->stage) & 3;
        pick = phase;
        if (phase == 0) {
            place->vt->notify(place, 4);
            return;
        }
        duration = 0xA;
        switch (pick) {
        case 1:
            color = 0;
            break;
        case 2:
            color = 4;
            break;
        case 3:
            color = 7;
            duration = 5;
            break;
        }
        Place_StartFade(place, color, 0, duration, 1);
    } else {
        Place_StartFade(place, 0, 0, 5, 1);
    }
}

/* Slot 0x98: state 5, fade to the dream colour (slot 0x200), or go to slot 0x9C when DreamSys +0x164 is negative. */
void Place_OnLinkDynamic(Place *place) {
    DreamSys *dreamSys;

    if (place->dreamSys->stage < 0) {
        place->vt->onEvent13(place);
    } else {
        place->state = 5;
        dreamSys = place->dreamSys;
        Place_StartFade(place, dreamSys->vtbl->getDreamColor(dreamSys), 0, 0xA, 1);
        dreamSys = place->dreamSys;
        dreamSys->vtbl->unkFC(dreamSys);
    }
}

/* Slot 0x9C: state 6, a 30-tick fade to the dream colour. */
void Place_OnLinkStatic(Place *place) {
    DreamSys *dreamSys;

    dreamSys = place->dreamSys;
    place->state = 6;
    Place_StartFade(place, dreamSys->vtbl->getDreamColor(dreamSys), 0, 0x1E, 1);
    dreamSys = place->dreamSys;
    dreamSys->vtbl->unkFC(dreamSys);
}

/* Slot 0xA0: state 7, fade to the day's colour. */
void Place_OnNextFlashback(Place *place) {
    s32 color;
    DreamSys *dreamSys;

    dreamSys = place->dreamSys;
    place->state = 7;
    dreamSys->vtbl->setFlashbackMode(dreamSys, &color, -1);
    Place_StartFade(place, color, 0, 5, 1);
    dreamSys = place->dreamSys;
    dreamSys->vtbl->unkFC(dreamSys);
}

/* Slot 0xA4 */
void Place_OnLink15(Place *place) {
    place->state = 8;
    Place_StartFade(place, 0, 0, 6, 1);
    place->dreamSys->vtbl->unkF4(place->dreamSys, 1);
}

/* Slot 0xA8 */
void Place_OnLink16(Place *place) {
    place->state = 10;
    Place_StartFade(place, 0, 0, 6, 1);
    place->dreamSys->vtbl->unk13C(place->dreamSys, 2);
    place->dreamSys->vtbl->unkF4(place->dreamSys, 2);
}

/* Slot 0xAC */
void Place_OnLink17(Place *place) {
    place->vt->notify(place, 0xB);
}

/* Start the view's fader towards a colour index (0 to 7), watched when asked. */
void Place_StartFade(void *place_, s32 color, s32 channels, s32 duration, s32 watch) {
    Place *place = place_;
    View *view;
    Fade *fader;

    view = place->view;
    fader = view->vtbl->getOverlay(view);
    if (duration != 0) {
        fader->vtbl->setStep(fader, duration);
    }
    if (watch != 0) {
        place->vt->watch(place, fader);
    }
    fader->vtbl->startOut(fader, place->unk10, color, channels);
}

/* Slot 0xB0: the fader is done (5: back to state 0; 6: its colour goes to the view, state 10 becomes 4). */
void Place_OnFaderNotify(Place *place, Fade *fader, s32 message) {
    void *color;

    switch (message) {
    case 5:
        place->vt->unwatch(place, fader);
        place->dreamSys->vtbl->unkF4(place->dreamSys, 0);
        place->state = 0;
        break;
    case 6:
        place->vt->unwatch(place, fader);
        color = fader->vtbl->getColor(fader);
        place->view->vtbl->setClearColor(place->view, color);
        if (place->state == 5 || place->state == 8) {
        } else if (place->state == 10) {
            place->dreamSys->vtbl->unk17C(place->dreamSys, 1);
            place->dreamSys->vtbl->unkF4(place->dreamSys, 0);
            place->state = 4;
        }
        place->vt->notify(place, place->state);
        break;
    }
}

/* Slot 0xB4: map message 7 runs slot 0xB8 (called without arguments; a0 still holds the place). */
void Place_OnMapNotify(Place *place, s32 sender, s32 message) {
    if (message == 7) {
        place->vt->spawnCell();
    }
}

/* Slot 0xB8: spawn the characters of the map cell under the dreamer (Sym_SpawnOrSpy, discoveries "Grey Man spawn"). */
s32 Place_SpawnCell(Place *place) {
    s32 chunkKey;
    StageMap *map;
    DreamSys *dreamSys;
    MapChunk *chunk;
    MapSlot *slot;
    s32 dayNumber;
    s32 spawned;

    map = place->map;
    slot = map->vtbl->currentSlot(map, &chunkKey);
    dreamSys = place->dreamSys;
    dayNumber = dreamSys->vtbl->getDayNumber(dreamSys, 0);
    spawned = Sym_SpawnOrSpy(slot->chunk->entities, &chunkKey, dayNumber);
    slot->spawned = (Object *)spawned;
    if (spawned != 0) {
        return 0;
    }
    chunk = slot->chunk;
    chunk->vtbl->freeEntities(chunk);
    return 1;
}

void Place_StubBC(void) {
}

/* Slot 0xC0, SELECT held: arms the exit while the pause is open and the state is 0. */
void Place_ArmExit(Place *place) {
    if (place->pauseOpen != 0 && place->state == 0) {
        place->exitArmed = 1;
    }
}

/* Slot 0xC4, SELECT released */
void Place_DisarmExit(Place *place) {
    place->exitArmed = 0;
}

/* Slot 0xC8, TRIANGLE: when armed, close the pause and send 0xD (DreamSys_EndDay(2), a new game). */
void Place_ConfirmExit(Place *place) {
    if (place->exitArmed != 0) {
        place->vt->closePause(place);
        place->vt->notify(place, 0xD);
    }
}

/* Slot 0xCC, never called: send 0xC (DreamSys_EndDay(1), the day is restored). */
void Place_ExitNoRecord(Place *place) {
    if (place->exitArmed != 0) {
        place->vt->closePause(place);
        place->vt->notify(place, 0xC);
    }
}

/* Slot 0xD0: open the pause window ("Pause"), and suspend the place's objects on its fourth tick. */
void Place_UpdatePause(Place *place) {
    s32 ticks = place->pauseOpen;

    if (ticks == 0) {
        place->pauseText = (PlaceObj *)Label_Create((s32)place->refs.font, 5, (s32)g_pauseText);
        place->pauseText->vt->unk4C(place->pauseText, place->map, g_pauseTextPos);
        place->pauseText->vt->unkB8(place->pauseText, g_pauseTextColor);
        place->pauseOpen = 1;
        return;
    }
    place->pauseOpen = ticks + 1;
    if (ticks == 4) {
        place->view->vtbl->setUnkB8(place->view, 0);
        place->unk10->vt->unk4C(place->unk10);
        place->music->vt->unk4C(place->music);
        place->unk34->vt->unk88(place->unk34);
    }
}

/* Slot 0xD4: close the pause window and resume the objects. */
void Place_ClosePause(Place *place) {
    if (place->pauseOpen != 0) {
        place->pauseText->vt->delete_(place->pauseText);
    }
    place->unk34->vt->unk8C(place->unk34);
    place->music->vt->unk50(place->music);
    place->unk10->vt->unk50(place->unk10);
    place->view->vtbl->setUnkB8(place->view, 1);
    place->pauseOpen = 0;
}

PlaceVtbl *Place_GetVtbl(void) {
    return (PlaceVtbl *)g_placeVtbl;
}

/*
 * When a place loads (Place slot 0x4C): keep its map, stage, refs and day number, reset the
 * tick counter g_placeTicks and the two spot slots (g_soundSpotSlots[0..1], g_soundSpotSlot1 is [1]), and
 * return the ambience. Runs only while no place is up (g_sceneryMap is 0 again after Scenery_Teardown).
 */
Ambience *Scenery_Begin(s32 map, s32 stage, PlaceRefs *refs, s32 dayNumber, s32 unused) {
    s32 *slot;
    s32 n;

    if (g_sceneryMap == 0) {
        n = 1;
        slot = &g_soundSpotSlot1;
        g_sceneryMap = map;
        g_placeStage = stage;
        g_placeRefs = refs;
        g_ambienceFamily = -1;
        g_placeDayNumber = dayNumber;
        D_8008AC78 = unused;
        g_placeTicks = 0;
        do {
            *slot = 0;
            n -= 1;
            slot -= 1;
        } while (n >= 0);
        return Ambience_Get();
    }
    return 0;
}

/* The stage's fixed ambience record, else one of the day's family (Ambience_PickFamily), into g_ambience. */
Ambience *Ambience_Get(void) {
    AmbienceRecord *record;

    record = g_stageAmbience[g_placeStage];
    if (record == NULL) {
        record = Ambience_PickFamily();
    }
    Ambience_Fill(&g_ambience, record);
    if (record->depth >= 4) {
        g_ambienceTintColor = (s32)(g_ambienceColors + record->colorB * 3);
    }
    return &g_ambience;
}

void Ambience_Fill(Ambience *ambience, AmbienceRecord *record) {
    ambience->colorA = g_ambienceColors + record->colorA * 3;
    ambience->colorB = g_ambienceColors + record->colorB * 3;
    ambience->depth = g_ambienceDepths[record->depth];
    ambience->mode = record->mode;
}

/* The extra ambience object, when the record's depth is 4 or more. */
void Ambience_CreateTint(void) {
    AmbienceBand *band;
    View *view;

    if (g_ambienceTintColor != 0) {
        band = Box_Create((s32)g_ambienceTintSize, g_ambienceTintColor, 0);
        g_ambienceTint = band;
        band->vt->setSemiTrans(band, 1);
        g_ambienceTint->vt->setBlendMode(g_ambienceTint, 0);
        view = g_placeRefs->view;
        g_ambienceTint->vt->attach(g_ambienceTint, view->vtbl->getOverlay(view), g_ambienceTintPos);
    }
}

void Ambience_DeleteTint(void) {
    if (g_ambienceTintColor != 0) {
        g_ambienceTint->vt->delete_(g_ambienceTint);
        g_ambienceTintColor = 0;
    }
}

/*
 * The ambience family of the dream: g_ambienceFamilyCycle[(day number + stage) & 15], a 16-entry cycle over
 * 4 families, then record (day number + stage) % count (work/hunt6/C-notes-note.md). Family 0
 * also picks the band palette and, for records 0 to 5, the band layout (1 or 2).
 */
AmbienceRecord *Ambience_PickFamily(void) {
    s32 sum;
    s32 family;
    s32 index;
    AmbienceRecord *record;
    void *palette;

    sum = g_placeDayNumber + g_placeStage;
    family = g_ambienceFamilyCycle[sum & 0xF];
    g_ambienceFamily = family;
    index = sum % g_ambienceFamilyCounts[family];
    g_ambienceIndex = index;
    record = g_ambienceFamilies[family] + index;
    if (family == 0) {
        g_bandClearColor = g_ambienceColors + record->colorA * 3;
        palette = g_bandPaletteB;
        if (record->colorB != 0x12) {
            palette = g_bandPaletteA;
        }
        g_bandPalette = palette;
        if (index < 4) {
            g_bandLayout = 1;
        } else if (index < 6) {
            g_bandLayout = 2;
        }
    }
    return record;
}

/* Make the 18 bands (run again by every first tick: the old ones are not freed, work/hunt6/F-findings.md). */
void Ambience_CreateBands(void) {
    Point layout[2];
    s32 i;
    AmbienceBand *band;
    View *view;

    if (g_bandLayout != 0) {
        layout[0] = g_bandPos;
        if (g_bandLayout == 2) {
            layout[0].y += 0x1E;
        }
        layout[1] = g_bandSize;
        g_ambienceBands[0] = Box_Create((s32)&layout[1], (s32)g_bandPalette, 0x1FFF);
        for (i = 1; i < 0x12; i++) {
            band = Box_Create((s32)&layout[1], (s32)g_bandPalette + i * 3, 0x1FFF);
            g_ambienceBands[i] = band;
            band->vt->attach(band, (s32)g_ambienceBands[0], layout);
            layout[0].y += 3;
            layout[1].y -= 7;
        }
        view = g_placeRefs->view;
        g_ambienceBands[0]->vt->attach(g_ambienceBands[0], view->vtbl->getOverlay(view), layout);
    }
}

/* Every tick: shift the band colours and positions with the view's height. */
void Ambience_UpdateBands(void) {
    u8 rgb[8];
    Point pos;
    View *view;
    AmbienceBand **band;
    s32 shift;
    s32 off;
    s32 i;

    if (g_bandLayout == 0) {
        return;
    }
    view = g_placeRefs->view;
    shift = ((view->viewpoint.y - view->refPoint.y) / 600) * 3;
    if (shift > 0) {
        pos = g_bandPos;
        i = 0;
        if (g_bandLayout == 2) {
            pos.y += 0x1E;
        }
        band = g_ambienceBands;
        off = 0;
        pos.y += shift * 3;
        for (; i < 18; i++) {
            Ambience_ShiftRgb(rgb, g_bandPalette + off, shift);
            (*band)->vt->setColor(*band, 1, rgb);
            (*band)->vt->setPos(*band, &pos);
            off += 3;
            pos.y += 3;
            band++;
        }
        Ambience_ShiftRgb(rgb, g_bandClearColor, shift);
        view->vtbl->setClearColor(view, rgb);
    }
}

/* out = rgb with red and green lowered and blue raised by shift. */
void Ambience_ShiftRgb(u8 *out, u8 *rgb, s32 shift) {
    out[0] = rgb[0] - shift;
    out[1] = rgb[1] - shift;
    out[2] = rgb[2] + shift;
}

void Ambience_DeleteBands(void) {
    if (g_bandLayout != 0) {
        Object_DeleteArray(g_ambienceBands, 0x12);
        g_bandLayout = 0;
    }
}

/*
 * First tick: the scenery objects into g_scenery around origin, g_sceneryCount of them
 * (work/hunt6/F-findings.md): count of kind 0 from g_sceneryKind0Counts, kind 1 up to 16 for family 2,
 * plus one of kind 3 for family 0 or of kind 2 for family 2.
 */
void Scenery_CreateAll(s32 origin) {
    s32 *end;
    s32 extra;
    s32 count;

    if (g_ambienceFamily >= 0) {
        Scenery_SetPlaceRefs(g_ambienceFamily, g_placeRefs->models, g_placeRefs->font, g_placeRefs->view);
        count = g_sceneryKind0Counts[rand() & 3];
        extra = (g_ambienceFamily == 2) ? (0x10 - count) : 0;
        g_sceneryCount = count + extra;
        end = Scenery_CreateKind1(Scenery_CreateKind0(g_scenery, count, origin), extra, (void *)origin);
        if (g_ambienceFamily == 0) {
            Scenery_CreateKind3(end, origin);
            g_sceneryCount += 1;
        } else if (g_ambienceFamily == 2) {
            Scenery_CreateKind2(end, origin);
            g_sceneryCount += 1;
        }
    }
}

/* Every tick: slot 0xEC (Scenery_Update) of every scenery object. */
void Scenery_UpdateAll(s32 origin) {
    s32 i;
    Scenery **objs;

    if (g_ambienceFamily >= 0) {
        objs = (Scenery **)g_scenery;
        for (i = 0; i < g_sceneryCount; i++) {
            Scenery *obj = objs[i];
            obj->vt->update(obj, origin);
        }
    }
}

void Scenery_DeleteAll(void) {
    if (g_ambienceFamily >= 0) {
        Object_DeleteArray(g_scenery, g_sceneryCount);
    }
}

/* When the place goes (Place slot 0x50): free the extra object, the bands, the scenery and the spots. */
void Scenery_Teardown(void) {
    s32 i;

    Ambience_DeleteTint();
    Ambience_DeleteBands();
    Scenery_DeleteAll();
    for (i = 0; i < 2; i++) {
        g_soundSpotSlots[i] = (SpotSlot *)SoundSpot_Release(g_soundSpotSlots[i]);
    }
    if (g_sceneryMap != 0) {
        g_sceneryMap = 0;
    }
}

/* Kind 0: count objects at random offsets (Scenery_RandomizeParamsDay7 on day numbers divisible by 7, else Scenery_RandomizeParams). */
s32 *Scenery_CreateKind0(s32 *out, s32 count, void *origin) {
    void (*randomize)(void *, s32);
    s32 i;
    s32 height;

    g_sceneryParams.variant = rand() % 7;
    g_sceneryParams.scale = &g_sceneryScales[((u32)rand() % 5) * 12];
    height = (u32)rand() % 5;
    if (height != 0) {
        height = g_sceneryHeights[height];
    }

    randomize = Scenery_RandomizeParamsDay7;
    if (g_placeDayNumber % 7 != 0) {
        randomize = Scenery_RandomizeParams;
    }

    for (i = 0; i < count; i++) {
        randomize(origin, height);
        *out = (s32)Scenery_New(0, (s32)&g_sceneryParams, g_sceneryMap, (s32)origin);
        out++;
    }
    return out;
}

/* Kind 1 */
s32 *Scenery_CreateKind1(s32 *out, s32 count, void *origin) {
    s32 i;
    s32 height = g_sceneryHeights2;

    g_sceneryParams.scale = g_sceneryKind1Scale;
    for (i = 0; i < count; i++) {
        Scenery_RandomizeParams(origin, height);
        *out = Scenery_New(1, &g_sceneryParams, g_sceneryMap, origin);
        out++;
    }
    return out;
}

/* Kind 3, one object: a fixed offset with the second band palette, else a random one behind the origin. */
s32 *Scenery_CreateKind3(s32 *out, s32 origin) {
    Scenery_RandomizeParams((void *)origin, g_sceneryHeights2);
    if (g_bandLayout != 0 && g_bandPalette == g_bandPaletteB) {
        g_sceneryParams.x = 0xFFFF5000;
        g_sceneryParams.y = -0x2000;
        g_sceneryParams.z = 0;
        g_sceneryParams.color = g_sceneryKind3Colors + 3;
    } else {
        if (g_sceneryParams.z > 0) {
            g_sceneryParams.z = -g_sceneryParams.z;
        }
        if (g_sceneryParams.z < -0x7800) {
            g_sceneryParams.z = -0x7800;
        }
        g_sceneryParams.color = g_sceneryKind3Colors + ((u32)rand() % 3) * 3;
    }
    g_sceneryParams.rotation = g_sceneryRotations;
    *out++ = (s32)Scenery_New(3, (s32)&g_sceneryParams, g_sceneryMap, origin);
    return out;
}

/* Kind 2, one object; the word after unk1C gets day number % 20 (or D_80087430 when it is 0). */
s32 *Scenery_CreateKind2(s32 *out, s32 origin) {
    ParamWord *p;
    s32 *q;
    s32 x;
    s32 v;

    v = (s32)(g_sceneryKind2Colors + ((u32)rand() % 3) * 3);
    p = (ParamWord *)&g_sceneryParams.color;
    p->v = v;
    p++;
    if (g_placeDayNumber % 20) {
        x = D_80087430;
    } else {
        x = g_placeDayNumber % 20;
    }
    p->v = x;
    Scenery_RandomizeParams((void *)origin, g_sceneryHeights2);
    q = (s32 *)&g_sceneryParams.rotation;
    *q = (s32)g_sceneryRotations;
    g_sceneryParams.variant = rand() % 6;
    *out++ = (s32)Scenery_New(2, (s32)&g_sceneryParams, g_sceneryMap, origin);
    return out;
}

/* Random offset: x and z in -22..22 tiles (<< 11), y = height (or one of g_sceneryHeights when 0). */
void Scenery_RandomizeParams(void *origin, s32 height) {
    if (height == 0) {
        height = g_sceneryHeights[rand() & 3];
    }
    g_sceneryParams.y = height;
    g_sceneryParams.x = (rand() % 23) << 11;
    if (rand() & 1) {
        g_sceneryParams.x = -g_sceneryParams.x;
    }
    g_sceneryParams.z = (rand() % 23) << 11;
    if (rand() & 1) {
        g_sceneryParams.z = -g_sceneryParams.z;
    }
    g_sceneryParams.rotation = g_sceneryRotations + ((u32)rand() % 7) * 12;
    g_sceneryParams.direction = rand() % 5;
}

/* Day numbers divisible by 7: x in 0..19 tiles, z 0xA000, -0x6000 or 0x800 by day number % 3. */
void Scenery_RandomizeParamsDay7(void) {
    s32 v;
    s32 m;

    rand();
    g_sceneryParams.y = g_sceneryHeights1;
    v = rand();
    g_sceneryParams.z = 0xA000;
    g_sceneryParams.x = (v % 20) << 11;
    m = g_placeDayNumber % 3;
    if (m == 1) {
        g_sceneryParams.z = 0xFFFF6000;
    } else if (m == 2) {
        g_sceneryParams.z = 0x800;
    }
    g_sceneryParams.rotation = g_sceneryRotations + ((u32)rand() % 7) * 12;
    g_sceneryParams.direction = rand() % 5;
}

/* Hold the next free spot in range of origin in slot and register its handler. */
SpotSlot *SoundSpot_Acquire(SpotSlot *slot, s32 *found, s32 origin, s32 unused) {
    SpotRecord *record;

    record = SoundSpot_FindInRange(slot->pos, &slot->distance, origin);
    if (record != NULL) {
        slot->record = record;
        HandlerNode_Start(g_placeRefs->handlerList, &slot->node, record->range, slot, g_soundSpotHandlers[record->range]);
        if (record->range == *found) {
            *found = -record->range;
        }
        record->range = -record->range;
        return slot;
    }
    return NULL;
}

/* Walk the stage's spots from g_soundSpotNext and return the first free one within its range of origin. */
SpotRecord *SoundSpot_FindInRange(void *pos, void *distance, s32 origin) {
    SpotQuery query;
    SpotRecord *record;
    s32 *from;
    s32 i;
    s32 n;
    s32 dx;
    s32 dz;
    s32 dist;

    from = (s32 *)origin;
    if (from != NULL) {
        n = g_stageSoundSpotCounts[g_placeStage] - g_soundSpotNext;
        record = g_stageSoundSpots[g_placeStage] + g_soundSpotNext;
        for (i = 0; i < n; i++, record++) {
            g_soundSpotNext++;
            if (record->range > 0) {
                query.a = record->tile;
                query.b = g_soundSpotTileExtras[record->idx];
                (*(void (**)(s32, void *, s32))((u8 *)*(s32 *)g_sceneryMap + 0xE8))(g_sceneryMap, pos, (s32)&query);
                dx = ((s32 *)pos)[0] - from[0];
                if (dx < 0) {
                    dx = ~dx + 1;
                }
                dz = ((s32 *)pos)[2] - from[2];
                dist = dx + (dz < 0 ? ~dz + 1 : dz);
                *(s32 *)distance = dist;
                if (dist < g_soundSpotRanges[record->range]) {
                    return record;
                }
            }
        }
    }
    return NULL;
}

/* Release a slot: unregister its handler and free its spot. */
s32 SoundSpot_Release(SpotSlotU *slot) {
    HandlerNode_Stop((void *)g_placeRefs->handlerList, &slot->node);
    slot->record->range = -slot->record->range;
    return 0;
}

s32 SoundSpot_Update(s32 slot, void *origin, s32 unused) {
    if (SoundSpot_IsInRange(slot, origin) != 0) {
        HandlerNode_Run(g_placeRefs->handlerList, slot + 0x14);
        return 1;
    }
    return 0;
}

/* Is the held spot still within its range of origin (the range is negative while held)? */
s32 SoundSpot_IsInRange(SpotSlot *slot, s32 *origin) { s32 dx,dz,d; if (origin != NULL) {
    dx = slot->pos[0] - origin[0];
    if (dx < 0) dx = ~dx + 1;
    dz = slot->pos[2] - origin[2];
    d = dx + (dz < 0 ? ~dz + 1 : dz);
    slot->distance = d;
    if (d < g_soundSpotRanges[-slot->record->range]) return 1; } return 0; }

/*
 * The scenery tick (Place slot 0x8C), with the map position of the dreamer. On the first tick
 * after a place starts (g_placeTicks reads 0) it makes the extra object, the bands and the
 * scenery; zeroing g_placeTicks makes them again without freeing the old ones (the "location_time"
 * leak, work/hunt6/F-findings.md). Then it updates them and the two spot slots, and returns the
 * range of a spot just taken when it equals found.
 */
s32 Scenery_Tick(s32 mapPos, s32 ignored, s32 found) {
    s32 posBuf[4];
    void *origin;
    s32 i;
    s32 unused;
    SpotSlot **slot;

    origin = 0;
    if (mapPos != 0) {
        origin = posBuf;
        (*(void (**)(s32, void *, s32))((u8 *)*(s32 *)g_sceneryMap + 0xE8))(g_sceneryMap, origin, mapPos);
    }
    if (g_placeTicks++ == 0) {
        Ambience_CreateTint();
        Ambience_CreateBands();
        Scenery_CreateAll((s32)origin);
    }
    Ambience_UpdateBands();
    Scenery_UpdateAll((s32)origin);
    Stage_CyclePalettes();
    g_soundSpotNext = 0;
    slot = g_soundSpotSlots;
    for (i = 0; i < 2; i++, slot++) {
        if (*slot != NULL) {
            if (SoundSpot_Update(*slot, origin, ignored) == 0) {
                *slot = (SpotSlot *)SoundSpot_Release(*slot);
            }
        } else {
            *slot = (SpotSlot *)SoundSpot_Acquire(&g_soundSpotSlotData[i], &found, origin, ignored);
        }
    }
    return found;
}

void Stage_CyclePalettes(void) {
    if (g_placeStage == 2) {
        Display_RotateRect(g_clutCycleRectA, 1, g_clutCycleSpareA);
    } else if (g_placeStage >= 3 && g_placeStage < 6) {
        Display_RotateRect(g_clutCycleRectB, 1, g_clutCycleSpareB);
    }
}

/* Spot handlers (table g_soundSpotHandlers, by range): slot is the SpotSlot, state the handler's state. */
void SoundSpot_Type1(void *slot, SpotState *state) {
    s32 tick;

    state->level = SoundSpot_CalcFade(slot);
    tick = state->tick;
    if (tick == 0) {
        state->sound0 = 7;
        state->octave0 = 0;
    } else if (tick == 2) {
        state->sound1 = 7;
        state->octave1 = 0;
    } else if (tick == 5) {
        state->sound2 = 7;
        state->octave2 = 0;
    } else if (tick >= 8) {
        state->tick = -1;
    }
}

void SoundSpot_Type2(void *slot, SpotState *state) {
    state->level = SoundSpot_CalcFade(slot);
    if (state->tick == 0) {
        state->sound0 = 0x18;
        state->octave0 = -2;
        return;
    }
    if (state->tick >= 0x401) {
        state->tick = -1;
    }
}

void SoundSpot_Type3(void *slot, SpotState *state) {
    s32 tick;

    state->level = SoundSpot_CalcFade(slot);
    tick = state->tick;
    if (tick == 0) {
        state->sound0 = 0xC;
        state->octave0 = 2;
        return;
    }
    if (tick >= 5) {
        state->tick = -1;
    }
}

void SoundSpot_Type4(void *slot, SpotState *state) {
    state->level = SoundSpot_CalcFade(slot);
    if (state->tick % 20 == 0) {
        state->sound0 = 0x1E;
        state->volume0 = 0x20;
        state->octave0 = 0;
        state->endVolume0 = 0xA;
    }
    if (state->tick % 400 == 0) {
        state->sound1 = 0x1E;
        state->octave1 = 0;
    }
    state->sound2 = 6;
    state->volume2 = 0x20;
    state->octave2 = 0;
    state->endVolume2 = 0xA;
}

void SoundSpot_Type5(void *slot, SpotState *state) {
    state->level = SoundSpot_CalcFade((SpotSlot *)slot);
    if (state->tick % 3 == 0) {
        state->sound0 = 0x1E;
        state->octave0 = 0;
    }
    if (state->tick % 5 == 0) {
        state->sound1 = 0x1E;
        state->octave1 = 0;
        state->volume1 = 0x18;
        state->endVolume1 = 0x18;
    }
    if (state->tick % 7 == 0) {
        state->sound0 = 0x1E;
        state->octave0 = 0;
    }
    state->sound2 = 6;
    state->octave2 = 1;
    state->volume2 = 0x2A;
    state->endVolume2 = 0xA;
}

void SoundSpot_Type6(void *slot, SpotState *state) {
    state->level = SoundSpot_CalcFade((SpotSlot *)slot);
    if (state->tick == 0) {
        state->sound0 = 0x1E;
        state->octave0 = -1;
        return;
    }
    if (state->tick < 50 && state->tick % 5 == 4) {
        state->sound1 = 0x1E;
        state->octave1 = 0;
        state->endVolume1 = state->volume1 -= state->tick * 2;
        return;
    }
    if (state->tick >= 0x65 && state->tick < 0x6E) {
        state->sound2 = 0xD;
        state->octave2 = 1;
        return;
    }
    if (state->tick >= 0xC9) {
        state->tick = -1;
    }
}

void SoundSpot_Type7(void *slot, SpotState *state) {
    s32 tick;

    state->level = SoundSpot_CalcFade(slot);
    tick = state->tick;
    if (tick == 0) {
        state->sound0 = 7;
        state->octave0 = 2;
        return;
    }
    if (tick >= 0x1B) {
        state->tick = -1;
    }
}

void SoundSpot_Type8(void *slot, SpotState *state) {
    s32 tick;

    state->level = SoundSpot_CalcFade(slot);
    tick = state->tick;
    if (tick == 0) {
        state->sound0 = 0x14;
        state->octave0 = 1;
        return;
    }
    if (tick == 3) {
        state->octave0 = 2;
        state->volume0 = 0x18;
        state->sound0 = 3;
        state->endVolume0 = 0x14;
        return;
    }
    if (tick >= 0x33) {
        state->tick = -1;
    }
}

void SoundSpot_Type9(void *slot, SpotState *state) {
    state->level = SoundSpot_CalcFade(slot);
    if (state->tick % 20 == 0) {
        state->sound0 = 9;
        state->octave0 = 0;
        state->volume0 = 0x40;
        state->endVolume0 = 0x40;
    }
}

void SoundSpot_Type10(void *slot, SpotState *state) {
    state->level = SoundSpot_CalcFade(slot);
    if (state->tick == ((state->tick / 20) * 20)) {
        state->sound0 = 9;
        state->octave0 = -2;
    }
}

void SoundSpot_Type11(void *slot, SpotState *state) {
    s32 phase;

    state->level = SoundSpot_CalcFade(slot);
    phase = state->tick % 20;
    if (phase == 1) {
        state->sound0 = 9;
        state->octave0 = -2;
    } else if (phase == 16) {
        state->sound1 = 9;
        state->octave1 = -2;
    }
}

void SoundSpot_Type12(void *slot, SpotState *state) {
    s32 phase;

    SoundSpot_Type11(slot, state);
    phase = state->tick % 70;
    if (phase == 50) {
        state->sound2 = 20;
        state->octave2 = 1;
    } else if (phase >= 54 && phase < 59) {
        state->sound2 = 13;
        state->octave2 = 1;
    } else if (phase == 61) {
        state->sound2 = 9;
        state->octave2 = -1;
    }
}

void SoundSpot_Type13(void *slot, SpotState *state) {
    s32 tick;

    state->level = SoundSpot_CalcFade(slot);
    tick = state->tick;
    if (tick == 0) {
        state->sound0 = 0x14;
        state->octave0 = -2;
        state->sound1 = 0x14;
        state->octave1 = -2;
        return;
    }
    if (tick == 4) {
        state->sound1 = 0x14;
        state->octave1 = -2;
        return;
    }
    if (tick == 20) {
        state->sound0 = 0x10;
        state->octave0 = -2;
        state->sound1 = 0x12;
        state->octave1 = -2;
        return;
    }
    if (tick >= 0xC9) {
        state->tick = -1;
    }
}

void SoundSpot_Type14(void *slot, SpotState *state) {
    state->level = SoundSpot_CalcFade(slot);
    if (state->tick == 0) {
        state->sound0 = 0x18;
        state->octave0 = 0;
    }
}

/* distance / (range / unk28): grows with the distance to the spot. */
s32 SoundSpot_CalcFade(SpotSlot *slot) {
    return slot->distance / (g_soundSpotRanges[-slot->record->range] / slot->fadeSteps);
}

/* Spawn rule 7 (Sym_CheckRule): 1 when the ambience family is even, 0 for odd ones and none (-1). */
s32 Ambience_IsEvenFamily(void) {
    return (g_ambienceFamily & 1) ^ 1;
}

/* Allocate a scenery object (0x98 bytes) of a kind from params at map, origin. */
void *Scenery_New(s32 kind, s32 params, s32 map, s32 origin) {
    void *scenery;

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
void *Scenery_Construct(Scenery *scenery, s32 kind, s32 params, s32 map, s32 origin) {
    if (Actor_GetVtbl()->construct(scenery) != 0) {
        scenery->vt = Scenery_GetVtbl();
        scenery->unk44 = 0;
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
void Scenery_Build(void *self, s32 map, s32 origin) {
    Scenery *scenery = (Scenery *)self;
    Vec3 pos;
    s32 kind;

    g_sceneryViewY = g_sceneryView->viewpoint.y;
    Scenery_AddOffset(&pos, (Vec3 *)origin, &scenery->offset);
    Scenery_AttachPart(self, map, &pos, scenery->rotation, (s32)scenery->scale);
    kind = scenery->kind;
    if (kind < 2) {
        SceneNode_LinkModel(self, g_sceneryModels->vt->unk80(g_sceneryModels, g_sceneryModelIndexes[kind]));
    }
    switch (scenery->kind) {
    case 0:
        Scenery_PlaceKind0Parts(self, 0);
        return;
    case 2:
        Scenery_BuildKind2(self, 0);
        return;
    case 3:
        Scenery_BuildKind3(self, 0);
        return;
    }
}

/* Follow the origin (and the view's height since it was made), then update the parts by kind. */
void Scenery_Follow(Scenery *scenery, Vec3 *origin) {
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
void Scenery_DeleteParts(Scenery *scenery) {
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

void Scenery_AddOffset(Vec3 *out, Vec3 *a, Vec3 *b) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

/* Slots 0x4C, 0x44 and 0x48 of a scenery object or part (pos is not used). */
void Scenery_AttachPart(void *self, s32 parent, Vec3 *pos, s32 rotation, s32 scale) {
    SceneryPart *obj = self;

    obj->vt->attach(obj, parent);
    obj->vt->setRotation(obj, 1, rotation);
    obj->vt->setScale(obj, 1, scale);
}

/* Kind 0: make (move == 0) or move its two parts, set apart along direction unk6C (1 to 4). */
void Scenery_PlaceKind0Parts(void *self, s32 move) {
    Scenery *scenery = self;
    Vec3 pos;
    s32 dir;
    SceneryPart **part;
    s32 i;

    dir = scenery->direction;
    if (dir != 0) {
        pos = D_800877EC;
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
                SceneNode_LinkModel(*part, scenery->model);
                Scenery_AttachPart(*part, (s32)scenery, &pos, scenery->rotation, (s32)scenery->scale);
            }
            part++;
        }
    }
}

/* Kind 0 tick: past 500 ticks, with a speed in g_sceneryKind0Speeds[unk70], move the parts every 0x5FB4 / speed ticks. */
void Scenery_UpdateKind0(void *self, Vec3 *origin) {
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
                    pos = D_8008782C;
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

void Scenery_DeleteKind0Parts(Scenery *scenery) {
    if (scenery->direction != 0) {
        Object_DeleteArray(scenery->u.pair, 2);
    }
}

/* Kind 2: five parts, then part 1 placed from g_sceneryKind2Offsets[unk70] or coloured, part 2 shown. */
void Scenery_BuildKind2(void *self, s32 unused) {
    Scenery *scenery;
    SceneryPart *part;
    SceneryPartVtbl *vt;
    s32 *value;
    s32 coin;
    s32 color;
    s32 partColor;
    s32 arg;

    scenery = (Scenery *)self;
    coin = rand() % 2;
    partColor = 0;
    if (coin == 0) {
        partColor = (s32)D_80087868;
    }
    Scenery_CreateSpriteParts(self, 0, 0, partColor);
    if (scenery->variant >= 2) {
        value = D_80087880;
        part = scenery->u.many.parts[1];
        *value = g_sceneryKind2Offsets[scenery->variant];
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
        color = (s32)D_80087874;
        if (coin != 0) {
            color = (s32)D_8008785C;
        }
        vt->setScale(part, 1, color);
    }
    scenery->u.many.parts[2]->vt->setVisible(scenery->u.many.parts[2], 0);
}

/* Kinds 2 and 3: five parts of class g_sceneryPartVtbl in the place's font. */
void Scenery_CreateSpriteParts(Scenery *scenery, s32 unused, s32 index, s32 color) {
    SceneryPart **part;
    s32 i;

    part = scenery->u.many.parts;
    for (i = 0; i < 5; i++) {
        *part = SceneryPart_New(index, 0, (s32)g_sceneryFont);
        (*part)->vt->attach(*part, scenery, 0);
        (*part)->vt->setColor(*part, scenery->color);
        if (color != 0) {
            (*part)->vt->setScale(*part, 1, color);
        }
        part++;
    }
}

void Scenery_UpdateKind2(void *scenery, Vec3 *origin) {
}

void Scenery_DeleteKind2Parts(Scenery *scenery) {
    Object_DeleteArray(scenery->u.many.parts, 5);
}

void Scenery_BuildKind3(Scenery *scenery, s32 unused) {
    Scenery_CreateSpriteParts(scenery, 0, 0, 0);
}

/* Kind 3 tick: parts 1 to 4 get a random colour of g_sceneryKind3Scales and a random angle. */
void Scenery_UpdateKind3(Scenery *scenery, Vec3 *origin) {
    s32 i;
    SceneryPart **part;

    part = &scenery->u.many.parts[1];
    for (i = 0; i < 4; i++) {
        (*part)->vt->setScale(*part, 1, g_sceneryKind3Scales + ((u32)rand() % 6) * 12);
        (*part)->angle = (rand() % 360) << 12;
        part++;
    }
}

void Scenery_DeleteKind3Parts(Scenery *scenery) {
    Object_DeleteArray(scenery->u.many.parts, 5);
}

SceneryVtbl *Scenery_GetVtbl(void) {
    return (SceneryVtbl *)g_sceneryVtbl;
}

/* Keep the place's models, font and view for the scenery, and prepare models g_sceneryModelIndexes[0..1]. */
void Scenery_SetPlaceRefs(s32 family, PlaceObj *models, void *font, View *view) {
    s32 i;

    g_sceneryModels = models;
    g_sceneryFont = font;
    g_sceneryView = view;
    for (i = 0; i < 2; i++) {
        ModelObject_SetClut(models->vt->unk80(models, g_sceneryModelIndexes[i]), g_sceneryModelClut);
    }
}

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

void Actor_ApplyPos(void *self, s32 set, s32 *vec) {
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
void Actor_MoveThenSnap(Actor *actor, void (*move)(void *, s32, s32), s32 value, s32 notify) {
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
s32 Actor_GetGroundRects(void *actor, void *outRects, void *outCells, void *cellInfo, s32 size) {
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

s32 Actor_FindGroundInCells(s32 actor, s32 delta, s32 pos, s32 count, s32 rects, void **cells) {
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
s32 Actor_FindGroundInRect(s32 actor, s32 delta, s32 pos, s32 rect, void *cell) {
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

s32 Actor_ProbeGroundAt(s32 entry) {
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

/* Allocate a scenery part of class g_sceneryPartVtbl (0xA8 bytes) for kinds 2 and 3. */
void *SceneryPart_New(s32 index, s32 blendRate, s32 font) {
    void *part;

    part = Heap_Alloc(0xA8);
    if (part != NULL) {
        SceneryPart_GetVtbl()->construct(part, index, blendRate, font);
        return part;
    }
    return NULL;
}

/* Slot 0x08 of g_sceneryPartVtbl: base construct with the font and the 12-byte entry g_sceneryPartRects[index]. */
void SceneryPart_Construct(TextPart *part, s32 index, s32 blendRate, s32 font) {
    SpriteNode_GetVtbl()->construct(part, font, 0, g_sceneryPartRects + index * 0xC, blendRate, 0);
    part->vt = SceneryPart_GetVtbl();
    part->unkA4 = 0;
    part->vt->init(part, index);
}

/* Slot 0x40 */
void SceneryPart_Init(TextPart *part, s32 index) {
    part->index = index;
    part->clutX = g_sceneryPartCluts[index * 2];
    part->clutY = g_sceneryPartClutsY[index * 2];
}

/* Slot 0x48: two 4.12 ratios from ratio[0] / ratio[1] and ratio[2] / ratio[3]. */
void SceneryPart_SetScale(TextPart *part, s32 assign, s16 *ratio) {
    s16 x;
    s16 y;

    x = ((ratio[0] / ratio[1]) << 12) + (((ratio[0] % ratio[1]) << 12) / ratio[1]);
    y = ((ratio[2] / ratio[3]) << 12) + (((ratio[2] % ratio[3]) << 12) / ratio[3]);
    if (part->unk58 != 0) {
        part->unk5C = (x * part->unk5C) >> 12;
        part->unk60 = (y * part->unk60) >> 12;
    } else {
        part->scaleX = x;
        part->scaleY = y;
    }
}

void SceneryPart_Stub98(void) {
}

void SceneryPart_StubBC(void) {
}

void SceneryPart_StubC0(void) {
}

void SceneryPart_StubC4(void) {
}

TextPartVtbl *SceneryPart_GetVtbl(void) {
    return (TextPartVtbl *)g_sceneryPartVtbl;
}

/* Allocate the graph object (0x244 bytes) and construct it with Graph_GetVtable's slot 0x08. */
void *Graph_New(s32 dreamSys) {
    void *graph;

    graph = Heap_Alloc(0x244);
    if (graph != 0) {
        Graph_GetVtable()->construct(graph, dreamSys);
        return graph;
    }
    return 0;
}

Point g_bandPos = { -100, -60 };
Point g_bandSize = { 0x140, 0x90 };

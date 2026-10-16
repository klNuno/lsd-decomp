#include "common.h"
#include "game/heap.h"
#include "game/dreamsys.h"
#include "game/entity.h"
#include "game/place.h"

/*
 * The memory card file list window (vtable D_80086F88, returned by func_80052B60; its first
 * methods are in src/game/80050BA8.c): background CARD\SELECT.TIM, up to 4 visible rows of
 * 26 characters built by Label_Create, the selected row in D_8008AB10 (0x80, 0x80, 0), the
 * others in D_8008AB0C (0x50, 0x50, 0x50). Slots 0x7C to 0x88 scroll it, 0x8C to 0x98 draw it.
 */
typedef struct CardListVtbl {
    u8 pad_00[0x10];
    void (*watch)();      /* 0x10 Object_Watch */
    void (*unwatch)();    /* 0x14 Object_Unwatch */
    u8 pad_18[0x30 - 0x18];
    void (*notify)();     /* 0x30 Object_Notify */
    u8 pad_34[0x48 - 0x34];
    void (*close)();      /* 0x48 func_800520A0 */
    u8 pad_4C[0x54 - 0x4C];
    void (*setMode)();    /* 0x54 func_800521D4 */
    u8 pad_58[0x60 - 0x58];
    void (*unk60)();      /* 0x60 func_800523F0 */
    u8 pad_64[0x7C - 0x64];
    void (*scrollRight)(); /* 0x7C func_80052430 */
    void (*scrollLeft)(); /* 0x80 func_80052498 */
    void (*moveUp)();     /* 0x84 func_800524F8 */
    void (*moveDown)();   /* 0x88 func_80052598 */
    void (*createRows)(); /* 0x8C func_80052644 */
    void (*deleteRows)(); /* 0x90 func_8005278C */
    void (*drawRows)();   /* 0x94 func_8005281C */
    void (*moveCursor)(); /* 0x98 func_80052A58 */
} CardListVtbl;

/* A row text, the background, a loaded file: the slots called on them here. */
typedef struct CardTextVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();   /* 0x04 Object_Delete */
    u8 pad_08[0x4C - 0x08];
    void (*unk4C)();      /* 0x4C (obj, parent, position) */
    u8 pad_50[0x78 - 0x50];
    void (*unk78)();      /* 0x78 called on a file right after Tim_New */
    u8 pad_7C[0xB8 - 0x7C];
    void (*setColor)();   /* 0xB8 D_8008AB10 or D_8008AB0C */
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
    s32 column;           /* 0x24 first visible character (text base for func_8005292C) */
    s32 cursor;           /* 0x28 selected row */
    s32 mode;             /* 0x2C 2 or 3 (setMode) */
    s32 modeTicks;        /* 0x30 */
    s32 unk34;            /* 0x34 unwatched by setMode and the destructor */
    s32 unk38;
    s32 unk3C;
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
 * The base class of the scenery objects and their kind 0 parts: vtable D_800878D4 (func_80057C84),
 * constructor func_80057044, 0x58 bytes. The scenery vtable and DreamSys's reuse its slots
 * 0x10 to 0x18 and 0xB8 to 0xE8; its methods end this unit.
 */
typedef struct ActorVtbl {
    u8 pad_00[0x08];
    s32 (*construct)();   /* 0x08 func_80057044 */
    void (*destruct)();   /* 0x0C SceneNode_Destroy */
    u8 pad_10[0x40 - 0x10];
    void (*init)();       /* 0x40 func_800571E8 */
    u8 pad_44[0x88 - 0x44];
    void (*unk88)();      /* 0x88 func_800571F8 */
    void (*unk8C)();
    void (*unk90)();
    u8 pad_94[0xA0 - 0x94];
    void (*unkA0)();
    u8 pad_A4[0xBC - 0xA4];
    void (*movePos)();    /* 0xBC Actor_MovePos */
    void (*unkC0)();
    void (*unkC4)();
    void (*unkC8)();
    u8 pad_CC[0xDC - 0xCC];
    void (*onTouch34)();  /* 0xDC func_80057B90: func_80057320 on message byte 0x34 */
    void (*onTouch24)();  /* 0xE0 func_80057C14: on message byte 0x24 */
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
    void (*unk88)();
    u8 pad_8C[0x9C - 0x8C];
    void (*unk9C)();
} ActorBaseVtbl;

typedef struct Actor {
    ActorVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    Coord2 *posBlock;     /* 0x14 its GsCOORDINATE2 (gs.h): flg cleared after each move */
    u8 pad_18[0x20 - 0x18];
    s32 unk20;            /* 0x20 tested by ModelObject_IsReady */
    u8 pad_24[0x28 - 0x24];
    s32 contact;          /* 0x28 the object found by func_80057668, 0 when none */
    u8 pad_2C[0x44 - 0x2C];
    s32 unk44;            /* 0x44 cleared by the constructor */
    s16 unk48;            /* 0x48 0x12C at init */
    u8 pad_4A[0x4C - 0x4A];
    s32 map;              /* 0x4C the watched object whose class id ends in 0x114 (the map) */
    s32 unk50;            /* 0x50 the watched object whose class id ends in 5 */
    s32 unk54;            /* 0x54 slot 0xEC */
} Actor;

/* A cell of the map grid as func_80057A18 reads it: 20 x 20 entry words at +0x10 (0x50 per row). */
typedef struct GridCell {
    u8 pad_00[0x10];
    s32 entries;
} GridCell;

/* An object in a grid entry, chained by +0x38. */
typedef struct GridEntry {
    u8 pad_00[0x38];
    s32 next;
} GridEntry;

/* The scenery part class D_800879C4 (0xA8 bytes, func_80057C94), built on the class of SpriteNode_GetVtbl. */
typedef struct TextPartVtbl {
    u8 pad_00[0x08];
    void (*construct)();  /* 0x08 func_80057D10 */
    u8 pad_0C[0x40 - 0x0C];
    void (*init)();       /* 0x40 func_80057DBC */
} TextPartVtbl;

typedef struct TextPart {
    TextPartVtbl *vt;
    u8 pad_04[0x58 - 0x04];
    void *unk58;          /* 0x58 slot 0x48 scales +0x5C and +0x60 while set, else stores the ratios at +0x80 */
    s32 unk5C;
    s32 unk60;
    u8 pad_64[0x74 - 0x64];
    u16 unk74;            /* 0x74 D_80087AA4[index * 2] */
    u16 unk76;            /* 0x76 D_80087AA6[index * 2] */
    u8 pad_78[0x80 - 0x78];
    s16 unk80;
    s16 unk82;
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
    PlaceOwnerObj *unkC;
} PlaceOwner;

/* The class SpriteNode_GetVtbl returns, base of TextPart. */
typedef struct TextPartBaseVtbl { u8 pad_00[0x8]; void (*construct)(void *, s32, s32, void *, s32, s32); } TextPartBaseVtbl;

/*
 * The contact search of func_80057668 over the map's grid: 20 x 20 entry words per cell
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
    void (*unk88)(GridActor *, s32);  /* -1 contact found, -2 none */
    u8 pad_8C[0xBC - 0x8C];
    void (*movePos)(GridActor *, void *);
} GridActorVtbl;

/* An Actor as func_80057668 reads it. */
struct GridActor {
    GridActorVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    u8 *posBlock;
    u8 pad_18[0x28 - 0x18];
    s32 contact;
    u8 pad_2C[0x4C - 0x2C];
    StageMap *map;        /* 0x4C */
};

/* One word of g_sceneryParams, as func_8005511C writes unk1C and unk20. */
typedef struct ParamWord {
    s32 v;
} ParamWord;

/* A screen position, {x, y} (the band layout D_8008AB68, D_8008AB70). */
typedef struct Point {
    s32 x;
    s32 y;
} Point;

/* The ambience band objects (Box_Create): 18 in g_ambienceBands for family 0, one at D_8008AC94. */
typedef struct AmbienceBandVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();   /* 0x04 Object_Delete */
    u8 pad_08[0x4C - 0x08];
    void (*attach)();     /* 0x4C (band, parent, position) */
    u8 pad_50[0x64 - 0x50];
    void (*unk64)();
    void (*unk68)();
    u8 pad_6C[0xB8 - 0x6C];
    void (*setColor)();   /* 0xB8 (band, 1, RGB) */
    void (*setPos)();     /* 0xBC */
} AmbienceBandVtbl;

typedef struct AmbienceBand {
    AmbienceBandVtbl *vt;
} AmbienceBand;

/* The parameters g_sceneryParams holds for the next scenery object (copied whole by its init, func_800564A4). */
typedef struct SceneryParams {
    s32 x;        /* 0x00 offset from the origin: random +-22 tiles (<< 11) in func_80055258 */
    s32 y;        /* 0x04 */
    s32 z;        /* 0x08 */
    u8 *unkC;     /* 0x0C 12-byte entry of D_80087174 */
    u8 *unk10;    /* 0x10 12-byte entry of D_800871C8, or D_80087204 */
    s32 unk14;    /* 0x14 rand() % 5 */
    s32 unk18;    /* 0x18 */
    u8 *unk1C;    /* 0x1C 3-byte entry of D_8008721C or D_80087228 */
    s32 unk20;    /* 0x20 kind 2: day number % 20, or D_80087430 */
} SceneryParams;

/* A part of a scenery object (classes D_800878D4 for kind 0, D_800879C4 for kinds 2 and 3). */
typedef struct SceneryPartVtbl {
    u8 pad_00[0x44];
    void (*unk44)();
    void (*unk48)();
    void (*unk4C)();
    u8 pad_50[0x60 - 0x50];
    void (*unk60)();
    void (*unk64)();
    void (*unk68)();
    u8 pad_6C[0xB8 - 0x6C];
    void (*unkB8)();
    void (*unkBC)();
} SceneryPartVtbl;

typedef struct SceneryPart {
    SceneryPartVtbl *vt;
    u8 pad_04[0x84 - 0x04];
    s32 unk84;    /* 0x84 random angle (rand() % 360) << 12 for kind 3 */
} SceneryPart;

/*
 * A scenery object (class D_800876FC returned by Scenery_GetVtbl, 0x98 bytes, made by Scenery_New):
 * one of 4 kinds made around the dreamer at a place's first tick (Scenery_CreateAll, work/hunt6/F-findings.md).
 * Its base class is D_800878D4 (constructor func_80057044, 0x58 bytes).
 */
typedef struct SceneryVtbl {
    u8 pad_00[0x08];
    s32 (*construct)();   /* 0x08 func_800563C0 */
    void (*destruct)();   /* 0x0C func_80056464 */
    u8 pad_10[0x40 - 0x10];
    void (*init)();       /* 0x40 func_800564A4 */
    void (*unk44)();
    void (*unk48)();
    void (*unk4C)();
    u8 pad_50[0xB8 - 0x50];
    void (*setPos)();     /* 0xB8 Actor_SetPos */
    void (*movePos)();    /* 0xBC Actor_MovePos */
    u8 pad_C0[0xEC - 0xC0];
    void (*update)();     /* 0xEC func_800564F4 */
} SceneryVtbl;

typedef struct Scenery {
    SceneryVtbl *vt;
    u8 pad_04[0x14 - 0x04];
    s32 *posBlock;        /* 0x14 its first word is cleared once moved */
    u8 pad_18[0x20 - 0x18];
    void *model;          /* 0x20 */
    u32 ticks;            /* 0x24 counted by update (func_800564F4) */
    u8 pad_28[0x44 - 0x28];
    s32 unk44;            /* 0x44 cleared by the constructor */
    u8 pad_48[0x54 - 0x48];
    s32 kind;             /* 0x54 0 to 3 */
    Vec3 offset;          /* 0x58 params x, y, z: offset from the origin */
    s32 unk64;            /* 0x64 params unkC */
    s16 *unk68;           /* 0x68 params unk10 */
    s32 unk6C;            /* 0x6C params unk14, kind 0: direction 1 to 4 of its two parts */
    s32 unk70;            /* 0x70 params unk18 */
    s32 unk74;            /* 0x74 params unk1C */
    s32 unk78;
    union {
        SceneryPart *pair[2];                                 /* 0x7C kind 0 */
        struct { u8 pad_7C[0x84 - 0x7C]; SceneryPart *parts[5]; } many; /* 0x84 kinds 2 and 3 */
    } u;
} Scenery;

/*
 * A spot: an 8-byte record of D_800876B4[stage] (count D_800876EC[stage]) with a map tile
 * record, a handler index idx and a range class. While the dreamer is within D_80087474[range]
 * (ground distance |dx| + |dz|), one of the two slots D_8008AC9C holds it and its handler
 * D_800874B0[range] runs (func_8005556C); the range is negated while it is held.
 */
typedef struct SpotTile {
    u8 b0, b1, b2, b3;    /* handed to map slot 0xE8 with the D_800874EC entry */
} SpotTile;

typedef struct SpotTileExtra {
    SpotTile tile;
    s16 v;
} SpotTileExtra;

typedef struct SpotRecord {
    SpotTile tile;        /* 0x0 */
    u8 idx;               /* 0x4 index of D_800874EC */
    u8 unk5;
    s8 range;             /* 0x6 > 0 free, < 0 held by a slot */
    u8 unk7;
} SpotRecord;

typedef struct SpotQuery {
    SpotTile a;
    SpotTileExtra b;
} SpotQuery;

/* The two slots (D_8008AC9C points into D_8008E154, 0x68 bytes each). */
typedef struct SpotSlot {
    SpotRecord *record;   /* 0x00 */
    s32 pos[3];           /* 0x04 the spot's position (map slot 0xE8) */
    s32 distance;         /* 0x10 ground distance to the dreamer */
    s32 node;             /* 0x14 handler node, registered with func_8002CC34 */
    u8 pad_18[0x28 - 0x18];
    s32 unk28;            /* 0x28 func_8005627C divides the range by it */
    u8 pad_2C[0x68 - 0x2C];
} SpotSlot;

/* The same slot as func_800557DC reads it (the range byte unsigned). */
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

/* The handler state the spot handlers func_80055A88 to func_80056238 get: a tick count and three {value, step} channels. */
typedef struct SpotState {
    u8 pad_00[0x4];
    s32 tick;             /* 0x04 the handler sets -1 to stop */
    u8 pad_08[0x10 - 0x8];
    s32 level;            /* 0x10 func_8005627C: distance / (range / slot +0x28) */
    u8 pad_14[0x1C - 0x14];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad_2C[0x30 - 0x2C];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    u8 pad_40[0x44 - 0x40];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
} SpotState;


/* .sdata owned by this unit (config/splat.yaml), defined at the end of the file: pairs read whole by func_800549A8, func_80054850 */
extern Point D_8008AB68;
extern Point D_8008AB70;
s32 g_ambienceFamily;
extern void Object_DeleteArray(void *, s32);
void func_800573CC(void *self, s32 set, s32 *vec);
void func_80056D18(Scenery *scenery, s32 arg1, s32 arg2, s32 color);
void Place_CheckTextureLoad(void *arg0, void *arg1);
extern void func_80056640();
extern s32 D_80087474[];
s32 D_8008AB50;
s32 g_sceneryCount;
extern u8 g_scenery[];
void func_8002CC84(void *, void *);
extern s32 SceneNode_ProbeHeight(void);
PlaceBaseVtbl *Task_GetVtbl();
extern s16 D_8008ABA8[];
void func_80057534(void *self, s16 *field, s32 value, s32 notify, s32 message);
extern s16 D_8008ABA4[];
extern u16 D_80087AA4[];
extern u16 D_80087AA6[];
void Stage_GetChunkPath(s32);
void Stage_GetChunkPathAt(s32, s32, s32);
void func_80056718();
ActorVtbl *func_80057C84(void);
ActorBaseVtbl *SceneNode_GetVtbl(void);
s32 D_8008AB54;
AmbienceBand *D_8008AC94;
s32 func_8005627C(SpotSlot *slot);
s32 Scenery_Tick(s32 mapPos, s32 arg1, s32 found);
void func_8002CD08(s32, s32);
PlaceRefs *g_placeRefs;
extern void SceneNode_RotateVector(void *, void *, void *);
s32 func_80057668();
extern u8 D_8008AB10[];
void *Heap_Alloc(s32 size);
GraphCtorVtbl *Graph_GetVtable(void);
void Place_StartFade(void *arg0, s32 color, s32 arg2, s32 duration, s32 watch);
extern u8 D_800872C4[];
extern s32 D_8008730C[];
extern void Display_RotateRect(s32 *arg0, s32 arg1, s32 *arg2);
extern s32 D_80087444[];
extern s32 D_80087450[];
extern s32 D_8008745C[];
extern s32 D_80087468[];
s32 g_placeStage;
extern void func_8005C76C(void);
extern void Scenery_Teardown(void);
s32 D_8008AB4C;
s32 g_placeTicks;
s32 g_placeDayNumber;
s32 D_8008AC78;
extern s32 D_8008ACA0;
Ambience *Ambience_Get(void);
extern SpotSlot *D_8008AC9C[];
void Heap_Free(void *);
TextPartVtbl *func_80057F58(void);
extern s32 D_8008AB98[];
extern s16 D_8008AB94[];
PlaceObj *D_8008ACA4;
void *D_8008ACA8;
View *D_8008ACAC;
void ModelObject_SetClut(void *, void *);
void func_80052E7C(Place *place, s32 result, s32 arg2, s32 arg3);
PlaceVtbl *Place_GetVtbl(void);
SceneryVtbl *Scenery_GetVtbl(void);
extern AmbienceRecord *D_800873EC[];
extern Ambience D_80087424;
AmbienceRecord *Ambience_PickFamily(void);
extern void Ambience_Fill(Ambience *ambience, AmbienceRecord *record);
void func_80056520(void *self, s32 map, s32 origin);
void func_80055258(void *origin, s32 height);
extern s32 D_80087330;
extern u8 D_80087204[];
extern SceneryParams g_sceneryParams;
s32 Sym_SpawnOrSpy(s32, void *, s32);
extern u8 D_80087A8C[];
TextPartBaseVtbl *SpriteNode_GetVtbl(void);
void func_80056054(void *slot, SpotState *state);
extern AmbienceBand *g_ambienceBands[];
extern void *Box_Create(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_8008AB58[];
extern s32 D_8008AB60[];
SpotRecord *func_80055620(void *pos, void *distance, s32 origin);
extern s32 D_800874B0[];
extern s32 func_8002CC34(s32, void *, s32, void *, s32);
s32 func_80057A18(s32 actor, s32 delta, s32 pos, s32 rect, void *cell);
extern s32 strlen(u8 *s);
extern void *memcpy(void *dst, void *src, s32 n);
extern void *func_80057C94(s32 index, s32 arg1, s32 font);
extern s32 rand(void);
extern u8 D_8008788C[];
extern s8 D_80087324[];
void func_80056F5C(s32 family, PlaceObj *models, void *font, View *view);
s32 *func_80054DA4(s32 *out, s32 count, void *origin);
s32 *func_80054F30(s32 *out, s32 count, void *origin);
s32 *func_80054FD8(s32 *out, s32 origin);
s32 *func_8005511C(s32 *out, s32 origin);
s32 D_8008AC84;
void *D_8008AC8C;
u8 *D_8008AC90;
extern s8 D_800873DC[];
extern s8 D_800873D8[];
extern u8 D_80087234[];
extern u8 D_8008726C[];
extern AmbienceRecord *D_800873C8[];
extern void func_80056794(Vec3 *out, Vec3 *a, Vec3 *b);
s32 D_8008ACB0;
void func_800569A8(void *self, Vec3 *origin);
extern void func_80056DF0(void *scenery, Vec3 *origin);
extern void func_80056E44(Scenery *scenery, Vec3 *origin);
extern u8 D_8008AB0C[];
void func_800567D4(void *self, s32 parent, Vec3 *pos, s32 arg3, s32 arg4);
void SceneNode_LinkModel(void *arg0, void *arg1);
void func_80056858(void *self, s32 move);
void func_80056BBC(void *self, s32 arg1);
void func_80056E1C(Scenery *scenery, s32 arg1);
extern s32 Label_Create(s32, s32, s32);
extern u8 D_8008AB44[];
extern s32 D_8008AB38[];
extern s32 D_8008AB40[];
s32 D_8008AB00;
s32 D_8008AB04;
u8 *func_8005292C(CardList *list, u8 *out, s32 i, s32 top, u8 *text);
void func_800529FC(CardList *list, s32 top, s32 column, s32 cursor, s32 highlight);
s32 func_80057784(void *actor, void *outRects, void *outCells, void *cellInfo, s32 size);
s32 ModelObject_IsReady(s32);
void ModelBox_ShiftList(s32 **arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80057B54();
extern s32 D_8008732C;
extern u8 D_80087174[];
extern s32 D_80087844[];
extern s32 D_80087868[];
extern s32 D_80087880[];
extern u8 D_80087874[];
extern u8 D_8008785C[];
void Actor_MovePos(void *actor, s32 *delta);
extern s8 *File_JoinPath(s8 *, s8 *, s8 *, s8 *);
extern CardText *Tim_New(s32);
extern CardText *ScreenSprite_Create(CardText *, s32 *, s32);
extern s8 D_8008AB14[];
extern s8 D_8008AB1C[];
extern s8 D_8008AB24[];
extern s32 D_8008AAF8[];
extern s32 D_80087028[];
void func_80055410();
void *Scenery_New(s32 kind, s32 params, s32 map, s32 origin);
extern s32 D_80087328[];
extern u8 D_800871C8[];
s32 D_8008AC98;
extern SpotSlot D_8008E154[];
void func_80054850(void);
void func_800549A8(void);
void func_80055A24(void);
extern u8 D_80086F88[];
extern u8 D_80087034[];
extern u8 D_800876FC[];
extern u8 D_800878D4[];
extern u8 D_800879C4[];
extern s32 D_8008780C[];
extern Vec3 D_8008782C;
extern s32 D_80087838[];
extern void Sym_InitStage(s32 stage, StageMap *map, DreamSys *dreamSys, PlaceObj *arg3, PlaceObj *arg4);
extern void *Stage_GetGrid(s32 stage);
extern s32 D_8008715C[];
extern s32 D_80087168[];
extern s32 D_8008710C[];
s32 D_8008AB34;
extern SpotTileExtra D_800874EC[];
extern SpotRecord *D_800876B4[];
extern u8 D_800876EC[];
extern s32 D_80087118[];
extern s32 D_80087150[];
Ambience *Scenery_Begin(s32 map, s32 stage, PlaceRefs *refs, s32 dayNumber, s32 arg4);
s32 Stage_PickTexturePath(s32, s32, s32);
s32 Music_PickTrack(s32, s32);
void *Tix_Create(s32 path);
s32 SceneNode_SetRayHeightCheck(s32);
void func_80057618(Actor *actor, void (*move)(void *, s32, s32), s32 arg2, s32 arg3);
extern u8 D_8008721C[];
void func_80055410(void);
void func_80054B1C(u8 *out, u8 *rgb, s32 shift);
extern Vec3 D_800877EC;
extern s32 D_800877F8[];
void *func_80056FE4(void);
extern s32 D_80087430;
extern u8 D_80087228[];

INCLUDE_RODATA("asm/nonmatchings/game/80051F24", D_800116A4);

/* Slot 0x44: open the list with background CARD\SELECT.TIM and the rows in FONTICON. */
void func_80051F24(CardList *list, s32 parent) {
    s8 path[0x20];
    CardText *file;
    CardText *background;
    CardText *iconFile;

    if ((parent != 0) && (list->background == NULL)) {
        file = Tim_New((s32)File_JoinPath(path, D_8008AB14, D_8008AB1C, D_8008AB24));
        file->vt->unk78(file);
        list->background = ScreenSprite_Create(file, D_80087028, 0);
        file->vt->delete_(file);
        background = list->background;
        background->vt->unk4C(background, parent, D_8008AAF8);
        iconFile = Tim_New((s32)File_JoinPath(path, (s8 *)"FONTICON\0\0\0\0\0\0\0", D_8008AB1C, D_8008AB24));
        iconFile->vt->unk78(iconFile);
        list->vt->createRows(list, parent, iconFile, list->top, list->column, list->cursor);
        iconFile->vt->delete_(iconFile);
    }
}

/* Slot 0x48: delete the rows and the background. */
void func_800520A0(CardList *list) {
    CardText *background;

    if (list->background != NULL) {
        list->vt->deleteRows(list);
        background = list->background;
        list->background = background->vt->delete_(background);
    }
}

void func_80052110(CardList *list, s32 arg1, s32 arg2, s32 arg3) {
    list->vt->watch(list, arg1);
    list->vt->watch(list, arg2);
    list->unk3C = arg3;
    list->mode = 0;
}

void func_8005217C(CardList *list) {
    list->vt->unwatch(list, list->unk34);
    list->vt->unwatch(list, list->unk38);
    list->unk3C = 0;
}

void func_800521D4(CardList *list, s32 mode) {
    list->modeTicks = 0;
    switch (mode) {
    case 2:
    case 3:
        list->vt->unwatch(list, list->unk34);
        list->vt->close(list);
        list->mode = mode;
        break;
    case 4:
        list->vt->notify(list, list->mode);
        break;
    }
}

void func_8005227C(CardList *list) {
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
void func_800522DC(CardList *list, s32 arg1, s32 code) {
    void (*fn)(CardList *, s32, s32);
    u32 idx = code - 4;

    switch (idx) {
    case 21:
        list->vt->unk60(list, 0x10, idx);
        list->vt->setMode(list, 2);
        return;
    case 19:
        list->vt->unk60(list, 0x10, idx);
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
    fn(list, arg1, idx);
}

void func_800523F0(CardList *list, s32 arg1) {
    CardListOwner *owner = (CardListOwner *)list->unk3C;
    if (owner != NULL) {
        owner->vt->unk80(owner, arg1, 0x60, 0x60);
    }
}

/* Slot 0x7C: show one more character on the right while the longest row goes past 26. */
void func_80052430(CardList *list) {
    if (list->background != 0 && (list->column + 0x1A) < list->width) {
        list->vt->drawRows(list, list->top, ++list->column, list->cursor, 1);
    }
}

/* Slot 0x80: back one character. */
void func_80052498(CardList *list) {
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
void func_800524F8(CardList *list) {
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
void func_80052598(CardList *list) {
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
void func_80052644(CardList *list, s32 parent, s32 font, s32 top, s32 column, s32 cursor) {
    u8 text[0x1C];
    s32 pos[4];
    s32 i;
    s32 n;
    CardText **row;
    CardText *created;
    CardText *obj;

    if (list->background != 0) {
        pos[0] = D_8008AB00;
        pos[1] = D_8008AB04;
        n = list->count;
        row = list->rows;
        if (n >= 5) {
            n = 4;
        }
        i = 0;
        if (n > 0) {
            do {
                func_8005292C(list, text, i, top, (u8 *)column);
                created = (CardText *)Label_Create(font, 0x1A, (s32)text);
                *row = created;
                created->vt->unk4C(created, parent, pos);
                obj = *row;
                i += 1;
                obj->vt->setColor(obj, D_8008AB0C);
                pos[1] += 0xA;
                row += 1;
            } while (i < n);
        }
        func_800529FC(list, top, column, cursor, 1);
    }
}

/* Slot 0x90 */
void func_8005278C(CardList *list) {
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
void func_8005281C(CardList *list, s32 top, s32 column, s32 cursor, s32 notify) {
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
            func_8005292C(list, text, i, top, column);
            obj = *row;
            obj->vt->setText(obj, text);
            row++;
        }
        func_800529FC(list, top, column, cursor, 0);
        if (notify != 0) {
            list->vt->unk60(list, 0);
        }
    }
}

/* Copy row (top + i) into out, padded with spaces to 26 characters. */
u8 *func_8005292C(CardList *list, u8 *out, s32 i, s32 top, u8 *text) {
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

void func_800529FC(CardList *list, s32 top, s32 column, s32 cursor, s32 highlight) {
    s32 row;
    CardText *obj;

    list->top = top;
    list->column = column;
    list->cursor = cursor;
    if (highlight != 0) {
        row = cursor - top;
        obj = list->rows[row];
        obj->vt->setColor(obj, D_8008AB10, column, row);
    }
}

/* Slot 0x98: move the highlight one row down (down != 0) or up. */
void func_80052A58(CardList *list, s32 down, s32 notify) {
    CardText **row;
    CardText *obj;

    if (list->background != 0) {
        row = &list->rows[list->cursor - list->top];
        obj = *row;
        obj->vt->setColor(obj, D_8008AB0C);
        if (down != 0) {
            row++;
            list->cursor++;
        } else {
            row--;
            list->cursor--;
        }
        obj = *row;
        obj->vt->setColor(obj, D_8008AB10);
        if (notify != 0) {
            list->vt->unk60(list, 0);
        }
    }
}

s32 func_80052B54(CardList *list) {
    return list->cursor;
}

CardListVtbl *func_80052B60(void) {
    return (CardListVtbl *)D_80086F88;
}

/* Allocate a place (0x88 bytes) and construct it (slot 0x08); called by the dream runner DreamRunner_CreateStage. */
void *Place_New(s32 handlerList, s32 music, s32 font, s32 arg3, s32 stage) {
    void *place;

    place = Heap_Alloc(0x88);
    if (place != NULL) {
        Place_GetVtbl()->construct(place, handlerList, music, font, arg3, stage);
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
void func_80052CD8(s32 place) {
    Task_GetVtbl(place)->destruct(place);
}

/*
 * Slot 0x38: a watched object sent a message. The first word of the sender's vtable is its
 * class id: DreamSys (0x1F34) goes to slot 0x90, ids ending in 0x164 (the fader) to 0xB0,
 * ids ending in 0x114 (the map) to 0xB4.
 */
void func_80052D10(Place *place, s32 **sender, s32 message) {
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

void func_80052DE0(void) {
}

/* Slot 0x44: keep the DreamSys and register func_80052E7C with the runner's object. */
void func_80052DE8(Place *place, PlaceOwner *owner, DreamSys *dreamSys) {
    PlaceOwnerObj *obj;

    obj = owner->unkC;
    obj->vt->setCallback(obj, &func_80052E7C, place);
    place->dreamSys = dreamSys;
    Task_GetVtbl()->attach(place, owner, 1);
    place->vt->watch(place, dreamSys);
}

void func_80052E7C(Place *place, s32 result, s32 arg2, s32 arg3) {
    if (result >= 0) {
        Stage_GetChunkPath(place->stage);
    } else {
        Stage_GetChunkPathAt(place->stage, arg2, arg3);
    }
}

/* Slot 0x48 */
void func_80052EBC(Place *place) {
    place->vt->unwatch(place, place->dreamSys);
    Task_GetVtbl()->detach(place);
}

/*
 * Slot 0x4C, when a stage loads: picks the music track (Music_PickTrack) and starts the
 * texture-set loader (Stage_PickTexturePath, Tix_Create), starts the scenery
 * (Scenery_Begin, which gives the ambience) and sets the state to 5.
 */
void Place_Load(Place *place, s32 arg1, Ambience *ambience, s32 arg3) {
    View *view;
    s32 mode;

    view = place->view;
    view->vtbl->detach(view);
    place->texLoading = 1;
    place->music->vt->unk5C(place->music, Music_PickTrack(place->stage, 0));
    place->texLoader = Tix_Create(Stage_PickTexturePath(place->stage, 0, place->dreamSys->vtbl->getDayNumber(place->dreamSys, 0)));
    view->vtbl->setCamera(view, place->dreamSys, D_8008715C, D_80087168, 0);
    place->refs.view = view;
    place->ambience = Scenery_Begin((s32)place->map, place->stage, &place->refs, place->dreamSys->vtbl->getDayNumber(place->dreamSys, 0), 0);
    if (ambience != 0) {
        place->ambience = ambience;
    }
    place->unk4C = arg3;
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
    place->unk48 = arg1;
    if (arg1 == 0) {
        place->unk48 = 0xA000;
    }
    SceneNode_SetRayHeightCheck(mode);
    place->dreamSys->vtbl->unkEC(place->dreamSys, D_80087118[place->stage]);
    place->state = 5;
}

/* Slot 0x50: teardown (called without the place), free the scenery, stop the music object. */
void func_80053134(Place *place) {
    PlaceObj *music;

    place->vt->teardown();
    func_8005C76C();
    Scenery_Teardown();
    music = place->music;
    music->vt->unk48(music);
}

/* Slot 0x54 */
void func_800531A0(Place *place, s32 arg1, s32 event) {
    if (event == 2) {
        Place_CheckTextureLoad(place, place->texLoader);
    }
}

/*
 * Check the texture-set loader. When it failed (+0x80, a heap allocation returned 0) the set
 * is dropped and the time limit becomes elapsed + 30 s (discoveries "the 30-second dreams");
 * when it is done the ambience colour goes to it. Then, once the map is ready, start the place.
 */
void Place_CheckTextureLoad(void *arg0, void *arg1) {
    PlaceTexLoader *loader = arg1;
    Place *place = arg0;
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
void Place_OnPad(Place *place, s32 arg1, s32 code) {
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

void func_800534C0(void) {
}

/* Slot 0x80, after the texture set: hands the stage to the spawn code (Sym_InitStage) and sets up the map. */
void func_800534C8(Place *place) {
    View *view;
    StageMap *map;
    Ambience *ambience;
    PlaceObj *first;
    DreamSys *dreamSys;

    view = place->view;
    ambience = place->ambience;
    view->vtbl->detach(view);
    first = *place->unkC;
    view->vtbl->setProjection(view, ((((s32) *first->vt->unk7C(first, 0) / 2) * 5) / 3) + D_8008AB34);
    view->vtbl->setCamera(view, place->dreamSys, D_8008715C, D_80087168, 0);
    Sym_InitStage(place->stage, place->map, place->dreamSys, place->unk34, place->unk10);
    map = place->map;
    place->vt->watch(place, map);
    map->vtbl->setAmbient(map, ambience->unk8, 0);
    map->vtbl->unkC4(map, 3, ambience->unk0, ambience->unk4);
    map->vtbl->setGrid(map, Stage_GetGrid(place->stage));
    dreamSys = place->dreamSys;
    dreamSys->vtbl->unk4C(dreamSys, map);
    map->vtbl->setViewDistance(map, place->unk48);
    map->vtbl->setMessageFilter(map, D_8008710C);
}

/* Slot 0x84 */
void func_800536B0(Place *place) {
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
void func_8005393C(Place *place) {
    StageMap *map = place->map;
    Scenery_Tick((s32)map->vtbl->getLocation(map, 0, 0), 0, 0);
}

/* Slot 0x90: DreamSys messages 10 to 17 go to slots 0x94 to 0xAC while the state is 0. */
void func_80053984(Place *place, s32 sender, s32 message) {
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
void func_80053ACC(Place *place) {
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
void func_80053BE8(Place *place) {
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
void func_80053C94(Place *place) {
    DreamSys *dreamSys;

    dreamSys = place->dreamSys;
    place->state = 6;
    Place_StartFade(place, dreamSys->vtbl->getDreamColor(dreamSys), 0, 0x1E, 1);
    dreamSys = place->dreamSys;
    dreamSys->vtbl->unkFC(dreamSys);
}

/* Slot 0xA0: state 7, fade to the day's colour. */
void func_80053D18(Place *place) {
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
void func_80053D9C(Place *place) {
    place->state = 8;
    Place_StartFade(place, 0, 0, 6, 1);
    place->dreamSys->vtbl->unkF4(place->dreamSys, 1);
}

/* Slot 0xA8 */
void func_80053E00(Place *place) {
    place->state = 10;
    Place_StartFade(place, 0, 0, 6, 1);
    place->dreamSys->vtbl->unk13C(place->dreamSys, 2);
    place->dreamSys->vtbl->unkF4(place->dreamSys, 2);
}

/* Slot 0xAC */
void func_80053E84(Place *place) {
    place->vt->notify(place, 0xB);
}

/* Start the view's fader towards a colour index (0 to 7), watched when asked. */
void Place_StartFade(void *arg0, s32 color, s32 arg2, s32 duration, s32 watch) {
    Place *place = arg0;
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
    fader->vtbl->startOut(fader, place->unk10, color, arg2);
}

/* Slot 0xB0: the fader is done (5: back to state 0; 6: its colour goes to the view, state 10 becomes 4). */
void func_80053F84(Place *place, Fade *fader, s32 message) {
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
void func_800540E8(Place *place, s32 sender, s32 message) {
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

void func_800541CC(void) {
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
        place->pauseText = (PlaceObj *)Label_Create((s32)place->refs.font, 5, (s32)D_8008AB44);
        place->pauseText->vt->unk4C(place->pauseText, place->map, D_8008AB38);
        place->pauseText->vt->unkB8(place->pauseText, D_8008AB40);
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
    return (PlaceVtbl *)D_80087034;
}

/*
 * When a place loads (Place slot 0x4C): keep its map, stage, refs and day number, reset the
 * tick counter g_placeTicks and the two spot slots (D_8008AC9C[0..1], D_8008ACA0 is [1]), and
 * return the ambience. Runs only while no place is up (D_8008AB4C is 0 again after Scenery_Teardown).
 */
Ambience *Scenery_Begin(s32 map, s32 stage, PlaceRefs *refs, s32 dayNumber, s32 arg4) {
    s32 *slot;
    s32 n;

    if (D_8008AB4C == 0) {
        n = 1;
        slot = &D_8008ACA0;
        D_8008AB4C = map;
        g_placeStage = stage;
        g_placeRefs = refs;
        g_ambienceFamily = -1;
        g_placeDayNumber = dayNumber;
        D_8008AC78 = arg4;
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

/* The stage's fixed ambience record, else one of the day's family (Ambience_PickFamily), into D_80087424. */
Ambience *Ambience_Get(void) {
    AmbienceRecord *record;

    record = D_800873EC[g_placeStage];
    if (record == NULL) {
        record = Ambience_PickFamily();
    }
    Ambience_Fill(&D_80087424, record);
    if (record->depth >= 4) {
        D_8008AB54 = (s32)(D_800872C4 + record->colorB * 3);
    }
    return &D_80087424;
}

void Ambience_Fill(Ambience *ambience, AmbienceRecord *record) {
    ambience->colorA = D_800872C4 + record->colorA * 3;
    ambience->colorB = D_800872C4 + record->colorB * 3;
    ambience->depth = D_8008730C[record->depth];
    ambience->mode = record->mode;
}

/* The extra ambience object, when the record's depth is 4 or more. */
void func_80054660(void) {
    AmbienceBand *band;
    View *view;

    if (D_8008AB54 != 0) {
        band = Box_Create((s32)D_8008AB60, D_8008AB54, 0);
        D_8008AC94 = band;
        band->vt->unk64(band, 1);
        D_8008AC94->vt->unk68(D_8008AC94, 0);
        view = g_placeRefs->view;
        D_8008AC94->vt->attach(D_8008AC94, view->vtbl->getOverlay(view), D_8008AB58);
    }
}

void func_80054714(void) {
    if (D_8008AB54 != 0) {
        D_8008AC94->vt->delete_(D_8008AC94);
        D_8008AB54 = 0;
    }
}

/*
 * The ambience family of the dream: D_800873DC[(day number + stage) & 15], a 16-entry cycle over
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
    family = D_800873DC[sum & 0xF];
    g_ambienceFamily = family;
    index = sum % D_800873D8[family];
    D_8008AC84 = index;
    record = D_800873C8[family] + index;
    if (family == 0) {
        D_8008AC90 = D_800872C4 + record->colorA * 3;
        palette = D_8008726C;
        if (record->colorB != 0x12) {
            palette = D_80087234;
        }
        D_8008AC8C = palette;
        if (index < 4) {
            D_8008AB50 = 1;
        } else if (index < 6) {
            D_8008AB50 = 2;
        }
    }
    return record;
}

/* Make the 18 bands (run again by every first tick: the old ones are not freed, work/hunt6/F-findings.md). */
void func_80054850(void) {
    Point layout[2];
    s32 i;
    AmbienceBand *band;
    View *view;

    if (D_8008AB50 != 0) {
        layout[0] = D_8008AB68;
        if (D_8008AB50 == 2) {
            layout[0].y += 0x1E;
        }
        layout[1] = D_8008AB70;
        g_ambienceBands[0] = Box_Create((s32)&layout[1], (s32)D_8008AC8C, 0x1FFF);
        for (i = 1; i < 0x12; i++) {
            band = Box_Create((s32)&layout[1], (s32)D_8008AC8C + i * 3, 0x1FFF);
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
void func_800549A8(void) {
    u8 rgb[8];
    Point pos;
    View *view;
    AmbienceBand **band;
    s32 shift;
    s32 off;
    s32 i;

    if (D_8008AB50 == 0) {
        return;
    }
    view = g_placeRefs->view;
    shift = ((view->viewpoint.y - view->refPoint.y) / 600) * 3;
    if (shift > 0) {
        pos = D_8008AB68;
        i = 0;
        if (D_8008AB50 == 2) {
            pos.y += 0x1E;
        }
        band = g_ambienceBands;
        off = 0;
        pos.y += shift * 3;
        for (; i < 18; i++) {
            func_80054B1C(rgb, D_8008AC8C + off, shift);
            (*band)->vt->setColor(*band, 1, rgb);
            (*band)->vt->setPos(*band, &pos);
            off += 3;
            pos.y += 3;
            band++;
        }
        func_80054B1C(rgb, D_8008AC90, shift);
        view->vtbl->setClearColor(view, rgb);
    }
}

/* out = rgb with red and green lowered and blue raised by shift. */
void func_80054B1C(u8 *out, u8 *rgb, s32 shift) {
    out[0] = rgb[0] - shift;
    out[1] = rgb[1] - shift;
    out[2] = rgb[2] + shift;
}

void func_80054B50(void) {
    if (D_8008AB50 != 0) {
        Object_DeleteArray(g_ambienceBands, 0x12);
        D_8008AB50 = 0;
    }
}

/*
 * First tick: the scenery objects into g_scenery around origin, g_sceneryCount of them
 * (work/hunt6/F-findings.md): count of kind 0 from D_80087324, kind 1 up to 16 for family 2,
 * plus one of kind 3 for family 0 or of kind 2 for family 2.
 */
void Scenery_CreateAll(s32 origin) {
    s32 *end;
    s32 extra;
    s32 count;

    if (g_ambienceFamily >= 0) {
        func_80056F5C(g_ambienceFamily, g_placeRefs->models, g_placeRefs->font, g_placeRefs->view);
        count = D_80087324[rand() & 3];
        extra = (g_ambienceFamily == 2) ? (0x10 - count) : 0;
        g_sceneryCount = count + extra;
        end = func_80054F30(func_80054DA4(g_scenery, count, origin), extra, (void *)origin);
        if (g_ambienceFamily == 0) {
            func_80054FD8(end, origin);
            g_sceneryCount += 1;
        } else if (g_ambienceFamily == 2) {
            func_8005511C(end, origin);
            g_sceneryCount += 1;
        }
    }
}

/* Every tick: slot 0xEC (func_800564F4) of every scenery object. */
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

    func_80054714();
    func_80054B50();
    Scenery_DeleteAll();
    for (i = 0; i < 2; i++) {
        D_8008AC9C[i] = (SpotSlot *)func_800557DC(D_8008AC9C[i]);
    }
    if (D_8008AB4C != 0) {
        D_8008AB4C = 0;
    }
}

/* Kind 0: count objects at random offsets (func_80055410 on day numbers divisible by 7, else func_80055258). */
s32 *func_80054DA4(s32 *out, s32 count, void *origin) {
    void (*randomize)(void *, s32);
    s32 i;
    s32 height;

    g_sceneryParams.unk18 = rand() % 7;
    g_sceneryParams.unk10 = &D_800871C8[((u32)rand() % 5) * 12];
    height = (u32)rand() % 5;
    if (height != 0) {
        height = D_80087328[height];
    }

    randomize = func_80055410;
    if (g_placeDayNumber % 7 != 0) {
        randomize = func_80055258;
    }

    for (i = 0; i < count; i++) {
        randomize(origin, height);
        *out = (s32)Scenery_New(0, (s32)&g_sceneryParams, D_8008AB4C, (s32)origin);
        out++;
    }
    return out;
}

/* Kind 1 */
s32 *func_80054F30(s32 *out, s32 count, void *origin) {
    s32 i;
    s32 height = D_80087330;

    g_sceneryParams.unk10 = D_80087204;
    for (i = 0; i < count; i++) {
        func_80055258(origin, height);
        *out = Scenery_New(1, &g_sceneryParams, D_8008AB4C, origin);
        out++;
    }
    return out;
}

/* Kind 3, one object: a fixed offset with the second band palette, else a random one behind the origin. */
s32 *func_80054FD8(s32 *out, s32 origin) {
    func_80055258((void *)origin, D_80087330);
    if (D_8008AB50 != 0 && D_8008AC8C == D_8008726C) {
        g_sceneryParams.x = 0xFFFF5000;
        g_sceneryParams.y = -0x2000;
        g_sceneryParams.z = 0;
        g_sceneryParams.unk1C = D_8008721C + 3;
    } else {
        if (g_sceneryParams.z > 0) {
            g_sceneryParams.z = -g_sceneryParams.z;
        }
        if (g_sceneryParams.z < -0x7800) {
            g_sceneryParams.z = -0x7800;
        }
        g_sceneryParams.unk1C = D_8008721C + ((u32)rand() % 3) * 3;
    }
    g_sceneryParams.unkC = D_80087174;
    *out++ = (s32)Scenery_New(3, (s32)&g_sceneryParams, D_8008AB4C, origin);
    return out;
}

/* Kind 2, one object; the word after unk1C gets day number % 20 (or D_80087430 when it is 0). */
s32 *func_8005511C(s32 *out, s32 origin) {
    ParamWord *p;
    s32 *q;
    s32 x;
    s32 v;

    v = (s32)(D_80087228 + ((u32)rand() % 3) * 3);
    p = (ParamWord *)&g_sceneryParams.unk1C;
    p->v = v;
    p++;
    if (g_placeDayNumber % 20) {
        x = D_80087430;
    } else {
        x = g_placeDayNumber % 20;
    }
    p->v = x;
    func_80055258((void *)origin, D_80087330);
    q = (s32 *)&g_sceneryParams.unkC;
    *q = (s32)D_80087174;
    g_sceneryParams.unk18 = rand() % 6;
    *out++ = (s32)Scenery_New(2, (s32)&g_sceneryParams, D_8008AB4C, origin);
    return out;
}

/* Random offset: x and z in -22..22 tiles (<< 11), y = height (or one of D_80087328 when 0). */
void func_80055258(void *origin, s32 height) {
    if (height == 0) {
        height = D_80087328[rand() & 3];
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
    g_sceneryParams.unkC = D_80087174 + ((u32)rand() % 7) * 12;
    g_sceneryParams.unk14 = rand() % 5;
}

/* Day numbers divisible by 7: x in 0..19 tiles, z 0xA000, -0x6000 or 0x800 by day number % 3. */
void func_80055410(void) {
    s32 v;
    s32 m;

    rand();
    g_sceneryParams.y = D_8008732C;
    v = rand();
    g_sceneryParams.z = 0xA000;
    g_sceneryParams.x = (v % 20) << 11;
    m = g_placeDayNumber % 3;
    if (m == 1) {
        g_sceneryParams.z = 0xFFFF6000;
    } else if (m == 2) {
        g_sceneryParams.z = 0x800;
    }
    g_sceneryParams.unkC = D_80087174 + ((u32)rand() % 7) * 12;
    g_sceneryParams.unk14 = rand() % 5;
}

/* Hold the next free spot in range of origin in slot and register its handler. */
SpotSlot *func_8005556C(SpotSlot *slot, s32 *found, s32 origin, s32 arg3) {
    SpotRecord *record;

    record = func_80055620(slot->pos, &slot->distance, origin);
    if (record != NULL) {
        slot->record = record;
        func_8002CC34(g_placeRefs->handlerList, &slot->node, record->range, slot, D_800874B0[record->range]);
        if (record->range == *found) {
            *found = -record->range;
        }
        record->range = -record->range;
        return slot;
    }
    return NULL;
}

/* Walk the stage's spots from D_8008AC98 and return the first free one within its range of origin. */
SpotRecord *func_80055620(void *pos, void *distance, s32 origin) {
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
        n = D_800876EC[g_placeStage] - D_8008AC98;
        record = D_800876B4[g_placeStage] + D_8008AC98;
        for (i = 0; i < n; i++, record++) {
            D_8008AC98++;
            if (record->range > 0) {
                query.a = record->tile;
                query.b = D_800874EC[record->idx];
                (*(void (**)(s32, void *, s32))((u8 *)*(s32 *)D_8008AB4C + 0xE8))(D_8008AB4C, pos, (s32)&query);
                dx = ((s32 *)pos)[0] - from[0];
                if (dx < 0) {
                    dx = ~dx + 1;
                }
                dz = ((s32 *)pos)[2] - from[2];
                dist = dx + (dz < 0 ? ~dz + 1 : dz);
                *(s32 *)distance = dist;
                if (dist < D_80087474[record->range]) {
                    return record;
                }
            }
        }
    }
    return NULL;
}

/* Release a slot: unregister its handler and free its spot. */
s32 func_800557DC(SpotSlotU *slot) {
    func_8002CC84((void *)g_placeRefs->handlerList, &slot->node);
    slot->record->range = -slot->record->range;
    return 0;
}

s32 func_8005582C(s32 slot, void *origin, s32 arg2) {
    if (func_80055874(slot, origin) != 0) {
        func_8002CD08(g_placeRefs->handlerList, slot + 0x14);
        return 1;
    }
    return 0;
}

/* Is the held spot still within its range of origin (the range is negative while held)? */
s32 func_80055874(SpotSlot *slot, s32 *origin) { s32 dx,dz,d; if (origin != NULL) {
    dx = slot->pos[0] - origin[0];
    if (dx < 0) dx = ~dx + 1;
    dz = slot->pos[2] - origin[2];
    d = dx + (dz < 0 ? ~dz + 1 : dz);
    slot->distance = d;
    if (d < D_80087474[-slot->record->range]) return 1; } return 0; }

/*
 * The scenery tick (Place slot 0x8C), with the map position of the dreamer. On the first tick
 * after a place starts (g_placeTicks reads 0) it makes the extra object, the bands and the
 * scenery; zeroing g_placeTicks makes them again without freeing the old ones (the "location_time"
 * leak, work/hunt6/F-findings.md). Then it updates them and the two spot slots, and returns the
 * range of a spot just taken when it equals found.
 */
s32 Scenery_Tick(s32 mapPos, s32 arg1, s32 found) {
    s32 posBuf[4];
    void *origin;
    s32 i;
    s32 unused;
    SpotSlot **slot;

    origin = 0;
    if (mapPos != 0) {
        origin = posBuf;
        (*(void (**)(s32, void *, s32))((u8 *)*(s32 *)D_8008AB4C + 0xE8))(D_8008AB4C, origin, mapPos);
    }
    if (g_placeTicks++ == 0) {
        func_80054660();
        func_80054850();
        Scenery_CreateAll((s32)origin);
    }
    func_800549A8();
    Scenery_UpdateAll((s32)origin);
    func_80055A24();
    D_8008AC98 = 0;
    slot = D_8008AC9C;
    for (i = 0; i < 2; i++, slot++) {
        if (*slot != NULL) {
            if (func_8005582C(*slot, origin, arg1) == 0) {
                *slot = (SpotSlot *)func_800557DC(*slot);
            }
        } else {
            *slot = (SpotSlot *)func_8005556C(&D_8008E154[i], &found, origin, arg1);
        }
    }
    return found;
}

void func_80055A24(void) {
    if (g_placeStage == 2) {
        Display_RotateRect(D_80087444, 1, D_80087450);
    } else if (g_placeStage >= 3 && g_placeStage < 6) {
        Display_RotateRect(D_8008745C, 1, D_80087468);
    }
}

/* Spot handlers (table D_800874B0, by range): slot is the SpotSlot, state the handler's state. */
void func_80055A88(void *slot, SpotState *state) {
    s32 tick;

    state->level = func_8005627C(slot);
    tick = state->tick;
    if (tick == 0) {
        state->unk1C = 7;
        state->unk20 = 0;
    } else if (tick == 2) {
        state->unk30 = 7;
        state->unk34 = 0;
    } else if (tick == 5) {
        state->unk44 = 7;
        state->unk48 = 0;
    } else if (tick >= 8) {
        state->tick = -1;
    }
}

void func_80055B10(void *slot, SpotState *state) {
    state->level = func_8005627C(slot);
    if (state->tick == 0) {
        state->unk1C = 0x18;
        state->unk20 = -2;
        return;
    }
    if (state->tick >= 0x401) {
        state->tick = -1;
    }
}

void func_80055B6C(void *slot, SpotState *state) {
    s32 tick;

    state->level = func_8005627C(slot);
    tick = state->tick;
    if (tick == 0) {
        state->unk1C = 0xC;
        state->unk20 = 2;
        return;
    }
    if (tick >= 5) {
        state->tick = -1;
    }
}

void func_80055BC8(void *slot, SpotState *state) {
    state->level = func_8005627C(slot);
    if (state->tick % 20 == 0) {
        state->unk1C = 0x1E;
        state->unk24 = 0x20;
        state->unk20 = 0;
        state->unk28 = 0xA;
    }
    if (state->tick % 400 == 0) {
        state->unk30 = 0x1E;
        state->unk34 = 0;
    }
    state->unk44 = 6;
    state->unk4C = 0x20;
    state->unk48 = 0;
    state->unk50 = 0xA;
}

void func_80055CA8(void *slot, SpotState *state) {
    state->level = func_8005627C((SpotSlot *)slot);
    if (state->tick % 3 == 0) {
        state->unk1C = 0x1E;
        state->unk20 = 0;
    }
    if (state->tick % 5 == 0) {
        state->unk30 = 0x1E;
        state->unk34 = 0;
        state->unk38 = 0x18;
        state->unk3C = 0x18;
    }
    if (state->tick % 7 == 0) {
        state->unk1C = 0x1E;
        state->unk20 = 0;
    }
    state->unk44 = 6;
    state->unk48 = 1;
    state->unk4C = 0x2A;
    state->unk50 = 0xA;
}

void func_80055DB4(void *slot, SpotState *state) {
    state->level = func_8005627C((SpotSlot *)slot);
    if (state->tick == 0) {
        state->unk1C = 0x1E;
        state->unk20 = -1;
        return;
    }
    if (state->tick < 50 && state->tick % 5 == 4) {
        state->unk30 = 0x1E;
        state->unk34 = 0;
        state->unk3C = state->unk38 -= state->tick * 2;
        return;
    }
    if (state->tick >= 0x65 && state->tick < 0x6E) {
        state->unk44 = 0xD;
        state->unk48 = 1;
        return;
    }
    if (state->tick >= 0xC9) {
        state->tick = -1;
    }
}

void func_80055E94(void *slot, SpotState *state) {
    s32 tick;

    state->level = func_8005627C(slot);
    tick = state->tick;
    if (tick == 0) {
        state->unk1C = 7;
        state->unk20 = 2;
        return;
    }
    if (tick >= 0x1B) {
        state->tick = -1;
    }
}

void func_80055EF0(void *slot, SpotState *state) {
    s32 tick;

    state->level = func_8005627C(slot);
    tick = state->tick;
    if (tick == 0) {
        state->unk1C = 0x14;
        state->unk20 = 1;
        return;
    }
    if (tick == 3) {
        state->unk20 = 2;
        state->unk24 = 0x18;
        state->unk1C = 3;
        state->unk28 = 0x14;
        return;
    }
    if (tick >= 0x33) {
        state->tick = -1;
    }
}

void func_80055F74(void *slot, SpotState *state) {
    state->level = func_8005627C(slot);
    if (state->tick % 20 == 0) {
        state->unk1C = 9;
        state->unk20 = 0;
        state->unk24 = 0x40;
        state->unk28 = 0x40;
    }
}

void func_80055FE8(void *slot, SpotState *state) {
    state->level = func_8005627C(slot);
    if (state->tick == ((state->tick / 20) * 20)) {
        state->unk1C = 9;
        state->unk20 = -2;
    }
}

void func_80056054(void *slot, SpotState *state) {
    s32 phase;

    state->level = func_8005627C(slot);
    phase = state->tick % 20;
    if (phase == 1) {
        state->unk1C = 9;
        state->unk20 = -2;
    } else if (phase == 16) {
        state->unk30 = 9;
        state->unk34 = -2;
    }
}

void func_800560E4(void *slot, SpotState *state) {
    s32 phase;

    func_80056054(slot, state);
    phase = state->tick % 70;
    if (phase == 50) {
        state->unk44 = 20;
        state->unk48 = 1;
    } else if (phase >= 54 && phase < 59) {
        state->unk44 = 13;
        state->unk48 = 1;
    } else if (phase == 61) {
        state->unk44 = 9;
        state->unk48 = -1;
    }
}

void func_80056194(void *slot, SpotState *state) {
    s32 tick;

    state->level = func_8005627C(slot);
    tick = state->tick;
    if (tick == 0) {
        state->unk1C = 0x14;
        state->unk20 = -2;
        state->unk30 = 0x14;
        state->unk34 = -2;
        return;
    }
    if (tick == 4) {
        state->unk30 = 0x14;
        state->unk34 = -2;
        return;
    }
    if (tick == 20) {
        state->unk1C = 0x10;
        state->unk20 = -2;
        state->unk30 = 0x12;
        state->unk34 = -2;
        return;
    }
    if (tick >= 0xC9) {
        state->tick = -1;
    }
}

void func_80056238(void *slot, SpotState *state) {
    state->level = func_8005627C(slot);
    if (state->tick == 0) {
        state->unk1C = 0x18;
        state->unk20 = 0;
    }
}

/* distance / (range / unk28): grows with the distance to the spot. */
s32 func_8005627C(SpotSlot *slot) {
    return slot->distance / (D_80087474[-slot->record->range] / slot->unk28);
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
void *func_800563C0(Scenery *scenery, s32 kind, s32 params, s32 map, s32 origin) {
    if (func_80057C84()->construct(scenery) != 0) {
        scenery->vt = Scenery_GetVtbl();
        scenery->unk44 = 0;
        scenery->kind = kind;
        scenery->vt->init(scenery, params);
        func_80056520(scenery, map, origin);
        return scenery;
    }
    return NULL;
}

/* Slot 0x0C (func_80056718 is called without the object; a0 still holds it). */
void func_80056464(s32 scenery) {
    func_80056718();
    func_80057C84()->destruct(scenery);
}

/* Slot 0x40: copy the parameters to +0x58. */
void func_800564A4(Scenery *scenery, SceneryParams *params) {
    *(SceneryParams *)((u8 *)scenery + 0x58) = *params;
    scenery->ticks = 0;
}

/* Slot 0xEC, every tick (func_80056640 is called without arguments; a0 and a1 still hold them). */
void func_800564F4(Scenery *scenery) {
    scenery->ticks++;
    func_80056640();
}

/* Place it at origin + offset and build its parts by kind. */
void func_80056520(void *self, s32 map, s32 origin) {
    Scenery *scenery = (Scenery *)self;
    Vec3 pos;
    s32 kind;

    D_8008ACB0 = D_8008ACAC->viewpoint.y;
    func_80056794(&pos, (Vec3 *)origin, &scenery->offset);
    func_800567D4(self, map, &pos, scenery->unk64, (s32)scenery->unk68);
    kind = scenery->kind;
    if (kind < 2) {
        SceneNode_LinkModel(self, D_8008ACA4->vt->unk80(D_8008ACA4, D_8008AB98[kind]));
    }
    switch (scenery->kind) {
    case 0:
        func_80056858(self, 0);
        return;
    case 2:
        func_80056BBC(self, 0);
        return;
    case 3:
        func_80056E1C(self, 0);
        return;
    }
}

/* Follow the origin (and the view's height since it was made), then update the parts by kind. */
void func_80056640(Scenery *scenery, Vec3 *origin) {
    Vec3 pos;

    func_80056794(&pos, origin, &scenery->offset);
    pos.y += D_8008ACAC->viewpoint.y - D_8008ACB0;
    scenery->vt->setPos(scenery, &pos);
    switch (scenery->kind) {
    case 0:
        func_800569A8(scenery, origin);
        return;
    case 2:
        func_80056DF0(scenery, origin);
        return;
    case 3:
        func_80056E44(scenery, origin);
        return;
    }
}

/* Delete the parts by kind. */
void func_80056718(Scenery *scenery) {
    switch (scenery->kind) {
    case 0:
        func_80056B8C(scenery);
        break;
    case 2:
        func_80056DF8(scenery);
        break;
    case 3:
        func_80056F28(scenery);
        break;
    }
}

void func_80056794(Vec3 *out, Vec3 *a, Vec3 *b) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

/* Slots 0x4C, 0x44 and 0x48 of a scenery object or part (pos is not used). */
void func_800567D4(void *self, s32 parent, Vec3 *pos, s32 arg3, s32 arg4) {
    SceneryPart *obj = self;

    obj->vt->unk4C(obj, parent);
    obj->vt->unk44(obj, 1, arg3);
    obj->vt->unk48(obj, 1, arg4);
}

/* Kind 0: make (move == 0) or move its two parts, set apart along direction unk6C (1 to 4). */
void func_80056858(void *self, s32 move) {
    Scenery *scenery = self;
    Vec3 pos;
    s32 dir;
    SceneryPart **part;
    s32 i;

    dir = scenery->unk6C;
    if (dir != 0) {
        pos = D_800877EC;
        part = scenery->u.pair;
        for (i = 0; i < 2; i++) {
            if (dir < 3) {
                pos.x += *scenery->unk68 * D_800877F8[dir];
            } else {
                pos.y += D_800877F8[dir];
            }
            if (move != 0) {
                SceneryPart *obj = *part;
                obj->vt->unkB8(obj, &pos);
            } else {
                *part = func_80056FE4();
                SceneNode_LinkModel(*part, scenery->model);
                func_800567D4(*part, (s32)scenery, &pos, scenery->unk64, (s32)scenery->unk68);
            }
            part++;
        }
    }
}

/* Kind 0 tick: past 500 ticks, with a speed in D_8008780C[unk70], move the parts every 0x5FB4 / speed ticks. */
void func_800569A8(void *self, Vec3 *origin) {
    Scenery *scenery = self;
    SceneryPart **part;
    Vec3 pos;
    s32 *speed;
    s32 idx;
    s32 i;
    s32 off;
    s32 period;
    u32 ticks;

    idx = scenery->unk70;
    if (scenery->unk6C != 0) {
        if (D_8008780C[idx] != 0) {
            part = scenery->u.pair;
            if (scenery->ticks >= 0x1F5) {
                scenery->vt->unk44(scenery, 0, &D_80087838);
                i = 0;
                speed = &D_8008780C[idx];
                off = 0;
                do {
                    pos = D_8008782C;
                    pos.z += off + *speed;
                    (*part)->vt->unkBC(*part, &pos);
                    i++;
                    off += 3;
                    (*part)->vt->unk44(*part, 0, &D_80087838);
                    part++;
                } while (i < 2);
                period = 0x5FB4 / D_8008780C[idx];
                ticks = scenery->ticks;
                if (period >= 0) {
                    if (ticks % (u32)period == 0) {
                        func_80056858(scenery, 1);
                    }
                } else {
                    if (ticks % (u32)(~period + 1) == 0) {
                        func_80056858(scenery, 1);
                    }
                }
            }
        }
    }
    *scenery->posBlock = 0;
}

void func_80056B8C(Scenery *scenery) {
    if (scenery->unk6C != 0) {
        Object_DeleteArray(scenery->u.pair, 2);
    }
}

/* Kind 2: five parts, then part 1 placed from D_80087844[unk70] or coloured, part 2 shown. */
void func_80056BBC(void *self, s32 arg1) {
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
    func_80056D18(self, 0, 0, partColor);
    if (scenery->unk70 >= 2) {
        value = D_80087880;
        part = scenery->u.many.parts[1];
        *value = D_80087844[scenery->unk70];
        Actor_MovePos(part, value);
        arg = scenery->unk78;
        vt = part->vt;
        if (arg == 0) {
            arg = scenery->unk74;
        }
        vt->unkB8(part, arg);
    } else {
        part = scenery->u.many.parts[1];
        part->vt->unk64(part, 1);
        part->vt->unk68(part, 0);
        vt = part->vt;
        color = (s32)D_80087874;
        if (coin != 0) {
            color = (s32)D_8008785C;
        }
        vt->unk48(part, 1, color);
    }
    scenery->u.many.parts[2]->vt->unk60(scenery->u.many.parts[2], 0);
}

/* Kinds 2 and 3: five parts of class D_800879C4 in the place's font. */
void func_80056D18(Scenery *scenery, s32 arg1, s32 arg2, s32 color) {
    SceneryPart **part;
    s32 i;

    part = scenery->u.many.parts;
    for (i = 0; i < 5; i++) {
        *part = func_80057C94(arg2, 0, (s32)D_8008ACA8);
        (*part)->vt->unk4C(*part, scenery, 0);
        (*part)->vt->unkB8(*part, scenery->unk74);
        if (color != 0) {
            (*part)->vt->unk48(*part, 1, color);
        }
        part++;
    }
}

void func_80056DF0(void *scenery, Vec3 *origin) {
}

void func_80056DF8(Scenery *scenery) {
    Object_DeleteArray(scenery->u.many.parts, 5);
}

void func_80056E1C(Scenery *scenery, s32 arg1) {
    func_80056D18(scenery, 0, 0, 0);
}

/* Kind 3 tick: parts 1 to 4 get a random colour of D_8008788C and a random angle. */
void func_80056E44(Scenery *scenery, Vec3 *origin) {
    s32 i;
    SceneryPart **part;

    part = &scenery->u.many.parts[1];
    for (i = 0; i < 4; i++) {
        (*part)->vt->unk48(*part, 1, D_8008788C + ((u32)rand() % 6) * 12);
        (*part)->unk84 = (rand() % 360) << 12;
        part++;
    }
}

void func_80056F28(Scenery *scenery) {
    Object_DeleteArray(scenery->u.many.parts, 5);
}

SceneryVtbl *Scenery_GetVtbl(void) {
    return (SceneryVtbl *)D_800876FC;
}

/* Keep the place's models, font and view for the scenery, and prepare models D_8008AB98[0..1]. */
void func_80056F5C(s32 family, PlaceObj *models, void *font, View *view) {
    s32 i;

    D_8008ACA4 = models;
    D_8008ACA8 = font;
    D_8008ACAC = view;
    for (i = 0; i < 2; i++) {
        ModelObject_SetClut(models->vt->unk80(models, D_8008AB98[i]), D_8008AB94);
    }
}

/* Allocate a kind 0 part: an object of the base class D_800878D4 (0x58 bytes). */
void *func_80056FE4(void) {
    void *part;

    part = Heap_Alloc(0x58);
    if (part == 0) {
        return 0;
    }
    if (func_80057C84()->construct(part) != 0) {
        return part;
    }
    Heap_Free(part);
    return 0;
}

/* Slot 0x08 of the base class D_800878D4 */
void *func_80057044(Actor *actor) {
    if (SceneNode_GetVtbl()->construct(actor) != 0) {
        actor->vt = func_80057C84();
        actor->unk44 = 0;
        actor->map = 0;
        actor->unk50 = 0;
        actor->vt->init(actor);
        return actor;
    }
    return 0;
}

/* Slot 0x10, watch: keep a map (class id ending in 0x114) at +0x4C, a class id ending in 5 at +0x50. */
void func_800570B4(Actor *actor, s32 **other) {
    s32 classId;

    SceneNode_GetVtbl()->watch(actor, other);
    classId = **other;
    if ((classId & 0xFFF) == 0x114) {
        actor->map = (s32)other;
        return;
    }
    if ((classId & 0xF) == 5) {
        actor->unk50 = (s32)other;
    }
}

/* Slot 0x14, unwatch */
void func_80057130(Actor *actor, s32 **other) {
    s32 classId;

    classId = **other;
    if ((classId & 0xFFF) == 0x114) {
        actor->map = 0;
    } else if ((classId & 0xF) == 5) {
        actor->unk50 = 0;
    }
    SceneNode_GetVtbl()->unwatch(actor, other);
}

/* Slot 0x18, unwatch all */
void func_800571A8(Actor *actor) {
    actor->map = 0;
    actor->unk50 = 0;
    SceneNode_GetVtbl()->unwatchAll(actor);
}

/* Slot 0x40 */
void func_800571E8(Actor *actor) {
    actor->unk48 = 0x12C;
    actor->unk54 = 0;
}

/* Slot 0x88: messages 5 to 8 while unk20 passes ModelObject_IsReady. */
void func_800571F8(Actor *actor, s32 message) {
    s32 *buf[14];
    Actor *contact;

    SceneNode_GetVtbl()->unk88(actor, message);
    if (message < 9) {
        if (message >= 5) {
            if ((actor->unk20 != 0) && (ModelObject_IsReady(actor->unk20) != 0)) {
                actor->vt->unk8C(actor, buf);
                if (message != 5) {
                    ModelBox_ShiftList(buf, message == 7, actor->unk48 >= 0,
                                  actor->unk48 >= 0 ? actor->unk48 + actor->unk54 : actor->unk48 - actor->unk54);
                }
                actor->vt->unk90(actor, buf, message);
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
void func_80057320(Actor *actor, u8 **message) {
    u8 c = **message;

    if (c == 0x34) {
        actor->vt->onTouch34();
    } else if (c == 0x24) {
        actor->vt->onTouch24();
    }
}

/* Slot 0xB8: set the position. */
void Actor_SetPos(void *actor, s32 *pos) {
    func_800573CC(actor, 1, pos);
}

/* Slot 0xBC: move by a vector. */
void Actor_MovePos(void *actor, s32 *delta) {
    func_800573CC(actor, 0, delta);
}

void func_800573CC(void *self, s32 set, s32 *vec) {
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
void func_80057444(Actor *actor, void *arg1) {
    s32 delta[3];

    SceneNode_RotateVector(actor, delta, arg1);
    actor->vt->movePos(actor, delta);
}

/* Slots 0xC4 to 0xCC: one of the three s16 of D_8008ABA4/D_8008ABA8 set for slot 0xC0, then message 6, 7 or 8. */
void func_8005748C(void *actor, s32 value, s32 notify) {
    func_80057534(actor, D_8008ABA8, value, notify, 6);
}

void func_800574C4(void *actor, s32 value, s32 notify) {
    func_80057534(actor, D_8008ABA4, value, notify, 7);
}

void func_800574FC(void *actor, s32 value, s32 notify) {
    func_80057534(actor, D_8008ABA4 + 1, value, notify, 8);
}

void func_80057534(void *self, s16 *field, s32 value, s32 notify, s32 message) {
    Actor *actor = self;

    actor->unk48 = *field = value;
    actor->vt->unkC0(actor, D_8008ABA4);
    *field = 0;
    if (notify != 0) {
        actor->vt->unk88(actor, message);
    }
}

/* Slot 0xD0 */
void func_800575B0(Actor *actor, s32 arg1, s32 arg2) {
    func_80057618(actor, actor->vt->unkC4, arg1, arg2);
}

/* Slot 0xD4 */
void func_800575E0(Actor *actor, s32 arg1, s32 arg2) {
    func_80057618(actor, actor->vt->unkC8, arg1, arg2);
}

void func_80057610(void) {
}

/* Run a move, then look for a contact when the move found none. */
void func_80057618(Actor *actor, void (*move)(void *, s32, s32), s32 arg2, s32 arg3) {
    actor->contact = 0;
    move(actor, arg2, arg3);
    if (actor->contact == 0) {
        func_80057668(actor);
    }
}

/* Look for an object in the map cells around the actor's position (+0x14 block, +0x18). */
s32 func_80057668(GridActor *actor) {
    s32 cell[0xC];
    s32 rects[0xC];
    void *cells[4];
    s32 delta[4];
    u8 *pos;
    s32 found;

    if (actor->map != NULL) {
        pos = actor->posBlock + 0x18;
        if (actor->map->vtbl->locate(actor->map, cell, pos) == 0) {
            found = func_80057784(actor, rects, cells, cell, 1);
            found = func_80057954((s32)actor, (s32)delta, (s32)pos, found, (s32)rects, cells);
            actor->contact = found;
            if (found != 0) {
                actor->vt->movePos(actor, delta);
                actor->vt->unk88(actor, -1);
                return 1;
            }
            actor->vt->unk88(actor, -2);
        }
    }
    return 0;
}

/* The rectangles of cells to search: the cell itself and the slots above and below it (n == 1), else the n x n square clipped to the 20 x 20 grid. */
s32 func_80057784(void *actor, void *outRects, void *outCells, void *cellInfo, s32 size) {
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

s32 func_80057954(s32 actor, s32 delta, s32 pos, s32 count, s32 rects, void **cells) {
    s32 found;
    MapSlot *cell;
    s32 i;

    i = 0;
    while (i < count) {
        cell = *cells;
        i += 1;
        if (cell->chunk->loaded != 0) {
            found = func_80057A18(actor, delta, pos, rects, cell);
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
s32 func_80057A18(s32 actor, s32 delta, s32 pos, s32 rect, void *cell) {
    GridRect *r = (GridRect *)rect;
    GridCell *grid = (GridCell *)cell;
    s32 entry;
    s32 col;
    s32 row;
    s32 *slot;

    slot = (s32 *)(grid->entries + r->top * 0x50 + r->left * 4);
    for (row = 0; row < r->height; row++) {
        for (col = 0; col < r->width; col++) {
            if (func_80057B54(*slot, delta, pos) != 0) {
                return *slot;
            }
            entry = ((GridEntry *)*slot)->next;
            if (entry != 0) {
                do {
                    if (func_80057B54(entry, delta, pos) != 0) {
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

s32 func_80057B54(s32 entry) {
    if (entry != 0 && SceneNode_ProbeHeight() != 0) {
        return entry;
    }
    return 0;
}

/* Slot 0xDC: the base slot 0x9C, then slot 0xA0 for messages 5 to 8. */
void func_80057B90(Actor *actor, void *arg1, s32 message) {
    SceneNode_GetVtbl()->unk9C(actor, arg1, message);
    if (message < 9) {
        if (message >= 5) {
            actor->vt->unkA0(actor, arg1, message);
        }
    }
}

/* Slot 0xE0 */
void func_80057C14(s32 actor, s32 arg1, s32 message) {
    SceneNode_GetVtbl()->unk9C(actor, arg1, message);
}

/* Slot 0xE4 */
void func_80057C6C(Actor *actor, s16 value) {
    actor->unk48 = value;
}

void func_80057C74(void) {
}

/* Slot 0xEC */
void func_80057C7C(Actor *actor, s32 value) {
    actor->unk54 = value;
}

ActorVtbl *func_80057C84(void) {
    return (ActorVtbl *)D_800878D4;
}

/* Allocate a scenery part of class D_800879C4 (0xA8 bytes) for kinds 2 and 3. */
void *func_80057C94(s32 index, s32 arg1, s32 font) {
    void *part;

    part = Heap_Alloc(0xA8);
    if (part != NULL) {
        func_80057F58()->construct(part, index, arg1, font);
        return part;
    }
    return NULL;
}

/* Slot 0x08 of D_800879C4: base construct with the font and the 12-byte entry D_80087A8C[index]. */
void func_80057D10(TextPart *part, s32 index, s32 arg2, s32 font) {
    SpriteNode_GetVtbl()->construct(part, font, 0, D_80087A8C + index * 0xC, arg2, 0);
    part->vt = func_80057F58();
    part->unkA4 = 0;
    part->vt->init(part, index);
}

/* Slot 0x40 */
void func_80057DBC(TextPart *part, s32 index) {
    part->index = index;
    part->unk74 = D_80087AA4[index * 2];
    part->unk76 = D_80087AA6[index * 2];
}

/* Slot 0x48: two 4.12 ratios from ratio[0] / ratio[1] and ratio[2] / ratio[3]. */
void func_80057DF4(TextPart *part, s32 arg1, s16 *ratio) {
    s16 x;
    s16 y;

    x = ((ratio[0] / ratio[1]) << 12) + (((ratio[0] % ratio[1]) << 12) / ratio[1]);
    y = ((ratio[2] / ratio[3]) << 12) + (((ratio[2] % ratio[3]) << 12) / ratio[3]);
    if (part->unk58 != 0) {
        part->unk5C = (x * part->unk5C) >> 12;
        part->unk60 = (y * part->unk60) >> 12;
    } else {
        part->unk80 = x;
        part->unk82 = y;
    }
}

void func_80057F38(void) {
}

void func_80057F40(void) {
}

void func_80057F48(void) {
}

void func_80057F50(void) {
}

TextPartVtbl *func_80057F58(void) {
    return (TextPartVtbl *)D_800879C4;
}

/* Allocate the graph object (0x244 bytes) and construct it with Graph_GetVtable's slot 0x08. */
void *Graph_New(s32 arg0) {
    void *graph;

    graph = Heap_Alloc(0x244);
    if (graph != 0) {
        Graph_GetVtable()->construct(graph, arg0);
        return graph;
    }
    return 0;
}

Point D_8008AB68 = { -100, -60 };
Point D_8008AB70 = { 0x140, 0x90 };

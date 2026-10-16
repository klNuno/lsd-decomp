#include "common.h"
#include "game/dreamsys.h"
#include "game/scene.h"

extern void Object_DeleteArray(void *, s32);
u8 *g_navFlags;
s32 *g_dynamicLinkCount;
extern s32 D_8008ABF0[];
s32 g_linkToStage;
s32 g_linkFromStage;
/* A scripted link target as Link_GetStepScript reads it: byte 5 is the index into g_linkSteps. */
typedef struct { u8 pad[5]; s8 stepScript; } ScriptedTarget;
extern ScriptedTarget *g_scriptedLinkTargets[];
s32 g_linkToIndex;
extern s16 g_stageTimeLimits[];
void Actor_ApplyPos(void *self, s32 set, s32 *vec);
extern void Scenery_CreateSpriteParts(u8 *scenery, s32 unused, s32 index, s32 color);
extern void Place_CheckTextureLoad(void *, void *);
void HandlerNode_Stop(void *, void *);
s32 Mood_GetColor(s16 *point);
extern u8 g_staticLinkCounts[];
extern s32 g_staticLinkLists[];
extern s32 g_staticLinkTargets[];
s32 Link_Find(void *place, void *location, s32 stage, u8 *counts, s32 *lists, s32 *targets, s32 setNavFlag);
extern u8 g_facingLinkCounts[];
extern void *g_facingLinkLists[];
extern void *g_facingLinkTargets[];
s16 *Stage_GetChunkMood(s32 stage, s8 *place);
extern u8 g_extraLinkCounts;
extern s32 g_extraLinkLists;
extern s32 g_extraLinkTargets;
s32 g_extraListOn;
extern u8 g_scriptedLinkCounts[];
extern s32 g_scriptedLinkLists[];
s32 Spawn_PickRandom(void *place, s32 stage, s32 unused);
s32 DreamSys_ExecuteLink();
extern u8 g_turnRotations[];
/* The StageMap (stage.h) as DreamSys_OnMapMessage calls it: slot 0x10C StageMap_GetLocation. */
typedef struct MapLocateVtbl {
    u8 pad_00[0x10C];
    s32 (*getLocation)(void *, s32, s32);
} MapLocateVtbl;
typedef struct MapLocateView {
    MapLocateVtbl *vt;
} MapLocateView;
s32 Link_FindStatic(void *, void *, s32);
s32 Nav_CalcScore(void);
extern ScreenVtbl *MenuScreen_GetVtbl(void);
/* g_actorVtbl (0x800878D4), the Actor base class (place.h), as the DreamSys methods call it. */
typedef struct ActorVtblView {
    u8 pad_00[0x8];
    void (*init)(void *);                       /* 0x08 Actor_Construct */
    u8 pad_0C[0x50 - 0x0C];
    void (*detach)(void *);                     /* 0x50 SceneNode_Detach */
    u8 pad_54[0x9C - 0x54];
    void (*onNode)(void *, s32 **, s32);        /* 0x9C Actor_OnNode */
    u8 pad_A0[0xDC - 0xA0];
    void (*onNode34)(void *, s32 **, s32);      /* 0xDC Actor_OnNode34 */
    void (*onNode24)(void *, s32 **, s32);      /* 0xE0 Actor_OnNode24 */
} ActorVtblView;
ActorVtblView *Actor_GetVtbl(void);
extern u16 g_linkHeadingYaws[];
/* A rotation in degrees (three Fractions, SceneNode_GetRotation) read for its yaw numerator. */
typedef struct RotationYaw {
    u8 pad_00[4];
    u16 yaw;
} RotationYaw;
s32 g_saveMagic;
extern void Nav_InitFlags(u8 *flags, s32 *linkCount);
extern void *memset(void *dst, s32 value, s32 size);
s32 Spawn_PickFromMood(void *place, s32 *secondsOut, void *point, s32 day);
void *Heap_Alloc(s32 size);
DreamSysVtbl *DreamSys_GetVtable(void);
extern s32 g_dreamerStartRotation[];
s32 Mood_CalcAxis(s32, s32, s32);
void Heap_Free(s32);
s32 Link_PickFallStage();
s32 *func_8005BF48(void);
extern s32 g_fallStep[];
extern void HandlerNode_Run(s32, void *);
extern s8 g_moodColors[][3];
void SceneNode_GetRotation(DreamSys *dreamSys, s32 *degrees);
s32 Link_FindFacing(void *out, s16 *location, s32 stage);
s32 Link_CheckFacing(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation);
s32 Day_FindSpecial(void *cinematic, s32 dayNumber);
extern s32 g_graphReelColor;
extern s32 rand(void);
extern s16 g_specialDays[42];
extern s32 D_8008ABF4;
/* DreamSys +0x168 as Day_FindSpecial writes it: {category, variant} (dreamsys.h cinematic.id). */
typedef struct SpecialCine {
    s16 category;
    s16 variant;
} SpecialCine;
extern s32 HandlerNode_Start(s32, void *, s32, void *, s32);
extern s16 g_linkStep2Start[];
extern u8 g_yawPlus45[];
void DreamSys_MoveToTileOffset(DreamSys *, s16 *, s16 *);
extern u8 g_graphBoxSize[];
extern s32 g_graphNewestColor[];
void *Box_Create(s32 size, s32 color, s32 priority);
/* A box color the graph steps down; signed bytes, as the code subtracts. */
typedef struct GraphColor {
    s8 r;
    s8 g;
    s8 b;
} GraphColor;
extern GraphColor g_graphOldColor;
extern s32 g_pointAheadZ[];
extern void SceneNode_LocalToWorld(void *node, void *dst, void *src, s32 unused);
s32 Entity_IsWithinBox(s32 *center, s32 range, s32 *pos);
s32 DreamSys_GetSightHeight(ScreenVec *start, ScreenVec *end, s32 pos);
extern u8 g_linkHeadings[];
extern u8 *g_facingArrivalHeadings[];
extern u8 *g_facingLinkHeadings[];
s32 g_linkFromIndex;
s32 Link_IsFacing(RotationYaw *rotation, u8 heading);
extern u8 *g_scriptedLinkHeadings[];
extern u8 *g_scriptedArrivalHeadings[];
extern s16 g_linkStep0Start[];
s32 g_fallPlace5;
/* The map location (StageMap_GetLocation) as Link_PickFallStage reads it: the tile word, then the x and y (height) offsets. */
typedef struct FallLocation {
    s32 tile;
    s16 x;
    s16 y;
} FallLocation;
extern s32 g_pitchSteps[];
extern s32 g_pitchLimits[];
/* The Tmd (loader.h) slot 0x80 Tmd_GetModel (tmd, index). */
typedef struct TmdModelVtbl {
    u8 pad_00[0x80];
    s32 (*getModel)(void *, s32);
} TmdModelVtbl;
extern s8 g_stepSoundTones[];
extern s8 g_stepSoundOctaves[];
/* The StageMap slot 0xE4 StageMap_SetTarget (map, out position, target, place). */
typedef struct MapTargetVtbl {
    u8 pad_00[0xE4];
    void (*setTarget)(void *, void *, void *, void *);
} MapTargetVtbl;
/* g_actorVtbl slot 0x4C SceneNode_Attach, called with the map and the start position. */
typedef struct ActorAttachVtbl {
    u8 pad_00[0x4C];
    void (*attach)(void *, void *, void *);
} ActorAttachVtbl;
extern s16 g_linkStep1Start[];
extern u8 g_yawMinus45[];
/* g_actorVtbl slot 0x88 Actor_SendBoxes. */
typedef struct ActorBoxesVtbl {
    u8 pad_00[0x88];
    void (*sendBoxes)(void *, s32);
} ActorBoxesVtbl;
extern s16 g_linkStep3Start[];
/* What SceneNode_GetRotation writes: three Fractions of degrees (x, y, z). */
typedef struct RotationDegrees {
    s16 xNum;
    s16 xDen;
    s16 yNum;
    s16 yDen;
    s16 zNum;
    s16 zDen;
} RotationDegrees;
extern s32 g_lookBackSteps[];
extern s32 g_lookBackLimits[];
extern s16 g_turnRotationYaw[];
void DreamSys_ReverseDirection(DreamSys *dreamSys);
extern s32 g_graphVtbl[];
extern u8 g_dreamSysVtbl[];
extern s32 g_walkSpeeds[];
extern s8 g_walkSigns[];
extern void (*g_walkMoves[])(void *, s32, s32);
/* The entity vtable (0x80089AD4, entity.h) as DreamSys_OnEntityEvent calls it. */
typedef struct EventEntityVtbl {
    u8 pad_00[0x38];
    void (*onNotify)(void *, void *, s32);      /* 0x38 Model_OnNotify */
    u8 pad_3C[0x14C - 0x3C];
    s32 (*getRecord)(void *);                   /* 0x14C Entity_GetRecord: the record starts with its mood point */
    s32 (*getPoints)(void *);                   /* 0x150 Entity_GetPoints */
    s32 (*getLinkStage)(void *);                /* 0x154 Entity_GetLinkStage */
    s32 (*getVideo)(void *);                    /* 0x158 Entity_GetVideo */
} EventEntityVtbl;
s32 Link_FindScripted(void *out, void *location, s32 stage);
s32 Link_CheckScripted(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation);
s32 Link_GetStepScript(void);
extern s32 (*g_linkSteps[])(void *);
/* The first 4 bytes of a StagePlace, copied as one: chunk column and row, tile x and y. */
typedef struct { u8 col, row, tileX, tileY; } PlaceTile;
/* One g_tileOffsets entry, 6 bytes copied into StagePlace +4: the x, y (as one word) and z offsets in the tile. */
typedef struct { PlaceTile xy; s16 z; } TileOffset;
/* A spawn point or link target, 6 bytes: the tile, an index into g_tileOffsets and the navigation flag a link sets. */
typedef struct { PlaceTile tile; u8 offsetIndex; s8 navFlag; } SpawnPoint;
/* One entry of a stage link list: chunk key (col | row << 8), tile key (x | y << 8, negative for any tile), target stage and index. */
typedef struct { s16 chunkKey; s16 tileKey; s8 toStage; u8 toIndex; } LinkEntry;
/* A StagePlace as the link and spawn pickers write it. */
typedef struct { PlaceTile tile; TileOffset offset; } PlaceOut;
extern TileOffset g_tileOffsets[];
s32 Link_FindExtra(void *out, void *location, s32 stage);
s32 Link_GetExtraSeconds(void);
extern SpawnPoint *g_spawnPoints[];
extern u8 g_spawnCounts[];
s32 rand();
u32 Stage_FindChunkByMood(void *placeOut, void *mood);
/*
 * The graph screen (vtable g_graphVtbl, class word 0x2F130, 0x244 bytes; Graph_New and Graph_Init are in
 * src/game/80057FC8.c): a MenuScreen (scene.h) whose menu slots draw the mood chart instead of items,
 * one 10 x 10 box per day for the last 100 days of the save block, and that spots the secret reel
 * (docs/discoveries.md, the secret video reel).
 */
typedef struct Graph {
    MenuScreen screen;      /* 0x000 vtbl is g_graphVtbl */
    DreamSys *dreamSys;     /* 0x0A4 Graph_Init's argument: the save block comes from it */
    Widget *boxes[100];     /* 0x0A8 Box_Create boxes: [0] the newest day, then older and older days */
    s32 reelFound;          /* 0x238 Graph_CheckReel: the four reel points are on the chart */
    u32 reelShown;          /* 0x23C reel points painted green so far */
    s8 *reelDays;           /* 0x240 4 bytes: for each reel point, how many days back it was found */
} Graph;

/* g_graphVtbl: the MenuScreen slots (ScreenVtbl), plus one of its own. */
typedef struct GraphVtbl {
    u8 pad_00[0x124];
    void (*blinkReel)(Graph *graph); /* 0x124 Graph_BlinkReel */
} GraphVtbl;

/* A MoodPoint compared whole, as one s16 (x low byte, y high byte). */
typedef struct ReelPoint {
    s16 v;
} ReelPoint;

/* The save block as Graph_CheckReel reads it: SaveBlock (dreamsys.h) with the points as s16 and a signed reelSeen. */
typedef struct ReelSave {
    u8 pad_00[4];
    s32 year;               /* 0x004 */
    s32 day;                /* 0x008 */
    u8 pad_0C[0x18 - 0x0C];
    ReelPoint graph[0x16D]; /* 0x018 */
    u8 pad_2F2[0x467 - 0x2F2];
    s8 reelSeen;            /* 0x467 */
} ReelSave;

s32 Graph_CheckReel(Graph *graph, void *saveBlock);
extern ReelPoint g_reelPoints[]; /* the 4 points of the reel */

/* Slot 0x40 */
void Graph_LoadImage(Graph *graph) {
    graph->screen.fadeSpeed = 5;
    graph->screen.viewPacketCount = 0x190;
    graph->screen.vtbl->setPicture(graph, "ETC\\HGRAPH.TIM", 0);
    graph->screen.vtbl->setTimeout(graph, 10);
}

/* Slot 0x5C: the newest day's box blinks every other tick, then the reel points (slot 0x124). */
void Graph_OnClock(Graph *graph, void *sender, s32 message) {
    SaveBlock *save;

    MenuScreen_GetVtbl()->onClock(graph, sender, message);
    if (graph->screen.focus == MENU_FOCUS_ITEMS) {
        save = graph->dreamSys->vtbl->getSaveBlock(graph->dreamSys, 0);
        if (save->year != 0 || save->day != 0) {
            graph->boxes[0]->vtbl->setVisible(graph->boxes[0], graph->screen.ticks & 1);
        }
    }
    ((GraphVtbl *)graph->screen.vtbl)->blinkReel(graph);
}

/* Slot 0x78: CIRCLE closes the graph, unless the reel was found. */
void Graph_OnCircle(Graph *graph) {
    if (graph->reelFound == 0) {
        graph->screen.vtbl->playSound(graph, 0x10);
        graph->screen.vtbl->close(graph);
    }
}

/* Slot 0xD8: the 100 day boxes, red for the newest, then from white down by 20 per step for the next 6 and by 1 after. */
void Graph_CreateSprites(Graph *graph) {
    GraphColor color;
    s32 i;
    s32 step;

    graph->boxes[0] = Box_Create((s32)g_graphBoxSize, (s32)g_graphNewestColor, 0);
    color = g_graphOldColor;
    i = 1;
    do {
        graph->boxes[i] = Box_Create((s32)g_graphBoxSize, (s32)&color, 0);
        step = (i < 7) ? 0x14 : 1;
        i++;
        color.r -= step;
        color.g -= step;
        color.b -= step;
    } while (i < 100);
    graph->reelDays = Heap_Alloc(4);
}

/* Slot 0xDC */
void Graph_FreeSprites(Graph *graph) {
    s32 i;
    Widget *box;

    Heap_Free((s32)graph->reelDays);
    for (i = 0; i < 100; i++) {
        box = graph->boxes[i];
        box->vtbl->delete_(box);
    }
    MenuScreen_GetVtbl()->freeMenu(graph);
}

/* Slot 0x44: run returns 2 when the reel was found (Scene_RunTitle then plays it). */
s32 Graph_Run(Graph *graph, void *env, s32 watchOnly) {
    s32 result;

    MenuScreen_GetVtbl()->run(graph, env, watchOnly);
    result = 2;
    if (graph->reelFound == 0) {
        result = graph->screen.result;
    }
    return result;
}

/* Slot 0xE0: one box per day, walking back from yesterday; the newest is drawn last, on top. */
void Graph_Draw(Graph *graph, void *root) {
    ScreenPoint pos;
    ScreenPoint newestPos;
    ScreenPoint unused;
    DreamSys *dreamSys;
    Widget *box;
    SaveBlock *save;
    s32 haveNewest;
    s32 k;
    s32 i;
    s32 n;

    MenuScreen_GetVtbl()->showItems(graph, root);
    dreamSys = graph->dreamSys;
    save = dreamSys->vtbl->getSaveBlock(dreamSys, 0);
    graph->reelFound = Graph_CheckReel(graph, save);
    haveNewest = 0;
    if (save->year == 0) {
        n = save->day;
        if (n >= 0x65) {
            n = 0x64;
        }
    } else {
        n = 0x64;
    }
    k = 0;
    i = save->day - 1;
    if (n > 0) {
        do {
            if (i < 0) {
                i = 0x16C;
            }
            pos.x = save->graph[i].x * 10 - 5;
            pos.y = -save->graph[i].y * 10 - 5;
            if (k == 0) {
                newestPos = pos;
                haveNewest = 1;
            } else {
                box = graph->boxes[k];
                box->vtbl->extra(box, root, &pos, 0);
            }
            k += 1;
            i -= 1;
        } while (k < n);
    }
    if (haveNewest != 0) {
        box = graph->boxes[0];
        box->vtbl->extra(box, root, &newestPos, 0);
    }
}

/* Looks for each of the 4 points of g_reelPoints among the last n days (n at most 100), newest first. */
s32 Graph_CheckReel(Graph *graph, void *saveBlock) {
    ReelSave *save = saveBlock;
    s32 n, j, k, count;
    u32 i;

    if (save->reelSeen != 0) return 0;
    if (save->year != 0) n = 100;
    else { n = save->day; if (n > 100) n = 100; }
    i = 0;
loop:
    count = 0;
    k = save->day - 1;
    for (j = 0; j < n; j++) {
        if (k < 0) k = 0x16C;
        if (g_reelPoints[i].v == save->graph[k].v) { count++; graph->reelDays[i] = j; }
        k--;
    }
    if (count == 0) return 0;
    if (++i < 4) goto loop;
    save->reelSeen = 1;
    graph->reelShown = 0;
    return 1;
}

/* Slot 0x124: from tick 31, every 24 ticks, the next matched day turns green (g_graphReelColor). */
void Graph_BlinkReel(Graph *graph) {
    u32 ticks;
    u32 shown;
    Widget *box;

    if (graph->reelFound != 0) {
        ticks = graph->screen.ticks;
        if (ticks >= 0x1F) {
            shown = graph->reelShown;
            if ((shown < 4) && (ticks % 24 == 0)) {
                box = graph->boxes[graph->reelDays[shown]];
                box->vtbl->setColor(box, 1, &g_graphReelColor);
                graph->reelShown = graph->reelShown + 1;
            }
        }
    }
}

void *Graph_GetVtable(void) {
    return g_graphVtbl;
}

void *DreamSys_New(s32 tmd, s32 soundBank, s32 camera) {
    void *dreamSys;

    dreamSys = Heap_Alloc(0x928);
    if (dreamSys != 0) {
        DreamSys_GetVtable()->init(dreamSys, tmd, soundBank, camera);
        return dreamSys;
    }
    return 0;
}

void DreamSys_Init(DreamSys *dreamSys, void **tmd, s32 soundBank, s32 camera) {
    Actor_GetVtbl()->init(dreamSys);
    dreamSys->vtbl = (DreamSysVtbl *)DreamSys_GetVtable();
    dreamSys->soundBank = soundBank;
    dreamSys->camera.obj = camera;
    dreamSys->unk64 = 0;
    dreamSys->unk60 = tmd;
    dreamSys->vtbl->watch(dreamSys, ((TmdModelVtbl *)*tmd)->getModel(tmd, 0));
    dreamSys->vtbl->swapTimeLimit(dreamSys, -1);
    dreamSys->unk70 = 1;
    dreamSys->unk6C = 0;
    dreamSys->neverSaved = 1;
    dreamSys->vtbl->initNewGame(dreamSys);
    dreamSys->vtbl->unk40(dreamSys);
}

void DreamSys_Reset(DreamSys *dreamSys) {
    dreamSys->vtbl->unk60(dreamSys, 0);
    dreamSys->vtbl->unk44(dreamSys, 1, g_dreamerStartRotation);
    dreamSys->unk80 = 0;
    dreamSys->unk98 = 0;
    dreamSys->unkCC.word = 0;
    dreamSys->unk908 = 0;
    dreamSys->unk90C = 0;
    dreamSys->linkStep = 0;
    dreamSys->unk78 = 0;
    dreamSys->unk924 = 0;
}

void DreamSys_EnterMap(DreamSys *dreamSys, void **map) {
    s32 startPos[4];
    Flashback *elem;
    void *arrivalHeading;

    ((MapTargetVtbl *)*map)->setTarget(map, startPos, dreamSys, (u8 *)dreamSys + 0x16C);
    ((ActorAttachVtbl *)Actor_GetVtbl())->attach(dreamSys, map, startPos);
    dreamSys->vtbl->watch(dreamSys, map);
    if (dreamSys->transition == 0xE) {
        elem = &dreamSys->save.flashbacks[dreamSys->nextFlashback];
        dreamSys->vtbl->unk44(dreamSys, 1, elem->rotation.bytes);
        dreamSys->vtbl->swapTimeLimit(dreamSys, elem->length + 4);
        dreamSys->nextFlashback++;
    }
    if (dreamSys->unk6C != 0) {
        arrivalHeading = dreamSys->unk888;
        if (arrivalHeading != 0) {
            dreamSys->vtbl->unk44(dreamSys, 1, arrivalHeading);
        }
    }
}

void DreamSys_LeaveMap(DreamSys *dreamSys) {
    DreamPlayer *map;

    map = dreamSys->player;
    map->vt->unkF0(map);
    dreamSys->vtbl->unwatch(dreamSys, dreamSys->player);
    Actor_GetVtbl()->detach(dreamSys);
}

void DreamSys_OnGroundProbe(DreamSys *dreamSys, s32 message) {
    s32 groundSound;
    DreamPlayer *map;
    DreamPlayer *map2;

    ((ActorBoxesVtbl *)Actor_GetVtbl())->sendBoxes(dreamSys, message);
    switch (message) {
    case -1:
        groundSound = dreamSys->unk28->unk36 & 0x7F;
        dreamSys->unkB8 = groundSound;
        if (groundSound >= 0x18) {
            dreamSys->unkB8 = 0;
        }
        if (dreamSys->transition == 0xF && dreamSys->unkB8 == 0) {
            dreamSys->unkB8 = 2;
        }
        if (dreamSys->stage == 9) {
            map = dreamSys->player;
            dreamSys->vtbl->unk1D4(dreamSys, map->vt->unk10C(map, 0, 0));
        }
        return;
    case -2:
        map2 = dreamSys->player;
        if (map2->vt->unk11C(map2, dreamSys->pos.bytes + 0x18)->unk4->unk2C == 2) {
            map = dreamSys->player;
            dreamSys->vtbl->unk1D4(dreamSys, map->vt->unk10C(map, 0, 0));
        } else {
            dreamSys->vtbl->unk224(dreamSys);
        }
        return;
    }
}

void DreamSys_OnPad(DreamSys *dreamSys, s32 sender, s32 code) {
    if (dreamSys->unk6C == 0 && dreamSys->unk70 == 0) {
        code -= 2;
        if (dreamSys->unk908 == 0) {
            switch (code) {
                case 0:
                    dreamSys->unkA0 = 1;
                    break;
                case 1:
                    dreamSys->unkA0 = 2;
                    break;
                case 2:
                    dreamSys->unkA4 = 1;
                    break;
                case 3:
                    dreamSys->unkA4 = 2;
                    break;
                case 4:
                    dreamSys->unk88 = 1;
                    break;
                case 5:
                    if (dreamSys->unkA0 == 1) {
                        dreamSys->vtbl->unk184(dreamSys, 4);
                    }
                    break;
                case 6:
                    dreamSys->unk88 = 2;
                    break;
                case 11:
                    dreamSys->unk90 = 2;
                    break;
                case 12:
                    dreamSys->unkA0 = 4;
                    break;
                case 13:
                    dreamSys->unk90 = 1;
                    break;
                case 14:
                    dreamSys->unkA0 = 3;
                    break;
                case 23:
                    dreamSys->unk74 = 1;
                    break;
                case 32:
                    dreamSys->vtbl->unk188(dreamSys, sender, code);
                    break;
                case 47:
                    break;
            }
        }
    }
}

void DreamSys_TickTimer(DreamSys *dreamSys, s32 sender, s32 message) {
    u32 ticks;

    if (message == 2) {
        ticks = dreamSys->timer;
        dreamSys->timer = ticks + 1;
        if (ticks >= (u32) dreamSys->timeLimit) {
            if (dreamSys->flashbackMode != 0) {
                if (dreamSys->transition != 0 || dreamSys->vtbl->loadNextFlashback(dreamSys, 0) != 0) {
                reset:
                    dreamSys->timer = 0;
                    return;
                }
            } else {
                dreamSys->vtbl->maybeSaveFlashback(dreamSys, 0, 0x10);
            }
            dreamSys->vtbl->unk30(dreamSys, 0xA);
            goto reset;
        }
        dreamSys->vtbl->unk118(dreamSys);
        dreamSys->vtbl->unk11C(dreamSys);
    }
}

void DreamSys_RouteMapMessage(DreamSys *dreamSys, s32 **sender, s32 message) {
    Actor_GetVtbl()->onNode(dreamSys, sender, message);
    if ((**sender & 0xFFF) == 0x114) {
        dreamSys->vtbl->unk1E4(dreamSys, sender, message);
    }
}

void DreamSys_RouteEntityMessage(DreamSys *dreamSys, s32 **sender, s32 message) {
    Actor_GetVtbl()->onNode34(dreamSys, sender, message);
    if ((**sender & 0xFFFFF) == 0x1F234) {
        dreamSys->vtbl->onEntityEvent(dreamSys, sender, message);
    }
}

void DreamSys_OnWallTouch(DreamSys *dreamSys, s32 **sender, s32 message) {
    DreamPlayer *map;
    StagePlace *touched;

    Actor_GetVtbl()->onNode24(dreamSys, sender, message);
    if (message == 4 && dreamSys->transition == 0) {
        map = dreamSys->player;
        touched = map->vt->unkD4(map, sender);
        dreamSys->place = *touched;
        if (dreamSys->vtbl->linkStatic(dreamSys, &dreamSys->place) == 0 && dreamSys->dynamicLinkOn != 0) {
            dreamSys->vtbl->linkDynamic(dreamSys);
        }
        dreamSys->vtbl->unk224(dreamSys);
        dreamSys->vtbl->unkE8(dreamSys);
    }
}

void func_800590E0(void) {
}

s32 DreamSys_SetFlashbackMode(DreamSys *dreamSys, s32 *colorOut, s32 mode) {
    s32 oldMode;

    oldMode = dreamSys->flashbackMode;
    if (mode < 0) {
        *colorOut = Mood_GetColor((s16 *)((u8 *)dreamSys + (dreamSys->save.day * 2 + 0x190)));
    } else {
        dreamSys->flashbackMode = mode;
    }
    return oldMode;
}

void DreamSys_SetAutoWalk(DreamSys *dreamSys, s32 mode) {
    s32 heading;

    dreamSys->unk6C = mode;
    if (mode != 0) {
        dreamSys->vtbl->unk180(dreamSys, 1);
        heading = dreamSys->unk884;
        if (heading != 0) {
            dreamSys->vtbl->unk44(dreamSys, 1, heading);
        }
    }
}

void DreamSys_StartPlace(DreamSys *dreamSys, s32 speed, s32 linkPeriod) {
    RotationDegrees rotation;

    dreamSys->vtbl->logChunkMood(dreamSys, &dreamSys->place);
    dreamSys->vtbl->unk138(dreamSys, 1);
    dreamSys->vtbl->unk13C(dreamSys, 1);
    dreamSys->vtbl->unk180(dreamSys, speed);
    dreamSys->unkBC = -1;
    dreamSys->unkB4 = 0;
    dreamSys->unkB8 = 0;
    dreamSys->unkA0 = 0;
    dreamSys->unkA4 = 0;
    dreamSys->unk88 = 0;
    dreamSys->unk90 = 0;
    dreamSys->unk8C = 0;
    dreamSys->unk94 = 0;
    dreamSys->vtbl->unk18C(dreamSys, 0, 1, 1, 1);
    dreamSys->vtbl->unk190(dreamSys, linkPeriod);
    dreamSys->cinematic.id.variant = -1;
    dreamSys->unk70 = 0;
    dreamSys->transition = 0;
    dreamSys->unk74 = 0;
    dreamSys->unk908 = 0;
    dreamSys->unk90C = 0;
    dreamSys->linkStep = 0;
    dreamSys->unk78 = 0;
    SceneNode_GetRotation(dreamSys, (s32 *)&rotation);
    rotation.zNum = 0;
    rotation.zDen = 1;
    dreamSys->vtbl->unk44(dreamSys, 1, &rotation);
}

void DreamSys_LockControls(DreamSys *dreamSys) {
    dreamSys->unk70 = 1;
}

s32 DreamSys_WasCirclePressed(DreamSys *dreamSys) {
    return dreamSys->unk74;
}

s32 DreamSys_SwapTimeLimit(DreamSys *dreamSys, s32 seconds) {
    s32 old;

    if (seconds >= 0) {
        seconds *= 15;
    }
    old = dreamSys->timeLimit;
    dreamSys->timeLimit = seconds;
    if (old >= 0) {
        old = (u32)old / 15;
    }
    return old;
}

u32 DreamSys_GetElapsedSeconds(DreamSys *dreamSys) {
    return dreamSys->timer / 15;
}

void DreamSys_SetSoundBank(DreamSys *dreamSys, s32 value) {
    dreamSys->soundBank = value;
}

void DreamSys_SetCamera(DreamSys *dreamSys, s32 value) {
    dreamSys->camera.obj = value;
}

void DreamSys_SetEtcTim(DreamSys *dreamSys, s32 value) {
    dreamSys->unk64 = value;
}

void DreamSys_TickBegin(DreamSys *dreamSys) {
    if (dreamSys->unk70 == 0) {
        dreamSys->unk74 = 0;
        dreamSys->dynamicLinkOn = dreamSys->timer % dreamSys->unk120 == 0;
    }
}

void DreamSys_TickHandlers(DreamSys *dreamSys) {
    if (dreamSys->unk80 != NULL) {
        dreamSys->unk80();
    }
    if (dreamSys->unk98 != NULL) {
        dreamSys->unk98(dreamSys);
    }
}

s32 DreamSys_TestPointAhead(DreamSys *dreamSys, Vec3 *pointOut, s32 distance, s32 *pos, s32 range) {
    Vec3 point;
    s32 height;
    s32 *worldPos;

    g_pointAheadZ[0] = distance;
    SceneNode_LocalToWorld(dreamSys, &point, &g_pointAheadZ[-2], 0);
    height = DreamSys_GetSightHeight((ScreenVec *)(dreamSys->camera.bytes + 0x14), (ScreenVec *)(dreamSys->camera.bytes + 0x20), distance);
    if (dreamSys->unkC != 0) {
        worldPos = (s32 *)(dreamSys->pos.bytes + 0x38);
    } else {
        worldPos = NULL;
    }
    point.y = height + worldPos[1];
    if (pointOut != NULL) {
        *pointOut = point;
    }
    if (pos != NULL) {
        return Entity_IsWithinBox((s32 *)&point, range, pos);
    }
    return 0;
}

s32 DreamSys_GetSightHeight(ScreenVec *start, ScreenVec *end, s32 pos) {
    s32 span;

    pos /= 1024;
    span = (end->z - start->z) / 1024;
    if (span == 0) {
        span = 1;
    }
    return ((end->y - start->y) * pos) / span + start->y;
}

void func_80059590(DreamSys *dreamSys) {
    dreamSys->unk7C = 0;
}

void func_80059598(DreamSys *dreamSys) {
    dreamSys->unk78 = 0;
}

s32 func_800595A0(void) {
    return 0;
}

void DreamSys_StopControls(DreamSys *dreamSys, s32 stopLook) {
    dreamSys->vtbl->unk13C(dreamSys, 0);
    if (stopLook != 0) {
        dreamSys->vtbl->unk138(dreamSys, 0);
    }
}

void DreamSys_SetControls(DreamSys *dreamSys, s32 moveMode, s32 lookMode) {
    dreamSys->vtbl->unk13C(dreamSys);
    dreamSys->vtbl->unk138(dreamSys, lookMode);
}

void DreamSys_SetLookMode(DreamSys *dreamSys, s32 mode) {
    DreamSysVtbl *vtbl = dreamSys->vtbl;

    dreamSys->unk84 = mode;
    switch (mode) {
    case 0:
        dreamSys->unk80 = 0;
        return;
    case 1:
        dreamSys->unk80 = vtbl->unk140;
        return;
    case 2:
        dreamSys->unk80 = vtbl->unk14C;
        return;
    case 3:
        dreamSys->unk80 = vtbl->unk150;
        return;
    }
}

void DreamSys_SetMoveMode(DreamSys *dreamSys, s32 mode) {
    DreamSysVtbl *vt;

    vt = dreamSys->vtbl;
    if (dreamSys->unk9C == 2) {
        vt->unk17C(dreamSys, 0);
    }
    dreamSys->unk9C = mode;
    switch (mode) {
    case 0:
        dreamSys->unk98 = 0;
        return;
    case 1:
        dreamSys->unk98 = vt->unk154;
        return;
    case 2: {
        s32 handler;
        DreamSysVtbl *vtblAgain;

        handler = vt->unk178;
        vtblAgain = dreamSys->vtbl;
        dreamSys->unkC4 = 1;
        dreamSys->unkC8 = 1;
        dreamSys->unk98 = handler;
        HandlerNode_Start(dreamSys->soundBank, dreamSys->unkCC.bytes, 1, dreamSys, vtblAgain->unk194);
        return;
    }
    }
}

void DreamSys_TickLook(DreamSys *dreamSys) {
    dreamSys->vtbl->unk144(dreamSys);
    dreamSys->vtbl->unk148(dreamSys);
}

void DreamSys_TickPitch(DreamSys *dreamSys) {
    s32 newPitch;
    s32 step;
    s32 pitch;
    s32 limit;
    DreamCamera *camera2;
    DreamCamera *camera;
    s32 input;

    input = dreamSys->unk88;
    if (input != 0) {
        step = g_pitchSteps[input];
        limit = g_pitchLimits[input];
        newPitch = step + dreamSys->unk8C;
        if ((newPitch < 0 ? ~newPitch + 1 : newPitch) < limit) {
            camera = dreamSys->camera.obj;
            camera->unk24 = (u32) (step + camera->unk24);
            dreamSys->unk8C = newPitch;
        }
        dreamSys->unk88 = 0;
        return;
    }
    pitch = dreamSys->unk8C;
    if (pitch != 0) {
        step = -0x258;
        if (pitch < 0) {
            step = 0x258;
        }
        camera2 = dreamSys->camera.obj;
        camera2->unk24 = (u32) (step + camera2->unk24);
        dreamSys->unk8C = (s32) (step + dreamSys->unk8C);
    }
}

void DreamSys_TickLookBack(DreamSys *dreamSys) {
    s32 step;
    s32 sum;
    s32 lim;

    dreamSys->unkA8 = dreamSys->unkA0 == 1;
    if (dreamSys->unk90 != 0) {
        step = g_lookBackSteps[dreamSys->unk90];
        sum = step + dreamSys->unk94;
        lim = g_lookBackLimits[dreamSys->unk90];
        if ((sum < 0 ? ~sum + 1 : sum) < lim) {
            g_turnRotationYaw[0] = step;
            dreamSys->vtbl->unk44(dreamSys, 0, &g_turnRotationYaw[-2]);
            dreamSys->unk94 = sum;
        }
        dreamSys->unk90 = 0;
        DreamSys_ReverseDirection(dreamSys);
    } else if (dreamSys->unk94 != 0) {
        step = dreamSys->unk94 < 0 ? 0x2D : -0x2D;
        g_turnRotationYaw[0] = step;
        dreamSys->vtbl->unk44(dreamSys, 0, &g_turnRotationYaw[-2]);
        dreamSys->unk94 += step;
        DreamSys_ReverseDirection(dreamSys);
    }
}

void DreamSys_ReverseDirection(DreamSys *dreamSys) {
    s32 direction;
    s32 reversed;

    direction = dreamSys->unkA0;
    dreamSys->unkA8 = 0;
    if (direction != 0) {
        if (direction & 1) {
            reversed = direction + 1;
        } else {
            reversed = direction - 1;
        }
        dreamSys->unkA0 = reversed;
    }
}

void func_80059A48(void) {
}

void func_80059A50(void) {
}

void DreamSys_TickMove(DreamSys *dreamSys) {
    if (dreamSys->unk6C == 0) {
        dreamSys->vtbl->unk174(dreamSys);
        dreamSys->vtbl->unk158(dreamSys);
    } else if (dreamSys->unk6C == 2) {
        dreamSys->vtbl->unk160(dreamSys);
    } else {
        dreamSys->vtbl->unk15C(dreamSys);
    }
}

void DreamSys_TickWalk(DreamSys *dreamSys) {
    if (dreamSys->unk70 == 0) {
        dreamSys->vtbl->unk170(dreamSys, dreamSys->vtbl->unk164(dreamSys, 1));
    }
}

void DreamSys_TickAutoWalk(DreamSys *dreamSys) {
    dreamSys->unkA0 = 1;
    if (dreamSys->unk70 == 0) {
        dreamSys->vtbl->unk170(dreamSys, dreamSys->vtbl->unk164(dreamSys, 1));
    } else {
        dreamSys->vtbl->unk164(dreamSys, 0);
    }
}

void DreamSys_SetForward(DreamSys *dreamSys) {
    dreamSys->unkA0 = 1;
}

s32 DreamSys_TickStep(DreamSys *dreamSys, void *allowShake) {
    s32 playSound = 0;
    s32 direction;
    s32 tick;
    s32 bit;
    s32 step;
    DreamCamera *camera = allowShake;

    direction = 0;
    if (dreamSys->unkA0 != 0) {
        direction = dreamSys->unkA0;
        tick = dreamSys->unkB4 + 1;
        dreamSys->unkB4 = tick;
        if (tick < 4) {
            if (dreamSys->unkAC == 4) {
                bit = tick & 1;
                playSound = bit == 0;
            }
        } else {
            dreamSys->unkA0 = 0;
            playSound = 1;
        }
        if (playSound != 0) {
            dreamSys->vtbl->unk168(dreamSys);
        }
        camera = dreamSys->camera.obj;
        if (camera != 0 && dreamSys->save.shake != 0 && allowShake != 0) {
            step = -0x32;
            if (dreamSys->unkB4 >= 3) {
                step = 0x32;
            }
            camera->unk18 += step;
            camera->unk24 += step;
        }
        if (dreamSys->unkA0 == 0) {
            dreamSys->unkB4 = 0;
        }
    }
    if (playSound == 0) {
        dreamSys->vtbl->unk16C(dreamSys, camera);
    }
    return direction;
}

void DreamSys_PlayStepSound(DreamSys *dreamSys) {
    SoundBank *bank = dreamSys->soundBank;
    s32 groundSound = dreamSys->unkB8;
    SoundBankVtbl *bankVtbl = bank->vtbl;
    s32 tone;

    if (groundSound != 0) {
        tone = g_stepSoundTones[groundSound] * 0x10;
        bankVtbl->setOctave(bank, g_stepSoundOctaves[groundSound]);
        dreamSys->unkBC = bankVtbl->playTone(bank, tone, 0x6E, 0x6E);
        if (dreamSys->unkB8 != 0x16) {
            dreamSys->unkBC = -1;
        }
        if (dreamSys->unkB8 == 0xB) {
            bankVtbl->setOctave(bank, 1);
            bankVtbl->playTone(bank, tone, 0x6E, 0x6E);
            bankVtbl->setOctave(bank, 2);
            bankVtbl->playTone(bank, 0x90, 0x6E, 0x6E);
        }
    }
}

void DreamSys_StopStepSound(DreamSys *dreamSys) {
    s32 voice;
    SoundBank *bank;

    voice = dreamSys->unkBC;
    if (voice >= 0) {
        bank = dreamSys->soundBank;
        bank->vtbl->stopVoice(bank, voice);
        dreamSys->unkBC = -1;
    }
}

void DreamSys_Walk(DreamSys *dreamSys, s32 direction) {
    s32 distance;
    s32 location;
    DreamPlayer *map;
    Coord2 *coord;

    if (direction != 0) {
        distance = g_walkSigns[direction] * g_walkSpeeds[dreamSys->unkAC];
        dreamSys->vtbl->unk12C(dreamSys);
        map = dreamSys->player;
        location = map->vt->unk10C(map, 0, 0);
        if (dreamSys->vtbl->unk1DC(dreamSys, location) == 0 && dreamSys->vtbl->unk1D8(dreamSys, location) == 0 && dreamSys->vtbl->unk1D0(dreamSys, location) == 0) {
            dreamSys->vtbl->unk220(dreamSys);
            g_walkMoves[direction](dreamSys, distance, dreamSys->unk90C == 0);
            if (dreamSys->stage == 0) {
                coord = dreamSys->pos.coord;
                if (coord->coord.t.y < -0x7D0 && coord->coord.t.x >= -0x1F3) {
                    dreamSys->vtbl->onWallTouch(dreamSys, dreamSys, 4);
                }
            }
        }
        dreamSys->pos.coord->flg = 0;
    }
}

void DreamSys_TickTurn(DreamSys *dreamSys) {
    s32 turn;

    turn = dreamSys->unkA4;
    if (turn != 0) {
        dreamSys->vtbl->unk44(dreamSys, 0, g_turnRotations + turn * 12);
        dreamSys->unkA4 = 0;
    }
}

void DreamSys_TickFall(DreamSys *dreamSys) {
    DreamCamera *camera;

    if (dreamSys->unkC4 != 0) {
        dreamSys->vtbl->move(dreamSys, g_fallStep);
        camera = dreamSys->camera.obj;
        camera->unk24 = camera->unk24 - 0x258;
    }
    if (dreamSys->unkC8 != 0) {
        HandlerNode_Run((s32) dreamSys->soundBank, dreamSys->unkCC.bytes);
    }
}

void DreamSys_EndFall(DreamSys *dreamSys, s32 stopSound) {
    dreamSys->unkC4 = 0;
    dreamSys->unkC8 = stopSound;
    if (stopSound != 0) {
        HandlerNode_Stop(dreamSys->soundBank, dreamSys->unkCC.bytes);
    }
}

s32 DreamSys_SwapSpeed(DreamSys *dreamSys, s32 speed) {
    s32 old;

    old = dreamSys->unkAC;
    if (speed >= 0) {
        dreamSys->unkAC = speed;
        dreamSys->unkB0 = speed;
    }
    return old;
}

void DreamSys_PushSpeed(DreamSys *dreamSys, s32 speed) {
    s32 current;

    current = dreamSys->unkAC;
    if (current != speed) {
        dreamSys->unkB0 = current;
        dreamSys->unkAC = speed;
    }
}

void DreamSys_PopSpeed(DreamSys *dreamSys) {
    dreamSys->unkAC = dreamSys->unkB0;
}

void DreamSys_SetLinkFlags(DreamSys *dreamSys, s32 dynamicLinkOn, s32 arg2, s32 arg3, s32 arg4) {
    if (dynamicLinkOn >= 0) {
        dreamSys->dynamicLinkOn = dynamicLinkOn;
    }
    if (arg2 >= 0) {
        dreamSys->unk128 = arg2;
    }
    if (arg3 >= 0) {
        dreamSys->unk12C = arg3;
    }
    if (arg4 >= 0) {
        dreamSys->unk130 = arg4;
    }
}

void DreamSys_SetLinkPeriod(DreamSys *dreamSys, s32 period) {
    dreamSys->unk120 = period;
}

void DreamSys_FallSoundHandler(s32 owner, HandlerNode *node) {
    s32 r;
    if (node->id == 1) {
        r = node->tick % 20; if (r == 0) {
            node->voices[0].sound = 9;
            node->voices[0].octave = -1;
        } else {
            node->voices[1].sound = 9;
            node->voices[1].octave = -1;
        }
    }
}

void DreamSys_InitNewGame(DreamSys *dreamSys) {
    dreamSys->save.magic = g_saveMagic;
    dreamSys->save.year = 0;
    dreamSys->save.day = 0;
    dreamSys->save.unlockScore = 0;
    dreamSys->save.navScore = 0;
    dreamSys->save.instanceScore = 0;
    dreamSys->save.flashbackCount = 0;
    dreamSys->save.reelSeen = 0;
    dreamSys->save.unk460 = 0;
    dreamSys->save.shake = 1;
    dreamSys->save.unk504 = 0;
    dreamSys->save.unk508 = 0;
    Nav_InitFlags(dreamSys->save.navFlags, &dreamSys->save.dynamicLinkCount);
    memset(dreamSys->save.unk50C, 0, 0x1F4);
}

void DreamSys_SwapShake(DreamSys *dreamSys, s32 *shake) {
    s32 old;

    old = dreamSys->save.shake;
    dreamSys->save.shake = *shake;
    *shake = old;
}

s32 DreamSys_GetDayNumber(DreamSys *dreamSys, s32 *yearOut) {
    if (yearOut != NULL) {
        *yearOut = dreamSys->save.year;
    }
    return dreamSys->save.day + 1;
}

s32 DreamSys_AdvanceDay(DreamSys *dreamSys) {
    if (++dreamSys->save.day >= 365) {
        dreamSys->save.day = 0;
        dreamSys->save.year++;
    }
    return dreamSys->save.day;
}

void DreamSys_ClearNeverSaved(DreamSys *dreamSys) {
    dreamSys->neverSaved = 0;
}

s32 DreamSys_IsNeverSaved(DreamSys *dreamSys) {
    return dreamSys->neverSaved;
}

s32 DreamSys_GetSaveBlock(s32 dreamSys, s32 *sizeOut) {
    if (sizeOut != NULL) {
        *sizeOut = 0x700;
    }
    return dreamSys + 0x178;
}

s32 DreamSys_StartDay(DreamSys *dreamSys) {
    s32 specialPoint;

    dreamSys->nextFlashback = 0;
    dreamSys->timer = 0;
    dreamSys->savedDay = dreamSys->save.day;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->vtbl->loadNextFlashback(dreamSys, 1);
        return dreamSys->stage;
    }
    specialPoint = Day_FindSpecial(dreamSys->cinematic.bytes, dreamSys->save.day + 1);
    dreamSys->vtbl->resetMoodAccumulators(dreamSys, specialPoint);
    if (specialPoint == 0) {
        dreamSys->vtbl->chooseStart(dreamSys);
        return dreamSys->stage;
    }
    return -1;
}

s32 DreamSys_EndDay(DreamSys *dreamSys, s32 reason) {
    dreamSys->save.day = dreamSys->savedDay;
    if (dreamSys->flashbackMode == 0 && reason == 0) {
        dreamSys->vtbl->calcUnlockScore(dreamSys);
        dreamSys->vtbl->computeDayPoint(dreamSys, &dreamSys->save.graph[dreamSys->save.day]);
        dreamSys->vtbl->advanceDay(dreamSys);
    } else if (reason == 2) {
        dreamSys->vtbl->initNewGame(dreamSys);
        dreamSys->neverSaved = 1;
    }
    return dreamSys->flashbackMode;
}

CineRef DreamSys_GetCinematic(DreamSys *dreamSys) {
    return dreamSys->cinematic.ref;
}

void DreamSys_ChooseStart(DreamSys *dreamSys) {
    s32 prevPoint;
    s32 seconds;

    dreamSys->vtbl->getPreviousPoint(dreamSys, &prevPoint, 1);
    dreamSys->stage = Spawn_PickFromMood(&dreamSys->place, &seconds, &prevPoint, dreamSys->save.day);
    seconds = dreamSys->vtbl->swapTimeLimit(dreamSys, seconds);
    dreamSys->transition = 0xB;
}

void DreamSys_LinkDynamic(DreamSys *dreamSys) {
    if (dreamSys->transition == 0) {
        DreamSys_ExecuteLink(dreamSys, Spawn_PickRandom(&dreamSys->place, dreamSys->stage, dreamSys->timer), 0xC, 1);
    }
}

s32 DreamSys_LinkStatic(DreamSys *dreamSys, void *target) {
    s32 newStage;

    if (dreamSys->transition == 0) {
        newStage = Link_FindStatic(&dreamSys->place, target, dreamSys->stage);
        if (newStage >= 0) {
            DreamSys_ExecuteLink(dreamSys, newStage, 0xD, 1);
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 DreamSys_LoadNextFlashback(DreamSys *dreamSys, s32 quiet) {
    Flashback *elem;
    s32 idx;

    idx = dreamSys->nextFlashback;
    if (idx < dreamSys->save.flashbackCount) {
        dreamSys->transition = 0xE;
        elem = &dreamSys->save.flashbacks[idx];
        if (quiet == 0) {
            dreamSys->vtbl->unk30(dreamSys, 0xE);
        }
        dreamSys->save.day = elem->day;
        dreamSys->stage = elem->stage;
        dreamSys->place = elem->place;
        return 1;
    }
    return 0;
}

s32 DreamSys_LinkFacing(DreamSys *dreamSys, s16 *location) {
    s32 rotation[4];
    s32 newStage;

    if (dreamSys->transition != 0) {
        return 0;
    }
    newStage = Link_FindFacing(&dreamSys->place, location, dreamSys->stage);
    if (newStage < 0) {
        return 0;
    }
    SceneNode_GetRotation(dreamSys, rotation);
    if (Link_CheckFacing(&dreamSys->unk888, &dreamSys->unk884, rotation) == 0) {
        return 0;
    }
    if (dreamSys->unkA8 == 0) {
        return 0;
    }
    DreamSys_ExecuteLink(dreamSys, newStage, 0xF, 0);
    return 1;
}

s32 DreamSys_LinkFall(DreamSys *dreamSys, s32 location) {
    s32 newStage;

    if (dreamSys->transition == 0) {
        newStage = Link_PickFallStage(&dreamSys->place, dreamSys->stage, location, dreamSys->timer);
        if (newStage >= 0) {
            dreamSys->unk880 = func_8005BF48();
            dreamSys->unk884 = 0;
            dreamSys->unk888 = 0;
            DreamSys_ExecuteLink(dreamSys, newStage, 0x10, 0);
            return 1;
        }
    }
    return 0;
}

s32 DreamSys_LinkExtra(DreamSys *dreamSys, void *location) {
    s32 worldPos[4];
    s32 bonusSeconds;
    s32 newStage;

    newStage = Link_FindExtra(&dreamSys->place, location, dreamSys->stage);
    if (newStage >= 0) {
        bonusSeconds = Link_GetExtraSeconds();
        if (DreamSys_ExecuteLink(dreamSys, newStage, 0x11, 0) != 0) {
            dreamSys->transition = 0;
            dreamSys->player->vt->unkE8(dreamSys->player, worldPos, &dreamSys->place);
            dreamSys->vtbl->setPosition(dreamSys, worldPos);
            if (bonusSeconds != 0 && dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->swapTimeLimit(dreamSys, dreamSys->vtbl->getElapsedSeconds(dreamSys) + bonusSeconds);
            }
        }
        return 1;
    }
    return 0;
}

s32 DreamSys_ExecuteLink(DreamSys *dreamSys, s32 newStage, s32 transition, s32 playSound) {
    dreamSys->transition = transition;
    dreamSys->vtbl->unk30(dreamSys, transition);
    if (dreamSys->transition == 0) {
        return 0;
    }
    dreamSys->stage = newStage;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->timer = 0;
    }
    if (playSound != 0) {
        SoundBank *bank = dreamSys->soundBank;
        bank->vtbl->playTone(bank, 0x90, 0x6E, 0x6E);
    }
    return 1;
}

s32 DreamSys_StartLinkStep(DreamSys *dreamSys, StagePlace *target) {
    s32 rotation[4];

    if (dreamSys->transition == 0) {
        if (dreamSys->linkStep != 0) {
            if (dreamSys->linkStep(dreamSys) != 0) {
                dreamSys->unk908 = 0;
                dreamSys->linkStep = 0;
                dreamSys->unk90C = 0;
                if (dreamSys->unkAC == 4) {
                    dreamSys->vtbl->unk188(dreamSys);
                    return 0;
                }
            }
            return 0;
        }
        if (Link_FindScripted(&dreamSys->place, target, dreamSys->stage) >= 0) {
            SceneNode_GetRotation(dreamSys, rotation);
            if (Link_CheckScripted((u8 **)&dreamSys->unk888, (u8 **)&dreamSys->unk884, (RotationYaw *)rotation) != 0 && dreamSys->unkA8 != 0) {
                dreamSys->linkTarget = *target;
                dreamSys->unk908 = 1;
                dreamSys->unk90C = 1;
                dreamSys->linkStepTick = 0;
                dreamSys->linkStep = g_linkSteps[Link_GetStepScript()];
                dreamSys->vtbl->unk44(dreamSys, 1, dreamSys->unk884);
                dreamSys->linkStep(dreamSys);
            }
        }
    }
    return 0;
}

s32 DreamSys_LinkStep0(DreamSys *dreamSys) {
    s32 tick;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep0Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->unkAC != 4) {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x85) {
            return 1;
        }
        if ((tick >= 0x2B && tick < 0x3A) || (tick >= 0x4B && tick < 0x5A)) {
            dreamSys->unkA4 = 2;
        }
    } else {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x13) {
            return 1;
        }
        if ((tick >= 8 && tick < 0xA) || (tick >= 0xD && tick < 0xF)) {
            dreamSys->vtbl->unk44(dreamSys, 0, g_yawPlus45);
        }
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 DreamSys_LinkStep1(DreamSys *dreamSys) {
    s32 lookDown;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep1Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->unkAC != 4) {
        if (dreamSys->linkStepTick >= 0x95) {
            return 1;
        }
        if ((u32)(dreamSys->linkStepTick - 0x16) < 0xF || (u32)(dreamSys->linkStepTick - 0x39) < 0x10 || (u32)(dreamSys->linkStepTick - 0x6E) < 0xF) {
            dreamSys->unkA4 = 1;
        }
        lookDown = (u32)(dreamSys->linkStepTick - 0x39) < 0x35;
    } else {
        if (dreamSys->linkStepTick >= 0x19) {
            return 1;
        }
        if ((u32)(dreamSys->linkStepTick - 6) < 2 || (u32)(dreamSys->linkStepTick - 0xB) < 2 || (u32)(dreamSys->linkStepTick - 0x14) < 2) {
            dreamSys->vtbl->unk44(dreamSys, 0, g_yawMinus45);
        }
        lookDown = (u32)(dreamSys->linkStepTick - 3) < 0xE;
    }
    if (lookDown) {
        dreamSys->unk88 = 2;
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 DreamSys_LinkStep2(DreamSys *dreamSys) {
    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep2Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->unkAC != 4) {
        if (dreamSys->linkStepTick > 100) {
            return 1;
        }
        if (dreamSys->linkStepTick >= 43 && dreamSys->linkStepTick < 58) {
            dreamSys->unkA4 = 2;
        }
    } else {
        if (dreamSys->linkStepTick > 14) {
            return 1;
        }
        if (dreamSys->linkStepTick >= 8 && dreamSys->linkStepTick < 10) {
            dreamSys->vtbl->unk44(dreamSys, 0, g_yawPlus45);
        }
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 DreamSys_LinkStep3(DreamSys *dreamSys) {
    s32 tick;
    s32 lookDown;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep3Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->unkAC != 4) {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x71) {
            return 1;
        }
        if ((u32)(tick - 0x1E) < 0xF || (u32)(tick - 0x52) < 0xF) {
            dreamSys->unkA4 = 1;
        }
        lookDown = (u32)(dreamSys->linkStepTick - 0x1E) < 0x34;
    } else {
        tick = dreamSys->linkStepTick;
        if (tick >= 0x13) {
            return 1;
        }
        if ((u32)(tick - 6) < 2 || (u32)(tick - 0xF) < 2) {
            dreamSys->vtbl->unk44(dreamSys, 0, g_yawMinus45);
        }
        lookDown = (u32)dreamSys->linkStepTick < 9;
    }
    if (lookDown) {
        dreamSys->unk88 = 2;
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

void DreamSys_MoveToTileOffset(DreamSys *dreamSys, s16 *from, s16 *to) {
    s32 delta[3];

    delta[0] = from[0] - to[0];
    delta[1] = from[1] - to[1];
    delta[2] = from[2] - to[2];
    delta[1] = 0;
    dreamSys->vtbl->move(dreamSys, delta);
}

s32 DreamSys_GetStage(DreamSys *dreamSys) {
    return dreamSys->stage;
}

void DreamSys_OnMapMessage(DreamSys *dreamSys, MapLocateView *sender, s32 message) {
    if (message == 5) {
        dreamSys->vtbl->logChunkMood(dreamSys, sender->vt->getLocation(sender, 0, 0));
    }
}

void DreamSys_OnEntityEvent(DreamSys *dreamSys, EventEntityVtbl **entity, s32 message) {
    s32 oldStage;

    if (dreamSys->transition == 0) {
        switch (message) {
        case 4:
            (*entity)->onNotify(entity, dreamSys, message);
            return;
        case 9:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->logEntityMood(dreamSys, (*entity)->getRecord(entity));
                dreamSys->save.instanceScore = (*entity)->getPoints(entity) + dreamSys->save.instanceScore;
                dreamSys->vtbl->maybeSaveFlashback(dreamSys, 0, 0x10);
                return;
            }
            break;
        case 10:
            oldStage = dreamSys->stage;
            dreamSys->stage = -(*entity)->getLinkStage(entity);
            dreamSys->vtbl->linkDynamic(dreamSys);
            if (dreamSys->stage < 0) {
                dreamSys->stage = oldStage;
                return;
            }
            break;
        case 11:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->cinematic.id.category = -1;
                dreamSys->timer = dreamSys->timeLimit;
                dreamSys->cinematic.id.variant = (*entity)->getVideo(entity);
                return;
            }
            break;
        case 12:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->timer = dreamSys->timeLimit;
            }
            break;
        }
    }
}

void DreamSys_GetPreviousPoint(DreamSys *dreamSys, MoodPoint *out, s32 yesterday) {
    s32 sum1 = 0;
    s32 sum0 = 0;
    s32 count;
    s32 i;
    MoodPoint *p;

    if (yesterday != 0) {
        if (dreamSys->save.year != 0 || dreamSys->save.day != 0) {
            sum0 = dreamSys->save.graph[dreamSys->save.day - 1].x;
            sum1 = dreamSys->save.graph[dreamSys->save.day - 1].y;
        }
    } else {
        count = 365;
        if (dreamSys->save.year == 0) {
            count = dreamSys->save.day;
        }
        if (count != 0) {
            p = dreamSys->save.graph;
            for (i = 0; i < count; i++, p++) {
                sum0 += p->x;
                sum1 += p->y;
            }
            sum0 = sum0 / count;
            sum1 = sum1 / count;
        }
    }
    out->x = sum0;
    out->y = sum1;
}

void DreamSys_ResetMoodAccumulators(DreamSys *dreamSys, s32 point) {
    MoodAccum *chunk = &dreamSys->chunkMood;
    MoodAccum *entity = &dreamSys->entityMood;

    dreamSys->vtbl->moodReset(dreamSys, chunk);
    dreamSys->vtbl->moodReset(dreamSys, entity);
    if (point != 0) {
        dreamSys->vtbl->moodLog(dreamSys, chunk, point);
        dreamSys->vtbl->moodLog(dreamSys, entity, point);
    }
}

void DreamSys_LogChunkMood(DreamSys *dreamSys, s8 *place) {
    dreamSys->vtbl->moodLog(dreamSys, &dreamSys->chunkMood, Stage_GetChunkMood(dreamSys->stage, place));
}

void DreamSys_LogEntityMood(DreamSys *dreamSys, s32 point) {
    dreamSys->vtbl->moodLog(dreamSys, &dreamSys->entityMood, point);
}

void DreamSys_ComputeDayPoint(DreamSys *dreamSys, MoodPoint *out) {
    s16 chunkPoint;
    s16 entityPoint;

    dreamSys->vtbl->moodResolve(dreamSys, &dreamSys->chunkMood, &chunkPoint);
    dreamSys->vtbl->moodResolve(dreamSys, &dreamSys->entityMood, &entityPoint);
    if (dreamSys->entityMood.count == 0) {
        entityPoint = chunkPoint;
    }
    out->x = ((s8)chunkPoint + (s8)entityPoint) / 2;
    out->y = (((s8 *)&chunkPoint)[1] + ((s8 *)&entityPoint)[1]) / 2;
}

void DreamSys_GetDreamColor(DreamSys *dreamSys) {
    s16 point;

    dreamSys->vtbl->computeDayPoint(dreamSys, &point);
    Mood_GetColor(&point);
}

s32 Mood_GetColor(s16 *point) {
    s8 buf[2];
    s8 *p;
    s32 i;
    s8 v;


    *(u16 *)buf = *(u16 *)point;
    p = buf;
    i = 0;
    do {
        v = *p;
        if (v >= 4) {
            *p = 2;
        } else if (v < -3) {
            *p = 0;
        } else {
            *p = 1;
        }
        i++;
        p++;
    } while (i < 2);
    return g_moodColors[buf[0]][buf[1]];
}

void Mood_Reset(DreamSys *dreamSys, MoodAccum *accum) {
    accum->last = 0;
    accum->sumY = 0;
    accum->sumX = 0;
    accum->count = 0;
}

void Mood_Log(DreamSys *dreamSys, MoodAccum *accum, MoodPoint *point) {
    s32 sumX;

    sumX = accum->sumX;
    accum->last = *(u16 *)point;
    accum->sumX = point->x + sumX;
    accum->sumY = point->y + accum->sumY;
    accum->count = accum->count + 1;
}

void Mood_Resolve(DreamSys *dreamSys, MoodAccum *accum, MoodPoint *point) {
    if (accum->count != 0) {
        point->x = Mood_CalcAxis(((MoodPoint *)accum)->x, accum->sumX, accum->count);
        point->y = Mood_CalcAxis(((MoodPoint *)accum)->y, accum->sumY, accum->count);
        return;
    }
    *(u16 *)point = *(u16 *)accum;
}

s32 Mood_CalcAxis(s32 last, s32 sum, s32 count) {
    s32 r = sum / count + last / 3;
    if (r > 9) {
        r = -9;
    } else if (r < -9) {
        r = 9;
    }
    return r;
}

void DreamSys_CalcUnlockScore(DreamSys *dreamSys) {
    s32 score;

    dreamSys->save.navScore = Nav_CalcScore();
    score = dreamSys->save.instanceScore;
    if (score < 0) {
        dreamSys->save.instanceScore = 0;
    } else if (score > 0x02FAF080) {
        dreamSys->save.instanceScore = 0x02FAF080;
    }
    dreamSys->save.unlockScore = dreamSys->save.navScore + dreamSys->save.instanceScore;
}

void DreamSys_AddFlashback(DreamSys *dreamSys, s32 stage, StagePlace *place, DreamRotation *rotation, s32 arg4, s32 length, s32 day) {
    Flashback *ent;
    s32 n;

    ent = dreamSys->save.flashbacks;
    n = dreamSys->save.flashbackCount;
    if (n < 10) {
        dreamSys->save.flashbackCount = n + 1;
        ent += n;
    } else {
        ent += dreamSys->timer % 9;
    }
    ent->stage = stage;
    ent->place = *place;
    ent->rotation.rot = *rotation;
    ent->unk1C = arg4;
    ent->length = length;
    ent->day = day;
}

void DreamSys_MaybeSaveFlashback(DreamSys *dreamSys, s32 arg1, s32 length) {
    s32 rotation[4];
    s32 location;
    DreamPlayer *map;

    if (dreamSys->player != NULL) {
        if (rand() % 3 == 0) {
            map = dreamSys->player;
            location = map->vt->unk10C(map, 0, 0);
            SceneNode_GetRotation(dreamSys, rotation);
            dreamSys->vtbl->addFlashback(dreamSys, dreamSys->stage, location, rotation, arg1, length, dreamSys->save.day);
        }
    }
}

void DreamSys_ClearFlashbacks(DreamSys *dreamSys) {
    dreamSys->save.flashbackCount = 0;
}

void DreamSys_SavePosition(DreamSys *dreamSys) {
    Coord2 *src = dreamSys->pos.coord;

    dreamSys->coordCopy = *src;
    dreamSys->paramCopy = *src->param;
}

void DreamSys_RestorePosition(DreamSys *dreamSys) {
    Coord2 *dst = dreamSys->pos.coord;

    *dst = dreamSys->coordCopy;
    *dst->param = dreamSys->paramCopy;
    dst->flg = 0;
}

s32 func_8005BA20(DreamSys *dreamSys, s32 value) {
    s32 old;

    if (value < 0) {
        return dreamSys->unk924;
    }
    old = dreamSys->unk924;
    dreamSys->unk924 = value;
    return old;
}

DreamSysVtbl *DreamSys_GetVtable(void) {
    return (DreamSysVtbl *)g_dreamSysVtbl;
}

void Nav_InitFlags(u8 *flags, s32 *linkCount) {
    s32 i;
    for (i = 29; i >= 0; i--) {
        flags[i] = 0;
    }
    g_navFlags = flags;
    *linkCount = 0;
    g_dynamicLinkCount = linkCount;
}

s32 Nav_CalcScore(void) {
    s32 i;
    s32 sum = 0;

    for (i = 0; i < 30; i++) {
        if (((s8 *)g_navFlags)[i] != 0) {
            sum += 1000000;
        }
    }
    if (sum > 29999999) {
        sum = 50000000;
    }
    sum -= *g_dynamicLinkCount * 11024;
    if (sum < 0) {
        sum = 0;
    }
    return sum;
}

s16 Stage_GetTimeLimit(s32 stage) {
    return g_stageTimeLimits[stage];
}

s32 Spawn_PickRandom(void *place, s32 stage, s32 unused) {
    s32 newStage;
    s32 n;
    PlaceOut *out;
    SpawnPoint *target;

    n = 6;
    if (stage >= 0) {
        newStage = rand() % n;
        if (newStage == stage) {
            newStage += 1;
            if (newStage >= 6) {
                newStage = 0;
            }
        }
    } else {
        newStage = -stage;
    }
    target = (SpawnPoint *)((s32)g_spawnPoints[newStage] + (rand() % g_spawnCounts[newStage]) * 6);
    out = place;
    out->tile = target->tile;
    out->offset = g_tileOffsets[target->offsetIndex];
    *g_dynamicLinkCount += 1;
    return newStage;
}

s32 Link_FindStatic(void *out, void *location, s32 stage) {
    return Link_Find(out, location, stage, g_staticLinkCounts, g_staticLinkLists, g_staticLinkTargets, 1);
}

s32 Link_FindFacing(void *out, s16 *location, s32 stage) {
    return Link_Find(out, location, stage, g_facingLinkCounts, g_facingLinkLists, g_facingLinkTargets, 1);
}

s32 Link_CheckFacing(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation) {
    u8 heading;

    heading = g_facingLinkHeadings[g_linkFromStage][g_linkFromIndex];
    if (Link_IsFacing(rotation, heading) != 0) {
        if (headingOut != NULL) {
            *headingOut = g_linkHeadings + heading * 12;
        }
        if (arrivalOut != NULL) {
            *arrivalOut = g_linkHeadings + g_facingArrivalHeadings[g_linkToStage][g_linkToIndex] * 12;
        }
        return 1;
    }
    return 0;
}

s32 Link_IsFacing(RotationYaw *rotation, u8 heading) {
    s32 diff = rotation->yaw - g_linkHeadingYaws[heading * 6];
    s16 diff16 = diff;
    s16 wrapped;

    wrapped = diff;
    if (diff16 > 0xB4) {
        wrapped -= 0x168;
    } else if (diff16 < -0xB4) {
        wrapped += 0x168;
    }
    return (u16)(wrapped + 0x2C) < 0x59U;
}

s32 Link_PickFallStage(void *place, s32 stage, FallLocation *location, s32 timer) {
    s32 ret;

    if (stage != 3 && stage != 1 && stage != 5 && stage != 9 && stage != 12) {
        return -1;
    }
    if (stage == 5) {
        if (location->y >= -0xFFF && location->tile != g_fallPlace5) {
            return -1;
        }
    } else if (stage == 9) {
        if (location->y < 0x800) {
            return -1;
        }
    }
    if (timer & 1) {
        stage = -12;
    }
    ret = Spawn_PickRandom(place, stage, timer);
    g_linkToStage = ret;
    return ret;
}

s32 *func_8005BF48(void) {
    s32 *r = NULL;
    if (g_linkToStage != 12) {
        r = D_8008ABF0;
    }
    return r;
}

void Link_SetExtraListOn(s32 on) {
    g_extraListOn = on;
}

s32 Link_FindExtra(void *out, void *location, s32 stage) {
    if (g_extraListOn != 0) {
        return Link_Find(out, location, stage, &g_extraLinkCounts, &g_extraLinkLists, &g_extraLinkTargets, 0);
    }
    return -1;
}

s32 Link_GetExtraSeconds(void) {
    return g_linkFromStage == 0 ? 10 : 0;
}

s32 Link_FindScripted(void *out, void *location, s32 stage) {
    if (stage == 0) {
        return Link_Find(out, location, 0, g_scriptedLinkCounts, g_scriptedLinkLists, (s32 *)g_scriptedLinkTargets, 0);
    }
    return -1;
}

s32 Link_CheckScripted(u8 **arrivalOut, u8 **headingOut, RotationYaw *rotation) {
    u8 heading;

    heading = g_scriptedLinkHeadings[g_linkFromStage][g_linkFromIndex];
    if (Link_IsFacing(rotation, heading) != 0) {
        if (headingOut != 0) {
            *headingOut = g_linkHeadings + heading * 12;
        }
        if (arrivalOut != 0) {
            *arrivalOut = g_linkHeadings + g_scriptedArrivalHeadings[g_linkToStage][g_linkToIndex] * 12;
        }
        return 1;
    }
    return 0;
}

s32 Link_GetStepScript(void) {
    return g_scriptedLinkTargets[g_linkToStage][g_linkToIndex].stepScript;
}

s32 Link_Find(void *place, void *location, s32 stage, u8 *counts, s32 *lists, s32 *targets, s32 setNavFlag) {
    LinkEntry *entry;
    SpawnPoint *target;
    PlaceOut *out;
    s16 *key;
    s32 n;
    s32 i;
    s32 toStage;
    s32 toIndex;

    out = place;
    key = location;
    n = counts[stage];
    if (n != 0) {
        entry = (LinkEntry *)lists[stage];
        for (i = 0; i < n; i++, entry++) {
            if (key[0] == entry->chunkKey && (key[1] == entry->tileKey || entry->tileKey < 0)) {
                g_linkFromStage = stage;
                g_linkFromIndex = i;
                toStage = entry->toStage;
                g_linkToStage = toStage;
                toIndex = entry->toIndex;
                target = (SpawnPoint *)targets[toStage] + toIndex;
                g_linkToIndex = toIndex;
                out->tile = target->tile;
                out->offset = g_tileOffsets[target->offsetIndex];
                if (setNavFlag != 0) {
                    g_navFlags[target->navFlag] = 1;
                }
                return g_linkToStage;
            }
        }
    }
    return -1;
}

s32 Spawn_PickFromMood(void *place, s32 *secondsOut, void *point, s32 day) {
    s16 key[4];
    s32 idx;
    s32 cnt;
    s32 i;
    SpawnPoint *rec;
    PlaceOut *out;

    idx = Stage_FindChunkByMood(key, point);
    if (idx >= 0) {
        *secondsOut = g_stageTimeLimits[idx];
        cnt = g_spawnCounts[idx];
        rec = g_spawnPoints[idx];
        for (i = 0; i < cnt; i++, rec++) {
            if (key[0] == *(s16 *)rec) {
                goto found;
            }
        }
        rec = g_spawnPoints[idx] + key[0] % cnt;
found:
        out = place;
        out->tile = rec->tile;
        out->offset = g_tileOffsets[rec->offsetIndex];
        return idx;
    }
    idx = Spawn_PickRandom(place, idx, day);
    *secondsOut = g_stageTimeLimits[idx];
    return idx;
}

s32 Day_FindSpecial(void *cinematic, s32 dayNumber) {
    SpecialCine *o = cinematic;
    s32 i;

    for (i = 0; i < sizeof(g_specialDays) / sizeof(g_specialDays[0]); i++) {
        if (dayNumber == g_specialDays[i]) {
            o->variant = rand() % 6;
            o->category = i % 12;
            return (s32) &D_8008ABF4;
        }
    }
    return 0;
}

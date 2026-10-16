#include "common.h"
#include "game/dreamsys.h"
#include "game/scene.h"

extern void Object_DeleteArray(void *, s32);
u8 *g_navFlags;
s32 *g_dynamicLinkCount;
extern s32 D_8008ABF0[];
s32 g_linkToStage;
s32 g_linkFromStage;
typedef struct { u8 pad[5]; s8 u5; } S6;
extern S6 *g_scriptedLinkTargets[];
s32 g_linkToIndex;
typedef struct Unk_8005B5A4 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Unk_8005B5A4;
extern s16 g_stageTimeLimits[];
void Actor_ApplyPos(void *arg0, s32 arg1, s32 *arg2);
extern void Scenery_CreateSpriteParts(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void Place_CheckTextureLoad(void *, void *);
typedef struct { s32 u0; s32 u4; u8 pad[0x14]; s32 u1C; s32 u20; u8 pad2[0xC]; s32 u30; s32 u34; } S;
void HandlerNode_Stop(void *, void *);
s32 Mood_GetColor(s16 *arg0);
extern u8 g_staticLinkCounts[];
extern s32 g_staticLinkLists[];
extern s32 g_staticLinkTargets[];
s32 Link_Find(void *arg0, void *arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 arg6);
extern u8 g_facingLinkCounts[];
extern void *g_facingLinkLists[];
extern void *g_facingLinkTargets[];
s16 *Stage_GetChunkMood(s32 arg0, s8 *arg1);
extern u8 g_extraLinkCounts;
extern s32 g_extraLinkLists;
extern s32 g_extraLinkTargets;
s32 g_extraListOn;
extern u8 g_scriptedLinkCounts[];
extern s32 g_scriptedLinkLists[];
s32 Spawn_PickRandom(void *arg0, s32 arg1, s32 arg2);
s32 DreamSys_ExecuteLink();
extern u8 g_turnRotations[];
typedef struct Unk_8005AFDC_VtblB {
    u8 pad_00[0x10C];
    s32 (*unk10C)(void *, s32, s32);
} Unk_8005AFDC_VtblB;
typedef struct Unk_8005AFDC_B {
    Unk_8005AFDC_VtblB *vt;
} Unk_8005AFDC_B;
s32 Link_FindStatic(void *, void *, s32);
s32 Nav_CalcScore(void);
extern ScreenVtbl *MenuScreen_GetVtbl(void);
typedef struct Unk_80058A94_RetVt {
    u8 pad_00[0x8];
    void (*unk8)(void *);
    u8 pad_0C[0x50 - 0x0C];
    void (*unk50)(void *);
    u8 pad_54[0x9C - 0x54];
    void (*unk9C)(void *, s32 **, s32);
    u8 pad_A0[0xDC - 0xA0];
    void (*unkDC)(void *, s32 **, s32);
    void (*unkE0)(void *, s32 **, s32);
} Unk_80058A94_RetVt;
Unk_80058A94_RetVt *Actor_GetVtbl(void);
extern u16 g_linkHeadingYaws[];
typedef struct Unk_8005BE28 {
    u8 pad_00[4];
    u16 u4;
} Unk_8005BE28;
s32 g_saveMagic;
extern void Nav_InitFlags(u8 *arg0, s32 *arg1);
extern void *memset(void *arg0, s32 arg1, s32 arg2);
s32 Spawn_PickFromMood(void *arg0, s32 *arg1, void *arg2, s32 arg3);
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
void SceneNode_GetRotation(DreamSys *dreamSys, s32 *arg1);
s32 Link_FindFacing(void *arg0, s16 *arg1, s32 arg2);
s32 Link_CheckFacing(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2);
s32 Day_FindSpecial(void *arg0, s32 arg1);
extern s32 g_graphReelColor;
extern s32 rand(void);
extern s16 g_specialDays[42];
extern s32 D_8008ABF4;
typedef struct Unk_8005C438 {
    s16 unk0;
    s16 unk2;
} Unk_8005C438;
extern s32 HandlerNode_Start(s32, void *, s32, void *, s32);
extern s16 g_linkStep2Start[];
extern u8 g_yawPlus45[];
void DreamSys_MoveToTileOffset(DreamSys *, s16 *, s16 *);
extern u8 g_graphBoxSize[];
extern s32 g_graphNewestColor[];
void *Box_Create(s32 arg0, s32 arg1, s32 arg2);
/* A box color the graph steps down; signed bytes, as the code subtracts. */
typedef struct GraphColor {
    s8 r;
    s8 g;
    s8 b;
} GraphColor;
extern GraphColor g_graphOldColor;
typedef struct Unk_8005942C_Vec {
    s32 x;
    s32 y;
    s32 z;
} Unk_8005942C_Vec;
extern s32 g_pointAheadZ[];
extern void SceneNode_LocalToWorld(void *arg0, void *arg1, void *arg2, s32 arg3);
s32 Entity_IsWithinBox(s32 *arg0, s32 arg1, s32 *arg2);
s32 DreamSys_GetSightHeight(Unk_8005B5A4 *arg0, Unk_8005B5A4 *arg1, s32 arg2);
extern u8 g_linkHeadings[];
extern u8 *g_facingArrivalHeadings[];
extern u8 *g_facingLinkHeadings[];
s32 g_linkFromIndex;
s32 Link_IsFacing(Unk_8005BE28 *arg0, u8 arg1);
extern u8 *g_scriptedLinkHeadings[];
extern u8 *g_scriptedArrivalHeadings[];
extern s16 g_linkStep0Start[];
s32 g_fallPlace5;
typedef struct Unk_8005BE90 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
} Unk_8005BE90;
extern s32 g_pitchSteps[];
extern s32 g_pitchLimits[];
typedef struct Unk_800587F0_ArgVtbl {
    u8 pad_00[0x80];
    s32 (*unk80)(void *, s32);
} Unk_800587F0_ArgVtbl;
extern s8 g_stepSoundTones[];
extern s8 g_stepSoundOctaves[];
typedef struct Unk_80058968_ArgVtbl {
    u8 pad_00[0xE4];
    void (*unkE4)(void *, void *, void *, void *);
} Unk_80058968_ArgVtbl;
typedef struct Unk_80058968_RetVtbl {
    u8 pad_00[0x4C];
    void (*unk4C)(void *, void *, void *);
} Unk_80058968_RetVtbl;
extern s16 g_linkStep1Start[];
extern u8 g_yawMinus45[];
typedef struct Unk_80058B08_Ret {
    u8 pad_00[0x88];
    void (*unk88)(void *, s32);
} Unk_80058B08_Ret;
extern s16 g_linkStep3Start[];
typedef struct Unk_8001E6F8_Out {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Unk_8001E6F8_Out;
extern s32 g_lookBackSteps[];
extern s32 g_lookBackLimits[];
extern s16 g_turnRotationYaw[];
void DreamSys_ReverseDirection(DreamSys *dreamSys);
extern s32 g_graphVtbl[];
extern u8 g_dreamSysVtbl[];
extern s32 g_walkSpeeds[];
extern s8 g_walkSigns[];
extern void (*g_walkMoves[])(void *, s32, s32);
typedef struct Unk_8005B03C_ObjVtbl {
    u8 pad_00[0x38];
    void (*unk38)(void *, void *, s32);
    u8 pad_3C[0x14C - 0x3C];
    s32 (*unk14C)(void *);
    s32 (*unk150)(void *);
    s32 (*unk154)(void *);
    s32 (*unk158)(void *);
} Unk_8005B03C_ObjVtbl;
s32 Link_FindScripted(void *arg0, void *arg1, s32 arg2);
s32 Link_CheckScripted(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2);
s32 Link_GetStepScript(void);
extern s32 (*g_linkSteps[])(void *);
typedef struct { u8 r, g, b, cd; } Unk_8005C150_C;
typedef struct { Unk_8005C150_C c; s16 v; } Unk_8005C150_E;
typedef struct { Unk_8005C150_C c; u8 idx; s8 flag; } Unk_8005C150_Y;
typedef struct { s16 a; s16 b; s8 c; u8 d; } Unk_8005C150_T;
typedef struct { Unk_8005C150_C a; Unk_8005C150_E b; } Unk_8005C150;
extern Unk_8005C150_E g_tileOffsets[];
s32 Link_FindExtra(void *arg0, void *arg1, s32 arg2);
s32 Link_GetExtraSeconds(void);
extern Unk_8005C150_Y *g_spawnPoints[];
extern u8 g_spawnCounts[];
s32 rand();
u32 Stage_FindChunkByMood(void *arg0, void *arg1);
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

void *DreamSys_New(s32 arg0, s32 arg1, s32 arg2) {
    void *dreamSys;

    dreamSys = Heap_Alloc(0x928);
    if (dreamSys != 0) {
        DreamSys_GetVtable()->init(dreamSys, arg0, arg1, arg2);
        return dreamSys;
    }
    return 0;
}

void DreamSys_Init(DreamSys *dreamSys, void **arg1, s32 arg2, s32 camera) {
    Actor_GetVtbl()->unk8(dreamSys);
    dreamSys->vtbl = (DreamSysVtbl *)DreamSys_GetVtable();
    dreamSys->soundBank = arg2;
    dreamSys->camera.obj = camera;
    dreamSys->unk64 = 0;
    dreamSys->unk60 = arg1;
    dreamSys->vtbl->watch(dreamSys, ((Unk_800587F0_ArgVtbl *)*arg1)->unk80(arg1, 0));
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

void DreamSys_EnterMap(DreamSys *dreamSys, void **arg1) {
    s32 sp10[4];
    Flashback *elem;
    void *temp_a2;

    ((Unk_80058968_ArgVtbl *)*arg1)->unkE4(arg1, sp10, dreamSys, (u8 *)dreamSys + 0x16C);
    ((Unk_80058968_RetVtbl *)Actor_GetVtbl())->unk4C(dreamSys, arg1, sp10);
    dreamSys->vtbl->watch(dreamSys, arg1);
    if (dreamSys->transition == 0xE) {
        elem = &dreamSys->save.flashbacks[dreamSys->nextFlashback];
        dreamSys->vtbl->unk44(dreamSys, 1, elem->rotation.bytes);
        dreamSys->vtbl->swapTimeLimit(dreamSys, elem->length + 4);
        dreamSys->nextFlashback++;
    }
    if (dreamSys->unk6C != 0) {
        temp_a2 = dreamSys->unk888;
        if (temp_a2 != 0) {
            dreamSys->vtbl->unk44(dreamSys, 1, temp_a2);
        }
    }
}

void DreamSys_LeaveMap(DreamSys *dreamSys) {
    DreamPlayer *player;

    player = dreamSys->player;
    player->vt->unkF0(player);
    dreamSys->vtbl->unwatch(dreamSys, dreamSys->player);
    Actor_GetVtbl()->unk50(dreamSys);
}

void DreamSys_OnGroundProbe(DreamSys *dreamSys, s32 arg1) {
    s32 temp_v0;
    DreamPlayer *player;
    DreamPlayer *player2;

    ((Unk_80058B08_Ret *)Actor_GetVtbl())->unk88(dreamSys, arg1);
    switch (arg1) {
    case -1:
        temp_v0 = dreamSys->unk28->unk36 & 0x7F;
        dreamSys->unkB8 = temp_v0;
        if (temp_v0 >= 0x18) {
            dreamSys->unkB8 = 0;
        }
        if (dreamSys->transition == 0xF && dreamSys->unkB8 == 0) {
            dreamSys->unkB8 = 2;
        }
        if (dreamSys->stage == 9) {
            player = dreamSys->player;
            dreamSys->vtbl->unk1D4(dreamSys, player->vt->unk10C(player, 0, 0));
        }
        return;
    case -2:
        player2 = dreamSys->player;
        if (player2->vt->unk11C(player2, dreamSys->pos.bytes + 0x18)->unk4->unk2C == 2) {
            player = dreamSys->player;
            dreamSys->vtbl->unk1D4(dreamSys, player->vt->unk10C(player, 0, 0));
        } else {
            dreamSys->vtbl->unk224(dreamSys);
        }
        return;
    }
}

void DreamSys_OnPad(DreamSys *dreamSys, s32 arg1, s32 arg2) {
    if (dreamSys->unk6C == 0 && dreamSys->unk70 == 0) {
        arg2 -= 2;
        if (dreamSys->unk908 == 0) {
            switch (arg2) {
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
                    dreamSys->vtbl->unk188(dreamSys, arg1, arg2);
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
    Actor_GetVtbl()->unk9C(dreamSys, sender, message);
    if ((**sender & 0xFFF) == 0x114) {
        dreamSys->vtbl->unk1E4(dreamSys, sender, message);
    }
}

void DreamSys_RouteEntityMessage(DreamSys *dreamSys, s32 **sender, s32 message) {
    Actor_GetVtbl()->unkDC(dreamSys, sender, message);
    if ((**sender & 0xFFFFF) == 0x1F234) {
        dreamSys->vtbl->onEntityEvent(dreamSys, sender, message);
    }
}

void DreamSys_OnWallTouch(DreamSys *dreamSys, s32 **sender, s32 message) {
    DreamPlayer *player;
    StagePlace *src;

    Actor_GetVtbl()->unkE0(dreamSys, sender, message);
    if (message == 4 && dreamSys->transition == 0) {
        player = dreamSys->player;
        src = player->vt->unkD4(player, sender);
        dreamSys->place = *src;
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

void DreamSys_SetAutoWalk(DreamSys *dreamSys, s32 arg1) {
    s32 temp_a2;

    dreamSys->unk6C = arg1;
    if (arg1 != 0) {
        dreamSys->vtbl->unk180(dreamSys, 1);
        temp_a2 = dreamSys->unk884;
        if (temp_a2 != 0) {
            dreamSys->vtbl->unk44(dreamSys, 1, temp_a2);
        }
    }
}

void DreamSys_StartPlace(DreamSys *dreamSys, s32 arg1, s32 arg2) {
    Unk_8001E6F8_Out sp18;

    dreamSys->vtbl->logChunkMood(dreamSys, &dreamSys->place);
    dreamSys->vtbl->unk138(dreamSys, 1);
    dreamSys->vtbl->unk13C(dreamSys, 1);
    dreamSys->vtbl->unk180(dreamSys, arg1);
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
    dreamSys->vtbl->unk190(dreamSys, arg2);
    dreamSys->cinematic.id.variant = -1;
    dreamSys->unk70 = 0;
    dreamSys->transition = 0;
    dreamSys->unk74 = 0;
    dreamSys->unk908 = 0;
    dreamSys->unk90C = 0;
    dreamSys->linkStep = 0;
    dreamSys->unk78 = 0;
    SceneNode_GetRotation(dreamSys, (s32 *)&sp18);
    sp18.unk8 = 0;
    sp18.unkA = 1;
    dreamSys->vtbl->unk44(dreamSys, 1, &sp18);
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

s32 DreamSys_TestPointAhead(DreamSys *dreamSys, Unk_8005942C_Vec *arg1, s32 arg2, s32 *arg3, s32 arg4) {
    Unk_8005942C_Vec sp10;
    s32 temp_v0;
    s32 *temp;

    g_pointAheadZ[0] = arg2;
    SceneNode_LocalToWorld(dreamSys, &sp10, &g_pointAheadZ[-2], 0);
    temp_v0 = DreamSys_GetSightHeight((Unk_8005B5A4 *)(dreamSys->camera.bytes + 0x14), (Unk_8005B5A4 *)(dreamSys->camera.bytes + 0x20), arg2);
    if (dreamSys->unkC != 0) {
        temp = (s32 *)(dreamSys->pos.bytes + 0x38);
    } else {
        temp = NULL;
    }
    sp10.y = temp_v0 + temp[1];
    if (arg1 != NULL) {
        *arg1 = sp10;
    }
    if (arg3 != NULL) {
        return Entity_IsWithinBox((s32 *)&sp10, arg4, arg3);
    }
    return 0;
}

s32 DreamSys_GetSightHeight(Unk_8005B5A4 *start, Unk_8005B5A4 *end, s32 pos) {
    s32 span;

    pos /= 1024;
    span = (end->unk8 - start->unk8) / 1024;
    if (span == 0) {
        span = 1;
    }
    return ((end->unk4 - start->unk4) * pos) / span + start->unk4;
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

void DreamSys_StopControls(DreamSys *dreamSys, s32 arg1) {
    dreamSys->vtbl->unk13C(dreamSys, 0);
    if (arg1 != 0) {
        dreamSys->vtbl->unk138(dreamSys, 0);
    }
}

void DreamSys_SetControls(DreamSys *dreamSys, s32 arg1, s32 arg2) {
    dreamSys->vtbl->unk13C(dreamSys);
    dreamSys->vtbl->unk138(dreamSys, arg2);
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
        DreamSysVtbl *temp_v1;

        handler = vt->unk178;
        temp_v1 = dreamSys->vtbl;
        dreamSys->unkC4 = 1;
        dreamSys->unkC8 = 1;
        dreamSys->unk98 = handler;
        HandlerNode_Start(dreamSys->soundBank, dreamSys->unkCC.bytes, 1, dreamSys, temp_v1->unk194);
        return;
    }
    }
}

void DreamSys_TickLook(DreamSys *dreamSys) {
    dreamSys->vtbl->unk144(dreamSys);
    dreamSys->vtbl->unk148(dreamSys);
}

void DreamSys_TickPitch(DreamSys *dreamSys) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1_3;
    DreamCamera *camera2;
    DreamCamera *camera;
    s32 temp_v1;

    temp_v1 = dreamSys->unk88;
    if (temp_v1 != 0) {
        temp_a2 = g_pitchSteps[temp_v1];
        temp_v1_3 = g_pitchLimits[temp_v1];
        temp_a1 = temp_a2 + dreamSys->unk8C;
        if ((temp_a1 < 0 ? ~temp_a1 + 1 : temp_a1) < temp_v1_3) {
            camera = dreamSys->camera.obj;
            camera->unk24 = (u32) (temp_a2 + camera->unk24);
            dreamSys->unk8C = temp_a1;
        }
        dreamSys->unk88 = 0;
        return;
    }
    temp_v0 = dreamSys->unk8C;
    if (temp_v0 != 0) {
        temp_a2 = -0x258;
        if (temp_v0 < 0) {
            temp_a2 = 0x258;
        }
        camera2 = dreamSys->camera.obj;
        camera2->unk24 = (u32) (temp_a2 + camera2->unk24);
        dreamSys->unk8C = (s32) (temp_a2 + dreamSys->unk8C);
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
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = dreamSys->unkA0;
    dreamSys->unkA8 = 0;
    if (temp_v1 != 0) {
        if (temp_v1 & 1) {
            var_v0 = temp_v1 + 1;
        } else {
            var_v0 = temp_v1 - 1;
        }
        dreamSys->unkA0 = var_v0;
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

s32 DreamSys_TickStep(DreamSys *dreamSys, void *arg1) {
    s32 var_s1 = 0;
    s32 var_s3;
    s32 temp_a0;
    s32 bit;
    s32 step;
    DreamCamera *camera = arg1;

    var_s3 = 0;
    if (dreamSys->unkA0 != 0) {
        var_s3 = dreamSys->unkA0;
        temp_a0 = dreamSys->unkB4 + 1;
        dreamSys->unkB4 = temp_a0;
        if (temp_a0 < 4) {
            if (dreamSys->unkAC == 4) {
                bit = temp_a0 & 1;
                var_s1 = bit == 0;
            }
        } else {
            dreamSys->unkA0 = 0;
            var_s1 = 1;
        }
        if (var_s1 != 0) {
            dreamSys->vtbl->unk168(dreamSys);
        }
        camera = dreamSys->camera.obj;
        if (camera != 0 && dreamSys->save.shake != 0 && arg1 != 0) {
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
    if (var_s1 == 0) {
        dreamSys->vtbl->unk16C(dreamSys, camera);
    }
    return var_s3;
}

void DreamSys_PlayStepSound(DreamSys *dreamSys) {
    SoundBank *obj = dreamSys->soundBank;
    s32 idx = dreamSys->unkB8;
    SoundBankVtbl *vt = obj->vtbl;
    s32 t;

    if (idx != 0) {
        t = g_stepSoundTones[idx] * 0x10;
        vt->setOctave(obj, g_stepSoundOctaves[idx]);
        dreamSys->unkBC = vt->playTone(obj, t, 0x6E, 0x6E);
        if (dreamSys->unkB8 != 0x16) {
            dreamSys->unkBC = -1;
        }
        if (dreamSys->unkB8 == 0xB) {
            vt->setOctave(obj, 1);
            vt->playTone(obj, t, 0x6E, 0x6E);
            vt->setOctave(obj, 2);
            vt->playTone(obj, 0x90, 0x6E, 0x6E);
        }
    }
}

void DreamSys_StopStepSound(DreamSys *dreamSys) {
    s32 temp_a1;
    SoundBank *temp_a0;

    temp_a1 = dreamSys->unkBC;
    if (temp_a1 >= 0) {
        temp_a0 = dreamSys->soundBank;
        temp_a0->vtbl->stopVoice(temp_a0, temp_a1);
        dreamSys->unkBC = -1;
    }
}

void DreamSys_Walk(DreamSys *dreamSys, s32 arg1) {
    s32 temp_s3;
    s32 place;
    DreamPlayer *player;
    Coord2 *body;

    if (arg1 != 0) {
        temp_s3 = g_walkSigns[arg1] * g_walkSpeeds[dreamSys->unkAC];
        dreamSys->vtbl->unk12C(dreamSys);
        player = dreamSys->player;
        place = player->vt->unk10C(player, 0, 0);
        if (dreamSys->vtbl->unk1DC(dreamSys, place) == 0 && dreamSys->vtbl->unk1D8(dreamSys, place) == 0 && dreamSys->vtbl->unk1D0(dreamSys, place) == 0) {
            dreamSys->vtbl->unk220(dreamSys);
            g_walkMoves[arg1](dreamSys, temp_s3, dreamSys->unk90C == 0);
            if (dreamSys->stage == 0) {
                body = dreamSys->pos.coord;
                if (body->coord.t.y < -0x7D0 && body->coord.t.x >= -0x1F3) {
                    dreamSys->vtbl->onWallTouch(dreamSys, dreamSys, 4);
                }
            }
        }
        dreamSys->pos.coord->flg = 0;
    }
}

void DreamSys_TickTurn(DreamSys *dreamSys) {
    s32 temp_v0;

    temp_v0 = dreamSys->unkA4;
    if (temp_v0 != 0) {
        dreamSys->vtbl->unk44(dreamSys, 0, g_turnRotations + temp_v0 * 12);
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

void DreamSys_EndFall(DreamSys *dreamSys, s32 arg1) {
    dreamSys->unkC4 = 0;
    dreamSys->unkC8 = arg1;
    if (arg1 != 0) {
        HandlerNode_Stop(dreamSys->soundBank, dreamSys->unkCC.bytes);
    }
}

s32 DreamSys_SwapSpeed(DreamSys *dreamSys, s32 arg1) {
    s32 temp_v0;

    temp_v0 = dreamSys->unkAC;
    if (arg1 >= 0) {
        dreamSys->unkAC = arg1;
        dreamSys->unkB0 = arg1;
    }
    return temp_v0;
}

void DreamSys_PushSpeed(DreamSys *dreamSys, s32 arg1) {
    s32 temp_v0;

    temp_v0 = dreamSys->unkAC;
    if (temp_v0 != arg1) {
        dreamSys->unkB0 = temp_v0;
        dreamSys->unkAC = arg1;
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

void DreamSys_SetLinkPeriod(DreamSys *dreamSys, s32 arg1) {
    dreamSys->unk120 = arg1;
}

void DreamSys_FallSoundHandler(s32 arg0, S *arg1) {
    s32 r;
    if (arg1->u0 == 1) {
        r = arg1->u4 % 20; if (r == 0) {
            arg1->u1C = 9;
            arg1->u20 = -1;
        } else {
            arg1->u30 = 9;
            arg1->u34 = -1;
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
    s32 temp;

    dreamSys->nextFlashback = 0;
    dreamSys->timer = 0;
    dreamSys->savedDay = dreamSys->save.day;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->vtbl->loadNextFlashback(dreamSys, 1);
        return dreamSys->stage;
    }
    temp = Day_FindSpecial(dreamSys->cinematic.bytes, dreamSys->save.day + 1);
    dreamSys->vtbl->resetMoodAccumulators(dreamSys, temp);
    if (temp == 0) {
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

s32 DreamSys_LoadNextFlashback(DreamSys *dreamSys, s32 arg1) {
    Flashback *elem;
    s32 idx;

    idx = dreamSys->nextFlashback;
    if (idx < dreamSys->save.flashbackCount) {
        dreamSys->transition = 0xE;
        elem = &dreamSys->save.flashbacks[idx];
        if (arg1 == 0) {
            dreamSys->vtbl->unk30(dreamSys, 0xE);
        }
        dreamSys->save.day = elem->day;
        dreamSys->stage = elem->stage;
        dreamSys->place = elem->place;
        return 1;
    }
    return 0;
}

s32 DreamSys_LinkFacing(DreamSys *dreamSys, s16 *arg1) {
    s32 sp10[4];
    s32 temp;

    if (dreamSys->transition != 0) {
        return 0;
    }
    temp = Link_FindFacing(&dreamSys->place, arg1, dreamSys->stage);
    if (temp < 0) {
        return 0;
    }
    SceneNode_GetRotation(dreamSys, sp10);
    if (Link_CheckFacing(&dreamSys->unk888, &dreamSys->unk884, sp10) == 0) {
        return 0;
    }
    if (dreamSys->unkA8 == 0) {
        return 0;
    }
    DreamSys_ExecuteLink(dreamSys, temp, 0xF, 0);
    return 1;
}

s32 DreamSys_LinkFall(DreamSys *dreamSys, s32 arg1) {
    s32 newStage;

    if (dreamSys->transition == 0) {
        newStage = Link_PickFallStage(&dreamSys->place, dreamSys->stage, arg1, dreamSys->timer);
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

s32 DreamSys_LinkExtra(DreamSys *dreamSys, void *arg1) {
    s32 sp10[4];
    s32 bonusSeconds;
    s32 newStage;

    newStage = Link_FindExtra(&dreamSys->place, arg1, dreamSys->stage);
    if (newStage >= 0) {
        bonusSeconds = Link_GetExtraSeconds();
        if (DreamSys_ExecuteLink(dreamSys, newStage, 0x11, 0) != 0) {
            dreamSys->transition = 0;
            dreamSys->player->vt->unkE8(dreamSys->player, sp10, &dreamSys->place);
            dreamSys->vtbl->setPosition(dreamSys, sp10);
            if (bonusSeconds != 0 && dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->swapTimeLimit(dreamSys, dreamSys->vtbl->getElapsedSeconds(dreamSys) + bonusSeconds);
            }
        }
        return 1;
    }
    return 0;
}

s32 DreamSys_ExecuteLink(DreamSys *dreamSys, s32 newStage, s32 transition, s32 arg3) {
    dreamSys->transition = transition;
    dreamSys->vtbl->unk30(dreamSys, transition);
    if (dreamSys->transition == 0) {
        return 0;
    }
    dreamSys->stage = newStage;
    if (dreamSys->flashbackMode != 0) {
        dreamSys->timer = 0;
    }
    if (arg3 != 0) {
        SoundBank *obj = dreamSys->soundBank;
        obj->vtbl->playTone(obj, 0x90, 0x6E, 0x6E);
    }
    return 1;
}

s32 DreamSys_StartLinkStep(DreamSys *dreamSys, StagePlace *target) {
    s32 sp10[4];

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
            SceneNode_GetRotation(dreamSys, sp10);
            if (Link_CheckScripted((u8 **)&dreamSys->unk888, (u8 **)&dreamSys->unk884, (Unk_8005BE28 *)sp10) != 0 && dreamSys->unkA8 != 0) {
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
    s32 temp_v1;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep0Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->unkAC != 4) {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x85) {
            return 1;
        }
        if ((temp_v1 >= 0x2B && temp_v1 < 0x3A) || (temp_v1 >= 0x4B && temp_v1 < 0x5A)) {
            dreamSys->unkA4 = 2;
        }
    } else {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x13) {
            return 1;
        }
        if ((temp_v1 >= 8 && temp_v1 < 0xA) || (temp_v1 >= 0xD && temp_v1 < 0xF)) {
            dreamSys->vtbl->unk44(dreamSys, 0, g_yawPlus45);
        }
    }
    dreamSys->unkA0 = 1;
    dreamSys->linkStepTick++;
    return 0;
}

s32 DreamSys_LinkStep1(DreamSys *dreamSys) {
    s32 flag;

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
        flag = (u32)(dreamSys->linkStepTick - 0x39) < 0x35;
    } else {
        if (dreamSys->linkStepTick >= 0x19) {
            return 1;
        }
        if ((u32)(dreamSys->linkStepTick - 6) < 2 || (u32)(dreamSys->linkStepTick - 0xB) < 2 || (u32)(dreamSys->linkStepTick - 0x14) < 2) {
            dreamSys->vtbl->unk44(dreamSys, 0, g_yawMinus45);
        }
        flag = (u32)(dreamSys->linkStepTick - 3) < 0xE;
    }
    if (flag) {
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
    s32 temp_v1;
    s32 var;

    if (dreamSys->linkStepTick == 0) {
        DreamSys_MoveToTileOffset(dreamSys, g_linkStep3Start, &dreamSys->linkTarget.x);
    }
    if (dreamSys->unkAC != 4) {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x71) {
            return 1;
        }
        if ((u32)(temp_v1 - 0x1E) < 0xF || (u32)(temp_v1 - 0x52) < 0xF) {
            dreamSys->unkA4 = 1;
        }
        var = (u32)(dreamSys->linkStepTick - 0x1E) < 0x34;
    } else {
        temp_v1 = dreamSys->linkStepTick;
        if (temp_v1 >= 0x13) {
            return 1;
        }
        if ((u32)(temp_v1 - 6) < 2 || (u32)(temp_v1 - 0xF) < 2) {
            dreamSys->vtbl->unk44(dreamSys, 0, g_yawMinus45);
        }
        var = (u32)dreamSys->linkStepTick < 9;
    }
    if (var) {
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

void DreamSys_OnMapMessage(DreamSys *dreamSys, Unk_8005AFDC_B *sender, s32 message) {
    if (message == 5) {
        dreamSys->vtbl->logChunkMood(dreamSys, sender->vt->unk10C(sender, 0, 0));
    }
}

void DreamSys_OnEntityEvent(DreamSys *dreamSys, Unk_8005B03C_ObjVtbl **entity, s32 message) {
    s32 oldStage;

    if (dreamSys->transition == 0) {
        switch (message) {
        case 4:
            (*entity)->unk38(entity, dreamSys, message);
            return;
        case 9:
            if (dreamSys->flashbackMode == 0) {
                dreamSys->vtbl->logEntityMood(dreamSys, (*entity)->unk14C(entity));
                dreamSys->save.instanceScore = (*entity)->unk150(entity) + dreamSys->save.instanceScore;
                dreamSys->vtbl->maybeSaveFlashback(dreamSys, 0, 0x10);
                return;
            }
            break;
        case 10:
            oldStage = dreamSys->stage;
            dreamSys->stage = -(*entity)->unk154(entity);
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
                dreamSys->cinematic.id.variant = (*entity)->unk158(entity);
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
    s32 temp;

    dreamSys->save.navScore = Nav_CalcScore();
    temp = dreamSys->save.instanceScore;
    if (temp < 0) {
        dreamSys->save.instanceScore = 0;
    } else if (temp > 0x02FAF080) {
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
    s32 place;
    DreamPlayer *player;

    if (dreamSys->player != NULL) {
        if (rand() % 3 == 0) {
            player = dreamSys->player;
            place = player->vt->unk10C(player, 0, 0);
            SceneNode_GetRotation(dreamSys, rotation);
            dreamSys->vtbl->addFlashback(dreamSys, dreamSys->stage, place, rotation, arg1, length, dreamSys->save.day);
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
    s32 temp;

    if (value < 0) {
        return dreamSys->unk924;
    }
    temp = dreamSys->unk924;
    dreamSys->unk924 = value;
    return temp;
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

s32 Spawn_PickRandom(void *place, s32 stage, s32 arg2) {
    s32 newStage;
    s32 n;
    Unk_8005C150 *out;
    Unk_8005C150_Y *rec;

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
    rec = (Unk_8005C150_Y *)((s32)g_spawnPoints[newStage] + (rand() % g_spawnCounts[newStage]) * 6);
    out = place;
    out->a = rec->c;
    out->b = g_tileOffsets[rec->idx];
    *g_dynamicLinkCount += 1;
    return newStage;
}

s32 Link_FindStatic(void *arg0, void *arg1, s32 arg2) {
    return Link_Find(arg0, arg1, arg2, g_staticLinkCounts, g_staticLinkLists, g_staticLinkTargets, 1);
}

s32 Link_FindFacing(void *arg0, s16 *arg1, s32 arg2) {
    return Link_Find(arg0, arg1, arg2, g_facingLinkCounts, g_facingLinkLists, g_facingLinkTargets, 1);
}

s32 Link_CheckFacing(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2) {
    u8 temp;

    temp = g_facingLinkHeadings[g_linkFromStage][g_linkFromIndex];
    if (Link_IsFacing(arg2, temp) != 0) {
        if (arg1 != NULL) {
            *arg1 = g_linkHeadings + temp * 12;
        }
        if (arg0 != NULL) {
            *arg0 = g_linkHeadings + g_facingArrivalHeadings[g_linkToStage][g_linkToIndex] * 12;
        }
        return 1;
    }
    return 0;
}

s32 Link_IsFacing(Unk_8005BE28 *arg0, u8 arg1) {
    s32 diff = arg0->u4 - g_linkHeadingYaws[arg1 * 6];
    s16 temp = diff;
    s16 var_a1;

    var_a1 = diff;
    if (temp > 0xB4) {
        var_a1 -= 0x168;
    } else if (temp < -0xB4) {
        var_a1 += 0x168;
    }
    return (u16)(var_a1 + 0x2C) < 0x59U;
}

s32 Link_PickFallStage(void *arg0, s32 arg1, Unk_8005BE90 *arg2, s32 arg3) {
    s32 ret;

    if (arg1 != 3 && arg1 != 1 && arg1 != 5 && arg1 != 9 && arg1 != 12) {
        return -1;
    }
    if (arg1 == 5) {
        if (arg2->unk6 >= -0xFFF && arg2->unk0 != g_fallPlace5) {
            return -1;
        }
    } else if (arg1 == 9) {
        if (arg2->unk6 < 0x800) {
            return -1;
        }
    }
    if (arg3 & 1) {
        arg1 = -12;
    }
    ret = Spawn_PickRandom(arg0, arg1, arg3);
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

void Link_SetExtraListOn(s32 arg0) {
    g_extraListOn = arg0;
}

s32 Link_FindExtra(void *arg0, void *arg1, s32 arg2) {
    if (g_extraListOn != 0) {
        return Link_Find(arg0, arg1, arg2, &g_extraLinkCounts, &g_extraLinkLists, &g_extraLinkTargets, 0);
    }
    return -1;
}

s32 Link_GetExtraSeconds(void) {
    return g_linkFromStage == 0 ? 10 : 0;
}

s32 Link_FindScripted(void *arg0, void *arg1, s32 arg2) {
    if (arg2 == 0) {
        return Link_Find(arg0, arg1, 0, g_scriptedLinkCounts, g_scriptedLinkLists, (s32 *)g_scriptedLinkTargets, 0);
    }
    return -1;
}

s32 Link_CheckScripted(u8 **arg0, u8 **arg1, Unk_8005BE28 *arg2) {
    u8 temp_s0;

    temp_s0 = g_scriptedLinkHeadings[g_linkFromStage][g_linkFromIndex];
    if (Link_IsFacing(arg2, temp_s0) != 0) {
        if (arg1 != 0) {
            *arg1 = g_linkHeadings + temp_s0 * 12;
        }
        if (arg0 != 0) {
            *arg0 = g_linkHeadings + g_scriptedArrivalHeadings[g_linkToStage][g_linkToIndex] * 12;
        }
        return 1;
    }
    return 0;
}

s32 Link_GetStepScript(void) {
    return g_scriptedLinkTargets[g_linkToStage][g_linkToIndex].u5;
}

s32 Link_Find(void *arg0, void *arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 arg6) {
    Unk_8005C150_T *t0;
    Unk_8005C150_Y *y;
    Unk_8005C150 *o;
    s16 *a1;
    s32 n;
    s32 i;
    s32 c;
    s32 d;

    o = arg0;
    a1 = arg1;
    n = arg3[arg2];
    if (n != 0) {
        t0 = (Unk_8005C150_T *)arg4[arg2];
        for (i = 0; i < n; i++, t0++) {
            if (a1[0] == t0->a && (a1[1] == t0->b || t0->b < 0)) {
                g_linkFromStage = arg2;
                g_linkFromIndex = i;
                c = t0->c;
                g_linkToStage = c;
                d = t0->d;
                y = (Unk_8005C150_Y *)arg5[c] + d;
                g_linkToIndex = d;
                o->a = y->c;
                o->b = g_tileOffsets[y->idx];
                if (arg6 != 0) {
                    g_navFlags[y->flag] = 1;
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
    Unk_8005C150_Y *rec;
    Unk_8005C150 *out;

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
        out->a = rec->c;
        out->b = g_tileOffsets[rec->idx];
        return idx;
    }
    idx = Spawn_PickRandom(place, idx, day);
    *secondsOut = g_stageTimeLimits[idx];
    return idx;
}

s32 Day_FindSpecial(void *cinematic, s32 dayNumber) {
    Unk_8005C438 *o = cinematic;
    s32 i;

    for (i = 0; i < sizeof(g_specialDays) / sizeof(g_specialDays[0]); i++) {
        if (dayNumber == g_specialDays[i]) {
            o->unk2 = rand() % 6;
            o->unk0 = i % 12;
            return (s32) &D_8008ABF4;
        }
    }
    return 0;
}

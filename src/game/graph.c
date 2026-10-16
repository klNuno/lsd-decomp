#include "common.h"
#include "game/dreamsys.h"
#include "game/scene.h"
#include "game/sound.h"
#include "game/graph.h"
#include "game/heap.h"
#include "game/menu_screen.h"
#include "game/box.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/*
 * The graph screen (vtable g_graphVtbl, class word 0x2F130, 0x244 bytes, made by Graph_New): a
 * MenuScreen (scene.h) whose menu slots draw the mood chart instead of items, one 10 x 10 box per
 * day for the last 100 days of the save block, and that spots the secret reel (docs/discoveries.md,
 * the secret video reel).
 */
typedef struct Graph {
    MenuScreen screen;      /* 0x000 vtbl is g_graphVtbl */
    DreamSys *dreamSys;     /* 0x0A4 Graph_Init's argument: the save block comes from it */
    Widget *boxes[100];     /* 0x0A8 Box_Create boxes: [0] the newest day, then older and older days */
    s32 reelFound;          /* 0x238 Graph_CheckReel: the four reel points are on the chart */
    u32 reelShown;          /* 0x23C reel points painted green so far */
    s8 *reelDays;           /* 0x240 4 bytes: for each reel point, how many days back it was found */
} Graph;

/* g_graphVtbl: the MenuScreen slots (ScreenVtbl, slot 0x40 is Graph_LoadImage), plus one of its own. */
typedef struct GraphVtbl {
    u8 pad_00[0x08];
    void (*init)(void *, s32);       /* 0x008 Graph_Init */
    u8 pad_0C[0x124 - 0x0C];
    void (*blinkReel)(Graph *graph); /* 0x124 Graph_BlinkReel */
} GraphVtbl;

static GraphVtbl *Graph_GetVtable(void);

/* Allocate the graph object (0x244 bytes) and construct it with Graph_GetVtable's slot 0x08. */
void *Graph_New(s32 dreamSys) {
    void *graph;

    graph = Heap_Alloc(0x244);
    if (graph != 0) {
        Graph_GetVtable()->init(graph, dreamSys);
        return graph;
    }
    return 0;
}

/* Graph_New's init (slot 0x08 of the graph vtable): the MenuScreen init with the sound file ETC\\ETCSE,
 * the graph vtable, then the graph's slots 0xD8 (setMenu) and 0x40 (Graph_LoadImage). */
void Graph_Init(Graph *graph, DreamSys *dreamSys) {
    MenuScreen_GetVtbl()->init(graph, 0, "ETC\\ETCSE", 0);
    graph->screen.vtbl = Graph_GetVtable();
    graph->screen.sound->vtbl->setOctave(graph->screen.sound, -1);
    graph->dreamSys = dreamSys;
    graph->screen.vtbl->setMenu(graph, 0);
    graph->screen.vtbl->reset(graph, dreamSys);
}
extern s32 g_graphReelColor;
extern u8 g_graphBoxSize[];
extern s32 g_graphNewestColor[];
/* A box color the graph steps down; signed bytes, as the code subtracts. */
typedef struct GraphColor {
    s8 r;
    s8 g;
    s8 b;
} GraphColor;
extern GraphColor g_graphOldColor;
extern GraphVtbl g_graphVtbl[];

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

static s32 Graph_CheckReel(Graph *graph, void *saveBlock);
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
static s32 Graph_CheckReel(Graph *graph, void *saveBlock) {
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

static GraphVtbl *Graph_GetVtable(void) {
    return g_graphVtbl;
}

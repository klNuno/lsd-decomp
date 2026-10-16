#include "common.h"

typedef struct Graph Graph;

/* The MenuScreen vtable: only the init slot (0x08) is used here. */
typedef struct MenuScreenVtbl {
    u8 pad_00[0x8];
    void (*init)(Graph *, s32, char *, s32); /* 0x08 MenuScreen_Init (defined in src/game/8003B854.c) */
} MenuScreenVtbl;

/* The graph vtable (g_graphVtbl): slot 0x40 is Graph_LoadImage (src/game/80058078.c). */
typedef struct GraphVtbl {
    u8 pad_00[0x40];
    void (*loadImage)(Graph *, s32);         /* 0x40 */
    u8 pad_44[0xD8 - 0x44];
    void (*unk_D8)(Graph *, s32);            /* 0xD8 */
} GraphVtbl;

/* The child object at 0x48 of a graph: only its vtable and slot 0x9C are used here. */
typedef struct GraphChildVtbl {
    u8 pad_00[0x9C];
    void (*unk_9C)(struct GraphChild *, s32); /* 0x9C called with -1 */
} GraphChildVtbl;

typedef struct GraphChild {
    GraphChildVtbl *vtbl;
} GraphChild;

/* The graph screen (the mood chart): the vtable at 0x00, the fields from 0x04 to 0x48 are not named here, the child at 0x48. */
struct Graph {
    GraphVtbl *vtbl;
    u8 pad_04[0x44];
    GraphChild *unk_48;
    u8 pad_4C[0xA4 - 0x4C];
    s32 unk_A4;                              /* 0xA4 the value given to Graph_Init, passed to slot 0x40 */
};

extern MenuScreenVtbl *MenuScreen_GetVtbl(void);
extern GraphVtbl *Graph_GetVtable(void);

/* Graph_New's init (slot 0x08 of the graph vtable): the MenuScreen init with the sound file ETC\\ETCSE,
 * the graph vtable, the child's slot 0x9C, then the graph's slots 0xD8 and 0x40. */
void Graph_Init(Graph *graph, s32 value) {
    MenuScreen_GetVtbl()->init(graph, 0, "ETC\\ETCSE", 0);
    graph->vtbl = Graph_GetVtable();
    graph->unk_48->vtbl->unk_9C(graph->unk_48, -1);
    graph->unk_A4 = value;
    graph->vtbl->unk_D8(graph, 0);
    graph->vtbl->loadImage(graph, value);
}

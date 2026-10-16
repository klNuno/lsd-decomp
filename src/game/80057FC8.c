#include "common.h"
#include "game/scene.h"
#include "game/sound.h"

typedef struct Graph Graph;

/* The graph vtable (g_graphVtbl): slot 0x40 is Graph_LoadImage (src/game/80058078.c). */
typedef struct GraphVtbl {
    u8 pad_00[0x40];
    void (*loadImage)(Graph *, s32);         /* 0x40 */
    u8 pad_44[0xD8 - 0x44];
    void (*unk_D8)(Graph *, s32);            /* 0xD8 */
} GraphVtbl;

/* The graph screen (the mood chart): the vtable at 0x00, a MenuScreen (scene.h) whose sound bank at 0x48 is used here. */
struct Graph {
    GraphVtbl *vtbl;
    u8 pad_04[0x44];
    SoundBank *sound;    /* 0x48 MenuScreen.sound (scene.h), ETC\\ETCSE */
    u8 pad_4C[0xA4 - 0x4C];
    s32 unk_A4;                              /* 0xA4 the value given to Graph_Init, passed to slot 0x40 */
};

extern ScreenVtbl *MenuScreen_GetVtbl(void);
extern GraphVtbl *Graph_GetVtable(void);

/* Graph_New's init (slot 0x08 of the graph vtable): the MenuScreen init with the sound file ETC\\ETCSE,
 * the graph vtable, the child's slot 0x9C, then the graph's slots 0xD8 and 0x40. */
void Graph_Init(Graph *graph, s32 value) {
    MenuScreen_GetVtbl()->init(graph, 0, "ETC\\ETCSE", 0);
    graph->vtbl = Graph_GetVtable();
    graph->sound->vtbl->setOctave(graph->sound, -1);
    graph->unk_A4 = value;
    graph->vtbl->unk_D8(graph, 0);
    graph->vtbl->loadImage(graph, value);
}

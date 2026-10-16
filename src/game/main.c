#include "common.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/pad.h"
#include "game/scene.h"
#include "psyq/libapi.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

Heap *g_mainHeap;
Scene *g_scene;
extern SceneSettings g_sceneSettings;

/* The boot entry. gcc inserts the __main() call (constructors) itself at the top of main. Makes the boot heap and the scene, then calls the scene's slots 0x44 and 0x4C. */
void main(void) {
    Display *display;

    SetMem(2);
    g_mainHeap = Heap_Create(0x166C00, 0);
    Heap_SetCurrent(g_mainHeap);
    g_scene = Scene_New(&g_sceneSettings);
    display = Display_New();
    g_scene->vtbl->setup(g_scene, display, Pad_New(0, 0));
    g_scene->vtbl->run(g_scene);
}

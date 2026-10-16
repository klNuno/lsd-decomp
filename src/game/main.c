#include "common.h"
#include "game/scene.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

Heap *g_mainHeap;
Scene *g_scene;
extern s32 g_sceneSettings[];
void SetMem(s32);
Heap *Heap_Create(u32, s32);
void Heap_SetCurrent(Heap *);
s32 Scene_New(s32);
Display *Display_New(void);
s32 Pad_New(s32, s32);

/* The boot entry. gcc inserts the __main() call (constructors) itself at the top of main. Makes the boot heap and the scene, then calls the scene's slots 0x44 and 0x4C. */
void main(void) {
    Display *display;

    SetMem(2);
    g_mainHeap = Heap_Create(0x166C00, 0);
    Heap_SetCurrent(g_mainHeap);
    g_scene = (Scene *)Scene_New((s32)g_sceneSettings);
    display = Display_New();
    g_scene->vtbl->setup(g_scene, display, Pad_New(0, 0));
    g_scene->vtbl->run(g_scene);
}

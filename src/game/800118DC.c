#include "common.h"

struct Heap;
struct Display;

/* The scene vtable (g_sceneVtbl, src/game/80025F7C.c). Only the two slots main calls are named. */
typedef struct SceneVtbl {
    u8 pad_00[0x44];
    void (*unk_44)(void *, void *, s32); /* 0x44 called with the scene, the display and Pad_New(0, 0) */
    u8 pad_48[0x4];
    void (*unk_4C)(void *);              /* 0x4C called with the scene alone */
} SceneVtbl;

/* The scene as main sees it: only the vtable pointer at 0x00 (the full layout is in src/game/80025F7C.c). */
typedef struct Scene {
    SceneVtbl *vtbl;
} Scene;

struct Heap *g_mainHeap;
Scene *g_scene;
extern s32 g_sceneSettings[];
void SetMem(s32);
struct Heap *Heap_Create(u32, s32);
void Heap_SetCurrent(struct Heap *);
s32 Scene_New(s32);
struct Display *Display_New(void);
s32 Pad_New(s32, s32);

/* The boot entry. gcc inserts the __main() call (constructors) itself at the top of main. Makes the boot heap and the scene, then calls the scene's slots 0x44 and 0x4C. */
void main(void) {
    struct Display *display;

    SetMem(2);
    g_mainHeap = Heap_Create(0x166C00, 0);
    Heap_SetCurrent(g_mainHeap);
    g_scene = (Scene *)Scene_New((s32)g_sceneSettings);
    display = Display_New();
    g_scene->vtbl->unk_44(g_scene, display, Pad_New(0, 0));
    g_scene->vtbl->unk_4C(g_scene);
}

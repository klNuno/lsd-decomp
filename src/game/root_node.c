#include "common.h"
#include "game/root_node.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/flat_light.h"
#include "psyq/libgs.h"

/*
 * RootNode: vtable g_rootNodeVtbl 0x8006EFAC (tag 0x14), 0x54 bytes, RootNode_Create: a scene node
 * holding 3 lights (FlatLight_New) and the ambient color; the default root of a screen (screen.h
 * ScreenEnv) and the base class of StageMap.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* not in game/scene_node.h: actor.c still reads this vtable through its own view of the slots */
SceneNodeVtbl *SceneNode_GetVtbl(void);
/* not in game/root_node.h: stage_map.c still reads this vtable through its own view of the slots */
RootNodeVtbl *RootNode_GetVtbl(void);
extern RootNodeVtbl g_rootNodeVtbl;

RootNode *RootNode_Create(void) {
    RootNode *root;

    root = Heap_Alloc(0x54);
    if (root != NULL) {
        RootNode_GetVtbl()->init(root);
        return root;
    }
    return NULL;
}

/* Slot 0x08: makes and watches its 3 lights. */
void RootNode_Init(RootNode *root) {
    s32 i;
    FlatLight **light;

    SceneNode_GetVtbl()->init(root);
    root->vtbl = RootNode_GetVtbl();
    for (i = 0, light = root->lights; i < 3; i++, light++) {
        *light = FlatLight_New(i);
        root->vtbl->watch(root, *light);
    }
    root->vtbl->setup(root);
}

/* Slot 0x0C: deletes its lights. */
void RootNode_Destroy(RootNode *root) {
    s32 i;
    FlatLight *light;

    for (i = 0; i < 3; i++) {
        light = root->vtbl->getLight(root, i);
        light->object.vtbl->delete_(light);
    }
    SceneNode_GetVtbl()->destroy(root);
}

/* Slot 0x40: only clears the flg word of its GsCOORDINATE2 (the base SceneNode_Reset resets the node). */
void RootNode_Setup(RootNode *root) {
    *root->coord = 0;
}

/* Slot 0x9C, empty */
void RootNode_OnNode(void) {
}

/* Slot 0xB8 */
FlatLight *RootNode_GetLight(RootNode *root, s32 index) {
    return root->lights[index];
}

/* Slot 0xBC: swap != 0 returns the previous color in *color. */
void RootNode_SetAmbient(RootNode *root, Color3 *color, s32 swap) {
    Color3 previous;

    if (swap != 0) {
        previous = root->ambient;
        root->ambient = *color;
        *color = previous;
    } else {
        root->ambient = *color;
    }
    GsSetAmbient((u8)root->ambient.r * 0x10, (u8)root->ambient.g * 0x10, (u8)root->ambient.b * 0x10);
}

RootNodeVtbl *RootNode_GetVtbl(void) {
    return &g_rootNodeVtbl;
}

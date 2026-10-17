#ifndef GAME_ROOT_NODE_H
#define GAME_ROOT_NODE_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/flat_light.h"

/*
 * RootNode (vtable g_rootNodeVtbl 0x8006EFAC, tag 0x14, 0x54 bytes, src/game/root_node.c): a scene node
 * (scene_node.h) holding 3 lights and the ambient color; the default root of a screen (screen.h
 * ScreenEnv) and the base class of StageMap.
 */
typedef struct RootNodeVtbl {
    u8 pad_00[0x08];
    void (*init)(void *);                     /* 0x08 RootNode_Init */
    void (*destroy)(void *);                  /* 0x0C RootNode_Destroy */
    void (*watch)(void *, void *);            /* 0x10 SceneNode_Watch */
    u8 pad_14[0x40 - 0x14];
    void (*reset)(void *);                    /* 0x40 RootNode_Reset */
    u8 pad_44[0xB8 - 0x44];
    FlatLight *(*getLight)(void *, s32);      /* 0xB8 RootNode_GetLight */
} RootNodeVtbl;

/* The first 0x44 bytes are the scene node's (scene_node.h SceneNode). */
typedef struct RootNode {
    RootNodeVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C */
    s32 unk10;
    s32 *coord;             /* 0x14 its GsCOORDINATE2, the first word is flg */
    u8 pad_18[0x44 - 0x18];
    FlatLight *lights[3];   /* 0x44 FlatLight_New(0 to 2), watched by the node */
    Color3 ambient;         /* 0x50 GsSetAmbient takes it times 16 */
} RootNode;

/* Functions of src/game/root_node.c that other files call or reference (docs/naming.md, Prototypes) */
RootNodeVtbl *RootNode_GetVtbl(void);
RootNode *RootNode_Create(void);
FlatLight *RootNode_GetLight(RootNode *root, s32 index);
void RootNode_SetAmbient(RootNode *root, Color3 *color, s32 swap);

#endif

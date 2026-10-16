#ifndef GAME_BG_H
#define GAME_BG_H

#include "common.h"
#include "game/gs.h"
#include "game/scene_node.h"

/*
 * Psy-Q GsBG, GsMAP and GsCELL as src/game/bg.c, bg_map.c and bg_cells.c fill them: a background sprite made of
 * cells. src/game/menu_screen.c builds one full-screen 16-bit Bg: BgCells, a BgMap over them,
 * then a Bg in mode 1 over the map.
 */
typedef struct GsBg {
    u32 attribute;            /* 0x01000000 8-bit or 0x02000000 16-bit colour mode */
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 scrollX;
    s16 scrollY;
    Color3 color;
    u8 pad_13;
    void *map;
    s16 mx;                   /* rotation and scale centre, w / 2 and h / 2 */
    s16 my;
    s16 scaleX;               /* 0x1000 = 1 */
    s16 scaleY;
    s32 rotate;
} GsBg;

typedef struct GsCell {
    u8 u;
    u8 v;
    u16 cba;
    u16 flag;
    u16 tpage;
} GsCell;

/* Bg (vtable g_bgVtbl, 0x68 bytes, Bg_Create): derives from the class of SceneNode_GetVtbl */
typedef struct BgVtbl {
    s32 unk_00;               /* 0x54 */
    void *(*delete_)();       /* 0x04 Object_Delete */
    s32 (*init)();            /* 0x08 Bg_Init (self, map, mode) */
    void (*destroy)();        /* 0x0C SceneNode_Destroy */
    u8 pad_10[0x40 - 0x10];
    void (*setMap)();         /* 0x40 Bg_SetMap (self, map, mode) */
    void (*setRotation)();    /* 0x44 Bg_SetRotation (self, set, fraction) */
    void (*setScale)();       /* 0x48 Bg_SetScale (self, set, fractions) */
    void (*show)();           /* 0x4C SceneNode_Attach (self, root, position) */
    void (*hide)();           /* 0x50 SceneNode_Detach */
    u8 pad_54[0xB8 - 0x54];
    void (*setColor)();       /* 0xB8 Bg_SetColor (self, set, color) */
    void (*unk_BC)();         /* Bg_EmptySlotBC, empty */
} BgVtbl;

typedef struct Bg {
    BgVtbl *vtbl;
    u8 pad_04[0x44 - 0x04];
    GsBg bg;                  /* 0x44 */
} Bg;

/* Functions of src/game/bg.c that other files call or reference (docs/naming.md, Prototypes) */
struct BgMap;
Bg *Bg_Create(struct BgMap *map, s32 mode);

#endif

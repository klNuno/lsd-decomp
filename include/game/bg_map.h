#ifndef GAME_BG_MAP_H
#define GAME_BG_MAP_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/bg_cells.h"

/* BgMap (vtable g_bgMapVtbl, 0x44 bytes, BgMap_Create): a GsMAP of 20x15 cells over a BgCells */
typedef struct BgMapVtbl {
    FileVtbl base;
    void (*build)();          /* 0x78 BgMap_Build */
} BgMapVtbl;

typedef struct BgMap {
    BgMapVtbl *vtbl;          /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    u8 *data;
    s32 size;
    CdlLOC cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;
    u16 direct;
    u16 state;
    u8 cellW;                 /* 0x2C GsMAP from here: cellw, cellh, ncellw, ncellh, base, index */
    u8 cellH;
    u16 cellsX;
    s16 cellsY;
    u8 pad_32[0x34 - 0x32];
    GsCell *cells;            /* 0x34 the BgCells' GsCell table */
    s16 *index;               /* 0x38 cellsX * cellsY cell numbers, 0 to n - 1 */
    BgCells *cellSource;      /* 0x3C */
    u16 fullScreen;           /* 0x40 */
    u16 built;                /* 0x42 */
} BgMap;

/* Functions of src/game/bg_map.c that other files call or reference (docs/naming.md, Prototypes) */
BgMap *BgMap_Create(s32 skipBuild, BgCells *cells);
BgMapVtbl *BgMap_GetVtbl(void);

#endif

#ifndef GAME_BG_CELLS_H
#define GAME_BG_CELLS_H

#include "common.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/bg.h"

/* BgCells (vtable g_bgCellsVtbl, 0x38 bytes, BgCells_Create): 300 cells of 16x16 over VRAM x 640 to 960 */
typedef struct BgCellsVtbl {
    FileVtbl base;
    void (*build)();          /* 0x78 BgCells_Build */
} BgCellsVtbl;

typedef struct BgCells {
    BgCellsVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x2A - 0x0C];
    u16 state;                /* 0x2A */
    GsCell *cells;            /* 0x2C */
    u16 fullScreen;           /* 0x30 set by init when made without a file */
    u16 built;                /* 0x32 */
    s32 unk_34;               /* freed by destroy, never set in this unit */
} BgCells;

/* Functions of src/game/bg_cells.c that other files call or reference (docs/naming.md, Prototypes) */
BgCells *BgCells_Create(s32 skipBuild);
BgCellsVtbl *BgCells_GetVtbl(void);

#endif

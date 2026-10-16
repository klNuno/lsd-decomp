#include "common.h"
#include "game/bg_cells.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/bg.h"
#include "psyq/libgpu.h"

/*
 * BgCells: the GsCELL table of a BgMap (include/game/bg_cells.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern BgCellsVtbl g_bgCellsVtbl;

BgCells *BgCells_Create(s32 skipBuild) {
    BgCells *bgCells;

    bgCells = Heap_Alloc(0x38);
    if (bgCells != NULL) {
        BgCells_GetVtbl()->base.init(bgCells, skipBuild);
        return bgCells;
    }
    return NULL;
}

void BgCells_Init(BgCells *bgCells, s32 skipBuild) {
    char unused[0x20]; /* same 0x20 buffer as SeqFile_Init's strcpy target */

    File_GetBackendVtbl()->init(bgCells);
    bgCells->vtbl = BgCells_GetVtbl();
    bgCells->unk_34 = 0;
    bgCells->built = 0;
    if (skipBuild == 0) {
        bgCells->fullScreen = 1;
        bgCells->state = 0;
        bgCells->vtbl->base.onLoaded(bgCells);
    }
}

void BgCells_Destroy(BgCells *bgCells) {
    Heap_Free(bgCells->unk_34);
    Heap_Free(bgCells->cells);
    File_GetBackendVtbl()->destroy(bgCells);
}

void BgCells_OnLoaded(BgCells *bgCells) {
    s32 unused[8];

    if (bgCells->state == 0) {
        bgCells->vtbl->build(bgCells);
        bgCells->built = 1;
    }
}

/*
 * Slot 0x78: 300 cells of 16x16, 20 per row over VRAM x 640 to 960, rows of 16 lines;
 * the texture page follows x (x >> 6, + 0x10 from line 256).
 */
void BgCells_Build(BgCells *bgCells) {
    s32 i;
    s32 n;
    s32 u;
    s32 v;
    s32 x;
    s32 tpage;
    GsCell *p;
    GsCell *cells;

    if (bgCells->fullScreen != 0) {
        x = 0x280;
        v = 0;
        u = 0;
        tpage = GetTPage(2, 0, 0x280, 0) & 0xFFFF;
        cells = Heap_Alloc(0x960);
        bgCells->cells = cells;
        if (cells != NULL) {
            i = 0;
            p = cells;
            n = 0x12C;
            do {
                p->u = u;
                u += 0x10;
                x += 0x10;
                p->tpage = tpage;
                p->v = v;
                p->cba = 0;
                p->flag = 0;
                if (x >= 0x3C0) {
                    u = 0;
                    x = 0x280;
                    v += 0x10;
                }
                if ((x & 0x3F) == 0) {
                    tpage = x >> 6;
                    if (v >= 0x100) {
                        tpage += 0x10;
                    }
                    u = 0;
                }
                i += 1;
                p++;
            } while (i < n);
        }
    }
}

BgCellsVtbl *BgCells_GetVtbl(void) {
    return &g_bgCellsVtbl;
}

#include "common.h"
#include "game/loader.h"
#include "game/bg_map.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * BgMap: the GsMAP of a Bg (include/game/loader.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern BgMapVtbl g_bgMapVtbl;

/* ---- BgMap: GsMAP over a BgCells ---- */

s32 BgMap_Create(s32 skipBuild, s32 cells) {
    s32 bgMap;

    bgMap = Heap_Alloc(0x44);
    if (bgMap != 0) {
        BgMap_GetVtbl()->base.init(bgMap, skipBuild, cells);
        return bgMap;
    }
    return 0;
}

void BgMap_Init(BgMap *bgMap, s32 skipBuild, BgCells *cells) {
    s32 unused[8];

    File_GetBackendVtbl()->init(bgMap);
    bgMap->vtbl = BgMap_GetVtbl();
    bgMap->cellSource = cells;
    bgMap->built = 0;
    if (skipBuild == 0) {
        bgMap->fullScreen = 1;
        bgMap->state = 0;
        bgMap->vtbl->base.onLoaded(bgMap);
    }
}

void BgMap_Destroy(BgMap *bgMap) {
    Heap_Free(bgMap->index);
    File_GetBackendVtbl()->destroy(bgMap);
}

/* Slot 0x78 is called without arguments: a0 still holds bgMap */
void BgMap_OnLoaded(BgMap *bgMap) {
    if (bgMap->state == 0) {
        bgMap->vtbl->build();
        bgMap->built = 1;
    }
}

/* Slot 0x78: 20x15 cells of 16x16 numbered in order; frees the data when it cannot */
void BgMap_Build(BgMap *bgMap) {
    s16 *index;
    s16 *p;
    s32 i;
    s32 n;

    bgMap->cells = (s32)bgMap->cellSource->cells;
    if (bgMap->fullScreen != 0) {
        bgMap->cellsX = 0x14;
        bgMap->cellW = 0x10;
        bgMap->cellH = 0x10;
        bgMap->cellsY = 0xF;
        n = bgMap->cellsX * bgMap->cellsY;
        index = (s16 *)Heap_Alloc(n * 2);
        bgMap->index = index;
        if (index != NULL) {
            p = index;
            for (i = 0; i < n; i++) {
                *p++ = i;
            }
            return;
        }
    }
    bgMap->vtbl->base.freeData(bgMap);
}

BgMapVtbl *BgMap_GetVtbl(void) {
    return &g_bgMapVtbl;
}

#include "common.h"
#include "game/bg.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/scene_node.h"

/*
 * Bg: a PSY-Q GsBG background object (include/game/bg.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* BgMap as Bg_SetMap reads it: cellsY unsigned (signed in BgMap_Build) */
typedef struct BgMapView {
    u8 pad_00[0x2C];
    u8 cellW;                  /* 0x2C the GsMAP */
    u8 cellH;
    u16 cellsX;
    u16 cellsY;
} BgMapView;

/* not in game/scene_node.h: actor.c still reads this vtable through its own view of the slots */
SceneNodeVtbl *SceneNode_GetVtbl(void);
static BgVtbl *Bg_GetVtbl(void);
extern BgVtbl g_bgVtbl;
extern Color3 g_bgDefaultColor;    /* {0x80, 0x80, 0x80}, the neutral GsBG colour */

Bg *Bg_Create(struct BgMap *map, s32 mode) {
    Bg *bg = Heap_Alloc(0x68);

    if (bg != NULL) {
        Bg_GetVtbl()->init(bg, map, mode);
        return bg;
    }
    return NULL;
}

void Bg_Init(Bg *bg, struct BgMap *map, s32 mode) {
    BgVtbl *vtbl;

    SceneNode_GetVtbl()->init(bg);
    vtbl = Bg_GetVtbl();
    bg->vtbl = vtbl;
    vtbl->setMap(bg, map, mode);
}

/* Slot 0x40: mode 0 sizes the GsBG from the map (8-bit), mode 1 makes it 320x240 (16-bit) */
void Bg_SetMap(Bg *bg, BgMapView *map, s32 mode) {
    if (mode == 0) {
        bg->bg.attribute = 0x01000000;
        bg->bg.w = map->cellW * map->cellsX;
        bg->bg.h = map->cellH * map->cellsY;
    } else if (mode == 1) {
        bg->bg.attribute = 0x02000000;
        bg->bg.w = 0x140;
        bg->bg.h = 0xF0;
    }
    bg->bg.x = 0;
    bg->bg.y = 0;
    bg->bg.scrollX = 0;
    bg->bg.scrollY = 0;
    bg->bg.color = g_bgDefaultColor;
    bg->bg.map = &map->cellW;
    bg->bg.scaleX = 0x1000;
    bg->bg.scaleY = 0x1000;
    bg->bg.rotate = 0;
    bg->bg.mx = bg->bg.w / 2;
    bg->bg.my = bg->bg.h / 2;
}

/* Slot 0x44: degrees x, y, z like SceneNode_SetRotation; a GsBG turns around z only:
   rotate = num / den in fixed point 12 bits, set when set != 0, else added */
void Bg_SetRotation(Bg *bg, s32 set, Fraction *degrees) {
    s16 num = degrees[2].num;
    s16 den = degrees[2].den;
    s32 value = ((num / den) << 12) + (((num % den) << 12) / den);

    if (set != 0) {
        bg->bg.rotate = value;
        return;
    }
    bg->bg.rotate = value + bg->bg.rotate;
}

/*
 * Slot 0x48: scaleX = s[0] / s[1] and scaleY = s[2] / s[3] in fixed point 12 bits (a zero
 * divisor gives 1.0 when setting), capped at 30000; set != 0 sets them, else adds. An added
 * value past the cap gives 1 when that fraction had a negative term.
 */
void Bg_SetScale(Bg *bg, s32 set, s16 *fractions) {
    s16 scaleX;
    s16 scaleY;
    s32 negativeX = 0;
    s32 negativeY = 0;
    s16 value;

    if (fractions[0] < 0 || fractions[1] < 0) {
        negativeX = 1;
    }
    if (fractions[2] < 0 || fractions[3] < 0) {
        negativeY = 1;
    }
    if (fractions[1] != 0) {
        s32 q = fractions[0] / fractions[1];
        s32 r = fractions[0] % fractions[1];
        scaleX = (q << 12) + ((r << 12) / fractions[1]);
    }
    if (fractions[3] != 0) {
        s32 q = fractions[2] / fractions[3];
        s32 r = fractions[2] % fractions[3];
        scaleY = (q << 12) + ((r << 12) / fractions[3]);
    }
    if (set != 0) {
        if (fractions[1] == 0) {
            bg->bg.scaleX = 0x1000;
        } else {
            value = scaleX >= 0x7531 ? 0x7530 : scaleX;
            bg->bg.scaleX = value;
        }
        if (fractions[3] == 0) {
            bg->bg.scaleY = 0x1000;
        } else {
            value = scaleY >= 0x7531 ? 0x7530 : scaleY;
            bg->bg.scaleY = value;
        }
        return;
    }
    value = bg->bg.scaleX;
    if (value + scaleX >= 0x7531) {
        bg->bg.scaleX = negativeX ? 1 : 0x7530;
    } else {
        bg->bg.scaleX = scaleX + value;
    }
    value = bg->bg.scaleY;
    if (value + scaleY >= 0x7531) {
        bg->bg.scaleY = negativeY ? 1 : 0x7530;
    } else {
        bg->bg.scaleY = scaleY + value;
    }
}

void Bg_SetColor(Bg *bg, s32 set, Color3 *color) {
    if (set != 0) {
        bg->bg.color = *color;
    }
}

void Bg_EmptySlotBC(void) {
}

static BgVtbl *Bg_GetVtbl(void) {
    return &g_bgVtbl;
}

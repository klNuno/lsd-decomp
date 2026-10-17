#include "common.h"
#include "game/glyph.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/screen_sprite.h"
#include "game/tim.h"

/*
 * Glyph: vtable g_glyphVtbl 0x8006EC74 (tag 0x1144), 0xAC bytes, Glyph_Create: a ScreenSprite
 * showing one 8x8 character of a font image laid out 32 characters per row. Like ScreenSprite and
 * SpriteNode, a scene node (base SceneNode_GetVtbl, vtable 0x8006B5CC, tag 4) that draws a libgs
 * GsSPRITE cut from a TIM image; slots 0x60 to 0x68 work on the sprite's attribute word instead of
 * the node's.
 *
 * File boundaries: likely (docs/layout.md)
 */

static void Glyph_GetRect(SpriteRect *rect, u32 code);

extern GlyphVtbl g_glyphVtbl;
extern SpriteRect g_glyphCellRect;      /* {0, 0, 8, 8}: the cell of character 0 */

Glyph *Glyph_Create(Tim *font, u8 code) {
    Glyph *glyph;

    glyph = Heap_Alloc(0xAC);
    if (glyph != NULL) {
        Glyph_GetVtbl()->init(glyph, font, code);
        return glyph;
    }
    return NULL;
}

/* Slot 0x08: a screen sprite on the cell of a space (0x20), then the code. */
void Glyph_Init(Glyph *glyph, Tim *font, u8 code) {
    SpriteRect rect;
    GlyphVtbl *vtbl;

    Glyph_GetRect(&rect, 0x20);
    ScreenSprite_GetVtbl()->init(glyph, font, &rect, 0);
    vtbl = Glyph_GetVtbl();
    glyph->vtbl = vtbl;
    vtbl->reset(glyph, code);
}

/* Slot 0x40 */
void Glyph_Reset(Glyph *glyph, u8 code) {
    glyph->vtbl->setCode(glyph, code);
}

/* Slot 0xC4: moves the sprite to the character's cell. */
void Glyph_SetCode(Glyph *glyph, u8 code) {
    u8 rect[12];

    glyph->code = code;
    Glyph_GetRect((SpriteRect *)rect, code);
    glyph->sprite.u = rect[0];
    glyph->sprite.v = rect[2];
}

/* Slot 0xC8 */
u8 Glyph_GetCode(Glyph *glyph) {
    s32 unused[4];
    return glyph->code;
}

GlyphVtbl *Glyph_GetVtbl(void) {
    return &g_glyphVtbl;
}

/* The 8x8 cell of a character: 32 per row. */
static void Glyph_GetRect(SpriteRect *rect, u32 code) {
    *rect = g_glyphCellRect;
    code = code & 0xFF;
    rect->u = rect->u + ((code & 0x1F) * 8);
    rect->v = rect->v + ((code >> 5) * 8);
}

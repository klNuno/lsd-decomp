#ifndef GAME_GLYPH_H
#define GAME_GLYPH_H

#include "common.h"

/* Functions of src/game/glyph.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/glyph.c */
struct Glyph;
struct GlyphVtbl;
struct Tim;
struct Glyph *Glyph_Create(struct Tim *font, u8 code);
struct GlyphVtbl *Glyph_GetVtbl(void);

#endif

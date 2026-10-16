#ifndef GAME_GLYPH_H
#define GAME_GLYPH_H

#include "common.h"

/* Functions of src/game/glyph.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/glyph.c */
struct GlyphVtbl;
void *Glyph_Create(s32 font, u8 code);
struct GlyphVtbl *Glyph_GetVtbl(void);

#endif

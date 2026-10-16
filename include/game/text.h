#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "common.h"

/* Functions of src/game/text.c that other files call or reference (docs/naming.md, Prototypes) */
s8 *Text_Decode(s8 *dst, u8 *src);
s8 *Text_Encode(s8 *dst, u8 *src);
void Text_FormatNumber(s8 *dst, s32 value, s32 width, s32 noPad);

#endif

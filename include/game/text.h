#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "common.h"

/* One full-width (Shift-JIS) character of the card title. */
typedef struct SjisChar {
    s8 hi;
    s8 lo;
} SjisChar;

typedef struct SjisChar3 {
    SjisChar c[3];
} SjisChar3;

/* Functions of src/game/text.c that other files call or reference (docs/naming.md, Prototypes) */
s8 *Text_Decode(s8 *dst, u8 *src);
s8 *Text_Encode(s8 *dst, u8 *src);
void Text_FormatNumber(s8 *dst, s32 value, s32 width, s32 noPad);

#endif

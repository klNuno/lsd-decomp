#ifndef PSYQ_LIBPRESS_H
#define PSYQ_LIBPRESS_H

#include "types.h"

/* LIBPRESS functions the movie player (movie.c) calls. */

void DecDCTReset(s32 mode);
void DecDCTvlc(u32 *bs, u32 *buf);
void DecDCTin(u32 *buf, s32 mode);
void DecDCTout(u32 *buf, s32 size);
void DecDCToutCallback(void (*func)(void));

#endif

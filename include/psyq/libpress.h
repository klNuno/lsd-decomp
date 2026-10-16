#ifndef PSYQ_LIBPRESS_H
#define PSYQ_LIBPRESS_H

#include "types.h"

/* LIBPRESS functions the movie player (movie.c) calls; buffers are passed as addresses. */

void DecDCTReset(s32 mode);
void DecDCTvlc(s32 bs, s32 buf);
void DecDCTin(s32 buf, s32 mode);
void DecDCTout(s32 buf, s32 size);
void DecDCToutCallback(void (*func)(void));

#endif

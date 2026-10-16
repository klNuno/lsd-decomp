#ifndef PSYQ_LIBC_H
#define PSYQ_LIBC_H

#include "types.h"

/* LIBC and LIBC2 functions the game calls. */

s32 printf(const char *fmt, ...);
s32 strlen(u8 *s);
s8 *strcpy(s8 *dst, s8 *src);
s8 *strcat(s8 *dst, s8 *src);
char *strstr(char *s, char *find);
/* the builtin's form: card.c's call compiles to other bytes with any other */
void *memcpy(void *dst, const void *src, u32 n);
void *memset(void *dst, s32 c, s32 n);
s32 atoi(u8 *s);
s8 *itoa(s32 value);
s32 rand(void);
void srand(u32 seed);

#endif

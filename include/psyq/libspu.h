#ifndef PSYQ_LIBSPU_H
#define PSYQ_LIBSPU_H

#include "types.h"

/* LIBSPU functions the game calls. */

void SpuInit(void);
void SpuInitHot(void);
void SpuQuit(void);
void SpuSetCommonAttr(void *attr);

#endif

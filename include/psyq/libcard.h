#ifndef PSYQ_LIBCARD_H
#define PSYQ_LIBCARD_H

#include "types.h"

/* LIBCARD functions the game calls (the BIOS card calls InitCARD and _card_info are in libapi.h). */

void _card_clear(s32 channel);

#endif

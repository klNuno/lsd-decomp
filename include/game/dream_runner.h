#ifndef GAME_DREAM_RUNNER_H
#define GAME_DREAM_RUNNER_H

#include "common.h"

/* Functions of src/game/dream_runner.c that other files call or reference (docs/naming.md, Prototypes) */
s32 DreamRunner_New(s32 context, s32 dreamSys, s32 arg2);
void File_ResolvePathTablePart(s32 arg0);

#endif

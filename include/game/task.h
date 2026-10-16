#ifndef GAME_TASK_H
#define GAME_TASK_H

#include "common.h"
#include "game/stage.h"

/* Functions of src/game/task.c that other files call or reference (docs/naming.md, Prototypes) */
void Task_OnPad(void);
void Task_OnTick(Task *task, s32 sender, s32 message);
void Task_SetState(Task *task, s32 state);
void Task_SetTimeout(Task *task, s32 timeout);
void Task_PlayTone(Task *task, s32 tone);

#endif

#include "common.h"
#include "game/task.h"
#include "game/heap.h"
#include "game/sound_bank.h"
#include "game/screen.h"

/*
 * Task (vtable g_taskVtbl 0x80086668, types in game/task.h): a class with a tick count, a timeout
 * and a result that DreamRunner and Place derive from.
 *
 * File boundaries: likely (docs/layout.md)
 */

extern u8 g_taskVtbl[];

/* the vtable of screen.c through this file's view of its slots, so not from game/screen.h */
TaskBaseVtbl *Screen_GetVtbl(void);
/* not in game/task.h: each file that calls it reads the vtable through its own view of the slots */
TaskVtbl *Task_GetVtbl(void);

static s32 Task_New(s32 bankName, s32 sound) {
    s32 task;

    task = Heap_Alloc(0x38);
    if (task != 0) {
        Task_GetVtbl()->init(task, bankName, sound);
        return task;
    }
    return 0;
}

/* With a bank name the task makes and owns its sound bank, else it uses the one given. */
void Task_Init(Task *task, s32 bankName, void *sound) {
    Screen_GetVtbl()->init(task);
    task->vtbl = Task_GetVtbl();
    if (bankName != 0) {
        task->sound = Sound_CreateBank(bankName);
    } else {
        task->sound = sound;
    }
    task->bankName = bankName;
    task->vtbl->reset(task);
}

void Task_Destroy(Task *task) {
    if (task->bankName != 0) {
        SoundBank *sound = task->sound;
        sound->vtbl->delete_(sound);
    }
    Screen_GetVtbl()->destroy(task);
}

void Task_ClearTimeout(Task *task) {
    task->vtbl->setTimeout(task, -1);
}

s32 Task_Run(Task *task, s32 context, s32 noLoop) {
    task->result = 0;
    Screen_GetVtbl()->run(task, context, noLoop);
    return task->result;
}

void Task_Finish(s32 task) {
    Screen_GetVtbl()->finish(task);
}

void Task_OnPad(void) {
}

void Task_OnTick(Task *task, s32 sender, s32 message) {
    Screen_GetVtbl()->onTick(task, sender, message);
    if (task->ticks > task->timeout) {
        task->vtbl->setState(task, TASK_STATE_TIMEOUT);
    }
}

void Task_SetState(Task *task, s32 state) {
    Screen_GetVtbl()->setState(task, state);
    if (state == TASK_STATE_TIMEOUT) {
        task->result = 1;
        task->vtbl->onTimeout(task);
    }
}

/* Timeout x 20 ticks; negative never times out. */
void Task_SetTimeout(Task *task, s32 timeout) {
    task->timeout = timeout;
    if (timeout >= 0) {
        task->timeout = timeout * 20;
    }
}

void Task_PlayTone(Task *task, s32 tone) {
    SoundBank *sound = task->sound;
    if (sound != NULL) {
        sound->vtbl->playTone(sound, tone, 0x7F, 0x7F);
    }
}

TaskVtbl *Task_GetVtbl(void) {
    return (TaskVtbl *)g_taskVtbl;
}

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

extern TaskVtbl g_taskVtbl;

/* not in game/task.h: place.c still reads this vtable through its own view of the slots */
TaskVtbl *Task_GetVtbl(void);

static Task *Task_New(s8 *bankName, SoundBank *sound) {
    Task *task;

    task = Heap_Alloc(0x38);
    if (task != NULL) {
        Task_GetVtbl()->init(task, bankName, sound);
        return task;
    }
    return NULL;
}

/* With a bank name the task makes and owns its sound bank, else it uses the one given. */
void Task_Init(Task *task, s8 *bankName, SoundBank *sound) {
    Screen_GetVtbl()->init(task);
    task->vtbl = Task_GetVtbl();
    if (bankName != NULL) {
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

void Task_Finish(Task *task) {
    Screen_GetVtbl()->finish(task);
}

void Task_OnPad(void) {
}

void Task_OnTick(Task *task, s32 sender, s32 message) {
    Screen_GetVtbl()->onClock(task, sender, message);
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
    return &g_taskVtbl;
}

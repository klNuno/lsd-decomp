#ifndef GAME_TASK_H
#define GAME_TASK_H

#include "common.h"
#include "game/sound_bank.h"
#include "game/screen.h"

/*
 * Task (src/game/task.c): vtable 0x80086668, class id 0x230, 0x38 bytes, a class with a timeout and a
 * result that the dream runner (dream_runner.h) and the dream stage (place.h) derive from. Its base
 * (vtable 0x8006E878) runs the loop.
 * Vtable contents come from the executable (work/readable/W3/vt.py); slots are named after the
 * function stored there. Slots are left unprototyped where callers pass different types.
 */

/* The base class of Task (vtable 0x8006E878, src/game/screen.c): the slots Task chains to. */
typedef struct TaskBaseVtbl {
    u8 pad_00[0x08];
    void (*init)();         /* 0x08 Screen_Init */
    void (*destroy)();      /* 0x0C Object_Destroy */
    u8 pad_10[0x44 - 0x10];
    void (*run)();          /* 0x44 Screen_Run */
    void (*finish)();        /* 0x48 Screen_Finish */
    u8 pad_4C[0x5C - 0x4C];
    void (*onTick)();       /* 0x5C Screen_OnClock: ticks++ */
    void (*setState)();     /* 0x60 Screen_SetState: state = arg, notify the watchers */
} TaskBaseVtbl;

typedef struct TaskVtbl {
    s32 classWord;          /* 0x230 */
    void *(*delete_)();     /* 0x04 Object_Delete */
    void (*init)();         /* 0x08 Task_Init */
    void (*destroy)();      /* 0x0C Task_Destroy */
    void (*watch)();        /* 0x10 Object_Watch */
    void (*unwatch)();      /* 0x14 Object_Unwatch */
    u8 pad_18[0x30 - 0x18];
    void (*notify)();       /* 0x30 Object_Notify */
    u8 pad_34[0x38 - 0x34];
    void (*onNotify)();     /* 0x38 */
    u8 pad_3C[0x40 - 0x3C];
    void (*reset)();        /* 0x40 Task_ClearTimeout: no timeout */
    s32 (*run)();           /* 0x44 Task_Run: run the loop, return the result */
    void (*finish)();        /* 0x48 Task_Finish */
    u8 pad_4C[0x54 - 0x4C];
    void (*update)();       /* 0x54 Screen_OnDisplay (base), message type 1 */
    u8 pad_58[0x5C - 0x58];
    void (*onTick)();       /* 0x5C Task_OnTick */
    void (*setState)();     /* 0x60 Task_SetState: state 4 means timed out */
    u8 pad_64[0x6C - 0x64];
    void (*setTimeout)();   /* 0x6C Task_SetTimeout */
    void (*playTone)();     /* 0x70 Task_PlayTone */
    u8 pad_74[0x7C - 0x74];
    void (*onTimeout)();    /* 0x7C 0 in this vtable, set by derived classes */
} TaskVtbl;

typedef struct Task {
    TaskVtbl *vtbl;
    u8 pad_04[0x1C - 0x04];
    u32 ticks;              /* 0x1C counted by the base's slot 0x5C */
    s32 state;              /* 0x20 set by slot 0x60 */
    u8 pad_24[0x28 - 0x24];
    s32 result;             /* 0x28 returned by run */
    u32 timeout;            /* 0x2C ticks; -1 never (slot 0x6C) */
    s32 bankName;           /* 0x30 when not 0, the task made its own sound bank from this name */
    SoundBank *sound;       /* 0x34 */
} Task;

#define TASK_STATE_TIMEOUT 4

/* Functions of src/game/task.c that other files call or reference (docs/naming.md, Prototypes) */
void Task_OnPad(void);
void Task_OnTick(Task *task, s32 sender, s32 message);
void Task_SetState(Task *task, s32 state);
void Task_SetTimeout(Task *task, s32 timeout);
void Task_PlayTone(Task *task, s32 tone);

#endif

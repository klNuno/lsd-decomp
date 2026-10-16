#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H

#include "common.h"
#include "game/heap.h"

/* The clock (vtable g_clockVtbl 0x8006EF50, class word 5, src/game/clock.c, sender type 5): each
   step counts and sends CLOCK_MSG_TICK, or CLOCK_MSG_PAUSED when paused, CLOCK_MSG_STOPPED when stopped. */
#define CLOCK_MSG_TICK 2
#define CLOCK_MSG_PAUSED 3
#define CLOCK_MSG_STOPPED 4

typedef struct ClockVtbl {
    s32 classWord;           /* 0x00 5 */
    void *(*delete_)();      /* 0x04 Object_Delete */
    void (*init)(void *);    /* 0x08 Clock_Init */
    void (*destroy)();       /* 0x0C Clock_Destroy */
    u8 pad_10[0x24 - 0x10];
    void (*removeWatcher)(); /* 0x24 Clock_RemoveWatcher */
    u8 pad_28[0x30 - 0x28];
    void (*notify)(void *, s32);  /* 0x30 Clock_Notify */
    u8 pad_34[0x40 - 0x34];
    void (*reset)(void *, s32);   /* 0x40 Clock_Reset (clock, ticks) */
    void (*step)();          /* 0x44 Clock_Step */
    s32 (*getTicks)();       /* 0x48 Clock_GetTicks */
    void (*pause)();         /* 0x4C Clock_Pause */
    void (*resume)();        /* 0x50 Clock_Resume */
    s32 (*isPaused)();       /* 0x54 Clock_IsPaused */
    void (*stop)();          /* 0x58 Clock_Stop */
} ClockVtbl;

typedef struct Clock {
    ClockVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 ticks;              /* 0x0C steps counted while running */
    s32 paused;             /* 0x10 */
    s32 stopped;            /* 0x14 */
    ListNode *notifyIter;   /* 0x18 the watcher list cursor while Clock_Notify runs */
} Clock;

/* Functions of src/game/clock.c that other files call or reference (docs/naming.md, Prototypes) */
void *Clock_Create(void);

#endif

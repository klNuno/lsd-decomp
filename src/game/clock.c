#include "common.h"
#include "game/clock.h"
#include "game/heap.h"

/*
 * Clock: vtable g_clockVtbl 0x8006EF50 (tag 5), 0x1C bytes, Clock_Create: each step adds a tick and
 * tells every watcher 2, or 3 when paused, 4 when stopped (clock.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

static ClockVtbl *Clock_GetVtbl(void);
extern ClockVtbl g_clockVtbl;

void *Clock_Create(void) {
    void *clock;

    clock = Heap_Alloc(0x1C);
    if (clock != 0) {
        Clock_GetVtbl()->init(clock);
        return clock;
    }
    return 0;
}

/* Slot 0x08 */
void Clock_Init(Clock *clock) {
    ClockVtbl *vtbl;

    Object_GetBaseVtbl()->init(clock);
    vtbl = Clock_GetVtbl();
    clock->vtbl = vtbl;
    vtbl->reset(clock, 0);
}

/* Slot 0x0C */
void Clock_Destroy(Clock *clock) {
    Object_GetBaseVtbl()->destroy(clock);
}

/* Slot 0x24: a watcher removed while Clock_Notify runs moves its cursor past it. */
void Clock_RemoveWatcher(Clock *clock, Object *watcher) {
    ListNode *node;

    node = clock->notifyIter;
    if (node != NULL && watcher == node->value) {
        clock->notifyIter = node->next;
    }
    Object_GetBaseVtbl()->removeWatcher(clock, watcher);
}

/* Slot 0x30: Object_Notify with its cursor in the clock. */
void Clock_Notify(Clock *clock, s32 message) {
    Object *watcher;

    clock->notifyIter = clock->watchers;
    List_Next(&watcher, &clock->notifyIter);
    while (watcher != NULL) {
        watcher->vtbl->onNotify(watcher, clock, message);
        List_Next(&watcher, &clock->notifyIter);
    }
    clock->notifyIter = 0;
}

/* Slot 0x40 */
void Clock_Reset(Clock *clock, s32 ticks) {
    clock->ticks = ticks;
    clock->stopped = 0;
    clock->paused = 0;
    clock->notifyIter = 0;
}

/* Slot 0x44 */
void Clock_Step(Clock *clock) {
    s32 message = CLOCK_MSG_STOPPED;

    if (clock->stopped == 0) {
        message = CLOCK_MSG_PAUSED;
        if (clock->paused == 0) {
            message = CLOCK_MSG_TICK;
            clock->ticks++;
        }
    }
    clock->vtbl->notify(clock, message);
}

/* Slot 0x48 */
s32 Clock_GetTicks(Clock *clock) {
    return clock->ticks;
}

/* Slot 0x4C */
void Clock_Pause(Clock *clock) {
    clock->paused = 1;
}

/* Slot 0x50 */
void Clock_Resume(Clock *clock) {
    clock->paused = 0;
}

/* Slot 0x54 */
s32 Clock_IsPaused(Clock *clock) {
    return clock->paused;
}

/* Slot 0x58 */
void Clock_Stop(Clock *clock) {
    clock->stopped = 1;
}

static ClockVtbl *Clock_GetVtbl(void) {
    return &g_clockVtbl;
}

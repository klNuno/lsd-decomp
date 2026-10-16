#include "common.h"
#include "game/screen.h"
#include "game/heap.h"
#include "game/scene_node.h"
#include "game/display.h"
#include "game/pad.h"
#include "game/view.h"
#include "game/clock.h"
#include "game/root_node.h"

/*
 * Screen (include/game/screen.h): the base screen class (vtable 0x8006E878), a state machine run by
 * the display loop, with clock, pad and view.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* not in game/screen.h: each file that calls it reads the vtable through its own view of the slots */
ScreenVtbl *Screen_GetVtbl(void);
extern ScreenVtbl g_screenVtbl[]; /* Screen */

void Screen_Init(Screen *screen) {
    ScreenVtbl *vtbl;

    Object_GetBaseVtbl()->init(screen);
    vtbl = Screen_GetVtbl();
    screen->vtbl = vtbl;
    vtbl->reset(screen);
}

/* Dispatches on the sender's type, the low 4 bits of its vtable tag. */
void Screen_OnNotify(Screen *screen, Object *sender, s32 message) {
    s32 type;

    Object_GetBaseVtbl()->onNotify(screen, sender, message);
    type = sender->vtbl->classWord & 0xF;
    if (type == 1) {
        screen->vtbl->onDisplay(screen, sender, message);
    } else if (type == 2) {
        screen->vtbl->onPad(screen, sender, message);
    } else if (type == 5) {
        screen->vtbl->onClock(screen, sender, message);
    }
}

void Screen_Reset(Screen *screen) {
    screen->ticks = 0;
    screen->state = 0;
}

/* Slot 0x44: watches the env's objects, begins, then runs the display loop until state 3. */
void Screen_Run(Screen *screen, ScreenEnv *env, s32 noLoop) {
    ScreenVtbl *vtbl;
    View *view;
    SceneNode *root;
    void *object;           /* the clock, the root, then the view: each from env or made new */

    vtbl = screen->vtbl;
    object = env->clock;
    if (object == NULL) {
        object = Clock_Create();
    }
    screen->clock = object;
    object = env->root;
    if (object == NULL) {
        object = RootNode_Create();
    }
    screen->root = object;
    object = env->view;
    if (object == NULL) {
        object = View_New();
    }
    screen->view = object;
    screen->env = env;
    view = screen->view;
    vtbl->watch(screen, env->display);
    vtbl->watch(screen, env->pad);
    vtbl->watch(screen, screen->clock);
    vtbl->begin(screen, 0, 0, 0);
    screen->noLoop = noLoop;
    if (noLoop == 0) {
        view->vtbl->watch(view, env->display);
        view->vtbl->watch(view, screen->clock);
        root = screen->root;
        root->vtbl->watch(root, screen->clock);
        vtbl->setState(screen, SCREEN_START);
        vtbl->finish(screen);
    }
}

/* Ends, unwatches everything, deletes the clock, root and view it made itself. */
void Screen_Finish(Screen *screen) {
    ScreenVtbl *vtbl;
    View *view;
    SceneNode *root;
    SceneNode *ownRoot;
    Clock *clock;

    vtbl = screen->vtbl;
    vtbl->end(screen);
    view = screen->view;
    if (screen->noLoop == 0) {
        root = screen->root;
        root->vtbl->unwatch(root, screen->clock);
        view->vtbl->unwatch(view, screen->clock);
        view->vtbl->unwatch(view, screen->env->display);
    }
    vtbl->unwatch(screen, screen->clock);
    vtbl->unwatch(screen, screen->env->pad);
    vtbl->unwatch(screen, screen->env->display);
    if (screen->env->view != view) {
        screen->view = view->vtbl->delete_(view);
    }
    ownRoot = screen->root;
    if (screen->env->root != ownRoot) {
        screen->root = ownRoot->vtbl->delete_(ownRoot);
    }
    clock = screen->clock;
    if (screen->env->clock != clock) {
        screen->clock = clock->vtbl->delete_(clock);
    }
}

/* Each frame of the display: steps the clock, reads the pad and sends its codes. */
void Screen_OnDisplay(Screen *screen, Display *display, s32 message) {
    Clock *clock;
    Pad *pad;

    if (message == 2) {
        clock = screen->clock;
        clock->vtbl->step(clock);
        pad = screen->env->pad;
        pad->vtbl->read(pad);
        pad->vtbl->send(pad);
    }
}

void Screen_OnClock(Screen *screen) {
    screen->ticks++;
}

void Screen_SetState(Screen *screen, s32 state) {
    ScreenVtbl *vtbl = screen->vtbl;

    screen->state = state;
    vtbl->notify(screen, state);
    if (state == SCREEN_START) {
        vtbl->startLoop(screen);
    } else if (state == SCREEN_STOP) {
        vtbl->stopLoop(screen);
    }
}

void Screen_StartLoop(Screen *screen) {
    screen->ticks = 0;
    screen->env->display->vtbl->startLoop(screen->env->display);
}

void Screen_StopLoop(Screen *screen) {
    Display *display;

    display = screen->env->display;
    display->vtbl->stopLoop(display);
    screen->ticks = 0;
}

ScreenVtbl *Screen_GetVtbl(void) {
    return g_screenVtbl;
}

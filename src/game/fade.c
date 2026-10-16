#include "common.h"
#include "game/scene.h"
#include "game/fade.h"
#include "game/heap.h"
#include "game/box.h"

/*
 * Fade: the Box that fades a color over the screen (the view's overlay, the Place fader, the entity
 * effect). A 2D widget drawn by the scene tree (src/game/scene_draw.c).
 *
 * File boundaries: likely (docs/layout.md)
 */

/*
 * Box (vtable g_boxVtbl at 0x8006EAC0, class word 0x64, 0x6C bytes): a scene node holding a PSY-Q
 * GsBOXF at +0x58. The scene draw (Scene_DrawNode, kind 0x64) places it at +0x50, in percent of the
 * half screen when +0x48 is set, and sorts it with GsSortBoxFill at the priority +0x44.
 */
typedef struct BoxVtbl {
    u8 pad_00[0x8];
    void (*init)(void *box, s32 size, u8 *color, s32 priority); /* 0x08 Box_Construct */
    u8 pad_0C[0x40 - 0xC];
    void (*reset)(void *box, s32 size, s32 color, s32 priority); /* 0x40 Box_Init */
    u8 pad_44[0x4C - 0x44];
    void (*show)();                           /* 0x4C Box_Show (box, root, position) */
    u8 pad_50[0xB8 - 0x50];
    void (*setColor)(void *box, s32 copy, u8 *color); /* 0xB8 */
    void (*setPosition)(void *box, s32 position);    /* 0xBC */
    u8 pad_C0[0xCC - 0xC0];
    void (*setMask)(void *box, s32 bits);     /* 0xCC */
} BoxVtbl;

/* Fade, Label: include/game/scene.h */

extern u8 g_fadePalette[][3];
extern u8 g_fadeBlackPalette[3];    /* eight black RGB triples, read like g_fadePalette */
static FadeVtbl *Fade_GetVtbl(void);
extern u8 g_fadeVtbl[];

/* new Fade(size, channels, priority) */
void *Fade_Create(s32 size, s32 channels, s32 priority) {
    void *fade;

    fade = Heap_Alloc(0xA0);
    if (fade != NULL) {
        Fade_GetVtbl()->init(fade, size, channels, priority);
        return fade;
    }
    return NULL;
}

/* Slot 0x08: builds the Box with the channels' color, then sets the Fade vtable and runs slot 0x40 */
void Fade_Construct(void **fade, s32 size, s32 channels, s32 priority) {
    BoxVtbl *boxVtbl;
    u8 *color;
    FadeVtbl *vtbl;

    boxVtbl = Box_GetVtbl();
    if (channels != 0) {
        color = g_fadePalette[channels];
    } else {
        color = g_fadeBlackPalette;
    }
    boxVtbl->init(fade, size, color, priority);
    vtbl = Fade_GetVtbl();
    *fade = vtbl;
    vtbl->reset(fade, channels);
}

/* Slot 0x40: idle, step 10, hidden and opaque */
void Fade_Init(Fade *fade, s32 channels) {
    fade->defaultChannels = channels;
    fade->state = 0;
    fade->step.value = 0xA;
    fade->channels = 0;
    fade->unk_7C = 0;
    fade->vtbl->setVisible(fade, 0);
    fade->vtbl->setSemiTrans(fade, 0);
    fade->tint = 0;
}

/* Slot 0x98: on message 2 from the watched object, one step of the fade, or Fade_Stop at the end */
void Fade_Step(Fade *fade, s32 ticker, s32 message) {
    if (message == 2) {
        if (fade->remaining-- > 0) {
            if (fade->unk_7C != 9) {
                if (fade->channels & 4) {
                    fade->color.r += fade->step.low;
                }
                if (fade->channels & 2) {
                    fade->color.g += fade->step.low;
                }
                if (fade->channels & 1) {
                    fade->color.b += fade->step.low;
                }
            }
        } else {
            fade->vtbl->stop(fade);
        }
    }
}

/* Slot 0xD0 */
void Fade_SetStep(Fade *fade, s32 step) {
    fade->step.value = step;
}

/* Slot 0xD4: fade in, from the full color down to nothing (Place calls it when a stage starts) */
void Fade_StartIn(Fade *fade, s32 ticker, s32 channels, s32 arg3) {
    s32 index;
    if (fade->state == 0) {
        index = fade->vtbl->begin(fade, ticker, channels, arg3);
        fade->vtbl->setColor(fade, 1, g_fadePalette[index]);
        fade->state = 1;
        fade->step.value = -fade->step.value;
    }
}

/* Slot 0xD8: fade out, from black up to the color (Place_StartFade) */
void Fade_StartOut(Fade *fade, s32 ticker, s32 channels, s32 arg3) {
    if (fade->state == 0) {
        channels = fade->vtbl->begin(fade, ticker, channels, arg3);
        if (fade->tint != 0) {
            fade->remaining--;
        } else {
            fade->vtbl->setColor(fade, 1, &g_fadeBlackPalette[channels * 3]);
        }
        fade->state = 2;
    }
}

/*
 * Slot 0xDC: watches the ticker, sets the channels (0: all, black through blend mode 2, else
 * blend mode 1) and the tick count 0x100 / step, then shows the box semi-transparent.
 */
s32 Fade_Begin(Fade *fade, s32 ticker, s32 channels, s32 arg3) {
    FadeVtbl *vtbl;
    s32 index;
    s32 mode;
    s32 ticks;

    vtbl = fade->vtbl;
    index = channels;
    if (index < 0) {
        index = fade->defaultChannels;
    } else {
        fade->defaultChannels = index;
    }
    mode = 1;
    if (index != 0) {
        fade->channels = index;
    } else {
        mode = 2;
        fade->channels = 0xF;
    }
    fade->channels = index;
    if (index == 0) {
        fade->channels = 0xF;
    }
    ticks = 0x100 / fade->step.value;
    fade->unk_7C = arg3;
    fade->remaining = ticks;
    if (fade->tint != 0) {
        fade->remaining = ticks - ticks / fade->tintDivisor;
    }
    channels = fade->mask / fade->remaining;
    fade->unk_84 = channels;
    vtbl->watch(fade);
    vtbl->setSemiTrans(fade, 1);
    vtbl->setBlendMode(fade, mode);
    vtbl->setVisible(fade, 1);
    return index;
}

/* Slot 0xE0: stops watching the ticker and notifies 5 (fade in done) or 6 (fade out done) */
void Fade_Stop(Fade *fade, s32 ticker) {
    FadeVtbl *vtbl = fade->vtbl;
    s32 message;

    if (fade->state == 0) {
        return;
    }
    if (fade->state == 1) {
        message = 5;
        if (fade->tint == 0) {
            vtbl->setVisible(fade, 0);
            vtbl->setSemiTrans(fade, 0);
        }
    } else {
        message = 6;
        if (fade->tint != 0) {
            if (fade->channels == 0xF) {
                vtbl->setColor(fade, 1, g_fadeBlackPalette);
            }
            vtbl->setSemiTrans(fade, 0);
        }
    }
    vtbl->unwatch(fade, ticker);
    if (fade->step.value < 0) {
        fade->step.value = -fade->step.value;
    }
    fade->state = 0;
    vtbl->notify(fade, message);
}

/* Slot 0xE4: the color of the current channels */
u8 *Fade_GetColor(Fade *fade) {
    s32 channels = fade->channels;

    if (channels == 0xF) {
        return g_fadeBlackPalette;
    }
    return g_fadePalette[channels];
}

/* Slot 0xE8: saves the size and position, then sets new ones (size read as u16 halves) */
void Fade_SaveAndSetRect(Fade *fade, u16 *size, ScreenPoint *position) {
    if (fade->parent != 0) {
        fade->savedWidth.value = fade->width;
        fade->savedHeight.value = fade->height;
        fade->savedPosition = fade->position;
        fade->width = size[0];
        fade->height = size[2];
        fade->position = *position;
    }
}

/* Slot 0xEC */
void Fade_RestoreRect(Fade *fade) {
    fade->position = fade->savedPosition;
    fade->width = fade->savedWidth.half;
    fade->height = fade->savedHeight.half;
}

/* Slot 0xF0 */
void Fade_SetTint(Fade *fade, s32 tint, s32 tintDivisor) {
    fade->tint = tint;
    fade->tintDivisor = tintDivisor;
}

static FadeVtbl *Fade_GetVtbl(void) {
    return (FadeVtbl *)g_fadeVtbl;
}

#include "common.h"
#include "game/pad.h"
#include "game/heap.h"
#include "psyq/libetc.h"

/*
 * The pad (vtable g_padVtbl, 0x20 bytes, made by Pad_New; main makes one for the scene):
 * it reads PadRead once per frame and sends one event code per button through Object_Notify
 * (sender type 2 of include/game/screen.h). Code = state + button index, the button order is the
 * mask table g_padButtonMasks (docs/discoveries.md, the erase combo: 0 UP ... 15 START).
 *
 * File boundaries: proven (docs/layout.md)
 */

s32 g_padCount;
static PadVtbl *Pad_GetVtbl(void);
extern s32 g_padButtonMasks[16];
extern PadVtbl g_padVtbl;

Pad *Pad_New(s32 padInitMode, s32 padId) {
    Pad *pad;

    pad = Heap_Alloc(0x20);
    if (pad != NULL) {
        Pad_GetVtbl()->init(pad, padInitMode, padId);
        return pad;
    }
    return NULL;
}

/* The first pad made calls PadInit, the last one deleted PadStop (g_padCount counts them). */
void Pad_Init(Pad *pad, s32 padInitMode, s32 padId) {
    PadVtbl *vtbl;
    s32 count;

    Object_GetBaseVtbl()->init(pad);
    vtbl = Pad_GetVtbl();
    count = g_padCount;
    pad->vtbl = vtbl;
    g_padCount = count + 1;
    if (count == 0) {
        PadInit(padInitMode);
    }
    pad->vtbl->reset(pad, padId);
}

void Pad_Destroy(Pad *pad) {
    if (--g_padCount == 0) {
        PadStop();
    }
    Object_GetBaseVtbl()->destroy(pad);
}

void Pad_Reset(Pad *pad, s32 padId) {
    s32 id = padId != 0;
    pad->padId = id;
    pad->held = 0;
    pad->released = 0;
    pad->pressed = 0;
    pad->vtbl->initButtons(pad, id);
}

void Pad_Read(Pad *pad) {
    s32 now;
    s32 before;
    s32 changed;

    now = PadRead(pad->padId);
    before = pad->held;
    pad->held = now;
    changed = now ^ before;
    pad->released = changed & before;
    pad->pressed = changed & now;
}

/* One code per button: released wins over pressed, pressed over held; sent from button 15 down to 0. */
void Pad_SendEvents(Pad *pad) {
    void (*notify)(void *, s32);
    s32 codes[16];
    s32 *out;
    s32 i;
    s32 state;
    s32 mask;
    s32 held;
    s32 released;
    s32 pressed;

    held = pad->held;
    released = pad->released;
    pressed = pad->pressed;
    if (held != 0 || released != 0 || pressed != 0) {
        out = codes;
        for (i = 0; i < 16; i++) {
            mask = g_padButtonMasks[i];
            state = -1;
            if (released & mask) {
                state = PAD_RELEASED;
            } else if (pressed & mask) {
                state = PAD_PRESSED;
            } else if (held & mask) {
                state = PAD_HELD;
            }
            if (state >= 0) {
                *out++ = state + i;
            }
        }
        out--;
        notify = pad->vtbl->notify;
        while (out >= codes) {
            notify(pad, *out);
            out--;
        }
    }
}

void Pad_EmptySlot4C(void) {
}

/* The PadRead bit of each button index (docs/discoveries.md, the erase combo). */
void Pad_InitButtons(void) {
    s32 *dst = g_padButtonMasks;
    s32 masks[16] = {
        0x1000, 0x4000, 0x8000, 0x2000, /* UP, DOWN, LEFT, RIGHT */
        0x10, 0x40, 0x80, 0x20,         /* TRIANGLE, CROSS, SQUARE, CIRCLE */
        0x200, 0x400, 0x100, 0x8,       /* L3, R3, SELECT, R1 (PSY-Q pad bits) */
        0x2, 0x4, 0x1, 0x800,           /* R2, L1, L2, START */
    };
    s32 i;

    for (i = 0; i < 16; i++) {
        *dst++ = masks[i];
    }
}

void Pad_EmptySlot54(void) {
}

static PadVtbl *Pad_GetVtbl(void) {
    return &g_padVtbl;
}

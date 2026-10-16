#include "common.h"
#include "game/heap.h"

/*
 * The pad (vtable g_padVtbl, 0x20 bytes, made by Pad_New; main makes one for the scene):
 * it reads PadRead once per frame and sends one event code per button through Object_Notify
 * (sender type 2 of include/game/scene.h). Code = state + button index, the button order is the
 * mask table g_padButtonMasks (docs/discoveries.md, the erase combo: 0 UP ... 15 START).
 */

/* The states of an event code. */
#define PAD_HELD 2
#define PAD_PRESSED 0x12  /* down this frame */
#define PAD_RELEASED 0x22 /* up this frame */

/* Every slot of g_padVtbl past Object's (0x00 to 0x3C). */
typedef struct PadClassVtbl {
    s32 tag;               /* 0x00 2 */
    void *(*delete_)();    /* 0x04 Object_Delete */
    void (*init)();        /* 0x08 Pad_Init (pad, padInitMode, padId) */
    void (*destroy)();     /* 0x0C Pad_Destroy */
    u8 pad_10[0x30 - 0x10];
    void (*notify)();      /* 0x30 Object_Notify: sends one code */
    u8 pad_34[0x40 - 0x34];
    void (*reset)();       /* 0x40 Pad_Reset (pad, padId) */
    void (*read)();        /* 0x44 Pad_Read */
    void (*send)();        /* 0x48 Pad_SendEvents */
    void (*unk4C)();       /* 0x4C func_80025E14, empty */
    void (*initButtons)(); /* 0x50 Pad_InitButtons */
    void (*unk54)();       /* 0x54 func_80025E94, empty */
} PadClassVtbl;

typedef struct PadObject {
    PadClassVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s16 padId;   /* 0x0C PadRead's argument, 0 or 1 */
    u8 pad_0E[0x10 - 0x0E];
    s32 held;    /* 0x10 the last PadRead */
    s32 released; /* 0x14 bits that went up this frame */
    s32 pressed; /* 0x18 bits that went down this frame */
} PadObject;

extern s32 PadRead(u16);
void PadStop(void);
ObjectVtbl *Object_GetBaseVtbl(void);
s32 g_padCount;
s32 Heap_Alloc(s32);
PadClassVtbl *Pad_GetVtbl(void);
extern s32 g_padButtonMasks[16];
void PadInit(s32);
extern PadClassVtbl g_padVtbl;

s32 Pad_New(s32 padInitMode, s32 padId) {
    s32 pad;

    pad = Heap_Alloc(0x20);
    if (pad != 0) {
        Pad_GetVtbl()->init(pad, padInitMode, padId);
        return pad;
    }
    return 0;
}

/* The first pad made calls PadInit, the last one deleted PadStop (g_padCount counts them). */
void Pad_Init(PadObject *pad, s32 padInitMode, s32 padId) {
    PadClassVtbl *vtbl;
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

void Pad_Destroy(PadObject *pad) {
    if (--g_padCount == 0) {
        PadStop();
    }
    Object_GetBaseVtbl()->destroy(pad);
}

void Pad_Reset(PadObject *pad, s32 padId) {
    s32 id = padId != 0;
    pad->padId = id;
    pad->held = 0;
    pad->released = 0;
    pad->pressed = 0;
    pad->vtbl->initButtons(pad, id);
}

void Pad_Read(PadObject *pad) {
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
void Pad_SendEvents(PadObject *pad) {
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

void func_80025E14(void) {
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

void func_80025E94(void) {
}

PadClassVtbl *Pad_GetVtbl(void) {
    return &g_padVtbl;
}

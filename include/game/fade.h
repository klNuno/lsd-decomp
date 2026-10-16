#ifndef GAME_FADE_H
#define GAME_FADE_H

#include "common.h"
#include "game/gs.h"
#include "game/display.h"

/*
 * Fade (vtable g_fadeVtbl at 0x8006E99C, class word 0x164, 0xA0 bytes, src/game/fade.c): a Box
 * that fades from or to a color. The color index is a 3-bit RGB channel mask (g_fadePalette: 1 blue,
 * 2 green, 4 red, 7 white); 0 means black and stores the mask 0xF. Each tick of the watched object
 * adds the step to the masked channels; at the end the fade notifies its watchers: 5 after a fade in,
 * 6 after a fade out. It is the view's 320 x 240 overlay (View +0xB0), the Place fader and the
 * Grey Man white flash (entity.h Entity.effect).
 */
typedef struct Fade Fade;

typedef struct FadeVtbl {
    u8 pad_00[0x4];
    void *(*delete_)();                       /* 0x04 Object_Delete */
    void (*init)(void *fade, s32 size, s32 channels, s32 priority); /* 0x08 Fade_Construct */
    u8 pad_0C[0x10 - 0xC];
    void (*watch)(Fade *fade);                /* 0x10 (fade, ticker) */
    void (*unwatch)(Fade *fade, s32 ticker);  /* 0x14 */
    u8 pad_18[0x30 - 0x18];
    void (*notify)(Fade *fade, s32 message);  /* 0x30 */
    u8 pad_34[0x40 - 0x34];
    void (*reset)(void *fade, s32 channels);  /* 0x40 Fade_Init */
    u8 pad_44[0x4C - 0x44];
    void (*show)();                           /* 0x4C Box_Show (fade, root, position) */
    void (*hide)();                           /* 0x50 */
    u8 pad_54[0x60 - 0x54];
    void (*setVisible)(Fade *fade, s32 visible);   /* 0x60 */
    void (*setSemiTrans)(Fade *fade, s32 on);      /* 0x64 */
    void (*setBlendMode)(Fade *fade, s32 mode);    /* 0x68 */
    u8 pad_6C[0xB8 - 0x6C];
    void (*setColor)(Fade *fade, s32 copy, u8 *color); /* 0xB8 */
    u8 pad_BC[0xD0 - 0xBC];
    void (*setStep)();                        /* 0xD0 Fade_SetStep (fade, step): 5, 6, 10 or 30 */
    void (*startIn)();                        /* 0xD4 Fade_StartIn (fade, ticker, channels, arg3) */
    void (*startOut)();                       /* 0xD8 Fade_StartOut (fade, ticker, channels, arg3) */
    s32 (*begin)(Fade *fade, s32 ticker, s32 channels, s32 arg3); /* 0xDC Fade_Begin */
    void (*stop)(void *fade);                 /* 0xE0 Fade_Stop (fade, ticker) */
    void *(*getColor)();                      /* 0xE4 Fade_GetColor */
    u8 pad_E8[0xF0 - 0xE8];
    s32 (*setTint)();                         /* 0xF0 Fade_SetTint (fade, tint, divisor) */
} FadeVtbl;

/* The step at +0x74 is an s32, read as its low byte by Fade_Step */
typedef union FadeStep {
    s32 value;
    u8 low;
} FadeStep;

/* A size saved by Fade_SaveAndSetRect as an s32 and read back by Fade_RestoreRect as a u16 */
typedef union FadeSaved {
    s32 value;
    u16 half;
} FadeSaved;

/* Fade messages to its watchers */
#define FADE_MSG_IN_DONE 5
#define FADE_MSG_OUT_DONE 6

struct Fade {
    FadeVtbl *vtbl;
    u8 pad_04[0xC - 0x4];
    s32 parent;             /* 0x0C */
    u8 pad_10[0x50 - 0x10];
    ScreenPoint position;   /* 0x50 */
    s32 attribute;          /* 0x58 */
    u16 x;                  /* 0x5C */
    u16 y;                  /* 0x5E */
    u16 width;              /* 0x60 */
    u16 height;             /* 0x62 */
    Color3 color;           /* 0x64 */
    u8 pad_67;
    s32 mask;               /* 0x68 */
    s32 state;              /* 0x6C 0 idle, 1 fading in, 2 fading out */
    s32 defaultChannels;    /* 0x70 used when Fade_Begin gets a negative index */
    FadeStep step;          /* 0x74 added to the channels each tick, 10 by default */
    s32 channels;           /* 0x78 */
    s32 unk_7C;             /* third argument of Fade_Begin: 9 holds the color */
    s32 remaining;          /* 0x80 ticks left */
    s32 unk_84;             /* mask / ticks */
    FadeSaved savedWidth;   /* 0x88 */
    FadeSaved savedHeight;  /* 0x8C */
    ScreenPoint savedPosition; /* 0x90 */
    s32 tint;               /* 0x98 set in flashbacks: the fade stops short and the color stays */
    s32 tintDivisor;        /* 0x9C the fade runs ticks - ticks / tintDivisor */
};

/* Functions of src/game/fade.c that other files call or reference (docs/naming.md, Prototypes) */
void *Fade_Create(s32 size, s32 channels, s32 priority);

#endif

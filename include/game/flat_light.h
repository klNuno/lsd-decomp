#ifndef GAME_FLAT_LIGHT_H
#define GAME_FLAT_LIGHT_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"

/*
 * A flat light: an Object of 0x20 bytes whose vtable is g_flatLightVtbl. It keeps the
 * light number of GsSetFlatLight, the light's direction vector and its RGB colour. The three
 * methods of the vtable (slots 0x40 to 0x48) store one of these and send them to the GPU.
 */
typedef struct FlatLight {
    Object object;     /* 0x00 vtable, watched, watchers */
    s32 lightId;       /* 0x0C light number, the first argument of GsSetFlatLight */
    Vec3 vector;       /* 0x10 direction, copied from s16 x, y, z */
    s8 colorR;         /* 0x1C */
    s8 colorG;         /* 0x1D */
    s8 colorB;         /* 0x1E */
} FlatLight;

/* The class vtable: the Object slots, then the flat light methods. */
typedef struct FlatLightVtbl {
    ObjectVtbl object;    /* 0x00 to 0x38, Object's slots (slot 0x08 is the class init) */
    s32 unk_3C;           /* 0x3C 0 */
    void (*setId)();      /* 0x40 stores the light number */
    void (*setColor)();   /* 0x44 optionally stores the colour, then sends the light */
    void (*setVector)();  /* 0x48 optionally stores the direction, then sends the light */
} FlatLightVtbl;

/* Functions of src/game/flat_light.c that other files call or reference (docs/naming.md, Prototypes) */
FlatLight *FlatLight_New(s32 lightId);

#endif

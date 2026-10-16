#include "common.h"
#include "game/heap.h"
#include "game/flat_light.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

/*
 * A flat light: an Object of 0x20 bytes whose vtable is g_flatLightVtbl. It keeps the
 * light number of GsSetFlatLight, the light's direction vector and its RGB colour. The three
 * methods of the vtable (slots 0x40 to 0x48) store one of these and send them to the GPU.
 */
typedef struct FlatLight {
    Object object;     /* 0x00 vtable, watched, watchers */
    s32 lightId;       /* 0x0C light number, the first argument of GsSetFlatLight */
    u8 vector[0xC];    /* 0x10 direction: three s32 words, copied from s16 x, y, z */
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

/* The third argument is the RGB bytes (slot 0x44) or the xyz words (slot 0x48), whichever the caller passes. */
void GsSetFlatLight(s32 lightId, void *vector, void *data);
static FlatLightVtbl *FlatLight_GetVtbl(void);
extern FlatLightVtbl g_flatLightVtbl;

/* Allocates a flat light for lightId and initializes it; returns 0 when the heap is full. */
s32 FlatLight_New(s32 lightId) {
    s32 flatLight;

    flatLight = Heap_Alloc(0x20);
    if (flatLight != 0) {
        FlatLight_GetVtbl()->object.init(flatLight, lightId);
        return flatLight;
    }
    return 0;
}

/* Class init: the base Object init, the vtable pointer, then the light number. */
void FlatLight_Init(void **object, s32 lightId) {
    FlatLightVtbl *vtbl;

    ((ObjectVtbl *)Object_GetBaseVtbl())->init(object);
    vtbl = FlatLight_GetVtbl();
    *object = vtbl;
    vtbl->setId(object, lightId);
}

/* Slot 0x40: stores the light number. */
void FlatLight_SetId(FlatLight *flatLight, s32 lightId) {
    flatLight->lightId = lightId;
}

/* Slot 0x44: when saveColor is not 0 the RGB colour is kept in the object; the light is sent either way. */
void FlatLight_SetColor(FlatLight *flatLight, s32 saveColor, s8 *rgb) {
    s32 r;
    s32 g;
    s32 b;

    if (saveColor != 0) {
        r = rgb[0];
        g = rgb[1];
        b = rgb[2];
        flatLight->colorR = r;
        flatLight->colorG = g;
        flatLight->colorB = b;
    }
    GsSetFlatLight(flatLight->lightId, flatLight->vector, rgb);
}

/* Slot 0x48: when saveVector is not 0 the s16 x, y, z are kept as s32 words; the light is sent either way. */
void FlatLight_SetVector(FlatLight *flatLight, s32 saveVector, s16 *xyz) {
    if (saveVector != 0) {
        *(s32 *)&flatLight->vector[0] = xyz[0];
        *(s32 *)&flatLight->vector[4] = xyz[1];
        *(s32 *)&flatLight->vector[8] = xyz[2];
    }
    GsSetFlatLight(flatLight->lightId, flatLight->vector, xyz);
}

/* The vtable of the flat light class. */
static FlatLightVtbl *FlatLight_GetVtbl(void) {
    return &g_flatLightVtbl;
}

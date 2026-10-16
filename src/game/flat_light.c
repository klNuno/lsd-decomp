#include "common.h"
#include "game/heap.h"
#include "game/flat_light.h"
#include "psyq/libgs.h"

/*
 * File boundaries: proven (docs/layout.md)
 */

static FlatLightVtbl *FlatLight_GetVtbl(void);
extern FlatLightVtbl g_flatLightVtbl;

/* Allocates a flat light for lightId and initializes it; returns 0 when the heap is full. */
FlatLight *FlatLight_New(s32 lightId) {
    FlatLight *flatLight;

    flatLight = Heap_Alloc(0x20);
    if (flatLight != NULL) {
        FlatLight_GetVtbl()->object.init(flatLight, lightId);
        return flatLight;
    }
    return NULL;
}

/* Class init: the base Object init, the vtable pointer, then the light number. */
void FlatLight_Init(void **object, s32 lightId) {
    FlatLightVtbl *vtbl;

    Object_GetBaseVtbl()->init(object);
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
    GsSetFlatLight(flatLight->lightId, &flatLight->vector, rgb);
}

/* Slot 0x48: when saveVector is not 0 the s16 x, y, z are kept as s32 words; the light is sent either way. */
void FlatLight_SetVector(FlatLight *flatLight, s32 saveVector, s16 *xyz) {
    if (saveVector != 0) {
        flatLight->vector.x = xyz[0];
        flatLight->vector.y = xyz[1];
        flatLight->vector.z = xyz[2];
    }
    GsSetFlatLight(flatLight->lightId, &flatLight->vector, xyz);
}

/* The vtable of the flat light class. */
static FlatLightVtbl *FlatLight_GetVtbl(void) {
    return &g_flatLightVtbl;
}

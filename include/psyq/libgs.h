#ifndef PSYQ_LIBGS_H
#define PSYQ_LIBGS_H

#include "types.h"
#include "game/gs.h"

/*
 * LIBGS functions the game calls. Arguments the game types with its own structs (sprites, box
 * fills, backgrounds, object handlers, lights, views) are void *.
 */

/* Graphics system and display buffers */
void GsInitGraph(u16 x, u16 y, u16 intmode, u16 dith, u16 vrammode);
void GsDefDispBuff(u16 x0, u16 y0, u16 x1, u16 y1);
void GsSwapDispBuff(void);
s32 GsGetActiveBuff(void);
void GsInit3D(void);
void GsSetNearClip(s32 nearZ);
void GsSetWorkBase(void *base);

/* Ordering tables */
void GsClearOt(s32 offset, s32 point, GsOT *ot);
void GsDrawOt(GsOT *ot);
void GsSortClear(u8 r, u8 g, u8 b, GsOT *ot);
void GsSortBg(void *bg, void *ot, u16 pri);
void GsSortBoxFill(void *box, void *ot, u16 pri);
void GsSortSprite(void *sp, void *ot, u16 pri);

/* Coordinates, matrices, view and lights */
void GsInitCoordinate2(Coord2 *super, Coord2 *coord);
void GsGetLs(Coord2 *coord, Matrix *ls);
void GsGetLws(Coord2 *coord, Matrix *lw, Matrix *ls);
void GsSetLsMatrix(Matrix *m);
void GsSetLightMatrix(Matrix *m);
void GsSetRefView2(void *view);
void GsSetLightMode(s32 mode);
void GsSetAmbient(s32 r, s32 g, s32 b);
/* data: the RGB bytes or the xyz words, whichever flat_light.c passes (its slots 0x44 and 0x48) */
void GsSetFlatLight(s32 id, void *vector, void *data);

/* Models and images */
void GsMapModelingData(u32 *p);
void GsLinkObject4(u32 *tmd, void *obj, s32 n);
void GsGetTimInfo(u32 *im, void *tim);

/* LIBGS commons the game reads: the light mode GsSetLightMode sets, and the next free byte of
 * the packet buffer that GsSetWorkBase sets and the sort functions advance. */
extern s32 GsLIGHT_MODE;
extern u8 *GsOUT_PACKET_P;

#endif

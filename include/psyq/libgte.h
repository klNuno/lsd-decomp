#ifndef PSYQ_LIBGTE_H
#define PSYQ_LIBGTE_H

#include "types.h"
#include "game/gs.h"

/*
 * LIBGTE functions the game calls (the inline GTE macros are in gte.h). Vector arguments the game
 * passes through several struct views are void *.
 */

void SetGeomScreen(s32 h);
void SetFarColor(u8 r, u8 g, u8 b);
void SetFogNear(s32 a, s32 h);

void RotMatrix(void *r, Matrix *m);
void MulMatrix2(void *m0, void *m1);
void ApplyMatrixLV(void *m, void *v0, void *v1);
void ApplyMatrixSV(Matrix *m, void *v0, void *v1);
void OuterProduct0(void *v0, void *v1, void *v2);
void Square0(void *v0, void *v1);
s32 SquareRoot0(s32 a);
s32 ratan2(s32 y, s32 x);

/* Clip and draw one TMD primitive: the next primitive and the packet area, as render.c uses them. */
void *RCpolyF3(void *primtop, void *packet);
void *RCpolyF4(void *primtop, void *packet);
void *RCpolyFT3(void *primtop, void *packet);
void *RCpolyFT4(void *primtop, void *packet);
void *RCpolyG3(void *primtop, void *packet);
void *RCpolyG4(void *primtop, void *packet);
void *RCpolyGT3(void *primtop, void *packet);
void *RCpolyGT4(void *primtop, void *packet);

#endif

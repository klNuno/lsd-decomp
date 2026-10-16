#ifndef GAME_GS_H
#define GAME_GS_H

#include "common.h"

/*
 * PSY-Q libgs and libgte structures as the game reads them. Every scene node, model, entity, map tile
 * and DreamSys has a GsCOORDINATE2 at +0x14 (SceneNode_Init allocates it with its GsCOORD2PARAM);
 * GsGetLw leaves the world matrix and position in workm and workT.
 */

/* PSY-Q SVECTOR */
typedef struct SVector {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVector;

/* PSY-Q VECTOR without its pad: a position, x, y (height), z */
typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

/* An RGB triple, copied whole (0x80 is neutral for GsBG and sprites). */
typedef struct Color3 {
    u8 r;
    u8 g;
    u8 b;
} Color3;

/* PSY-Q GsCOORD2PARAM, 0x28 bytes. */
typedef struct Coord2Param {
    s32 scale[4];           /* 0x00 VECTOR, 4096 = 1.0 (SceneNode_SetScale) */
    union {
        SVector vec;        /* copied whole (SceneNode_SetRotation, func_8001D4DC) */
        s16 axis[4];        /* per axis; [1] is the yaw of a map tile (StageMap_BuildTiles) */
    } rotate;               /* 0x10 SVECTOR, 4096 = 360 degrees */
    Vec3 trans;             /* 0x18 VECTOR */
    s32 pad_24;
} Coord2Param;

/* PSY-Q MATRIX: the rotation m (4.12), then the translation t at 0x14. */
typedef struct Matrix {
    s16 m[3][3];            /* 0x00 */
    u8 pad_12[0x14 - 0x12];
    Vec3 t;                 /* 0x14 */
} Matrix;

/* PSY-Q GsCOORDINATE2, 0x50 bytes. */
typedef struct Coord2 {
    s32 flg;                /* 0x00 cleared after each change so libgs recomputes the matrix */
    Matrix coord;           /* 0x04 local matrix; coord.t is the position relative to the parent */
    Matrix workm;           /* 0x24 world matrix; workm.t is the world position GsGetLw leaves there */
    Coord2Param *param;     /* 0x44 */
    struct Coord2 *super;   /* 0x48 the parent's coordinate */
    struct Coord2 *sub;     /* 0x4C */
} Coord2;

/* PSY-Q GsOT, the ordering table header. */
typedef struct GsOT {
    u32 length;  /* log2 of the entry count */
    void *org;   /* the entries */
    u32 offset;
    u32 point;
    void *tag;
} GsOT;

#endif

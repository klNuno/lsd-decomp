#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "common.h"
#include "game/gs.h"

/* The scene node's model reference: same layout as the coordinate system that
   Scene_DrawNode passes to GsGetLs, and the model's vertex, normal and primitive tables */
typedef struct TmdModel {
    u8 *vertices;
    s32 vertexCount;         /* ModelEntry.vertexCount, not read by the renderer */
    u8 *normals;
    s32 normalCount;         /* ModelEntry.normalCount, not read by the renderer */
    u8 *primitives;          /* groups: u16 count, u16 type, then count faces */
    s32 primitiveCount;
} TmdModel;
typedef struct TmdObject {
    u32 attribute;           /* bit 31 skips the object; bits 3-4, 5, 6, 9-11 read below */
    Coord2 *coord;
    TmdModel *model;
} TmdObject;

/* Functions of src/game/render.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/render.c */
struct TmdCtx;
void Render_SortModel(TmdObject *object, GsOT *ot, s32 shift, struct TmdCtx *scratch);

#endif

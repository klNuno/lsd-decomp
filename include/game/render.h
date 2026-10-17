#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "common.h"
#include "game/gs.h"
#include "game/model_object.h"

/* The first three words of a GsDOBJ2 (libgs): the part of a scene node (SceneNode.object) and of
   a map tile that Render_SortModel reads. The renderer walks the TMD object's vertex, normal and
   primitive tables byte by byte (primitive groups: u16 count, u16 type, then count faces). */
typedef struct DObj2 {
    u32 attribute;           /* bit 31 skips the object; bits 3-4, 5, 6, 9-11 read below */
    Coord2 *coord;
    ModelEntry *tmd;
} DObj2;

/* Functions of src/game/render.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/render.c */
struct TmdCtx;
void Render_SortModel(DObj2 *object, GsOT *ot, s32 shift, struct TmdCtx *scratch);

#endif

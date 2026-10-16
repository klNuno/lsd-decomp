#include "common.h"
#include "gte.h"
#include "game/gs.h"
#include "game/render.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

s32 g_clipDivisionForced; /* Render_ForceClipDivision: when set, g_clipForcedDivision replaces the attribute's bits 9-11 */
s32 g_clipForcedDivision;

/*
 * The model renderer (Render_SortModel to the end): Scene_DrawNode calls Render_SortModel for each
 * scene node with its ordering table, an OT shift and the scratchpad at 0x1F800000 as work
 * area (TmdCtx). It walks the model's primitive groups (u16 count, u16 type), projects each
 * face with the GTE, culls it, writes one GPU packet per face and links it into the ordering
 * table. A face whose screen box exceeds 256 pixels, or that the GTE flags 0x40000, goes to
 * the Sony clipper RCpoly* instead, through the work areas g_clipTriWork (triangles) and
 * g_clipQuadWork (quads).
 */
extern s32 g_renderUnlit; /* attribute bit 6: sets packet code bit 0 (no texture shading) */
typedef struct Rgbc { u8 r, g, b, cd; } Rgbc;
typedef struct Bytes8 { u8 b[8]; } Bytes8;
typedef struct ScreenXY { s16 x; s16 y; } ScreenXY;
typedef struct TmdRgb { s8 r, g, b; } TmdRgb;

/* The first 8 bytes of every GPU packet: OT tag (word count in byte 3), colour, code in byte 7 */
typedef struct PrimHeader {
    u8 pad_00[3];
    u8 len;
    u8 pad_04[3];
    u8 code;
} PrimHeader;

/* One 0x18-byte vertex of a clipper work area, filled from the face before RCpoly* runs */
typedef struct ClipVertex {
    Bytes8 pos;    /* copy of the model vertex */
    u16 uv;
    u16 unk_0A;
    Rgbc rgb;
    Rgbc sxy;      /* copy of the packet's screen xy */
    u8 sz[4];      /* written by gte_stsz3 / gte_stsz4 */
} ClipVertex;

/* Header of a clipper work area (g_clipTriWork, g_clipQuadWork), filled by Render_FillClipHeader */
typedef struct ClipHeader {
    s32 division;  /* g_clipForcedDivision when Render_ForceClipDivision set it, else attribute bits 9-11 */
    s32 width;     /* g_clipScreenWidth, 320 */
    s32 height;    /* g_clipScreenHeight, 240 */
    u16 clut;      /* textured faces only */
    u16 tpage;
    Rgbc rgb;
    s32 otEntry;
} ClipHeader;

/* The work area at the scratchpad, one per call of Render_SortModel */
typedef struct TmdCtx {
    s32 *ot;                 /* 0x00 ordering table base */
    s32 shift;               /* 0x04 otz >> shift picks the OT entry */
    s32 unk_08;              /* 0x08 set to 10 */
    u8 *vertices;            /* 0x0C model vertices, 8 bytes each */
    u8 *normals;             /* 0x10 model normals, 8 bytes each */
    u8 primLen;              /* 0x14 packet word count, restored by Render_TransformTri */
    u8 primCode;             /* 0x15 packet code with the flag bits of Render_SetPrimFlags */
    u8 pad_16[2];
    u32 type;                /* 0x18 group type, & 0xFD07 */
    s32 semiTrans;           /* 0x1C group type bit 9: packet code bit 1 */
    s32 otz;                 /* 0x20 */
    s32 depth;               /* 0x24 depth cue; >= 0x1000 culls, also shifts the CLUT row */
    s32 nclip;               /* 0x28 <= 0 culls (back face) */
    s32 depthShift;          /* 0x2C 9 or 16 */
    union {
        s32 *s;
        u32 *u;
        s32 addr;
    } otEntry;               /* 0x30 &ot[otz >> shift] */
    TmdRgb baseRgb;          /* 0x34 g_texturedRgb, light colour of the textured groups */
    Matrix savedRot;      /* 0x38 */
    u8 pad_58[4];
    s32 gteFlag;             /* 0x5C */
    union {
        s32 word[4];
        ScreenXY pt[4];
    } sxy;                   /* 0x60 projected corners */
    ScreenXY min;            /* 0x70 screen box of the face */
    ScreenXY max;            /* 0x74 */
    s32 clip;                /* 0x78 1: the face goes through RCpoly* */
    u8 pad_7C[0x88 - 0x7C];
    union {
        u8 *b[3];
        ClipVertex *v[3];
    } triClip;               /* 0x88 vertices of g_clipTriWork */
    union {
        u8 *b[4];
        ClipVertex *v[4];
    } quadClip;              /* 0x94 vertices of g_clipQuadWork */
    u8 *src[4];              /* 0xA4 the face's model vertices */
} TmdCtx;

/* GPU packets, laid out by their code byte (0x20 F3 ... 0x3C GT4, set in Render_SortModel) */
typedef struct PolyG3 {
    u32 tag;
    Rgbc c0;
    u32 xy0;
    Rgbc c1;
    u32 xy1;
    Rgbc c2;
    u32 xy2;
} PolyG3;
typedef struct PolyFT3 {
    u32 tag;
    s32 rgbc;
    s32 xy0;
    u16 uv0;
    u16 clut;
    s32 xy1;
    u16 uv1;
    u16 tpage;
    s32 xy2;
    u16 uv2;
    u16 pad1;
} PolyFT3;
typedef struct PolyG4 {
    u32 tag;
    Rgbc c0;
    s16 x0, y0;
    Rgbc c1;
    s16 x1, y1;
    Rgbc c2;
    s16 x2, y2;
    Rgbc c3;
    s16 x3, y3;
} PolyG4;
typedef struct PolyFT4 {
    u32 tag;
    s32 rgbc;
    s32 xy0;
    u16 uv0;
    u16 clut;
    s32 xy1;
    u16 uv1;
    u16 tpage;
    s32 xy2;
    u16 uv2;
    u16 pad1;
    s32 xy3;
    u16 uv3;
} PolyFT4;
typedef struct PolyGT3 {
    u32 tag;
    Rgbc c0;
    s32 xy0;
    u16 uv0;
    u16 clut;
    Rgbc c1;
    s32 xy1;
    u16 uv1;
    u16 tpage;
    Rgbc c2;
    s32 xy2;
    u16 uv2;
    u16 pad2;
} PolyGT3;
typedef struct PolyGT4 {
    u32 tag;
    Rgbc c0;
    s32 xy0;
    u16 uv0;
    u16 clut;
    Rgbc c1;
    s32 xy1;
    u16 uv1;
    u16 tpage;
    Rgbc c2;
    s32 xy2;
    u16 uv2;
    u16 pad2;
    Rgbc c3;
    s32 xy3;
    u16 uv3;
    u16 pad3;
} PolyGT4;

/* The scene node's model reference: same layout as the coordinate system that
   Scene_DrawNode passes to GsGetLs, and the model's vertex, normal and primitive tables */
typedef struct TmdModel {
    u8 *vertices;
    s32 vertexCount;         /* TmdObjectEntry.vertexCount, not read by the renderer */
    u8 *normals;
    s32 normalCount;         /* TmdObjectEntry.normalCount, not read by the renderer */
    u8 *primitives;          /* groups: u16 count, u16 type, then count faces */
    s32 primitiveCount;
} TmdModel;
typedef struct TmdObject {
    u32 attribute;           /* bit 31 skips the object; bits 3-4, 5, 6, 9-11 read below */
    Coord2 *coord;
    TmdModel *model;
} TmdObject;
typedef struct TmdOt {
    u32 unk_00;
    s32 *org;
} TmdOt;

/* Views of triClip, quadClip and src for Render_CopyClipTri and Render_CopyClipQuad */
typedef struct ClipRefs { ClipVertex *v[4]; } ClipRefs;

extern u8 g_clipTriWork[];
extern u8 g_clipQuadWork[];
extern void *RCpolyF3(void *, void *);
extern void *RCpolyF4(void *, void *);
extern void *RCpolyFT3(void *, void *);
extern void *RCpolyFT4(void *, void *);
extern void *RCpolyG3(void *, void *);
extern void *RCpolyG4(void *, void *);
extern void *RCpolyGT3(void *, void *);
extern void *RCpolyGT4(void *, void *);
extern s32 g_renderDivision;
s32 g_clipScreenWidth; /* 320 in .sdata, never written */
s32 g_clipScreenHeight; /* 240 in .sdata, never written */
static void Render_FillClipHeader(ClipHeader *header, TmdCtx *ctx, Rgbc *rgb, s32 textured, u16 clut, u16 tpage);
static void Render_CopyClipTri(void *dst, void *src, void *sxy0, void *sxy1, void *sxy2);
static void Render_CopyClipQuad(void *dst, void *src, void *sxy0, void *sxy1, void *sxy2, void *sxy3);
static s32 Render_TransformTri(u8 *prim, TmdCtx *ctx);
static void Render_CheckScreenBox(TmdCtx *ctx, s32 count);
static void Render_SetPrimFlags(PrimHeader *prim, TmdCtx *ctx);
static s32 Render_ProjectTri(u8 *prim, TmdCtx *ctx, u16 i0, u16 i1, u16 i2, void (*storeXy)(u8 *));
static s32 Render_ProjectQuad(u8 *prim, TmdCtx *ctx, u16 i0, u16 i1, u16 i2, u16 i3, void (*storeXy)(u8 *, s32));
static void Render_StoreXyF3(void *prim);
static void Render_StoreXyG3(void *prim);
static void Render_StoreXyFT3(void *prim);
static void Render_StoreXyGT3(void *prim);
static void Render_StoreXyF4(u8 *prim, s32 firstThree);
static void Render_StoreXyG4(u8 *prim, s32 firstThree);
static void Render_StoreXyFT4(u8 *prim, s32 firstThree);
static void Render_StoreXyGT4(u8 *prim, s32 firstThree);
static void *Render_AddPolyF3(u8 *prim, TmdCtx *ctx);
static void *Render_AddPolyG3(PolyG3 *prim, TmdCtx *ctx);
static void *Render_AddPolyFT3(PolyFT3 *prim, TmdCtx *ctx);
static void *Render_AddPolyF4(u32 *prim, TmdCtx *ctx);
static void *Render_AddPolyG4(PolyG4 *prim, TmdCtx *ctx);
static void *Render_AddPolyFT4(PolyFT4 *prim, TmdCtx *ctx);
static void *Render_AddPolyGT3(PolyGT3 *prim, TmdCtx *ctx);
static void *Render_AddPolyGT4(PolyGT4 *prim, TmdCtx *ctx);
static void Render_InitClipSlots(u8 **slots, u8 *area, s32 count);
extern s32 D_8008E250; /* attribute bit 5 */
extern s32 D_8008E24C; /* attribute bits 3-4 */
extern s32 D_800902E0;
extern u8 *g_packetCursor; /* next free byte of the packet buffer, set by the psyq func_8003FBE4 */
extern TmdRgb g_texturedRgb; /* {0x80, 0x80, 0x80} in .sdata */

/* Sorts one model into the ordering table (called by Scene_DrawNode for each scene node) */
void Render_SortModel(TmdObject *object, TmdOt *ot, s32 shift, TmdCtx *scratch) {
    TmdCtx *ctx;
    u8 *prim;
    u8 *packet;
    s32 remaining;
    s32 count;

    if ((s32)object->attribute < 0) {
        return;
    }
    ctx = scratch;
    ctx->ot = ot->org;
    ctx->shift = shift;
    Render_InitClipSlots(ctx->triClip.b, g_clipTriWork, 3);
    Render_InitClipSlots(ctx->quadClip.b, g_clipQuadWork, 4);
    remaining = object->model->primitiveCount;
    packet = object->model->primitives;
    ctx->vertices = object->model->vertices;
    ctx->normals = object->model->normals;
    if (object->coord->super != NULL) {
        gte_ReadRotMatrix(&ctx->savedRot);
        gte_MulMatrix0(&object->coord->super->workm, &object->coord->workm, &object->coord->workm);
        gte_SetRotMatrix(&ctx->savedRot);
    }
    g_renderDivision = (object->attribute >> 9) & 7;
    g_renderUnlit = (object->attribute >> 6) & 1;
    D_8008E250 = (object->attribute >> 5) & 1;
    D_8008E24C = (object->attribute >> 3) & 3;
    ctx->unk_08 = 10;
    ctx->baseRgb = g_texturedRgb;
    if ((D_8008E250 != 0 && D_800902E0 != 0) || D_8008E24C != 0) {
        ctx->depthShift = 9;
    } else {
        ctx->depthShift = 16;
    }
    while (remaining != 0) {
        prim = g_packetCursor;
        ctx->type = *(u16 *)(packet + 2) & 0xFD07;
        count = *(u16 *)packet;
        ctx->semiTrans = (*(u32 *)packet >> 25) & 1;
        remaining -= count;
        switch (ctx->type) {
        case 0x2000:
            prim[3] = 4;
            prim[7] = 0x20;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectTri(prim, (void *)ctx, *(u16 *)(packet + 0xA), *(u16 *)(packet + 0xC), *(u16 *)(packet + 0xE), Render_StoreXyF3) == 0) {
                    gte_ldv0(ctx->normals + *(u16 *)(packet + 8) * 8);
                    gte_ldrgb(packet + 4);
                    gte_ncds();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyF3(prim, (void *)ctx);
                }
                packet += 0x10;
                count--;
            } while (count != 0);
            break;
        case 0x2004:
            prim[3] = 6;
            prim[7] = 0x30;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectTri(prim, (void *)ctx, *(u16 *)(packet + 0x12), *(u16 *)(packet + 0x14), *(u16 *)(packet + 0x16), Render_StoreXyG3) == 0) {
                    gte_ldv0(ctx->normals + *(u16 *)(packet + 0x10) * 8);
                    gte_ldrgb(packet + 4);
                    gte_ncds();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    gte_ldrgb(packet + 8);
                    gte_ncds();
                    gte_strgb(prim + 0xC);
                    gte_ldrgb(packet + 0xC);
                    gte_ncds();
                    gte_strgb(prim + 0x14);
                    prim = Render_AddPolyG3((void *)prim, (void *)ctx);
                }
                packet += 0x18;
                count--;
            } while (count != 0);
            break;
        case 0x2101:
            prim[3] = 4;
            prim[7] = 0x20;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectTri(prim, (void *)ctx, *(u16 *)(packet + 8), *(u16 *)(packet + 0xA), *(u16 *)(packet + 0xC), Render_StoreXyF3) == 0) {
                    gte_ldrgb(packet + 4);
                    gte_dpcs();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyF3(prim, (void *)ctx);
                }
                packet += 0x10;
                count--;
            } while (count != 0);
            break;
        case 0x2400:
            prim[3] = 7;
            prim[7] = 0x24;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            gte_ldrgb(&ctx->baseRgb);
            do {
                if (Render_ProjectTri(prim, (void *)ctx, *(u16 *)(packet + 0x12), *(u16 *)(packet + 0x14), *(u16 *)(packet + 0x16), Render_StoreXyFT3) == 0) {
                    *(s32 *)(prim + 0xC) = *(s32 *)(packet + 4);
                    *(s32 *)(prim + 0x14) = *(s32 *)(packet + 8);
                    *(s32 *)(prim + 0x1C) = *(s32 *)(packet + 0xC);
                    *(u16 *)(prim + 0xE) += (ctx->depth >> ctx->depthShift) << 6;
                    gte_ldv0(ctx->normals + *(u16 *)(packet + 0x10) * 8);
                    gte_ncds();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyFT3((void *)prim, (void *)ctx);
                }
                packet += 0x18;
                count--;
            } while (count != 0);
            break;
        case 0x2501:
            prim[3] = 7;
            prim[7] = 0x24;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectTri(prim, (void *)ctx, *(u16 *)(packet + 0x14), *(u16 *)(packet + 0x16), *(u16 *)(packet + 0x18), Render_StoreXyFT3) == 0) {
                    *(s32 *)(prim + 0xC) = *(s32 *)(packet + 4);
                    *(s32 *)(prim + 0x14) = *(s32 *)(packet + 8);
                    *(s32 *)(prim + 0x1C) = *(s32 *)(packet + 0xC);
                    *(u16 *)(prim + 0xE) += (ctx->depth >> ctx->depthShift) << 6;
                    gte_ldrgb(packet + 0x10);
                    gte_dpcs();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyFT3((void *)prim, (void *)ctx);
                }
                packet += 0x1C;
                count--;
            } while (count != 0);
            break;
        case 0x2800:
            prim[3] = 5;
            prim[7] = 0x28;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectQuad(prim, (void *)ctx, *(u16 *)(packet + 0xA), *(u16 *)(packet + 0xC), *(u16 *)(packet + 0xE), *(u16 *)(packet + 0x10), Render_StoreXyF4) == 0) {
                    gte_ldv0(ctx->normals + *(u16 *)(packet + 8) * 8);
                    gte_ldrgb(packet + 4);
                    gte_ncds();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyF4((void *)prim, (void *)ctx);
                }
                packet += 0x14;
                count--;
            } while (count != 0);
            break;
        case 0x2901:
            prim[3] = 5;
            prim[7] = 0x28;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectQuad(prim, (void *)ctx, *(u16 *)(packet + 8), *(u16 *)(packet + 0xA), *(u16 *)(packet + 0xC), *(u16 *)(packet + 0xE), Render_StoreXyF4) == 0) {
                    gte_ldrgb(packet + 4);
                    gte_dpcs();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyF4((void *)prim, (void *)ctx);
                }
                packet += 0x10;
                count--;
            } while (count != 0);
            break;
        case 0x2C00:
            prim[3] = 9;
            prim[7] = 0x2C;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            gte_ldrgb(&ctx->baseRgb);
            do {
                if (Render_ProjectQuad(prim, (void *)ctx, *(u16 *)(packet + 0x16), *(u16 *)(packet + 0x18), *(u16 *)(packet + 0x1A), *(u16 *)(packet + 0x1C), Render_StoreXyFT4) == 0) {
                    *(s32 *)(prim + 0xC) = *(s32 *)(packet + 4);
                    *(s32 *)(prim + 0x14) = *(s32 *)(packet + 8);
                    *(s32 *)(prim + 0x1C) = *(s32 *)(packet + 0xC);
                    *(s32 *)(prim + 0x24) = *(s32 *)(packet + 0x10);
                    *(u16 *)(prim + 0xE) += (ctx->depth >> ctx->depthShift) << 6;
                    gte_ldv0(ctx->normals + *(u16 *)(packet + 0x14) * 8);
                    gte_ncds();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyFT4((void *)prim, (void *)ctx);
                }
                packet += 0x20;
                count--;
            } while (count != 0);
            break;
        case 0x2D01:
            prim[3] = 9;
            prim[7] = 0x2C;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectQuad(prim, (void *)ctx, *(u16 *)(packet + 0x18), *(u16 *)(packet + 0x1A), *(u16 *)(packet + 0x1C), *(u16 *)(packet + 0x1E), Render_StoreXyFT4) == 0) {
                    *(s32 *)(prim + 0xC) = *(s32 *)(packet + 4);
                    *(s32 *)(prim + 0x14) = *(s32 *)(packet + 8);
                    *(s32 *)(prim + 0x1C) = *(s32 *)(packet + 0xC);
                    *(s32 *)(prim + 0x24) = *(s32 *)(packet + 0x10);
                    *(u16 *)(prim + 0xE) += (ctx->depth >> ctx->depthShift) << 6;
                    gte_ldrgb(packet + 0x14);
                    gte_dpcs();
                    gte_strgb(prim + 4);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyFT4((void *)prim, (void *)ctx);
                }
                packet += 0x20;
                count--;
            } while (count != 0);
            break;
        case 0x3101:
            prim[3] = 6;
            prim[7] = 0x30;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectTri(prim, (void *)ctx, *(u16 *)(packet + 0x10), *(u16 *)(packet + 0x12), *(u16 *)(packet + 0x14), Render_StoreXyG3) == 0) {
                    gte_ldrgb3c(packet + 4);
                    gte_dpct();
                    gte_strgb3_g3(prim);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyG3((void *)prim, (void *)ctx);
                }
                packet += 0x18;
                count--;
            } while (count != 0);
            break;
        case 0x3501:
            prim[3] = 9;
            prim[7] = 0x34;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectTri(prim, (void *)ctx, *(u16 *)(packet + 0x1C), *(u16 *)(packet + 0x1E), *(u16 *)(packet + 0x20), Render_StoreXyGT3) == 0) {
                    *(s32 *)(prim + 0xC) = *(s32 *)(packet + 4);
                    *(s32 *)(prim + 0x18) = *(s32 *)(packet + 8);
                    *(s32 *)(prim + 0x24) = *(s32 *)(packet + 0xC);
                    *(u16 *)(prim + 0xE) += (ctx->depth >> ctx->depthShift) << 6;
                    gte_ldrgb3(packet + 0x10, packet + 0x14, packet + 0x18);
                    gte_dpct();
                    gte_strgb3(prim + 4, prim + 0x10, prim + 0x1C);
                    prim[7] = ctx->primCode;
                    prim = Render_AddPolyGT3((void *)prim, (void *)ctx);
                }
                packet += 0x24;
                count--;
            } while (count != 0);
            break;
        case 0x3901:
            prim[3] = 8;
            prim[7] = 0x38;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectQuad(prim, (void *)ctx, *(u16 *)(packet + 0x14), *(u16 *)(packet + 0x16), *(u16 *)(packet + 0x18), *(u16 *)(packet + 0x1A), Render_StoreXyG4) == 0) {
                    gte_ldrgb3c(packet + 4);
                    gte_dpct();
                    gte_strgb3_g3(prim);
                    prim[7] = ctx->primCode;
                    gte_ldrgb(packet + 0x10);
                    gte_dpcs();
                    gte_strgb(prim + 0x1C);
                    prim = Render_AddPolyG4((void *)prim, (void *)ctx);
                }
                packet += 0x1C;
                count--;
            } while (count != 0);
            break;
        case 0x3D01:
            prim[3] = 12;
            prim[7] = 0x3C;
            Render_SetPrimFlags((void *)prim, (void *)ctx);
            do {
                if (Render_ProjectQuad(prim, (void *)ctx, *(u16 *)(packet + 0x24), *(u16 *)(packet + 0x26), *(u16 *)(packet + 0x28), *(u16 *)(packet + 0x2A), Render_StoreXyGT4) == 0) {
                    *(s32 *)(prim + 0xC) = *(s32 *)(packet + 4);
                    *(s32 *)(prim + 0x18) = *(s32 *)(packet + 8);
                    *(s32 *)(prim + 0x24) = *(s32 *)(packet + 0xC);
                    *(s32 *)(prim + 0x30) = *(s32 *)(packet + 0x10);
                    *(u16 *)(prim + 0xE) += (ctx->depth >> ctx->depthShift) << 6;
                    gte_ldrgb3(packet + 0x14, packet + 0x18, packet + 0x1C);
                    gte_dpct();
                    gte_strgb3(prim + 4, prim + 0x10, prim + 0x1C);
                    prim[7] = ctx->primCode;
                    gte_ldrgb(packet + 0x20);
                    gte_dpcs();
                    gte_strgb(prim + 0x28);
                    prim = Render_AddPolyGT4((void *)prim, (void *)ctx);
                }
                packet += 0x2C;
                count--;
            } while (count != 0);
            break;
        default:
            return;
        }
        g_packetCursor = prim;
    }
}

/* Packet code bits: 1 semi-transparent (group type bit 9), 0 no shading (attribute bit 6) */
static void Render_SetPrimFlags(PrimHeader *prim, TmdCtx *ctx) {
    if (ctx->semiTrans != 0) {
        prim->code |= 2;
    } else {
        prim->code &= ~2;
    }
    if (g_renderUnlit != 0) {
        prim->code |= 1;
    } else {
        prim->code &= ~1;
    }
    ctx->primLen = prim->len;
    ctx->primCode = prim->code;
}

/* Projects a triangle; 0 when it is drawn, 1 when culled */
static s32 Render_ProjectTri(u8 *prim, TmdCtx *ctx, u16 i0, u16 i1, u16 i2, void (*storeXy)(u8 *)) {
    u8 **v = ctx->src;
    v[0] = ctx->vertices + i0 * 8;
    v[1] = ctx->vertices + i1 * 8;
    v[2] = ctx->vertices + i2 * 8;
    gte_ldv3(v[0], v[1], v[2]);
    if (Render_TransformTri(prim, ctx) == 0) {
        gte_stsz3(ctx->triClip.b[0] + 0x14, ctx->triClip.b[1] + 0x14, ctx->triClip.b[2] + 0x14);
        storeXy(prim);
        Render_CheckScreenBox(ctx, 3);
        return 0;
    }
    return 1;
}

/* Projects a quad; 0 when it is drawn, 1 when culled (on its first three corners) */
static s32 Render_ProjectQuad(u8 *prim, TmdCtx *ctx, u16 i0, u16 i1, u16 i2, u16 i3, void (*storeXy)(u8 *, s32)) {
    u8 **v = ctx->src;
    v[0] = ctx->vertices + i0 * 8;
    v[1] = ctx->vertices + i1 * 8;
    v[2] = ctx->vertices + i2 * 8;
    v[3] = ctx->vertices + i3 * 8;
    gte_ldv3(v[0], v[1], v[2]);
    if (Render_TransformTri(prim, ctx) == 0) {
        storeXy(prim, 1);
        gte_ldv0(v[3]);
        gte_rtps();
        gte_stsz4(ctx->quadClip.b[0] + 0x14, ctx->quadClip.b[1] + 0x14, ctx->quadClip.b[2] + 0x14, ctx->quadClip.b[3] + 0x14);
        storeXy(prim, 0);
        gte_stsxy(&ctx->sxy.word[3]);
        Render_CheckScreenBox(ctx, 4);
        return 0;
    }
    return 1;
}

/* rtpt of the three loaded vertices; culls on a GTE error (except flag 0x40000, which asks
   for the clipper), a back face, or depth >= 0x1000; else picks the OT entry */
static s32 Render_TransformTri(u8 *prim, TmdCtx *ctx) {
    ctx->clip = 0;
    gte_rtpt();
    prim[3] = ctx->primLen;
    gte_stflg_4(&ctx->gteFlag);
    if (ctx->gteFlag != 0) {
        if (ctx->gteFlag != 0x40000) {
            return 1;
        }
        ctx->clip = 1;
    }
    gte_nclip();
    gte_stopz(&ctx->nclip);
    if (ctx->nclip <= 0) {
        return 1;
    }
    gte_stdp(&ctx->depth);
    if (ctx->depth >= 0x1000) {
        return 1;
    }
    gte_avsz3();
    gte_stotz(&ctx->otz);
    gte_stsxy3(&ctx->sxy.word[0], &ctx->sxy.word[1], &ctx->sxy.word[2]);
    ctx->otEntry.s = &ctx->ot[ctx->otz >> ctx->shift];
    return 0;
}

static void Render_StoreXyF3(void *prim) {
    gte_stsxy3_f3(prim);
}

static void Render_StoreXyG3(void *prim) {
    gte_stsxy3_g3(prim);
}

static void Render_StoreXyFT3(void *prim) {
    gte_stsxy3_ft3(prim);
}

static void Render_StoreXyGT3(void *prim) {
    gte_stsxy3_gt3(prim);
}

static void Render_StoreXyF4(u8 *prim, s32 firstThree) {
    if (firstThree != 0) {
        gte_stsxy3_f4(prim);
    } else {
        gte_stsxy(prim + 0x14);
    }
}

static void Render_StoreXyG4(u8 *prim, s32 firstThree) {
    if (firstThree != 0) {
        gte_stsxy3_g4(prim);
    } else {
        gte_stsxy(prim + 0x20);
    }
}

static void Render_StoreXyFT4(u8 *prim, s32 firstThree) {
    if (firstThree != 0) {
        gte_stsxy3_ft4(prim);
    } else {
        gte_stsxy(prim + 0x20);
    }
}

static void Render_StoreXyGT4(u8 *prim, s32 firstThree) {
    if (firstThree != 0) {
        gte_stsxy3_gt4(prim);
    } else {
        gte_stsxy(prim + 0x2C);
    }
}

/*
 * Render_AddPolyF3 to Render_AddPolyGT4 finish one face: through RCpoly* when ctx->clip is set,
 * else linked at the head of its OT entry (24-bit next pointer in the tag). They return the
 * next free byte of the packet buffer.
 */
static void *Render_AddPolyF3(u8 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipTriWork, ctx, prim + 4, 0, 0, 0);
        Render_CopyClipTri(ctx->triClip.v, ctx->src, prim + 8, prim + 0xC, prim + 0x10);
        return RCpolyF3(prim, g_clipTriWork);
    }
    *(s32 *)prim = (*(s32 *)prim & 0xFF000000) | (*ctx->otEntry.s & 0xFFFFFF);
    *ctx->otEntry.s = (*ctx->otEntry.s & 0xFF000000) | ((s32)prim & 0xFFFFFF);
    return prim + 0x14;
}

static void *Render_AddPolyG3(PolyG3 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipTriWork, ctx, &prim->c0, 0, 0, 0);
        Render_CopyClipTri(&ctx->triClip, &ctx->src, &prim->xy0, &prim->xy1, &prim->xy2);
        ctx->triClip.v[0]->unk_0A = prim->c1.cd;
        ctx->triClip.v[1]->unk_0A = prim->c1.cd;
        ctx->triClip.v[2]->unk_0A = prim->c2.cd;
        ctx->triClip.v[0]->rgb = prim->c0;
        ctx->triClip.v[1]->rgb = prim->c1;
        ctx->triClip.v[2]->rgb = prim->c2;
        return RCpolyG3(prim, g_clipTriWork);
    }
    prim->tag = (prim->tag & 0xFF000000) | (*ctx->otEntry.u & 0xFFFFFF);
    *ctx->otEntry.u = (*ctx->otEntry.u & 0xFF000000) | ((u32)prim & 0xFFFFFF);
    return prim + 1;
}

static void *Render_AddPolyFT3(PolyFT3 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipTriWork, ctx, &prim->rgbc, 1, prim->clut, prim->tpage);
        Render_CopyClipTri(&ctx->triClip, &ctx->src, &prim->xy0, &prim->xy1, &prim->xy2);
        ctx->triClip.v[0]->unk_0A = prim->pad1;
        ctx->triClip.v[1]->unk_0A = prim->pad1;
        ctx->triClip.v[2]->unk_0A = prim->pad1;
        ctx->triClip.v[0]->uv = prim->uv0;
        ctx->triClip.v[1]->uv = prim->uv1;
        ctx->triClip.v[2]->uv = prim->uv2;
        return RCpolyFT3(prim, g_clipTriWork);
    }
    prim->tag = (prim->tag & 0xFF000000) | (*ctx->otEntry.u & 0xFFFFFF);
    *ctx->otEntry.u = (*ctx->otEntry.u & 0xFF000000) | ((u32)prim & 0xFFFFFF);
    return (u8 *)prim + 0x20;
}

static void *Render_AddPolyF4(u32 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipQuadWork, ctx, (u8 *)prim + 4, 0, 0, 0);
        Render_CopyClipQuad(ctx->quadClip.v, ctx->src, (u8 *)prim + 8, (u8 *)prim + 0xC, (u8 *)prim + 0x10, (u8 *)prim + 0x14);
        return RCpolyF4(prim, g_clipQuadWork);
    }
    *prim = (*prim & 0xFF000000) | (*ctx->otEntry.u & 0xFFFFFF);
    *ctx->otEntry.u = (*ctx->otEntry.u & 0xFF000000) | ((u32)prim & 0xFFFFFF);
    return (u8 *)prim + 0x18;
}

static void *Render_AddPolyG4(PolyG4 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipQuadWork, ctx, &prim->c0, 0, 0, 0);
        Render_CopyClipQuad(&ctx->quadClip, &ctx->src, &prim->x0, &prim->x1, &prim->x2, &prim->x3);
        ctx->quadClip.v[0]->unk_0A = prim->c1.cd;
        ctx->quadClip.v[1]->unk_0A = prim->c1.cd;
        ctx->quadClip.v[2]->unk_0A = prim->c2.cd;
        ctx->quadClip.v[3]->unk_0A = prim->c3.cd;
        ctx->quadClip.v[0]->rgb = prim->c0;
        ctx->quadClip.v[1]->rgb = prim->c1;
        ctx->quadClip.v[2]->rgb = prim->c2;
        ctx->quadClip.v[3]->rgb = prim->c3;
        return RCpolyG4(prim, g_clipQuadWork);
    }
    prim->tag = (prim->tag & 0xFF000000) | (*ctx->otEntry.u & 0xFFFFFF);
    *ctx->otEntry.u = (*ctx->otEntry.u & 0xFF000000) | ((u32)prim & 0xFFFFFF);
    return prim + 1;
}

static void *Render_AddPolyFT4(PolyFT4 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipQuadWork, ctx, &prim->rgbc, 1, prim->clut, prim->tpage);
        Render_CopyClipQuad(&ctx->quadClip, &ctx->src, &prim->xy0, &prim->xy1, &prim->xy2, &prim->xy3);
        ctx->quadClip.v[0]->unk_0A = prim->pad1;
        ctx->quadClip.v[1]->unk_0A = prim->pad1;
        ctx->quadClip.v[2]->unk_0A = prim->pad1;
        ctx->quadClip.v[3]->unk_0A = prim->pad1;
        ctx->quadClip.v[0]->uv = prim->uv0;
        ctx->quadClip.v[1]->uv = prim->uv1;
        ctx->quadClip.v[2]->uv = prim->uv2;
        ctx->quadClip.v[3]->uv = prim->uv3;
        return RCpolyFT4(prim, g_clipQuadWork);
    }
    prim->tag = (prim->tag & 0xFF000000) | (*ctx->otEntry.u & 0xFFFFFF);
    *ctx->otEntry.u = (*ctx->otEntry.u & 0xFF000000) | ((u32)prim & 0xFFFFFF);
    return (u8 *)prim + 0x28;
}

static void *Render_AddPolyGT3(PolyGT3 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipTriWork, ctx, &prim->c0, 1, prim->clut, prim->tpage);
        Render_CopyClipTri(&ctx->triClip, &ctx->src, &prim->xy0, &prim->xy1, &prim->xy2);
        ctx->triClip.v[0]->unk_0A = prim->pad2;
        ctx->triClip.v[1]->unk_0A = prim->pad2;
        ctx->triClip.v[2]->unk_0A = prim->pad2;
        ctx->triClip.v[0]->rgb = prim->c0;
        ctx->triClip.v[1]->rgb = prim->c1;
        ctx->triClip.v[2]->rgb = prim->c2;
        ctx->triClip.v[0]->uv = prim->uv0;
        ctx->triClip.v[1]->uv = prim->uv1;
        ctx->triClip.v[2]->uv = prim->uv2;
        return RCpolyGT3(prim, g_clipTriWork);
    }
    prim->tag = (prim->tag & 0xFF000000) | (*ctx->otEntry.u & 0xFFFFFF);
    *ctx->otEntry.u = (*ctx->otEntry.u & 0xFF000000) | ((u32)prim & 0xFFFFFF);
    return prim + 1;
}

static void *Render_AddPolyGT4(PolyGT4 *prim, TmdCtx *ctx) {
    if (ctx->clip != 0) {
        Render_FillClipHeader(g_clipQuadWork, ctx, &prim->c0, 1, prim->clut, prim->tpage);
        Render_CopyClipQuad(&ctx->quadClip, &ctx->src, &prim->xy0, &prim->xy1, &prim->xy2, &prim->xy3);
        ctx->quadClip.v[0]->unk_0A = prim->pad2;
        ctx->quadClip.v[1]->unk_0A = prim->pad2;
        ctx->quadClip.v[2]->unk_0A = prim->pad3;
        ctx->quadClip.v[3]->unk_0A = prim->pad3;
        ctx->quadClip.v[0]->rgb = prim->c0;
        ctx->quadClip.v[1]->rgb = prim->c1;
        ctx->quadClip.v[2]->rgb = prim->c2;
        ctx->quadClip.v[3]->rgb = prim->c3;
        ctx->quadClip.v[0]->uv = prim->uv0;
        ctx->quadClip.v[1]->uv = prim->uv1;
        ctx->quadClip.v[2]->uv = prim->uv2;
        ctx->quadClip.v[3]->uv = prim->uv3;
        return RCpolyGT4(prim, g_clipQuadWork);
    }
    prim->tag = (prim->tag & 0xFF000000) | (*ctx->otEntry.u & 0xFFFFFF);
    *ctx->otEntry.u = (*ctx->otEntry.u & 0xFF000000) | ((u32)prim & 0xFFFFFF);
    return prim + 1;
}

/* Points `count` vertex slots at the work area's 0x18-byte vertices, from area + 0x18,
   and records them in the area's own table (+0xA8 for triangles, +0xF0 for quads) */
static void Render_InitClipSlots(u8 **slots, u8 *area, s32 count) {
    u8 **slot;
    u8 *entry;

    entry = area + 0x18;
    if (count == 4) {
        slot = (u8 **)(area + 0xF0);
    } else {
        slot = (u8 **)(area + 0xA8);
    }
    while (count-- > 0) {
        *slot = entry;
        *slots = entry;
        entry += 0x18;
        slot++;
        slots++;
    }
}

/* Screen box of the face; wider or taller than 256 pixels sends it to the clipper */
static void Render_CheckScreenBox(TmdCtx *ctx, s32 count) {
    ScreenXY *p;

    ctx->max = ctx->sxy.pt[0];
    ctx->min = ctx->max;
    for (p = &ctx->sxy.pt[1]; p < (ScreenXY *)((u8 *)ctx + count * 4 + 0x5C); p++) {
        if (p->x < ctx->min.x) {
            ctx->min.x = p->x;
        }
        if (p->y < ctx->min.y) {
            ctx->min.y = p->y;
        }
        if (ctx->max.x < p->x) {
            ctx->max.x = p->x;
        }
        if (ctx->max.y < p->y) {
            ctx->max.y = p->y;
        }
    }
    if (ctx->max.x - ctx->min.x > 0x100) {
        ctx->clip = 1;
    }
    if (ctx->max.y - ctx->min.y > 0x100) {
        ctx->clip = 1;
    }
}

static void Render_FillClipHeader(ClipHeader *header, TmdCtx *ctx, Rgbc *rgb, s32 textured, u16 clut, u16 tpage) {
    s32 value;

    if (g_clipDivisionForced != 0) {
        value = g_clipForcedDivision;
    } else {
        value = g_renderDivision;
    }
    header->division = value;
    header->width = g_clipScreenWidth;
    header->height = g_clipScreenHeight;
    if (textured != 0) {
        header->clut = clut;
        header->tpage = tpage;
    }
    header->rgb = *rgb;
    header->otEntry = ctx->otEntry.addr;
}

/* Copies the three model vertices and the packet's screen xy into the clipper vertices */
static void Render_CopyClipTri(void *dstArg, void *srcArg, void *sxy0, void *sxy1, void *sxy2) {
    ClipRefs *dst = dstArg;
    ClipRefs *src = srcArg;

    dst->v[0]->pos = src->v[0]->pos;
    dst->v[1]->pos = src->v[1]->pos;
    dst->v[2]->pos = src->v[2]->pos;
    dst->v[0]->sxy = *(Rgbc *)sxy0;
    dst->v[1]->sxy = *(Rgbc *)sxy1;
    dst->v[2]->sxy = *(Rgbc *)sxy2;
}

/* The same for a quad: three through Render_CopyClipTri, then the fourth */
static void Render_CopyClipQuad(void *dstArg, void *srcArg, void *sxy0, void *sxy1, void *sxy2, void *sxy3) {
    ClipRefs *dst = dstArg;
    ClipRefs *src = srcArg;

    Render_CopyClipTri(dstArg, srcArg, sxy0, sxy1, sxy2);
    dst->v[3]->pos = src->v[3]->pos;
    dst->v[3]->sxy = *(Rgbc *)sxy3;
}

/* Forces the clipper header's first word to `value` while `on` is set (see Render_FillClipHeader) */
static void Render_ForceClipDivision(s32 on, s32 value) {
    g_clipDivisionForced = on;
    if (on != 0) {
        g_clipForcedDivision = value;
    }
}

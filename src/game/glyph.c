#include "common.h"
#include "game/heap.h"
#include "game/scene.h"

/*
 * Glyph: vtable g_glyphVtbl 0x8006EC74 (tag 0x1144), 0xAC bytes, Glyph_Create: a ScreenSprite
 * showing one 8x8 character of a font image laid out 32 characters per row. Like ScreenSprite and
 * SpriteNode, a scene node (base SceneNode_GetVtbl, vtable 0x8006B5CC, tag 4) that draws a libgs
 * GsSPRITE cut from a TIM image; slots 0x60 to 0x68 work on the sprite's attribute word instead of
 * the node's.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* libgs GsSPRITE */
typedef struct Sprite {
    s32 attribute;  /* 0x00 bit 31 hidden, bit 30 semi-transparent, bits 28-29 blend rate, 24-25 color mode */
    u16 x;          /* 0x04 */
    u16 y;          /* 0x06 */
    u16 w;          /* 0x08 */
    u16 h;          /* 0x0A */
    u16 tpage;      /* 0x0C */
    u8 u;           /* 0x0E */
    u8 v;           /* 0x0F */
    u16 cx;         /* 0x10 CLUT */
    u16 cy;         /* 0x12 */
    Color3 color;   /* 0x14 0x80 neutral */
    u8 pad_17;
    s16 mx;         /* 0x18 rotation and scaling center */
    s16 my;         /* 0x1A */
    u16 scaleX;     /* 0x1C 0x1000 = 1 */
    u16 scaleY;     /* 0x1E */
    s32 rotate;     /* 0x20 degrees, 20.12 */
} Sprite;

/* The part of a TIM image cut into a sprite: copied whole. */
typedef struct SpriteRect {
    u16 u;
    u16 v;
    s32 w;
    s32 h;
} SpriteRect;

struct ScreenSprite;

typedef struct ScreenSpriteVtbl {
    u8 pad_00[0x08];
    void (*init)(void *, s32, SpriteRect *, s32);         /* 0x08 ScreenSprite_Init */
    u8 pad_0C[0x40 - 0x0C];
    void (*setup)(void *);                                /* 0x40 ScreenSprite_Setup, empty */
    u8 pad_44[0xBC - 0x44];
    void (*setPosition)(struct ScreenSprite *, ScreenPoint *); /* 0xBC ScreenSprite_SetPosition */
} ScreenSpriteVtbl;

typedef struct ScreenSprite {
    ScreenSpriteVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C */
    u8 pad_10[0x64 - 0x10];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0xA0 - 0x88];
    ScreenPoint position;   /* 0xA0 set once attached */
} ScreenSprite;

struct Glyph;

typedef struct GlyphVtbl {
    u8 pad_00[0x08];
    void (*init)(void *, s32, s32);           /* 0x08 Glyph_Init (glyph, font, code) */
    u8 pad_0C[0x40 - 0x0C];
    void (*setup)(void *, s32);               /* 0x40 Glyph_Setup (glyph, code) */
    u8 pad_44[0xC4 - 0x44];
    void (*setCode)(struct Glyph *, u8);      /* 0xC4 Glyph_SetCode */
} GlyphVtbl;

typedef struct Glyph {
    GlyphVtbl *vtbl;
    u8 pad_04[0x64 - 0x04];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0xA8 - 0x88];
    u8 code;                /* 0xA8 the character shown */
} Glyph;

void *Heap_Alloc(s32 size);

GlyphVtbl *Glyph_GetVtbl(void);
void Glyph_GetRect(SpriteRect *rect, u32 code);
ScreenSpriteVtbl *ScreenSprite_GetVtbl(void);

extern GlyphVtbl g_glyphVtbl;
extern SpriteRect g_glyphCellRect;      /* {0, 0, 8, 8}: the cell of character 0 */

/* Glyph */

void *Glyph_Create(s32 font, u8 code) {
    void *glyph;

    glyph = Heap_Alloc(0xAC);
    if (glyph != NULL) {
        Glyph_GetVtbl()->init(glyph, font, code);
        return glyph;
    }
    return NULL;
}

/* Slot 0x08: a screen sprite on the cell of a space (0x20), then the code. */
void Glyph_Init(Glyph *glyph, s32 font, u8 code) {
    SpriteRect rect;
    GlyphVtbl *vtbl;

    Glyph_GetRect(&rect, 0x20);
    ScreenSprite_GetVtbl()->init(glyph, font, &rect, 0);
    vtbl = Glyph_GetVtbl();
    glyph->vtbl = vtbl;
    vtbl->setup(glyph, code);
}

/* Slot 0x40 */
void Glyph_Setup(Glyph *glyph, u8 code) {
    glyph->vtbl->setCode(glyph, code);
}

/* Slot 0xC4: moves the sprite to the character's cell. */
void Glyph_SetCode(Glyph *glyph, u8 code) {
    u8 rect[12];

    glyph->code = code;
    Glyph_GetRect((SpriteRect *)rect, code);
    glyph->sprite.u = rect[0];
    glyph->sprite.v = rect[2];
}

/* Slot 0xC8 */
u8 Glyph_GetCode(Glyph *glyph) {
    s32 unused[4];
    return glyph->code;
}

GlyphVtbl *Glyph_GetVtbl(void) {
    return &g_glyphVtbl;
}

/* The 8x8 cell of a character: 32 per row. */
void Glyph_GetRect(SpriteRect *rect, u32 code) {
    *rect = g_glyphCellRect;
    code = code & 0xFF;
    rect->u = rect->u + ((code & 0x1F) * 8);
    rect->v = rect->v + ((code >> 5) * 8);
}

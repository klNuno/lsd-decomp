#include "common.h"
#include "game/heap.h"
#include "game/loader.h"
#include "game/scene.h"

/*
 * Six classes. The first three are scene nodes (base SceneNode_GetVtbl, vtable 0x8006B5CC, tag 4)
 * that draw a libgs GsSPRITE cut from a TIM image; their slots 0x60 to 0x68 work on the
 * sprite's attribute word instead of the node's.
 *
 *   SpriteNode    vtable g_spriteNodeVtbl 0x8006EE1C (tag 0x44), 0xA0 bytes, SpriteNode_Create.
 *   ScreenSprite  vtable g_screenSpriteVtbl 0x8006ED4C (tag 0x144), 0xA8 bytes, ScreenSprite_Create:
 *                 a SpriteNode attached with a 2D position (slot 0x4C) and a pivot (slot 0xC0). The
 *                 comment keyboard's input box, the card menu's message and the list backgrounds.
 *   Glyph         vtable g_glyphVtbl 0x8006EC74 (tag 0x1144), 0xAC bytes, Glyph_Create: a ScreenSprite
 *                 showing one 8x8 character of a font image laid out 32 characters per row.
 *   SeqFile       vtable g_seqFileVtbl 0x8006EED8 (tag 0xB03), 0x30 bytes, SeqFile_Create: a file
 *                 class (loader.h) loaded with loadAsync; the music player (src/game/800398E0.c)
 *                 hands its data to SsSeqOpen once +0x2C is set.
 *   Clock         vtable g_clockVtbl 0x8006EF50 (tag 5), 0x1C bytes, Clock_Create: each step adds a
 *                 tick and tells every watcher 2, or 3 when paused, 4 when stopped (scene.h).
 *   RootNode      vtable g_rootNodeVtbl 0x8006EFAC (tag 0x14), 0x54 bytes, RootNode_Create: a scene
 *                 node holding 3 lights (FlatLight_New) and the ambient color; the default root of a
 *                 screen (scene.h ScreenEnv) and the base class of StageMap.
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

/* SpriteRect as SpriteNode_FillSprite reads it: bytes for u and v, halves for w and h. */
typedef struct SpriteRectBytes {
    u8 u;
    u8 pad_01;
    u8 v;
    u8 pad_03;
    u16 w;
    u16 pad_06;
    u16 h;
} SpriteRectBytes;

/* The start of the GsIMAGE of a TIM image object (at +0x2C), as SpriteNode_FillSprite reads it. */
typedef struct SpriteTim {
    s32 pmode;      /* 0x00 the low 2 bits are the color mode */
    s16 px;         /* 0x04 VRAM position of the pixels */
    s16 py;
    u8 pad_08[0x10 - 0x08];
    u16 cx;         /* 0x10 VRAM position of the CLUT */
    u16 cy;
} SpriteTim;

/* The rotation a scene node takes (base slot 0x44): 3 angles in degrees, each a fraction. */
typedef struct NodeAngles {
    Fraction x;
    Fraction y;
    Fraction z;
} NodeAngles;

struct SpriteNode;

/* Slots of g_spriteNodeVtbl this unit calls, with the arguments it passes. */
typedef struct SpriteNodeVtbl {
    u8 pad_00[0x08];
    void (*init)(void *, s32, s32, s32, s32, s32);     /* 0x08 SpriteNode_Init */
    u8 pad_0C[0x40 - 0x0C];
    void (*setImage)(void *, s32, s32, s32, s32, s32); /* 0x40 SpriteNode_SetImage */
    u8 pad_44[0x4C - 0x44];
    void (*attach)(void *, s32, void *);               /* 0x4C SceneNode_Attach (node, parent, Vec3 position) */
} SpriteNodeVtbl;

/* The first 0x18 bytes are the scene node's (scene.h SceneNode). */
typedef struct SpriteNode {
    SpriteNodeVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C SceneNode *, 0 until attached */
    u8 pad_10[0x48 - 0x10];
    s32 tim;                /* 0x48 SpriteTim *, the GsIMAGE inside the image object */
    SpriteRect rect;        /* 0x4C */
    s32 unk58;              /* 0x58 0 */
    u8 pad_5C[0x64 - 0x5C];
    Sprite sprite;          /* 0x64 */
    u8 pad_88[0xA0 - 0x88];
} SpriteNode;

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

/* A file object (loader.h) whose data is a SEQ file. */
typedef struct SeqFile {
    FileVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    s32 data;               /* 0x10 the SEQ, given to SsSeqOpen */
    s32 size;               /* 0x14 */
    u8 pad_18[0x2C - 0x18];
    s32 loaded;             /* 0x2C set by SeqFile_OnLoaded */
} SeqFile;

typedef struct RootNodeVtbl {
    u8 pad_00[0x08];
    void (*init)(void *);                     /* 0x08 RootNode_Init */
    u8 pad_0C[0x10 - 0x0C];
    void (*watch)(void *, s32);               /* 0x10 SceneNode_Watch */
    u8 pad_14[0x40 - 0x14];
    void (*setup)(void *);                    /* 0x40 RootNode_Setup */
    u8 pad_44[0xB8 - 0x44];
    Object *(*getLight)(void *, s32);         /* 0xB8 RootNode_GetLight */
} RootNodeVtbl;

typedef struct RootNode {
    RootNodeVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 parent;             /* 0x0C */
    s32 unk10;
    s32 *coord;             /* 0x14 its GsCOORDINATE2, the first word is flg */
    u8 pad_18[0x44 - 0x18];
    s32 lights[3];          /* 0x44 FlatLight_New(0 to 2), watched by the node */
    Color3 ambient;         /* 0x50 GsSetAmbient takes it times 16 */
} RootNode;

void *Heap_Alloc(s32 size);
ObjectVtbl *Object_GetBaseVtbl(void);
ObjectVtbl *SceneNode_GetVtbl(void);
FileVtbl *File_GetBackendVtbl(void);
void List_Next(s32 *value, ListNode **iter);
s32 Bits_SetField(s32 *word, s32 shift, s32 bits, s32 value);
s32 FlatLight_New(s32);
u16 GetTPage(s32 tp, s32 abr, s16 x, s16 y);
void GsSetAmbient(s32 r, s32 g, s32 b);
s8 *strcpy(s8 *dst, s8 *src);

GlyphVtbl *Glyph_GetVtbl(void);
void Glyph_GetRect(SpriteRect *rect, u32 code);
ScreenSpriteVtbl *ScreenSprite_GetVtbl(void);
void SpriteNode_FillSprite();
SpriteNodeVtbl *SpriteNode_GetVtbl(void);
FileVtbl *SeqFile_GetVtbl(void);
ClockVtbl *Clock_GetVtbl(void);
RootNodeVtbl *RootNode_GetVtbl(void);

extern GlyphVtbl g_glyphVtbl;
extern SpriteRect g_glyphCellRect;      /* {0, 0, 8, 8}: the cell of character 0 */
extern ScreenSpriteVtbl g_screenSpriteVtbl;
extern s32 g_screenSpriteOrigin[3];          /* {0, 0, 0}: the Vec3 a screen sprite is attached at */
extern SpriteNodeVtbl g_spriteNodeVtbl;
extern FileVtbl g_seqFileVtbl;
extern ClockVtbl g_clockVtbl;
extern RootNodeVtbl g_rootNodeVtbl;

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

/* ScreenSprite */

void *ScreenSprite_Create(s32 image, SpriteRect *rect, s32 arg2) {
    void *sprite;

    sprite = Heap_Alloc(0xA8);
    if (sprite != 0) {
        ScreenSprite_GetVtbl()->init(sprite, image, rect, arg2);
        return sprite;
    }
    return 0;
}

/* Slot 0x08 */
void ScreenSprite_Init(ScreenSprite *sprite, s32 image, s32 rect, s32 arg3) {
    SpriteNode_GetVtbl()->init(sprite, image, 0, rect, 0, arg3);
    sprite->vtbl = ScreenSprite_GetVtbl();
    sprite->vtbl->setup(sprite);
}

/* Slot 0x40 */
void ScreenSprite_Setup(void) {
}

/* Slot 0x4C: attach to the parent node at the origin, then set the 2D position. */
void ScreenSprite_Attach(ScreenSprite *sprite, s32 parent, ScreenPoint *position) {
    if (sprite->parent == 0) {
        SpriteNode_GetVtbl()->attach(sprite, parent, g_screenSpriteOrigin);
        sprite->vtbl->setPosition(sprite, position);
    }
}

/* Slot 0xBC */
void ScreenSprite_SetPosition(ScreenSprite *sprite, ScreenPoint *position) {
    if (sprite->parent != 0) {
        sprite->position = *position;
    }
}

/* Slot 0xC0: the rotation and scaling center, 0 middle, 1 left, 2 right, 3 top, 4 bottom. */
void ScreenSprite_SetPivot(ScreenSprite *sprite, s32 pivot) {
    if (sprite->parent != 0) {
        switch (pivot) {
        case 0:
            sprite->sprite.mx = sprite->sprite.w >> 1;
            sprite->sprite.my = sprite->sprite.h >> 1;
            break;
        case 1:
            sprite->sprite.mx = 0;
            break;
        case 2:
            sprite->sprite.mx = sprite->sprite.w;
            break;
        case 3:
            sprite->sprite.my = 0;
            break;
        case 4:
            sprite->sprite.my = sprite->sprite.h;
            break;
        }
    }
}

ScreenSpriteVtbl *ScreenSprite_GetVtbl(void) {
    return &g_screenSpriteVtbl;
}

/* SpriteNode */

void *SpriteNode_Create(s32 image, s32 blendRate, s32 rect, s32 arg3, s32 arg4) {
    void *node;

    node = Heap_Alloc(0xA0);
    if (node != 0) {
        SpriteNode_GetVtbl()->init(node, image, blendRate, rect, arg3, arg4);
        return node;
    }
    return 0;
}

/* Slot 0x08 */
void SpriteNode_Init(SpriteNode *node, s32 image, s32 blendRate, s32 rect, s32 arg4, s32 arg5) {
    SpriteNodeVtbl *vtbl;

    SceneNode_GetVtbl()->init(node);
    vtbl = SpriteNode_GetVtbl();
    node->vtbl = vtbl;
    vtbl->setImage(node, image, blendRate, rect, arg4, arg5);
}

/* Slot 0x40 (node, image object, blend rate, rect) */
void SpriteNode_SetImage(SpriteNode *node, s32 image, s32 blendRate, SpriteRect *rect) {
    node->tim = image + 0x2C;
    node->rect = *rect;
    SpriteNode_FillSprite(&node->sprite, blendRate, rect, node->tim);
    node->unk58 = 0;
}

/* Fills the sprite for the rect of the TIM: centered pivot, white, scale 1, no rotation. */
void SpriteNode_FillSprite(Sprite *sprite, s32 blendRate, SpriteRectBytes *rect, SpriteTim *tim) {
    s32 colorMode;

    colorMode = tim->pmode;
    sprite->x = 0;
    sprite->y = 0;
    colorMode &= 3;
    sprite->attribute = colorMode << 0x18;
    sprite->w = rect->w;
    sprite->h = rect->h;
    sprite->mx = sprite->w >> 1;
    sprite->my = sprite->h >> 1;
    sprite->tpage = GetTPage(colorMode, blendRate, tim->px, tim->py);
    sprite->u = rect->u;
    sprite->v = rect->v;
    sprite->cx = tim->cx;
    sprite->cy = tim->cy;
    sprite->color.b = 0x80;
    sprite->color.g = 0x80;
    sprite->color.r = 0x80;
    sprite->rotate = 0;
    sprite->scaleX = 0x1000;
    sprite->scaleY = 0x1000;
}

/* Slot 0x44: a sprite only turns around z; assign 0 adds to the current angle. */
void SpriteNode_SetRotation(SpriteNode *node, s32 assign, NodeAngles *angles) {
    s32 rotate;

    rotate = ((angles->z.num / angles->z.den) << 12) + (((angles->z.num % angles->z.den) << 12) / angles->z.den);
    if (assign != 0) {
        node->sprite.rotate = rotate;
        return;
    }
    node->sprite.rotate = rotate + node->sprite.rotate;
}

/* Slot 0x60: returns whether it was visible. */
s32 SpriteNode_SetVisible(SpriteNode *node, s32 visible) {
    return Bits_SetField(&node->sprite.attribute, 0x1F, 1, visible == 0) == 0;
}

/* Slot 0x64 */
void SpriteNode_SetSemiTrans(SpriteNode *node, s32 semiTrans) {
    Bits_SetField(&node->sprite.attribute, 0x1E, 1, semiTrans != 0);
}

/* Slot 0x68 */
void SpriteNode_SetBlendRate(SpriteNode *node, s32 blendRate) {
    Bits_SetField(&node->sprite.attribute, 0x1C, 2, blendRate);
}

/* Slot 0x98, empty as in the base */
void SpriteNode_OnClock(void) {
}

/* Slot 0xB8 */
void SpriteNode_SetColor(SpriteNode *node, Color3 *color) {
    node->sprite.color = *color;
}

SpriteNodeVtbl *SpriteNode_GetVtbl(void) {
    return &g_spriteNodeVtbl;
}

/* SeqFile */

s32 SeqFile_Create(s32 path) {
    void *file;

    file = Heap_Alloc(0x30);
    if (file != 0) {
        SeqFile_GetVtbl()->init(file, path);
        return (s32)file;
    }
    return 0;
}

/* Slot 0x08: starts loading the path, copied first. */
void SeqFile_Init(SeqFile *file, s8 *path) {
    char name[0x20];

    File_GetBackendVtbl()->init(file);
    file->vtbl = SeqFile_GetVtbl();
    file->loaded = 0;
    if (path != NULL) {
        strcpy(name, path);
        file->vtbl->loadAsync(file, name);
    }
}

/* Slot 0x0C */
void SeqFile_Destroy(SeqFile *file) {
    file->loaded = 0;
    File_GetBackendVtbl()->destroy(file);
}

/* Slot 0x64 */
void SeqFile_OnLoaded(SeqFile *file) {
    file->loaded = 1;
}

FileVtbl *SeqFile_GetVtbl(void) {
    return &g_seqFileVtbl;
}

/* Clock */

void *Clock_Create(void) {
    void *clock;

    clock = Heap_Alloc(0x1C);
    if (clock != 0) {
        Clock_GetVtbl()->init(clock);
        return clock;
    }
    return 0;
}

/* Slot 0x08 */
void Clock_Init(Clock *clock) {
    ClockVtbl *vtbl;

    Object_GetBaseVtbl()->init(clock);
    vtbl = Clock_GetVtbl();
    clock->vtbl = vtbl;
    vtbl->reset(clock, 0);
}

/* Slot 0x0C */
void Clock_Destroy(Clock *clock) {
    Object_GetBaseVtbl()->destroy(clock);
}

/* Slot 0x24: a watcher removed while Clock_Notify runs moves its cursor past it. */
void Clock_RemoveWatcher(Clock *clock, s32 watcher) {
    ListNode *node;

    node = clock->notifyIter;
    if (node != NULL && watcher == node->value) {
        clock->notifyIter = node->next;
    }
    Object_GetBaseVtbl()->removeWatcher(clock, watcher);
}

/* Slot 0x30: Object_Notify with its cursor in the clock. */
void Clock_Notify(Clock *clock, s32 message) {
    Object *watcher;

    clock->notifyIter = clock->watchers;
    List_Next((s32 *)&watcher, &clock->notifyIter);
    while (watcher != NULL) {
        watcher->vtbl->onNotify(watcher, clock, message);
        List_Next((s32 *)&watcher, &clock->notifyIter);
    }
    clock->notifyIter = 0;
}

/* Slot 0x40 */
void Clock_Reset(Clock *clock, s32 ticks) {
    clock->ticks = ticks;
    clock->stopped = 0;
    clock->paused = 0;
    clock->notifyIter = 0;
}

/* Slot 0x44 */
void Clock_Step(Clock *clock) {
    s32 message = CLOCK_MSG_STOPPED;

    if (clock->stopped == 0) {
        message = CLOCK_MSG_PAUSED;
        if (clock->paused == 0) {
            message = CLOCK_MSG_TICK;
            clock->ticks++;
        }
    }
    clock->vtbl->notify(clock, message);
}

/* Slot 0x48 */
s32 Clock_GetTicks(Clock *clock) {
    return clock->ticks;
}

/* Slot 0x4C */
void Clock_Pause(Clock *clock) {
    clock->paused = 1;
}

/* Slot 0x50 */
void Clock_Resume(Clock *clock) {
    clock->paused = 0;
}

/* Slot 0x54 */
s32 Clock_IsPaused(Clock *clock) {
    return clock->paused;
}

/* Slot 0x58 */
void Clock_Stop(Clock *clock) {
    clock->stopped = 1;
}

ClockVtbl *Clock_GetVtbl(void) {
    return &g_clockVtbl;
}

/* RootNode */

void *RootNode_Create(void) {
    void *root;

    root = Heap_Alloc(0x54);
    if (root != 0) {
        RootNode_GetVtbl()->init(root);
        return root;
    }
    return 0;
}

/* Slot 0x08: makes and watches its 3 lights. */
void RootNode_Init(RootNode *root) {
    s32 i;
    s32 *light;

    SceneNode_GetVtbl()->init(root);
    root->vtbl = RootNode_GetVtbl();
    for (i = 0, light = root->lights; i < 3; i++, light++) {
        *light = FlatLight_New(i);
        root->vtbl->watch(root, *light);
    }
    root->vtbl->setup(root);
}

/* Slot 0x0C: deletes its lights. */
void RootNode_Destroy(RootNode *root) {
    s32 i;
    Object *light;

    for (i = 0; i < 3; i++) {
        light = root->vtbl->getLight(root, i);
        light->vtbl->delete_(light);
    }
    SceneNode_GetVtbl()->destroy(root);
}

/* Slot 0x40: only clears the flg word of its GsCOORDINATE2 (the base SceneNode_Reset resets the node). */
void RootNode_Setup(RootNode *root) {
    *root->coord = 0;
}

/* Slot 0x9C, empty */
void RootNode_OnNode(void) {
}

/* Slot 0xB8 */
s32 RootNode_GetLight(RootNode *root, s32 index) {
    return root->lights[index];
}

/* Slot 0xBC: swap != 0 returns the previous color in *color. */
void RootNode_SetAmbient(RootNode *root, Color3 *color, s32 swap) {
    Color3 previous;

    if (swap != 0) {
        previous = root->ambient;
        root->ambient = *color;
        *color = previous;
    } else {
        root->ambient = *color;
    }
    GsSetAmbient((u8)root->ambient.r * 0x10, (u8)root->ambient.g * 0x10, (u8)root->ambient.b * 0x10);
}

RootNodeVtbl *RootNode_GetVtbl(void) {
    return &g_rootNodeVtbl;
}

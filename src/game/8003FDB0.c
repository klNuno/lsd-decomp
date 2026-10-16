#include "common.h"
#include "game/scene.h"

/*
 * The 2D widgets drawn by the scene tree (src/game/80012064.c): Box, a filled rectangle; Fade, the
 * Box that fades a color over the screen (the view's overlay, the Place fader, the entity effect);
 * Label, a row of character glyphs. Plus the Shift-JIS text helpers.
 */

/* An (x, y) pair of s32 */
/* A bit field setter of src/game/8001CA94.c: sets width bits at shift in *word, returns the old value */
s32 Bits_SetField(s32 *word, s32 shift, s32 width, s32 value);
void *Heap_Alloc(s32 size);
void *Heap_Free(void *);
void Object_DeleteArray(void *, s32);

/* The base scene node class (SceneNode_GetVtbl, src/game/8001CA94.c), as Box calls it */
typedef struct BaseNodeVtbl {
    u8 pad_00[0x8];
    void (*init)(void *box);                  /* 0x08 */
    u8 pad_0C[0x4C - 0xC];
    void (*show)(void *box, s32 root, s32 position); /* 0x4C */
} BaseNodeVtbl;
BaseNodeVtbl *SceneNode_GetVtbl(void);

/*
 * Box (vtable g_boxVtbl at 0x8006EAC0, class word 0x64, 0x6C bytes): a scene node holding a PSY-Q
 * GsBOXF at +0x58. The scene draw (Scene_DrawNode, kind 0x64) places it at +0x50, in percent of the
 * half screen when +0x48 is set, and sorts it with GsSortBoxFill at the priority +0x44.
 */
typedef struct BoxVtbl {
    u8 pad_00[0x8];
    void (*init)(void *box, s32 size, u8 *color, s32 priority); /* 0x08 Box_Construct */
    u8 pad_0C[0x40 - 0xC];
    void (*reset)(void *box, s32 size, s32 color, s32 priority); /* 0x40 Box_Init */
    u8 pad_44[0x4C - 0x44];
    void (*show)();                           /* 0x4C Box_Show (box, root, position) */
    u8 pad_50[0xB8 - 0x50];
    void (*setColor)(void *box, s32 copy, u8 *color); /* 0xB8 */
    void (*setPosition)(void *box, s32 position);    /* 0xBC */
    u8 pad_C0[0xCC - 0xC0];
    void (*setMask)(void *box, s32 bits);     /* 0xCC */
} BoxVtbl;

typedef struct Box {
    BoxVtbl *vtbl;
    u8 pad_04[0xC - 0x4];
    s32 parent;             /* 0x0C SceneNode *, set while the box is shown */
    u8 pad_10[0x44 - 0x10];
    s32 priority;           /* 0x44 ordering table priority given to GsSortBoxFill */
    s32 relative;           /* 0x48 position in percent of the half screen */
    s32 unk_4C;
    ScreenPoint position;       /* 0x50 */
    s32 attribute;          /* 0x58 GsBOXF: bit 31 hidden, bit 30 semi-transparent, bits 28-29 blend mode */
    u16 x;                  /* 0x5C GsBOXF, written by the draw from position */
    u16 y;                  /* 0x5E */
    u16 width;              /* 0x60 */
    u16 height;             /* 0x62 */
    Color3 color;              /* 0x64 */
    u8 pad_67;
    s32 mask;               /* 0x68 (1 << bits) - 1, 13 bits by default */
} Box;

extern u8 g_boxDefaultColor[];     /* the default box color, (128, 128, 128) */
BoxVtbl *Box_GetVtbl(void);
void Rgb_CopyOrAdd(void *box, Color3 *dst, Color3 *src, s32 copy);

/* Fade, Label: include/game/scene.h */

extern u8 g_fadePalette[][3];
extern u8 g_fadeBlackPalette[3];    /* eight black RGB triples, read like g_fadePalette */
FadeVtbl *Fade_GetVtbl(void);

/* A glyph (vtable g_glyphVtbl, src/game/80041AB4.c): one character sprite, and the base of Label */
typedef struct Glyph Glyph;
typedef struct GlyphVtbl {
    u8 pad_00[0x8];
    void (*init)(void *glyph, s32 font, s32 c); /* 0x08 */
    void (*destroy)(void *glyph);             /* 0x0C */
    u8 pad_10[0x4C - 0x10];
    void (*show)();                           /* 0x4C (glyph, root, position) */
    void (*hide)(void *glyph);                /* 0x50 */
    u8 pad_54[0x60 - 0x54];
    s32 (*setVisible)(Glyph *glyph, void *visible, s32 previous); /* 0x60 */
    u8 pad_64[0xB8 - 0x64];
    void (*setColor)(void *glyph, s32 color); /* 0xB8 */
    void (*setPosition)(void *glyph, void *position); /* 0xBC */
    u8 pad_C0[0xC4 - 0xC0];
    void (*setChar)(Glyph *glyph, u8 c, Glyph **slot); /* 0xC4 */
} GlyphVtbl;

struct Glyph {
    GlyphVtbl *vtbl;
};

GlyphVtbl *Glyph_GetVtbl(void);
void *Glyph_Create(s32, u8);

LabelVtbl *Label_GetVtbl(void);
s8 *itoa(s32 value);
s8 *strcpy(s8 *dst, s8 *src);
s32 strlen(u8 *s);
void *memset(void *dst, s32 c, s32 n);
s8 *Text_Encode(s8 *dst, u8 *src);
extern u8 g_fadeVtbl[];
extern u8 g_boxVtbl[];
extern u8 g_labelVtbl[];

/* new Fade(size, channels, priority) */
void *Fade_Create(s32 size, s32 channels, s32 priority) {
    void *fade;

    fade = Heap_Alloc(0xA0);
    if (fade != NULL) {
        Fade_GetVtbl()->init(fade, size, channels, priority);
        return fade;
    }
    return NULL;
}

/* Slot 0x08: builds the Box with the channels' color, then sets the Fade vtable and runs slot 0x40 */
void Fade_Construct(void **fade, s32 size, s32 channels, s32 priority) {
    BoxVtbl *boxVtbl;
    u8 *color;
    FadeVtbl *vtbl;

    boxVtbl = Box_GetVtbl();
    if (channels != 0) {
        color = g_fadePalette[channels];
    } else {
        color = g_fadeBlackPalette;
    }
    boxVtbl->init(fade, size, color, priority);
    vtbl = Fade_GetVtbl();
    *fade = vtbl;
    vtbl->reset(fade, channels);
}

/* Slot 0x40: idle, step 10, hidden and opaque */
void Fade_Init(Fade *fade, s32 channels) {
    fade->defaultChannels = channels;
    fade->state = 0;
    fade->step.value = 0xA;
    fade->channels = 0;
    fade->unk_7C = 0;
    fade->vtbl->setVisible(fade, 0);
    fade->vtbl->setSemiTrans(fade, 0);
    fade->tint = 0;
}

/* Slot 0x98: on message 2 from the watched object, one step of the fade, or Fade_Stop at the end */
void Fade_Step(Fade *fade, s32 ticker, s32 message) {
    if (message == 2) {
        if (fade->remaining-- > 0) {
            if (fade->unk_7C != 9) {
                if (fade->channels & 4) {
                    fade->color.r += fade->step.low;
                }
                if (fade->channels & 2) {
                    fade->color.g += fade->step.low;
                }
                if (fade->channels & 1) {
                    fade->color.b += fade->step.low;
                }
            }
        } else {
            fade->vtbl->stop(fade);
        }
    }
}

/* Slot 0xD0 */
void Fade_SetStep(Fade *fade, s32 step) {
    fade->step.value = step;
}

/* Slot 0xD4: fade in, from the full color down to nothing (Place calls it when a stage starts) */
void Fade_StartIn(Fade *fade, s32 ticker, s32 channels, s32 arg3) {
    s32 index;
    if (fade->state == 0) {
        index = fade->vtbl->begin(fade, ticker, channels, arg3);
        fade->vtbl->setColor(fade, 1, g_fadePalette[index]);
        fade->state = 1;
        fade->step.value = -fade->step.value;
    }
}

/* Slot 0xD8: fade out, from black up to the color (Place_StartFade) */
void Fade_StartOut(Fade *fade, s32 ticker, s32 channels, s32 arg3) {
    if (fade->state == 0) {
        channels = fade->vtbl->begin(fade, ticker, channels, arg3);
        if (fade->tint != 0) {
            fade->remaining--;
        } else {
            fade->vtbl->setColor(fade, 1, &g_fadeBlackPalette[channels * 3]);
        }
        fade->state = 2;
    }
}

/*
 * Slot 0xDC: watches the ticker, sets the channels (0: all, black through blend mode 2, else
 * blend mode 1) and the tick count 0x100 / step, then shows the box semi-transparent.
 */
s32 Fade_Begin(Fade *fade, s32 ticker, s32 channels, s32 arg3) {
    FadeVtbl *vtbl;
    s32 index;
    s32 mode;
    s32 ticks;

    vtbl = fade->vtbl;
    index = channels;
    if (index < 0) {
        index = fade->defaultChannels;
    } else {
        fade->defaultChannels = index;
    }
    mode = 1;
    if (index != 0) {
        fade->channels = index;
    } else {
        mode = 2;
        fade->channels = 0xF;
    }
    fade->channels = index;
    if (index == 0) {
        fade->channels = 0xF;
    }
    ticks = 0x100 / fade->step.value;
    fade->unk_7C = arg3;
    fade->remaining = ticks;
    if (fade->tint != 0) {
        fade->remaining = ticks - ticks / fade->tintDivisor;
    }
    channels = fade->mask / fade->remaining;
    fade->unk_84 = channels;
    vtbl->watch(fade);
    vtbl->setSemiTrans(fade, 1);
    vtbl->setBlendMode(fade, mode);
    vtbl->setVisible(fade, 1);
    return index;
}

/* Slot 0xE0: stops watching the ticker and notifies 5 (fade in done) or 6 (fade out done) */
void Fade_Stop(Fade *fade, s32 ticker) {
    FadeVtbl *vtbl = fade->vtbl;
    s32 message;

    if (fade->state == 0) {
        return;
    }
    if (fade->state == 1) {
        message = 5;
        if (fade->tint == 0) {
            vtbl->setVisible(fade, 0);
            vtbl->setSemiTrans(fade, 0);
        }
    } else {
        message = 6;
        if (fade->tint != 0) {
            if (fade->channels == 0xF) {
                vtbl->setColor(fade, 1, g_fadeBlackPalette);
            }
            vtbl->setSemiTrans(fade, 0);
        }
    }
    vtbl->unwatch(fade, ticker);
    if (fade->step.value < 0) {
        fade->step.value = -fade->step.value;
    }
    fade->state = 0;
    vtbl->notify(fade, message);
}

/* Slot 0xE4: the color of the current channels */
u8 *Fade_GetColor(Fade *fade) {
    s32 channels = fade->channels;

    if (channels == 0xF) {
        return g_fadeBlackPalette;
    }
    return g_fadePalette[channels];
}

/* Slot 0xE8: saves the size and position, then sets new ones (size read as u16 halves) */
void Fade_SaveAndSetRect(Fade *fade, u16 *size, ScreenPoint *position) {
    if (fade->parent != 0) {
        fade->savedWidth.value = fade->width;
        fade->savedHeight.value = fade->height;
        fade->savedPosition = fade->position;
        fade->width = size[0];
        fade->height = size[2];
        fade->position = *position;
    }
}

/* Slot 0xEC */
void Fade_RestoreRect(Fade *fade) {
    fade->position = fade->savedPosition;
    fade->width = fade->savedWidth.half;
    fade->height = fade->savedHeight.half;
}

/* Slot 0xF0 */
void Fade_SetTint(Fade *fade, s32 tint, s32 tintDivisor) {
    fade->tint = tint;
    fade->tintDivisor = tintDivisor;
}

FadeVtbl *Fade_GetVtbl(void) {
    return (FadeVtbl *)g_fadeVtbl;
}

/* new Box(size, color, priority) */
void *Box_Create(s32 size, s32 color, s32 priority) {
    void *box;

    box = Heap_Alloc(0x6C);
    if (box != NULL) {
        Box_GetVtbl()->init(box, size, color, priority);
        return box;
    }
    return NULL;
}

/* Slot 0x08: base scene node init, then the Box vtable and slot 0x40 */
void Box_Construct(void **box, s32 size, s32 color, s32 priority) {
    BoxVtbl *vtbl;

    SceneNode_GetVtbl()->init(box);
    vtbl = Box_GetVtbl();
    *box = vtbl;
    vtbl->reset(box, size, color, priority);
}

/* Slot 0x40: relative position (0, 0), the size, the color or the default gray, mask of 13 bits */
void Box_Init(Box *box, u16 *size, u8 *color, s32 priority) {
    BoxVtbl *vtbl;

    box->priority = priority;
    box->relative = 1;
    box->unk_4C = 0;
    box->attribute = 0;
    box->x = 0;
    box->y = 0;
    box->width = size[0];
    box->height = size[2];
    vtbl = box->vtbl;
    if (color == NULL) {
        color = g_boxDefaultColor;
    }
    vtbl->setColor(box, 1, color);
    box->vtbl->setMask(box, 0xD);
}

/* Slot 0x4C: attaches the box under root once, then places it */
void Box_Show(Box *box, s32 root, s32 position) {
    if (box->parent == 0) {
        SceneNode_GetVtbl()->show(box, root, 0);
        box->vtbl->setPosition(box, position);
    }
}

/* Slot 0x60: shows or hides the box (GsBOXF bit 31), returns whether it was shown */
s32 Box_SetVisible(Box *box, s32 visible) {
    return Bits_SetField(&box->attribute, 0x1F, 1, visible == 0) == 0;
}

/* Slot 0x64: semi-transparency on or off (GsBOXF bit 30) */
void Box_SetSemiTrans(Box *box, s32 on) {
    Bits_SetField(&box->attribute, 0x1E, 1, on != 0);
}

/* Slot 0x68: the semi-transparency mode (GsBOXF bits 28-29: 1 adds, 2 subtracts) */
void Box_SetBlendMode(Box *box, s32 mode) {
    Bits_SetField(&box->attribute, 0x1C, 2, mode);
}

/* Slot 0xB8: copies the color, or adds it when copy is 0 */
void Box_SetColor(Box *box, s32 copy, u8 *color) {
    Rgb_CopyOrAdd(box, &box->color, color, copy);
}

void Rgb_CopyOrAdd(void *box, Color3 *dst, Color3 *src, s32 copy) {
    if (copy != 0) {
        *dst = *src;
        return;
    }
    dst->r += src->r;
    dst->g += src->g;
    dst->b += src->b;
}

/* Slot 0xBC: moves a shown box */
void Box_SetPosition(Box *box, ScreenPoint *position) {
    if (box->parent != 0) {
        box->position = *position;
    }
}

/* Slot 0xC0: resizes a shown box (size read as u16 halves) */
void Box_SetSize(Box *box, u16 *size) {
    if (box->parent != 0) {
        box->width = size[0];
        box->height = size[2];
    }
}

/* Slot 0xC4: shows the box (root and position passed through), then clears the percent flag */
void Box_ShowAbsolute(Box *box, s32 root, s32 position, s32 value) {
    box->vtbl->show();
    box->relative = 0;
    box->unk_4C = value;
}

/* Slot 0xC8 */
void Box_SetPriority(Box *box, s32 priority) {
    box->priority = priority;
}

/* Slot 0xCC */
void Box_SetMask(Box *box, s32 bits) {
    box->mask = (1 << bits) - 1;
}

BoxVtbl *Box_GetVtbl(void) {
    return (BoxVtbl *)g_boxVtbl;
}

/* new Label(font, count, text) */
s32 Label_Create(s32 font, s32 count, s32 text) {
    s32 label = Heap_Alloc(0xB8);

    if (label != 0) {
        Label_GetVtbl()->init((void *)label, font, count, text);
        return label;
    }
    return 0;
}

/* Slot 0x08: a space glyph of font with count space glyphs under it, then slot 0x40 with the text */
void Label_Construct(Label *label, s32 font, s32 count, s32 text) {
    Glyph **glyphs;
    s32 i;

    Glyph_GetVtbl()->init(label, font, 0x20);
    label->vtbl = Label_GetVtbl();
    label->count = count;
    label->shownCount = count;
    label->firstShown = 0;
    label->gapAt = 0;
    glyphs = ((void *)Heap_Alloc(count * 4));
    if (glyphs != NULL) {
        label->glyphs = glyphs;
        for (i = 0; i < count; i++) {
            *glyphs = Glyph_Create(font, 0x20);
            glyphs += 1;
        }
        label->vtbl->reset(label, text);
    }
}

/* Slot 0x0C */
void Label_Destroy(Label *label) {
    Object_DeleteArray(label->glyphs, label->count);
    label->glyphs = Heap_Free(label->glyphs);
    Glyph_GetVtbl()->destroy(label);
}

/* Slot 0x40: spacing 7, then the text */
void Label_Init(Label *label, s32 text) {
    label->vtbl->setSpacing(label, 7);
    label->vtbl->setText(label, text);
}

/* Slot 0x4C: shows the label and its shown glyphs side by side under root */
void Label_Show(Label *label, s32 root, ScreenPoint *origin) {
    ScreenPoint pos;
    Glyph **p;
    s32 i;

    if (label->parent == 0) {
        Glyph_GetVtbl()->show(label, root, origin);
        pos = *origin;
        p = &label->glyphs[label->firstShown];
        for (i = label->firstShown; i < label->firstShown + label->shownCount; i++) {
            if (label->gapAt != 0 && i == label->gapAt) {
                pos.x += 0x10;
            }
            (*p)->vtbl->show(*p, label, &pos);
            pos.x += label->spacing;
            p++;
        }
    }
}

/* Slot 0x50: hides the shown glyphs, then the label */
void Label_Hide(Label *label) {
    s32 i;
    Glyph **p;
    Glyph *glyph;

    if (label->parent != 0) {
        if (label->glyphs != NULL) {
            p = &label->glyphs[label->firstShown];
            for (i = label->firstShown; i < label->firstShown + label->shownCount; i++) {
                glyph = *p++;
                glyph->vtbl->hide(glyph);
            }
        }
        Glyph_GetVtbl()->hide(label);
    }
}

/* Slot 0x60: sets the visibility of the shown glyphs */
s32 Label_SetVisible(Label *label, void *visible, s32 previous) {
    s32 i;
    Glyph **p;
    Glyph *glyph;

    p = &label->glyphs[label->firstShown];
    for (i = label->firstShown; i < label->firstShown + label->shownCount; i++) {
        glyph = *p++;
        previous = glyph->vtbl->setVisible(glyph, visible, previous);
    }
    return previous;
}

/* Slot 0xB8: sets the color of the shown glyphs */
void Label_SetColor(Label *label, s32 color) {
    s32 i;
    Glyph **p;
    Glyph *glyph;

    p = &label->glyphs[label->firstShown];
    for (i = label->firstShown; i < label->firstShown + label->shownCount; i++) {
        glyph = *p++;
        glyph->vtbl->setColor(glyph, color);
    }
}

/* Slot 0xBC: moves a shown label and lays out every glyph from origin */
void Label_SetPosition(Label *label, ScreenPoint *origin) {
    ScreenPoint pos;
    Glyph **p;
    Glyph *glyph;
    s32 i;

    if (label->parent != 0) {
        Glyph_GetVtbl()->setPosition(label, origin);
        pos = *origin;
        p = label->glyphs;
        for (i = 0; i < label->count; p++, i++) {
            glyph = *p;
            glyph->vtbl->setPosition(glyph, &pos);
            pos.x += label->spacing;
        }
    }
}

/* Slot 0xC4: the character of one glyph */
void Label_SetChar(Label *label, s32 c, s32 index) {
    Glyph **slot = &label->glyphs[index];
    Glyph *glyph = *slot;

    glyph->vtbl->setChar(glyph, c, slot);
}

void Label_EmptySlotC8(void) {
}

/* Slot 0xCC: one character per glyph, up to the end of text */
void Label_SetText(Label *label, u8 *text) {
    Glyph **p = label->glyphs;

    if (text != NULL) {
        while (*text != 0) {
            Glyph *glyph = *p;

            ((void (*)(Glyph *, u8))glyph->vtbl->setChar)(glyph, *text++);
            p++;
        }
    }
}

void Label_EmptySlotD0(void) {
}

/* Slot 0xD4 */
void Label_SetSpacing(Label *label, s32 spacing) {
    label->spacing = spacing;
}

LabelVtbl *Label_GetVtbl(void) {
    return (LabelVtbl *)g_labelVtbl;
}

s8 *Text_Decode(s8 *dst, u8 *src) {
    s8 *end = dst;
    s8 *out;
    u8 c;
    s32 value;
    s32 k;

    c = *src++;
    if (c != 0) {
        k = 0x40;
        out = dst;
        do {
            out++;
            c = *src;
            end++;
            if (c >= 0x80 || c == k) {
                value = c - 0x20;
            } else {
                value = c - 0x1F;
            }
            out[-1] = value;
            src++;
        } while (*src++ != 0);
    }
    *end = 0;
    return end;
}

s8 *Text_Encode(s8 *dst, u8 *src) {
    s8 *next;
    s8 *out;
    u8 c;
    s32 hi;
    s32 lo;

    next = dst;
    out = dst;
    while (*src != 0) {
        next++;
        hi = 0x81;
        if (*src >= 0x30) {
            hi = 0x82;
        }
        *out = hi;
        out = next;
        c = *src;
        next++;
        if (c >= 0x60 || c == 0x20) {
            lo = c + 0x20;
        } else {
            lo = c + 0x1F;
        }
        src++;
        *out = lo;
        out = next;
    }
    *next = 0;
    return next;
}

void Text_FormatNumber(s8 *dst, s32 value, s32 width, s32 noPad) {
    char digits[width + 1];
    char padded[width + 1];
    s32 pad;
    u8 *src;

    pad = strlen(strcpy(digits, itoa(value)));
    pad = width - pad;
    if (noPad == 0) {
        memset(padded, 0x30, width);
        strcpy(padded + pad, digits);
    }
    src = padded;
    if (noPad != 0) {
        src = digits;
    }
    Text_Encode(dst, src);
}

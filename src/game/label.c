#include "common.h"
#include "game/label.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/glyph.h"

/*
 * Label: a row of character glyphs, a 2D widget drawn by the scene tree (src/game/scene_draw.c).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* A glyph (vtable g_glyphVtbl, src/game/glyph.c): one character sprite, and the base of Label */
typedef struct Glyph Glyph;
typedef struct GlyphVtbl {
    u8 pad_00[0x8];
    void (*init)(void *glyph, Tim *font, s32 c); /* 0x08 */
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

static LabelVtbl *Label_GetVtbl(void);
extern LabelVtbl g_labelVtbl;

/* new Label(font, count, text) */
Label *Label_Create(Tim *font, s32 count, char *text) {
    Label *label = Heap_Alloc(0xB8);

    if (label != NULL) {
        Label_GetVtbl()->init(label, font, count, text);
        return label;
    }
    return NULL;
}

/* Slot 0x08: a space glyph of font with count space glyphs under it, then slot 0x40 with the text */
void Label_Construct(Label *label, Tim *font, s32 count, char *text) {
    Glyph **glyphs;
    s32 i;

    Glyph_GetVtbl()->init(label, font, 0x20);
    label->vtbl = Label_GetVtbl();
    label->count = count;
    label->shownCount = count;
    label->firstShown = 0;
    label->gapAt = 0;
    glyphs = Heap_Alloc(count * 4);
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
void Label_Init(Label *label, char *text) {
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

static LabelVtbl *Label_GetVtbl(void) {
    return &g_labelVtbl;
}

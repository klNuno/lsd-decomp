#include "common.h"
#include "game/heap.h"
#include "game/comment_object.h"
#include "game/file_base.h"
#include "game/tim.h"
#include "game/label.h"
#include "game/text.h"
#include "game/glyph.h"
#include "game/screen_sprite.h"
#include "game/sound_bank.h"
#include "psyq/libc.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/* Comment keyboard object (0x4C bytes). Its vtable is g_commentVtbl. */
typedef struct CommentObject CommentObject;
typedef struct CommentVtbl CommentVtbl;
struct CommentVtbl {
    s32 classWord;                              /* 0x00 first word, value 0x10 in the data, meaning unknown */
    u8 pad_04[0x08 - 0x04];                  /* 0x04 base Object slot, not used in this unit */
    void (*init)(CommentObject *, u8 *, s32);                 /* 0x08 CommentObject_Init */
    void (*destroy)(CommentObject *);                         /* 0x0C CommentObject_Destroy */
    void (*watch)(CommentObject *, s32 **);                   /* 0x10 CommentObject_Watch */
    void (*unwatch)(CommentObject *, s32 **);                 /* 0x14 CommentObject_Unwatch */
    void (*unwatchAll)(CommentObject *);                      /* 0x18 CommentObject_UnwatchAll */
    u8 pad_1C[0x30 - 0x1C];                  /* 0x1C to 0x2F base Object slots */
    void (*notify)(CommentObject *, s32);    /* 0x30 base notify, setState case 4 passes the state */
    u8 pad_34[0x38 - 0x34];                  /* 0x34 base Object slot */
    void (*onNotify)(CommentObject *, s32 **, s32);           /* 0x38 CommentObject_OnNotify */
    u8 pad_3C[0x40 - 0x3C];                  /* 0x3C not used by this unit */
    void (*setText)(CommentObject *, u8 *, s32);              /* 0x40 CommentObject_SetText */
    void (*open)(CommentObject *, s32);               /* 0x44 CommentObject_Open */
    void (*close)(CommentObject *);                      /* 0x48 CommentObject_Close, deletes the three widgets */
    void (*watchPair)(CommentObject *, s32 **, s32 **, SoundBank *);  /* 0x4C CommentObject_WatchPair */
    void (*unwatchPair)(CommentObject *);                      /* 0x50 CommentObject_UnwatchPair */
    void (*setState)(CommentObject *, s32);                    /* 0x54 CommentObject_SetState */
    void (*tick)(CommentObject *, s32 **, s32);                /* 0x58 CommentObject_Tick, called for sender tag 5 */
    void (*onKey)(CommentObject *, s32 **, s32);               /* 0x5C CommentObject_OnKey, called for sender tag 2 */
    void (*playTone)(CommentObject *, s32);                 /* 0x60 CommentObject_PlayTone */
    u8 pad_64[0x88 - 0x64];                  /* 0x64 to 0x87 not used by this unit */
    void (*caretRight)(CommentObject *);                       /* 0x88 CommentObject_CaretRight */
    void (*caretLeft)(CommentObject *);                        /* 0x8C CommentObject_CaretLeft */
    void (*charNext)(CommentObject *);                         /* 0x90 CommentObject_CharNext */
    void (*charPrev)(CommentObject *);                         /* 0x94 CommentObject_CharPrev */
    void (*toggleFlag)(CommentObject *);                       /* 0x98 CommentObject_ToggleFlag */
    void (*resetChar)(CommentObject *);                        /* 0x9C CommentObject_ResetChar */
    void (*clearText)(CommentObject *);                       /* 0xA0 CommentObject_ClearText */
    void (*setCaretPos)(CommentObject *, s32, s32);            /* 0xA4 CommentObject_SetCaretPos, caret index and refresh flag */
    void (*setChar)(CommentObject *, s32, s32, s32);           /* 0xA8 CommentObject_SetChar, caret, charIndex and refresh flag */
};

struct CommentObject {
    CommentVtbl *vtbl;                       /* 0x00 */
    ListNode *watched;                       /* 0x04 base Object */
    ListNode *watchers;                      /* 0x08 base Object */
    s32 mode;                                /* 0x0C setText: mode 1 copies with Text_Decode and halves textLength */
    s32 textLength;                          /* 0x10 strlen of the initial text (init) */
    s32 alphabetLength;                      /* 0x14 length of the alphabet g_alphabet (init) */
    s32 caret;                               /* 0x18 caret index, zeroed by setText, bounded by textLength */
    s32 charIndex;                           /* 0x1C alphabet index, zeroed by setText, bounded by alphabetLength */
    s32 repeatOnHold;                              /* 0x20 toggled by CommentObject_ToggleFlag */
    u8 *sourceText;                          /* 0x24 source string read by setText */
    s8 *textBuf;                             /* 0x28 Heap_Alloc(textLength + 4) in init, freed in destroy */
    s32 state;                               /* 0x2C */
    s32 tickCount;                           /* 0x30 ticks spent in states 2 and 3, zeroed by setState */
    s32 **pad;                        /* 0x34 sender stored by watch when its tag is 2, key codes go to slot 0x5C */
    s32 **clock;                        /* 0x38 sender stored by watch when its tag is 5, slot 0x58 */
    SoundBank *sound;                        /* 0x3C the card's sound bank, slot 0x80 plays the tones */
    Glyph *caretGlyph;                       /* 0x40 Glyph_Create(font, '_'), moved by SetCaretPos */
    Label *textLabel;                        /* 0x44 Label_Create from the FONTICON font, showing textBuf */
    ScreenSprite *inputBox;                  /* 0x48 the COMINPUT image, NULL until Open */
};

static CommentVtbl *CommentObject_GetVtbl(void);
s32 g_commentOriginX;
s32 g_commentOriginY;
u8 *g_alphabet;
static void CommentObject_ClearSenders(CommentObject *obj);
extern CommentVtbl g_commentVtbl;
extern s8 g_widgetPrefix[];
extern s8 g_widgetSuffix[];
extern s32 g_glyphColor[];
extern s32 g_inputBoxPos[];
extern s32 g_commentTextPos[];
extern SpriteRect g_inputBoxRect;

void *CommentObject_New(u8 *text, s32 mode) {
    void *obj;

    obj = Heap_Alloc(0x4C);
    if (obj != NULL) {
        CommentObject_GetVtbl()->init(obj, text, mode);
        return obj;
    }
    return NULL;
}

void CommentObject_Init(CommentObject *obj, u8 *text, s32 mode) {
    u8 *alpha;
    s32 alphabetLen;
    s32 textLen;

    Object_GetBaseVtbl()->init(obj);
    obj->vtbl = CommentObject_GetVtbl();
    textLen = strlen(text);
    obj->textLength = textLen;
    obj->textBuf = Heap_Alloc(textLen + 4);
    alpha = g_alphabet;
    alphabetLen = 0;
    if (*alpha != 0) {
        do {
            alpha++;
            alphabetLen++;
        } while (*alpha != 0);
    }
    obj->alphabetLength = alphabetLen;
    CommentObject_ClearSenders(obj);
    obj->vtbl->setText(obj, text, mode);
}

static void CommentObject_ClearSenders(CommentObject *obj) {
    obj->pad = NULL;
    obj->clock = NULL;
    obj->inputBox = 0;
}

void CommentObject_Destroy(CommentObject *obj) {
    Heap_Free(obj->textBuf);
    Object_GetBaseVtbl()->destroy(obj);
}

void CommentObject_Watch(CommentObject *obj, s32 **sender) {
    s32 tag;

    if (sender != NULL) {
        Object_GetBaseVtbl()->watch(obj, sender);
        tag = **sender & 0xF;
        if (tag == 2) {
            obj->pad = sender;
            return;
        }
        if (tag == 5) {
            obj->clock = sender;
        }
    }
}

void CommentObject_Unwatch(CommentObject *obj, s32 **sender) {
    s32 tag;

    if (sender != NULL) {
        tag = **sender & 0xF;
        if (tag == 2) {
            obj->pad = NULL;
        } else if (tag == 5) {
            obj->clock = NULL;
        }
        Object_GetBaseVtbl()->unwatch(obj, sender);
    }
}

void CommentObject_UnwatchAll(CommentObject *obj) {
    obj->pad = 0;
    obj->clock = 0;
    obj->inputBox = 0;
    Object_GetBaseVtbl()->unwatchAll(obj);
}

void CommentObject_OnNotify(CommentObject *obj, s32 **sender, s32 value) {
    s32 tag;

    Object_GetBaseVtbl()->onNotify(obj, sender, value);
    tag = **sender & 0xF;
    if (tag == 2) {
        obj->vtbl->onKey(obj, sender, value);
    } else if (tag == 5) {
        obj->vtbl->tick(obj, sender, value);
    }
}

void CommentObject_SetText(CommentObject *obj, u8 *text, s32 mode) {
    obj->mode = mode;
    obj->sourceText = text;
    obj->caret = 0;
    obj->charIndex = 0;
    if (mode == 1) {
        Text_Decode(obj->textBuf, text);
        obj->textLength = obj->textLength / 2;
    } else {
        strcpy(obj->textBuf, text);
    }
}

INCLUDE_RODATA("asm/nonmatchings/game/comment_object", g_alphabetText);

void CommentObject_Open(CommentObject *obj, s32 parent) {
    s8 nameBuf[0x20];
    Tim *inputWidget;
    ScreenSprite *box;
    Label *label;
    Glyph *glyph;
    Tim *fontWidget;

    if ((parent != 0) && (obj->inputBox == NULL)) {
        inputWidget = Tim_New(File_JoinPath(nameBuf, "COMINPUT", g_widgetPrefix, g_widgetSuffix));
        inputWidget->vtbl->upload(inputWidget);
        obj->inputBox = ScreenSprite_Create(inputWidget, &g_inputBoxRect, 0);
        inputWidget->vtbl->base.delete_(inputWidget);
        box = obj->inputBox;
        box->vtbl->attach(box, parent, g_inputBoxPos);
        fontWidget = Tim_New(File_JoinPath(nameBuf, "FONTICON", g_widgetPrefix, g_widgetSuffix));
        fontWidget->vtbl->upload(fontWidget);
        obj->textLabel = Label_Create(fontWidget, obj->textLength, obj->textBuf);
        obj->caretGlyph = Glyph_Create(fontWidget, 0x5F);
        fontWidget->vtbl->base.delete_(fontWidget);
        label = obj->textLabel;
        label->vtbl->show(label, parent, g_commentTextPos);
        label = obj->textLabel;
        label->vtbl->setColor(label, g_glyphColor);
        glyph = obj->caretGlyph;
        glyph->vtbl->attach(glyph, parent, &g_commentOriginX);
    }
}

void CommentObject_Close(CommentObject *obj) {
    ScreenSprite *box;
    Label *label;
    Glyph *glyph;

    box = obj->inputBox;
    if (box != NULL) {
        obj->inputBox = box->vtbl->delete_(box);
        label = obj->textLabel;
        label->vtbl->delete_(label);
        glyph = obj->caretGlyph;
        glyph->vtbl->delete_(glyph);
    }
}

void CommentObject_WatchPair(CommentObject *obj, s32 **pad, s32 **clock, SoundBank *sound) {
    obj->vtbl->watch(obj, pad);
    obj->vtbl->watch(obj, clock);
    obj->sound = sound;
    obj->state = 0;
    obj->repeatOnHold = 0;
}

void CommentObject_UnwatchPair(CommentObject *obj) {
    obj->vtbl->unwatch(obj, obj->pad);
    obj->vtbl->unwatch(obj, obj->clock);
    obj->sound = 0;
}

void CommentObject_SetState(CommentObject *obj, s32 newState) {
    obj->tickCount = 0;
    switch (newState) {
    case 2:
    case 3:
        obj->vtbl->unwatch(obj, obj->pad);
        obj->vtbl->close(obj);
        obj->state = newState;
        break;
    case 4:
        obj->vtbl->notify(obj, obj->state);
        break;
    }
}

/* Tick: after the first tick in states 2 and 3, each tick asks for setState 4. */
void CommentObject_Tick(CommentObject *obj) {
    s32 state;
    s32 prevCount;

    state = obj->state;
    if (state < 4) {
        if (state >= 2) {
            prevCount = obj->tickCount;
            obj->tickCount = prevCount + 1;
            if (prevCount != 0) {
                obj->vtbl->setState(obj, 4);
            }
        }
    }
}

/* Key handler. keyCode is the third argument. The sender argument is unused. */
void CommentObject_OnKey(CommentObject *obj, s32 sender, s32 keyCode) {
    switch (keyCode) {
    case 25:
        if (obj->mode == 1) {
            Text_Encode(obj->sourceText, obj->textBuf);
        } else {
            strcpy(obj->sourceText, obj->textBuf);
        }
        obj->vtbl->playTone(obj, 0x10);
        obj->vtbl->setState(obj, 2);
        break;
    case 23:
        obj->vtbl->playTone(obj, 0x10);
        obj->vtbl->setState(obj, 3);
        break;
    case 32:
        obj->vtbl->clearText(obj);
        break;
    case 31:
        obj->vtbl->resetChar(obj);
        break;
    case 28:
        obj->vtbl->toggleFlag(obj);
        break;
    case 21:
        if (obj->repeatOnHold == 0) {
            obj->vtbl->caretRight(obj);
        }
        break;
    case 5:
        if (obj->repeatOnHold != 0) {
            obj->vtbl->caretRight(obj);
        }
        break;
    case 20:
        if (obj->repeatOnHold == 0) {
            obj->vtbl->caretLeft(obj);
        }
        break;
    case 4:
        if (obj->repeatOnHold != 0) {
            obj->vtbl->caretLeft(obj);
        }
        break;
    case 18:
        if (obj->repeatOnHold == 0) {
            obj->vtbl->charNext(obj);
        }
        break;
    case 2:
        if (obj->repeatOnHold != 0) {
            obj->vtbl->charNext(obj);
        }
        break;
    case 19:
        if (obj->repeatOnHold == 0) {
            obj->vtbl->charPrev(obj);
        }
        break;
    case 3:
        if (obj->repeatOnHold != 0) {
            obj->vtbl->charPrev(obj);
        }
        break;
    }
}

void CommentObject_PlayTone(CommentObject *obj, s32 tone) {
    SoundBank *sound;

    sound = obj->sound;
    if (sound != NULL) {
        sound->vtbl->playTone(sound, tone, 0x60, 0x60);
    }
}

void CommentObject_CaretRight(CommentObject *obj) {
    s32 nextCaret;
    s32 prevCaret;

    if (obj->inputBox != 0) {
        prevCaret = obj->caret;
        nextCaret = prevCaret + 1;
        obj->caret = nextCaret;
        if (nextCaret < obj->textLength) {
            obj->vtbl->setCaretPos(obj, nextCaret, 1);
            return;
        }
        obj->caret = prevCaret;
    }
}

void CommentObject_CaretLeft(CommentObject *obj) {
    s32 prevCaret;
    s32 nextCaret;

    if (obj->inputBox != 0) {
        prevCaret = obj->caret;
        nextCaret = prevCaret - 1;
        obj->caret = nextCaret;
        if (nextCaret >= 0) {
            obj->vtbl->setCaretPos(obj, nextCaret, 1);
            return;
        }
        obj->caret = prevCaret;
    }
}

void CommentObject_CharNext(CommentObject *obj) {
    s32 nextIndex;

    if (obj->inputBox != 0) {
        nextIndex = obj->charIndex + 1;
        obj->charIndex = nextIndex;
        if (nextIndex < obj->alphabetLength) {
            obj->vtbl->setChar(obj, obj->caret, nextIndex, 1);
            return;
        }
        obj->charIndex = 0;
    }
}

void CommentObject_CharPrev(CommentObject *obj) {
    s32 nextIndex;

    if (obj->inputBox != 0) {
        nextIndex = obj->charIndex - 1;
        obj->charIndex = nextIndex;
        if (nextIndex > 0) {
            obj->vtbl->setChar(obj, obj->caret, nextIndex, 1);
            return;
        }
        obj->charIndex = obj->alphabetLength;
    }
}

void CommentObject_ToggleFlag(CommentObject *obj) {
    if (obj->inputBox != 0) {
        obj->repeatOnHold ^= 1;
    }
}

void CommentObject_ResetChar(CommentObject *obj) {
    if (obj->inputBox != 0) {
        obj->charIndex = 0;
        obj->vtbl->setChar(obj, obj->caret, 0, 1);
    }
}

void CommentObject_ClearText(CommentObject *obj) {
    s32 index;

    if (obj->inputBox != 0) {
        obj->charIndex = 0;
        for (index = obj->textLength - 1; index >= 0; index--) {
            obj->caret = index;
            obj->vtbl->setChar(obj, index, obj->charIndex, 0);
        }
        obj->vtbl->setCaretPos(obj, obj->caret, 1);
    }
}

void CommentObject_SetCaretPos(CommentObject *obj, s32 caret, s32 withTone) {
    s32 pos[2];
    Glyph *glyph;

    if (obj->inputBox != 0) {
        pos[1] = g_commentOriginY;
        pos[0] = caret * 7 + g_commentOriginX;
        glyph = obj->caretGlyph;
        glyph->vtbl->setPosition(glyph, pos);
        obj->caret = caret;
        if (withTone != 0) {
            obj->vtbl->playTone(obj, 0);
        }
    }
}

void CommentObject_SetChar(CommentObject *obj, s32 caret, s32 charIndex, s32 withTone) {
    Label *label;

    if (obj->inputBox != 0) {
        obj->textBuf[caret] = g_alphabet[charIndex];
        label = obj->textLabel;
        label->vtbl->setChar(label, g_alphabet[charIndex], caret);
        obj->caret = caret;
        obj->charIndex = charIndex;
        if (withTone != 0) {
            obj->vtbl->playTone(obj, 0);
        }
    }
}

static CommentVtbl *CommentObject_GetVtbl(void) {
    return &g_commentVtbl;
}

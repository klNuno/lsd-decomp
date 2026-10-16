#include "common.h"
#include "game/heap.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/* Comment keyboard object (0x4C bytes). Its vtable is g_commentVtbl. */
typedef struct CommentObject CommentObject;
typedef struct CommentVtbl CommentVtbl;
/* Widget owned by the comment object (FONTICON glyphs and COMINPUT). */
typedef struct CommentWidget CommentWidget;
typedef struct CommentWidgetVtbl CommentWidgetVtbl;

struct CommentWidgetVtbl {
    s32 unk_00;
    void *(*delete_)(CommentWidget *);       /* 0x04 same slot as scene.h WidgetVtbl delete_ */
    u8 pad_08[0x4C - 0x08];
    void (*attach)(CommentWidget *, s32, void *); /* 0x4C SceneNode_Attach and its overrides (ScreenSprite_Attach, Label_Show): parent, position */
    u8 pad_50[0x78 - 0x50];
    void (*unk_78)(CommentWidget *);         /* 0x78 called on each widget right after it is created */
    u8 pad_7C[0x80 - 0x7C];
    void (*unk_80)(CommentWidget *, s32, s32, s32);  /* 0x80 called on the box object at CommentObject 0x3C */
    u8 pad_84[0xB8 - 0x84];
    void (*setColor)(CommentWidget *, void *);   /* 0xB8 same slot as scene.h setColor, called with g_glyphColor */
    void (*setPosition)(CommentWidget *, void *);  /* 0xBC same slot as scene.h setPosition */
    u8 pad_C0[0xC4 - 0xC0];
    void (*setChar)(CommentWidget *, s32, s32);  /* 0xC4 Label_SetChar: one glyph of g_alphabet at the caret */
};

struct CommentWidget {
    CommentWidgetVtbl *vtbl;                 /* 0x00 */
};

struct CommentVtbl {
    s32 unk_00;                              /* 0x00 first word, value 0x10 in the data, meaning unknown */
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
    void (*buildWidgets)(CommentObject *, s32);               /* 0x44 CommentObject_BuildWidgets */
    void (*freeWidgets)(CommentObject *);                      /* 0x48 CommentObject_FreeWidgets, deletes the three widgets */
    void (*watchPair)(CommentObject *, s32 **, s32 **, CommentWidget *);  /* 0x4C CommentObject_WatchPair */
    void (*unwatchPair)(CommentObject *);                      /* 0x50 CommentObject_UnwatchPair */
    void (*setState)(CommentObject *, s32);                    /* 0x54 CommentObject_SetState */
    void (*tick)(CommentObject *, s32 **, s32);                /* 0x58 CommentObject_Tick, called for sender tag 5 */
    void (*onKey)(CommentObject *, s32 **, s32);               /* 0x5C CommentObject_OnKey, called for sender tag 2 */
    void (*setBoxValue)(CommentObject *, s32);                 /* 0x60 CommentObject_SetBoxValue */
    u8 pad_64[0x88 - 0x64];                  /* 0x64 to 0x87 not used by this unit */
    void (*caretRight)(CommentObject *);                       /* 0x88 CommentObject_CaretRight */
    void (*caretLeft)(CommentObject *);                        /* 0x8C CommentObject_CaretLeft */
    void (*charNext)(CommentObject *);                         /* 0x90 CommentObject_CharNext */
    void (*charPrev)(CommentObject *);                         /* 0x94 CommentObject_CharPrev */
    void (*toggleFlag)(CommentObject *);                       /* 0x98 CommentObject_ToggleFlag */
    void (*resetChar)(CommentObject *);                        /* 0x9C CommentObject_ResetChar */
    void (*refreshAll)(CommentObject *);                       /* 0xA0 CommentObject_RefreshAll */
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
    s32 unk_20;                              /* 0x20 toggled by CommentObject_ToggleFlag */
    u8 *sourceText;                          /* 0x24 source string read by setText */
    s8 *textBuf;                             /* 0x28 Heap_Alloc(textLength + 4) in init, freed in destroy */
    s32 state;                               /* 0x2C */
    s32 tickCount;                           /* 0x30 ticks spent in states 2 and 3, zeroed by setState */
    s32 **senderTag2;                        /* 0x34 sender stored by watch when its tag is 2, key codes go to slot 0x5C */
    s32 **senderTag5;                        /* 0x38 sender stored by watch when its tag is 5, slot 0x58 */
    CommentWidget *boxWidget;                /* 0x3C box object, its slot 0x80 is called with 0x60 */
    CommentWidget *caretGlyph;              /* 0x40 Glyph_Create(font, '_'), moved by SetCaretPos */
    CommentWidget *textLabel;               /* 0x44 Label_Create from the FONTICON font, showing textBuf */
    CommentWidget *inputBox;                /* 0x48 ScreenSprite of the COMINPUT image, NULL until BuildWidgets */
};

extern void Heap_Free(s32);
extern ObjectVtbl *Object_GetBaseVtbl(void);
extern void *Heap_Alloc(s32 size);
CommentVtbl *CommentObject_GetVtbl(void);
s8 *Text_Decode(s8 *dst, u8 *src);
s8 *strcpy(s8 *dst, u8 *src);
s32 g_commentOriginX;
s32 g_commentOriginY;
u8 *g_alphabet;
void CommentObject_ClearSenders(CommentObject *obj);
extern s32 strlen(u8 *);
extern u8 g_commentVtbl[];
extern s8 *File_JoinPath(s8 *, s8 *, s8 *, s8 *);
extern CommentWidget *Tim_New(s32);
extern CommentWidget *ScreenSprite_Create(CommentWidget *, s32 *, s32);
extern s32 Label_Create(s32, s32, s32);
extern void *Glyph_Create(s32, u8);
extern s8 g_widgetPrefix[];
extern s8 g_widgetSuffix[];
extern s32 g_glyphColor[];
extern s32 g_inputShowArg[];
extern s32 g_fontShowArg[];
extern s32 g_inputBoxRect[];
s8 *Text_Encode(s8 *dst, u8 *src);

void *CommentObject_New(s32 text, s32 mode) {
    void *obj;

    obj = Heap_Alloc(0x4C);
    if (obj != NULL) {
        CommentObject_GetVtbl()->init(obj, (u8 *)text, mode);
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

void CommentObject_ClearSenders(CommentObject *obj) {
    obj->senderTag2 = NULL;
    obj->senderTag5 = NULL;
    obj->inputBox = 0;
}

void CommentObject_Destroy(CommentObject *obj) {
    Heap_Free((s32)obj->textBuf);
    Object_GetBaseVtbl()->destroy(obj);
}

void CommentObject_Watch(CommentObject *obj, s32 **sender) {
    s32 tag;

    if (sender != NULL) {
        Object_GetBaseVtbl()->watch(obj, sender);
        tag = **sender & 0xF;
        if (tag == 2) {
            obj->senderTag2 = sender;
            return;
        }
        if (tag == 5) {
            obj->senderTag5 = sender;
        }
    }
}

void CommentObject_Unwatch(CommentObject *obj, s32 **sender) {
    s32 tag;

    if (sender != NULL) {
        tag = **sender & 0xF;
        if (tag == 2) {
            obj->senderTag2 = NULL;
        } else if (tag == 5) {
            obj->senderTag5 = NULL;
        }
        Object_GetBaseVtbl()->unwatch(obj, sender);
    }
}

void CommentObject_UnwatchAll(CommentObject *obj) {
    obj->senderTag2 = 0;
    obj->senderTag5 = 0;
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

void CommentObject_BuildWidgets(CommentObject *obj, s32 enable) {
    s8 nameBuf[0x20];
    CommentWidget *inputWidget;
    CommentWidget *widget;
    CommentWidget *fontWidget;

    if ((enable != 0) && (obj->inputBox == NULL)) {
        inputWidget = Tim_New((s32)File_JoinPath(nameBuf, "COMINPUT", g_widgetPrefix, g_widgetSuffix));
        inputWidget->vtbl->unk_78(inputWidget);
        obj->inputBox = ScreenSprite_Create(inputWidget, g_inputBoxRect, 0);
        inputWidget->vtbl->delete_(inputWidget);
        widget = obj->inputBox;
        widget->vtbl->attach(widget, enable, g_inputShowArg);
        fontWidget = Tim_New((s32)File_JoinPath(nameBuf, "FONTICON", g_widgetPrefix, g_widgetSuffix));
        fontWidget->vtbl->unk_78(fontWidget);
        obj->textLabel = (CommentWidget *)Label_Create((s32)fontWidget, obj->textLength, (s32)obj->textBuf);
        obj->caretGlyph = Glyph_Create((s32)fontWidget, 0x5F);
        fontWidget->vtbl->delete_(fontWidget);
        widget = obj->textLabel;
        widget->vtbl->attach(widget, enable, g_fontShowArg);
        widget = obj->textLabel;
        widget->vtbl->setColor(widget, g_glyphColor);
        widget = obj->caretGlyph;
        widget->vtbl->attach(widget, enable, &g_commentOriginX);
    }
}

void CommentObject_FreeWidgets(CommentObject *obj) {
    CommentWidget *widget;

    widget = obj->inputBox;
    if (widget != NULL) {
        obj->inputBox = widget->vtbl->delete_(widget);
        widget = obj->textLabel;
        widget->vtbl->delete_(widget);
        widget = obj->caretGlyph;
        widget->vtbl->delete_(widget);
    }
}

void CommentObject_WatchPair(CommentObject *obj, s32 **senderTag2, s32 **senderTag5, CommentWidget *box) {
    obj->vtbl->watch(obj, senderTag2);
    obj->vtbl->watch(obj, senderTag5);
    obj->boxWidget = box;
    obj->state = 0;
    obj->unk_20 = 0;
}

void CommentObject_UnwatchPair(CommentObject *obj) {
    obj->vtbl->unwatch(obj, obj->senderTag2);
    obj->vtbl->unwatch(obj, obj->senderTag5);
    obj->boxWidget = 0;
}

void CommentObject_SetState(CommentObject *obj, s32 newState) {
    obj->tickCount = 0;
    switch (newState) {
    case 2:
    case 3:
        obj->vtbl->unwatch(obj, obj->senderTag2);
        obj->vtbl->freeWidgets(obj);
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
            Text_Encode((s8 *)obj->sourceText, obj->textBuf);
        } else {
            strcpy((s8 *)obj->sourceText, obj->textBuf);
        }
        obj->vtbl->setBoxValue(obj, 0x10);
        obj->vtbl->setState(obj, 2);
        break;
    case 23:
        obj->vtbl->setBoxValue(obj, 0x10);
        obj->vtbl->setState(obj, 3);
        break;
    case 32:
        obj->vtbl->refreshAll(obj);
        break;
    case 31:
        obj->vtbl->resetChar(obj);
        break;
    case 28:
        obj->vtbl->toggleFlag(obj);
        break;
    case 21:
        if (obj->unk_20 == 0) {
            obj->vtbl->caretRight(obj);
        }
        break;
    case 5:
        if (obj->unk_20 != 0) {
            obj->vtbl->caretRight(obj);
        }
        break;
    case 20:
        if (obj->unk_20 == 0) {
            obj->vtbl->caretLeft(obj);
        }
        break;
    case 4:
        if (obj->unk_20 != 0) {
            obj->vtbl->caretLeft(obj);
        }
        break;
    case 18:
        if (obj->unk_20 == 0) {
            obj->vtbl->charNext(obj);
        }
        break;
    case 2:
        if (obj->unk_20 != 0) {
            obj->vtbl->charNext(obj);
        }
        break;
    case 19:
        if (obj->unk_20 == 0) {
            obj->vtbl->charPrev(obj);
        }
        break;
    case 3:
        if (obj->unk_20 != 0) {
            obj->vtbl->charPrev(obj);
        }
        break;
    }
}

void CommentObject_SetBoxValue(CommentObject *obj, s32 value) {
    CommentWidget *box;

    box = obj->boxWidget;
    if (box != NULL) {
        box->vtbl->unk_80(box, value, 0x60, 0x60);
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
        obj->unk_20 ^= 1;
    }
}

void CommentObject_ResetChar(CommentObject *obj) {
    if (obj->inputBox != 0) {
        obj->charIndex = 0;
        obj->vtbl->setChar(obj, obj->caret, 0, 1);
    }
}

void CommentObject_RefreshAll(CommentObject *obj) {
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

void CommentObject_SetCaretPos(CommentObject *obj, s32 caret, s32 refresh) {
    s32 pos[2];
    CommentWidget *widget;

    if (obj->inputBox != 0) {
        pos[1] = g_commentOriginY;
        pos[0] = caret * 7 + g_commentOriginX;
        widget = obj->caretGlyph;
        widget->vtbl->setPosition(widget, pos);
        obj->caret = caret;
        if (refresh != 0) {
            obj->vtbl->setBoxValue(obj, 0);
        }
    }
}

void CommentObject_SetChar(CommentObject *obj, s32 caret, s32 charIndex, s32 refresh) {
    CommentWidget *glyph;

    if (obj->inputBox != 0) {
        obj->textBuf[caret] = g_alphabet[charIndex];
        glyph = obj->textLabel;
        glyph->vtbl->setChar(glyph, g_alphabet[charIndex], caret);
        obj->caret = caret;
        obj->charIndex = charIndex;
        if (refresh != 0) {
            obj->vtbl->setBoxValue(obj, 0);
        }
    }
}

CommentVtbl *CommentObject_GetVtbl(void) {
    return (CommentVtbl *)g_commentVtbl;
}

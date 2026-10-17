#include "common.h"
#include "game/heap.h"
#include "game/string_list.h"
#include "game/file_base.h"
#include "game/tim.h"
#include "game/label.h"
#include "game/text.h"
#include "game/screen_sprite.h"
#include "psyq/libc.h"

/*
 * File boundaries: likely (docs/layout.md)
 */

/* StringList object (0x54 bytes). Its vtable is g_stringListVtbl. */
typedef struct StringList StringList;
typedef struct StringListVtbl StringListVtbl;

struct StringListVtbl {
    s32 classWord;                              /* 0x00 first word, value 0x20 in the data, meaning unknown */
    u8 pad_04[0x08 - 0x04];                  /* 0x04 base Object slot, not used in this file */
    void (*init)(StringList *, char **, s32);                 /* 0x08 StringList_Init */
    void (*destroy)(StringList *);                            /* 0x0C StringList_Destroy */
    void (*watch)();                                          /* 0x10 StringList_Watch */
    void (*unwatch)();                                        /* 0x14 StringList_Unwatch */
    void (*unwatchAll)(StringList *);                         /* 0x18 StringList_UnwatchAll */
    u8 pad_1C[0x30 - 0x1C];                  /* 0x1C to 0x2F base Object slots */
    void (*notify)();                                         /* 0x30 Object_Notify */
    u8 pad_34[0x38 - 0x34];
    void (*onNotify)(StringList *, s32 **, s32);              /* 0x38 StringList_OnNotify */
    u8 pad_3C[0x40 - 0x3C];                  /* 0x3C not used by this file */
    void (*reset)(StringList *);                              /* 0x40 StringList_Reset */
    u8 pad_44[0x48 - 0x44];
    void (*close)();                                          /* 0x48 StringList_Close */
    u8 pad_4C[0x54 - 0x4C];
    void (*setState)();                                        /* 0x54 StringList_SetState */
    void (*tick)(StringList *, s32 **, s32);                /* 0x58 called by onNotify for sender tag 5 */
    void (*onKey)(StringList *, s32 **, s32);                /* 0x5C called by onNotify for sender tag 2 */
    void (*playTone)();                                    /* 0x60 StringList_PlayTone */
    u8 pad_64[0x7C - 0x64];
    void (*scrollRight)();                                    /* 0x7C StringList_ScrollRight */
    void (*scrollLeft)();                                     /* 0x80 StringList_ScrollLeft */
    void (*moveUp)();                                         /* 0x84 StringList_CursorUp */
    void (*moveDown)();                                       /* 0x88 StringList_CursorDown */
    void (*createRows)();                                     /* 0x8C StringList_CreateRows */
    void (*deleteRows)();                                     /* 0x90 StringList_DeleteRows */
    void (*drawRows)();                                       /* 0x94 StringList_RedrawRows */
    void (*moveCursor)();                                     /* 0x98 StringList_MoveHighlight */
};

struct StringList {
    StringListVtbl *vtbl;                    /* 0x00 */
    ListNode *watched;                       /* 0x04 base Object */
    ListNode *watchers;                      /* 0x08 base Object */
    s32 mode;                                /* 0x0C set by init (StringList_Init) */
    s32 count;                               /* 0x10 set by init */
    s32 maxLength;                           /* 0x14 set by init */
    u8 **strings;                            /* 0x18 set by init: a copy of each string */
    s32 *lengths;                            /* 0x1C set by init */
    s32 top;                              /* 0x20 cleared by reset (StringList_Reset) */
    s32 column;                              /* 0x24 cleared by reset (StringList_Reset) */
    s32 cursor;                              /* 0x28 cleared by reset (StringList_Reset) */
    s32 state;                              /* 0x2C not referenced in this unit */
    s32 stateTicks;                              /* 0x30 not referenced in this unit */
    s32 **pad;                        /* 0x34 tag pointer used by watch and unwatch */
    s32 **clock;                        /* 0x38 tag pointer used by watch and unwatch */
    u8 pad_3C[0x50 - 0x3C];                  /* 0x3C to 0x4F not used by this unit */
    s32 background;                              /* 0x50 written by ClearSenders (StringList_ClearSenders) and UnwatchAll (StringList_UnwatchAll) */
};

static StringListVtbl *StringList_GetVtbl(void);
static void StringList_ClearSenders(StringList *list);

void *StringList_New(char **strings, s32 mode) {
    void *list;

    list = Heap_Alloc(0x54);
    if (list != NULL) {
        StringList_GetVtbl()->init(list, strings, mode);
        return list;
    }
    return NULL;
}

void StringList_Init(StringList *list, char **strings, s32 mode) {
    s32 len;
    s32 index;
    char **cursor;
    s32 unused[2];

    index = 0;
    cursor = strings;
    Object_GetBaseVtbl()->init(list);
    list->vtbl = StringList_GetVtbl();

    while (*cursor++ != NULL) {
        index++;
    }
    list->count = index;
    list->strings = Heap_Alloc(index * 4);
    cursor = strings;
    list->lengths = Heap_Alloc(list->count * 4);
    index = 0;
    list->maxLength = 0;

    if (list->count > 0) {
        do {
            len = strlen(*cursor);
            if (mode == 1) {
                len /= 2;
            }
            list->lengths[index] = len;
            list->strings[index] = Heap_Alloc(len + 4);
            if (mode == 1) {
                Text_Decode(list->strings[index], *cursor);
            } else {
                strcpy(list->strings[index], *cursor);
            }
            list->maxLength = (list->maxLength < len) ? len : list->maxLength;
            cursor++;
            index++;
        } while (index < list->count);
    }

    list->mode = mode;
    StringList_ClearSenders(list);
    list->vtbl->reset(list);
}

static void StringList_ClearSenders(StringList *list) {
    list->pad = 0;
    list->clock = 0;
    list->background = 0;
}

void StringList_Destroy(StringList *list) {
    s32 index;

    for (index = 0; index < list->count; index++) {
        Heap_Free(list->strings[index]);
    }
    Heap_Free(list->lengths);
    Heap_Free(list->strings);
    Object_GetBaseVtbl()->destroy(list);
}

void StringList_Watch(StringList *list, s32 **sender) {
    s32 tag;

    if (sender != NULL) {
        Object_GetBaseVtbl()->watch(list, sender);
        tag = **sender & 0xF;
        if (tag == 2) {
            list->pad = sender;
            return;
        }
        if (tag == 5) {
            list->clock = sender;
        }
    }
}

void StringList_Unwatch(StringList *list, s32 **sender) {
    s32 tag;

    if (sender != NULL) {
        tag = **sender & 0xF;
        if (tag == 2) {
            list->pad = NULL;
        } else if (tag == 5) {
            list->clock = NULL;
        }
        Object_GetBaseVtbl()->unwatch(list, sender);
    }
}

void StringList_UnwatchAll(StringList *list) {
    list->pad = 0;
    list->clock = 0;
    list->background = 0;
    Object_GetBaseVtbl()->unwatchAll(list);
}

void StringList_OnNotify(StringList *list, s32 **sender, s32 value) {
    s32 tag;

    Object_GetBaseVtbl()->onNotify(list, sender, value);
    tag = **sender & 0xF;
    if (tag == 2) {
        list->vtbl->onKey(list, sender, value);
    } else if (tag == 5) {
        list->vtbl->tick(list, sender, value);
    }
}

void StringList_Reset(StringList *list) {
    list->top = 0;
    list->column = 0;
    list->cursor = 0;
}

/*
 * The memory card file list window: background CARD\SELECT.TIM, up to 4 visible rows of
 * 26 characters built by Label_Create, the selected row in g_stringListCursorColor (0x80, 0x80, 0), the
 * others in g_stringListRowColor (0x50, 0x50, 0x50). Slots 0x7C to 0x88 scroll it, 0x8C to 0x98 draw it.
 */

/* A row text, the background, a loaded file: the slots called on them here. */
typedef struct CardTextVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();   /* 0x04 Object_Delete */
    u8 pad_08[0x4C - 0x08];
    void (*attach)();      /* 0x4C (obj, parent, position) */
    u8 pad_50[0x78 - 0x50];
    void (*setZSort)();      /* 0x78 called on a file right after Tim_New */
    u8 pad_7C[0xB8 - 0x7C];
    void (*setColor)();   /* 0xB8 g_stringListCursorColor or g_stringListRowColor */
    u8 pad_BC[0xCC - 0xBC];
    void (*setText)();    /* 0xCC */
} CardTextVtbl;

typedef struct CardText {
    CardTextVtbl *vt;
} CardText;

typedef struct CardListOwnerVtbl {
    u8 pad_00[0x80];
    void (*playTone)();
} CardListOwnerVtbl;

typedef struct CardListOwner {
    CardListOwnerVtbl *vt;
} CardListOwner;

/* The StringList object as the window methods read it. */
typedef struct CardList {
    StringListVtbl *vt;
    u8 pad_04[0x10 - 0x04];
    s32 count;            /* 0x10 rows in the list */
    s32 width;            /* 0x14 characters of the longest row */
    u8 **strings;         /* 0x18 the rows (StringList.strings) */
    u8 pad_1C[0x20 - 0x1C];
    s32 top;              /* 0x20 first visible row */
    s32 column;           /* 0x24 first visible character (text base for StringList_FormatRow) */
    s32 cursor;           /* 0x28 selected row */
    s32 state;             /* 0x2C 2 or 3 (setMode) */
    s32 stateTicks;        /* 0x30 */
    s32 pad;            /* 0x34 unwatched by setMode and the destructor */
    s32 clock;
    CardListOwner *sound; /* 0x3C its slot 0x80 plays a tone */
    CardText *rows[4];    /* 0x40 visible rows */
    CardText *background; /* 0x50 CARD\SELECT.TIM, 0 while closed */
} CardList;
extern u8 g_stringListCursorColor[];
extern u8 g_stringListRowColor[];
s32 g_stringListRowX;
s32 g_stringListRowY;
static u8 *StringList_FormatRow(CardList *list, u8 *out, s32 i, s32 top, s32 column);
static void StringList_SetView(CardList *list, s32 top, s32 column, s32 cursor, s32 highlight);
extern s8 g_selectTimName[];
extern s8 g_cardDirName[];
extern s8 g_timExtension[];
extern s32 g_stringListBgPos[];
extern SpriteRect g_stringListBgRect;
extern StringListVtbl g_stringListVtbl;

INCLUDE_RODATA("asm/nonmatchings/game/string_list", g_stringListAlphabetText);

/* Slot 0x44: open the list with background CARD\SELECT.TIM and the rows in FONTICON. */
void StringList_Open(CardList *list, s32 parent) {
    s8 path[0x20];
    Tim *file;
    CardText *background;
    Tim *iconFile;

    if ((parent != 0) && (list->background == NULL)) {
        file = Tim_New(File_JoinPath(path, g_selectTimName, g_cardDirName, g_timExtension));
        file->vtbl->upload(file);
        list->background = (CardText *)ScreenSprite_Create(file, &g_stringListBgRect, 0);
        file->vtbl->base.delete_(file);
        background = list->background;
        background->vt->attach(background, parent, g_stringListBgPos);
        iconFile = Tim_New(File_JoinPath(path, "FONTICON\0\0\0\0\0\0\0", g_cardDirName, g_timExtension));
        iconFile->vtbl->upload(iconFile);
        list->vt->createRows(list, parent, iconFile, list->top, list->column, list->cursor);
        iconFile->vtbl->base.delete_(iconFile);
    }
}

/* Slot 0x48: delete the rows and the background. */
void StringList_Close(CardList *list) {
    CardText *background;

    if (list->background != NULL) {
        list->vt->deleteRows(list);
        background = list->background;
        list->background = background->vt->delete_(background);
    }
}

void StringList_WatchPair(CardList *list, s32 pad, s32 clock, CardListOwner *sound) {
    list->vt->watch(list, pad);
    list->vt->watch(list, clock);
    list->sound = sound;
    list->state = 0;
}

void StringList_UnwatchPair(CardList *list) {
    list->vt->unwatch(list, list->pad);
    list->vt->unwatch(list, list->clock);
    list->sound = 0;
}

void StringList_SetState(CardList *list, s32 mode) {
    list->stateTicks = 0;
    switch (mode) {
    case 2:
    case 3:
        list->vt->unwatch(list, list->pad);
        list->vt->close(list);
        list->state = mode;
        break;
    case 4:
        list->vt->notify(list, list->state);
        break;
    }
}

void StringList_Tick(CardList *list) {
    s32 mode;
    s32 ticks;

    mode = list->state;
    if (mode >= 4) {
        return;
    }
    if (mode < 2) {
        return;
    }
    ticks = list->stateTicks;
    list->stateTicks = ticks + 1;
    if (ticks != 0) {
        list->vt->setState(list, 4);
    }
}

/* Pad codes minus 4: 25 and 23 close the list (modes 2, 3), 5, 4, 18, 19 move and scroll it. */
void StringList_OnKey(CardList *list, s32 sender, s32 code) {
    void (*fn)(CardList *, s32, s32);
    u32 idx = code - 4;

    switch (idx) {
    case 21:
        list->vt->playTone(list, 0x10, idx);
        list->vt->setState(list, 2);
        return;
    case 19:
        list->vt->playTone(list, 0x10, idx);
        list->vt->setState(list, 3);
        return;
    case 1:
        fn = list->vt->scrollRight;
        break;
    case 0:
        fn = list->vt->scrollLeft;
        break;
    case 14:
        fn = list->vt->moveUp;
        break;
    case 15:
        fn = list->vt->moveDown;
        break;
    default:
        return;
    }
    fn(list, sender, idx);
}

void StringList_PlayTone(CardList *list, s32 tone) {
    CardListOwner *owner = list->sound;
    if (owner != NULL) {
        owner->vt->playTone(owner, tone, 0x60, 0x60);
    }
}

/* Slot 0x7C: show one more character on the right while the longest row goes past 26. */
void StringList_ScrollRight(CardList *list) {
    if (list->background != 0 && (list->column + 0x1A) < list->width) {
        list->vt->drawRows(list, list->top, ++list->column, list->cursor, 1);
    }
}

/* Slot 0x80: back one character. */
void StringList_ScrollLeft(CardList *list) {
    s32 column;

    if (list->background != 0) {
        column = list->column - 1;
        if (column >= 0) {
            list->column = column;
            list->vt->drawRows(list, list->top, column, list->cursor, 1);
        }
    }
}

/* Slot 0x84: cursor up, scrolling when it is on the top row. */
void StringList_CursorUp(CardList *list) {
    s32 top;
    s32 cursor;

    if (list->background != 0) {
        if (list->cursor - 1 >= 0) {
            if (list->cursor - list->top > 0) {
                list->vt->moveCursor(list, 0, 1);
                return;
            }
            top = --list->top;
            cursor = --list->cursor;
            list->vt->drawRows(list, top, list->column, cursor, 1);
        }
    }
}

/* Slot 0x88: cursor down, scrolling past the fourth row. */
void StringList_CursorDown(CardList *list) {
    s32 top;
    s32 cursor;
    s32 aboveTop;

    if (list->background != 0) {
        cursor = list->cursor;
        if ((cursor + 1) < list->count) {
            top = list->top;
            aboveTop = top - 1;
            if ((cursor - aboveTop) < 4) {
                list->vt->moveCursor(list, 1, 1);
                return;
            }
            list->top = top + 1;
            list->vt->drawRows(list, top + 1, list->column, ++list->cursor, 1);
        }
    }
}

/* Slot 0x8C: build up to 4 row texts 10 pixels apart, then highlight the cursor row. */
void StringList_CreateRows(CardList *list, s32 parent, Tim *font, s32 top, s32 column, s32 cursor) {
    u8 text[0x1C];
    s32 pos[4];
    s32 i;
    s32 n;
    CardText **row;
    CardText *created;
    CardText *obj;

    if (list->background != 0) {
        pos[0] = g_stringListRowX;
        pos[1] = g_stringListRowY;
        n = list->count;
        row = list->rows;
        if (n >= 5) {
            n = 4;
        }
        i = 0;
        if (n > 0) {
            do {
                StringList_FormatRow(list, text, i, top, column);
                created = (CardText *)Label_Create(font, 0x1A, text);
                *row = created;
                created->vt->attach(created, parent, pos);
                obj = *row;
                i += 1;
                obj->vt->setColor(obj, g_stringListRowColor);
                pos[1] += 0xA;
                row += 1;
            } while (i < n);
        }
        StringList_SetView(list, top, column, cursor, 1);
    }
}

/* Slot 0x90 */
void StringList_DeleteRows(CardList *list) {
    s32 i;
    s32 n;
    CardText *obj;

    if (list->background != 0) {
        n = list->count;
        if (n >= 5) {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            obj = list->rows[i];
            obj->vt->delete_(obj);
            list->rows[i] = NULL;
        }
    }
}

/* Slot 0x94: refill the row texts from top and column. */
void StringList_RedrawRows(CardList *list, s32 top, s32 column, s32 cursor, s32 notify) {
    u8 text[0x20];
    s32 i;
    s32 n;
    CardText **row;
    CardText *obj;

    if (list->background != 0) {
        row = list->rows;
        n = list->count;
        if (n >= 5) {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            StringList_FormatRow(list, text, i, top, column);
            obj = *row;
            obj->vt->setText(obj, text);
            row++;
        }
        StringList_SetView(list, top, column, cursor, 0);
        if (notify != 0) {
            list->vt->playTone(list, 0);
        }
    }
}

/* Copy row (top + i) from character column into out, padded with spaces to 26 characters. */
static u8 *StringList_FormatRow(CardList *list, u8 *out, s32 i, s32 top, s32 column) {
    s32 idx = top + i;
    s32 len;
    s32 j;

    len = strlen(list->strings[idx] + column);
    if (len >= 0x1B) {
        len = 0x1A;
    }
    memcpy(out, list->strings[idx] + column, len);
    for (j = len; j < 0x1A; j++) {
        out[j] = 0x20;
    }
    out[0x1A] = 0;
    return out;
}

static void StringList_SetView(CardList *list, s32 top, s32 column, s32 cursor, s32 highlight) {
    s32 row;
    CardText *obj;

    list->top = top;
    list->column = column;
    list->cursor = cursor;
    if (highlight != 0) {
        row = cursor - top;
        obj = list->rows[row];
        obj->vt->setColor(obj, g_stringListCursorColor, column, row);
    }
}

/* Slot 0x98: move the highlight one row down (down != 0) or up. */
void StringList_MoveHighlight(CardList *list, s32 down, s32 notify) {
    CardText **row;
    CardText *obj;

    if (list->background != 0) {
        row = &list->rows[list->cursor - list->top];
        obj = *row;
        obj->vt->setColor(obj, g_stringListRowColor);
        if (down != 0) {
            row++;
            list->cursor++;
        } else {
            row--;
            list->cursor--;
        }
        obj = *row;
        obj->vt->setColor(obj, g_stringListCursorColor);
        if (notify != 0) {
            list->vt->playTone(list, 0);
        }
    }
}

s32 StringList_GetCursor(CardList *list) {
    return list->cursor;
}

static StringListVtbl *StringList_GetVtbl(void) {
    return &g_stringListVtbl;
}

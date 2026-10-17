#include "common.h"
#include "game/card.h"
#include "game/heap.h"
#include "game/file_base.h"
#include "game/sound_bank.h"
#include "game/tim.h"
#include "game/text.h"
#include "game/screen_sprite.h"
#include "game/menu.h"
#include "game/comment_object.h"
#include "game/string_list.h"
#include "psyq/libapi.h"
#include "psyq/libcard.h"
#include "psyq/libc.h"

/*
 * The memory card object the main menu drives (class Card, vtable g_cardVtbl 0x80086DC4). Types and
 * states: include/game/card.h.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The PS1 save file header: the icon palette and one 16x16 4-bit icon frame. */
typedef struct CardIconPalette {
    u8 b[0x20];
} CardIconPalette;
typedef struct CardIconFrame {
    u8 b[0x80];
} CardIconFrame;

/* The header Card_WriteFileOnce writes, 0x80 bytes plus 0x80 per icon frame. */
typedef struct CardSaveHeader {
    u8 magic[2];               /* 0x00 "SC" */
    u8 iconFlag;               /* 0x02 0x10 + icon frames: (iconFlag << 7) - 0x780 is the header size */
    u8 blocks;                 /* 0x03 8 KB blocks */
    char title[0x60 - 0x04];   /* 0x04 the card title */
    CardIconPalette palette;   /* 0x60 */
    CardIconFrame frames[3];   /* 0x80 */
} CardSaveHeader;

/* The icon TIM (menu.h MenuPicture.tim, CARD\FILEICN1.TIM): its palette and three 16x16 4-bit frames. */
struct CardIconTim {
    u8 pad_00[0x14];
    CardIconPalette palette;   /* 0x14 */
    u8 pad_34[0x40 - 0x34];
    CardIconFrame frames[3];   /* 0x40 */
};

static s32 Card_ForEachEvent(Card *card, s32 (*eventFn)(), s32 critical);
static s32 Card_WaitAnyEvent(s32 *events, s32 count);
static void Card_DisableEvents(Card *card);
static s32 Card_GetInfo();
static s32 Card_ReadDirectory();
static CardVtbl *Card_GetVtbl(void);
extern char g_cardDevice1[];
extern char g_cardDevice0[];
static s32 Card_HasSpaceOnce();
extern char g_cardTempName[];
static char *Card_MakePath(char *buf, s32 port, char *name);
static s32 Card_ReadFileOnce(Card *card, char *name, void *buf, s32 size);
static s32 Card_FindFileOnce(Card *card, char *titleOut, char *name);
extern s32 g_cardEventSpecs[];
static s32 Card_ProbeOnce(Card *card, s32 *error, s32 *changed, s32 *formatted);
static s32 Card_CheckReady();
static void Card_FreeFileList(Card *card);
static void Card_AllocFileList(Card *card);
static void Card_TrimFileList(Card *card);
static void Card_ClearLinks(Card *card);
static void Card_EnableEvents(Card *card);
s32 g_cardCount;
static void Card_ClearEvents(Card *card);
static s32 Card_WaitEvent(Card *card);
extern s8 *g_cardMessageNames[];
extern SpriteRect g_cardMessageRect;
extern s32 g_cardMessagePos[];
extern s8 g_cardPictureDir[];
extern s8 g_timSuffix[];
extern CardVtbl g_cardVtbl;
SjisChar *g_titleLetters;
static s32 Card_WriteFileOnce(Card *card, char *name, char *title, u8 iconFrames, MenuPicture *icon, void *data, s32 size);

/* Allocates a Card (0x84 bytes) and runs Card_Init. */
Card *Card_New(s32 sharePad, s32 port) {
    Card *card;

    card = Heap_Alloc(0x84);
    if (card != NULL) {
        Card_GetVtbl()->init(card, sharePad, port);
        return card;
    }
    return NULL;
}

/* Card slot 0x08: the first card starts the card BIOS (InitCARD, StartCARD, _bu_init). */
void Card_Init(Card *card, s32 sharePad, s32 port) {
    CardVtbl *vtbl;
    s32 count;

    Object_GetBaseVtbl()->init(card);
    vtbl = Card_GetVtbl();
    count = g_cardCount;
    card->vtbl = vtbl;
    g_cardCount = count + 1;
    if (count == 0) {
        InitCARD(sharePad);
        StartCARD();
        _bu_init();
    }
    Card_ClearLinks(card);
    card->vtbl->setPort(card, port);
}

static void Card_ClearLinks(Card *card) {
    card->pad = 0;
    card->clock = 0;
    card->root = 0;
    card->keyboard = 0;
    card->chooser = 0;
}

/* Card slot 0x0C */
void Card_Destroy(Card *card) {
    Object_GetBaseVtbl()->destroy(card);
}

/* Card slot 0x10: keeps the watched object in the field of its class. */
void Card_Watch(Card *card, s32 **object) {
    if (object != NULL) {
        Object_GetBaseVtbl()->watch(card, object);
        if ((**object & 0xF) == 2) {
            card->pad = object;
            return;
        }
        if ((**object & 0xF) == 5) {
            card->clock = object;
            return;
        }
        if ((**object & 0xFF) == 16) {
            card->keyboard = (CardDialog *)object;
            return;
        }
        if ((**object & 0xFF) == 32) {
            card->chooser = (CardDialog *)object;
        }
    }
}

/* Card slot 0x14 */
void Card_Unwatch(Card *card, s32 **object) {
    s32 classWord;

    if (object != NULL) {
        classWord = **object;
        if ((classWord & 0xF) == 2) {
            card->pad = 0;
        } else if ((classWord & 0xF) == 5) {
            card->clock = 0;
        } else if ((classWord & 0xFF) == 0x10) {
            card->keyboard = 0;
        } else if ((classWord & 0xFF) == 0x20) {
            card->chooser = 0;
        }
        Object_GetBaseVtbl()->unwatch(card, object);
    }
}

/* Card slot 0x18 */
void Card_UnwatchAll(Card *card) {
    card->pad = 0;
    card->clock = 0;
    card->root = 0;
    card->keyboard = 0;
    card->chooser = 0;
    Object_GetBaseVtbl()->unwatchAll(card);
}

/* Card slot 0x40 */
void Card_SetPort(Card *card, s32 port) {
    card->port = port;
    card->channel = port << 4;
}

/* Card slot 0x44: the four card BIOS events (class SwCARD 0xF4000001, specs g_cardEventSpecs). */
s32 Card_OpenEvents(Card *card) {
    s32 i;

    EnterCriticalSection();
    for (i = 0; i < 4; i++) {
        card->events[i] = OpenEvent(0xF4000001, g_cardEventSpecs[i], 0x2000, 0);
    }
    ExitCriticalSection();
    Card_EnableEvents(card);
    return 1;
}

/* Card slot 0x48 */
s32 Card_CloseEvents(Card *card) {
    Card_DisableEvents(card);
    Card_ForEachEvent(card, CloseEvent, 1);
    return 1;
}

/* Card slot 0x4C: info and directory, tried up to 11 more times while either fails. */
s32 Card_Probe(Card *card, s32 *error, s32 *changed, s32 *formatted) {
    s32 firstChanged;
    s32 ok;
    s32 tries;

    tries = 0xA;
    *changed = 0;
    ok = Card_ProbeOnce(card, error, &firstChanged, formatted);
    if (ok == 0 || *error != 0 || *formatted == 0) {
        do {
            ok = Card_ProbeOnce(card, error, changed, formatted);
        } while (tries-- != 0 && (ok == 0 || *error != 0 || *formatted == 0));
    }
    *changed |= firstChanged;
    return ok;
}

static s32 Card_ProbeOnce(Card *card, s32 *error, s32 *changed, s32 *formatted) {
    s32 ok;

    ok = Card_GetInfo(card, error, changed);
    if (ok != 0) {
        ok = Card_ReadDirectory(card, error, formatted);
    }
    return ok;
}

/* _card_info, then the event it raised: 0x100 timeout (no card), 0x8000 error, 0x2000 new card. */
static s32 Card_GetInfo(Card *card, s32 *error, s32 *changed) {
    s32 ok;
    s32 result;

    ok = 1;
    *error = 0;
    *changed = 0;
    Card_ClearEvents(card);
    do {
        result = _card_info(card->channel);
    } while (result == 0);
    result = Card_WaitEvent(card);
    if (result == 0x100) {
        ok = 0;
    } else if (result == 0x8000) {
        ok = 0;
        *error = 1;
    } else if (result == 0x2000) {
        *changed = 1;
        _card_clear(card->channel);
    }
    return ok;
}

/* _card_load reads the directory; 0x2000 (new card) here means the card is not formatted. */
static s32 Card_ReadDirectory(Card *card, s32 *error, s32 *formatted) {
    s32 ok;
    s32 result;

    ok = 1;
    *error = 0;
    *formatted = 1;
    Card_ClearEvents(card);
    while (_card_load(card->channel) == 0) {
    }
    result = Card_WaitEvent(card);
    if (result == 0x100) {
        ok = 0;
    } else if (result == 0x8000) {
        ok = 0;
        *error = 1;
    } else if (result == 0x2000) {
        *formatted = 0;
    }
    return ok;
}

/* Card slot 0x50 */
s32 Card_Format(Card *card) {
    s32 ok;
    s32 tries = 10;
    do {
        ok = format(card->port != 0 ? g_cardDevice1 : g_cardDevice0);
        if (ok != 0) {
            break;
        }
    } while (tries-- != 0);
    return ok;
}

/* Card slot 0x54: 1 when the file exists; copies its title to titleOut when that is not 0. */
s32 Card_FindFile(Card *card, char *titleOut, char *name) {
    s32 found;
    s32 tries = 0;

    if ((name == NULL) || (*name == 0)) {
        return 0;
    }
    do {
        found = Card_FindFileOnce(card, titleOut, name);
        if (found != 0) {
            break;
        }
    } while (tries-- != 0);
    return found;
}

static s32 Card_FindFileOnce(Card *card, char *titleOut, char *name) {
    char path[32];
    s32 fd;
    char *header;

    fd = open(Card_MakePath(path, card->port, name), 1);
    if (fd == -1) {
        return 0;
    }
    if (titleOut != 0) {
        header = Heap_Alloc(0x80);
        read(fd, header, 0x80);
        strcpy(titleOut, header + 4);
        Heap_Free(header);
    }
    close(fd);
    return 1;
}

/* Card slot 0x58: the first prefix + suffix with no file, written into buf. */
char *Card_FindFreeName(Card *card, char *buf, char *prefix, char **suffixes) {
    while (*suffixes != NULL) {
        strcpy(buf, prefix);
        strcat(buf, *suffixes);
        if (card->vtbl->findFile(card, 0, buf) == 0) {
            return buf;
        }
        suffixes++;
    }
    return NULL;
}

/* Card slot 0x5C: for each file that exists, its title and its suffix; returns how many. */
s32 Card_ListFiles(Card *card, char **titles, char **found, char *prefix, char **suffixes) {
    char path[32];
    char **suffix;
    s32 count;

    suffix = suffixes;
    count = 0;
    while (*suffix != NULL) {
        strcpy(path, prefix);
        strcat(path, *suffix);
        if (card->vtbl->findFile(card, *titles, path) != 0) {
            count++;
            titles++;
            *found++ = *suffix;
        }
        suffix++;
    }
    return count;
}

/* Card slot 0x60 */
s32 Card_HasSpace(Card *card, u8 iconFrames, s32 size) {
    s32 ok;
    s32 tries = 10;

    do {
        ok = Card_HasSpaceOnce(card, iconFrames, size);
    } while (ok == 0 && tries-- != 0);
    return ok;
}

/* Creates then deletes a TEMP file of the blocks size needs (8 KB blocks, header included). */
static s32 Card_HasSpaceOnce(Card *card, s32 iconFrames, s32 size) {
    char path[32];
    s32 fd;
    u32 blocks;

    blocks = (u32)(size + 0x21FF) >> 13;
    fd = open(Card_MakePath(path, card->port, g_cardTempName), (blocks << 16) | 0x200);
    if (fd != -1) {
        close(fd);
        delete(path);
        return 1;
    }
    return 0;
}

/* Card slot 0x64 */
s32 Card_ReadFile(Card *card, char *name, void *buf, s32 size) {
    s32 ok;
    s32 tries = 10;

    do {
        ok = Card_ReadFileOnce(card, name, buf, size);
    } while (ok == 0 && tries-- != 0);
    return ok;
}

/* Reads a save file's data: header byte 2 (0x10 + icon frames) gives the header size. */
static s32 Card_ReadFileOnce(Card *card, char *name, void *buf, s32 size) {
    char path[32];
    s32 fd;
    CardSaveHeader *header;
    s32 offset;

    fd = open(Card_MakePath(path, card->port, name), 1);
    if (fd == -1) {
        return 0;
    }
    header = Heap_Alloc(0x80);
    read(fd, header, 0x80);
    offset = (header->iconFlag << 7) - 0x780;
    Heap_Free(header);
    lseek(fd, offset, 0);
    read(fd, buf, size);
    close(fd);
    return 1;
}

/* Card slot 0x68: sets the title letter from the file name; clears it again when the write fails. */
s32 Card_WriteFile(Card *card, char *name, char *title, u8 iconFrames, MenuPicture *icon, void *data, s32 size) {
    s32 ok;
    s32 tries;

    tries = 10;
    Card_SetTitleLetter((CardTitle *)title, name);
    do {
        ok = Card_WriteFileOnce(card, name, title, iconFrames, icon, data, size);
    } while (ok == 0 && tries-- != 0);
    if (ok == 0) {
        Card_SetTitleLetter((CardTitle *)title, 0);
    }
    return ok;
}

INCLUDE_RODATA("asm/nonmatchings/game/card", D_8001150C);

INCLUDE_RODATA("asm/nonmatchings/game/card", D_80011518);

INCLUDE_RODATA("asm/nonmatchings/game/card", D_80011524);

/*
 * Writes a save file: the header ("SC", 0x10 + icon frames, blocks, the title, the icon
 * palette and frames from the TIM) then the data, rounded up to 128 bytes.
 */
static s32 Card_WriteFileOnce(Card *card, char *name, char *title, u8 iconFrames, MenuPicture *icon, void *data, s32 size) {
    char pathBuf[0x20];
    char *path;
    s32 fd;
    CardSaveHeader *header;
    struct CardIconTim *tim;

    path = Card_MakePath(pathBuf, card->port, name);
    delete(path);
    fd = open(path, (((u32)(size + 0x21FF) >> 13) << 16) | 0x200);
    if (fd == -1) {
        printf("File not create in WriteFile\n");
        return 0;
    }
    close(fd);
    fd = open(path, 2);
    if (fd == -1) {
        return 0;
    }
    tim = icon->tim;
    header = Heap_Alloc(0x200);
    header->magic[0] = 'S';
    header->magic[1] = 'C';
    header->iconFlag = iconFrames + 0x10;
    header->blocks = (u32)(size + 0x1FFF) >> 13;
    strcpy(header->title, title);
    header->palette = tim->palette;
    header->frames[0] = tim->frames[0];
    header->frames[1] = tim->frames[1];
    header->frames[2] = tim->frames[2];
    write(fd, header, (iconFrames << 7) + 0x80);
    Heap_Free(header);
    write(fd, data, ((u32)(size + 0x7F) >> 7) << 7);
    close(fd);
    return 1;
}

/* "bu00:" or "bu10:" followed by the name. */
static char *Card_MakePath(char *buf, s32 port, char *name) {
    char *device = g_cardDevice0;
    if (port != 0) {
        device = g_cardDevice1;
    }
    memcpy(buf, device, 6);
    strcat(buf, name);
    return buf;
}

static void Card_EnableEvents(Card *card) {
    Card_ForEachEvent(card, EnableEvent, 1);
}

static void Card_DisableEvents(Card *card) {
    Card_ForEachEvent(card, DisableEvent, 1);
}

/* Clears the four events. */
static void Card_ClearEvents(Card *card) {
    Card_ForEachEvent(card, TestEvent, 0);
}

/* Runs eventFn on each event until one returns 0. */
static s32 Card_ForEachEvent(Card *card, s32 (*eventFn)(), s32 critical) {
    s32 ret;
    s32 i;

    if (critical != 0) {
        EnterCriticalSection();
    }
    for (i = 0; i < 4; i++) {
        ret = eventFn(card->events[i]);
        if (ret == 0) {
            break;
        }
    }
    if (critical != 0) {
        ExitCriticalSection();
    }
    return ret;
}

static s32 Card_WaitEvent(Card *card) {
    return Card_WaitAnyEvent(card->events, 4);
}

/* Waits for one of the events and returns its spec. */
static s32 Card_WaitAnyEvent(s32 *events, s32 count) {
    s32 i;

    for (;;) {
        for (i = 0; i < count; i++) {
            if (TestEvent(events[i]) != 0) {
                return g_cardEventSpecs[i];
            }
        }
    }
}

/* Card slot 0x6C: the file name parts, the menu's pad, clock, root and sounds. */
void Card_Open(Card *card, char *prefix, char **suffixes, void *pad, void *clock, s32 root, SoundBank *sound) {
    card->prefix = prefix;
    card->suffixes = suffixes;
    card->titles = 0;
    card->root = root;
    card->sound = sound;
    card->vtbl->watch(card, pad);
    card->vtbl->watch(card, clock);
    card->message = 0;
    card->state = 0;
    card->operation = 0;
}

/* Card slot 0x70 */
void Card_Close(Card *card) {
    card->sound = 0;
    card->root = 0;
    card->vtbl->unwatch(card, card->pad);
    card->vtbl->unwatch(card, card->clock);
}

/* Card slot 0x74: lists the save files, then the chooser (or LOADING once one is confirmed). */
void Card_Load(Card *card, char *fileName, char *title, void *data, s32 size) {
    s32 next;
    s32 found;

    card->fileName = fileName;
    card->title = title;
    card->data = data;
    card->operation = CARD_OP_LOAD;
    card->size = size;
    if (Card_CheckReady() != 0) {
        Card_FreeFileList(card);
        Card_AllocFileList(card);
        found = card->vtbl->listFiles(card, card->titles, card->foundSuffixes, card->prefix, card->suffixes);
        card->fileCount = found;
        if (found != 0) {
            Card_TrimFileList(card);
            next = CARD_STATE_CHOOSE;
            if (card->state == CARD_STATE_LOAD_CONFIRM) {
                next = CARD_STATE_LOADING;
            }
        } else {
            next = CARD_STATE_NOT_FOUND;
            card->fileCount = 0xF;
        }
        card->vtbl->setState(card, next);
    }
}

static void Card_AllocFileList(Card *card) {
    s32 i;

    if (card->titles == NULL) {
        card->titles = Heap_Alloc(0x40);
        for (i = 0; i < 0xF; i++) {
            card->titles[i] = Heap_Alloc(0x41);
        }
        card->foundSuffixes = Heap_Alloc(0x40);
    }
}

/* Frees the title buffers past the files found. */
static void Card_TrimFileList(Card *card) {
    s32 i;

    for (i = card->fileCount; i < 0xF; i++) {
        card->titles[i] = Heap_Free(card->titles[i]);
    }
    card->titles[i] = 0;
}

static void Card_FreeFileList(Card *card) {
    s32 i;

    if (card->titles != NULL) {
        Heap_Free(card->foundSuffixes);
        for (i = 0; i < card->fileCount; i++) {
            Heap_Free(card->titles[i]);
        }
        Heap_Free(card->titles);
        card->titles = NULL;
    }
}

/*
 * Card slot 0x78: an existing file asks to overwrite first; then the comment keyboard, then
 * SAVING. No room for a new file: CARD_STATE_FULL.
 */
void Card_Save(Card *card, char *fileName, char *title, s32 commentStart, u8 iconFrames, MenuPicture *icon, void *data, s32 size) {
    s32 next;

    card->fileName = fileName;
    card->title = title;
    card->commentStart = commentStart;
    card->operation = CARD_OP_SAVE;
    card->iconFrames = iconFrames;
    card->icon = icon;
    card->data = data;
    card->size = size;
    if (Card_CheckReady(card) != 0) {
        if (card->vtbl->findFile(card, 0, fileName) != 0) {
            next = CARD_STATE_OVERWRITE;
            if (card->state == CARD_STATE_OVERWRITE) {
                next = CARD_STATE_KEYBOARD;
            } else if (card->state == CARD_STATE_KEYBOARD) {
                next = CARD_STATE_SAVING;
            }
            card->vtbl->setState(card, next);
        } else if (card->vtbl->hasSpace(card, iconFrames, size) == 0) {
            card->vtbl->setState(card, CARD_STATE_FULL);
        } else {
            card->vtbl->setState(card, card->state == CARD_STATE_KEYBOARD ? CARD_STATE_SAVING : CARD_STATE_KEYBOARD);
        }
    }
}

/* 1 when a formatted card answers; otherwise sets the state that says why and returns 0. */
static s32 Card_CheckReady(Card *card) {
    s32 error;
    s32 changed;
    s32 formatted;
    s32 ok;
    s32 state;

    card->vtbl->openEvents(card);
    ok = card->vtbl->probe(card, &error, &changed, &formatted);
    card->vtbl->closeEvents(card);
    if (ok != 0 && changed == 0 && formatted != 0) {
        return 1;
    }
    if (ok == 0) {
        state = CARD_STATE_NO_CARD;
    } else if (error != 0) {
        state = CARD_STATE_ERROR;
    } else if (changed != 0) {
        state = CARD_STATE_CHANGED;
    } else if (formatted == 0) {
        state = CARD_STATE_UNFORMATTED_SAVE;
        if (card->operation == CARD_OP_LOAD) {
            state = CARD_STATE_UNFORMATTED_LOAD;
        }
    }
    card->vtbl->setState(card, state);
    return 0;
}

/* Card slot 0x38: pad (class 2), clock (5), keyboard (0x10), chooser (0x20). */
void Card_OnNotify(Card *card, s32 **sender, s32 message) {
    CardVtbl *vtbl;
    s32 classWord;

    vtbl = card->vtbl;
    Object_GetBaseVtbl()->onNotify(card, sender, message);
    classWord = **sender;
    if ((classWord & 0xF) == 2) {
        vtbl->onPad(card, sender, message);
    } else if ((classWord & 0xF) == 5) {
        vtbl->onTick(card, sender, message);
    } else if ((classWord & 0xFF) == 0x10) {
        vtbl->onKeyboard(card, sender, message);
    } else if ((classWord & 0xFF) == 0x20) {
        vtbl->onChooser(card, sender, message);
    }
}

/*
 * Card slot 0x7C: tells the watchers (the menu) the new state, shows its picture and runs
 * it. Setting the current state again closes. DONE and CLOSED free the file list and go idle.
 */
void Card_SetState(Card *card, s32 state) {
    CardVtbl *vtbl;
    s32 i;
    char *fileName;
    s32 ok;
    void (*openDialog)(Card *);
    u32 finished;

    vtbl = card->vtbl;
    if (card->state == state) {
        state = CARD_STATE_CLOSED;
    }
    vtbl->notify(card, state);
    vtbl->hideMessage(card);
    vtbl->showMessage(card, state);
    card->ticks = 0;
    switch (state) {
    case CARD_STATE_DO_FORMAT:
        ok = vtbl->format(card);
        state = CARD_STATE_FORMAT_ERROR;
        if (ok != 0) {
            state = CARD_STATE_KEYBOARD;
        }
        goto setNext;
    case CARD_STATE_DO_SAVE:
        fileName = card->fileName;
        if (*fileName == 0) {
            vtbl->findFreeName(card, fileName, card->prefix, card->suffixes);
        }
        ok = vtbl->writeFile(card, card->fileName, card->title, card->iconFrames, card->icon, card->data, card->size);
        state = CARD_STATE_SAVE_ERROR;
        goto checkOk;
    case CARD_STATE_DO_LOAD:
        ok = vtbl->readFile(card, card->fileName, card->data, card->size);
        state = CARD_STATE_LOAD_ERROR;
checkOk:
        if (ok != 0) {
            state = CARD_STATE_DONE;
        }
setNext:
        vtbl->setState(card, state);
        finished = state - CARD_STATE_DONE;
        break;
    case CARD_STATE_KEYBOARD:
        openDialog = vtbl->openKeyboard;
        goto runOpen;
    case CARD_STATE_CHOOSE:
        openDialog = vtbl->openChooser;
runOpen:
        openDialog(card);
    default:
        finished = state - CARD_STATE_DONE;
        break;
    }
    if (finished < 2U) {
        if (card->operation == CARD_OP_LOAD && card->titles != 0) {
            Heap_Free(card->foundSuffixes);
            for (i = 0; i < card->fileCount; i++) {
                Heap_Free(card->titles[i]);
            }
            Heap_Free(card->titles);
            card->titles = 0;
        }
        card->state = 0;
        card->operation = 0;
    } else {
        card->state = state;
    }
}

/* Card slot 0x80: draws CARD\<g_cardMessageNames[state]>.TIM. */
void Card_ShowMessage(Card *card, s32 state) {
    s8 path[0x20];
    s8 *dst;
    s8 *name;
    Tim *picture;
    CardMessage *message;

    if (state < 0x11 && card->root != 0 && card->message == NULL) {
        dst = path;
        dst[0] = 0;
        name = g_cardMessageNames[state];
        strcat(dst, g_cardPictureDir);
        strcat(dst, name);
        strcat(dst, g_timSuffix);
        picture = Tim_New(dst);
        picture->vtbl->upload(picture);
        message = (CardMessage *)ScreenSprite_Create(picture, &g_cardMessageRect, 0);
        card->message = message;
        picture->vtbl->base.delete_(picture);
        message->vt->attach(message, card->root, g_cardMessagePos);
    }
}

/* Card slot 0x84 */
void Card_HideMessage(Card *card) {
    CardMessage *message = card->message;
    if (message != NULL) {
        card->message = message->vt->delete_(message);
    }
}

/* Card slot 0x88: CIRCLE (0x19) confirms, CROSS (0x17) cancels. */
void Card_OnPad(Card *card, void *sender, s32 padCode) {
    if (card->state != 0) {
        if (padCode == 0x19) {
            card->vtbl->onConfirm(card);
        } else if (padCode == 0x17) {
            card->vtbl->onCancel(card);
        }
    }
}

/* Card slot 0x8C */
void Card_PlaySound(Card *card, s32 sound) {
    SoundBank *bank = card->sound;
    if (bank != NULL) {
        bank->vtbl->playTone(bank, sound, 0x7F, 0x7F);
    }
}

/* Card slot 0x90: CIRCLE retries, goes on, starts the format or closes on an error. */
void Card_OnConfirm(Card *card) {
    CardVtbl *vtbl;

    vtbl = card->vtbl;
    switch (card->state) {
    case CARD_STATE_NO_CARD:
    case CARD_STATE_CHANGED:
    case CARD_STATE_OVERWRITE:
    case CARD_STATE_LOAD_CONFIRM:
        vtbl->playSound(card, 0);
        if (card->state == CARD_STATE_LOAD_CONFIRM) {
            strcpy(card->fileName, card->prefix);
            strcat(card->fileName, card->foundSuffixes[card->choice]);
            strcpy(card->title, card->titles[card->choice]);
        }
        if (card->operation == CARD_OP_SAVE) {
            vtbl->save(card, card->fileName, card->title, card->commentStart, card->iconFrames, card->icon, card->data, card->size);
            return;
        } else if (card->operation == CARD_OP_LOAD) {
            vtbl->load(card, card->fileName, card->title, card->data, card->size);
            return;
        }
        break;
    case CARD_STATE_UNFORMATTED_SAVE:
        vtbl->playSound(card, 0);
        vtbl->setState(card, CARD_STATE_FORMATTING);
        break;
    case CARD_STATE_ERROR:
    case CARD_STATE_UNFORMATTED_LOAD:
    case CARD_STATE_FORMAT_ERROR:
    case CARD_STATE_FULL:
    case CARD_STATE_SAVE_ERROR:
    case CARD_STATE_NOT_FOUND:
    case CARD_STATE_LOAD_ERROR:
        vtbl->playSound(card, 0x10);
        vtbl->setState(card, CARD_STATE_CLOSED);
        break;
    }
}

/* Card slot 0x94: CROSS closes the questions. */
void Card_OnCancel(Card *card) {
    switch (card->state) {
    case CARD_STATE_CHANGED:
    case CARD_STATE_UNFORMATTED_SAVE:
    case CARD_STATE_OVERWRITE:
    case CARD_STATE_LOAD_CONFIRM:
        card->vtbl->playSound(card, 0x10);
        card->vtbl->setState(card, CARD_STATE_CLOSED);
        break;
    }
}

/* Card slot 0x98 (clock message): FORMATTING, SAVING and LOADING stay 7 ticks before the work. */
void Card_OnTick(Card *card) {
    if (card->state == CARD_STATE_FORMATTING) {
        if (card->ticks++ >= 6) {
            card->vtbl->setState(card, CARD_STATE_DO_FORMAT);
        }
    } else if (card->state == CARD_STATE_SAVING) {
        if (card->ticks++ >= 6) {
            card->vtbl->setState(card, CARD_STATE_DO_SAVE);
        }
    } else if (card->state == CARD_STATE_LOADING) {
        if (card->ticks++ >= 6) {
            card->vtbl->setState(card, CARD_STATE_DO_LOAD);
        }
    }
}

/* Card slot 0x9C: the comment keyboard on the title text. */
void Card_OpenKeyboard(Card *card) {
    if (card->root != 0 && card->pad != 0) {
        if (card->keyboard == NULL) {
            card->keyboard = CommentObject_New(card->title + card->commentStart * 2, 1);
            card->ownsDialog = 1;
        }
        card->vtbl->watch(card, card->keyboard);
        card->keyboard->vt->open(card->keyboard, card->root);
        card->keyboard->vt->watchPair(card->keyboard, card->pad, card->clock, card->sound);
    }
}

/* Card slot 0xA0 */
void Card_CloseKeyboard(Card *card) {
    CardDialog *keyboard;

    if (card->root != 0 && card->pad != 0) {
        keyboard = card->keyboard;
        if (keyboard != NULL) {
            keyboard->vt->unwatchPair(keyboard);
            card->keyboard->vt->close(card->keyboard);
            if (card->ownsDialog != 0) {
                card->keyboard->vt->delete_(card->keyboard);
                card->keyboard = NULL;
            }
        }
    }
}

/* Card slot 0xA4: keyboard message 2 (done) saves, 3 (cancelled) closes. */
void Card_OnKeyboard(Card *card, void *sender, s32 message) {
    switch (message) {
    case 2:
        card->vtbl->closeKeyboard(card);
        card->vtbl->save(card, card->fileName, card->title, card->commentStart, card->iconFrames, card->icon, card->data, card->size);
        break;
    case 3:
        card->vtbl->closeKeyboard(card);
        card->vtbl->setState(card, CARD_STATE_CLOSED);
        break;
    }
}

/* Card slot 0xA8: the chooser over the titles of the files found. */
void Card_OpenChooser(Card *card) {
    CardDialog *chooser;

    if (card->root != 0 && card->pad != 0) {
        if (card->chooser == 0) {
            card->chooser = StringList_New(card->titles, 1);
            card->ownsDialog = 1;
        }
        card->vtbl->watch(card, card->chooser);
        chooser = card->chooser;
        chooser->vt->open(chooser, card->root);
        chooser = card->chooser;
        chooser->vt->watchPair(chooser, card->pad, card->clock, card->sound);
    }
}

/* Card slot 0xAC */
void Card_CloseChooser(Card *card) {
    CardDialog *chooser;

    if (card->root != 0 && card->pad != 0) {
        chooser = card->chooser;
        if (chooser != NULL) {
            chooser->vt->unwatchPair(chooser);
            chooser = card->chooser;
            chooser->vt->close(chooser);
            if (card->ownsDialog != 0) {
                chooser = card->chooser;
                chooser->vt->delete_(chooser);
                card->chooser = 0;
            }
        }
    }
}

/* Card slot 0xB0: message 2 keeps the file picked and asks to confirm, 3 closes. */
void Card_OnChooser(Card *card, CardDialog *chooser, s32 message) {
    switch (message) {
    case 2:
        card->choice = chooser->vt->getChoice(chooser);
        card->vtbl->closeChooser(card);
        card->vtbl->setState(card, CARD_STATE_LOAD_CONFIRM);
        break;
    case 3:
        card->vtbl->closeChooser(card);
        card->vtbl->setState(card, CARD_STATE_CLOSED);
        break;
    }
}

static CardVtbl *Card_GetVtbl(void) {
    return &g_cardVtbl;
}

/*
 * Puts the letter of the save file in the title: the number after the dash of fileName
 * ("-01" is ａ, "-15" is ｏ). For "-08" and "-09" atoi starts after the 0 (a leading 0 reads
 * as octal). With no name, the letter is blanked.
 */
void Card_SetTitleLetter(CardTitle *title, u8 *fileName) {
    s32 start;
    s32 i;

    if (fileName != NULL) {
        start = 0xD;
        if ((u32)(fileName[0xE] - 0x38) < 2U) {
            start = 0xE;
        }
        title->comment[0] = g_titleLetters[15];
        title->mark = *(CardTitleMark *)&g_titleLetters[15];
        i = atoi(fileName + start) - 1;
        title->mark.letter.c[1] = g_titleLetters[i];
    } else {
        title->mark.letter = *(SjisChar3 *)&g_titleLetters[15];
    }
}

INCLUDE_RODATA("asm/nonmatchings/game/card", D_80011550);

#ifndef GAME_TIX_H
#define GAME_TIX_H

#include "common.h"
#include "game/gs.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * TIX texture set (vtable g_tixVtbl, 0x84 bytes, Tix_Create): a STGxx\TEXA to TEXD.TIX
 * file (docs/discoveries.md "The 40-day texture cycle"). Its 0x24-byte header is
 * {count, offsets[4], sizes[4]} (u32 words); each part is a TimPack read into one shared
 * buffer and uploaded to VRAM. A failed allocation sets +0x80, which the stage turns into the
 * 30-second end (docs/discoveries.md "Glitch textures").
 * +0x40 holds four palette fades: palette i is the 256-colour CLUT row at VRAM y 0x1E0 + 8i;
 * the 7 rows under it are filled with that palette blended toward a colour (Tix_BuildFade).
 */
typedef struct TixVtbl {
    FileVtbl base;
    void (*setFadeShift)();    /* 0x78 Tix_SetFadeShift (self, palette, shift) */
    void (*setFadeColorAll)(); /* 0x7C Tix_SetFadeColorAll (self, color) */
    void (*setFadeColor)();    /* 0x80 Tix_SetFadeColor (self, palette, color) */
} TixVtbl;

typedef struct TixFade {
    u16 shift;      /* 0x00 g_clutFadeShift (3): rows = 1 << shift */
    u16 rows;       /* 0x02 rows of the fade, the source row included */
    s16 x;          /* 0x04 VRAM rect of the palette: 0 */
    s16 y;          /* 0x06 0x1E0 + palette * rows */
    s16 w;          /* 0x08 0x100 */
    u16 h;          /* 0x0A 1, then rows once the fade is built */
    Color3 color; /* 0x0C the colour the rows blend toward */
    u8 pad_0F;
} TixFade;

struct TimPack;

/* The TIX header, copied as bytes (alignment 1) */
typedef struct TixHeaderBytes {
    u8 bytes[0x24];
} TixHeaderBytes;

typedef struct Tix {
    TixVtbl *vtbl;            /* 0x00 to 0x2B: the File header (file_base.h) */
    ListNode *watched;
    ListNode *watchers;
    s32 isOpen;
    union {
        u32 *header;          /* {count, offsets[4], sizes[4]}, 0x24 bytes */
        TixHeaderBytes *copy; /* the same 0x24 bytes, copied whole from the read buffer */
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 0x24 */
    CdlLocDir cdPos;
    u32 cdSize;
    u16 keepData;
    u16 pending;
    u32 flags;                /* 0x24 done requests (File_ServiceQueue): 0x10 open, 0x40 seek, 0x80 read */
    u16 direct;
    u16 state;                /* 0x2A 9 reading the header, 10 reading parts, 0 done */
    u32 partIndex;            /* 0x2C part being read */
    struct TimPack **parts;   /* 0x30 one TimPack per part */
    u8 *buffer;               /* 0x34 read buffer: 0x800 for the header, then the largest part */
    u32 bufferSize;           /* 0x38 */
    s32 loaded;               /* 0x3C 1 once every part is uploaded */
    TixFade fades[4];         /* 0x40 */
    s32 failed;               /* 0x80 an allocation failed: nothing is uploaded */
} Tix;

/* Functions of src/game/tix.c that other files call or reference (docs/naming.md, Prototypes) */
Tix *Tix_Create(char *path);
TixVtbl *Tix_GetVtbl(void);

#endif

#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include "common.h"
#include "game/heap.h"

/*
 * File loaders of src/game/80043008.c. Each class below derives from the file class of
 * src/game/80025F7C.c (base vtable 0x8006D430, returned by Object_GetClassTable; func_80026CAC
 * returns the CD or PC back end, picked by D_8008A84C). At boot func_80026CFC copies the back
 * end's I/O slots (0x40 to 0x58 and 0x68 to 0x74) into the base vtable and into every class
 * vtable listed at 0x8006D4AC, which holds the vtable getters of this unit: in the data those
 * slots are 0.
 *
 * A file object can own its data (slot 0x58 loads the whole file into +0x10, +0x14 = size) or
 * borrow it from a parent file (data set by the creator, size 0: slot 0x5C frees only when the
 * size is not 0). Creators take a FileSource: a parent's data address, or a path to load.
 * Slots are left unprototyped: the code calls some of them with fewer arguments.
 */

/* func_80026CE8(source, data, path, unk_08): data != 0 borrows it, else the path is loaded */
typedef struct FileSource {
    s32 data;   /* address inside a parent file, or 0 */
    s32 path;   /* char *, used when data is 0 */
    s32 unk_08; /* 1 from every creator here and in Sym_LoadModels */
} FileSource;

/* Slots 0x00 to 0x74 of every file class vtable */
typedef struct FileVtbl {
    s32 unk_00;                /* 0x003 in the base, 0xF03 in the TIX class, other values per class */
    void *(*delete_)();        /* 0x04 func_800269F0 */
    s32 (*init)();             /* 0x08 */
    void (*destroy)();         /* 0x0C */
    u8 pad_10[0x3C - 0x10];    /* Object methods, see ObjectVtbl */
    s32 unk_3C;                /* 0 */
    void (*unk_40)();          /* CD: func_800272C8, empty */
    void (*open)();            /* 0x44 (self, path, 1, 0), CD: File_LoadByName (CdSearchFile) */
    void (*close)();           /* 0x48 CD: File_Unload */
    s32 (*seek)();             /* 0x4C (self, offset, whence); whence 2 returns the size (func_80026B08) */
    void (*unk_50)();          /* CD: func_800276C8, empty */
    s32 (*read)();             /* 0x54 (self, buffer, size), CD: File_Read (CdRead) */
    void (*load)();            /* 0x58 (self, path): the whole file into +0x10 (func_80026B08, File_Open) */
    void (*freeData)();        /* 0x5C func_80026C20: frees +0x10 when +0x14 != 0 */
    void (*unk_60)();          /* func_80026C80, empty */
    s32 (*onLoaded)();         /* 0x64 run after each queued request (File_ServiceQueue) and by creators of
                                  borrowed data; classes parse their data here; base func_80026C88: flags |= 1 */
    void (*runQueue)();        /* 0x68 CD: File_ServiceQueue, runs the queued requests */
    void (*loadAsync)();       /* 0x6C (self, path), CD: File_RequestOpen queues slot 0x58 */
    void (*unk_70)();          /* CD: File_Stop */
    void (*cancel)();          /* 0x74 CD: File_CancelRequests, drops the object's queued requests */
} FileVtbl;

/* A colour as three bytes (the GsBG and fade colours; 0x80 is neutral) */
typedef struct ColorRGB {
    u8 r;
    u8 g;
    u8 b;
} ColorRGB;

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
    ColorRGB color; /* 0x0C the colour the rows blend toward */
    u8 pad_0F;
} TixFade;

struct TimPack;

typedef struct Tix {
    TixVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    u32 *header;              /* 0x10 {count, offsets[4], sizes[4]}, 0x24 bytes */
    s32 size;                 /* 0x14 0x24 */
    u8 pad_18[0x24 - 0x18];
    u32 flags;                /* 0x24 done requests (File_ServiceQueue): 0x10 open, 0x40 seek, 0x80 read */
    u8 pad_28[0x2A - 0x28];
    u16 state;                /* 0x2A 9 reading the header, 10 reading parts, 0 done */
    u32 partIndex;            /* 0x2C part being read */
    struct TimPack **parts;   /* 0x30 one TimPack per part */
    s32 buffer;               /* 0x34 read buffer: 0x800 for the header, then the largest part */
    u32 bufferSize;           /* 0x38 */
    s32 loaded;               /* 0x3C 1 once every part is uploaded */
    TixFade fades[4];         /* 0x40 */
    s32 failed;               /* 0x80 an allocation failed: nothing is uploaded */
} Tix;

/*
 * TimPack (vtable g_timPackVtbl, 0x3C bytes, TimPack_Create): one part of a TIX, {count,
 * offsets[count]} then the TIM images. onLoaded makes a TIM object (func_8003B39C) per image,
 * borrowing its data, and points its +0x4C at the fade of its palette row.
 */
typedef struct TimPackVtbl {
    FileVtbl base;
    void (*uploadAll)();      /* 0x78 TimPack_UploadAll: slot 0x78 (upload to VRAM) of every TIM */
} TimPackVtbl;

struct TimObject;

typedef struct TimPack {
    TimPackVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    union {
        s32 addr;
        s32 *words;           /* count, then count offsets from the start */
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x24 - 0x18];
    s32 flags;                /* 0x24 0x200: a load request (slot 0x58) is done (File_ServiceQueue) */
    u8 pad_28[0x2C - 0x28];
    s32 count;                /* 0x2C TIM objects made */
    struct TimObject **tims;  /* 0x30 */
    s32 fades;                /* 0x34 address of the owner's TixFade[4] */
    s32 loaded;               /* 0x38 */
} TimPack;

/*
 * TMD model file (vtable g_tmdVtbl, 0x30 bytes, Tmd_Create): ETC\DREAMER.TMD,
 * ETC\DREAME5.TMD and the TMD inside each MOM. onLoaded maps it with GsMapModelingData and
 * makes one model object (ModelObject_Create) per TMD object.
 */
typedef struct TmdObjectEntry {
    u32 vertices;         /* Sony TMD object table entry, 0x1C bytes */
    u32 vertexCount;
    u32 normals;
    u32 normalCount;
    u32 primitives;
    u32 primitiveCount;
    s32 scale;
} TmdObjectEntry;

typedef struct TmdHeader {
    u32 id;               /* 0x41 */
    u32 flags;            /* GsMapModelingData gets its address */
    u32 objectCount;
    TmdObjectEntry objects[1];
} TmdHeader;

typedef struct TmdVtbl {
    FileVtbl base;
    void (*mapModelingData)(); /* 0x78 Tmd_MapModelingData */
    s32 (*getObject)();        /* 0x7C Tmd_GetObject (self, index): address of TMD object index */
    s32 (*getModel)();         /* 0x80 Tmd_GetModel (self, index) */
    void (*unk_84)();          /* func_80043B70, empty */
} TmdVtbl;

typedef struct Tmd {
    TmdVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    union {
        s32 addr;
        u32 *words;
        TmdHeader *header;
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
    Object **models;          /* 0x2C one model per TMD object, NULL-terminated */
} Tmd;

/*
 * TOD animation file (vtable g_todVtbl, 0x2C bytes, Tod_Create): Sony TOD, an 8-byte file
 * header then frames {u16 size, u16 packetCount, u32 frame} of packets. A packet header word
 * holds the object id (bits 0 to 15), the type (16 to 19), the flag (20 to 23) and the length
 * in words (24 to 31): Tod_ReadPacket splits it. Type 8 flag 0 creates an object, type 2 gives
 * an object its TMD (u16 at +4).
 * TodPack (vtable g_todPackVtbl, 0x2C bytes, TodPack_Create) derives from it: {unk, count,
 * offsets[count]} of TOD files; onLoaded replaces each offset with a Tod object.
 */
typedef struct TodVtbl {
    FileVtbl base;
    u8 (*scanFirstFrame)();   /* 0x78 Tod Tod_ScanFirstFrame, TodPack TodPack_ScanFirstFrame (self, ids, tmdIndex) */
    s32 (*scanFrame)();       /* 0x7C Tod_ScanFrame (self, ids, tmdIndex, frame) */
    void (*readPacket)();     /* 0x80 Tod_ReadPacket (self, packet, &id, &type, &flag, &length) */
} TodVtbl;

typedef struct TodFrame {
    u16 size;
    u16 packetCount;
    u32 frame;
} TodFrame;

typedef struct TodPacket {
    u32 header;
    u16 tmdId;                /* type 2 packets */
} TodPacket;

typedef struct Tod {
    TodVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    s32 data;                 /* 0x10 the TOD file */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
} Tod;

typedef struct TodPackHeader {
    s32 unk_00;
    s32 count;
    s32 offsets[1];           /* from the start; Tod objects once loaded */
} TodPackHeader;

typedef struct TodPack {
    TodVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    union {
        TodPackHeader *header;
        u32 *words;
    } data;                   /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
} TodPack;

/*
 * MOM model (vtable g_momVtbl, 0x38 bytes, Mom_Create): ETC\SYMSPY.MOM and the models of
 * a map square. +0x8 is the offset of its TMD, its TodPack starts at +0xC.
 * MML (vtable g_mmlVtbl, 0x3C bytes, Mml_Create) derives from it: the model list of a map
 * square (LBD +0x10), {unk, count, offsets[count]} of MOM files, each replaced by a Mom object
 * at load; slot 0x88 returns one (Sym_SpawnGroup).
 */
typedef struct MomVtbl {
    FileVtbl base;
    s32 (*loadParts)();       /* 0x78 Mom Mom_LoadParts, Mml Mml_LoadParts */
    void (*freeParts)();      /* 0x7C Mom Mom_FreeParts, Mml Mml_FreeParts */
    s32 (*scanFirstFrame)();  /* 0x80 Mom_ScanFirstFrame: the TodPack's slot 0x78 */
    void (*readPacket)();     /* 0x84 Mom_ReadPacket: the TodPack's slot 0x80 */
    s32 (*getMom)();          /* 0x88 MML only: Mml_GetMom (self, index) */
} MomVtbl;

typedef struct Mom {
    MomVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    u8 *data;                 /* 0x10 */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x2C - 0x18];
    Tmd *tmd;                 /* 0x2C */
    TodPack *motions;         /* 0x30 */
    s32 hasParts;             /* 0x34 1 from Mom_Create, 0 for an MML */
} Mom;

typedef struct Mml {
    MomVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x10 - 0x0C];
    s32 *data;                /* 0x10 {unk, count, offsets[count]}, then Mom objects */
    s32 size;                 /* 0x14 */
    u8 pad_18[0x38 - 0x18];   /* Mom's tmd and motions stay NULL, hasParts 0 */
    s32 momCount;             /* 0x38 Mom objects made */
} Mml;

/*
 * Psy-Q GsBG, GsMAP and GsCELL as the code below fills them: a background sprite made of
 * cells. src/game/8003B854.c builds one full-screen 16-bit Bg: BgCells, a BgMap over them,
 * then a Bg in mode 1 over the map.
 */
typedef struct GsBg {
    u32 attribute;            /* 0x01000000 8-bit or 0x02000000 16-bit colour mode */
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 scrollX;
    s16 scrollY;
    ColorRGB color;
    u8 pad_13;
    void *map;
    s16 mx;                   /* rotation and scale centre, w / 2 and h / 2 */
    s16 my;
    s16 scaleX;               /* 0x1000 = 1 */
    s16 scaleY;
    s32 rotate;
} GsBg;

typedef struct GsCell {
    u8 u;
    u8 v;
    u16 cba;
    u16 flag;
    u16 tpage;
} GsCell;

/* Bg (vtable g_bgVtbl, 0x68 bytes, Bg_Create): derives from the class of func_8001E57C */
typedef struct BgVtbl {
    s32 unk_00;               /* 0x54 */
    void *(*delete_)();       /* 0x04 Object_Delete */
    s32 (*init)();            /* 0x08 Bg_Init (self, map, mode) */
    void (*destroy)();        /* 0x0C func_8001CBA4 */
    u8 pad_10[0x40 - 0x10];
    void (*setMap)();         /* 0x40 Bg_SetMap (self, map, mode) */
    void (*setRotation)();    /* 0x44 Bg_SetRotation (self, set, fraction) */
    void (*setScale)();       /* 0x48 Bg_SetScale (self, set, fractions) */
    u8 pad_4C[0xB8 - 0x4C];
    void (*setColor)();       /* 0xB8 Bg_SetColor (self, set, color) */
    void (*unk_BC)();         /* func_80044674, empty */
} BgVtbl;

typedef struct Bg {
    BgVtbl *vtbl;
    u8 pad_04[0x44 - 0x04];
    GsBg bg;                  /* 0x44 */
} Bg;

/* BgCells (vtable g_bgCellsVtbl, 0x38 bytes, BgCells_Create): 300 cells of 16x16 over VRAM x 640 to 960 */
typedef struct BgCellsVtbl {
    FileVtbl base;
    void (*build)();          /* 0x78 BgCells_Build */
} BgCellsVtbl;

typedef struct BgCells {
    BgCellsVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x2A - 0x0C];
    u16 state;                /* 0x2A */
    GsCell *cells;            /* 0x2C */
    u16 fullScreen;           /* 0x30 set by init when made without a file */
    u16 built;                /* 0x32 */
    s32 unk_34;               /* freed by destroy, never set in this unit */
} BgCells;

/* BgMap (vtable g_bgMapVtbl, 0x44 bytes, BgMap_Create): a GsMAP of 20x15 cells over a BgCells */
typedef struct BgMapVtbl {
    FileVtbl base;
    void (*build)();          /* 0x78 BgMap_Build */
} BgMapVtbl;

typedef struct BgMap {
    BgMapVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    u8 pad_0C[0x2A - 0x0C];
    u16 state;                /* 0x2A */
    u8 cellW;                 /* 0x2C GsMAP from here: cellw, cellh, ncellw, ncellh, base, index */
    u8 cellH;
    u16 cellsX;
    s16 cellsY;
    u8 pad_32[0x34 - 0x32];
    s32 cells;                /* 0x34 the BgCells' GsCell table */
    s16 *index;               /* 0x38 cellsX * cellsY cell numbers, 0 to n - 1 */
    BgCells *cellSource;      /* 0x3C */
    u16 fullScreen;           /* 0x40 */
    u16 built;                /* 0x42 */
} BgMap;

/*
 * Movie (vtable g_movieVtbl, 0x6C bytes, Movie_Create): the MDEC player. A stream object
 * (func_80046F0C) hands it frames; it decodes the VLC data into one of two run-level buffers,
 * sends it through DecDCTin and gets 16-pixel-wide slices back through DecDCTout, each loaded
 * into VRAM by Movie_OnSlice from the MDEC callback. g_activeMovie is the one
 * playing.
 */
typedef struct MovieRect {
    u16 x;                    /* the rect of the GPU object's slot 0x58 (func_8003B4A8 builds the same) */
    u16 y;
    s32 w;
    s32 h;
} MovieRect;

typedef struct MovieVtbl {
    s32 unk_00;               /* 0x70 */
    void *(*delete_)();       /* 0x04 Object_Delete */
    s32 (*init)();            /* 0x08 Movie_Init (self, rect, streamArg, skipAlloc) */
    void (*destroy)();        /* 0x0C Movie_Destroy */
    u8 pad_10[0x40 - 0x10];
    s32 (*open)();            /* 0x40 Movie_Open (self, source, unk_5C, repeat, loops) */
    void (*start)();          /* 0x44 Movie_Start */
    s32 (*update)();          /* 0x48 Movie_Update */
    void (*stop)();           /* 0x4C Movie_Stop */
    void (*unk_50)();         /* func_80045AC8, empty */
    void (*unk_54)();         /* func_80045AD0, empty */
    s32 (*readFrame)();       /* 0x58 Movie_ReadFrame */
    void (*unk_5C)();         /* func_80045BC0, empty */
    void (*onSlice)();        /* 0x60 Movie_OnSlice */
    s32 (*onStopped)();       /* 0x64 Movie_OnStopped */
    s32 (*decodeFrame)();     /* 0x68 Movie_DecodeFrame */
    void (*setUnk68)();       /* 0x6C func_80045E3C */
} MovieVtbl;

struct MovieStream;

typedef struct Movie {
    MovieVtbl *vtbl;
    ListNode *watched;
    ListNode *watchers;
    s32 skipAlloc;            /* 0x0C nonzero: the buffers are neither allocated nor freed */
    s32 streamBuffer;         /* 0x10 0x12000 bytes handed to the stream */
    s32 runLevel[2];          /* 0x14 w * h * 2 + 0x1000 bytes each, used in turn */
    s32 slice;                /* 0x1C one decoded 16-pixel column, h * 32 bytes */
    MovieRect frame;          /* 0x20 where the frame goes in VRAM */
    MovieRect sliceRect;      /* 0x2C the next slice, w = 16 */
    s32 sliceWords;           /* 0x38 DecDCTout size: 16 * h / 2 */
    s32 runLevelIndex;        /* 0x3C */
    s32 frameReady;           /* 0x40 a frame is VLC-decoded and waits for the MDEC */
    s32 stopped;              /* 0x44 */
    s32 streamEnded;          /* 0x48 */
    s32 frameDone;            /* 0x4C every slice of the frame is out */
    s32 unk_50;               /* -1 from the stream callback Movie_OnStreamCallback, 1 from func_800458AC */
    s32 repeat;               /* 0x54 restart when stopped */
    s32 loops;                /* 0x58 0 = no limit */
    s32 unk_5C;               /* passed to the stream's slot 0x50 */
    struct MovieStream *stream; /* 0x60 */
    s32 unk_64;
    s32 unk_68;               /* set by slot 0x6C (1 from init) */
} Movie;

#endif

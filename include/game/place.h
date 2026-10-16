#ifndef GAME_PLACE_H
#define GAME_PLACE_H

#include "common.h"
#include "game/dreamsys.h"

/*
 * Place: the object that runs one stage while the dreamer is in it (the "dream stage class"
 * of docs/discoveries.md, vtable 0x80087034 returned by Place_GetVtbl, 0x88 bytes made by
 * Place_New from the dream runner DreamRunner_CreateStage). Its methods are in src/game/80051F24.c:
 * load (slot 0x4C, music track and texture set), the pad handler (0x58, pause and the hidden
 * exit), the per-tick update (0x5C) and the place's scenery and ambience.
 * The base class is the one Task_GetVtbl returns (src/game/800494B4.c).
 * Slots are left unprototyped: callers pass different argument types.
 */

/*
 * The ambience record a place gets from Scenery_Begin (D_80087424, or a fixed one given to
 * load): Ambience_Fill fills +0xC to +0x1C from a 4-byte family record {unk0, unk1, unk2, unk3}
 * (work/hunt6/C-notes-note.md). +0x0 to +0x8 are static data handed to the map.
 */
/* A 4-byte ambience record: per stage (D_800873EC) or from a family table (D_800873C8, Ambience_PickFamily). */
typedef struct AmbienceRecord {
    s8 mode;      /* 0x0 Ambience.mode */
    s8 depth;     /* 0x1 index of D_8008730C; 4 and up also make the extra object of func_80054660 */
    s8 colorB;    /* 0x2 RGB triple index (0x12 picks the second band palette) */
    s8 colorA;    /* 0x3 RGB triple index */
} AmbienceRecord;

typedef struct Ambience {
    s32 unk0;     /* 0x00 map slot 0xC4, second argument */
    s32 unk4;     /* 0x04 map slot 0xC4, third argument */
    s32 unk8;     /* 0x08 map slot 0xBC */
    u8 *colorA;   /* 0x0C RGB triple of D_800872C4, record byte 3 */
    s32 unk10;
    s32 mode;     /* 0x14 record byte 0; picks colorA or colorB for the view (1 and 2 tested) */
    u8 *colorB;   /* 0x18 RGB triple of D_800872C4, record byte 2 */
    s32 depth;    /* 0x1C D_8008730C[record byte 1]: 0x6800, 0x5000, 0x3800, 0x2000, 0x1000 or 0x800 */
} Ambience;

/* What map slot 0x114 returns for a position (Place_SpawnCell). */
typedef struct MapCellOwnerVtbl {
    u8 pad_00[0x84];
    void (*unk84)();
} MapCellOwnerVtbl;

typedef struct MapCellOwner {
    MapCellOwnerVtbl *vt;
    u8 pad_04[0x34 - 0x04];
    s32 unk34;    /* first argument of Sym_SpawnOrSpy */
} MapCellOwner;

typedef struct MapCell {
    u8 pad_00[0x04];
    MapCellOwner *owner;
    u8 pad_08[0x14 - 0x08];
    s32 spawned;  /* 0x14 Sym_SpawnOrSpy's result */
} MapCell;

/* The object at Place +0x14, also D_8008ABFC (Sym_InitStage) and D_8008AB4C: the map class of
   src/game/800494B4.c (0x1E8 bytes, vtable 0x800866E8, StageMap in the W3 lane's stage.h). */
typedef struct PlaceMapVtbl {
    u8 pad_00[0xBC];
    void (*unkBC)();
    u8 pad_C0[0xC4 - 0xC0];
    void (*unkC4)();
    u8 pad_C8[0xCC - 0xC8];
    void (*unkCC)();
    u8 pad_D0[0xDC - 0xD0];
    void (*unkDC)();
    void (*unkE0)();
    u8 pad_E4[0xE8 - 0xE4];
    void (*unkE8)();                  /* (map, out position, tile record) */
    void (*unkEC)();
    u8 pad_F0[0x10C - 0xF0];
    s32 (*unk10C)();                  /* position handed to the scenery tick */
    u8 pad_110[0x114 - 0x110];
    MapCell *(*cellAt)();             /* 0x114 (map, &chunkKey): the cell, and its key for Sym_SpawnOrSpy */
    u8 pad_118[0x134 - 0x118];
    void (*unk134)();
} PlaceMapVtbl;

typedef struct PlaceMap {
    PlaceMapVtbl *vt;
    u8 pad_04[0x1B4 - 0x04];
    u16 unk1B4;   /* 0x1B4 the place starts once it reads 0 (Place_CheckTextureLoad); pending loads per the W3 lane */
} PlaceMap;

/* What slot 0xAC of the object at Place +0x18 returns: the fade or transition object (Place_StartFade). */
typedef struct PlaceFaderVtbl {
    u8 pad_00[0xD0];
    void (*unkD0)();                  /* duration-like value: 5, 6, 10 or 30 */
    void (*unkD4)();
    void (*unkD8)();
    u8 pad_DC[0xE4 - 0xDC];
    void *(*unkE4)();
    u8 pad_E8[0xF0 - 0xE8];
    s32 (*unkF0)();
} PlaceFaderVtbl;

typedef struct PlaceFader {
    PlaceFaderVtbl *vt;
} PlaceFader;

/* The object at Place +0x18 (and +0x78). */
typedef struct PlaceViewVtbl {
    u8 pad_00[0x54];
    void (*unk54)();
    u8 pad_58[0x60 - 0x58];
    void (*unk60)();
    void (*unk64)();
    void (*unk68)();
    void (*unk6C)();
    void (*unk70)();
    void (*unk74)();
    u8 pad_78[0xAC - 0x78];
    PlaceFader *(*getFader)();        /* 0xAC */
    void (*unkB0)();
    void (*unkB4)();                  /* 0 while the pause window is open, 1 after */
} PlaceViewVtbl;

typedef struct PlaceView {
    PlaceViewVtbl *vt;
    u8 pad_04[0x18 - 0x04];
    s32 unk18;            /* 0x18 the scenery follows its changes (func_80056640) */
    u8 pad_1C[0x24 - 0x1C];
    s32 unk24;            /* 0x24 (unk18 - unk24) / 600 shifts the band colours (func_800549A8) */
} PlaceView;

/* Objects the pause window suspends (slots 0x4C/0x50, 0x88/0x8C) and the "Pause" text. */
typedef struct PlaceObjVtbl {
    u8 pad_00[0x04];
    void (*delete_)();                /* 0x04 Object_Delete */
    u8 pad_08[0x48 - 0x08];
    void (*unk48)();
    void (*unk4C)();
    void (*unk50)();
    u8 pad_54[0x5C - 0x54];
    void (*unk5C)();                  /* music: plays the track Music_PickTrack chose */
    u8 pad_60[0x7C - 0x60];
    s32 *(*unk7C)();                  /* 0x7C first word read by the view setup */
    void *(*unk80)();                 /* 0x80 refs.models: the model of an index */
    u8 pad_84[0x88 - 0x84];
    void (*unk88)();
    void (*unk8C)();
    u8 pad_90[0xB8 - 0x90];
    void (*unkB8)();
} PlaceObjVtbl;

typedef struct PlaceObj {
    PlaceObjVtbl *vt;
} PlaceObj;

/* The class Task_GetVtbl returns, base of Place: the slots Place calls up to. */
typedef struct PlaceBaseVtbl {
    u8 pad_00[0x08];
    void (*construct)();              /* 0x08 */
    void (*destruct)();               /* 0x0C */
    u8 pad_10[0x38 - 0x10];
    void (*onNotify)();               /* 0x38 */
    u8 pad_3C[0x44 - 0x3C];
    void (*attach)();                 /* 0x44 */
    void (*detach)();                 /* 0x48 */
} PlaceBaseVtbl;

/* Vtable 0x80087034. Slot names from the functions stored there (src/game/80051F24.c). */
typedef struct PlaceVtbl {
    s32 unk00;                        /* 0x0002F230 */
    void *(*delete_)();               /* 0x04 Object_Delete */
    void (*construct)();              /* 0x08 Place_Construct */
    void (*destruct)();               /* 0x0C func_80052CD8 */
    void (*watch)();                  /* 0x10 Object_Watch */
    void (*unwatch)();                /* 0x14 Object_Unwatch */
    u8 pad_18[0x30 - 0x18];
    void (*notify)();                 /* 0x30 Object_Notify: 0xC and 0xD reach the dream runner */
    u8 pad_34[0x40 - 0x34];
    void (*unk40)();                  /* 0x40 func_80052DE0, empty */
    void (*attach)();                 /* 0x44 func_80052DE8 */
    void (*detach)();                 /* 0x48 func_80052EBC */
    void (*load)();                   /* 0x4C Place_Load */
    void (*unload)();                 /* 0x50 func_80053134 */
    u8 pad_54[0x74 - 0x54];
    void (*togglePause)();            /* 0x74 Place_TogglePause */
    u8 pad_78[0x80 - 0x78];
    void (*setup)();                  /* 0x80 func_800534C8 */
    void (*teardown)();               /* 0x84 func_800536B0 */
    void (*start)();                  /* 0x88 Place_Start */
    void (*update)();                 /* 0x8C func_8005393C */
    void (*onDreamSysNotify)();       /* 0x90 func_80053984: DreamSys messages */
    void (*onEvent10)();              /* 0x94 func_80053ACC, DreamSys message 10 */
    void (*onEvent12)();              /* 0x98 func_80053BE8 */
    void (*onEvent13)();              /* 0x9C func_80053C94 */
    void (*onEvent14)();              /* 0xA0 func_80053D18 */
    void (*onEvent15)();              /* 0xA4 func_80053D9C */
    void (*onEvent16)();              /* 0xA8 func_80053E00 */
    void (*onEvent17)();              /* 0xAC func_80053E84 */
    void (*onFaderNotify)();          /* 0xB0 func_80053F84 */
    void (*onMapNotify)();            /* 0xB4 func_800540E8: map messages */
    s32 (*spawnCell)();               /* 0xB8 Place_SpawnCell */
    void (*unkBC)();                  /* 0xBC func_800541CC, empty */
    void (*armExit)();                /* 0xC0 Place_ArmExit, SELECT held */
    void (*disarmExit)();             /* 0xC4 Place_DisarmExit, SELECT released */
    void (*confirmExit)();            /* 0xC8 Place_ConfirmExit, TRIANGLE: code 0xD */
    void (*exitNoRecord)();           /* 0xCC Place_ExitNoRecord: code 0xC, never called */
    void (*updatePause)();            /* 0xD0 Place_UpdatePause */
    void (*closePause)();             /* 0xD4 Place_ClosePause */
} PlaceVtbl;

/* Place +0x6C to +0x7C, the four words the scenery code keeps a pointer to (g_placeRefs). */
typedef struct PlaceRefs {
    s32 handlerList;      /* +0x0 list the spot handlers are registered in (func_8002CC34) */
    PlaceObj *models;     /* +0x4 slot 0x80 returns a model by index (func_80056520, func_80056F5C) */
    void *font;           /* +0x8 font of the "Pause" text and of the kind 2 and 3 scenery parts */
    PlaceView *view;      /* +0xC the view again, set by load */
} PlaceRefs;

typedef struct Place {
    PlaceVtbl *vt;
    u8 pad_04[0x0C - 0x04];
    PlaceObj **unkC;      /* 0x0C */
    PlaceObj *unk10;      /* 0x10 suspended by the pause window; passed to Sym_InitStage and the fader */
    PlaceMap *map;        /* 0x14 */
    PlaceView *view;      /* 0x18 */
    s32 ticks;            /* 0x1C counted by the tick while started */
    s32 state;            /* 0x20 0 normal, 5 after load, 4 to 10 while a transition runs */
    u8 pad_24[0x34 - 0x24];
    PlaceObj *unk34;      /* 0x34 suspended by the pause window (slots 0x88/0x8C); Sym_InitStage arg3 */
    s32 stage;            /* 0x38 stage index 0 to 13 */
    DreamSys *dreamSys;   /* 0x3C set by attach, watched */
    s32 unk40;            /* 0x40 0x10 at load, DreamSys slot 0xF8 third argument */
    s32 unk44;            /* 0x44 2 on stage 0, else 3; DreamSys slot 0xF8 second argument */
    s32 unk48;            /* 0x48 load argument, 0xA000 when 0; map slot 0xDC */
    s32 unk4C;            /* 0x4C load argument */
    Ambience *ambience;   /* 0x50 Scenery_Begin's record, or the one given to load */
    PlaceObj *music;      /* 0x54 slot 0x5C plays Music_PickTrack's sequence */
    void *texLoader;      /* 0x58 Tix_Create's texture-set loader (discoveries "texture set") */
    u8 pad_5C[0x60 - 0x5C];
    s32 texLoading;       /* 0x60 set at load, cleared when the loader is done or failed */
    s32 ready;            /* 0x64 set once the map is ready, then slot 0x88 starts the place */
    s32 started;          /* 0x68 set by start; the pad handler and the tick run only then */
    PlaceRefs refs;       /* 0x6C what the scenery code keeps of the place (g_placeRefs) */
    PlaceObj *pauseText;  /* 0x7C "Pause" (D_8008AB44) while the window is open */
    s32 pauseOpen;        /* 0x80 0 closed, else ticks since it opened + 1 */
    s32 exitArmed;        /* 0x84 SELECT held while paused in the normal state */
} Place;

#endif

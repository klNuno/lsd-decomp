#ifndef GAME_PLACE_H
#define GAME_PLACE_H

#include "common.h"
#include "game/view.h"
#include "game/task.h"
#include "game/stage_map.h"
#include "game/scenery.h"
#include "game/dream_sys.h"
#include "game/sound_bank.h"

struct Tix;

/*
 * Place: the object that runs one stage while the dreamer is in it (the "dream stage class"
 * of docs/discoveries.md, vtable 0x80087034 returned by Place_GetVtbl, 0x88 bytes made by
 * Place_New from the dream runner DreamRunner_CreateStage). Its methods are in src/game/place.c:
 * load (slot 0x4C, music track and texture set), the pad handler (0x58, pause and the hidden
 * exit), the per-tick update (0x5C) and the place's scenery and ambience.
 * The base class is the one Task_GetVtbl returns (src/game/task.c).
 * Slots are left unprototyped: callers pass different argument types.
 */

/* Objects the pause window suspends (slots 0x4C/0x50, 0x88/0x8C) and the "Pause" text. */
typedef struct PlaceObjVtbl {
    u8 pad_00[0x04];
    void (*delete_)();                /* 0x04 Object_Delete */
    u8 pad_08[0x48 - 0x08];
    void (*stop)();
    void (*pause)();
    void (*resume)();
    u8 pad_54[0x5C - 0x54];
    void (*setSeq)();                  /* music: plays the track Music_PickTrack chose */
    u8 pad_60[0x7C - 0x60];
    s32 *(*getScreenRect)();                  /* 0x7C first word read by the view setup */
    void *(*getModel)();                 /* 0x80 refs.models: the model of an index */
    u8 pad_84[0x88 - 0x84];
    void (*muteBank)();
    void (*unmuteBank)();
    u8 pad_90[0xB8 - 0x90];
    void (*setColor)();
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

/* Vtable 0x80087034. Slot names from the functions stored there (src/game/place.c). */
typedef struct PlaceVtbl {
    s32 classWord;                    /* 0x0002F230 */
    void *(*delete_)();               /* 0x04 Object_Delete */
    void (*construct)();              /* 0x08 Place_Construct */
    void (*destruct)();               /* 0x0C Place_Destruct */
    void (*watch)();                  /* 0x10 Object_Watch */
    void (*unwatch)();                /* 0x14 Object_Unwatch */
    u8 pad_18[0x30 - 0x18];
    void (*notify)();                 /* 0x30 Object_Notify: 0xC and 0xD reach the dream runner */
    u8 pad_34[0x40 - 0x34];
    void (*reset)();                  /* 0x40 Place_EmptySlot40, empty */
    void (*attach)();                 /* 0x44 Place_Attach */
    void (*detach)();                 /* 0x48 Place_Detach */
    void (*load)();                   /* 0x4C Place_Load */
    void (*unload)();                 /* 0x50 Place_Unload */
    u8 pad_54[0x74 - 0x54];
    void (*togglePause)();            /* 0x74 Place_TogglePause */
    u8 pad_78[0x80 - 0x78];
    void (*setup)();                  /* 0x80 Place_Setup */
    void (*teardown)();               /* 0x84 Place_Teardown */
    void (*start)();                  /* 0x88 Place_Start */
    void (*update)();                 /* 0x8C Place_Update */
    void (*onDreamSysNotify)();       /* 0x90 Place_OnDreamSysNotify: DreamSys messages */
    void (*onEvent10)();              /* 0x94 Place_OnTimeUp, DreamSys message 10 */
    void (*onEvent12)();              /* 0x98 Place_OnLinkDynamic */
    void (*onEvent13)();              /* 0x9C Place_OnLinkStatic */
    void (*onEvent14)();              /* 0xA0 Place_OnNextFlashback */
    void (*onEvent15)();              /* 0xA4 Place_OnLink15 */
    void (*onEvent16)();              /* 0xA8 Place_OnLink16 */
    void (*onEvent17)();              /* 0xAC Place_OnLink17 */
    void (*onFaderNotify)();          /* 0xB0 Place_OnFaderNotify */
    void (*onMapNotify)();            /* 0xB4 Place_OnMapNotify: map messages */
    s32 (*spawnCell)();               /* 0xB8 Place_SpawnCell */
    void (*unkBC)();                  /* 0xBC Place_EmptySlotBC, empty */
    void (*armExit)();                /* 0xC0 Place_ArmExit, SELECT held */
    void (*disarmExit)();             /* 0xC4 Place_DisarmExit, SELECT released */
    void (*confirmExit)();            /* 0xC8 Place_ConfirmExit, TRIANGLE: code 0xD */
    void (*exitNoRecord)();           /* 0xCC Place_ExitNoRecord: code 0xC, never called */
    void (*updatePause)();            /* 0xD0 Place_UpdatePause */
    void (*closePause)();             /* 0xD4 Place_ClosePause */
} PlaceVtbl;

/* Place +0x6C to +0x7C, the four words the scenery code keeps a pointer to (g_placeRefs). */
typedef struct PlaceRefs {
    SoundBank *handlerList; /* +0x0 list the spot handlers are registered in (HandlerNode_Start) */
    PlaceObj *models;     /* +0x4 slot 0x80 returns a model by index (Scenery_Build, Scenery_SetPlaceRefs) */
    void *font;           /* +0x8 font of the "Pause" text and of the kind 2 and 3 scenery parts */
    View *view;           /* +0xC the view again, set by load */
} PlaceRefs;

typedef struct Place {
    PlaceVtbl *vt;
    u8 pad_04[0x0C - 0x04];
    PlaceObj **env;      /* 0x0C */
    PlaceObj *clock;      /* 0x10 suspended by the pause window; passed to Sym_InitStage and the fader */
    StageMap *map;        /* 0x14 the stage map (stage_map.h), also g_symMap (Sym_InitStage) and g_sceneryMap */
    View *view;           /* 0x18 the screen's view (screen.h Screen.view): its overlay is the place fader */
    s32 ticks;            /* 0x1C counted by the tick while started */
    s32 state;            /* 0x20 0 normal, 5 after load, 4 to 10 while a transition runs */
    u8 pad_24[0x34 - 0x24];
    PlaceObj *sound;      /* 0x34 suspended by the pause window (slots 0x88/0x8C); Sym_InitStage arg3 */
    s32 stage;            /* 0x38 stage index 0 to 13 */
    DreamSys *dreamSys;   /* 0x3C set by attach, watched */
    s32 linkPeriod;            /* 0x40 0x10 at load, DreamSys slot 0xF8 third argument */
    s32 moveSpeed;            /* 0x44 2 on stage 0, else 3; DreamSys slot 0xF8 second argument */
    s32 viewDistance;            /* 0x48 load argument, 0xA000 when 0; map slot 0xDC */
    s32 unk4C;            /* 0x4C load argument */
    Ambience *ambience;   /* 0x50 Scenery_Begin's record, or the one given to load */
    PlaceObj *music;      /* 0x54 slot 0x5C plays Music_PickTrack's sequence */
    struct Tix *texLoader; /* 0x58 Tix_Create's texture-set loader (discoveries "texture set") */
    u8 pad_5C[0x60 - 0x5C];
    s32 texLoading;       /* 0x60 set at load, cleared when the loader is done or failed */
    s32 ready;            /* 0x64 set once the map is ready, then slot 0x88 starts the place */
    s32 started;          /* 0x68 set by start; the pad handler and the tick run only then */
    PlaceRefs refs;       /* 0x6C what the scenery code keeps of the place (g_placeRefs) */
    Widget *pauseText;    /* 0x7C the label "Pause" (g_pauseText) while the window is open */
    s32 pauseOpen;        /* 0x80 0 closed, else ticks since it opened + 1 */
    s32 exitArmed;        /* 0x84 SELECT held while paused in the normal state */
} Place;

/* Functions of src/game/place.c that other files call or reference (docs/naming.md, Prototypes) */
void *Place_New(SoundBank *handlerList, void *music, void *font, void *models, s32 stage);

#endif

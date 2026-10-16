#ifndef GAME_DREAM_SYS_H
#define GAME_DREAM_SYS_H

#include "common.h"
#include "game/gs.h"
#include "game/sound_bank.h"
#include "game/stage.h"

/*
 * DreamSys: the game-state object, one instance at 0x80091530, class vtable
 * g_dreamSysVtbl (DreamSysVtbl). DreamSys_New allocates it with 0x928 bytes and
 * calls slot 0x8 (DreamSys_Init). The bytes from +0x178 to +0x878 are the
 * 0x700-byte block the memory card saves (DreamSys_GetSaveBlock).
 * Evidence for each named field: docs/discoveries.md (rows cited below).
 */

struct DreamPlayer;
struct DreamSys;

/* A graph point: two mood axes in -9..9. */
typedef struct MoodPoint {
    s8 x;
    s8 y;
} MoodPoint;

/* One mood accumulator (Mood_Log): last point logged, sums per axis, count. */
typedef struct MoodAccum {
    s16 last; /* the last MoodPoint, both bytes */
    s32 sumX;
    s32 sumY;
    s32 count;
} MoodAccum;

/* The cinematic of the day, as DreamSys_GetCinematic returns it: {category, variant}. */
typedef struct CineRef {
    u8 b0, b1, b2, b3;
} CineRef;

/* The 12 bytes a flashback keeps next to its place (DreamSys_AddFlashback). */
typedef struct DreamRotation {
    u8 unk0[12];
} DreamRotation;

/* One saved flashback, 0x24 bytes, 10 at DreamSys +0x470. */
typedef struct Flashback {
    s32 stage;
    StagePlace place;
    union {
        DreamRotation rot;
        u8 bytes[12];
    } rotation;
    s16 length;      /* 0x10 seconds, playback adds 4 */
    s16 unk1C;
    s32 day;
} Flashback;

/* The camera object at +0x5C: the SHAKE option moves +0x18 and +0x24. */
typedef struct DreamCamera {
    u8 pad_00[0x18];
    u32 viewpointY;
    u8 pad_1C[0x24 - 0x1C];
    u32 refPointY;
} DreamCamera;

/* The object at +0x28: only its u16 at +0x36 is read. */
typedef struct DreamSysObj28 {
    u8 pad_00[0x36];
    u16 flags;
} DreamSysObj28;

/* What player slot 0x11C returns. */
typedef struct DreamPlayerInfoSub {
    u8 pad_00[0x2C];
    s16 loaded;
} DreamPlayerInfoSub;

typedef struct DreamPlayerInfo {
    u8 pad_00[4];
    DreamPlayerInfoSub *chunk;
} DreamPlayerInfo;

/* The player object at +0x4C (discoveries: flashbacks need it): slots used here. */
typedef struct DreamPlayerVtbl {
    u8 pad_00[0xD4];
    StagePlace *(*getTellKey)(struct DreamPlayer *, s32 **);
    u8 pad_D8[0xE8 - 0xD8];
    void (*placeToWorld)(struct DreamPlayer *, void *, void *);
    u8 pad_EC[0xF0 - 0xEC];
    void (*deactivate)(struct DreamPlayer *);
    u8 pad_F4[0x10C - 0xF4];
    s32 (*getLocation)(struct DreamPlayer *, s32, s32); /* the current place, kept by flashbacks */
    u8 pad_110[0x11C - 0x110];
    DreamPlayerInfo *(*slotAt)(struct DreamPlayer *, s32);
} DreamPlayerVtbl;

typedef struct DreamPlayer {
    DreamPlayerVtbl *vt;
} DreamPlayer;

/* The 0x700-byte block the memory card saves and loads: DreamSys +0x178 to +0x878 (DreamSys_GetSaveBlock,
   SaveMenu_Save, menu.h Menu +0xBC). Offsets below are from the block; add 0x178 for DreamSys. */
typedef struct SaveBlock {
    s32 magic;              /* 0x000 "J01" (g_saveMagic) */
    s32 year;               /* 0x004 */
    s32 day;                /* 0x008 0 to 364 */
    s32 unlockScore;        /* 0x00C navScore + instanceScore */
    s32 navScore;           /* 0x010 Nav_CalcScore */
    s32 instanceScore;      /* 0x014 */
    MoodPoint graph[365];   /* 0x018 one point per day */
    u8 pad_2F2[0x2F4 - 0x2F2];
    s32 flashbackCount;     /* 0x2F4 */
    Flashback flashbacks[10]; /* 0x2F8 */
    u8 unk460;              /* 0x460 */
    u8 pad_461[0x467 - 0x461];
    u8 reelSeen;            /* 0x467 the secret video reel was played */
    u8 navFlags[32];        /* 0x468 30 navigation flags (g_navFlags) */
    s32 dynamicLinkCount;   /* 0x488 g_dynamicLinkCount */
    u8 pad_48C[0x500 - 0x48C];
    s32 shake;              /* 0x500 SHAKE option */
    s32 unk504;
    s32 unk508;
    u8 unk50C[500];
} SaveBlock;

/* g_dreamSysVtbl. Slots named after their function; slot 0 holds 0x1F34. */
typedef struct DreamSysVtbl {
    s32 classWord;                                                        /* 0x1F34 */
    void (*delete_)();                                                  /* 0x004 Object_Delete */
    void (*init)(struct DreamSys *, void **, s32, s32);              /* 0x008 DreamSys_Init */
    void (*destroy)();                                                  /* 0x00C SceneNode_Destroy */
    void (*watch)(struct DreamSys *, void *);                        /* 0x010 Actor_Watch: Actor watch, keeps a watched map at +0x4C */
    void (*unwatch)(struct DreamSys *, void *);                      /* 0x014 Actor_Unwatch: Actor unwatch */
    void (*unwatchAll)();                                            /* 0x018 Actor_UnwatchAll: Actor unwatch all */
    void (*nextWatched)();                                                 /* 0x01C Object_NextWatched */
    void (*addWatcher)();                                                 /* 0x020 Object_AddWatcher */
    void (*removeWatcher)();                                                 /* 0x024 Object_RemoveWatcher */
    void (*freeWatchers)();                                                 /* 0x028 Object_FreeWatchers */
    void (*nextWatcher)();                                                 /* 0x02C Object_NextWatcher */
    void (*notify)(struct DreamSys *, s32);                           /* 0x030 Object_Notify */
    void (*unk34)();                                                 /* 0x034 Object_EmptySlot34 */
    void (*onNotify)();                                                 /* 0x038 SceneNode_OnNotify */
    void (*unk3C)();                                                 /* 0x03C 0x00000000 */
    void (*reset)(struct DreamSys *);                                /* 0x040 DreamSys_Reset */
    void (*setRotation)(struct DreamSys *, s32, void *);                   /* 0x044 SceneNode_SetRotation */
    void (*setScale)();                                                 /* 0x048 SceneNode_SetScale */
    void (*enterMap)();                                                 /* 0x04C DreamSys_EnterMap */
    void (*leaveMap)();                                                 /* 0x050 DreamSys_LeaveMap */
    void (*detachChildren)();                                                 /* 0x054 SceneNode_DetachChildren */
    void (*nextChild)();                                                 /* 0x058 SceneNode_NextChild */
    void (*unk5C)();                                                 /* 0x05C SceneNode_EmptySlot5C */
    void (*setVisible)(struct DreamSys *, s32);                           /* 0x060 SceneNode_SetVisible */
    void (*setSemiTrans)();                                                 /* 0x064 SceneNode_SetSemiTrans */
    void (*setBlendRate)();                                                 /* 0x068 SceneNode_SetBlendRate */
    void (*setLit)(struct DreamSys *, s32);                           /* 0x06C SceneNode_SetLit */
    void (*setLightFlags)();                                                 /* 0x070 SceneNode_SetLightFlags */
    void (*setDim)();                                                 /* 0x074 SceneNode_SetDim */
    void (*setZSort)();                                                 /* 0x078 SceneNode_SetZSort */
    void (*setDivision)();                                                 /* 0x07C SceneNode_SetDivision */
    void (*setBackfaceClip)();                                                 /* 0x080 SceneNode_SetBackfaceClip */
    void (*getRotMatrix)();                                                 /* 0x084 SceneNode_GetRotMatrix */
    void (*onGroundProbe)();                                                 /* 0x088 DreamSys_OnGroundProbe */
    void (*getBoxList)();                                                 /* 0x08C SceneNode_GetBoxList */
    void (*sendShape)();                                                 /* 0x090 SceneNode_SendShape */
    void (*onPad)();                                                 /* 0x094 DreamSys_OnPad */
    void (*tickTimer)(struct DreamSys *, s32, s32);                  /* 0x098 DreamSys_TickTimer */
    void (*routeMapMessage)();                                                 /* 0x09C DreamSys_RouteMapMessage */
    void (*checkContact)();                                                 /* 0x0A0 SceneNode_CheckContact */
    void (*worldToLocal)();                                                 /* 0x0A4 SceneNode_WorldToLocal */
    void (*boxesOverlap)();                                                 /* 0x0A8 SceneNode_BoxesOverlap */
    void (*rayTestBoxes)();                                                 /* 0x0AC SceneNode_RayTestBoxes */
    void (*unkB0)();                                                 /* 0x0B0 0x00000000 */
    void (*addActorWatchers)();                                                 /* 0x0B4 SceneNode_AddActorWatchers */
    void (*setPosition)(struct DreamSys *, void *);                  /* 0x0B8 Actor_SetPos */
    void (*move)(struct DreamSys *, s32 *);                          /* 0x0BC Actor_MovePos */
    void (*moveLocal)();                                                 /* 0x0C0 Actor_MoveLocal */
    void (*moveZ)();                                                 /* 0x0C4 Actor_MoveZ */
    void (*moveX)();                                                 /* 0x0C8 Actor_MoveX */
    void (*moveY)();                                                 /* 0x0CC Actor_MoveY */
    void (*moveZOnGround)();                                                 /* 0x0D0 Actor_MoveZOnGround */
    void (*moveXOnGround)(struct DreamSys *, void *, s32);                   /* 0x0D4 Actor_MoveXOnGround */
    void (*unkD8)();                                                 /* 0x0D8 Actor_EmptySlotD8 */
    void (*routeEntityMessage)();                                                 /* 0x0DC DreamSys_RouteEntityMessage */
    void (*onWallTouch)(struct DreamSys *, void *, s32);             /* 0x0E0 DreamSys_OnWallTouch */
    void (*setSpeed)();                                                 /* 0x0E4 Actor_SetSpeed */
    void (*afterWallTouch)(struct DreamSys *);                                /* 0x0E8 DreamSys_EmptySlotE8 */
    void (*setBoxMargin)();                                                 /* 0x0EC Actor_SetBoxMargin */
    s32 (*setFlashbackMode)(struct DreamSys *, s32 *, s32);          /* 0x0F0 DreamSys_SetFlashbackMode */
    void (*setAutoWalk)();                                                 /* 0x0F4 DreamSys_SetAutoWalk */
    void (*startPlace)();                                                 /* 0x0F8 DreamSys_StartPlace */
    void (*lockControls)();                                                 /* 0x0FC DreamSys_LockControls */
    s32 (*wasCirclePressed)();                                                 /* 0x100 DreamSys_WasCirclePressed, returns DreamSys +0x74 */
    s32 (*swapTimeLimit)(struct DreamSys *, s32);                    /* 0x104 DreamSys_SwapTimeLimit */
    s32 (*getElapsedSeconds)(struct DreamSys *);                     /* 0x108 DreamSys_GetElapsedSeconds */
    void (*setSoundBank)();                                                /* 0x10C DreamSys_SetSoundBank */
    void (*setCamera)();                                                /* 0x110 DreamSys_SetCamera */
    void (*setEtcTim)();                                                /* 0x114 DreamSys_SetEtcTim */
    void (*tickBegin)(struct DreamSys *);                               /* 0x118 DreamSys_TickBegin */
    void (*tickHandlers)(struct DreamSys *);                               /* 0x11C DreamSys_TickHandlers */
    void (*testPointAhead)();                                                /* 0x120 DreamSys_TestPointAhead */
    void (*unk124)();                                                /* 0x124 func_80059590 */
    void (*unk128)();                                                /* 0x128 func_80059598 */
    void (*beforeWalk)(struct DreamSys *);                               /* 0x12C DreamSys_EmptySlot12C */
    void (*stopControls)();                                                /* 0x130 DreamSys_StopControls */
    void (*setControls)();                                                /* 0x134 DreamSys_SetControls */
    void (*setLookMode)(struct DreamSys *, s32);                          /* 0x138 DreamSys_SetLookMode */
    void (*setMoveMode)();                                                /* 0x13C DreamSys_SetMoveMode */
    void (*tickLook)(struct DreamSys *);                               /* 0x140 DreamSys_TickLook */
    void (*tickPitch)(struct DreamSys *);                               /* 0x144 DreamSys_TickPitch */
    void (*tickLookBack)(struct DreamSys *);                               /* 0x148 DreamSys_TickLookBack */
    void (*tickLookMode2)(void);                                            /* 0x14C DreamSys_EmptySlot14C */
    void (*tickLookMode3)(void);                                            /* 0x150 DreamSys_EmptySlot150 */
    void (*tickMove)(struct DreamSys *);                               /* 0x154 DreamSys_TickMove */
    void (*tickWalk)(struct DreamSys *);                               /* 0x158 DreamSys_TickWalk */
    void (*tickAutoWalk)(struct DreamSys *);                               /* 0x15C DreamSys_TickAutoWalk */
    void (*setForward)(struct DreamSys *);                               /* 0x160 DreamSys_SetForward */
    s32 (*tickStep)(struct DreamSys *, s32);                           /* 0x164 DreamSys_TickStep */
    void (*playStepSound)(struct DreamSys *);                               /* 0x168 DreamSys_PlayStepSound */
    void (*stopStepSound)(struct DreamSys *, void *);                       /* 0x16C DreamSys_StopStepSound */
    void (*walk)(struct DreamSys *, s32);                          /* 0x170 DreamSys_Walk */
    void (*tickTurn)(struct DreamSys *);                               /* 0x174 DreamSys_TickTurn */
    void (*tickFall)(struct DreamSys *);                               /* 0x178 DreamSys_TickFall */
    void (*endFall)(struct DreamSys *, s32);                          /* 0x17C DreamSys_EndFall */
    void (*swapSpeed)(struct DreamSys *, s32);                          /* 0x180 DreamSys_SwapSpeed */
    void (*pushSpeed)(struct DreamSys *, s32);                          /* 0x184 DreamSys_PushSpeed */
    void (*popSpeed)();                                                /* 0x188 DreamSys_PopSpeed */
    void (*setLinkFlags)(struct DreamSys *, s32, s32, s32, s32);           /* 0x18C DreamSys_SetLinkFlags */
    void (*setLinkPeriod)(struct DreamSys *, s32);                          /* 0x190 DreamSys_SetLinkPeriod */
    void (*fallSoundHandler)(s32, void *);                                     /* 0x194 DreamSys_FallSoundHandler */
    void (*initNewGame)(struct DreamSys *);                          /* 0x198 DreamSys_InitNewGame */
    void (*swapShake)(struct DreamSys *, s32 *);                     /* 0x19C DreamSys_SwapShake */
    s32 (*getDayNumber)(struct DreamSys *, s32 *);                   /* 0x1A0 DreamSys_GetDayNumber */
    s32 (*advanceDay)(struct DreamSys *);                            /* 0x1A4 DreamSys_AdvanceDay */
    void (*clearNeverSaved)(struct DreamSys *);                      /* 0x1A8 DreamSys_ClearNeverSaved */
    s32 (*isNeverSaved)(struct DreamSys *);                          /* 0x1AC DreamSys_IsNeverSaved */
    SaveBlock *(*getSaveBlock)(struct DreamSys *, s32 *);            /* 0x1B0 DreamSys_GetSaveBlock */
    s32 (*startDay)(struct DreamSys *);                              /* 0x1B4 DreamSys_StartDay */
    s32 (*endDay)(struct DreamSys *, s32);                           /* 0x1B8 DreamSys_EndDay */
    CineRef (*getCinematic)(struct DreamSys *);                      /* 0x1BC DreamSys_GetCinematic */
    void (*chooseStart)(struct DreamSys *);                          /* 0x1C0 DreamSys_ChooseStart */
    void (*linkDynamic)(struct DreamSys *);                          /* 0x1C4 DreamSys_LinkDynamic */
    s32 (*linkStatic)(struct DreamSys *, void *);                    /* 0x1C8 DreamSys_LinkStatic */
    s32 (*loadNextFlashback)(struct DreamSys *, s32);                /* 0x1CC DreamSys_LoadNextFlashback */
    s32 (*linkFacing)(struct DreamSys *, s32);                           /* 0x1D0 DreamSys_LinkFacing */
    s32 (*linkFall)(struct DreamSys *, s32);                           /* 0x1D4 DreamSys_LinkFall */
    s32 (*linkExtra)(struct DreamSys *, s32);                           /* 0x1D8 DreamSys_LinkExtra */
    s32 (*startLinkStep)(struct DreamSys *, s32);                           /* 0x1DC DreamSys_StartLinkStep */
    s32 (*getStage)(struct DreamSys *);                              /* 0x1E0 DreamSys_GetStage */
    void (*onMapMessage)(struct DreamSys *, s32 **, s32);                  /* 0x1E4 DreamSys_OnMapMessage */
    void (*onEntityEvent)(struct DreamSys *, s32 **, s32);           /* 0x1E8 DreamSys_OnEntityEvent */
    void (*getPreviousPoint)(struct DreamSys *, void *, s32);        /* 0x1EC DreamSys_GetPreviousPoint */
    void (*resetMoodAccumulators)(struct DreamSys *, s32);           /* 0x1F0 DreamSys_ResetMoodAccumulators */
    void (*logChunkMood)(struct DreamSys *, s8 *);                   /* 0x1F4 DreamSys_LogChunkMood */
    void (*logEntityMood)(struct DreamSys *, s32);                   /* 0x1F8 DreamSys_LogEntityMood */
    void (*computeDayPoint)(struct DreamSys *, struct MoodPoint *);  /* 0x1FC DreamSys_ComputeDayPoint */
    s32 (*getDreamColor)(struct DreamSys *);                         /* 0x200 DreamSys_GetDreamColor: colour index 0 to 7 */
    void (*moodReset)(struct DreamSys *, struct MoodAccum *);        /* 0x204 Mood_Reset */
    void (*moodLog)(struct DreamSys *, struct MoodAccum *, struct MoodPoint *); /* 0x208 Mood_Log */
    void (*moodResolve)(struct DreamSys *, struct MoodAccum *, struct MoodPoint *); /* 0x20C Mood_Resolve */
    void (*calcUnlockScore)(struct DreamSys *);                      /* 0x210 DreamSys_CalcUnlockScore */
    void (*addFlashback)(struct DreamSys *, s32, void *, void *, s32, s32, s32); /* 0x214 DreamSys_AddFlashback */
    void (*maybeSaveFlashback)(struct DreamSys *, s32, s32);         /* 0x218 DreamSys_MaybeSaveFlashback */
    void (*clearFlashbacks)(struct DreamSys *);                      /* 0x21C DreamSys_ClearFlashbacks */
    void (*savePosition)(struct DreamSys *);                               /* 0x220 DreamSys_SavePosition */
    void (*restorePosition)(struct DreamSys *);                               /* 0x224 DreamSys_RestorePosition */
    void (*unk228)();                                                /* 0x228 func_8005BA20 */
} DreamSysVtbl;

typedef struct DreamSys {
    DreamSysVtbl *vtbl;
    u8 pad_04[0x0C - 0x04];
    s32 parent;
    u8 pad_10[0x14 - 0x10];
    union {
        Coord2 *coord;
        u8 *bytes;
    } pos;                  /* 0x14 its GsCOORDINATE2 (gs.h), as for entities */
    u8 pad_18[0x24 - 0x18];
    u32 timer;              /* ticks of the dream, 15 per second (DreamSys_TickTimer) */
    DreamSysObj28 *contact;
    u8 pad_2C[0x44 - 0x2C];
    s32 transition;         /* link or event code while one runs, 0 when idle */
    u8 pad_48[0x4C - 0x48];
    DreamPlayer *map;
    u8 pad_50[0x58 - 0x50];
    SoundBank *soundBank;      /* 0x58 the model's sound bank (sound_bank.h, Model +0x58), DreamSys_New's second argument */
    union {
        DreamCamera *obj;
        u8 *bytes;
    } camera;
    void **tmd;
    s32 etcTim;
    s32 flashbackMode;      /* DreamSys_SetFlashbackMode */
    s32 autoWalk;
    s32 controlsLocked;
    s32 circlePressed;
    s32 unk78;
    s32 unk7C;
    void (*lookHandler)(void);    /* one of slots 0x140, 0x14C, 0x150, picked by unk84 */
    s32 lookMode;
    s32 pitchInput;
    s32 pitch;
    s32 lookBackInput;
    s32 lookBackYaw;
    void (*moveHandler)(struct DreamSys *); /* slot 0x154 or 0x178, picked by unk9C */
    s32 moveMode;
    s32 walkDirection;
    s32 turnInput;
    s32 walkingForward;
    s32 speed;
    s32 savedSpeed;
    s32 stepTick;
    s32 stepSound;
    s32 stepVoice;
    u8 pad_C0[0xC4 - 0xC0];
    s32 falling;
    s32 fallSoundOn;
    union {
        s32 word;
        u8 bytes[4];
    } fallSound;
    u8 pad_D0[0x120 - 0xD0];
    u32 linkPeriod;
    s32 dynamicLinkOn;      /* links dynamically only when set (DreamSys_OnWallTouch) */
    s32 unk128;
    s32 unk12C;
    s32 unk130;
    s32 timeLimit;          /* seconds x 15 (DreamSys_SwapTimeLimit) */
    u8 pad_138[0x144 - 0x138];
    MoodAccum chunkMood;    /* chunks walked through (DreamSys_LogChunkMood) */
    MoodAccum entityMood;   /* entities touched (DreamSys_OnEntityEvent, message 9) */
    s32 stage;              /* current stage, 0 to 13 */
    union {
        u8 bytes[4];
        CineRef ref;        /* returned whole by DreamSys_GetCinematic */
        struct {
            s16 category;   /* -1: an entity's video */
            s16 variant;
        } id;
    } cinematic;
    StagePlace place;       /* where the player stands or arrives */
    u8 pad_176[0x178 - 0x176];
    SaveBlock save;         /* 0x178 the 0x700 bytes the memory card saves (DreamSys_GetSaveBlock) */
    s32 neverSaved;         /* set by a new game, cleared by a save or a load */
    s32 nextFlashback;      /* playback index into flashbacks */
    s32 *fallTurn;
    u8 *linkHeading;
    u8 *arrivalHeading;
    s32 savedDay;           /* day at the start of the dream (DreamSys_StartDay) */
    Coord2 coordCopy;       /* DreamSys_SavePosition saves pos and its param, DreamSys_RestorePosition restores them */
    Coord2Param paramCopy;
    s32 ignorePad;
    s32 skipMoveBoxes;
    s32 (*linkStep)(struct DreamSys *); /* one of g_linkSteps, run until it returns 1 */
    s32 linkStepTick;
    StagePlace linkTarget;
    u8 pad_922[0x924 - 0x922];
    s32 unk924;
} DreamSys;

/* Functions of src/game/dream_sys.c that other files call or reference (docs/naming.md, Prototypes) */
void *DreamSys_New(s32 tmd, s32 soundBank, s32 camera);

#endif

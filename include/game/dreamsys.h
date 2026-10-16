#ifndef GAME_DREAMSYS_H
#define GAME_DREAMSYS_H

#include "common.h"

/*
 * DreamSys: the game-state object, one instance at 0x80091530, class vtable
 * g_dreamSysVtbl (DreamSysVtbl). DreamSys_New allocates it with 0x928 bytes and
 * calls slot 0x8 (DreamSys_Init). The bytes from +0x178 to +0x878 are the
 * 0x700-byte block the memory card saves (DreamSys_GetSaveBlock).
 * Evidence for each named field: docs/discoveries.md (rows cited below).
 */

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

/* A place in a stage, copied whole: +0x16C, flashback entries, link target. */
typedef struct DreamPlace {
    u8 unk0[4];
    s16 vec[3]; /* subtracted from fixed s16[3] points by func_8005AF64 */
} DreamPlace;

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
    DreamPlace place;
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
    u32 unk18;
    u8 pad_1C[0x24 - 0x1C];
    u32 unk24;
} DreamCamera;

/* The 0x28-byte block +0x14 points to at +0x44, saved at +0x8E0. */
typedef struct DreamBodyExtra {
    s32 unk[10];
} DreamBodyExtra;

/* The 0x50-byte block at +0x14, saved at +0x890 by func_8005B904. */
typedef struct DreamBody {
    s32 unk0;
    u8 pad_04[0x18 - 0x04];
    s32 unk18;
    s32 unk1C;
    u8 pad_20[0x44 - 0x20];
    DreamBodyExtra *unk44;
    u8 pad_48[0x50 - 0x48];
} DreamBody;

/* The object at +0x28: only its u16 at +0x36 is read. */
typedef struct DreamSysObj28 {
    u8 pad_00[0x36];
    u16 unk36;
} DreamSysObj28;

/* The object at +0x58 (sprite or sound player, unknown): slots used here. */
typedef struct DreamSysObj58Vtbl {
    u8 pad_00[0x80];
    s32 (*unk80)(struct DreamSysObj58 *, s32, s32, s32);
    void (*unk84)(struct DreamSysObj58 *, s32);
    u8 pad_88[0x9C - 0x88];
    void (*unk9C)(struct DreamSysObj58 *, s32);
} DreamSysObj58Vtbl;

typedef struct DreamSysObj58 {
    DreamSysObj58Vtbl *vt;
} DreamSysObj58;

/* What player slot 0x11C returns. */
typedef struct DreamPlayerInfoSub {
    u8 pad_00[0x2C];
    s16 unk2C;
} DreamPlayerInfoSub;

typedef struct DreamPlayerInfo {
    u8 pad_00[4];
    DreamPlayerInfoSub *unk4;
} DreamPlayerInfo;

/* The player object at +0x4C (discoveries: flashbacks need it): slots used here. */
typedef struct DreamPlayerVtbl {
    u8 pad_00[0xD4];
    DreamPlace *(*unkD4)(struct DreamPlayer *, s32 **);
    u8 pad_D8[0xE8 - 0xD8];
    void (*unkE8)(struct DreamPlayer *, void *, void *);
    u8 pad_EC[0xF0 - 0xEC];
    void (*unkF0)(struct DreamPlayer *);
    u8 pad_F4[0x10C - 0xF4];
    s32 (*unk10C)(struct DreamPlayer *, s32, s32); /* the current place, kept by flashbacks */
    u8 pad_110[0x11C - 0x110];
    DreamPlayerInfo *(*unk11C)(struct DreamPlayer *, s32);
} DreamPlayerVtbl;

typedef struct DreamPlayer {
    DreamPlayerVtbl *vt;
} DreamPlayer;

/* g_dreamSysVtbl. Slots named after their function; slot 0 holds 0x1F34. */
typedef struct DreamSysVtbl {
    s32 unk0;                                                        /* 0x1F34 */
    void (*unk4)();                                                  /* 0x004 Object_Delete */
    void (*init)(struct DreamSys *, void **, s32, s32);              /* 0x008 DreamSys_Init */
    void (*unkC)();                                                  /* 0x00C func_8001CBA4 */
    void (*unk10)(struct DreamSys *, void *);                        /* 0x010 func_800570B4 */
    void (*unk14)(struct DreamSys *, void *);                        /* 0x014 func_80057130 */
    void (*unk18)();                                                 /* 0x018 func_800571A8 */
    void (*unk1C)();                                                 /* 0x01C Object_NextWatched */
    void (*unk20)();                                                 /* 0x020 Object_AddWatcher */
    void (*unk24)();                                                 /* 0x024 Object_RemoveWatcher */
    void (*unk28)();                                                 /* 0x028 Object_FreeWatchers */
    void (*unk2C)();                                                 /* 0x02C Object_NextWatcher */
    void (*unk30)(struct DreamSys *, s32);                           /* 0x030 Object_Notify */
    void (*unk34)();                                                 /* 0x034 func_80018350 */
    void (*unk38)();                                                 /* 0x038 func_8001CD60 */
    void (*unk3C)();                                                 /* 0x03C 0x00000000 */
    void (*unk40)(struct DreamSys *);                                /* 0x040 func_800588EC */
    void (*unk44)(struct DreamSys *, s32, void *);                   /* 0x044 func_8001CEB4 */
    void (*unk48)();                                                 /* 0x048 func_8001D008 */
    void (*unk4C)();                                                 /* 0x04C func_80058968 */
    void (*unk50)();                                                 /* 0x050 func_80058A94 */
    void (*unk54)();                                                 /* 0x054 func_8001D204 */
    void (*unk58)();                                                 /* 0x058 func_8001D280 */
    void (*unk5C)();                                                 /* 0x05C func_8001D33C */
    void (*unk60)(struct DreamSys *, s32);                           /* 0x060 func_8001D344 */
    void (*unk64)();                                                 /* 0x064 func_8001D374 */
    void (*unk68)();                                                 /* 0x068 func_8001D3A0 */
    void (*unk6C)(struct DreamSys *, s32);                           /* 0x06C func_8001D3CC */
    void (*unk70)();                                                 /* 0x070 func_8001D3F8 */
    void (*unk74)();                                                 /* 0x074 func_8001D424 */
    void (*unk78)();                                                 /* 0x078 func_8001D450 */
    void (*unk7C)();                                                 /* 0x07C func_8001D480 */
    void (*unk80)();                                                 /* 0x080 func_8001D4AC */
    void (*unk84)();                                                 /* 0x084 func_8001D4DC */
    void (*unk88)();                                                 /* 0x088 func_80058B08 */
    void (*unk8C)();                                                 /* 0x08C func_8001D600 */
    void (*unk90)();                                                 /* 0x090 func_8001D624 */
    void (*unk94)();                                                 /* 0x094 func_80058C58 */
    void (*tickTimer)(struct DreamSys *, s32, s32);                  /* 0x098 DreamSys_TickTimer */
    void (*unk9C)();                                                 /* 0x09C func_80058E8C */
    void (*unkA0)();                                                 /* 0x0A0 func_8001D714 */
    void (*unkA4)();                                                 /* 0x0A4 func_8001D950 */
    void (*unkA8)();                                                 /* 0x0A8 func_8001DA28 */
    void (*unkAC)();                                                 /* 0x0AC func_8001DDF4 */
    void (*unkB0)();                                                 /* 0x0B0 0x00000000 */
    void (*unkB4)();                                                 /* 0x0B4 func_8001E4A4 */
    void (*unkB8)(struct DreamSys *, void *);                        /* 0x0B8 func_80057384 */
    void (*unkBC)(struct DreamSys *, s32 *);                         /* 0x0BC func_800573A8 */
    void (*unkC0)();                                                 /* 0x0C0 func_80057444 */
    void (*unkC4)();                                                 /* 0x0C4 func_8005748C */
    void (*unkC8)();                                                 /* 0x0C8 func_800574C4 */
    void (*unkCC)();                                                 /* 0x0CC func_800574FC */
    void (*unkD0)();                                                 /* 0x0D0 func_800575B0 */
    void (*unkD4)(struct DreamSys *, void *, s32);                   /* 0x0D4 func_800575E0 */
    void (*unkD8)();                                                 /* 0x0D8 func_80057610 */
    void (*unkDC)();                                                 /* 0x0DC func_80058F18 */
    void (*onWallTouch)(struct DreamSys *, void *, s32);             /* 0x0E0 DreamSys_OnWallTouch */
    void (*unkE4)();                                                 /* 0x0E4 func_80057C6C */
    void (*unkE8)(struct DreamSys *);                                /* 0x0E8 func_800590E0 */
    void (*unkEC)();                                                 /* 0x0EC func_80057C7C */
    s32 (*setFlashbackMode)(struct DreamSys *, s32 *, s32);          /* 0x0F0 DreamSys_SetFlashbackMode */
    void (*unkF4)();                                                 /* 0x0F4 func_80059148 */
    void (*unkF8)();                                                 /* 0x0F8 func_800591B4 */
    void (*unkFC)();                                                 /* 0x0FC func_80059310 */
    void (*unk100)();                                                /* 0x100 func_8005931C */
    s32 (*swapTimeLimit)(struct DreamSys *, s32);                    /* 0x104 DreamSys_SwapTimeLimit */
    s32 (*getElapsedSeconds)(struct DreamSys *);                     /* 0x108 DreamSys_GetElapsedSeconds */
    void (*unk10C)();                                                /* 0x10C func_8005937C */
    void (*unk110)();                                                /* 0x110 func_80059384 */
    void (*unk114)();                                                /* 0x114 func_8005938C */
    void (*unk118)(struct DreamSys *);                               /* 0x118 func_80059394 */
    void (*unk11C)(struct DreamSys *);                               /* 0x11C func_800593D8 */
    void (*unk120)();                                                /* 0x120 func_8005942C */
    void (*unk124)();                                                /* 0x124 func_80059590 */
    void (*unk128)();                                                /* 0x128 func_80059598 */
    void (*unk12C)(struct DreamSys *);                               /* 0x12C func_800595A0 */
    void (*unk130)();                                                /* 0x130 func_800595A8 */
    void (*unk134)();                                                /* 0x134 func_80059610 */
    void (*unk138)(struct DreamSys *, s32);                          /* 0x138 func_8005966C */
    void (*unk13C)();                                                /* 0x13C func_800596E8 */
    void (*unk140)(struct DreamSys *);                               /* 0x140 func_800597C0 */
    void (*unk144)(struct DreamSys *);                               /* 0x144 func_80059814 */
    void (*unk148)(struct DreamSys *);                               /* 0x148 func_800598E8 */
    void (*unk14C)(void);                                            /* 0x14C func_80059A48 */
    void (*unk150)(void);                                            /* 0x150 func_80059A50 */
    void (*unk154)(struct DreamSys *);                               /* 0x154 func_80059A58 */
    void (*unk158)(struct DreamSys *);                               /* 0x158 func_80059AEC */
    void (*unk15C)(struct DreamSys *);                               /* 0x15C func_80059B50 */
    void (*unk160)(struct DreamSys *);                               /* 0x160 func_80059BD4 */
    s32 (*unk164)(struct DreamSys *, s32);                           /* 0x164 func_80059BE0 */
    void (*unk168)(struct DreamSys *);                               /* 0x168 func_80059D1C */
    void (*unk16C)(struct DreamSys *, void *);                       /* 0x16C func_80059E3C */
    void (*unk170)(struct DreamSys *, s32);                          /* 0x170 func_80059E98 */
    void (*unk174)(struct DreamSys *);                               /* 0x174 func_8005A050 */
    void (*unk178)(struct DreamSys *);                               /* 0x178 func_8005A0B0 */
    void (*unk17C)(struct DreamSys *, s32);                          /* 0x17C func_8005A134 */
    void (*unk180)(struct DreamSys *, s32);                          /* 0x180 func_8005A168 */
    void (*unk184)(struct DreamSys *, s32);                          /* 0x184 func_8005A184 */
    void (*unk188)();                                                /* 0x188 func_8005A1A4 */
    void (*unk18C)(struct DreamSys *, s32, s32, s32, s32);           /* 0x18C func_8005A1B0 */
    void (*unk190)(struct DreamSys *, s32);                          /* 0x190 func_8005A1EC */
    void (*unk194)(s32, void *);                                     /* 0x194 func_8005A1F4 */
    void (*initNewGame)(struct DreamSys *);                          /* 0x198 DreamSys_InitNewGame */
    void (*swapShake)(struct DreamSys *, s32 *);                     /* 0x19C DreamSys_SwapShake */
    s32 (*getDayNumber)(struct DreamSys *, s32 *);                   /* 0x1A0 DreamSys_GetDayNumber */
    s32 (*advanceDay)(struct DreamSys *);                            /* 0x1A4 DreamSys_AdvanceDay */
    void (*clearNeverSaved)(struct DreamSys *);                      /* 0x1A8 DreamSys_ClearNeverSaved */
    s32 (*isNeverSaved)(struct DreamSys *);                          /* 0x1AC DreamSys_IsNeverSaved */
    void *(*getSaveBlock)(struct DreamSys *, s32 *);                 /* 0x1B0 DreamSys_GetSaveBlock */
    s32 (*startDay)(struct DreamSys *);                              /* 0x1B4 DreamSys_StartDay */
    s32 (*endDay)(struct DreamSys *, s32);                           /* 0x1B8 DreamSys_EndDay */
    CineRef (*getCinematic)(struct DreamSys *);                      /* 0x1BC DreamSys_GetCinematic */
    void (*chooseStart)(struct DreamSys *);                          /* 0x1C0 DreamSys_ChooseStart */
    void (*linkDynamic)(struct DreamSys *);                          /* 0x1C4 DreamSys_LinkDynamic */
    s32 (*linkStatic)(struct DreamSys *, void *);                    /* 0x1C8 DreamSys_LinkStatic */
    s32 (*loadNextFlashback)(struct DreamSys *, s32);                /* 0x1CC DreamSys_LoadNextFlashback */
    s32 (*unk1D0)(struct DreamSys *, s32);                           /* 0x1D0 func_8005A700 */
    s32 (*unk1D4)(struct DreamSys *, s32);                           /* 0x1D4 func_8005A7A0 */
    s32 (*unk1D8)(struct DreamSys *, s32);                           /* 0x1D8 func_8005A82C */
    s32 (*unk1DC)(struct DreamSys *, s32);                           /* 0x1DC func_8005A9CC */
    s32 (*getStage)(struct DreamSys *);                              /* 0x1E0 DreamSys_GetStage */
    void (*unk1E4)(struct DreamSys *, s32 **, s32);                  /* 0x1E4 func_8005AFDC */
    void (*onEntityEvent)(struct DreamSys *, s32 **, s32);           /* 0x1E8 DreamSys_OnEntityEvent */
    void (*getPreviousPoint)(struct DreamSys *, void *, s32);        /* 0x1EC DreamSys_GetPreviousPoint */
    void (*resetMoodAccumulators)(struct DreamSys *, s32);           /* 0x1F0 DreamSys_ResetMoodAccumulators */
    void (*logChunkMood)(struct DreamSys *, s8 *);                   /* 0x1F4 DreamSys_LogChunkMood */
    void (*logEntityMood)(struct DreamSys *, s32);                   /* 0x1F8 DreamSys_LogEntityMood */
    void (*computeDayPoint)(struct DreamSys *, struct MoodPoint *);  /* 0x1FC DreamSys_ComputeDayPoint */
    void (*getDreamColor)(struct DreamSys *);                        /* 0x200 DreamSys_GetDreamColor */
    void (*moodReset)(struct DreamSys *, struct MoodAccum *);        /* 0x204 Mood_Reset */
    void (*moodLog)(struct DreamSys *, struct MoodAccum *, struct MoodPoint *); /* 0x208 Mood_Log */
    void (*moodResolve)(struct DreamSys *, struct MoodAccum *, struct MoodPoint *); /* 0x20C Mood_Resolve */
    void (*calcUnlockScore)(struct DreamSys *);                      /* 0x210 DreamSys_CalcUnlockScore */
    void (*addFlashback)(struct DreamSys *, s32, void *, void *, s32, s32, s32); /* 0x214 DreamSys_AddFlashback */
    void (*maybeSaveFlashback)(struct DreamSys *, s32, s32);         /* 0x218 DreamSys_MaybeSaveFlashback */
    void (*clearFlashbacks)(struct DreamSys *);                      /* 0x21C DreamSys_ClearFlashbacks */
    void (*unk220)(struct DreamSys *);                               /* 0x220 func_8005B904 */
    void (*unk224)(struct DreamSys *);                               /* 0x224 func_8005B990 */
    void (*unk228)();                                                /* 0x228 func_8005BA20 */
} DreamSysVtbl;

typedef struct DreamSys {
    DreamSysVtbl *vtbl;
    u8 pad_04[0x0C - 0x04];
    s32 unkC;
    u8 pad_10[0x14 - 0x10];
    union {
        DreamBody *body;
        u8 *bytes;
    } unk14;
    u8 pad_18[0x24 - 0x18];
    u32 timer;              /* ticks of the dream, 15 per second (DreamSys_TickTimer) */
    DreamSysObj28 *unk28;
    u8 pad_2C[0x44 - 0x2C];
    s32 transition;         /* link or event code while one runs, 0 when idle */
    u8 pad_48[0x4C - 0x48];
    DreamPlayer *player;
    u8 pad_50[0x58 - 0x50];
    DreamSysObj58 *unk58;
    union {
        DreamCamera *obj;
        u8 *bytes;
    } camera;
    void **unk60;
    s32 unk64;
    s32 flashbackMode;      /* DreamSys_SetFlashbackMode */
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    void (*unk80)(void);    /* one of slots 0x140, 0x14C, 0x150, picked by unk84 */
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
    void (*unk98)(struct DreamSys *); /* slot 0x154 or 0x178, picked by unk9C */
    s32 unk9C;
    s32 unkA0;
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    s32 unkBC;
    u8 pad_C0[0xC4 - 0xC0];
    s32 unkC4;
    s32 unkC8;
    union {
        s32 word;
        u8 bytes[4];
    } unkCC;
    u8 pad_D0[0x120 - 0xD0];
    u32 unk120;
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
    DreamPlace place;       /* where the player stands or arrives */
    u8 pad_176[0x178 - 0x176];
    /* The 0x700-byte save block starts here. */
    s32 magic;              /* "J01" (g_saveMagic) */
    s32 year;
    s32 day;                /* 0 to 364 */
    s32 unlockScore;        /* navScore + instanceScore */
    s32 navScore;           /* Nav_CalcScore */
    s32 instanceScore;
    MoodPoint graph[365];   /* one point per day */
    u8 pad_46A[0x46C - 0x46A];
    s32 flashbackCount;
    Flashback flashbacks[10];
    u8 unk5D8;
    u8 pad_5D9[0x5DF - 0x5D9];
    u8 reelSeen;            /* the secret video reel was played */
    u8 navFlags[32];        /* 30 navigation flags (g_navFlags) */
    s32 dynamicLinkCount;   /* g_dynamicLinkCount */
    u8 pad_604[0x678 - 0x604];
    s32 shake;              /* SHAKE option */
    s32 unk67C;
    s32 unk680;
    u8 unk684[500];
    /* End of the save block. */
    s32 neverSaved;         /* set by a new game, cleared by a save or a load */
    s32 nextFlashback;      /* playback index into flashbacks */
    s32 *unk880;
    u8 *unk884;
    u8 *unk888;
    s32 savedDay;           /* day at the start of the dream (DreamSys_StartDay) */
    DreamBody bodyCopy;     /* func_8005B904 */
    DreamBodyExtra bodyExtraCopy;
    s32 unk908;
    s32 unk90C;
    s32 (*linkStep)(struct DreamSys *); /* one of g_linkSteps, run until it returns 1 */
    s32 linkStepTick;
    DreamPlace linkTarget;
    u8 pad_922[0x924 - 0x922];
    s32 unk924;
} DreamSys;

#endif

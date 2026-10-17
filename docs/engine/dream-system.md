# The dream system

DreamSys is the dreamer and the game state in one object. It walks through the dream, counts the dream timer, logs the moods of what the player walks through and touches, and turns them into the day's point on the graph. It also decides where each dream starts, starts every link, keeps the flashback memories and ends the day. Its state outlives every dream: the bytes the memory card saves are a block inside it.

Code: [`src/game/dream_sys.c`](../../src/game/dream_sys.c), types in [`include/game/dream_sys.h`](../../include/game/dream_sys.h). The link and spawn pickers it calls are in [`src/game/dream_link.c`](../../src/game/dream_link.c) ([links](links.md)). The objects around it: DreamRunner ([`src/game/dream_runner.c`](../../src/game/dream_runner.c)) and Place ([`src/game/place.c`](../../src/game/place.c)), described in [stages and places](stages-and-places.md).

## The object

| Item | Value |
| --- | --- |
| Constructor | `DreamSys_New(tmd, soundBank, camera)`, 0x928 bytes, then slot 0x08 `DreamSys_Init` |
| Vtable | `g_dreamSysVtbl` (0x80087BDC), class word 0x1F34, returned by `DreamSys_GetVtable` |
| Base class | Actor ([`src/game/actor.c`](../../src/game/actor.c)): `DreamSys_Init` first runs `Actor_GetVtbl()->init` |
| Instance | one, made by `Scene_Init` ([`src/game/scene.c`](../../src/game/scene.c)) with the model `ETC\DREAME5.TMD`, kept until power-off |

Because DreamSys is an Actor, it has a position (`pos`, a GsCOORDINATE2), it moves with the Actor slots (`move`, `moveZOnGround`) and it sends its box list after each move like any character ([characters](characters.md)). `DreamSys_Init` sets the time limit to "none" (-1), locks the controls, marks the game as never saved and runs `DreamSys_InitNewGame` and `DreamSys_Reset`.

The fields that matter:

| Offset | Field | Meaning |
| --- | --- | --- |
| 0x24 | `timer` | ticks of the current dream |
| 0x44 | `transition` | code of the link or event running, 0 when idle (table below) |
| 0x4C | `map` | the StageMap the dreamer walks on |
| 0x5C | `camera` | the DreamView, set by the runner |
| 0x68 | `flashbackMode` | 1 while the menu's FLASHBACK replay runs |
| 0x124 | `dynamicLinkOn` | random links allowed this tick |
| 0x134 | `timeLimit` | seconds x 15 |
| 0x144, 0x154 | `chunkMood`, `entityMood` | the two mood accumulators |
| 0x164 | `stage` | current stage, 0 to 13 |
| 0x168 | `cinematic` | {category, variant} of the video or picture due at the end |
| 0x16C | `place` | a StagePlace: where the dreamer stands or arrives |
| 0x178 | `save` | the 0x700-byte SaveBlock |
| 0x88C | `savedDay` | the day when the dream started |

The SaveBlock (`DreamSys_GetSaveBlock` returns DreamSys + 0x178 and the size 0x700) holds the magic `g_saveMagic`, year, day (0 to 364), the three scores, 365 graph points, the flashback count and 10 flashbacks, the reel flag, the 30 navigation flags, the dynamic link count and the SHAKE option. How the card writes it: [menus and save](menus-and-save.md). Player view: [everything the game remembers fits in one block](../discoveries.md#-everything-the-game-remembers-fits-in-one-block).

## How messages reach it

DreamSys never polls. It watches objects and reacts to their notifications. `SceneNode_OnNotify` ([`src/game/scene_node.c`](../../src/game/scene_node.c)) dispatches on the low 4 bits of the sender's class word:

| Sender | Class word | DreamSys slot | Function |
| --- | --- | --- | --- |
| Pad | low nibble 2 | 0x94 | `DreamSys_OnPad`: walk, turn, look, run, CIRCLE |
| Clock | low nibble 5 | 0x98 | `DreamSys_OnClock`, on message 2 (one tick) |
| StageMap | 0x114 | 0x9C, then 0x1E4 | `DreamSys_RouteMapMessage`, then `DreamSys_OnMapMessage` |
| A map tile | class byte 0x24 | 0x9C, then 0xE0 | `DreamSys_OnWallTouch` ([links](links.md)) |
| An entity | 0x1F234 | 0x9C, 0xDC, then 0x1E8 | `DreamSys_RouteEntityMessage`, then `DreamSys_OnEntityEvent` |

DreamRunner makes DreamSys watch the pad and the clock (`DreamRunner_Run`); `DreamSys_EnterMap` makes it watch the map; an entity and DreamSys watch each other through `Model_SetTarget` when the entity is attached.

## One tick

`DreamSys_OnClock` runs on each clock message 2:

1. `timer` goes up by one. If the value before the increment reached `timeLimit`, the dream is over: out of flashback mode, `DreamSys_MaybeSaveFlashback` may keep a memory, then DreamSys notifies 0xA (time up) and the timer goes back to 0. In flashback mode the next memory is loaded instead (`DreamSys_LoadNextFlashback`), and only when none is left does it notify 0xA.
2. Otherwise `DreamSys_TickBegin` clears the CIRCLE flag and sets `dynamicLinkOn = (timer % linkPeriod == 0)`; the place gives a period of 16 ([walls](../discoveries.md#-falling-off-an-edge-walls-and-the-cottages-walking-squares)).
3. `DreamSys_TickHandlers` calls the look handler and the move handler.

The handlers are picked by `DreamSys_SetLookMode` (0 none, 1 `DreamSys_TickLook`, 2 and 3 empty slots) and `DreamSys_SetMoveMode` (0 none, 1 `DreamSys_TickMove`, 2 `DreamSys_TickFall`, which also starts the fall sounds). `DreamSys_TickMove` turns, then walks one step (`DreamSys_TickStep`, `DreamSys_Walk`); during an auto walk it only walks forward. `DreamSys_Walk` asks the link code first ([links](links.md)) and moves only when no link fires. The step length is `g_walkSigns[direction] * g_walkSpeeds[speed]` with speeds 0, 0x18, 0x40, 0x80 and 0x180; the place gives speed 3 (2 in stage 0), and holding the run button pushes speed 4 (`DreamSys_PushSpeed`, `DreamSys_PopSpeed`). The footstep sound comes from the ground tile's flags ([links](links.md#walls-and-tile-flags)); the SHAKE option bobs the camera on each step.

## The dream timer

`DreamSys_SwapTimeLimit(seconds)` stores seconds x 15 and returns the old limit in seconds; a negative value means no limit. `DreamSys_GetElapsedSeconds` returns `timer / 15`. The limit is set:

- at the start of a dream, from the start stage (`DreamSys_ChooseStart`, `g_stageTimeLimits`);
- for each flashback, to its length + 4 (`DreamSys_EnterMap`);
- to elapsed + 30 s when a place's texture set fails to load (`Place_CheckTextureLoad`, [glitch textures](../discoveries.md#-glitch-textures-a-texture-set-that-failed-to-load));
- to elapsed + the extra seconds of an extra link from stage 0 (`DreamSys_LinkExtra`, 10 s, read in the code only).

Entity events 11 and 12 end the dream by setting `timer = timeLimit`, so the normal time-up path runs on the next tick. Player view: [the start place sets the length of the dream](../discoveries.md#-the-start-place-sets-the-length-of-the-dream).

## Transitions

Every link or event goes through `DreamSys_ExecuteLink(stage, transition, playSound)`: it stores the code in `transition`, notifies it, and if a watcher cleared `transition` during the notify, the link is cancelled. Otherwise it stores the new stage. The Place hears the codes in `Place_OnDreamSysNotify`, only while its state is 0; in any other state it sets `transition` back to 0, which cancels the link.

| Code | Source | Place reaction | Place state | End |
| --- | --- | --- | --- | --- |
| 0xA | time up (`DreamSys_OnClock`) | `Place_OnTimeUp`: `(ticks + stage) & 3` picks no fade or a fade to colour 0, 4 or 7; in flashback mode a 5-tick fade to colour 0 | 4 | end of day |
| 0xB | start chosen (`DreamSys_ChooseStart`, stored, not notified) | none | | |
| 0xC | random link (`DreamSys_LinkDynamic`) | `Place_OnLinkDynamic`: 10-tick fade to the dream colour; a negative stage goes to the 0xD handler | 5 | new place |
| 0xD | fixed link (`DreamSys_LinkStatic`) | `Place_OnLinkStatic`: 30-tick fade to the dream colour | 6 | new place |
| 0xE | next flashback (`DreamSys_LoadNextFlashback`) | `Place_OnNextFlashback`: fade to the day's colour | 7 | new place |
| 0xF | facing link (`DreamSys_LinkFacing`) | `Place_OnLinkFacing`: black fade, auto walk | 8 | new place |
| 0x10 | fall (`DreamSys_LinkFall`) | `Place_OnLinkFall`: black fade, fall mode, auto walk 2 | 10, then 4 | end of day |
| 0x11 | extra link (`DreamSys_LinkExtra`) | `Place_OnLinkExtra`: notifies 0xB, which the runner ignores | | same place |

When the fade ends, `Place_OnFaderNotify` notifies the place's state to its watcher, the DreamRunner. State 10 becomes 4 first, which is why a fall ends the day. `DreamRunner_OnPlaceMessage` rebuilds the place for states 5 to 8 (and 10, never reached), and ends the day for 4.

Note the order inside `DreamSys_ExecuteLink`: the notify runs before the new stage is stored. An entity link sets `stage` to minus its target before calling `DreamSys_LinkDynamic` (`DreamSys_OnEntityEvent`, message 10), so the place sees a negative stage and takes the 30-tick fade of a fixed link.

## A dream from start to end

1. `Scene_RunDream` makes a DreamRunner, which loads the dreamer model, the effects bank and the music bank ([stages and places](stages-and-places.md)).
2. On its first update the runner calls `DreamSys_StartDay`: it clears the timer, saves the day in `savedDay`, and either loads the first flashback (flashback mode), or looks for a special day (`Day_FindSpecial`, [randomness](randomness.md)). On a special day it returns -1 and the runner ends the day at once with result 2. Otherwise it resets the mood accumulators and calls `DreamSys_ChooseStart`, which returns the start stage.
3. The runner builds the Place for that stage. When the place is set up it calls `DreamSys_EnterMap`, which puts the dreamer at `place` and loads the chunks around it; when the place starts it calls `DreamSys_StartPlace` (logs the first chunk mood, look and move modes 1, speed, link period, controls on, `transition` 0, cinematic variant -1).
4. The dream runs: ticks, links (each rebuilds the place), touches.
5. Time up, a fall, an entity end or the erase combo makes the place notify the runner, which deletes the place and calls `DreamSys_EndDay(reason)`.

`DreamSys_EndDay` first puts back `savedDay` (a flashback changes `save.day`). Reason 0 out of flashback mode is a normal end: `DreamSys_CalcUnlockScore`, `DreamSys_ComputeDayPoint` into `graph[day]`, then `DreamSys_AdvanceDay`. Reason 2 (the SELECT + TRIANGLE erase, message 0xD) runs `DreamSys_InitNewGame`. Reason 1 (message 0xC, sent only by the never-called `Place_ExitNoRecord`) changes nothing. It returns `flashbackMode`.

The runner's result goes back to `Scene_RunDream`: 1 nothing to show, 2 play the cinematic of `cinematic` (a special day, or an entity's event video when category is -1), 3 skip the graph at the next title (flashback mode, an end or the erase).

## The end of a year

`DreamSys_AdvanceDay` adds 1 to `save.day` and at 365 sets it to 0 and adds 1 to `save.year`. `DreamSys_GetDayNumber` returns day + 1 (and the year through its pointer); special days, parity rules and texture cycles all use that number. `Scene_RunDream` returns 1 when the day number is 1 and the year is not 0, and the scene loop then plays `ETC\ENDING.STR` ([boot and objects](boot-and-objects.md)). Player view: [the day counter and the hidden year](../discoveries.md#-the-day-counter-and-the-hidden-year), [the ending](../discoveries.md#-the-ending-plays-when-a-year-closes-not-on-day-365).

## Moods and the graph

A mood is a MoodPoint, two s8 axes from -9 to 9 ([`include/game/stage.h`](../../include/game/stage.h)). Each chunk of a stage has one (`Stage_GetChunkMood`, [stages and places](stages-and-places.md)), each entity type has one in its record ([characters](characters.md)).

| Step | Function | What it does |
| --- | --- | --- |
| Reset | `DreamSys_ResetMoodAccumulators` | clears both accumulators; on a special day logs (0, 0) in both |
| Chunk entered | `DreamSys_OnMapMessage` (map message 5), `DreamSys_LogChunkMood` | logs the new chunk's mood in `chunkMood` |
| Entity touched | `DreamSys_OnEntityEvent` (message 9), `DreamSys_LogEntityMood` | logs the record's mood in `entityMood` |
| Log | `Mood_Log` | keeps the last point, adds each axis to its sum, counts |
| Resolve | `Mood_Resolve`, `Mood_CalcAxis` | per axis `sum / count + last / 3`; above 9 becomes -9, below -9 becomes 9 |
| Day point | `DreamSys_ComputeDayPoint` | mean of the chunk and entity results; the chunk result alone when nothing was touched |

The colour of the day so far is `DreamSys_GetDreamColor`: the day point banded by `Mood_GetColor` (an axis below -3 is band 0, -3 to 3 band 1, 4 and up band 2) and looked up in `g_moodColors[x band][y band]`:

| | y band 0 | y band 1 | y band 2 |
| --- | --- | --- | --- |
| x band 0 | 6 | 7 | 2 |
| x band 1 | 4 | 7 | 1 |
| x band 2 | 3 | 0 | 5 |

The names lsddecomp gives these indexes are 0 black, 1 blue, 2 green, 3 cyan, 4 red, 5 pink, 6 yellow, 7 white; the code itself only uses the numbers. The colour drives the link fades, the colour rules of the spawn tables ([characters](characters.md)) and `DreamSys_SetFlashbackMode(-1)`, which returns the colour of the stored day point for the flashback veil.

Where tomorrow starts: `DreamSys_ChooseStart` reads yesterday's point (`DreamSys_GetPreviousPoint` with 1; (0, 0) on the very first day), then `Spawn_PickFromMood` finds the first chunk with that mood ([links](links.md#where-a-dream-starts)). With 0 instead of 1, `DreamSys_GetPreviousPoint` averages all stored points; no code in the game calls it that way. On day 0 of year 1 and later it reads the two bytes before `graph[0]`: [the first dream of a new year](../discoveries.md#-the-first-dream-of-a-new-year-starts-from-the-wrong-data).

The graph screen (`src/game/graph.c`) only reads the save block. Player view: [how a day becomes a point on the graph](../discoveries.md#-how-a-day-becomes-a-point-on-the-graph), [the secret video reel](../discoveries.md#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film).

## Scores

`DreamSys_CalcUnlockScore` runs at each normal day end: `navScore = Nav_CalcScore()` (1,000,000 per set navigation flag, 50,000,000 when all 30 are set, minus 11,024 per dynamic link, never below 0), `instanceScore` clamped to 0..50,000,000, and `unlockScore = navScore + instanceScore`. Touching an entity adds its record's points x 1000 to `instanceScore`. The menu shows FLASHBACK once `unlockScore` is above 9,999,999 and one memory is kept. Player view: [what unlocks Flashback](../discoveries.md#-what-unlocks-flashback-in-the-menu).

## Flashbacks

| Step | Function |
| --- | --- |
| Keep | `DreamSys_MaybeSaveFlashback`: on time up and on each touch, `rand() % 3 == 0` keeps {stage, place, rotation, length 16 s, day} |
| Store | `DreamSys_AddFlashback`: appends while fewer than 10, else overwrites entry `timer % 9` |
| Erase | `DreamSys_ClearFlashbacks`: count to 0, called only by the Grey Man's handler ([characters](characters.md)) |
| Replay on | the menu's FLASHBACK item calls `DreamSys_SetFlashbackMode(.., 1)`; the menu's reset turns it off |
| Replay | `DreamSys_StartDay` loads entry 0; each time up loads the next (`DreamSys_LoadNextFlashback`, transition 0xE) until none is left |

In flashback mode `DreamSys_ExecuteLink` restarts the timer on every link, touches log nothing, entity events 11 and 12 do nothing, and `DreamSys_EndDay` adds no graph point and keeps the day. Player view: [how flashback memories are kept](../discoveries.md#-how-flashback-memories-are-kept), [what erases the flashbacks](../discoveries.md#-what-erases-the-flashbacks).

## Unknowns

- `DreamSys_SetLinkFlags` stores three more flags at +0x128 to +0x130 that no game code reads.
- `func_8005BA20` (slot 0x228) swaps +0x924; `Scene_Init` passes it a scene setting and `DreamSys_Reset` clears it. Nothing else reads it.

# Randomness

Every die the game rolls comes from one generator: the PSY-Q `rand`, a linear congruential sequence. The game seeds it once at most, before the title screen, from leftover render data, and then lets it run for the whole session. Many things that look random are not: they follow the day number, the stage, the dream timer or the place's tick count. This page lists both.

Code: the wrapper and the pickers in [`src/game/path_table.c`](../../src/game/path_table.c), the seed in [`src/game/scene.c`](../../src/game/scene.c), the draws in [`src/game/dream_link.c`](../../src/game/dream_link.c), [`src/game/dream_sys.c`](../../src/game/dream_sys.c), [`src/game/sym.c`](../../src/game/sym.c), [`src/game/scenery.c`](../../src/game/scenery.c), [`src/game/scenery_obj.c`](../../src/game/scenery_obj.c) and [`src/game/entity.c`](../../src/game/entity.c). `rand` and `srand` themselves are Sony code (`psyq/80049480`).

## The generator

| Item | Value |
| --- | --- |
| Draw | `rand` @0x80049480: `g_randState = g_randState * 0x41C64E6D + 0x3039`, returns bits 16 to 30 (0 to 32767) |
| State | `g_randState` @0x8008AC68, 0 in the executable |
| Seed | `srand` @0x800494A8, one caller: `Rand_SeedAndNext` |
| Wrapper | `Rand_SeedAndNext(seed)`: calls `srand(seed)` only when seed is not 0, then returns `rand()` |

The game draws in two ways: `rand()` directly (dream_link.c, dream_sys.c, sym.c, scenery, entity.c), and `Rand_SeedAndNext(0)`, which is the same draw (the music, texture and opening pickers). Some callers pass `Rand_SeedAndNext` a second argument; its K&R definition ignores it ([naming](../naming.md), Prototypes).

The only non-zero seed: `Scene_SeedRandom`, slot 0x40 of the scene, run once by `Scene_Init`, calls `Rand_SeedAndNext(*(s32 *)0x1F800000 % 365)`. 0x1F800000 is the scratchpad, which `View_DrawNode` hands to `Render_SortModel` as its work buffer ([rendering](rendering.md)), so the seed is whatever the renderer left there. When that word is a multiple of 365 the seed is 0 and `srand` is not called. In the emulator it was 0. Player view: [the dice of the game](../discoveries.md#-the-dice-of-the-game).

Since every draw takes the next number of one sequence, the result of a roll depends on how many draws came before it. Some draws happen every tick: an asleep entity with wake mode 3 (in range) or 4 rolls `(rand() & 0x7F) == 0` each tick ([characters](characters.md#the-record)), the kind 3 scenery of a family 0 place draws 8 numbers each tick (`Scenery_UpdateKind3`), and some handlers draw every tick (`Behavior_Mushroom` starts or stops its animation on `rand() % 12` and `rand() % 6`). So in practice the sequence keeps moving with play.

## What draws

| Roll | Function | Draw | Effect |
| --- | --- | --- | --- |
| Opening video | `Cine_PickOpeningPath` | `% 7` | one of `ETC\OPENINGA.STR` to `G` |
| Music bank | `Music_PickBank` (each dream) | `% 7` | one of the 7 `SND\` banks ([sound and video](sound-and-video.md)) |
| Music track | `Music_PickTrack` (each place) | `% 5` | `BGA` to `BGE.SEQ`; in stage 9 track 2 becomes 3 |
| Texture set | `Stage_PickTexturePath` (each place) | `% (((day - 1) % 40) / 10 + 1)` | `TEXA` to `TEXD.TIX` ([below](#texture-sets)) |
| Special day | `Day_FindSpecial` | `% 6` | the variant: video or picture ([below](#special-days)) |
| Random link | `Spawn_PickRandom` | `% 6`, then `% count` | target stage 0 to 5, then the arrival point ([links](links.md#random-links)) |
| Flashback | `DreamSys_MaybeSaveFlashback` | `% 3 == 0` | keep the moment ([dream system](dream-system.md#flashbacks)) |
| Grey Man | `Sym_SpawnOrSpy` | `% 12 == 0` | spawn him at a blocked slot on an even day ([characters](characters.md#the-grey-man)) |
| Scenery | `Scenery_CreateAll`, `Scenery_CreateKind0` to `Kind3`, `Scenery_RandomizeParams` | `& 3`, `% 7`, `% 5`, `% 23`, `& 1` and more | count, variant, scale, height, offsets, rotation, colour of each object |
| Scenery tick | `Scenery_UpdateKind3`, `Scenery_BuildKind2` | `% 6`, `% 360`, `% 2` | part scales and angles, kind 2 scale |
| Wake | `Entity_CheckWake` | `& 0x7F` | wake modes 3 and 4 |
| Handlers | `Behavior_*` (67 draws in entity.c) | various | sizes, paths, states, endings ([characters](characters.md#behaviour-handlers)) |

## Texture sets

Each stage has four texture sets, `TEXA.TIX` to `TEXD.TIX`, the first four paths of the stage ([stages and places](stages-and-places.md#the-stages)). `Place_Load` calls `Stage_PickTexturePath(stage, 0, day number)`:

| Day number in its 40-day cycle | Sets that can load |
| --- | --- |
| 1 to 10 | A |
| 11 to 20 | A, B |
| 21 to 30 | A to C |
| 31 to 40 | A to D |

The pick is `rand() % n` among the first n sets. `Tix_Create` reads the chosen file; `Place_CheckTextureLoad` applies it with the ambience colour, or drops it and shortens the dream when the heap cannot hold it ([stages and places](stages-and-places.md#the-life-of-a-place), [files and CD](files-and-cd.md)). Player view: [the 40-day texture cycle](../discoveries.md#-the-40-day-texture-cycle).

## Special days

`DreamSys_StartDay` calls `Day_FindSpecial(cinematic, day number)` before choosing a start ([dream system](dream-system.md#a-dream-from-start-to-end)). It searches the 42 s16 day numbers of `g_specialDays`; on the first match at index i it writes category `i % 12` and variant `rand() % 6` into DreamSys's `cinematic` and returns `g_specialDayPoint`, the (0, 0) point both mood accumulators start from. The day then has no dream: the runner ends it at once with result 2, and `Scene_PlayCinematic` shows the cinematic.

`Cine_GetPath(videoId, {category, variant})` resolves it in the path table ([files and CD](files-and-cd.md)):

| Variant | Content | Shown by |
| --- | --- | --- |
| 0, 1 | `FILM\SPDAYnnA.STR`, `B.STR`, video id `category * 2 + 14 + variant` | `VideoScreen_New`, when the scene's video setting is on |
| 2 to 5 | a still picture, video id -1 | `MenuScreen_New` with a 10-second timeout |

Each category takes 0xA8 bytes of the path table from `g_pathTable + 0x3EC8` (`Cine_GetSpecialDayPaths`), 6 paths of 0x1C bytes. A negative category is an entity's event video instead (`Cine_GetEventPath`, `FILM\EVENTn.STR`, video ids from 8). The table holds day 126 twice (indexes 5 and 30), so index 30 never matches. Player view: [the 42 special days](../discoveries.md#-the-42-special-days), [what a special day shows](../discoveries.md#-what-a-special-day-shows).

## Not random

| Looks random | What decides it | Code |
| --- | --- | --- |
| Which characters appear | day parity, 3-day and 30-day cycles, the day's colour, "once" flags | `Sym_CheckDayParity`, `Sym_CheckRule` |
| A place's ambience and sky | `(day number + stage) & 15` picks the family, `% count` the record | `Ambience_PickFamily` |
| Where a dream starts | yesterday's graph point, first matching chunk | `Spawn_PickFromMood` |
| When a wall gives a random link | `timer % 16 == 0` | `DreamSys_TickBegin` |
| Where a fall would send you | an odd timer picks stage 12 | `Link_PickFallStage` |
| The fade at time up | `(place ticks + stage) & 3`: no fade, or colour 0, 4 or 7 | `Place_OnTimeUp` |
| Which old flashback is replaced | `timer % 9` | `DreamSys_AddFlashback` |
| The cloud band | day number divisible by 7, then day % 3 for its distance | `Scenery_RandomizeParamsDay7` (it still draws for x) |
| Giant flowers and tall mushrooms | day number % 3: always on one residue (1 for flowers, 2 for mushrooms), a 1-in-3 roll when it is 0, never on the other | `Behavior_Flower`, `Behavior_Mushroom` |

The "type A" and "type B" days players talk about are odd and even day numbers, through the slots' day flags and rules 20 and 21.

## Unknowns

- What the scratchpad holds at the seed on a real console was not measured; the emulator gave 0.

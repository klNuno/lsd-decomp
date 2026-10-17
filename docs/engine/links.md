# Links

A link moves the dreamer to another place. The game has six kinds: a fixed link through a marked wall, a random link through a marked wall, a facing link when the dreamer walks forward onto a marked tile facing the right way, an extra link list switched on by some stages and characters, the scripted walks of stage 0, and links that characters send. Falling off an edge also runs the link code, but it ends the day. Each place has fixed arrival points; the same tables pick where each dream starts.

Code: [`src/game/dream_link.c`](../../src/game/dream_link.c) (tables and pickers), the DreamSys methods in [`src/game/dream_sys.c`](../../src/game/dream_sys.c) that call them, and the tile messages in [`src/game/stage_map.c`](../../src/game/stage_map.c) and [`src/game/map_tile.c`](../../src/game/map_tile.c). What happens after a link (fade, new place) is in [the dream system](dream-system.md#transitions).

## Places on a stage

A position is a StagePlace, 10 bytes ([`include/game/stage.h`](../../include/game/stage.h)): chunk column and row, tile x and y in the chunk (0 to 19), and an x, y, z offset from the tile centre. The link code compares two keys built from it, as `StageMap_GetLocation` keeps them in its MapLocation:

- chunk key: `col | row << 8` (s16);
- tile key: `tileX | tileY << 8` (s16).

Link targets and arrival points are SpawnPoint records of 6 bytes: the 4 tile bytes, an index into `g_tileOffsets` (6-byte x, y, z offsets in the tile) and the navigation flag the link sets. `Link_Find` and the spawn pickers copy both parts into the output StagePlace. [Stages and places](stages-and-places.md) explains how a StagePlace becomes a world position.

## Walls and tile flags

Every tile model of a chunk keeps the flags byte of its map record (`StageMap_BuildTiles`, [stages and places](stages-and-places.md#chunks-tiles-and-models)). Bit 0x80 makes it a wall; the low 7 bits are the footstep sound.

How a wall touch reaches DreamSys:

1. After each move an actor sends its box list (`Actor_MoveAxis`, `Actor_SendBoxes`, messages 6, 7 and 8 for its z, x and y axes).
2. The StageMap passes these messages on only for the senders whose class word is in `g_placeMapMessageFilter`: DreamSys (0x1F34) and entities (0x1F234) (`StageMap_FilterMessage`).
3. `StageMap_TellNearTiles` locates the sender and builds a 3 x 3 tile view around it (its whole floor on a stacked stage); `StageMap_TellViewTiles` walks those tiles and their stacked models and stores the chunk key and tile of each one in `tellKey`, `tellX`, `tellY`.
4. `MapTile_Tell` passes the message to a tile only when `flags & 0x80`. The tile (`MapTile_OnActorMessage`) runs `SceneNode_CheckContact`: within 0x4000 units on each axis, the sender's boxes must overlap the tile model's boxes and pass the ray tests. Then the sender gets message 4 with the tile as sender.
5. In DreamSys, a sender of class byte 0x24 (a map tile) reaches `DreamSys_OnWallTouch`.

`DreamSys_OnWallTouch` (message 4, no transition running) copies the told tile's place (`StageMap_GetTellKey`) into `place`, tries `DreamSys_LinkStatic`, then, if no fixed link matched and `dynamicLinkOn` is set, `DreamSys_LinkDynamic`. In every case it then puts the dreamer back where it was before the step (`DreamSys_RestorePosition`, saved by `DreamSys_Walk`). An entity that touches a wall falls asleep instead (`Entity_OnWallTouch`).

The footstep sound: when the ground test finds a tile under the dreamer, `DreamSys_OnGroundProbe` (message -1) takes `contact->flags & 0x7F` as the step sound (0x18 and above give 0); `DreamSys_PlayStepSound` plays tone `g_stepSoundTones[sound]` at octave `g_stepSoundOctaves[sound]`.

Player view: [the world is built from square blocks](../discoveries.md#-the-world-is-built-from-square-blocks-and-only-marked-blocks-are-walls).

## The link tables

Four link lists share one format and one search, `Link_Find(out, location, stage, counts, lists, targets, setNavFlag)`. Each list is per stage: `counts[stage]` entries of 6 bytes in `lists[stage]`, each {chunk key, tile key, target stage, target index}. A tile key below 0 matches any tile of the chunk. On a match, `Link_Find` writes the target `targets[toStage][toIndex]` into `out`, sets `g_navFlags[target.navFlag]` when asked, records the match in `g_linkFromStage`, `g_linkFromIndex`, `g_linkToStage` and `g_linkToIndex`, and returns the target stage. It reads neither the day nor a counter.

| Kind | Finder | Counts, lists, targets | Sets the nav flag | Extra check | Transition |
| --- | --- | --- | --- | --- | --- |
| Fixed (wall) | `Link_FindStatic` | `g_staticLinkCounts`, `g_staticLinkLists`, `g_staticLinkTargets` | yes | none | 0xD |
| Facing | `Link_FindFacing` | `g_facingLinkCounts`, `g_facingLinkLists`, `g_facingLinkTargets` | yes | heading, walking forward | 0xF |
| Extra | `Link_FindExtra` | `g_extraLinkCounts`, `g_extraLinkLists`, `g_extraLinkTargets` | no | `g_extraListOn` | 0x11 |
| Scripted | `Link_FindScripted` | `g_scriptedLinkCounts`, `g_scriptedLinkLists`, `g_scriptedLinkTargets` | no | stage 0 only, heading, walking forward | none |

The fixed and facing lists are the 30 navigation goals of the flashback score; goal 13 is in neither ([fixed links are the navigation goals](../discoveries.md#-fixed-links-are-the-navigation-goals-and-one-can-never-be-completed)).

## Links checked on each step

`DreamSys_Walk` asks the map for the dreamer's location before moving and tries, in order:

1. `DreamSys_StartLinkStep`: a scripted walk already running, or a new one.
2. `DreamSys_LinkExtra`.
3. `DreamSys_LinkFacing`.

`DreamSys_StartLinkStep` always returns 0, so it never stops the step; when the extra or the facing link fires, the dreamer does not move. These links fire on the tile the dreamer stands on, not on a wall.

Facing and scripted links also need the heading. `Link_CheckFacing` (`Link_CheckScripted` for the scripted list) reads the heading of the matched entry (`g_facingLinkHeadings[from stage][from index]`), and `Link_IsFacing` accepts the dreamer's yaw when it lies within -44 to +44 degrees of `g_linkHeadingYaws[heading]`. The link also needs `walkingForward`. It returns two rotations from `g_linkHeadings`: the heading to walk in (`linkHeading`) and the one to face on arrival (`arrivalHeading`, from `g_facingArrivalHeadings[to stage][to index]`). The place's reaction to transition 0xF turns on the auto walk (`DreamSys_SetAutoWalk`), which faces `linkHeading`; `DreamSys_EnterMap` turns the dreamer to `arrivalHeading` in the new place.

The extra list: `Link_FindExtra` searches only while `g_extraListOn` is set. `Sym_InitStage` sets it at each place load to (stage == 3 or stage == 11), and `Sym_EnableExtraListForType` sets it when a spawn group of type 11, 56, 78 or 93 passes its rule ([characters](characters.md)). An extra link does not rebuild the place: after `DreamSys_ExecuteLink` the transition goes back to 0 and the dreamer is moved to the target on the loaded map (`StageMap_PlaceToWorld`, `Actor_SetPos`). `Link_GetExtraSeconds` returns 10 when the link came from stage 0, and the time limit becomes elapsed + 10 s (read in the code only).

The scripted walks: on one of the 8 tiles of stage 0, facing the heading and walking forward, `DreamSys_StartLinkStep` stores the target in `linkStartPlace`, ignores the pad, skips the move boxes and picks `g_linkSteps[Link_GetStepScript()]` (byte 5 of the target record). Each tick it runs that step function until it returns 1:

| Script | Function | Ticks (walking, running) | What it does |
| --- | --- | --- | --- |
| 0 | `DreamSys_LinkStep0` | 0x85, 0x13 | two turns, forward steps |
| 1 | `DreamSys_LinkStep1` | 0x95, 0x19 | three turns the other way, looks down, forward steps |
| 2 | `DreamSys_LinkStep2` | 101, 15 | one turn, forward steps |
| 3 | `DreamSys_LinkStep3` | 0x71, 0x13 | two turns, looks down, forward steps |

Each script first moves the dreamer to a start offset in the tile (`DreamSys_MoveToTileOffset`). None of them calls `DreamSys_ExecuteLink`: the walk only moves the dreamer and gives the pad back. Stage 0 also has a hard-coded wall touch in `DreamSys_Walk`: a y below -2000 with x of -499 or more calls `DreamSys_OnWallTouch` on the dreamer itself.

## Random links

`DreamSys_LinkDynamic` calls `Spawn_PickRandom(place, stage, timer)`:

- with `stage >= 0`, it draws `rand() % 6` among stages 0 to 5 and moves a draw equal to the current stage to the next one (5 wraps to 0);
- with a negative stage, it takes `-stage` as is.

Then it picks one of the target stage's arrival points, `g_spawnPoints[stage] + rand() % g_spawnCounts[stage]`, and adds 1 to the dynamic link count (`g_dynamicLinkCount`, which points into the save block). Every call counts, whatever its caller: wall links, character links, falls and the fallback start. Each count takes 11,024 off the navigation score ([scores](dream-system.md#scores)). Player view: [where a random link sends you](../discoveries.md#-where-a-random-link-sends-you).

A wall gives a random link only on a tick where `timer % 16 == 0` (`DreamSys_TickBegin`), so pressing against a wall links within 16 ticks.

## Links sent by characters

An entity record names a link stage ([characters](characters.md)). The entity posts event 10 when the dreamer bumps into it with a positive link, or when the dreamer comes within its link radius with a negative one. `DreamSys_OnEntityEvent` (message 10) sets `stage` to minus `Entity_GetLinkStage`, calls `DreamSys_LinkDynamic`, and puts the old stage back if the link did not run. Through `Spawn_PickRandom` with a negative stage, the target stage is fixed and the arrival point random. Player view: [signals from characters](../discoveries.md#-signals-from-characters-and-objects).

## Falls

After each step the ground test (`Actor_SnapToGround`) sends -1 when it found a tile under the actor and -2 when it did not. `DreamSys_OnGroundProbe` handles both:

- -2: when the map slot under the new position has its chunk built (`loaded == 2`), `DreamSys_LinkFall`; else the dreamer is put back.
- -1: in stage 9 only, `DreamSys_LinkFall` too, with the ground found.

`Link_PickFallStage` returns -1 except in stages 1, 3, 5, 9 and 12. Stage 5 also needs a height below -0xFFF or the place `g_fallPlace5`; stage 9 needs a height of 0x800 or more. An odd `timer` makes the stage -12, so `Spawn_PickRandom` returns stage 12; otherwise it draws as for a wall. `Link_GetFallTurn` gives `g_fallTurn` unless the target is 12. The link runs with transition 0x10: the place puts DreamSys in move mode 2 (`DreamSys_TickFall` moves it by `g_fallStep` each tick and tilts the camera) and, at the end of the black fade, turns its state 10 into 4, the time-up state. The day ends; the picked stage is never built. Player view: [falling off an edge](../discoveries.md#-falling-off-an-edge-walls-and-the-cottages-walking-squares).

## Where a dream starts

The start of each dream uses the same arrival points. `DreamSys_ChooseStart` passes yesterday's graph point to `Spawn_PickFromMood`:

1. `Stage_FindChunkByMood` scans stages 0 to 13 and their chunks row by row and returns the first chunk whose s16 mood equals the point.
2. In that stage, the arrival point whose 2-byte chunk key equals the chunk is taken; when none does, entry `chunkKey % count`.
3. The time limit comes from `g_stageTimeLimits[stage]`.
4. With no matching chunk, `Stage_FindChunkByMood` returns -1 and `Spawn_PickRandom(-1)` turns it into stage 1, at a random arrival point.

Player view: [how the graph picks where tomorrow starts](../discoveries.md#-how-the-graph-picks-where-tomorrow-starts).

## Tables

| Symbol | Content |
| --- | --- |
| `g_staticLinkCounts`, `g_staticLinkLists`, `g_staticLinkTargets` | fixed wall links per stage |
| `g_facingLinkCounts`, `g_facingLinkLists`, `g_facingLinkTargets` | facing links per stage |
| `g_facingLinkHeadings`, `g_facingArrivalHeadings` | heading index per entry and per target |
| `g_extraLinkCounts`, `g_extraLinkLists`, `g_extraLinkTargets` | the extra list |
| `g_scriptedLinkCounts`, `g_scriptedLinkLists`, `g_scriptedLinkTargets` | stage 0's 8 scripted tiles |
| `g_linkHeadings`, `g_linkHeadingYaws` | 12-byte rotations and their yaw |
| `g_spawnPoints`, `g_spawnCounts` | arrival points per stage |
| `g_tileOffsets` | offsets in a tile |
| `g_stageTimeLimits` | dream length in seconds per start stage |
| `g_navFlags`, `g_dynamicLinkCount` | pointers into the save block, set by `Nav_InitFlags` |
| `g_linkSteps` | the 4 scripted walks |

A dump of the fixed and facing lists: `work/hunt3/links.py`.

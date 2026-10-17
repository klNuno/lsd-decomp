# Characters

Characters and objects that move, wake up or react are entities. Each map chunk lists spawn slots; when the chunk's character models arrive, the spawn code checks each slot's day rule and its groups' rules and creates the entities that pass. Each entity type has a 16-byte record (mood, points, wake and sleep rules, ranges, link, video) and a behaviour handler that runs every tick. One character is special: the Grey Man is created once per place and moved in front of the dreamer when a die allows it.

Code: [`src/game/sym.c`](../../src/game/sym.c) (spawning), [`src/game/entity.c`](../../src/game/entity.c) (the entity class and its 115 behaviour handlers), [`src/game/model.c`](../../src/game/model.c) (the model base class), [`src/game/actor.c`](../../src/game/actor.c) (movement), [`src/game/handler_node.c`](../../src/game/handler_node.c) (per-tick handler and its sounds). Types: [`include/game/entity.h`](../../include/game/entity.h).

## Spawning

The place spawns the characters of a chunk when the map tells it the chunk's entity part has arrived (map message 7, [stages and places](stages-and-places.md#the-stagemap)):

1. `Place_SpawnCell` takes the map's current slot and its chunk key and calls `Sym_SpawnOrSpy(entities, chunkKey, day number)`. When nothing spawns, it frees the chunk's entity part.
2. `Sym_FindSlot` looks for the chunk key in `g_spawnSlots[stage]`. One exception, `Sym_PickSlotVariant`: in stage 4, slot 16 is replaced by the slot 5 entries further when the day's colour is 4 (red).
3. `Sym_CheckDayParity`: a slot's day flag of 0 passes every day; otherwise the slot is skipped when `(day number % 2) + 1` equals it (flag 1 passes on odd day numbers, flag 2 on even ones).
4. A skipped slot may get the Grey Man instead ([below](#the-grey-man)).
5. `Sym_SpawnSlot` makes an Mml object from the entity part (`Mml_Create`, the square's character models) and tries each of the slot's up to 3 groups (`Sym_SpawnGroup`).
6. `Sym_SpawnGroup` checks the group's rule (`Sym_CheckRule`). When it passes, it takes model `group.model` of the square (`Mml` slot 0x88) and creates the group's entity type at each of its up to 4 places (`Sym_SpawnAtPlace`). A group of type 2 also tries the group 7 entries further.
7. `Sym_SpawnAtPlace` calls `Entity_Create(type, source, soundBank)`, turns the place record into a world position (`StageMap_PlaceToWorld` with the slot's chunk key and a `g_spawnPlaceOffsets` record), sets its rotation (`g_spawnPlaceRotations`) and attaches it with DreamSys, the clock and the map.

The spawned Mml is kept in the map slot and deleted when the slot is reassigned.

| Table | Record | Fields |
| --- | --- | --- |
| `g_spawnSlots[stage]`, `g_spawnSlotCounts` | 6 bytes | chunk key, day flag, 3 group indexes (-1 ends) |
| `g_spawnGroups[stage]`, `g_spawnGroupCounts` | 8 bytes | done flag, rule, model index, entity type, 4 place indexes (-1 ends) |
| `g_spawnPlaces` | 4 bytes | tile word, rotation index, offset index |

Dumps of these tables: `work/hunt3/spawns.py`.

### Rules

`Sym_CheckRule(day number, group)`; a passing rule sets the group's done flag. A negative rule is "once": it uses the same test on its absolute value but fails while the done flag is set. `Sym_ResetGroupsAndLoadSpy` clears every done flag when a DreamRunner is made, so "once" means once per dream (likely, from that call site).

| Rule | Passes when |
| --- | --- |
| 0, 1 | always |
| 2, 3, 4 | the 30-day month `(day - 1) / 30 + 1` is rule - 1, plus 0, 3, 6 or 9 (`Sym_CheckMonthRule`) |
| 5 | day % 3 == 0 |
| 6 | day % 3 != 0 |
| 7 | the ambience family is even (`Ambience_IsEvenFamily`, [ambience](stages-and-places.md#ambience-and-scenery)) |
| 8, 9 | day % 3 == 1 or 2 |
| 10 to 17 | the day's colour equals `g_ruleColors[rule - 10]` (`Sym_CheckColorRule`, `DreamSys_GetDreamColor`) |
| 20 | even day |
| 21 | odd day |
| others below 10 | always |

The colour is the running day point at the moment the chunk loads ([moods](dream-system.md#moods-and-the-graph)). A chunk loads when it enters the 7 map slots around the dreamer (`StageMap_LoadAround`: the dreamer's square and its 6 neighbours, odd rows shifted half a square left), which `StageMap_Follow` requests in the same tick as map message 5, the one that logs the new square's mood. So a square's characters are made with the colour of the step onto one of its neighbours, and the square's own mood is logged only later, when the dreamer steps on it; only the start square is logged before its characters. A move to a square that is not loaded is never seen by `StageMap_Follow`, so it logs and loads nothing. Checked in the emulator (`work/hunt10/L1-findings.md` section 2), and used to reach the Natural World's cyan lions with no colour forced ([the lions](../discoveries.md#-the-natural-world-lions-a-random-temper-and-a-cyan-day-pair-that-leads-to-temple-dojo)). `Sym_EnableExtraListForType` also switches on the extra link list when a group of type 11, 56, 78 or 93 passes ([links](links.md#links-checked-on-each-step)). Player view: [the hidden rules that decide which characters appear](../discoveries.md#-the-hidden-rules-that-decide-which-characters-appear).

## The entity class

| Class | File | Size | Vtable | Constructor |
| --- | --- | --- | --- | --- |
| Actor | `actor.c` | 0x58 | 0x800878D4 | `Actor_Construct` |
| Model, an Actor | `model.c` | 0x98 | 0x8008A6C4 | `Model_Construct` |
| Entity, a Model | `entity.c` | 0x108 | 0x80089AD4, class word 0x1F234 | `Entity_Construct` |

Model splits a model file into parts (one per TMD object), plays one animation frame by frame (`Model_Tick`, `Model_ApplyFrame`) and keeps a target: `Model_SetTarget` makes the entity and DreamSys watch each other, which is how entity events reach DreamSys. Actor gives the moves (`Actor_MoveZ`, `Actor_MoveX`, `Actor_MoveY` along the model's own axes, `Actor_MoveZOnGround` with the ground test). Their third argument, `notify`, makes `Actor_MoveAxis` send the box list after the move (`sendBoxes`, message 6, 7 or 8 for z, x or y); the map passes it to wall tiles, and a hit wall answers with message 4, which `Entity_OnWallTouch` turns into sleep ([walls](links.md#walls-and-tile-flags)). It is a wall check, not a follow flag: the minotaur rickshaw moves with it and rolls straight on ([the rickshaws](../discoveries.md#-three-minotaur-rickshaws-on-a-yellow-day-in-kyoto)).

`Entity_Create(type, source, soundBank)` allocates 0x108 bytes and constructs: the Model part, the type, no effects, then `Entity_Init` (light flags 1 when the record's points byte is 1 to 9, tick mode 0x42, asleep). `Entity_Attach` attaches the model; a record with wake mode 0 wakes at once, and with handler range 0 also starts its handler at once.

The entity slots that matter:

| Slot | Function | Role |
| --- | --- | --- |
| 0x30 | `Object_Notify` | posts an entity event to its watchers |
| 0x44, 0x48 | `SceneNode_SetRotation`, `SceneNode_SetScale` | rotation and scale as {num, den} fractions, set or added |
| 0x4C, 0x50 | `Entity_Attach`, `Entity_Detach` | |
| 0x98 | `Entity_Update` | each clock tick |
| 0xDC | `Entity_OnActorTouch` | a contact; posts the record's link or end |
| 0xE0 | `Entity_OnWallTouch` | a wall: falls asleep |
| 0x14C to 0x158 | `Entity_GetRecord`, `Entity_GetPoints`, `Entity_GetLinkStage`, `Entity_GetVideo` | record readers DreamSys calls |
| 0x15C, 0x160 | `Entity_Wake`, `Entity_Sleep` | visible and awake, or hidden, handler stopped, touch cleared |
| 0x164 | `Entity_SetTouched` | posts event 9 |
| 0x168, 0x16C | `Entity_StartHandler`, `Entity_StopHandler` | the behaviour handler, animation and tick |
| 0x170 to 0x180 | `Entity_CheckWake`, `Entity_CheckSleep`, `Entity_CheckTouch`, `Entity_CheckHandlerStart`, `Entity_CheckHandlerStop` | the record's rules |

### One tick

`Entity_Update` runs on each clock tick: `Entity_CheckWake`, and `Entity_CheckSleep` while awake (which also runs `Entity_CheckLinkRadius`); `Entity_CheckHandlerStart`, and `Entity_CheckHandlerStop` while the handler runs; `Entity_CheckTouch`; then the model's update (`Model_Tick`). Tick mode 0x42 makes the model's per-tick function slot 0x11C, `Entity_RunHandler`, which runs the handler (`HandlerNode_Run`) while `Entity_StartHandler` has the tick on; then the animation steps one frame.

Every range test goes through `Entity_IsAtPointAhead`, which calls `DreamSys_TestPointAhead`: the point `range << 11` units ahead of the dreamer along the camera's sight line must fall within `boxSize << 11` of the entity on each axis (`0x800 / -boxSize` when negative; `Entity_IsWithinBox`). So "in range" means "looked at from that distance", not a circle around the dreamer. A record with a points byte of -1 to -9 raises the tested point by `points * 1024`.

### The record

`g_entityRecords[type]`, 16 bytes ([`include/game/entity.h`](../../include/game/entity.h), `EntityRecord`):

| Offset | Field | Use |
| --- | --- | --- |
| 0x0 | mood | logged when touched |
| 0x2 | points | x 1000 into the instance score |
| 0x3 | wake mode | 0 at spawn, 1 in range, 2 out of range, 3 in range and `(rand() & 0x7F) == 0`, 4 that die anywhere |
| 0x4 | sleep mode | 1 in range, 2 out of range, 10 and up after `mode * 15` ticks awake |
| 0x5 | wake range | range of the wake and sleep tests |
| 0x6 | touch range | negative: the entity also turns to face the dreamer (`SceneNode_TurnToward`) |
| 0x7 | link | above 0 stage link - 1, below 0 stage `~link`; 0x7F ends the dream |
| 0x8 | video | event video + 1; with a negative link, the link radius `<< 9` |
| 0x9 | box size | last parameter of every range test |
| 0xA | sound range | over which the handler's sounds fade |
| 0xB | handler range | starts the handler; negative also stops it out of range |
| 0xC | handler | the behaviour function |

A dump of the 130 records: `work/hunt3/recs.py`. Player view: [the character record](../discoveries.md#-the-character-record-mood-points-waking-up-and-leaving).

### Events

| Event | Sent by | DreamSys reaction (`DreamSys_OnEntityEvent`) |
| --- | --- | --- |
| 4 | DreamSys's contact with an entity | passes it back to the entity's slot 0x38 |
| 9 | `Entity_SetTouched` | logs the mood, adds the points, may keep a flashback |
| 10 | `Entity_OnActorTouch` with a link above 0, `Entity_CheckLinkRadius` with a link below 0, handlers | link to the record's stage ([links](links.md#links-sent-by-characters)) |
| 11 | `Entity_OnActorTouch` with link 0x7F and a video, handlers | ends the dream and queues the record's video |
| 12 | `Entity_OnActorTouch` with link 0x7F and no video, handlers | ends the dream |

All are ignored while a transition runs; 9, 11 and 12 do nothing in flashback mode. Player view: [signals from characters and objects](../discoveries.md#-signals-from-characters-and-objects).

## Behaviour handlers

A handler has the form `handler(entity, node)`. `Entity_StartHandler` registers the record's handler in the entity's HandlerNode (`HandlerNode_Start`, node id type + 1), plays the animation and starts the tick. Each tick `HandlerNode_Run` resets the node's 3 voices, calls the handler, then plays the sounds the handler put in `node->voices[i].sound` and `octave`, at a volume lowered by `node->fade` (the handler usually sets it from `Entity_GetSoundFade`). A sound of -2 stops the voice.

Handlers count their own ticks in `entity->handlerTicks` (0 on the first tick, so first-tick draws happen once per wake) and keep a state in `entity->state` (1 stops `Entity_CheckWake` for good). What they do with them: move (`moveZ`, `moveZOnGround`), turn (`rotate`, `SceneNode_TurnToward`), resize (`scale`), read the CIRCLE flag (`DreamSys_WasCirclePressed`), stop or give back the controls (`DreamSys_SetControls`), flash the screen (`Entity_StartEffect`, a Fade), post events, and call DreamSys or the map.

Handlers are named `Behavior_TypeNNN` after their entity type until their character is known (`Behavior_Astronaut`, `Behavior_FlyingTrain`, `Behavior_MazePenguin`). Some characters are now known while their handler keeps its type name: `Behavior_Type85` is the Violence District gunman; `Behavior_Type81` runs the Natural World lions, types 81 and 120 on one model, and draws a temper at the first tick (`rand() & 1`, then `state = rand() % 3`: calm 2 times in 3, a charge or a stare that posts event 12, 1 in 6 each); `Behavior_Type31` is the Abyss Demon, which holds the controls until its animation has played once, then posts event 10. Record 81 is the only one with link 0x7F, so walking into a savannah lion ends the dream, while record 120 links to stage 7. A charging lion (state 1) grows by `g_scaleGrowStep` each tick and sleeps within 0x200 of the dreamer; in the emulator its contact always came first, so the charge ends the dream through link 0x7F.

Handlers whose first reading was wrong, rechecked in the emulator (`work/hunt10/L3-findings.md`):

| Handler | Type | What it does each tick |
| --- | --- | --- |
| `Behavior_PurpleBeast` | 8 | sets the scale to `g_scaleDouble` (a fixed 2x) and moves by `g_moveYNeg64` (64 units up); no turn. Record 8 wakes 1 tick in 128 in range and is hidden until then, and its touch range equals its wake range, so it is touched as it appears |
| `Behavior_YellowDayBeast` | 109 | sets the scale to `g_scaleHalf` and `moveZ(-10)` |
| `Behavior_RedDayPenguin` | 114 | nothing 1 tick in 3, else rotates by `g_rotY9` (2 times in 3) or `g_rotYNeg9`: it spins on the spot |
| `Behavior_BridgeGeisha` | 110 | sets the scale to `g_scaleTwoFifths` and stops the animation; within 0x800 of the dreamer (`Entity_GroundDistance`, \|dx\| + \|dz\|) state 10: `g_rotY4` for 45 ticks (a half-turn), back to state 0 from tick 501 |
| `Behavior_MinotaurRickshaw` | 21 | two sounds per half animation loop, `moveZ(-0x1E, notify 1)` | Player view of many of them: [Rare sights](../discoveries.md#rare-sights), [characters that answer to CIRCLE](../discoveries.md#-characters-that-answer-to-circle).

## The Grey Man

The Grey Man is entity type 98, built on the only Sym model the game loads.

| Step | Function |
| --- | --- |
| Model | `Sym_ResetGroupsAndLoadSpy` (DreamRunner init) loads `ETC\SYMSPY.MOM` into `g_spyModel`; the loop stops before `ETC\SYMDOG.MOM` |
| Entity | `Sym_InitStage` (each `Place_Setup`) creates `Entity_Create(0x62, ...)` on it, not attached |
| Spawn | `Sym_SpawnOrSpy`: when a slot's day flag blocks it, the stage is not 0, `rand() % 12 == 0` and the day number is even, so only flag-1 slots can hold him |
| Placement | `Sym_SpawnSpy`: detach, then attach at `SceneNode_LocalToWorld(dreamer, (0, -200, 8000))`, facing the dreamer |
| Erase | `Behavior_EraseFlashbacks`: once touched, a Fade flash (colour 7), sleep, `DreamSys_ClearFlashbacks`; each tick it moves 30 units along its own z axis |
| Free | `Sym_FreeSpy` (`Place_Unload`) |
| Leftovers | after his flash, a `Fade` of 164 bytes (`Fade_Create`), a model and 10 watcher nodes, 460 bytes in 13 blocks, stay until the place is unloaded; the menu after the dream holds the same blocks as without him (heap compared in the emulator, `work/hunt10/L2-findings.md` section 3) |

There is one Grey Man per place, so a second roll moves the same one. The stages with a flag-1 slot are 2, 4, 5, 6, 7, 9 and 13; stages 1, 3, 8, 10 and 12 have only flag 0 and stage 11 only flag 2, so he never appears there (stage 11 checked in the emulator with the die forced). Record 98 has mood (-10, -10), past the edge of the graph. Player view: [the Grey Man flips your graph](../discoveries.md#-the-grey-man-flips-your-graph-and-wipes-your-memories), [when he can appear](../discoveries.md#-when-the-grey-man-can-appear), [who can meet him](../discoveries.md#-who-can-meet-the-grey-man-and-where).

## The type 74 room

`Behavior_Type74` runs the room at the end of the Long Hallway (stage 10). On its first tick it repaints the background of the whole place: it reaches the DreamView through DreamSys (`camera.view`) and sets its clear colour to `g_type74ClearColor`. It then draws `rand() % 3`, forced to 0 when the dreamer's z is below 0x262. States 1 and 2 push the dreamer forward (`moveZ` on DreamSys) and post event 10, a link; state 0 walks the dreamer back and gives the controls back. It is a rare handler that moves DreamSys itself. Player view: [the Long Hallway's room](../discoveries.md#-the-long-hallways-room-turns-the-sky-blue-then-pulls-you-out-2-times-in-3).

## Giant and tiny characters

All sizes go through slot 0x48, `SceneNode_SetScale(entity, set, factors)`: three {num, den} s16 pairs turned into the model's scale, written when `set` is 1, added when 0. Handlers pass tables of fractions; for example `Behavior_TinyLips` faces the dreamer, sets `g_scaleTiny` = 1/32 on every axis and moves 30 units along its z axis, each tick. A first-tick draw (`handlerTicks == 0`) gives a random size once per wake (`Behavior_RollWideOrSlide`, `Behavior_Type36`, `Behavior_Type20`).

Four handlers scale the place instead of themselves: they call StageMap slot 0x138 `StageMap_StartTileStretch`, which scales every tile of the loaded chunks in height ([stages and places](stages-and-places.md#the-stagemap)). Player view: [more characters that change size](../discoveries.md#-more-characters-that-change-size), [four characters stretch or flatten the whole place](../discoveries.md#-four-characters-stretch-or-flatten-the-whole-place), [Happy Town's flowers and mushrooms](../discoveries.md#-happy-towns-flowers-and-mushrooms-grow-with-the-day-number).

## Unknowns

- The meaning of the ambience family behind rule 7 is not proven.
- `Model_OnNotify` deletes a model whose borrowed file (class 0x5F03) goes away; that this is how a reassigned map slot ends its characters is likely, not traced. A Kyoto rickshaw followed 33 blocks from its square was detached (`Entity_Detach` ran: its attached word went to 0) in an open street, which fits (`work/hunt10/L3-findings.md` section 4).

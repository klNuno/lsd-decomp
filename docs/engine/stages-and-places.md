# Stages and places

A stage is one of the 14 dream areas, the `STGxx` folders of the disc. A place is the object that runs a stage while the dreamer is in it: it loads the stage's music track and texture set, builds the map around the dreamer, the scenery and the characters, and handles the pause. Every link deletes the place and builds a new one; the dream runner above it lasts the whole dream.

Code: [`src/game/dream_runner.c`](../../src/game/dream_runner.c), [`src/game/place.c`](../../src/game/place.c), [`src/game/stage_map.c`](../../src/game/stage_map.c), [`src/game/map_chunk.c`](../../src/game/map_chunk.c), [`src/game/map_models.c`](../../src/game/map_models.c), [`src/game/map_tile.c`](../../src/game/map_tile.c), [`src/game/stage.c`](../../src/game/stage.c), [`src/game/path_table.c`](../../src/game/path_table.c), [`src/game/scenery.c`](../../src/game/scenery.c), [`src/game/scenery_obj.c`](../../src/game/scenery_obj.c), [`src/game/scenery_part.c`](../../src/game/scenery_part.c).

## The stages

Every per-stage table is indexed 0 to 13. Names are the community's, as [the findings](../discoveries.md) use them; the code has none.

| Stage | Name | Chunks (cols x rows) | Stacked | Ambience | Dream length (s) | Sound spots |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | Bright Moon Cottage | 1 x 5 | yes | family | 240 | 1 |
| 1 | Pit & Temple | 3 x 2 | | family | 180 | 0 |
| 2 | Kyoto | 6 x 6 | | family | 480 | 9 |
| 3 | Natural World | 16 x 16 | | family | 420 | 29 |
| 4 | Happy Town | 6 x 5 | | family | 120 | 5 |
| 5 | Violence District | 5 x 6 | | fixed | 600 | 9 |
| 6 | Moonlight Tower | 1 x 6 | yes | fixed | 60 | 0 |
| 7 | Temple Dojo | 5 x 1 | | fixed | 300 | 0 |
| 8 | Flesh Tunnels | 1 x 3 | | fixed | 240 | 0 |
| 9 | Clockwork Machines | 1 x 2 | | fixed | 300 | 0 |
| 10 | Long Hallway | 3 x 1 | | fixed | 240 | 1 |
| 11 | Sun Faces Heave | 4 x 3 | | fixed | 180 | 1 |
| 12 | Black Space | 4 x 5 | | fixed | 120 | 0 |
| 13 | Monument Park | 2 x 2 | | family | 480 | 1 |

Sources: `g_stageGrids` (`Stage_GetGrid`), `g_stageAmbience` (NULL means "pick from the day's family"), `g_stageTimeLimits`, `g_stageSoundSpotCounts`.

The disc paths of a stage come from the path table ([files and CD](files-and-cd.md)): `g_stageFirstPath[stage]` is the stage's first entry, then `Stage_GetPathBase` hands out three runs of 0x1C-byte paths:

| Offset from the base | Files | Picked by |
| --- | --- | --- |
| +0x00 | `TEXA.TIX` to `TEXD.TIX` | `Stage_PickTexturePath` ([randomness](randomness.md#texture-sets)) |
| +0x70 | `BGA.SEQ` to `BGE.SEQ` | `Music_PickTrack` ([sound and video](sound-and-video.md)) |
| +0xFC | `M000.LBD` on, one per chunk, `row * cols + col` | `Stage_GetChunkPath`, `Stage_GetChunkPathAt` |

## The objects

| Object | File | Size, vtable | Lives |
| --- | --- | --- | --- |
| DreamRunner, a Task | `dream_runner.c` | 0x50, 0x800865C8, class 0x1F230 | one dream |
| Place, a Task | `place.c` | 0x88, 0x80087034, class 0x2F230 | one stage visit |
| StageMap, a RootNode | `stage_map.c` | 0x1E8, 0x800866E8, class 0x114 | one dream |
| MapChunk, a File | `map_chunk.c` | 0x3C, `g_mapChunkVtbl` | one per map slot |
| MapModels | `map_models.c` | 0x34, `g_mapModelsVtbl` | one per map slot |
| MapTile, a SceneNode | `map_tile.c` | 0x3C, 0x80086AA0, class 0x24 | 1 root + 410 per map slot |

Task is the base of DreamRunner and Place ([`src/game/task.c`](../../src/game/task.c)); it derives from Screen, so both run through `Screen_Run` like the menu screens ([boot and objects](boot-and-objects.md)).

`DreamRunner_Init` loads what lasts the whole dream: the effects bank `SND\SE` (the Task's own sound bank), the Grey Man model (`Sym_LoadModels`, [characters](characters.md)), `ETC\ETC.TIM`, `ETC\DREAMER.TMD`, the music bank (`Bgm_New(Music_PickBank(0))`), and in the runner context the DreamView, a Clock and the StageMap.

## The life of a place

1. `DreamRunner_CreateStage` makes the place with `Place_New(sound, music, etcTim, dreamerModel, stage)` and calls its slot 0x44, `Place_Attach`. That registers `Place_GetChunkPath` as the map's chunk loader (StageMap slot 0xC8), keeps DreamSys, watches it and runs the Task inside the runner's loop.
2. `Screen_Run` calls slot 0x4C, `Place_Load`: it picks the music track and starts the texture-set loader (`Tix_Create`), points the view at DreamSys, calls `Scenery_Begin` for the ambience, sets the link period (16), the walking speed (3, or 2 in stage 0), the map bounds (stage 0 only, `g_stage0Bounds`), the view distance (0xA000), the ray height rule for stages 0, 3, 5 and 6 (`SceneNode_SetRayHeightCheck`) and the stage's box margin (`g_stageBoxMargins`), then state 5.
3. On each display event 2, `Place_CheckTextureLoad` checks the loader. Done: the palette fades towards the ambience colour, then `Place_Setup`. Failed: the set is dropped, `Place_Setup` runs anyway and the time limit becomes elapsed + 30 s.
4. `Place_Setup` sets the projection, hands the stage to the spawn code (`Sym_InitStage`), watches the map, gives it the ambience's ambient colour and lights and the stage's grid, and calls `DreamSys_EnterMap`, which puts the dreamer at its place and loads the chunks around it.
5. Once the map has no slot left loading (`pendingSlots == 0`), `Place_Start` runs: `DreamSys_StartPlace`, the map is activated, the view takes the ambience's clear colour, fog distance and fog colour, and the fader fades in (with the day's colour as a veil in flashback mode). The fader's message 5 sets state 0: the place is playable.
6. Each tick (`Place_Tick`) runs `Place_Update`, which runs `Scenery_Tick` at the dreamer's map position, or the pause window while it is open.
7. A transition from DreamSys sets states 4 to 10 ([the dream system](dream-system.md#transitions)); the fade's end notifies the state to the runner, which stops and deletes the place. `Place_Unload` (slot 0x50) runs `Place_Teardown` (closes the pause, locks the controls, `DreamSys_LeaveMap`), frees the Grey Man (`Sym_FreeSpy`) and the scenery (`Scenery_Teardown`), and stops the music.

Place states (`Place.state`):

| State | Meaning |
| --- | --- |
| 5 | loading, or a random link fading out |
| 0 | playing: DreamSys transitions are accepted only now |
| 4 | the day is ending (time up, or a fall after its fade) |
| 6, 7, 8 | fixed link, next flashback, facing link fading out |
| 10 | falling |

The pad handler `Place_OnPad` takes START (pause), and the SELECT held + TRIANGLE pair that notifies 0xD and erases the game ([SELECT + TRIANGLE](../discoveries.md#-select--triangle-in-the-pause-erases-your-game)). The pause (`Place_UpdatePause`) shows the "Pause" label and, on its fourth tick, stops the view, the clock, the music and the sound bank; `Place_ClosePause` resumes them.

## The StageMap

The map keeps the dreamer's chunk and its neighbours loaded and draws the tiles near the camera.

Geometry (`Stage_PlaceToWorld`): a chunk is 0xA000 units square, 20 x 20 tiles of 0x800. Chunk (col, row) sits at `col * 0xA000` from the grid origin, and odd rows are shifted half a chunk, so a chunk has 6 neighbours (`g_chunkNeighborOffsets`, `g_chunkNeighborSteps`). The world position adds the tile (`tileX << 11`), 0x400 to reach the tile centre, and the place's offset. On a stacked stage (0 and 6) the grid is one column of floors, each 0x800 higher than the last (`StageMap_SlotAt`).

Slots: the map has 7 MapSlots, each with a MapChunk, a MapModels, a root MapTile and 410 tile nodes (400 squares, plus 10 for blocks stacked on a square). The flow:

| Step | Function | What it does |
| --- | --- | --- |
| Arrive | `StageMap_SetTarget` | from `DreamSys_EnterMap`: the dreamer's world position, then `StageMap_LoadAround` on its chunk and all 6 neighbours |
| Ask | `StageMap_LoadAround`, `StageMap_AssignChunks` | places each slot's root node and asks the chunk loader (`Place_GetChunkPath`) for each chunk's path; a slot without one is emptied |
| Read | `MapChunk_Load`, `MapChunk_OnLoaded` | reads the chunk file into the slot's 0xB358-byte buffer, then its entity part into a new heap block |
| Build | `StageMap_PollLoads`, `StageMap_BuildTiles` | on each update, a slot whose data arrived gets its tiles (`loaded = 2`); an entity part that arrived sends slot message 7 |
| Follow | `StageMap_Tick`, `StageMap_Follow` | each tick while active: locate the dreamer, load around its chunk on a flat stage, redraw the view, notify 5 when the chunk changed |
| Show | `StageMap_UpdateView` | hides the old view's tiles and shows the tiles within the view distance |
| Leave | `StageMap_Deactivate` | from `DreamSys_LeaveMap`: clears the slots |

The map's own messages: 5 (new chunk) makes DreamSys log the chunk's mood ([moods](dream-system.md#moods-and-the-graph)); 7 (a slot's entities are in) makes the place spawn the characters of that chunk (`Place_SpawnCell`, [characters](characters.md)); 6 (a slot is reassigned) deletes the objects spawned there.

`StageMap_StartTileStretch` and `StageMap_StepTileStretch` scale every tile of the loaded chunks in height for a few characters ([four characters stretch the place](../discoveries.md#-four-characters-stretch-or-flatten-the-whole-place)).

## Chunks, tiles and models

A chunk file `STGxx\Mxxx.LBD` starts with a header (`MapChunkData`, [`include/game/map_chunk.h`](../../include/game/map_chunk.h)):

| Offset | Field |
| --- | --- |
| 0x02 | non-zero when the file has an entity part |
| 0x04 | offset of the model list |
| 0x08 | size of the model list; the TMD follows it |
| 0x10 | offset of the entity part (the square's MML of character models) |
| 0x14 | size of the entity part |

The model list holds a 20 x 20 grid of 12-byte records from offset 8 (`GridRecord`, `src/game/map_models.c`): present, an unread byte, object index in the chunk's TMD, flags, quarter turns, height, and the offset of the next record stacked on the same square. `MapModels_NextModel` places a block at x = col * 0x800 + 0x400, z = row * 0x800 + 0x400, y = height << 11, yaw = quarter turns << 10; `StageMap_BuildTiles` links each into its tile's GsDOBJ2 (`GsLinkObject4`), copies the flags into `MapTile.flags` and chains stacked blocks behind the square's tile. The flags make walls and footstep sounds ([links](links.md#walls-and-tile-flags)).

Moods: each chunk also has one s16 mood in `g_stageChunkMoods[stage]`, row-major, read by `Stage_GetChunkMood` and searched by `Stage_FindChunkByMood` ([where a dream starts](links.md#where-a-dream-starts)).

## Ambience and scenery

`Scenery_Begin` (from `Place_Load`) keeps the map, stage, refs and day number, resets the scenery tick counter and the two sound spot slots, and returns the ambience (`Ambience_Get`):

- a stage with a fixed record in `g_stageAmbience` uses it;
- the others pick a family, `g_ambienceFamilyCycle[(day number + stage) & 15]`, then record `(day number + stage) % count` of that family (`Ambience_PickFamily`).

A 4-byte record gives a mode, a fog depth index (`g_ambienceDepths`: 0x6800 down to 0x800) and two colours of `g_ambienceColors`. The place uses colour A as the clear colour and colour A or B as the fog colour by mode. A depth index of 4 or more also makes a semi-transparent tint box over the view (`Ambience_CreateTint`). Family 0 also sets the band palette and layout of the 18 sky bands (`Ambience_CreateBands`, `Ambience_UpdateBands`, which follow the view's height). The family's parity is spawn rule 7 (`Ambience_IsEvenFamily`, [characters](characters.md)).

`Scenery_Tick` runs each tick. On the first one it makes the tint, the bands and the scenery objects (`Scenery_CreateAll`: a random count of kind 0 objects, kind 1 up to 16 for family 2, one kind 3 for family 0 or one kind 2 for family 2), placed as offsets from the dreamer's position, with the day-7 band rule (`Scenery_RandomizeParamsDay7`). Then it updates bands and objects, cycles the palettes of stages 2 to 5 (`Stage_CyclePalettes`) and runs the sound spots. Scenery objects are `Scenery` ([`include/game/scenery_obj.h`](../../include/game/scenery_obj.h)), Actors with `SceneryPart` sprite parts. Player view: [three quiet rules for the look of a place](../discoveries.md#-three-quiet-rules-for-the-look-of-a-place); the first-tick setup is also the leak of [glitch textures](../discoveries.md#-glitch-textures-a-texture-set-that-failed-to-load).

Sound spots: `g_stageSoundSpots[stage]` lists 8-byte records (a map tile and a type 1 to 14). Each tick, a free slot takes the first spot in range of the dreamer (`SoundSpot_FindInRange`, `SoundSpot_Acquire`), which registers the type's handler (`SoundSpot_Type1` to `SoundSpot_Type14`) on a HandlerNode playing from the effects bank; a spot out of range is dropped (`SoundSpot_IsInRange`, `SoundSpot_Release`). The volume falls with distance (`SoundSpot_CalcFade`). Player view: [places have fixed sound sources](../discoveries.md#-places-have-fixed-sound-sources).

## Unknowns

- `Place.unk4C` keeps the last argument of `Place_Load`; `Screen_Run` passes 0 and nothing reads it in `place.c`.
- Deleting a slot's spawned object ends its characters very likely through `Model_OnNotify`, which deletes a model when the file it borrows (class 0x5F03) sends message 1; that this file is the square's MML was not checked.

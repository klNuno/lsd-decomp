# Boot, the run loop and the object model

When the console starts the game, `main` builds one heap, one scene, one display and one pad, then
hands control to the scene, which never returns. Everything the game runs (logos, videos, the
title, the menu, a dream) is an object of a small C class system written by the original
programmers: a vtable pointer at offset 0, a constructor that allocates from the game heap, and
methods called through the vtable. This page explains that system, then follows the boot down to
the first screen.

## From main to the scene loop

[`main`](../../src/game/main.c) does five things:

1. `SetMem(2)`: 2 MB of RAM.
2. `Heap_Create(0x166C00, 0)`: one pool of about 1.4 MB from Sony's `malloc`, kept in
   `g_mainHeap` and made current with `Heap_SetCurrent`.
3. `Scene_New(&g_sceneSettings)`: the [scene](../../src/game/scene.c), kept in `g_scene`.
4. `Display_New()` and `Pad_New(0, 0)`, passed to the scene's slot 0x44 (`Scene_Start`).
5. The scene's slot 0x4C, `App_Run`, which loops forever.

`Scene_Init` first runs the base init `App_Init` ([app.c](../../src/game/app.c)): `CdInit` once,
`File_SetBackend(0x13)` (the CD back end, see [files and CD](files-and-cd.md)) and a 320 x 240
screen size. Then it sets the disc prefix `CDI\` (`File_SetPathPrefix(File_GetRootDir())`), loads
`ETC\DREAME5.TMD`, builds the one `DreamSys` that holds the whole game state
([dream system](dream-system.md)) and calls slot 0x40, `Scene_SeedRandom`, the only non-zero seed
of the game: a scratchpad word modulo 365 ([randomness](randomness.md),
[the dice of the game](../discoveries.md#-the-dice-of-the-game)).

`App_Start` (reached from `Scene_Start`) makes the display current, calls `GsInitGraph` through
`Display_InitGraph`, resets the SPU (LIBSND `SsInit`), runs `GsInit3D` and builds the `ScreenEnv`
every screen runs with: the display and the pad, with clock, root and view left at 0.

`App_Run` then calls these scene slots:

| Slot | Function | What it does |
| --- | --- | --- |
| 0x50 | `Scene_ShowLogos` | two logo pictures around `ETC\ASMK.STR`; each logo's close resolves half of the path table (`File_ResolvePathTablePart`) |
| 0x54 | `Scene_PlayOpening` | one of seven opening videos (`Cine_PickOpeningPath`) |
| 0x58 | `Scene_RunTitle` | the graph, then the main menu ([menus and save](menus-and-save.md)); returns 2 to start a dream, 0 to go back to the opening |
| 0x60 | `Scene_RunDream` | builds a `DreamRunner`, runs it, then plays the day's cinematic or sets `skipGraph` |
| 0x64 | `Scene_PlayEnding` | `ETC\ENDING.STR`, when `Scene_RunDream` returned 1 ([the ending](../discoveries.md#-the-ending-plays-when-a-year-closes-not-on-day-365)) |

Slot 0x50 runs once; 0x54, 0x58 and 0x60 loop for the rest of the session. `g_sceneSettings`
holds the switches `Scene_*` test: file back end 0x13, `useCdSearch` 0, then videos, logos and
title all 1.

## Objects and classes

Every object starts with the three words of `Object` ([heap.h](../../include/game/heap.h)): the
vtable, a list of the objects it watches and a list of the objects watching it. The root vtable
`g_objectVtbl` has 15 slots:

| Slot | Function | Role |
| --- | --- | --- |
| 0x00 | class word | identifies the class (below) |
| 0x04 | `Object_Delete` | destroy, `Heap_Free`, return NULL |
| 0x08 | `Object_Init` | constructor body |
| 0x0C | `Object_Destroy` | notify watchers with message 1, unwatch all, free the watcher list |
| 0x10 to 0x2C | `Object_Watch` and friends | the two lists |
| 0x30 | `Object_Notify` | call slot 0x38 of every watcher with (watcher, sender, message) |
| 0x38 | `Object_OnNotify` | message 1 from a watched object: unwatch it |

A class is written in one file (see [layout](../layout.md)) as: a `X_New` or `X_Create` that calls
`Heap_Alloc(size)` and then slot 0x08 of `X_GetVtbl()`; an `X_Init` that first calls its base
class's slot 0x08 (for example `Screen_GetVtbl()->init` in `Task_Init`), then stores its own vtable
and calls its reset slot (0x40, `X_Reset`); overrides that call the base slot and add to it; and `X_GetVtbl` last.
The vtables live in the data, not in C: our headers describe them as structs of slots, and each
file that calls another class's vtable declares its own view of the slots it uses.

### Watching is the message bus

There is no event queue. An object that must react to another one watches it (slot 0x10); the
watched object sends a small integer to every watcher through slot 0x30. The display sends 2 once
per frame, the clock sends 2 (tick), 3 (paused) or 4 (stopped), the pad sends one code per button,
a fade sends 5 or 6 when done, a task its state. Watching also builds the scene graph: a
`SceneNode` attached to a parent is watched by it, and the renderer walks those lists
([rendering](rendering.md)). A receiver tells senders apart by the low 4 bits of the sender's
class word: 1 display, 2 pad, 3 file, 4 scene node, 5 clock, 9 model object.

### Class words

The class word is built digit by digit: a subclass keeps its parent's hex digits and adds one or
more above them. From the vtables in the data:

| Root (low digit) | Descendants |
| --- | --- |
| 0 `Object` | 0x10 `CommentObject`, 0x20 `StringList`, 0x30 `Screen`, 0x130 `MenuScreen`, 0x1130 `VideoScreen`, 0x1F130 `Menu`, 0x2F130 `Graph`, 0x230 `Task`, 0x1F230 `DreamRunner`, 0x2F230 `Place`, 0x40 `Stream`, 0x50 `Bgm`, 0x60 `App`, 0x1F60 `Scene`, 0x70 `Movie` |
| 3 `File` | 0x13 CD back end, 0x23 null back end, 0x103 `Tim`, 0x203 `BgMap`, 0x303 `BgCells`, 0x903 `MapChunk`, 0xA03 `SoundBank`, 0xB03 `SeqFile`, 0xC03 `TimPack`, 0xD03 `Tmd`, 0xE03 `MapModels`, 0xF03 `Tix`, 0x4F03 `Tod`, 0x14F03 `TodPack`, 0x5F03 `Mom`, 0x15F03 `Mml` |
| 4 `SceneNode` | 0x14 `RootNode`, 0x114 `StageMap`, 0x24 `MapTile`, 0x34 `Actor`, 0x234 `Model`, 0x1F234 `Entity`, 0x1F34 `DreamSys`, 0xEF34 `Scenery`, 0x44 `SpriteNode`, 0x144 `ScreenSprite`, 0x1144 `Glyph`, 0x11144 `Label`, 0x1F44 `SceneryPart`, 0x54 `Bg`, 0x64 `Box`, 0x164 `Fade` |
| others | 1 `Display`, 2 `Pad`, 5 `Clock`, 6 `FlatLight`, 7 `View`, 0x17 `DreamView`, 9 `ModelObject`, 0xB `Card` |

The inheritance in this table matches the init chains in the code: each `X_Init` calls slot 0x08
of the class whose word its own extends (`Fade_Init` calls `Box_GetVtbl()->init`,
`DreamSys_Init` the `Actor` one). What the digit 0xF means in 0x1F34 or 0x4F03 is not known.
`View_DrawNode` reads the low byte to pick how to draw a node (0x54 background, 0x64 box, 0x44
sprite, any other kind a model; a hidden 0x24 map tile is skipped).

A receiver reads as many digits as it needs. The low 4 bits give the sender type (4 any scene
node, 5 a clock), the low byte the family: `Actor_OnNode` reads the first byte of the sender's
vtable and sends 0x34 (an Actor, so a Model, an Entity, DreamSys or Scenery) to slot 0xDC
(`X_OnActorContact`) and 0x24 (a map tile) to slot 0xE0 (`X_OnTileContact`). Wider masks pick
one class: `& 0xFFF` equal to 0x114 is the stage map (`DreamSys_RouteMapMessage`), `& 0xFFFFF`
equal to 0x1F234 an entity (`DreamSys_OnActorContact`).

## Screens and the frame

A `Screen` ([screen.c](../../src/game/screen.c)) is a modal state machine. Its run slot 0x44,
`Screen_Run`, takes the clock, root and view of the `ScreenEnv` or makes its own (`Clock_Create`,
`RootNode_Create`, `View_New`), watches the display, the pad and the clock, calls begin (slot
0x4C), then sets state 2 (`SCREEN_START`), which calls `Display_StartLoop`. That loop,
`Display_RunFrameLoop` ([display.c](../../src/game/display.c)), only returns when a state 3
(`SCREEN_STOP`) clears `Display.running`. So "run a screen" is a blocking call that returns the
screen's result, and `Scene_RunScreen` is just create, run, delete.

One frame, as the code orders it:

1. `VSync(vsyncMode)` (mode 3 by default), then the display's frame callback, which the CD code
   may hook (`File_OnVSync`).
2. The display notifies its watchers with 2. `View_OnDisplay` presents the ordering table built
   the frame before (`View_Present`). `Screen_OnDisplay` steps the clock and calls the pad's read
   and send slots.
3. `Clock_Step` adds a tick and notifies its watchers: the screen counts `ticks` and runs its own
   state logic, the view builds the next ordering table (`View_OnClock`, then `View_Render`).
4. `Pad_SendEvents` sends one code per button to the screen's `onPad` (slot 0x58).

The order inside step 2 comes from `List_Push`, which adds watchers at the head: the view watches
the display after the screen, so it is notified first. `Task` ([task.c](../../src/game/task.c))
adds a result, a timeout in ticks (20 per second of argument) and an optional sound bank to
`Screen`; `DreamRunner` and `Place` derive from it ([dream system](dream-system.md),
[stages and places](stages-and-places.md)).

## The heap

[heap.c](../../src/game/heap.c) is a first-fit allocator over the one pool. Each block starts with
a header word: the size (header included) in the low 28 bits, `HEAP_FREE` (bit 30) when free,
`HEAP_PREV_FREE` (bit 31) when the block below is free. A free block's last word points back to
its header so `Heap_Free` can merge with the block below. Free blocks form a doubly linked list.

- `Heap_Alloc(size)` rounds up to a word, at least 12 bytes, adds the header, and takes the first
  free block large enough from the head of the list. A block with less than 16 bytes to spare is
  handed out whole; otherwise its low end is used and the rest stays on the list. No block large
  enough returns NULL.
- `Heap_Free(data)` merges with free neighbours on both sides and pushes the result at the head.
- Both take a second, K&R parameter: the heap to use when `g_currentHeap` is NULL. Callers pass
  only the first argument, so this fallback only matters before `Heap_SetCurrent`; `Heap_Create`
  relies on it when it initializes the new pool with `g_currentHeap` still NULL.
- `Heap_SetBusy` raises `g_heapBusy` while either function runs. `File_OnVSync` checks
  `Heap_IsBusy` and does nothing that frame when it is set, because the CD request code
  allocates from a VSync callback ([files and CD](files-and-cd.md)).

Nothing resets the pool. Constructors return NULL when the heap is full. One failure is visible in the game: a texture set that cannot get its buffers
([glitch textures](../discoveries.md#-glitch-textures-a-texture-set-that-failed-to-load)).

`List_Push`, `List_Remove`, `List_FreeAll` and `List_Next` in the same file implement the watcher
lists: 8-byte nodes, each a 16-byte heap block, and a watch adds one node to each of the two
objects.

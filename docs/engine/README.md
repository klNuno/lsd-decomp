# Engine docs

How LSD: Dream Emulator works, for a programmer who opens the code for the first time. Each page
explains one system from the code: its classes and vtables, the data it reads, and the flow of a
frame or an event, with links to the files and functions. For what a player sees, follow the links
to [the findings](../discoveries.md); for the names, see [the glossary](../naming.md); for where
each file sits in the executable, see [the layout](../layout.md).

## Pages

Machinery:

- [Boot, the run loop and the object model](boot-and-objects.md): `main`, the scene loop, the
  class system (vtables, class words, watching as messaging), screens and one frame, the heap.
- [Files and the CD](files-and-cd.md): the file class and its back ends, the path table, the
  synchronous and queued CD modes, and the TIM, TIX, TMD, TOD, MOM, MML and LBD formats.
- [Rendering](rendering.md): display and view, ordering tables, the scene walk,
  `Render_SortModel`, clipping, fog through palette rows, sprites, boxes and fades.
- [Sound and video](sound-and-video.md): VAB sound banks, the sequencer timer, the music per
  place, and the MDEC movie player with its CD stream.
- [Menus, the pad and the memory card](menus-and-save.md): the title chain, pad codes, the menu
  screen class, the main menu, the card dialogs, the comment keyboard and the save block.

The dream:

- [The dream system](dream-system.md): `DreamSys`, the day and the dream timer, moods and the
  graph, flashbacks, the end of a dream and of a year.
- [Links](links.md): walls and tile flags, falls, the link tables, how the next place is chosen.
- [Stages and places](stages-and-places.md): stages, the place object, the `StageMap`, chunks,
  tiles and models, scenery, ambience and sound spots.
- [Characters](characters.md): spawn tables, the entity class and its behaviours, the Grey Man,
  the type 74 room, giant and tiny characters.
- [Randomness](randomness.md): the one random generator, what draws from it, texture sets and
  special days, and what only looks random.

## Where to start reading the code

Follow the calls from the entry point; each step names the function to open next.

1. [`main`](../../src/game/main.c): makes the heap (`Heap_Create`), the scene (`Scene_New`), the
   display and the pad, then calls the scene's slots 0x44 and 0x4C.
2. [`Scene_Init`](../../src/game/scene.c) and [`App_Init`](../../src/game/app.c): the CD back end,
   the disc prefix, the one `DreamSys`, the random seed. Read
   [heap.c](../../src/game/heap.c) and [heap.h](../../include/game/heap.h) here: every class
   starts with the `Object` of that file.
3. `App_Run` ([app.c](../../src/game/app.c)): the loop that calls the scene's slots: logos,
   opening, title, dream, ending (`Scene_ShowLogos` to `Scene_PlayEnding` in scene.c).
4. [`Screen_Run`](../../src/game/screen.c) and [`Display_RunFrameLoop`](../../src/game/display.c):
   how every screen blocks in the frame loop until its state is 3, and what one frame sends to
   whom ([clock.c](../../src/game/clock.c), [pad.c](../../src/game/pad.c),
   [view.c](../../src/game/view.c)).
5. The title side: `Scene_RunTitle`, then [`MenuScreen`](../../src/game/menu_screen.c) and the main
   menu [`Menu`](../../src/game/menu.c), with [card.c](../../src/game/card.c) for SAVE and LOAD.
6. The dream side: `Scene_RunDream` makes a [`DreamRunner`](../../src/game/dream_runner.c), a
   `Task` ([task.c](../../src/game/task.c)) whose update starts the day
   (`DreamSys_StartDay` in [dream_sys.c](../../src/game/dream_sys.c)) and builds a
   [`Place`](../../src/game/place.c) per stage; the place loads the map
   ([stage_map.c](../../src/game/stage_map.c)), the textures ([tix.c](../../src/game/tix.c)),
   the music ([bgm.c](../../src/game/bgm.c)), the scenery ([scenery.c](../../src/game/scenery.c))
   and the characters ([sym.c](../../src/game/sym.c), [entity.c](../../src/game/entity.c)).
7. Under all of it: [file_cd.c](../../src/game/file_cd.c) for loading,
   [scene_draw.c](../../src/game/scene_draw.c) and [render.c](../../src/game/render.c) for
   drawing.

Three habits of the code help when reading any file:

- A class is one file that ends with `X_GetVtbl`. Its constructor `X_New` or `X_Create` allocates
  and calls slot 0x08; each override calls the base class's slot first. Slots are named in the
  vtable struct of the class's header; calls go through `obj->vtbl->slot(obj, ...)`.
- Objects talk by watching each other: `Object_Notify` calls slot 0x38 of every watcher with a
  small message, and the receiver checks the low 4 bits of the sender's class word
  ([class words](boot-and-objects.md#class-words)).
- Files load through queued requests while a dream runs: a loader's work happens in its
  `onLoaded` slot (0x64), called once per finished request
  ([the CD back end](files-and-cd.md#the-cd-back-end)).

# Naming guide

How the systems behind these names work is in [the engine docs](engine/README.md).

A wrong name costs more than no name. Rename only with evidence, and write the evidence down.

## Default names

- Functions: `func_8001XXXX` (splat's). Data: `D_8008XXXX`. Jump tables: `jtbl_8001XXXX`. Struct fields: `unk_XX` with the hex offset.
- Sony library functions keep their PSY-Q names (`InitHeap`, `CdInit`, `ResetGraph`) from the signature match, in `config/symbol_addrs.psyq.txt`.
- Names taken from FirecatFG's lsddecomp live in their own file, `config/symbol_addrs.lsddecomp.txt`, and stay there until our own evidence confirms them.

## Our names

- Format: `Subsystem_VerbNoun` for functions (`Dream_AdvanceDay`, `Link_PickTarget`), `g_` plus a noun for globals (`g_dayCount`), `PascalCase` for struct types (`DreamState`).
- Subsystems in use: see the glossary. Add a subsystem to the glossary before using it.
- A field keeps its offset in its name (`unk_14`) until two independent uses agree on its meaning.
- Every rename goes in `config/symbol_addrs.txt` with a comment pointing to its row in `docs/discoveries.md`.

## Readable C

Matching is half the job; the other half is C a person can read. Every change below must keep the bytes: `tools/unit_check.sh src/game/FILE.c` compares one file with the reference objects, `make check` judges the whole executable. The files are named by the class or subsystem they hold; [layout.md](layout.md) gives their boundaries and the declaration rules a file must keep.

- Parameters and locals get meaningful lowerCamelCase names (`entity`, `record`, `dayNumber`, `limit`); loop counters stay `i`, `j`. The object a method works on is named after its type (`dreamSys`, `entity`, `heap`). m2c names (`arg0`, `temp_s0`, `var_v0`, `sp10`) go away once the meaning is known; when it is not, keep them.
- Shared objects have one struct in `include/game/*.h` (`DreamSys`, `Entity`, `EntityRecord`, `Heap`), used by every unit instead of per-function `Unk_8005XXXX` copies, as long as each field a function touches has the same offset and the same type. A field keeps `unk_XX` until its meaning has evidence.
- Functions and globals are renamed only through `tools/rename.py NAMES.tsv` (OLD, NEW, evidence per line), which rewrites src/, include/, docs/ and `config/symbol_addrs.txt`; then `make split && make check`.
- Never change statements, their order, expression types or casts while renaming: those change the code the compiler emits.

## Prototypes

A function's prototype lives in the header of the file that defines it, `include/game/<file>.h`, written like the definition with its parameter names; callers include that header ([layout.md](layout.md), rule 6). Its non-gp globals that other files read are declared there with `extern`; gp globals never are (rule 1). Sony functions are declared in `include/psyq/<lib>.h` (libapi, libetc, libgpu, libgte, libgs, libcd, libspu, libsnd, libpress, libcard, libc), one header per PSY-Q library, holding only what the game calls in the form its calls need; a struct argument the callers read through different views of their own is `void *`. The exceptions keep the bytes, each with a comment saying why:

- Unprototyped in the header (`s32 Cine_PickOpeningPath();`) when a caller passes another number of arguments than the definition takes, because the call in the executable passes them: `Heap_Create`, `SceneNode_ProbeHeight`, `SceneNode_LocalToWorld`, `ModelObject_GetBox`, `File_LoadWhole`, `Music_GetEffectsBank`, `Music_PickTrack`, `Stage_GetChunkPath`, `Cine_PickOpeningPath`, `Cine_GetEndingPath`, and `Cine_GetPath` (scene.c passes the `{category, variant}` pair as one s32). `Heap_Alloc`, `Heap_Free` and `Rand_SeedAndNext` are K&R definitions on purpose, so their header form has no parameters either.
- `X_GetVtbl` of Actor, RootNode, Screen, SceneNode, SpriteNode, Task and View stays out of the headers: a subclass calls its base class's methods through its own view of the vtable struct (other slot names or types), so each file that calls it declares it with its own return type, one comment line above. Merging those views into one vtable struct per class removes the exception.
- `Cine_GetVideoFrames` is defined as s16 in path_table.c; scene.c declares it as s32 because its code takes the word as is, and an s16 prototype adds a sign extension.

## Evidence that counts

- The function's behaviour read from matched C, with the call sites that use it.
- A RAM check in the emulator (`tools/emu/run.sh`) that shows the value changing the way the name says.
- A string or table in the executable that the code reads.

Not evidence on its own: a name from a wiki, a guess from the address, a similar-looking function in another game.

## Glossary

| Term | Meaning | Source |
| --- | --- | --- |
| Day | One dream, from falling asleep to waking; the counter at +0x180 wraps from 364 to 0 and increments the year | code: `DreamSys_AdvanceDay` @0x8005A304, checked in RAM 2026-10-15 |
| Zone | One of the dream areas (Happy Town, Violence District, Moonlight Tower and others) | community knowledge |
| Link | Touching something that moves you to another place: dynamic (random main zone) or static (per-zone table) | community knowledge (lsddecomp, compu-lsd) |
| Graph | The mood chart shown after each day, two axes | community knowledge |
| Flashback | A replay of saved moments: up to 10 entries of 0x24 bytes at DreamSys +0x470, 20 s each; the menu item needs an unlock score above 9,999,999 and one entry | code: discoveries 2026-10-15 (`Menu_UpdateFlashbackItem` @0x8004D678, `DreamSys_AddFlashback` @0x8005B74C) |
| Grey Man | The figure who erases flashbacks when met | community knowledge (compu-lsd, fandom) |
| DreamSys | The game-state object at `0x80091530` (vtable `0x80087BDC`): day, year, scores, graph, timer, current stage | code: discoveries 2026-10-15, checked in RAM |
| Day number | Day + 1 as returned by `DreamSys_GetDayNumber` @0x8005A2E4; parity and special-day checks use it, the stored day at +0x180 starts at 0 | code: discoveries 2026-10-15 |
| Stage | One of the 14 `STGxx` folders, indexed 0 to 13 in every per-stage table (time limits, chunk moods, spawn points, paths) | code: discoveries 2026-10-15 |
| Spawn | A stage's arrival point: {chunk, tile, adjustment index}, 6 bytes, tables at 0x800885B8 | code: discoveries 2026-10-15 |
| Mood | A graph point, two s8 axes in -9..9; a chunk's mood is one s16 in its stage table | code: discoveries 2026-10-15 |
| Unlock score | DreamSys +0x184 = navigation score (+0x188) + instance score (+0x18C), recomputed at each normal day end | code: discoveries 2026-10-15 (`DreamSys_CalcUnlockScore` @0x8005B6E0, `Nav_CalcScore` @0x8005BA7C) |
| Special day | One of the 42 day numbers of `g_specialDays` @0x80088CCC; shows `SPDAYnnA/B.STR` (variants 0, 1) or `SPDAYnnC-F.TIM` (2 to 5) instead of a dream | code: discoveries 2026-10-15, checked in game |
| Entity event | A message from an entity to DreamSys (`DreamSys_OnEntityEvent` @0x8005B03C): 9 touch, 10 link, 11 end with video, 12 end | code: discoveries 2026-10-15 |
| Sym | Entities loaded from `ETC\SYM*.MOM`; only `SYMSPY.MOM` is loaded | code: discoveries 2026-10-15 |
| Nav | Navigation flags and score: 30 flags at DreamSys +0x5E0 and the dynamic link count at +0x600 that make the navigation score | code: discoveries 2026-10-15 (`Nav_CalcScore` @0x8005BA7C) |
| Cine | Special-day and entity-event cinematics: the {category, variant} to path and video id tables | code: discoveries 2026-10-15 (`Cine_GetPath` @0x80049334) |
| Scene | The scene class that `Scene_Init` builds with `ETC\DREAME5.TMD` and a new DreamSys, and the code of its file `src/game/scene.c` (random seed, special-day cinematic) | code: discoveries 2026-10-15 (`Scene_PlayCinematic` @0x8002677C) |
| Menu | The main menu object, the screen with the day number and the Flashback item, and its items | code: discoveries 2026-10-15 (`Menu_UpdateFlashbackItem` @0x8004D678) |
| SaveMenu | The memory card menu object: card file name, title with the day number, save and load of the 0x700-byte block | code: discoveries 2026-10-15 (`SaveMenu_Save` @0x8004E0E4) |
| Rand | The game's wrapper around PSY-Q `srand` and `rand` | code: discoveries 2026-10-15 (`Rand_SeedAndNext` @0x80048CFC) |
| Music | The dream's sound bank (one of 7, `g_musicBanks`) and track (one of 5 per stage) and the unused override that would pin them | code: discoveries 2026-10-15 (`Music_PickBank` @0x80048D74, `Music_PickTrack` @0x80048F84, `Music_SetOverride` @0x80048D28) |
| Heap | The game's one memory pool (0x166C00 bytes, made at boot), first-fit allocator and free | code: work/hunt6/F-findings.md, `include/game/heap.h` |
| List | A singly linked list of values, one 8-byte node per value | code: `include/game/heap.h` (`ListNode`) |
| Object | The root class (vtable 0x8006B58C) every game object derives from: init, destroy, and lists of the objects it watches and of its watchers, told with message 1 when it goes away | code: `include/game/heap.h` (`Object`, `ObjectVtbl`) |
| Render | Model drawing: TMD polygons sorted into the ordering table, projected, clipped and turned into GPU packets | code: src/game/render.c |
| Entity | A character or object of the dream (0x108 bytes, vtable 0x80089AD4), created from a spawn group with its 16-byte record at 0x80089EA4 | code: `include/game/entity.h`, discoveries "The character record" |
| Screen | The base screen class (vtable 0x8006E878): a state machine run by the display loop, with clock, pad and view | code: src/game/screen.c, `include/game/screen.h` |
| MenuScreen | A Screen with sound bank, picture, fades, timeout and an item menu (vtable 0x8006E730): logos, special-day pictures, the main menu | code: `include/game/menu_screen.h` |
| VideoScreen | The MenuScreen that plays one STR video (vtable 0x8006E5F8) | code: `include/game/video_screen.h` |
| View | The 3D view (vtable 0x8006E8E4): GsRVIEW2, double ordering tables, fog and light mode | code: `include/game/view.h` |
| Task | A class with a tick count, a timeout and a result (vtable 0x80086668) that DreamRunner and Place derive from | code: `include/game/task.h` |
| DreamRunner | The object built for each dream (vtable 0x800865C8): loads the dreamer model and the music bank, creates the place, rebuilds it after a link | code: `include/game/dream_runner.h` |
| StageMap | The map that keeps the 7 chunks around the dreamer loaded and shows the tiles in view (vtable 0x800866E8) | code: `include/game/stage_map.h` |
| MapTile | One tile model of a chunk (vtable 0x80086AA0), a GsDOBJ2 at +0x10 | code: `include/game/map_tile.h` |
| Place | The object that runs one stage while the dreamer is in it (vtable 0x80087034): load, pad handler, pause, fades | code: `include/game/place.h` |
| Actor | The base class of scenery objects and their parts (vtable 0x800878D4, 0x58 bytes) | code: src/game/actor.c |
| Scenery | The objects a place builds around the dreamer at its first tick, and their update | code: `include/game/scenery.h`, work/hunt6/F-findings.md |
| Ambience | The fog and sky record of a place, picked per stage or from the day's family | code: src/game/scenery.c |
| Model | The model base class every entity derives from (vtable 0x8008A6C4, 0x98 bytes): model file, parts, animation, per-tick function, sound bank | code: src/game/model.c |
| ModelObject | One model instance of a TMD object, an Object subclass of 0x24 bytes, with its box and ray test | code: src/game/model_object.c |
| ModelBox | The min and max corners of a model object, and the 8-corner box list of the ray tests | code: src/game/model_object.c |
| SceneNode | An object of the node classes of src/game/scene_node.c: parent at +0xC, GsCOORDINATE2 at +0x14 | code: src/game/scene_node.c |
| File | The CD file object: locate, load, seek and the read queue (0x2C bytes) | code: src/game/file_cd.c |
| Tix | A TEXx.TIX texture set file and its palette fades | code: `include/game/tix.h` |
| TimPack | One part of a TIX, a list of TIM images | code: `include/game/tim_pack.h` |
| Tmd | A TMD model file and its model objects | code: `include/game/tmd.h` |
| Tod | A TOD animation file | code: `include/game/tod.h` |
| TodPack | A list of TOD files, the motions of a MOM | code: `include/game/tod_pack.h` |
| Mom | A MOM model file: a TMD and a TodPack | code: `include/game/mom.h` |
| Mml | The list of MOM models of a map square | code: `include/game/mml.h` |
| Bg | A PSY-Q GsBG background object | code: `include/game/bg.h` |
| BgMap | The GsMAP of a Bg | code: `include/game/bg_map.h` |
| BgCells | The GsCELL table of a BgMap | code: `include/game/bg_cells.h` |
| Movie | The MDEC movie player | code: `include/game/movie.h` |
| Card | The memory card object (vtable 0x80086DC4, 0x84 bytes): card events, bu00 and bu10 file access, the save format, the save and load dialogs | code: `include/game/card.h` |
| Sound | A model's sound bank (0x64 bytes): loads a VAB, builds its tone tables, starts and stops voices | code: src/game/sound_bank.c |
| Fade | A Box that fades its color (vtable 0x8006E99C): the 320x240 layer of the view, the place fader, the Grey Man white flash; RgbFade fades one RGB triple | code: src/game/fade.c |
| RgbFade | See Fade | code: src/game/fade.c |
| Rgb | Color byte helpers | code: src/game/box.c |
| Pos | Position pair helpers: set, save, restore | code: src/game/fade.c |
| Text | Shift-JIS fullwidth text: encode, decode, format a number | code: src/game/text.c |
| CommentObject | The on-screen keyboard object (0x4C bytes, vtable 0x80086ED0): text buffer, alphabet, caret | code: src/game/comment_object.c |
| StringList | A list of strings with their lengths and a maximum length | code: src/game/string_list.c |
| App | The base class of Scene (vtable 0x8006E4F0): CD init, 320x240 screen, display and pad, the main loop | code: src/game/app.c |
| Display | The display object (vtable 0x8006C070): frame loop and VRAM transfers | code: src/game/display.c |
| Bgm | The music player ("WBgm" in its error message): a sound bank and a SEQ file played by libsnd | code: src/game/bgm.c |
| Tim | A TIM image object (vtable 0x8006E558); one helper rotates a VRAM area, the palette cycling of stages 2 to 5 | code: src/game/tim.c |
| Pad | The controller object | code: src/game/pad.c |
| Stream | The CD stream class (vtable 0x800817E0) that feeds the movie player | code: src/game/stream.c |
| MapChunk | One stage chunk file (STGxx\Mxxx.LBD) and its entity part, plus the path table accessors (stage files, music, videos) | code: src/game/map_chunk.c, src/game/path_table.c |
| SpriteNode | A scene node that draws a GsSPRITE cut from a TIM (vtable 0x8006EE1C) | code: src/game/sprite_node.c |
| ScreenSprite | A SpriteNode placed by a 2D position and a pivot (vtable 0x8006ED4C) | code: src/game/screen_sprite.c |
| Glyph | A ScreenSprite that shows one 8x8 character of a font (vtable 0x8006EC74) | code: src/game/glyph.c |
| SeqFile | A SEQ music file loaded asynchronously and opened with SsSeqOpen (vtable 0x8006EED8) | code: src/game/seq_file.c |
| Clock | A tick counter that tells its watchers 2, 3 when paused, 4 when stopped (vtable 0x8006EF50) | code: src/game/clock.c |
| RootNode | The root scene node with 3 lights and the ambient color, base of StageMap (vtable 0x8006EFAC) | code: src/game/root_node.c |
| FlatLight | The flat light helpers of RootNode | code: src/game/flat_light.c |
| Box | A filled 2D rectangle widget, a GsBOXF at +0x58 (vtable 0x8006EAC0) | code: src/game/box.c |
| Label | A row of glyphs that shows a text (vtable 0x8006EB90) | code: src/game/label.c |
| Spu | SPU hardware init and reset | code: src/game/spu.c |
| Seq | The root counter timer that drives the sequencer | code: src/game/seq_timer.c |
| Fraction | A {numerator, denominator} pair used for scales | code: src/game/scene_node.c |
| Bits | Bit flag helpers of the scene nodes (GsDOBJ2 attribute bits) | code: src/game/scene_node.c |
| DreamView | The dream camera, a View subclass of 0xDC bytes (vtable 0x800869D8) | code: src/game/dream_view.c |
| MapModels | The model list of one map chunk (vtable 0x8006D940) | code: src/game/map_models.c |
| HandlerNode | The node that runs a behaviour handler every tick and plays its voices | code: `include/game/handler_node.h`, src/game/handler_node.c |
| SoundSpot | A fixed ambient sound source of a place, played from the SND\SE bank; at most two play at once, quieter with distance | code: src/game/scenery.c |
| SceneryPart | A sprite part of the scenery (vtable 0x800879C4) | code: src/game/scenery_part.c |
| Behavior | A 16-byte entity behaviour record {handler, parameters} and its handler | code: discoveries 2026-10-15 (`Behavior_EraseFlashbacks` @0x80064618) |

Rows sourced to community knowledge are working terms, not verified facts; rows sourced to code cite their discoveries entry.

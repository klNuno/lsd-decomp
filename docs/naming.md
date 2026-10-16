# Naming guide

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

Matching is half the job; the other half is C a person can read. Every change below must keep the bytes: `tools/unit_check.sh src/game/UNIT.c` compares one unit with the reference objects, `make check` judges the whole executable.

- Parameters and locals get meaningful lowerCamelCase names (`entity`, `record`, `dayNumber`, `limit`); loop counters stay `i`, `j`. The object a method works on is named after its type (`dreamSys`, `entity`, `heap`). m2c names (`arg0`, `temp_s0`, `var_v0`, `sp10`) go away once the meaning is known; when it is not, keep them.
- Shared objects have one struct in `include/game/*.h` (`DreamSys`, `Entity`, `EntityRecord`, `Heap`), used by every unit instead of per-function `Unk_8005XXXX` copies, as long as each field a function touches has the same offset and the same type. A field keeps `unk_XX` until its meaning has evidence.
- Functions and globals are renamed only through `tools/rename.py NAMES.tsv` (OLD, NEW, evidence per line), which rewrites src/, include/, docs/ and `config/symbol_addrs.txt`; then `make split && make check`.
- Never change statements, their order, expression types or casts while renaming: those change the code the compiler emits.

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
| Scene | The scene class that `func_80025FDC` builds with `ETC\DREAME5.TMD` and a new DreamSys, and the code of its unit `game/80025F7C` (random seed, special-day cinematic) | code: discoveries 2026-10-15 (`Scene_PlayCinematic` @0x8002677C) |
| Menu | The main menu object, the screen with the day number and the Flashback item, and its items | code: discoveries 2026-10-15 (`Menu_UpdateFlashbackItem` @0x8004D678) |
| SaveMenu | The memory card menu object: card file name, title with the day number, save and load of the 0x700-byte block | code: discoveries 2026-10-15 (`SaveMenu_Save` @0x8004E0E4) |
| Rand | The game's wrapper around PSY-Q `srand` and `rand` | code: discoveries 2026-10-15 (`Rand_SeedAndNext` @0x80048CFC) |
| Music | The dream's sound bank (one of 7, `D_800819CC`) and track (one of 5 per stage) and the unused override that would pin them | code: discoveries 2026-10-15 (`Music_PickBank` @0x80048D74, `Music_PickTrack` @0x80048F84, `Music_SetOverride` @0x80048D28) |
| Heap | The game's one memory pool (0x166C00 bytes, made at boot), first-fit allocator and free | code: work/hunt6/F-findings.md, `include/game/heap.h` |
| List | A singly linked list of values, one 8-byte node per value | code: `include/game/heap.h` (`ListNode`) |
| Object | The root class (vtable 0x8006B58C) every game object derives from: init, destroy, and lists of the objects it watches and of its watchers, told with message 1 when it goes away | code: `include/game/heap.h` (`Object`, `ObjectVtbl`) |
| Render | Model drawing: TMD polygons sorted into the ordering table, projected, clipped and turned into GPU packets | code: src/game/80017A20.c second half |
| Entity | A character or object of the dream (0x108 bytes, vtable 0x80089AD4), created from a spawn group with its 16-byte record at 0x80089EA4 | code: `include/game/entity.h`, discoveries "The character record" |
| Behavior | A 16-byte entity behaviour record {handler, parameters} and its handler | code: discoveries 2026-10-15 (`Behavior_EraseFlashbacks` @0x80064618) |

Rows sourced to community knowledge are working terms, not verified facts; rows sourced to code cite their discoveries entry.

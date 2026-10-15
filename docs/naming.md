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

## Evidence that counts

- The function's behaviour read from matched C, with the call sites that use it.
- A RAM check in the emulator (`tools/emu/run.sh`) that shows the value changing the way the name says.
- A string or table in the executable that the code reads.

Not evidence on its own: a name from a wiki, a guess from the address, a similar-looking function in another game.

## Glossary

| Term | Meaning | Source |
| --- | --- | --- |
| Day | One dream, from falling asleep to waking; the counter at +0x180 wraps from 364 to 0 and increments the year | code: `func_8005A304`, checked in RAM 2026-10-15 |
| Zone | One of the dream areas (Happy Town, Violence District, Moonlight Tower and others) | community knowledge |
| Link | Touching something that moves you to another place: dynamic (random main zone) or static (per-zone table) | community knowledge (lsddecomp, compu-lsd) |
| Graph | The mood chart shown after each day, two axes | community knowledge |
| Flashback | A replay of saved moments: up to 10 entries of 0x24 bytes at DreamSys +0x470, 20 s each; the menu item needs an unlock score above 9,999,999 and one entry | code: discoveries 2026-10-15 (`func_8004D678`, `func_8005B74C`) |
| Grey Man | The figure who erases flashbacks when met | community knowledge (compu-lsd, fandom) |
| DreamSys | The game-state object at `0x80091530` (vtable `0x80087BDC`): day, year, scores, graph, timer, current stage | code: discoveries 2026-10-15, checked in RAM |
| Day number | Day + 1 as returned by `func_8005A2E4`; parity and special-day checks use it, the stored day at +0x180 starts at 0 | code: discoveries 2026-10-15 |
| Stage | One of the 14 `STGxx` folders, indexed 0 to 13 in every per-stage table (time limits, chunk moods, spawn points, paths) | code: discoveries 2026-10-15 |
| Spawn | A stage's arrival point: {chunk, tile, adjustment index}, 6 bytes, tables at 0x800885B8 | code: discoveries 2026-10-15 |
| Mood | A graph point, two s8 axes in -9..9; a chunk's mood is one s16 in its stage table | code: discoveries 2026-10-15 |
| Unlock score | DreamSys +0x184 = navigation score (+0x188) + instance score (+0x18C), recomputed at each normal day end | code: discoveries 2026-10-15 (`func_8005B6E0`, `func_8005BA7C`) |
| Special day | One of the 42 day numbers of `D_80088CCC`; shows `SPDAYnnA/B.STR` (variants 0, 1) or `SPDAYnnC-F.TIM` (2 to 5) instead of a dream | code: discoveries 2026-10-15, checked in game |
| Entity event | A message from an entity to DreamSys (`func_8005B03C`): 9 touch, 10 link, 11 end with video, 12 end | code: discoveries 2026-10-15 |
| Sym | Entities loaded from `ETC\SYM*.MOM`; only `SYMSPY.MOM` is loaded | code: discoveries 2026-10-15 |

Rows sourced to community knowledge are working terms, not verified facts; rows sourced to code cite their discoveries entry.

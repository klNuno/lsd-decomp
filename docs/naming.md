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
| Day | One dream, from falling asleep to waking; the counter wraps after day 365 | community knowledge (lsddecomp) |
| Zone | One of the dream areas (Happy Town, Violence District, Moonlight Tower and others) | community knowledge |
| Link | Touching something that moves you to another place: dynamic (random main zone) or static (per-zone table) | community knowledge (lsddecomp, compu-lsd) |
| Graph | The mood chart shown after each day, two axes | community knowledge |
| Flashback | A replay of an earlier day, unlocked by a score | community knowledge (lsddecomp) |
| Grey Man | The figure who erases flashbacks when met | community knowledge (compu-lsd, fandom) |

Every row above is a working term from `docs/community-knowledge.md`, not a verified fact; the code decides.

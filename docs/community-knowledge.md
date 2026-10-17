# What the community already knows

Starting point, from the planning notes of 2026-10-14. "Code" means read in code or data by an earlier project; "observed" means players only. Nothing here is trusted until our own code reading confirms it.

## Game rules

| Topic | Known | Status | Source |
|---|---|---|---|
| Dream graph | End point is the mean of a "zones crossed" axis and an "entities touched" axis; each axis is a mean of values plus a last-event term; past plus or minus 9 a value wraps to the other side | code | lsddecomp, compu-lsd Graph |
| Next dream start | Each chunk of each zone has a mood coordinate; the next dream starts on the chunk matching yesterday's point, else in a random zone | code | lsddecomp |
| Link colour | Each axis falls in one of 3 bands; a 3x3 table gives one of 8 colours. A second table, `SPECIAL_COLORS`, has no known role | code | lsddecomp |
| Dream length | Set by the starting zone, from 60 s (Moonlight Tower) to 600 s (Violence District); linking during the end fade resets the timer | code | lsddecomp, DreamTimer.md |
| Forced endings | The lions, the Ferris wheel and the Kyoto old ladies max the timer, which ends the dream. Our check: the Ferris wheel and the Kyoto old woman end the dream in the emulator, and so does a fall off an edge ([CIRCLE](discoveries.md#-characters-that-answer-to-circle), [stretch](discoveries.md#-four-characters-stretch-or-flatten-the-whole-place), [falls](discoveries.md#-falling-off-an-edge-walls-and-the-cottages-walking-squares)); a savannah lion ends it when you walk into it (code), when its charge reaches you (emulator, temper drawn by the game) or, 1 time in 6, walks up to you and ends it (emulator, temper forced) ([the lions](discoveries.md#-the-natural-world-lions-a-random-temper-and-a-cyan-day-pair-that-leads-to-temple-dojo)) | code | lsddecomp, DreamTimer.md, fandom Falling |
| Links | Dynamic link: one of the 6 main zones at random, never the current one. Static link: per-zone tables (chunk, tile) to (zone, spawn point) | code | lsddecomp, compu-lsd Linking |
| Special days | 42 days in a table show a video or a diary text instead of a dream; players see 2 variants per day, the code seems to draw from 6 | code | lsddecomp, fandom Video Dreams |
| After day 365 | The day counter wraps to 0 and a hidden year counter increments; players see an ending video on day 365 | code | lsddecomp, fandom Clips |
| Flashback | Unlocked by a score (30 navigation challenges worth 1 million each, a penalty per dynamic link), not by day count; at most 10 kept; players see it around days 10 to 20 | code | lsddecomp, fandom Flashback |
| Grey Man | Appears on even days (type B), erases flashbacks, sends the graph to the opposite side; never seen at Sun Faces Heave or in the Long Hallway. Wikis disagree on whether he chases the player. Our check: he is placed about four tiles ahead of the player, facing the player, and the same Grey Man is moved again at each new spawn ([when he appears](discoveries.md#-when-the-grey-man-can-appear)); never at Sun Faces Heave is right: it has no spot he can take, checked in the emulator with his die forced ([where](discoveries.md#-who-can-meet-the-grey-man-and-where)) | observed | compu-lsd Spy, fandom Gray Man |
| Texture sets | 4 sets per zone (normal, kanji, downer, upper); new sets after days 10, 20 and 30, on a 40-day cycle | observed | compu-lsd Textures, fandom Textures |
| Glitch textures | Appear after long sessions until power-off; reproducible by zeroing the frame counters in RAM. Our check: a texture set that fails to load for lack of memory; zeroing "location_time" leaks enough to cause it until power-off, but no ordinary path we played leaked a byte ([glitch textures](discoveries.md#-glitch-textures-a-texture-set-that-failed-to-load)) | observed | fandom Data Analysis |
| Generation seed | A debug picture shows "World: 17464 0 36838"; said to be fed by loads, timers and menus | observed | fandom Generation |
| Rare events | Flying train in Happy Town, giant astronaut bar (days 200 to 300), special lions near Temple Dojo, multiple gunmen or minotaurs; conditions unknown. Our check: the figures we first took for the gunmen are the maze penguins ([discoveries](discoveries.md#-a-red-day-fills-the-maze-of-questions-with-rainbow-penguins)); our best match for the gunmen is a cyan-day row of four more Violence District gunmen, seen on screen with the colour forced ([discoveries](discoveries.md#-characters-that-answer-to-circle)); our best match for the special lions is a cyan-day pair of Natural World lions that send you to Temple Dojo, reached in the emulator by a walk that makes the day cyan with no colour forced ([discoveries](discoveries.md#-the-natural-world-lions-a-random-temper-and-a-cyan-day-pair-that-leads-to-temple-dojo)) | observed | fandom Train, LSD Revamped docs |
| Cut content | Unused grey dog (`SYMDOG.MOM`), Bright Moon WC room, alternate Asmik logo, unused Clockwork Machines track; a 1997 demo had a debug menu | rumour | TCRF |
| Myths | Hidden ending if the graph is full, "over 500 tracks", no Grey Man after day 365, legends about the diary's author | rumour | compu-lsd |

## Technical

- All game logic is in `SLPS_015.56`; lsddecomp's config treats it as one code segment with no overlays.
- Loaded at `0x80010000` (checked on our dump: PS-X EXE header, `t_addr 0x80010000`, `t_size 0x7b000`, entry `0x8001199c`). lsddecomp gives `gp = 0x8008A808`, not yet checked here (the header's `gp0` is 0, so the startup code sets it).
- PSY-Q functions from libgs, libpad, libspu and libc are already spotted. SDK and compiler versions are unproven; lsddecomp guessed GCC 2.6.3 with aspsx 2.34.
- Code style: structures with vtables and `New_X` constructors, object-oriented C or C++.
- RAM map of day, timer, position and graph values is published (fandom Data Analysis) and matches lsddecomp's `DreamSys` offsets.

| Version | Id | Notes |
|---|---|---|
| Limited edition (retail) | SLPS-01556 | 1998-10-22, with the "Lucy in the Sky with Dynamites" CD single. The target |
| Normal edition | SLPS-01642 | Listed by psxdatacenter, existence doubted by compu-lsd |
| Japanese PSN | unknown | 2010-08-11; whether its executable differs is unknown |
| June 1998 beta | none | Never released, known from ad screenshots |

| Format | Content | Decoded by | State |
|---|---|---|---|
| LBD | 20x20-tile level chunk | libLSD | Known; collision and footstep fields were guesses. Our check: the low 7 bits are the step sound, the top bit marks a wall block that can link you, rotations are quarter turns, heights whole tiles, and the `SolidTile` byte is never read ([blocks and walls](discoveries.md#-the-world-is-built-from-square-blocks-and-only-marked-blocks-are-walls)) |
| MOM / MML / MOS | Entity model and animations | libLSD | Containers complete; behaviour lives in the exe |
| TMD, TIM, TOD | Sony models, textures, animations | libLSD, LSDView | Complete |
| TIX | A zone's texture set (TEXA to TEXD) | libLSD | Complete |
| VH/VB, SEQ | Sound banks and music | libLSD | Readable, convertible to MIDI |
| STR | Videos | standard PS1 tools | Complete |
| Memory card save | Progression | nobody | Undocumented |
| Zone, link and spawn tables | In the exe | lsddecomp | Addresses found, partly typed |

## Earlier projects

- FirecatFG/lsddecomp (2024, 5 commits): 119 named symbols, 25 `DreamSys` functions in C (22 with bodies, 6 more commented out), a per-location dream time table at `0x80087f14` and a timer note (timer `0x80091554`, duration `0x80091664`). Its build: bundled GCC 2.6.3 `cc1` with `-O2 -G0 -funsigned-char`, maspsx `--aspsx-version=2.34 --expand-div --dont-force-G0 -G8`. Rough split, unproven compiler, no licence: its addresses and findings are a credited reference, its code is not reused.
- Figglewatts/LSD Revamped: faithful graph and graph-to-dream mapping; dream length, Grey Man, texture choice and links are invented or approximate. Not a source of truth, and its repo holds original game files: take nothing from it.
- Not found: GameShark codes, a public Ghidra project, leaked symbols.

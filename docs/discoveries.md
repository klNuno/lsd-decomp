# Discoveries

What reading the game's code taught us about LSD: Dream Emulator. Each finding below says in plain words what happens when you play, then keeps the proof (functions, addresses, tables, how it was checked) folded under "Technical details". Open questions live in [mysteries.md](mysteries.md).

Status of each finding:

- 🎮 Checked in the game: we ran the game in an emulator, changed or watched its memory, and saw the predicted result on screen or in memory.
- 🎮 Partly checked: part of it was seen in the emulator, the rest is read in the code.
- 📖 Read in the code only: the code says so, nobody has seen it happen yet.

Game screenshots live in `img/game/`, which is not tracked: they show in a local clone with your own captures, not on GitHub. The charts are ours and are tracked.

## The findings at a glance

Days and years
- [The day counter and the hidden year](#the-day-counter-and-the-hidden-year): after day 365 you are back on day 1 and a hidden year counter goes up.
- [The first dream of a new year starts from the wrong data](#the-first-dream-of-a-new-year-starts-from-the-wrong-data): a bug picks the start place from part of a score instead of day 365.

The dream graph
- [How a day becomes a point on the graph](#how-a-day-becomes-a-point-on-the-graph): an average of the moods of where you walked and what you touched.
- [How the graph picks where tomorrow starts](#how-the-graph-picks-where-tomorrow-starts): 51 graph points lead nowhere and always send you to the same place.

How long a dream lasts
- [The start place sets the length of the dream](#the-start-place-sets-the-length-of-the-dream): from 1 to 10 minutes, fixed the moment you fall asleep.

Special days
- [The 42 special days](#the-42-special-days): 13 fixed days plus a weekly run that stops at day 204.
- [What a special day shows](#what-a-special-day-shows): a video 1 time in 3, a still picture 2 times in 3.

Flashbacks
- [How flashback memories are kept](#how-flashback-memories-are-kept): 1 chance in 3 per moment, 10 slots, and the tenth is never replaced.
- [What unlocks Flashback in the menu](#what-unlocks-flashback-in-the-menu): a score above 9,999,999, mostly from 30 hidden navigation goals.
- [What erases the flashbacks](#what-erases-the-flashbacks): one kind of character wipes the list on contact; which one is not proven.

The Grey Man
- [When the Grey Man can appear](#when-the-grey-man-can-appear): even days only, 1 chance in 12 at a spot left empty that day.

Textures
- [The 40-day texture cycle](#the-40-day-texture-cycle): the later in a 40-day cycle, the more texture sets a place can wear.

Links between places
- [Where a random link sends you](#where-a-random-link-sends-you): the place after yours comes up twice as often as the others.
- [Signals from characters and objects](#signals-from-characters-and-objects): touching, forced links, forced endings and event videos.

Memory card
- [Everything the game remembers fits in one block](#everything-the-game-remembers-fits-in-one-block): 1,792 bytes, starting with the letters J01.
- [How the memory card save works](#how-the-memory-card-save-works): the day number goes into the save title.

Randomness
- [The dice of the game](#the-dice-of-the-game): a fixed number sequence that is almost never reseeded.

Unused content
- [The dog that never loads](#the-dog-that-never-loads): a dog model sits on the disc, but the loader stops before it.

## Days and years

### The day counter and the hidden year

The game counts your days. The number you see is the internal counter plus one, so the first day shows as day 1. When day 365 ends, the counter goes back to day 1 and a hidden year counter goes up by one. The game never shows the year, but it is saved, and it changes how the next dream starts (see the next finding).

Status: 🎮 checked in the game.

<p>
<img src="img/game/menu-day-001.png" alt="Main menu on day 1 of a new game" width="32%">
<img src="img/game/menu-day-365.png" alt="Main menu on day 365, the last day of the first year" width="32%">
<img src="img/game/menu-new-year.png" alt="Main menu after day 365: the counter is back on day 1" width="32%">
</p>

<details><summary>Technical details</summary>

Day counter: +0x180 counts from 0; `func_8005A304` increments it and at 365 sets it to 0 and increments the year at +0x17C. Code that needs the day number calls `func_8005A2E4` (vtable 0x1A0), which returns day+1 and the year. `func_8005A368` saves the day at +0x88C when a dream starts and `func_8005A41C` restores it before advancing.

- Proof: `func_8005A304` @0x8005A304 (matched C), `func_8005A2E4` @0x8005A2E4, `func_8005A368` @0x8005A368, `func_8005A41C` @0x8005A41C.
- In game: yes. Poked day 364 (and +0x88C) during a dream and forced the timer; after that dream ended the RAM read year 1, day 0.
- Question: [8](mysteries.md#days-textures-randomness). Found 2026-10-15.

</details>

### The first dream of a new year starts from the wrong data

Each dream starts from the graph point of the day before. On the first day of a new year, yesterday is day 365, but the game reads the wrong two bytes: part of the touch score (see [the flashback unlock](#what-unlocks-flashback-in-the-menu)) instead of day 365's point. So the first dream of year 2 and later can start somewhere unrelated to how day 365 went. Only the very first day of a new game is handled on purpose: it always starts from the middle of the graph.

Status: 🎮 checked in the game.

<img src="img/game/new-year-dream.png" alt="First dream of year 2: it started in a place predicted from the score bytes, not from day 365" width="60%">

<details><summary>Technical details</summary>

First dream of a new year: the start point comes from the wrong bytes. `func_8005B1F4` (vtable 0x1EC, mode 1) reads yesterday's graph point at +0x190 + (day-1)*2; on day 0 with year >= 1 it reads +0x18E, the upper half of the instance score at +0x18C, instead of day 364's point. Only year 0 day 0 is special-cased to (0,0).

- Proof: `func_8005B1F4` @0x8005B1F4 (asm: `lb 0x190(day*2-2)`), caller `func_8005A508` @0x8005A508.
- In game: yes. Set the instance score to 0x01FD0000 (bytes 0x18E, 0x18F = -3, 1) and wrapped the year; the next dream started on stage 2 with time limit 7200 and its first logged chunk mood (-3, 1), as predicted from the table; day 364's point (0,0) would have given stage 0.
- Questions: [8](mysteries.md#days-textures-randomness), [2](mysteries.md#graph-and-dream-start). Found 2026-10-15.

</details>

## The dream graph

### How a day becomes a point on the graph

Every area of a dream carries a mood, a point on the graph from -9 to 9 on each axis, and so do the characters and objects you touch. At the end of a normal day, the game averages the moods of the areas you walked through and adds a third of the last one; it does the same for what you touched, then takes the middle of the two. If you touched nothing, only the areas count. A result past 9 does not stop at the edge: it jumps to the opposite edge, -9. Only a normal day end stores a point, and days watched in flashback mode leave none. The graph screen shows your last 100 days.

Status: 🎮 partly checked in the game (the "third of the last one" part was not exercised).

<img src="img/game/graph-screen.png" alt="The graph screen with one point per past day" width="60%">

<details><summary>Technical details</summary>

Graph point of a day: `func_8005B5B8` (vtable 0x208) keeps two accumulators, chunks at +0x144 and entities at +0x154, each {last point, sum x, sum y, count}. `func_8005B66C` makes each axis `sum / count + last / 3` (C division, truncated), and a result above 9 becomes -9 and below -9 becomes 9 (a flip to the edge, not a modulo). `func_8005B420` averages the chunk and entity results per axis, using the chunk result twice when no entity was logged (+0x160 = 0). `func_8005A41C` stores it in the graph at +0x190 + day*2, only on a normal end (argument 0) outside flashback mode, then advances the day. The graph screen `func_80058404` draws the last 100 days at 10 units per step.

- Proof: `func_8005B5B8` @0x8005B5B8, `func_8005B66C` @0x8005B66C (both matched C), `func_8005B5F0` @0x8005B5F0, `func_8005B420` @0x8005B420, `func_8005A41C` @0x8005A41C, `func_80058404` @0x80058404.
- In game: partly. The forced end wrote day 364's point from a chunk-only accumulator ((0,0), count 1); the new dream's chunk accumulator held (-3,1). The `last / 3` term was not exercised.
- Question: [1](mysteries.md#graph-and-dream-start). Found 2026-10-15.

</details>

### How the graph picks where tomorrow starts

Tomorrow's dream starts in the first area, in the game's own list order, whose mood is exactly yesterday's point. Day 1 starts from the middle of the graph and so always opens in the same place. Of the 361 points of the graph, 51 match no area at all: most sit in the four corners, plus two odd holes near the middle. After a day that lands on one of them, the dream always starts in the same place (number 1 in the game's list) at one of its 3 spawn points, and the game counts it as a random link, which lowers the [flashback score](#what-unlocks-flashback-in-the-menu).

Status: 🎮 partly checked in the game (the fallback to place 1 was not triggered).

![Graph grid of 19 by 19 points: 310 lead to a start place, 51 lead nowhere, in the four corners plus (0, 3) and (5, 7)](img/chart-mood-grid.svg)

<img src="img/game/first-dream.png" alt="The first dream of a new game, which always starts in the same place" width="60%">

<details><summary>Technical details</summary>

Start chunk choice: `func_8004950C` scans stages 0 to 13 and their chunks row by row and returns the first chunk whose s16 mood equals yesterday's point. `func_8005C28C` then takes the stage's spawn point that names that chunk (else chunk % count). With no match it returns -1, and `func_8005BB30` turns -1 into stage 1 (`negu`), with a random spawn among its 3: always stage 1, not a random zone. 51 of the 361 points have no chunk: 49 in the four corners, all with abs(x) >= 6 and abs(y) >= 6 (13 in the top-left corner, 12 in each other one; the corners are cut along a rough diagonal, not as full 4 x 4 squares, see the chart), plus (0,3) and (5,7). (0,0) lands on stage 0, chunk (0,3). That fallback also increments the dynamic-link counter.

- Proof: `func_8004950C` @0x8004950C, `func_8005C28C` @0x8005C28C, `func_8005BB30` @0x8005BB30, tables 0x80086590, 0x800861D4, 0x800885B8, 0x800885F0; coverage computed by `work/hunt/moodmap.py`. The same script shows stage 3 is the first match for 180 of the 310 covered points.
- In game: partly. Day 1 (point (0,0)) and the poked point (-3,1) both landed on the predicted stage; the stage-1 fallback was not triggered.
- Chart: `work/findings/charts.py`, which checks its list of 51 points against the executable (`--check`).
- Question: [2](mysteries.md#graph-and-dream-start). Found 2026-10-15.

</details>

## How long a dream lasts

### The start place sets the length of the dream

How long you get to wander is decided the moment you fall asleep, by the place the dream starts in: from 1 minute to 10. Walking through links never adds or removes time; only in flashback mode does a link restart the clock. These are the game's own figures; in the emulator the clock ran slower than real seconds, so the real length on a console may be longer.

Status: 🎮 checked in the game (the limit, not the real-time speed of the clock).

![Bar chart: dream length per starting stage, from 1 minute (stage 6) to 10 minutes (stage 5); stage 0, where day 1 starts, gives 4 minutes](img/chart-dream-length.svg)

<details><summary>Technical details</summary>

Dream length is fixed when the dream starts, from the starting stage: `func_8005C28C` reads the s16 seconds table `D_80087F14` (stages 0 to 13: 240, 180, 480, 420, 120, 600, 60, 300, 240, 300, 240, 180, 120, 480) and `func_80059328` (vtable 0x104) stores seconds x 15 at +0x134. `func_80058D94` (vtable 0x98) adds 1 to the timer at +0x24 on each message 2 and ends the dream once the count before the increment reaches the limit; `func_80059360` converts ticks back with /15. Links do not touch the limit; `func_8005A928` zeroes the timer on a link only in flashback mode (+0x68 set).

- Proof: `func_8005A508` @0x8005A508, `func_8005C28C` @0x8005C28C, `func_80059328` @0x80059328 (matched C), `func_80058D94` @0x80058D94, `func_80059360` @0x80059360, `func_8005A928` @0x8005A928, table 0x80087F14.
- In game: yes. Day 1 started on stage 0 with limit 3600 (240 x 15) and the year-1 dream on stage 2 with 7200 (480 x 15). In the emulator the timer gained 50 to 76 ticks per 600 vsyncs, so a tick is a game frame, not 1/15 s of real time; hardware rate not measured.
- Question: [11](mysteries.md#days-textures-randomness). Found 2026-10-15.

</details>

## Special days

### The 42 special days

The game keeps a list of 42 special days. 13 are fixed dates spread over the year, and 29 form a weekly run: every 7th day from day 7 to day 126, then, one day late, from 134 to 204. Day 126 is in both groups, so the list holds 41 different days and its second entry for 126 can never be reached. After day 204 only the fixed dates remain. On a special day the game skips the normal choice of a start place, and the day's mood log starts from the middle of the graph.

Status: 📖 read in the code only (the content a special day shows is checked, see the next finding).

![Calendar strip of 365 days: 13 fixed special days in orange, 29 weekly ones in blue from day 7 to 204, with day 133 skipped](img/chart-special-days.svg)

<details><summary>Technical details</summary>

Special days: `func_8005A368` calls `func_8005C438(+0x168, day number)`, which searches the 42 s16 days of `D_80088CCC`. On a match it writes {index % 12, rand() % 6} at +0x168, the dream gets mood (0,0) from `D_8008ABF4` and no spawn is chosen. Day 126 is listed twice (indexes 5 and 30), so index 30 is unreachable.

Table order: indexes 0 to 12 are 2, 15, 43, 81, 120, 126, 202, 259, 267, 284, 308, 328, 358; indexes 13 to 30 are 7 to 126 in steps of 7; indexes 31 to 41 are 134 to 204 in steps of 7 (133 is not listed). Read from the executable by `work/findings/charts.py --check`.

- Proof: `func_8005C438` @0x8005C438, `func_8005A368` @0x8005A368, `func_8005B2F4` @0x8005B2F4, table 0x80088CCC.
- In game: no.
- Question: [7](mysteries.md#days-textures-randomness). Found 2026-10-15.

</details>

### What a special day shows

Each special day belongs to one of 12 categories, and each category has 6 pieces: 2 videos and 4 still pictures, 72 files in all on the disc. When a special day comes, the game rolls a 6-sided die: 1 or 2 plays a video, 3 to 6 shows a still picture. So a special day is a video 1 time in 3 and a picture 2 times in 3. Since there are 42 entries and only 12 categories, several days share the same category. The video also needs one more condition that is not understood yet.

Status: 🎮 checked in the game (both the video and the picture branch).

<p>
<img src="img/game/special-day-video.png" alt="A special day playing its video" width="49%">
<img src="img/game/special-day-still.png" alt="A special day showing a still picture instead" width="49%">
</p>

<details><summary>Technical details</summary>

Special-day content: `func_8002677C` reads {category, variant} through `func_8005A4E8` (vtable 0x1BC, the 4 bytes at +0x168) and `func_80049334` resolves them. For a category >= 0 the path is the table at 0x800858CC (`D_80081A04` + 0x3EC8, `func_800492D0`), 0xA8 bytes per category = 6 paths of 0x1C bytes: variants 0 and 1 are `FILM\SPDAYnnA.STR` and `B.STR`, played by `func_8003B854` with video id category x 2 + 14 + variant (s16 table `D_80086170`); variants 2 to 5 get id -1 and show `IMG1\` or `IMG2\SPDAYnnC` to `F.TIM` through `func_8003BE94`. With `rand() % 6` a special day is a video 1 time in 3 and a still picture 2 times in 3. The 42 days are 13 fixed ones (2, 15, 43, 81, 120, 126, 202, 259, 267, 284, 308, 328, 358, indexes 0 to 12) then a weekly run (indexes 13 to 41): every 7th day from 7 to 126, then from 134 to 204; `index % 12` names the category, so categories share days. The video branch also needs the scene's `+0x20->+0x8` flag (unknown); the 72 files exist on the disc.

- Proof: `func_8002677C` @0x8002677C, `func_80049334` @0x80049334 (matched C), `func_800492D0` @0x800492D0 (matched C), `func_8005A4E8` @0x8005A4E8, `func_8005C438` @0x8005C438, tables 0x800858CC, 0x80086170, 0x80088CCC.
- In game: yes. PCSX-Redux interpreter with Lua breakpoints (`work/hunt2/bp.lua`): poked day 6 at `func_8005A368`, `func_8005C438` got day number 7, `func_80049334` got category 1 variant 1 and an STR video with a timecode played (capture at vsync 3600); with the rand state forced to 1 at the same call, variant 2 came out and a still diary picture showed (vsync 3200).
- Question: [7](mysteries.md#days-textures-randomness). Found 2026-10-15.

</details>

## Flashbacks

### How flashback memories are kept

Now and then the game keeps a memory of the moment: when you touch something, and when a dream runs out of time, it rolls a 3-sided die and keeps the moment on a 1. A memory holds the place, where you stood, which way you faced and the day. Up to 10 are kept. Once all 10 slots are full, a new memory replaces one of the first nine, picked from the timer, so the tenth memory stays forever. In flashback mode each memory plays for 20 seconds before the next, and those days add no point to the graph.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

Flashback list: count at +0x46C, entries of 0x24 bytes from +0x470 (10 at most, ending at +0x5D8). `func_8005B81C` (vtable 0x218) saves one with probability 1/3 (`rand() % 3 == 0`) when the player object at +0x4C exists; it runs when the day timer expires (`func_80058D94`) and on entity message 9 (`func_8005B03C`). `func_8005B74C` (0x214) appends {stage, position, rotation, length 0x10, day} while fewer than 10 are kept, else overwrites entry `timer % 9`: once full, the 10th entry is never replaced. Flashback mode is +0x68, set by `func_800590E8` (vtable 0xF0) from the menu (`func_8004D9D4` case 1). Playback: `func_8005A63C` (0x1CC) loads entry +0x87C (stage, position, its day into +0x180), `func_80058968` gives it 0x10 + 4 = 20 seconds and moves to the next; in that mode the day end stores no graph point.

- Proof: `func_8005B81C` @0x8005B81C, `func_8005B74C` @0x8005B74C, `func_8005A63C` @0x8005A63C, `func_80058968` @0x80058968, `func_800590E8` @0x800590E8 (matched C), `func_8004D9D4` @0x8004D9D4.
- In game: no.
- Question: [6](mysteries.md#grey-man-and-flashback). Found 2026-10-15.

</details>

### What unlocks Flashback in the menu

Flashback appears in the menu once two things are true: at least one memory is kept, and your score is above 9,999,999. The score is recomputed at the end of each normal day from two parts. The first: 1,000,000 for each of 30 hidden "navigation" goals you completed (all 30 give 50,000,000), minus 11,024 for every random link you took. The second: points from touching characters and objects, up to 50,000,000. So 10 navigation goals with no random link are enough on their own. What completes a navigation goal is not traced yet.

Status: 📖 read in the code only (on day 1 both values were still 0).

<p>
<img src="img/game/flashback-locked.png" alt="Menu with the Flashback item still locked" width="49%">
<img src="img/game/flashback-unlocked.png" alt="Menu with the Flashback item available" width="49%">
</p>

<details><summary>Technical details</summary>

Flashback unlock: the menu item is enabled by `func_8004D678` only when the save block's +0xC (DreamSys +0x184, unlock score) is above 9,999,999 and +0x2F4 (+0x46C, flashbacks kept) is not 0. `func_8005B6E0` (vtable 0x210, run by `func_8005A41C` on a normal day end) sets +0x184 = +0x188 + +0x18C. +0x188 comes from `func_8005BA7C`: 1,000,000 per non-zero byte among the 30 navigation flags (+0x5E0 via `D_8008ACB4`), 50,000,000 once all 30 are set, minus 11,024 per dynamic link (+0x600), floored at 0. +0x18C, the instance score, is clamped to 0..50,000,000 and grows on entity message 9 by the entity's vtable 0x150 value (`func_8005B03C`). So 10 navigation challenges with no dynamic link unlock it; each dynamic link costs 11,024. What sets a navigation flag is not traced.

- Proof: `func_8004D678` @0x8004D678, `func_8005B6E0` @0x8005B6E0, `func_8005BA7C` @0x8005BA7C (all matched C), `func_8005B03C` @0x8005B03C, `func_8005A41C` @0x8005A41C.
- In game: no. On day 1 +0x184 and +0x46C read 0 at `func_8005A368`, the threshold was not reached.
- Question: [6](mysteries.md#grey-man-and-flashback). Found 2026-10-15.

</details>

### What erases the flashbacks

One piece of code empties the whole memory list, and only one kind of character runs it: when that character gets close to you or touches you, it changes state and wipes every kept memory. Players say the Grey Man does this, but the code does not yet tell which character it is. Players also report that the graph flips after meeting him; no code that flips stored graph points was found.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

Erasing flashbacks: `func_8005B8FC` (vtable 0x21C) sets +0x46C to 0 and has one caller, `func_80064618`, an entity behaviour handler (16-byte record {handler, parameters} at 0x8008A4D0). When its +0xF4 is set and `func_8005D108(0, 0, 10, 0)` passes (likely a contact or range test), it sets state 7 on the object at +0x100, calls its own vtable 0x160, then clears the list. Which entity uses that record is not traced, so the link to `SYMSPY.MOM` (the Grey Man) is still a guess. No code that negates stored graph points was found, so the "graph flip" is not explained.

- Proof: `func_8005B8FC` @0x8005B8FC, `func_80064618` @0x80064618 (matched C), record 0x8008A4D0.
- In game: no.
- Question: [5](mysteries.md#grey-man-and-flashback). Found 2026-10-15.

</details>

## The Grey Man

### When the Grey Man can appear

Each spot where a character can stand has a day rule: always, even days only, or odd days only. When a spot stays empty because of its rule, the day number is even and you are not in the first place of the game's list, the game rolls a 12-sided die; on a 1, the Grey Man stands there instead. So he never shows up on odd days. That this model is the Grey Man rests on its file name, `SYMSPY.MOM`.

Status: 📖 read in the code only.

<img src="img/game/grey-man.png" alt="The Grey Man standing in a dream" width="60%">

<details><summary>Technical details</summary>

Grey Man spawn: per entity spawn slot, `func_80054120` calls `func_8005C7D4(entity, slot, day number)` (day number from vtable 0x1A0 of the object that `func_800534C8` also passes as `D_8008AC00`). `func_8005C9A4` lets a slot's entity appear when its flag is 0, or 1 on even day numbers, or 2 on odd ones. When the flag blocks it, the stage index (`D_8008ABF8`) is not 0, `rand() % 12 == 0` and the day number is even, `func_8005CF34` spawns the model loaded from `ETC\SYMSPY.MOM` (`D_80088D28`, loaded by `func_8005C508`). That this model is the Grey Man rests on the file name. Erasing flashbacks is not traced yet (see [What erases the flashbacks](#what-erases-the-flashbacks) for what was found since).

- Proof: `func_8005C7D4` @0x8005C7D4 (asm: `andi s1,1` and the 0x2AAAAAAB divide by 12), `func_8005C9A4` @0x8005C9A4, `func_8005C8AC` @0x8005C8AC, `func_8005C508` @0x8005C508, `func_80054120` @0x80054120.
- In game: no.
- Question: [5](mysteries.md#grey-man-and-flashback). Found 2026-10-15.

</details>

## Textures

### The 40-day texture cycle

Every place has up to four texture sets, A to D. When a place loads, the game looks at where the day falls in a 40-day cycle. Days 1 to 10 always load set A. Days 11 to 20 load A or B, 21 to 30 one of A to C, 31 to 40 one of A to D, each equally likely. Then the cycle starts again at day 41. Since the day number returns to 1 after day 365, days 361 to 365 count as days 1 to 5 and always load set A.

Status: 📖 read in the code only.

![Step chart: days 1 to 10 of the cycle allow only set A, 11 to 20 A or B, 21 to 30 A to C, 31 to 40 A to D](img/chart-texture-cycle.svg)

<p>
<img src="img/game/textures-day-05.png" alt="A place on day 5, early in the cycle: always texture set A" width="49%">
<img src="img/game/textures-day-35.png" alt="A place on day 35, late in the cycle: any of the sets A to D" width="49%">
</p>

<details><summary>Technical details</summary>

Texture set: when a stage loads, `func_80052F10` calls `func_80048EA0(stage, day number)`, which picks set `rand() % (((day - 1) % 40) / 10 + 1)` among the stage's `TEXA` to `TEXD.TIX` paths (path table of 0x1C-byte entries from 0x80081A04, `func_80048E2C`). Days 1 to 10 of each 40-day cycle always load A, 11 to 20 A or B, 21 to 30 A to C, 31 to 40 A to D, each at random.

- Proof: `func_80048EA0` @0x80048EA0, `func_80048E2C` @0x80048E2C, `func_80052F10` @0x80052F10, rand wrapper `func_80048CFC` @0x80048CFC.
- In game: no.
- Question: [9](mysteries.md#days-textures-randomness). Found 2026-10-15.

</details>

## Links between places

### Where a random link sends you

Touching a wall can send you to another place. The game first looks for a fixed link for that wall; only if there is none, and random links are allowed at that moment, does it pick a place at random. It rolls a 6-sided die over the six main places (0 to 5 in its list). If the die names the place you are in, you go to the next one instead. So the place right after yours comes up 2 times in 6 and each of the other four 1 time in 6. Every random link is counted, and each one lowers the [flashback score](#what-unlocks-flashback-in-the-menu) by 11,024.

Status: 📖 read in the code only.

![Bar chart, example from main stage 2: stage 3 has 2 chances in 6, stages 0, 1, 4 and 5 have 1 in 6 each](img/chart-link-odds.svg)

<details><summary>Technical details</summary>

Links: a wall touch (`func_80058FAC`, message 4, no transition running) tries the static tables first (`func_8005A5D8` → `func_8005BCB4` → `func_8005C150` with 0x80088748, 0x80088710, 0x80088664) and links dynamically only if +0x124 is set (`func_8005A1B0`, vtable 0x18C). A dynamic link (`func_8005A580` → `func_8005BB30`) draws `rand() % 6` and moves a draw equal to the current stage to the next one (wrapping at 6), so from a main stage 0 to 5 the next stage is twice as likely (2/6) as each of the other four (1/6). It increments the counter at +0x600.

- Proof: `func_80058FAC` @0x80058FAC, `func_8005A5D8` @0x8005A5D8, `func_8005A580` @0x8005A580, `func_8005BB30` @0x8005BB30, `func_8005A1B0` @0x8005A1B0.
- In game: no.
- Question: [13](mysteries.md#events-and-hidden-content). Found 2026-10-15.

</details>

### Signals from characters and objects

Characters and objects talk to the dream through a handful of signals. Touching one logs its mood for the graph, adds its points to the touch score and may keep a [flashback memory](#how-flashback-memories-are-kept). Others send you to a fixed place, end the dream and queue their own video, or simply end the dream. These are the forced endings and event videos players know (the train, the astronaut, the lions); what makes each character send its signal is not traced yet. In flashback mode touching, event videos and forced endings do nothing.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

Entity events reach DreamSys through `func_8005B03C`, ignored while +0x44 is set: 4 calls the entity's slot 0x38; 9 (touch) logs the entity mood (0x14C), adds its slot 0x150 to the instance score and may save a flashback; 10 links to the fixed stage given by slot 0x154 (through `func_8005BB30` with a negative argument); 11 ends the dream (timer = limit) and queues the entity's video (+0x168 = -1, +0x16A = slot 0x158), played by the category -1 branch of `func_80049334` (`func_80049270`); 12 ends the dream. 9, 11 and 12 do nothing in flashback mode. These are the forced endings and event videos; the conditions that make an entity send them (train, astronaut, lions) are in the entity behaviour records, not traced.

- Proof: `func_8005B03C` @0x8005B03C, `func_80049270` @0x80049270 (matched C), `func_8005A928` @0x8005A928.
- In game: no.
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.

</details>

## Memory card

### Everything the game remembers fits in one block

All that the game carries from one day to the next lives in a single block of 1,792 bytes that starts with the letters "J01": the year, the day, the scores, your graph for all 365 days, the 30 navigation goals, the number of random links taken, and the flashback memories. This block is what the memory card saves (next finding).

Status: 🎮 checked in the game (the block and its "J01" mark were found in memory).

<details><summary>Technical details</summary>

One `DreamSys` object at `0x80091530` (vtable `0x80087BDC`). Its persistent block runs from +0x178 to +0x878 (0x700 bytes, returned with that size by `func_8005A350`, vtable slot 0x1B0) and starts with the magic `"J01"` written by `func_8005A258`. Layout read so far: +0x17C year, +0x180 day (0-based), +0x184 unlock score, +0x188 navigation score, +0x18C instance score, +0x190 graph (365 pairs of s8), +0x5E0 30 navigation flags, +0x600 dynamic-link count, +0x684 500 bytes cleared at new game. Likely the memory card payload; not yet traced to the card code. (Since traced: the memory card finding below saves exactly this block. The flashback list at +0x46C to +0x5D8 also sits inside it.)

- Proof: `func_8005A258` @0x8005A258, `func_8005A350` @0x8005A350, `func_8005BA50` @0x8005BA50 (stores the +0x5E0 and +0x600 addresses in `D_8008ACB4`, `D_8008ACB8`), graph reader `func_80058404` @0x80058404.
- In game: yes. Headless PCSX-Redux Lua probe (`work/hunt/dreamsys.lua`) at the title and in the first dream: vtable found once at 0x80091530, `"J01"` at +0x178, `D_8008ACB4` = 0x80091B10 (+0x5E0), `D_8008ACB8` = 0x80091B30 (+0x600).
- Question: [15](mysteries.md#events-and-hidden-content). Found 2026-10-15.

</details>

### How the memory card save works

Saving writes the whole memory block to the card under the file name `BISLPS-01556xxx`. The save title shows your day number in 3 digits. After one particular kind of dream ending, the game erases the first character of the file name before saving and adds extra text to the title; which ending that is, and what the text says, is not read yet. The card driver itself has not been read.

Status: 📖 read in the code only.

<img src="img/game/save-screen.png" alt="The memory card save screen with the day number in the save title" width="60%">

<details><summary>Technical details</summary>

Memory card: `func_8004D578` keeps the DreamSys save block (vtable 0x1B0) and its size 0x700 at +0xBC and +0xC0 of the save menu object and calls `func_8004D6AC(day number)`, which writes the day as 3 characters (`func_8004109C`) into the save title `D_8008AA18` (0x8001149C) at +0x12. `func_8004E0E4` saves through the card object's slot 0x78 with file name `D_8008AA10` = `BISLPS-01556xxx`, that title, 0xD, 3, the block and its size; `func_8004E1C4` loads through slot 0x74. When DreamSys +0x878 is set (`func_8005A344`; `func_8005A41C` sets it with `func_8005A258` on an end of type 2) the file name's first byte is zeroed before the save and `func_8004DB18` appends `D_8008AA14` to the title. The card driver itself is not read.

- Proof: `func_8004D578` @0x8004D578, `func_8004D6AC` @0x8004D6AC, `func_8004E0E4` @0x8004E0E4, `func_8004E1C4` @0x8004E1C4, `func_8004DB18` @0x8004DB18, strings 0x80011464, 0x8001149C.
- In game: no.
- Question: [15](mysteries.md#events-and-hidden-content). Found 2026-10-15.

</details>

## Randomness

### The dice of the game

Every die roll on this page (special days, flashbacks, the Grey Man, textures, random links) comes from one number sequence, the standard one of the PlayStation's development kit. The game can restart that sequence from a new point only once, early, before the title screen takes input, and the starting value is leftover data from drawing the screen. In the emulator that leftover was 0, which means "do not restart", so the sequence ran on from power-on. Whether a real console leaves something else there was not measured.

Status: 🎮 partly checked in the game (in the emulator only, not on a console).

<details><summary>Technical details</summary>

Random numbers: `rand` @0x80049480 is the PSY-Q LCG, state `D_8008AC68` (0 in the executable) times 0x41C64E6D plus 0x3039, returning bits 16 to 30. `srand` has one caller, `func_80048CFC(seed)`, which reseeds only when seed is not 0 and then draws. The only non-zero seed comes from `func_800260A4` (slot 0x40 of the scene class that `func_80025FDC` builds with `ETC\DREAME5.TMD` and a new DreamSys): scratchpad word 0x1F800000 % 365. That scratchpad is a render work buffer (`func_80012064` hands it to `func_80018464`), so the seed is leftover render data, at most 728 seeds (-364 to 364, signed modulo) plus "no reseed".

- Proof: `rand` @0x80049480, `srand` @0x800494A8, `func_80048CFC` @0x80048CFC (matched C), `func_800260A4` @0x800260A4 (matched C), `func_80025FDC` @0x80025FDC, `func_80012064` @0x80012064.
- In game: partly. Breakpoints showed `func_800260A4` run once, at vsync 1318 before the title input, with scratchpad word 0, so `srand` was never called; the rand state at the first special-day check was 0xA70427DF. Real hardware's scratchpad at that moment was not measured.
- Question: [10](mysteries.md#days-textures-randomness). Found 2026-10-15.

</details>

## Unused content

### The dog that never loads

The disc holds a model for a dog next to the Grey Man's. The loader is written to load both, but it stops after the first one, and nothing else in the game asks for the dog. So the dog is never loaded and cannot appear.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

`ETC\SYMDOG.MOM` is never loaded: `func_8005C508` loads `ETC\SYMSPY.MOM`, writes the dog's path into its load descriptor and leaves its loop after one pass (`beqz s1` after `s1++`). No other code references the dog path `D_8001187C`.

- Proof: `func_8005C508` @0x8005C508, `D_8001187C`.
- In game: no.
- Question: [14](mysteries.md#events-and-hidden-content). Found 2026-10-15.

</details>

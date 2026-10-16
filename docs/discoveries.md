# Discoveries

What reading the game's code taught us about LSD: Dream Emulator. Each finding below says in plain words what happens when you play, then keeps the proof (functions, addresses, tables, how it was checked) folded under "Technical details". Open questions live in [mysteries.md](mysteries.md).

Status of each finding:

- 🎮 Checked in the game: we ran the game in an emulator, changed or watched its memory, and saw the predicted result on screen or in memory.
- 🎮 Partly checked: part of it was seen in the emulator, the rest is read in the code.
- 📖 Read in the code only: the code says so, nobody has seen it happen yet.

What the mark before each title means:

- 🆕 New: nobody had written it down before us, not the wikis, not lsddecomp, not the community notes.
- 🧩 Known in part: players had seen it or knew some of it; we add how it works, its exact conditions or its numbers.
- ✅ Confirmed: something players or earlier projects believed, now proven by the code or the emulator.
- 🔄 Corrected: a belief that was partly wrong; the finding gives the right version.
- ❌ Myth busted: a belief the code proves false.

The screenshots come from the game running in an emulator, sometimes with memory values written in to reach a state quickly; each finding says when.

## The findings at a glance

Days and years
- ✅ [The day counter and the hidden year](#-the-day-counter-and-the-hidden-year): after day 365 you are back on day 1 and a hidden year counter goes up.
- 🆕 [The first dream of a new year starts from the wrong data](#-the-first-dream-of-a-new-year-starts-from-the-wrong-data): a bug picks the start place from part of a score instead of day 365.

The ending
- ✅ [The ending plays when a year closes, not on day 365](#-the-ending-plays-when-a-year-closes-not-on-day-365): the video comes right after the dream of day 365, when the counter goes back to day 1.

The dream graph
- ✅ [The secret video reel: four graph points and 11 minutes of film](#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film): a face drawn on the graph makes it blink green, then plays 20 special-day videos back to back.
- ✅ [How a day becomes a point on the graph](#-how-a-day-becomes-a-point-on-the-graph): an average of the moods of where you walked and what you touched.
- ✅ [The graph screen only shows your last 100 days](#-the-graph-screen-only-shows-your-last-100-days): a full year-long graph never appears on screen.
- 🧩 [How the graph picks where tomorrow starts](#-how-the-graph-picks-where-tomorrow-starts): 51 graph points lead nowhere, and 93 others wake you in the right place but on another square.

How long a dream lasts
- ✅ [The start place sets the length of the dream](#-the-start-place-sets-the-length-of-the-dream): from 1 to 10 minutes, fixed the moment you fall asleep.

Special days
- ✅ [The 42 special days](#-the-42-special-days): 13 fixed days plus a weekly run that stops at day 204.
- ✅ [What a special day shows](#-what-a-special-day-shows): a video 1 time in 3, a still picture 2 times in 3.

Flashbacks
- 🧩 [How flashback memories are kept](#-how-flashback-memories-are-kept): 1 chance in 3 per moment, 10 slots, and the tenth is never replaced.
- ✅ [What unlocks Flashback in the menu](#-what-unlocks-flashback-in-the-menu): a score above 9,999,999, mostly from the navigation goals, which are the fixed links.
- ✅ [What erases the flashbacks](#-what-erases-the-flashbacks): touching the Grey Man wipes them all, every time.

The Grey Man
- ✅ [The Grey Man flips your graph and wipes your memories](#-the-grey-man-flips-your-graph-and-wipes-your-memories): his mood sits past the edge of the graph, so touching him throws your day to the opposite corner.
- 🧩 [When the Grey Man can appear](#-when-the-grey-man-can-appear): even days only, 1 chance in 12 at a spot left empty that day.
- 🔄 [Who can meet the Grey Man, and where](#-who-can-meet-the-grey-man-and-where): he only replaces odd-day characters, and six places never get him.

Rare sights
- ✅ [The flying train: a pink day and a long dream](#-the-flying-train-a-pink-day-and-a-long-dream): on an odd pink day Happy Town's train stops at the opera pillar, honks and flies off, if the dream lasts long enough.
- ✅ [The astronaut lands at the bar on a pink day](#-the-astronaut-lands-at-the-bar-on-a-pink-day): on an even pink day it dives into the cottage's yard and stands at the bar; the day number does not matter.
- 🧩 [A red day fills a Happy Town street with gunmen](#-a-red-day-fills-a-happy-town-street-with-gunmen): one gunman becomes nine, and the question mark in the sky goes away.
- 🧩 [Three minotaur rickshaws on a yellow day in Kyoto](#-three-minotaur-rickshaws-on-a-yellow-day-in-kyoto): one rickshaw becomes three on an odd yellow day.
- 🆕 [Three purple beasts on a yellow day: our best match for the special lions](#-three-purple-beasts-on-a-yellow-day-our-best-match-for-the-special-lions): a lone beast of Pit & Temple gets three walking companions.
- 🧩 [A red day puts a geisha on a Kyoto bridge](#-a-red-day-puts-a-geisha-on-a-kyoto-bridge): she stands still on the red bridge, and her link goes to Black Space.

Characters and events
- 🧩 [The hidden rules that decide which characters appear](#-the-hidden-rules-that-decide-which-characters-appear): day cycles, your mood so far, and groups that show up only once.
- 🧩 [The character record: mood, points, waking up and leaving](#-the-character-record-mood-points-waking-up-and-leaving): 130 character types, and the five that end the dream on a video.
- 🧩 [Signals from characters and objects](#-signals-from-characters-and-objects): touching, forced links, forced endings and event videos.

Textures
- 🧩 [Glitch textures: a texture set that failed to load](#-glitch-textures-a-texture-set-that-failed-to-load): the place is drawn with leftovers, and the dream ends 30 seconds later.
- ✅ [The 40-day texture cycle](#-the-40-day-texture-cycle): the later in a 40-day cycle, the more texture sets a place can wear.

Links between places
- 🆕 [Fixed links are the navigation goals, and one can never be completed](#-fixed-links-are-the-navigation-goals-and-one-can-never-be-completed): 29 of the 30 goals can be reached, so the big bonus never pays out.
- 🔄 [Where a random link sends you](#-where-a-random-link-sends-you): the place after yours comes up twice as often as the others.
- 🔄 [Fixed links do not change with visits, but some depend on who showed up](#-fixed-links-do-not-change-with-visits-but-some-depend-on-who-showed-up): no visit counter; four characters switch on extra links.

Music
- ✅ [A Clockwork Machines track that can never play](#-a-clockwork-machines-track-that-can-never-play): the dice can pick it, but the game plays the next track instead.
- 🆕 [A switch to pin the music that nobody pulls](#-a-switch-to-pin-the-music-that-nobody-pulls): a leftover way to force one sound bank and one track.

Memory card
- 🧩 [Everything the game remembers fits in one block](#-everything-the-game-remembers-fits-in-one-block): 1,792 bytes, starting with the letters J01, with the SHAKE option and the video reel flag.
- 🧩 [How the memory card save works](#-how-the-memory-card-save-works): the day number goes into the save title, and a new game saves to a new file.

Randomness
- 🔄 [The dice of the game](#-the-dice-of-the-game): a fixed number sequence that is almost never reseeded; "type A and B days" are just odd and even days.

Hidden and unused content
- 🆕 [SELECT + TRIANGLE in the pause erases your game](#-select--triangle-in-the-pause-erases-your-game): the game's only hidden button input, with no warning; no cheat code exists.
- ✅ [The dog that never loads](#-the-dog-that-never-loads): a dog model sits on the disc, but the loader stops before it.
- 🧩 [What the game never asks for](#-what-the-game-never-asks-for): three files on the disc and one menu slot, and no debug menu found.

Myths checked
- ❌ [Myth: a hidden ending if the graph is full](#-myth-a-hidden-ending-if-the-graph-is-full): false.
- ❌ [Myth: no Grey Man after day 365](#-myth-no-grey-man-after-day-365): false, he came back in year two.
- ❌ [Myth: over 500 music tracks](#-myth-over-500-music-tracks): false, 462 at most, and some of them are silence.
- ❌ [Myth: the astronaut lands only between days 200 and 300](#-myth-the-astronaut-lands-only-between-days-200-and-300): false, a pink day decides it, and it landed on day 4.

## Days and years

### ✅ The day counter and the hidden year

The game counts your days. The number you see is the internal counter plus one, so the first day shows as day 1. When day 365 ends, the counter goes back to day 1 and a hidden year counter goes up by one. The game never shows the year, but it is saved, it plays [the ending video](#-the-ending-plays-when-a-year-closes-not-on-day-365) when it goes up, and it changes how the next dream starts (see the next finding).

Status: 🎮 checked in the game.

<p>
<img src="img/game/menu-day-001.png" alt="Main menu on day 1 of a new game" width="32%">
<img src="img/game/menu-day-365.png" alt="Main menu on day 365, the last day of the first year" width="32%">
<img src="img/game/menu-new-year.png" alt="Main menu after day 365: the counter is back on day 1" width="32%">
</p>

<details><summary>Technical details</summary>

Day counter: +0x180 counts from 0; `DreamSys_AdvanceDay` @0x8005A304 increments it and at 365 sets it to 0 and increments the year at +0x17C. Code that needs the day number calls `DreamSys_GetDayNumber` @0x8005A2E4 (vtable 0x1A0), which returns day+1 and the year. `DreamSys_StartDay` @0x8005A368 saves the day at +0x88C when a dream starts and `DreamSys_EndDay` @0x8005A41C restores it before advancing.

- Proof: `DreamSys_AdvanceDay` @0x8005A304 (matched C), `DreamSys_GetDayNumber` @0x8005A2E4, `DreamSys_StartDay` @0x8005A368, `DreamSys_EndDay` @0x8005A41C.
- In game: yes. Poked day 364 (and +0x88C) during a dream and forced the timer; after that dream ended the RAM read year 1, day 0.
- Question: [8](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: lsddecomp already read the wrap to day 0 and the year increment in `DreamSys_AdvanceDay`, and the fandom wiki (Data Analysis) knew the RAM holds the day minus one; new here are the emulator proof and what the year changes.

</details>

### 🆕 The first dream of a new year starts from the wrong data

Each dream starts from the graph point of the day before. On the first day of a new year, yesterday is day 365, but the game reads the wrong two bytes: part of the touch score (see [the flashback unlock](#-what-unlocks-flashback-in-the-menu)) instead of day 365's point. So the first dream of year 2 and later can start somewhere unrelated to how day 365 went. Only the very first day of a new game is handled on purpose: it always starts from the middle of the graph.

Status: 🎮 checked in the game.

<img src="img/game/new-year-dream.png" alt="First dream of year 2: it started in a place predicted from the score bytes, not from day 365" width="60%">

<details><summary>Technical details</summary>

First dream of a new year: the start point comes from the wrong bytes. `DreamSys_GetPreviousPoint` @0x8005B1F4 (vtable 0x1EC, mode 1) reads yesterday's graph point at +0x190 + (day-1)*2; on day 0 with year >= 1 it reads +0x18E, the upper half of the instance score at +0x18C, instead of day 364's point. Only year 0 day 0 is special-cased to (0,0).

- Proof: `DreamSys_GetPreviousPoint` @0x8005B1F4 (asm: `lb 0x190(day*2-2)`), caller `DreamSys_ChooseStart` @0x8005A508.
- In game: yes. Set the instance score to 0x01FD0000 (bytes 0x18E, 0x18F = -3, 1) and wrapped the year; the next dream started on stage 2 with time limit 7200 and its first logged chunk mood (-3, 1), as predicted from the table; day 364's point (0,0) would have given stage 0.
- Questions: [8](mysteries.md#days-textures-randomness), [2](mysteries.md#graph-and-dream-start). Found 2026-10-15.
- Before us: nothing on it in the fandom wiki (Chart, Ending, Data Analysis), compu-lsd (Graph), the LSD Revamped docs or lsddecomp; the bug is new.

</details>

## The ending

### ✅ The ending plays when a year closes, not on day 365

The ending video (the erupting Mount Fuji and a countdown) does not play during day 365. It plays right after that dream ends, at the moment the day counter goes back to day 1 and the hidden year counter goes up. Then the menu comes back on "Day 001". The game checks for "day 1 and a year above 0", so the video should come back at the end of every later year too. Nothing else in the game asks for the ending video.

Status: 🎮 checked in the game (the end of year 1; later years are read in the code only).

<p>
<img src="img/game/hidden-ending-fuji.png" alt="Ending video: a figure rises above Mount Fuji" width="49%">
<img src="img/game/hidden-ending-countdown.png" alt="Ending video: a countdown circle showing 3" width="49%">
</p>

<details><summary>Technical details</summary>

The scene class (vtable `0x8006D3C8`, built by `Scene_New` from `main` @0x800118DC) runs its loop in `App_Run`: slot 0x50 logos, then forever slot 0x54 opening video, slot 0x58 title; when the title returns 2, slot 0x60 runs the dream (`Scene_RunDream`), and if that returns non-zero slot 0x64 `Scene_PlayEnding` plays the video returned by `Cine_GetEndingPath` (file table base `File_GetPathTable` + 0x3E04 = `ETC\ENDING.STR` @0x80085808, video index 7). `Scene_RunDream` returns 1 when `DreamSys_GetDayNumber` @0x8005A2E4 (vtable 0x1A0) returns 1 and writes a non-zero year. After a normal end, `DreamSys_EndDay` @0x8005A41C calls `DreamSys_AdvanceDay` @0x8005A304, which wraps 364 to 0 and adds a year. No other code reads the ending entry.

- Proof: `App_Run` @0x8003B110, `Scene_RunDream` @0x80026698, `Scene_PlayEnding` @0x80026900, `Cine_GetEndingPath` @0x800491FC, `DreamSys_GetDayNumber` @0x8005A2E4, vtable 0x8006D3C8 (slot 0x64 = 0x80026900, the only pointer to it).
- In game: yes. Interpreter run (`work/hunt3/run3.log`): day +0x180 = 364 at vsync 2300, dream started (StartDay at 3126), timer +0x24 = 3590 of 3600 at 4000. Breakpoints: `DreamSys_EndDay` type 0 at 4366, then `Scene_PlayEnding` at 4378 with year 1, day 0; the video ran until the title at 6360, which showed "Day 001". Forced: day and timer.
- Not checked: the end of year 2 and later. By the same test, a dream that does not advance the day (a flashback) started on day 1 of year 1 or later should replay the ending; not run. The pause code's type 1 quit would do the same, but no input reaches it ([the erase combo](#-select--triangle-in-the-pause-erases-your-game)).
- Questions: [14](mysteries.md#events-and-hidden-content), [8](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: the fandom wiki (Ending) already says the video starts when day 365 comes to an end and comes back at the end of every later year; we confirm it in the code and the emulator and show that nothing else asks for `ENDING.STR`.

</details>

## The dream graph

### ✅ The secret video reel: four graph points and 11 minutes of film

The graph hides a face. If, among the days the graph screen shows (your last 100), your day points have landed at least once on each of four exact cells, the game plays a secret. The four cells are the centre, the cell just above it to the left, the cell just above it to the right, and the cell three steps below the centre: two eyes, a nose and a mouth. The order and the dates do not matter.

When the graph screen comes up after the title, those four cells turn green one after the other. Then, instead of the menu, a long film starts by itself: the special-day videos back to back (pigeons on a window sill, a sheep, a radio tower and more), 20 of the 24, about 11 minutes by the game's own count. You can only see it once per game: a flag is set and saved with the game, and only a new game, or [the erase combo](#-select--triangle-in-the-pause-erases-your-game), clears it.

Status: 🎮 checked in the game, with the graph points written in (the film was watched for several minutes, not to its end).

<p>
<img src="img/game/video-reel-graph-before.png" alt="The graph screen with the four secret points still white, just after it opens" width="49%">
<img src="img/game/video-reel-graph-green.png" alt="The same four points turned green: two eyes above the centre, the centre, and a mouth three cells below" width="49%">
</p>
<p>
<img src="img/game/video-reel-film.png" alt="The film that starts by itself after the green blink: an inverted city shot" width="49%">
<img src="img/game/video-reel-pigeons.png" alt="Minutes later the film is still running, now on the pigeons of a special-day video" width="49%">
</p>

<details><summary>Technical details</summary>

The graph screen draw `Graph_Draw` @0x80058404 gets the save block (DreamSys vtable 0x1B0, DreamSys + 0x178: +0x4 year, +0x8 day, +0x18 graph) and stores `Graph_CheckReel` @0x800585B4 in +0x238. `Graph_CheckReel` (now C, `src/game/80058078.c`) returns 0 at once when byte +0x467 of the save block is set. That byte is DreamSys +0x5DF: the hunters' notes give both offsets, and they are the same byte (0x178 + 0x467 = 0x5DF). Otherwise, for each of the 4 targets of `g_reelPoints` (s8 pairs as (x, y): (-1, 1), (1, 1), (0, 0), (0, -3)) it compares the stored s16 point of the last n days, n = min(day, 100) in year 0 and 100 from year 1 on, walking back from yesterday and wrapping to index 0x16C. It writes the position of a matching day into the 4-byte buffer at +0x240 and returns 0 as soon as one target has no match. When all four match it sets +0x467 = 1, +0x23C = 0 and returns 1.

- Blink: `Graph_BlinkReel` @0x80058694, while +0x238 is set and the screen timer +0x1C is at least 31, paints the next of the four matched points every 24 frames with `g_graphReelColor` = (0, 255, 0). The newest point is normally red `g_graphNewestColor` and older ones fade from white `g_graphOldColor` (`Graph_CreateSprites`).
- Exit: `Graph_Run` returns 2 instead of the screen's normal result when +0x238 is set. The title routine `Scene_RunTitle` @0x80026410 runs the graph before the menu when the game is not on its first day (and the video flag of the scene settings is on); a 2 calls `Scene_PlayReel` @0x8002658C, which asks `Cine_GetSpecialDayRun(&len, 0, 10)` @0x800493E4 for the path `FILM\SPDAY01A.STR` (`Cine_GetSpecialDayPaths(0)`) and a length: the sum of the 20 entries of `g_videoTable` @0x80086170 from index 14 (categories 0 to 9, both videos each) plus 10 frames per join, 10,122 frames, 674.8 s at 15 frames per second. The video player (`VideoScreen_New`, slots 0x6C, 0x12C, 0x44) plays that path for that length; `SPDAY01A.STR` to `SPDAY10B.STR` are contiguous on the disc (LBA 127656 to 229085), so the stream runs on through the ten categories' A and B videos in order.
- Once per game: +0x5DF lies inside the 0x700-byte block the memory card saves ([the save block](#-everything-the-game-remembers-fits-in-one-block)), and only `DreamSys_InitNewGame` @0x8005A258 clears it (`arg0->unk5DF = 0`), which a new game and the erase combo both call. Saving then reloading a game that has seen the reel was not run.
- Proof: `Graph_Draw`, `Graph_CheckReel`, `Graph_BlinkReel`, `Graph_Run`, `Scene_RunTitle`, `Scene_PlayReel`, `Cine_GetSpecialDayRun`, `DreamSys_InitNewGame`; tables `g_reelPoints`, `g_graphReelColor`, `g_videoTable`.
- In game: yes, two independent runs (dynarec, `work/shots/drive.lua`). Run A: +0x180 = 4 (day 5), +0x190 to +0x197 = the four points, +0x5DF = 0 at vsync 2100, CIRCLE at 2200 opened the graph; the cells were white at 2520 and turned green one at a time (one at 2600, three at 2700, four at 2800, 100 pure-green pixels per cell); at 3200 a full-screen video played with no input. A second run with captures every 700 vsyncs up to 13,400 showed the film going through different clips (inverted city crowd, machinery, TV static, the pigeons of the day-7 video, a sheep with a timecode, a pagoda, a radio tower). Control run: same day with points (2, 2), (3, 3), (4, 4), (5, 5), no green, and the graph left to the menu (Day 005) on its own. Run B (`work/hunt4/B-run6.log`): day 10, the four points then six others; +0x5DF went from 0 to 1 between vsync 2300 and 2400, the four cells turned green between 2560 and 2900, and a video ran from about 3600 and was still running at 4500. Forced: the day and the graph points only.
- Not checked: the end of the film (its 11 minutes are the game's own count, not timed), which frames come from which file, and the flag surviving a save and load.
- Question: [4](mysteries.md#graph-and-dream-start). Found 2026-10-15.
- Before us: the fandom wiki (Chart trivia, Video Dreams) already gives the same four cells and the green blink, and calls the film all the video dreams; new here: only the last 100 days count, the film is 20 of the 24 videos, and it plays once per game.

</details>

### ✅ How a day becomes a point on the graph

Every area of a dream carries a mood, a point on the graph from -9 to 9 on each axis, and so do the characters and objects you touch. At the end of a normal day, the game averages the moods of the areas you walked through and adds a third of the last one; it does the same for what you touched, then takes the middle of the two. If you touched nothing, only the areas count. A result past 9 does not stop at the edge: it jumps to the opposite edge, -9, and a result below -9 jumps to 9. That jump is how [the Grey Man flips your graph](#-the-grey-man-flips-your-graph-and-wipes-your-memories). Only a normal day end stores a point, and days watched in flashback mode leave none. The graph screen shows [your last 100 days](#-the-graph-screen-only-shows-your-last-100-days).

Status: 🎮 checked in the game (the whole sum, the third of the last one and the jump included, during the Grey Man test).

<img src="img/game/graph-screen.png" alt="The graph screen with one point per past day" width="60%">

<details><summary>Technical details</summary>

Graph point of a day: `Mood_Log` @0x8005B5B8 (vtable 0x208) keeps two accumulators, chunks at +0x144 and entities at +0x154, each {last point, sum x, sum y, count}. `Mood_CalcAxis` @0x8005B66C makes each axis `sum / count + last / 3` (C division, truncated), and a result above 9 becomes -9 and below -9 becomes 9 (a flip to the edge, not a modulo). `DreamSys_ComputeDayPoint` @0x8005B420 averages the chunk and entity results per axis, using the chunk result twice when no entity was logged (+0x160 = 0). `DreamSys_EndDay` @0x8005A41C stores it in the graph at +0x190 + day*2, only on a normal end (argument 0) outside flashback mode, then advances the day. The graph screen `Graph_Draw` draws the last 100 days at 10 units per step.

- Proof: `Mood_Log` @0x8005B5B8, `Mood_CalcAxis` @0x8005B66C (both matched C), `Mood_Resolve` @0x8005B5F0, `DreamSys_ComputeDayPoint` @0x8005B420, `DreamSys_EndDay` @0x8005A41C, `Graph_Draw` @0x80058404.
- In game: yes. The forced end wrote day 364's point from a chunk-only accumulator ((0,0), count 1); the new dream's chunk accumulator held (-3,1). The Grey Man run then exercised every term: chunks {last (-3, 1), sum (-3, 1), n 1} gave (-3 + -1, 1 + 0) = (-4, 1); entities {last (-10, -10), sum (-10, -10), n 1} gave -10 + -3 = -13, flipped to 9 on both axes; the stored point was the truncated mean (2, 5). Logs `work/hunt3/gm.log` to `gm3.log`.
- Question: [1](mysteries.md#graph-and-dream-start). Found 2026-10-15.
- Before us: Higashi's formula (fandom wiki, Chart; compu-lsd, Graph) and lsddecomp's `last / 3` already described it; the community's five-step table for the last term differs from the code only at plus or minus 9, where the code adds 3, not 2.

</details>

### ✅ The graph screen only shows your last 100 days

The graph screen draws one point per day, but only for your last 100 days. On day 150 the first 50 days are gone from the picture, and from the second year on it always shows exactly 100. The newest point is red and the older ones fade from white to dark grey. A full year-long graph never appears on screen.

Status: 🎮 checked in the game, with the graph points written in.

<p>
<img src="img/game/graph-150-days.png" alt="Graph on day 150: days 1 to 50 sat on the top-right cell and are not drawn; only the 10 by 10 block of the last 100 days shows at the lower left" width="49%">
<img src="img/game/graph-99-days.png" alt="The same graph on day 99: a dark grey point appears on the top-right cell, over the medallion, and the lower-left block is half as tall" width="49%">
</p>

<details><summary>Technical details</summary>

`Graph_Draw` @0x80058404 draws n = min(day, 100) points in year 0 and 100 from year 1 on, walking back from yesterday's index and wrapping from 0 to 0x16C (day 365). `Graph_CreateSprites` creates exactly 100 point sprites: the first is red, the next six fade by 20 per step from white, the rest by 1.

- Proof: `Graph_Draw`, `Graph_CreateSprites`.
- In game: yes (dynarec, runs 3 and 4 of `work/hunt4/`): days 1 to 50 written at (8, 8), the top-right cell, then a 10 x 10 block in the lower left. With +0x180 = 150 the top-right cell is empty; with 99 a dark grey point sits in it. Forced: the day and the graph points.
- Found 2026-10-15; it also rules out [the "full graph" ending](#-myth-a-hidden-ending-if-the-graph-is-full).
- Before us: the fandom wiki (Chart) already says each filled cell stays for 100 days, so the whole chart can never be filled; we confirm it in the code and the emulator.

</details>

### 🧩 How the graph picks where tomorrow starts

Tomorrow's dream starts in the first area, in the game's own list order, whose mood is exactly yesterday's point. Day 1 starts from the middle of the graph and so always opens in the same place. Of the 361 points of the graph, 51 match no area at all: most sit in the four corners, plus two odd holes near the middle. After a day that lands on one of them, the dream always starts in the same place (number 1 in the game's list) at one of its 3 spawn points, and the game counts it as a random link, which lowers the [flashback score](#-what-unlocks-flashback-in-the-menu).

Each place is a grid of map squares, each with its own mood. Filler squares (sea edges, empty corners) carry the mood (9, 0), which the game uses as "no mood here": 106 squares in 8 places. But (9, 0) is also a real graph point, so a day that ends there matches the first filler square in the list, an empty square of place 1, and you then wake up at one of place 1's arrival points. The game can only drop you on a square that has an arrival point: 93 of the 310 points that match a square name one without, so you wake up in the right place, but on another of its squares.

Status: 🎮 partly checked in the game (the fallback to place 1 was not triggered; the filler squares and the 93 off-square starts are read in the code and data only).

![Graph grid of 19 by 19 points: 310 lead to a start place, 51 lead nowhere, in the four corners plus (0, 3) and (5, 7)](img/chart-mood-grid.svg)

<img src="img/game/first-dream.png" alt="The first dream of a new game, which always starts in the same place" width="60%">

<details><summary>Technical details</summary>

Start chunk choice: `Stage_FindChunkByMood` @0x8004950C scans stages 0 to 13 and their chunks row by row and returns the first chunk whose s16 mood equals yesterday's point. `Spawn_PickFromMood` @0x8005C28C then takes the stage's spawn point that names that chunk (else chunk % count). With no match it returns -1, and `Spawn_PickRandom` @0x8005BB30 turns -1 into stage 1 (`negu`), with a random spawn among its 3: always stage 1, not a random zone. 51 of the 361 points have no chunk: 49 in the four corners, all with abs(x) >= 6 and abs(y) >= 6 (13 in the top-left corner, 12 in each other one; the corners are cut along a rough diagonal, not as full 4 x 4 squares, see the chart), plus (0,3) and (5,7). (0,0) lands on stage 0, chunk (0,3). That fallback also increments the dynamic-link counter.

The {9, 0} sentinel: the grids `g_stageChunkMoods[stage]` (s16 mood per square, row-major, low byte x, high byte y; sizes at `g_stageGrids`) hold (9, 0) on 106 squares: stage 1 (1), 2 (1), 3 (74), 4 (3), 5 (3), 11 (10), 12 (13), 13 (1). They are filler pieces: in stage 4 the squares of column 5 rows 0, 2 and 4, whose files are the small 8,580 and 6,740-byte ones; in stage 3 the 4,944-byte edge pieces (chunk file of square (col, row) = `M{row*cols+col:03d}.LBD`, checked on all 14 stages; lsddecomp's `StageGrid.c` shows the same values). `Stage_FindChunkByMood` has no special case, so the point (9, 0) matches stage 1, square (0, 1), key 0x100. `Spawn_PickFromMood` then looks for an arrival record (`g_spawnPoints[stage]`, 6-byte records keyed by row << 8 | col, counts `g_spawnCounts`) naming that square; none does, so it takes record `key % count` = 256 % 3 = 1, square (1, 0) of stage 1. The same happens for 93 of the 310 matched points (count printed by an inline script over the same tables): the place is exact, the square is not always. The chunk mood logger has no filter either (`DreamSys_OnMapMessage`, event 5 → vtable 0x1F4 → `Mood_Log`), so walking into a (9, 0) square would count (9, 0) toward the day; whether any filler square can be walked into was not checked.

- Proof: `Stage_FindChunkByMood` @0x8004950C, `Spawn_PickFromMood` @0x8005C28C, `Spawn_PickRandom` @0x8005BB30, tables 0x80086590, 0x800861D4, 0x800885B8, 0x800885F0; coverage computed by `work/hunt/moodmap.py`. The same script shows stage 3 is the first match for 180 of the 310 covered points. Square-to-file check: `work/hunt4/A/mml.py`.
- In game: partly. Day 1 (point (0,0)) and the poked point (-3,1) both landed on the predicted stage; the stage-1 fallback was not triggered.
- Chart: `work/findings/charts.py`, which checks its list of 51 points against the executable (`--check`).
- Question: [2](mysteries.md#graph-and-dream-start). Found 2026-10-15.
- Before us: Higashi's spawn chart (fandom wiki, Chart; compu-lsd, Graph) already maps points to places and says points outside the drawn chart start in Pit & Temple, while the community notes (from lsddecomp) said a random zone; new here: the 51 dead points with two holes near the middle, the (9, 0) filler squares and the 93 off-square starts.

</details>

## How long a dream lasts

### ✅ The start place sets the length of the dream

How long you get to wander is decided the moment you fall asleep, by the place the dream starts in: from 1 minute to 10. Walking through links never adds or removes time; only in flashback mode does a link restart the clock. These are the game's own figures; in the emulator the clock ran slower than real seconds, so the real length on a console may be longer.

Status: 🎮 checked in the game (the limit, not the real-time speed of the clock).

![Bar chart: dream length per starting stage, from 1 minute (stage 6) to 10 minutes (stage 5); stage 0, where day 1 starts, gives 4 minutes](img/chart-dream-length.svg)

<details><summary>Technical details</summary>

Dream length is fixed when the dream starts, from the starting stage: `Spawn_PickFromMood` @0x8005C28C reads the s16 seconds table `g_stageTimeLimits` @0x80087F14 (stages 0 to 13: 240, 180, 480, 420, 120, 600, 60, 300, 240, 300, 240, 180, 120, 480) and `DreamSys_SwapTimeLimit` @0x80059328 (vtable 0x104) stores seconds x 15 at +0x134. `DreamSys_TickTimer` @0x80058D94 (vtable 0x98) adds 1 to the timer at +0x24 on each message 2 and ends the dream once the count before the increment reaches the limit; `DreamSys_GetElapsedSeconds` @0x80059360 converts ticks back with /15. Links do not touch the limit; `DreamSys_ExecuteLink` @0x8005A928 zeroes the timer on a link only in flashback mode (+0x68 set).

- Proof: `DreamSys_ChooseStart` @0x8005A508, `Spawn_PickFromMood` @0x8005C28C, `DreamSys_SwapTimeLimit` @0x80059328 (matched C), `DreamSys_TickTimer` @0x80058D94, `DreamSys_GetElapsedSeconds` @0x80059360, `DreamSys_ExecuteLink` @0x8005A928, table 0x80087F14.
- In game: yes. Day 1 started on stage 0 with limit 3600 (240 x 15) and the year-1 dream on stage 2 with 7200 (480 x 15). In the emulator the timer gained 50 to 76 ticks per 600 vsyncs, so a tick is a game frame, not 1/15 s of real time; hardware rate not measured.
- Question: [11](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: lsddecomp's DreamTimer.md already had the 14 lengths per starting place, from 60 to 600 seconds; we confirm them in the emulator and show that links do not change the limit outside flashback mode.

</details>

## Special days

### ✅ The 42 special days

The game keeps a list of 42 special days. 13 are fixed dates spread over the year, and 29 form a weekly run: every 7th day from day 7 to day 126, then, one day late, from 134 to 204. Day 126 is in both groups, so the list holds 41 different days and its second entry for 126 can never be reached. After day 204 only the fixed dates remain. On a special day the game skips the normal choice of a start place, and the day's mood log starts from the middle of the graph.

Status: 📖 read in the code only (the content a special day shows is checked, see the next finding).

![Calendar strip of 365 days: 13 fixed special days in orange, 29 weekly ones in blue from day 7 to 204, with day 133 skipped](img/chart-special-days.svg)

<details><summary>Technical details</summary>

Special days: `DreamSys_StartDay` @0x8005A368 calls `Day_FindSpecial @0x8005C438(+0x168, day number)`, which searches the 42 s16 days of `g_specialDays` @0x80088CCC. On a match it writes {index % 12, rand() % 6} at +0x168, the dream gets mood (0,0) from `D_8008ABF4` and no spawn is chosen. Day 126 is listed twice (indexes 5 and 30), so index 30 is unreachable.

Table order: indexes 0 to 12 are 2, 15, 43, 81, 120, 126, 202, 259, 267, 284, 308, 328, 358; indexes 13 to 30 are 7 to 126 in steps of 7; indexes 31 to 41 are 134 to 204 in steps of 7 (133 is not listed). Read from the executable by `work/findings/charts.py --check`.

- Proof: `Day_FindSpecial` @0x8005C438, `DreamSys_StartDay` @0x8005A368, `DreamSys_ResetMoodAccumulators` @0x8005B2F4, table 0x80088CCC.
- In game: no.
- Question: [7](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: lsddecomp had the 42-day table and the fandom wiki (Video Dreams) lists the days of each of the 12 sets; new here: how the list is built (13 fixed days plus a weekly run) and the unreachable second entry for day 126.

</details>

### ✅ What a special day shows

Each special day belongs to one of 12 categories, and each category has 6 pieces: 2 videos and 4 still pictures, 72 files in all on the disc. When a special day comes, the game rolls a 6-sided die: 1 or 2 plays a video, 3 to 6 shows a still picture. So a special day is a video 1 time in 3 and a picture 2 times in 3. Since there are 42 entries and only 12 categories, several days share the same category. The video also needs one more condition that is not understood yet.

Status: 🎮 checked in the game (both the video and the picture branch).

<p>
<img src="img/game/special-day-video.png" alt="A special day playing its video" width="49%">
<img src="img/game/special-day-still.png" alt="A special day showing a still picture instead" width="49%">
</p>

<details><summary>Technical details</summary>

Special-day content: `Scene_PlayCinematic` @0x8002677C reads {category, variant} through `DreamSys_GetCinematic` @0x8005A4E8 (vtable 0x1BC, the 4 bytes at +0x168) and `Cine_GetPath` @0x80049334 resolves them. For a category >= 0 the path is the table at 0x800858CC (`g_pathTable` + 0x3EC8, `Cine_GetSpecialDayPaths` @0x800492D0), 0xA8 bytes per category = 6 paths of 0x1C bytes: variants 0 and 1 are `FILM\SPDAYnnA.STR` and `B.STR`, played by `VideoScreen_New` with video id category x 2 + 14 + variant (s16 table `g_videoTable` @0x80086170); variants 2 to 5 get id -1 and show `IMG1\` or `IMG2\SPDAYnnC` to `F.TIM` through `MenuScreen_New`. With `rand() % 6` a special day is a video 1 time in 3 and a still picture 2 times in 3. The 42 days are 13 fixed ones (2, 15, 43, 81, 120, 126, 202, 259, 267, 284, 308, 328, 358, indexes 0 to 12) then a weekly run (indexes 13 to 41): every 7th day from 7 to 126, then from 134 to 204; `index % 12` names the category, so categories share days. The video branch also needs the scene's `+0x20->+0x8` flag (unknown); the 72 files exist on the disc.

- Proof: `Scene_PlayCinematic` @0x8002677C, `Cine_GetPath` @0x80049334 (matched C), `Cine_GetSpecialDayPaths` @0x800492D0 (matched C), `DreamSys_GetCinematic` @0x8005A4E8, `Day_FindSpecial` @0x8005C438, tables 0x800858CC, 0x80086170, 0x80088CCC.
- In game: yes. PCSX-Redux interpreter with Lua breakpoints (`work/hunt2/bp.lua`): poked day 6 at `DreamSys_StartDay` @0x8005A368, `Day_FindSpecial` got day number 7, `Cine_GetPath` got category 1 variant 1 and an STR video with a timecode played (capture at vsync 3600); with the rand state forced to 1 at the same call, variant 2 came out and a still diary picture showed (vsync 3200).
- Question: [7](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: the fandom wiki (Video Dreams) already says each set has 2 videos and 4 text dreams, a video 2 times in 6; we confirm the die and both branches in the code and the emulator.

</details>

## Flashbacks

### 🧩 How flashback memories are kept

Now and then the game keeps a memory of the moment: when you touch something, and when a dream runs out of time, it rolls a 3-sided die and keeps the moment on a 1. A memory holds the place, where you stood, which way you faced and the day. Up to 10 are kept. Once all 10 slots are full, a new memory replaces one of the first nine, picked from the timer, so the tenth memory stays forever. In flashback mode each memory plays for 20 seconds before the next, and those days add no point to the graph.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

Flashback list: count at +0x46C, entries of 0x24 bytes from +0x470 (10 at most, ending at +0x5D8). `DreamSys_MaybeSaveFlashback` @0x8005B81C (vtable 0x218) saves one with probability 1/3 (`rand() % 3 == 0`) when the player object at +0x4C exists; it runs when the day timer expires (`DreamSys_TickTimer` @0x80058D94) and on entity message 9 (`DreamSys_OnEntityEvent` @0x8005B03C). `DreamSys_AddFlashback` @0x8005B74C (0x214) appends {stage, position, rotation, length 0x10, day} while fewer than 10 are kept, else overwrites entry `timer % 9`: once full, the 10th entry is never replaced. Flashback mode is +0x68, set by `DreamSys_SetFlashbackMode` @0x800590E8 (vtable 0xF0) from the menu (`Menu_Confirm` case 1). Playback: `DreamSys_LoadNextFlashback` @0x8005A63C (0x1CC) loads entry +0x87C (stage, position, its day into +0x180), `DreamSys_EnterMap` gives it 0x10 + 4 = 20 seconds and moves to the next; in that mode the day end stores no graph point.

- Proof: `DreamSys_MaybeSaveFlashback` @0x8005B81C, `DreamSys_AddFlashback` @0x8005B74C, `DreamSys_LoadNextFlashback` @0x8005A63C, `DreamSys_EnterMap` @0x80058968, `DreamSys_SetFlashbackMode` @0x800590E8 (matched C), `Menu_Confirm` @0x8004D9D4.
- In game: no (the Grey Man run saw one memory saved on a touch, the count going from 3 to 4, without checking the die).
- Question: [6](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: lsddecomp knew the limit of 10 memories and the fandom wiki (Flashback) that notable events, even repeated trumpeters, are kept; new here: the 1 in 3 roll, the tenth memory that stays and the 20 seconds per memory.

</details>

### ✅ What unlocks Flashback in the menu

Flashback appears in the menu once two things are true: at least one memory is kept, and your score is above 9,999,999. The score is recomputed at the end of each normal day from two parts. The first: 1,000,000 for each hidden "navigation" goal you completed, minus 11,024 for every random link you took. The second: points from touching characters and objects, up to 50,000,000. The navigation goals are [the fixed links between places](#-fixed-links-are-the-navigation-goals-and-one-can-never-be-completed): the first time you take each one, its goal is done. There are 30 goals and a 50,000,000 bonus for all 30, but one goal can never be completed, so that bonus never pays out and the navigation part stops at 29,000,000. So 10 navigation goals with no random link are enough on their own.

Status: 🎮 checked in the game, with the values written in: a score of 10,000,000 and one kept memory made FLASHBACK appear between START and SAVE. The navigation goals are read in the code only.

<p>
<img src="img/game/flashback-locked.png" alt="Menu with the Flashback item still locked" width="49%">
<img src="img/game/flashback-unlocked.png" alt="Menu with FLASHBACK between START and SAVE, after the score and one memory were written in" width="49%">
</p>

<details><summary>Technical details</summary>

Flashback unlock: the menu item is enabled by `Menu_UpdateFlashbackItem` @0x8004D678 only when the save block's +0xC (DreamSys +0x184, unlock score) is above 9,999,999 and +0x2F4 (+0x46C, flashbacks kept) is not 0. `DreamSys_CalcUnlockScore` @0x8005B6E0 (vtable 0x210, run by `DreamSys_EndDay` @0x8005A41C on a normal day end) sets +0x184 = +0x188 + +0x18C. +0x188 comes from `Nav_CalcScore` @0x8005BA7C: 1,000,000 per non-zero byte among the 30 navigation flags (+0x5E0 via `g_navFlags` @0x8008ACB4), 50,000,000 once all 30 are set (only above 29,999,999), minus 11,024 per dynamic link (+0x600), floored at 0. +0x18C, the instance score, is clamped to 0..50,000,000 and grows on entity message 9 by the entity's vtable 0x150 value (`DreamSys_OnEntityEvent` @0x8005B03C). So 10 navigation challenges with no dynamic link unlock it; each dynamic link costs 11,024. The flags are set only by `Link_Find` @0x8005C150 when its sixth argument is not 0, from the two static link tables, whose union lacks flag 13: +0x188 stops at 29,000,000 and the unlock score at 79,000,000 (see [the fixed links](#-fixed-links-are-the-navigation-goals-and-one-can-never-be-completed)).

- Proof: `Menu_UpdateFlashbackItem` @0x8004D678, `DreamSys_CalcUnlockScore` @0x8005B6E0, `Nav_CalcScore` @0x8005BA7C (all matched C), `DreamSys_OnEntityEvent` @0x8005B03C, `DreamSys_EndDay` @0x8005A41C, `Link_Find` @0x8005C150.
- In game: yes, forced. On a fresh day 1 +0x184 and +0x46C read 0 and the item is absent. Writing +0x184 = 10,000,000, +0x46C = 1 and zeroing entry +0x470 at vsync 2100 made the menu show FLASHBACK between START and SAVE (capture at 2460; with a flashback kept, the title skips the graph and opens the menu). Script `work/shots/drive.lua`, log `work/shots/manifest.md`. The navigation flags were not exercised (no fixed link was taken in the emulator).
- Question: [6](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: lsddecomp already read a score of 30 navigation challenges at 1,000,000 each minus a penalty per random link, where the fandom wiki (Flashback) spoke of a gauge of events; we confirm it in the emulator and add the exact threshold.

</details>

### ✅ What erases the flashbacks

The Grey Man does. One piece of code empties the whole memory list, and only he runs it: when he touches you, he vanishes in a white flash and every kept memory is gone. There is no die roll, so every touch erases them all. The same touch also [flips your graph](#-the-grey-man-flips-your-graph-and-wipes-your-memories).

Status: 🎮 checked in the game, with the Grey Man forced to appear.

<details><summary>Technical details</summary>

Erasing flashbacks: `DreamSys_ClearFlashbacks` @0x8005B8FC (vtable 0x21C) sets +0x46C to 0 and has one caller, `Behavior_EraseFlashbacks` @0x80064618, the handler of entity type 98 (16-byte record {handler, parameters} at 0x8008A4D0, the handler at +0xC of record 98 from `g_entityRecords`). Type 98 is the Grey Man: `Sym_InitStage` creates the spy object with `Entity_Create(i + 0x62, ...)`, so the `SYMSPY.MOM` model and the eraser are the same character. A touch (`Entity_CheckTouch`, slot 0x178 → slot 0x164 `Entity_SetTouched`) sends message 9 and sets +0xF4. On its next run the handler sees +0xF4, starts the effect object `Entity_StartEffect(obj, 0, 0, 10, 0)` (the white flash), sets state 7 on the object at +0x100, calls its own vtable 0x160, then clears the list. No code negates stored graph points: the "graph flip" is the wrap of `Mood_CalcAxis` @0x8005B66C on his mood (-10, -10).

- Proof: `DreamSys_ClearFlashbacks` @0x8005B8FC, `Behavior_EraseFlashbacks` @0x80064618, `Sym_InitStage`, `Entity_SetTouched`, `Entity_CheckTouch` (all matched C), record 0x8008A4D0.
- In game: yes, forced. Flashback count +0x46C = 3 written at vsync 3700; at 4399 the Grey Man touched the player, the handler ran with +0xF4 = 1 on an object of type 98 and `DreamSys_ClearFlashbacks` ran with the count at 4 (the touch had just saved one); at 4449 the count read 0. Logs `work/hunt3/gm.log`, `gm2.log`, `gm3.log`.
- Question: [5](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: the game's manual (quoted on the fandom wiki, Gray Man) says meeting him erases your memory, and compu-lsd (Spy) says it might; we confirm that every touch erases them all and that nothing else does.

</details>

## The Grey Man

### ✅ The Grey Man flips your graph and wipes your memories

When you touch the Grey Man, three things happen at once. He vanishes in a white flash, every kept flashback memory is erased, and his mood is logged like any character you touch. His mood is (-10, -10), one step beyond the -9 edge of the graph. Then the "last thing touched" bonus pushes your "things touched" score further down. Past -9 the value jumps to +9, so if he is the only thing you touched, or most of what you touched was dark, that half of your day point jumps to the opposite corner. This is the graph flip players report. In the emulator, one touch moved the day's point from where it should have landed, (-6, -4), to (2, 5). If you never touch him, he leaves on his own after a fixed time: 3 minutes if his clock runs at the speed of the dream timer.

Status: 🎮 checked in the game, with the Grey Man forced to appear (his leaving on his own is read in the code only).

<p>
<img src="img/game/events-grey-man-flash.png" alt="The white flash right after touching the Grey Man under the torii of stage 2" width="49%">
<img src="img/game/events-grey-man-graph.png" alt="The graph after that day: the newest point, in red, sits in the upper half, far from the earlier point on the left" width="49%">
</p>

<details><summary>Technical details</summary>

The Grey Man is entity type 98: `Sym_InitStage` creates the spy object with `Entity_Create(i + 0x62, ...)`, and record 98 of the behaviour table (16 bytes from `g_entityRecords + 16 * type`, handler at +0xC, so 0x8008A4D0) holds `Behavior_EraseFlashbacks` @0x80064618. Record 98: mood (-10, -10) at +0/+1, touch score 20 (x 1000, read by vtable 0x150 `Entity_GetPoints`), wake mode 0 (awake at spawn), sleep mode 180 (leaves after 180 x 15 ticks of his own counter +0x24), touch range 1, no link, no video. Touch: `Entity_CheckTouch` (0x178) calls slot 0x164 `Entity_SetTouched`, which sends message 9 and sets +0xF4. Message 9 (`DreamSys_OnEntityEvent` @0x8005B03C) logs the record's mood into the entity accumulator at DreamSys +0x154 (`DreamSys_LogEntityMood` → `Mood_Log` @0x8005B5B8), adds 20,000 to +0x18C and may save a flashback. On its next run the handler sees +0xF4, starts the effect object `Entity_StartEffect(obj, 0, 0, 10, 0)` (the white flash), sets state 7, calls slot 0x160 and `DreamSys_ClearFlashbacks` @0x8005B8FC. The day point is `Mood_CalcAxis` @0x8005B66C = sum / count + last / 3, wrapped to the other side past +/-9: with the Grey Man as the only entity, -10 + (-10 / 3 = -3) = -13 → +9 on both axes. The wrap happens whenever the mean of touched moods, the Grey Man included, is below -6 on an axis while he is the last one touched.

- Proof: `Sym_InitStage` (0x62 constant), record 0x8008A4C4, `Behavior_EraseFlashbacks` @0x80064618, `Entity_SetTouched`, `Entity_CheckTouch`, `DreamSys_OnEntityEvent` @0x8005B03C, `Mood_CalcAxis` @0x8005B66C, `DreamSys_ComputeDayPoint` @0x8005B420 (all matched C).
- In game: yes, forced. Interpreter, +0x180 = 3 (day number 4), +0x194/+0x195 = (-3, 1) so the dream starts on stage 2, rand state 0 at every `Sym_SpawnOrSpy` entry, flashback count +0x46C = 3 written at vsync 3700. At vsync 4399 he touched the player: message 9, the handler ran with +0xF4 = 1 on an object with type 98, and `DreamSys_ClearFlashbacks` ran with the count at 4 (the touch had just saved one); at 4449 the count read 0 and the instance score 20,000. The accumulators then read zones {last (-3, 1), sum (-3, 1), n 1} and entities {last (-10, -10), sum (-10, -10), n 1}. With the timer forced to the limit at 4700 the day ended and stored point (2, 5) for that day: zones give (-4, 1), entities wrap to (9, 9), mean (2, 5). Without the wrap it would have been (-6, -4). Flash captured at 4460, graph at 7100. Logs `work/hunt3/gm.log`, `gm2.log`, `gm3.log`.
- Question: [5](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: the fandom wiki (Gray Man, Linking) already explains his (-10, -10) value and the jump to the opposite side of the chart; we confirm it in the code and the emulator, and add when the jump does not happen and that he leaves after a fixed time.

</details>

### 🧩 When the Grey Man can appear

Each spot where a character can stand has a day rule: always, odd days only, or even days only. When a spot stays empty because of its rule, the day number is even and you are not in the first place of the game's list, the game rolls a 12-sided die; on a 1, the Grey Man stands there instead. So he never shows up on odd days. Forcing the die in the emulator on day 4 brought him out, walking toward the player; when he reached the player the screen flashed white and [the memories were erased](#-what-erases-the-flashbacks).

Status: 🎮 checked in the game, with the die forced.

<img src="img/game/grey-man.png" alt="The Grey Man, in a hat and long coat, walking toward the camera under the torii of the canal place on day 4" width="60%">

<details><summary>Technical details</summary>

Grey Man spawn: per entity spawn slot, `Place_SpawnCell` calls `Sym_SpawnOrSpy @0x8005C7D4(entity, slot, day number)` (day number from vtable 0x1A0 of the object that `Place_Setup` also passes as `g_symDreamSys`). `Sym_CheckDayParity` @0x8005C9A4 returns `flag != (day % 2) + 1` for a non-zero flag: a slot's entity appears when its flag is 0, or 1 on odd day numbers, or 2 on even ones. When the flag blocks it, the stage index (`g_currentStage` @0x8008ABF8) is not 0, `rand() % 12 == 0` and the day number is even, `Sym_SpawnSpy` @0x8005CF34 spawns the model loaded from `ETC\SYMSPY.MOM` (`g_spyModel` @0x80088D28, loaded by `Sym_LoadModels` @0x8005C508). So only flag-1 slots on even days can hold him. The forced spawn in the emulator shows the Grey Man (hat, long coat), so `SYMSPY.MOM` is his model; he is entity type 98, whose handler erases the flashbacks (see [What erases the flashbacks](#-what-erases-the-flashbacks)).

- Proof: `Sym_SpawnOrSpy` @0x8005C7D4 (asm: `andi s1,1` and the 0x2AAAAAAB divide by 12), `Sym_CheckDayParity` @0x8005C9A4, `Sym_FindSlot` @0x8005C8AC, `Sym_LoadModels` @0x8005C508, `Place_SpawnCell` @0x80054120.
- In game: yes, forced. PCSX-Redux interpreter: +0x180 = 3 (day number 4, even), yesterday's point +0x194/+0x195 = (-3, 1) so the dream starts on stage 2, rand state 0 at every `Sym_SpawnOrSpy` entry (3 slots, vsyncs 3460 to 3481); the Grey Man walked toward the camera (capture at 4400) and the screen flashed white when he reached the player (4500). A later run with the same setup measured the flashback list cleared by that contact (`work/hunt3/gm.log`). Log `work/shots/manifest.md`.
- Question: [5](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: the wikis (fandom Gray Man, compu-lsd Spy) knew he comes on even (type B) days, but put his spawn down to the seed or an unknown "Gray Man Power"; new here: the 1 in 12 roll on a spot left empty.

</details>

### 🔄 Who can meet the Grey Man, and where

The Grey Man only takes a spot that its own rule leaves empty. A spot marked "odd days only" is empty on even days, and since he also needs an even day, he only ever takes the place of odd-day characters. Some places have no such spot at all: stages 1, 3, 8, 10 and 12 have only "every day" spots, and stage 0 is excluded outright. He cannot appear in those six. He can appear in stages 2, 4, 5, 6, 7, 9, 11 and 13.

Status: 📖 read in the code only (the rule that lets him spawn was seen working on stage 2).

<details><summary>Technical details</summary>

`Sym_CheckDayParity` @0x8005C9A4 returns `flag != (day % 2) + 1` for a non-zero flag: flag 1 lets the slot's characters appear on odd day numbers only, flag 2 on even ones only. `Sym_SpawnOrSpy` @0x8005C7D4 rolls for the Grey Man only when that check fails, the stage is not 0 and the day number is even, so only flag-1 slots on even days can hold him. Slot tables: per stage, `g_spawnSlots[stage]` points to 6-byte slots {s16 chunk key, s8 day flag, s8 groups[3]}, with the count in `g_spawnSlotCounts[stage]`. All slots have flag 0 in stages 1, 3, 8, 10 and 12. Dump: `work/hunt3/spawns.py`.

- Proof: `Sym_CheckDayParity` @0x8005C9A4, `Sym_SpawnOrSpy` @0x8005C7D4, `Sym_FindSlot` @0x8005C8AC (matched C), tables 0x80089A8C and 0x80089AC4.
- In game: only the stage 2 case (`work/shots/manifest.md`, grey-man.png); the empty stages were not walked.
- Question: [5](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: the fandom wiki (Gray Man, Sun Faces Heave) lists seven places where he appears and seven where he never does, Sun Faces Heave among them; the code agrees on every place but one: Sun Faces Heave (stage 11) can hold him.

</details>

## Rare sights

The rare events players hunt for are ordinary characters with a condition attached. Most of the conditions are the colour of your day so far: the game cuts [your graph point](#-how-a-day-becomes-a-point-on-the-graph) into a 3 by 3 grid and gives each part one of 8 colours, and some characters only come out, or only act differently, in one of them. The ones below were all seen in the emulator. To reach them quickly we wrote the day number, yesterday's point and, for most of them, the colour into memory; what the characters did on screen was the game's own code.

### ✅ The flying train: a pink day and a long dream

On odd-numbered days, Happy Town's slow train (a green locomotive and one wagon) starts rolling along its track once you have looked toward its spot on the rails from far away. Standing close to that spot and looking at it does nothing. This is the code behind the players' "it spawns when you look at a certain spot of the railroad".

If your day is pink at the moment it starts, the train does not vanish at the end of its run. It stops beside the opera singer's pillar, waits about 40 seconds, honks, sets off again and climbs into the sky. Pink is the graph's upper-right corner. The same pink colour brings four opera singers down to the foot of the pillar, so the two sights come together.

The catch is time. In the emulator the train took a little over three minutes after it started to reach the pillar, and a dream that starts in Happy Town ends before that. The dream has to start in a place with a longer clock, reach Happy Town early, on an odd day, with a pink day, and you have to wake the train quickly. On a day of any other colour, the code makes the train vanish just after the point where the pink train stops, near the same pillar (not filmed).

Status: 🎮 checked in the game: the odd day, the start square, the pink colour and a longer dream were forced, and the player was moved to look at the spot, then kept beside the train. The stop, the honk and the flight were the game's own.

<p>
<img src="img/game/flying-train-rolling.png" alt="Happy Town's slow train, a green locomotive and one wagon, rolling along the track in front of a wall of colourful tiles" width="32%">
<img src="img/game/flying-train-pillar.png" alt="The train reaching the opera singer's pillar, with the singer on top and the four pink-day singers standing on the ground in front" width="32%">
<img src="img/game/flying-train-sky.png" alt="The train in the sky above Happy Town's roofs, its wheels off the ground" width="32%">
</p>

<details><summary>Technical details</summary>

- Spawn: stage 4 (Happy Town), square (col 1, row 1), slot 3 (key 257, day flag 1: odd day numbers only), group 4: type 111, rule 1 (always), model 0, place 2. Record 111 (0x8008A594): wake mode 1 (in range), wake range +5 = 15, range +9 = 3, touch range 15, link -4 (stage 3, the Natural World), handler `Behavior_FlyingTrain` @0x80064E34 (C, `src/game/8005C508.c`).
- How "in range" works: `Entity_IsInRange` asks DreamSys slot 0x120 `DreamSys_TestPointAhead` for the point (record +5) << 11 units straight ahead of the player and tests, axis by axis (`Entity_IsWithinBox`), whether the character is within (record +9) << 11 of it. For the train: the spot 30,720 units ahead of you must land within 6,144 of it. Player position: DreamSys (0x80091530) +0x14 points to a block with x, y, z as s32 at +0x18, +0x1C, +0x20, copied at +0x38, +0x3C, +0x40 (the copy `Entity_GroundDistance` and `DreamSys_TestPointAhead` read).
- Handler: at tick +0xFC = 0 it asks DreamSys slot 0x200 (`GetDreamColor`); colour 5 (pink) sets +0x44 = 11. Normal run: `Behavior_TrainRun(.., 0x1E1, 0x884, -0x3C)`, forward at speed 0x3C, three turns of 1 degree per tick about y (rotation table `g_rotY1`, slot 0x44) in tick windows from 481 (first read as a horn; corrected while naming the code, 2026-10-16), sound 4 on its three voices at the start, and at tick 0x884 = 2,180 slot 0x160 (leave). Pink run: the same until tick 0x870 = 2,160, then slot 0x130 (stop); tick 0xA00 = 2,560 calls slot 0x12C (play an animation), with sound 5 on voice 0 from tick 0x9F6 to 0x9FF (the honk); from tick 0xA03 it rolls again with the leave tick moved to 0xFA0 = 4,000, and from tick 0xAF1 = 2,801 slot 0xCC with -0x20 every tick lifts it (PS1 y points down).
- Opera singers: stage 4 square (col 1, row 0), slot 0 (every day): group 0 is the singer on the pillar (type 38), group 28 is type 112 at places 137 to 140 with rule 17 (`SPECIAL_COLORS[7]` = 5, pink).
- In game: yes, interpreter (`work/hunt5/C/r5.log`). Forced: day +0x180 = 4 (day number 5), yesterday's point +0x196 = (-2, 7) (start on square (1, 1)), mood accumulator (6, 5) at each spot check (colour 5), time limit +0x134 = 200,000 at vsync 3600, player moved at vsync 3600 to 30,720 units behind the spot facing it, then put back every 10 vsyncs 14,000 units south of the train. Spawned at vsync 3488, woke at 3603, +0x44 = 11 from the first tick, stopped at tick 2,160 at (-59117, 0, -70763), 4,100 units from the pillar and next to the four type 112 singers; still from vsync 14,800 to 17,100; moving again at tick 2,642; y left 0 between ticks 2,787 and 2,837 and reached -9,088 at tick 3,085. Control `r4.log`: 12,000 units from the spot, facing it, it never woke in 13,000 vsyncs.
- Why it is rare: the train's ticks ran at about 0.175 per vsync, so the stop came about 11,200 vsyncs after it woke; a dream that started in Happy Town (120 s limit in `g_stageTimeLimits`) ended at vsync 12,091 in `r4.log`, about 8,600 vsyncs after it began. Measured in the emulator only; a console's frame rate may differ.
- Not seen: the normal train leaving at tick 2,180 and the pink train leaving at tick 4,000 (code only). Types 41 and 49 share its model (Happy Town squares (3, 3) and (5, 3)) and may be the fast even-day train players describe; not run.
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the fandom wiki (Train, Rare Events) already had the odd-day slow train woken by looking at a spot, its stop at the opera pillar, the honk and the flight on a pink chart point (x 4 to 9, y 3 to 9); we confirm it in the emulator and show why the dream is usually too short.

</details>

### ✅ The astronaut lands at the bar on a pink day

On even-numbered days a giant astronaut floats over Bright Moon Cottage, out and back, playing its trumpet. If your day is pink at the moment it appears, it turns out of its flight path, dives into the yard, walks to the cottage's bar and stays standing beside the counter, and the trumpet stops. On any other colour it never comes down.

Nothing in its code looks at the day number beyond odd or even, so the "days 200 to 300" players repeat is [a myth](#-myth-the-astronaut-lands-only-between-days-200-and-300): it landed on day 4. It appears once per dream. A dream that starts in the cottage probably cannot do it, since the cottage's own squares do not reach pink; the pink has to come from earlier in the dream (our guess from the squares' moods, not played).

Status: 🎮 checked in the game: the even day, the start square and the pink colour were forced; the turn, the dive, the walk to the bar and the stop were the game's own. With the natural colour it kept flying.

<p>
<img src="img/game/astronaut-dive.png" alt="The giant astronaut in a green sky over the cottage's roof, turned head-down at the start of its dive" width="49%">
<img src="img/game/astronaut-at-the-bar.png" alt="The astronaut standing beside the cottage's bar: bottle shelves and the counter on the left, the garden behind" width="49%">
</p>

<details><summary>Technical details</summary>

- Spawn: stage 0 (Bright Moon Cottage), square (col 0, row 4), mood (-5, -7), slot 4 (key 1024, day flag 2: even day numbers). Group 0: type 0, rule -1 (always, once per world build: the done flag is cleared by `Sym_LoadModels`), place 42. Record 0 (0x80089EA4): mood (0, 2), points 20, wake mode 0, touch range 2, link -13 (stage 12, Black Space, as players report), handler `Behavior_Astronaut` @0x8005E160.
- Handler: at its first tick it reads DreamSys slot 0x200 (`GetDreamColor`); 5 (pink) sets +0x44 = 100. Normal: trumpet every 10 ticks, `unkC4(+0x32)` for 1,200 ticks then `unkC4(-0x32)` for 1,200 ticks, and at tick 2,400 the counter restarts. Landing: forward for 100 ticks, then `unkBC(g_moveY64ZNeg64)` = (0, 0x40, -0x40) until tick 250 (the dive), sound only before tick 250, walk `unkC4(-0x32)` with the absolute rotation `g_rotYNeg120` (0, -120, 0) degrees from tick 261 to 567, then the absolute rotation `g_astronautBarPose` (50, -120, 30) degrees from tick 569.
- No day rule: the only day-of-year rules in the spawn code are the 30-day "month" rules 2 to 4 (another square of stage 0, another model); the [40-day cycle](#-the-40-day-texture-cycle) changes only textures; the ambience pick `Ambience_PickFamily` feeds only rule 7, used by one group of stage 3.
- In game: yes, interpreter. Pink runs `work/hunt5/C/r6-astro-pink.log`, `r14`, `r16`: colour point (8, 6) at vsync 3463, +0x44 = 100 from the first tick; y went from -9,216 to 384 between ticks 68 and 308, then it reached (-5104, 384, -5328) and stayed there from tick 588 to the end of the run (tick 866). Control `r6b-astro-ctl.log`: natural colour point (-6, -9), +0x44 = 0, y stayed -9,216, still flying at tick 508. Forced: day +0x180 = 3 (day number 4), yesterday's point +0x194 = (-5, -7), mood (6, 5) at spot checks, limit +0x134 = 200,000, camera kept 4,000 to 5,000 units behind it; in `r16` the player's height was set to the astronaut's minus 1,000 after its tick 600 to see the ground floor. In `r16` the camera touched it at vsync 3500 (instance score +20,000, no link); its landing had been decided at its first tick.
- Not played: the natural route (a link into the cottage's yard square with a pink day). The cottage squares carry moods from (-5, -7) to (1, 1), hence the guess above.
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the fandom wiki (Floating Astronaut, Rare Events) already gives even days, a pink chart point when it appears and no landing in a dream started in the cottage; we confirm the colour rule in the code and the emulator.

</details>

### 🧩 A red day fills a Happy Town street with gunmen

In Happy Town there is a street square where, on odd-numbered days, a single figure with a long gun stands and a big question mark floats in the sky. If the colour of your day so far is red when that square loads, the question mark is gone and eight more gunmen stand there, nine in all. Touching one flashes the screen red and sends you to another corner of Happy Town, a grey courtyard with a blue and white checkered floor.

Red is the bottom middle part of the colour grid: neither static nor dynamic, and downer. The easiest way in is to end a day on the point (2, 8), near the top of the graph. If the next day has an odd number, the dream starts on that very square, and the square's own mood plus the game's bonus for the last place visited pushes your point past the top edge. It flips to the bottom of the graph: red, and the gunmen come out.

Status: 🎮 checked in the game: only the day number and yesterday's point were written in; the red colour and the crowd came from the game itself.

<p>
<img src="img/game/gunmen-red-day.png" alt="Happy Town on a red day: six of the gunmen stand together on the patterned floor, in front of a striped wall" width="32%">
<img src="img/game/gunmen-question-mark.png" alt="The same square on a day of another colour: one gunman far away and a big question mark floating in the sky" width="32%">
<img src="img/game/gunman-link-courtyard.png" alt="Where touching a gunman sends you: a grey courtyard with a blue and white checkered floor, still in Happy Town" width="32%">
</p>

<details><summary>Technical details</summary>

Square: stage 4 (Happy Town), column 0 row 4 (key 0x400, `STG04\N1\M024.LBD`, mood (2, 8)). Its spawn slot 16 (day flag 1: odd day numbers only) lists groups 13 (type 51, rule always, place 81), 22 (type 54, model 1, place 84: the question mark) and 25 (type 113). `Sym_PickSlotVariant` swaps slot 16 for slot 21 when the stage is 4 and `GetDreamColor` (DreamSys vtable 0x200) returns 4; it compares the colour with the stage number, which happens to be 4. Slot 21 holds groups 13, 26 and 27; the last two are type 114 with rule 11 (`SPECIAL_COLORS[1]` = 4), 4 places each (129 to 136), and `Sym_SpawnGroup` spawns a group at each listed place. Types 51 and 114 use the same model (model 0 of the square's MML) and the same record (touch range 6, link -5 → stage ~(-5) = 4 with +8 = 1, so they link as soon as the player is close); only the handler differs (`Behavior_Type51` vs `Behavior_RedDayGunman`, which picks random animations).

- Colour at the start: the chunk accumulator holds only (2, 8); `Mood_CalcAxis` gives x = 2 + 2 / 3 = 2 and y = 8 + 8 / 3 = 10 (integer division), flipped to -9; `Mood_GetColor` bands (2, -9) to [1][0] of `g_moodColors` = 4 (red in lsddecomp's colour enum). The link flash uses `g_fadePalette[4]` = (255, 0, 0).
- Proof: `Sym_PickSlotVariant`, `Sym_SpawnGroup`, `Sym_CheckRule`, `Sym_CheckColorRule`, `Mood_GetColor`, `Mood_CalcAxis` @0x8005B66C, spawn dump `work/hunt3/spawns.txt`.
- In game: yes, interpreter (`work/hunt4/A/q12.lua`, breakpoints on `Sym_SpawnOrSpy`, `Sym_CheckRule`, `Sym_SpawnAtPlace`, `Mood_GetColor`). Forced: +0x180 = 4 (day number 5) and yesterday's point +0x196 = (2, 8) at vsync 2100, nothing else. Log `work/hunt4/A/ht1.log`: colour point (2, -9) at 3420, type 51 at place 81, then type 114 at places 129 to 136; six of them in one frame while turning (run `ht-pan`). Control `ht-ctl.log`: the chunk accumulator forced to (0, 0) at every slot check (colour 7): types 51 and 54 only, and the question mark floats over the square. Touch (`ht-red.log`): walking forward from 4400 met a gunman, red screen from 4700 to 5000, then the grey checkered courtyard at 5100, still stage 4.
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the community notes list "multiple gunmen" as a rare sight with unknown conditions, and the fandom wiki (Gunman) only covers Violence District's gunman; new here: the street square, the red-day rule and the nine figures.

</details>

### 🧩 Three minotaur rickshaws on a yellow day in Kyoto

Kyoto's rickshaw minotaur, a cart pulled by a brown bull-man, normally rolls alone down one street on odd-numbered days. If your day so far is yellow when that street loads, two more rickshaws join it, three in a row. Yellow is the graph's lower-left corner. Kyoto's own squares mostly lean the other way, so the yellow has to come from places or touches earlier that day.

Status: 🎮 checked in the game: the odd day, the start square and the yellow colour were forced; with the natural colour only one rickshaw came. Their link to the Natural World, which players report, is read in the code only.

<p>
<img src="img/game/minotaurs-yellow-day.png" alt="A Kyoto street on a yellow day: three rickshaw carts with big wheels rolling one behind the other" width="49%">
<img src="img/game/minotaur-alone.png" alt="The same street on a day of another colour: one rickshaw only" width="49%">
</p>

<details><summary>Technical details</summary>

- Spawn: stage 2 (Kyoto), square (col 0, row 2), mood (2, -1), slot 5 (key 512, day flag 1: odd day numbers). Group 14: type 21, rule 1 (always), place 35. Group 19: type 21, rule 10 (`SPECIAL_COLORS[0]` = 6, yellow), places 126 and 127. Both use model 0 of the square, so the extra two look the same. Record 21 (0x80089FF4): mood (-1, -2), wake mode 0, link -4 (stage 3, the Natural World), handler `Behavior_MinotaurRickshaw` (moves at -0x1E with the follow flag, sound every half animation loop).
- In game: yes, interpreter. Yellow runs `work/hunt5/C/r9-mino-yellow.log`, `r12-mino-yellow.log`: colour point (-8, -8) at vsync 3445, type 21 at places 35, 126 and 127, at (-89088, -200, -15360), (-93184, -200, -17408), (-91136, -200, -19456), all moving the same way. Control `r9b-mino-ctl.log`, `r12b-mino-ctl.log`: colour point (2, -1) (white), type 21 at place 35 only. Forced: day +0x180 = 4 (day number 5), yesterday's point +0x196 = (2, -1), mood (-6, -6) at each spot check in the yellow runs, limit raised, camera 5,000 units behind the first cart.
- Other Kyoto colour groups in the same table, not run: green (rule 15) puts 4 more of type 20 on square (3, 1); white (rule 13) 2 more of type 94; red (rule 11) type 110, [the geisha on the bridge](#-a-red-day-puts-a-geisha-on-a-kyoto-bridge).
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the fandom wiki (Minotaur, Rickshaw Minotaur) says several sometimes appear together and that the rickshaw comes on odd days and links to the Natural World; new here: the yellow-day rule and the street.

</details>

### 🆕 Three purple beasts on a yellow day: our best match for the special lions

Pit & Temple (stage 1) normally has one purple beast with a mane that stands still and, rarely, wakes up when you are near. On a yellow day three more of the same beast walk through that square in single file. In the code, coming close to any of them sends you elsewhere in Pit & Temple.

Players talk about "special lions near Temple Dojo". These four-legged maned beasts are our best match, by their look and their behaviour, but nothing in the game names them, so the match is not proven. The lions players see in the Natural World were not looked for.

Status: 🎮 checked in the game: the start square and the yellow colour were forced; the trio and its walk were the game's own. The link when you come close is read in the code only.

<p>
<img src="img/game/purple-beasts-trio.png" alt="Three purple maned beasts walking in single file on green ground, under a dark blue sky" width="49%">
<img src="img/game/purple-beast-front.png" alt="The first purple beast seen head-on, the other two hidden behind it" width="49%">
</p>

<details><summary>Technical details</summary>

- Spawn: stage 1, square (col 1, row 1), mood (0, -9), slot 1 (key 257, every day). Group 1: type 8, rule 1, place 24. Group 2: type 109, rule 10 (yellow), places 110 to 112. Both model 0 of the square (10 objects, 90 polygons, `work/hunt4/A/models.txt`).
- Record 8: wake mode 3 (in range, then 1 in 128 per tick), handler `Behavior_PurpleBeast` (idle animation, turns toward a fixed target). Record 109: wake mode 0, touch range 7, link -2 (stage 1) with +8 = 4 (links as soon as the player is within 4 << 9 = 2,048), handler `Behavior_YellowDayBeast` (walk animation and `unkC4(-10)` each tick).
- In game: yes, interpreter. Yellow runs `work/hunt5/C/r7-lions-yellow.log`, `r11-lions-yellow.log`, `r15-lions-side`: colour point (-8, -8) at vsync 3347, type 109 at (-3072, -200, -25600), (-3072, -200, -27648), (-3072, -200, -29696), all moving +z at about 2 units per vsync. Control `work/hunt4/A/lc.log` (colour blue): type 8 only. Forced: day +0x180 = 4, yesterday's point +0x196 = (0, -9), mood (-6, -6) at each spot check, camera 6,000 units from the first beast (9,000 behind and 2,500 to the side in `r15`).
- Kyoto square (4, 3), the other candidate, holds a geisha model, not a lion (see [the geisha](#-a-red-day-puts-a-geisha-on-a-kyoto-bridge)).
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the community notes mention "special lions near Temple Dojo" without a page we could open, the fandom wiki (Lion) covers only the two Natural World lions, and the LSD Revamped catalogue of Pit & Temple does not list this beast; the yellow-day trio is new, and its match to the lions is not proven.

</details>

### 🧩 A red day puts a geisha on a Kyoto bridge

On a red day, a geisha stands still on the red arched bridge of a Kyoto canal, in the same square where on even days another geisha walks down the street toward you. Players report a geisha "rarely standing still on a bridge" whose link goes to Black Space, and her code sends you there.

The walking one is the dangerous one: in one of her two scripts she turns, comes at you and ends the dream with her video.

Status: 🎮 checked in the game: the start square and the red colour were forced; she stood on the bridge for the whole run. Her link and the walking geisha's video are read in the code only.

<p>
<img src="img/game/geisha-red-bridge.png" alt="A figure in a long dark robe standing still on Kyoto's red arched bridge at night" width="49%">
<img src="img/game/geisha-even-street.png" alt="The even-day geisha in white walking down the same square's street, the red bridge on the right" width="49%">
</p>

<details><summary>Technical details</summary>

- Spawn: stage 2 (Kyoto), square (col 4, row 3), mood (-1, -1), slot 10 (key 772, every day). Group 2: type 11, rule 20 (even days), place 58. Group 17: type 110, rule 11 (`SPECIAL_COLORS[1]` = 4, red), place 121. Group 21: type 125, rule 21 (odd days), places 207 to 210. All model 0 of the square (5 objects, 88 polygons).
- Record 110: wake mode 0, touch range 5, link -13 (stage 12, Black Space in the community numbering), handler `Behavior_BridgeGeisha`: idle animation, and when the player comes within 0x800 a 45-tick animation, then 500 ticks of rest. Record 11: +7 = 8, +8 = 4 (video 3), handler `Behavior_WalkingGeisha`: at tick 1,560 a coin flip picks one of two scripts; in one, if DreamSys slot 0x100 answers non-zero between ticks 3,421 and 3,540, she turns, comes at the player at speed 0x78 and ends the dream with her video within 0x400. Record 125: 1 in 4 leaves at its first tick, the others walk slowly and leave at tick 3,600.
- In game: yes, interpreter. Red runs `work/hunt5/C/r8c-ky43-red.log`, `r13-ky43-red.log`: colour point (0, -8) at vsync 3465, type 110 at place 121, standing at (31744, -900, 29048) on the bridge (y -900, above the street's -200), still through the run; type 11 also spawned (even day). Forced: day +0x180 = 3 (day number 4), yesterday's point +0x194 = (-1, -1), mood (0, -6) at spot checks, camera 4,000 units from her. The walking geisha: `r8b-ky43-even.log`, no colour forced.
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the fandom wiki (Geisha) already says a geisha standing still on a bridge links to Black Space; new here: she comes on a red day, on that square.

</details>

## Characters and events

### 🧩 The hidden rules that decide which characters appear

Each place has a list of character groups, and each group has a rule checked when its spot loads. Some rules follow the day: every day, even or odd days, one day in three, or a 90-day cycle of three 30-day "months". Others follow your mood so far today: the group appears only if the colour of your day so far (one of 8 colours) matches. Some groups are marked "once": they can appear one time, then not again until the dream world is rebuilt (most likely each new dream). A group can stand at up to 4 places at once, and stage 4 has a spot where, in one mood colour, two such groups fill 8 places with the same character: that is the ["many gunmen" sighting, now seen in the game](#-a-red-day-fills-a-happy-town-street-with-gunmen). The "many minotaurs" work the same way: [three rickshaws on a yellow day in Kyoto](#-three-minotaur-rickshaws-on-a-yellow-day-in-kyoto).

The colour table players know from lsddecomp as `SPECIAL_COLORS` is part of these rules: for 8 of them it names the colour your day must be in for a group to come out (yellow, red, cyan, white, black, green, blue, pink, one each). It has nothing to do with links.

A character's look comes from the map square it stands on, not from its type: each square's file carries one to three models, and a group only says "model 0, 1 or 2 of this square". So a "rare version" of a character is often the same model with another behaviour swapped in by a day or colour rule. The Happy Town gunman is one (types 51 and 114). Another: in stage 1, a creature that normally stands alone comes as three on a yellow day, walking, and sends you elsewhere in stage 1 as soon as you come near ([now seen on screen](#-three-purple-beasts-on-a-yellow-day-our-best-match-for-the-special-lions)). All the sights of [Rare sights](#rare-sights) come from these rules or from a character that checks the colour itself.

Status: 📖 read in the code only, except the colour rules shown in [Rare sights](#rare-sights), which are checked in the game.

<details><summary>Technical details</summary>

A slot lists up to 3 groups; `Sym_SpawnSlot` tries each group in turn. Groups are 8-byte entries in `g_spawnGroups[stage]` (count `g_spawnGroupCounts[stage]`): {+0 done flag, +1 s8 rule, +2 model index, +3 entity type, +4 u8 places[4] ending at 0xFF}. `Sym_CheckRule` reads the rule; a negative rule only passes while the done flag is clear, and the flags are cleared by `Sym_LoadModels` @0x8005C508, called from `DreamRunner_Init` (the world constructor that also loads `ETC\DREAMER.TMD`); that this runs once per dream is likely, not measured. Rules: 0 and 1 always; 2, 3 and 4 pass when the 30-day month `(day - 1) / 30 + 1` equals 1, 2 or 3 plus a multiple of 3 (`Sym_CheckMonthRule`; the 13th month, days 361 to 365, never passes); 5 day % 3 == 0; 6 day % 3 != 0; 8 and 9 day % 3 == 1 or 2; 20 even days; 21 odd days; 7 `Ambience_IsEvenFamily` (bit 0 of `g_ambienceFamily`, picked by `Ambience_PickFamily` from a 16-entry table; its meaning is unproven); 10 to 17 (`Sym_CheckColorRule`) compare `g_ruleColors[rule]` (6, 4, 3, 7, 0, 2, 1, 5) with the current colour, DreamSys vtable 0x200 `DreamSys_GetDreamColor` = `DreamSys_ComputeDayPoint` banded by `Mood_GetColor` (< -3, -3..3, >= 4) into the 3x3 table `g_moodColors` = {6,7,2 / 4,7,1 / 3,0,5}. `Sym_SpawnGroup` spawns the type at every listed place (`Sym_SpawnAtPlace` per place). Stage 4, slot 16 (chunk 1024) switches to slot 21 when the colour is 4 (`Sym_PickSlotVariant`), whose groups 26 and 27 put type 114 on 8 places. Other colour groups: stage 1 type 109 (x3, colour 6), stage 2 types 110, 20 (x4), 21 (x2), 94 (x2), stage 3 types 119 to 122, stage 4 types 112 (x4, colour 5) and 113, stage 5 type 85 (x4, colour 3), stage 8 type 95 (x4, colour 1), stage 12 type 108 (colour 6). Full dump: `work/hunt3/spawns.txt`.

`SPECIAL_COLORS`: lsddecomp's symbol 0x80088D20 (s8[8], "gets compared against the current dream color") is `g_ruleColors + 10`, the part of the table that `Sym_CheckColorRule` @0x8005CD58 reads for rules 10 to 17 (`Sym_CheckRule` default branch): rule 10 → 6 (yellow), 11 → 4 (red), 12 → 3 (cyan), 13 → 7 (white), 14 → 0 (black), 15 → 2 (green), 16 → 1 (blue), 17 → 5 (pink), in lsddecomp's colour enum. The colour is that of the running day point when a square's characters are created.

Models: `Sym_SpawnGroup` gets the model with `chunk->vt->unk88(chunk, group.model)` on the square's LBD object (`Mml_Create`), then creates the entity with the group's type (`Sym_SpawnAtPlace` → `Entity_Create(type, ...)`). The square file's MML (offset at LBD +0x10) holds the models; every group's model index exists in its square's file (all 14 stages, `work/hunt4/A/mml.py`, list `work/hunt4/A/models.txt`). Stage 1, square (col 1, row 1), model 0 is shared by type 8 (rule always, place 24, wake mode 3, handler `Behavior_PurpleBeast` stands still) and type 109 (rule 10 = yellow, places 110 to 112, awake at spawn, link -2 → stage 1 with +8 = 4, handler `Behavior_YellowDayBeast` walks).

- Proof: `Sym_SpawnSlot`, `Sym_SpawnGroup`, `Sym_CheckRule`, `Sym_CheckMonthRule`, `Sym_CheckColorRule`, `Sym_PickSlotVariant`, `Sym_SpawnAtPlace` (all matched C), `DreamSys_GetDreamColor`, `Mood_GetColor`, tables 0x80089A44, 0x80089A7C, 0x80088D16, 0x80087E14.
- In game: the stage 4 colour rule ([the gunmen](#-a-red-day-fills-a-happy-town-street-with-gunmen)), the stage 2 rules 10 and 11 ([the minotaurs](#-three-minotaur-rickshaws-on-a-yellow-day-in-kyoto), [the geisha](#-a-red-day-puts-a-geisha-on-a-kyoto-bridge)) and the stage 4 rule 17 (the opera singers of [the flying train](#-the-flying-train-a-pink-day-and-a-long-dream)). The stage 1 yellow trio, first in the spawn log: interpreter, +0x180 = 4, yesterday's point +0x196 = (0, -9) (the dream starts on that square), chunk accumulator forced to (-6, -6) at each slot check (colour 6): `work/hunt4/A/ly.log` shows type 8 at place 24 and type 109 at places 110 to 112; control `lc.log` (natural colour blue): type 8 only. Hunt 5 brought them into view ([the purple beasts](#-three-purple-beasts-on-a-yellow-day-our-best-match-for-the-special-lions)); whether they are the community's "special lions" is not proven.
- Questions: [12](mysteries.md#events-and-hidden-content), [3](mysteries.md#graph-and-dream-start). Found 2026-10-15.
- Before us: the fandom wiki (Rare Events, Linking) tied rare events to zones of the chart and knew the A and B days, and lsddecomp noted that `SPECIAL_COLORS` is compared with the dream colour; new here: the full rule list (day cycles, 30-day months, "once" groups) and what the table does.

</details>

### 🧩 The character record: mood, points, waking up and leaving

Every character type, 130 of them, has a 16-byte record. It gives the mood logged when you touch it, the points it is worth (from -100,000 to +100,000), when it wakes up, when it leaves, how close you must be to touch it, and where it sends you or which video it plays. A character can wake up when you come near or when you walk away. Three types (7 and 8 in stage 1, 102 in stage 6) also need luck: near you, they have 1 chance in 128 per tick to wake. Type 102 is the only character of stage 6 and sends you to stage 12. The characters that end the dream on a video are type 13 (stage 2, always there), type 11 (stage 2, even days), type 47 (stage 4), type 79 (stage 9, rule "once") and type 89 (stage 5, rule "once"). Type 12 in stage 2 ends the dream without a video.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

Record `g_entityRecords + 16 * type`: +0/+1 s8 mood (returned whole by vtable 0x14C `Entity_GetRecord`), +2 s8 points / 1000 (0x150 `Entity_GetPoints`), +3 wake mode (`Entity_CheckWake`, 0x170: 0 at spawn via `Entity_Attach`, 1 in range, 2 out of range, 3 in range then `(rand() & 0x7F) == 0`, 4 `(rand() & 0x7F) == 0` anywhere), +4 sleep mode (`Entity_CheckSleep`: 1 in range, 2 out of range, >= 10 after `mode * 15` ticks), +5 wake range, +6 touch range (`Entity_CheckTouch`; negative also makes it face or follow the player through `Entity_FaceDreamer`), +7 link (0x154 `Entity_GetLinkStage`: v > 0 → stage v - 1, v < 0 → stage ~v, sent as message 10; when v < 0 and +8 != 0, `Entity_CheckLinkRadius` links as soon as the player is within +8 << 9), +8 video + 1 (0x158 `Entity_GetVideo`, message 11), +9 range parameter, +0xB another range (0x168), +0xC handler run each tick (`Entity_StartHandler` registers it). Message 11 senders: handlers of types 11 (`Behavior_WalkingGeisha`, video 3), 13 (`Behavior_Type13`, video 3), 47 (`Behavior_Type47`, 11 or 12, video 1), 79 (`Behavior_Type79`, video 0), 89 (`Behavior_Type89`, video 4); message 12 from type 12 (`Behavior_Type12`) and 47. Six `FILM\EVENTn.STR` paths sit 0x1C apart at 0x80085829; which video number maps to which file was not checked. Types 98 and 100 have mood (-10, -10), types 99 and 101 have (10, 10) and (9, 9); type 99 would be the dog (the loader's `i + 0x62` loop), and its record has no handler.

- Proof: behaviour vtable 0x80089AD4 (slots 0x14C to 0x17C), the functions above (matched C), dump `work/hunt3/recs.txt`.
- In game: only type 98 ([the Grey Man](#-the-grey-man-flips-your-graph-and-wipes-your-memories)).
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the wikis give chart values and links for many characters (Higashi's research on the fandom wiki, such as the Gray Man's (-10, -10)) and lsddecomp's DreamTimer.md the forced endings; new here: the 16-byte record itself, the wake and leave rules and the full list of video endings.

</details>

### 🧩 Signals from characters and objects

Characters and objects talk to the dream through a handful of signals. Touching one logs its mood for the graph, adds its points to the touch score and may keep a [flashback memory](#-how-flashback-memories-are-kept). Others send you to a fixed place, end the dream and queue their own video, or simply end the dream. Which characters send which signal is listed in [the character record](#-the-character-record-mood-points-waking-up-and-leaving), and when they appear in [the spawn rules](#-the-hidden-rules-that-decide-which-characters-appear). The [flying train](#-the-flying-train-a-pink-day-and-a-long-dream), [the astronaut](#-the-astronaut-lands-at-the-bar-on-a-pink-day) and [the purple beasts](#-three-purple-beasts-on-a-yellow-day-our-best-match-for-the-special-lions) are now matched on screen: their records name a place to send you to, and none of them ends the dream or plays a video. In flashback mode touching, event videos and forced endings do nothing.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

Entity events reach DreamSys through `DreamSys_OnEntityEvent` @0x8005B03C, ignored while +0x44 is set: 4 calls the entity's slot 0x38; 9 (touch) logs the entity mood (0x14C), adds its slot 0x150 to the instance score and may save a flashback; 10 links to the fixed stage given by slot 0x154 (through `Spawn_PickRandom` @0x8005BB30 with a negative argument); 11 ends the dream (timer = limit) and queues the entity's video (+0x168 = -1, +0x16A = slot 0x158), played by the category -1 branch of `Cine_GetPath` @0x80049334 (`Cine_GetEventPath` @0x80049270); 12 ends the dream. 9, 11 and 12 do nothing in flashback mode. These are the forced endings and event videos. Message 11 comes from the handlers of types 11, 13, 47, 79 and 89, message 12 from types 12 and 47 (record dump `work/hunt3/recs.txt`); the flying train is type 111, the astronaut type 0 and the purple beasts type 109 (matched on screen in hunt 5, see [Rare sights](#rare-sights)), and none of them sends message 11 or 12.

- Proof: `DreamSys_OnEntityEvent` @0x8005B03C, `Cine_GetEventPath` @0x80049270 (matched C), `DreamSys_ExecuteLink` @0x8005A928.
- In game: no.
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: lsddecomp's DreamTimer.md knew that some characters end the dream (lions, Ferris wheel, Kyoto old ladies) and the fandom wiki (Clips) lists the event videos; new here: the signal system behind them and that flashback mode ignores them.

</details>

## Textures

### 🧩 Glitch textures: a texture set that failed to load

After long sessions, players see places drawn with the wrong textures: grey walls covered in scraps of the menu and "me me me" letters. This is what happens when the game fails to load a place's texture set. It does not stop: it draws the place with whatever is left in video memory, and sets the dream to end 30 seconds later. Each new place that fails the same way pushes the end to 30 seconds after that link, which is why the dream timer seems to grow at every link in that state.

The load fails when the game finds no free memory for the textures. What uses that memory up over a long session was not found.

Status: 🎮 checked in the game, with the failure forced (the slow memory exhaustion behind it is read in the code only).

<p>
<img src="img/game/glitch-textures.png" alt="The first room with no texture set: grey walls, leftover menu letters and the words me me me" width="49%">
<img src="img/game/first-dream.png" alt="The same room drawn normally" width="49%">
</p>

<details><summary>Technical details</summary>

When a stage loads, `Place_Load` @0x80052F10 starts a texture-set loader (`Tix_Create`, class `g_tixVtbl`, 0x84 bytes) at stage +0x58 and sets +0x60. On every tick `Place_CheckTextureLoad` checks it: when the loader's +0x80 is set, it destroys the loader without applying anything and calls DreamSys slot 0x104 `DreamSys_SwapTimeLimit` with slot 0x108 `DreamSys_GetElapsedSeconds` + 0x1E, so the limit becomes elapsed + 30 s. The loader sets +0x80 only in its fail branch (`Tix_OnReadDone`), when the heap allocator `Heap_Alloc` returns 0 for the file list or the data buffer. That fits "after long sessions until power-off" (heap exhaustion or fragmentation); the allocator and the per-dream frees were not audited.

- Proof: `Place_Load`, `Place_CheckTextureLoad`, `Tix_Create`, `Tix_OnReadDone`, `Heap_Alloc`, `DreamSys_SwapTimeLimit` @0x80059328.
- In game: yes, forced. Interpreter (`work/hunt4/B-texfail.lua`): at the first check (vsync 2891, stage 0, day 1) the loader's +0x80 was written to 1. The tatami room came up untextured with leftover menu graphics, and the limit +0x134 read 450 (30 s x 15) instead of the normal 3600. Forced: the loader's failure flag only. Not tried: a real long session, and the community's "zero the frame counters" recipe.
- Question: [11](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: the fandom wiki (Textures, Data Analysis) and the LSD Revamped docs (Dynamic Analysis findings) saw it after long sessions or after editing the timers in RAM; new here: the failed texture load behind it and the 30-second end.

</details>

### ✅ The 40-day texture cycle

Every place has up to four texture sets, A to D. When a place loads, the game looks at where the day falls in a 40-day cycle. Days 1 to 10 always load set A. Days 11 to 20 load A or B, 21 to 30 one of A to C, 31 to 40 one of A to D, each equally likely. Then the cycle starts again at day 41. Since the day number returns to 1 after day 365, days 361 to 365 count as days 1 to 5 and always load set A.

Status: 🎮 checked in the game, with the draw forced: the same room wears set A on day 5 and set D on day 33.

![Step chart: days 1 to 10 of the cycle allow only set A, 11 to 20 A or B, 21 to 30 A to C, 31 to 40 A to D](img/chart-texture-cycle.svg)

<p>
<img src="img/game/textures-day-05.png" alt="The first room on day 5, early in the cycle: always texture set A" width="49%">
<img src="img/game/textures-day-33.png" alt="The same room on day 33 with set D drawn: photo collage textures" width="49%">
</p>

<details><summary>Technical details</summary>

Texture set: when a stage loads, `Place_Load` calls `Stage_PickTexturePath @0x80048EA0(stage, day number)`, which picks set `rand() % (((day - 1) % 40) / 10 + 1)` among the stage's `TEXA` to `TEXD.TIX` paths (path table of 0x1C-byte entries from 0x80081A04, `Stage_GetPathBase` @0x80048E2C). Days 1 to 10 of each 40-day cycle always load A, 11 to 20 A or B, 21 to 30 A to C, 31 to 40 A to D, each at random.

- Proof: `Stage_PickTexturePath` @0x80048EA0, `Stage_GetPathBase` @0x80048E2C, `Place_Load` @0x80052F10, rand wrapper `Rand_SeedAndNext` @0x80048CFC.
- In game: yes, forced. PCSX-Redux interpreter, same room and spot at the dream start: +0x180 = 4 (day 5) loads set A; +0x180 = 32 (day 33) with the rand state forced to 3 at `Stage_PickTexturePath` (rand % 4 = 3) loads set D, the photo collage. Day 33 rather than 35 because 35 is a special day. Log `work/shots/manifest.md`.
- Question: [9](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: the fandom wiki (Textures) and compu-lsd (Textures) already describe a 40-day cycle with a set added every 10 days; we confirm it in the code and the emulator, with each allowed set equally likely.

</details>

## Links between places

### 🆕 Fixed links are the navigation goals, and one can never be completed

The 30 hidden navigation goals behind the [Flashback score](#-what-unlocks-flashback-in-the-menu) are the game's fixed links: the first time you take each fixed link between two places, its goal is marked done. There are 49 such links, through walls and through passages, and together they mark 29 different goals. Goal 13 is not marked by any of them. So the 30th goal never completes, the 50,000,000 bonus for all 30 never pays out, and the navigation score tops out at 29,000,000.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

`Link_Find` @0x8005C150 matches the player's (chunk, tile) against a stage's link list and, when its sixth argument is not 0, sets `g_navFlags[y->flag] = 1` from the destination entry. Two callers pass 1: `Link_FindStatic` (wall touch, `DreamSys_LinkStatic` @0x8005A5D8; tables 0x80088748 counts, 0x80088710 lists, 0x80088664 destinations: 17 links, flags 0 to 12) and `Link_FindFacing` (`DreamSys_LinkFacing`, DreamSys vtable 0x1D0; tables 0x800889F0, 0x80088980, 0x80088820: 32 links, flags 14 to 29). The other two callers (`Link_FindExtra`, `Link_FindScripted`) pass 0. No other code writes the flags (`Nav_InitFlags` clears them, `Nav_CalcScore` counts 30 bytes and pays 50,000,000 only above 29,999,999). The union of the two tables lacks flag 13, so +0x188 tops out at 29,000,000. Script `work/hunt3/links.py`, output `links.txt`.

- Proof: `Link_Find`, `Link_FindStatic`, `Link_FindFacing`, `Nav_CalcScore` @0x8005BA7C, `Nav_InitFlags` @0x8005BA50 (matched C), the six tables above. The flag writer and the missing flag 13 were checked a second time by the main thread.
- In game: no (no fixed link was taken in the emulator).
- Question: [6](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: lsddecomp named 30 navigation challenges worth 1,000,000 each but not what they are; that they are the fixed links, and that goal 13 can never be completed, is new (nothing on the fandom wiki, compu-lsd or the LSD Revamped docs).

</details>

### 🔄 Where a random link sends you

Touching a wall can send you to another place. The game first looks for a fixed link for that wall; only if there is none, and random links are allowed at that moment, does it pick a place at random. It rolls a 6-sided die over the six main places (0 to 5 in its list). If the die names the place you are in, you go to the next one instead. So the place right after yours comes up 2 times in 6 and each of the other four 1 time in 6. Every random link is counted, and each one lowers the [flashback score](#-what-unlocks-flashback-in-the-menu) by 11,024.

Status: 📖 read in the code only.

![Bar chart, example from main stage 2: stage 3 has 2 chances in 6, stages 0, 1, 4 and 5 have 1 in 6 each](img/chart-link-odds.svg)

<details><summary>Technical details</summary>

Links: a wall touch (`DreamSys_OnWallTouch` @0x80058FAC, message 4, no transition running) tries the static tables first (`DreamSys_LinkStatic` @0x8005A5D8 → `Link_FindStatic` → `Link_Find` with 0x80088748, 0x80088710, 0x80088664) and links dynamically only if +0x124 is set (`DreamSys_SetLinkFlags`, vtable 0x18C). A dynamic link (`DreamSys_LinkDynamic` @0x8005A580 → `Spawn_PickRandom` @0x8005BB30) draws `rand() % 6` and moves a draw equal to the current stage to the next one (wrapping at 6), so from a main stage 0 to 5 the next stage is twice as likely (2/6) as each of the other four (1/6). It increments the counter at +0x600.

- Proof: `DreamSys_OnWallTouch` @0x80058FAC, `DreamSys_LinkStatic` @0x8005A5D8, `DreamSys_LinkDynamic` @0x8005A580, `Spawn_PickRandom` @0x8005BB30, `DreamSys_SetLinkFlags` @0x8005A1B0.
- In game: no.
- Question: [13](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: compu-lsd (Linking) said random links depend on how long the game and the place have been running, and the community notes (from lsddecomp) said any main place but yours, at random; the code rolls a 6-sided die and turns your own place into the next one, which doubles that place's odds.

</details>

### 🔄 Fixed links do not change with visits, but some depend on who showed up

A fixed link always leads to the same place: the game does not count visits and does not read the day when it looks one up. One extra list of walk-through links is switched on only in stages 3 and 11, or once a character of type 11, 56, 78 or 93 has appeared in that dream. Those characters follow [the day rules](#-the-hidden-rules-that-decide-which-characters-appear): type 11 is in stage 2 on even days, 56 in stage 5, 78 in stage 8 when the day is a multiple of 3, and 93 in stage 0 under the "once" rule. So when a fixed link seems to change from day to day, the day number is behind it through who appeared, not through visit counts. One more link routine, used only from stages 1, 3, 5, 9 and 12, sends you to stage 12 instead of its usual pick about half the time, depending on the dream timer; what you do to trigger it was not found.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

`Link_Find` compares only (chunk, tile) (tile -1 is a wildcard) and stores the match in `g_linkFromStage`, `g_linkFromIndex`, `g_linkToStage`, `g_linkToIndex`; it reads neither the day nor a counter. The extra list (`Link_FindExtra`, tables 0x80088B5C, 0x80088B24, 0x80088A80, run by `DreamSys_LinkExtra`, DreamSys vtable 0x1D8) is used only while `g_extraListOn` is set: `Sym_InitExtraList` sets it to (stage == 11 or stage == 3) at stage load, and `Sym_CheckExtraListType` sets it to 1 when a group of type 0xB, 0x38, 0x4E or 0x5D passes its rule in `Sym_SpawnGroup`. Also in the link code: `Link_PickFallStage` (vtable 0x1D4) only works from stages 1, 3, 5, 9 and 12 and, when the dream timer is odd, sends the player to stage 12 instead of the usual pick; which player action calls it was not traced.

- Proof: `Link_Find`, `Link_FindExtra`, `Sym_InitExtraList`, `Sym_CheckExtraListType`, `Link_PickFallStage` (matched C).
- In game: no.
- Question: [13](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the LSD Revamped docs (Tile Linking) say some tiles link elsewhere on different days or after a number of visits; the code keeps no visit count, and the day matters only through which characters appeared.

</details>

## Music

### ✅ A Clockwork Machines track that can never play

Each place picks one of its five music tracks at random when you arrive. Stage 9 (Clockwork Machines in the community's numbering) has a special rule: when the dice choose its third track, the game plays the fourth one instead. The third track is a distinct piece of music on the disc, so it is never heard. This matches the "unused Clockwork Machines track" players had spotted in the files.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

`Music_PickTrack` @0x80048F84 draws `rand() % 5` and returns the stage's path entry at `Stage_GetPathBase(stage) + 0x70` (BGA to BGE.SEQ, 0x1C bytes each). For stage 9 it turns 2 into 3, and a forced track 3 (`g_musicTrackOverride`) into 4, so `STG09\BGC.SEQ` (1,500 bytes, md5 0ab37f1d..., different from the four others) is never returned. `Place_Load` is its caller, when a stage loads.

- Proof: `Music_PickTrack` @0x80048F84, `Stage_GetPathBase` @0x80048E2C (file table 0x80081A04, s16 first-file index per stage at 0x800819E8: stage 9 = 474), so track 2 of stage 9 is the entry at 0x80084E84, `STG09\BGC.SEQ`.
- In game: no.
- Question: [14](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: TCRF (through the community notes) and the LSD Revamped docs (Unused Clockwork Machines track) already knew the track is never heard and blamed a tempo of 0 in the file; the code shows the game never even picks it.

</details>

### 🆕 A switch to pin the music that nobody pulls

Every dream picks one of 7 sound banks and one of 5 tracks at random. The code keeps two override switches that would force a chosen bank and a chosen track, very likely left for the developers to test the music. Nothing in the game ever sets them.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

`Music_PickBank` @0x80048D74 picks `rand() % 7` among the banks of `g_musicBanks` (`SND\AMBIENT`, `CARTOON`, `ELECTRO`, `ETHNOVA`, `HUMAN`, `LOVELY`, `STANDERD`) unless `g_musicBankOverride` is set; `Music_PickTrack` picks the track unless `g_musicTrackOverride` is set. The only writer of both is `Music_SetOverride` @0x80048D28, and no code calls it (no `jal`, no pointer to it in the executable).

- Proof: `Music_SetOverride`, `Music_PickBank`, `Music_PickTrack`, word scan of `SLPS_015.56` for 0x80048D28 (none).
- In game: no.
- Question: [14](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: nothing on it in the fandom wiki (Music), compu-lsd, the LSD Revamped docs (static analysis, music research) or lsddecomp; new.

</details>

## Memory card

### 🧩 Everything the game remembers fits in one block

All that the game carries from one day to the next lives in a single block of 1,792 bytes that starts with the letters "J01": the year, the day, the scores, your graph for all 365 days, the 30 navigation goals, the number of random links taken, and the flashback memories. It also keeps whether you have already seen [the video reel](#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film), and the SHAKE option of the menu. SHAKE is On in a new game; when it is on, the view dips and comes back up over each walking step, very likely the walking head bob (read in the code, not filmed). This block is what the memory card saves (next finding).

Status: 🎮 checked in the game (the block and its "J01" mark were found in memory, and the SHAKE byte follows the menu).

<img src="img/game/menu-shake.png" alt="The main menu with the SHAKE choice open: Off or On" width="60%">

<details><summary>Technical details</summary>

One `DreamSys` object at `0x80091530` (vtable `0x80087BDC`). Its persistent block runs from +0x178 to +0x878 (0x700 bytes, returned with that size by `DreamSys_GetSaveBlock` @0x8005A350, vtable slot 0x1B0) and starts with the magic `"J01"` written by `DreamSys_InitNewGame` @0x8005A258. Layout read so far: +0x17C year, +0x180 day (0-based), +0x184 unlock score, +0x188 navigation score, +0x18C instance score, +0x190 graph (365 pairs of s8), +0x5E0 30 navigation flags, +0x600 dynamic-link count, +0x684 500 bytes cleared at new game. Likely the memory card payload; not yet traced to the card code. (Since traced: the memory card finding below saves exactly this block. The flashback list at +0x46C to +0x5D8 also sits inside it.)

More fields: +0x5DF is the "video reel already seen" flag (`Graph_CheckReel`, see [the reel](#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film)). +0x678 is the SHAKE option: 1 at a new game (`DreamSys_InitNewGame`), the menu value is swapped in through DreamSys slot 0x19C `DreamSys_SwapShake` (called from `Menu_Close`, twice from `Menu_RefreshFromSave` and from `SaveMenu_Save`), and in a dream `DreamSys_TickStep` moves the camera object's +0x18 and +0x24 by -50 then +50 over the 4 ticks of a movement step when it is set. +0x5D8, +0x67C and +0x680 are cleared at a new game; no load from them, nor from +0x684 (500 bytes), was found, either from DreamSys or from the save block base (offsets 0x460, 0x504, 0x508, 0x50C). +0x878, right after the block and so not saved, is the "never saved or loaded" flag ([the save](#-how-the-memory-card-save-works)).

- Proof: `DreamSys_InitNewGame` @0x8005A258, `DreamSys_GetSaveBlock` @0x8005A350, `Nav_InitFlags` @0x8005BA50 (stores the +0x5E0 and +0x600 addresses in `g_navFlags` @0x8008ACB4, `g_dynamicLinkCount` @0x8008ACB8), graph reader `Graph_Draw` @0x80058404.
- In game: yes. Headless PCSX-Redux Lua probe (`work/hunt/dreamsys.lua`) at the title and in the first dream: vtable found once at 0x80091530, `"J01"` at +0x178, `g_navFlags` = 0x80091B10 (+0x5E0), `g_dynamicLinkCount` = 0x80091B30 (+0x600). SHAKE (`work/hunt4/B-run5.log`): menu SHAKE set to Off, then START; +0x678 went from 1 to 0 at vsync 3150, when the dream began. The camera dip itself was not filmed.
- Question: [15](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the fandom wiki (Data Analysis) had RAM addresses for the day and the chart (its day at 0x800916B0 is this block's +0x180), and its Game menu page says SHAKE toggles the head bob and a save keeps the chart and the day; new here: the whole block, its J01 mark and its layout.

</details>

### 🧩 How the memory card save works

Saving writes the whole memory block to the card under the file name `BISLPS-01556xxx`. The save title shows your day number in 3 digits. A game that has never been saved or loaded, a new one or one wiped by [the erase combo](#-select--triangle-in-the-pause-erases-your-game), saves to a new file with a blank comment: in the emulator, the first save of a new game became `BISLPS-01556-01`. After a save or a load, later saves keep that file's name (read in the code, not tried). The card driver itself has not been read.

Status: 🎮 partly checked: a save made in the emulator on day 42 carries the title "LSD a Day042"; the save screen itself does not show the day.

<img src="img/game/save-screen.png" alt="The save screen: Saving. Please wait." width="60%">

<details><summary>Technical details</summary>

Memory card: `Menu_Init` keeps the DreamSys save block (vtable 0x1B0) and its size 0x700 at +0xBC and +0xC0 of the save menu object and calls `SaveMenu_SetTitleDay @0x8004D6AC(day number)`, which writes the day as 3 characters (`Text_FormatNumber`) into the save title `g_cardTitle` @0x8008AA18 (0x8001149C) at +0x12. `SaveMenu_Save` @0x8004E0E4 saves through the card object's slot 0x78 with file name `g_cardFileName` @0x8008AA10 = `BISLPS-01556xxx`, that title, 0xD, 3, the block and its size; `SaveMenu_Load` @0x8004E1C4 loads through slot 0x74. DreamSys +0x878 (read by `DreamSys_IsNeverSaved`) is the "never saved or loaded" flag, not a broken-save marker: the DreamSys constructor `DreamSys_Init` sets it at power-on, `DreamSys_EndDay` @0x8005A41C sets it again with `DreamSys_InitNewGame` @0x8005A258 on an end of type 2 (the erase combo), and `DreamSys_ClearNeverSaved` (vtable 0x1A8) clears it when a card operation reports code 0x16 (`Menu_OnCardNotify`). While it is set, `SaveMenu_Save` zeroes the file name's first byte before the save and `Menu_CreateTitleLabel` copies `g_cardBlankComment` (19 full-width spaces) to title offset 0x18, the path every new game takes; a new game saved this way became `BISLPS-01556-01`, so a zeroed name gets a new numbered file. The card driver itself is not read.

- Proof: `Menu_Init` @0x8004D578, `SaveMenu_SetTitleDay` @0x8004D6AC, `SaveMenu_Save` @0x8004E0E4, `SaveMenu_Load` @0x8004E1C4, `Menu_CreateTitleLabel` @0x8004DB18, strings 0x80011464, 0x8001149C.
- In game: partly. With +0x180 = 41 (day 42), SAVE then an empty comment wrote card file `BISLPS-01556-01` with the title "ＬＳＤ　ａ　Ｄａｙ０４２" to the emulator's memory card (`~/.config/pcsx-redux/memcard1.mcd`); the screen shows only "Saving. Please wait.". That game had +0x878 set (a new game), so this save took the zeroed-name path. Not run: a save right after the erase combo (to keep the emulator's shared memory card as it is), and the card driver.
- Question: [15](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the fandom wiki (Game menu) says a save keeps the chart and the day and shows a save number next to the day; new here: the file name, the title carrying the day, and the new file a new game saves to.

</details>

## Randomness

### 🔄 The dice of the game

Every die roll on this page (special days, flashbacks, the Grey Man, textures, random links, music) comes from one number sequence, the standard one of the PlayStation's development kit. The game can restart that sequence from a new point only once, early, before the title screen takes input, and the starting value is leftover data from drawing the screen. In the emulator that leftover was 0, which means "do not restart", so the sequence ran on from power-on. Whether a real console leaves something else there was not measured.

Two things players tie to randomness are not random, or not from this game. The "type A" and "type B" days are odd and even day numbers: each spot where characters stand has a rule (every day, odd days, even days), and the Grey Man needs an even day. And the debug picture showing "World: 17464 0 36838" was not made by this game: the word "world" appears nowhere on the disc.

Status: 🎮 partly checked in the game (in the emulator only, not on a console; the A/B days and the "World" text are read in the code and the disc only).

<details><summary>Technical details</summary>

Random numbers: `rand` @0x80049480 is the PSY-Q LCG, state `g_randState` @0x8008AC68 (0 in the executable) times 0x41C64E6D plus 0x3039, returning bits 16 to 30. `srand` has one caller, `Rand_SeedAndNext @0x80048CFC(seed)`, which reseeds only when seed is not 0 and then draws. The only non-zero seed comes from `Scene_SeedRandom` @0x800260A4 (slot 0x40 of the scene class that `Scene_Init` builds with `ETC\DREAME5.TMD` and a new DreamSys): scratchpad word 0x1F800000 % 365. That scratchpad is a render work buffer (`Scene_DrawNode` hands it to `Render_SortModel`), so the seed is leftover render data, at most 728 seeds (-364 to 364, signed modulo) plus "no reseed".

- Proof: `rand` @0x80049480, `srand` @0x800494A8, `Rand_SeedAndNext` @0x80048CFC (matched C), `Scene_SeedRandom` @0x800260A4 (matched C), `Scene_Init` @0x80025FDC, `Scene_DrawNode` @0x80012064.
- In game: partly. Breakpoints showed `Scene_SeedRandom` run once, at vsync 1318 before the title input, with scratchpad word 0, so `srand` was never called; the rand state at the first special-day check was 0xA70427DF. Real hardware's scratchpad at that moment was not measured.
- A/B days: `Sym_CheckDayParity` @0x8005C9A4 reads each spawn slot's day flag (0 every day, 1 odd day numbers, 2 even ones), and spawn rules 20 and 21 of `Sym_CheckRule` test even and odd days; type A = odd day numbers, type B = even ones ([when the Grey Man can appear](#-when-the-grey-man-can-appear)).
- "World: 17464 0 36838": neither the executable (ASCII or full-width Shift-JIS) nor any byte of the disc image contains "world" in any case (stream search of the 2352-byte sectors, so a word split across a sector edge would be missed). 36838 is above 32767, so it is not a single PSY-Q `rand()` output either. The picture comes from another build or a tool.
- Question: [10](mysteries.md#days-textures-randomness). Found 2026-10-15.
- Before us: the fandom wiki (Generation, Linking) took the debug picture's "World" numbers for the dream seed, rerolled by every action, and compu-lsd (Linking) tied random links to timers; the code has one sequence that is almost never reseeded and no "World" text, while type A and B days as odd and even days were already known (fandom Flashback, compu-lsd Spy).

</details>

## Hidden and unused content

### 🆕 SELECT + TRIANGLE in the pause erases your game

Pause a dream with START, hold SELECT, then press TRIANGLE. The dream stops at once and the menu comes back on "Day 001": the day, the year, the score, the flashback memories and the navigation goals are wiped, with no warning and no confirmation. Your next save then goes to a new file, as for a brand new game (read in the code). The [video reel](#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film) can be seen again after that.

It is the only hidden button input in the game. Every piece of code that reacts to the pad was read: each one reacts to a single press at a time and none remembers earlier presses, so no typed cheat code can exist. The pause code also holds a second exit, a quit that does not count the day, but no button leads to it: it is dead code, maybe a developer shortcut whose button was removed.

Status: 🎮 checked in the game (the wipe; the new save file and the dead exit are read in the code only).

<p>
<img src="img/game/erase-combo-pause.png" alt="The pause on day 41, just before the combo: a small red Pause at the top of the tatami room" width="49%">
<img src="img/game/erase-combo-day-001.png" alt="Right after SELECT held and TRIANGLE: the menu back on Day 001" width="49%">
</p>

<details><summary>Technical details</summary>

The pad object (`Pad_New`, vtable `0x8006D370`) reads `PadRead` once per frame (`Pad_Read`) and turns 16 buttons into event codes (`Pad_SendEvents`): code = state + button index, state 2 = held, 0x12 = pressed this frame, 0x22 = released this frame. Button order (`Pad_InitButtons`, table `g_padButtonMasks`): 0 UP, 1 DOWN, 2 LEFT, 3 RIGHT, 4 TRIANGLE, 5 CROSS, 6 SQUARE, 7 CIRCLE, 8 and 9 L3 and R3, 10 SELECT, 11 to 14 the shoulder buttons, 15 START. The codes go to listeners through the base class send (`Object_Notify`, listener slot 0x38).

The dream stage class (vtable `0x80087034`) has one pad handler, `Place_OnPad` @0x80053358 (slot 0x58), with four cases: 33 = START pressed (slot 0x74, pause toggle; the pause window `Place_UpdatePause`, slot 0xD0, shows "Pause" from `g_pauseText`), 12 = SELECT held (slot 0xC0 `Place_ArmExit`: arms the exit, +0x84 = 1, only while the pause is open, +0x80 != 0, and the stage is in its normal state, +0x20 == 0), 22 = TRIANGLE pressed (slot 0xC8 `Place_ConfirmExit`: when armed, closes the pause and sends code 0xD to the dream runner), 44 = SELECT released (slot 0xC4 `Place_DisarmExit`: disarms). The runner `DreamRunner_OnStageMessage` @0x80049EB4 turns 0xD into `DreamSys_EndDay(2)` @0x8005A41C, which calls `DreamSys_InitNewGame` @0x8005A258 (year, day, three scores, flashback count, navigation flags, the reel flag +0x5DF and 500 bytes at +0x684 cleared; the graph at +0x190 is left in place) and sets +0x878, the "never saved or loaded" flag a new game also has ([the save](#-how-the-memory-card-save-works)). Arming needs SELECT held for at least one frame after its press frame, which is why SELECT+START and single buttons did nothing in the first tries (`work/hunt3/run2.log`).

The second exit: slot 0xCC `Place_ExitNoRecord` sends code 0xC (`DreamSys_EndDay(1)`: day restored, nothing recorded). `Place_OnPad` has no case for it, the address 0x8005426C appears once in the executable (the vtable, at 0x80087100), no other vtable inherits it, and the 32 functions that load a slot 0xCC call it on other classes with arguments, not on the stage.

Other pad handlers, all read (C scan for case and compare values in the pad ranges, plus the functions still in assembly at the time): the title and menu class `MenuScreen_OnPad` (UP, DOWN, START, CROSS, CIRCLE; 4 vtables), the yes/no box `Card_OnPad` (CIRCLE, CROSS), the comment keyboard `CommentObject_OnKey` (directions, CIRCLE, CROSS, SELECT, two shoulder buttons for the character page) and the walking controls `DreamSys_OnPad` @0x80058C58 (UP and DOWN walk, LEFT and RIGHT turn, TRIANGLE and SQUARE set +0x88, CROSS while walking calls slot 0x184, the shoulder buttons set +0x90 or +0xA0, CIRCLE sets +0x74). No handler tests a pad mask directly and no code stores past codes. The exact roles of the shoulder buttons were not tested.

- Proof: `Pad_SendEvents`, `Pad_InitButtons`, `Place_OnPad` (matched C), `Place_ArmExit`, `Place_DisarmExit`, `Place_ConfirmExit`, `Place_ExitNoRecord`, `DreamRunner_OnStageMessage`, `DreamSys_EndDay`, `DreamSys_InitNewGame`, the handlers above.
- In game: yes (`work/hunt4/B-run1.log`, dynarec): day +0x180 = 40 and score +0x184 = 5,000,000 written at vsync 2100, the dream started normally; START at 3800 (pause shown), SELECT held from 3900 for 150 vsyncs, TRIANGLE at 3960. RAM at 3964: day 0, year 0, score 0; the menu showed "Day 001" from vsync 4100 (that capture is pixel-identical to the Day 001 menu picture above, which is reused). Forced: the day and the score, to make the wipe visible; the input and its effect are the game's. Not run: a save after the wipe (to keep the emulator's shared memory card as it is).
- Questions: [14](mysteries.md#events-and-hidden-content), [15](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: nothing on it in the fandom wiki (Game menu and the pages above), compu-lsd, the LSD Revamped docs or a web search; new.

</details>

### ✅ The dog that never loads

The disc holds a model for a dog next to the Grey Man's. The loader is written to load both, but it stops after the first one, and nothing else in the game asks for the dog. So the dog is never loaded and cannot appear. The character list even keeps a slot for it, right after the Grey Man's, with a bright mood and no behaviour at all.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

`ETC\SYMDOG.MOM` is never loaded: `Sym_LoadModels` @0x8005C508 loads `ETC\SYMSPY.MOM`, writes the dog's path into its load descriptor and leaves its loop after one pass (`beqz s1` after `s1++`). No other code references the dog path `D_8001187C`. The spy objects are created as type `i + 0x62` (`Sym_InitStage`), so the dog would be type 99, right after the Grey Man's 98; record 99 has mood (10, 10) and no handler (`work/hunt3/recs.txt`).

- Proof: `Sym_LoadModels` @0x8005C508, `D_8001187C`, `Sym_InitStage`, record 99 at `g_entityRecords` + 0x630.
- In game: no.
- Question: [14](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: TCRF, the fandom wiki (Unused Content) and the LSD Revamped catalogue (General Objects) already knew `SYMDOG.MOM` as an unused dog with two animations; we confirm in the code why it never loads.

</details>

### 🧩 What the game never asks for

The executable names every file on the disc except three: a second Asmik logo picture, a second "ETC" picture, and a 62 MB dummy video that fills the end of the disc. The scene code also keeps an empty slot for a mode that the title screen can never choose. No debug menu, test mode or cheat sequence turned up in what we read, and the code has no path to a WC room file: rooms live inside the stage chunk files.

Status: 📖 read in the code only.

<details><summary>Technical details</summary>

All printable paths in `SLPS_015.56` were compared to the 685 files of the disc (patched English v1): every named path exists, and only `ETC\ASMKLOG.TIM` (153,620 bytes, dated 1997-05-20, same size as `ASMKLOGO.TIM`), `ETC\ETC2.TIM` (30,784 bytes) and `ZDUMMY\ZDUMMY.STR` (61,937,664 bytes) are never named. The `CARD\*.TIM` pictures are built from `CARD\` plus the names at 0x8008AA34 and are used. The scene loop `App_Run` calls slot 0x5C when the title returns 1; slot 0x5C is the empty `func_80026690`, and the title routine `Scene_RunTitle` only returns 0 or 2. The scene settings `g_sceneSettings` passed by `main` (0x13, 0, 1, 1, 1, 1) turn the logos (+0xC), videos (+0x8) and title (+0x10) on; flipping them is the closest thing to a dev switch found. The pad handlers of the title and menu screens were read since: none keeps a sequence ([the erase combo](#-select--triangle-in-the-pause-erases-your-game)).

- Proof: `App_Run`, `func_80026690`, `Scene_RunTitle`, `g_sceneSettings`, `main` @0x800118DC, string scan (`work/hunt3`, inline scripts).
- In game: no.
- Question: [14](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the fandom wiki (Data Analysis, Unused Content) knew `ZDUMMY.STR` as disc filler, the Japanese Asmik logo and the cut WC room, and TCRF (through the community notes) a debug menu in a 1997 demo; new here: the executable never names these three files, and no WC room file or debug menu turned up.

</details>

## Myths checked

Things players repeat about the game, checked against the code and, when possible, in the emulator.

### ❌ Myth: a hidden ending if the graph is full

The myth: fill every cell of the graph and you get a secret ending.

Verdict: false. The ending video plays only [when a year closes](#-the-ending-plays-when-a-year-closes-not-on-day-365). No code counts how many cells you have filled: the graph is read only to pick where tomorrow starts and by the graph screen, which [shows 100 days at most](#-the-graph-screen-only-shows-your-last-100-days) anyway. The one secret tied to the graph is [the video reel](#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film), and it needs four cells, not a full graph.

Status: 📖 read in the code only (the reel itself is checked in the game).

<details><summary>Technical details</summary>

`ETC\ENDING.STR` is reached only through scene slot 0x64, when `Scene_RunDream` sees day number 1 and a year above 0. The graph points at +0x190 are read by `DreamSys_GetPreviousPoint` @0x8005B1F4 (yesterday's point, for `DreamSys_ChooseStart` @0x8005A508), by the graph screen `Graph_Draw` and by the reel check `Graph_CheckReel`; none counts cells.

- Proof: `Scene_RunDream`, `Scene_PlayEnding`, `DreamSys_GetPreviousPoint`, `Graph_Draw`, `Graph_CheckReel`.
- In game: no (the reel is, see its entry).
- Found 2026-10-15.
- Before us: a rumour listed by compu-lsd (through the community notes); the fandom wiki (Chart) already argued the chart can never be full, and the code shows no such ending exists.

</details>

### ❌ Myth: no Grey Man after day 365

The myth: once you pass day 365, the Grey Man never shows up again.

Verdict: false. His check only looks at the day number you see, 1 to 365, never at the hidden year. In the emulator he stood under the torii of the canal place on day 4 of the second year, exactly as in the first.

Status: 🎮 checked in the game, with the die forced.

<img src="img/game/grey-man-year-2.png" alt="The Grey Man on the path under the torii, on day 4 of the second year" width="60%">

<details><summary>Technical details</summary>

`Sym_SpawnOrSpy` @0x8005C7D4 gets the day number from DreamSys slot 0x1A0 `DreamSys_GetDayNumber`, which is day + 1 and ignores the year; the rest of its test (spot rule, stage not 0, 1 in 12, even day) has no year term, and `Sym_LoadModels` loads `ETC\SYMSPY.MOM` every dream.

- Proof: `Sym_SpawnOrSpy`, `DreamSys_GetDayNumber` @0x8005A2E4, `Sym_LoadModels` @0x8005C508.
- In game: yes (interpreter, `work/hunt4/B-run2.log`): year +0x17C = 1 and day +0x180 = 3 (day number 4 of the second year), yesterday's point (-3, 1) for stage 2, rand state 0 at each `Sym_SpawnOrSpy` entry (3460, 3472, 3481, all with day number 4). He stood on the path under the torii (capture at 4300) and reached the player at 4399, when the flashback eraser ran. Forced: year, day, yesterday's point and the rand state, the same setup as the year-one picture of [when the Grey Man can appear](#-when-the-grey-man-can-appear).
- Question: [5](mysteries.md#grey-man-and-flashback). Found 2026-10-15.
- Before us: a rumour listed by compu-lsd (through the community notes); the code and the emulator prove it false.

</details>

### ❌ Myth: over 500 music tracks

The myth: the game has more than 500 different music tracks.

Verdict: false: 462 at most, and some picks are silence. Each dream picks one of 7 sound banks, and each place you enter picks one of its 5 melodies, played on that bank. The 14 places hold 70 melody files, but three of them are the same tiny file that plays one inaudible note and stops, and one [Clockwork Machines melody never plays](#-a-clockwork-machines-track-that-can-never-play). That leaves 66 real melodies, times 7 banks: 462. In three places (stages 0, 3 and 5), one place load in five plays no music at all.

Status: 📖 read in the code and the disc files (not heard: the emulator runs without sound).

<details><summary>Technical details</summary>

Bank: `rand() % 7` among `SND\AMBIENT`, `CARTOON`, `ELECTRO`, `ETHNOVA`, `HUMAN`, `LOVELY`, `STANDERD`, once per dream (`Music_PickBank`, called by the world constructor `DreamRunner_Init`). Melody: `rand() % 5` among the place's `BGA` to `BGE.SEQ`, at each place load (`Music_PickTrack`, from `Place_Load`). No other random step touches the music in those functions. On the disc: 70 sequence files, 68 different; `STG00\BGD.SEQ`, `STG03\BGD.SEQ` and `STG05\BGC.SEQ` are the same 38-byte file (one note at velocity 1, then the end), and `STG09\BGC.SEQ` is never returned. 66 melodies x 7 banks = 462.

- Proof: `Music_PickBank`, `Music_PickTrack`, `DreamRunner_Init`, `Place_Load`; hashes in `work/hunt4/B-seq.txt`, read in place by `work/hunt4/B-tools/isohash.py`.
- In game: no.
- Question: [14](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: a rumour listed by compu-lsd (through the community notes); the fandom wiki (Music) counts 490 tracks with 28 silent ones, and the code and the disc give 462 at most.

</details>

### ❌ Myth: the astronaut lands only between days 200 and 300

The myth: the giant astronaut lands at Bright Moon Cottage's bar only on days 200 to 300.

Verdict: false. What decides the landing is the colour of your day when the astronaut appears: pink, and only on even days. Its code never looks at the day number beyond odd or even, and in the emulator it landed at the bar on day 4. See [the astronaut at the bar](#-the-astronaut-lands-at-the-bar-on-a-pink-day).

Status: 🎮 checked in the game, with the day and the colour forced.

<details><summary>Technical details</summary>

Type 0's group (stage 0, slot 4) has day flag 2 (even days) and rule -1 (once, no day term); its handler `Behavior_Astronaut` reads only the colour (DreamSys slot 0x200) at its first tick. The only day-of-year rules in the spawn code are the 30-day month rules 2 to 4 (`Sym_CheckMonthRule`), used by another square of stage 0 with another model.

- Proof: `Behavior_Astronaut`, `Sym_CheckRule`, `Sym_CheckMonthRule`, spawn dump `work/hunt3/spawns.txt`.
- In game: yes (interpreter, `work/hunt5/C/r16`): day +0x180 = 3 (day number 4), pink forced, standing at the bar from tick 588.
- Question: [12](mysteries.md#events-and-hidden-content). Found 2026-10-15.
- Before us: the claim comes from the LSD Revamped docs (Giant Astronaut bar event); the fandom wiki (Floating Astronaut) already showed a landing on day 26, and the code and the emulator prove it false.

</details>

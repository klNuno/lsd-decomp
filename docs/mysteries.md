# Open questions

Fifteen questions the code can settle. Each one closes with an entry in [discoveries.md](discoveries.md) that cites its function and address. Status of what the community already knows: [community-knowledge.md](community-knowledge.md).

## Graph and dream start

- [x] 1. Is the "last event" term of each graph axis `last / 3` (lsddecomp's reading) or the community's five-step table? They only differ at plus or minus 9. Answered: `last / 3`, checked in the emulator ([how a day becomes a point](discoveries.md#how-a-day-becomes-a-point-on-the-graph)).
- [ ] 2. How does `GetStageChunkFromMood` pick the starting chunk? What does the sentinel `{9,0}` mean, and why do some results land outside the graph? Partly answered: the first area whose mood equals yesterday's point, else place 1 ([how the graph picks where tomorrow starts](discoveries.md#how-the-graph-picks-where-tomorrow-starts)); the sentinel is not explained.
- [ ] 3. What is the `SPECIAL_COLORS` table for?
- [ ] 4. What triggers the "video reel", when four graph cells blink green?

## Grey Man and Flashback

- [x] 5. Grey Man spawn logic: day parity, odds per zone, timers. Does he always erase the flashbacks? Answered: even days, 1 in 12 on a spot left empty, never in six places, he leaves after a fixed time, and every touch erases them ([when](discoveries.md#when-the-grey-man-can-appear), [where](discoveries.md#who-can-meet-the-grey-man-and-where), [what he does](discoveries.md#the-grey-man-flips-your-graph-and-wipes-your-memories)).
- [x] 6. Which total score unlocks Flashback? What are the 30 "navigation challenges", and how is the "instance" score earned? Answered: above 9,999,999 ([the unlock](discoveries.md#what-unlocks-flashback-in-the-menu)); the 30 goals are the fixed links, one unreachable ([the goals](discoveries.md#fixed-links-are-the-navigation-goals-and-one-can-never-be-completed)); the instance score comes from touching characters ([the records](discoveries.md#the-character-record-mood-points-waking-up-and-leaving)).

## Days, textures, randomness

- [x] 7. The full list of the 42 special days and their videos. Why do players see 2 variants when the code seems to draw from 6? Answered: [the 42 days](discoveries.md#the-42-special-days); 2 videos and 4 still pictures per category ([what a special day shows](discoveries.md#what-a-special-day-shows)).
- [x] 8. What happens on day 365, then from year 1 on? Does the year counter change anything? Answered: the ending plays when the year closes ([the ending](discoveries.md#the-ending-plays-when-a-year-closes-not-on-day-365)); the year only changes the first dream of the next year, through a bug ([the wrong data](discoveries.md#the-first-dream-of-a-new-year-starts-from-the-wrong-data)).
- [x] 9. How is the texture set chosen (a 10/20/30/40-day cycle?), and what is `TEXD` really? Answered: a 40-day cycle, set D is one more random texture set ([the cycle](discoveries.md#the-40-day-texture-cycle)).
- [ ] 10. What is the seed "World: a b c"? How is `rand()` seeded? Where do the A/B day patterns come from? Partly answered: `rand()` is almost never reseeded ([the dice](discoveries.md#the-dice-of-the-game)); the "World" seed and the A/B patterns are not explained.
- [ ] 11. What causes the glitch textures, and why does the timer grow at every link in that state?

## Events and hidden content

- [ ] 12. Exact conditions of each rare event: flying train, astronaut bar, special lions, multiple gunmen and minotaurs. Partly answered: the spawn rules and character records are listed ([spawn rules](discoveries.md#the-hidden-rules-that-decide-which-characters-appear), [records](discoveries.md#the-character-record-mood-points-waking-up-and-leaving)); no type is matched yet to the train, astronaut or lions on screen.
- [x] 13. Do the static link variations per tile depend on the day or on the number of visits? Answered: neither; some extra links depend on which characters appeared ([fixed links](discoveries.md#fixed-links-do-not-change-with-visits-but-some-depend-on-who-showed-up)).
- [x] 14. Is there reachable code for the unused dog, the WC room or a debug menu? Is `ENDING.STR` referenced anywhere but day 365? Answered: [the dog](discoveries.md#the-dog-that-never-loads) never loads; no WC room file and no debug menu in what was read ([never asked for](discoveries.md#what-the-game-never-asks-for)); `ENDING.STR` plays only when a year closes ([the ending](discoveries.md#the-ending-plays-when-a-year-closes-not-on-day-365)).
- [ ] 15. The memory card save format, and the fields of `DreamSys` still unknown. Partly answered: [the save block](discoveries.md#everything-the-game-remembers-fits-in-one-block) and [the save](discoveries.md#how-the-memory-card-save-works); the card driver and some fields are still unread.

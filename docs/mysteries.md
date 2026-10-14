# Open questions

Fifteen questions the code can settle. Each one closes with an entry in [discoveries.md](discoveries.md) that cites its function and address. Status of what the community already knows: [community-knowledge.md](community-knowledge.md).

## Graph and dream start

- [ ] 1. Is the "last event" term of each graph axis `last / 3` (lsddecomp's reading) or the community's five-step table? They only differ at plus or minus 9.
- [ ] 2. How does `GetStageChunkFromMood` pick the starting chunk? What does the sentinel `{9,0}` mean, and why do some results land outside the graph?
- [ ] 3. What is the `SPECIAL_COLORS` table for?
- [ ] 4. What triggers the "video reel", when four graph cells blink green?

## Grey Man and Flashback

- [ ] 5. Grey Man spawn logic: day parity, odds per zone, timers. Does he always erase the flashbacks?
- [ ] 6. Which total score unlocks Flashback? What are the 30 "navigation challenges", and how is the "instance" score earned?

## Days, textures, randomness

- [ ] 7. The full list of the 42 special days and their videos. Why do players see 2 variants when the code seems to draw from 6?
- [ ] 8. What happens on day 365, then from year 1 on? Does the year counter change anything?
- [ ] 9. How is the texture set chosen (a 10/20/30/40-day cycle?), and what is `TEXD` really?
- [ ] 10. What is the seed "World: a b c"? How is `rand()` seeded? Where do the A/B day patterns come from?
- [ ] 11. What causes the glitch textures, and why does the timer grow at every link in that state?

## Events and hidden content

- [ ] 12. Exact conditions of each rare event: flying train, astronaut bar, special lions, multiple gunmen and minotaurs.
- [ ] 13. Do the static link variations per tile depend on the day or on the number of visits?
- [ ] 14. Is there reachable code for the unused dog, the WC room or a debug menu? Is `ENDING.STR` referenced anywhere but day 365?
- [ ] 15. The memory card save format, and the fields of `DreamSys` still unknown.

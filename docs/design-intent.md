# What the code tells us about what the creators meant

This page reads the whole game as a design. It is written for a player, not a programmer. Every part keeps the code, the creators' words and our reading apart, and says how sure the reading is:

- **The code says**: a fact read in the game's program, with a link to the finding that proves it.
- **The creators said**: a quote or a close paraphrase of the people who made the game, with the page it comes from.
- **Our reading**: what we think the choice means. A reading is an argument, never a fact.
- **How sure**: how much weight the reading can bear.

The proof of every code fact (function name, address, whether it was checked in the emulator) is in [the findings](discoveries.md) and in [the engine pages](engine/README.md). Japanese sources are quoted in our own translation.

## Summary in ten lines

1. The game has rules everywhere. Many apparent surprises depend on the day number, the place and the accumulated mood, alongside dice rolls.
2. The graph is a diary of moods, one point per day, and yesterday's point picks the place where you wake today. The manual tells you to work out that rule yourself.
3. Walking into a wall to change place is the founding idea. Osamu Sato says it came from crashing in racing games, and the code keeps it simple: marked walls, six main places, one die.
4. The length of a dream is fixed the moment it starts, by the starting place. The manual describes it the other way round for the Violence District.
5. Your mood during a dream gives the day one of 8 colours, and the colour quietly unlocks rare sights. Nothing on screen explains it.
6. The Grey Man erases your flashbacks and throws the day's point to the other side of the graph. He erases nothing else. His record sits at one corner past the edge of the graph; a dog that was cut sits at the opposite corner.
7. Videos and diary pages replace the dream on 41 fixed days, 35 of them in the first 204 days of the year.
8. After day 365 the credits play, a hidden year counter goes up, and the same year starts again. No secret ending exists.
9. The game keeps a hidden score with 30 goals for a "non-game", and one goal can never be reached. No screen ever shows this score.
10. Our reading is that the cut and unused parts (a dog, a quit that skips the day, spare room in the save) may reflect features left unfinished, not a hidden second game; the code does not explain why development stopped there.

## Who said what, and where

The creators' words used on this page come from pages we opened ourselves:

| Short name | What it is | URL |
| --- | --- | --- |
| RBMA 2017 | Interview of Osamu Sato, Red Bull Music Academy Daily | https://daily.redbullmusicacademy.com/2017/11/osamu-sato-interview/ |
| Vice 2015 | Interview of Osamu Sato | https://www.vice.com/en_us/article/d734ja/the-most-elusive-video-game-creator |
| Gata | Interview of Osamu Sato, Gata Magazine | https://gatamagazine.com/articles/art/lsd-is-groovy-an-interview-with-osamu-sato |
| 1998 site | The developers' own page for the game, archived in February 1998 (Japanese) | https://web.archive.org/web/19980221074326/http://compu-lsd.com/lsd/index.html |
| Manual | The game comes with eight square cards. Cards 1 to 6 carry the manual on their back, transcribed in Japanese by the Osamu Sato Wiki; card 7 carries the credits and card 8 an advert for the soundtrack and the book (the wiki does not transcribe them). We read the cards on the wiki's scans and checked every passage quoted here against them | https://compu-lsd.com/w/LSD_Manual_Cards/Transcription and https://compu-lsd.com/w/LSD_Manual_Cards |
| G8 1999 | The page of Creation Gallery G8 (Tokyo) for its 1999 exhibition "LSD: Lovely Sweet Dream", which credits the show's planning to Osamu Sato and OSD (Japanese) | https://scrapbox.io/recruit-art-center/LSD%E2%94%80%E3%83%A9%E3%83%96%E3%83%AA%E3%83%BC%E3%83%BB%E3%82%B9%E3%82%A4%E3%83%BC%E3%83%88%E3%83%BB%E3%83%89%E3%83%AA%E3%83%BC%E3%83%A0 |
| Sato's site | Osamu Sato's own site: exhibitions, photographs and a biography; nothing on how the game works | https://www.osamusato.net/ |
| Wiki | Osamu Sato Wiki, pages on the game and on the book "Lovely Sweet Dream" | https://compu-lsd.com/w/LSD:_Dream_Emulator and https://compu-lsd.com/w/Lovely_Sweet_Dream |

The wiki is fan work, so we use it for dates and for what it reports from the developers, not as a creator's voice. Sato's site answers at www.osamusato.net (the bare osamusato.net has no address); its English biography calls the game "the content for PLAY STATION" and says nothing about its rules. The book "Lovely Sweet Dream" (Media Factory, 1998, ISBN 4-88991-655-5, 198 pages) was not read: we did not find an authorised online edition. What we know of it comes from its publisher's blurb, the G8 page and the advert on card 8.

## The big picture

**The creators said.** The 1998 site describes the game as wandering through "the dream world one person has seen over the past ten years", says the letters stand for "Link", "Speed", "Dream", and names the genre "a strolling-type dream emulator" that should give "a languid feeling no game has had". Sato in 2017: it "isn't really a game either. It's got absolutely zero gameplay to it" and "I wanted to make contemporary art or music" (RBMA 2017). In 2015: "Dreams are irrational without any rules, and you most often don't remember when you wake up in the morning. I wanted to make a piece like that" (Vice 2015). The wiki reports that the dreams come from a diary kept for about ten years by Hiroko Nishikawa, who worked at Sato's company, and that her book "Lovely Sweet Dream" came out the same day as the game. The game's own credits confirm it: Hiroko Nishikawa is listed for "original dream diary" and for "map design", beside Osamu Sato (concept, planning), Satoshi Ashibe (concept, planning, map design) and Yoshinori Maeda (main program) (Manual, card 7). The gallery that showed the game in 1999 dates the diary from 1 January 1988, over ten years, and calls the result "a game with no goal, as if the leaps of a dream were laid over the chain-like feel of net surfing" (G8 1999).

**The code says.** The program is a set of fixed tables: a mood for every square of every place, a record for each of 130 character types, 49 fixed links, 41 special days, a dream length per place. Many conditions are fixed, alongside random choices for links, music, textures and character behaviour ([the dice of the game](discoveries.md#-the-dice-of-the-game)).

**Our reading.** "Without any rules" describes how the game feels, not how it works. The diarist also drew maps, so the places themselves, not only the text pages, may come from her hand; the credits say she worked on the maps, not which ones. The rules exist, but they are hidden, they depend on things a player does not watch (the day number, the mood so far), and the game never states them. That is a fair way to build a dream: a dream also has causes you cannot see from inside.

**How sure.** High for the facts, medium for the intent.

## The graph and its two axes

**The code says.** The graph is a grid from -9 to 9 on two axes. The game prints UPPER at the top, DOWNER at the bottom, STATIC on the left and DYNAMIC on the right. Every square of every place and every character carries a point on this grid. The screen shows only your last 100 days, the newest in red, the older ones fading to grey ([the graph screen](discoveries.md#-the-graph-screen-only-shows-your-last-100-days)).

**The creators said.** The manual calls it "a graph that shows the current psychological state" and says the point "changes with the places you walked and the things you saw" (Manual, cards 2 and 3).

**Our reading.** The graph is the dreamer's mood diary, not a score. Two word pairs borrowed from drug slang and from motion give a map of feeling without good or bad: no corner is rewarded by the graph itself. The 100-day limit on screen fits the same idea, since old days fade the way old dreams do, but it may also be a simple drawing budget.

**How sure.** High that it is a mood record (the manual says so), low on why 100 days.

## How a day becomes a point

**The code says.** At the end of a normal day the game averages the moods of the squares you crossed and adds a third of the last one. It does the same for the things you touched, then takes the middle of the two results. A result past 9 jumps to -9, and the reverse. Normal day endings store a point, including dreams followed by a video. Scheduled video or diary days store the centre point. Flashback playback stores no new point ([how a day becomes a point](discoveries.md#-how-a-day-becomes-a-point-on-the-graph)).

**The creators said.** Nothing on the formula. The manual only says the point follows what you walked through and saw.

**Our reading.** Two choices stand out. The last place and the last thing touched count extra, which is how people remember dreams: by their end. And the edge of the graph wraps, so a mood pushed too far turns into its opposite. We cannot tell if the wrap was wanted. It reads like a deliberate "too much joy tips over", but it is also exactly what a programmer writes to keep a number in range without thinking further. The Grey Man relies on it (see below), which argues that the team at least knew.

**How sure.** Medium on the weight of the ending, low on the wrap being a statement.

## Where tomorrow starts

**The code says.** The game first finds the first map square, in table order, whose mood equals yesterday's point. It starts you there only if that square has an arrival point; otherwise it uses another arrival point in the same place. This happens for 93 of the 310 points that match a square. Day 1 starts from (0, 0), the cottage. Of the 361 points of the graph, 51 match no square, 49 of them in the corners: those days always start in Pit & Temple, at one of its 3 arrival points picked by a die, and count as a random link. The Natural World comes first in the search for 180 of the 310 points that match ([how the graph picks where tomorrow starts](discoveries.md#-how-the-graph-picks-where-tomorrow-starts)).

**The creators said.** "This point is also closely tied to the place where the next day's dream begins. What kind of relation is it? Please think about it" (Manual, card 3).

**Our reading.** This is the one rule the creators openly ask the player to discover, so it is the heart of the design: yesterday's mood decides where you fall asleep. The rule is simple (first square with the same point), and it has side effects: the Natural World opens more than half of the possible mornings, and the four corners of the graph all lead to the same temple. The bias may be a side effect of the tables and their search order. We have no evidence that rules out a deliberate choice.

**How sure.** High on the intent (the manual), low on whether the side effects were planned.

## Links and what decides where you go

**The code says.** A wall is a block with a mark; 5,223 of the 31,068 blocks have it ([blocks and walls](discoveries.md#-the-world-is-built-from-square-blocks-and-only-marked-blocks-are-walls)). When you push into one, the game first looks for a fixed link at that spot. If there is none, a random link fires, to one of the six main places chosen by a die; if the die names the place you are in, you get the next one, so that place comes up 2 times in 6 ([where a random link sends you](discoveries.md#-where-a-random-link-sends-you)). Fixed links never change with the number of visits; a few only open when a certain character has appeared ([fixed links](discoveries.md#-fixed-links-do-not-change-with-visits-but-some-depend-on-who-showed-up)). The fade of a link takes the colour of the day.

**The creators said.** "I wanted to make something that even people who sucked at games could play [...] So if I crashed into the wall I would be launched into the next world [...] I wanted to make something where the player explores a world that keeps transforming like that" (RBMA 2017). The manual: bump into "walls, trees, fences" to move, and "link as the mood takes you and enjoy the changing scenery"; it adds that "some fields, they say, cannot be reached except by LINK" (Manual, card 6). Falling is foretold too: the temple card warns of "the big hole gaping in the middle" and the Natural World card stops on "if you step off a cliff..." (Manual, card 5). The 1999 gallery page compares the chain of links to net surfing (G8 1999).

**Our reading.** The code matches the stated idea closely. A mistake in other games (hitting a wall) is the main verb here, and it costs nothing visible. The random link only knows six places, so the eight other places are rewards for finding a fixed link or for waking up in the right mood; the manual's "fields you can only reach by LINK" says the same thing in a player's words. The net surfing image fits the code well: a wall is a hyperlink, most lead to one of a few main pages, and the rare ones are fixed addresses. The game has no visit counter anywhere, which contradicts the fan idea that links "learn" from where you have been.

**How sure.** High.

## The hidden score

**The code says.** The game keeps a navigation score. Each of 30 goals, marked by fixed links, is worth 1,000,000; each random link costs 11,024; touching characters adds or removes up to 100,000 each. The Flashback item appears when the score passes 9,999,999 and one memory exists ([what unlocks Flashback](discoveries.md#-what-unlocks-flashback-in-the-menu)). Goal 13 has no link, so the 50,000,000 bonus for all 30 goals can never be paid ([fixed links are the navigation goals](discoveries.md#-fixed-links-are-the-navigation-goals-and-one-can-never-be-completed)). No screen shows the score (read in the code only).

**The creators said.** "It's got absolutely zero gameplay to it. I rejected this idea of games" (RBMA 2017). The manual says Flashback appears "as you wander through many fields and see many things" (Manual, card 3), and that "when you have explored every field thoroughly, a new discovery may come" (Manual, card 5). The 1999 gallery page calls LSD "a game with no goal" (G8 1999).

**Our reading.** Here the code contradicts the statement, in letter if not in spirit. There is a score, there are goals, and wandering by random links is penalised while finding fixed links is rewarded. But the score only does one thing a player can see: it decides when Flashback appears. We read it as a private measure of "has this player explored enough", not as a game to win. The manual's promise of "a new discovery" after exploring every field is the closest any creator text comes to naming it, and Flashback is the discovery the score pays for. The bonus that cannot be paid looks like a goal whose link was removed late, and nobody noticed because nothing depends on it.

**How sure.** Medium.

## Dream length

**The code says.** The length is fixed when the dream starts, by the place it starts in: from 60 seconds (Moonlight Tower) to 600 (Violence District), with 240 for the cottage and 420 for the Natural World. The starting place sets the initial dream limit. Most links preserve it. An extra link in Bright Moon Cottage can leave ten game seconds, and a failed texture load leaves thirty. Flashback links restart the replay clock. We found one clock with one speed ([the start place sets the length](discoveries.md#-the-start-place-sets-the-length-of-the-dream)). The real speed of that clock on a console was not measured.

**The creators said.** "The flow of time differs from field to field: slowly in calm places such as the Natural World, fast in frightening places such as the Violence District. So in a relaxed place one play lasts longer, and in an intense place it ends sooner" (Manual, card 3).

**Our reading.** The manual and the code disagree. In the code time does not flow faster anywhere, the place you are in does not matter, only the place you started in, and the Violence District gives the longest dream of all, not a short one. Either the rule changed after the manual was written, or the manual's writer described the idea and not the final table. The fixed length does serve the stated wish for a game anyone can play: a normal day has a timer, even when the player finds no particular event. Why the scariest place got ten minutes we do not know.

**How sure.** High on the contradiction, low on its cause.

## Day colours and hidden spawn rules

**The code says.** During a dream the mood so far falls into one of 9 cells (3 bands per axis), and a table gives each cell a colour: 8 colours, white used twice. The colour tints the link fades and the flashback veil, and it is one of the conditions of the hidden rules that decide which characters appear, with odd or even day, a 3-day cycle and a 90-day cycle of three "months" ([the hidden rules](discoveries.md#-the-hidden-rules-that-decide-which-characters-appear)). Each colour has its own rare sights: the train that flies and the astronaut on a pink day, nine penguins in a maze on a red day, lions that lead to Temple Dojo on a cyan day, and more ([rare sights](discoveries.md#rare-sights)). The colour names are those of an earlier fan project; the code only has numbers.

**The creators said.** "I put a bunch of hooks in LSD, gimmicks that I hoped would help even at least one person have fun or find interesting" (RBMA 2017). The manual says the scenery "changes each time you visit" and that "the world of LSD is always in flux" (Manual, card 6). Of the characters it says: "they are not always standing in the same place; they too wander the dream world" (Manual, card 4). None of these mentions colours.

**Our reading.** The colour is the bridge between the mood diary and the world: how the dream has felt so far changes who shows up next. Since the centre of the graph is white and most days stay near the centre, the coloured sights are rare by construction, without a single die. We think this is what Sato calls hooks: things placed for the one player who happens to be there on the right day in the right mood. The "type A" and "type B" days of fan guides are simply odd and even days.

**How sure.** High on the mechanism, medium on the intent: the manual says characters move between places and days, but no creator described the colours or the day rules.

## The Grey Man and what he erases

**The code says.** He can appear on even days only, 1 time in 12, on a spot that an odd-day character left empty, about four tiles ahead of you and facing you. Seven places can never hold him ([when](discoveries.md#-when-the-grey-man-can-appear), [where](discoveries.md#-who-can-meet-the-grey-man-and-where)). Touching him erases the list of flashbacks. He is the only character that clears the list; starting a new game, including the pause erase combination, clears it too. He erases nothing else: not the graph, not the save ([what erases the flashbacks](discoveries.md#-what-erases-the-flashbacks)). His mood is (-10, -10), one step past the corner, so the wrap throws the day's point to the other side ([the Grey Man flips your graph](discoveries.md#-the-grey-man-flips-your-graph-and-wipes-your-memories)). He is worth +20,000 points, and he still comes [after day 365](discoveries.md#-myth-no-grey-man-after-day-365).

**The creators said.** "If you meet the mysterious gentleman who sometimes appears in the fields, your memory is erased, so be careful" (Manual, card 3).

**Our reading.** He is the one thing in the game with a cost, and the cost is forgetting. That fits Sato's line that you "most often don't remember when you wake up" (Vice 2015): the Grey Man is that forgetting, given a body. His mood off the scale says he does not belong to the dream's moods at all. The positive points say the designers did not see meeting him as failing; he counts as something seen. He does glide toward you in a straight line, but fan stories that he hunts you from place to place or deletes your progress find no support in the code.

**How sure.** High on what he does, medium on what he stands for.

## Flashbacks

**The code says.** Each time you touch something, and when time runs out, a die keeps the moment 1 time in 3. The game holds 10 memories at most; a new one then replaces one of the first nine, picked by the clock, so the tenth never leaves. A flashback replays about 20 seconds per memory behind a veil of that day's colour ([how flashback memories are kept](discoveries.md#-how-flashback-memories-are-kept)).

**The creators said.** Flashback lets you "recall the striking scenes you have seen so far and see them once more" (Manual, card 3).

**Our reading.** Memory here is unreliable on purpose: you do not choose what is kept, and most moments are lost. The memory that can never be replaced is almost surely a slip (a count of 9 where 10 was meant), not a statement about one dream that stays for life, even if it reads nicely that way.

**How sure.** High on the first point, medium on the slip.

## Special days and videos

**The code says.** A table lists 42 day numbers, 41 different days because day 126 is there twice. On those days there is no dream: 1 time in 3 a video, 2 times in 3 a still page of diary text, and the day is logged at the centre of the graph ([the 42 special days](discoveries.md#-the-42-special-days), [what a special day shows](discoveries.md#-what-a-special-day-shows)). A weekly run goes from day 7 to day 126, then one day late from 134 to 204, and 13 more days are fixed dates; after day 204 only 6 special days remain. A secret reel of 20 videos plays once per game when four given cells of the graph are filled in the last 100 days ([the secret reel](discoveries.md#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film)).

**The creators said.** "Suddenly text from a dream diary will appear, or a movie of a UFO, imagery like something out of a dream suddenly playing" (RBMA 2017). The wiki's page on the book says some dreams of the diary are quoted directly in these text pages.

**Our reading.** These days are the diary speaking in its own voice, between the nights you walk through. The weekly rhythm in the first half of the year, then near silence, suggests the team filled the calendar from the start and ran out of material or time before the end, more than a wish to make the second half lonely. The duplicate is consistent with a table-entry mistake, but it does not establish how the table was made. The reel is the best hidden prize in the game, and its four cells draw a small face on the graph, which is a joke only someone who made the graph would hide there.

**How sure.** Medium.

## The 365 days, the year counter and the ending

**The code says.** The day counter runs to 365, then wraps, and a year counter that no screen shows goes up by one ([the day counter and the hidden year](discoveries.md#-the-day-counter-and-the-hidden-year)). When a year closes, the ending video plays, and it plays again at the end of every year ([the ending](discoveries.md#-the-ending-plays-when-a-year-closes-not-on-day-365)). Nothing else changes with the year. Filling the graph does nothing ([myth checked](discoveries.md#-myth-a-hidden-ending-if-the-graph-is-full)). The first dream of a new year reads its start from the wrong bytes of memory ([the new-year bug](discoveries.md#-the-first-dream-of-a-new-year-starts-from-the-wrong-data)).

**The creators said.** Nothing we found on the ending or on the 365 days. On an earlier work, Sato speaks of reincarnation as "moving on to the next world after you die" and says "LSD is focusing on Eastern elements" (RBMA 2017).

**Our reading.** One year of a dream diary, then the same year again: the game is a loop, not a story with an end. It is tempting to tie the loop to the reincarnation idea Sato used before, but he does not make that link himself, so we leave it as a possibility. The new-year bug survived into the released game; it does not tell us how extensively later years were tested.

**How sure.** High on the loop, low on any deeper meaning.

## Randomness and the calendar

**The code says.** One number sequence feeds every die, and the game gives it a fresh start once at most, before the title ([the dice of the game](discoveries.md#-the-dice-of-the-game)). Many things that look random are not: the sky and ambience follow the day number and the place, the wall link waits for 1 clock tick in 16, a band of clouds comes on days divisible by 7, giant flowers and mushrooms follow the day number ([not random](engine/randomness.md#not-random)). The picture with "World: 17464 0 36838" that fans took for a seed is a position readout in a 1998 developer tool; the game has no world seed.

**The creators said.** "After you make it through the opening things begin to change randomly" (RBMA 2017). The wiki lists "procedurally generated" among the false rumours about the game.

**Our reading.** For Sato, "randomly" means "you cannot predict it", and that is true for a player. In the code the real engine of variety is the calendar. The day number gives players shared calendar conditions, but their routes, moods and random draws can make the same numbered day very different. That makes the game something people can compare notes on, and Sato says he hoped it "would spread through word of mouth" (Gata). We do not know if the team chose the calendar for that reason or because it was the easiest thing to program.

**How sure.** High on the facts, low on the motive.

## Textures cycling over days

**The code says.** Each place has four texture sets. On a 40-day cycle, the first 10 days use only the first set, and each further block of 10 days adds one more set to the draw ([the 40-day texture cycle](discoveries.md#-the-40-day-texture-cycle)). The famous glitch textures are a set that failed to load for lack of memory; the dream then ends 30 seconds later ([glitch textures](discoveries.md#-glitch-textures-a-texture-set-that-failed-to-load)).

**The creators said.** "Sometimes a whole wall is covered in eyeballs, sometimes text is lined up on it [...] the same place will give a completely different impression" (Manual, card 6).

**Our reading.** The cycle is a slow ramp: ten plain days so that you learn the places, then stranger and stranger versions, then calm again. It is the clearest case of pacing in the game, done with the calendar and one small die. The glitch look is not an intended fifth set. The code treats it as a failure and cuts the dream short, so the legend of a "corrupted" hidden world is a memory shortage. In normal play the shortage comes from a timing accident: a patch of ground swapped while its characters were still arriving leaves four characters in memory for good, and every later set that needs the full margin fails ([glitch textures](discoveries.md#-glitch-textures-a-texture-set-that-failed-to-load)).

**How sure.** High.

## Sound

**The code says.** Each dream picks 1 of 7 sound banks, each place 1 of 5 tracks: 70 music files, 66 of them real melodies, 462 combinations at most ([myth: over 500 tracks](discoveries.md#-myth-over-500-music-tracks)). One track of Clockwork Machines can never play ([the track](discoveries.md#-a-clockwork-machines-track-that-can-never-play)). Places also hold fixed sound spots, 29 of the 56 in the Natural World ([fixed sound sources](discoveries.md#-places-have-fixed-sound-sources)).

**The creators said.** "I made all the music myself and then had seven remixers in England, Japan and so on make their versions of it" (RBMA 2017). The figure of "about 500 different patterns" comes from the interviewer in that same article, not from Sato.

The credits card settles where the remixes went: it lists "opening original music & BGM: OSAMU SATO", then "remix (opening music)" with seven titles by seven artists, among them Ken Ishii, Jimi Tenor and μ-Ziq (Manual, card 7). The advert on card 8 sells the soundtrack as "the complete remixes used in the opening movie of LSD, with the originals" (Manual, card 8).

**Our reading.** The seven remixes are the music of the opening films: the disc holds exactly seven, `OPENINGA` to `OPENINGG`, and one is picked at random at each boot ([sound and video](engine/sound-and-video.md)). The music of the dreams is credited to Sato alone, so the seven sound banks are not the seven remixers, as this page first read; seven is a shared number, not a proof. A bank changes the instruments for a whole dream and the track changes with the place, which is the same trick as the textures, applied to the ear. The code corrects the "500 patterns" figure either way.

**How sure.** High that the remixes belong to the opening (the credits and the advert say so); not checked by ear, since our emulator runs muted. Low on why the dream music also has seven banks.

## The save

**The code says.** The saved game state is 1,792 bytes. With its 512-byte title and icon header, the file writes 2,304 bytes and occupies one 8 KB memory-card block. It holds the graph of the whole year, the 30 goals, the count of random links, 10 flashbacks, the reel flag and the SHAKE option ([one block](discoveries.md#-everything-the-game-remembers-fits-in-one-block), [how the save works](discoveries.md#-how-the-memory-card-save-works)). Nothing checks that a loaded save is valid. SELECT + TRIANGLE in the pause erases the current game with no question asked ([the erase combo](discoveries.md#-select--triangle-in-the-pause-erases-your-game)).

**The creators said.** The manual explains how to save, load and name the file (Manual, card 2). The erase combo is in it, on the controls card: "during the pause, pressing SELECT and TRIANGLE together gives a software reset and returns to the menu screen. The Day and the graph data are reset too, so be careful". The same card says the CIRCLE and SELECT buttons "are not used" (Manual, card 1).

**Our reading.** The save does not resume your current walk. It keeps days and memories, including the place and position of each flashback. The erase combo is a documented reset, not a hidden shortcut: the manual warns about it, and the game asks for no confirmation. It wipes more than the manual says (the score, the memories, the goals and the reel flag go with the day and the graph). The manual's "CIRCLE and SELECT are not used" is wrong for the shipped game: CIRCLE answers [three characters](discoveries.md#-characters-that-answer-to-circle) and SELECT runs the cursor of the comment keyboard. Those two inputs read like late additions after the manual was written, or details its writer left out.

**How sure.** High on the first two points (the manual and the code), low on why the manual and the buttons disagree.

## What dead code, unused switches and bugs tell us

**The code says.**

- A dog model is on the disc and never loaded. Its record has the mood (10, 10) and no behaviour: the exact opposite corner from the Grey Man's (-10, -10) ([the dog that never loads](discoveries.md#-the-dog-that-never-loads)).
- The pause has a way to quit a dream without counting the day, which no button reaches. A switch can pin the music, hold a fade or loop a video, and nobody pulls it ([unused switches](discoveries.md#-switches-and-features-the-game-never-uses), [the music switch](discoveries.md#-a-switch-to-pin-the-music-that-nobody-pulls)).
- A function that averages every point of the graph exists and is never called (`DreamSys_GetPreviousPoint` @0x8005B1F4, mode 0).
- A new game clears one unused byte, two unused words beside SHAKE and a final 500-byte area that no other game code uses (`DreamSys_InitNewGame` @0x8005A258, read in the code only).
- Files the game never asks for sit on the disc, among them a second publisher logo ([what the game never asks for](discoveries.md#-what-the-game-never-asks-for)).
- No debug menu or additional cheat sequence was found beyond the pause erase combination. The remaining debug messages go to a developer's console.
- Small slips remain: day 126 listed twice, goal 13 without a link, the tenth flashback that never leaves, the new-year start, a fall that picks a place nobody then uses ([falls](discoveries.md#-falling-off-an-edge-walls-and-the-cottages-walking-squares)).

**The creators said.** The 1998 site, in a note dated 13 February, admits that a "beta version" is only now ready although a note of the previous July had announced that testing was about to begin: "a complete lie, wasn't it". The wiki dates the public announcement to January 1997 and the release to 22 October 1998. Asked about Easter eggs in 2017, Sato answers: "No, not really. I think everything has been found. I've forgotten almost everything I put in there. I don't really play the game myself" (RBMA 2017).

**Our reading.**

- The dog and the Grey Man look like a planned pair, one at each corner past the edge: one that pushes the day to an extreme, one that would have pushed it the other way. Only the Grey Man got a behaviour. This is our strongest guess about cut content, and it rests on two numbers, so treat it as a guess.
- The unused average of all points suggests an earlier idea where the whole history of moods, not only yesterday, chose the next start. The shipped rule is the simpler one.
- The two unused words beside SHAKE, the same size as it, suggest more settings were foreseen; the code does not say so. The 500 bytes are plain reserve, and nothing hides in them.
- The quit that skips the day was probably a tester's tool. Shipping without it fits the design: a day, once begun, always counts.
- Together with the developers' account of a late beta, these leftovers suggest unfinished work. They do not establish the team's size, testing effort or reason for stopping.
- We found no earlier written explanation for several of these rules. That does not tell us which events players had seen by 2017, or whether Sato counted these implementation details as Easter eggs.

**How sure.** Medium overall, low for the dog.

## Where the code contradicts what people say

| Claim | Who | What the code says |
| --- | --- | --- |
| "Zero gameplay" | Sato, RBMA 2017 | A hidden score with 30 goals gates Flashback |
| Time flows fast in the Violence District, so the play is short | Manual, card 3 | One clock speed; starting there gives the longest dream, 600 seconds |
| About 500 musical patterns | Interviewer, RBMA 2017, and later articles | 462 combinations at most, 66 melodies |
| The world is procedurally generated from a seed | Fan theory | Fixed maps; the "World" numbers are a tool readout |
| A full graph gives a hidden ending | Fan theory | No code looks at how full the graph is |
| The Grey Man stops after the first year | Fan theory | Nothing in his rule reads the year |
| The astronaut only lands between days 200 and 300 | Fan theory | [An even day and a pink day](discoveries.md#-myth-the-astronaut-lands-only-between-days-200-and-300) |
| Glitch textures are a secret fifth world | Fan theory | A texture set that did not fit in memory |
| "A game with no goal" | G8 1999 | The same hidden score with 30 goals |
| The CIRCLE and SELECT buttons are not used | Manual, card 1 | CIRCLE answers three characters, SELECT runs the comment cursor and arms the erase combo |

Where the code agrees with the creators, it agrees well: the wall crash as a link, the diary pages and videos that cut in, seven opening films for seven remixes, the Grey Man who erases memory, the erase combo on the controls card, the start of the next dream tied to the graph.

## What we still do not understand

- **The manual's time rule.** We do not know if an earlier build really had a clock that ran faster in some places, or if the manual simplified. We have no earlier build to read.
- **Why the Violence District gives the longest dream** and Moonlight Tower the shortest. The table has no visible logic of calm against fear.
- **The dog.** We know its file, its record and its mood. We do not know what it was meant to do, or why it was cut.
- **Goal 13.** Which link was meant to mark it, and whether its absence is a slip or a late removal.
- **The points on each character** (from -100,000 to +100,000). They feed the hidden score, but we cannot say what the designers were judging when they gave one character a plus and another a minus ([the character record](discoveries.md#-the-character-record-mood-points-waking-up-and-leaving)).
- **How the mood tables were filled.** Why 51 points of the graph match no square, and why two of them, (0, 3) and (5, 7), are holes in the middle. We suspect hand entry, with no proof.
- **The meaning of the colours.** The code has numbers, not names. We do not know if the team thought of them as colours of moods or only as fade colours that later served as conditions.
- **The clock on a real console.** All lengths are the game's own counts; how many real seconds a count lasts on the original machine was not measured.
- **The first die on a real console.** In the emulator the sequence was never given a fresh start. On a console the starting value may differ, which would change which opening video and which first rolls a fresh boot gives.
- **The cyan lions on foot.** A walk of 24 squares in an exact order, using only pad input after the day number and yesterday's point were set in RAM, reaches them ([the lions](discoveries.md#-the-natural-world-lions-a-random-temper-and-a-cyan-day-pair-that-leads-to-temple-dojo)), but nothing tells whether the designers expected anyone to find such a walk.
- **How often the glitch textures came on a real console.** In the emulator, an hour of play with the pad alone hit the timing accident once. A real CD drive has its own timing, so how often players met it in 1998 is not known.
- **The diary itself.** We do not compare the text pages with the book, since we do not copy game text, and we did not read the book. So we cannot say which dreams of the game come from the diary and which the team invented, nor which maps the diarist drew.
- **The ending.** No creator statement we could open explains why the credits return every year.

Open questions on the code side are tracked in [the mysteries page](mysteries.md).

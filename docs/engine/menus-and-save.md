# Menus, the pad and the memory card

Between dreams the game runs a short chain of screens: logo pictures, an opening video, the graph,
then the main menu with START, FLASHBACK, SAVE, LOAD, GRAPH and SHAKE. All of them are built on one
menu screen class that fades in, waits for the pad, and fades out. SAVE and LOAD hand the pad to a
memory card object that runs its own dialog, with a comment keyboard for saves and a file chooser
for loads. What gets saved is one 0x700-byte block of the dream state.

## The title chain

`Scene_RunTitle` ([scene.c](../../src/game/scene.c)) runs, each time through the scene loop:

1. The graph (`Graph_New`, a `MenuScreen` subclass, [dream system](dream-system.md)), unless the
   day number is 1 or the last dream set `skipGraph`. A graph result of 2 plays the secret reel
   ([sound and video](sound-and-video.md#videos)).
2. The main menu (`Menu_New`) until its result is not 2; a result of 2 (GRAPH) shows the graph
   again and comes back.
3. Menu result 0 returns 2, which makes `App_Run` start a dream; any other result returns 0, back
   to the opening video. The menu's 10-second timeout gives result 1.

Before it, `Scene_ShowLogos` shows `ETC\ASMKLOGO.TIM` and `ETC\OSDLOGO.TIM` as bare `MenuScreen`s
with a picture and timeout 0 ([boot](boot-and-objects.md#from-main-to-the-scene-loop)). Every
screen of this chain runs with the CD back end in synchronous mode (`File_EnableWait(0, 0, 0)`),
so a picture is in VRAM as soon as `Tim_New` returns ([files and CD](files-and-cd.md#the-cd-back-end)).

## Pad events

[`Pad`](../../src/game/pad.c) (class word 2) is made once by `main` and kept in the `ScreenEnv`.
Each frame `Screen_OnDisplay` calls `Pad_Read` (`PadRead`, then the bits that went down and up)
and `Pad_SendEvents`, which sends one code per button through `Object_Notify`: released wins over
pressed, pressed over held, and codes go out from button 15 down to 0. A code is a state plus a
button index: held 2, pressed 0x12, released 0x22, and the buttons in the order of
`Pad_InitButtons`:

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Button | UP | DOWN | LEFT | RIGHT | TRIANGLE | CROSS | SQUARE | CIRCLE | L3 | R3 | SELECT | R1 | R2 | L1 | L2 | START |

So 0x19 (25) is CIRCLE pressed, 0x17 (23) CROSS pressed, 33 START pressed, 12 SELECT held. A held
button repeats its code every frame. The dream's own handler is `Place_OnPad`
([the erase combo](../discoveries.md#-select--triangle-in-the-pause-erases-your-game)).

## MenuScreen

[`MenuScreen`](../../include/game/menu_screen.h) (class word 0x130,
[menu_screen.c](../../src/game/menu_screen.c)) adds to `Screen`: an optional sound bank, a
picture, a timeout (20 ticks per second), fades, and a menu of items described by a static
`MenuDef` (font, texts, positions, hidden flags, per-item option lists).

- `MenuScreen_Begin` shows the item texts (`Label`s) and the `Bg` under the screen's root, clears
  the screen to the start colour, sets the view (3 OT bits, 300 packets) and allocates its tables.
- `MenuScreen_SetPicture` loads a TIM and uploads it; the `Bg` built from `BgCells` and `BgMap`
  draws the picture area (VRAM x 640, `MenuScreen_GetPictureRect`) over the whole screen.
- `MenuScreen_OnClock` drives the states of [screen.h](../../include/game/screen.h): 2 goes to
  4 (fading in); 4 steps `MenuScreen_FadeInStep` (brightness up by `fadeSpeed`, 9, per tick until
  128) and then sets 5 (active: focus on the items, initial item selected); 7 steps the fade out;
  8 sets 3, which stops the frame loop and returns from `run`. A timeout sets 6: result 1, close.
- `MenuScreen_OnPad` reacts only to presses and only with the focus: UP and DOWN move through
  items or options, CIRCLE confirms (state 11, or 15 inside an option list), CROSS cancels an option
  list (17), START sets 10. CIRCLE, CROSS and START play tone 0x10 on the bank.
- `MenuScreen_Confirm` opens the item's option list, or closes the screen on `closeItem`; close
  runs the `onClose` callback, then state 7.

## The main menu

[`Menu`](../../include/game/menu.h) (class word 0x1F130, [menu.c](../../src/game/menu.c)) is a
`MenuScreen` with `g_mainMenuDesc`, the bank `ETC\ETCSE` (octave -1), the picture
`ETC\TITLE.TIM` and a 10-second timeout. It keeps the `DreamSys` and a pointer to its save block.

| Item | What happens |
| --- | --- |
| START | the base closes it (it is `closeItem`); result 0, a dream starts |
| FLASHBACK | flashback mode on (`setFlashbackMode`), result 0, close; hidden unless the unlock score is above 9,999,999 and a memory is kept ([what unlocks it](../discoveries.md#-what-unlocks-flashback-in-the-menu)) |
| SAVE | slot 0x130 `Menu_Save` |
| LOAD | slot 0x134 `Menu_Load` |
| GRAPH | result 2, close |
| SHAKE | an option list; `Menu_Close` and `Menu_Save` store the choice in `DreamSys` (`swapShake`) |

Pressing START anywhere (state 10) cancels an open option list, selects the menu's initial item
and confirms it.
Above the items, a `Label` shows the save title `g_cardTitle` (see below); `Menu_SetItemsColor`,
called by every fade step, makes it blink through the colour channels.

## The memory card

SAVE and LOAD call `Menu_OpenCard`: the first time it makes `CARD\FILEICN1.TIM` (the file icon)
and a [`Card`](../../include/game/card.h) (class word 0xB, [card.c](../../src/game/card.c)),
then hands it the pad, the clock, the root and the bank, and stops watching the pad and the clock
itself. The card wraps the card BIOS (`InitCARD`, `StartCARD`, `_bu_init` on the first card; four
card events; `_card_info`, `_card_load`, and files on `bu00:`).

Every step is a state set by `Card_SetState` (slot 0x7C), which notifies the menu, shows the
picture `CARD\<name>.TIM` of that state and runs it:

| States | Meaning |
| --- | --- |
| 2 to 8 | no card, error, card changed, unformatted (load or save), formatting, format error |
| 9, 10 | full, overwrite question |
| 11, 12 | saving, save error |
| 13 to 16 | no save file, load question, loading, load error |
| 17, 18 | comment keyboard open, file chooser open |
| 19 to 21 | the work itself: format, write, read (7 ticks after 7, 11, 15) |
| 22, 23 | done, closed: the menu takes the pad back (`Menu_OnCardNotify`) |

`Card_CheckReady` probes the card first (info, then directory, up to 12 tries) and turns a missing,
changed or unformatted card into its state. CIRCLE (`Card_OnConfirm`) retries or goes on, CROSS
(`Card_OnCancel`) closes a question.

- **Save** (`Card_Save`): if the file exists, the overwrite question; then the comment keyboard;
  then SAVING, and 7 ticks later `Card_WriteFile`. A game never saved writes to the first free
  name, `BISLPS-01556` plus `-01` to `-15` (`Card_FindFreeName`). The file is a PS1 save header
  (`SC`, 0x10 plus the icon frame count, the block count, the title, the palette and three 16 x 16 frames of the
  icon TIM) then the data, rounded up to 128 bytes (`Card_WriteFileOnce`).
- **Load** (`Card_Load`): lists the files with the game's prefix (`Card_ListFiles`), opens the
  chooser on their titles, asks for confirmation, then LOADING and `Card_ReadFile`, which skips the
  header by its size byte.
- On done, `Menu_OnCardNotify` clears the "never saved" flag and redraws the title and items
  (`Menu_RefreshFromSave`).

The title is a Shift-JIS string: the game name, the file's letter (a for `-01` up to o for `-15`,
`Card_SetTitleLetter`), the day number in three digits, then the comment. The keyboard edits the
comment 13 characters in (`commentStart`, passed as 13 by `Menu_Save`)
([how the save works](../discoveries.md#-how-the-memory-card-save-works)).

### Comment keyboard and file chooser

`CommentObject` ([comment_object.c](../../src/game/comment_object.c), class word 0x10) shows the
comment with a `Label` in the `FONTICON` font, a `Glyph` caret and the `COMINPUT` box. It watches
the pad and the clock; `CommentObject_OnKey` maps CIRCLE (25) to "copy the text back, notify 2",
CROSS (23) to "notify 3", the shoulder codes 31 and 32 to the two delete keys, SELECT (28) to
`CommentObject_ToggleFlag`, and the d-pad to caret and character moves: pressed codes normally,
held codes after SELECT ([SELECT on the keyboard](../discoveries.md#-select-on-the-comment-keyboard-makes-the-cursor-run)).
`StringList` ([string_list.c](../../src/game/string_list.c), class word 0x20) is the chooser: the
same pattern over a list of titles, notifying 2 with the choice or 3. `Card_OnKeyboard` and
`Card_OnChooser` turn 2 into the next step and 3 into CLOSED.

## The save block

What the card writes is `DreamSys_GetSaveBlock`: 0x700 bytes at `DreamSys` +0x178
([dream_sys.h](../../include/game/dream_sys.h) `SaveBlock`): a magic word, the year and day,
three scores, 365 graph points, the flashback memories, the reel flag, the 30 navigation flags,
the dynamic link count and the SHAKE choice. A load reads straight into it; the menu then rebuilds
its title from `g_cardTitle`, which the load also filled from the chosen file. The meaning of each
field is in [the dream system](dream-system.md) and
[everything the game remembers](../discoveries.md#-everything-the-game-remembers-fits-in-one-block).

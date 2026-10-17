# Sound and video

The game has three kinds of sound: short tones played from VAB banks (menu clicks, character and
place sounds), one SEQ music track per place played by libsnd, and the CD audio inside `.STR`
videos. The banks and the music are file objects like any other ([files and CD](files-and-cd.md));
the sequencer runs from a hardware timer set up by the game's own copy of Sony's tick code. Videos
are played by an MDEC player fed by a CD stream object, inside a screen like the menus.

## Sound banks

A [`SoundBank`](../../include/game/sound_bank.h) (class word 0xA03, 0x64 bytes,
[sound_bank.c](../../src/game/sound_bank.c)) is a file object holding one VAB. Its vtable:

| Slot | Function | Role |
| --- | --- | --- |
| 0x08 | `Sound_InitBank` | starts the sound system on the first bank, then queues `<path>.VH` |
| 0x0C | `Sound_DestroyBank` | `SsVabClose`; the last bank, with no music object alive, stops the timer and the SPU |
| 0x64 | `Sound_UpdateBank` | `onLoaded`: state 1 opens the header (`SsVabOpenHead`) and loads `<path>.VB`; state 6 sends the body (`SsVabTransBody`) |
| 0x78 | `Sound_PollTransfer` | `SsVabTransCompleted(1)`, then slot 0x7C |
| 0x7C | `Sound_LoadProgramTable` | reads every program and tone attribute into heap tables, starts the sequencer timer the first time |
| 0x80 | `Sound_PlayTone` | `SsUtKeyOn` then `SsUtAutoVol`; returns the voice |
| 0x84 | `Sound_StopVoice` | `SsUtKeyOffV`, or all voices for 24 and above |
| 0x88, 0x8C | `Sound_MuteBank`, `Sound_UnmuteBank` | `SsSetMute`: the pause mutes the place's bank |
| 0x9C | `Sound_SetOctave` | notes shift by `octave * 12 - 24` |

A sound number packs the program in its high bits and the tone in its low 4 bits
(`program = sound >> 4`); the note is the tone's centre note from the VAB plus the octave shift.

The first bank ever made runs LIBSND's `SsInit` (`SpuInit`, the SPU voice and control registers
loaded from tables, `SpuVmInit(24)`, sound state cleared), `SsSetTableSize` on the SEQ table of
[bgm.c](../../src/game/bgm.c), and `SsSetTickMode(1)`.

Who owns a bank: a `MenuScreen` can (the main menu and the graph load `ETC\ETCSE`), the dream runner (the effects
bank `SND\SE`, `Music_GetEffectsBank`), and every model at +0x58. Characters and scenery play
through [`HandlerNode`](../../src/game/handler_node.c): `HandlerNode_Run` resets three voice
requests, calls the behaviour handler once per tick, then stops or starts the voices it asked for,
lowered by its `fade` value, which the character handlers set from the entity's `getSoundFade`
slot ([characters](characters.md)). The fixed sound spots of a place use the same nodes
([fixed sound sources](../discoveries.md#-places-have-fixed-sound-sources),
[stages and places](stages-and-places.md)).

## The sequencer timer

The sequencer timer is Sony's own LIBSND code (`SsSetTickMode`, `SsStart`, `SsEnd`, `SsQuit`,
linked as is in psyq/80032588; the C once kept in `seq_timer.c` is in work/sony/c/).
`SsSetTickMode(1)` asks for 60 ticks per second; on an NTSC console (`g_videoMode` 0, read by
`GetVideoMode` in `_SsInit`) that becomes rate 5, the vertical blank. `_SsStart` then picks a
root counter:

| Rate | Counter | Handler |
| --- | --- | --- |
| 5, started at once | root counter 3 (vblank), interrupt 0 | `_SsTrapIntrVSync`: the previous interrupt-0 handler, then `SsSeqCalledTbyT` |
| 5, deferred | none | `VSyncCallback(SsSeqCalledTbyT)` |
| 2, 3 | root counter 2, fixed targets | `SsSeqCalledTbyT` |
| other, below 70 | root counter 2 | `_SsSeqCalledTbyT_1per2`: every second interrupt |

`Sound_LoadProgramTable` calls `SsStart` (at once) and `SsSetMVol(0x78, 0x78)` the first
time a bank is ready. `Sound_GetTickRate` returns 60, which `Bgm_FadeVolume` uses to turn seconds
into sequencer ticks.

## Music

[`Bgm`](../../src/game/bgm.c) (class word 0x50, its error string calls it "WBgm") pairs a sound
bank and a [`SeqFile`](../../src/game/seq_file.c). It watches the current display: on each frame
message 2 while its state is `BGM_WAITING`, `Bgm_Open` checks that the bank's transfer is done and
the SEQ is loaded, then calls `SsSeqOpen` and `SsSeqSetVol(0x34, 0x34)`; with `autoPlay` it plays
at once with `SsSeqPlay(id, SSPLAY_PLAY, 0)`, which loops the track until stopped.

Per dream and per place:

1. `DreamRunner_Init` makes one `Bgm` with `Music_PickBank(0)` (one of seven `SND\` banks at
   random, unless `g_musicBankOverride` is set) and no SEQ, `autoPlay` 1.
2. `Place_Load`, when a stage loads, calls `setSeq` (slot 0x5C) with `Music_PickTrack(stage)`: one
   of the stage's `BGA` to `BGE.SEQ` at random, BGC replaced by BGD in stage 9
   ([a track that can never play](../discoveries.md#-a-clockwork-machines-track-that-can-never-play)).
   The new `SeqFile` loads through the CD queue; the next frames open and play it.
3. The pause calls `pause` and `resume` (`SsSeqPause`, `SsSeqReplay`); `Place_Unload` calls `stop`
   (`SsSeqStop`, `SsSeqClose`).

`Music_SetOverride` would pin the bank and the track but has no caller
([a switch nobody pulls](../discoveries.md#-a-switch-to-pin-the-music-that-nobody-pulls),
[over 500 tracks](../discoveries.md#-myth-over-500-music-tracks)). The bank and track draws use
the game's one random generator ([randomness](randomness.md)).

## Videos

Three objects play a video:

| Object | File | Role |
| --- | --- | --- |
| `VideoScreen` | [video_screen.c](../../src/game/video_screen.c) | a `MenuScreen` (class word 0x1130): fade, timeout, CIRCLE to skip |
| `Movie` | [movie.c](../../src/game/movie.c) | the MDEC player: VLC decode, `DecDCTin`, slices back with `DecDCTout` |
| `Stream` | [stream.c](../../src/game/stream.c) | one `.STR` file through `StSetRing`, `StSetStream`, `CdRead2` and `StGetNext` |

Callers ([scene.c](../../src/game/scene.c)) make a `VideoScreen` and call its slot 0x44,
`VideoScreen_Play(env, path, frameCount, autoStart)`; the frame count comes from `g_videoTable`
through `Cine_GetVideoFrames` ([path_table.c](../../src/game/path_table.c)). The video ids:

| Id | Video |
| --- | --- |
| 0 to 6 | `ETC\OPENINGA` to `OPENINGG.STR`, one picked at random by `Cine_PickOpeningPath` |
| 7 | `ETC\ENDING.STR` |
| 8 and up | `FILM\EVENT1` to `EVENT6.STR` |
| 14 + 2 x category | the two videos (variants 0 and 1) of a special-day category; variants 2 to 5 are pictures, id -1 |
| 0x31 | `ETC\ASMK.STR`, the logo |

`Cine_GetSpecialDayRun` sums the frames of the first ten categories for the secret reel, which
plays `FILM\SPDAY01A.STR` with a timeout of that length
([the secret video reel](../discoveries.md#-the-secret-video-reel-four-graph-points-and-11-minutes-of-film),
[what a special day shows](../discoveries.md#-what-a-special-day-shows)).

### How a frame gets to the screen

- `Movie_Init` makes a `Stream` at speed mode 0 (double speed) and 15 frames per second,
  allocates a 0x12000-byte ring, two run-level buffers and one slice buffer, resets the MDEC and
  installs `Movie_OnMdecOut` as the `DecDCTout` callback. The frame goes to the picture rectangle
  of `MenuScreen_GetPictureRect`.
- `VideoScreen_Begin` calls `Movie_Open`: `Stream_Open` searches `\CDI\<path>;1` with
  `CdSearchFile` itself (videos are not in the path table), turns CD audio on at full volume
  (`Stream_EnableCdAudio`), takes the drive (`g_activeStream`) and seeks. A failure sets the
  screen's timeout to 0, so it closes.
- Each clock tick, `VideoScreen_OnClock` calls `Movie_Update`. The first call starts the stream
  (`Stream_Start` up to the frame count); later calls run `Movie_DecodeFrame`, which waits for the
  previous frame's slices, sends the ready run-level buffer to the MDEC, and VLC-decodes the next
  frame from the stream (`Movie_ReadFrame`, `DecDCTvlc`) into the other buffer.
- The MDEC callback calls `Movie_OnSlice`, which loads the 16-pixel-wide slice into VRAM through
  the display and asks for the next one until the frame is done.
- When the stream passes its last frame, `Movie_ReadFrame` stops it; `Movie_OnStopped` then clears
  `g_activeMovie` and returns 1. `Movie_Update` has no return statement on that path, so the 1 left
  by the call is what reaches `VideoScreen_OnClock` (our reading of the code), which closes the
  screen.

A `VideoScreen` times out at 15 ticks per second of its timeout (20 for other menu screens).
`Movie_Start` installs `Movie_OnStreamCallback` through the stream's slot 0x7C, but
`Stream_SetCallback` is empty, so the loop counter is never used
([the unused switches](../discoveries.md#-switches-and-features-the-game-never-uses)).
Before every video the scene calls `File_EnableWait(0, 0, 0)` so the file queue is idle and the
drive is free for the stream.

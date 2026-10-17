# Files and the CD

Everything the game shows or plays comes off the disc: pictures, models, animations, sound banks,
music, map chunks and videos. A single file class hides the drive behind a vtable, keeps a table of
560 disc positions resolved at boot, and can read in two ways: at once, blocking, for the title and
the menus, or as a queue of requests stepped from the vertical blank while a dream runs, so the
world keeps moving while chunks and textures stream in. Videos bypass all this and use the Sony
streaming library ([sound and video](sound-and-video.md)).

## The File class

`File` ([file_base.h](../../include/game/file_base.h)) is an `Object` of 0x2C bytes; every loader
derives from it ([class words](boot-and-objects.md#class-words) ending in 3).

| Field | Meaning |
| --- | --- |
| +0x0C `isOpen` | the file's disc position is known |
| +0x10 `data`, +0x14 `size` | the file bytes; `size` 0 means the bytes belong to a parent file |
| +0x18 `cdPos`, +0x1C `cdSize` | `CdlLOC` and size from the directory |
| +0x20 `keepData` | `freeData` keeps the bytes |
| +0x22 `pending` | queued requests not yet done |
| +0x24 `flags` | what finished: 0x10 open, 0x20 close, 0x40 seek, 0x80 read, 0x200 whole load, 4 nothing pending |
| +0x2A `state` | free for the class (9 and 10 in `Tix` and `MapChunk`) |

Slots 0x40 to 0x58 and 0x68 to 0x74 are the I/O slots: open, close, seek, read, load the whole
file, run the queue, load asynchronously, stop, cancel. They are 0 in the data. At boot
`File_SetBackend` ([file_base.c](../../src/game/file_base.c)) copies them from the chosen back
end into the base vtable and into every loader vtable listed in `g_fileClassGetters`:
0x13 is the CD back end of [file_cd.c](../../src/game/file_cd.c), 0x23 a null back end
([file_null.c](../../src/game/file_null.c)) whose I/O slots do nothing. The scene always picks
0x13. The other slots are the class's own: 0x5C `File_FreeData`, and 0x64 `onLoaded`, which runs
after each finished request and is where every loader parses its data.

Creators take a `FileSource`: either a pointer into a parent file (the object borrows it and
parses at once) or a path (the object calls `loadAsync`, slot 0x6C). That is how a `Mom` builds a
`Tmd` and a `TodPack` from its own bytes without a second read.

## Paths and the path table

`File_BuildPath` turns a name into `\CDI\<name>;1`. The table `g_pathTable`
([path_table.c](../../src/game/path_table.c)) holds 0x1C-byte entries: a name of 0x14 bytes,
then the `CdlLOC` and the size once resolved. `File_GetPathTable` counts 0x230 (560) of them:

| Part | Content |
| --- | --- |
| first | the sound banks (`SND\...`) |
| per stage, from `g_stageFirstPath[stage]` | `TEXA` to `TEXD.TIX` (+0), `BGA` to `BGE.SEQ` (+0x70), then the `Mxxx.LBD` chunks (+0xFC) |
| after entry 560 (not resolved) | the opening, ending, event and special-day `.STR` videos, read by the `Cine_*` getters |

`File_ResolvePathTablePart` ([dream_runner.c](../../src/game/dream_runner.c)) feeds it to
`File_AddDirEntries`, which runs `CdSearchFile` on each new entry (`File_ResolveEntries`, about
100 retries, then a "File not found" `printf`). The first logo closes after half the table, the second after
the rest; `DreamRunner_Init` calls it again with 1, which resolves the whole table only if the
logos were skipped. Once resolved, the queued CD code finds a file with `File_FindEntry`, a
`strstr` over the table, and never searches the disc again during a dream.

The getters that pick from the table (music bank, track, texture set, chunk, cinematic) are
covered where they are used: [sound and video](sound-and-video.md),
[stages and places](stages-and-places.md), [randomness](randomness.md).

## The CD back end

Three globals set by `File_Enable` decide how each I/O slot behaves; `File_EnableWait` retries it
until no CD operation is running.

| `g_fileEnabled`, `g_fileOption` | Mode | Used by |
| --- | --- | --- |
| 0, 0 | synchronous: `File_Locate` (`CdSearchFile`), `File_ReadSync`, `File_LoadWhole` | logos, videos, title, menu: `File_EnableWait(0, 0, 0)` before each |
| 1, 1 | queued and asynchronous, positions from the path table | the dream: `DreamRunner_Init` calls `File_EnableWait(useCdSearch == 0, 1, 1)` |
| 0, 1 | queued, but each request blocks and searches the disc | `useCdSearch` set; `g_sceneSettings` leaves it 0 ([unused switches](../discoveries.md#-switches-and-features-the-game-never-uses)) |

In the queued modes an I/O slot called with `File.direct` clear does not touch the drive:
`File_QueueRequest` appends a `FileRequest` (kind 2 open, 3 close, 4 seek, 5 read, 7 load whole)
to `g_fileRequestHead`, adds one to `pending` and hooks the vertical blank (`File_HookVSync`).

`File_OnVSync` then runs once per frame, from `VSyncCallback` when `File_Enable` got a non-zero
mode (the dream passes 1) or from the display's frame callback otherwise. It returns at once when
`g_fileLock` is set or the heap is busy, then:

1. steps the current operation: `File_PollIo` (`g_fileAsyncMode` 1: seek with `CdControlF`,
   `CdSync`, then `CdRead` and `CdReadSync`) or `File_StepIo` (mode 2: the whole-file read of
   `File_LoadWholeCd`), with a retry after 600 polls or a CD error;
2. calls `runQueue`, `File_ServiceQueue`: if the head request has not started, it sets `direct`,
   calls the matching I/O slot (which now starts the operation) and clears `direct`; if it has
   finished, it sets the `flags` bits, decrements `pending`, calls the file's `onLoaded`, frees
   the request and, when the queue is empty, unhooks the vertical blank.

So a loader written as "open, seek, read" in its constructor gets three queued requests and its
`onLoaded` called after each; it checks `flags & 0x80` to know its read is done. `File_Lock` and
`File_Unlock` only raise and clear `g_fileLock` so the callback skips a frame while the main code
edits the queue. `File_RequestLoad`, the CD `loadAsync`, writes a flag through an uninitialized
request pointer before queueing, as the original code does.

## Formats as the loaders read them

| Class (file) | Format | What `onLoaded` does |
| --- | --- | --- |
| `Tim` ([tim.c](../../src/game/tim.c)) | Sony TIM (`GsGetTimInfo` reads it from the word after the id) | nothing; slot 0x78 `Tim_Upload` sends pixels and CLUT to VRAM through `Display_LoadImage` |
| `TimPack` ([tim_pack.c](../../src/game/tim_pack.c)) | `{count, offsets[count]}` then TIMs | one borrowing `Tim` per image, each pointed at the fade of its CLUT row |
| `Tix` ([tix.c](../../src/game/tix.c)) | `STGxx\TEXx.TIX`: header `{count, offsets[4], sizes[4]}`, each part a `TimPack` | state 9 reads the header into a 0x800 buffer, state 10 reads each part into one buffer sized for the largest, uploads it, frees it; a failed `Heap_Alloc` sets `failed` (+0x80) |
| `Tmd` ([tmd.c](../../src/game/tmd.c)) | Sony TMD: id 0x41, flags, object count, 0x1C-byte object table | `GsMapModelingData`, then one `ModelObject` per TMD object (NULL-terminated array) |
| `Tod` ([tod.c](../../src/game/tod.c)) | Sony TOD: 8-byte header, frames `{u16 size, u16 packets, u32 frame}` | none; `Tod_ReadPacket` splits a packet word into id (0 to 15), type (16 to 19), flag (20 to 23), length (24 to 31) |
| `TodPack` ([tod_pack.c](../../src/game/tod_pack.c)) | `{unk, count, offsets[count]}` of TODs | a `Tod` per offset, written over the offset |
| `Mom` ([mom.c](../../src/game/mom.c)) | model: word 2 the TMD offset, a `TodPack` at +0xC | `Mom_LoadParts`: a `Tmd` and a `TodPack` borrowing its bytes |
| `Mml` ([mml.c](../../src/game/mml.c)) | `{unk, count, offsets[count]}` of MOMs | a `Mom` per offset; slot 0x88 `Mml_GetMom` hands one out |
| `MapChunk` ([map_chunk.c](../../src/game/map_chunk.c)) | `STGxx\Mxxx.LBD`, read into a fixed 0xB358-byte buffer | state 9: the chunk is in, then reads its entity part (header +0x10 offset, +0x14 size) into its own block (state 10) |
| `SeqFile` ([seq_file.c](../../src/game/seq_file.c)) | SEQ music | sets `loaded` |
| `SoundBank` ([sound_bank.c](../../src/game/sound_bank.c)) | VAB as `.VH` then `.VB` | see [sound and video](sound-and-video.md) |

An LBD chunk holds three things the code reads: at header +0x04 the tile list that `MapModels`
walks (a 20 x 20 grid of 0xC-byte records), right after it a TMD (`StageMap_BuildTiles` makes a
`Tmd` borrowing it), and at +0x10 the entity part, which is an MML that `Sym_SpawnOrSpy` opens
with `Mml_Create` ([characters](characters.md), [stages and places](stages-and-places.md)).
`ETC\SYMSPY.MOM` (the Grey Man's model, loaded by `Sym_ResetGroupsAndLoadSpy`) and `ETC\DREAMER.TMD` (loaded
by `DreamRunner_Init`) are the other model files; `ETC\SYMDOG.MOM` is named but never loaded
([the dog that never loads](../discoveries.md#-the-dog-that-never-loads)).

The TIX palettes deserve a note: each of the four 256-colour CLUT rows at VRAM y 0x1E0 + 8i
gets seven more rows under it, the same palette blended step by step toward a colour
(`Tix_BuildFade`, colour 0 kept transparent). The place gives that colour when the set is loaded
(`Tix_SetFadeColorAll`), and the renderer uses those rows for depth fog ([rendering](rendering.md)).
The texture set to load is picked by day ([the 40-day texture cycle](../discoveries.md#-the-40-day-texture-cycle)).

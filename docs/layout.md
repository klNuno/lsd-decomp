# Source file layout

The game code is split into the 68 source files the original programmers most likely had. Each file
holds its functions in address order; the files sit in link order between the Sony library objects.
The plan is `config/layout.tsv`; `tools/split_units.py docs` writes this page from it, and
`tools/split_units.py apply` replays the split from the address units of commit 4439128 (it still
makes `spu.c` and `seq_timer.c`, which turned out to be Sony's LIBSND afterwards: see below).

Confidence: **proven** means a Sony object sits on both sides of the file in .text, or the binary
rules out every other cut; **likely** means one end is proven and the other follows a class that ends
with its `X_GetVtbl`, with its vtable and data in class order; **guess** means the binary allows
another cut (each guess says which).

68 files: 12 proven, 50 likely, 6 guess.

## Files in link order

| File | Functions | Confidence | Evidence |
| --- | --- | --- | --- |
| [`main.c`](../src/game/main.c) | `main` @0x800118DC | proven | first game code, then psyq/80011994 (2MBYTE, LIBAPI, MALLOC) |
| *psyq/80011994* | Sony: 2MBYTE,LIBAPI,MALLOC | | |
| [`scene_draw.c`](../src/game/scene_draw.c) | `View_DrawNode` @0x80012064 | proven | one function between psyq/80011994 and psyq/80012768 |
| *psyq/80012768* | Sony: LIBAPI,LIBC2,LIBGS,LIBGTE | | |
| [`heap.c`](../src/game/heap.c) | `Heap_Create..Heap_IsBusy` @0x80017A20 | guess | start proven (psyq/80012768 before); Heap, Object and List with Heap_SetBusy/IsBusy after Object (gp g_heapBusy, sdata right after g_currentHeap) read as one file; heap.c plus object.c is the alternative; types already grouped in heap.h |
| [`render.c`](../src/game/render.c) | `Render_SortModel..Render_ForceClipDivision` @0x80018464 | likely | end proven (psyq/8001A564 LIBGTE after); gp g_clip*/g_texturedRgb and an sdata inversion bind all 27 functions; nothing ties them to Heap/Object; reload carry Render_ProjectTri -> Render_ProjectQuad (TRAPS) inside |
| *psyq/8001A564* | Sony: LIBGTE | | |
| [`scene_node.c`](../src/game/scene_node.c) | `SceneNode_New..SceneNode_SetRayHeightCheck` @0x8001CA94 | proven | psyq/8001A564 before, psyq/8001EF70 after; gp g_rayHeightCheck binds 34..54, the rest is the SceneNode class |
| *psyq/8001EF70* | Sony: LIBGS,LIBGTE | | |
| [`model_object.c`](../src/game/model_object.c) | `ModelObject_Create..ModelObject_SetClut` @0x8001F250 | proven | psyq/8001EF70 before, psyq/80020548 after; one class |
| *psyq/80020548* | Sony: LIBGS,LIBGTE | | |
| [`display.c`](../src/game/display.c) | `Display_New..Display_SetCurrent` @0x800206E0 | proven | psyq/80020548 before, psyq/80020C74 after; one class |
| *psyq/80020C74* | Sony: LIBAPI,LIBC2,LIBETC,LIBGPU,LIBGS,LIBGTE | | |
| [`pad.c`](../src/game/pad.c) | `Pad_New..Pad_GetVtbl` @0x80025B34 | proven | psyq/80020C74 before, psyq/80025EAC after; one class |
| *psyq/80025EAC* | Sony: LIBAPI,LIBETC | | |
| [`scene.c`](../src/game/scene.c) | `Scene_New..Scene_GetVtbl` @0x80025F7C | likely | start proven (psyq/80025EAC before); class ends with Scene_GetVtbl; only Scene functions use the unit .rodata; data order g_sceneVtbl then File data |
| [`file_base.c`](../src/game/file_base.c) | `File_Delete..File_JoinPath` @0x800269F0 | likely | end proven (psyq/80027130 LIBC2 after); data inversion g_fileVtbl after g_fileClassGetters binds 22..26, gp g_fileBackend binds 24..37; File base class and backend selection |
| *psyq/80027130* | Sony: LIBC2 | | |
| [`file_cd.c`](../src/game/file_cd.c) | `File_Create..File_GetVSyncMode` @0x800271D8 | proven | psyq/80027130 before, psyq/80028B78 after; rodata strings of File_ResolveEntries/File_SyncOpen sit before the jtbls of File_ServiceQueue (one cc1 output) and gp g_fileEnabled bind it |
| *psyq/80028B78* | Sony: LIBC2,LIBCD | | |
| [`map_models.c`](../src/game/map_models.c) | `MapModels_New..func_8002C3B8` @0x8002C12C | likely | start proven (psyq/80028B78 before); class ends with MapModels_GetVtbl, func_8002C3B8 (empty slot) kept with it |
| [`file_null.c`](../src/game/file_null.c) | `File_NullInit..File_NullGetVSyncMode` @0x8002C3C0 | likely | null File backend class, vtable g_fileNullVtbl and gp g_fileNullEnabled/Option between MapModels and Sound data |
| [`sound_bank.c`](../src/game/sound_bank.c) | `Sound_CreateBank..Sound_GetTickRate` @0x8002C480 | likely | gp/sdata block 25..40 (g_bankCount, g_soundTickRate...); vtable g_soundBankVtbl after g_fileNullVtbl |
| [`handler_node.c`](../src/game/handler_node.c) | `HandlerNode_Start..HandlerNode_Run` @0x8002CC34 | guess | end proven (psyq/8002CF18 LIBSND after); three functions with no data; could close sound_bank.c |
| *psyq/8002CF18* | Sony: LIBSND VMANAGER (SpuVmAlloc..SpuVmSeqKeyOff), near match | | |
| *psyq/800307F0* | Sony: LIBSND | | |
| *psyq/80030980* | Sony: LIBSND VMANAGER (SpuVmSetVol..SsUtKeyOffV), near match | | |
| *psyq/800319B4* | Sony: LIBSND | | |
| *psyq/80031A44* | Sony: LIBSND VMANAGER (SsUtChangePitch..SsUtAllKeyOff), near match | | |
| *psyq/80032148* | Sony: LIBSND | | |
| *psyq/8003221C* | Sony: LIBSND SSINIT (_SsInit, SsInit, SsInitHot), near match (game/spu until 2026-10-17) | | |
| *psyq/800323A8* | Sony: LIBSND | | |
| *psyq/80032588* | Sony: LIBSND SSINIT (SsSetTickMode.._SsSeqCalledTbyT_1per2), near match (game/seq_timer until 2026-10-17) | | |
| *psyq/80032B18* | Sony: LIBAPI,LIBSND | | |
| *psyq/80033C90* | Sony: LIBSND DECRE, near match | | |
| *psyq/80033FB8* | Sony: LIBSND | | |
| *psyq/8003410C* | Sony: LIBSND PLAY, SEQREAD, near match | | |
| *psyq/80035F3C* | Sony: LIBSND | | |
| *psyq/80036528* | Sony: LIBSND CRES, near match | | |
| *psyq/800368E8* | Sony: LIBSND | | |
| *psyq/80036AA8* | Sony: LIBSPU SpuInitHot, near match | | |
| *psyq/80036AC8* | Sony: LIBAPI,LIBSPU | | |
| *psyq/80038D54* | Sony: LIBSPU SpuInit, near match | | |
| *psyq/80038D74* | Sony: LIBAPI,LIBSPU | | |
| [`bgm.c`](../src/game/bgm.c) | `Bgm_New..Bgm_GetSeqTable` @0x800398E0 | proven | psyq/80038D74 before, psyq/8003A078 after; gp binds 1..15 |
| *psyq/8003A078* | Sony: LIBSND | | |
| *psyq/8003A670* | Sony: LIBSND SEQINIT, near match | | |
| *psyq/8003AA68* | Sony: LIBSND | | |
| [`app.c`](../src/game/app.c) | `App_Init..App_GetVtbl` @0x8003AF8C | proven | psyq/8003AA68 before, psyq/8003B21C after |
| *psyq/8003B21C* | Sony: LIBCD,LIBGS | | |
| [`tim.c`](../src/game/tim.c) | `Tim_New..Display_RotateRect` @0x8003B39C | proven | psyq/8003B21C before, psyq/8003B770 after; Display_RotateRect is a helper after Tim_GetVtbl |
| *psyq/8003B770* | Sony: LIBGS | | |
| [`video_screen.c`](../src/game/video_screen.c) | `VideoScreen_New..VideoScreen_GetVtbl` @0x8003B854 | likely | start proven (psyq/8003B770 before); class ends with its GetVtbl; g_videoScreenVtbl first in the unit data |
| [`menu_screen.c`](../src/game/menu_screen.c) | `MenuScreen_New..MenuScreen_GetPictureRect` @0x8003BE94 | likely | data inversions bind 24..69; both jtbls of the unit are MenuScreen; GetPictureRect follows its GetVtbl |
| [`screen.c`](../src/game/screen.c) | `Screen_Init..Screen_GetVtbl` @0x8003DFDC | likely | base class Screen, g_screenVtbl between MenuScreen and View data |
| [`view.c`](../src/game/view.c) | `View_New..View_SetGeomScreen` @0x8003E5D8 | likely | end proven (psyq/8003F2AC after); sdata inversions bind 83..101; owns the gp record g_viewDefaultScreenSize (.sdata subsegment) |
| *psyq/8003F2AC* | Sony: LIBGS,LIBGTE | | |
| [`fade.c`](../src/game/fade.c) | `Fade_Create..Fade_GetVtbl` @0x8003FDB0 | likely | start proven (psyq/8003F2AC before); data inversion binds 9..13; class ends with GetVtbl |
| [`box.c`](../src/game/box.c) | `Box_Create..Box_GetVtbl` @0x800404D0 | likely | class with Rgb_CopyOrAdd helper inside; g_boxVtbl after Fade data |
| [`label.c`](../src/game/label.c) | `Label_Create..Label_GetVtbl` @0x800408CC | likely | class ends with GetVtbl; g_labelVtbl last in unit data |
| [`text.c`](../src/game/text.c) | `Text_Decode..Text_FormatNumber` @0x80040FC0 | guess | end proven (psyq/8004117C after); three Shift-JIS helpers with no data, could close label.c |
| *psyq/8004117C* | Sony: LIBC,LIBC2 | | |
| [`glyph.c`](../src/game/glyph.c) | `Glyph_Create..Glyph_GetRect` @0x80041AB4 | likely | start proven (psyq/8004117C before); vtables of the unit follow class order |
| [`screen_sprite.c`](../src/game/screen_sprite.c) | `ScreenSprite_Create..ScreenSprite_GetVtbl` @0x80041C9C | likely | data inversion binds 10..13; only jtbl of the unit |
| [`sprite_node.c`](../src/game/sprite_node.c) | `SpriteNode_Create..SpriteNode_GetVtbl` @0x80041EE8 | likely | class ends with GetVtbl, vtable in class order |
| [`seq_file.c`](../src/game/seq_file.c) | `SeqFile_Create..SeqFile_GetVtbl` @0x800422CC | likely | class ends with GetVtbl, vtable in class order |
| [`clock.c`](../src/game/clock.c) | `Clock_Create..Clock_GetVtbl` @0x80042400 | likely | class ends with GetVtbl, vtable in class order |
| [`root_node.c`](../src/game/root_node.c) | `RootNode_Create..RootNode_GetVtbl` @0x80042694 | likely | end proven (psyq/800428F4 after) |
| *psyq/800428F4* | Sony: LIBGS | | |
| [`flat_light.c`](../src/game/flat_light.c) | `FlatLight_New..FlatLight_GetVtbl` @0x8004291C | proven | psyq/800428F4 before, psyq/80042A8C after: a 6-function class alone, the clearest sign of one class per file |
| *psyq/80042A8C* | Sony: LIBGS | | |
| [`tix.c`](../src/game/tix.c) | `Tix_Create..Tix_GetVtbl` @0x80043008 | likely | start proven (psyq/80042A8C before); gp binds 1..8 |
| [`tmd.c`](../src/game/tmd.c) | `Tmd_Create..Tmd_GetVtbl` @0x80043840 | likely | class ends with GetVtbl |
| [`tim_pack.c`](../src/game/tim_pack.c) | `TimPack_Create..TimPack_GetVtbl` @0x80043B88 | likely | class ends with GetVtbl |
| [`tod.c`](../src/game/tod.c) | `Tod_Create..Tod_GetVtbl` @0x80043E84 | likely | class ends with GetVtbl |
| [`bg.c`](../src/game/bg.c) | `Bg_Create..Bg_GetVtbl` @0x800441B4 | likely | class ends with GetVtbl |
| [`mom.c`](../src/game/mom.c) | `Mom_Create..Mom_GetVtbl` @0x8004468C | likely | class ends with GetVtbl |
| [`mml.c`](../src/game/mml.c) | `Mml_Create..Mml_GetVtbl` @0x80044A0C | likely | class ends with GetVtbl |
| [`bg_map.c`](../src/game/bg_map.c) | `BgMap_Create..BgMap_GetVtbl` @0x80044CD4 | likely | class ends with GetVtbl |
| [`bg_cells.c`](../src/game/bg_cells.c) | `BgCells_Create..BgCells_GetVtbl` @0x80044F30 | likely | class ends with GetVtbl |
| [`tod_pack.c`](../src/game/tod_pack.c) | `TodPack_Create..TodPack_GetVtbl` @0x800451B8 | likely | class ends with GetVtbl |
| [`movie.c`](../src/game/movie.c) | `Movie_Create..Movie_GetVtbl` @0x80045438 | likely | end proven (psyq/80045E54 LIBPRESS after); gp binds 80..93 |
| *psyq/80045E54* | Sony: LIBAPI,LIBC,LIBC2,LIBPRESS | | |
| [`stream.c`](../src/game/stream.c) | `Stream_New..Stream_GetVtbl` @0x80046F0C | proven | psyq/80045E54 before, psyq/80047910 after; gp binds 4..15 |
| *psyq/80047910* | Sony: LIBCD | | |
| [`map_chunk.c`](../src/game/map_chunk.c) | `MapChunk_New..MapChunk_GetVtbl` @0x80048894 | likely | start proven (psyq/80047910 before); class ends with GetVtbl, g_mapChunkVtbl first in unit data |
| [`path_table.c`](../src/game/path_table.c) | `File_GetRootDir..Cine_GetSpecialDayRun` @0x80048CF0 | likely | end proven (psyq/80049480 rand after); data inversion g_musicBanks/g_stageFirstPath before g_pathTable binds 14..19, gp music overrides 13..23; SND strings then ETC\ASMK.STR in rodata |
| *psyq/80049480* | Sony: LIBC2 | | |
| [`stage.c`](../src/game/stage.c) | `Stage_GetCount..Stage_GetChunkMood` @0x800494B4 | guess | start proven (psyq/80049480 before); stage table accessors with their own tables, data before DreamRunner data; could open dream_runner.c |
| [`dream_runner.c`](../src/game/dream_runner.c) | `DreamRunner_New..File_ResolvePathTablePart` @0x80049608 | guess | data inversion binds 12..19; File_ResolvePathTablePart (own gp pair) placed after DreamRunner_GetVtbl by guess |
| [`task.c`](../src/game/task.c) | `Task_New..Task_GetVtbl` @0x8004A130 | likely | class ends with GetVtbl, g_taskVtbl after DreamRunner data |
| [`stage_map.c`](../src/game/stage_map.c) | `StageMap_New..StageMap_GetVtbl` @0x8004A4C8 | likely | data inversions bind 34..94 (MapTile_Tell, Stage_PlaceToWorld inside) |
| [`dream_view.c`](../src/game/dream_view.c) | `DreamView_New..DreamView_GetVtbl` @0x8004D254 | likely | class ends with GetVtbl, vtable in class order |
| [`map_tile.c`](../src/game/map_tile.c) | `MapTile_New..MapTile_GetVtbl` @0x8004D38C | likely | class ends with GetVtbl, last data of the unit |
| [`menu.c`](../src/game/menu.c) | `Menu_New..Menu_GetVtbl` @0x8004D518 | likely | rodata object B (string after DreamRunner_OnPlaceMessage jtbl) proves a boundary in (0x80049EB4, 0x8004D578]; Menu_New opens the class; gp g_cardTitle etc. bind Menu_Init..Menu_GetVtbl |
| [`card.c`](../src/game/card.c) | `Card_New..Card_SetTitleLetter` @0x8004E2E0 | likely | end proven (psyq/800508E8 LIBCARD after); data and sdata inversions bind 41..76 |
| *psyq/800508E8* | Sony: LIBAPI,LIBC2,LIBCARD | | |
| [`comment_object.c`](../src/game/comment_object.c) | `CommentObject_New..CommentObject_GetVtbl` @0x80050BA8 | likely | start proven (psyq/800508E8 before); end proven to lie in (CommentObject_SetChar, StringList_Open]: FONTICON is stored twice (cc1 merges equal literals per file) and gp g_alphabet binds 1..25; exact cut at the class end likely |
| [`string_list.c`](../src/game/string_list.c) | `StringList_New..StringList_GetVtbl` @0x80051A5C | likely | object D (alphabet copy after CommentObject_OnKey jtbl); StringList methods are copies of CommentObject ones; gp/rodata bind StringList_Open..StringList_SetView |
| [`place.c`](../src/game/place.c) | `Place_New..Place_GetVtbl` @0x80052B70 | likely | gp and data inversions bind Place_Load..Place_GetVtbl; Place jtbl follows the StringList jtbl (no constraint) |
| [`scenery.c`](../src/game/scenery.c) | `Scenery_Begin..Ambience_IsEvenFamily` @0x800544E4 | likely | proven one file: sdata gp g_sceneryMap and 13 sbss statics bind 60..102; ETC\ETCSE after the Place jtbl proves a boundary after Place_OnDreamSysNotify; separate from place.c and scenery_obj.c by guess (Scenery_SetPlaceRefs setter) |
| [`scenery_obj.c`](../src/game/scenery_obj.c) | `Scenery_New..Scenery_SetPlaceRefs` @0x80056320 | likely | gp g_sceneryModels/View/Font bind 108..124; class ends with GetVtbl then the setter the manager calls |
| [`actor.c`](../src/game/actor.c) | `Actor_New..Actor_GetVtbl` @0x80056FE4 | likely | class ends with GetVtbl, g_actorVtbl after Scenery data |
| [`scenery_part.c`](../src/game/scenery_part.c) | `SceneryPart_New..SceneryPart_GetVtbl` @0x80057C94 | likely | data inversion binds 157..164 |
| [`graph.c`](../src/game/graph.c) | `Graph_New..Graph_GetVtbl` @0x80057F68 | likely | ETC\ETCSE (Graph_Init) after the Place jtbl proves a boundary before Graph_Init; [ETCSE][ETC\HGRAPH.TIM] is 0x1C bytes so the DreamSys jtbl at 0x80011788 is 8-aligned in its own object: the 0x80058078 cut is not forced; one class |
| [`dream_sys.c`](../src/game/dream_sys.c) | `DreamSys_New..DreamSys_GetVtbl` @0x80058774 | likely | data inversions bind DreamSys_Reset..DreamSys_GetVtbl (Mood_* inside); jtbls of DreamSys_OnPad and DreamSys_OnEntityEvent |
| [`dream_link.c`](../src/game/dream_link.c) | `Nav_InitFlags..Day_FindSpecial` @0x8005BA50 | guess | gp g_navFlags binds 112..128; Sym strings after the DreamSys jtbl prove a boundary after DreamSys_GetVtbl, Link_Find, Spawn_PickFromMood or Day_FindSpecial; could close dream_sys.c |
| [`sym.c`](../src/game/sym.c) | `Sym_ResetGroupsAndLoadSpy..Sym_SpawnSpy` @0x8005C508 | likely | rodata object F starts with its strings (proven boundary in (0x8005B03C, 0x8005C508]); gp g_sym* and data inversions bind 0..16 |
| [`entity.c`](../src/game/entity.c) | `Entity_Create..Behavior_Type129` @0x8005CFDC | likely | proven one file for Entity_Attach..Behavior_TinyLips: 670+ data inversions between entity records and behaviour tables; Entity_Create..Init and Behavior_Type129 by adjacency |
| [`model.c`](../src/game/model.c) | `Model_New..Model_GetVtbl` @0x800655D4 | likely | end proven (end of .text); class ends with GetVtbl, g_modelVtbl last |

## Rodata

A C file emits its strings and constants at parse time and its jump tables after the function
bodies; `INCLUDE_RODATA` lines place the symbols that are not migrated. Each `.rodata` entry of
`config/splat.yaml` names the file whose functions use it:

| ROM offset | Address | File |
| --- | --- | --- |
| 0xA8C | 0x8001028C | `heap.c` |
| 0xB54 | 0x80010354 | `model_object.c` |
| 0xF64 | 0x80010764 | `pad.c` |
| 0xFA4 | 0x800107A4 | `scene.c` |
| 0xFD8 | 0x800107D8 | `file_cd.c` |
| 0x17EC | 0x80010FEC | `bgm.c` |
| 0x1890 | 0x80011090 | `menu_screen.c` |
| 0x1A90 | 0x80011290 | `screen_sprite.c` |
| 0x1B84 | 0x80011384 | `path_table.c` |
| 0x1BEC | 0x800113EC | `dream_runner.c` |
| 0x1C34 | 0x80011434 | `menu.c` |
| 0x1D0C | 0x8001150C | `card.c` |
| 0x1DD0 | 0x800115D0 | `comment_object.c` |
| 0x1EA4 | 0x800116A4 | `string_list.c` |
| 0x1F4C | 0x8001174C | `place.c` |
| 0x1F6C | 0x8001176C | `graph.c` |
| 0x1F88 | 0x80011788 | `dream_sys.c` |
| 0x206C | 0x8001186C | `sym.c` |

## How the boundaries were found

| Source | What it shows | Strength |
| --- | --- | --- |
| Sony objects between game code in .text | A file boundary on each side | Proven |
| Data order | .data, .sdata and the small .sbss statics follow link order, Sony objects included. Two symbols in inverted order bind their users into one file. | Proven, if a symbol is defined in a file that uses it |
| gp access | maspsx only reaches through gp the symbols a file defines or declares `.comm`. No gp symbol is reached through gp from two files, so all its gp users are one file. | Proven for .sdata; for .sbss it assumes no shared `.comm` |
| Rodata (cc1 2.6.3) | A string after a jump table starts a new file; a string used by a function placed before the jump table of an earlier function binds the range. | Proven where it applies |
| Equal literals | cc1 merges identical string literals in one file: two stored copies ("FONTICON") mean two files. | Proven |
| One class per file | FlatLight, Pad, Display, Bgm, App, Tim, Stream, ModelObject and SceneNode each sit alone between Sony objects. Classes end with `X_GetVtbl`, and vtables follow class order. | Convention: likely |
| Text padding | None between game functions | No signal |

`make check` cannot judge a layout: any cut matches as long as each file declares the gp symbols it
uses (rule 1 below). The 46 boundaries between two game functions rest on the evidence above; 23
are proven exactly by a Sony object.

The study corrected one older claim: the cut at 0x80058078 is not forced. `ETC\ETCSE` and
`ETC\HGRAPH.TIM` form one rodata object of 0x1C bytes, so DreamSys's first jump table at
0x80011788 is 8-aligned in its own object either way, and Graph_New, Graph_Init and
Graph_LoadImage..Graph_GetVtbl read as one class file, `graph.c`.

A later check corrected the study itself (2026-10-17): `spu.c` and `seq_timer.c`, two files it
rated proven because a Sony object sits on each side, are Sony code too. Their 11 functions line up
one to one with the labels of LIBSND's `SSINIT.OBJ` in PSY-Q 3.3 (`_SsInit`, `SsInit`,
`SsInitHot`, `SsSetTickMode`, `_SsStart`, `SsStart`, `SsStart2`, `SsEnd`, `SsQuit`,
`_SsTrapIntrVSync`, `_SsSeqCalledTbyT_1per2`), ten of them word for word and `_SsInit` at 88 %
of its words; the game links a LIBSND build the signature database lacks. They are the Sony units
`psyq/8003221C` and `psyq/80032588` now (names in `tools/psyq/match.py`, `NEAR_MATCHES`); the 46 and
23 boundaries counted above are the study's and include those two files.

## Rules for contributors

1. **A small global (8 bytes or less) reached through gp is declared without `extern` in every file
   that uses it**, as a tentative definition (`s32 g_fileBackend;`). cc1 emits `.comm`, maspsx
   reaches it through gp, and the linker merges it with the asm data. An `extern` gives `lui`
   accesses and shifts the whole executable. Never move such a declaration into a header with
   `extern`.
2. **An initialized gp record is defined, with its initializer, at the end of the file that uses
   it**: `g_viewDefaultScreenSize` in `view.c`, `g_bandPos` and `g_bandSize` in `scenery.c`. Their
   `.sdata` entries in `config/splat.yaml` name those files.
3. **No `static` variable while the data lives in asm**: it would allocate bytes in the C object and
   duplicate the data. File statics stay tentative definitions. A function is `static` when no other
   file calls it and no data points to it (275 are); one that a vtable or table in asm names stays
   global, or the link fails. `static` keeps the bytes but changes the relocations, so
   `tools/unit_check.sh --save` must run again after one is added or removed.
4. A file with rodata keeps its `.rodata` entry in `config/splat.yaml` (dot form, same name); an
   `INCLUDE_RODATA` path names `asm/nonmatchings/game/<file>`. After renaming a file, run
   `make split` twice: splat writes the `.s` only once the C file names it.
5. GCC 2.6.3 carries reload choices from one function to the next (`Render_ProjectTri` then
   `Render_ProjectQuad` in `render.c`): keep functions in address order inside a file.
6. **A file's header, `include/game/<file>.h`, holds its class and declares what other files call or
   reference**: the structs, vtable and constants of the class the file defines, then its functions
   in the form of their definition, parameter names included, and the non-gp globals other files
   read, with `extern`. A class header includes its base class's header (heap.h for Object, then
   scene_node.h, screen.h, task.h or file_base.h, then the subclasses). A small type several classes
   share sits with the class that uses it most (ScreenPoint, ScreenRect and ScreenSize in display.h,
   SjisChar in text.h, StagePlace in stage.h); gs.h is the one shared header, PSY-Q-like types. Sony
   functions are declared in `include/psyq/<lib>.h`. A file includes its own header first, then the
   header of every file it uses, and keeps no local copy; only gp globals (rule 1), forward
   declarations of its own helpers and the exceptions listed in [naming.md](naming.md#prototypes)
   stay in the file. The
   Makefile does not track headers: after editing one, `rm -rf build/src && make check` (not
   `make clean`, which also deletes the unit_check references in `build/ref`), then
   `tools/unit_check.sh` on every file that includes it.
7. **The build must stay shiftable: every address in it is a symbol the linker can move.** After
   `make check`, `python3 tools/rawscan.py` links the objects a second time with `.main` 0x10000
   higher and lists every word that did not move although it points into the executable (data
   pointers, `jal`, `lui` of an address). Read a field of the containing table in C
   (`g_entityRecords[i].link`, `g_ruleColors[rule - 10]`) instead of declaring a symbol in the
   middle of it, and give a string or a label that data points at its own entry in
   `config/symbol_addrs.txt` (Sony ones in the hand-kept block of `symbol_addrs.psyq.txt`), so that
   `linker/undefined_syms_auto.txt` keeps only `D_7FFFFF`. A label splat writes at an address that is
   not word aligned needs `defined:True`, or splat also writes it there as a fixed number. `tools/rawscan.py
   --max 0` must exit 0: the count is 0 since 2026-10-16. The last raw words were in files splat
   writes: Sony's startup (`asm/psyq/80011994.s`, written as `.word` because the function ends in a
   table) and the header's initial pc and .text size. `make split` runs `tools/postsplit.py` after
   splat to write them as symbols, and `_gp` comes from `ld_gp_expression` in `config/splat.yaml`.
   A build with 0x100 bytes of code added before `main` plays like the retail game (logos, title, a
   dream, its links and the fall, pixel for pixel).

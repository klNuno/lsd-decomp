"""Historical: unit comment blocks for the files cut out of a unit that held several classes, used once by
tools/split_units.py to replay the split of commit 6c028b9; headers and names are those of that commit.
A file missing here keeps its unit's comment whole (one-file units) or gets only the boundary line."""

HEADERS = {
    'scene': '''/*
 * The scene (vtable g_sceneVtbl, 0x2C bytes, made by Scene_New from main with the settings
 * g_sceneSettings): it derives from the App class of src/game/app.c (vtable 0x8006E4F0), whose run
 * loop App_Run calls slot 0x50 logos, then forever slot 0x54 opening video and slot 0x58
 * title; a title result of 2 runs the dream (slot 0x60), and a non-zero dream result plays the
 * ending (slot 0x64). docs/discoveries.md, "The ending plays when a year closes".
 */''',
    'file_base': '''/*
 * The file base class (vtable g_fileBaseVtbl, returned by File_GetBaseVtbl, include/game/loader.h):
 * delete, init, destroy, load the whole file, free its data. File_SetBackend picks the back end
 * (0x13 the CD, 0x23 an empty one) and copies its I/O slots into every file class; the helpers
 * at the end forward to the CD functions of src/game/file_cd.c only when the CD back end is on.
 */''',
    'map_models': '''/*
 * MapModels: the model list of one map chunk (vtable 0x8006D940, made by MapModels_New).
 */''',
    'file_null': '''/*
 * The null file back end (vtable g_fileNullVtbl, File_GetNullVtbl): the back end 0x23 that
 * File_SetBackend of src/game/file_base.c can pick; every I/O slot is empty.
 */''',
    'sound_bank': '''/*
 * Sound: the PSY-Q sound bank (VAB) that a model holds at +0x58 and its tone table (vtable
 * g_soundBankVtbl). Several functions see the bank through a view struct where a field has another
 * type or width there.
 */''',
    'handler_node': '''/*
 * The handler nodes that play sounds from a model's sound bank once per tick (see src/game/entity.c):
 * HandlerNode_Start registers a behaviour handler, HandlerNode_Run calls it, then plays the sounds it
 * asked for.
 */''',
    'video_screen': '''/*
 * VideoScreen (include/game/scene.h): the MenuScreen that plays one STR video (vtable 0x8006E5F8).
 */''',
    'menu_screen': '''/*
 * MenuScreen (include/game/scene.h): a Screen with sound bank, picture, fades, timeout and an item
 * menu (vtable 0x8006E730): logos, special-day pictures, the main menu.
 */''',
    'screen': '''/*
 * Screen (include/game/scene.h): the base screen class (vtable 0x8006E878), a state machine run by
 * the display loop, with clock, pad and view.
 */''',
    'view': '''/*
 * View (include/game/scene.h): the 3D view (vtable 0x8006E8E4): GsRVIEW2, double ordering tables,
 * fog and light mode.
 */''',
    'fade': '''/*
 * Fade: the Box that fades a color over the screen (the view's overlay, the Place fader, the entity
 * effect). A 2D widget drawn by the scene tree (src/game/scene_draw.c).
 */''',
    'box': '''/*
 * Box: a filled rectangle, a 2D widget drawn by the scene tree (src/game/scene_draw.c).
 */''',
    'label': '''/*
 * Label: a row of character glyphs, a 2D widget drawn by the scene tree (src/game/scene_draw.c).
 */''',
    'text': '''/*
 * The Shift-JIS text helpers: decode, encode and format a number.
 */''',
    'glyph': '''/*
 * Glyph: vtable g_glyphVtbl 0x8006EC74 (tag 0x1144), 0xAC bytes, Glyph_Create: a ScreenSprite
 * showing one 8x8 character of a font image laid out 32 characters per row. Like ScreenSprite and
 * SpriteNode, a scene node (base SceneNode_GetVtbl, vtable 0x8006B5CC, tag 4) that draws a libgs
 * GsSPRITE cut from a TIM image; slots 0x60 to 0x68 work on the sprite's attribute word instead of
 * the node's.
 */''',
    'screen_sprite': '''/*
 * ScreenSprite: vtable g_screenSpriteVtbl 0x8006ED4C (tag 0x144), 0xA8 bytes, ScreenSprite_Create:
 * a SpriteNode (src/game/sprite_node.c) attached with a 2D position (slot 0x4C) and a pivot (slot
 * 0xC0). The comment keyboard's input box, the card menu's message and the list backgrounds.
 */''',
    'sprite_node': '''/*
 * SpriteNode: vtable g_spriteNodeVtbl 0x8006EE1C (tag 0x44), 0xA0 bytes, SpriteNode_Create. A scene
 * node (base SceneNode_GetVtbl, vtable 0x8006B5CC, tag 4) that draws a libgs GsSPRITE cut from a TIM
 * image; its slots 0x60 to 0x68 work on the sprite's attribute word instead of the node's.
 */''',
    'seq_file': '''/*
 * SeqFile: vtable g_seqFileVtbl 0x8006EED8 (tag 0xB03), 0x30 bytes, SeqFile_Create: a file class
 * (loader.h) loaded with loadAsync; the music player (src/game/bgm.c) hands its data to SsSeqOpen
 * once +0x2C is set.
 */''',
    'clock': '''/*
 * Clock: vtable g_clockVtbl 0x8006EF50 (tag 5), 0x1C bytes, Clock_Create: each step adds a tick and
 * tells every watcher 2, or 3 when paused, 4 when stopped (scene.h).
 */''',
    'root_node': '''/*
 * RootNode: vtable g_rootNodeVtbl 0x8006EFAC (tag 0x14), 0x54 bytes, RootNode_Create: a scene node
 * holding 3 lights (FlatLight_New) and the ambient color; the default root of a screen (scene.h
 * ScreenEnv) and the base class of StageMap.
 */''',
    'tix': '''/*
 * Tix: a TEXx.TIX texture set file and its palette fades (include/game/loader.h).
 */''',
    'tmd': '''/*
 * Tmd: a TMD model file and its model objects (include/game/loader.h).
 */''',
    'tim_pack': '''/*
 * TimPack: one part of a TIX, a list of TIM images (include/game/loader.h).
 */''',
    'tod': '''/*
 * Tod: a TOD animation file (include/game/loader.h).
 */''',
    'bg': '''/*
 * Bg: a PSY-Q GsBG background object (include/game/loader.h).
 */''',
    'mom': '''/*
 * Mom: a MOM model file, a TMD and a TodPack (include/game/loader.h).
 */''',
    'mml': '''/*
 * Mml: the list of MOM models of a map square (include/game/loader.h).
 */''',
    'bg_map': '''/*
 * BgMap: the GsMAP of a Bg (include/game/loader.h).
 */''',
    'bg_cells': '''/*
 * BgCells: the GsCELL table of a BgMap (include/game/loader.h).
 */''',
    'tod_pack': '''/*
 * TodPack: a list of TOD files, the motions of a MOM (include/game/loader.h).
 */''',
    'movie': '''/*
 * The MDEC movie player (vtable g_movieVtbl, include/game/loader.h). It owns a CD stream of
 * src/game/stream.c (Movie +0x60).
 */''',
    'map_chunk': '''/*
 * The map chunk file class (vtable g_mapChunkVtbl, 0x3C bytes, created by MapChunk_New for each
 * StageMap slot): a file object of src/game/file_base.c with a 0xB358-byte buffer that receives a
 * stage's STGxx\\Mxxx.LBD chunk file (slot 0x78), then, when the header says so, a second read of
 * the chunk's entity part into its own heap block (slot 0x80). include/game/stage.h holds the
 * part of it StageMap reads (MapChunk); MapChunk below is the whole object.
 */''',
    'path_table': '''/*
 * The path table g_pathTable: 0x1C-byte path entries, 560 counted by File_GetPathTable (sound banks, then per stage
 * TEXA to TEXD.TIX, BGA to BGE.SEQ and the Mxxx.LBD chunks from g_stageFirstPath[stage]), then the
 * opening, ending, event and special-day videos. The getters below hand out pieces of it, with
 * the video id (index into g_videoTable) through their out parameter.
 */''',
    'stage': '''/*
 * Stage tables (types in game/stage.h): one entry per STGxx folder, 0 to 13 (time limits, chunk
 * moods, spawn points, paths).
 */''',
    'dream_runner': '''/*
 * DreamRunner (vtable g_dreamRunnerVtbl 0x800865C8, types in game/stage.h): the object built for
 * each dream. It loads the dreamer model and the music bank, creates the place, rebuilds it after a
 * link.
 */''',
    'task': '''/*
 * Task (vtable g_taskVtbl 0x80086668, types in game/stage.h): a class with a tick count, a timeout
 * and a result that DreamRunner and Place derive from.
 */''',
    'stage_map': '''/*
 * StageMap (vtable g_stageMapVtbl 0x800866E8, types in game/stage.h): the map that keeps the 7
 * chunks around the dreamer loaded and shows the tiles in view.
 */''',
    'dream_view': '''/*
 * DreamView (vtable g_dreamViewVtbl 0x800869D8): the dream camera, a View subclass of 0xDC bytes.
 */''',
    'map_tile': '''/*
 * MapTile (vtable g_mapTileVtbl 0x80086AA0, types in game/stage.h): one tile model of a chunk, a
 * GsDOBJ2 at +0x10.
 */''',
    'menu': '''/*
 * The main menu (class Menu, vtable g_menuVtbl 0x80086B60). It drives the memory card object of
 * src/game/card.c. Types and states: include/game/menu.h.
 */''',
    'card': '''/*
 * The memory card object the main menu drives (class Card, vtable g_cardVtbl 0x80086DC4). Types and
 * states: include/game/menu.h.
 */''',
    'sym': '''/*
 * Sym: entities loaded from ETC\\SYM*.MOM; only SYMSPY.MOM is loaded.
 */''',
    'entity': '''/*
 * Entities and their behaviour handlers (record +0xC). A handler runs once per tick as
 * handler(entity, node): Entity_StartHandler registers it in the node at Entity +0x9C
 * (HandlerNode_Start) and slot 0x11C (Entity_RunHandler) runs HandlerNode_Run, which calls the
 * handler, then plays the sounds the handler asked for on the entity's sound bank (+0x58).
 */''',
    'model': '''/*
 * Model: the model base class every entity derives from (vtable g_modelVtbl 0x8008A6C4, 0x98
 * bytes): model file, parts, animation, per-tick function, sound bank.
 */''',
}

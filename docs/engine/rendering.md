# Rendering

The game draws with Sony's libgs pipeline, but the 3D models go through its own sorter: a scene
graph of nodes is walked once per frame, each model's faces are projected on the GTE and written
as GPU packets into an ordering table, and the table built in the last frame is drawn while the
next one is filled. Depth fog does not change colours on the fly: textured faces pick one of eight
palette rows prepared when the texture set loads. This page covers the view, the scene walk,
`Render_SortModel`, clipping, fog, and the 2D objects (sprites, boxes, fades).

## Display and View

[`Display`](../../src/game/display.c) owns the PSY-Q graphics setup: `GsInitGraph` with the
screen size (320 x 240, interlace off, dithering on), two display buffers stacked in VRAM, the
frame loop (see [boot and objects](boot-and-objects.md#screens-and-the-frame)) and the VRAM
transfers `loadImage`, `storeImage`, `moveImage` and `clearImage`. `loadImage` and `storeImage`
run only while the frame loop is stopped, unless `syncDraw` is set (it is by default), in which
case they also wait for `DrawSync`.

[`View`](../../src/game/view.c) (0xBC bytes, class word 7) is the camera and the ordering tables.
`View_Reset` sets the defaults:

| Field | Default | Used for |
| --- | --- | --- |
| `otBits` | 13 | each ordering table has 2^13 entries |
| `packetCount`, `packetSize` | 2000, 0x40 | GPU packet area per buffer |
| `projection` | 0x100 | `SetGeomScreen` |
| `nearZ`, `farZ` | 10, 0x10000 | sprite culling and the sprite OT step |
| `lightMode` | 0 | `GsSetLightMode`; 1 and 3 turn fog on |
| `fogNear`, `fogColor` | 20000, default colour | `SetFogNear`, `SetFarColor` |
| `clearColor` | default colour | `GsSortClear` |

Screens change some of them before `allocOt`: a `MenuScreen` uses 3 bits and 300 packets, the
main menu 400 packets, the dream runner 1200 packets. `View_AllocOt` takes one heap block for both
buffers: per buffer a `GsOT` header, 4 << `otBits` bytes of entries, then the packet area.

A view watches a display (type 1), a clock (type 5) and at most one scene node (type 4), its
camera target. `View_SetCamera` watches the node and sets the `GsRVIEW2` viewpoint, reference
point and twist relative to the node's coordinate system (`super`). It also owns a root node of
its own, with a 320 x 240 `Fade` hung from it as an overlay (`View_Init`); the dream uses it as the
place's fader ([stages and places](stages-and-places.md)). In a dream the view is a `DreamView`
([dream_view.c](../../src/game/dream_view.c)), a `View` whose render does nothing until a node is
watched.

## One frame of drawing

- **Clock tick, `View_OnClock`:** on message 2 (tick) or 3 (paused) it calls `View_Render`, which
  sets `SetGeomScreen`, passes `nearZ` to a Sony routine (`func_8003FB0C`), sets the light mode and, for modes 1 and 3, the fog colour and
  distance, calls `GsSetRefView2`, computes the sprite step `otZStep = (farZ - nearZ) / 2^otBits
  + 1`, resets the packet cursor to this buffer's area and clears its table, then sorts two trees
  with slot 0xA0 (`Scene_DrawNode`): the view's own root, and the whole tree above the watched
  node (`SceneNode_GetRoot`). It first sorts the watched node alone when it has a parent; since
  the table is cleared right after, our reading is that this pass only refreshes its matrices.
- **Display message 2, `View_OnDisplay`:** `View_Present` reads the active buffer, calls
  `ResetGraph(1)` and `GsSwapDispBuff`, sorts a clear with `clearColor`, draws that buffer's table
  with `GsDrawOt`, and flips `buffer`. With `presentEnabled` 0 it skips all of this: the pause sets
  it after four ticks, so the picture freezes
  ([the pause](../discoveries.md#-select--triangle-in-the-pause-erases-your-game)). `extraSwap`,
  a second swap, is never set.

## The scene walk

A [`SceneNode`](../../include/game/scene_node.h) (0x44 bytes) is a libgs `GsDOBJ2` with a parent:
attribute word at +0x10, a `GsCOORDINATE2` at +0x14 (allocated with its `GsCOORD2PARAM` in
`SceneNode_Init`), the TMD object at +0x18. Attaching a node (`SceneNode_Attach`, slot 0x4C) makes
the parent watch it and sets the coordinate's `super`; watching a `ModelObject` (type 9) links its
TMD object (`SceneNode_LinkModel`). Slots 0x60 to 0x80 set attribute bits with libgs meanings:

| Bits | Slot | Meaning |
| --- | --- | --- |
| 31 | 0x60 `SetVisible` | hidden (`GsDOFF`): `Render_SortModel` returns at once |
| 30, 28-29 | 0x64, 0x68 | semi-transparent, blend rate |
| 9-11 | 0x7C `SetDivision` | subdivision passed to the clipper |
| 8, 7 | 0x80, 0x78 | no back-face cull, no z sort |
| 6 | 0x6C `SetLit` | unlit: packet code bit 0 set (texture drawn raw) |
| 3-5 | 0x70 `SetLightFlags` | read by the fog test below |

[`Scene_DrawNode`](../../src/game/scene_draw.c) is recursive. When a node's coordinate is dirty
(`flg` 0) it rebuilds the matrix with `RotMatrix` and the node's scale and marks every child dirty;
then it draws the children (watched type-4 objects whose parent is this node), then the node
itself, chosen by the low byte of its class word:

| Kind | Classes | How it is sorted |
| --- | --- | --- |
| 0x54 | `Bg` | `GsSortBg` at the last table entry (behind everything) |
| 0x64 | `Box`, `Fade` | `GsSortBoxFill` at its priority; size in pixels or in percent of half the screen |
| 0x44 with 0x144 | `ScreenSprite`, `Glyph`, `Label` | 2D: position from a scale of half the screen plus an offset, `GsSortSprite` at entry 0 (in front) |
| 0x44 | `SpriteNode`, `SceneryPart` | 3D: `GsGetLs`, projected by hand (`x * projection / z`), dropped behind `nearZ`, x and y clamped to 512, entry `(z - nearZ) / otZStep` |
| other | models, map tiles, `DreamSys` | `GsGetLws`, light and screen matrices, then `Render_SortModel` with shift `14 - otBits` and the scratchpad as work area; a hidden 0x24 map tile is skipped |

## Render_SortModel

[`Render_SortModel`](../../src/game/render.c) replaces libgs's own TMD sorters. It walks the
model's primitive groups (`u16 count`, `u16 type`), and for each type it supports writes one
packet per face at `g_packetCursor`:

| Group type (`& 0xFD07`) | Packet | Colour |
| --- | --- | --- |
| 0x2000, 0x2800 | F3, F4 | lit, `gte_ncds` from the face normal |
| 0x2004 | G3 | lit per vertex colour, same normal |
| 0x2400, 0x2C00 | FT3, FT4 | lit, base grey `g_texturedRgb` |
| 0x2101, 0x2901, 0x2501, 0x2D01 | F3, F4, FT3, FT4 | unlit, `gte_dpcs` (depth cue only) |
| 0x3101, 0x3901, 0x3501, 0x3D01 | G3, G4, GT3, GT4 | unlit, `gte_dpct` per vertex |

Any other type ends the model. Bit 9 of the group type sets the semi-transparency bit of the packet
code, attribute bit 6 the raw-texture bit (`Render_SetPrimFlags`).

Per face, `Render_ProjectTri` or `Render_ProjectQuad` loads the vertices, and
`Render_TransformTri` runs `rtpt`, then culls when the GTE flag is set (except 0x40000, see
below), when `nclip` says it faces away, or when the depth cue value reaches 0x1000. Otherwise
`avsz3` gives the table entry `ot[otz >> shift]`, and the `Render_AddPoly*` function links the
packet at the head of that entry.

### Clipping

A face goes to Sony's clipper `RCpolyF3` to `RCpolyGT4` instead when the GTE raised flag 0x40000
or when its screen box is wider or taller than 256 pixels (`Render_CheckScreenBox`). The face is
copied into the work areas `g_clipTriWork` or `g_clipQuadWork` with a header holding the
subdivision (attribute bits 9 to 11), the 320 x 240 screen and the table entry
(`Render_FillClipHeader`). `Render_ForceClipDivision` can force the subdivision; nothing in
render.c calls it.

### Fog and light modes

The depth cue value `depth` that `Render_TransformTri` reads grows with distance, from the
`fogNear` distance the view set, and a face at 0x1000 or more is not drawn at all: the fog's end
is also the draw distance. Colours computed on the GTE (`ncds`, `dpcs`, `dpct`) include its depth
cue toward the far colour. Textured faces also move their CLUT down `depth >> depthShift` rows. With `depthShift` 9 that is 0 to 7 rows: the seven rows under each
palette that `Tix_BuildFade` filled, blended toward the place's colour
([files and CD](files-and-cd.md#formats-as-the-loaders-read-them)). With 16 the row never moves.
Shift 9 applies when attribute bits 3-4 are non-zero, or when bit 5 is set and the view's light
mode (`g_gsLightMode`, written by `GsSetLightMode`) is non-zero. A place sets light mode 1, its
ambience's colours as clear and fog colours and its fog distance (`Place_Start`); which models
skip fog is in [the unused switches](../discoveries.md#-switches-and-features-the-game-never-uses).

## Sprites, boxes and fades

All 2D objects are scene nodes hung from a screen's root or a view's root.

- `SpriteNode` ([sprite_node.c](../../src/game/sprite_node.c)) holds a `GsSPRITE` cut from a TIM;
  `ScreenSprite` adds a 2D position and pivot; `Glyph` shows one 8 x 8 character of a font image
  laid out 32 per row; `Label` owns a row of glyphs, one per character. Their slots 0x60 to 0x68
  act on the sprite's attribute instead of the node's.
- `Box` ([box.c](../../src/game/box.c)) holds a `GsBOXF`: a filled rectangle at a priority.
- `Fade` ([fade.c](../../src/game/fade.c)) is a `Box` that fades. Its colour index is a 3-bit
  channel mask (1 blue, 2 green, 4 red, 7 white; 0 black). `Fade_Begin` watches a clock, makes the
  box semi-transparent in blend mode 1 (add) for a colour or 2 (subtract) for black, and sets
  `0x100 / step` ticks. Each tick `Fade_Step` adds the step to the masked channels (negative for a
  fade in); at the end `Fade_Stop` notifies 5 (in done) or 6 (out done). In a flashback `tint`
  stops the fade early and keeps the colour
  ([three quiet rules](../discoveries.md#-three-quiet-rules-for-the-look-of-a-place)).
- `Bg`, `BgMap` and `BgCells` wrap libgs `GsBG`, `GsMAP` and `GsCELL`: a `MenuScreen` uses them to
  draw a full-screen 16-bit picture from VRAM x 640 ([menus and save](menus-and-save.md)).

Two VRAM tricks finish the picture. `Display_RotateRect` ([tim.c](../../src/game/tim.c)) rotates a
VRAM area one column right through a spare column; `Stage_CyclePalettes`, called from `Scenery_Tick` on every unpaused tick of a place
(`Place_Update`), runs it on a CLUT area in stage 2 and in stages 3 to 5, the turning water of Kyoto
([three quiet rules](../discoveries.md#-three-quiet-rules-for-the-look-of-a-place)).
`RootNode` ([root_node.c](../../src/game/root_node.c)), the default root of a screen and the base
of the dream's `StageMap`, owns three `FlatLight` objects for `GsSetFlatLight` and an ambient
colour sent with `GsSetAmbient`.

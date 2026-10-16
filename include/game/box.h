#ifndef GAME_BOX_H
#define GAME_BOX_H

#include "common.h"
#include "game/display.h"
#include "game/gs.h"

/* A box size as Box_Init and Box_SetSize read it: two words, of which only the low halves count */
typedef struct BoxSize {
    u16 width;
    u16 pad_02;
    u16 height;
    u16 pad_06;
} BoxSize;

/* Functions of src/game/box.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/box.c */
struct Box;
struct BoxVtbl;
struct Box *Box_Create(BoxSize *size, u8 *color, s32 priority);
void Box_Show(struct Box *box, s32 root, s32 position);
s32 Box_SetVisible(struct Box *box, s32 visible);
void Box_SetSemiTrans(struct Box *box, s32 on);
void Box_SetBlendMode(struct Box *box, s32 mode);
void Box_SetColor(struct Box *box, s32 copy, Color3 *color);
void Box_SetPosition(struct Box *box, ScreenPoint *position);
void Box_SetSize(struct Box *box, BoxSize *size);
void Box_ShowAbsolute(struct Box *box, s32 root, s32 position, s32 value);
void Box_SetPriority(struct Box *box, s32 priority);
void Box_SetMask(struct Box *box, s32 bits);
struct BoxVtbl *Box_GetVtbl(void);

#endif

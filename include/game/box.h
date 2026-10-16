#ifndef GAME_BOX_H
#define GAME_BOX_H

#include "common.h"
#include "game/display.h"

/* Functions of src/game/box.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/box.c */
struct Box;
struct BoxVtbl;
void *Box_Create(s32 size, s32 color, s32 priority);
void Box_Show(struct Box *box, s32 root, s32 position);
s32 Box_SetVisible(struct Box *box, s32 visible);
void Box_SetSemiTrans(struct Box *box, s32 on);
void Box_SetBlendMode(struct Box *box, s32 mode);
void Box_SetColor(struct Box *box, s32 copy, u8 *color);
void Box_SetPosition(struct Box *box, ScreenPoint *position);
void Box_SetSize(struct Box *box, u16 *size);
void Box_ShowAbsolute(struct Box *box, s32 root, s32 position, s32 value);
void Box_SetPriority(struct Box *box, s32 priority);
void Box_SetMask(struct Box *box, s32 bits);
struct BoxVtbl *Box_GetVtbl(void);

#endif

#ifndef GAME_CARD_H
#define GAME_CARD_H

#include "common.h"
#include "game/menu.h"

/* Functions of src/game/card.c that other files call or reference (docs/naming.md, Prototypes) */
Card *Card_New(s32 sharePad, s32 port);
void Card_SetTitleLetter(CardTitle *title, u8 *fileName);

#endif

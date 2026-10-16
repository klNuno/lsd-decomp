#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "common.h"

/* Functions of src/game/model.c that other files call or reference (docs/naming.md, Prototypes) */
/* types defined in src/game/model.c */
struct Model;
struct ModelBaseVtbl;
void Model_OnNotify(struct Model *model, u16 **sender, s32 message);
void Model_SetVisible(struct Model *model, s32 visible);
void Model_SetLightFlags(struct Model *model, s32 flags);
void Model_SetAnim6Flag(struct Model *model, s32 value);
s32 Model_Load(struct Model *model);
void Model_Unload(struct Model *model);
s32 Model_FindPart(struct Model *model, u8 id);
s32 Model_CreateParts(struct Model *model);
void Model_FreeParts(struct Model *model);
void Model_TickAnimation(struct Model *model);
void Model_SetTickMode(struct Model *model, s32 mode);
void Model_StartTick(struct Model *model);
void Model_StopTick(struct Model *model);
void Model_TickForward(struct Model *model);
void Model_TickC(void);
void Model_PlaySound(struct Model *model, s32 sound);
void Model_SetAnimation(struct Model *model, s32 animation);
void Model_PlayAnimation(struct Model *model);
void Model_StopAnimation(struct Model *model);
void *Model_ApplyFrame(struct Model *model, u8 *frame, void *context);
s32 Model_ApplyCommand(struct Model *model, s32 command);
void Model_SetTarget(struct Model *model, struct Model *target);
void Model_ClearTarget(struct Model *model);
struct ModelBaseVtbl *Model_GetVtbl(void);

#endif

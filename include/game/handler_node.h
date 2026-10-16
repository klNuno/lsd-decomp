#ifndef GAME_HANDLER_NODE_H
#define GAME_HANDLER_NODE_H

#include "common.h"
#include "game/sound_bank.h"

/* One of the three voices of a HandlerNode (0x14 bytes); HandlerNode_Run resets sound, octave and volumes before each run. */
typedef struct HandlerVoice {
    s32 voice;     /* 0x00 SPU voice playing (sound bank slot 0x80), -1 none */
    s32 sound;     /* 0x04 bank program to start this tick, -1 none, -2 stops the voice */
    s32 octave;    /* 0x08 sound bank slot 0x9C (Sound_SetOctave): notes shift by octave * 12 - 24, 0 by default */
    s32 volume;    /* 0x0C start volume, 0x7F by default */
    s32 endVolume; /* 0x10 volume SsUtAutoVol slides to, 0x40 by default */
} HandlerVoice;

/* The handler node (0x54 bytes) at Entity +0x9C, the handler's second argument: HandlerNode_Start registers it,
   HandlerNode_Stop removes it, HandlerNode_Run runs handler(owner, node) once per tick. */
typedef struct HandlerNode {
    s32 id;                  /* 0x00 entity type + 1 while registered, 0 once stopped */
    s32 tick;                /* 0x04 runs so far, counted by HandlerNode_Run */
    void *owner;             /* 0x08 the entity, passed back as the handler's first argument */
    void (*handler)();       /* 0x0C the record's handler, called as handler(owner, node) */
    s32 fade;                /* 0x10 each step lowers both volumes by volume / fadeSteps; < 0 plays nothing (slot 0x148 by distance) */
    s32 fadeSteps;           /* 0x14 10 */
    HandlerVoice voices[3];  /* 0x18 */
} HandlerNode;

/* Functions of src/game/handler_node.c that other files call or reference (docs/naming.md, Prototypes) */
s32 HandlerNode_Start(SoundBank *bank, HandlerNode *node, s32 nodeId, void *owner, void (*handler)());
void HandlerNode_Stop(SoundBank *bank, HandlerNode *node);
void HandlerNode_Run(SoundBank *bank, HandlerNode *node);

#endif

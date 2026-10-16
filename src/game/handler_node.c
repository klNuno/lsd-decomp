#include "common.h"
#include "game/handler_node.h"
#include "game/sound_bank.h"

/*
 * The handler nodes that play sounds from a model's sound bank once per tick (see src/game/entity.c):
 * HandlerNode_Start registers a behaviour handler, HandlerNode_Run calls it, then plays the sounds it
 * asked for.
 *
 * File boundaries: guess (docs/layout.md)
 */

s32 HandlerNode_Start(s32 bank, HandlerNode *node, s32 nodeId, s32 owner, s32 handler) {
    HandlerVoice *voice;
    s32 noVoice;
    s32 i;

    if (node->id != 0) {
        return 0;
    }
    voice = node->voices;
    noVoice = -1;
    node->id = nodeId;
    node->owner = owner;
    node->handler = handler;
    for (i = 2; i >= 0; i--) {
        voice->voice = noVoice;
        voice++;
    }
    node->tick = 0;
    node->fadeSteps = 0xA;
    return 1;
}

void HandlerNode_Stop(SoundBank *bank, HandlerNode *node) {
    HandlerVoice *voice;
    s32 i;

    voice = node->voices;
    for (i = 0; i < 3; i++, voice++) {
        if (voice->voice >= 0) {
            voice->voice = bank->vtbl->stopVoice(bank, voice->voice);
        }
    }
    node->id = 0;
}

void HandlerNode_Run(SoundBank *bank, HandlerNode *node) {
    HandlerVoice *voice;
    void (*callback)(s32, void *);
    s32 i;
    s32 activeVoice;

    if (node->id > 0) {
        for (voice = node->voices, i = 0; i < 3; i++, voice++) {
            voice->sound = -1;
            voice->octave = 0;
            voice->volume = 0x7F;
            voice->endVolume = 0x40;
        }
        callback = (void (*)(s32, void *)) node->handler;
        node->fade = 0;
        if (callback != NULL) {
            callback(node->owner, node);
        }
        if (node->fade >= 0) {
            for (voice = node->voices, i = 0; i < 3; i++, voice++) {
                if (voice->sound >= 0) {
                    activeVoice = voice->voice;
                    if (activeVoice >= 0) {
                        bank->vtbl->stopVoice(bank, activeVoice);
                    }
                    bank->vtbl->setOctave(bank, voice->octave);
                    voice->voice = bank->vtbl->playTone(bank, voice->sound << 4, voice->volume - (voice->volume / node->fadeSteps) * node->fade, voice->endVolume - (voice->endVolume / node->fadeSteps) * node->fade);
                } else if (voice->sound == -2) {
                    activeVoice = voice->voice;
                    if (activeVoice >= 0) {
                        bank->vtbl->stopVoice(bank, activeVoice);
                    }
                }
            }
        }
        node->tick++;
    }
}

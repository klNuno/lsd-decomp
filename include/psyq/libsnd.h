#ifndef PSYQ_LIBSND_H
#define PSYQ_LIBSND_H

#include "types.h"

/*
 * LIBSND functions the game calls (the game links a LIBSND build the signature database lacks:
 * .agents/research/sony-suspects.md). Ids, voices and volumes are s16 as the calls pass them.
 */

void SpuVmInit(s32 mode);
void SsSetTableSize(s8 *table, s16 sMax, s16 tMax);
void SsSeqCalledTbyT(void);
void SsSetMVol(s16 voll, s16 volr);
void SsSetMute(s16 mute);

/* Sound banks */
s16 SsVabOpenHead(void *addr, s16 vabId);
s16 SsVabTransBody(void *addr, s16 vabId);
s16 SsVabTransCompleted(s16 immediateFlag);
void SsVabClose(s16 vabId);

/* Sequences */
s16 SsSeqOpen(s32 addr, s16 vabId);
void SsSeqClose(s16 seqId);
void SsSeqPlay(s16 seqId, s16 playMode, s16 count);
void SsSeqPause(s16 seqId);
void SsSeqReplay(s16 seqId);
void SsSeqStop(s16 seqId);
void SsSeqSetVol(s16 seqId, s16 voll, s16 volr);
void SsSeqSetCrescendo(s16 seqId, s16 vol, s32 vTime);

/* Voices */
s16 SsUtKeyOn(s16 vabId, s16 prog, s16 tone, s16 note, s16 fine, s16 voll, s16 volr);
void SsUtKeyOffV(s16 voice);
void SsUtAllKeyOff(s32 mode);
s16 SsUtAutoVol(s16 voice, s16 startVol, s16 endVol, s16 deltaTime);
s16 SsUtGetVabHdr(s16 vabId, void *vabhdr);
s16 SsUtGetProgAtr(s16 vabId, s16 progNum, u8 *progatr);
s16 SsUtGetVagAtr(s16 vabId, s16 progNum, s16 toneNum, u8 *vagatr);

#endif

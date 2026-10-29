#ifndef GUARD_SOUND_VOICE_H
#define GUARD_SOUND_VOICE_H
#include "global.h"

struct SoundChannelState;
struct SoundSampleHeader;

/* Two 0x48-byte PCM voices begin at sound root offsets 0x690 and 0x6D8. */
struct SoundVoiceState {
    const struct SoundSampleHeader *sample;
    u32 rate;
    u32 position;
    u32 control;
    u32 timer;
    s32 pitchAdjustment;
    struct SoundChannelState *pendingOwner;
    const struct SoundSampleHeader *pendingSample;
    u32 pendingPitch;
    s32 pendingNote;
    s32 pendingVolume;
    u32 pendingDuration;
    u8 pendingRoute;
    u8 pendingParameter;
    u16 unknown32;
    u16 duration;
    u16 elapsed;
    s16 pitchDelta;
    u8 fifo;
    u8 unknown3B;
    u8 volume;
    u8 unknown3D;
    u8 active;
    u8 route;
    u8 parameter;
    u8 unknown41[3];
    u32 emptyTicks;
};
typedef char SoundVoiceSize[(sizeof(struct SoundVoiceState) == 0x48) ? 1 : -1];

void sub_08073E88(struct SoundChannelState *owner, struct SoundVoiceState *voice,
    const struct SoundSampleHeader *sample, s32 note, s32 volume, u32 duration,
    u32 route, u8 parameter);
void sub_08073F2C(struct SoundChannelState *owner, struct SoundVoiceState *voice,
    const struct SoundSampleHeader *sample, u32 pitch, s32 volume, u32 duration,
    u32 route, u8 parameter);

#endif

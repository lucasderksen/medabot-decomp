/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "sound_voice.h"
#include "eeprom.h"
#include "state0_work.h"




void sub_08073F2C(struct SoundChannelState *owner, struct SoundVoiceState *voice,
    const struct SoundSampleHeader *sample, u32 value, s32 volume, u32 duration,
    u32 route, u8 parameter) {
    voice->active = 0;
    voice->pendingOwner = owner;
    voice->pendingSample = sample;
    voice->pendingPitch = value;
    voice->pendingVolume = volume;
    voice->pendingDuration = duration;
    voice->pendingRoute = route;
    voice->pendingParameter = parameter;
    voice->active = 1;
}

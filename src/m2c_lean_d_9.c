/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "map_metadata.h"
#include "record_helpers.h"
#include "scene_animation.h"
#include "scene_graphics_loads.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"

extern void sub_08073E1C(void *);

void sub_08073810(struct SoundChannelState *channel, struct SoundVoiceState *voice);

void sub_08073810(struct SoundChannelState *channel, struct SoundVoiceState *voice) {

    struct SoundRootState *root;
    u8 *flags;
    u8 *level;
    s16 *envelope;
    s16 scaled;
    u32 duration;
    u8 shorten;
    u8 status;

    level = &channel->byte66;
    scaled = (*level * channel->half40) & ~0xFFF;
    envelope = &channel->envelope;
    *envelope = scaled;
    flags = &channel->flags;
    if (0x10 & *flags) {
        if (*level == 0)
            goto mute;
        {
            root = gFamilySoundRoot74028;
            duration = channel->words18[4];
            if (channel->byte62 != 0) {
                shorten = channel->unknown5B[3];
                if (duration > shorten)
                    duration -= shorten;
                else
                    duration = 1;
            }
            switch (channel->byte63) {
            case 0: {
                const struct SoundSampleHeader *sample;
                s32 note;

                sample = root->instruments[channel->byte67];
                note = channel->half48 + *(s8 *)&channel->byte6A;
                sub_08073E88(channel, voice, sample, note, (u16)*envelope >> 12, duration, channel->byte6F, channel->parameter);
                break;
            }
            case 1:
                sub_08073F2C(channel, voice, root->instruments[channel->byte67], channel->half48, (u16)*envelope >> 12, duration, channel->byte6F, channel->parameter);
                break;
            case 2: {
                const struct SoundSampleHeader *sample;
                s32 note;
                u16 *key;
                u16 drum;

                key = &channel->half48;
                drum = *key;
                sample = root->drums[drum];
                note = root->aux->base + drum;
                sub_08073E88(channel, voice, sample, note, (u16)*envelope >> 12, duration, root->aux->routes[*key], channel->parameter);
                break;
            }
            }
        }
        goto clearFlags;
    mute:
        sub_08073E1C(voice);
    clearFlags:
        *flags = 0xEF & *flags;
    }
    if (channel->byte58 != 0) {
        voice->pitchAdjustment = channel->word38 >> 4;
        voice->control |= 2;
    }
    status = channel->flags;
    if (0x40 & status) {
        u32 cleared;

        voice->route = channel->byte6F;
        voice->parameter = channel->parameter;
        voice->control |= 4;
        /* The constant is the AND's destination, as in the reference. */
        cleared = 0xBF;
        cleared &= status;
        channel->flags = cleared;
    }
}

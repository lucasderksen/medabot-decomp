/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_work.h"

struct SoundChannel32F0 {
    u8 unknown00[0x40];
    u16 frequency;
    u8 unknown42[8];
    s16 envelope;
    u8 unknown4C[4];
    u8 flags;
    u8 unknown51[0x15];
    u8 volume;
    u8 low;
};

extern const u8 gUnknown_083ABBE2[];

void sub_080732F0(struct SoundChannel32F0 *channel, u16 *out, u8 *control);
void sub_0807334C(struct SoundChannel32F0 *channel, s16 *out);
void sub_080733BC(struct SoundChannel32F0 *channel, s16 *out);

void sub_080732F0(struct SoundChannel32F0 *channel, u16 *out, u8 *control) {

    if (channel->flags & 6) {
        channel->envelope = (channel->volume * channel->frequency) & ~0xFFF;
        *out = channel->low | channel->envelope | 0x800;
        *control |= 0x80;
        channel->flags = (channel->flags & 0xF9) | 0x10;
    }
}

void sub_0807334C(struct SoundChannel32F0 *channel, s16 *out) {

    if (channel->flags & 0x20) {
        sub_08073A48(channel->low);
        channel->flags &= 0xDF;
    }
    if (channel->flags & 2) {
        channel->envelope = (channel->volume * channel->frequency) & ~0xFFF;
        *out = gUnknown_083ABBE2[(u16)channel->envelope >> 12] << 8;
        channel->flags &= 0xFD;
    }
}

void sub_080733BC(struct SoundChannel32F0 *channel, s16 *out) {

    if (channel->flags & 2) {
        *out = channel->envelope = (channel->volume * channel->frequency) & ~0xFFF;
        channel->flags = (channel->flags & 0xFD) | 1;
    }
}

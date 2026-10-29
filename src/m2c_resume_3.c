/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "sound_work.h"


void sub_08074D50(u32 song, u32 parameter);

void sub_08074D50(u32 song, u32 parameter) {

    struct SoundRootState *root;
    const struct SoundSongHeader *header;
    u32 cursor;
    u32 i;
    u32 mask;
    root = sub_08075244();
    header = root->effects[song];
    i = 0;
    mask = 0x800;
    cursor = (u32)header;
loop:
    {
        if (header->channelMask & mask) {
            struct SoundChannelState *channel = &root->channels[i];
            if (channel->priority <= header->priority) {
                sub_0807455C(channel, *(void **)(cursor + 4));
                channel->priority = header->priority;
                channel->song = song;
                channel->parameter = parameter;
            }
            cursor += 4;
        }
        mask >>= 1;
        i++;
    }
    if (mask) goto loop;
}

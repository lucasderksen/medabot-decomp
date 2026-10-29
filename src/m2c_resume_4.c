/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "sound_work.h"

extern void sub_0807495C(void *channel);

void sub_08074A8C(u32 song, u32 parameter);

void sub_08074A8C(u32 song, u32 parameter) {

    struct SoundRootState *root;
    const struct SoundSongHeader *header;
    u32 i;
    u32 mask;
    u32 cursor;
    root = sub_08075244();
    header = root->music[song];
    sub_0807495C(&root->channels[0]);
    sub_0807495C(&root->channels[1]);
    sub_0807495C(&root->channels[2]);
    sub_0807495C(&root->channels[3]);
    sub_0807495C(&root->channels[8]);
    sub_0807495C(&root->channels[9]);
    sub_0807495C(&root->channels[12]);
    i = 0;
    mask = 0x800;
    cursor = (u32)header;
loop:
    {
        if (header->channelMask & mask) {
            struct SoundChannelState *channel = &root->channels[i];
            sub_0807455C(channel, *(void **)(cursor + 4));
            channel->priority = header->priority;
            channel->parameter = parameter;
            cursor += 4;
        }
        mask >>= 1;
        i++;
    }
    if (mask) goto loop;
    if (4 & header->channelMask) {
        sub_0807455C(&root->channels[12], root->channels[9].track);
        root->channels[12].priority = header->priority;
        root->channels[12].parameter = parameter;
    }
    root->songIndex = song;
}

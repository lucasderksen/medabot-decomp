/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "audio.h"

/* Observed channel prefix; suffixes are byte offsets in hexadecimal. */
struct AudioPitchFields {
    u8 unknown00[0x38];
    s32 word38;
    u8 unknown3C[0xA];
    u16 word46;
    u8 unknown48[8];
    u8 flags50;
    u8 unknown51[4];
    u8 byte55;
    u8 unknown56[2];
};
typedef char AudioPitchFieldsSizeCheck[
    sizeof(struct AudioPitchFields) == 0x58 ? 1 : -1];

void sub_08073480(void *channelAddress, volatile u16 *output) {
    struct AudioPitchFields *channel = channelAddress;
    u8 *flagsAddress;
    u8 flags;
    u32 mask, status, enable, enableCopy, update;
    u32 pitch;
    s16 signedPitch;

    flagsAddress = &channel->flags50;
    flags = *flagsAddress;
    mask = 0xEF;
    mask &= flags;
    *flagsAddress = mask;
    update = 1;
    update &= mask;
    if (update != 0) {
        status = 4 & *(volatile u16 *)0x04000084;
        enable = 0;
        if (status == 0)
            enable = 0x8000;
        enableCopy = enable;
        pitch = (u16)(channel->word46 + channel->byte55 + (channel->word38 >> 4));
        signedPitch = (s16)pitch;
        if (signedPitch < 0)
            pitch = 0;
        else if (signedPitch > 0x7FF)
            pitch = 0x7FF;
        *output = enableCopy | pitch;
        *flagsAddress = 0xFE & *flagsAddress;
    }
}

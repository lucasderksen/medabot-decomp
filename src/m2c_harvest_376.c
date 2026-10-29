/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "audio.h"

/* Observed channel prefix; suffixes are byte offsets in hexadecimal. */
struct AudioChannelResetFields {
    u8 unknown00[0x14];
    u32 word14;
    u8 unknown18[0x20];
    s32 word38;
    u8 unknown3C[4];
    u16 word40;
    u8 unknown42[2];
    u16 word44, word46, word48, word4A;
    u8 unknown4C[2];
    u16 word4E;
    u8 flags50;
    u8 unknown51[3];
    u8 byte54, byte55;
    u8 unknown56[2];
    u8 byte58;
    u8 unknown59[13];
    u8 byte66, byte67;
    u8 unknown68[3];
    u8 byte6B, unknown6C, byte6D;
};
typedef char AudioChannelResetFieldsSizeCheck[
    sizeof(struct AudioChannelResetFields) == 0x70 ? 1 : -1];

void sub_0807490C(void *channelAddress) {
    struct AudioChannelResetFields *channel = channelAddress;

    channel->word14 = 0;
    channel->byte54 = 0;
    channel->byte6B = 0;
    channel->byte66 = 0;
    channel->word48 = 0xFF;
    channel->flags50 = (u8) (0xA | channel->flags50);
    channel->byte6D = 0;
    channel->byte58 = 0;
    channel->word38 = 0;
    channel->word4E = 0xFFFF;
    channel->word44 = 0;
}

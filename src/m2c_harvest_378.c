/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "audio.h"

/* Observed channel fields; suffixes are byte offsets in hexadecimal. */
struct AudioCommandFields {
    u8 unknown00[0x14];
    const u8 *cursor14;
    u8 unknown18[0x10];
    s32 word28;
    u8 unknown2C[0x1A];
    u16 word46, word48;
    u8 unknown4A[6];
    u8 flags50;
    u8 unknown51[0x15];
    u8 byte66;
    u8 unknown67[5];
    u8 byte6C;
    u8 unknown6D[3];
};

typedef char AudioCommandFieldsSizeCheck[
    sizeof(struct AudioCommandFields) == 0x70 ? 1 : -1];

void sub_08072AC0(void *channelAddress) {
    struct AudioCommandFields *channel = channelAddress;
    const u8 *command;

    channel->word48 = 0xFF;
    channel->byte6C = 0xFF;
    channel->word46 = 0;
    command = channel->cursor14;
    channel->word28 = *command + 1;
    channel->cursor14 = command + 1;
    channel->byte66 = 0;
    channel->flags50 |= 0x52;
}

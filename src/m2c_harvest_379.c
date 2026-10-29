/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "audio.h"

/* Observed channel prefix; suffixes are byte offsets in hexadecimal. */
struct AudioStreamFields {
    u8 unknown00[0x24];
    const u8 *cursor24;
    u8 unknown28[4];
    s32 word2C, word30;
    u8 unknown34[0x1C];
    u8 flags50;
    u8 unknown51[3];
};
typedef char AudioStreamFieldsSizeCheck[
    sizeof(struct AudioStreamFields) == 0x54 ? 1 : -1];

extern void sub_08072AFC(void *, u8);
extern void sub_08072B18(void *, u8);

void sub_08072F7C(void *channelAddress) {
    struct AudioStreamFields *channel = channelAddress;
    const u8 *command;
    const u8 *cursor;
    u8 opcode;
    u8 parameter;
    s32 comparison;

    command = channel->cursor24;
    if (command == 0)
        return;
    cursor = command;
    opcode = *cursor;
    cursor++;
    channel->cursor24 = cursor;
    if ((opcode & 0xF0) == 0xD0) {
        sub_08072AFC(channel, opcode & 0xF);
        channel->word30 = channel->word2C;
        channel->flags50 |= 1;
        return;
    }
    if (opcode == 0xE1)
        goto unsignedParameter;
    comparison = opcode;
    if (comparison <= 0xE1)
        return;
    if (opcode == 0xE2)
        goto byteParameter;
    if (opcode != 0xFF)
        return;
    sub_08072AFC(channel, 0);
    channel->cursor24 = 0;
    return;

unsignedParameter:
    parameter = command[1];
    channel->cursor24 = cursor + 1;
    sub_08072B18(channel, parameter);
    return;

byteParameter:
    parameter = command[1];
    channel->cursor24 = cursor + 1;
    sub_08072B20(channel, parameter);
    return;
}

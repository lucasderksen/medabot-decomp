/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "audio.h"

/* InitAudio installs the original 22-entry bank at 080B18FC. */
struct AudioStreamRange {
    u16 count;
    u16 base;
    const u8 *routes;
    const u8 *streams[22];
};
struct AudioStreamRoot {
    u8 pad00[0x728];
    const struct AudioStreamRange *range;
};
struct AudioStreamChannel {
    u8 pad00[0x24];
    const u8 *cursor;
    u8 pad28[8];
    s32 remaining;
    u8 pad34[0x12];
    u16 pitch;
    u16 index;
    u8 pad4A[6];
    u8 flags;
    u8 pad51[0x1B];
    u8 previousNote;
    u8 pad6D[3];
};
typedef char AudioStreamRangeSizeCheck[
    sizeof(struct AudioStreamRange) == 0x60 ? 1 : -1];
typedef char AudioStreamRootSizeCheck[
    sizeof(struct AudioStreamRoot) == 0x72C ? 1 : -1];
typedef char AudioStreamChannelSizeCheck[
    sizeof(struct AudioStreamChannel) == 0x70 ? 1 : -1];

extern void *gFamilySoundRoot74028;

void sub_080728A0(void *channelPointer, u32 noteWord) {

    struct AudioStreamChannel *channel;
    const struct AudioStreamRange *range;
    const struct AudioStreamRange *rangeReload;
    void **rootAddress;
    u8 note;
    s32 index;
    s32 maximum;

    channel = channelPointer;
    note = noteWord;
    rootAddress = &gFamilySoundRoot74028;
    range = ((struct AudioStreamRoot *)*rootAddress)->range;
    index = note - range->base;
    if (index < 0) {
        index = 0;
    } else {
        maximum = range->count - 1;
        if (maximum < index) {
            index = maximum;
        }
    }
    channel->index = index;
    channel->previousNote = 0xFF;
    channel->pitch = 0;
    rangeReload = ((struct AudioStreamRoot *)*rootAddress)->range;
    channel->cursor = rangeReload->streams[index];
    channel->remaining = 0;
    channel->flags |= 0x52;
}

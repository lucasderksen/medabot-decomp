/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "audio.h"

extern s32 sub_08074540(void);
extern u8 *gFamilySoundRoot74028;
extern void sub_080737E8(void *);

/* The observed caller supplies slot 12 in the 0x734-byte audio work object. */
void sub_0807462C(s32 slot) {
    u8 **rootPointer;
    u8 *activeAddress;
    s32 channelOffset;
    s32 alternateActive;

    rootPointer = &gFamilySoundRoot74028;
    activeAddress = gFamilySoundRoot74028;
    channelOffset = 0x74 * slot;
    activeAddress += 0x14;
    if (*(u32 *)(activeAddress + channelOffset) != 0 && sub_08074540() == 0) {
        if (*(u32 *)(*rootPointer + 0x340) != 0) {
            {
                u8 loadedFlags;
                u32 mask;
                loadedFlags = *(*rootPointer + 0x37C);
                mask = 0x5F;
                mask |= loadedFlags;
                *(*rootPointer + 0x37C) = mask;
            }
            sub_080737E8(*rootPointer + 0x32C);
            return;
        }
        alternateActive = *(u32 *)(*rootPointer + 0x170);
        if (alternateActive != 0) {
            {
                u8 loadedFlags;
                u32 mask;
                loadedFlags = *(*rootPointer + 0x1AC);
                mask = 0x5F;
                mask |= loadedFlags;
                *(*rootPointer + 0x1AC) = mask;
            }
            sub_080737E8(*rootPointer + 0x15C);
            return;
        }
        *(*rootPointer + channelOffset + 0x66) = alternateActive;
        {
            u8 loadedFlags;
            u32 mask;
            loadedFlags = *(*rootPointer + channelOffset + 0x50);
            mask = 2;
            mask |= loadedFlags;
            *(*rootPointer + channelOffset + 0x50) = mask;
        }
        sub_080737E8(*rootPointer + channelOffset);
    }
}

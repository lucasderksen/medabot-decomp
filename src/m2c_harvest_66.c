/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_work.h"

extern const void *const gState0NextCommands_083B6100[];
extern s32 gUnknown_03000648;
extern s32 gUnknown_03000660;
extern s32 sub_08035740(void *, s16, s32);

void sub_0802AC7C(void);
void sub_0803081C(void);
s32 sub_080358B8(s32 slot, s32 row, s32 other);
s32 sub_08035960(s32 slot, s32 kind);

void sub_0802AC7C(void) {
    u8 *work = gState0TransferWork.bytes;
    u32 index = work[0x87] << 8;
    u8 *base = (u8 *) &gUnknown_03000660;
    u8 *record = (u8 *) (index + (u32) base);
    record++;
    sub_08035740(record, *(s16 *) (work + 0xEC), 0xFF);
    work[0xAA]++;
}

void sub_0803081C(void) {
    const void *const *commands = gState0NextCommands_083B6100;
    sub_08040BD8(commands[gState0TypedWork.bytes[0x84]], 0x21);
    if (gFrameObjects[0x21].commandStopped == 0xFF)
        gState0TransferWork.bytes[0xAA]++;
}

s32 sub_080358B8(s32 slot, s32 row, s32 other) {
    u8 *setup = gSetupBuffer_03000590;
    u32 address = row * 0x18;
    u32 offset = slot << 8;
    address += offset;
    address += (u32) setup;
    if (*(u8 *) (address + 0x49) == 0x23 && setup[(other << 8) + 0x91] == 0x6A)
        return 1;
    return 0;
}

s32 sub_08035960(s32 slot, s32 kind) {
    u32 i = 0;
    u8 *setup = gSetupBuffer_03000590;
    u8 *record;
    slot <<= 8;
    setup += 0x49;
    record = slot + setup;
    do {
        if (record[0x10] != 0 && record[0] == kind)
            return 1;
        record += 0x18;
        i++;
    } while (i <= 3);
    return 0;
}

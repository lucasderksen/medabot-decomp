/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"


s32 sub_08035AAC(s32 slot, s32 row, s32 other);

s32 sub_08035AAC(s32 slot, s32 row, s32 other) {
    u8 *setup = gSetupBuffer_03000590;
    u32 address = row * 0x18;
    u32 offset = slot << 8;
    u32 kind;
    address += offset;
    address += (u32) setup;
    kind = *(u8 *) (address + 0x49);
    if (((u8) (kind - 4) <= 1 || (setup[offset + 0xD6] & 1))
        && (setup[(other << 8) + 0xD6] & 8))
        return 1;
    return 0;
}

/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ObservedActionFrameBacking
{
    u8 unknown000[0x842];
    u16 screenX842;
    u8 unknown844[4];
    u8 scaleX848;
    u8 unknown849[0x19];
    u8 commandStopped862;
};


void sub_080246C0(void);
void sub_080262FC(void);
void sub_0802FD08(void);
s32 sub_08035AFC(s32 slot, s32 row, s32 other);
s32 sub_08035B4C(s32 slot, s32 row, s32 other);

void sub_080246C0(void) {
    u8 *scratch = gUnknown_0300052E;
    u8 *counter;
    u32 count;
    sub_0801A574(scratch, gState0TransferWork.bytes[0x88], 33);
    counter = scratch - 0x6A;
    count = *counter + 1;
    *counter = count;
    scratch -= 0x65;
    if (*scratch == 0 && (*(u8 *)&gRepeatedKeys & 1) && (u8)count > 50)
        *counter = 120;
    if (gUnknown_03000440[0x84] == 120)
    {
        u8 *work = gState0TransferWork.bytes;
        sub_08040CD0(work[0x88] * 4 + 33, 4);
        work[0xAA]++;
    }
}

void sub_080262FC(void) {
    if (gFrameObjects[0x21].scaleX == 0x40) {
        sub_08074DE0(0x53);
        gState0TransferWork.bytes[0xAA]++;
    } else {
        gFrameObjects[0x21].scaleX -= 8;
        gFrameObjects[0x21].scaleY -= 8;
    }
}

void sub_0802FD08(void) {
    if (gFrameObjects[0x21].scaleX == 0x40) {
        sub_08074DE0(0x54);
        gState0TransferWork.bytes[0xAA]++;
    } else {
        gFrameObjects[0x21].scaleX -= 8;
        gFrameObjects[0x21].scaleY -= 8;
    }
}

s32 sub_08035AFC(s32 slot, s32 row, s32 other) {
    u8 *setup = gSetupBuffer_03000590;
    u32 address = row * 0x18;
    u32 offset = slot << 8;
    u32 kind;
    address += offset;
    address += (u32) setup;
    kind = *(u8 *) (address + 0x49);
    if (((u8) (kind - 6) <= 1 || (setup[offset + 0xD6] & 2))
        && (setup[(other << 8) + 0xD6] & 0x10))
        return 1;
    return 0;
}

s32 sub_08035B4C(s32 slot, s32 row, s32 other) {
    u8 *setup = gSetupBuffer_03000590;
    u32 address = row * 0x18;
    u32 offset = slot << 8;
    u32 kind;
    address += offset;
    address += (u32) setup;
    kind = *(u8 *) (address + 0x49);
    if (((u8) (kind - 8) <= 1 || (setup[offset + 0xD6] & 4))
        && (setup[(other << 8) + 0xD6] & 0x20))
        return 1;
    return 0;
}

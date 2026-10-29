/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"

struct ContinuedFrame8Root { u8 pad00[0x200]; u16 flags200; s16 x202; s16 y204; u16 frame206; u8 pad208[2]; u8 palette20A; u8 priority20B; u8 pad20C[0x10]; u8 selector21C; };

extern const u8 gUnknown_083AD524[];
extern struct ContinuedFrame8Root gUnknown_03002C30;

void sub_08017B24(void);

void sub_08017B24(void) {
    struct ContinuedFrame8Root *frames;
    const u8 *coordinates;
    u8 *work;
    u8 *column;
    u32 zero;
    u32 bank;
    s32 temp_r0;
    u8 temp_r1;
    u8 temp_r3;

    frames = &gUnknown_03002C30;
    zero = 0;
    frames->flags200 = 0xC404;
    frames->selector21C = zero;
    frames->palette20A = 0xE;
    frames->priority20B = 0xC0;
    coordinates = gUnknown_083AD524;
    work = gState0TypedWork.bytes;
    column = work + 0x3D;
    bank = work[0x3C];
    temp_r0 = ((bank * 3) + *column) * 2;
    temp_r1 = *(const u8 *)((u32)coordinates + temp_r0);
    temp_r0 += 1;
    temp_r3 = *(const u8 *)((u32)coordinates + temp_r0);
    if (bank == 0) {
        frames->x202 = temp_r1 + 0x10;
        frames->y204 = (s16) temp_r3;
        frames->frame206 = 0x306;
    } else {
        frames->x202 = temp_r1 - 0x10;
        frames->y204 = (s16) temp_r3;
        frames->frame206 = 0x307;
    }
}

/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "state0_work.h"

extern const u8 *const gState0NextCommands_083B6100[];

void sub_080238A0(void);

void sub_080238A0(void) {
    const u8 *const *commands;
    u32 keys;
    commands = gState0NextCommands_083B6100;
    sub_08040BD8(commands[gState0TypedWork.bytes[0x84]], 0x21);
    if (((gState0TypedWork.bytes[0x89] != 0) || !((keys = *(u8 *)&gRepeatedKeys), (keys & 1u) & keys)) && (gState0TypedWork.widths.word86 != 0)) {
        gState0TypedWork.widths.word86 -= 1;
        return;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

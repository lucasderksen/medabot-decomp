/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "state0_work.h"

extern const u8 *gState0NextCommands_083B6100[];

void sub_08022938(void);

void sub_08022938(void) {
    const u8 **table;
    u32 keys;
    table = gState0NextCommands_083B6100;
    sub_08040BD8(table[62], 0x21U);
    if (((gState0TypedWork.bytes[0x89] != 0) ||
         !((keys = *(u8 *)&gRepeatedKeys), (keys & 1u) & keys)) &&
        (gState0TypedWork.widths.word86 != 0)) {
        gState0TypedWork.widths.word86 -= 1;
        return;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

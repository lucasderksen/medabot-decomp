/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_080374E0(u32 value, u32 limit);
void sub_0803752C(s32 start, s32 end, u32 limit);

void sub_080374E0(u32 value, u32 limit) {

    void *remaining;

    if (value > limit) {
        gState0TransferWork.limits.values[0] = (s16) limit;
        gState0TransferWork.limits.values[2] = (s16) limit;
        remaining = (gState0TransferWork.limits.values + 2) - 1;
        *(s16 *)remaining = 0;
        gState0TransferWork.limits.flag = 0;
        return;
    }
    gState0TransferWork.limits.values[0] = (s16) value;
    gState0TransferWork.limits.values[2] = (s16) value;
    gState0TransferWork.limits.values[1] = limit - value;
    gState0TransferWork.limits.flag = 1;
}

void sub_0803752C(s32 start, s32 end, u32 limit) {

    u32 difference;
    void *remaining;

    difference = (u32)end - (u32)start;
    if (difference > limit) {
        gState0TransferWork.limits.values[0] = (s16) limit;
        gState0TransferWork.limits.values[2] = (s16) limit;
        remaining = (gState0TransferWork.limits.values + 2) - 1;
        *(s16 *)remaining = 0;
        gState0TransferWork.limits.flag = 0;
        return;
    }
    gState0TransferWork.limits.values[0] = (s16) difference;
    gState0TransferWork.limits.values[2] = (s16) difference;
    gState0TransferWork.limits.values[1] = limit - difference;
    gState0TransferWork.limits.flag = 1;
}

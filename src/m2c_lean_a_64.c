/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "frame_command_data.h"
#include "input.h"
#include "pose_channels.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_inventory_parts.h"
#include "state0_work.h"


void sub_0800A1E4(void);

void sub_0800A1E4(void) {

    s32 found;

    if (gState0TypedWork.bytes[0x41] > 1) {
        if (0x20 & (u8)gRepeatedKeys) {
            sub_08074DE0(2);
            found = 0;
            do {
                if (gState0TypedWork.bytes[0x3D] == 0) {
                    gState0TypedWork.bytes[0x3D] = 0x1D;
                } else {
                    gState0TypedWork.bytes[0x3D] = gState0TypedWork.bytes[0x3D] - 1;
                }
                if (0x80 & gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte0) {
                    if (gState0TypedWork.bytes[0x3C] != 1)
                    {
                        found = 1;
                        goto second;
                    }
                    if (!(0x40 & gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte0)) {
                        found = 1;
                    }
                }
            } while (found == 0);
        }
    second:
        if (0x10 & (u8)gRepeatedKeys) {
            sub_08074DE0(2);
            found = 0;
            do {
                if (gState0TypedWork.bytes[0x3D] == 0x1D) {
                    gState0TypedWork.bytes[0x3D] = 0;
                } else {
                    gState0TypedWork.bytes[0x3D] = gState0TypedWork.bytes[0x3D] + 1;
                }
                if (0x80 & gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte0) {
                    if (gState0TypedWork.bytes[0x3C] != 1) {
                        return;
                    }
                    if (!(0x40 & gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte0)) {
                        found = 1;
                    }
                }
            } while (found == 0);
        }
    }
}

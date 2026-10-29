/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0803579C(u8, u8);
extern s32 sub_08035814(u8);
extern s32 sub_0803725C();
extern s32 sub_08037280(u8, u8);

void sub_080249C0(void);

void sub_080249C0(void) {
    sub_0803579C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
    sub_08035814(gState0TransferWork.bytes[0x87]);
    if (sub_0803725C() != 0) {
        gState0TransferWork.bytes[0xA6] = 0x1A;
        gState0TransferWork.bytes[0xAA]++;
    } else if (sub_080331F8(gState0TransferWork.bytes[0x88]) == 0) {
        gState0TransferWork.bytes[0xA6] = 0x39;
        gState0TransferWork.bytes[0xAA]++;
    } else {
        sub_08036270();
        sub_08037280(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
        gState0TransferWork.bytes[0xAA] = 4;
    }
}

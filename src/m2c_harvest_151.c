/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0803598C(s32, s32, s32);
extern s32 sub_080359D8(s32, s32, s32);
extern s32 sub_08035A24(s32, s32, s32);
extern s32 sub_08035A70(s32, s32, s32);

void sub_080391C4(void);

void sub_080391C4(void) {
    u8 *var_r1;

    if (sub_0803598C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7], gState0TransferWork.bytes[0x88]) != 0) {
        gState0TransferWork.bytes[0xB8] = 2;
        gState0TransferWork.bytes[0xBE] = 2;
        return;
    }
    if (sub_080359D8(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7], gState0TransferWork.bytes[0x88]) != 0) {
        var_r1 = gState0TransferWork.bytes + 0xB8;
        *var_r1 = 2;
        var_r1 += 6;
        *var_r1 = 3;
        return;
    }
    if (sub_08035A24(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7], gState0TransferWork.bytes[0x88]) != 0) {
        var_r1 = gState0TransferWork.bytes + 0xB8;
        *var_r1 = 2;
        var_r1 += 6;
        *var_r1 = 4;
        return;
    }
    if (sub_08035A70(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7], gState0TransferWork.bytes[0x88]) != 0) {
        var_r1 = gState0TransferWork.bytes + 0xB8;
        *var_r1 = 2;
        var_r1 += 6;
        *var_r1 = 6;
    }
}

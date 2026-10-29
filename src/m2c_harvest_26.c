/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_0803D4AC();

void sub_080182D0(void);
void sub_08039598(void);
void sub_080395C0(void);
void sub_0803EA18(void);
void sub_08072BE4(void *arg0);

void sub_080182D0(void) {
    u8 var_r0;
    u8 var_r0_2;

    if (gState0TypedWork.bytes[0x46] == 2) {
        gState0TypedWork.bytes[0x46] = 0;
    } else {
        gState0TypedWork.bytes[0x46] = gState0TypedWork.bytes[0x46] + 1;
    }
    if (gState0TypedWork.bytes[0x3D] == gState0TypedWork.bytes[0x46]) {
        if (gState0TypedWork.bytes[0x3D] == 2) {
            gState0TypedWork.bytes[0x46] = 0;
        } else {
            gState0TypedWork.bytes[0x46] = gState0TypedWork.bytes[0x46] + 1;
        }
    }
}

void sub_08039598(void) {
    u8 var_r0;

    if (gState0TransferWork.bytes[0xB8] == 2) {
        gState0TransferWork.bytes[0xFD] = 1;
    } else {
        gState0TransferWork.bytes[0xFD] = 0;
    }
    sub_0803D4AC();
}

void sub_080395C0(void) {
    u8 var_r0;

    if (gState0TransferWork.bytes[0xB8] == 4) {
        gState0TransferWork.bytes[0xFD] = 1;
    } else {
        gState0TransferWork.bytes[0xFD] = 0;
    }
    sub_0803D4AC();
}

void sub_0803EA18(void) {
    u8 var_r0;

    if (gState0TransferWork.bytes[0x1A0] == 0x60) {
        gState0TransferWork.bytes[0x1A0] = 0;
    } else {
        gState0TransferWork.bytes[0x1A0] = gState0TransferWork.bytes[0x1A0] + 4;
    }
}

void sub_08072BE4(void *arg0) {
  u8 new_var;
  u8 *temp_r1;
  u8 *temp_r1_2;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var = (u8) (*temp_r1);
  *((u8 *) (((s8 *) arg0) + 0x53)) = new_var;
  temp_r1_2 = temp_r1 + 1;
  *((u8 **) (((s8 *) arg0) + 0x14)) = temp_r1_2;
  *((u8 **) (((s8 *) arg0) + 0x1C)) = temp_r1_2;
}

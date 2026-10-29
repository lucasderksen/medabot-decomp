/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"


void sub_080734F4(void *arg0, s16 *arg1);

void sub_080734F4(void *arg0, s16 *arg1) {
    u8 temp_r3;

    temp_r3 = (*(u8 *)((u8 *)(arg0) + 0x50));
    if (1 & temp_r3) {
        *arg1 = (*(u8 *)((u8 *)(arg0) + 0x69)) | 0x8000;
        (*(u8 *)((u8 *)(arg0) + 0x50)) = (u8) (0xFE & temp_r3);
    }
}

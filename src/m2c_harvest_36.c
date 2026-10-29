/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"


void sub_080356B4(s32 arg0);
s32 sub_08036BB8(u8 *arg0, s32 arg1, s32 arg2);

void sub_080356B4(s32 arg0) {
    __typeof__(gFrameObjects[0]) *array0;
    struct FrameObject *temp_r0;

    array0 = gFrameObjects;
    temp_r0 = &array0[arg0];
    temp_r0->flags &= 0xFDFF;
}

s32 sub_08036BB8(u8 *arg0, s32 arg1, s32 arg2) {
    __typeof__(gSetupBuffer_03000590[0]) *array0;
    u8 *temp_r0;
    u8 temp_r0_2;

    array0 = gSetupBuffer_03000590;
    temp_r0 = &array0[(arg2 * 0x18) + (arg1 << 8)];
    if ((*(u8 *)((u8 *)(temp_r0) + 0x59)) != 0) {
        temp_r0_2 = *arg0;
        if (temp_r0_2 != 0) {
            *arg0 = temp_r0_2 - 1;
            (*(u8 *)((u8 *)(temp_r0) + 0x59)) = (u8) ((*(u8 *)((u8 *)(temp_r0) + 0x59)) - 1);
            return 0;
        }
    }
    return 1;
}

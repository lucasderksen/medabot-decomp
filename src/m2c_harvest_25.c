/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "frame.h"
#include "gba.h"
#include "state0_work.h"

extern s32 gUnknown_084885C0;
extern s32 gUnknown_084C7FF4;
extern s32 gUnknown_084E4638;
extern u8 gUnknown_08487D90;
extern u8 gUnknown_084C3E64;
extern u8 gUnknown_084C571C;
extern u8 gUnknown_084C7B64;
s32 sub_0803D450();
s32 sub_0803D4AC();

void sub_0803B5DC(void);

void sub_0803B5DC(void) {
    u8 *work0;
    u8 temp_r3;

    sub_0803D450();
    LeDecompress(&gUnknown_084C571C, (void *)0x06006400);
    LeDecompress(&gUnknown_08487D90, (void *)0x06006520);
    LeDecompress(&gUnknown_084C3E64, (void *)0x06006600);
    LeDecompress(&gUnknown_084C7B64, (void *)0x06006800);
    CpuFastSet(&gUnknown_084885C0, (void *)0x05000140, 8U);
    CpuFastSet(&gUnknown_084E4638, (void *)0x05000100, 8U);
    CpuFastSet(&gUnknown_084C7FF4, (void *)0x05000160, 8U);
    temp_r3 = 2 & gState0TransferWork.bytes[0xF8];
    if (temp_r3 == 0) {
        gFrameObjects[9].unknown2C[1] = temp_r3;
    } else {
        gFrameObjects[9].unknown2C[1] = 1;
    }
    gFrameObjects[9].unknown2C[2] = 1;
    work0 = (u8 *) &gState0TransferWork;
    gFrameObjects[9].byte2B = (u8) (*(u16 *)((u8 *)(work0) + 0x102));
    gFrameObjects[9].unknown2C[0] = (u8) (*(u16 *)((u8 *)(work0) + 0x104));
    gFrameObjects[9].unknown23[6] = 0x38;
    sub_0803D4AC();
}

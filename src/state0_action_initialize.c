#include "state0_next_helpers.h"
#include "state0_work.h"
#include "frame_objects.h"
#include "frame.h"
#include "gba.h"
#include "global.h"
#include "state0_next_helpers.h"

/* Partial physical access coverage only, not an original complete RAM type. */
struct ObservedActionWaitWork {
    u8 unknown00[0x87];
    u8 selected87;
    u8 selected88;
    u8 unknown89[2];
    u8 byte8B;
    u8 unknown8C[0x29];
    u8 completeB5;
    u8 unknownB6[0x1A];
    u8 byteD0;
    u8 unknownD1[0x1B];
    s16 signedEC;
    u8 unknownEE[0xB];
    u8 byteF9;
    u8 unknownFA;
    u8 byteFB, byteFC, byteFD, byteFE;
    u8 unknownFF;
    u16 half100;
    u8 unknown102[0x5D];
    u8 byte15F, byte160;
};

/* Partial backing view of actual two frame-byte writes, not a full object type. */
struct ObservedFrameWaitBytes { u8 unknown00[0x69]; u8 byte69; u8 unknown6A[0x3F]; u8 byteA9; };

void sub_08034074(void)
{
    struct ObservedActionWaitWork *work;
    u8 *setup;
    u32 rowOffset;
    u8 *record;
    sub_08035DE8();
    sub_080361C4();
    sub_08036218();
    sub_08040CD0(0, 0x28);
    CpuFastSet((const void *)0x084E4658, (void *)0x05000380, 8);
    work = (void *)gState0TransferWork.bytes;
    work->half100 = 0;
    work->byteFB = 0;
    work->byteFC = 0;
    work->byteFD = 0;
    work->byteFE = 0;
    setup = gSetupBuffer_03000590;
    rowOffset = work->selected87 * 256;
    record = setup + rowOffset;
    if (record[0xDD] <= 3)
        work->byteF9 = setup[work->selected87 * 256 + gState0TransferWork.bytes[0xA7] * 24 + 0x49];
    else
        work->byteF9 = record[0xA8] + 0x50;
    ((struct ObservedFrameWaitBytes *)gFrameObjects)->byte69 = 1;
    ((struct ObservedFrameWaitBytes *)gFrameObjects)->byteA9 = 1;
    sub_08034F08();
}


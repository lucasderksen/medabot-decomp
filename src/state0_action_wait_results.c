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

void sub_08034120(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    work->completeB5 = 0;
    sub_080393BC();
    if (work->completeB5)
    {
        gUnknown_03000440[0x130] = 0;
        sub_08034F08();
    }
}


void sub_08034170(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    work->byteD0 = work->byte8B;
    sub_08034F68(work->selected88, work->byteD0, work->signedEC);
    sub_08034F08();
}


void sub_080341C0(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_0801E2D8();
    if (work->completeB5)
        sub_08034F08();
}


void sub_08034200(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_0801F484();
    if (work->completeB5)
        sub_08034F08();
}


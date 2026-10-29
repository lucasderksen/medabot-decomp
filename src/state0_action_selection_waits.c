#include "state0_next_helpers.h"
#include "state0_work.h"
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

void sub_080345E8(void)
{
    u8 *work = gState0TransferWork.bytes;
    work[work[0x8A] * 8 + 0x2A] = 0;
    work[work[0x8A] * 8 + 0x2B] = 0;
    work[work[0x8A] * 8 + 0x2C] = 0;
    work[work[0x8A] * 8 + 0x2D] = 0;
    sub_08034F08();
}

void sub_08034628(void)
{
    sub_08026108();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08034644(void)
{
    u8 *work;
    sub_0802645C();
    work = gState0TransferWork.bytes;
    if (work[0xB5])
    {
        if (work[0xAB] == 1)
            sub_08034F08();
        else
        {
            gMainSubstate = 8;
            gUnknown_0300137C = 0;
        }
    }
}

void sub_08034684(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_08026884();
    if (work->completeB5)
        sub_08034F08();
}

void sub_08034708(void)
{
    struct ObservedActionWaitWork *work = (void *)gState0TransferWork.bytes;
    sub_0803769C(work->selected87);
    sub_080376F4(work->selected87);
    sub_08034F08();
}

void sub_0803476C(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_08026CF4();
    if (work->completeB5)
        sub_08034F08();
}

void sub_080347AC(void)
{
    sub_08036270();
    sub_08034F08();
}

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

void sub_08034008(void)
{
    struct ObservedActionWaitWork *work;
    sub_08035BD4();
    work = (void *)gState0TransferWork.bytes;
    sub_08035BFC(work->selected87, gState0TransferWork.bytes[0xA7]);
    sub_08034F08();
}


void sub_0803402C(void)
{
    sub_0801DE1C();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}


void sub_08034048(void)
{
    gUnknown_03000440[0x130] = 1;
    sub_0801DEE4();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}


void sub_08034240(void)
{
    sub_0801FA40();
    if (gState0TransferWork.bytes[0xB5])
    {
        gUnknown_03000440[0x130] = 0;
        sub_08034F08();
    }
}


void sub_0803426C(void)
{
    sub_0801FDEC();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

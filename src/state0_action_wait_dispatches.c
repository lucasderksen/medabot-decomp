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

void sub_08034288(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_08020050();
    if (work->completeB5)
        sub_08034F08();
}

void sub_080342C8(void)
{
    sub_0802057C();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_080342E4(void)
{
    sub_080207A4();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08034300(void)
{
    sub_0802081C();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_0803431C(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_080208C0();
    if (work->completeB5)
        sub_08034F08();
}

void sub_0803435C(void)
{
    sub_080209B0();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08034378(void)
{
    struct ObservedActionWaitWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_08020A68();
    if (work->completeB5)
        sub_08034F08();
}

void sub_080343B8(void)
{
    sub_08020CFC();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_080343D4(void)
{
    sub_080218BC();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_080343F0(void)
{
    sub_08021E04();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_0803440C(void)
{
    sub_08022154();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08034428(void)
{
    sub_080223BC();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

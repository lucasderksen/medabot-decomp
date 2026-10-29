#include "equipment_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "global.h"
#include "state0_next_helpers.h"

/* Partial observed access coverage, not an original complete work type. */
struct ObservedActionResultWork {
    u8 unknown00[0x60];
    u8 byte60;
    u8 unknown61[0x26];
    u8 selected87, selected88;
    u8 unknown89[0x2C];
    u8 completeB5;
    u8 unknownB6[2];
    u8 byteB8;
    u8 unknownB9[0x1D];
    u16 halfD6[4];
    u8 unknownDE[0xE];
    u16 halfEC;
    u8 unknownEE[8];
    u8 byteF6, unknownF7, byteF8;
    u8 unknownF9[6];
    u8 flagsFF;
    u8 unknown100[0x14];
    u8 byte114, byte115;
    u8 unknown116[0x49];
    u8 byte15F, byte160, byte161;
    u8 unknown162[0x26];
    u8 byte188, byte189;
};

/* Physical stride and named access bytes only, with no array extent claim. */
struct ObservedActionResultRecord {
    u8 unknown00[0xDE];
    u8 byteDE, unknownDF, byteE0, byteE1;
    u8 unknownE2[0x1E];
};

void sub_080347F8(void)
{
    {
        struct ObservedActionResultWork *work;
        struct ObservedActionResultRecord *records;
        u32 firstResult;
        u8 bit;
        sub_08035DE8();
        firstResult = sub_080361C4();
        work = (void *)gState0TransferWork.bytes;
        work->byte15F = firstResult;
        work->byte160 = sub_08036218();
        work->byteF6 = 3;
        records = (void *)gSetupBuffer_03000590;
        records[work->selected87].byteE0 = work->selected87 + 1;
        work->byte161 = work->selected88;
        sub_080355C4(work->selected87);
        work->byteF8 ^= 2;
        bit = work->byteF8 & 2;
        if (bit == 0)
            work->byte114 = 0;
        else
        {
            work->byte114 = 40;
            work->flagsFF |= 1;
        }
    }
    {
        struct ObservedActionResultWork *work = (void *)gState0TransferWork.bytes;
        if (!(work->byteF8 & 2))
        {
            work->byte115 = 40;
            work->flagsFF |= 2;
        }
        else
            work->byte115 = 0;
    }
    sub_08034F08();
}

void sub_080348D0(void)
{
    struct ObservedActionResultWork *work;
    u32 firstResult;
    sub_08035DE8();
    firstResult = sub_080361C4();
    work = (void *)gState0TransferWork.bytes;
    work->byte15F = firstResult;
    work->byte160 = sub_08036218();
    sub_08026ED0();
    if (work->completeB5)
        sub_08034F08();
}

void sub_08034AA0(void)
{
    u32 random = sub_080424B8();
    struct ObservedActionResultWork *work = (void *)gState0TransferWork.bytes;
    const u8 *table = gActionRandomBytes_083AF380;
    u32 mask = 15;
    work->byte188 = table[random & mask];
    work->byte189 = table[sub_080424B8() & mask];
    work->halfEC = (work->byte188 + work->byte189) * 10;
    sub_08034F08();
}

void sub_08034B68(void)
{
    struct ObservedActionResultWork *work = (void *)gState0TransferWork.bytes;
    u8 *selected = &work->selected87;
    work->byte60 = sub_08032FB8(*selected);
    if (sub_08037830(work->byte60, *selected) == 255)
        work->halfEC = 10;
    sub_08034F08();
}

void sub_08034BA0(void)
{
    sub_08026FD0();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"
/* Partial physical access coverage, not an original complete RAM type. */
struct ObservedActionFlagsWork {
    u8 unknown00[0x87];
    u8 selected87;
    u8 selected88;
    u8 unknown89[0x1E];
    u8 indexA7;
    u8 unknownA8[0x40];
    s16 signedE8;
    u16 valueEA;
};

void sub_08033C00(void)
{
    sub_08038BC0();
    sub_08034F08();
}

void sub_08033C10(void)
{
    sub_08038D30();
    sub_08034F08();
}

void sub_08033CD0(void)
{
    sub_08038E54();
    sub_08034F08();
}

void sub_08033CE0(void)
{
    sub_08039188();
    sub_08034F08();
}

void sub_08033CF0(void)
{
    sub_080391C4();
    sub_08034F08();
}

void sub_08033D00(void)
{
    sub_080392D8();
    sub_08034F08();
}

void sub_08033D10(void)
{
    struct ObservedActionFlagsWork *work = (void *)gState0TransferWork.bytes;
    work->valueEA = work->signedE8 >> 2;
    sub_08034F08();
}

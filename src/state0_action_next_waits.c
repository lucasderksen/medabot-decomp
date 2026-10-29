#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

struct ObservedRecordFlagAccess
{
    u8 unknown00[0x59];
    u8 byte59;
};

/* Partial unsigned halfword view, physical stride64 established by references. */
struct ObservedFrameHalfwords
{
    u16 flags;
    u16 x;
    u16 y;
    u8 unknown06[0x3A];
};

/* Only observed object9 physical output fields, over canonical frame backing. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x240];
    u16 flags240;
    u16 screenX242;
    u16 screenY244;
    u8 unknown246[4];
    u8 palette24A;
    u8 priority24B;
    u8 unknown24C[0x10];
    u8 table25C;
    u8 unknown25D[5];
    u8 commandStopped262;
    u8 unknown263;
    u8 byte264;
    u8 unknown265[0xB];
    u16 half270;
    u16 half272;
};

void sub_0801D2C4(void)
{
    u8 *work = gState0TransferWork.bytes;
    work[0xB5] = 1;
    work[0xAB] = 1;
}

void sub_0801D2D8(void)
{
    u8 *work = gState0TransferWork.bytes;
    work[0xB5] = 1;
    work[0xAB] = 2;
}

void sub_0801D36C(void)
{
    u8 *work = gState0TransferWork.bytes;
    work[0xB5] = 1;
    work[0xAB] = 1;
}

void sub_0801D3F8(void)
{
    u8 *work = gState0TransferWork.bytes;
    work[0xB5] = 1;
    work[0xAB] = 1;
}

void sub_0801D434(void)
{
    CpuFastSet(gActionPalette_084E45D8, (void *)0x050002C0, 8);
    gState0TransferWork.bytes[0xAA]++;
}

void sub_0801D524(void)
{
    if (sub_080355F0(9))
        gState0TransferWork.bytes[0xAA]++;
}

void sub_0801D544(void)
{
    sub_08040BD8(gUnknownPointers_083B6100[27], 9);
    if (((struct ObservedActionFrameBacking *)gFrameObjects)->commandStopped262 == 255)
    {
        sub_08040CD0(9, 1);
        gState0TransferWork.bytes[0xB5] = 1;
    }
}

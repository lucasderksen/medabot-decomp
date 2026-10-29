#include "bg_scroll.h"
#include "main.h"
#include "input.h"
#include "display_helpers.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Partial backing access model over canonical objects; no new data extent. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x842];
    u16 screenX842;
    u8 unknown844[4];
    u8 scaleX848;
    u8 unknown849[0x19];
    u8 commandStopped862;
};

void sub_0801C9C8(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *row = &work[0x87];
    sub_08034FC8(*row, gFrameCounter, work[0x51]);
    sub_08040BD8(gUnknownPointers_083B6100[work[0x52]], 33);
    if (((struct ObservedActionFrameBacking *)gFrameObjects)->commandStopped862 == 255)
    {
        sub_0803512C(*row);
        work[0xAA]++;
    }
}

void sub_0801CA60(void)
{
    u8 *scratch = gUnknown_0300052E;
    u8 *work = gState0TransferWork.bytes;
    sub_0801A28C(scratch, *(u16 *)&work[0xC8], 1);
    sub_0801A33C(scratch, work[0x87], 33);
    sub_08074DE0(91);
    scratch -= 0x6A;
    *scratch = 0;
    work[0xAA]++;
}

void sub_0801CAA8(void)
{
    u8 *scratch = gUnknown_0300052E;
    u8 *counter;
    u32 count;
    sub_0801A574(scratch, gState0TransferWork.bytes[0x87], 33);
    counter = scratch - 0x6A;
    count = *counter + 1;
    *counter = count;
    scratch -= 0x65;
    if (*scratch == 0 && (*(u8 *)&gRepeatedKeys & 1) && (u8)count > 50)
        *counter = 120;
    if (gUnknown_03000440[0x84] == 120)
    {
        u8 *work = gState0TransferWork.bytes;
        sub_08040CD0(work[0x87] * 4 + 33, 4);
        work[0xAA]++;
    }
}

void sub_0801CB74(void)
{
    u8 *work = gState0TransferWork.bytes;
    sub_08035164(work[0x87], work[0xD0], *(u16 *)&work[0xC8]);
    work[0xAA]++;
}

void sub_0801CC24(void)
{
    if (sub_0803526C(33, 60, 132))
    {
        sub_08074DE0(65);
        gUnknown_03000440[0x84] = 0;
        gState0TransferWork.bytes[0xAA]++;
    }
}

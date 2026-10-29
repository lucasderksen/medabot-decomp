#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "display_helpers.h"
#include "frame_objects.h"

void sub_08013A74(void)
{
    u8 *selection;
    u8 *base;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    base = gUnknown_03000440;
    counter = base;
    counter += 0x84;
    if (*counter <= 8)
    {
        u32 position = *counter * 4;
        u32 brightness = 32;
        u32 weight = brightness - position;
        u32 mask = 0xFFFF;
        sub_0803F684(0, weight, mask);
        brightness -= *counter * 4;
        sub_0803F998(0, brightness, mask);
        (*counter)++;
    }
    else
        gUnknown_0300137C = 11;
}

void sub_08013AE4(void)
{
    u8 *work;
    u8 *selection;
    u32 control;
    u32 zero;
    sub_080195C0();
    work = gState0TransferWork.bytes;
    selection = work + 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    switch (*selection)
    {
    case 0:
        {
            u8 *flags = work + 0x44;
            u32 previous = *flags;
            u32 mask = 1;
            mask |= previous;
            *flags = mask;
        }
        break;
    case 1:
        {
            u8 *flags = work + 0x44;
            u32 previous = *flags;
            u32 mask = 2;
            mask |= previous;
            *flags = mask;
        }
        break;
    case 2:
        {
            u8 *flags = work + 0x44;
            u32 previous = *flags;
            u32 mask = 4;
            mask |= previous;
            *flags = mask;
        }
        break;
    }
    sub_08040CD0(0, 70);
    control = *(volatile u16 *)0x04000008;
    sub_0803EF8C(30, 8, 0, 12, control, zero = 0);
    sub_0803EF8C(30, 8, 0, 12, *(volatile u16 *)0x0400000A, zero);
    gUnknown_0300137C = 13;
}

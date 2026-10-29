#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "utility_helpers.h"
#include "display_helpers.h"
#include "gba.h"


void sub_08013164(void)
{
    u8 *selection;
    u8 *base;
    u8 *counter;
    u8 next;
    u8 keys;
    u32 cancel;
    u32 zero;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_0801B9C4();
    base = gUnknown_03000440;
    counter = base + 0x84;
    next = *counter + 1;
    zero = 0;
    *counter = next;
    sub_080168F4();
    sub_080169AC();
    sub_08016C0C();
    keys = *gUnknown_0300058C;
    cancel = (u8)(keys & 2);
    if (cancel)
    {
        sub_08074DE0(5);
        sub_08040CD0(0, 6);
        sub_0801BACC();
        sub_08040CD0(20, 38);
        sub_0803EF8C(7, 1, 14, 12, *(volatile u16 *)0x04000008, zero);
        *counter = zero;
        gUnknown_0300137C++;
    }
    else if (keys & 1)
    {
        sub_08074DE0(4);
        sub_0801BACC();
        *(u16 *)(base + 0x86) = cancel;
        gUnknown_0300137C = 21;
    }
}


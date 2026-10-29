#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "utility_helpers.h"
#include "display_helpers.h"
#include "gba.h"


void sub_08013438(void)
{
    u8 *work;
    u8 *selection;
    u8 *base;
    u8 *counter;
    u8 next;
    u8 keys;
    u32 cancel;
    u32 zero;
    sub_080195C0();
    work = gState0TransferWork.bytes;
    selection = work + 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    base = gUnknown_03000440;
    counter = base + 0x84;
    next = *counter + 1;
    zero = 0;
    *counter = next;
    sub_0801767C();
    sub_080175FC();
    sub_080173B4(1);
    keys = *gUnknown_0300058C;
    cancel = (u8)(keys & 2);
    if (cancel)
    {
        sub_08074DE0(5);
        sub_0803EF8C(8, 1, 1, 17, *(volatile u16 *)0x04000008, zero);
        sub_08015E68(*selection);
        sub_08040CD0(0, 5);
        sub_08040CD0(20, 36);
        *counter = zero;
        gUnknown_0300137C++;
    }
    else if (keys & 1)
    {
        sub_08074DE0(4);
        *(u16 *)(base + 0x86) = cancel;
        gUnknown_0300137C = 29;
    }
}


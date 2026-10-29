#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "display_helpers.h"
#include "gba.h"


void sub_08012C64(void)
{
    u8 *work;
    u8 *selection;
    u8 keys;
    sub_080195C0();
    work = gState0TransferWork.bytes;
    selection = work + 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_08016288();
    sub_080178CC();
    if (work[0x83] != 0)
        return;
    sub_0801630C();
    keys = *gUnknown_0300058C;
    if (keys & 1)
    {
        if (gUnknown_03000440[0x89] == 1 && work[0x81] == 5)
        {
            sub_08074DE0(6);
            return;
        }
        sub_08074DE0(4);
        sub_08017914();
        gUnknown_03000440[0x84] = 0;
        gUnknown_0300137C++;
    }
    else if (keys & 2)
    {
        u8 counter = work[0x84];
        if (counter == 0 && *selection != 0)
        {
            u32 selected;
            u8 component;
            sub_08074DE0(5);
            selected = *selection;
            component = selected % 3u;
            sub_08015A00(selected, 0x28, component * 24 + 0x24);
            (*selection)--;
            sub_08015BA8(0);
            sub_0801A744(*selection);
            work[0x81] = counter;
            work[0x82] = counter;
            sub_08040CD0(0, 0x46);
            sub_0803EF8C(30, 8, 0, 12, *(volatile u16 *)0x04000008, 0);
            sub_0803EF8C(30, 8, 0, 12, *(volatile u16 *)0x0400000A, 0);
            gUnknown_0300137C = 4;
        }
    }
}

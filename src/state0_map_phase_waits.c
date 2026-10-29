#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "utility_helpers.h"


void sub_08012D98(void)
{
    u8 *selection;
    u8 *base;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_08016554();
    base = gUnknown_03000440;
    counter = base;
    counter += 0x84;
    (*counter)++;
    if (*counter == 20)
    {
        sub_08040CD0(30, 11);
        *counter = 0;
        gUnknown_0300137C++;
    }
}

void sub_08012DF4(void)
{
    u8 *selection;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_080165D0();
    sub_08016614();
    sub_08016660();
    counter = gUnknown_03000440;
    counter += 0x84;
    (*counter)++;
    if (*counter == 16)
        sub_080165B0();
}

void sub_08012E40(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_08015AFC();
    sub_08016068();
    sub_08044118(6, 5, 12, 21, *(volatile u16 *)0x0400000A, (u16 *)0x02020800);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08012EA8(void)
{
    u8 *selection;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_08016F28();
    sub_08016F64();
    sub_08016FB4();
    counter = gUnknown_03000440;
    counter += 0x84;
    (*counter)++;
    if (*counter == 10)
    {
        sub_08015F24();
        gUnknown_0300137C = 7;
    }
}

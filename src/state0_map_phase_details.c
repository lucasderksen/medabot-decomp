#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "utility_helpers.h"
#include "display_helpers.h"
#include "gba.h"


void sub_0801303C(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    CpuFastSet(gState0Palette_084E44F8, (void *)0x05000340, 8);
    CpuFastSet(gState0Palette_084E45D8, (void *)0x050002C0, 8);
    sub_08040CD0(0, 6);
    sub_08040CD0(30, 11);
    sub_080166AC();
    sub_0801B76C();
    sub_08044118(12, 4, 9, 21, *(volatile u16 *)0x04000008, (u16 *)0x02020800);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_080130D8(void)
{
    u8 *selection;
    u8 *base;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_080166F0();
    sub_0801672C();
    base = gUnknown_03000440;
    counter = base;
    counter += 0x84;
    (*counter)++;
    if (*counter == 16)
    {
        sub_08016DA4();
        sub_0801677C();
        sub_080167BC(1);
        sub_08016804(1);
        sub_0801684C(1);
        sub_08016894(1);
        sub_08016A3C();
        sub_08016AD8();
        sub_08016D18();
        sub_08016DCC();
        sub_0801B894();
        *counter = 0;
        gUnknown_0300137C++;
    }
}

void sub_08013228(void)
{
    u8 *selection;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_08016EDC();
    sub_08016E90();
    counter = gUnknown_03000440;
    counter += 0x84;
    (*counter)++;
    if (*counter == 16)
    {
        CpuFastSet(gState0Palette_084E44D8, (void *)0x05000340, 8);
        gUnknown_0300137C = 11;
    }
}

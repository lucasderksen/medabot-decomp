#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "utility_helpers.h"
#include "display_helpers.h"
#include "gba.h"


void sub_08013288(void)
{
    u8 *selection;
    u8 *base;
    u8 *counter;
    u8 next;
    u32 zero;
    u16 *timer;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    base = gUnknown_03000440;
    counter = base + 0x84;
    next = *counter;
    zero = 0;
    next += 2;
    *counter = next;
    sub_080168F4();
    sub_08016C0C();
    timer = (u16 *)(base + 0x86);
    (*timer)++;
    if (*timer == 16)
    {
        sub_08040CD0(0, 70);
        sub_0803EF8C(30, 8, 0, 12, *(volatile u16 *)0x04000008, zero);
        sub_0803EF8C(30, 8, 0, 12, *(volatile u16 *)0x0400000A, zero);
        CpuFastSet(gState0Palette_084E44D8, (void *)0x05000340, 8);
        gUnknown_0300137C = 13;
    }
}

void sub_08013330(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    CpuFastSet(gState0Palette_084E4518, (void *)0x05000340, 8);
    sub_08040CD0(0, 6);
    sub_08040CD0(30, 11);
    sub_08017004();
    sub_08044118(12, 4, 9, 21, *(volatile u16 *)0x04000008, (u16 *)0x02020800);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_080133B8(void)
{
    u8 *selection;
    u8 *base;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_08017048();
    sub_08017084();
    base = gUnknown_03000440;
    counter = base;
    counter += 0x84;
    (*counter)++;
    if (*counter == 16)
    {
        sub_080170D4();
        sub_08017104();
        sub_08017178(1);
        sub_080171C0(1);
        sub_08017208(1);
        sub_08017130(1);
        sub_08017268();
        sub_080173B4(0);
        *counter = 0;
        gUnknown_0300137C++;
    }
}

void sub_08013508(void)
{
    u8 *selection;
    u8 *counter;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_08016EDC();
    sub_08017948();
    counter = gUnknown_03000440;
    counter += 0x84;
    (*counter)++;
    if (*counter == 16)
    {
        CpuFastSet(gState0Palette_084E44D8, (void *)0x05000340, 8);
        gUnknown_0300137C = 11;
    }
}

void sub_08013568(void)
{
    u8 *selection;
    u8 *base;
    u8 *counter;
    u8 next;
    u32 zero;
    u16 *timer;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    base = gUnknown_03000440;
    counter = base + 0x84;
    next = *counter;
    zero = 0;
    next += 2;
    *counter = next;
    sub_0801767C();
    sub_080173B4(1);
    timer = (u16 *)(base + 0x86);
    (*timer)++;
    if (*timer == 16)
    {
        sub_08040CD0(0, 70);
        sub_0803EF8C(30, 8, 0, 12, *(volatile u16 *)0x04000008, zero);
        sub_0803EF8C(30, 8, 0, 12, *(volatile u16 *)0x0400000A, zero);
        CpuFastSet(gState0Palette_084E44D8, (void *)0x05000340, 8);
        gUnknown_0300137C = 13;
    }
}

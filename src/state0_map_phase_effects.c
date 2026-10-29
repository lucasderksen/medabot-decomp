#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"
#include "display_effects.h"
#include "graphics.h"
#include "object_helpers.h"
#include "interrupts.h"
#include "gba.h"


void sub_08013614(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    sub_0803FAA0(1, 2, 0);
    gUnknown_0300137C++;
}

void sub_08013650(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    {
        const u8 *const *messages = gState0PartStatusMessages_083B722C;
        u8 *buffer = gSetupBuffer_03000590;
        u8 *record = buffer + *selection * 256;
        if (sub_0803FB3C(messages[record[6]]))
        {
            gUnknown_03000440[0x1B] = 0;
            gUnknown_0300137C++;
        }
    }
}

void sub_080136B0(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    if (sub_08041CA4())
        gUnknown_0300137C = 11;
}

void sub_080136E8(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    sub_080164F4(*selection);
    sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_0801372C(void)
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
        sub_0803F684(0, *counter * 4, 0xFFFF);
        sub_0803F998(0, *counter * 4, 0xFFFF);
        (*counter)++;
    }
    else
        gUnknown_0300137C++;
}

void sub_08013798(void)
{
    CpuFastSet((void *)0x06002800, (void *)0x02020800, 0x200);
    CpuFastSet((void *)0x0600C800, (void *)0x02021000, 0x200);
    CpuFastSet((void *)0x0600D000, (void *)0x02021800, 0x200);
    CpuFastSet((void *)0x0600D800, (void *)0x02022000, 0x200);
    CpuFastSet((void *)0x03002C30, (void *)0x02028000, 0x800);
    sub_0804253C(5, 63, 32);
    gUnknownCallback_030017F0 = DummyInterruptHandler;
    gUnknown_0300137C++;
}

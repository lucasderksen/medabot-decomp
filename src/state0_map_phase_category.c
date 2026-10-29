#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "display_helpers.h"


/* Observed byte offset only; original aggregate layout/extent are unknown. */
struct MapFlagsView { u8 unknown00[0x55]; u8 flags55; };

void sub_0801427C(void)
{
    struct MapFlagsView *work = (struct MapFlagsView *)&gState0TransferWork;
    u8 *flags = &work->flags55;
    if (*flags == 0)
    {
        sub_08018C38();
        sub_08018C78();
    }
    if (*flags & 2)
        gUnknown_0300137C = 96;
    else if (*flags & 4)
        gUnknown_0300137C = 104;
    else if (*flags & 8)
        gUnknown_0300137C = 112;
    else if (*flags & 16)
        gUnknown_0300137C = 120;
    else
    {
        sub_0801902C();
        sub_080195C0();
        sub_0801BBC4();
        if (sub_08019EF0())
        {
            sub_08019078();
            gUnknown_0300137C++;
        }
    }
}

void sub_08014314(void)
{
    u8 *work;
    sub_080195C0();
    sub_08019078();
    sub_0801A5D8();
    work = gState0TransferWork.bytes;
    if (work[0x45] == 0)
        gUnknown_0300137C = 68;
    else
    {
        u8 *record;
        sub_0801A640();
        record = gSetupBuffer_03000590;
        record += work[0x87] * 256;
        if (record[0x40] == 0)
            sub_0801A678();
        else
        {
            u8 mask = record[0xBD] & 4;
            if (mask)
                gUnknown_0300137C = 71;
            else
            {
                sub_0801A0D0();
                gMainSubstate = 8;
                gUnknown_0300137C = mask;
            }
        }
    }
}

void sub_080143A0(void)
{
    u8 *work;
    u8 *selected;
    u8 *setup;
    u8 *flags;
    sub_080195C0();
    setup = gSetupBuffer_03000590;
    work = gState0TransferWork.bytes;
    selected = work + 0x87;
    flags = setup + *selected * 256;
    flags += 0xBD;
    *flags ^= 4;
    sub_0801A0D0();
    sub_0801A678();
    sub_08015414(*selected);
    if (sub_0801A6B0())
    {
        sub_0803F624(work + 0x45, 12, 0);
        gUnknown_0300137C = 76;
    }
    else
        gUnknown_0300137C = 69;
}

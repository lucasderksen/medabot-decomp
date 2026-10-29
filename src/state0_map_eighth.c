#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "graphics.h"

void sub_08011268(void)
{
    u8 *work;
    u8 *selected;
    sub_08012098();
    sub_08043CD4();
    work = gState0TransferWork.bytes;
    selected = work + 0x186;
    if (*selected == 3)
    {
        *selected = 0;
        gUnknown_0300137C = 88;
    }
    else
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x16F;
        if (items[scaled])
            gUnknown_0300137C++;
        else
            (*selected)++;
    }
}

void sub_080112C4(void)
{
    sub_08012098();
    sub_08043CD4();
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_080112F0(void)
{
    sub_08012098();
    sub_08043CD4();
    if (gUnknown_03000440[0x84] <= 8)
    {
        sub_0803F684(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        sub_0803F998(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gUnknown_0300137C++;
}

void sub_08011490(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = work + 0x186;
    if (*selected == 3)
    {
        *selected = 0;
        gUnknown_0300137C = 91;
    }
    else
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x16F;
        if (items[scaled])
            gUnknown_0300137C = 78;
        else
            (*selected)++;
    }
}

void sub_080114E0(void)
{
    sub_08012098();
    sub_08043CD4();
    sub_080750F0(8);
    gUnknown_0300137C++;
}

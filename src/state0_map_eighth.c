#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "graphics.h"

void sub_08011268(void)
{
    u8 *work;
    u8 *selected;
    sub_08012098();
    StepFirstBgAutoScroll();
    work = gState0TransferWork.bytes;
    selected = work + 0x186;
    if (*selected == 3)
    {
        *selected = 0;
        gNestedCallbackIndex = 88;
    }
    else
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x16F;
        if (items[scaled])
            gNestedCallbackIndex++;
        else
            (*selected)++;
    }
}

void sub_080112C4(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    gNestedCallbackIndex++;
}

void sub_080112F0(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    if (gUnknown_03000440[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        BlendObjPaletteBanksNow(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gNestedCallbackIndex++;
}

void sub_08011490(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = work + 0x186;
    if (*selected == 3)
    {
        *selected = 0;
        gNestedCallbackIndex = 91;
    }
    else
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x16F;
        if (items[scaled])
            gNestedCallbackIndex = 78;
        else
            (*selected)++;
    }
}

void sub_080114E0(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    FadeOutMusic(8);
    gNestedCallbackIndex++;
}

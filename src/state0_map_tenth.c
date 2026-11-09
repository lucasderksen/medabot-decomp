#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "equipment_helpers.h"

extern u8 gUnknown_030057E0[];

void sub_08011A58(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    sub_080123A0();
    sub_08012468();
    if (gUnknown_03000440[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        BlendObjPaletteBanksNow(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gNestedCallbackIndex++;
}

void sub_08011ABC(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    sub_080123A0();
    sub_08012468();
    gNestedCallbackIndex = 61;
}

void sub_08011ADC(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    if (RunDialogue(gState0FixedMessages_083C6744[110]))
    {
        gUnknown_03000440[0x1B] = 0;
        gNestedCallbackIndex++;
    }
}

void sub_08011B18(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    if (RunDialoguePortraitClose())
    {
        u32 address = (u32)gUnknown_030057E0;
        address += 0xC2F;
        if (*(u8 *)address)
            gNestedCallbackIndex++;
        else
            gNestedCallbackIndex = 119;
    }
}

void sub_08011B5C(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    if (gUnknown_03000440[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0x7FFF, gUnknown_03000440[0x84] * 4, 0xFFFF);
        BlendObjPaletteBanksNow(0x7FFF, gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gNestedCallbackIndex++;
}

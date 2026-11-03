#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "equipment_helpers.h"

#include "input.h"
extern u8 gUnknown_030057E0[];

void sub_08010794(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    if (gUnknown_03000440[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        BlendObjPaletteBanksNow(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gUnknown_0300137C++;
}


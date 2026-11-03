#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "equipment_helpers.h"

#include "input.h"
extern u8 gUnknown_030057E0[];

void sub_080107F0(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    sub_0803FAA0(1, 0, 0);
    gNestedCallbackIndex++;
}

void sub_08010814(void)
{
    StepFirstBgAutoScroll();
    if (RunDialogue(gState0MapMessages_083C2D3C[gState0TransferWork.bytes[0]]))
    {
        sub_08012098();
        gUnknown_03000440[0x84] = 8;
        gUnknown_03000440[0x85] = 8;
        gNestedCallbackIndex++;
    }
    sub_08012098();
}

void sub_08010860(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    if ((*(u8 *)&gNewKeys & 8) && sub_08042278(50) && !gUnknown_030057E0[0xC2D])
    {
        PlaySoundEffect(4);
        gNestedCallbackIndex++;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        PlaySoundEffect(4);
        gNestedCallbackIndex = 32;
    }
}

void sub_080108D0(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    if (RunDialogueClose())
    {
        sub_0803FAA0(1, 2, 0);
        gNestedCallbackIndex++;
    }
}

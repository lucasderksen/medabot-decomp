#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
extern u32 sub_0803E79C(void);
extern const void *const gUnknownPointers_083CF530[];

void sub_08014A44(void)
{
    InitDialogue(1, 0, 0);
    gNestedCallbackIndex++;
}

void sub_08014A60(void)
{
    if (RunDialogue(gUnknownPointers_083CF530[1]))
        gNestedCallbackIndex++;
}

void sub_08014A84(void)
{
    if (sub_0803E79C())
    {
        gMainSerialOutgoingWork.word06 = 0;
        gState0TypedWork.widths.word86 = 0;
        gNestedCallbackIndex++;
    }
}

void sub_08014AB4(void)
{
    if (gState0TypedWork.widths.word86 == 16)
        gNestedCallbackIndex++;
    else
        gState0TypedWork.widths.word86++;
}

void sub_08014ADC(void)
{
    gState0TransferWork.bytes[0x51] = 0;
    gState0TransferWork.bytes[0x52] = 0;
    gState0TransferWork.bytes[0x53] = 0;
    gState0TransferWork.bytes[0x54] = 0;
    gState0TransferWork.widths.words1A6[0] = 0;
    gState0TransferWork.bytes[0x1AF] = 0;
    gState0TransferWork.bytes[0x1B0] = 1;
    gState0TypedWork.widths.word86 = 0;
    gNestedCallbackIndex++;
}

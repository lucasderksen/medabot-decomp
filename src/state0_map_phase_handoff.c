#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
extern u32 sub_0803E79C(void);
extern const void *const gUnknownPointers_083CF530[];

void sub_08014A44(void)
{
    sub_0803FAA0(1, 0, 0);
    gUnknown_0300137C++;
}

void sub_08014A60(void)
{
    if (sub_0803FB3C(gUnknownPointers_083CF530[1]))
        gUnknown_0300137C++;
}

void sub_08014A84(void)
{
    if (sub_0803E79C())
    {
        gMainSerialOutgoingWork.word06 = 0;
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C++;
    }
}

void sub_08014AB4(void)
{
    if (gState0TypedWork.widths.word86 == 16)
        gUnknown_0300137C++;
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
    gUnknown_0300137C++;
}

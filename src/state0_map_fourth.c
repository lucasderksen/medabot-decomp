#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "equipment_helpers.h"

extern u8 gUnknown_030057E0[];

void sub_08010C50(void)
{
    u32 low;
    sub_08012098();
    sub_08043CD4();
    low = gUnknown_030057E0[0xC2E] & 15;
    if (low)
    {
        gUnknown_030057E0[0xC2E] = 0;
        gUnknown_0300137C = 62;
    }
    else
    {
        sub_080121CC();
        if (sub_08042114(gState0TransferWork.bytes[0x169], gState0TransferWork.bytes[0x168]))
            gState0TransferWork.bytes[0x16A] = low;
        else
            gState0TransferWork.bytes[0x16A] = 1;
        sub_0804213C(gState0TransferWork.bytes[0x169], gState0TransferWork.bytes[0x168], 1);
        gUnknown_0300137C++;
    }
}

void sub_08010CE8(void)
{
    const void *const *messages;
    const void *source;
    u8 *work;
    u8 *selected;
    u8 *buffer;
    sub_08012098();
    sub_08043CD4();
    sub_080124B8();
    messages = gState0PartMessages_083C6F68;
    work = gState0TransferWork.bytes;
    selected = &work[0x168];
    source = messages[*selected];
    buffer = gDebugMenuTextBuffer;
    sub_0803F63C(source, buffer, 14);
    sub_0803F63C(gPartTextPointers_083BBB4C[work[0x169] * 4 + *selected], buffer + 20, 15);
    gUnknown_0300137C++;
}

void sub_08010D58(void)
{
    sub_08012098();
    sub_08043CD4();
    sub_080123A0();
    if (sub_0803FB3C(gState0FixedMessages_083C6744[107]))
    {
        if (gState0TransferWork.bytes[0x16A])
            gUnknown_0300137C++;
        else
            gUnknown_0300137C = 60;
    }
}

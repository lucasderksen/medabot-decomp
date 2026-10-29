#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
extern u8 gUnknown_03000B90;
extern u32 sub_0803E79C(void);

void sub_08014CF0(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = work + 0x87;
    if (*selected <= 2)
    {
        struct MainSerialOutgoingWork *outgoing = &gMainSerialOutgoingWork;
        u8 *base = gSetupBuffer_03000590;
        u32 offset = *selected * 256;
        u8 *record = base + offset;
        u8 *sent;
        outgoing->word06 = record[0xDD] + 0x8000;
        sent = work + 0x1AF;
        if (*sent)
            gUnknown_0300137C++;
        else
            *sent = 1;
    }
    else
    {
        u16 value = gMainSerialOutgoingWork.words[gUnknown_03000B90 ^ 1][1];
        if (value & 0x8000)
        {
            u8 *base = gSetupBuffer_03000590;
            u32 offset = *selected * 256;
            u8 *record = base + offset;
            record[0xDD] = value;
            gUnknown_0300137C++;
        }
    }
}

void sub_08014D84(void)
{
    gUnknown_0300137C++;
}

void sub_08014D94(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = work + 0x87;
    if (*selected > 2)
    {
        u8 *base = gSetupBuffer_03000590;
        u32 offset = *selected * 256;
        u8 *record = base + offset;
        sub_08015564(*selected, record[0xDD]);
    }
    gUnknown_0300137C++;
}

void sub_08014DC8(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = work + 0x87;
    if (*selected > 2)
    {
        u8 *base = gSetupBuffer_03000590;
        u32 index = *selected;
        u32 offset = index * 256;
        u8 *record = base + offset;
        if (record[0xDD] > 3)
            sub_08015668(index, record[0xDD] - 4);
    }
    gUnknown_0300137C++;
}

void sub_08014E08(void)
{
    gMainSerialOutgoingWork.word06 = 0;
    gUnknown_0300137C = 69;
}

void sub_08014E20(void)
{
    gState0TypedWork.widths.word86++;
    if (sub_0803E79C())
    {
        gMainSerialOutgoingWork.word06 = 0;
        gUnknown_0300137C++;
    }
}

void sub_08014E54(void)
{
    if (gState0TypedWork.widths.word86)
        gState0TypedWork.widths.word86--;
    else
        gUnknown_0300137C++;
}

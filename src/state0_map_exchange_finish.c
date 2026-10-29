#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "object_helpers.h"
struct ExchangeRecord { u8 unknown00[0xDD]; u8 byteDD; u8 unknownDE[0x22]; };


void sub_08014C30(void)
{
    u8 *records;
    gMainSerialOutgoingWork.word06 = 0;
    records = gSetupBuffer_03000590;
    sub_08015564(3, records[0x3DD]);
    sub_08015564(4, records[0x4DD]);
    sub_08015564(5, records[0x5DD]);
    gUnknown_0300137C++;
}

void sub_08014C84(void)
{
    u32 index = 0;
    struct ExchangeRecord *records = (void *)gSetupBuffer_03000590;
    do
    {
        u32 selected = index + 3;
        if (records[index + 3].byteDD > 3)
            sub_08015668(selected, records[index + 3].byteDD - 4);
        index++;
    } while (index <= 2);
    gUnknown_0300137C++;
}

void sub_08014CC8(void)
{
    if (sub_08041CA4())
        gUnknown_0300137C++;
}

void sub_08014CE4(void)
{
    gUnknown_0300137C = 64;
}

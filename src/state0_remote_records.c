#include "state0_next_helpers.h"
#include "state0_work.h"
#include "object_helpers.h"


void sub_080150C0(void)
{
    u32 index = 0;
    u8 *work = gState0TransferWork.bytes;
    if (index < work[0x5B])
    {
        u8 *count = work + 0x5B;
        do
        {
            sub_080150FC((u8)index);
            index++;
        } while (index < *count);
    }
    sub_0801520C();
    sub_08014F90(3, gState0TransferWork.bytes[0x5B]);
}

void sub_0801520C(void)
{
    u32 index = 0;
    u8 *work = gState0TransferWork.bytes;
    if (index < work[0x5B])
    {
        u8 *scratch = gUnknown_0300052E;
        u8 *count = work + 0x5B;
        u8 *record = work + 4;
        u8 *base = gSetupBuffer_03000590;
        u8 *destination = base + 0x340;
        u8 *source = base + 0x300;
        do
        {
            *destination = 3;
            sub_08042B58(record[0], 0, scratch);
            destination[1] = scratch[3];
            destination[2] = source[1];
            destination[3] = record[0];
            destination[4] = record[1];
            destination[5] = record[2];
            destination[6] = record[3];
            record += 12;
            destination += 256;
            source += 256;
            index++;
        } while (index < *count);
    }
}


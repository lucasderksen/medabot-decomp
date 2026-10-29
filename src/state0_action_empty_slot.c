#include "state0_work.h"

void sub_08035234(u32 row)
{
    u8 *records = gSetupBuffer_03000590;
    if (records[row * 256 + 0x59] == 0)
    {
        u32 index = 0;
        u32 baseWord = (u32)&gState0TransferWork.bytes[0xE0];
        u32 quantity = row + 1;
        do
        {
            u8 *slot = (u8 *)(index + baseWord);
            if (*slot == 0)
            {
                *slot = quantity;
                break;
            }
            index++;
        } while (index <= 2);
    }
}

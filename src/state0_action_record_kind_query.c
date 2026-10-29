#include "state0_next_helpers.h"
#include "state0_work.h"

/* Observed full-word index and three byte fields; original layout unknown. */
u32 sub_08034F44(u32 row)
{
    u32 count = 0;
    u32 result;
    u32 baseWord = (u32)gSetupBuffer_03000590;
    u8 *record;
    row *= 256;
    baseWord += 0x49;
    record = (u8 *)(row + baseWord);
    do
    {
        if (*record == 21)
        {
            result = 1;
            goto done;
        }
        record += 24;
        count++;
    } while (count <= 2);
    result = 0;
done:
    return result;
}

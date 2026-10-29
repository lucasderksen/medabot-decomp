#include "global.h"
#include "state0_work.h"

/* Only observed physical fields; original setup allocation is unknown. */
struct ObservedAmountDistributionRecord
{
    u8 unknown00[0x95];
    u8 amounts95[5];
    u8 unknown9A[7];
    u8 flagA1;
    u8 halvesA2[5];
};

void sub_08035194(u32 row)
{
    u32 baseWord = (u32)gSetupBuffer_03000590;
    struct ObservedAmountDistributionRecord *record;
    row *= 256;
    record = (struct ObservedAmountDistributionRecord *)(row + baseWord);
    if (record->flagA1 == 0)
    {
        u32 value = record->amounts95[0] >> 1;
        u8 *destination = &record->halvesA2[0];
        *destination = value;
        value = record->amounts95[1] >> 1;
        destination++;
        *destination = value;
        value = record->amounts95[2] >> 1;
        destination++;
        *destination = value;
        value = record->amounts95[3] >> 1;
        destination++;
        *destination = value;
        value = record->amounts95[4] >> 1;
        destination++;
        *destination = value;
    }
}

#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"


void sub_0801528C(void)
{
    if (gUnknown_03000440[0x89] != 1 || gUnknown_03000B90 == 0)
    {
        u32 selected = 0;
        u32 base = (u32)gSetupBuffer_03000590;
        u8 *record = (u8 *)(base + 0x40);
        do
        {
            if (*record)
                sub_08031A3C(selected);
            record += 256;
            selected++;
        } while (selected <= 5);
    }
    else
    {
        {
            u32 selected = 3;
            u32 base = (u32)gSetupBuffer_03000590;
            u8 *record = (u8 *)(base + 0x340);
            do
            {
                if (*record)
                    sub_08031A3C(selected);
                record += 256;
                selected++;
            } while (selected <= 5);
        }
        {
            u32 selected = 0;
            u32 base = (u32)gSetupBuffer_03000590;
            u8 *record = (u8 *)(base + 0x40);
            do
            {
                if (*record)
                    sub_08031A3C(selected);
                record += 256;
                selected++;
            } while (selected <= 2);
        }
    }
}

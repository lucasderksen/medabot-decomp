#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "input.h"


void sub_08014548(void)
{
    u32 selected;
    sub_080195C0();
    sub_0801BBC4();
    for (selected = 0; selected <= 5; selected++)
    {
        u8 *record = gSetupBuffer_03000590;
        u8 *ready;
        record += selected * 256;
        if (!record[0x40])
            continue;
        ready = record + 0xBF;
        if (*ready)
        {
            u8 *flags = record + 0xBB;
            u32 zero = 0;
            u32 first;
            u32 second;
            *flags = 8;
            sub_08019348(selected);
            sub_08019544(selected);
            first = sub_08019FBC(selected, 1);
            second = sub_0801A030(selected, 1);
            if (first || second)
            {
                *ready = zero;
                gUnknown_0300137C = 69;
                break;
            }
        }
    }
}

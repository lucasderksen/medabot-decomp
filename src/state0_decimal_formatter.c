#include "state0_next_helpers.h"

void sub_0801A28C(u8 *destination, u32 value, u32 kind)
{
    u8 digits[3];
    /* Only this local stack word is qualified: the reference reloads SP+4
     * after each store and each unsigned division. This reproduces those
     * observed accesses, without claiming the original source qualifier. */
    volatile u32 remainder;
    u8 length;
    u8 seen;
    u8 index;

    if (kind != 0)
    {
        if (kind == 1)
        {
            destination[0] = 11;
            length = 1;
        }
        else
            length = 0;
    }
    else
    {
        destination[0] = 10;
        length = 1;
    }

    digits[0] = value / 100;
    remainder = value - (value / 100) * 100;
    digits[1] = remainder / 10;
    remainder -= (remainder / 10) * 10;
    digits[2] = remainder;

    seen = 0;
    index = 0;
    do
    {
        if (index <= 1)
        {
            if (digits[index] == 0)
            {
                if (seen != 0)
                {
                    destination[length] = digits[index];
                    length++;
                }
            }
            else
            {
                destination[length] = digits[index];
                seen = 1;
                length++;
            }
        }
        else
        {
            destination[length] = digits[index];
            length++;
        }
        index++;
    } while (index <= 2);

    destination[length] = 0xFE;
    destination[6] = length;
}

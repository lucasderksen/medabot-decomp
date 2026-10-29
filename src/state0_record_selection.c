#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"


void sub_0801531C(u32 value)
{
    u32 index = 0;
    u8 *base = gSetupBuffer_03000590;
    u32 offset = value * 256;
    u8 *record;
    base += 0x40;
    record = (u8 *)(offset + (u32)base);
    do
    {
        u32 selected = value + index;
        if (*record != 0 && sub_08015390(selected) != 0)
            sub_08015464(selected);
        record += 256;
        index++;
    } while (index <= 2);
}

void sub_08015358(u32 value)
{
    u8 *base = gSetupBuffer_03000590;
    u8 *record = base + value * 256;
    u8 *tag = record;
    tag += 0xC9;
    if (*tag == 44)
        sub_08015464(value);
    else if (sub_08015390(value) != 0)
        sub_08015464(value);
}

void sub_08015414(u32 first)
{
    u8 *base = gSetupBuffer_03000590;
    u8 *record = base + first * 256;
    u8 *cursor = record;
    u32 next;
    cursor += 0x3F;
    next = *cursor + 1;
    *cursor = next;
    if ((u8)next == 8)
        *cursor = record[9];
}

void sub_08015464(u32 first)
{
    u8 *base = gSetupBuffer_03000590;
    u8 *condition = base + first * 256;
    condition += 0xC1;
    if (*condition == 80 && (sub_080424B8() & 1) != 0)
    {
        if (sub_080155A8(first, 0, 1) == 0)
            return;
    }
    sub_080156D0();
    {
        u32 index = 0;
        u32 work = (u32)gState0TransferWork.bytes;
        u8 *priority = (u8 *)(work + 0x64);
        do
        {
            if (*priority == 255)
            {
                sub_08015564(first, 0);
                return;
            }
            if (sub_080156F8(first, *priority) == 0)
            {
                sub_08015564(first, *priority);
                return;
            }
            priority++;
            index++;
        } while (index <= 3);
    }
    sub_08015564(first, 0);
}

u32 sub_080154E0(u32 first, u32 second)
{
    u8 *base = gSetupBuffer_03000590;
    u8 *record = base + first * 256;
    u8 *tag = record;
    tag += 0xC9;
    if (*tag == 43)
    {
        u8 *value = record;
        value += 0xCA;
        if (*value == second)
            return 1;
    }
    return 0;
}

u32 sub_08015508(u32 first, u32 second)
{
    if (second == 1)
    {
        u8 *base = gSetupBuffer_03000590;
        u8 *value = base + first * 256;
        value += 0x58;
        if (*value == 0)
            return 1;
    }
    return 0;
}

u32 sub_08015528(u32 first, u32 second)
{
    u8 *base = gSetupBuffer_03000590;
    u32 pair = second - 1;
    u32 offset = pair * 24 + first * 256;
    u8 *value = base + offset;
    value += 0x59;
    if (*value == 0)
        return 1;
    return 0;
}

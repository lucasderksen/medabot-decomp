#include "gba.h"
#include "main_callbacks.h"

void sub_0805BCB0(u32 first, u32 second)
{
    u32 selected = (u8)first;
    u32 maximum = (u8)second;
    s32 row = 0;
    u32 lowMask = 0xFFF;
    u32 defaultBank = 0x6000;
    do
    {
        s32 x = 6;
        s32 y = row * 3 + 10;
        s32 step = 0;
        do
        {
            u16 offset = *(volatile u16 *)0x04000008;
            u32 screenOffset;
            u32 address;
            u16 *tile;
            u32 value;
            offset >>= 8;
            offset &= 31;
            screenOffset = offset * 2048;
            address = x * 2 + 0x06000000;
            screenOffset += address;
            screenOffset += y * 64;
            tile = (void *)screenOffset;
            value = *tile & lowMask;
            if (selected == row && step < (s32)maximum)
                value |= 0x7000;
            else
                value |= defaultBank;
            *tile = value;
            if (step <= 1)
                y++;
            else
                x++;
            step++;
        } while (step <= 19);
        row++;
    } while (row <= 2);
}


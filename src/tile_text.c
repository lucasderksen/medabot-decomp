#include "tile_text.h"
#include "display_helpers.h"

extern const u8 gUnknownBytes_083B83FC[];
extern const s16 gUnknownSines_083D6A2C[];
extern const s16 gUnknownSines_083D6C2C[];

void sub_08042678(void *destination, u32 inputLength)
{
    u8 *out = destination;
    u8 length = inputLength;
    u32 i;
    for (i = 0; i < length; i++)
        *out++ = 0x43;
    *out = 0xFE;
}

void sub_08042698(u32 width, u32 height, u32 x, u32 y, u32 control, u32 inputEntry)
{
    u16 entry = inputEntry;
    u32 screenOffset = ((control >> 8) & 31) << 11;
    u32 xAddress = x * 2 + 0x06000000;
    u16 *destination = (u16 *)(screenOffset + xAddress + y * 64);
    u32 row;
    u32 column;
    for (row = 0; row < height; row++)
    {
        u16 *out = destination + row * 32;
        for (column = 0; column < width; column++)
            *out++ = entry++;
    }
}

void sub_080426F0(u32 inputValue, u32 inputX, u32 inputY, u32 control, u32 inputEntry)
{
    u8 value = inputValue;
    u8 x = inputX;
    u8 y = inputY;
    u16 entry = inputEntry;
    u8 digits[3];
    u8 remainder;
    if (value == 255)
    {
        sub_08042698(1, 2, x, y, control, (u16)(entry + 24));
        sub_08042698(1, 2, x + 1, y, control, (u16)(entry + 24));
    }
    else
    {
        digits[0] = value / 100;
        remainder = value - (u8)(value / 100) * 100;
        digits[1] = remainder / 10;
        digits[2] = remainder - (u8)(remainder / 10) * 10;
        if (digits[0] != 0)
        {
            sub_08042698(1, 2, x, y, control, (u16)(entry + 20));
            sub_08042698(1, 2, x + 1, y, control, (u16)(entry + 22));
        }
        else if (digits[1] != 0)
        {
            sub_08042698(1, 2, x, y, control, (u16)(entry + digits[1] * 2));
            sub_08042698(1, 2, x + 1, y, control, (u16)(entry + digits[2] * 2));
        }
        else
        {
            sub_0803EF8C(1, 2, x, y, control, 0);
            sub_08042698(1, 2, x + 1, y, control, (u16)(entry + digits[2] * 2));
        }
    }
}

void sub_08042838(u32 value, u32 x, u32 y, u32 inputColumns, u32 control, u32 inputEntry)
{
    u8 columns = inputColumns;
    u16 entry = inputEntry;
    u8 digits[6];
    u32 remainder;
    u8 start;
    u32 found;
    u32 screenOffset, xAddress;
    u16 *destination;
    u32 i;
    digits[0] = value / 100000;
    remainder = value - value / 100000 * 100000;
    digits[1] = remainder / 10000;
    remainder -= value / 10000 * 10000;
    digits[2] = remainder / 1000;
    remainder -= remainder / 1000 * 1000;
    digits[3] = remainder / 100;
    remainder -= remainder / 100 * 100;
    digits[4] = remainder / 10;
    remainder -= remainder / 10 * 10;
    digits[5] = remainder;
    start = 6 - columns;
    found = 0;
    screenOffset = ((control >> 8) & 31) << 11;
    xAddress = x * 2 + 0x06000000;
    destination = (u16 *)(screenOffset + xAddress + y * 64);
    for (i = start; i < 6; i++)
    {
        if (i < 5)
        {
            if (digits[i] == 0)
            {
                if (found != 0)
                    *destination++ = entry + digits[i];
                else
                    *destination++ = 0;
            }
            else
            {
                *destination++ = entry + digits[i];
                found = 1;
            }
        }
        else
            *destination++ = entry + digits[i];
    }
}

void sub_08042950(u32 value, u32 x, u32 y, u32 inputColumns, u32 control, u32 inputEntry)
{
    u8 columns = inputColumns;
    u16 entry = inputEntry;
    u8 digits[6];
    u32 remainder;
    u8 start;
    u32 found;
    u32 screenOffset, xAddress;
    volatile u16 *destination;
    s16 lowerEntry;
    u32 i;
    digits[0] = value / 100000;
    remainder = value - value / 100000 * 100000;
    digits[1] = remainder / 10000;
    remainder -= value / 10000 * 10000;
    digits[2] = remainder / 1000;
    remainder -= remainder / 1000 * 1000;
    digits[3] = remainder / 100;
    remainder -= remainder / 100 * 100;
    digits[4] = remainder / 10;
    remainder -= remainder / 10 * 10;
    digits[5] = remainder;
    start = 6 - columns;
    found = 0;
    screenOffset = ((control >> 8) & 31) << 11;
    xAddress = x * 2 + 0x06000000;
    destination = (u16 *)(screenOffset + xAddress + y * 64);
    for (i = start; i < 6; i++)
    {
        lowerEntry = entry;
        if (i < 5)
        {
            if (digits[i] == 0)
            {
                if (found != 0)
                {
                    *destination = entry + digits[i] * 2;
                    destination[32] = lowerEntry + (digits[i] * 2 + 1);
                    *destination++;
                }
                else
                {
                    *destination = 0;
                    destination[32] = 0;
                    *destination++;
                }
            }
            else
            {
                *destination = entry + digits[i] * 2;
                destination[32] = lowerEntry + (digits[i] * 2 + 1);
                *destination++;
                found = 1;
            }
        }
        else
        {
            *destination = entry + digits[i] * 2;
            destination[32] = lowerEntry + (digits[i] * 2 + 1);
                *destination++;
        }

    }
}

void sub_08042A90(u32 first, u32 second, u32 x, u32 y, u32 separator, u32 control, u32 inputEntry)
{
    u16 entry = inputEntry;
    u8 firstDigits[2];
    u8 secondDigits[2];
    u32 screenOffset, xAddress;
    u16 *destination;
    u32 i;
    u32 remainder;
    firstDigits[0] = first / 10;
    remainder = first - first / 10 * 10;
    firstDigits[1] = remainder;
    secondDigits[0] = second / 10;
    remainder = second - second / 10 * 10;
    secondDigits[1] = remainder;
    screenOffset = ((control >> 8) & 31) << 11;
    xAddress = x * 2 + 0x06000000;
    destination = (u16 *)(screenOffset + xAddress + y * 64);
    for (i = 0; i < 2; i++)
    {
        if (firstDigits[i] == 0)
        {
            if (i == 1)
                *destination++ = entry + firstDigits[i];
        }
        else
            *destination++ = entry + firstDigits[i];
    }
    *destination++ = separator;
    for (i = 0; i < 2; i++)
    {
        if (secondDigits[i] == 0)
        {
            if (i == 1)
                *destination++ = entry + secondDigits[i];
        }
        else
            *destination++ = entry + secondDigits[i];
    }
}

void sub_08042B58(u32 record, u32 slot, void *destination)
{
    u8 *out = destination;
    u32 i = 0;
    u32 sourceAddress = (u32)gUnknownBytes_083B83FC;
    const u8 *source;
    sourceAddress += record * 64 + slot * 16;
    source = (const u8 *)sourceAddress;
    for (; i < 16; i++)
    {
        *out = *source;
        out++;
        source++;
    }
}

struct TileCoordinates sub_08042BC0(u32 angle, u32 radius, u32 x, u32 y)
{
    struct TileCoordinates result;
    x += (u32)((float)gUnknownSines_083D6C2C[angle] * ((float)radius * (1.0f / 256.0f)));
    y += (u32)((float)gUnknownSines_083D6A2C[angle] * ((float)radius * (1.0f / 256.0f)));
    result.x = x & 0x1FF;
    result.y = y & 0xFF;
    return result;
}

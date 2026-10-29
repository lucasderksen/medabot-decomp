#include "frame_objects.h"

extern void sub_08074DE0(u32 value);

void sub_08040B90(const u8 *commands, u8 index)
{
    u8 offset;
    const u8 *command;
    gFrameObjects[index].commandDelay = 0;
    gFrameObjects[index].commandOffset = 0;
    gFrameObjects[index].commandStopped = 0;
    offset = 0;
    for (; ; offset += 3)
    {
        command = commands + offset;
        if (*command <= 0xFA)
            goto found;
    }
found:
    gFrameObjects[index].frameAndGroup = command[1] * 256 + command[2];
}


void sub_08040BD8(const u8 *commands, u8 index)
{
    u32 repeat;
    if (gFrameObjects[index].commandStopped == 0xFF)
        return;
    repeat = 1;
    do
    {
        u32 opcode;
        if (gFrameObjects[index].commandDelay != 0)
        {
            gFrameObjects[index].commandDelay--;
            return;
        }
        opcode = commands[gFrameObjects[index].commandOffset];
        switch (opcode)
        {
        case 0xFB:
            /* The original command affects record zero, even for another index. */
            gFrameObjects[0].flags &= 0xBFFF;
            gFrameObjects[index].commandDelay = commands[gFrameObjects[index].commandOffset + 1];
            gFrameObjects[index].commandOffset += 3;
            return;
        case 0xFC:
            gFrameObjects[0].flags |= 0x4000;
            gFrameObjects[index].commandOffset += 3;
            break;
        case 0xFD:
            sub_08074DE0(commands[gFrameObjects[index].commandOffset + 1]);
            gFrameObjects[index].commandOffset += 3;
            break;
        case 0xFE:
            gFrameObjects[index].commandOffset = commands[gFrameObjects[index].commandOffset + 1] * 3;
            break;
        case 0xFF:
            gFrameObjects[index].commandStopped = 0xFF;
            return;
        default:
            gFrameObjects[index].commandDelay = opcode;
            gFrameObjects[index].frameAndGroup = commands[gFrameObjects[index].commandOffset + 1] * 256 + commands[gFrameObjects[index].commandOffset + 2];
            gFrameObjects[index].commandOffset += 3;
            break;
        }
    } while (repeat);
}

void sub_08040CD0(u8 start, u8 count)
{
    u32 i;
    u32 zero;
    for (i = 0; i < count; i++)
    {
        zero = 0;
        CpuFastSet(&zero, &gFrameObjects[start + i], CPU_SET_FILL | 16);
    }
}

void sub_08040D0C(u8 start, u8 count)
{
    u32 i;
    for (i = 0; i < count; i++)
        gFrameObjects[start + i].flags &= 0x7FFF;
}

void sub_08040D44(u8 start, u8 count)
{
    u32 i;
    for (i = 0; i < count; i++)
        gFrameObjects[start + i].flags |= 0x8000;
}

u32 sub_08040D78(u8 start, u8 count)
{
    u8 i;
    for (i = 0; i < count; i++)
    {
        if (start + i == 128)
            goto finish;
        if (gFrameObjects[start + i].flags == 0)
            return start + i;
    }
finish:
    return start;
}

void sub_08041370(u8 *output, u32 value)
{
    u8 digits[6];
    volatile u32 remainder;
    u32 started;
    u8 outputIndex;
    u8 digitIndex;
    digits[0] = value / 100000;
    remainder = value - (value / 100000) * 100000;
    digits[1] = remainder / 10000;
    /* The original subtracts a quotient of the input here, not the remainder. */
    remainder -= (value / 10000) * 10000;
    digits[2] = remainder / 1000;
    remainder -= (remainder / 1000) * 1000;
    digits[3] = remainder / 100;
    remainder -= (remainder / 100) * 100;
    digits[4] = remainder / 10;
    remainder -= (remainder / 10) * 10;
    digits[5] = remainder;
    if (digits[0] != 0)
    {
        output[0] = 5;
        output[1] = 18;
        output[2] = 18;
        output[3] = 15;
        output[4] = 18;
        output[5] = 0xFE;
    }
    else
    {
        started = 0;
        outputIndex = 0;
        for (digitIndex = 0; digitIndex <= 5; digitIndex++)
        {
            if (digitIndex <= 4)
            {
                if (digits[digitIndex] == 0)
                {
                    if (started)
                    {
                        output[outputIndex] = digits[digitIndex] + 0x35;
                        outputIndex++;
                    }
                }
                else
                {
                    output[outputIndex] = digits[digitIndex] + 0x35;
                    started = 1;
                    outputIndex++;
                }
            }
            else
            {
                output[outputIndex] = digits[digitIndex] + 0x35;
                outputIndex++;
            }
        }
        output[outputIndex] = 0xFE;
    }
}

void sub_08041490(u8 *output, u32 value, u32 base)
{
    u8 digits[6];
    volatile u32 remainder;
    u32 started;
    u8 outputIndex;
    u8 digitIndex;
    digits[0] = value / 100000;
    remainder = value - (value / 100000) * 100000;
    digits[1] = remainder / 10000;
    /* The original subtracts a quotient of the input here, not the remainder. */
    remainder -= (value / 10000) * 10000;
    digits[2] = remainder / 1000;
    remainder -= (remainder / 1000) * 1000;
    digits[3] = remainder / 100;
    remainder -= (remainder / 100) * 100;
    digits[4] = remainder / 10;
    remainder -= (remainder / 10) * 10;
    digits[5] = remainder;
    if (digits[0] != 0)
    {
        output[0] = 5;
        output[1] = 18;
        output[2] = 18;
        output[3] = 15;
        output[4] = 18;
        output[5] = 0xFE;
    }
    else
    {
        started = 0;
        outputIndex = 0;
        for (digitIndex = 0; digitIndex <= 5; digitIndex++)
        {
            if (digitIndex <= 4)
            {
                if (digits[digitIndex] == 0)
                {
                    if (started)
                    {
                        output[outputIndex] = digits[digitIndex] + base;
                        outputIndex++;
                    }
                }
                else
                {
                    output[outputIndex] = digits[digitIndex] + base;
                    started = 1;
                    outputIndex++;
                }
            }
            else
            {
                output[outputIndex] = digits[digitIndex] + base;
                outputIndex++;
            }
        }
        output[outputIndex] = 0xFE;
    }
}


#include "frame_objects.h"

extern const u8 gFrameByteMetrics[][2];

void sub_08040EE4(const u8 *bytes, u8 start, s32 x, s32 y, u8 boxWidth, u8 palette, u8 alignment, u16 flags, s32 xOffset, s32 yOffset)
{
    u8 totalWidth;
    u8 targetWidth;
    const u8 *cursor;
    const u8 *layoutCursor;
    struct FrameObject *object;
    x = x * 8 + xOffset;
    y = y * 8 + yOffset;
    totalWidth = 0;
    if (*bytes != 0xFE)
    {
        const u8 (*metrics)[2] = gFrameByteMetrics;
        cursor = bytes;
        do
        {
            totalWidth += metrics[*cursor][0];
            cursor++;
        } while (*cursor != 0xFE);
    }
    targetWidth = boxWidth * 8;
    if (totalWidth <= targetWidth)
    {
        switch (alignment)
        {
        case 0:
            totalWidth = (targetWidth - totalWidth) / 2;
            x += totalWidth;
            break;
        case 2:
            totalWidth = targetWidth - totalWidth;
            x += totalWidth;
            break;
        case 1:
            break;
        }
    }
    else
    {
        switch (alignment)
        {
        case 0:
            totalWidth = (totalWidth - targetWidth) / 2;
            x -= totalWidth;
            break;
        case 2:
            totalWidth = totalWidth - targetWidth;
            x -= totalWidth;
            break;
        case 1:
            break;
        }
    }
    if (*bytes != 0xFE)
    {
    u32 index = 0;
    struct FrameObject *base = gFrameObjects;
    do
    {
        object = &base[start + index];
        layoutCursor = bytes + index;
        if (*layoutCursor != 0)
        {
            object->flags = (flags << 10) | (s16)0xC004;
            object->screenX = x;
            object->screenY = y;
            object->palette = palette;
            object->tableSelector = 0;
            object->priority = ((3 & ~flags) << 6) + 63;
            object->frameAndGroup = *layoutCursor - 1;
        }
        x += gFrameByteMetrics[*layoutCursor][0];
        index++;
    } while (bytes[index] != 0xFE);
    }
}



#include "frame_objects.h"
extern const u8 gFrameByteMetrics[][2];
void sub_08040DB8(const u8 *bytes, u32 argument_start, s32 x, s32 y, u32 argument_boxWidth, u32 argument_palette, u32 argument_alignment, u32 argument_flags)
{
    u8 start = argument_start;
    u8 boxWidth = argument_boxWidth;
    u8 palette = argument_palette;
    u8 alignment = argument_alignment;
    u16 flags = argument_flags;
    u8 totalWidth;
    u8 targetWidth;
    const u8 *cursor;
    const u8 *layoutCursor;
    struct FrameObject *object;
    x *= 8;
    y *= 8;
    totalWidth = 0;
    if (*bytes != 0xFE)
    {
        const u8 (*metrics)[2] = gFrameByteMetrics;
        cursor = bytes;
        do
        {
            totalWidth += metrics[*cursor][0];
            cursor++;
        } while (*cursor != 0xFE);
    }
    targetWidth = boxWidth * 8;
    if (totalWidth <= targetWidth)
    {
        switch (alignment)
        {
        case 0:
            totalWidth = (targetWidth - totalWidth) / 2;
            x += totalWidth;
            break;
        case 2:
            totalWidth = targetWidth - totalWidth;
            x += totalWidth;
            break;
        case 1:
            break;
        }
    }
    else
    {
        switch (alignment)
        {
        case 0:
            totalWidth = (totalWidth - targetWidth) / 2;
            x -= totalWidth;
            break;
        case 2:
            totalWidth = totalWidth - targetWidth;
            x -= totalWidth;
            break;
        case 1:
            break;
        }
    }
    if (*bytes != 0xFE)
    {
    u32 index = 0;
    struct FrameObject *base = gFrameObjects;
    do
    {
        object = &base[start + index];
        layoutCursor = bytes + index;
        if (*layoutCursor != 0)
        {
            object->flags = (flags << 10) | (s16)0xC004;
            object->screenX = x;
            object->screenY = y;
            object->palette = palette;
            object->tableSelector = 0;
            object->priority = ((3 & ~flags) << 6) + 63;
            object->frameAndGroup = *layoutCursor - 1;
        }
        x += gFrameByteMetrics[*layoutCursor][0];
        index++;
    } while (bytes[index] != 0xFE);
    }
}


void sub_08041020(const u8 *bytes, u8 start, s32 x, s32 y, u8 boxWidth, u8 palette, u8 alignment, u16 flags)
{
    u8 totalWidth;
    u8 targetWidth;
    const u8 *cursor;
    const u8 *layoutCursor;
    struct FrameObject *object;
    x *= 8;
    y *= 8;
    totalWidth = 0;
    if (*bytes != 0xFE)
    {
        const u8 (*metrics)[2] = gFrameByteMetrics;
        cursor = bytes;
        do
        {
            totalWidth += metrics[*cursor][0];
            cursor++;
        } while (*cursor != 0xFE);
    }
    targetWidth = boxWidth * 8;
    if (totalWidth <= targetWidth)
    {
        switch (alignment)
        {
        case 0:
            totalWidth = (targetWidth - totalWidth) / 2;
            x += totalWidth;
            break;
        case 2:
            totalWidth = targetWidth - totalWidth;
            x += totalWidth;
            break;
        case 1:
            break;
        }
    }
    else
    {
        switch (alignment)
        {
        case 0:
            totalWidth = (totalWidth - targetWidth) / 2;
            x -= totalWidth;
            break;
        case 2:
            totalWidth = totalWidth - targetWidth;
            x -= totalWidth;
            break;
        case 1:
            break;
        }
    }
    if (*bytes != 0xFE)
    {
    u32 index = 0;
    struct FrameObject *base = gFrameObjects;
    do
    {
        object = &base[start + index];
        layoutCursor = bytes + index;
        if (*layoutCursor != 0)
        {
            object->flags = (flags << 10) | (s16)0xC004;
            object->screenX = x;
            object->screenY = y;
            object->palette = palette;
            object->tableSelector = 0;
            object->priority = ((3 & ~flags) << 6) + 63;
            object->frameAndGroup = *layoutCursor + 0x85FF;
        }
        x += gFrameByteMetrics[*layoutCursor][0];
        index++;
    } while (bytes[index] != 0xFE);
    }
}

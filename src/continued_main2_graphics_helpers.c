#include "compression.h"
#include "frame.h"
#include "main_callbacks.h"
#include "main_callbacks.h"

void sub_08059E50(void)
{
    /* Integer termination avoids forming an array[-1] pointer. */
    s32 index = 127;
    do
    {
        gFrameObjects[index].flags = 0;
        index--;
    } while ((s32)gFrameObjects + index * 64 >= (s32)gFrameObjects);
}

void sub_0805BA34(const void *source, u32 control)
{
    u8 *scratch = (void *)0x02030000;
    s32 width, height;
    s32 stride;
    s32 row, column;
    u32 layout;
    u16 *tiles;
    u16 *destination;
    LZ77UnCompWram(source, scratch);
    width = *(s32 *)scratch;
    height = *(s32 *)0x02030004;
    scratch += 16;
    tiles = (u16 *)scratch;
    destination = (u16 *)(0x06000000 + ((control >> 8) & 31) * 2048);
    layout = (control & 0xC000) >> 14;
    layout &= 1;
    stride = 32;
    if (layout != 0)
        stride = 64;
    for (row = 0; row < height; row++)
    {
        for (column = 0; column < stride; column++)
        {
            if (column < width)
                *destination = *tiles++;
            destination++;
        }
    }
}

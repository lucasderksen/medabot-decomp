#include "global.h"
#include "frame.h"
#include "input.h"
#include "background_state.h"

#include "object_numeric_helpers.h"
#include "later_graphics.h"

void sub_08048864(u32 input, u32 flagsInput, u32 frame, u32 palette, u32 selector)
{
    u8 index = input;
    u16 flags = flagsInput;
    struct FrameObject *objects = gFrameObjects;
    struct FrameObject *object = &objects[index];
    object->flags = flags;
    *(u16 *)&object->unknown2C[6] = flags;
    object->frameAndGroup = frame;
    object->palette = palette;
    object->tableSelector = selector;
}

void sub_08048888(u32 input)
{
    u8 index = input;
    sub_08049714(&gFrameObjects[index], 64);
    sub_08049344(index);
}

s32 sub_080488AC(s32 value)
{
    s32 count;
    if (value == 0)
        return 1;
    count = 0;
    while (count <= 9)
    {
        s32 divisor = 1;
        s32 index;
        for (index = 0; index < count; index++)
            divisor *= 10;
        if (value / divisor == 0)
            break;
        count++;
    }
    return count;
}

s32 sub_08048B88(s32 leftInput, s32 rightInput)
{
    s16 left = leftInput;
    s16 right = rightInput;
    return (s16)(left * 256 / right);
}

s32 sub_08048BA0(s32 input)
{
    s32 numerator = 65536;
    s16 value = input;
    return (s16)(numerator / value);
}


void sub_08048BB8(void)
{
    struct BackgroundState *work = &gBackgroundState_03005310;
    work->dx = 0;
    work->dy = 0;
    work->pa = 256;
    work->pb = 0;
    work->pc = 0;
    work->pd = 256;
    work->unknown30 = 0;
    work->scaleX = 256;
    work->scaleY = 256;
    work->angle = 0;
    work->x = 0;
    work->y = 0;
}

void sub_08048CA8(const u16 *source, u16 *destination, s32 rows, s32 columns,
                 s32 maximumRows, s32 stride, u32 addition)
{
    s32 row;
    if (rows > maximumRows)
        rows = maximumRows;
    for (row = 0; row < rows; row++)
    {
        s32 column;
        for (column = 0; column < columns; column++)
            *destination++ = *source++ + addition;
        destination += stride - columns;
    }
}

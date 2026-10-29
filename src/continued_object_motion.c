#include "global.h"
#include "frame.h"
#include "background_state.h"
#include "continued_commands.h"
#include "palette_transfer_helpers.h"

extern u8 gLaterBuffer_03006D20[];

union QueryCoordinate
{
    u32 value;
    struct { u32 fraction : 8; s32 integer : 24; } parts;
};
struct QueryMotionFrame
{
    u8 unknown00[11];
    u8 priority;
    union QueryCoordinate x, y;
    u8 unknown14[12];
    u8 direction;
    u8 unknown21[5];
    u8 state;
    u8 unknown27;
    u8 count;
    u8 unknown29[3];
    u8 offset;
    u8 unknown2D[7];
    u16 originY;
    u8 unknown36[10];
};
struct QueryMotionWork
{
    u8 unknown00[8];
    u16 originY;
    u8 index;
};

u32 sub_08050918(void)
{
    u32 result = 0;
    struct QueryMotionFrame *base = (struct QueryMotionFrame *)gFrameObjects;
    struct QueryMotionWork *work = (struct QueryMotionWork *)gLaterBuffer_03006D20;
    if (base[work->index].count <= 15)
    {
        base[work->index].y.parts.integer = work->originY - gScrollOscillationSines_083D6A2C[base[work->index].count * 8] / 16;
        base[work->index].offset = gScrollOscillationSines_083D6A2C[base[work->index].count * 8] / 16;
        base[work->index].count++;
        if (base[work->index].y.parts.integer / 4 <= (work->originY - 16) / 4)
            base[work->index].priority = 255;
        else
            sub_080487C8(work->index);
    }
    else
    {
        sub_080487C8(work->index);
        base[work->index].y.parts.integer = work->originY;
        base[work->index].offset = 0;
        result = 1;
    }
    return result;
}

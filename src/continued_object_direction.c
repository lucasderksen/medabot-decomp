#include "global.h"
#include "frame.h"
#include "background_state.h"
#include "continued_commands.h"
#include "palette_transfer_helpers.h"
#include "packed_fields.h"
#include "later_graphics.h"
#include "post_dispatch.h"

extern u8 gLaterBuffer_03006D20[];
extern u8 gUnknown_030057E0[];

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

u32 sub_080509EC(void)
{
    u32 result = 0;
    u8 index = gLaterBuffer_03006D20[10];
    struct QueryMotionFrame *base = (struct QueryMotionFrame *)gFrameObjects;
    struct QueryMotionFrame *object = &base[index];
    u8 *state = &object->state;
    switch (*state)
    {
    case 0:
        object->count = 0;
        object->unknown29[1] = 0;
        object->direction = gUnknown_030057E0[0xC95];
        sub_08049420(index, (u8)sub_08050300(index, gUnknown_030057E0[0xC95]));
        object->originY = object->y.parts.integer;
        sub_08047BA8(0x70);
        (*state)++;
        break;
    case 1:
        if (object->count < 2 * (16 / sub_08051940(index)))
        {
            switch (object->direction)
            {
            case 0:
                object->originY -= sub_08051940(index);
                break;
            case 1:
                object->originY += sub_08051940(index);
                break;
            case 2:
                object->x.parts.integer -= sub_08051940(index);
                break;
            case 3:
                object->x.parts.integer += sub_08051940(index);
                break;
            }
            {
                s32 amount = sub_08051940(index);
                const s16 *sines;
                u8 *count;
                u16 originY;
                struct QueryMotionFrame *base = (struct QueryMotionFrame *)gFrameObjects;
                struct QueryMotionFrame *object = &base[index];
                originY = object->originY;
                sines = gScrollOscillationSines_083D6A2C;
                count = &object->count;
                object->y.parts.integer = originY - sines[*count * (s32)((u32)amount << 2)] / 16;
                {
                    s32 secondAmount = sub_08051940(index);
                    object->offset = sines[*count * (s32)((u32)secondAmount << 2)] / 16;
                }
                (*count)++;
                if (object->priority != 255)
                {
                    if (object->y.parts.integer / 4 <= (object->originY - 16) / 4)
                        object->priority = 254;
                    else
                        sub_080487C8(index);
                }
            }
        }
        else
        {
            sub_080487C8(index);
            object->y.parts.integer = object->originY;
            object->offset = 0;
            result = 1;
        }
        break;
    }
    return result;
}

#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "post_dispatch.h"


/* Private access model. Direction/countdown fields are observed here only. */
union MovementCoordinate
{
    s32 value;
    struct { u32 fraction:8; s32 integer:24; } parts;
};

struct MovementFrameView
{
    u8 unknown00[0x0C];
    union MovementCoordinate x;
    union MovementCoordinate y;
    u8 unknown14[0x0C];
    u8 direction;
    u8 unknown21[6];
    u8 remaining;
    u8 countdown;
    u8 unknown29[7];
    u16 condition;
    u8 unknown32[14];
};

u32 sub_0805018C(u32 indexWord, u32 modeWord)
{
    u8 index = indexWord;
    u8 mode = modeWord;
    u32 result = 0;
    struct MovementFrameView *initialBase = (struct MovementFrameView *)gFrameObjects;
    struct MovementFrameView *object = &initialBase[index];
    if (object->countdown)
    {
        switch (object->direction)
        {
        case 0:
            {
                s32 amount = sub_08051940(index);
                object->y.parts.integer -= amount;
                break;
            }
        case 1:
            {
                s32 amount = sub_08051940(index);
                object->y.parts.integer += amount;
                break;
            }
        case 2:
            {
                s32 amount = sub_08051940(index);
                object->x.parts.integer -= amount;
                break;
            }
        case 3:
            {
                s32 amount = sub_08051940(index);
                object->x.parts.integer += amount;
                break;
            }
        }
        if (mode)
            sub_08050168(index);
        {
            struct MovementFrameView *base = (struct MovementFrameView *)gFrameObjects;
            struct MovementFrameView *next = &base[index];
            next->countdown--;
            if (next->countdown == 0)
            {
                switch (next->condition)
                {
                case 0x71:
                case 0x78:
                case 0x82:
                case 0x83:
                case 0x84:
                    sub_08047BA8(0x57);
                    break;
                }
                {
                    s32 divisor = sub_08051940(index);
                    struct MovementFrameView *reloadedBase = (struct MovementFrameView *)gFrameObjects;
                    struct MovementFrameView *reloaded = &reloadedBase[index];
                    reloaded->countdown = 16 / divisor;
                    reloaded->remaining--;
                    if (reloaded->remaining == 0)
                        result = 1;
                }
            }
        }
    }
    return result;
}

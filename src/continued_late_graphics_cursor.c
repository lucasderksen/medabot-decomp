#include "continued_late_graphics.h"
#include "frame.h"

/* Partial view of observed last-object offsets in the existing backing array.
 * This is an access model, not a recovered complete or original game type. */
struct ObservedPointerBacking {
    u8 unknown0000[0x1FC2];
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 scaleX;
    u8 scaleY;
    u8 palette;
    u8 priority;
    u8 unknown1FCC[0x10];
    u8 tableSelector;
};

void sub_08057FD4(void)
{
    u8 *work = gContinuedCommandWork_030064A0;
    u8 counter = work[0x67];
    s32 displacement = (u8)(counter & 4) >> 2;
    struct ObservedPointerBacking *objects;
    u32 zero;
    u32 negative = 8;
    negative &= counter;
    if (negative)
        displacement = -displacement;
    objects = (struct ObservedPointerBacking *)gFrameObjects;
    {
        u32 position = work[0x6C] * 8;
        u32 offset = displacement + 8;
        position += offset;
        zero = 0;
        objects->screenX = position;
    }
    {
        u32 position = work[0x6D] * 8 + 8;
        objects->screenY = position;
    }
    objects->frameAndGroup = 0x307;
    objects->palette = 14;
    objects->tableSelector = zero;
    objects->scaleX = 1;
    objects->scaleY = 1;
    objects->priority = 255;
}

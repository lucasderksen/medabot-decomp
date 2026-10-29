#include "frame_objects.h"
#include "utility_helpers.h"

struct ObservedMotionQueryObject
{
    u16 flags00;
    s16 currentX02;
    s16 currentY04;
    u8 unknown06[0x1F];
    u8 direction25;
    u8 unknown26[0xA];
    u16 targetX30;
    u16 targetY32;
    u8 unknown34[0xC];
};


u32 sub_080355F0(u32 index)
{
    struct ObservedMotionQueryObject *firstObjects = (void *)gFrameObjects;
    struct ObservedMotionQueryObject *objects;
    u32 result;
    {
        struct ObservedMotionQueryObject *object = &firstObjects[index];
        s32 currentX = object->currentX02;
        objects = firstObjects;
        if (currentX == object->targetX30 &&
            object->currentY04 == object->targetY32)
            result = 1;
        else
        {
            struct ObservedMotionQueryObject *moving = (void *)(index * 64 + (u32)objects);
            moving->direction25 = sub_080442B4(moving->currentX02,
                moving->currentY04, moving->targetX30, moving->targetY32);
            sub_0804422C(index);
            if (sub_08035658(index))
            {
                moving->currentX02 = moving->targetX30;
                moving->currentY04 = moving->targetY32;
                result = 1;
            }
            else
                result = 0;
        }
    }
    return result;
}

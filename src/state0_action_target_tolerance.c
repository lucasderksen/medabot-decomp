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

u32 sub_08035658(u32 index)
{
    struct ObservedMotionQueryObject *objects = (void *)gFrameObjects;
    struct ObservedMotionQueryObject *object = &objects[index];
    s32 currentX = object->currentX02;
    s32 currentY = object->currentY04;
    s32 targetX = object->targetX30;
    s32 targetY = object->targetY32;
    if (targetY - 2 <= currentY && targetY + 2 >= currentY &&
        targetX - 2 <= currentX && targetX + 2 >= currentX)
        return 1;
    return 0;
}

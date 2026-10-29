#include "frame_objects.h"

void sub_08035694(u32 index)
{
    struct FrameObject *objects = gFrameObjects;
    struct FrameObject *object = &objects[index];
    object->flags |= 0x200;
    object->scaleX = 64;
    object->scaleY = 64;
}

void sub_080356CC(u32 first, u32 second)
{
    struct FrameObject *objects = gFrameObjects;
    struct FrameObject *firstObject = &objects[first];
    struct FrameObject *secondObject;
    s32 firstY = firstObject->screenY;
    if ((u32)firstY > 159 ||
        firstY + 8 <= (secondObject = &objects[second])->screenY - 32)
    {
        sub_08040D0C(second, 1);
    }
    else
    {
        s32 adjustedY;
        sub_08040D44(second, 1);
        adjustedY = ((u8 *)secondObject)[4] - 8;
        secondObject->scaleX = 64 - (adjustedY - ((u8 *)firstObject)[4]) * 2;
        secondObject->scaleY = 64 - (adjustedY - ((u8 *)firstObject)[4]) * 2;
    }
}

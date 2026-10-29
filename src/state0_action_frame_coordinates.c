#include "frame_objects.h"

void sub_080350E0(u32 row)
{
    struct FrameObject *objects = gFrameObjects;
    u32 index = row * 4;
    struct FrameObject *source;
    {
        u32 destinationIndex = index;
        u32 sourceIndex = index;
        struct FrameObject *destination;
        destinationIndex += 0x5A;
        destination = &objects[destinationIndex];
        sourceIndex += 0x5D;
        source = &objects[sourceIndex];
        destination->screenX = (u16)source->screenX;
        destination->screenY = (u16)source->screenY - 8;
    }
    {
        u32 destinationIndex = index;
        struct FrameObject *destination;
        destinationIndex += 0x5B;
        destination = &objects[destinationIndex];
        destination->screenX = (u16)source->screenX - 8;
        destination->screenY = (u16)source->screenY;
    }
    {
        u32 destinationIndex = index;
        struct FrameObject *destination;
        destinationIndex += 0x5C;
        destination = &objects[destinationIndex];
        destination->screenX = (u16)source->screenX + 8;
        destination->screenY = (u16)source->screenY;
    }
}

#include "frame.h"
#include "state0_next_helpers.h"

/* Observed fields from object+4;64-byte access stride, not a new global type. */
struct ObservedFrameTail
{
    s16 y;
    u16 frame;
    u8 scaleX, scaleY, palette, priority;
    u8 unknown08[16];
    u8 tableSelector, affineIndex, unknown1A[2];
    u8 commandDelay, commandOffset;
    u8 unknown1E[34];
};

void sub_0801A228(u32 selected)
{
    u32 index = 0;
    struct FrameObject *objects = gFrameObjects;
    const u8 *steps = gFrameStepBytes_083AD533;
    u32 offset = (selected * 4 + 10) * 64;
    u32 tailOffset = offset;
    u32 delayOffset = offset;
    struct ObservedFrameTail *tail;
    u8 *delay;
    tailOffset += 4;
    tail = (void *)(tailOffset + (u32)objects);
    delayOffset += 32;
    delay = (void *)(delayOffset + (u32)objects);
    do
    {
        if (tail->commandOffset == 0xFF)
            return;
        if (tail->commandOffset <= 0x1F)
        {
            if (tail->commandDelay == 0)
            {
                tail->y += (s8)*(const u8 *)(tail->commandOffset + (u32)steps);
                tail->scaleY += 2;
                tail->commandOffset++;
            }
            else
                *delay = tail->commandDelay - 1;
        }
        tail++;
        delay += 64;
        index++;
    } while (index <= 2);
}

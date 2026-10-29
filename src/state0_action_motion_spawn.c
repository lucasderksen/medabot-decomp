#include "compression.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Observed physical object33 fields over the canonical backing, no extent claim. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x840];
    u16 flags840;
    u16 screenX842;
    u16 screenY844;
    u8 unknown846[4];
    u8 palette84A;
    u8 priority84B;
    u8 unknown84C[0x10];
    u8 table85C;
    u8 unknown85D[5];
    u8 commandStopped862;
};

void sub_0801CD50(void)
{
    struct FrameObject *objects;
    u8 *work;
    u8 *row;
    u32 index;
    u32 selected;
    struct FrameObject *object;
    LeDecompress(gActionMotionAsset_084CF178, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F918, (void *)0x050002E0, 8);
    objects = gFrameObjects;
    work = gState0TransferWork.bytes;
    row = &work[0x87];
    index = *row * 4;
    row += 0x49;
    selected = *row;
    selected += 90;
    index += selected;
    object = &objects[index];
    sub_08036FF8(33, object->screenX, object->screenY, 4);
    work[0xAA]++;
}

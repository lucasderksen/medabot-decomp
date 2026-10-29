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

void sub_0801CDD4(void)
{
    struct ObservedActionFrameBacking *objects;
    u8 *work;
    u8 *row;
    u8 *selected;
    LeDecompress(gActionMotionAsset_084CDF48, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F8D8, (void *)0x050002E0, 8);
    objects = (void *)gFrameObjects;
    objects->flags840 = 0xC004;
    objects->table85C = 0;
    work = gState0TransferWork.bytes;
    row = &work[0x87];
    {
        u32 index = *row * 4;
        u32 subindex;
    selected = &work[0xD0];
    subindex = *selected;
    subindex += 90;
    index += subindex;
    objects->screenX842 = gFrameObjects[index].screenX;
    }
    {
        u32 index = *row * 4;
        u32 subindex;
    subindex = *selected;
    subindex += 90;
    index += subindex;
    objects->screenY844 = gFrameObjects[index].screenY;
    }
    objects->palette84A = 7;
    objects->priority84B = 240;
    sub_08040B90(gUnknownPointers_083B6100[34], 33);
    work[0xAA]++;
}

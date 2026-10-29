#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "state0_inventory.h"
#include "tile_text.h"

extern const u8 *const gUnknownPointers_083B7048[];
extern const void *const gUnknownPointers_083B66EC[];
extern const void *const gPartTypeNames_083BEAFC[];

u32 sub_0800F6CC(void)
{
    u8 *work = gState0TypedWork.bytes;
    return work[0xEF] >= 100 ? work[0xEF] - 100 : work[0xEF];
}

void sub_0800F6E4(void)
{
    u8 *work;
    sub_08040D0C(10, 15);
    work = gState0TypedWork.bytes;
    if (work[0xEF] < 100)
    {
        const void *source = gUnknownPointers_083B7048[work[0xF0]];
        work += 0x9E;
        sub_0803F63C(source, work, 14);
        sub_08040DB8(work, 10, 1, 9, 10, 12, 0, 1);
    }
    else
    {
        const void *source = gPartTypeNames_083BEAFC[work[0xEF] - 100];
        work += 0x9E;
        sub_0803F63C(source, work, 14);
        sub_08040DB8(work, 10, 1, 9, 10, 12, 0, 1);
    }
}

void sub_0800F77C(void)
{
    const void *const *names;
    u8 *work;
    const void *source;
    sub_08040D0C(25, 15);
    names = gUnknownPointers_083B66EC;
    work = gState0TypedWork.bytes;
    source = names[work[0xEE]];
    work += 0x9E;
    sub_0803F63C(source, work, 14);
    sub_08040DB8(work, 25, 2, 11, 8, 12, 0, 1);
}

void sub_0800F7D0(void)
{
    u8 *work = gState0TypedWork.bytes;
    if (work[0x3E] <= 2)
    {
        u32 value = sub_08042B80(work[0xF0]);
        u16 entry = (value * 0x40000 + 0x83900000) >> 16;
        sub_08042698(2, 2, 11, 9, *(volatile u16 *)0x0400000A, entry);
    }
    else
        sub_08042698(2, 2, 11, 9, *(volatile u16 *)0x0400000A,
                     ((u32)work[0xEF] * 0x40000 + 0xA2080000) >> 16);
}

void sub_0800F844(void)
{
    u8 *work;
    const void *const *names;
    const void *source;
    sub_08040D0C(40, 15);
    names = gPartTextPointers_083BBB4C;
    work = gState0TypedWork.bytes;
    source = names[work[0x3D] * 4 + work[0x3E]];
    work += 0x9E;
    sub_08041D04(source, work, 15);
    sub_08040DB8(work, 40, 11, 3, 10, 13, 0, 1);
}

void sub_0800F8A0(void)
{
    sub_08042698(2, 2, 21, 3, *(volatile u16 *)0x0400000A,
                 ((u32)gState0TypedWork.bytes[0xF1] * 0x40000 + 0x73880000) >> 16);
}

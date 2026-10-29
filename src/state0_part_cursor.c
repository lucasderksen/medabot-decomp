#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame.h"
#include "frame_objects.h"

extern const u8 *const gUnknownPointers_083B803C[];

void sub_0800FF50(void)
{
    const u8 *const *tables = gUnknownPointers_083B803C;
    u8 *work = gState0TypedWork.bytes;
    const u8 *table = tables[work[0x43]];
    { u32 count = table[0]; work[0x45] = count; }
    gFrameObjects[6].flags = 0xC004;
    { u32 index = work[0x44] + 1; const u8 *entry = table + index * 2; gFrameObjects[6].screenX = entry[0] * 8; }
    { u32 index = work[0x44] + 1; gFrameObjects[6].screenY = table[index * 2 + 1] * 8; }
    gFrameObjects[6].frameAndGroup = 0x308;
    gFrameObjects[6].palette = 14;
    gFrameObjects[6].tableSelector = 0;
    gFrameObjects[6].priority = 193;
    sub_08040B90(gUnknownPointers_083B6100[3], 6);
}

void sub_0800FFF4(void)
{
    const u8 *const *tables = gUnknownPointers_083B803C;
    u8 *work = gState0TypedWork.bytes;
    const u8 *table = tables[work[0x43]];
    /* Observed screenX/screenY halfwords of object 6; preserve base lifetime. */
    u8 *objects = (u8 *)gFrameObjects;
    u8 *selection = work + 0x44;
    { u32 index = *selection + 1; const u8 *entry = table + index * 2; u32 coordinate = entry[0] * 8; *(u16 *)(objects + 0x182) = coordinate; }
    { u32 index = *selection + 1; u32 coordinate = table[index * 2 + 1] * 8; *(u16 *)(objects + 0x184) = coordinate; }
}

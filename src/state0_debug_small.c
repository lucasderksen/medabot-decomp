

#include "state0_debug_menu.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "display_helpers.h"
#include "input.h"
#include "main.h"

extern u8 gDebugMenuTextBuffer[];
extern u8 gDebugProcessStateByte;
extern u8 gUnknown_030057E0[];
extern const void *const gDebugTinpetLabels_083ACC40[];
extern const void *const gDebugRandomLabels_083ACCA0[];
void sub_08042238(u8 value);

void sub_0800C6F8(void)
{
    u32 hidden = gFrameCounter & 4;
    if (hidden) sub_08040CD0(8, 8);
    else
    {
        sub_0803F63C(gDebugTinpetLabels_083ACC40[0], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, hidden);
    }
    if (*(u8 *)&gRepeatedKeys & 0x30)
        (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]] ^= 1;
    sub_08040CD0(32, 3);
    sub_08041370(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x69));
    sub_08040DB8(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    if (*(u8 *)&gNewKeys & 2)
    {
        sub_08040CD0(8, 33);
        gUnknown_0300137C = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        if (!sub_08042218()) sub_08042238(*(u8 *)((u32)gDebugMenuTextBuffer - 0x69));
    }
}

void sub_0800D188(void)
{
    u32 hidden = gFrameCounter & 4;
    if (hidden) sub_08040CD0(8, 8);
    else
    {
        sub_0803F63C(gDebugRandomLabels_083ACCA0[0], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, hidden);
    }
    if (*(u8 *)&gRepeatedKeys & 0x30) gUnknown_030057E0[0xC2C] ^= 1;
    sub_08040CD0(32, 3);
    sub_08041370(gDebugMenuTextBuffer, gUnknown_030057E0[0xC2C]);
    sub_08040DB8(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    if (*(u8 *)&gNewKeys & 2)
    {
        sub_08040CD0(8, 33);
        gUnknown_0300137C = 1;
    }
}

void sub_0800D684(void)
{
    sub_08040CD0(0, 128);
    gState0TypedWork.bytes[0x39] = 0;
    gState0TypedWork.bytes[0x33]++;
}


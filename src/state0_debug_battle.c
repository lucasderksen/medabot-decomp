

#include "state0_debug_menu.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame_objects.h"
#include "display_helpers.h"
#include "input.h"
#include "main.h"

extern u8 gDebugMenuTextBuffer[];
extern u8 gUnknown_030057E0[];
extern const void *const gDebugBattleLabels_083ACCAC[];

void sub_0800D27C(void)
{
    u32 hidden = gFrameCounter & 4;
    u32 cancel;
    if (hidden) ClearFrameObjects(8, 8);
    else
    {
        CopyBytes(gDebugBattleLabels_083ACCAC[0], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, hidden);
    }
    if (*(u8 *)&gRepeatedKeys & 16)
        (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]++;
    if (*(u8 *)&gRepeatedKeys & 32)
        (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]--;
    ClearFrameObjects(32, 3);
    sub_08041370(gDebugMenuTextBuffer,
        ((u8 *)((u32)gDebugMenuTextBuffer - 0x69))[
            *(u8 *)((u32)gDebugMenuTextBuffer - 0x6A)]);
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    cancel = (u8)(*(u8 *)&gNewKeys & 2);
    if (cancel)
    {
        ClearFrameObjects(8, 33);
        gUnknown_0300137C = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        ClearFrameObjects(8, 33);
        gUnknown_030057E0[0xC2E] = cancel;
        gUnknown_030057E0[0xC2F] = cancel;
        gUnknown_030057E0[0xC2D] = 1;
        gUnknown_030057E0[0xC2A] = ((u8 *)((u32)gDebugMenuTextBuffer - 0x69))[
            *(u8 *)((u32)gDebugMenuTextBuffer - 0x6A)];
        gMainSubstate = 6;
        gUnknown_0300137C = cancel;
    }
}

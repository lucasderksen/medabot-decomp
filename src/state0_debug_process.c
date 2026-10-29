

#include "state0_debug_menu.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"

extern u8 gState0FrameBackup[];
extern u8 gDebugProcessStateByte;
extern u8 gDebugMenuTextBuffer[];
extern const void *const gDebugProcessLabels_083ACBE4[];
extern const MainCallback gDebugMenuProcessCallbacks_083ACACC[];

void sub_0800BAF8(void)
{
    if (*(u8 *)&gNewKeys & 64)
    {
        if (!gState0TypedWork.bytes[0x34]) gState0TypedWork.bytes[0x34] = 2;
        else gState0TypedWork.bytes[0x34]--;
    }
    if (*(u8 *)&gNewKeys & 128)
    {
        if (gState0TypedWork.bytes[0x34] == 2) gState0TypedWork.bytes[0x34] = 0;
        else gState0TypedWork.bytes[0x34]++;
    }
    { u8 *work = gState0TypedWork.bytes;
    switch (work[0x34])
    {
    case 0:
        if (gFrameCounter & 4) sub_08040CD0(8, 8);
        else
        {
            sub_0803F63C(gDebugProcessLabels_083ACBE4[0], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 8, 2, 2, 8, 15, 1, 0);
        }
        sub_0803F63C(gDebugProcessLabels_083ACBE4[1], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        sub_0803F63C(gDebugProcessLabels_083ACBE4[2], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    case 1:
        if (gFrameCounter & 4) sub_08040CD0(16, 8);
        else
        {
            sub_0803F63C(gDebugProcessLabels_083ACBE4[1], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 16, 2, 4, 8, 15, 1, 0);
        }
        sub_0803F63C(gDebugProcessLabels_083ACBE4[0], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        sub_0803F63C(gDebugProcessLabels_083ACBE4[2], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    default:
        if (gFrameCounter & 4) sub_08040CD0(24, 8);
        else
        {
            sub_0803F63C(gDebugProcessLabels_083ACBE4[2], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 24, 2, 6, 8, 15, 1, 0);
        }
        sub_0803F63C(gDebugProcessLabels_083ACBE4[1], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        sub_0803F63C(gDebugProcessLabels_083ACBE4[0], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        break;
    }
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    { (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]++; }
    if (*(u8 *)&gRepeatedKeys & 32)
    { (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]--; }
    sub_08040CD0(32, 3);
    sub_08041370(gDebugMenuTextBuffer, gDebugProcessStateByte);
    sub_08040DB8(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    sub_08040CD0(35, 3);
    sub_08041370(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x68));
    sub_08040DB8(gDebugMenuTextBuffer, 35, 8, 4, 3, 15, 1, 0);
    sub_08040CD0(38, 3);
    sub_08041370(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x67));
    sub_08040DB8(gDebugMenuTextBuffer, 38, 8, 6, 3, 15, 1, 0);
    if (*(u8 *)&gNewKeys & 2)
    {
        sub_08040CD0(8, 33);
        gUnknown_0300137C = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = (u32)gState0FrameBackup;
        dma[1] = (u32)gFrameObjects;
        dma[2] = 0x84000400;
        (void)dma[2];
        gMainState = gDebugProcessStateByte;
        gMainSubstate = *(u8 *)((u32)gDebugMenuTextBuffer - 0x68);
        gUnknown_0300137C = *(u8 *)((u32)gDebugMenuTextBuffer - 0x67);
    }
}

void sub_0800BE6C(void)
{
    gDebugMenuProcessCallbacks_083ACACC[gState0TypedWork.bytes[0x33]]();
}

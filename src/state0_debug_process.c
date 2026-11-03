

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
        if (gFrameCounter & 4) ClearFrameObjects(8, 8);
        else
        {
            CopyBytes(gDebugProcessLabels_083ACBE4[0], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 8, 2, 2, 8, 15, 1, 0);
        }
        CopyBytes(gDebugProcessLabels_083ACBE4[1], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        CopyBytes(gDebugProcessLabels_083ACBE4[2], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    case 1:
        if (gFrameCounter & 4) ClearFrameObjects(16, 8);
        else
        {
            CopyBytes(gDebugProcessLabels_083ACBE4[1], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 16, 2, 4, 8, 15, 1, 0);
        }
        CopyBytes(gDebugProcessLabels_083ACBE4[0], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        CopyBytes(gDebugProcessLabels_083ACBE4[2], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    default:
        if (gFrameCounter & 4) ClearFrameObjects(24, 8);
        else
        {
            CopyBytes(gDebugProcessLabels_083ACBE4[2], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 24, 2, 6, 8, 15, 1, 0);
        }
        CopyBytes(gDebugProcessLabels_083ACBE4[1], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        CopyBytes(gDebugProcessLabels_083ACBE4[0], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        break;
    }
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    { (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]++; }
    if (*(u8 *)&gRepeatedKeys & 32)
    { (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]--; }
    ClearFrameObjects(32, 3);
    FormatDecimalString(gDebugMenuTextBuffer, gDebugProcessStateByte);
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    ClearFrameObjects(35, 3);
    FormatDecimalString(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x68));
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 35, 8, 4, 3, 15, 1, 0);
    ClearFrameObjects(38, 3);
    FormatDecimalString(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x67));
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 38, 8, 6, 3, 15, 1, 0);
    if (*(u8 *)&gNewKeys & 2)
    {
        ClearFrameObjects(8, 33);
        gNestedCallbackIndex = 1;
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
        gNestedCallbackIndex = *(u8 *)((u32)gDebugMenuTextBuffer - 0x67);
    }
}

void sub_0800BE6C(void)
{
    gDebugMenuProcessCallbacks_083ACACC[gState0TypedWork.bytes[0x33]]();
}

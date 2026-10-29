

#include "state0_debug_menu.h"
#include "main.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "input.h"
#include "compression.h"
#include "display_helpers.h"

extern u8 gState0FrameBackup[];
extern const MainCallback gDebugMenuCallbacks_083ACA5C[];
extern const MainCallback gDebugMenuPages_083ACA80[];
extern const MainCallback gDebugMenuValues_083ACAC0[];
extern const void *const gDebugMenuCategoryText_083ACBA0[];

void sub_0800B814(void)
{
    gFrameObjects[7].scaleX -= 8;
    gFrameObjects[7].scaleY -= 8;
    if (!gFrameObjects[7].scaleX)
    {
        sub_08040D0C(7, 1);
        gFrameObjects[7].unknown23[6]++;
    }
}

void sub_0800B858(void)
{
    sub_0803EF8C(12, 8, 18, 12, *(volatile u16 *)0x04000008, 0);
    gFrameObjects[7].unknown23[6]++;
}

void sub_0800B890(void)
{
    gDebugMenuCallbacks_083ACA5C[gUnknown_0300137C]();
}

void sub_0800B8B0(void)
{
    volatile u32 *dma;
    u32 fill;
    *(volatile u16 *)0x04000000 |= 0x1000;
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)gFrameObjects;
    dma[1] = (u32)gState0FrameBackup;
    dma[2] = 0x84000400;
    (void)dma[2];
    fill = 0;
    dma[0] = (u32)&fill;
    dma[1] = (u32)gFrameObjects;
    dma[2] = 0x85000400;
    (void)dma[2];
    LeDecompress((const void *)0x084C8034, (void *)0x06017400);
    dma[0] = 0x084E43D8;
    dma[1] = 0x050003E0;
    dma[2] = 0x84000008;
    (void)dma[2];
    gUnknown_0300137C++;
}

void sub_0800B938(void)
{
    u32 cancel;
    if (*(u8 *)&gNewKeys & 16)
    {
        if (gState0TypedWork.bytes[0x32] == 10) gState0TypedWork.bytes[0x32] = 0;
        else gState0TypedWork.bytes[0x32]++;
    }
    if (*(u8 *)&gNewKeys & 32)
    {
        if (!gState0TypedWork.bytes[0x32]) gState0TypedWork.bytes[0x32] = 10;
        else gState0TypedWork.bytes[0x32]--;
    }
    { u32 hidden = gFrameCounter & 4;
    if (hidden)
        sub_08040CD0(0, 8);
    else
    {
        sub_0803F63C(gDebugMenuCategoryText_083ACBA0[gState0TypedWork.bytes[0x32]], &gState0TypedWork.bytes[0x9E], 8);
        sub_08040DB8(&gState0TypedWork.bytes[0x9E], 0, 1, 0, 8, 15, 1, hidden);
    }
    }
    cancel = *(u8 *)&gNewKeys & 2;
    if (cancel)
        gUnknown_0300137C++;
    else if (*(u8 *)&gNewKeys & 1)
    {
        sub_0803F63C(gDebugMenuCategoryText_083ACBA0[gState0TypedWork.bytes[0x32]], &gState0TypedWork.bytes[0x9E], 8);
        sub_08040DB8(&gState0TypedWork.bytes[0x9E], 0, 1, 0, 8, 15, 1, cancel);
        gState0TypedWork.bytes[0x33] = cancel;
        gState0TypedWork.bytes[0x34] = cancel;
        gState0TypedWork.bytes[0x35] = cancel;
        gState0TypedWork.bytes[0x36] = cancel;
        gState0TypedWork.bytes[0x37] = cancel;
        gUnknown_0300137C = 3;
    }
}

void sub_0800BA74(void)
{
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)gState0FrameBackup;
    dma[1] = (u32)gFrameObjects;
    dma[2] = 0x84000400;
    (void)dma[2];
    gMainSubstate = gState0TypedWork.bytes[0x30];
    gUnknown_0300137C = gState0TypedWork.bytes[0x31];
}

void sub_0800BAB8(void)
{
    gDebugMenuPages_083ACA80[gState0TypedWork.bytes[0x32]]();
}

void sub_0800BAD8(void)
{
    gDebugMenuValues_083ACAC0[gState0TypedWork.bytes[0x33]]();
}

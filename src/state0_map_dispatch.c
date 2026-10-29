#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "render_work.h"

extern const MainCallback gState0MapCallbacks_083ACE24[];

void sub_08010264(void)
{
    if (gRenderMode == 2)
    {
        u32 fill = 0x200;
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = (u32)&fill;
        dma[1] = (u32)gRenderWork->objects;
        dma[2] = 0x85000100;
        (void)dma[2];
    }
    gState0MapCallbacks_083ACE24[gUnknown_0300137C]();
}

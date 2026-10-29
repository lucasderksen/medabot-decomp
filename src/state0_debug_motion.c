

#include "state0_debug_menu.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame_objects.h"
#include "display_helpers.h"
#include "input.h"
#include "main.h"
#include "utility_helpers.h"
#include "render_work.h"

extern u8 gDebugMenuTextBuffer[];
extern const void *const gDebugMotionLabels_083ACCD0[];

void sub_0800D710(void)
{
    u32 fill = 512;
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    u32 hidden;
    u32 select;
    dma[0] = (u32)&fill;
    dma[1] = (u32)gRenderWork->objects;
    dma[2] = 0x85000100;
    (void)dma[2];
    sub_080447EC(0, gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  56, 104, 0, 4, 0, 1, 0, 0);
    sub_080447EC(1, gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  184, 48, 0, 8, 1, 1, 1, 40);
    hidden = gFrameCounter & 4;
    if (hidden) sub_08040CD0(8, 8);
    else
    {
        sub_0803F63C(gDebugMotionLabels_083ACCD0[0], gState0TypedWork.bytes + 0x9E, 8);
        sub_08040DB8(gState0TypedWork.bytes + 0x9E, 8, 2, 2, 8, 15, 1, hidden);
    }
    if (*(u8 *)&gRepeatedKeys & 16)
        (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]++;
    if (*(u8 *)&gRepeatedKeys & 32)
        (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]]--;
    sub_08040CD0(32, 3);
    sub_08041370(gDebugMenuTextBuffer,
        ((u8 *)((u32)gDebugMenuTextBuffer - 0x69))[
            *(u8 *)((u32)gDebugMenuTextBuffer - 0x6A)]);
    sub_08040DB8(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    if (*(u8 *)&gRepeatedKeys & 8)
    {
        u8 *index = (u8 *)((u32)gDebugMenuTextBuffer - 0x65);
        if (*index == 121) *index = 0;
        else (*index)++;
        gState0TypedWork.bytes[0x33]--;
    }
    else if ((select = (u8)(*(u8 *)&gRepeatedKeys & 4)))
    {
        u8 *index = (u8 *)((u32)gDebugMenuTextBuffer - 0x65);
        if (!*index) *index = 121;
        else (*index)--;
        gState0TypedWork.bytes[0x33]--;
    }
    else if (*(u8 *)&gNewKeys & 2)
    {
        sub_08040CD0(8, 33);
        gRenderMode = select;
        gUnknown_0300137C = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
        (*(u8 *)((u32)gDebugMenuTextBuffer - 0x6B))++;
}



#include "state0_debug_menu.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame_objects.h"
#include "display_helpers.h"
#include "input.h"
#include "main.h"
#include "utility_helpers.h"
#include "render_work.h"

extern u8 gDebugMenuTextBuffer[];
extern const void *const gDebugMotionLabels_083ACCD0[];

void sub_0800D90C(void)
{
    u32 fill = 512;
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)&fill;
    dma[1] = (u32)gRenderWork->objects;
    dma[2] = 0x85000100;
    (void)dma[2];
    { u8 *work = gState0TypedWork.bytes;
    sub_080447EC(0, work[0x39], work[0x39], work[0x39], work[0x39],
                  56, 104, 0, 4, 0, 1, 0, 0);
    sub_080447EC(1, work[0x39], work[0x39], work[0x39], work[0x39],
                  184, 48, 0, 8, 1, 1, 1, 40);
    sub_08044A3C(0, (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]], work[0x39]);
    sub_08044A3C(1, (gState0TypedWork.bytes + 0x35)[gState0TypedWork.bytes[0x34]], work[0x39]);
    if (*(u8 *)&gNewKeys & 2) work[0x33] -= 2;
    }
}

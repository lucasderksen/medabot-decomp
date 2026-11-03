#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "equipment_helpers.h"
#include "render_work.h"


void sub_080116C4(void)
{
    u8 *state;
    u8 *work;
    s32 selector;
    ClearBgScrolls2();
    ClearFrameObjects(0, 128);
    state = gUnknown_03000440;
    {
        u8 *counter = state + 0x96;
        u32 zero = 0;
        *counter = zero;
        gRenderMode = zero;
    }
    work = gState0TransferWork.bytes;
    selector = work[0x168];
    switch (selector)
    {
    case 2:
        {
            u8 *buffer = state + 0x3C;
            FillBytes(buffer, 20, 0);
            *buffer = selector;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gNestedCallbackIndex = 16;
        break;
    case 0:
        {
            u8 *buffer = state + 0x3C;
            FillBytes(buffer, 20, 0);
            *buffer = 2;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gNestedCallbackIndex = 16;
        break;
    case 1:
        {
            u8 *buffer = state + 0x3C;
            FillBytes(buffer, 20, 0);
            *buffer = 2;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gNestedCallbackIndex = 16;
        break;
    case 3:
        {
            u8 *buffer = state + 0x3C;
            FillBytes(buffer, 20, 0);
            *buffer = 2;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gNestedCallbackIndex = 16;
        break;
    default:
        return;
    }

}


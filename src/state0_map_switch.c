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
    sub_08043CA8();
    sub_08040CD0(0, 128);
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
            sub_0803F624(buffer, 20, 0);
            *buffer = selector;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gUnknown_0300137C = 16;
        break;
    case 0:
        {
            u8 *buffer = state + 0x3C;
            sub_0803F624(buffer, 20, 0);
            *buffer = 2;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gUnknown_0300137C = 16;
        break;
    case 1:
        {
            u8 *buffer = state + 0x3C;
            sub_0803F624(buffer, 20, 0);
            *buffer = 2;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gUnknown_0300137C = 16;
        break;
    case 3:
        {
            u8 *buffer = state + 0x3C;
            sub_0803F624(buffer, 20, 0);
            *buffer = 2;
        }
    {
        u32 value = work[0x169];
        state[0x3D] = value;
    }
    state[0x3E] = selector;
    gMainSubstate = 5;
    gUnknown_0300137C = 16;
        break;
    default:
        return;
    }

}


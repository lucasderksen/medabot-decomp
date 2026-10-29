

#include "state0_debug_menu.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"
#include "compression.h"
extern u8 gDebugMenuTextBuffer[];
extern const void *const gDebugFaceLabels_083ACC78[];
extern const void *const gUnknownPointers_083AC614[];
void sub_0800CBC8(void)
{
    if (((struct DebugMenuKeyBits *)&gNewKeys)->up | ((struct DebugMenuKeyBits *)&gNewKeys)->down)
        gState0TypedWork.bytes[0x34] ^= 1;
    { u8 *work = gState0TypedWork.bytes;
    switch (work[0x34])
    {
    case 0:
        if (gFrameCounter & 4) sub_08040CD0(8, 8);
        else
        {
            sub_0803F63C(gDebugFaceLabels_083ACC78[0], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 8, 2, 2, 8, 15, 1, 0);
        }
        sub_0803F63C(gDebugFaceLabels_083ACC78[1], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        break;
    case 1:
        { u32 hidden = gFrameCounter & 4;
        if (hidden) sub_08040CD0(16, 8);
        else
        {
            sub_0803F63C(gDebugFaceLabels_083ACC78[1], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 16, 2, 4, 8, 15, 1, hidden);
        }
        }
        sub_0803F63C(gDebugFaceLabels_083ACC78[0], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        break;
    }
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    {
        if (!gState0TypedWork.bytes[0x34])
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (*value == 175) *value = 0;
            else (*value)++;
        }
        else
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (*value == 8) *value = 0;
            else (*value)++;
        }
    }
    if (*(u8 *)&gRepeatedKeys & 32)
    {
        if (!gState0TypedWork.bytes[0x34])
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (!*value) *value = 175;
            else (*value)--;
        }
        else
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (!*value) *value = 8;
            else (*value)--;
        }
    }
    sub_08040CD0(32, 3);
    sub_08041370(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x69));
    sub_08040DB8(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    sub_08040CD0(35, 3);
    sub_08041370(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x68));
    sub_08040DB8(gDebugMenuTextBuffer, 35, 8, 4, 3, 15, 1, 0);
    { u32 cancel = (u8)(*(u8 *)&gNewKeys & 2);
    if (cancel)
    {
        sub_0803EF8C(17, 8, 0, 7, *(volatile u16 *)0x04000008, 0);
        sub_08040CD0(8, 33);
        gUnknown_0300137C = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        sub_0803F480(*(u8 *)((u32)gDebugMenuTextBuffer - 0x69),
                    *(u8 *)((u32)gDebugMenuTextBuffer - 0x68), 0, 7, 1);
        sub_0803F480(*(u8 *)((u32)gDebugMenuTextBuffer - 0x69),
                    *(u8 *)((u32)gDebugMenuTextBuffer - 0x68), 9, 7, cancel);
    }
    }
}



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
extern const void *const gDebugSoundLabels_083ACCC0[];
extern const void *const gUnknownPointers_083AC614[];
void sub_0800D3E4(void)
{
    if (((struct DebugMenuKeyBits *)&gNewKeys)->up | ((struct DebugMenuKeyBits *)&gNewKeys)->down)
        gState0TypedWork.bytes[0x34] ^= 1;
    { u8 *work = gState0TypedWork.bytes;
    switch (work[0x34])
    {
    case 0:
        if (gFrameCounter & 4) ClearFrameObjects(8, 8);
        else
        {
            CopyBytes(gDebugSoundLabels_083ACCC0[0], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 8, 2, 2, 8, 15, 1, 0);
        }
        CopyBytes(gDebugSoundLabels_083ACCC0[1], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        break;
    case 1:
        { u32 hidden = gFrameCounter & 4;
        if (hidden) ClearFrameObjects(16, 8);
        else
        {
            CopyBytes(gDebugSoundLabels_083ACCC0[1], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 16, 2, 4, 8, 15, 1, hidden);
        }
        }
        CopyBytes(gDebugSoundLabels_083ACCC0[0], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        break;
    }
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    {
        if (!gState0TypedWork.bytes[0x34])
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (*value == 127) *value = 0;
            else (*value)++;
        }
        else
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (*value == 53) *value = 0;
            else (*value)++;
        }
    }
    if (*(u8 *)&gRepeatedKeys & 32)
    {
        if (!gState0TypedWork.bytes[0x34])
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (!*value) *value = 127;
            else (*value)--;
        }
        else
        {
            u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
            if (!*value) *value = 53;
            else (*value)--;
        }
    }
    ClearFrameObjects(32, 3);
    FormatDecimalString(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x69));
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    ClearFrameObjects(35, 3);
    FormatDecimalString(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x68));
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 35, 8, 4, 3, 15, 1, 0);
    if (*(u8 *)&gNewKeys & 2)
    {
        PlayMusic(0);
        ClearFrameObjects(8, 33);
        gNestedCallbackIndex = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        u8 *selected = (u8 *)((u32)gDebugMenuTextBuffer - 0x6A);
        u8 *values = (u8 *)((u32)gDebugMenuTextBuffer - 0x69);
        if (!*selected) PlaySoundEffect(values[*selected]);
        else PlayMusic(values[*selected]);
    }
}

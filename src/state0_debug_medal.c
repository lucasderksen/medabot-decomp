



#include "state0_debug_menu.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"
#include "frame_objects.h"
#include "object_helpers.h"

extern u8 gState0FrameBackup[];
extern u8 gDebugProcessStateByte;
extern u8 gDebugProcessCallbackByte;
extern u8 gDebugMedalWork_03000BEA[];
extern const u8 *const gDebugMedalMetadata_083B6590[];
u32 sub_08041D70(u8 value);
extern u8 gDebugMenuTextBuffer[];
extern const void *const gDebugMedalLabels_083ACC08[];
extern const MainCallback gDebugMenuProcessCallbacks_083ACACC[];

void sub_0800BE8C(void)
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
            sub_0803F63C(gDebugMedalLabels_083ACC08[0], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 8, 2, 2, 8, 15, 1, 0);
        }
        sub_0803F63C(gDebugMedalLabels_083ACC08[1], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        sub_0803F63C(gDebugMedalLabels_083ACC08[2], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    case 1:
        if (gFrameCounter & 4) sub_08040CD0(16, 8);
        else
        {
            sub_0803F63C(gDebugMedalLabels_083ACC08[1], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 16, 2, 4, 8, 15, 1, 0);
        }
        sub_0803F63C(gDebugMedalLabels_083ACC08[0], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        sub_0803F63C(gDebugMedalLabels_083ACC08[2], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    default:
        if (gFrameCounter & 4) sub_08040CD0(24, 8);
        else
        {
            sub_0803F63C(gDebugMedalLabels_083ACC08[2], work + 0x9E, 8);
            sub_08040DB8(work + 0x9E, 24, 2, 6, 8, 15, 1, 0);
        }
        sub_0803F63C(gDebugMedalLabels_083ACC08[1], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        sub_0803F63C(gDebugMedalLabels_083ACC08[0], gDebugMenuTextBuffer, 8);
        sub_08040DB8(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        break;
    }
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    {
        u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
        if (*value == 29) *value = 0;
        else (*value)++;
    }
    if (*(u8 *)&gRepeatedKeys & 32)
    {
        u8 *value = (gState0TypedWork.bytes + 0x35) + gState0TypedWork.bytes[0x34];
        if (!*value) *value = 29;
        else (*value)--;
    }
    sub_08040CD0(32, 3);
    sub_08041370(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x69));
    sub_08040DB8(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    sub_08040CD0(35, 3);
    sub_08041370(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x68));
    sub_08040DB8(gDebugMenuTextBuffer, 35, 8, 4, 3, 15, 1, 0);
    sub_08040CD0(38, 3);
    sub_08041370(gDebugMenuTextBuffer, gDebugProcessCallbackByte);
    sub_08040DB8(gDebugMenuTextBuffer, 38, 8, 6, 3, 15, 1, 0);
    { u32 cancel = (u8)(*(u8 *)&gNewKeys & 2);
    if (cancel)
    {
        sub_08040CD0(8, 33);
        gUnknown_0300137C = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        u8 *selected = (u8 *)((u32)gDebugMenuTextBuffer - 0x6A);
        u8 *values = (u8 *)((u32)gDebugMenuTextBuffer - 0x69);
        switch (*selected)
        {
        case 0:
            if (*values <= 29 && !sub_08041D3C(*values))
            {
                u8 slot = sub_08041D70(values[*selected]);
                sub_0803F63C(gDebugMedalMetadata_083B6590[values[*selected]],
                            gDebugMedalWork_03000BEA + slot * 64, 11);
            }
            break;
        case 1:
            if (*(u8 *)((u32)gDebugMenuTextBuffer - 0x68) <= 29
                && sub_08041D3C(*(u8 *)((u32)gDebugMenuTextBuffer - 0x68)))
                sub_08041FE4(values[*selected]);
            break;
        default:
            gDebugProcessCallbackByte = cancel;
            do
            {
                if (!sub_08041D3C(gState0TypedWork.bytes[0x37]))
                {
                    u8 slot = sub_08041D70(gState0TypedWork.bytes[0x37]);
                    sub_0803F63C(gDebugMedalMetadata_083B6590[gState0TypedWork.bytes[0x37]],
                                gDebugMedalWork_03000BEA + slot * 64, 11);
                }
                gState0TypedWork.bytes[0x37]++;
            } while (gState0TypedWork.bytes[0x37] <= 29);
            break;
        }
    }
    }
}





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
u32 AddInventoryRecord(u8 value);
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
        if (gFrameCounter & 4) ClearFrameObjects(8, 8);
        else
        {
            CopyBytes(gDebugMedalLabels_083ACC08[0], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 8, 2, 2, 8, 15, 1, 0);
        }
        CopyBytes(gDebugMedalLabels_083ACC08[1], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        CopyBytes(gDebugMedalLabels_083ACC08[2], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    case 1:
        if (gFrameCounter & 4) ClearFrameObjects(16, 8);
        else
        {
            CopyBytes(gDebugMedalLabels_083ACC08[1], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 16, 2, 4, 8, 15, 1, 0);
        }
        CopyBytes(gDebugMedalLabels_083ACC08[0], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
        CopyBytes(gDebugMedalLabels_083ACC08[2], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 24, 2, 6, 8, 15, 1, 0);
        break;
    default:
        if (gFrameCounter & 4) ClearFrameObjects(24, 8);
        else
        {
            CopyBytes(gDebugMedalLabels_083ACC08[2], work + 0x9E, 8);
            PlaceAlignedTextObjects(work + 0x9E, 24, 2, 6, 8, 15, 1, 0);
        }
        CopyBytes(gDebugMedalLabels_083ACC08[1], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 16, 2, 4, 8, 15, 1, 0);
        CopyBytes(gDebugMedalLabels_083ACC08[0], gDebugMenuTextBuffer, 8);
        PlaceAlignedTextObjects(gDebugMenuTextBuffer, 8, 2, 2, 8, 15, 1, 0);
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
    ClearFrameObjects(32, 3);
    FormatDecimalString(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x69));
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 32, 8, 2, 3, 15, 1, 0);
    ClearFrameObjects(35, 3);
    FormatDecimalString(gDebugMenuTextBuffer, *(u8 *)((u32)gDebugMenuTextBuffer - 0x68));
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 35, 8, 4, 3, 15, 1, 0);
    ClearFrameObjects(38, 3);
    FormatDecimalString(gDebugMenuTextBuffer, gDebugProcessCallbackByte);
    PlaceAlignedTextObjects(gDebugMenuTextBuffer, 38, 8, 6, 3, 15, 1, 0);
    { u32 cancel = (u8)(*(u8 *)&gNewKeys & 2);
    if (cancel)
    {
        ClearFrameObjects(8, 33);
        gNestedCallbackIndex = 1;
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        u8 *selected = (u8 *)((u32)gDebugMenuTextBuffer - 0x6A);
        u8 *values = (u8 *)((u32)gDebugMenuTextBuffer - 0x69);
        switch (*selected)
        {
        case 0:
            if (*values <= 29 && !FindInventoryRecordById(*values))
            {
                u8 slot = AddInventoryRecord(values[*selected]);
                CopyBytes(gDebugMedalMetadata_083B6590[values[*selected]],
                            gDebugMedalWork_03000BEA + slot * 64, 11);
            }
            break;
        case 1:
            if (*(u8 *)((u32)gDebugMenuTextBuffer - 0x68) <= 29
                && FindInventoryRecordById(*(u8 *)((u32)gDebugMenuTextBuffer - 0x68)))
                ClearInventoryRecordById(values[*selected]);
            break;
        default:
            gDebugProcessCallbackByte = cancel;
            do
            {
                if (!FindInventoryRecordById(gState0TypedWork.bytes[0x37]))
                {
                    u8 slot = AddInventoryRecord(gState0TypedWork.bytes[0x37]);
                    CopyBytes(gDebugMedalMetadata_083B6590[gState0TypedWork.bytes[0x37]],
                                gDebugMedalWork_03000BEA + slot * 64, 11);
                }
                gState0TypedWork.bytes[0x37]++;
            } while (gState0TypedWork.bytes[0x37] <= 29);
            break;
        }
    }
    }
}

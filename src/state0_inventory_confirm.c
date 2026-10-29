

#include "state0_inventory_confirm.h"
#include "state0_callbacks.h"
#include "state0_inventory_view.h"
#include "state0_inventory.h"
#include "state0_work.h"
#include "frame.h"
#include "input.h"
#include "main.h"

struct KeyByteView { u8 low; u8 high; };
extern const u16 gState0CursorCoordinates_083ACA2C[];
extern const MainCallback gState0ConfirmCallbacks_083ACA4C[];


void sub_0800B4EC(void)
{
    struct InventoryRecord *records = gInventoryRecords;
    u8 *work = gState0TypedWork.bytes;
    u8 *selected = &work[0x3D];
    struct InventoryRecord *record = &records[*selected];
    if (record->byte0 & 0x80)
        if (*(u8 *)&gHeldKeys & 8)
            if (((struct KeyByteView *)&gRepeatedKeys)->high & 2)
                if (record->byte5 != 100)
                {
                    record->byte5++;
                    sub_08041D04(gInventoryMetadata_083B62D8 + records[*selected].byte1 * 16, &work[0xEE], 16);
                    records[*selected].unknown06[2] = sub_080420C4(records[*selected].byte5, work[0xF1], work[0xF2], work[0xF3], work[0xF4]);
                    sub_08009750();
                    sub_08009620();
                }
}

void sub_0800B594(void)
{
    struct InventoryRecord *records = gInventoryRecords;
    struct InventoryRecord *record = &records[gState0TypedWork.bytes[0x3D]];
    if (record->byte0 & 0x80)
        if (*(u8 *)&gHeldKeys & 8)
            if (((struct KeyByteView *)&gRepeatedKeys)->high & 1)
                if (*(u16 *)&record->unknown02[0] > 99)
                {
                    *(u16 *)&record->unknown02[0] -= 100;
                    sub_080097E0();
                }
}

void sub_0800B5E8(void)
{
    gFrameObjects[127].flags = 0xC804;
    { const u16 *coordinates = gState0CursorCoordinates_083ACA2C;
    gFrameObjects[127].screenX = coordinates[gState0TypedWork.selection.word48 * 2];
    { u32 offset = gState0TypedWork.selection.word48 * 2 + 1; gFrameObjects[127].screenY = coordinates[offset]; }
    gFrameObjects[127].frameAndGroup = 0x303;
    gFrameObjects[127].palette = 14;
    gFrameObjects[127].tableSelector = 0;
    gFrameObjects[127].priority = 64; }
}

void sub_0800B668(void)
{
    gFrameObjects[7].flags = 0xD204;
    gFrameObjects[7].screenX = 168;
    gFrameObjects[7].screenY = gState0TypedWork.bytes[0x4A] * 16 + 112;
    gFrameObjects[7].frameAndGroup = 0x307;
    gFrameObjects[7].palette = 14;
    gFrameObjects[7].scaleX = 64;
    gFrameObjects[7].scaleY = 64;
    gFrameObjects[7].tableSelector = 0;
    gFrameObjects[7].unknown23[6] = 0;
    gFrameObjects[7].unknown23[4] = 0;
    gFrameObjects[7].priority = 193;
}

void sub_0800B6E8(void)
{
    if (*(u8 *)&gRepeatedKeys & 64)
    {
        if (!gState0TypedWork.bytes[0x4A]) gState0TypedWork.bytes[0x4A] = 2;
        else gState0TypedWork.bytes[0x4A]--;
    }
    if (*(u8 *)&gRepeatedKeys & 128)
    {
        if (gState0TypedWork.bytes[0x4A] == 2) gState0TypedWork.bytes[0x4A] = 0;
        else gState0TypedWork.bytes[0x4A]++;
    }
    if (*(u8 *)&gRepeatedKeys & 192)
    {
        sub_08074DE0(2);
        gFrameObjects[7].screenY = gState0TypedWork.bytes[0x4A] * 16 + 112;
    }
}

u32 sub_0800B768(void)
{
    gState0ConfirmCallbacks_083ACA4C[gFrameObjects[7].unknown23[6]]();
    if (gFrameObjects[7].unknown23[6] == 3) return 1;
    return 0;
}

void sub_0800B79C(void)
{
    if (gFrameObjects[7].unknown23[4] != 30)
    {
        if (gFrameObjects[7].unknown23[4] & 4)
            gFrameObjects[7].flags &= 0xBFFF;
        else
            gFrameObjects[7].flags |= 0x4000;
        gFrameObjects[7].unknown23[4]++;
    }
    else
    {
        gFrameObjects[7].flags |= 0x4000;
        gFrameObjects[7].unknown23[6]++;
    }
}

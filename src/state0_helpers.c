#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "main.h"
#include "bg_scroll.h"
#include "frame.h"
#include "display_helpers.h"

void sub_08004E74(void)
{
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}

void sub_08004E98(void)
{
    gFrameObjects[0].flags = 0xC604;
    gFrameObjects[0].unknown23[0] = 0;
    sub_08004EF8(0);
    gFrameObjects[1].flags = 0xC604;
    gFrameObjects[1].unknown23[0] = 16;
    sub_08004EF8(1);
    gFrameObjects[2].flags = 0xC604;
    gFrameObjects[2].unknown23[0] = 32;
    sub_08004EF8(2);
    gFrameObjects[3].flags = 0xC604;
    gFrameObjects[3].unknown23[0] = 48;
    sub_08004EF8(3);
}

void sub_08004EF8(u32 index)
{
    union { struct TileCoordinates coordinates; s32 packed; } position;
    s32 copy;
    s32 delta;
    s32 x = gUnknownBytes_083AC5A0[gState0TypedWork.bytes[0x51] * 2];
    s32 y = gUnknownBytes_083AC5A0[gState0TypedWork.bytes[0x51] * 2 + 1];
    struct FrameObject *base = gFrameObjects;
    struct FrameObject *object = &base[index];
    position.coordinates = sub_08042CA0(((object->unknown23[0] + 16) & 63) * 4, 16, x, y, 8, 0);
    copy = position.packed;
    object->screenX = copy;
    object->screenY = copy >> 16;
    object->frameAndGroup = 0x400;
    object->palette = 12;
    object->tableSelector = 0;
    delta = object->screenY - 8;
    delta = y - delta;
    object->scaleY = 64 - 3 * delta;
    delta = object->screenY - 8;
    delta = y - delta;
    object->scaleX = 96 - 3 * delta;
    if ((u32)y > (u32)object->screenY)
        object->priority = gUnknownBytes_083AC5B2[gState0TypedWork.bytes[0x51]] - 1;
    else
        object->priority = gUnknownBytes_083AC5B2[gState0TypedWork.bytes[0x51]] + 4;
    gFrameObjects[index].angle = gFrameObjects[index].unknown23[0] << 4;
    gFrameObjects[index].unknown23[0] = (gFrameObjects[index].unknown23[0] + 1) & 63;
}

void sub_08004FD0(void)
{
    u32 i = 0;
    struct State0Record8 *record = gUnknownRecords_030017A0;
    for (; i <= 8; record++, i++)
        if (record->unknown00[0])
            sub_08042D94(record->byte3, record->byte4, record->byte5, record->byte6, i);
}

void sub_08005118(void)
{
    struct State0Record8 *record;
    struct State0Record8 *base;
    sub_08040D0C(50, 10);
    base = gUnknownRecords_030017A0;
    record = &base[gState0TypedWork.bytes[0x51]];
    if (record->unknown00[0] > 1)
        sub_08040DB8(gUnknown_03000BAA + sub_08041D3C(record->unknown00[2]) * 64,
                    50, 1, 13, 10, 13, 0, 2);
    else
    {
        sub_08042678(gState0TypedWork.bytes + 0x9E, 10);
        sub_08040DB8(gState0TypedWork.bytes + 0x9E, 50, 1, 13, 10, 13, 0, 2);
    }
}

void sub_0800519C(void)
{
    struct State0Record8 *record;
    struct State0Record8 *base;
    sub_08040D0C(60, 10);
    base = gUnknownRecords_030017A0;
    record = &base[gState0TypedWork.bytes[0x51]];
    if (record->unknown00[0] > 1)
    {
        sub_0803F63C(gUnknownPointers_083B6590[record->unknown00[2]], gState0TypedWork.bytes + 0x9E, 11);
        sub_08040DB8(gState0TypedWork.bytes + 0x9E, 60, 4, 16, 7, 14, 1, 2);
    }
    else
    {
        sub_08042678(gState0TypedWork.bytes + 0x9E, 9);
        sub_08040DB8(gState0TypedWork.bytes + 0x9E, 60, 4, 16, 7, 14, 1, 2);
    }
}

void sub_0800522C(void)
{
    struct State0Record8 *record = gUnknownRecords_030017A0;
    record += gState0TypedWork.bytes[0x51];
    if (record->unknown00[0] > 1)
        CpuFastSet(gUnknownBytes_084C29D8 + record->unknown00[2] * 128, (void *)0x06006600, 32);
    else
        CpuFastSet(gUnknownBytes_084C38D8, (void *)0x06006600, 32);
    sub_08042698(2, 2, 1, 16, *(volatile u16 *)0x0400000A, 0x6330);
}

void sub_080056A4(u32 index)
{
    union { struct TileCoordinates coordinates; s32 packed; } position;
    s32 copy;
    s32 delta;
    s32 x = gUnknownBytes_083AC5A0[(gState0TypedWork.bytes[0x52] & 0x7F) * 2];
    s32 y = gUnknownBytes_083AC5A0[(gState0TypedWork.bytes[0x52] & 0x7F) * 2 + 1] - 4;
    struct FrameObject *base = gFrameObjects;
    struct FrameObject *object = &base[index];
    position.coordinates = sub_08042CA0(((object->unknown23[0] + 16) & 63) * 4, 16, x, y, 8, 0);
    copy = position.packed;
    object->screenX = copy;
    object->screenY = copy >> 16;
    object->frameAndGroup = 0x400;
    object->palette = 12;
    object->tableSelector = 0;
    delta = object->screenY - 8;
    delta = y - delta;
    object->scaleY = 64 - 3 * delta;
    delta = object->screenY - 8;
    delta = y - delta;
    object->scaleX = 96 - 3 * delta;
    if ((u32)y > (u32)object->screenY)
        object->priority = gUnknownBytes_083AC5B2[gState0TypedWork.bytes[0x52] & 0x7F] - 1;
    else
        object->priority = gUnknownBytes_083AC5B2[gState0TypedWork.bytes[0x52] & 0x7F] + 4;
    gFrameObjects[index].angle = gFrameObjects[index].unknown23[0] << 4;
    gFrameObjects[index].unknown23[0] = (gFrameObjects[index].unknown23[0] - 1) & 63;
}

#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "main.h"
#include "input.h"
#include "frame.h"
#include "render_work.h"
#include "display_helpers.h"

void sub_0800529C(void)
{
    u32 fill;
    sub_0803F624(&gRecordDisplayWork, 0xD0, 0);
    sub_0803F624(gRecordDisplayData, 0x800, 0);
    sub_0803F624(gRecordDisplayExtra, 0x60, 0);
    gRenderMode = 2;
    gRenderWork = (struct RenderWork *)0x02024000;
    fill = 0;
    CpuFastSet(&fill, gRenderWork, CPU_SET_FILL | 0x426);
    gRecordDisplayExtraPointer = gRecordDisplayExtra;
    sub_08047414(&gRecordDisplayWork, gRenderWork, gUnknownBytes_083D1D78, gRecordDisplayData);
    gRecordDisplayWork.data = gRecordDisplayData;
    if (gState0TypedWork.bytes[0x5E])
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte3,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte4,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte5,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte6,
            40, 40, 450, 8, 1, 1);
    else
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte3,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte4,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte5,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte6,
            40, 40, 450, 8, 1, 0);
}

void sub_080053C8(void)
{
    u32 fill;
    gRecordDisplayWork.data = gRecordDisplayData;
    if (gState0TypedWork.bytes[0x5E])
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte3,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte4,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte5,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte6,
            40, 40, 450, 8, 1, 1);
    else
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte3,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte4,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte5,
            gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte6,
            40, 40, 450, 8, 1, 0);
    fill = 0x200;
    CpuFastSet(&fill, gRenderWork->objects, CPU_SET_FILL | 0x100);
    gRenderWork->byte1094 = 0;
    gRenderWork->byte1095 = 0;
}

void sub_080054C0(void)
{
    struct State0Record8 *base = gUnknownRecords_030017A0;
    struct State0Record8 *record = &base[gState0TypedWork.bytes[0x51]];
    if (record->unknown00[0])
    {
        if (gState0TypedWork.bytes[0x5E])
            sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
                record->byte3, record->byte4, record->byte5,
                gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte6,
                60, 50, 450, 8, 5, 1);
        else
            sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
                record->byte3, record->byte4, record->byte5,
                gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].byte6,
                60, 50, 450, 8, 5, 0);
    }
}

u32 sub_08005588(void)
{
    u32 changed = 0;
    const u8 *next;
    if ((u8)gRepeatedKeys & 0x40) { next = gUnknownPointers_083AC604[0]; changed = 1; }
    if ((u8)gRepeatedKeys & 0x80) { next = gUnknownPointers_083AC604[1]; changed = 1; }
    if ((u8)gRepeatedKeys & 0x20) { next = gUnknownPointers_083AC604[2]; changed = 1; }
    if ((u8)gRepeatedKeys & 0x10) { next = gUnknownPointers_083AC604[3]; changed = 1; }
    if (changed)
    {
    sub_08074DE0(2);
    gState0TypedWork.bytes[0x51] = next[gState0TypedWork.bytes[0x51]];
    sub_08004EF8(0); sub_08004EF8(1); sub_08004EF8(2); sub_08004EF8(3);
    sub_08005118(); sub_0800519C(); sub_0800522C(); sub_080053C8(); sub_08005000(); sub_08005948();
    return 1;
    }
    else return 0;
}

void sub_08005628(void)
{
    gFrameObjects[4].flags = 0xC604; gFrameObjects[4].unknown23[0] = 0; sub_080056A4(4);
    gFrameObjects[5].flags = 0xC604; gFrameObjects[5].unknown23[0] = 16; sub_080056A4(5);
    gFrameObjects[6].flags = 0xC604; gFrameObjects[6].unknown23[0] = 32; sub_080056A4(6);
    gFrameObjects[7].flags = 0xC604; gFrameObjects[7].unknown23[0] = 48; sub_080056A4(7);
}

void sub_08005798(void)
{
    if (gState0TypedWork.bytes[0x52] & 0x80)
    {
        if (gFrameCounter & 1)
        {
            gFrameObjects[4].flags |= 0x4000; gFrameObjects[5].flags |= 0x4000;
            gFrameObjects[6].flags |= 0x4000; gFrameObjects[7].flags |= 0x4000;
        }
        else
        {
            gFrameObjects[4].flags &= 0xBFFF; gFrameObjects[5].flags &= 0xBFFF;
            gFrameObjects[6].flags &= 0xBFFF; gFrameObjects[7].flags &= 0xBFFF;
        }
        sub_080056A4(4); sub_080056A4(5); sub_080056A4(6); sub_080056A4(7);
    }
    else
    {
        gFrameObjects[4].flags &= 0xBFFF; gFrameObjects[5].flags &= 0xBFFF;
        gFrameObjects[6].flags &= 0xBFFF; gFrameObjects[7].flags &= 0xBFFF;
    }
}

u32 sub_080058A4(void)
{
    if (!gState0TypedWork.bytes[0x50] && ((u8)gNewKeys & 4))
    {
    sub_08074DE0(2);
    if (gState0TypedWork.bytes[0x52] & 0x80)
    {
        gState0TypedWork.bytes[0x52] &= 0x7F;
        if (gState0TypedWork.bytes[0x52] != gState0TypedWork.bytes[0x51])
        {
            sub_0803F65C(&gUnknownRecords_030017A0[gState0TypedWork.bytes[0x52]],
                        &gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]], 8);
            sub_08004FD0(); sub_08005000(); sub_0800508C(); sub_08005118(); sub_0800519C();
            sub_0800522C(); sub_080053C8(); sub_08005948();
        }
        gState0TypedWork.bytes[0x52] = 0;
    }
    else
    {
        gState0TypedWork.bytes[0x52] = gState0TypedWork.bytes[0x51] + 0x80;
        sub_08005628();
    }
    sub_08005798();
    return 1;
    }
    return 0;
}

void sub_08005948(void)
{
    struct State0Record8 *base = gUnknownRecords_030017A0;
    struct State0Record8 *record = &base[gState0TypedWork.bytes[0x51]];
    if (sub_08043814(record->unknown00[2], record->byte3, record->byte4, record->byte5, record->byte6))
        sub_08043240(gState0TypedWork.bytes[0x51] * 4 + 10, 8);
}

void sub_0800598C(void)
{
    struct State0Record8 *base = gUnknownRecords_030017A0;
    struct State0Record8 *record = &base[gState0TypedWork.bytes[0x51]];
    if (sub_08043814(record->unknown00[2], record->byte3, record->byte4, record->byte5, record->byte6))
        sub_080432A0(gState0TypedWork.bytes[0x51] * 4 + 10, gState0TypedWork.bytes[0x51], 0);
}

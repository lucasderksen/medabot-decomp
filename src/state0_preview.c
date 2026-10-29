#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "later_helpers.h"


void sub_0800F300(void)
{
    u8 *work;
    u32 fill;
    gRecordDisplayWork.data = gRecordDisplayData;
    work = gState0TypedWork.bytes;
    switch (work[0x3E])
    {
    case 0:
        sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 0, 60, 50, 450, 8, 1);
        break;
    case 1:
        sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 1, 40, 60, 450, 8, 1);
        break;
    case 2:
        sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 2, 40, 40, 450, 8, 2);
        break;
    case 3:
        sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 3, 30, 50, 450, 8, 1);
        break;
    }
    fill = 512;
    CpuFastSet(&fill, gRenderWork->objects, CPU_SET_FILL | 0x100);
    gRenderWork->byte1094 = 0;
    gRenderWork->byte1095 = 0;
}

void sub_0800F440(void)
{
    u8 *work = gState0TypedWork.bytes;
    if ((u8)(work[0x3C] - 2) <= 1)
    {
        gRecordDisplayWork.data = gRecordDisplayData;
        switch (work[0x3E])
        {
        case 0:
            sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 0, 60, 50, 450, 8, 5);
            break;
        case 1:
            sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 1, 40, 60, 450, 8, 5);
            break;
        case 2:
            sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 2, 40, 40, 450, 8, 6);
            break;
        case 3:
            sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, work[0x3D], 3, 30, 50, 450, 8, 5);
            break;
        }
    }
    else
    {
        u8 *selected = &work[0x3D];
        u8 value = *selected;
        u8 *group = &work[0x3E];
        if (sub_08042114(value, *group))
        {
            gRecordDisplayWork.data = gRecordDisplayData;
            switch (*group)
            {
            case 0:
                sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, *selected, 0, 60, 50, 450, 8, 5);
                break;
            case 1:
                sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, *selected, 1, 40, 60, 450, 8, 5);
                break;
            case 2:
                sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, *selected, 2, 40, 40, 450, 8, 6);
                break;
            case 3:
                sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, *selected, 3, 30, 50, 450, 8, 5);
                break;
            }
        }
    }
}

void sub_0800F60C(void)
{
    u32 fill;
    u8 *work;
    void *objects;
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
    objects = gRenderWork->objects;
    work = gState0TypedWork.bytes;
    sub_08046A60(objects, &gRecordDisplayWork, work[0x3D], work[0x3E], 60, 40, 450, 8, 1);
}

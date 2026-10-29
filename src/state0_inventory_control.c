#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "frame.h"
#include "main.h"
#include "input.h"

union InventoryKeys { u32 raw; struct { u32 low:6; u32 up:1; u32 down:1; u32 high:24; } bits; };

void sub_0800656C(void)
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
            gState0TypedWork.bytes[0x98],
            gState0TypedWork.bytes[0x99],
            gState0TypedWork.bytes[0x9A],
            gState0TypedWork.bytes[0x9B],
            40, 40, 450, 8, 1, 1);
    else
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gState0TypedWork.bytes[0x98],
            gState0TypedWork.bytes[0x99],
            gState0TypedWork.bytes[0x9A],
            gState0TypedWork.bytes[0x9B],
            40, 40, 450, 8, 1, 0);
}


void sub_0800667C(void)
{
    u32 fill;
    gRecordDisplayWork.data = gRecordDisplayData;
    if (gState0TypedWork.bytes[0x5E])
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gState0TypedWork.bytes[0x98],
            gState0TypedWork.bytes[0x99],
            gState0TypedWork.bytes[0x9A],
            gState0TypedWork.bytes[0x9B],
            40, 40, 450, 8, 1, 1);
    else
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gState0TypedWork.bytes[0x98],
            gState0TypedWork.bytes[0x99],
            gState0TypedWork.bytes[0x9A],
            gState0TypedWork.bytes[0x9B],
            40, 40, 450, 8, 1, 0);
    fill = 0x200;
    CpuFastSet(&fill, gRenderWork->objects, CPU_SET_FILL | 0x100);
    gRenderWork->byte1094 = 0;
    gRenderWork->byte1095 = 0;
}


void sub_08006764(void)
{
    if (gState0TypedWork.bytes[0x5E])
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gState0TypedWork.bytes[0x98], gState0TypedWork.bytes[0x99],
            gState0TypedWork.bytes[0x9A], gState0TypedWork.bytes[0x9B],
            60, 50, 450, 8, 5, 1);
    else
        sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork,
            gState0TypedWork.bytes[0x98], gState0TypedWork.bytes[0x99],
            gState0TypedWork.bytes[0x9A], gState0TypedWork.bytes[0x9B],
            60, 50, 450, 8, 5, 0);
}

void sub_08006824(void)
{
    if (gFrameCounter & 8) {
        switch (gState0TypedWork.bytes[0x5A]) {
        case 0: sub_08006238(0); break;
        case 1: sub_08006284(0); break;
        case 2: sub_080062D0(0); break;
        case 3: sub_0800631C(0); break;
        case 4: sub_08006368(0); break;
        }
    } else {
        switch (gState0TypedWork.bytes[0x5A]) {
        case 0: sub_08006238(1); break;
        case 1: sub_08006284(1); break;
        case 2: sub_080062D0(1); break;
        case 3: sub_0800631C(1); break;
        case 4: sub_08006368(1); break;
        }
    }
}

u32 sub_080068EC(void)
{
    if ((u8)gRepeatedKeys & 0x40) {
        if (!gState0TypedWork.bytes[0x5A]) gState0TypedWork.bytes[0x5A] = 4;
        else gState0TypedWork.bytes[0x5A]--;
    }
    if ((u8)gRepeatedKeys & 0x80) {
        if (gState0TypedWork.bytes[0x5A] == 4) gState0TypedWork.bytes[0x5A] = 0;
        else gState0TypedWork.bytes[0x5A]++;
    }
    if (((union InventoryKeys *)&gRepeatedKeys)->bits.up | ((union InventoryKeys *)&gRepeatedKeys)->bits.down) {
        sub_08074DE0(2);
        sub_08006238(0); sub_08006284(0); sub_080062D0(0); sub_0800631C(0); sub_08006368(0);
        sub_08006494();
        return 1;
    }
    return 0;
}

u32 sub_08006980(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 previous;
    if (work[0x5A]) goto unchanged;
    previous = work[0x97];
    if ((u8)gRepeatedKeys & 0x20) work[0x97] = sub_0804361C(previous, 1);
    if ((u8)gRepeatedKeys & 0x10) work[0x97] = sub_0804361C(work[0x97], 0);
    if (previous != work[0x97]) goto changed;
unchanged:
    return 0;
changed:
    sub_08074DE0(2);
    sub_08005AD0(); sub_08005B44(); sub_08005C10(); sub_08005BB4();
    sub_08005D1C(); sub_08005E84(); sub_08005FEC(); sub_08006154();
    return 1;
}

u32 sub_08006A00(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 previous;
    if (work[0x5A] != 1) goto unchanged;
    previous = work[0x98];
    if ((u8)gRepeatedKeys & 0x20)
        work[0x98] = sub_080436AC(previous, 0, 1, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if ((u8)gRepeatedKeys & 0x10)
        work[0x98] = sub_080436AC(work[0x98], 0, 0, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if (previous != work[0x98]) goto changed;
unchanged:
    return 0;
changed:
    sub_08074DE0(2); sub_08005C9C(); sub_08005D1C();
    sub_08006414(); sub_08006444(); sub_0800667C();
    return 1;
}

u32 sub_08006A98(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 previous;
    if (work[0x5A] != 2) goto unchanged;
    previous = work[0x99];
    if ((u8)gRepeatedKeys & 0x20)
        work[0x99] = sub_080436AC(previous, 1, 1, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if ((u8)gRepeatedKeys & 0x10)
        work[0x99] = sub_080436AC(work[0x99], 1, 0, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if (previous != work[0x99]) goto changed;
unchanged:
    return 0;
changed:
    sub_08074DE0(2); sub_08005E00(); sub_08005E84();
    sub_08006414(); sub_08006444(); sub_0800667C();
    return 1;
}

u32 sub_08006B30(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 previous;
    if (work[0x5A] != 3) goto unchanged;
    previous = work[0x9A];
    if ((u8)gRepeatedKeys & 0x20)
        work[0x9A] = sub_080436AC(previous, 2, 1, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if ((u8)gRepeatedKeys & 0x10)
        work[0x9A] = sub_080436AC(work[0x9A], 2, 0, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if (previous != work[0x9A]) goto changed;
unchanged:
    return 0;
changed:
    sub_08074DE0(2); sub_08005F68(); sub_08005FEC();
    sub_08006414(); sub_08006444(); sub_0800667C();
    return 1;
}

u32 sub_08006BC8(void)
{
    u8 *work = gState0TypedWork.bytes;
    u32 previous;
    if (work[0x5A] != 4) goto unchanged;
    previous = work[0x9B];
    if ((u8)gRepeatedKeys & 0x20)
        work[0x9B] = sub_080436AC(previous, 3, 1, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if ((u8)gRepeatedKeys & 0x10)
        work[0x9B] = sub_080436AC(work[0x9B], 3, 0, gUnknownRecords_030017A0[work[0x51]].unknown00[1]);
    if (previous != work[0x9B]) goto changed;
unchanged:
    return 0;
changed:
    sub_08074DE0(2); sub_080060D0(); sub_08006154();
    sub_080063B4(); sub_08006414(); sub_08006444(); sub_0800667C();
    return 1;
}

#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "graphics.h"
#include "render_work.h"
#include "serial.h"

extern void sub_08004E74(void);
extern void sub_08005000(void);
extern void sub_080054C0(void);
extern void sub_08007480(void);
extern void sub_08042B58(u32, u32, void *);
extern u32 sub_0803E79C(void);
extern const void *const gUnknownPointers_083CF530[];


#define ENTRY_LINK_WORK() do { \
    sub_08004E74(); \
    sub_080054C0(); \
    sub_08007480(); \
} while (0)

void sub_08004764(void)
{
    sub_08004E74();
    sub_08005000();
    sub_080054C0();
    sub_08040D0C(0, 4);
    gState0TypedWork.widths.word5C = 0;
    gUnknown_0300137C++;
}

void sub_08004798(void)
{
    ENTRY_LINK_WORK();
    if (gState0TypedWork.widths.word5C > 60)
    {
        if (gState0TypedWork.bytes[0x50] == 1)
            gUnknown_0300137C = 48;
        else
        {
            SnapshotPalettes();
            gState0TypedWork.bytes[0x84] = 0;
            gUnknown_0300137C++;
        }
    }
}

void sub_080047EC(void)
{
    ENTRY_LINK_WORK();
    if (gState0TypedWork.bytes[0x84] <= 32)
    {
        sub_0803F684(0, gState0TypedWork.bytes[0x84], 0xFFFF);
        sub_0803F998(0, gState0TypedWork.bytes[0x84], 0xFFFF);
        gState0TypedWork.bytes[0x84]++;
    }
    else
        gUnknown_0300137C++;
}

void sub_08004840(void)
{
    sub_08040CD0(0, 128);
    gState0TypedWork.bytes[0x96] = 0;
    gRenderMode = 0;
    gMainSubstate = 7;
    gUnknown_0300137C = 0;
}

void sub_08004874(void)
{
    ENTRY_LINK_WORK();
    if (gState0TypedWork.widths.word5C > 60)
    {
        sub_080750F0(8);
        sub_0804253C(6, 63, 8);
        gUnknown_0300137C++;
    }
}

void sub_080048B0(void)
{
    ENTRY_LINK_WORK();
    if (sub_080425DC())
        gUnknown_0300137C++;
}

void sub_080048D8(void)
{
    s32 i;
    sub_08040CD0(0, 128);
    gState0TypedWork.bytes[0x96] = 0;
    gRenderMode = 0;
    for (i = 0; i <= 2; i++)
    {
        sub_08042B58(gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte6, 3, &gState0TypedWork.bytes[0xEE]);
        gState0TransferWork.indexed.results[i] = gState0TypedWork.bytes[0xEF] - 100;
        gState0TransferWork.indexed.records[i].byte0 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte3;
        gState0TransferWork.indexed.records[i].byte1 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte4;
        gState0TransferWork.indexed.records[i].byte2 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte5;
        gState0TransferWork.indexed.records[i].byte3 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte6;
    }
    gMainState = 3;
    gMainSubstate = 4;
    gUnknown_0300137C = 5;
}

void sub_080049C8(void)
{
    sub_08004E74();
    sub_080054C0();
    sub_0803FAA0(1, 0, 0);
    gUnknown_0300137C++;
}

void sub_080049EC(void)
{
    sub_08004E74();
    sub_080054C0();
    if (sub_0803FB3C(gUnknownPointers_083CF530[11]))
        gUnknown_0300137C++;
}

void sub_08004A18(void)
{
    sub_08004E74();
    sub_080054C0();
    sub_08014E7C();
    sub_08014E94();
    sub_08014EC8();
    gUnknown_0300137C++;
}

void sub_08004A40(void)
{
    sub_08004E74();
    sub_080054C0();
    if (sub_0803E79C())
    {
        gMainSerialOutgoingWork.word06 = 0;
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C++;
    }
}

void sub_08004A78(void)
{
    sub_08004E74();
    sub_080054C0();
    if (gState0TypedWork.widths.word86 == 24)
    {
        gState0TransferWork.bytes[0x51] = 0;
        gState0TransferWork.bytes[0x52] = 0;
        gState0TransferWork.bytes[0x53] = 0;
        gState0TransferWork.bytes[0x54] = 0;
        gState0TransferWork.widths.words1A6[0] = 0;
        gState0TransferWork.widths.words1A6[1] = 0;
        gState0TransferWork.widths.words1A6[2] = 0;
        gState0TransferWork.widths.words1A6[3] = 0;
        gState0TransferWork.bytes[0x1AF] = 0;
        gState0TransferWork.bytes[0x1B0] = 1;
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C++;
    }
    else
        (gState0TypedWork.widths.word86)++;
}

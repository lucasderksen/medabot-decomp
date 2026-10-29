#include "state0_callbacks.h"
#include "state0_work.h"
#include "graphics.h"
#include "render_work.h"
#include "serial.h"

extern void sub_08004E74(void);
extern void sub_080054C0(void);
extern void sub_08007540(void);
extern u8 gUnknown_03000B90;
extern u8 gTransferSendBuffers[3][256];
extern u8 gTransferReceiveBuffers[3][256];

void sub_08004C58(void)
{
    sub_08004E74();
    sub_080054C0();
    if (gState0TypedWork.widths.word86 == 16)
    {
        gState0TransferWork.bytes[0x51] = 0;
        gState0TransferWork.bytes[0x52] = 0;
        gState0TransferWork.bytes[0x53] = 0;
        gState0TransferWork.bytes[0x54] = 0;
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C++;
    }
    else
        gState0TypedWork.widths.word86++;
}

void sub_08004CA4(void)
{
    sub_08004E74();
    sub_080054C0();
    if (gState0TransferWork.bytes[0x51] <= 1)
    {
        switch (gState0TransferWork.bytes[0x51])
        {
        case 0:
            gMainSerialOutgoingWork.word06 = 0x8000 + gState0TransferWork.widths.words1A6[0];
            break;
        case 1:
            gMainSerialOutgoingWork.word06 = 0x8000 + gState0TransferWork.widths.words1A6[1];
            break;
        }
        gState0TransferWork.bytes[0x51]++;
    }
    {
        u16 received = gMainSerialOutgoingWork.words[gUnknown_03000B90 ^ 1][1];
        if (received & 0x8000)
        {
            switch (gState0TransferWork.bytes[0x52])
            {
            case 0:
                gState0TransferWork.widths.words1A6[2] = received & 0x7FFF;
                break;
            case 1:
                gState0TransferWork.widths.words1A6[3] = received & 0x7FFF;
                break;
            }
            gState0TransferWork.bytes[0x52]++;
            if (gState0TransferWork.bytes[0x52] == 2)
            {
                if (gState0TransferWork.widths.words1A6[0] == gState0TransferWork.widths.words1A6[3]
                    && gState0TransferWork.widths.words1A6[1] == gState0TransferWork.widths.words1A6[2])
                    gUnknown_0300137C++;
                else
                    gUnknown_0300137C = 50;
            }
        }
    }
}

void sub_08004DB4(void)
{
    gMainSerialOutgoingWork.word06 = 0;
    sub_08004E74();
    sub_080054C0();
    sub_08007540();
    SnapshotPalettes();
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08004DF0(void)
{
    sub_08004E74();
    sub_080054C0();
    if (gState0TypedWork.bytes[0x84] <= 32)
    {
        sub_0803F684(0, gState0TypedWork.bytes[0x84], 0xFFFF);
        sub_0803F998(0, gState0TypedWork.bytes[0x84], 0xFFFF);
        gState0TypedWork.bytes[0x84]++;
    }
    else
        gUnknown_0300137C++;
}

void sub_08004E40(void)
{
    sub_08040CD0(0, 128);
    gState0TypedWork.bytes[0x96] = 0;
    gRenderMode = 0;
    gMainSubstate = 7;
    gUnknown_0300137C = 0;
}

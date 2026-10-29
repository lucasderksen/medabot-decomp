#include "compression.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Observed physical object33 fields over the canonical backing, no extent claim. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x840];
    u16 flags840;
    u16 screenX842;
    u16 screenY844;
    u8 unknown846[4];
    u8 palette84A;
    u8 priority84B;
    u8 unknown84C[0x10];
    u8 table85C;
    u8 unknown85D[5];
    u8 commandStopped862;
};

void sub_0801CD08(void)
{
    u8 *work = gState0TransferWork.bytes;
    if (work[0x51] == 2)
        work[0xAA]++;
    else
        work[0xAA] = 8;
}

void sub_0801CD28(void)
{
    u8 *work = gState0TransferWork.bytes;
    work[0xA6] = 21;
    work[0xAA]++;
}

void sub_0801CD40(void)
{
    gState0TransferWork.bytes[0xAA] = 32;
}

void sub_0801CDB4(void)
{
    if (sub_080370AC(33, 4))
        gState0TransferWork.bytes[0xAA]++;
}

void sub_0801CE94(void)
{
    sub_08040BD8(gUnknownPointers_083B6100[34], 33);
    if (((struct ObservedActionFrameBacking *)gFrameObjects)->commandStopped862 == 255)
    {
        sub_08040CD0(33, 1);
        sub_080158F8();
        sub_0801A0D0();
        switch (gState0TransferWork.bytes[0x51])
        {
        case 0:
            LeDecompress(gActionKindAsset_084CA61C, (void *)0x06014800);
            CpuFastSet(gActionKindPalette_0850F5F8, (void *)0x050002C0, 8);
            break;
        case 1:
            LeDecompress(gActionKindAsset_084CA828, (void *)0x06014800);
            CpuFastSet(gActionKindPalette_0850F618, (void *)0x050002C0, 8);
            break;
        case 2:
            LeDecompress(gActionKindAsset_084CABC4, (void *)0x06014800);
            CpuFastSet(gActionKindPalette_0850F638, (void *)0x050002C0, 8);
            break;
        case 3:
            LeDecompress(gActionKindAsset_084CAD2C, (void *)0x06014800);
            CpuFastSet(gActionKindPalette_0850F658, (void *)0x050002C0, 8);
            break;
        }
        gState0TransferWork.bytes[0xAA] = 14;
    }
}

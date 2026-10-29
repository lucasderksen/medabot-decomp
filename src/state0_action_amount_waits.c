#include "compression.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Only observed physical object33 accesses, over the canonical array backing. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x840];
    u16 flags840;
    u16 screenX842;
    u16 screenY844;
    u16 frame846;
    u8 scaleX848;
    u8 scaleY849;
    u8 palette84A;
    u8 priority84B;
    u8 unknown84C[0x10];
    u8 table85C;
    u8 unknown85D[6];
    u8 byte863;
};

void sub_0801CFFC(void)
{
    switch (gState0TransferWork.bytes[0x51])
    {
    case 0:
        LeDecompress(gActionKindAsset_084CA61C, (void *)0x06015400);
        break;
    case 1:
        LeDecompress(gActionKindAsset_084CA828, (void *)0x06015400);
        break;
    case 2:
        LeDecompress(gActionKindAsset_084CABC4, (void *)0x06015400);
        break;
    case 3:
        LeDecompress(gActionKindAsset_084CAD2C, (void *)0x06015400);
        break;
    }
    gState0TransferWork.bytes[0xAA]++;
}

void sub_0801D174(void)
{
    ((struct ObservedActionFrameBacking *)gFrameObjects)->byte863 = 0;
    gUnknown_03000440[0x84] = 0;
    sub_08074DE0(52);
    gState0TransferWork.bytes[0xAA]++;
}

void sub_0801D1AC(void)
{
    if (sub_080353CC(33) == 0)
    {
        u8 *work = gUnknown_03000440;
        if ((work[0x84] & 1) == 0)
        {
            if (gState0TransferWork.bytes[0x89] == 0)
                ((struct ObservedActionFrameBacking *)gFrameObjects)->screenX842++;
            else
                ((struct ObservedActionFrameBacking *)gFrameObjects)->screenX842--;
        }
        work[0x84]++;
    }
    else
    {
        struct ObservedActionFrameBacking *objects = (void *)gFrameObjects;
        if (objects->scaleX848 == 8)
        {
            sub_08040CD0(33, 1);
            gState0TransferWork.bytes[0xAA]++;
        }
        else
            objects->scaleX848 -= 8;
    }
}

void sub_0801D244(void)
{
    u8 *work = gState0TransferWork.bytes;
    if (work[0x51] == 2)
        work[0xAA] = 46;
    else
        work[0xAA] = 45;
}

void sub_0801D264(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = &work[0x89];
    work[*selected * 8 + 0x2A] = 0;
    work[*selected * 8 + 0x2B] = 0;
    work[*selected * 8 + 0x2C] = 0;
    work[*selected * 8 + 0x2D] = 0;
    work[0xA6] = 37;
    work[0xAA]++;
}

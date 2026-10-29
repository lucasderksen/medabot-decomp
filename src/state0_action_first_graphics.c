#include "compression.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

void sub_0801C6C4(void)
{
    switch (gState0TransferWork.bytes[0x51])
    {
    case 0:
        LeDecompress((const u8 *)0x084CA61C, (void *)0x06014800);
        CpuFastSet((const void *)0x0850F5F8, (void *)0x050002C0, 8);
        break;
    case 1:
        LeDecompress((const u8 *)0x084CA828, (void *)0x06014800);
        CpuFastSet((const void *)0x0850F618, (void *)0x050002C0, 8);
        break;
    case 2:
        LeDecompress((const u8 *)0x084CABC4, (void *)0x06014800);
        CpuFastSet((const void *)0x0850F638, (void *)0x050002C0, 8);
        break;
    case 3:
        LeDecompress((const u8 *)0x084CAD2C, (void *)0x06014800);
        CpuFastSet((const void *)0x0850F658, (void *)0x050002C0, 8);
        break;
    }
    gState0TransferWork.bytes[0xAA]++;
}

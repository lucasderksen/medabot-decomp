#include "frame_objects.h"
#include "display_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"
/* Physical access coverage only, not the original object type or size. */
struct ObservedActionWork {
    u8 unknown00[0x87];
    u8 selected87;
    u8 unknown88[0x56];
    u8 selectedDE;
};


void sub_08033ACC(void)
{
    struct ObservedActionWork *work = (void *)gState0TransferWork.bytes;
    if (work->selectedDE)
    {
        u8 *buffer = gActionTransferBuffer_03003470;
        {
            u8 *first = buffer;
            s32 row = work->selectedDE;
            u32 base;
            row--;
            row *= 256;
            base = (u32)buffer;
            base += 0xE40;
            sub_0803F63C(first, (void *)(row + base), 0x40);
        }
        {
            u8 *first = buffer + 0x40;
            s32 row = work->selectedDE;
            u32 base;
            row--;
            row *= 256;
            base = (u32)buffer;
            base += 0xE80;
            sub_0803F63C(first, (void *)(row + base), 0x40);
        }
        {
            u8 *first = buffer + 0x80;
            s32 row = work->selectedDE;
            u32 base;
            row--;
            row *= 256;
            base = (u32)buffer;
            base += 0xEC0;
            sub_0803F63C(first, (void *)(row + base), 0x40);
        }
        {
            u8 *first = buffer + 0xC0;
            s32 row = work->selectedDE;
            u32 base;
            row--;
            row *= 256;
            base = (u32)buffer;
            base += 0xF00;
            sub_0803F63C(first, (void *)(row + base), 0x40);
        }
        sub_08040CD0(0x21, 4);
        sub_08040D44(work->selectedDE * 4 + 0x56, 4);
        sub_0801BC04(work->selectedDE - 1);
        work->selectedDE = 0;
        sub_080158F8();
        sub_0801A0D0();
    }
    sub_08034F08();
}

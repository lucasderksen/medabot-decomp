#include "compression.h"
#include "display_helpers.h"
#include "coordinate_helpers.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Partial physical access view over canonical stride64 FrameObject backing. */
struct ObservedActionPartnerFrame
{
    u16 flags;
    u16 x;
    u16 y;
    u8 unknown06[0x1E];
    u8 byte24;
    u8 byte25;
    u8 unknown26[0xA];
    u16 half30;
    u8 unknown32[0xE];
};

struct ObservedRecordFlagAccess
{
    u8 unknown00[0x59];
    u8 byte59;
};

void sub_0801D878(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = &work[0xDE];
    sub_080432A0((*selected - 1) * 4 + 90, *selected - 1, (work[0xF8] & 1) ^ 1);
    if (gUnknown_03000440[0x84] & 4)
        sub_08040D0C(*selected * 4 + 86, 4);
    else
        sub_08040D44(*selected * 4 + 86, 4);
    if (++gUnknown_03000440[0x84] == 60)
    {
        u8 *work = gState0TransferWork.bytes;
        u8 *selected = &work[0xDE];
        struct ObservedActionPartnerFrame *frames;
        sub_08040D44(*selected * 4 + 86, 4);
        sub_08074DE0(64);
        frames = (void *)gFrameObjects;
        frames[*selected * 4 + 89].byte24 = 4;
        frames[*selected * 4 + 89].byte25 = 0;
        {
            u32 offset = *selected * 256;
            struct ObservedActionPartnerFrame *destination;
            offset += 89 * 64;
            destination = (void *)(offset + (u32)frames);
            destination->half30 = 0;
        }
        sub_08035694(*selected + 113);
        work[0xAA]++;
    }
}

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

void sub_0801D6A4(void)
{
    switch (gState0TransferWork.bytes[0xDF])
    {
    case 27:
        LeDecompress(gActionPartnerAsset_084CAE20, (void *)0x06014800);
        CpuFastSet(gActionPartnerPalette_0850F698, (void *)0x050002C0, 8);
        break;
    case 28:
        LeDecompress(gActionPartnerAsset_084CB128, (void *)0x06014800);
        CpuFastSet(gActionPartnerPalette_0850F6B8, (void *)0x050002C0, 8);
        break;
    case 29:
        LeDecompress(gActionPartnerAsset_084CB43C, (void *)0x06014800);
        CpuFastSet(gActionPartnerPalette_0850F6D8, (void *)0x050002C0, 8);
        break;
    }
    gState0TransferWork.bytes[0xAA]++;
}

void sub_0801D95C(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = &work[0xDE];
    if (sub_080352EC(*selected * 4 + 89, -32, -16))
    {
        sub_080356CC(*selected * 4 + 89, *selected + 113);
        sub_080432A0((*selected - 1) * 4 + 90, *selected - 1, (work[0xF8] & 1) ^ 1);
        work[0xAA]++;
    }
    else
    {
        sub_080432A0((*selected - 1) * 4 + 90, *selected - 1, (work[0xF8] & 1) ^ 1);
        sub_080356CC(*selected * 4 + 89, *selected + 113);
    }
}

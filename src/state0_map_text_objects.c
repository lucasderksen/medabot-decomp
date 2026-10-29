#include "state0_next_helpers.h"
#include "state0_work.h"
#include "display_helpers.h"
#include "frame_objects.h"
#include "coordinate_helpers.h"


void sub_08011F50(void)
{
    const u8 *source = gState0EncounterLabels_083C40B8[gState0TransferWork.bytes[0]];
    u8 *buffer = gDebugMenuTextBuffer;
    sub_0803F63C(source, buffer, 18);
    sub_08040EE4(buffer, 10, 18, 3, 10, 13, 0, 1, 0, -4);
}

void sub_08011FA0(void)
{
    const u8 *source = gState0MapPartLabels_083BEB68[gState0TransferWork.bytes[0x38]];
    u8 *buffer = gDebugMenuTextBuffer;
    sub_0803F63C(source, buffer, 11);
    sub_08040DB8(buffer, 30, 1, 3, 8, 12, 0, 1);
}

void sub_08011FEC(void)
{
    u32 i = 0;
    u32 count = gState0TransferWork.bytes[2];
    if (i < count)
    {
        u8 *work = gState0TransferWork.bytes;
        u8 *record = work + 4;
        do
        {
            sub_08042D94(record[0], record[1], record[2], record[3], i);
            record += 12;
            i++;
        } while (i < work[2]);
    }
}

void sub_08012024(void)
{
    u32 i = 0;
    u32 count = gState0TransferWork.bytes[2];
    if (i < count)
    {
        u8 *work = gState0TransferWork.bytes;
        u32 position = (u32)gState0MapRowPositions_083AD064;
        u32 slot = 40;
        u8 *record = work + 4;
        do
        {
            sub_08042E58(record[0], record[1], record[2], record[3], i, slot,
                        *(const u8 *)position, *(const u8 *)(position + 1), 1, 1, 0);
            sub_08043240(slot, 8);
            position += 2;
            slot += 4;
            record += 12;
            i++;
        } while (i < work[2]);
    }
}

void sub_08012098(void)
{
    u32 i = 0;
    u32 count = gState0TransferWork.bytes[2];
    if (i < count)
    {
        u8 *work = gState0TransferWork.bytes;
        u32 slot = 40;
        do
        {
            sub_080432A0(slot, i, 1);
            slot += 4;
            i++;
        } while (i < work[2]);
    }
}

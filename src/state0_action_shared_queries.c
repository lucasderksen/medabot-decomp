#include "state0_next_helpers.h"
#include "state0_work.h"

/* Observed fullword input/result model; original unused formal slots unknown. */

/* Physical access view, not a recovered complete RAM object type. */
struct ObservedActionResultWork {
    u8 unknown00[0xE8];
    u16 valueE8;
    u8 unknownEA[2];
    s16 valueEC;
};

u32 sub_08033090(u32 first)
{
    u32 selected = sub_08033074();
    u32 forward = sub_080424B8() & 1;
    u32 tested = 0;
    u8 *entries = gSetupBuffer_03000590;
    do
    {
        u32 row = first + selected;
        if (entries[row * 256 + 0x40])
            return row;
        if (forward)
        {
            selected++;
            if (selected > 2)
                selected = 0;
        }
        else
        {
            if (selected == 0)
                selected = 2;
            else
                selected--;
        }
        tested++;
    } while (tested <= 2);
    return first + selected;
}

u32 sub_0803576C(u32 selected)
{
    u32 total = 0;
    u32 count = 0;
    u8 *entries = gSetupBuffer_03000590;
    u32 row = selected * 256;
    u8 *base = row + entries;
    u32 kind = base[4];
    u8 *record;
    entries += 0x48;
    record = row + entries;
    do
    {
        if (kind == *record)
            total += base[7];
        record += 24;
        count++;
    } while (count <= 3);
    return total;
}

struct ObservedSetupAB {
    u8 unknown00[0xA9];
    u8 byteA9;
    u8 unknownAA;
    u8 byteAB;
    u8 unknownAC[0x54];
};

void sub_0803769C(u32 selected)
{
    struct ObservedActionResultWork *work = (void *)gState0TransferWork.bytes;
    u8 *entries;
    u32 row;
    struct ObservedSetupAB *record;
    work->valueE8 = 0;
    entries = gSetupBuffer_03000590;
    row = selected * 256;
    record = &((struct ObservedSetupAB *)entries)[selected];
    work->valueE8 = record->byteAB;
    work->valueE8 += sub_0803576C(selected);
    work->valueE8 += sub_080424B8() & 7;
    {
        u32 offset = record->byteA9 + row;
        entries += 0x20;
        work->valueE8 += entries[offset];
    }
}

/* Observed physical row stride and byteAC; total setup extent unknown. */
struct ObservedSetupAC {
    u8 unknown00[0xAC];
    u8 byteAC;
    u8 unknownAD[0x53];
};

void sub_080376F4(u32 selected)
{
    struct ObservedActionResultWork *work = (void *)gState0TransferWork.bytes;
    s32 value = (s16)work->valueE8 >> 3;
    work->valueEC = value;
    {
        struct ObservedSetupAC *records = (void *)gSetupBuffer_03000590;
        value += records[selected].byteAC;
    }
    work->valueEC = value;
    if (value == 0)
        work->valueEC = 1;
}

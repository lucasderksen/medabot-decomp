#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
/* Observed256-byte record stride and accessed fields; original type unknown. */
struct MapTextRecord { u8 unknown00[0x40]; u8 byte40; u8 unknown41[0x8D]; u8 byteCE; u8 unknownCF[0x31]; };


void sub_08014920(void)
{
    u32 selected;
    u8 *buffer;
    sub_080195C0();
    sub_0801A0D0();
    selected = 0;
    buffer = gUnknown_0300052E;
    for (; selected <= 5; selected++)
    {
        u8 *base = gSetupBuffer_03000590;
        u32 offset = selected * 256;
        u8 *record = base + offset;
        if (record[0x40] && (record[0xCE] & 8))
        {
            sub_0801A28C(buffer, record[0xCD], 1);
            sub_0801A144(buffer, selected);
        }
    }
    sub_08074DE0(91);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08014994(void)
{
    u32 selected;
    u8 *counter;
    u8 *work;
    sub_080195C0();
    selected = 0;
    do
    {
        struct MapTextRecord *records = (void *)gSetupBuffer_03000590;
        if (records[selected].byte40 && (records[selected].byteCE & 8))
            sub_0801A228(selected);
        selected++;
    } while (selected <= 5);
    work = gUnknown_03000440;
    counter = work + 0x84;
    (*counter)++;
    if (*counter == 90)
    {
        u32 objectIndex;
        selected = 0;
        objectIndex = 10U << 24;
        for (; selected <= 5; selected++)
        {
            u8 *record = gSetupBuffer_03000590;
            record += selected * 256;
            if (record[0x40])
            {
                u8 *active = record + 0xCE;
                if (*active & 8)
                {
                    *active &= 0xF7;
                    sub_08040CD0(objectIndex >> 24, 3);
                }
            }
            objectIndex += 4U << 24;
        }
        gState0TransferWork.bytes[0x55] &= 0xEF;
        gUnknown_0300137C = 68;
    }
}

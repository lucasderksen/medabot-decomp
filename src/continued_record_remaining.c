#include "continued_commands.h"
#include "frame.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern const u8 gContinuedLookup_083D262C[];
extern void sub_0804D980(void *record);

struct RecordFlagsByte
{
    u8 slot : 5;
    u8 unknown5 : 1;
    u8 active : 1;
    u8 unknown7 : 1;
} __attribute__((packed));

void sub_0804BC20(void)
{
    u8 *work = gUnknown_030057E0;
    u32 offset = work[0xCB4] * 8;
    u8 *row = work + offset;
    u32 field = *(u16 *)(row + 0x5DE);
    u32 masked = 0xFFF;
    masked &= field;
    if (masked == *(u16 *)(work + 0xC8E))
    {
        u32 address = (u32)work;
        address += 0x5DC;
        address += offset;
        sub_0804D980((void *)address);
    }
}

void sub_0804BDD8(void)
{
    u8 *buffer, *work, *selection;
    u32 zero, slot, index, value, offset, address;
    sub_0804D8CC(2);
    buffer = gLaterBuffer_03006D20;
    work = gUnknown_030057E0;
    selection = work + 0xCB4;
    slot = ((struct RecordFlagsByte *)(work + *selection * 8 + 0x5E0))->slot + 49;
    zero = 0;
    buffer[10] = slot;
    index = buffer[10];
    value = work[0xC94] & 15;
    offset = *selection * 8;
    address = (u32)work;
    address += 0x5DC;
    offset += address;
    sub_0805218C(index, value, (void *)offset);
    buffer[0] = zero;
    buffer[2] = work[0xC95];
    work[0xC89] = 1;
}

void sub_0804BE50(void)
{
    u8 *work = gUnknown_030057E0;
    u32 offset = work[0xCB4] * 8;
    u8 *row = work + offset;
    if ((*(u16 *)(row + 0x5DE) & 0xFFF) == *(u16 *)(work + 0xC8E))
    {
        u32 slot = (u8)(((struct RecordFlagsByte *)(row + 0x5E0))->slot + 49);
        u32 base = (u32)gContinuedLookup_083D262C;
        u32 lookupIndex = gFrameObjects[47].commandOffset;
        u32 value = *(const u8 *)(base + lookupIndex);
        u32 address = (u32)work;
        address += 0x5DC;
        address += offset;
        sub_0805218C(slot, value, (void *)address);
    }
}

void sub_0804BEC4(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *argument = work + 0xC94;
    u32 offset;
    u8 *row;
    *argument = value;
    offset = work[0xCB4] * 8;
    row = work + offset;
    if ((*(u16 *)(row + 0x5DE) & 0xFFF) == *(u16 *)(work + 0xC8E))
    {
        u32 slot = (u8)(((struct RecordFlagsByte *)(row + 0x5E0))->slot + 49);
        u32 parameter = *argument;
        u32 address = (u32)work;
        address += 0x5DC;
        address += offset;
        sub_0805218C(slot, parameter, (void *)address);
    }
}

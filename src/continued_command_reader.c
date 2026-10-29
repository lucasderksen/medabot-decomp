#include "continued_commands.h"
#include "global.h"

extern const void *gSetupPointer_03005590;
extern u8 gUnknown_030057E0[];

u32 sub_0804D83C(void)
{
    const u8 *source = gSetupPointer_03005590;
    u16 firstOffset, secondOffset, dataOffset;
    u32 first, second, selected, offset, bank, position, value;
    const u8 *table;
    u8 *work;
    u16 *cursor;
    firstOffset = (source[0] | source[1] << 8) - 0x4000;
    secondOffset = (source[2] | source[3] << 8) - 0x4000;
    work = gUnknown_030057E0;
    selected = *(u16 *)(work + 0xC8E);
    first = firstOffset + selected * 2;
    /* Native ROM bus traversal crosses the separate directory and script objects. */
    table = (const u8 *)((u32)source + 0x4000);
    dataOffset = *((const u8 *)((u32)table + first));
    first++;
    dataOffset = (dataOffset | *((const u8 *)((u32)table + first)) << 8) - 0x4000;
    offset = dataOffset;
    second = secondOffset + selected;
    bank = *((const u8 *)((u32)table + second));
    cursor = (u16 *)(work + 0xC8A);
    position = *cursor;
    offset += position;
    offset += bank << 14;
    source = (const u8 *)((u32)source + offset);
    value = *source;
    *cursor = position + 1;
    return value;
}

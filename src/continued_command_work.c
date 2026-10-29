#include "continued_commands.h"
#include "later_graphics.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D38[];
extern u8 gContinuedCommandWork_030064A0[];
extern u8 gContinuedArguments_03006474[];
extern void (*const gContinuedCommandCallbacks_083D222C[])(void);

void sub_0804D39C(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    *previous = snapshot;
    sub_0804D8CC(2);
    gLaterBuffer_03006D38[0] = work[0xC94];
    if ((s32)sub_08047F9C() > 2)
        work[0xC89] = 1;
    else
        *current = *previous + work[0xC95];
}

void sub_0804D438(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    u16 packed;
    *previous = snapshot;
    sub_0804D8CC(3);
    packed = sub_08047D9C(work[0xC94], work[0xC95]);
    if ((packed >> 8) == 0)
        *current = *previous + work[0xC96];
}

void sub_0804D4FC(void)
{
    u8 *buffer = gContinuedCommandWork_030064A0;
    u8 *count = buffer + 0x52;
    u32 zero = 0;
    u32 value;
    u8 *work;
    *count = zero;
    sub_08049714(buffer + 2, 8);
    sub_08049714(buffer + 0xA, 8);
    sub_08049714(buffer + 0x12, 0x40);
    sub_08049714(count, 1);
    sub_08049714(buffer + 0x53, 1);
    sub_08049714(buffer + 0x54, 8);
    value = sub_0804D83C();
    work = gUnknown_030057E0;
    work[0xC92] = value;
    work[0xC89] = zero;
    work[0xC93] = zero;
    gContinuedCommandCallbacks_083D222C[work[0xC92]]();
}

void sub_0804D580(void)
{
    u8 *arguments, *buffer, *selection;
    u8 index;
    u32 value, zero, offset;
    sub_0804D8CC(8);
    arguments = gContinuedArguments_03006474;
    buffer = gContinuedCommandWork_030064A0;
    index = buffer[0x52]++;
    offset = index * 8;
    buffer += 0x12;
    sub_080497C0(arguments, buffer + offset, 8);
    value = sub_0804D83C();
    selection = (u8 *)((u32)arguments - 2);
    zero = 0;
    *selection = value;
    *(u8 *)((u32)arguments - 11) = zero;
    *(u8 *)((u32)arguments - 1) = zero;
    gContinuedCommandCallbacks_083D222C[*selection]();
}

void sub_0804D778(void)
{
    u8 *buffer = gContinuedCommandWork_030064A0;
    buffer[0x52] = 0;
    sub_08049714(buffer + 2, 8);
    sub_08049714(buffer + 0xA, 8);
    sub_08049714(buffer + 0x12, 0x40);
}

void sub_0804D7AC(void)
{
    u8 *arguments, *buffer;
    u8 index;
    u32 offset;
    sub_0804D8CC(8);
    arguments = gContinuedArguments_03006474;
    buffer = gContinuedCommandWork_030064A0;
    index = buffer[0x52]++;
    offset = index * 8;
    buffer += 0x12;
    sub_080497C0(arguments, buffer + offset, 8);
}

void sub_0804D7F8(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u32 snapshot = *current;
    sub_0804D8CC(2);
    if (work[0xC76] == 0)
    {
        u32 high = work[0xC94] << 8;
        u32 value = work[0xC95];
        value |= high;
        *current = snapshot + value;
    }
}

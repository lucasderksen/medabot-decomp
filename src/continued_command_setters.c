#include "continued_commands.h"
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern u8 gLaterBuffer_03006D38[];
/* Copied word-slot interfaces remain provisional. */

void sub_0804D208(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0x7FF] = value;
}

void sub_0804D224(void)
{
    u8 *work, *argument;
    u32 selected, value, index;
    sub_0804D8CC(5);
    work = gUnknown_030057E0;
    argument = work + 0xC94;
    selected = *argument;
    value = (u8)sub_08050710();
    sub_0804DBD0(selected, value);
    index = sub_0804DBF0(*argument);
    gLaterBuffer_03006D20[10] = index + 79;
    work[0xC89] = 1;
}

void sub_0804D270(void)
{
    u8 *work;
    u32 index;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    index = sub_0804DBF0(work[0xC94]);
    gLaterBuffer_03006D20[10] = index + 79;
    work[0xC89] = 1;
}

void sub_0804D2A8(void)
{
    u8 *work, *argument;
    u32 selected, value, index;
    sub_0804D8CC(5);
    work = gUnknown_030057E0;
    argument = work + 0xC94;
    selected = *argument;
    value = (u8)sub_08050710();
    sub_0804DBD0(selected, value);
    index = sub_0804DBF0(*argument);
    gLaterBuffer_03006D20[10] = index + 79;
    work[0xC89] = 1;
}

void sub_0804D2F4(void)
{
    u8 *work;
    u32 index;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    index = sub_0804DBF0(work[0xC94]);
    gLaterBuffer_03006D20[10] = index + 79;
    work[0xC89] = 1;
}

void sub_0804D32C(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D340(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D354(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D368(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D37C(void)
{

}

void sub_0804D380(void)
{

}

void sub_0804D384(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D398(void)
{

}

void sub_0804D400(void)
{
    u32 value = sub_0804D83C();
    gLaterBuffer_03006D38[1] = value;
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D424(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D48C(void)
{

}

void sub_0804D490(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC32] = value;
}

void sub_0804D4AC(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    work[0xC89] = 1;
}

void sub_0804D4D4(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    work[0xC89] = 1;
}

void sub_0804D5DC(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D758(void)
{
    sub_0804D8CC(1);
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804D7E4(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

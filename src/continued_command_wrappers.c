#include "continued_commands.h"
extern u8 gUnknown_030057E0[];
extern void sub_0804D980(void *record);
extern void sub_08053168(u32 value);
extern void sub_080531A0(u32 value);
extern void sub_08053238(u32 value, u32 field);
extern void sub_08053280(u32 value);

void sub_0804BAEC(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    work[0xC89] = 1;
}
void sub_0804BBA0(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    work[0xC89] = 1;
}
void sub_0804BBC8(void)
{
    u8 *work;
    u32 high, value;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    high = work[0xC94] << 8;
    value = work[0xC95];
    value |= high;
    sub_08053168(value);
}
void sub_0804BBF4(void)
{
    u8 *work;
    u32 high, value;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    high = work[0xC94] << 8;
    value = work[0xC95];
    value |= high;
    sub_080531A0(value);
}
void sub_0804BCD4(void)
{
    u8 *work;
    u32 high, value;
    void *record;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    high = work[0xC94] << 8;
    value = work[0xC95];
    value |= high;
    record = sub_0804D938(value);
    if (record)
        sub_0804D980(record);
}
void sub_0804BD08(void)
{
    u8 *work;
    u32 high, value;
    sub_0804D8CC(3);
    work = gUnknown_030057E0;
    high = work[0xC94] << 8;
    value = work[0xC95];
    value |= high;
    sub_08053238(value, work[0xC96] & 7);
}
void sub_0804BD44(void)
{
    u8 *work;
    u32 high, value;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    high = work[0xC94] << 8;
    value = work[0xC95];
    value |= high;
    sub_08053280(value);
}



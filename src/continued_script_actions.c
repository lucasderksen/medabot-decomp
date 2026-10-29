#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "packed_fields.h"
#include "later_graphics.h"
#include "post_dispatch.h"
#include "utility_helpers.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern void sub_08052E58(u32 first, u32 second, u32 mode);

void sub_0804CD84(void)
{
    sub_0804D8CC(1);
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804CDA4(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *argument = work + 0xC94;
    u8 *objects;
    *argument = value;
    objects = (u8 *)gFrameObjects;
    objects[48 * 64 + 0x21] = value;
    objects[48 * 64 + 0x20] = value;
    value += objects[48 * 64 + 0x2B] * 4;
    { u32 mapped = sub_08050300(48, (u8)value); sub_08049420(48, (u8)mapped); }
    sub_08052E34(*argument);
}

void sub_0804CE04(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *position = (u16 *)(work + 0xC8A);
    u32 previous = *position;
    u16 *saved = (u16 *)(work + 0xC8C);
    *saved = previous;
    sub_0804D8CC(1);
    if ((s32)sub_08047F9C() <= 2)
        *position = *saved + work[0xC95];
}

void sub_0804CE44(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *position = (u16 *)(work + 0xC8A);
    u32 previous = *position;
    u16 *saved = (u16 *)(work + 0xC8C);
    *saved = previous;
    sub_0804D8CC(2);
    if (sub_08047FBC(work[0xC94]) == 0)
        *position = *saved + work[0xC95];
}

void sub_0804CEF8(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    if ((u8)value == 1)
        work[0xC5D] = (work[0xC5D] & 0xFE) | 1;
    else
        work[0xC5D] &= 0xFE;
}

void sub_0804CF40(void)
{
    u32 value = sub_0804D83C();
    gUnknown_030057E0[0xC2C] = value;
}

void sub_0804D00C(void) { sub_0804DB80(); }

void sub_0804D018(void) { sub_08044B58(); }

void sub_0804D084(void) { sub_08050C94(); }

void sub_0804D090(void) { }

void sub_0804D204(void) { }

void sub_0804D0E0(void)
{
    sub_0804D8CC(2);
    gUnknown_030057E0[0xC89] = 1;
}

#include "continued_commands.h"
#include "frame.h"
#include "background_state.h"
#include "continued_blend_work.h"
#include "fresh_helpers.h"
#include "palette_transfer_helpers.h"
#include "post_dispatch.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];

void sub_0804C9D4(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    *previous = snapshot;
    sub_0804D8CC(2);
    if (work[0xC94] != gFrameObjects[47].commandOffset)
        *current = *previous + work[0xC95];
}

void sub_0804CA28(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    s32 result;
    *previous = snapshot;
    sub_0804D8CC(3);
    result = sub_08047D8C(work[0xC94]);
    if (result == 0 || result < work[0xC95])
        *current = *previous + work[0xC96];
}

void sub_0804CA84(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    s32 result;
    *previous = snapshot;
    sub_0804D8CC(3);
    result = sub_08047E50(work[0xC94], work[0xC95]);
    if (result != -1)
        work[0xC60] = result;
    else
        *current = *previous + work[0xC96];
}

void sub_0804CAE8(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    *previous = snapshot;
    sub_0804D8CC(2);
    if (sub_08047DB0(work[0xC94]) == 0)
        *current = *previous + work[0xC95];
}

void sub_0804CB34(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    s32 result, limit;
    u32 high;
    *previous = snapshot;
    sub_0804D8CC(3);
    result = sub_08047D4C();
    high = work[0xC94] << 8;
    high |= work[0xC95];
    limit = high * 10;
    if (result < limit)
        *current = *previous + work[0xC96];
}

void sub_0804CC5C(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    *previous = snapshot;
    sub_0804D8CC(2);
    if (work[0xC94] - 70 != work[0xC60])
        *current = *previous + work[0xC95];
}

void sub_0804CCAC(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    u32 result, mask;
    *previous = snapshot;
    sub_0804D8CC(2);
    result = sub_08049780(255);
    mask = 15;
    mask &= result;
    if (mask)
        *current = *previous + work[0xC96];
}

void sub_0804CCF4(void)
{
    u8 *work, *selection;
    u32 address;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    selection = work + 0xC94;
    if (*selection)
        --*selection;
    address = (u32)work;
    address += 0xC38;
    address += *selection;
    *(u8 *)address = work[0xC95];
    sub_08048288();
    switch (gContinuedBlendWork_03006F40.mode)
    {
    case 1:
    case 3:
    case 5:
    case 6:
        sub_080486B0();
        break;
    default:
        sub_08048708();
    }
}

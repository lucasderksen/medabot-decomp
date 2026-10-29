#include "continued_commands.h"
#include "bg_scroll.h"
#include "frame.h"
#include "fresh_helpers.h"

extern u8 gUnknown_030057E0[];

void sub_08052A78(s32 amountWord)
{
    s32 value = gBgScroll1.x;
    s32 amount = (s16)amountWord;
    gBgScroll1.x = amount + value;
    value = gBgScroll2.x;
    gBgScroll2.x = amount + value;
    amount = amount + gBgScroll3.x;
    gBgScroll3.x = amount;
}


void sub_08052AA4(void)
{
    u8 *work = gUnknown_030057E0;
    s32 x = work[0xC56] - 7;
    s32 y;
    if (x < 0)
        x = 0;
    if (x + 15 > (sub_080529AC(work[0x7FE], 0) >> 1))
    {
        x = sub_080529AC(work[0x7FE], 0) >> 1;
        x -= 15;
        if (sub_08052A50())
            x = 0;
    }
    {
        u8 *next = gUnknown_030057E0;
        y = next[0xC57] - 4;
        if (y <= 0)
            y = 0;
        if (y + 10 > (sub_080529AC(next[0x7FE], 1) >> 1))
        {
            y = sub_080529AC(next[0x7FE], 1) >> 1;
            y -= 10;
            if (sub_08052A64())
                y = 0;
        }
    }
    sub_08052A10((u16)(x * 16));
    sub_08052A30((u16)(y * 16));
}


void sub_08052B44(s32 amountWord)
{
    s32 value = gBgScroll1.y;
    s32 amount = (s16)amountWord;
    gBgScroll1.y = amount + value;
    value = gBgScroll2.y;
    gBgScroll2.y = amount + value;
    amount = amount + gBgScroll3.y;
    gBgScroll3.y = amount;
}


void sub_08052B70(void)
{
    u8 *objects = (u8 *)gFrameObjects;
    u8 *work = gUnknown_030057E0;
    u16 *position = (u16 *)(work + 0xC52);
    struct BgScroll *scroll = &gBgScroll1;
    u32 x = *position - scroll->x;
    u32 y;
    *(u16 *)(objects + 0xBC2) = x;
    y = *(u16 *)(work + 0xC54) - scroll->y;
    *(u16 *)(objects + 0xBC4) = y;
    *(u16 *)(objects + 0x1642) = x;
    y -= 5;
    *(u16 *)(objects + 0x1644) = y;
}


void sub_08052BEC(u32 valueWord)
{
    u8 value = valueWord;
    if (value)
    {
        struct FrameObject *objects = gFrameObjects;
        objects[47].flags = 0xC804;
        objects[89].flags = 0xCC0C;
    }
    else
    {
        struct FrameObject *objects = gFrameObjects;
        objects[47].flags = 0;
        objects[89].flags = 0;
    }
}


void sub_08052C30(void)
{
    u8 *work = gUnknown_030057E0;
    if (work[0xC5C] == 1 && !sub_08048088(0))
    {
        work[0xC5C] = work[0xC69];
        sub_08051E38(1);
    }
}

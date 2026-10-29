#include "continued_commands.h"
#include "global.h"
#include "frame.h"
#include "bg_scroll.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];

u32 sub_0804F188(u32 input)
{
    u8 selector = input;
    u32 result;
    switch (selector)
    {
    case 0:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC54);
            s32 position = *current;
            const u16 *origin = (u16 *)(work + 0xC4A);
            if (position == *origin)
                break;
            *current -= sub_08051940(47);
            if (sub_08052A64())
                break;
            if (*current - *origin >= *(u16 *)(work + 0x802) * 8 - 96)
                break;
            if ((s16)gBgScroll1.y == 0)
                break;
            sub_08052B44((s16)-sub_08051940(47));
            gFrameObjects[0].screenY += sub_08051940(47);
            break;
        }
    case 1:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC54);
            s32 position = *current;
            const u16 *origin = (u16 *)(work + 0xC4A);
            s32 difference = position - *origin + 16;
            const u16 *height = (u16 *)(work + 0x802);
            if (difference >= *height * 8)
                break;
            *current += sub_08051940(47);
            if (sub_08052A64())
                break;
            if (*current - *origin + 16 <= 80)
                break;
            if ((s16)gBgScroll1.y + 160 >= *height * 8)
                break;
            sub_08052B44((s16)sub_08051940(47));
            gFrameObjects[0].screenY -= sub_08051940(47);
            break;
        }
    case 2:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC52);
            s32 position = *current;
            const u16 *origin = (u16 *)(work + 0xC48);
            if (position == *origin)
                break;
            *current -= sub_08051940(47);
            if (sub_08052A50())
                break;
            if (*current - *origin >= *(u16 *)(work + 0x800) * 8 - 128)
                break;
            if ((s16)gBgScroll1.x == 0)
                break;
            sub_08052A78((s16)-sub_08051940(47));
            gFrameObjects[0].screenX += sub_08051940(47);
            break;
        }
    case 3:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC52);
            s32 position = *current;
            const u16 *origin = (u16 *)(work + 0xC48);
            s32 difference = position - *origin + 16;
            const u16 *width = (u16 *)(work + 0x800);
            if (difference >= *width * 8)
                break;
            *current += sub_08051940(47);
            if (sub_08052A50())
                break;
            if (*current - *origin + 16 <= 128)
                break;
            if ((s16)gBgScroll1.x + 240 >= *width * 8)
                break;
            sub_08052A78((s16)sub_08051940(47));
            gFrameObjects[0].screenX -= sub_08051940(47);
            break;
        }
    }
    gLaterBuffer_03006D20[0]--;
    result = 0;
    if (!gLaterBuffer_03006D20[0])
    {
        u8 *work = gUnknown_030057E0;
        work[0xC56] = sub_0805273C(*(u16 *)(work + 0xC52));
        work[0xC57] = sub_08052760(*(u16 *)(work + 0xC54));
        result = 1;
    }
    return result;
}

#include "continued_commands.h"
#include "frame.h"
#include "later_graphics.h"
#include "continued_graphics.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D38[];

void sub_08051988(u32 input)
{
    u8 mode = input;
    switch (mode)
    {
    case 0:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC54);
            s32 position = *current;
            u16 *origin = (u16 *)(work + 0xC4A);
            if (position != *origin)
            {
                *current -= sub_08051940(47);
                sub_08050168(47);
                if (!sub_08052A64())
                    if (*current - *origin < *(u16 *)(work + 0x802) * 8 - 96)
                        if ((s16)gBgScroll1.y != 0)
                            sub_08052B44((s16)-sub_08051940(47));
            }
        }
        break;
    case 1:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC54);
            s32 position = *current;
            u16 *origin = (u16 *)(work + 0xC4A);
            s32 delta = position - *origin + 16;
            u16 *height = (u16 *)(work + 0x802);
            if (delta < *height * 8)
            {
                *current += sub_08051940(47);
                sub_08050168(47);
                if (!sub_08052A64())
                    if (*current - *origin + 16 > 80)
                        if ((s16)gBgScroll1.y + 160 < *height * 8)
                            sub_08052B44((s16)sub_08051940(47));
            }
        }
        break;
    case 2:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC52);
            s32 position = *current;
            u16 *origin = (u16 *)(work + 0xC48);
            if (position != *origin)
            {
                *current -= sub_08051940(47);
                sub_08050168(47);
                if (!sub_08052A50())
                    if (*current - *origin < *(u16 *)(work + 0x800) * 8 - 128)
                        if ((s16)gBgScroll1.x != 0)
                            sub_08052A78((s16)-sub_08051940(47));
            }
        }
        break;
    case 3:
        {
            u8 *work = gUnknown_030057E0;
            u16 *current = (u16 *)(work + 0xC52);
            s32 position = *current;
            u16 *origin = (u16 *)(work + 0xC48);
            s32 delta = position - *origin + 16;
            u16 *width = (u16 *)(work + 0x800);
            if (delta < *width * 8)
            {
                *current += sub_08051940(47);
                sub_08050168(47);
                if (!sub_08052A50())
                    if (*current - *origin + 16 > 128)
                        if ((s16)gBgScroll1.x + 240 < *width * 8)
                            sub_08052A78((s16)sub_08051940(47));
            }
        }
        break;
    }
    {
        u8 *work = gUnknown_030057E0;
        if (!(u8)--work[0xC58])
        {
            u8 *objects = (u8 *)gFrameObjects;
            const u8 *lookup = gFrameByteLookup_083D2A88;
            u8 *selected = work + 0xC5C;
            u32 value = lookup[*selected];
            u8 *x;
            u8 *y;
            objects[47 * 64 + 0x2A] = value;
            value = sub_0805273C(*(u16 *)(work + 0xC52));
            x = work + 0xC56;
            *x = value;
            value = sub_08052760(*(u16 *)(work + 0xC54));
            y = work + 0xC57;
            *y = value;
            if (!work[0xC88] && !sub_08052400())
            {
                if (sub_08052C68(*x, *y))
                {
                    gBackgroundState_03005310.unknown00[1] = 3;
                    if (gLaterBuffer_03006D38[3])
                        sub_08047BA8(gSetupByteLookup_083D2B66[gLaterBuffer_03006D38[3]]);
                    sub_08049D90(0x7FFF, 0.0f, 32.0f, 8.0f);
                }
                else if (*selected != 1 && sub_080438C4())
                {
                    sub_080505FC();
                    sub_08047878(33, 0);
                }
            }
        }
    }
}

#include "continued_commands.h"
#include "continued_callbacks.h"
#include "continued_map.h"
#include "frame.h"
#include "background_state.h"
#include "later_graphics.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u32 gUnknown_0300137C;
extern void sub_0804B1B0(void);

void sub_0804AC14(void)
{
    s32 divisor = sub_08051940(47);
    u8 *work = gUnknown_030057E0;
    u8 *objects;
    u8 *first;
    s32 quotient = 16 / divisor;
    work[0xC58] = quotient;
    objects = (u8 *)gFrameObjects;
    first = objects + 47 * 64 + 0x20;
    sub_08052E0C(*first);
    sub_08049420(47, *first);
    if (work[0xC76])
    {
        u16 value = *(u16 *)(work + 0xC52);
        *(u16 *)(work + 0xC6E) = value;
        value = *(u16 *)(work + 0xC54);
        *(u16 *)(work + 0xC70) = value;
        sub_08052E34(*first);
        sub_08049420(48, (u8)(objects[48 * 64 + 0x2B] * 4 + objects[48 * 64 + 0x20]));
    }
    sub_08051EFC(1);
    sub_08047BA8(87);
    gBackgroundState_03005310.unknown00[1] = 1;
    gUnknown_0300137C = 5;
}

void sub_0804ADB4(void)
{
    if (sub_0804B6E0())
    {
        u8 *work = gUnknown_030057E0;
        u8 *selected;
        u8 *objects;
        u32 zero;
        u32 previous = work[0xC69];
        u32 selectedOffset = 0xC5C;
        u8 *stored = work + selectedOffset;
        zero = 0;
        *stored = previous;
        sub_08051E38(0);
        selected = work + 0xC67;
        *selected = 1;
        gBackgroundState_03005310.unknown00[1] = zero;
        sub_080517F0();
        sub_08052B70();
        sub_08052E0C(*selected);
        if (work[0xC76])
        {
            u16 value = *(u16 *)(work + 0xC52);
            *(u16 *)(work + 0xC6E) = value;
            value = *(u16 *)(work + 0xC54);
            *(u16 *)(work + 0xC70) = value;
            objects = (u8 *)gFrameObjects;
            sub_08052E34(objects[47 * 64 + 0x20]);
            sub_08049420(48, (u8)(objects[48 * 64 + 0x2B] * 4 + objects[48 * 64 + 0x20]));
        }
        sub_0804B1B0();
        gUnknown_0300137C = 5;
    }
}

void sub_0804AEC8(void)
{
    if (sub_0804B6E0())
    {
        u8 *work = gUnknown_030057E0;
        u8 *selected;
        u8 *objects;
        u32 zero;
        u32 previous = work[0xC69];
        u32 selectedOffset = 0xC5C;
        u8 *stored = work + selectedOffset;
        zero = 0;
        *stored = previous;
        sub_08051E38(0);
        selected = work + 0xC67;
        *selected = 1;
        gBackgroundState_03005310.unknown00[1] = zero;
        sub_080517F0();
        sub_08052B70();
        sub_08052E0C(*selected);
        if (work[0xC76])
        {
            u16 value = *(u16 *)(work + 0xC52);
            *(u16 *)(work + 0xC6E) = value;
            value = *(u16 *)(work + 0xC54);
            *(u16 *)(work + 0xC70) = value;
            objects = (u8 *)gFrameObjects;
            sub_08052E34(objects[47 * 64 + 0x20]);
            sub_08049420(48, (u8)(objects[48 * 64 + 0x2B] * 4 + objects[48 * 64 + 0x20]));
        }
        sub_0804B1B0();
        gUnknown_0300137C = 5;
    }
}

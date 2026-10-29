

#include "global.h"
#include "main.h"
#include "state0_work.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "object_helpers.h"
#include "bg_scroll.h"
extern u32 gMainSubstate;
extern u32 gUnknown_0300137C;
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03005310[];
extern u8 gLaterBuffer_030064A0[];
extern const void *const gPostDispatchPointers_083BA658[];
extern u32 gPostDispatchWord_03002B70;
extern void sub_08074DE0(u32);
extern void sub_08074B88(u32);
extern void sub_080750F0(u32);
extern u32 sub_08041D70(u8);
extern void sub_080422B8(u32, u32);
extern u32 sub_08042238(u32);

void sub_0804765C(u32 mode)
{
    switch (mode)
    {
    case 0:
        gLaterBuffer_03005310[0x39] = gState0TypedWork.bytes[0x9C];
        if (gUnknown_030057E0[0xC88])
        {
            gMainState = 1;
            gMainSubstate = 1;
            gUnknown_0300137C = 5;
        }
        else
        {
            gMainState = 1;
            gMainSubstate = 1;
            gUnknown_0300137C = 13;
        }
        break;
    case 1:
        gMainState = mode;
        gMainSubstate = 2;
        gUnknown_0300137C = 0;
        break;
    }
}

void sub_08047850(s32 mode)
{
    switch (mode)
    {
    case 0: case 1: case 2: case 3:
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 5;
        break;
    }
}

void sub_08047BA8(u32 value) { sub_08074DE0(value); }

void sub_08047BB4(u32 value) { sub_08074B88(value); }

void sub_08047BC0(u32 value) { sub_080750F0(value); }

const void *sub_08047BCC(u32 index) { return gUnknownPointers_083B6590[index]; }

const void *sub_08047BDC(u32 index) { return gPostDispatchPointers_083BA658[index]; }

const void *sub_08047BEC(u32 index, u32 row) { return gPartTextPointers_083BBB4C[row * 4 + index]; }

u32 sub_08047D4C(void) { return gPostDispatchWord_03002B70; }

void sub_08047D58(u32 amount)
{
    gPostDispatchWord_03002B70 += amount;
    if (gPostDispatchWord_03002B70 > 99999)
        gPostDispatchWord_03002B70 = 99999;
}

void sub_08047D74(u32 amount)
{
    s32 value = gPostDispatchWord_03002B70 - amount;
    if (value < 0)
        gPostDispatchWord_03002B70 = 0;
    else
        gPostDispatchWord_03002B70 = value;
}

u32 sub_08047D8C(u8 value) { return sub_08042278(value); }

u32 sub_08047D9C(u8 index, u8 row) { return sub_08042114(index, row); }

u32 sub_08047DB0(u8 identifier) { return sub_08041D3C(identifier); }

void sub_08047DC0(u8 index, u8 amount)
{
    if (amount == 0) amount = 1;
    sub_080422B8(index, amount);
}

void sub_08047DD8(u8 index, u8 amount)
{
    if (amount == 0) amount = 1;
    sub_08042318(index, amount);
}

void sub_08047DF0(u8 index, u8 row, u8 amount) { sub_0804213C(index, row, amount); }

void sub_08047E08(u8 index, u8 row, u8 amount) { sub_08042170(index, row, amount); }

u32 sub_08047E20(u8 identifier) { return sub_08041D70(identifier); }

u32 sub_08047E30(void) { return sub_08042218(); }

void sub_08047E3C(u8 value) { sub_08042238(value); }

void sub_08047E4C(void) {}

u32 sub_08047F9C(void)
{
    u32 count = 0;
    s32 i;
    for (i = 0; i <= 8; i++)
        if (gUnknownRecords_030017A0[i].unknown00[0] == 3) count++;
    return count;
}


#include "global.h"
#include "state0_work.h"
#include "bg_scroll.h"
#include "effect_work.h"
#include "display_effects.h"

#include "post_dispatch.h"
extern const struct PostDispatchTextBuffers gPostDispatchTextBuffers_080ABD6C;
extern u8 gLaterBuffer_030064A0[];
extern void sub_08047E4C(void);
extern s32 sub_080488AC(s32 value);
extern u32 sub_080488E8(s32 value, u8 digit);
extern void sub_080497C0(const void *, void *, u32);
extern void sub_0804126C(u8 *destination, u32 value);

void sub_08047C00(void)
{
    sub_08047E4C();
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    gLaterBuffer_030064A0[0] = 0;
    gLaterBuffer_030064A0[1] = 0;
}

u32 sub_08047C24(u8 first, u8 second, u8 mode, const void *script)
{
    u32 done = 0;
    u8 *work = gLaterBuffer_030064A0;
    switch (work[0])
    {
    case 0:
        if (work[1] == 0)
            sub_0803FAA0(first, second, mode);
        else
            sub_0803FB0C();
        gLaterBuffer_030064A0[0]++;
        break;
    case 1:
        if (sub_0803FB3C(script))
        {
            work[0] = 0;
            work[1]++;
            done = 1;
        }
        break;
    }
    return done;
}

void sub_08047C84(u32 index, s32 value)
{
    u8 digits[10];
    struct PostDispatchTextBuffers buffers = gPostDispatchTextBuffers_080ABD6C;
    u8 *destination = buffers.items[index];
    s32 count = sub_080488AC(value);
    s32 i;
    for (i = 0; i < count; i++)
        digits[i] = sub_080488E8(value, count - 1 - i) + 53;
    sub_080497C0(digits, destination, count);
    destination[count] = 0xFE;
}

void sub_08047CE4(u32 index, const u8 *source)
{
    struct PostDispatchTextBuffers buffers = gPostDispatchTextBuffers_080ABD6C;
    u8 *destination = buffers.items[index];
    s32 i;
    for (i = 0; i <= 15; i++)
    {
        if (*source == 0xFE) break;
        *destination++ = *source++;
    }
    *destination = 0xFE;
}

void sub_08047D24(u32 index, u32 value)
{
    u8 digits[10];
    struct PostDispatchTextBuffers buffers = gPostDispatchTextBuffers_080ABD6C;
    sub_0804126C(buffers.items[index], value);
}

u32 sub_08047EF0(u8 value, u8 part)
{
    u32 found = 0;
    s32 i = 0;
    struct State0Record8 *record = gUnknownRecords_030017A0;
    for (; i <= 8; i++)
    {
        if (record->unknown00[0] == 3)
        {
            switch (part)
            {
            case 0: if (record->byte3 == value) found = 1; break;
            case 1: if (record->byte4 == value) found = 1; break;
            case 2: if (record->byte5 == value) found = 1; break;
            case 3: if (record->byte6 == value) found = 1; break;
            }
        }
        if (found) break;
        record++;
    }
    return found;
}

s32 sub_08047F50(u8 value)
{
    u32 found = 0;
    s32 i = 0;
    struct State0Record8 *record = gUnknownRecords_030017A0;
    for (; i <= 8; i++)
    {
        if (record->unknown00[0] == 3 && record->byte3 == value && record->byte4 == value && record->byte5 == value && record->byte6 == value)
            found = 1;
        if (found) break;
        record++;
    }
    if (!found) return -1;
    return i;
}

u32 sub_08047FBC(u8 value)
{
    u32 found = 0;
    s32 i = 0;
    struct State0Record8 *record = gUnknownRecords_030017A0;
    for (; i <= 8; i++)
    {
        if (record->unknown00[0] == 3 && record->byte3 == value && record->byte4 == value && record->byte5 == value && record->byte6 == value)
            found = 1;
        if (found) break;
        record++;
    }
    return found;
}


#include "post_dispatch.h"
#include "state0_work.h"
#include "tile_text.h"
extern u8 gLaterBuffer_03006D38[];
s32 sub_08047E50(u8 value, u8 part)
{
    u8 metadata[16];
    u32 exists = sub_08047EF0(value, part);
    s32 result;
    if (exists)
    {
        u32 found = 0;
        s32 i = 0;
        struct State0Record8 *base = gUnknownRecords_030017A0;
        struct State0Record8 *record = base;
        for (; i <= 8; i++)
        {
            if (record->unknown00[0] == 3)
            {
                switch (part)
                {
                case 0: if (record->byte3 == value) found = 1; break;
                case 1: if (record->byte4 == value) found = 1; break;
                case 2: if (record->byte5 == value) found = 1; break;
                case 3: if (record->byte6 == value) found = 1; break;
                }
            }
            if (found) break;
            record++;
        }
        {
            u32 address = i * 8;
            struct State0Record8 *matched;
            address += (u32)base;
            matched = (struct State0Record8 *)address;
            sub_08042B58(matched->byte6, 3, metadata);
            result = metadata[1] - 100;
            gLaterBuffer_03006D38[6] = matched->unknown00[1];
        }
    }
    if (exists) return result;
    return -1;
}

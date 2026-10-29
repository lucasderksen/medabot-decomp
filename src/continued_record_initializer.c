#include "continued_commands.h"
#include "global.h"
#include "frame.h"
#include "bg_scroll.h"
#include "object_numeric_helpers.h"
#include "packed_fields.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];

struct PackedPosition
{
    u32 low : 8;
    s32 whole : 24;
};

void sub_0804D9F8(u32 index)
{
    u8 selected = index;
    u8 *objects;
    u8 *entries;
    u8 *work;
    u16 *x, *y, *storedX, *storedY;
    u8 *part;
    u32 one, value, offset;
    sub_08048888(48);
    sub_08048888(90);
    offset = selected * 64;
    objects = (u8 *)gFrameObjects;
    sub_080497C0(objects + offset, objects + 48 * 64, 64);
    offset = selected * 4;
    entries = gLaterBuffer_030055A0;
    sub_080497C0(entries + offset, entries + 48 * 4, 4);
    work = gUnknown_030057E0;
    {
        u8 *mode = work + 0xC76;
        one = 1;
        *mode = one;
    }
    x = (u16 *)(objects + 48 * 64 + 2);
    {
        u16 coordinate = *x;
        coordinate += gBgScroll1.x;
        storedX = (u16 *)(work + 0xC6E);
        *storedX = coordinate;
    }
    y = (u16 *)(objects + 48 * 64 + 4);
    {
        u16 coordinate = *y;
        coordinate += gBgScroll1.y;
        storedY = (u16 *)(work + 0xC70);
        *storedY = coordinate;
    }
    work[0xC72] = sub_0805273C(*storedX);
    work[0xC73] = sub_08052760(*storedY);
    part = objects + 48 * 64 + 0x2B;
    value = *part;
    work[0xC84] = value;
    sub_08051ED8();
    value = (u8)(*part * 4 + objects[48 * 64 + 0x21]);
    value = sub_08050300(48, value);
    sub_08049420(48, (u8)value);
    sub_08048864(90, 0xCC0C, 0x90, 14, one);
    {
        u16 coordinate = *x;
        *(u16 *)(objects + 90 * 64 + 2) = coordinate;
    }
    {
        u16 coordinate = *y;
        coordinate -= 5;
        *(u16 *)(objects + 90 * 64 + 4) = coordinate;
    }
    {
        s32 whole = *(s32 *)(objects + 48 * 64 + 0xC) >> 8;
        ((struct PackedPosition *)(objects + 90 * 64 + 0xC))->whole = whole;
    }
    {
        s32 whole = *(s32 *)(objects + 48 * 64 + 0x10) >> 8;
        whole -= 5;
        ((struct PackedPosition *)(objects + 90 * 64 + 0x10))->whole = whole;
    }
    sub_08051EFC(1);
    {
        u8 *current = work + 0xC5D;
        u32 previousValue = *current;
        u8 *previous = work + 0xC5E;
        *previous = previousValue;
        *current = 0xDF;
    }
}

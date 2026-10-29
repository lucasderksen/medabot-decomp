#include "continued_commands.h"
#include "frame.h"
#include "packed_fields.h"
#include "object_numeric_helpers.h"
#include "palette_transfer_helpers.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];

/* Private observed access view; original declarations are unknown. */
union PairCoordinate
{
    u32 value;
    struct { u32 fraction : 8; s32 integer : 24; } parts;
};
struct PairArrayView
{
    u8 unknown000[0xC00];
    u16 primaryFlags;
    u16 primaryScreenX, primaryScreenY;
    u8 unknownC06[5];
    u8 primaryPriority;
    u8 unknownC0C[0x1F];
    u8 primaryByte2B;
    u8 unknownC2C[4];
    u16 primaryHalf30;
    u8 unknownC32[0xA4E];
    u16 secondaryFlags;
    u16 secondaryScreenX, secondaryScreenY;
    u8 unknown1686[6];
    union PairCoordinate secondaryX, secondaryY;
};

void sub_08052F64(void)
{
    u8 *work = gUnknown_030057E0;
    if (work[0xC76])
    {
        u32 flags = 0xC804;
        u8 *palette = work + 0xC84;
        u32 paletteValue = *palette;
        u32 selected = paletteValue * 12;
        u8 *frame = work + 0xC83;
        u32 enabled;
        struct PairArrayView *objects;
        u16 *x, *y;
        selected += *frame;
        enabled = 1;
        sub_08048864(48, flags, selected, paletteValue, enabled);
        objects = (struct PairArrayView *)gFrameObjects;
        objects->primaryPriority = 0x40;
        objects->primaryByte2B = *palette;
        sub_08052E34(*frame);
        sub_08049420(48, (u8)sub_08050300(48, *frame));
        x = (u16 *)(work + 0xC6E);
        work[0xC72] = sub_0805273C(*x);
        y = (u16 *)(work + 0xC70);
        work[0xC73] = sub_08052760(*y);
        objects->primaryHalf30 = sub_08048684(objects->primaryByte2B);
        sub_080487C8(48);
        sub_08048864(90, 0xCC0C, 144, 14, enabled);
        objects->secondaryX.parts.integer = *x;
        objects->secondaryY.parts.integer = *y - 5;
        objects->secondaryScreenX = objects->primaryScreenX;
        objects->secondaryScreenY = objects->primaryScreenY - 5;
    }
}

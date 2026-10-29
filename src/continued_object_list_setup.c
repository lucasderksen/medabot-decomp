#include "compression.h"
#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "object_numeric_helpers.h"

extern u8 gUnknown_030057E0[];

union SetupCoordinate
{
    u32 value;
    struct { u32 fraction : 8; s32 integer : 24; } parts;
};
struct SetupArrayView
{
    u8 unknown000[0xBC0];
    u16 primaryFlags;
    u16 primaryScreenX, primaryScreenY;
    u8 unknownBC6[5];
    u8 primaryPriority;
    u8 unknownBCC[0xA74];
    u16 secondaryFlags;
    u16 secondaryScreenX, secondaryScreenY;
    u8 unknown1646[6];
    union SetupCoordinate secondaryX, secondaryY;
};

void sub_080517F0(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *x, *y;
    u32 flags;
    u32 enabled;
    struct SetupArrayView *objects;
    work[0xC58] = 0;
    { u8 value = work[0xC5C]; work[0xC28] = value; }
    sub_0805330C();
    x = (u16 *)(work + 0xC52);
    work[0xC56] = sub_0805273C(*x);
    y = (u16 *)(work + 0xC54);
    work[0xC57] = sub_08052760(*y);
    flags = 0xC804;
    enabled = 1;
    sub_08048864(47, flags, 3, 0, enabled);
    sub_08052E0C(work[0xC67]);
    sub_08051EFC(3);
    objects = (struct SetupArrayView *)gFrameObjects;
    objects->primaryPriority = 0x40;
    LZ77UnCompVram(gSetupCompressed_085FB6A4, (void *)0x06017FC0);
    sub_08048864(89, 0xCC0C, 144, 14, enabled);
    objects->secondaryX.parts.integer = *x;
    objects->secondaryY.parts.integer = *y - 5;
    objects->secondaryScreenX = objects->primaryScreenX;
    objects->secondaryScreenY = objects->primaryScreenY - 5;
    if (work[0xC5B])
        objects->primaryFlags = flags;
    else
    {
        objects->primaryFlags = 0;
        objects->secondaryFlags = 0;
    }
}

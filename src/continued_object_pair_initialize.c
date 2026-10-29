#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "object_numeric_helpers.h"
#include "palette_transfer_helpers.h"
#include "packed_fields.h"
#include "bitfields.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];

union InitialCoordinate
{
    s32 value;
    struct { u32 fraction:8; s32 integer:24; } parts;
};

struct InitialFrameView
{
    u8 unknown00[0x0C];
    union InitialCoordinate x;
    union InitialCoordinate y;
    u8 unknown14[0x0C];
    u8 direction;
    u8 unknown21[0x0A];
    u8 selector;
    u8 unknown2C;
    u8 unknown2D[3];
    u16 condition;
    u8 unknown32[14];
};

struct InitialMetadata
{
    u16 value;
    u16 unknown02;
};

void sub_080503FC(u32 indexWord, u32 selectorWord, u32 xWord, u32 yWord)
{
    u8 index = indexWord;
    u8 selector = selectorWord;
    u8 x = xWord;
    u8 y = yWord;
    u32 primary = index + 79;
    u8 primaryByte = primary;
    u8 frame;
    u8 palette;
    sub_08048888(primaryByte);
    frame = sub_080502C8(selector);
    palette = ExtractHighNibble(selector);
    sub_08048864(primaryByte, 0xC804, frame, palette, 1);
    {
        u32 tag = ExtractHighNibble(selector);
        struct InitialFrameView *objects = (struct InitialFrameView *)gFrameObjects;
        struct InitialFrameView *object = &objects[primary];
        u8 *selectorByte = &object->selector;
        struct InitialMetadata *metadata;
        u32 zero = 0;
        s32 condition;
        *selectorByte = tag;
        object->direction = ExtractLowTwoBits(selector);
        {
            u8 *work = gUnknown_030057E0;
            object->x.parts.integer = (x << 4) + *(u16 *)(work + 0xC48);
            object->y.parts.integer = (y << 4) + *(u16 *)(work + 0xC4A);
        }
        metadata = (struct InitialMetadata *)gLaterBuffer_030055A0;
        metadata[primary].value = 0xFFFF;
        object->unknown2C = zero;
        condition = sub_08048684(*selectorByte);
        object->condition = condition;
        sub_080487C8(primaryByte);
        if (gObjectAuxiliaryLookup_083D2D0D[condition])
        {
            u32 secondary = index + 121;
            struct InitialFrameView *secondaryObject;
            sub_08048864((u8)secondary, 0xCC0C, 144, 14, 1);
            secondaryObject = &objects[secondary];
            secondaryObject->x.parts.integer = object->x.parts.integer;
            secondaryObject->y.parts.integer = object->y.parts.integer - 5;
        }
    }
}

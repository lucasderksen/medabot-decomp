#include "later_graphics.h"
struct AlternateDmaRegisters { u32 source; u32 destination; u32 control; };
void sub_080490E0(u16 *destination, u32 selector, u32 attributes)
{
    u32 tile = (selector + 1) * 4;
    u32 flags = (selector << 12) + attributes;
    destination[0] = tile | flags;
    destination[1] = (tile + 1) | flags;
    destination[32] = (tile + 2) | flags;
    destination[33] = (tile + 3) | flags;
}

void sub_08049110(u16 *destination, u32 selectorInput, u32 attributesInput,
                  u32 rowInput, u32 columnInput, u32 unused5, u32 unused6)
{
    u16 selector = selectorInput;
    u16 attributes = attributesInput;
    u16 row = rowInput;
    u16 column = columnInput;
    u16 offset = column + row * 2;
    u32 tile = (selector + 1) * 4;
    *destination = (offset + tile) | ((selector << 12) + attributes);
}

void sub_08049198(u32 indexInput, const void *source)
{
    u8 index = indexInput;
    volatile struct AlternateDmaRegisters *dma = (volatile struct AlternateDmaRegisters *)0x040000D4;
    dma->source = (u32)source;
    dma->destination = 0x05000000 + index * 32;
    dma->control = 0x80000008;
    dma->control;
}

void sub_08049344(u32 indexInput)
{
    u8 index = indexInput;
    sub_08049714((void *)(0x030055A0 + index * 4), 4);
    sub_08049714((void *)(0x03002C30 + index * 64), 64);
}

void sub_080496EC(void)
{
}

void sub_080496F0(u32 indexInput, const void *source)
{
    u8 index = indexInput;
    volatile struct AlternateDmaRegisters *dma = (volatile struct AlternateDmaRegisters *)0x040000D4;
    dma->source = (u32)source;
    dma->destination = 0x05000200 + index * 32;
    dma->control = 0x80000008;
    dma->control;
}

void sub_08049714(void *destination, u32 size)
{
    u8 *cursor = destination;
    u32 index;
    for (index = 0; index < size; index++)
        *cursor++ = 0;
}

void sub_08049728(void *destination, u32 size, u32 valueInput)
{
    u8 value = valueInput;
    u8 *cursor = destination;
    u32 index;
    for (index = 0; index < size; index++)
        *cursor++ = value;
}

#include "gba.h"

s32 sub_08049740(const void *first, const void *second, s32 size)
{
    const u8 *a = first;
    const u8 *b = second;
    s32 different = 0;
    s32 index;
    for (index = 0; index < size; index++)
    {
        if (*a++ != *b++)
            different++;
    }
    return different;
}

u32 sub_08049768(const void *source, s32 size)
{
    const u8 *cursor = source;
    u32 total = 0;
    s32 index;
    for (index = 0; index < size; index++)
    {
        total += *cursor++;
    }
    return total;
}

#include "gba.h"

struct AlternateMatrix16 {
    s16 scaleX, scaleY, angle, pa, pb, pc, pd, unused0E;
};

void sub_08049318(void)
{
    struct SettingsPrefix { u8 unknown00[0x18]; u16 field18; u16 field1A; };
    struct SettingsPrefix *settings = (struct SettingsPrefix *)0x03005310;
    struct AlternateMatrix16 *matrix;
    s32 index;
    u32 zero;
    u32 scale;
    settings->field18 = 0;
    settings->field1A = 0;
    zero = 0;
    scale = 256;
    matrix = (struct AlternateMatrix16 *)0x03006D40;
    for (index = 0; index < 32; index++)
    {
        matrix->scaleX = scale;
        matrix->scaleY = scale;
        matrix->angle = zero;
        matrix++;
    }
}

void sub_080497C0(const void *source, void *destination, u32 size)
{
    u32 index;
    for (index = 0; index < size; index++)
    {
        *(u8 *)destination = *(const u8 *)source;
        source = (const u8 *)source + 1;
        destination = (u8 *)destination + 1;
    }
}

#include "gba.h"

void sub_08049140(const u16 *source, u16 *destination, s32 height, s32 width,
                  s32 maximumHeight, s32 stride, u32 tileOffset, u32 palette)
{
    s32 row, column;
    if (height > maximumHeight)
        height = maximumHeight;
    for (row = 0; row < height; row++)
    {
        for (column = 0; column < width; column++)
            *destination++ = (*source++ + tileOffset) | (palette << 12);
        destination += stride - width;
    }
}

#include "frame.h"
void sub_08049420(u32 input, u32 value)
{
    u8 index = input;
    struct FrameObject *objects = gFrameObjects;
    struct FrameObject *object = &objects[index];
    object->unknown23[1] = value;
    object->unknown23[0] = 0;
    object->commandStopped = 0;
}

#include "gba.h"
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03005310[];
extern const u8 gRandomBytes_083F7D80[];
s32 Mod(s32 numerator, s32 denominator);

u32 sub_08049780(u32 input)
{
    u8 range = input;
    const u8 *table = gRandomBytes_083F7D80;
    u32 address = (u32)gUnknown_030057E0;
    u8 *cursor;
    struct RandomSettings { u32 unknown00; u32 step; };
    struct RandomSettings *settings;
    u8 random;
    u32 value;
    address += 0xC37;
    cursor = (u8 *)address;
    value = *cursor;
    settings = (struct RandomSettings *)gLaterBuffer_03005310;
    value += settings->step;
    random = table[value & 255];
    *cursor = random;
    return (u8)Mod(random, range);
}

#include "gba.h"
#include "object_numeric_helpers.h"

s32 sub_08048B70(s32 left, s32 right);
extern const s16 gAffineSineTable_080AE8F4[];
extern struct AlternateMatrix16 gLaterMatrices_03006D40[];

void sub_08049374(u32 input)
{
    u8 index = input;
    const s16 *sine = gAffineSineTable_080AE8F4;
    struct AlternateMatrix16 *matrices = gLaterMatrices_03006D40;
    struct AlternateMatrix16 *matrix = &matrices[index];
    u32 offset = matrix->angle + 64;
    const s16 *cosine = (const s16 *)((u32)sine + offset * 2);
    matrix->pa = sub_08048B70(*cosine, (s16)sub_08048BA0(matrix->scaleX));
    matrix->pb = sub_08048B70(sine[matrix->angle], (s16)sub_08048BA0(matrix->scaleX));
    matrix->pc = sub_08048B70((s16)-sine[matrix->angle], (s16)sub_08048BA0(matrix->scaleY));
    offset = matrix->angle + 64;
    cosine = (const s16 *)((u32)sine + offset * 2);
    matrix->pd = sub_08048B70(*cosine, (s16)sub_08048BA0(matrix->scaleY));
}

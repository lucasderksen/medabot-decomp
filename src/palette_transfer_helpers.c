#include "continued_commands.h"
#include "palette_transfer_helpers.h"
#include "fresh_helpers.h"
#include "frame.h"

extern u8 gUnknown_030057E0[];
extern const u8 *const gPaletteSelectorTables_08413160[];

struct PaletteDmaRegisters
{
    const void *source;
    u32 destination;
    u32 control;
};

s32 sub_08048684(s32 index)
{
    const u8 *const *table = gPaletteSelectorTables_08413160;
    u8 *work = gUnknown_030057E0;
    u32 offset = 0x7FE;
    work += offset;
    return sub_08048210(table[*work][index]);
}

void sub_080486B0(void)
{
    s32 index = 0;
    volatile struct PaletteDmaRegisters *dma = (void *)0x040000D4;
    u32 destination = 0x05000200;
    s32 value;
    while ((value = sub_08048684(index)) != 0xFF)
    {
        value = sub_08048684(index);
        if (gPaletteSourcePointers_083F83C0[value] == 0)
            value = 1;
        dma->source = gPaletteSourcePointers_083F83C0[value];
        dma->destination = destination;
        dma->control = 0x84000008;
        dma->control;
        destination += 32;
        index++;
    }
}

void sub_08048708(void)
{
    s32 index = 0;
    volatile struct PaletteDmaRegisters *dma = (void *)0x040000D4;
    u32 destination = 0x0202F800;
    s32 value;
    while ((value = sub_08048684(index)) != 0xFF)
    {
        value = sub_08048684(index);
        if (gPaletteSourcePointers_083F83C0[value] == 0)
            value = 1;
        dma->source = gPaletteSourcePointers_083F83C0[value];
        dma->destination = destination;
        dma->control = 0x84000008;
        dma->control;
        destination += 32;
        index++;
    }
    {
        volatile struct PaletteDmaRegisters *finalDma = (void *)0x040000D4;
        finalDma->source = gScenePalette_085FB684;
        finalDma->destination = 0x0202F9C0;
        finalDma->control = 0x84000008;
        finalDma->control;
    }
}

void sub_0804877C(s32 input)
{
    s32 index = 0;
    s32 value = sub_08048210(input);
    const void *const *table;
    volatile struct PaletteDmaRegisters *dma;
    u32 control;
    table = gPaletteSourcePointers_083F83C0;
    dma = (void *)0x040000D4;
    control = 0x84000008;
    do
    {
        if (table[value] == 0)
            value = 1;
        dma->source = table[value];
        dma->destination = 0x05000200 + index * 32;
        dma->control = control;
        dma->control;
        index++;
    } while (index <= 11);
}

void sub_080487C8(u32 input)
{
    u8 index = input;
    extern const u8 gFramePriorityLookup_083D2C5D[];
    const u8 *table = gFramePriorityLookup_083D2C5D;
    struct FrameObject *objects = gFrameObjects;
    struct FrameObject *object = &objects[index];
    u32 value = table[*(u16 *)&object->unknown2C[4]];
    if (value == 2)
        value = 0xFF;
    else if (value == 1)
        value = 0;
    else
        value = 64;
    object->priority = value;
}


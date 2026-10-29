#include "continued_commands.h"
#include "fresh_helpers.h"

extern u8 gUnknown_030057E0[];
struct InputDmaRegisters { u32 source, destination, control; };

void sub_08051E38(u32 mode)
{
    u8 *work;
    sub_08048288();
    if (mode == 0)
    {
        volatile struct InputDmaRegisters *dma;
        const void *const *sources;
        const u8 *lookup;
        dma = (void *)0x040000D4;
        sources = gPaletteSourcePointers_083F83C0;
        lookup = gFreshBytes_083D2B26;
        work = gUnknown_030057E0;
        dma->source = (u32)sources[lookup[work[0xC5C]]];
        dma->destination = 0x05000200;
        dma->control = 0x84000008;
        dma->control;
    }
    else
    {
        volatile struct InputDmaRegisters *dma;
        const void *const *sources;
        const u8 *lookup;
        dma = (void *)0x040000D4;
        sources = gPaletteSourcePointers_083F83C0;
        lookup = gFreshBytes_083D2B26;
        work = gUnknown_030057E0;
        dma->source = (u32)sources[lookup[work[0xC5C]]];
        dma->destination = 0x0202F800;
        dma->control = 0x84000008;
        dma->control;
    }
    {
        u32 value = work[0xC5C];
        u32 offset = 0xC28;
        u8 *stored = work + offset;
        *stored = value;
    }
    sub_0805330C();
}

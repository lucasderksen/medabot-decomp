#include "gba.h"
#include "continued_map.h"
#include "later_graphics.h"

struct ContinuedDmaRegisters
{
    const void *source;
    void *destination;
    u32 control;
};

void sub_0804B15C(void)
{
}

void sub_0804B248(void)
{
    u32 fill = 0;
    volatile struct ContinuedDmaRegisters *dma = (volatile struct ContinuedDmaRegisters *)0x040000D4;
    dma->source = &fill;
    dma->destination = (void *)0x06001000;
    dma->control = 0x85000800;
    (void)dma->control;
}

void sub_0804B270(void)
{
    u32 fill = 0;
    volatile struct ContinuedDmaRegisters *dma = (volatile struct ContinuedDmaRegisters *)0x040000D4;
    dma->source = &fill;
    dma->destination = (void *)0x06002800;
    dma->control = 0x85001A00;
    (void)dma->control;
}

void sub_0804B298(void)
{
    sub_08049728((void *)0x06003000, 0x6000, 0x80);
}



extern u8 gUnknown_030057E0[];
extern const u8 *const gContinuedMapEntries_08412E60[];

void sub_0804B160(void)
{
    const u8 *const *table = gContinuedMapEntries_08412E60;
    u32 address = (u32)gUnknown_030057E0;
    u32 offset = 0x7FE;
    const u8 *source = table[*(u8 *)(address + offset)];
    if (source[0] != 0xFF)
    {
        const u16 *width = (const u16 *)(address + 0x800);
        u8 *destination;
        const u8 *entry;
        offset += 0x12;
        destination = (u8 *)(address + offset);
        entry = source;
        do
        {
            u32 position = entry[0] + entry[1] * (*width / 2);
            *(u8 *)(position + (u32)destination) = 2;
            entry += 8;
        } while (entry[0] != 0xFF);
    }
}

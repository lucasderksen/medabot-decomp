

#include "record_helpers.h"

void sub_08064BEC(void);
void sub_08064C0C(void);
void sub_08064C2C(void);
void sub_08064C4C(void);
void LZ77UnCompWram(const void *source, void *destination);

extern u8 gUnknown_03005290[];
extern u8 gUnknown_030052B0[];
extern u8 gUnknown_030052D0[];
extern u8 gUnknown_030052F0[];

struct DmaRegisters
{
    u32 source;
    u32 destination;
    u32 control;
};

void sub_08044DA8(struct OamEntry *object, s32 width, s32 height)
{
    u8 *bytes = (u8 *)object;
    if (width > height)
    {
        bytes[1] = (bytes[1] & 0x3F) | 0x80;
        if (width == 8)
            bytes[3] &= 0x3F;
        else if (width == 64)
            bytes[3] |= 0xC0;
        else if (height == 8)
            bytes[3] = (bytes[3] & 0x3F) | 0x40;
        else
            bytes[3] = (bytes[3] & 0x3F) | 0x80;
    }
    else if (width < height)
    {
        bytes[1] = (bytes[1] & 0x3F) | 0x40;
        if (height == 8)
            bytes[3] &= 0x3F;
        else if (height == 64)
            bytes[3] |= 0xC0;
        else if (width == 8)
            bytes[3] = (bytes[3] & 0x3F) | 0x40;
        else
            bytes[3] = (bytes[3] & 0x3F) | 0x80;
    }
    else
    {
        bytes[1] &= 0x3F;
        if (width == 8)
            bytes[3] &= 0x3F;
        else if (width == 16)
            bytes[3] = (bytes[3] & 0x3F) | 0x40;
        else if (width == 32)
            bytes[3] = (bytes[3] & 0x3F) | 0x80;
        else
            bytes[3] |= 0xC0;
    }
}

void sub_08045084(const void *source, s32 shape, s32 size, s32 rows, s32 columns, s32 mode, u32 tile, u32 unused, void *scratch, u32 useCpu)
{
    u16 destinationTile = tile;
    tile = (u16)tile;
    if (source != 0)
    {
        u32 bytes = sub_08044D0C(source, scratch);
        u8 *reordered = (u8 *)scratch + bytes;
        sub_08044FB4(reordered, scratch, shape, size, rows, columns, mode);
        if (useCpu != 0)
            CpuSet(reordered, (u8 *)0x06010000 + tile * 32, (bytes & 0x7FFFFF) / 4 | CPU_SET_32BIT);
        else
        {
            volatile struct DmaRegisters *dma = (volatile struct DmaRegisters *)0x040000B0;
            dma->source = (u32)reordered;
            dma->destination = (u32)((u8 *)0x06010000 + destinationTile * 32);
            dma->control = (bytes >> 2) | 0x94000000;
            dma->control;
        }
    }
}

#include "graphics.h"
#include "compression.h"
#include "main.h"

#define GRAPHICS_SCRATCH ((void *)0x02030000)
#define REG_DMA0CNT_H (*(volatile u16 *)0x040000BA)

extern IntrFunc gUnknownCallback_03000B98;
extern u16 gSavedPalettes[512];
extern u16 gBlendedPalettes[512];
s32 Div(s32 numerator, s32 denominator);
s32 DivArm(s32 denominator, s32 numerator);

struct BgAffineLine
{
    u16 pa;
    u16 pb;
    u16 pc;
    u16 pd;
    u16 xLow;
    u16 xHigh;
    u16 yLow;
    u16 yHigh;
};

struct DmaRegisters
{
    u32 source;
    u32 destination;
    u32 control;
};

void LoadLeTilemap(u32 x, u32 y, const u8 *source, u32 control, u16 entryOffset)
{
    gTilemapEntryOffset = entryOffset;
    LeDecompress(source, GRAPHICS_SCRATCH);
    CopyTilemap(x, y, GRAPHICS_SCRATCH, control);
}

void LoadLeTileRows(u32 x, u32 y, const u8 *source, u32 control)
{
    LeDecompress(source, GRAPHICS_SCRATCH);
    CopyTileRows(x, y, GRAPHICS_SCRATCH, control);
}

void LoadLeData(const u8 *source, void *destination)
{
    u32 size = LeDecompress(source, GRAPHICS_SCRATCH);
    CpuSet(GRAPHICS_SCRATCH, destination, (size >> 1) & 0x1FFFFF);
}

void CopyTileRows(u32 x, u32 y, const struct GraphicsRows *source, u32 control)
{
    u32 rowShift = ((control & 0xC000) >> 14) + 3;
    u32 screenOffset = ((control >> 8) & 31) << 11;
    u32 xAddress = x + 0x06000000;
    u8 *destination = (u8 *)(screenOffset + xAddress + (y << rowShift));
    const u8 *cursor = (const u8 *)source->data;
    u32 row;


    for (row = 0; row < source->height; row++)
    {
        CpuSet(cursor, destination + (row << rowShift) * 2, (source->width >> 1) & 0x1FFFFF);
        cursor += source->width;
    }
}

void CopyLargeTilemap(u16 *destination, const struct GraphicsRows *source)
{
    s32 width = source->width;
    s32 height;
    u32 outputOffset;
    u32 row;
    u32 column;
    const u16 *in;
    u16 *out;

    if (width > 32)
        width = 32;
    height = source->height;
    if (height > 32)
        height = 32;

    for (row = 0; (s32)row < height; row++)
    {
        in = &source->data[row * source->width];
        outputOffset = row * 64;
        out = (u16 *)((u32)destination + outputOffset);
        for (column = 0; (s32)column < width; column++)
            *out++ = *in++ + gTilemapEntryOffset;
    }
    for (row = 0; (s32)row < height; row++)
    {
        in = &source->data[row * source->width + 32];
        outputOffset = row * 64 + 0x800;
        out = (u16 *)((u32)destination + outputOffset);
        for (column = 32; column < source->width; column++)
            *out++ = *in++ + gTilemapEntryOffset;
    }
    for (row = 32; row < source->height; row++)
    {
        in = &source->data[row * source->width];
        outputOffset = row * 64 + 0x800;
        out = (u16 *)((u32)destination + outputOffset);
        for (column = 0; (s32)column < width; column++)
            *out++ = *in++ + gTilemapEntryOffset;
    }
    for (row = 32; row < source->height; row++)
    {
        in = &source->data[row * source->width + 32];
        outputOffset = row * 64 + 0x1000;
        out = (u16 *)((u32)destination + outputOffset);
        for (column = 32; column < source->width; column++)
            *out++ = *in++ + gTilemapEntryOffset;
    }
}

void SetBg3Affine(s32 scale, s32 angle, s32 x, s32 y, s32 centerX, s32 centerY)
{
    u32 table;
    u32 offset;
    s16 *cosine;
    s16 *sine;
    s32 pa;
    s32 pb;
    s32 pc;
    s32 pd;
    s32 referenceX;
    s32 referenceY;
    volatile u16 *matrix;
    volatile u16 *reference;

    table = (u32)gSineTable;
    angle &= 1023;
    offset = (angle + 256) * 2;
    cosine = (s16 *)(table + offset);
    pa = Div(*cosine << 2, scale);
    offset = angle * 2;
    sine = (s16 *)(table + offset);
    pb = Div(*sine << 2, scale);
    pc = Div(-*sine << 2, scale);
    pd = Div(*cosine << 2, scale);
    matrix = (volatile u16 *)0x04000030;
    *matrix++ = pa;
    *matrix++ = pb;
    *matrix++ = pc;
    *matrix = pd;
    referenceX = -(centerX * pa) - centerY * pb - x;
    referenceY = -(pc * centerX) - centerY * pd - y;
    reference = (volatile u16 *)0x04000038;
    *reference++ = referenceX;
    *reference++ = (referenceX & 0x0FFF0000) >> 16;
    *reference++ = referenceY;
    *reference = (referenceY & 0x0FFF0000) >> 16;
}

void PrepareBg2ScanlineAffine(s32 increment, s32 angle, s32 unused, s32 x, s32 y, s32 centerX, s32 centerY)
{
    struct BgAffineLine *line;
    u32 table;
    u32 offset;
    u32 buffer;
    s32 index;
    s32 denominator;
    s32 row;
    s32 pa;
    s32 pb;
    s32 pc;
    s32 pd;
    s32 referenceX;
    s32 referenceY;
    s16 *cosine;
    s16 *sine;

    if (!(gFrameCounter & 1))
        buffer = 0x02030000;
    else
        buffer = 0x02030A00;
    row = 0;
    table = (u32)gSineTable;
    index = angle & 1023;
    offset = index * 2;
    sine = (s16 *)(offset + table);
    line = (struct BgAffineLine *)buffer;
    denominator = 1;
    offset = (index + 256) * 2;
    cosine = (s16 *)(offset + table);
    for (; row < 160;)
    {
        pa = DivArm(denominator, *cosine << 7);
        pb = DivArm(denominator, *sine << 7);
        pc = -pb;
        pb *= 3;
        pd = pa * 3;
        line->pa = pa;
        line->pb = pb;
        line->pc = pc;
        line->pd = pd;
        referenceX = -(centerX * pa) - centerY * pb - x + pb * row;
        referenceY = -(centerX * pc) - centerY * pd - y + pd * row;
        line->xLow = referenceX;
        line->xHigh = referenceX >> 16;
        line->yLow = referenceY;
        line->yHigh = referenceY >> 16;
        denominator += increment;
        row++;
        line++;
    }
    gUnknownCallback_03000B98 = StartBg2ScanlineDma;
}

void StartBg2ScanlineDma(void)
{
    volatile struct DmaRegisters *dma = (volatile struct DmaRegisters *)0x040000B0;
    volatile u16 *registers = (volatile u16 *)0x04000020;
    const struct BgAffineLine *line;

    if (gFrameCounter & 1)
        line = (const struct BgAffineLine *)0x02030000;
    else
        line = (const struct BgAffineLine *)0x02030A00;
    registers[0] = line->pa;
    registers[1] = line->pb;
    registers[2] = line->pc;
    registers[3] = line->pd;
    registers[4] = line->xLow;
    registers[5] = line->xHigh;
    registers[6] = line->yLow;
    registers[7] = line->yHigh;
    REG_DMA0CNT_H = 0;
    dma->source = (u32)(line + 1);
    dma->destination = (u32)registers;
    dma->control = 0xA2600008;
}

void StopBg2ScanlineDma(void)
{
    REG_DMA0CNT_H = 0;
}

u32 NextRandom(u16 upperBound)
{
    u32 inverted;
    gRandomCounter++;
    gRandomValue.value = gRandomTable[gRandomCounter & 15] ^ gRandomState.value;
    inverted = ~gRandomValue.value;
    {
        u32 base = gRandomState.halves[1] + 0x55555555;
        gRandomState.value = inverted + base;
    }
    if (upperBound == 0)
        return gRandomValue.value;
    return ((u32)gRandomValue.halves[1] * upperBound) >> 16;
}

s32 Lerp4096(s32 a, s32 b, s32 weight)
{
    return b * weight / 4096 + a * (4096 - weight) / 4096;
}

void SnapshotPalettes(void)
{
    CpuFastSet((const void *)0x05000200, (void *)0x0202F800, 0x80);
    CpuFastSet((const void *)0x05000000, (void *)0x0202FA00, 0x80);
}

void ApplyBlendedPalettes(void)
{
    CpuFastSet((const void *)0x0202FC00, (void *)0x05000200, 0x80);
    CpuFastSet((const void *)0x0202FE00, (void *)0x05000000, 0x80);
}


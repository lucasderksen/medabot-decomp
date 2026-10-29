#include "display_helpers.h"
#include "gba.h"
#include "graphics.h"
#include "compression.h"
#include "initialization.h"
#include "audio.h"
#include "main.h"
#include "state0_callbacks.h"

#define REG_DISPCNT (*(volatile u16 *)0x04000000)
#define REG_BG0CNT (*(volatile u16 *)0x04000008)
#define REG_SOUNDCNT_X (*(volatile u16 *)0x04000084)
#define REG_DMA0CNT_H (*(volatile u16 *)0x040000BA)
#define gUnknown_03005030 (*(u8 *)0x03005030)

extern void VBlankIntrWait(void);
struct DisplaySerialView
{
    u32 unknown00[7];
    u32 flags;
};

u32 sub_0803EED8(void)
{
    if (gUnknown_03000440[0x89] == 1
        && (((struct DisplaySerialView *)&gMainSerialWork)->flags & 0x00FFFF00))
    {
        gMainState = 0;
        gMainSubstate = 10;
        gUnknown_0300137C = 16;
        return 1;
    }
    return 0;
}

void sub_0803EF20(void)
{
    gUnknown_03005030 = 0;
    sub_080021A4();
    VBlankIntrWait();
    REG_SOUNDCNT_X = 0;
    REG_IME = 0;
    ResetMemory();
    InitInterrupts();
    sub_080020C8();
    gMainState = 3;
    gMainSubstate = 0;
    gUnknown_0300137C = 0;
    REG_DMA0CNT_H = 0;
    VBlankIntrWait();
    InitAudio((void *)0x03002430);
    VBlankIntrWait();
}

void sub_0803EF8C(u32 width, u32 height, u32 x, u32 y, u32 control, u32 entry)
{
    u16 value = entry;
    u32 screenOffset = ((control >> 8) & 31) << 11;
    u32 xAddress = x * 2 + 0x06000000;
    u16 *destination = (u16 *)(screenOffset + xAddress + y * 64);
    u32 row, column;
    for (row = 0; row < height; row++)
    {
        u16 *out = destination + row * 32;
        for (column = 0; column < width; column++)
            *out++ = value;
    }
}

void sub_0803EFD8(u32 width, u32 height, u32 x, u32 y, u32 control, u32 entry)
{
    u16 value = entry;
    u32 row, column;
    u16 *destination;
    u32 rowsRemaining;
    u32 columnsRemaining;
    u16 *out;
    if (x < 32)
    {
        if (y < 32)
        {
            u32 screenOffset = ((control >> 8) & 31) << 11;
            u32 xAddress = x * 2 + 0x06000000;
            destination = (u16 *)(screenOffset + xAddress + y * 64);
            rowsRemaining = 32 - y;
            for (row = 0; row < height; row++)
            {
                columnsRemaining = 32 - x;
                out = destination + row * 32;
                for (column = 0; column < width; column++)
                {
                    *out++ = value;
                    columnsRemaining--;
                    if (columnsRemaining == 0)
                        out += 992;
                }
                rowsRemaining--;
                if (rowsRemaining == 0)
                    destination += 1024;
            }
        }
        else
        {
            u32 screenOffset, xAddress;
            y -= 32;
            screenOffset = ((control >> 8) & 31) << 11;
            xAddress = x * 2 + 0x06000000;
            destination = (u16 *)(screenOffset + xAddress + y * 64 + 0x1000);
            for (row = 0; row < height; row++)
            {
                columnsRemaining = 32 - x;
                out = destination + row * 32;
                for (column = 0; column < width; column++)
                {
                    *out++ = value;
                    columnsRemaining--;
                    if (columnsRemaining == 0)
                        out += 992;
                }
            }
        }
    }
    else
    {
        if (y < 32)
        {
            u32 screenOffset = ((control >> 8) & 31) << 11;
            u32 xAddress = (x - 32) * 2 + 0x06000000;
            destination = (u16 *)(screenOffset + xAddress + y * 64 + 0x800);
            rowsRemaining = 32 - y;
            for (row = 0; row < height; row++)
            {
                out = destination + row * 32;
                for (column = 0; column < width; column++)
                    *out++ = value;
                rowsRemaining--;
                if (rowsRemaining == 0)
                    destination += 1024;
            }
        }
        else
        {
            u32 screenOffset, xAddress;
            y -= 32;
            screenOffset = ((control >> 8) & 31) << 11;
            xAddress = (x - 32) * 2 + 0x06000000;
            destination = (u16 *)(screenOffset + xAddress + y * 64 + 0x1800);
            for (row = 0; row < height; row++)
            {
                out = destination + row * 32;
                for (column = 0; column < width; column++)
                    *out++ = value;
            }
        }
    }
}

void sub_0803F15C(u32 width, u32 height, u32 x, u32 y, const void *source, u32 control, u32 entryOffset)
{
    u32 screenOffset;
    u32 xAddress;
    u16 *destination;
    const u16 *cursor;
    u32 row, column;
    gTilemapEntryOffset = entryOffset;
    screenOffset = ((control >> 8) & 31) << 11;
    xAddress = x * 2 + 0x06000000;
    destination = (u16 *)(screenOffset + xAddress + y * 64);
    cursor = source;
    for (row = 0; row < height; row++)
    {
        u16 *out = destination + row * 32;
        for (column = 0; column < width; column++)
            *out++ = *cursor++ + gTilemapEntryOffset;
    }
}

void sub_0803F3A8(void)
{
    LeDecompress((const u8 *)0x08486E6C, (void *)0x06000020);
    LeDecompress((const u8 *)0x084C39D8, (void *)0x06001780);
    CpuFastSet((const void *)0x08488520, (void *)0x050001E0, 8);
}

void sub_0803F3E0(void)
{
    REG_DISPCNT |= 0x100;
    { u16 value; volatile u16 *control = (volatile u16 *)0x04000008; value = 0x500; *control = value; }
    LoadLeTilemap(0, 13, (const u8 *)0x08487FDC, REG_BG0CNT, 1);
}

void sub_0803F41C(u32 bank, u32 frame, void *destination, u32 paletteSlot, u32 savedPalette)
{
    LeDecompress(gUnknownPointers_083AFE88[bank * 9 + frame], destination);
    if (savedPalette)
        CpuFastSet(gUnknownPointers_083B1748[bank], (void *)(0x0202FA00 + paletteSlot * 32), 8);
    else
        CpuFastSet(gUnknownPointers_083B1748[bank], (void *)(0x05000000 + paletteSlot * 32), 8);
}

void sub_0803F480(u32 bank, u32 frame, u32 x, u32 y, u32 mapBank)
{
    REG_DISPCNT |= 0x100;
    REG_BG0CNT = 0x500;
    LeDecompress(gUnknownPointers_083AFE88[bank * 9 + frame], (void *)0x06000F80);
    CpuFastSet(gUnknownPointers_083B1748[bank], (void *)0x050001A0, 8);
    sub_0803F15C(8, 8, x, y, gUnknownPointers_083B4C60[mapBank * 9 + 8], REG_BG0CNT, 0);
}

u32 sub_0803F51C(u32 bank, u32 frame, u32 x, u32 y, u32 mapBank, u32 reverse)
{
    u8 record[2];
    u8 *cursor = record;
    *cursor++ = bank;
    *cursor = frame;
    if (gUnknown_03000440[0xE] == 0)
    {
        REG_DISPCNT |= 0x100;
        REG_BG0CNT = 0x500;
        LeDecompress(gUnknownPointers_083AFE88[bank * 9 + frame], (void *)0x06000F80);
        CpuFastSet(gUnknownPointers_083B1748[bank], (void *)0x050001A0, 8);
    }
    if (!reverse)
        sub_0803F15C(8, 8, x, y, gUnknownPointers_083B4C60[mapBank * 9 + gUnknown_03000440[0xE]], REG_BG0CNT, 0);
    else
    {
        u32 table = (u32)gUnknownPointers_083B4C60;
        u32 index = mapBank * 9;
        u32 current = gUnknown_03000440[0xE];
        current -= 8;
        index -= current;
        sub_0803F15C(8, 8, x, y, *(const void **)(table + index * 4), REG_BG0CNT, 0);
    }
    gUnknown_03000440[0xE]++;
    if (gUnknown_03000440[0xE] == 9)
        return 1;
    return 0;
}

void sub_0803F624(void *destination, u32 size, u32 inputValue)
{
    u8 *out = destination;
    u8 value = inputValue;
    u32 i;
    for (i = 0; i < size; i++)
        *out++ = value;
}

void sub_0803F63C(const void *source, void *destination, u32 size)
{
    u32 i;
    for (i = 0; i < size; i++)
    {
        *(u8 *)destination = *(const u8 *)source;
        source = (const u8 *)source + 1;
        destination = (u8 *)destination + 1;
    }
}

void sub_0803F65C(void *first, void *second, u32 size)
{
    u32 i;
    for (i = 0; i < size; i++)
    {
        u8 temp = *(u8 *)first;
        *(u8 *)first = *(u8 *)second;
        first = (u8 *)first + 1;
        *(u8 *)second = temp;
        second = (u8 *)second + 1;
    }
}

#include "tile_selector_expansion.h"
#include "later_graphics.h"

void sub_08048E24(const u8 *source, u16 *destination, s32 height, s32 width,
                 u32 unused4, u32 unused5, s32 rowOffset, s32 columnOffset,
                 u32 attributes)
{
    s32 row, column;
    s32 rows = height + rowOffset > 31 ? 32 : height;
    s32 columns;

    for (row = 0; row < rows; row++)
    {
        columns = width + columnOffset > 31 ? 32 : width;
        for (column = 0; column < columns; column++)
            sub_08049110((u16 *)((u32)destination + (row + rowOffset) * 64 + (column + columnOffset) * 2),
                ((const u8 *)((u32)source + width / 2 * (row / 2)))[column / 2], (u16)attributes,
                (u16)(row % 2), (u16)(column % 2),
                (u16)(rowOffset % 2), (u16)(columnOffset % 2));
        if (width > 31)
            for (column = 0; column < width - 32; column++)
                sub_08049110((u16 *)((u32)destination + 2048 + (row + rowOffset) * 64 + (column + columnOffset) * 2),
                    ((const u8 *)((u32)source + width / 2 * (row / 2)))[column / 2 + 16], (u16)attributes,
                    (u16)(row % 2), (u16)(column % 2),
                    (u16)(rowOffset % 2), (u16)(columnOffset % 2));
    }
    if (height > 31)
        for (row = 0; row < height - 32; row++)
        {
            columns = 32;
            if (width <= 31)
                columns = width;
            for (column = 0; column < columns; column++)
                sub_08049110((u16 *)((u32)destination + 4096 + (row + rowOffset) * 64 + (column + columnOffset) * 2),
                    ((const u8 *)((u32)source + width / 2 * (row / 2 + 16)))[column / 2], (u16)attributes,
                    (u16)(row % 2), (u16)(column % 2),
                    (u16)(rowOffset % 2), (u16)(columnOffset % 2));
            if (width > 31)
                for (column = 0; column < width - 32; column++)
                    sub_08049110((u16 *)((u32)destination + 6144 + (row + rowOffset) * 64 + (column + columnOffset) * 2),
                        ((const u8 *)((u32)source + width / 2 * (row / 2 + 16)))[column / 2 + 16], (u16)attributes,
                        (u16)(row % 2), (u16)(column % 2),
                        (u16)(rowOffset % 2), (u16)(columnOffset % 2));
        }
}

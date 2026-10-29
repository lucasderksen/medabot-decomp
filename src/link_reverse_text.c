#include "link_menu.h"
void sub_080674BC(u8 *str, u8 row)
{
    s32 i;
    s32 len;
    u16 *dst;
    s16 c;
    u32 screen;
    u32 blank;
    u32 rowAddress;

    len = 0;
    while (*str != 0) {
        str++;
        len++;
    }
    str = (u8 *)((u32)str - 1);
    screen = (((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11);
    rowAddress = (row << 6) + 0x0600003A;
    dst = (u16 *)(screen + rowAddress);
    for (i = 0; i <= 0x13; i++) {
        blank = 0;
        if (i < len && (c = *str, str = (u8 *)((u32)str - 1), c) != ' ') {
            c -= 0x41;
            *dst = ((u16 *)0x06000000)[0x6E80 + c];
        } else
            do {
                *dst = blank;
            } while (0);
        dst--;
    }
}

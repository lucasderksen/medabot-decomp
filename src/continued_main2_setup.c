#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "continued_late_graphics.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "frame.h"
#include "compression.h"
#include "main_callbacks.h"

#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)
#define BG0_CONTROL (*(volatile u16 *)0x04000008)
#define BG1_CONTROL (*(volatile u16 *)0x0400000A)
#define BG2_CONTROL (*(volatile u16 *)0x0400000C)
#define BG3_CONTROL (*(volatile u16 *)0x0400000E)

/* Only the accessed context fields are modeled. */
struct Main2SetupContext
{
    u8 unknown00[5];
    u8 byte05;
    u8 unknown06[0x30];
    u16 halfword36;
};

void sub_0805C128(void)
{
    u32 fill = 0;
    CpuFastSet(&fill, VRAM, 0x01006000);
    sub_080415BC();
    sub_08059E50();
    DISPLAY_CONTROL = 0x60;
    sub_080656DC((u8 *)gMainContextPointer_03006F74 + 0x50,
                  16, 0, (u32)-1, 192);
    gUnknown_0300137C++;
}


void sub_0805C17C(void)
{
    volatile u16 *bg0 = (volatile u16 *)0x04000008;
    volatile u16 *bg1, *bg2, *bg3;
    u32 one = 1;
    u32 size;
    u32 zero;
    u32 control;
    control = 0x1F04;
    *bg0 = control;
    bg1 = (volatile u16 *)0x0400000A;
    control -= 255;
    *bg1 = control;
    bg2 = (volatile u16 *)0x0400000C;
    control = 0x3D06;
    *bg2 = control;
    bg3 = (volatile u16 *)0x0400000E;
    control -= 255;
    *bg3 = control;
    sub_0805BA34(gMain2Map_08790DA8, *bg0);
    sub_0805BA34(gMain2Map_08790F78, *bg1);
    sub_0805BA34(gMain2Map_087911BC, *bg2);
    sub_0805BA34(gMain2Map_0879131C, *bg3);
    size = sub_08044D0C(gMain2Tiles_0878F7E8, (void *)0x02030000);
    CpuSet((void *)0x02030000, (void *)0x06004000, (size << 10) >> 11);
    zero = 0;
    ((struct Main2SetupContext *)gMainContextPointer_03006F74)->halfword36 = (size >> 5) - 1;
    LeDecompress(gMain2ObjectTiles_08785FB4, (void *)0x06010000);
    CpuFastSet(gMain2Palette_0878F5E8, (void *)0x0202FA00, 128);
    CpuFastSet(gMain2Palette_0878F5E8, PALETTE_RAM, 128);
    CpuFastSet(gUnknownWords_084E43F8, (void *)0x0202F800, 128);
    CpuFastSet(gUnknownWords_084E43F8, (void *)0x05000200, 128);
    gFrameObjects[14].flags = 0x8000;
    gFrameObjects[14].priority = one;
    gFrameObjects[14].tableSelector = 2;
    gFrameObjects[14].palette = zero;
    gFrameObjects[14].frameAndGroup = 6;
    gFrameObjects[14].screenX = 32;
    gFrameObjects[14].screenY = 80;
    ((struct Main2SetupContext *)gMainContextPointer_03006F74)->byte05 = zero;
    gUnknown_0300137C++;
}

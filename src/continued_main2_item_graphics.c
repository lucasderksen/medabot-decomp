#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "frame.h"
#include "compression.h"
#include "bg_scroll.h"
#include "main_callbacks.h"

#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

/* This partial view observes only the context halfword at 36. */
struct Main2TileContext
{
    u8 unknown00[0x36];
    u16 halfword36;
};

void sub_0805CC3C(void)
{
    volatile u16 *bg1 = (volatile u16 *)0x0400000A;
    volatile u16 *bg2, *bg3;
    u32 length;
    u32 control;
    u8 index;
    const u8 *objectTiles;
    control = 0x1E05;
    *bg1 = control;
    bg2 = (volatile u16 *)0x0400000C;
    control = 0x1C06;
    *bg2 = control;
    bg3 = (volatile u16 *)0x0400000E;
    control = 0x3D07;
    *bg3 = control;
    sub_0805BA34(gMain2Map_0878D694, *bg1);
    sub_0805BA34(gMain2Map_0878D7C4, *bg2);
    sub_0805BA34(gMain2Map_0878D960, *bg3);
    length = sub_08044D0C(gMain2Tiles_0878C288, (void *)0x02030000);
    CpuSet((void *)0x02030000, (void *)0x06004000, (length << 10) >> 11);
    {
        const u8 *source = gMain2AdditionalTiles_08785EC0;
        u32 destination = 0x06000000;
        destination += length;
        destination += 0x4000;
        LeDecompress(source, (void *)destination);
    }
    ((struct Main2TileContext *)gMainContextPointer_03006F74)->halfword36 = (length >> 5) - 1;
    LeDecompress(gMain2ObjectTiles_08785FB4, (void *)0x06010000);
    for (index = 0; index <= 1; index++)
    {
        gFrameObjects[index + 81].flags = 0x8000;
        gFrameObjects[index + 81].tableSelector = 2;
        gFrameObjects[index + 81].screenX = index * 40 + 24;
        gFrameObjects[index + 81].screenY = 24;
        gFrameObjects[index + 81].palette = 0;
        gFrameObjects[index + 81].frameAndGroup = 5;
    }
    gFrameObjects[81].flags |= 0x1000;
    index = 0;
    objectTiles = gMain2SharedObjectTiles_084C8034;
    do
    {
        gFrameObjects[index + 83].flags = 0x8000;
        gFrameObjects[index + 83].tableSelector = 2;
        gFrameObjects[index + 83].palette = 0;
        gFrameObjects[index + 83].frameAndGroup = 6;
        index++;
    } while (index <= 1);
    for (index = 0; index <= 4; index++)
    {
        gFrameObjects[index + 85].flags = 0x8000;
        gFrameObjects[index + 85].tableSelector = 2;
        gFrameObjects[index + 85].palette = 14;
        gFrameObjects[index + 85].frameAndGroup = 7;
        gFrameObjects[index + 85].screenX = 224;
        gFrameObjects[index + 85].screenY = index * 16 + 32;
    }
    LeDecompress(objectTiles, (void *)0x06017400);
    gUnknown_0300137C++;
}

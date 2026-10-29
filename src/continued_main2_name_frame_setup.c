#include "gba.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "record_helpers.h"
#include "compression.h"


/* Only observed accessed fields; original and complete layout unknown. */
struct Main2NextContext
{
    u8 byte00;
    u8 unknown01;
    u16 half02;
    u8 unknown04;
    u8 byte05;
    u8 byte06;
    u8 unknown07[0x24];
    u8 byte2B;
    u16 half2C;
    u8 unknown2E[8];
    u16 half36;
    u8 unknown38[0x10];
    u8 byte48;
    u8 byte49;
    u8 byte4A;
    u8 byte4B;
};
#define CONTEXT ((struct Main2NextContext *)gMainContextPointer_03006F74)
#define DISPCNT (*(volatile u16 *)0x04000000)
#define BG1CNT (*(volatile u16 *)0x0400000A)
#define BG2CNT (*(volatile u16 *)0x0400000C)
#define BG3CNT (*(volatile u16 *)0x0400000E)
#define BLDCNT (*(volatile u16 *)0x04000050)
#define BLDY (*(volatile u16 *)0x04000054)

void sub_0805F19C(void)
{
    volatile u16 *bg1 = (volatile u16 *)0x0400000A;
    volatile u16 *bg2, *bg3;
    u32 length;
    u8 index;
    u32 control = 0x1E05;
    *bg1 = control;
    bg2 = (volatile u16 *)0x0400000C;
    control -= 255;
    *bg2 = control;
    bg3 = (volatile u16 *)0x0400000E;
    control = 0x3C07;
    *bg3 = control;
    sub_0805BA34(gMain2NameMap_08792888, BG1CNT);
    sub_0805BA34(gMain2NameMap_087929E8, BG2CNT);
    sub_0805BA34(gMain2NameMap_08792BB8, BG3CNT);
    length = sub_08044D0C(gMain2NameTiles_087917F4, (void *)0x02030000);
    CpuSet((void *)0x02030000, (void *)0x06004000, (length << 10) >> 11);
    {
        const u8 *source = gMain2AdditionalTiles_08785EC0;
        u32 destination = 0x06000000;
        destination += length;
        destination += 0x4000;
        LeDecompress(source, (void *)destination);
    }
    CONTEXT->half36 = (length >> 5) - 1;
    CpuFastSet(gMain2NamePalette_087915F4, (void *)0x05000000, 128);
    CpuFastSet(gMain2NameTransfer_08483534, (void *)0x050001C0, 8);
    LeDecompress(gMain2ObjectTiles_08785FB4, (void *)0x06010000);
    CpuFastSet(gUnknownWords_084E43F8, (void *)0x050003C0, 8);
    gFrameObjects[0].flags = 0x8000;
    gFrameObjects[0].tableSelector = 2;
    gFrameObjects[0].palette = 14;
    gFrameObjects[0].frameAndGroup = 6;
    CONTEXT->byte05 = 0;
    gFrameObjects[0].screenX = 20;
    gFrameObjects[0].screenY = CONTEXT->byte05 * 16 + 32;
    for (index = 0; index <= 1; index++)
    {
        gFrameObjects[index + 1].flags = 0x8000;
        gFrameObjects[index + 1].tableSelector = 2;
        gFrameObjects[index + 1].palette = 14;
        gFrameObjects[index + 1].frameAndGroup = 5;
    }
    gFrameObjects[1].flags |= 0x1000;
    gFrameObjects[1].screenX = 120;
    gFrameObjects[1].screenY = 32;
    gFrameObjects[2].screenX = 144;
    gFrameObjects[2].screenY = 32;
    for (index = 0; index <= 1; index++)
    {
        gFrameObjects[index + 3].flags = 0x8000;
        gFrameObjects[index + 3].tableSelector = 2;
        gFrameObjects[index + 3].palette = 14;
        gFrameObjects[index + 3].frameAndGroup = 5;
    }
    gFrameObjects[3].flags |= 0x1000;
    gFrameObjects[3].screenX = 120;
    gFrameObjects[3].screenY = 48;
    gFrameObjects[4].screenX = 144;
    gFrameObjects[4].screenY = 48;
    gUnknown_0300137C++;
}

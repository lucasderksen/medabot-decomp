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

void sub_0805F144(void)
{
    sub_08074B88(0);
    {
        u32 fill = 0;
        CpuFastSet(&fill, (void *)0x06000000, 0x01006000);
    }
    sub_080415BC();
    sub_08040CD0(0, 128);
    DISPCNT = 0x60;
    BLDCNT = 0x2FF;
    BLDY = 16;
    gUnknown_0300137C++;
}

void sub_0805F358(void)
{
    DISPCNT |= 0x200;
    DISPCNT |= 0x400;
    DISPCNT |= 0x800;
    DISPCNT |= 0x1000;
    CONTEXT->byte2B = 0;
    CONTEXT->half2C = 0;
    sub_08059F58(CONTEXT->byte2B, -2, 16, 4, 2, (BG1CNT >> 8) & 31);
    sub_08059F58(CONTEXT->half2C, -3, 15, 6, 2, (BG1CNT >> 8) & 31);
    CONTEXT->byte00 = 32;
    BLDY = CONTEXT->byte00 >> 1;
    gUnknown_0300137C++;
}

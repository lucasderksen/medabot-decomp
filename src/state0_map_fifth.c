#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "frame.h"
#include "compression.h"


void sub_08010DAC(void)
{
    volatile u32 *dma;
    struct FrameObject *base;
    sub_08012098();
    sub_08043CD4();
    sub_080123A0();
    LeDecompress((const u8 *)0x084D923C, (void *)0x06012400);
    dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x0850FF78;
    dma[1] = 0x05000340;
    dma[2] = 0x84000008;
    dma[2];
    base = gFrameObjects;
    base[1].flags = 0xC624;
    base[1].tableSelector = 0;
    base[1].screenX = 192;
    base[1].screenY = 96;
    base[1].palette = 10;
    base[1].priority = 192;
    base[1].frameAndGroup = 0x5900;
    base[1].scaleY = 64;
    base[1].scaleX = 64;
    base[1].unknown23[0] = 0;
    base[1].unknown23[5] = 0;
    sub_08074DE0(42);
    gUnknown_0300137C++;
}

void sub_08010E50(void)
{
    sub_08012098();
    sub_08043CD4();
    sub_080123A0();
    if (sub_08036AC4(1, 0))
        gUnknown_0300137C++;
}

void sub_08010E7C(void)
{
    volatile u32 *dma;
    struct FrameObject *base;
    sub_08012098();
    sub_08043CD4();
    sub_080123A0();
    sub_08012468();
    LeDecompress((const u8 *)0x084D9350, (void *)0x06016C00);
    dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x084E4538;
    dma[1] = 0x05000360;
    dma[2] = 0x84000008;
    dma[2];
    base = gFrameObjects;
    base[2].flags = 0xC404;
    base[2].tableSelector = 0;
    base[2].screenX = 8;
    base[2].screenY = 80;
    base[2].palette = 11;
    base[2].priority = 192;
    base[2].frameAndGroup = 0x5A00;
    gUnknown_0300137C++;
}

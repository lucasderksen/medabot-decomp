#include "continued_late_graphics.h"
#include "global.h"
#include "later_graphics.h"
#include "compression.h"
#include "display_helpers.h"
#include "continued_graphics.h"
#include "continued_map_data.h"
#include "continued_map.h"
#include "fresh_helpers.h"
#include "frame.h"
#include "object_helpers.h"

/* Existing failed callee reconstructions retain these observed word slots. */



struct SetupDmaRegisters { u32 source, destination, control; };



void sub_080576E0(void)
{
    void **setup;
    sub_0804B248();
    sub_08049714(gFrameObjects, 0x2000);
    sub_08049714(gLaterBuffer_030055A0, 0x200);
    {
        u32 fill = 0;
        volatile struct SetupDmaRegisters *dma = (void *)0x040000D4;
        dma->source = (u32)&fill;
        dma->destination = 0x07000000;
        dma->control = 0x85000100;
        (void)dma->control;
        *(volatile u16 *)0x04000000 = 0x1F40;
        gUnknown_030057E0[0xCBA] = 1;
        sub_080480E4();
        LeDecompress((const u8 *)0x084C2430, (void *)0x060017E0);
        LeDecompress((const u8 *)0x084C1E24, (void *)0x06001800);
        LeDecompress((const u8 *)0x084C200C, (void *)0x06001B00);
        LeDecompress((const u8 *)0x084C2150, (void *)0x06001E00);
        LeDecompress((const u8 *)0x084C22E8, (void *)0x06002100);
        LeDecompress((const u8 *)0x084871A4, (void *)0x06002400);
        dma->source = 0x08488520;
        dma->destination = 0x0202FBE0;
        dma->control = 0x84000008;
        (void)dma->control;
        LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
        dma->source = 0x084E43D8;
        dma->destination = 0x0202F9E0;
        dma->control = 0x84000008;
        (void)dma->control;
        LZ77UnCompVram(gUnknownBytes_085FB6E4, (void *)0x06000F80);
        LZ77UnCompVram(gUnknownBytes_085FBB78, (void *)0x06002100);
    }
    setup = &gSetupPointer_03006D14;
    sub_08049714(*setup, 0x2000);
    {
        volatile struct SetupDmaRegisters *dma = (void *)0x040000D4;
        u8 *destination;
        dma->source = (u32)gUnknownBytes_085FBA78;
        destination = *setup;
        dma->destination = (u32)destination;
        dma->control = 0x80000070;
        (void)dma->control;
        dma->source = (u32)gUnknownBytes_085FBBC0;
        dma->destination = (u32)(destination + 0x400);
        dma->control = 0x80000010;
        (void)dma->control;
        sub_08049210(gUnknownHalfwords_083D611C,
                     (u16 *)(destination + 0x800), 0, 0, 16, 10, 0, 15, 0);
    }
    sub_080491B8((u16 *)((u8 *)*setup + 0x1000), 2, 14, 16, 10, 0, 15, 0);
    sub_08049210(*setup, (u16 *)((u8 *)*setup + 0x800), 1, 1, 14, 8, 124, 14, 0);

    switch (sub_08057D80(0))
    {
    case 0: LZ77UnCompVram(gUnknownBytes_085FBC00, (void *)0x06016F80); break;
    case 1:
        LZ77UnCompVram(gUnknownBytes_085FC038, (void *)0x06016F80);
        sub_080581C8(0);
        break;
    default: LZ77UnCompVram(gUnknownBytes_085FBE1C, (void *)0x06016F80); break;
    }
    switch (sub_08057D80(1))
    {
    case 0: LZ77UnCompVram(gUnknownBytes_085FBC88, (void *)0x06017000); break;
    case 1:
        LZ77UnCompVram(gUnknownBytes_085FC038, (void *)0x06017000);
        sub_080581C8(1);
        break;
    default: LZ77UnCompVram(gUnknownBytes_085FBEA4, (void *)0x06017000); break;
    }
    switch (sub_08057D80(2))
    {
    case 0: LZ77UnCompVram(gUnknownBytes_085FBD14, (void *)0x06017080); break;
    case 1:
        LZ77UnCompVram(gUnknownBytes_085FC038, (void *)0x06017080);
        sub_080581C8(2);
        break;
    default: LZ77UnCompVram(gUnknownBytes_085FBF30, (void *)0x06017080); break;
    }
    switch (sub_08057D80(3))
    {
    case 0: LZ77UnCompVram(gUnknownBytes_085FBD9C, (void *)0x06017100); break;
    case 1:
        LZ77UnCompVram(gUnknownBytes_085FC038, (void *)0x06017100);
        sub_080581C8(3);
        break;
    default: LZ77UnCompVram(gUnknownBytes_085FBFB8, (void *)0x06017100); break;
    }

    LeDecompress((const u8 *)0x08486E6C, (void *)0x06000020);
    LeDecompress((const u8 *)0x084C39D8, (void *)0x06001780);
    {
        volatile struct SetupDmaRegisters *dma = (void *)0x040000D4;
        dma->source = 0x08488520;
        dma->destination = 0x0202FBE0;
        dma->control = 0x84000008;
        (void)dma->control;
        dma->source = (u32)gUnknownBytes_084C7F34;
        dma->destination = 0x0202FBC0;
        dma->control = 0x84000008;
        (void)dma->control;
        LeDecompress(gUnknownBytes_08487388, (void *)0x06002600);
        LeDecompress(gUnknownBytes_08487408, (void *)0x060026E0);
        LeDecompress(gUnknownBytes_084C88B8, (void *)0x06017E00);
        dma->source = (u32)gUnknownWords_084E43F8;
        dma->destination = 0x0202F9C0;
        dma->control = 0x84000008;
        (void)dma->control;
        sub_080492A8((const u16 *)(gContinuedCommandWork_030064A0 + 0x72),
                     (void *)0x06002800, 0, 0, 30, 20, 32, 32, 0, 0);
        dma->source = (u32)gUnknownBytes_085FBBE0;
        dma->destination = 0x0202F980;
        dma->control = 0x84000008;
        (void)dma->control;
        dma->source = (u32)gUnknownBytes_085FBDFC;
        dma->destination = 0x0202F9A0;
        dma->control = 0x84000008;
        (void)dma->control;
    }
    sub_08058070(0);
    sub_08049D18(0, 32.0f, 0.0f, 8.0f);
    sub_0804A210();
}

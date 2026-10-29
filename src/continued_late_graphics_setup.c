#include "continued_late_graphics.h"
#include "object_helpers.h"
#include "global.h"
#include "later_graphics.h"
#include "compression.h"
#include "display_helpers.h"
#include "continued_graphics.h"
#include "continued_map_data.h"

/* Existing failed callee reconstructions retain these observed word slots. */


struct SetupDmaRegisters { u32 source, destination, control; };

void sub_0805718C(void)
{
    void **setup;
    sub_08049714(gContinuedCommandWork_030064A0, 0x874);
    LZ77UnCompVram(gUnknownBytes_085FB6E4, (void *)0x06000F80);
    LZ77UnCompVram(gUnknownBytes_085FBB78, (void *)0x06002100);
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
    {
        volatile struct SetupDmaRegisters *dma = (void *)0x040000D4;
        dma->source = (u32)gUnknownBytes_085FBBE0;
        dma->destination = 0x05000380;
        dma->control = 0x84000008;
        (void)dma->control;
        dma->source = (u32)gUnknownBytes_085FBDFC;
        dma->destination = 0x050003A0;
        dma->control = 0x84000008;
        (void)dma->control;
        sub_0803F3A8();
        dma->source = (u32)gUnknownBytes_084C7F34;
        dma->destination = 0x050001C0;
        dma->control = 0x84000008;
        (void)dma->control;
        LeDecompress(gUnknownBytes_08487388, (void *)0x06002600);
        LeDecompress(gUnknownBytes_08487408, (void *)0x060026E0);
        LeDecompress(gUnknownBytes_084C88B8, (void *)0x06017E00);
        dma->source = (u32)gUnknownWords_084E43F8;
        dma->destination = 0x050003C0;
        dma->control = 0x84000008;
        (void)dma->control;
    }
    {
        u8 *work = gContinuedCommandWork_030064A0;
        u8 *width, *height;
        work[0x66] = 0;
        work[0x67] = 0;
        work[0x6F] = 0;
        width = &work[0x6C];
        height = &work[0x6D];
        work[0x6E] = 0;
        *width = 16;
        *height = 3;
    }
    sub_0804A210();
}

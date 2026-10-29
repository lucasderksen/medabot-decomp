#include "continued_commands.h"
#include "continued_callbacks.h"
#include "continued_graphics.h"
#include "gba.h"
#include "frame.h"
#include "later_graphics.h"
#include "object_numeric_helpers.h"
#include "background_state.h"
#include "fresh_helpers.h"
#include "equipment_helpers.h"
#include "blend_setup_helpers.h"

struct SetupDma { u32 source, destination, control; };
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];
extern void sub_0804B248(void);

void sub_0804A60C(void)
{
    u32 fill;
    u32 zero;
    volatile struct SetupDma *dma;
    u8 *work;
    u32 offset;
    sub_08049714(gFrameObjects, 8192);
    sub_08049714(gLaterBuffer_030055A0, 512);
    zero = 0;
    fill = zero;
    dma = (volatile struct SetupDma *)0x040000D4;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    dma->control = 0x85000100;
    dma->control;
    sub_08049318();
    sub_08048BB8();
    work = gUnknown_030057E0;
    offset = 0xC8A;
    *(u16 *)(work + offset) = zero;
    work[0xC88] = 0;
    work[0xC89] = 0;
    sub_08049D18(32767, 32.0f, 0.0f, 8.0f);
    sub_0804A210();
}

void sub_0804A944(void)
{
    u32 fill;
    volatile struct SetupDma *dma;
    sub_08049714(gFrameObjects, 8192);
    sub_08049714(gLaterBuffer_030055A0, 512);
    fill = 0;
    dma = (volatile struct SetupDma *)0x040000D4;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    dma->control = 0x85000100;
    dma->control;
    fill = 0;
    dma->source = (u32)&fill;
    dma->destination = 0x05000000;
    dma->control = 0x85000100;
    dma->control;
    *(volatile u16 *)0x04000050 = 0;
    *(volatile u16 *)0x04000054 = 0;
    gBackgroundState_03005310.unknown00[1] = 0;
    sub_080506BC();
    *(volatile u16 *)0x04000000 = 0x1E40;
    gUnknown_030057E0[0xCBA] = 2;
    sub_080480E4();
    sub_0804387C();
    sub_0804842C(14, 0);
    sub_08052AA4();
    sub_08048830();
    sub_08049D18(0, 32.0f, 0.0f, 8.0f);
    sub_0804A210();
}

void sub_0804AA74(void)
{
    u32 fill;
    volatile struct SetupDma *dma;
    sub_08049714(gFrameObjects, 8192);
    sub_08049714(gLaterBuffer_030055A0, 512);
    fill = 0;
    dma = (volatile struct SetupDma *)0x040000D4;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    dma->control = 0x85000100;
    dma->control;
    sub_0804B248();
    *(volatile u16 *)0x04000000 = 0x1E40;
    gUnknown_030057E0[0xCBA] = 2;
    sub_080480E4();
    sub_0804842C(6, 0);
    sub_08049D18(0, 32.0f, 0.0f, 8.0f);
    sub_0804A210();
}

void sub_0804ACD4(void)
{
    u32 fill;
    volatile struct SetupDma *dma;
    sub_08049714(gFrameObjects, 8192);
    sub_08049714(gLaterBuffer_030055A0, 512);
    fill = 0;
    dma = (volatile struct SetupDma *)0x040000D4;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    dma->control = 0x85000100;
    dma->control;
    sub_0804B248();
    *(volatile u16 *)0x04000000 = 0x1E40;
    gUnknown_030057E0[0xCBA] = 2;
    sub_080480E4();
    sub_0804387C();
    sub_0804842C(11, 0);
    sub_08049D18(0, 32.0f, 0.0f, 8.0f);
    sub_0804A210();
}

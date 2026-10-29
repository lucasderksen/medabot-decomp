#include "continued_commands.h"
#include "frame.h"
#include "later_graphics.h"
#include "continued_graphics.h"
#include "fresh_helpers.h"
#include "blend_setup_helpers.h"
#include "continued_map.h"

extern u8 gLaterBuffer_03006D20[];
extern u8 gLaterBuffer_030055A0[];
extern u8 gUnknown_030057E0[];
struct TransitionDmaRegisters { u32 source, destination, control; };

u32 sub_08050CCC(u32 first, u32 second)
{
    u32 complete = 0;
    u32 state = gLaterBuffer_03006D20[11];
    u8 *work = gLaterBuffer_03006D20;
    switch (state)
    {
    case 0:
        if (first != 32)
        {
            s32 steps;
            if (first == 18)
                sub_0804842C(23, 0);
            steps = 8;
            if (first == 8)
                steps = 255;
            sub_08049D90(0, 0.0f, 32.0f, (float)steps);
        }
        gLaterBuffer_03006D20[11]++;
        break;
    case 1:
        if (first == 32)
        {
            sub_080505FC();
            sub_08047878(32, second);
            gLaterBuffer_03006D20[11]++;
        }
        else if (sub_08049E08(0))
        {
            if (first == 18)
                sub_0804842C(24, 0);
            sub_080505FC();
            sub_08047878(first, second);
            gLaterBuffer_03006D20[11]++;
        }
        break;
    case 2:
        sub_08049714(gFrameObjects, 8192);
        sub_08049714(gLaterBuffer_030055A0, 512);
        {
            u32 fill = 0;
            volatile struct TransitionDmaRegisters *dma = (void *)0x040000D4;
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
        }
        sub_0804B248();
        sub_080506BC();
        *(volatile u16 *)0x04000000 = 0x1E40;
        if (first == 16 || first == 32)
            gUnknown_030057E0[0xCBA] = 2;
        else
            gUnknown_030057E0[0xCBA] = 1;
        sub_080480E4();
        sub_08052AA4();
        sub_08048830();
        if (first == 19)
        {
            u8 *position = gLaterBuffer_03005350;
            sub_080533E4(147, *(u32 *)(position + 0x1D8), *(u32 *)(position + 0x1DC), 0);
            while (!sub_08050BC8())
                ;
        }
        if (first != 8)
            sub_08049D18(0, 32.0f, 0.0f, 8.0f);
        switch (first)
        {
        case 32: sub_0804842C(13, 0); break;
        case 1: sub_0804842C(17, 0); break;
        case 3: sub_0804842C(20, 0); break;
        case 19: sub_0804842C(19, 0); break;
        case 0: sub_0804842C(16, 0); break;
        case 2: sub_0804842C(18, 0); break;
        case 8: sub_0804842C(27, 0); break;
        case 5: sub_0804842C(26, 0); break;
        case 16: sub_0804842C(21, 0); break;
        case 18: sub_0804842C(25, 0); break;
        case 17: sub_0804842C(22, 0); break;
        case 20: sub_0804842C(15, 0); break;
        }
        gLaterBuffer_03006D20[11]++;
        break;
    case 3:
        work[11]++;
        break;
    case 4:
        if (first == 8 || sub_08049E08(0))
            complete = 1;
        break;
    }
    return complete;
}

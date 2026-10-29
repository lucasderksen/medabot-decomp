#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "frame_objects.h"
#include "main.h"
#include "graphics.h"
#include "gba.h"


/* Partial observed physical offsets, not the original aggregate type. */
struct MosaicBackingView {
    u8 unknown00[0xC0];
    u16 fieldC0; s16 xC2; s16 yC4; u16 fieldC6;
    u8 byteC8; u8 byteC9; u8 paletteCA; u8 priorityCB;
    u8 unknownCC[0x10]; u8 selectorDC; u8 unknownDD[3];
    u8 delayE0; u8 unknownE1[0x1F];
    u16 field100; s16 x102; s16 y104; u16 field106;
    u8 byte108; u8 byte109; u8 palette10A; u8 priority10B;
    u8 unknown10C[0x10]; u8 selector11C;
};

void sub_080140B0(void)
{
    u8 *initial = gUnknown_03000440;
    u8 *state = initial + 0x84;
    s32 mode = *state;
    u8 *work = gUnknown_03000440;
    switch (mode)
    {
    case 0:
    {
        u8 *base = (u8 *)gFrameObjects;
        struct MosaicBackingView *backing = (struct MosaicBackingView *)base;
        u32 zero = 0;
        backing->fieldC0 = 0xC005;
        backing->selectorDC = zero;
        backing->xC2 = 120;
        backing->yC4 = 56;
        backing->paletteCA = 15;
        backing->priorityCB = 192;
        backing->fieldC6 = 0x0900;
        backing->delayE0 = 8;
        *(volatile u16 *)0x0400004C = (backing->delayE0 << 12) + (backing->delayE0 << 8);
        (*state)++;
        break;
    }
    case 1:
        if (!(gFrameCounter & 1))
        {
            u8 *base = (u8 *)gFrameObjects;
            u8 *delay = base + 0xE0;
            u32 amount = *delay - 1;
            *delay = amount;
            *(volatile u16 *)0x0400004C = (*delay << 12) + (*delay << 8);
            if (!(u8)amount)
            {
                struct MosaicBackingView *backing = (struct MosaicBackingView *)base;
                u32 zero = 0;
                backing->field100 = 0xC224;
                backing->selector11C = zero;
                backing->x102 = 120;
                backing->y104 = 72;
                backing->palette10A = 15;
                backing->priority10B = 192;
                backing->field106 = 0x0901;
                backing->byte109 = 8;
                backing->byte108 = 64;
                (*state)++;
            }
        }
        break;
    case 2:
    {
        struct MosaicBackingView *backing = (struct MosaicBackingView *)gFrameObjects;
        u8 *value = &backing->byte109;
        if ((*value += 8) == 96)
            (*state)++;
        break;
    }
    case 3:
    {
        struct MosaicBackingView *backing = (struct MosaicBackingView *)gFrameObjects;
        u8 *value = &backing->byte109;
        if ((*value -= 8) == 64)
        {
            (*state)++;
            *(u16 *)(work + 0x86) = 0;
        }
        break;
    }
    default:
    {
        u16 *counter = (u16 *)(work + 0x86);
        if (++*counter == 60)
        {
            sub_08040CD0(3, 2);
            CpuFastSet((const void *)0x0850F398, (void *)0x050003E0, 8);
            gUnknown_0300137C++;
        }
        break;
    }
    }
}


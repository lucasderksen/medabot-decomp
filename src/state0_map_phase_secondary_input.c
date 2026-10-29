#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "main.h"
#include "object_helpers.h"
#include "coordinate_helpers.h"
#include "tile_text.h"
#include "render_work.h"
#include "gba.h"


void sub_08013E30(void)
{
    u8 *work;
    u8 *state;
    sub_080182D0();
    sub_08018218();
    sub_080182AC();
    work = gUnknown_03000440;
    state = work + 0x3F;
    switch (*state)
    {
    case 0:
    {
        u8 counter;
        sub_08017CE8();
        sub_0801830C();
        counter = *(u8 *)&gFrameCounter;
        sub_08041C14(8, counter, sub_0801827C());
        sub_080183A4();
        if ((gUnknown_0300058C[1] & 1) && work[0x3C] == 0)
        {
            sub_08074DE0(2);
            sub_080185A8();
            work[0x40] = 0;
            (*state)++;
        }
        else
        {
            if (gUnknown_0300058C[1] & 2)
            {
                u8 *other = gUnknown_03000440;
                if (other[0x3C] == 1)
                {
                    u8 *cleared;
                    sub_08074DE0(2);
                    sub_080185A8();
                    cleared = other;
                    cleared += 0x40;
                    *cleared = 0;
                    cleared--;
                    (*cleared)++;
                    break;
                }
            }
            if (gUnknown_0300058C[0] & 2)
            {
                sub_08074DE0(5);
                sub_0804253C(6, 63, 32);
                gUnknown_0300137C++;
            }
        }
        break;
    }
    case 1:
        if (sub_080185E8())
        {
            work[0x40] = 0;
            (*state)++;
        }
        break;
    case 2:
        if (sub_080187D4())
            (*state)++;
        break;
    case 3:
    {
        u8 *part;
        u8 *selected = work + 0x3D;
        u8 *kind = work + 0x3C;
        u32 index = *kind * 3;
        index += *selected;
        part = (u8 *)0x03001864;
        sub_08015838(index, part);
        sub_08018074(part[0], part[1], part[2], part[3]);
        sub_08018098();
        sub_08043240(0, 8);
        sub_08042698(2, 2, 11, 2, *(volatile u16 *)0x0400000A, 0x63C0);
        sub_08018180();
        *state = 0;
        break;
    }
    }
}

void sub_08013FA8(void)
{
    u8 counter;
    sub_080182D0();
    sub_08017CE8();
    sub_08018218();
    sub_0801830C();
    counter = *(u8 *)&gFrameCounter;
    sub_08041C14(8, counter, sub_0801827C());
    sub_080182AC();
    if (sub_080425DC())
    {
        u8 *cleared = gUnknown_03000440;
        u32 zero;
        u32 objects;
        u32 palette;
        u32 background;
        cleared += 0x96;
        zero = 0;
        *cleared = zero;
        gRenderMode = zero;
        objects = 512;
        CpuFastSet(&objects, gRenderWork->objects, 0x01000100);
        palette = zero;
        CpuFastSet(&palette, (void *)0x05000200, 0x01000080);
        background = zero;
        CpuFastSet(&background, (void *)0x05000000, 0x01000080);
        gUnknown_0300137C = 60;
    }
}

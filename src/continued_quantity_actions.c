#include "global.h"
#include "post_dispatch.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

void sub_0804ED88(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        {
            u32 amount;
            sub_08047C00();
            amount = work[0xC94] << 8;
            amount |= work[0xC95];
            amount *= 10;
            sub_08047BA8(7);
            sub_08047D58(amount);
            sub_08047D24(0, amount);
            *state = 1;
            break;
        }
    case 1:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[26]))
            sub_08050290();
        break;
    }
}

void sub_0804EE8C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        {
            const u8 *selected;
            sub_08047C00();
            sub_08047BA8(14);
            selected = work + 0xC94;
            sub_08047CE4(0, sub_08047BCC(*selected));
            if (sub_08047DB0(*selected))
                *state = 1;
            else
            {
                gQuantityResult_030017EC = sub_08047E20(*selected);
                *state = 2;
            }
            break;
        }
    case 1:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[28]))
            sub_08050290();
        break;
    case 2:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[29]))
        {
            sub_08050CC0();
            (*state)++;
        }
        break;
    case 3:
        if (sub_08050CCC(1, work[0xC94]))
            sub_08050290();
        break;
    }
}

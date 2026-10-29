#include "global.h"
#include "post_dispatch.h"
#include "fresh_helpers.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

void sub_0804E928(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        {
            const u8 *selected;
            s32 amount, requested, delta;
            sub_08047C00();
            selected = work + 0xC94;
            amount = sub_08047D8C(*selected);
            if (amount == 99)
            {
                sub_08047BA8(6);
                sub_08047CE4(0, sub_080480D4(*selected));
                *state = 1;
                break;
            }
            sub_08047BA8(14);
            requested = work[0xC95];
            if (requested + amount > 99)
                delta = 99 - amount;
            else
                delta = requested;
            {
                u8 *nextWork = gUnknown_030057E0;
                const u8 *nextSelected = nextWork + 0xC94;
                sub_08047DC0(*nextSelected, (u8)delta);
                sub_08047CE4(0, sub_080480D4(*nextSelected));
                sub_08047C84(1, delta);
                nextWork[0xC93] = 2;
            }
            break;
        }
    case 1:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[0]))
            sub_08050290();
        break;
    case 2:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[1]))
            sub_08050290();
        break;
    }
}

void sub_0804EA18(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    const void *script;
    switch (*state)
    {
    case 0:
        {
            const u8 *selected;
            s32 amount, requested, delta, difference;
            sub_08047C00();
            selected = work + 0xC94;
            amount = sub_08047D8C(*selected);
            if (amount == 0)
            {
                sub_08047BA8(6);
                sub_08047CE4(0, sub_080480D4(*selected));
                *state = 1;
                break;
            }
            sub_08047BA8(5);
            requested = work[0xC95];
            difference = amount - requested;
            delta = requested;
            if (difference < 0)
                delta = amount;
            sub_08047DD8(*selected, (u8)delta);
            sub_08047CE4(0, sub_080480D4(*selected));
            sub_08047C84(1, delta);
            amount = sub_08047D8C(*selected);
            if (amount == 0)
                *state = 3;
            else
                *state = 2;
            break;
        }
    case 1:
        script = gQuantityScripts_0847E388[2];
        goto showScript;
    case 2:
        script = gQuantityScripts_0847E388[3];
showScript:
        if (sub_08047C24(0, 0, 0, script))
            sub_08050290();
        break;
    case 3:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[4]))
            sub_08050290();
        break;
    }
}

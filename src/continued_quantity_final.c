#include "global.h"
#include "post_dispatch.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

void sub_0804EB0C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        {
            const u8 *selected, *row;
            s32 encoded, amount, requested, delta;
            u8 identifier;
            sub_08047C00();
            selected = work + 0xC94;
            identifier = *selected;
            row = work + 0xC95;
            encoded = sub_08047D9C(identifier, *row);
            amount = (encoded & 0xFF00) >> 8;
            if (amount == 99)
            {
                sub_08047BA8(6);
                sub_08047CE4(0, sub_08047BEC(*row, *selected));
                *state = 1;
                break;
            }
            sub_08047BA8(14);
            requested = work[0xC96];
            if (requested + amount > 99)
                delta = 99 - amount;
            else
                delta = requested;
            {
                u8 *nextWork = gUnknown_030057E0;
                const u8 *nextSelected = nextWork + 0xC94;
                const u8 *nextRow;
                identifier = *nextSelected;
                nextRow = nextWork + 0xC95;
                sub_08047DF0(identifier, *nextRow, (u8)delta);
                sub_08047CE4(0, sub_08047BEC(*nextRow, *nextSelected));
                sub_08047C84(1, delta);
                nextWork[0xC93] = 2;
            }
            break;
        }
    case 1:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[5]))
            sub_08050290();
        break;
    case 2:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[work[0xC95] + 6]))
            sub_08050290();
        break;
    }
}

void sub_0804EC38(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    const void *script;
    switch (*state)
    {
    case 0:
        {
            const u8 *selected, *row;
            s32 encoded, mask, amount, requested, delta, difference;
            u8 identifier;
            sub_08047C00();
            selected = work + 0xC94;
            identifier = *selected;
            row = work + 0xC95;
            encoded = sub_08047D9C(identifier, *row);
            mask = 0xFF00;
            amount = (encoded & mask) / 256;
            if (amount == 0)
            {
                sub_08047BA8(6);
                sub_08047CE4(0, sub_08047BEC(*row, *selected));
                *state = 1;
                break;
            }
            sub_08047BA8(5);
            requested = work[0xC96];
            difference = amount - requested;
            delta = requested;
            if (difference < 0)
                delta = amount;
            sub_08047E08(*selected, *row, (u8)delta);
            sub_08047CE4(0, sub_08047BEC(*row, *selected));
            sub_08047C84(1, delta);
            encoded = sub_08047D9C(*selected, *row);
            if ((encoded & mask) == 0)
                *state = 3;
            else
                *state = 2;
            break;
        }
    case 1:
        script = gQuantityScripts_0847E388[work[0xC95] + 14];
        goto showScript;
    case 2:
        script = gQuantityScripts_0847E388[work[0xC95] + 18];
showScript:
        if (sub_08047C24(0, 0, 0, script))
            sub_08050290();
        break;
    case 3:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[work[0xC95] + 18]))
            sub_08050290();
        break;
    }
}

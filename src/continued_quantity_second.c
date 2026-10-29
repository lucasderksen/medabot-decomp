#include "global.h"
#include "post_dispatch.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

void sub_0804EE00(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        {
            s32 amount, current;
            u32 encoded;
            sub_08047C00();
            encoded = work[0xC94] << 8;
            encoded |= work[0xC95];
            amount = encoded * 10;
            sub_08047BA8(5);
            current = sub_08047D4C();
            if (current - amount <= 0)
                amount = current;
            sub_08047BA8(5);
            sub_08047D74(amount);
            sub_08047D24(0, amount);
            *state = 1;
            break;
        }
    case 1:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[27]))
            sub_08050290();
        break;
    }
}

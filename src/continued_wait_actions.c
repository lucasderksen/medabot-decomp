#include "continued_commands.h"
#include "global.h"
#include "fresh_helpers.h"
#include "palette_transfer_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern void sub_0804B2B0(void);

void sub_0804E43C(void) { if (sub_080508B4()) sub_08050290(); }

void sub_0804E450(void) { if (sub_08050918()) sub_08050290(); }

void sub_0804E464(void) { if (sub_0805082C(gLaterBuffer_03006D20[10])) sub_08050290(); }

void sub_0804E480(void) { sub_0804E498(); }

void sub_0804E48C(void) { sub_0804E498(); }

void sub_0804E51C(void) { sub_0804E534(); }

void sub_0804E528(void) { sub_0804E534(); }

void sub_0804E58C(void) { if (sub_0805082C(gLaterBuffer_03006D20[10])) sub_08050290(); }

void sub_0804E5A8(void) { if (sub_080508B4()) sub_08050290(); }

void sub_0804E5BC(void) { if (sub_08050918()) sub_08050290(); }

void sub_0804E5D0(void) { sub_0804E5F0(0, 1); }

void sub_0804E5E0(void) { sub_0804E5F0(1, 1); }

void sub_0804E498(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050358(work[0xC94], work[0xC95], work[0xC96], work[0xC97]);
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC98], 0);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 1)) sub_08050290();
        break;
    }
}

void sub_0804E534(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC95], 0);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 1)) sub_08050290();
        break;
    }
}

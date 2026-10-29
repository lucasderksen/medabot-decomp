#include "global.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];

void sub_0804F83C(void) { if (sub_080509EC()) sub_08050290(); }

void sub_0804F850(void) { sub_08050290(); }

void sub_0804F860(void) { }

void sub_0804F864(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050358(work[0xC94], work[0xC95], work[0xC96], work[0xC97]);
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC98], 1);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 1))
            sub_08050290();
        break;
    }
}

void sub_0804F8E8(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC95], 1);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 1))
            sub_08050290();
        break;
    }
}

void sub_0804F940(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050358(work[0xC94], work[0xC95], work[0xC96], work[0xC97]);
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC98], 1);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 0))
            sub_08050290();
        break;
    }
}

void sub_0804F9C4(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_080500BC(gLaterBuffer_03006D20[10], work[0xC95], 1);
        (*state)++;
        break;
    case 1:
        if (sub_0805018C(gLaterBuffer_03006D20[10], 0))
            sub_08050290();
        break;
    }
}

void sub_0804FA1C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050CC0();
        (*state)++;
        break;
    case 1:
        if (sub_08050CCC(19, 0))
            sub_08050290();
        break;
    }
}

void sub_0804FA5C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050CC0();
        (*state)++;
        break;
    case 1:
        if (sub_08050CCC(0, 0))
            sub_08050290();
        break;
    }
}

void sub_0804FA9C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050CC0();
        (*state)++;
        break;
    case 1:
        if (sub_08050CCC(2, 0))
            sub_08050290();
        break;
    }
}

void sub_0804FADC(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08050CC0();
        (*state)++;
        break;
    case 1:
        if (sub_08050CCC(8, 0))
            sub_08050290();
        break;
    }
}

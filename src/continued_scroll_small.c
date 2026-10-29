#include "global.h"
#include "continued_commands.h"
extern u8 gUnknown_030057E0[];

void sub_0804F67C(void)
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
        if (sub_08050CCC(3, work[0xC94]))
            sub_08050290();
        break;
    }
}

void sub_0804F5C8(void) { }

void sub_0804F5CC(void) { }

void sub_0804F5D0(void) { }

void sub_0804F5D4(void) { }

void sub_0804F5D8(void) { }

void sub_0804F674(void) { }

void sub_0804F678(void) { }

void sub_0804F6C4(void) { }

void sub_0804F6C8(void) { }

void sub_0804F6CC(void) { }

void sub_0804F6D0(void) { }

void sub_0804F6D4(void) { }

void sub_0804F6D8(void) { }

void sub_0804F6DC(void) { }

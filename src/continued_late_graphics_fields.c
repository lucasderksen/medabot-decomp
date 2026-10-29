#include "global.h"
#include "continued_late_graphics.h"
#include "continued_map_data.h"
#include "continued_commands.h"

/* Observed partial view only; the complete object extent is unknown. */
struct SelectionFields
{
    u8 unknown00[0x24];
    u16 half24;
    u16 half26;
    u16 half28;
    u16 half2A;
    u16 half2C;
    u16 half2E;
    u16 half30;
    u8 byte32;
};

struct SetupFieldView { u8 unknown00[0xC90]; u16 halfC90; };

void sub_080581C8(u32 index)
{
    sub_08049210((const u16 *)((u8 *)gSetupPointer_03006D14 + 0x400),
                  (u16 *)((u8 *)gSetupPointer_03006D14 + 0x800),
                  index * 2 + 1, 6, 8, 2, 264, 14, 0);
}

void sub_08058208(u32 unused)
{
    sub_0805821C(gContinuedOtherWork_030057A0[0x14]);
}

void sub_0805821C(u32 selector)
{
    switch (selector)
    {
    case 0:
        ((struct SelectionFields *)gContinuedOtherWork_030057A0)->half26 =
            gUnknown_030057E0[0x7FE];
        break;
    case 1:
    {
        struct SelectionFields *work = (struct SelectionFields *)gContinuedOtherWork_030057A0;
        work->half28 = ((struct SetupFieldView *)gUnknown_030057E0)->halfC90;
        work->half2A = sub_080531E0(work->half28);
        work->half2C = sub_080532D4(work->half28);
        break;
    }
    case 2:
    case 3:
    case 4:
        break;
    case 5:
        ((struct SelectionFields *)gContinuedOtherWork_030057A0)->byte32 = 0;
        break;
    case 6:
    {
        struct SelectionFields *work = (struct SelectionFields *)gContinuedOtherWork_030057A0;
        work->byte32 = 0;
        work->half24 = 0;
        break;
    }
    }
}

void sub_080582B8(u32 selector, s32 mode)
{
    switch (selector)
    {
    case 0:
        break;
    case 1:
        switch (mode)
        {
        case 0:
        {
            struct SelectionFields *work = (struct SelectionFields *)gContinuedOtherWork_030057A0;
            work->half2A = sub_080531E0(work->half28);
            work->half2C = sub_080532D4(work->half28);
            break;
        }
        case 1:
        case 2:
        {
            struct SelectionFields *work = (struct SelectionFields *)gContinuedOtherWork_030057A0;
            sub_0805321C(work->half28, (u8)work->half2A);
            sub_08053238(work->half28, (u8)work->half2C);
            break;
        }
        }
        break;
    }
}

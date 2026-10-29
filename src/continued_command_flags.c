#include "continued_commands.h"
#include "global.h"
#include "palette_transfer_helpers.h"

extern u8 gUnknown_030057E0[];
/* Copied routines consume two observed word slots. */

struct RecordFlagsByte
{
    u8 slot : 5;
    u8 unknown5 : 1;
    u8 unknown6 : 1;
    u8 unknown7 : 1;
} __attribute__((packed));

void sub_0804D5F0(void)
{
    u8 *work;
    u32 flags;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    flags = work[0xC94];
    if (flags & 0x10)
    {
        if (flags & 0x40)
        {
            u8 *argument = work + 0xC95;
            if (*argument == 0)
                sub_080487C8(47);
            else
                sub_080507BC(47, *argument);
            goto complete;
        }
        if (flags & 0x20)
        {
            u8 *row = work + work[0xCB4] * 8;
            if ((*(u16 *)(row + 0x5DE) & 0xFFF) == *(u16 *)(work + 0xC8E))
            {
                u8 index = ((struct RecordFlagsByte *)(row + 0x5E0))->slot + 49;
                u8 *argument = work + 0xC95;
                if (*argument == 0)
                    sub_080487C8(index);
                else
                    sub_080507BC(index, *argument);
            }
            goto complete;
        }
        {
            u8 *argument = work + 0xC95;
            if (*argument == 0)
            {
                u32 index = 15;
                index &= flags;
                sub_080487C8((u8)(sub_0804DBF0(index) + 79));
            }
            else
            {
                u32 index = 15;
                index &= flags;
                sub_080507CC(index, *argument);
            }
        }
        goto complete;
    }
    if (flags & 0x40)
    {
        sub_080507EC(47, work[0xC95]);
        goto complete;
    }
    if (flags & 0x20)
    {
        u8 *row = work + work[0xCB4] * 8;
        if ((*(u16 *)(row + 0x5DE) & 0xFFF) == *(u16 *)(work + 0xC8E))
        {
            flags = (u8)(((struct RecordFlagsByte *)(row + 0x5E0))->slot + 49);
            sub_080507EC(flags, work[0xC95]);
        }
        goto complete;
    }
    {
        u32 index = 15;
        index &= flags;
        sub_0805080C(index, work[0xC95]);
    }
complete:
    return;
}

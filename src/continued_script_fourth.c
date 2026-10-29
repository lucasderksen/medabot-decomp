#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "packed_fields.h"
#include "later_graphics.h"
#include "post_dispatch.h"
#include "utility_helpers.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern void sub_08052E58(u32 first, u32 second, u32 mode);

void sub_0804D100(void)
{
    struct Record8 { u8 first, second; u16 identifier; u8 unknown[4]; };
    u8 *work;
    struct Record8 *record;
    struct Record8 *base;
    u32 selector;
    u32 match, requested;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    selector = work[0xCB4] * 8;
    base = (struct Record8 *)(work + 0x5DC);
    record = (struct Record8 *)((u32)base + selector);
    match = record->identifier & 0xFFF;
    requested = work[0xC94] << 8;
    requested |= work[0xC95];
    if (match == requested)
        sub_08052E58(record->first, record->second, 0);
}

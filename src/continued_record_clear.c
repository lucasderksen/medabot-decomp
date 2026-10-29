#include "continued_commands.h"
#include "global.h"
#include "object_numeric_helpers.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];
extern const u8 *const gRecordByteTables_08404334[];
extern void sub_08052E58(u32 first, u32 second, u32 mode);

struct RecordFlagsByte
{
    u8 slot : 5;
    u8 unknown5 : 1;
    u8 active : 1;
    u8 unknown7 : 1;
} __attribute__((packed));

struct Record8
{
    u8 first, second;
    u16 identifier;
    struct RecordFlagsByte flags;
    u8 unknown5[3];
};

void sub_0804D980(void *record)
{
    u8 *saved = record;
    struct Record8 *row = (struct Record8 *)saved;
    const u8 *const *tables = gRecordByteTables_08404334;
    u8 *work = gUnknown_030057E0;
    const u8 *source = tables[work[0x7FE]];
    u32 first = row->first;
    u32 second = row->second;
    u32 width = *(u16 *)(work + 0x800) >> 1;
    u32 offset = second * width;
    source += offset + first;
    sub_08052E58(first, second, *source);
    if (row->flags.active)
    {
        sub_08048888((u8)(row->flags.slot + 49));
        sub_08048888((u8)(row->flags.slot + 91));
    }
    sub_08049714(saved, 8);
}
